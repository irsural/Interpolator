//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "addcolrow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddCorRowF *AddCorRowF;
//---------------------------------------------------------------------------
__fastcall TAddCorRowF::TAddCorRowF(TComponent* Owner)
  : TForm(Owner),
  mp_select_col(0),
  mp_select_row(0),
  mp_successfully_add_col(0),
  mp_successfully_add_row(0),
  mp_start_num_col(0),
  mp_end_num_col(0),
  mp_step_num_col(0),
  mp_type_step_col(0),
  mp_start_num_row(0),
  mp_end_num_row(0),
  mp_step_num_row(0),
  mp_type_step_row(0),

  mp_add_col_or_row_successfully(0)
{
}
//---------------------------------------------------------------------------
void TAddCorRowF::dialog_user_add_col_row(
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
    type_step_t* ap_type_step_row)
{
  mp_select_col = ap_select_col;
  mp_select_row = ap_select_row;
  mp_successfully_add_col = ap_successfully_add_col;
  mp_successfully_add_row = ap_successfully_add_row;
  mp_start_num_col = ap_start_num_col;
  mp_end_num_col = ap_end_num_col;
  mp_step_num_col = ap_step_num_col;
  mp_type_step_col = ap_type_step_col;
  mp_start_num_row = ap_start_num_row;
  mp_end_num_row = ap_end_num_row;
  mp_step_num_row = ap_step_num_row;
  mp_type_step_row = ap_type_step_row;
}
void TAddCorRowF::add_col_row_successfully_stat(bool* ap_stat)
  {mp_add_col_or_row_successfully = ap_stat;}
