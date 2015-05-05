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
  TComponent* Owner, string_type* ap_str)
  : TForm(Owner),
  mp_str(ap_str)
{
}
//---------------------------------------------------------------------------
void __fastcall TModifiDataTableF::OKButtonClick(TObject *Sender)
{
  string_type str = Edit->Text.c_str();
  *mp_str = str;
}
//---------------------------------------------------------------------------
