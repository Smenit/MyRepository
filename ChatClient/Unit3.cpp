//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Unit1.h"
#include "Unit3.h"
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
  : TForm(Owner)                                                //PhoneSR
{                                                                 //PhoneSMS
  randomize();
}

//---------------------------------------------------------------------------
void TForm3::DCodeBig()
{
String * test = new String [5];
String PDUcode;
String Number; //Не перевернутый номер
String resNumber;//Перевернутый номер
String FullString;
String LText;
String DText;
String Sim;
String NStrs;
String Text;
String NStrsInt;
int f=0;
String PhoneSrL; //Длина номера телефона
String SMSC;        //Сам номер смс центра  не перевернутый
String resSMS;     // Номер sms центра перевернутый
   FullString=PDUMessage->Lines->GetText();
   int iProv = 1;
while(iProv <= FullString.Length())
  {
    if(FullString[iProv] == '\r')
        FullString.Delete(iProv, 2);
    iProv++;
  }
 String SMSCLength;

 SMSCLength=FullString.SubString(0,2);
 AnsiString len = SMSCLength;
   std::string hex;
  hex = len.c_str();
  std::istringstream stream(hex);
  int dec;
  stream >> std::hex >> dec;
dec=dec*2;






SMSC=FullString.SubString(5,dec-2);
int i=1;
  while(i<dec-2)
  {
  resSMS=resSMS+SMSC[i+1]+SMSC[i];
  i+=2;
  }


if (resSMS[resSMS.Length()]=='F')
resSMS.Delete(resSMS.Length(),1);
resSMS=resSMS.Insert("+", 1);





PhoneSrL=FullString.SubString(dec+7,2);




AnsiString Nlen = PhoneSrL;

  hex = Nlen.c_str();
  std::istringstream Nstream(hex);
  int Ndec;
  Nstream >> std::hex >> Ndec;
  if (Ndec%2==0) {
    Ndec=Ndec-1;
  }


Number=FullString.SubString(dec+11,Ndec+1);



  i=1;
  while(i<Ndec+1)
  {
  resNumber=resNumber+Number[i+1]+Number[i];
  i+=2;
  }

   if (resNumber[resNumber.Length()]=='F')
resNumber.Delete(resNumber.Length(),1);
resNumber=resNumber.Insert("+", 1);

 PhoneSR->Text=resNumber;


NStrs=FullString.SubString(dec+9+10+Ndec+7,2);

AnsiString NTlen = NStrs;
hex = NTlen.c_str();
  std::istringstream NTSstream(hex);
  int NTdecStrs;
  NTSstream >> std::hex >> NTdecStrs;



 for ( int j = 0; j<NTdecStrs; j++) {


LText=FullString.SubString(dec+9+Ndec+7,2);
 AnsiString NTlen = LText;

  hex = NTlen.c_str();
  std::istringstream NTstream(hex);
  int NTdec;
  NTstream >> std::hex >> NTdec;
  NTdec=NTdec*2;
  NTdec=NTdec-12;







 Text=FullString.SubString(dec+9+Ndec+7+2+12,NTdec);

for (int i = 1; i <=NTdec; i+=4) {


 Sim=Text.SubString(i,4);

 Sim=wchar_t(StrToInt("0x"+Sim));

DText=DText+""+Sim;
Sim="";


}



FullString=FullString.Delete(1,2+dec+9+Ndec+7+2+NTdec+9);
TextMessage->Text=DText;
//TextMessage->Text=FullString;



 }

 PhoneSMS->Text=resSMS;




}




