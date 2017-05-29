//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
#include <System.JSON.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int n=0;// n - непрочитанные сообщения
String userID;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

TrayIcon1->Icons = new TImageList(this);
	 TIcon *MyIcon = new TIcon;
	if(n!=0) //проверка на пришедшие сообщения
	{
	//смена иконка в tray
	MyIcon->LoadFromFile("2.ico");
	TrayIcon1->Icon->Assign(MyIcon);
	TrayIcon1->Icons->AddIcon(MyIcon);
    //сами уведомления
	TrayIcon1->BalloonTimeout = 3000; // Ставлю на 3 секунды
	TrayIcon1->BalloonTitle = "Вам сообщение";
	TrayIcon1->BalloonHint ="Кол-во непрочитанных сообщений: "+IntToStr(n);
	TrayIcon1->ShowBalloonHint(); // Вызов
	 }
	else
	{
	 MyIcon->LoadFromFile("1.ico");
	TrayIcon1->Icon->Assign(MyIcon);
	TrayIcon1->Icons->AddIcon(MyIcon);
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Form1->Caption = "Осьминожка";
// проверка на заполненость Edit
if (LogIN->Text == "")

{ShowMessage("Вы не ввели логин");}

else

if (IP->Text == "")

{ShowMessage ("Вы не ввели IP-сервера");}

else
 if(Port->Text=="")
	{
		ShowMessage("Введите Порт");
		return;
	}
else
{
//Подключение к серверу

	    // ПО нажатию
    ClientSocket1->Address = IP->Text; // IP
    ClientSocket1->Port = StrToInt(Port->Text); // Порт
    ClientSocket1->Active = true;
		//JSON
		TJSONObject *o = new TJSONObject();
		o->AddPair( new TJSONPair("type","connect") );
		o->AddPair( new TJSONPair("login",LogIN->Text) );
		//Отправка на сервер инф. о подключении клиента
		ClientSocket1->Socket->SendText(o->ToString());

Form1->Timer1->Enabled=true;
BitBtn1->Visible = true;
Disconnect->Visible = true;
Button3->Visible = true;
Button5->Visible = true;
Chat->Visible = true;
Message->Visible = true;
Label5->Visible = true;

Label1->Visible = false;
Label2->Visible = false;
Label3->Visible = false;
Label4->Visible = false;
LogIN->Visible = false;
IP->Visible = false;
Port->Visible = false;
Button1->Visible = false;
Button2->Visible = false;
Button4->Visible = false;

}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket)

{
	Chat->Lines->Add("Мы подключились");
		//JSON
		TJSONObject *o = new TJSONObject();
		o->AddPair( new TJSONPair("type","connect") );
		o->AddPair( new TJSONPair("login",LogIN->Text) );
		//Отправка на сервер инф. о подключении клиента
		ClientSocket1->Socket->SendText(o->ToString());
		Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket)

{

// Строка пришедшая от пользователя
String text = Socket->ReceiveText();

// Разбираем пришедшие данные
TJSONObject *bustStr = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::UTF8->GetBytes( text ),0);




		//Уведомляем клиента о входе в сеть других пользователей
	if( transferText( bustStr->Pairs[0]->JsonValue->ToString() ) == "infoConnect"){

	Chat->Lines->Add(transferText(bustStr->Pairs[1]->JsonValue->ToString())+" появился в сети");
	}

    	//Уведомляем клиента о входе в сеть других пользователей
	if( transferText( bustStr->Pairs[0]->JsonValue->ToString() ) == "infoDisonnect"){

	Chat->Lines->Add(transferText(bustStr->Pairs[1]->JsonValue->ToString())+" вышел из сети");
	}

		//Сообщения
	if( transferText( bustStr->Pairs[0]->JsonValue->ToString() ) == "message"){

	Chat->Lines->Add(transferText(bustStr->Pairs[1]->JsonValue->ToString())+" :  "+transferText(bustStr->Pairs[2]->JsonValue->ToString()));
	}


	  /*
     	//Уведомляем клиента о входе в сеть других пользователей
	if( transferText( bustStr->Pairs[0]->JsonValue->ToString() ) == "infoConnect"){

	Chat->Lines->Add(transferText(bustStr->Pairs[1]->JsonValue->ToString()))+" появился в сети";
	}
	   */

 // Если нет типа, то выкидываем
	if( transferText( bustStr->Pairs[0]->JsonString->ToString() ) != "type")
		return;


  //Memo1->Lines->Add(Socket->ReceiveText());
  //Memo1->Text=Socket->ReceiveText();
}
//---------------------------------------------------------------------------
 String TForm1::transferText(String text)
 {

	text.Delete(1,1);
	text.Delete(text.Length(),1);

	return text;
 }
