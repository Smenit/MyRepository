//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdSocksServer.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Win.MConnect.hpp>
#include <Datasnap.Win.SConnect.hpp>
#include <System.Win.ScktComp.hpp>
#include <IdMappedPortTCP.hpp>
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TServerSocket *Server;
	TButton *StartButton;
	TButton *CloseButton;
	TLabel *Status;
	TLabel *StatusName;
	TEdit *Port;
	TLabel *PortName;
	TMemo *Log;
	TLabel *LogName;
	void __fastcall StartButtonClick(TObject *Sender);
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall ServerClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ServerClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ServerClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ServerClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);


private:	// User declarations
	String transferText(String text);
	int serverDispatch(String type, String senderLogin, String text);
	String connectJsonRes(String login);
	String disonnectJsonRes(String login);
	String messageJsonRes(String login, String text);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
