//---------------------------------------------------------------------------

#ifndef modifidatatableH
#define modifidatatableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <irsstdg.h>
//---------------------------------------------------------------------------
class TModifiDataTableF : public TForm
{
__published:	// IDE-managed Components
  TEdit *Edit;
  TButton *OKButton;
  TButton *CancelButton;
  TLabel *Label1;
  TLabel *Label2;
  void __fastcall OKButtonClick(TObject *Sender);
private:	// User declarations
  irs::string* mp_str;
public:		// User declarations

  __fastcall TModifiDataTableF(TComponent* Owner, irs::string* ap_str);
};
//---------------------------------------------------------------------------
extern PACKAGE TModifiDataTableF *ModifiDataTableF;
//---------------------------------------------------------------------------
#endif