//----------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Connecting(TObject *Sender, TCustomWinSocket *Socket)

{
	Chat->Lines->Add("Попытка присоединиться...");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket)

{
 Chat->Lines->Add("Мы отключились");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
Chat->Lines->Add("Ошибка");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PortKeyPress(TObject *Sender, System::WideChar &Key)
{
	// Ввод только чисел и backspace
    if( Key != 8 && ( (Key < '0' || Key > '9' ) ) ) Key = NULL;
	else if( Key == 8 && Port->Text.Length() == 1 && Port->Text[1] == '+')
        Key = NULL;
	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   CanClose = false;
	TrayIcon1->Visible = true;
	ShowWindow(Form1->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
    TrayIcon1->Visible = false;
	ShowWindow(Form1->Handle, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
  if(Button==mbRight)
TrayIcon1->PopupMenu = PopupMenu1;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::CloseClick(TObject *Sender)
{
 TrayIcon1->Visible = false;
 Application->Terminate();
 //Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DisconnectClick(TObject *Sender)
{
Form1->Caption = "Вход";
Chat->Lines->Clear();
Message->Text = "";
IP->Text = "";
Port->Text = "";
//Скрытие всего что находилось на форме
Form1->Timer1->Enabled=false;
BitBtn1->Visible = false;
Disconnect->Visible = false;
Button3->Visible = false;
Chat->Visible = false;
Message->Visible = false;
Label5->Visible = false;
 //Открытие нужных элементов
Label1->Visible = true;
Label2->Visible = true;
Label3->Visible = true;
Label4->Visible = true;
LogIN->Visible = true;
IP->Visible = true;
Port->Visible = true;
Button1->Visible = true;
Button2->Visible = true;
Button4->Visible = true;
Button5->Visible = false;

			TJSONObject *o = new TJSONObject();
		o->AddPair( new TJSONPair("type","disconnect") );
		o->AddPair( new TJSONPair("login",LogIN->Text) );
		//Отправка на сервер инф. о подключении клиента
		ClientSocket1->Socket->SendText(o->ToString());
		 Timer1->Enabled=false;
		ClientSocket1->Active = false;
		Chat->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  /*
	TJSONObject *o = new TJSONObject();
		o->AddPair( new TJSONPair("type","online") );
		o->AddPair( new TJSONPair("login",LogIN->Text) );
		//Отправка на сервер инф. о состоянии клиента
		ClientSocket1->Socket->SendText(o->ToString());
	 */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if(Message->Text==""){
		ShowMessage("Введите текст который надо отправить");
		return;
	}

	// Отправка текста
  //  AnsiString Time = Now().FormatString("hh:nn");
	// Memo1->Lines->Add(Time);

		//JSON
		TJSONObject *o = new TJSONObject();
		o->AddPair( new TJSONPair("type","message") );
		o->AddPair( new TJSONPair("login",LogIN->Text) );
		o->AddPair( new TJSONPair("text",Message->Text) );

		//Отправка на сервер
	   // Chat->Lines->Add(LogIN->Text+" :  "+Message->Text);
		ClientSocket1->Socket->SendText(o->ToString());

	Message->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
 Application->Terminate();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::MessageKeyPress(TObject *Sender, System::WideChar &Key)
{
if(Key == VK_RETURN){
		Button3Click(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
Form1->Visible=false;
Form3->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
Button5->Visible=false;
}
//---------------------------------------------------------------------------

