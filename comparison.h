//---------------------------------------------------------------------------

#ifndef comparisonH
#define comparisonH

#include <irsdefs.h>

#include <irssysutils.h>

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TComparsionDataForm : public TForm
{
__published:	// IDE-managed Components
  TEdit *FirstDataFileNameEdit;
  TEdit *SecondDataFileNameEdit;
  TButton *OpenFirstDataFileButton;
  TButton *OpenSecondDataFileButton;
  TPanel *Panel1;
  TStringGrid *StringGrid;
  TOpenDialog *OpenDialog;
  TButton *ÑompareButton;
  TButton *ExportButton;
  TSaveDialog *SaveDialog;
  TLabeledEdit *MinLabeledEdit;
  TLabeledEdit *MaxLabeledEdit;
  TCheckBox *ColorEnabledCheckBox;
  TLabeledEdit *ColorLabeledEdit1;
  TLabeledEdit *ColorLabeledEdit2;
  TLabeledEdit *ColorLabeledEdit3;
  TLabeledEdit *ColorLabeledEdit4;
  TRadioButton *ColorShadesRadioButton;
  TRadioButton *DifferentColorsRadioButton;
  void __fastcall OpenFirstDataFileButtonClick(TObject *Sender);
  void __fastcall OpenSecondDataFileButtonClick(TObject *Sender);
  void __fastcall ÑompareButtonClick(TObject *Sender);
  void __fastcall ExportButtonClick(TObject *Sender);
  void __fastcall StringGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
  void __fastcall ColorShadesRadioButtonClick(TObject *Sender);
  void __fastcall DifferentColorsRadioButtonClick(TObject *Sender);
  void __fastcall ColorEnabledCheckBoxClick(TObject *Sender);
private:	// User declarations
  typedef size_t size_type;
  typedef irs::string_t string_type;
  enum { col_width = 140 };
  double m_min_value;
  double m_max_value;
  struct table_cell_t
  {
    bool init;
    double value;
    table_cell_t(bool a_init = false, double a_value = 0):
      init(a_init),
      value(a_value)
    {}
  };
  irs::table_t<table_cell_t> m_table_values;
  irs::table_t<TColor> m_table_colors;
  vector<TLabeledEdit*> m_color_edits;
  void update_color();
public:		// User declarations
  __fastcall TComparsionDataForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TComparsionDataForm *ComparsionDataForm;
//---------------------------------------------------------------------------
#endif
