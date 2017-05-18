//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <string.h>
#include <iostream>     // std::cout
#include <sstream>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}

// �������������� ������ � ������ (PDU) � ������� (���������)
String TForm1::workNumber(String number, String type){

	if(type == "uncode"){

		// ������� 1 ������ +
		number.Delete(1,1);

		// ���� ����� ��������, �� ��������� F � �����
		if(number.Length() % 2 == 1)
			number = number + "F";
	}

	// ������ ����� �������
	int i = 1;
	char swap[1];

	while(i < number.Length()){

		swap[0] = number[i];
		number[i] = number[i+1];
		number[i+1] = swap[0];

		i = i + 2;
	}

	// ������� F, ���� ����� ��������
	if(type == "decode")
		if(number[ number.Length() ] == 'F')
			number.Delete( number.Length() ,1);

	// ��������� + � ������, ���� ����������
	if(type == "decode")
		number = "+" + number;

	return number;

}


//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	String text;
	String textNew;
	String fullStr;

	// �������� �� ���� ������
	if(Edit1->Text == "" || Edit1->Text.Length() < 12){
		Label4->Caption = "�������� ������ ������.";
		return;
	}

	// �������� �� ���� ������
	if(Edit2->Text == "" || Edit1->Text.Length() < 1){
		Label5->Caption = "�� ������ �����.";
		return;
	}

	// ������� ���
	Label4->Caption = "";
	Label5->Caption = "";
	text = "";
	textNew = "";
	fullStr = "";
	Memo2->Clear();
	String Recipient = "";

	// ��������� �����
	String EncodeNum = workNumber(Edit1->Text, "uncode");

	// ���-�� �������� � ������
	if(EncodeNum[ EncodeNum.Length() -1 ] == 'F')
		Recipient = IntToHex( EncodeNum.Length()-1 , 2) + "91" + EncodeNum;
	else
		Recipient = IntToHex( EncodeNum.Length() , 2) + "91" + EncodeNum;

	// ����� ���������
	text = Edit2->Text;

	// ������ � ������� ��������
	TBytes FirstLine;
	FirstLine = TEncoding::Unicode->GetBytes(text);

	// ��������� ������ ������ ��� PDU
	for(int i = 0; i < FirstLine.Length; i+=2)
		textNew = textNew + IntToHex(FirstLine[i+1], 2) + "" + IntToHex(FirstLine[i], 2);

	// ������� ������ ��������� PDU ������
	Memo2->Lines->Add("000100" + Recipient + "000812" + "" + textNew);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	// ���� ������ ����� � backspace
	if( Key != 8 && ( (Key < '0' || Key > '9' ) ) ) Key = NULL;
	else if( Key == 8 && Edit1->Text.Length() == 1 && Edit1->Text[1] == '+')
		Key = NULL;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	// �������� ����������
	String pduFull = Memo1->Lines->GetText();

	// �������� �� ������� � ���-�� ��������
	if(pduFull == ""){
		Label8->Caption = "�� �� ����� PDU.";
		return;
	}
	else if(pduFull.Length() < 28){
		Label8->Caption = "�������� ������ PDU.";
		return;
	}

	Label8->Caption = "";
	Edit3->Text = "";
	Edit4->Text = "";
	int countNum = 0;

	// ������� ������ ��������� ������
	pduFull.Delete(1,6);

	// ���������� ��� ������
	String numberMob;

	// ��������� 16 ������ � 10 ���� (���-�� �������� � ��������)
	AnsiString countNumber = pduFull.SubString(1,2);
	std::string hex;
	hex = countNumber.c_str();
	std::istringstream stream(hex);
	stream >> std::hex >> countNum;

	// ������� ���������� �� ���-�� �������� �
	pduFull.Delete(1,4);

	// ����
	if(countNum % 2 == 1)
		countNum = countNum + 1;

    // ����������� �����
	for(int i = 1; i <= countNum; i++)
		numberMob = numberMob + pduFull[i];

	// �������� ���������� ����� � ��������� ���
	Edit3->Text = workNumber(numberMob, "decode");

	// �������� ����� � ��������� ������ �����
	pduFull.Delete(1,6+countNum);

	// ������ ��� �������������� � ������
	String textConv;

	// ���������� ���� �������� � ���� �������
	for(int i = 1; i <= pduFull.Length()-2; i+=4){
		textConv = (String)"0x" + (String)pduFull[i] + (String)pduFull[i+1] + (String)pduFull[i+2] + (String)pduFull[i+3];
		Edit4->Text = Edit4->Text + wchar_t( StrToInt(textConv) );
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
	// ��������� + � ������ (���� �������)
	if(Edit1->Text.Length() == 0)
		Edit1->Text = '+';
	else if(Edit1->Text.Length() > 1 && Edit1->Text[1] != '+'){

		String textNumCheck = Edit1->Text;

		for(int i = 1; i <= textNumCheck.Length(); i++){

			if(textNumCheck[i] == '+'){
				textNumCheck.Delete(i,1);
				break;
			}
		}

		Edit1->Text = "+" + textNumCheck;
	}


}
//---------------------------------------------------------------------------



