//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "optionsprog.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsF *OptionsF;
//---------------------------------------------------------------------------
__fastcall TOptionsF::TOptionsF(TComponent* Owner)
  : TForm(Owner),
  m_status_options(OFF_PROCESSING)
{
  m_options_mnk.index=0;
  m_options_mnk.table_raw_data=false;
  m_options_mnk.table_optimal_data=true;
  m_options_mnk.table_correct_data=false;
  m_options_mnk.result_save_file=false;
  m_options_mnk.name_dir="";
  m_options_mnk.file_name="optdata.txt";

  m_options_correct.index=1;
  m_options_correct.correct_x=false;
  m_options_correct.function_correct_x_str="";
  m_options_correct.correct_y=false;
  m_options_correct.function_correct_y_str="";
  m_options_correct.correct_z=false;
  m_options_correct.function_correct_z_str="";
  m_options_correct.table_raw_data=false;
  m_options_correct.table_optimal_data=false;
  m_options_correct.table_correct_data=true;
  m_options_correct.result_save_file=false;
  m_options_correct.name_dir="";
  m_options_correct.file_name="correctdata.txt";

  m_options_coef.index=2;
  m_options_coef.table_raw_data=false;
  m_options_coef.table_optimal_data=true;
  m_options_coef.table_correct_data=false;
  m_options_coef.result_save_file=false;
  m_options_coef.name_dir="";
  m_options_coef.file_name="coefdata.txt";
}
//---------------------------------------------------------------------------
void TOptionsF::reset_status_options()
{
  if(m_status_options == ON_READ){
    select_options_mnk();
    select_options_correct();
    select_options_coef();
  }      
  m_status_options = OFF_PROCESSING;
}
//---------------------------------------------------------------------------
void __fastcall TOptionsF::CloseFormButtonClick(TObject *Sender)
{
  OptionsF->Close();
}
//---------------------------------------------------------------------------
void TOptionsF::select_options_mnk()
{
  OptDispOutMNKCheckBox1->Checked = m_options_mnk.table_raw_data;
  OptDispOutMNKCheckBox2->Checked = m_options_mnk.table_optimal_data;
  OptDispOutMNKCheckBox3->Checked = m_options_mnk.table_correct_data;
  OptSveFileMNKCheckBox->Checked = m_options_mnk.result_save_file;
  DirNameMNKLabeledEdit->Text = m_options_mnk.name_dir;
  FileNameMNKLabeledEdit->Text = m_options_mnk.file_name;
}

void TOptionsF::select_options_correct()
{
  EnabledCorrectXCheckBox->Checked = m_options_correct.correct_x;
  CorrectXLabeledEdit->Text = m_options_correct.function_correct_x_str;
  EnabledCorrectYCheckBox->Checked = m_options_correct.correct_y;
  CorrectYLabeledEdit->Text = m_options_correct.function_correct_y_str;
  EnabledCorrectZCheckBox->Checked = m_options_correct.correct_z;
  CorrectZLabeledEdit->Text = m_options_correct.function_correct_z_str;
  OptDispOutCorCheckBox1->Checked = m_options_correct.table_raw_data;
  OptDispOutCorCheckBox2->Checked = m_options_correct.table_optimal_data;
  OptDispOutCorCheckBox3->Checked = m_options_correct.table_correct_data;
  OptSveFileCorCheckBox->Checked = m_options_correct.result_save_file;
  DirNameCorLabeledEdit->Text = m_options_correct.name_dir;
  FileNameCorLabeledEdit->Text = m_options_correct.file_name;

}

void TOptionsF::select_options_coef()
{
  OptDispOutCoefCheckBox1->Checked = m_options_coef.table_raw_data;
  OptDispOutCoefCheckBox2->Checked = m_options_coef.table_optimal_data;
  OptDispOutCoefCheckBox3->Checked = m_options_coef.table_correct_data;
  OptSveFileCoefCheckBox->Checked = m_options_coef.result_save_file;
  DirNameCoefLabeledEdit->Text = m_options_coef.name_dir;
  FileNameCoefLabeledEdit->Text = m_options_coef.file_name;
}     

