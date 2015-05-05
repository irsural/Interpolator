//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "optionsoptimize.h"

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
  m_options_mnk.name_dir = irst("");
  m_options_mnk.file_name = irst("optdata.txt");

  m_options_correct.index=1;
  m_options_correct.correct_x=false;
  m_options_correct.function_correct_x_str = irst("");
  m_options_correct.correct_y=false;
  m_options_correct.function_correct_y_str = irst("");
  m_options_correct.correct_z=false;
  m_options_correct.table_raw_data=false;
  m_options_correct.table_optimal_data=false;
  m_options_correct.table_correct_data=true;
  m_options_correct.result_save_file=false;
  m_options_correct.name_dir = irst("");
  m_options_correct.file_name = irst("");
}
//---------------------------------------------------------------------------
void __fastcall TOptionsF::CloseFormButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void TOptionsF::select_options_mnk()
{
  OptDispOutMNKCheckBox1->Checked=m_options_mnk.table_raw_data;
  OptDispOutMNKCheckBox2->Checked=m_options_mnk.table_optimal_data;
  OptDispOutMNKCheckBox3->Checked=m_options_mnk.table_correct_data;
  OptSveFileMNKCheckBox->Checked=m_options_mnk.result_save_file;
  FileNameMNKLabeledEdit->Text=m_options_mnk.name_dir+
    m_options_mnk.file_name;
}

void TOptionsF::select_options_correct()
{
  EnabledCorrectXCheckBox->Checked=m_options_correct.correct_x;
  CorrectXLabeledEdit->Text=m_options_correct.function_correct_x_str;
  EnabledCorrectYCheckBox->Checked=m_options_correct.correct_y;
  CorrectYLabeledEdit->Text=m_options_correct.function_correct_y_str;
  EnabledCorrectZCheckBox->Checked=m_options_correct.correct_z;
  CorrectZLabeledEdit->Text=m_options_correct.function_correct_z_str;
  OptDispOutCorCheckBox1->Checked=m_options_correct.table_raw_data;
  OptDispOutCorCheckBox2->Checked=m_options_correct.table_optimal_data;
  OptDispOutCorCheckBox3->Checked=m_options_correct.table_correct_data;
  OptSveFileCorCheckBox->Checked=m_options_correct.result_save_file;
  FileNameCorLabeledEdit->Text=m_options_correct.name_dir+
    m_options_correct.file_name;
}
void TOptionsF::reset_status_options()
{m_status_options = OFF_PROCESSING;}


void __fastcall TOptionsF::FormShow(TObject *Sender){
  OptionsTreeView->Items->Item[0]->Selected=true;
  select_options_mnk();
  select_options_correct();
}
//---------------------------------------------------------------------------


void __fastcall TOptionsF::OpenDirCorButtonClick(TObject *Sender)
{
  AnsiString dir="";
  /*if(SelectDirectory("Укажите каталог для сохранения файла", "", dir)){
    if(TypeOptimizeRadioButton1->Checked==true){
      options_mnk.name_dir=dir;
      select_options_mnk();
    }
    else{
      options_correct.name_dir=dir;
      select_options_correct();
    }
  } */
}
//---------------------------------------------------------------------------



void __fastcall TOptionsF::OptionsTreeViewChange(TObject *Sender,
      TTreeNode *Node)
{
  switch(Node->SelectedIndex)
  {
    case 0:{
      OptimizeMNKOptionsPanel->Visible=true;
      CorrectOptionsPanel->Visible=false;
    } break;
    case 1:{
      OptimizeMNKOptionsPanel->Visible=false;
      CorrectOptionsPanel->Visible=true;
    } break;
  }
}
//---------------------------------------------------------------------------