//---------------------------------------------------------------------------
void __fastcall TAddCorRowF::AddGroupColCheckBoxClick(TObject *Sender)
{
  if(AddGroupColCheckBox->Checked == true){
    StartNumColLabeledE->Enabled = true;
    EndNumColLabeledE->Enabled = true;
    StepNumColLabeledE->Enabled = true;
    TypeStepColCB->Enabled = true;
  }
  else{
    StartNumColLabeledE->Enabled = false;
    EndNumColLabeledE->Enabled = false;
    StepNumColLabeledE->Enabled = false;
    TypeStepColCB->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TAddCorRowF::AddGroupRowCheckBoxClick(TObject *Sender)
{
  if(AddGroupRowCheckBox->Checked == true){
    StartNumRowLabeledE->Enabled = true;
    EndNumRowLabeledE->Enabled = true;
    StepNumRowLabeledE->Enabled = true;
    TypeStepRowCB->Enabled = true;
  }
  else{
    StartNumRowLabeledE->Enabled = false;
    EndNumRowLabeledE->Enabled = false;
    StepNumRowLabeledE->Enabled = false;
    TypeStepRowCB->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TAddCorRowF::CloseFormButtonClick(TObject *Sender)
{
  AddCorRowF->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAddCorRowF::OKButtonClick(TObject *Sender)
{
  enum error_t{NONE_ERROR, INDEFINITE_ERROR, START_NUM_LARGE_END_NUM_ERROR,
  START_NUM_LESS_END_NUM_ERROR, START_NUM_AND_END_NUM_ERROR,
  STEP_NUM_ERROR} error = NONE_ERROR;
  if(ColLabeledE->Text != ""){
    *mp_select_col = StrToInt(ColLabeledE->Text);
  }else error = INDEFINITE_ERROR;
  if(RowLabeledE->Text != ""){
    *mp_select_row = StrToInt(RowLabeledE->Text);
  }else error = INDEFINITE_ERROR;

  if(StartNumColLabeledE->Text != ""){
    *mp_start_num_col = StrToFloat(StartNumColLabeledE->Text);
  }else if(AddGroupColCheckBox->Checked == true)
    error = INDEFINITE_ERROR;
  if(EndNumColLabeledE->Text != ""){
    *mp_end_num_col = StrToFloat(EndNumColLabeledE->Text);
  }else if(AddGroupColCheckBox->Checked == true)
    error = INDEFINITE_ERROR;
  if(StepNumColLabeledE->Text != ""){
    *mp_step_num_col = StrToFloat(StepNumColLabeledE->Text);
  }else if(AddGroupColCheckBox->Checked == true)
    error = INDEFINITE_ERROR;
  switch(TypeStepColCB->ItemIndex)
  {
    case m_index_increment_combobox:{
      *mp_type_step_col = INCREMENT_STEP;
      if(*mp_start_num_col >= *mp_end_num_col)
        error = START_NUM_LARGE_END_NUM_ERROR;
    } break;
    case m_index_decrement_combobox:{
      *mp_type_step_col = DECREMENT_STEP;
      if(*mp_start_num_col <= *mp_end_num_col)
        error = START_NUM_LESS_END_NUM_ERROR;
    }break;
    case m_index_multiplier_combobox:{
      *mp_type_step_col = MULTIPLIER_STEP;
      if(*mp_step_num_col == 1 || *mp_step_num_col <= 0){
        error = STEP_NUM_ERROR;
      }else if(*mp_step_num_col > 1){
        if(fabs(*mp_start_num_col) >= fabs(*mp_end_num_col))
          error = START_NUM_AND_END_NUM_ERROR;
      }else{
        if(fabs(*mp_start_num_col) <= fabs(*mp_end_num_col))
          error = START_NUM_AND_END_NUM_ERROR;
      }
    } break;
    default:break;
  }

  if(StartNumRowLabeledE->Text != ""){
    *mp_start_num_row = StrToFloat(StartNumRowLabeledE->Text);
  }else if(AddGroupRowCheckBox->Checked == true)
    error = INDEFINITE_ERROR;
  if(EndNumRowLabeledE->Text != ""){
    *mp_end_num_row = StrToFloat(EndNumRowLabeledE->Text);
  }else if(AddGroupRowCheckBox->Checked == true)
    error = INDEFINITE_ERROR;
  if(StepNumRowLabeledE->Text != ""){
    *mp_step_num_row = StrToFloat(StepNumRowLabeledE->Text);
  }else if(AddGroupRowCheckBox->Checked == true)
    error = INDEFINITE_ERROR;
  if(mp_add_col_or_row_successfully != 0){
    *mp_add_col_or_row_successfully = true;
  }
  switch(TypeStepRowCB->ItemIndex)
  {
    case m_index_increment_combobox:{
      *mp_type_step_row = INCREMENT_STEP;
      if(*mp_start_num_row >= *mp_end_num_row){
        error = START_NUM_LARGE_END_NUM_ERROR;
      }
    } break;
    case m_index_decrement_combobox:{
      *mp_type_step_row = DECREMENT_STEP;
      if(*mp_start_num_row <= *mp_end_num_row)
        error = START_NUM_LESS_END_NUM_ERROR;
    } break;
    case m_index_multiplier_combobox:{
      *mp_type_step_row = MULTIPLIER_STEP;
      if(*mp_step_num_row == 1 || *mp_step_num_row <= 0)
        error = STEP_NUM_ERROR;
      else if(*mp_step_num_row > 1){
        if(fabs(*mp_start_num_row) >= fabs(*mp_end_num_row)){
          error = START_NUM_AND_END_NUM_ERROR;
        }
      }else{
        if(fabs(*mp_start_num_row) <= fabs(*mp_end_num_row))
          error = START_NUM_AND_END_NUM_ERROR;
      }
    } break;
    default:break;
  }
  if(error == NONE_ERROR){
    *mp_successfully_add_col = AddGroupColCheckBox->Checked;
    *mp_successfully_add_row = AddGroupRowCheckBox->Checked;
    AddCorRowF->Close();
  }else{
    switch(error){
      case INDEFINITE_ERROR:{
        ShowMessage("Ќе заполнены некоторые пол€!");
      } break;
      case START_NUM_LARGE_END_NUM_ERROR:{
        ShowMessage("Ќачальное значение должно быть меньше конечного!");
      } break;
      case START_NUM_LESS_END_NUM_ERROR:{
        ShowMessage("Ќачальное значение должно быть больше конечного!");
      } break;
      case START_NUM_AND_END_NUM_ERROR:{
        ShowMessage("Ќеверный выбор начального и конечного значени€!");
      } break;
      case STEP_NUM_ERROR:{
        ShowMessage("Ќеправельный выбор шага!\n"
          "«начение должно быть больше \"0\" и не равно \"1\"");
      } break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TAddCorRowF::FormShow(TObject *Sender)
{
  if(mp_select_col != NULL && mp_select_row != NULL){
    ColLabeledE->Text = IntToStr(*mp_select_col);
    RowLabeledE->Text = IntToStr(*mp_select_row);
  }
}
//---------------------------------------------------------------------------
void __fastcall TAddCorRowF::FormCreate(TObject *Sender)
{
  TypeStepColCB->ItemIndex = 0;
  TypeStepRowCB->ItemIndex = 0;
}
//---------------------------------------------------------------------------







