//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "copytable.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCopyTableForm *CopyTableForm;
//---------------------------------------------------------------------------
__fastcall TCopyTableForm::TCopyTableForm(TComponent* Owner)
  : TForm(Owner),
  m_status_copy_table(OFF_COPY),
  mv_number_table_copy(0)
{
}
//---------------------------------------------------------------------------
void TCopyTableForm::reset_number_table_copy()
  {mv_number_table_copy.resize(0);}
//---------------------------------------------------------------------------
//има источника
int TCopyTableForm::name_sours_table(AnsiString a_name)
{
  NameSoursLabel->Caption=static_cast<AnsiString>("Источник - ")+
    a_name.SubString(1,m_max_size_name_sours);
  if(a_name.Length()>m_max_size_name_sours)
    return 1;
  else
    return 0;
}
//---------------------------------------------------------------------------
//имя первого принимающего
int TCopyTableForm::name_first_accepting(AnsiString a_name)
{
  CopyCheckBox1->Caption=a_name.SubString(1,m_max_size_name_first_accepting);
  if(a_name.Length()>m_max_size_name_first_accepting)
    return 1;
  else
    return 0;
}
//---------------------------------------------------------------------------
//имя второго принимающего
int TCopyTableForm::name_second_accepting(AnsiString a_name)
{
  CopyCheckBox2->Caption=
    a_name.SubString(1,m_max_size_name_second_accepting);
  if(a_name.Length()>m_max_size_name_second_accepting)
    return 1;
  else
    return 0;
}
//---------------------------------------------------------------------------
void TCopyTableForm::reset_status_copy_data()
{
  m_status_copy_table=OFF_COPY;
  if(!(CopyCheckBox1->Checked==false&&CopyCheckBox2->Checked==false)){
    CopyTableButton->Enabled=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TCopyTableForm::CloseFormButtonClick(TObject *Sender)
{
  CopyTableForm->Close();  
}
//---------------------------------------------------------------------------
void __fastcall TCopyTableForm::CopyTableButtonClick(
      TObject *Sender)
{
  if(m_status_copy_table==OFF_COPY)
  {
    CopyTableButton->Enabled=false;
    m_status_copy_table=ON_COPY;
    if(CopyCheckBox1->Checked==true)
      mv_number_table_copy.push_back(1);
    if(CopyCheckBox2->Checked==true)
      mv_number_table_copy.push_back(2);

  }  
}
//---------------------------------------------------------------------------


void __fastcall TCopyTableForm::CopyCheckBox1Click(TObject *Sender)
{
  if(CopyCheckBox1->Checked==false&&CopyCheckBox2->Checked==false)
    CopyTableButton->Enabled=false;
  else if(m_status_copy_table==OFF_COPY)
    CopyTableButton->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TCopyTableForm::CopyCheckBox2Click(TObject *Sender)
{
  if(CopyCheckBox1->Checked==false&&CopyCheckBox2->Checked==false)
    CopyTableButton->Enabled=false;
  else if(m_status_copy_table==OFF_COPY)
    CopyTableButton->Enabled=true; 
}
//---------------------------------------------------------------------------

void __fastcall TCopyTableForm::FormShow(TObject *Sender)
{
  CopyCheckBox1->Checked=false;
  CopyCheckBox2->Checked=false;
  CopyTableButton->Enabled=false;
}
//---------------------------------------------------------------------------

