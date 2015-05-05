//---------------------------------------------------------------------------

#ifndef copytableH
#define copytableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <vector>
#include "servisfunction.h"
//---------------------------------------------------------------------------  
class TCopyTableForm : public TForm
{
__published:	// IDE-managed Components
  TButton *CopyTableButton;
  TPanel *Panel;
  TLabel *NameSoursLabel;
  TMemo *Memo1;
  TButton *CloseFormButton;
  TTimer *Timer1;
  TGroupBox *GroupBox1;
  TCheckBox *CopyCheckBox1;
  TCheckBox *CopyCheckBox2;
  void __fastcall CloseFormButtonClick(TObject *Sender);
  void __fastcall CopyTableButtonClick(TObject *Sender);
  void __fastcall CopyCheckBox1Click(TObject *Sender);
  void __fastcall CopyCheckBox2Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  static const m_max_size_name_sours=59;
  static const m_max_size_name_first_accepting=64;
  static const m_max_size_name_second_accepting=64;
  m_copy_data m_status_copy_table;
  vector<int> mv_number_table_copy;
public:		// User declarations
  __fastcall TCopyTableForm(TComponent* Owner);
  int name_sours_table(AnsiString a_name);     //има источника
  int name_first_accepting(AnsiString a_name); //имя первого принимающего
  int name_second_accepting(AnsiString a_name);//имя второго принимающего
  inline m_copy_data read_status_copy_data();
  void reset_status_copy_data();
  inline vector<int> read_number_table_copy();
  void reset_number_table_copy();
};
inline m_copy_data TCopyTableForm::read_status_copy_data()
  {return m_status_copy_table;}     
inline vector<int> TCopyTableForm::read_number_table_copy()
  {return mv_number_table_copy;}
//---------------------------------------------------------------------------
extern PACKAGE TCopyTableForm *CopyTableForm;
//---------------------------------------------------------------------------
#endif
