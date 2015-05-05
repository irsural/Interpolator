//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
//#include <irsstrdefs.h>
#include <cbsysutils.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm *AboutForm;
//---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner)
  : TForm(Owner)
{
  irs::string_t file_version_str;
  irs::string_t file_name = Application->ExeName.c_str();
  irs::cbuilder::file_version_t file_version;
  if (irs::cbuilder::get_file_version(file_name, file_version)) {
    file_version_str =
      irs::cbuilder::file_version_to_str(file_version);
    file_version_str = file_version_str + irst(" Alpha");
  }
  Label1->Caption =
    String(irst("Interpolator for Windows XP ")) + file_version_str.c_str();
  BuildDataTimeLabel->Caption =
    String(irst("Build:  ")) +
    String(__TIME__) +
    String(irst(" ")) +
    String(__DATE__);
}
//---------------------------------------------------------------------------
