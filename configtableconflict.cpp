//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configtableconflict.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConfigTableConflictF *ConfigTableConflictF;
//---------------------------------------------------------------------------
__fastcall TConfigTableConflictF::TConfigTableConflictF(TComponent* Owner)
  : TForm(Owner)
{
}


TConfigTableConflictF::result_t TConfigTableConflictF::get_result() const
{
  if (TableToConfigRadioButton->Checked) {
    return r_data_table_to_config;
  }

  if (TableFromConfigRadioButton->Checked) {
    return r_config_table_to_data;
  }

  return r_dont_modify_config;
}
//---------------------------------------------------------------------------
