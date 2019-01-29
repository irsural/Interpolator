//---------------------------------------------------------------------------

#ifndef configtableconflictH
#define configtableconflictH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TConfigTableConflictF : public TForm
{
__published:	// IDE-managed Components
  TButton *OkButton;
  TButton *CancelButton;
  TRadioButton *TableToConfigRadioButton;
  TRadioButton *TableFromConfigRadioButton;
  TRadioButton *ConfigReadOnlyRadioButton;
  TLabel *DescriptionLabel;
private: // User declarations
public: // User declarations
  enum result_t {
    r_data_table_to_config,
    r_config_table_to_data,
    r_dont_modify_config,
  };
  __fastcall TConfigTableConflictF(TComponent* Owner);

  result_t	get_result() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigTableConflictF *ConfigTableConflictF;
//---------------------------------------------------------------------------
#endif
