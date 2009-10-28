//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "modifidatatable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TModifiDataTableF *ModifiDataTableF;
//---------------------------------------------------------------------------
__fastcall TModifiDataTableF::TModifiDataTableF(
  TComponent* Owner, irs::string* ap_str)
  : TForm(Owner),
  mp_str(ap_str)
{
}
//---------------------------------------------------------------------------
void __fastcall TModifiDataTableF::OKButtonClick(TObject *Sender)
{
  irs::string str = Edit->Text.c_str();
  *mp_str = str;
}
//---------------------------------------------------------------------------
