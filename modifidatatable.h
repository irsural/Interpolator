//---------------------------------------------------------------------------

#ifndef modifidatatableH
#define modifidatatableH
//---------------------------------------------------------------------------
#include <irsdefs.h>

#include <irscpp.h>
#include <irsstrdefs.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <irsfinal.h>
//#include <irsstdg.h>
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
  irs::irs_string_t* mp_str;
public:		// User declarations

  __fastcall TModifiDataTableF(TComponent* Owner, irs::string* ap_str);
};
//---------------------------------------------------------------------------
extern PACKAGE TModifiDataTableF *ModifiDataTableF;
//---------------------------------------------------------------------------
#endif
