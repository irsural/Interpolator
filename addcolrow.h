//---------------------------------------------------------------------------

#ifndef addcolrowH
#define addcolrowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <math.h>
//---------------------------------------------------------------------------
enum type_step_t{INCREMENT_STEP, DECREMENT_STEP, MULTIPLIER_STEP};
class TAddCorRowF : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *GroupBox1;
  TGroupBox *GroupBox2;
  TCheckBox *AddGroupColCheckBox;
  TCheckBox *AddGroupRowCheckBox;
  TLabeledEdit *StartNumColLabeledE;
  TLabeledEdit *EndNumColLabeledE;
  TLabeledEdit *StepNumColLabeledE;
  TLabeledEdit *StartNumRowLabeledE;
  TLabeledEdit *EndNumRowLabeledE;
  TLabeledEdit *StepNumRowLabeledE;
  TLabeledEdit *ColLabeledE;
  TLabeledEdit *RowLabeledE;
  TButton *OKButton;
  TButton *CloseFormButton;
  TComboBox *TypeStepColCB;
  TComboBox *TypeStepRowCB;
  TLabel *NameTypeStepColLabel;
  TLabel *NameTypeStepRowLabel;
  void __fastcall AddGroupColCheckBoxClick(TObject *Sender);
  void __fastcall AddGroupRowCheckBoxClick(TObject *Sender);
  void __fastcall CloseFormButtonClick(TObject *Sender);
  void __fastcall OKButtonClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  static const int m_index_increment_combobox = 0;
  static const int m_index_decrement_combobox = 1;
  static const int m_index_multiplier_combobox = 2;
  int* mp_select_col;
  int* mp_select_row;
  bool* mp_successfully_add_col;
  bool* mp_successfully_add_row;
  double* mp_start_num_col;
  double* mp_end_num_col;
  double* mp_step_num_col;
  type_step_t* mp_type_step_col;
  double* mp_start_num_row;
  double* mp_end_num_row;
  double* mp_step_num_row;
  type_step_t* mp_type_step_row;

  bool* mp_add_col_or_row_successfully;

public:		// User declarations
  __fastcall TAddCorRowF(TComponent* Owner);
  void dialog_user_add_col_row(
    int* ap_select_col,
    int* ap_select_row,
    bool* ap_successfully_add_col,
    bool* ap_successfully_add_row,
    double* ap_start_num_col,
    double* ap_end_num_col,
    double* ap_step_num_col,
    type_step_t* ap_type_step_col,
    double* ap_start_num_row,
    double* ap_end_num_row,
    double* ap_step_num_row,
    type_step_t* ap_type_step_row);
  void add_col_row_successfully_stat(bool* ap_stat);

};
//---------------------------------------------------------------------------
extern PACKAGE TAddCorRowF *AddCorRowF;
//---------------------------------------------------------------------------
#endif
