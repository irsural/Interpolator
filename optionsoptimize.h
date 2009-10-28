//---------------------------------------------------------------------------

#ifndef optionsoptimizeH
#define optionsoptimizeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "servisfunction.h"
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TOptionsF : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *OptionsDysplayOutGB;
  TButton *CloseFormButton;
  TButton *ApplyButton;
  TCheckBox *OptDispOutCorCheckBox1;
  TCheckBox *OptDispOutCorCheckBox2;
  TCheckBox *OptDispOutCorCheckBox3;
  TCheckBox *OptSveFileCorCheckBox;
  TLabeledEdit *FileNameCorLabeledEdit;
  TButton *OpenDirCorButton;
  TTreeView *OptionsTreeView;
  TPanel *BottomPanel;
  TPanel *CorrectOptionsPanel;
  TGroupBox *CorrectGroupBox;
  TLabeledEdit *CorrectXLabeledEdit;
  TLabeledEdit *CorrectYLabeledEdit;
  TLabeledEdit *CorrectZLabeledEdit;
  TCheckBox *EnabledCorrectXCheckBox;
  TCheckBox *EnabledCorrectYCheckBox;
  TCheckBox *EnabledCorrectZCheckBox;
  TPanel *NameSelectOptiomsPanel;
  TPanel *PageControlPanel;
  TPanel *OptimizeMNKOptionsPanel;
  TGroupBox *GroupBox1;
  TCheckBox *OptDispOutMNKCheckBox1;
  TCheckBox *OptDispOutMNKCheckBox2;
  TCheckBox *OptDispOutMNKCheckBox3;
  TCheckBox *OptSveFileMNKCheckBox;
  TLabeledEdit *FileNameMNKLabeledEdit;
  TButton *OpenDirMNKButton;
  TPanel *Panel1;
  TTimer *FormOptionsTimer1;
  void __fastcall CloseFormButtonClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);   
  void __fastcall OpenDirCorButtonClick(TObject *Sender);
  void __fastcall OptionsTreeViewChange(TObject *Sender, TTreeNode *Node);
private:	// User declarations
  options_optimize_type_mnk_t m_options_mnk;
  options_optimize_type_correct_t m_options_correct;
  status_options_t m_status_options;
public:		// User declarations
  __fastcall TOptionsF(TComponent* Owner);
  void select_options_mnk();
  void select_options_correct();
  inline status_options_t status_options();
  void reset_status_options();
  inline options_optimize_type_mnk_t read_options_mnk();
  inline options_optimize_type_correct_t read_options_correct();
  void write_options_mnk(options_optimize_type_mnk_t a_options);
  void write_options_correct(options_optimize_type_correct_t a_options);
};
inline status_options_t TOptionsF::status_options()
  {return m_status_options;}          
inline options_optimize_type_mnk_t TOptionsF::read_options_mnk()
  {return m_options_mnk;}
inline options_optimize_type_correct_t TOptionsF::read_options_correct()
  {return m_options_correct;}
inline void TOptionsF::write_options_mnk(
  options_optimize_type_mnk_t a_options)
  {m_options_mnk = a_options;}
inline void TOptionsF::write_options_correct(
  options_optimize_type_correct_t a_options)
  {m_options_correct = a_options;}
//---------------------------------------------------------------------------
extern PACKAGE TOptionsF *OptionsF;
//---------------------------------------------------------------------------
#endif
