//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include <irsstdg.h>
#include <cbsysutils.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm *AboutForm;
//---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner)
  : TForm(Owner)
{
  irs::string file_version_str;
  irs::string file_name = Application->ExeName.c_str();
  irs::cbuilder::file_version_t file_version;
  if (irs::cbuilder::get_file_version(file_name, file_version)) {
    file_version_str =
      irs::cbuilder::file_version_to_str(file_version);
    file_version_str = file_version_str + " Alpha";
  }
  Label1->Caption =
    AnsiString("Interpolator for Windows XP ") + file_version_str.c_str();
  BuildDataTimeLabel->Caption =
    AnsiString("Build:  " ) +
    AnsiString(__TIME__) +
    AnsiString(" ") +
    AnsiString(__DATE__);
}
//---------------------------------------------------------------------------