void __fastcall TOptionsF::FormShow(TObject *Sender){
  m_status_options = ON_READ;
  OptionsTreeView->Items->Item[0]->Selected=true;
}
//---------------------------------------------------------------------------


void __fastcall TOptionsF::OpenDirCorButtonClick(TObject *Sender)
{
  AnsiString dir="";
  if(SelectDirectory("Укажите каталог для сохранения файла", "", dir)){
    m_options_correct.name_dir=dir;
    select_options_correct();
  }
}
//---------------------------------------------------------------------------



void __fastcall TOptionsF::OptionsTreeViewChange(TObject *Sender,
      TTreeNode *Node)
{
  switch(Node->SelectedIndex)
  {
    case 0:{
      OptimizeMNKOptionsPanel->Visible = true;
      CorrectOptionsPanel->Visible = false;
      CalculatingCoefOptionsPanel->Visible =  false;
    } break;
    case 1:{
      OptimizeMNKOptionsPanel->Visible = false;
      CorrectOptionsPanel->Visible = true;
      CalculatingCoefOptionsPanel->Visible = false;
    } break;
    case 2:{
      OptimizeMNKOptionsPanel->Visible = false;
      CorrectOptionsPanel->Visible = false;
      CalculatingCoefOptionsPanel->Visible = true;
    } break;
  }
}       

void __fastcall TOptionsF::OpenDirMNKButtonClick(TObject *Sender)
{
  AnsiString dir="";
  if(SelectDirectory("Укажите каталог для сохранения файла", "", dir)){
    m_options_mnk.name_dir=dir;
    select_options_mnk();
  }
}
//---------------------------------------------------------------------------

void __fastcall TOptionsF::ApplyButtonClick(TObject *Sender)
{
  m_options_mnk.table_raw_data = OptDispOutMNKCheckBox1->Checked;
  m_options_mnk.table_optimal_data = OptDispOutMNKCheckBox2->Checked;
  m_options_mnk.table_correct_data = OptDispOutMNKCheckBox3;
  m_options_mnk.result_save_file = OptSveFileMNKCheckBox->Checked;
  m_options_mnk.name_dir = DirNameMNKLabeledEdit->Text;
  m_options_mnk.file_name = FileNameMNKLabeledEdit->Text;

  m_options_correct.correct_x = EnabledCorrectXCheckBox->Checked;
  m_options_correct.function_correct_x_str = CorrectXLabeledEdit->Text;
  m_options_correct.correct_y = EnabledCorrectYCheckBox->Checked;
  m_options_correct.function_correct_y_str = CorrectYLabeledEdit->Text;
  m_options_correct.correct_z = EnabledCorrectZCheckBox->Checked;
  m_options_correct.function_correct_z_str = CorrectZLabeledEdit->Text;
  m_options_correct.table_raw_data = OptDispOutCorCheckBox1;
  m_options_correct.table_optimal_data = OptDispOutCorCheckBox2;
  m_options_correct.table_correct_data = OptDispOutCorCheckBox3;
  m_options_correct.result_save_file = OptSveFileCorCheckBox->Checked;
  m_options_correct.name_dir = DirNameCorLabeledEdit->Text;
  m_options_correct.file_name = FileNameCorLabeledEdit->Text;

  m_options_coef.table_raw_data = OptDispOutCoefCheckBox1->Checked;
  m_options_coef.table_optimal_data = OptDispOutCoefCheckBox2->Checked;
  m_options_coef.table_correct_data = OptDispOutCoefCheckBox3;
  m_options_coef.result_save_file = OptSveFileCoefCheckBox->Checked;
  m_options_coef.name_dir = DirNameCoefLabeledEdit->Text;
  m_options_coef.file_name = FileNameCoefLabeledEdit->Text;

  m_status_options = ON_UPDAT;
}
//---------------------------------------------------------------------------

