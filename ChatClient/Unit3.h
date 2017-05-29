//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TEdit *PhoneSR;
	TLabel *Label1;
	TLabel *Label2;
	TButton *btnCoding;
	TLabel *Label3;
	TButton *Button2;
	TMemo *PDUMessage;
	TEdit *PhoneSMS;
	TLabel *Label4;
	TMemo *TextMessage;
	void __fastcall btnCodingClick(TObject *Sender);
	void __fastcall PhoneSRChange(TObject *Sender);
	void __fastcall PhoneSRKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall PhoneSMSChange(TObject *Sender);
	void __fastcall PhoneSMSKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
    String CodingPhoneNumber(String);
    String FullPhoneNumberSMS(String);
	String FullPhoneNumberSR(String);
	void CheckPduHeader();
	void DCodeBig();
	void Swap(wchar_t &, wchar_t &);
    void Swap(unsigned char &, unsigned char &);
    String MessageLength(String Text);
	String CodingText(String);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
