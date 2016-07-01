//---------------------------------------------------------------------------

#ifndef parametersH
#define parametersH

#include <irsdefs.h>

#include <irssysutils.h>

#include "servisfunction.h"

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------

class TParametersForm : public TForm
{
__published:	// IDE-managed Components
  TListBox *ParametersListBox;
  TStringGrid *StringGrid;
  TCheckBox *ColorEnabledCheckBox;
  TButton *ExportButton;
  void __fastcall ParametersListBoxClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall StringGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
  void __fastcall ColorEnabledCheckBoxClick(TObject *Sender);
  void __fastcall ExportButtonClick(TObject *Sender);
private:	// User declarations
  typedef size_t size_type;
  typedef irs::string_t string_type;
  enum { col_width = 140 };

  enum calc_mode_t {
    mode_error,
    mode_sko,
    mode_delta_2,
    mode_student_t_95,
    mode_student_t_99,
    mode_student_t_999
  };

  map<String, calc_mode_t> m_modes;
  map<calc_mode_t, String> m_modes_file_name_suffix;

  table_data_t** mp_table;

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
    /*table_cell_t& operator=(const table_cell_t& a_table_cell)
    {
      init = a_table_cell.init;
      value = a_table_cell.value;
      return *this;
    }*/
  };
  irs::table_t<TColor> m_table_colors;
  vector<TLabeledEdit*> m_color_edits;

  const irs::matrix_t<cell_t>* get_table() const;
  type_anchor_t get_type_anchor() const;
  inf_in_param_t get_inf_in_param() const;
  calc_mode_t get_mode() const;
  String get_file_name() const;
  
  void calc_min_max_errors(const irs::table_t<table_cell_t>& a_table,
    double* ap_min, double* ap_max) const;

  irs::table_t<table_cell_t> calc_table_errors(
    const irs::matrix_t<cell_t>& a_table,
    const type_anchor_t a_type_anchor) const;

  irs::table_t<table_cell_t> calc_table_values(
    const irs::matrix_t<cell_t>& a_table,
    const calc_mode_t a_mode) const;

  double calc_value(const cell_t::points_type& a_points,
    const calc_mode_t a_calc_mode) const;

  void fill_header(
    const irs::matrix_t<cell_t>& a_table,
    irs::table_t<table_cell_t>* ap_table_result) const;

  void TParametersForm::calc_min_max(const irs::table_t<table_cell_t>& a_table);
  void out_to_string_grid(const irs::table_t<table_cell_t>& a_table);
  void calc(const calc_mode_t a_mode);
  void update();
public:		// User declarations
  __fastcall TParametersForm(TComponent* Owner);
  void set_table(table_data_t** ap_table);
  void add_mode(const String& a_name, const String& a_file_name_suffix,
    const calc_mode_t a_mode);
};
//---------------------------------------------------------------------------
extern PACKAGE TParametersForm *ParametersForm;
//---------------------------------------------------------------------------
#endif
