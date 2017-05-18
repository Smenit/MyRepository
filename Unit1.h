//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TMemo *Memo2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TMemo *Memo1;
	TButton *Button2;
	TLabel *Label8;
	TEdit *Edit3;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *Edit4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);

private:	// User declarations
	String workNumber(String number, String type);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
