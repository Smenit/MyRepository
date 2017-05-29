//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.JSON.hpp>
#pragma hdrstop

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

// Время
String loginUser;

// Удаляем "" в JSON строке
String TForm1::transferText(String text){

	text.Delete(1,1);
	text.Delete(text.Length(),1);

	return text;
}

// Формируем JSON (возвращает Логин) при коннекте клиента
String TForm1::connectJsonRes(String login){

	TJSONObject *jsonRes = new TJSONObject();
	__try {
		jsonRes->AddPair( new TJSONPair("type","infoConnect") );
		jsonRes->AddPair( new TJSONPair("login",login) );
	}

	__finally {

	}

	return jsonRes->ToString();
}

// Формируем JSON (возвращает Логин) при дисконнекте клиента
String TForm1::disonnectJsonRes(String login){

	TJSONObject *jsonRes = new TJSONObject();
	__try {
		jsonRes->AddPair( new TJSONPair("type","infoDisonnect") );
		jsonRes->AddPair( new TJSONPair("login",login) );
	}

	__finally {

	}

	return jsonRes->ToString();
}

// Формируем JSON строку для возврата клиенту (возвращает Тип, Логин и текст)
String TForm1::messageJsonRes(String login, String text){

	TJSONObject *jsonRes = new TJSONObject();
	__try {
		jsonRes->AddPair( new TJSONPair("type","message") );
		jsonRes->AddPair( new TJSONPair("login",login) );
		jsonRes->AddPair( new TJSONPair("text",text) );
	}

	__finally {

	}

	return jsonRes->ToString();
}

// Рассылка между пользователя
int TForm1::serverDispatch(String type, String senderLogin, String text){

	// Рассылка при подключении пользователя
	if(type == "connect"){

		// Проходим по всем пользователям
		for(int i = 0; i < Server->Socket->ActiveConnections; i++)
				Server->Socket->Connections[i]->SendText( connectJsonRes(senderLogin) );
	}
	// Рассылка при отключении пользователя
	else if(type == "disonnect"){

		// Проходим по всем пользователям
		for(int i = 0; i < Server->Socket->ActiveConnections; i++)
				Server->Socket->Connections[i]->SendText( disonnectJsonRes(senderLogin) );
	}
	// Рассылка сообщений
	else if(type == "message"){

		// Проходим по всем пользователям
		for(int i = 0; i < Server->Socket->ActiveConnections; i++)
				Server->Socket->Connections[i]->SendText( messageJsonRes(senderLogin, text) );
	}

}

//---------------------------------------------------------------------------
void __fastcall TForm1::StartButtonClick(TObject *Sender)
{
	// Запуск сервера
	Server->Port = StrToInt(Port->Text);
	Server->Active = true;

	// Отключение кнопки Запустить
	StartButton->Enabled = false;
	// Включение кнопки Отключить
	CloseButton->Enabled = true;

	// Меняем статус
	StatusName->Caption = "Включен";

	// Добавляем в лог
	Log->Lines->Add("Сервер запущен");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::CloseButtonClick(TObject *Sender)
{
	// Отключение сервера
	Server->Active = false;
	Server->Close();

	// Включение кнопки Запустить
	StartButton->Enabled = true;
	// Отключение кнопки Отключить
	CloseButton->Enabled = false;

	// Меняем статус
	StatusName->Caption = "Отключен";

	// Добавляем в лог
	Log->Lines->Add("Сервер отключен");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerClientConnect(TObject *Sender, TCustomWinSocket *Socket)

{
	Log->Lines->Add("Подключен клиент");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerClientRead(TObject *Sender, TCustomWinSocket *Socket)

{
	// Логин пользователя
	loginUser = "";

	// Строка пришедшая от пользователя
	String text = Socket->ReceiveText();

	// Для тестов
	//Log->Lines->Add(text);

	// Разбираем пришедшие данные
	TJSONObject *bustStr = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::UTF8->GetBytes( text ),0);

	// Если нету типа, то выкидываем
	if( transferText( bustStr->Pairs[0]->JsonString->ToString() ) != "type")
		return;

	// Тип запроса
	String typeQuest = transferText( bustStr->Pairs[0]->JsonValue->ToString() );

	// ID пользователя (если нужный запрос)
	if( transferText( bustStr->Pairs[1]->JsonString->ToString() ) == "login" )
		loginUser = transferText( bustStr->Pairs[1]->JsonValue->ToString() );

	// Добавляем в лог
	Log->Lines->Add("Пришел JSON от " + loginUser);

	// При подключении пользователя
	if(typeQuest == "connect"){


		// Для тестов
		Log->Lines->Add("Подключился " + loginUser);

		// Отправка информации, кто подключился
		serverDispatch("connect", loginUser, "");


	}
	// Если пользователь отключился
	else if(typeQuest == "disconnect"){

		// Отправка информации, кто отключился
		serverDispatch("disonnect", loginUser, "");

	}
	// При получении сообщения
	else if(typeQuest == "message"){

		// Текст сообщения
		String text = transferText( bustStr->Pairs[2]->JsonValue->ToString() );

		// Проверка
		if(text == "")
			return;

		serverDispatch("message", loginUser, text);
	}
	 else {
		return;
	}

	/// Обработка результатов
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)

{
	Log->Lines->Add("Клиент отключен");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerClientError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
	Log->Lines->Add("Ошибки у клиента");
}
//---------------------------------------------------------------------------