void TForm3::CheckPduHeader()
{
    String FullString; //Вся строка
    String SMSCLength;  //Длина номера смс центра
    String PhoneSrL;    //Длина номер получателся
    String Text;        //Обрезанный текст в 16ричной
    String SMSC;        //Сам номер смс центра  не перевернутый
  String Number;      //Cам номер получателя  не перевернутый
  String resNumber;   // Номер получателся перевернутый
  String Sim;        //Используется для декода каждого символа
  String resSMS;     // Номер sms центра перевернутый
  String DText;      //  Раскодированный в USC  текс
  String LText;      //Длина не раскодированного текста
  String PDUheader;
  FullString=PDUMessage->Lines->GetText();
  SMSCLength=FullString.SubString(0,2);

  AnsiString len = SMSCLength;
  std::string hex;
  hex = len.c_str();
  std::istringstream stream(hex);
  int dec;
  stream >> std::hex >> dec;
  dec=dec*2;

  PDUheader=FullString.SubString(dec+3,2);

  if (PDUheader=="01")
  {
    PhoneSrL=FullString.SubString(dec+7,2);




    AnsiString Nlen = PhoneSrL;

  hex = Nlen.c_str();
  std::istringstream Nstream(hex);
  int Ndec;
  Nstream >> std::hex >> Ndec;
  if (Ndec%2==0) {
    Ndec=Ndec-1;
  }

LText=FullString.SubString(dec+9+Ndec+7,2);
 AnsiString NTlen = LText;

  hex = NTlen.c_str();
  std::istringstream NTstream(hex);
  int NTdec;
  NTstream >> std::hex >> NTdec;
  NTdec=NTdec*2;

Text=FullString.SubString(dec+9+Ndec+7+2,NTdec);

for (int i = 1; i <=NTdec; i+=4) {


 Sim=Text.SubString(i,4);

 Sim=wchar_t(StrToInt("0x"+Sim));

DText=DText+""+Sim;
Sim="";

}


TextMessage->Text=DText;

SMSC=FullString.SubString(5,dec-2);
int i=1;
  while(i<dec-2)
  {
  resSMS=resSMS+SMSC[i+1]+SMSC[i];
  i+=2;
  }




if (resSMS[resSMS.Length()]=='F')
  resSMS.Delete(resSMS.Length(),1);


resSMS=resSMS.Insert("+", 1);
 PhoneSMS->Text=resSMS;


///////////////////////////////////////////////////////////////////////
Number=FullString.SubString(dec+11,Ndec+1);


 i=1;
  while(i<Ndec+1)
  {
  resNumber=resNumber+Number[i+1]+Number[i];
  i+=2;
  }

   if (resNumber[resNumber.Length()]=='F')
    resNumber.Delete(resNumber.Length(),1);


resNumber=resNumber.Insert("+", 1);

 PhoneSR->Text=resNumber;

}

if (PDUheader=="41")
{
DCodeBig();
}





}



