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

// Преобразование номера в нужный (PDU) и обратно (текстовый)
String TForm1::workNumber(String number, String type){

	if(type == "uncode"){

		// Удаляем 1 символ +
		number.Delete(1,1);

		// Если число нечетное, до добавляем F в конце
		if(number.Length() % 2 == 1)
			number = number + "F";
	}

	// Меняем числа местами
	int i = 1;
	char swap[1];

	while(i < number.Length()){

		swap[0] = number[i];
		number[i] = number[i+1];
		number[i+1] = swap[0];

		i = i + 2;
	}

	// Удаляем F, если число нечетное
	if(type == "decode")
		if(number[ number.Length() ] == 'F')
			number.Delete( number.Length() ,1);

	// Добавляем + в начало, если декодируем
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

	// Проверка на ввод данных
	if(Edit1->Text == "" || Edit1->Text.Length() < 12){
		Label4->Caption = "Неверный формат номера.";
		return;
	}

	// Проверка на ввод текста
	if(Edit2->Text == "" || Edit1->Text.Length() < 1){
		Label5->Caption = "Не введен текст.";
		return;
	}

	// Очищаем все
	Label4->Caption = "";
	Label5->Caption = "";
	text = "";
	textNew = "";
	fullStr = "";
	Memo2->Clear();
	String Recipient = "";

	// Формируем номер
	String EncodeNum = workNumber(Edit1->Text, "uncode");

	// Кол-во символов в номере
	if(EncodeNum[ EncodeNum.Length() -1 ] == 'F')
		Recipient = IntToHex( EncodeNum.Length()-1 , 2) + "91" + EncodeNum;
	else
		Recipient = IntToHex( EncodeNum.Length() , 2) + "91" + EncodeNum;

	// Текст сообщения
	text = Edit2->Text;

	// Массив с байтами символов
	TBytes FirstLine;
	FirstLine = TEncoding::Unicode->GetBytes(text);

	// Формируем массив байтов для PDU
	for(int i = 0; i < FirstLine.Length; i+=2)
		textNew = textNew + IntToHex(FirstLine[i+1], 2) + "" + IntToHex(FirstLine[i], 2);

	// Выводим полный результат PDU строки
	Memo2->Lines->Add("000100" + Recipient + "000812" + "" + textNew);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	// Ввод только чисел и backspace
	if( Key != 8 && ( (Key < '0' || Key > '9' ) ) ) Key = NULL;
	else if( Key == 8 && Edit1->Text.Length() == 1 && Edit1->Text[1] == '+')
		Key = NULL;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	// Получаем содержание
	String pduFull = Memo1->Lines->GetText();

	// Проверка на пустату и кол-во символов
	if(pduFull == ""){
		Label8->Caption = "Вы не ввели PDU.";
		return;
	}
	else if(pduFull.Length() < 28){
		Label8->Caption = "Неверный формат PDU.";
		return;
	}

	Label8->Caption = "";
	Edit3->Text = "";
	Edit4->Text = "";
	int countNum = 0;

	// Удаляем первые служебные данные
	pduFull.Delete(1,6);

	// Переменная для номера
	String numberMob;

	// Переводим 16 ричную в 10 чную (кол-во символов в телефоне)
	AnsiString countNumber = pduFull.SubString(1,2);
	std::string hex;
	hex = countNumber.c_str();
	std::istringstream stream(hex);
	stream >> std::hex >> countNum;

	// Удаляем информацию об кол-во символов и
	pduFull.Delete(1,4);

	// Если
	if(countNum % 2 == 1)
		countNum = countNum + 1;

    // Вытаскивает номер
	for(int i = 1; i <= countNum; i++)
		numberMob = numberMob + pduFull[i];

	// Получаем нормальный номер и вставляем его
	Edit3->Text = workNumber(numberMob, "decode");

	// Вырезаем номер и оставляем только текст
	pduFull.Delete(1,6+countNum);

	// Строка для переделываения в символ
	String textConv;

	// Перебираем коды символов в сами символы
	for(int i = 1; i <= pduFull.Length()-2; i+=4){
		textConv = (String)"0x" + (String)pduFull[i] + (String)pduFull[i+1] + (String)pduFull[i+2] + (String)pduFull[i+3];
		Edit4->Text = Edit4->Text + wchar_t( StrToInt(textConv) );
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
	// Вставляем + в начало (если удалено)
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



