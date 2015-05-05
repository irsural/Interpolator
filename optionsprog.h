//---------------------------------------------------------------------------

#ifndef optionsprogH
#define optionsprogH
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
  TLabeledEdit *DirNameCorLabeledEdit;
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
  TLabeledEdit *DirNameMNKLabeledEdit;
  TButton *OpenDirMNKButton;
  TPanel *Panel1;
  TLabeledEdit *FileNameCorLabeledEdit;
  TLabeledEdit *FileNameMNKLabeledEdit;
  TPanel *CalculatingCoefOptionsPanel;
  TPanel *Panel2;
  TGroupBox *GroupBox2;
  TCheckBox *OptDispOutCoefCheckBox1;
  TCheckBox *OptDispOutCoefCheckBox2;
  TCheckBox *OptDispOutCoefCheckBox3;
  TCheckBox *OptSveFileCoefCheckBox;
  TLabeledEdit *DirNameCoefLabeledEdit;
  TButton *OpenDirCoefButton;
  TLabeledEdit *FileNameCoefLabeledEdit;
  void __fastcall CloseFormButtonClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);   
  void __fastcall OpenDirCorButtonClick(TObject *Sender);
  void __fastcall OptionsTreeViewChange(TObject *Sender, TTreeNode *Node);
  void __fastcall OpenDirMNKButtonClick(TObject *Sender);
  void __fastcall ApplyButtonClick(TObject *Sender);
private:	// User declarations
  options_optimize_type_mnk_t m_options_mnk;
  options_optimize_type_correct_t m_options_correct;
  options_calculating_coef_t m_options_coef;
  status_options_t m_status_options;
  bool m_on_read_data;
  bool m_on_update_data;
public:		// User declarations
  __fastcall TOptionsF(TComponent* Owner);
  void select_options_mnk();
  void select_options_correct();
  void select_options_coef();
  inline status_options_t status_options() const;
  void reset_status_options();
  inline options_optimize_type_mnk_t read_options_mnk();
  inline options_optimize_type_correct_t read_options_correct();
  inline options_calculating_coef_t read_options_coef();
  inline void write_options_mnk(options_optimize_type_mnk_t a_options);
  inline void write_options_correct(options_optimize_type_correct_t a_options);
  inline void write_options_coef(options_calculating_coef_t a_options);

};
inline status_options_t TOptionsF::status_options() const
  {return m_status_options;}
inline options_optimize_type_mnk_t TOptionsF::read_options_mnk()
  {return m_options_mnk;}
inline options_optimize_type_correct_t TOptionsF::read_options_correct()
  {return m_options_correct;}
inline options_calculating_coef_t TOptionsF::read_options_coef()
  {return m_options_coef;}
inline void TOptionsF::write_options_mnk(
  options_optimize_type_mnk_t a_options)
  {m_options_mnk = a_options;}
inline void TOptionsF::write_options_correct(
  options_optimize_type_correct_t a_options)
  {m_options_correct = a_options;}
inline void TOptionsF::write_options_coef(options_calculating_coef_t a_options)
  {m_options_coef = a_options;}
//---------------------------------------------------------------------------
extern PACKAGE TOptionsF *OptionsF;
//---------------------------------------------------------------------------
#endif