String TForm3::CodingPhoneNumber(String phoneNumber)
{
    String result; // готовый номер получателя

    if(phoneNumber[1] == '+') //отбрасываем +
       phoneNumber.Delete(1,1);
    if(phoneNumber.Length() % 2 != 0) //добавление F, если надо
        phoneNumber += "F";

    int i = 1;
    while(i < phoneNumber.Length()) //меняем местами соседние символы
    {
        Swap(phoneNumber[i], phoneNumber[i+1]);
        i+=2;
    }

    result+=phoneNumber;



    return result;
}
//---------------------------------------------------------------------------
String TForm3::FullPhoneNumberSMS(String phone)
{
    String fullPhone = IntToHex((CodingPhoneNumber(phone).Length() / 2) + 1, 2) + "91" +
    CodingPhoneNumber(phone);
    return fullPhone;
}
String TForm3::FullPhoneNumberSR(String phone)
{
    String fullPhone;
    int phoneLength = (phone.Length())-1;
    if(phoneLength % 2 == 0)
    {
      fullPhone = IntToHex(CodingPhoneNumber(phone).Length(), 2) + "91" +
      CodingPhoneNumber(phone);
    }
    else if(phoneLength % 2 != 0)
    {
        fullPhone = IntToHex((CodingPhoneNumber(phone).Length())-1, 2) + "91" +
      CodingPhoneNumber(phone);
    }
    return fullPhone;
}
String TForm3::MessageLength(String Text) //длина сообщения в байтах
{
    String Len = IntToHex((Text.Length())*2, 2);

    return Len;
}
String TForm3::CodingText(String Text)
{
    String Str;
    TBytes bytes = TEncoding::Unicode->GetBytes(Text);  //получаем массив байтов
    for(int i = 0; i < bytes.Length; i+=2) //меняем байты местами
    {
        Swap(bytes[i], bytes[i+1]);
    }
    for(int i = 0; i < bytes.Length; i++) //переводим байты в Hex
    {
        Str = Str + IntToHex(bytes[i], 2);
    }
    return Str;
}
void __fastcall TForm3::btnCodingClick(TObject *Sender)
{
  if(TextMessage->Text.Length() <= 70)
    {
        PDUMessage->Clear();
      PDUMessage->Lines->Add(FullPhoneNumberSMS(PhoneSMS->Text)+ "0100" +
        FullPhoneNumberSR(PhoneSR->Text) + "0008" + MessageLength(TextMessage->Text) +
        CodingText(TextMessage->Text));
    }
    else if(TextMessage->Text.Length() > 70)
    {
        PDUMessage->Clear();
        int count = ceil((TextMessage->Text.Length())/67.);
        int COUNT = count;
        String Text = TextMessage->Text;
    String * test = new String [count];
    int i = 0, TP_MR = 0;
		int refNum = random(255);
        while(count != 0)
        {
            //PDUMessage->Lines->Add(Text.SubString(1, 67));
            //Text.Delete(1, 67);
            test[i] = Text.SubString(1, 67);
      Text.Delete(1, 67);

      PDUMessage->Lines->Add(FullPhoneNumberSMS(PhoneSMS->Text) + "41" + IntToHex(TP_MR, 2) +
      FullPhoneNumberSR(PhoneSR->Text) + "0008" + IntToHex((test[i].Length())*2+6, 2) + "050003" +
      IntToHex(refNum, 2) + IntToHex(COUNT, 2) + IntToHex(i+1, 2) + CodingText(test[i]));
      count--;
      i++;
      TP_MR++;
        }

  }
}
//---------------------------------------------------------------------------
void TForm3::Swap(wchar_t & a, wchar_t & b) //меняем местами соседние элементы
{
    wchar_t temp;
    temp = a;
    a = b;
    b = temp;
}
//---------------------------------------------------------------------------
void TForm3::Swap(unsigned char & a, unsigned char  & b) //меняем местами соседние элементы
{
    unsigned char temp;
    temp = a;
    a = b;
    b = temp;
}

void __fastcall TForm3::PhoneSRChange(TObject *Sender)
{
    if (PhoneSR->Text=="")
    PhoneSR->Text="+";

  if (PhoneSR->Text[1]!='+')
    PhoneSR->Text="+";
}
//---------------------------------------------------------------------------

void __fastcall TForm3::PhoneSRKeyPress(TObject *Sender, System::WideChar &Key)
{
    if( Key != VK_BACK && (Key < '0' || Key > '9'))
      Key = NULL;
   else if( Key == VK_BACK && PhoneSR->Text.Length() == 1 && PhoneSR->Text[1] == '+')
        Key = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::PhoneSMSChange(TObject *Sender)
{
    if (PhoneSMS->Text=="")
    PhoneSMS->Text="+";

  if (PhoneSMS->Text[1]!='+')
    PhoneSMS->Text="+";
}
//---------------------------------------------------------------------------

void __fastcall TForm3::PhoneSMSKeyPress(TObject *Sender, System::WideChar &Key)
{
    if( Key != VK_BACK && (Key < '0' || Key > '9'))
      Key = NULL;
    else if( Key == VK_BACK && PhoneSMS->Text.Length() == 1 && PhoneSMS->Text[1] == '+')
        Key = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
  CheckPduHeader();
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
Form1->Visible=true;
Form3->Visible=false;
}
//---------------------------------------------------------------------------

