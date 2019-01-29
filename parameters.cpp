//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "parameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TParametersForm *ParametersForm;
//---------------------------------------------------------------------------
__fastcall TParametersForm::TParametersForm(TComponent* Owner)
  : TForm(Owner),
  m_modes(),
  m_modes_file_name_suffix(),
  mp_table(NULL),
  m_min_value(0),
  m_max_value(0),
  m_table_colors(),
  m_color_edits()
{
  add_mode(irst("Ошибка, %: (value-reference)/|reference|*100%"),
    irst("ошибка"),
    mode_error);
  add_mode(irst("Полудельта, %: |max-min|/|average|*100/2, %"),
    irst("полудельта"),
    mode_delta_2);
  add_mode(irst("СКО/|average|*100, %"),
    irst("ско"),
    mode_sko);
  add_mode(irst("Доверительный интервал (95 %), %"),
    irst("интервал_95"),
    mode_student_t_95);
  add_mode(irst("Доверительный интервал (99 %), %"),
    irst("интервал_99"),
    mode_student_t_99);
  add_mode(irst("Доверительный интервал (99.9 %), %"),
    irst("интервал_999"),
    mode_student_t_999);

  /*map<String, calc_mode_t>::const_iterator it = m_modes.begin();
  while (it != m_modes.end()) {
    ParametersListBox->Items->Add(it->first);
    ++it;
  } */

  //ParametersListBox->Items->Add(irst("СКО"));
  //ParametersListBox->Items->Add(irst("|Ymax-Ymin|/|Yaverage|*100/2, %"));

  ParametersListBox->ItemIndex = 0;
}

void TParametersForm::add_mode(const String& a_name,
  const String& a_file_name_suffix, const calc_mode_t a_mode)
{
  m_modes.insert(make_pair(a_name, a_mode));
  m_modes_file_name_suffix.insert(make_pair(a_mode, a_file_name_suffix));
  ParametersListBox->Items->Add(a_name);
}

void TParametersForm::set_table(table_data_t** ap_table)
{
  mp_table = ap_table;
}

//---------------------------------------------------------------------------
void __fastcall TParametersForm::ParametersListBoxClick(TObject *Sender)
{
  update();
}

void TParametersForm::update()
{
  if (ParametersListBox->ItemIndex < 0) {
    return;
  }

  String name = ParametersListBox->Items->Strings[ParametersListBox->ItemIndex];
  map<String, calc_mode_t>::const_iterator it = m_modes.find(name);
  IRS_LIB_ASSERT(it != m_modes.end());

  const calc_mode_t mode = it->second;
  calc(mode);
}

const irs::matrix_t<cell_t>* TParametersForm::get_table() const
{
  if (!mp_table) {
    return NULL;
  }

  //table_data_t* table = *mp_table;
  const std::vector<irs::matrix_t<cell_t> >& vector_table =
    (*mp_table)->read_table();
  if (vector_table.empty()) {
    return NULL;
  }
  return &vector_table.front();
}

type_anchor_t TParametersForm::get_type_anchor() const
{
  if (!mp_table) {
    return PARAMETR1;
  }
  return (*mp_table)->get_inf_in_param().type_anchor;
}

inf_in_param_t TParametersForm::get_inf_in_param() const
{
  if (!mp_table) {
    return inf_in_param_t();
  }
  return (*mp_table)->get_inf_in_param();
}

TParametersForm::calc_mode_t TParametersForm::get_mode() const
{
  if (ParametersListBox->ItemIndex < 0) {
    throw std::logic_error("Должен быть выбран режим рассчета в списке");
  }

  String name = ParametersListBox->Items->Strings[ParametersListBox->ItemIndex];
  map<String, calc_mode_t>::const_iterator it = m_modes.find(name);
  IRS_LIB_ASSERT(it != m_modes.end());

  calc_mode_t mode = it->second;
  return mode;
}

String TParametersForm::get_file_name() const
{
  if (!mp_table) {
    return String();
  }
  String file_name = (*mp_table)->get_file_namedir();

  if (!file_name.IsEmpty()) {
    file_name = irs::str_conv<String>(irs::get_ultra_short_file_name(
      irs::str_conv<string_type>(file_name)));
    const calc_mode_t calc_mode = get_mode();
    map<calc_mode_t, String>::const_iterator it =
      m_modes_file_name_suffix.find(calc_mode);
    IRS_LIB_ASSERT(it != m_modes_file_name_suffix.end());
    const String suffix = it->second;
    file_name += String(irst("_")) + suffix + irst(".csv");
  }

  return file_name;
}

void TParametersForm::calc_min_max_errors(
  const irs::table_t<table_cell_t>& a_table,
  double* ap_min, double* ap_max) const
{
  *ap_min = 0;
  *ap_max = 0;
  bool min_max_init = false;

  for (size_type c = 1; c < a_table.get_col_count(); c++) {
    for (size_type r = 1; r < a_table.get_row_count(); r++) {
      const table_cell_t& cell = a_table.read_cell(c, r);
      if (cell.init) {
        const double value = cell.value;
        if (!min_max_init) {
          *ap_min = value;
          *ap_max = value;
          min_max_init = true;
        } else {
          *ap_min = fabs(value) < fabs(*ap_min) ? value: *ap_min;
          *ap_max = fabs(value) > fabs(*ap_max) ? value: *ap_max;
        }
      }
    }
  }
}

irs::table_t<TParametersForm::table_cell_t> TParametersForm::calc_table_errors(
  const irs::matrix_t<cell_t>& a_table,
  const type_anchor_t a_type_anchor) const
{
  irs::table_t<table_cell_t> table_result;
  fill_header(a_table, &table_result);

  for (int c = 1; c < a_table.col_count(); c++) {
    for (int r = 1; r < a_table.row_count(); r++) {
      const cell_t& cell = a_table[c][r];
      if (cell.init) {
        double value = cell.value;
        double reference = 0;
        switch (a_type_anchor) {
          case PARAMETR1: {
            const cell_t& cell_x = a_table[c][0];
            if (cell_x.init) {
              reference = cell_x.value;
            }
          } break;
          case PARAMETR2: {
            const cell_t& cell_y = a_table[0][r];
            if (cell_y.init) {
              reference = cell_y.value;
            }
          } break;
          case PARAMETR3: {
            const cell_t& cell_z = a_table[0][0];
            if (cell_z.init) {
              reference = cell_z.value;
            }
          } break;
        }
        if (reference != 0) {
          const double result = (value - reference)/fabs(reference)*100;
          table_result.write_cell(c, r, table_cell_t(true, result));
        }
      }
    }
  }

  return table_result;
}

irs::table_t<TParametersForm::table_cell_t>
TParametersForm::calc_table_values(
  const irs::matrix_t<cell_t>& a_table,
  const calc_mode_t a_mode) const
{
  irs::table_t<table_cell_t> table_result;
  fill_header(a_table, &table_result);

  for (int c = 1; c < a_table.col_count(); c++) {
    for (int r = 1; r < a_table.row_count(); r++) {
      const cell_t& cell = a_table[c][r];
      if (cell.init) {
        const cell_t::points_type& points = cell.points;
        if (!points.empty()) {
          const double result = calc_value(points, a_mode);
          table_result.write_cell(c, r, table_cell_t(true, result));
        }
      }
    }
  }
  return table_result;
}

double TParametersForm::calc_value(const cell_t::points_type& a_points,
  const calc_mode_t a_calc_mode) const
{
  double x_min = 0;
  double x_max = 0;
  double y_min = 0;
  double y_max = 0;
  if (!a_points.empty()) {
    const cell_t::point_type& point = a_points[0];
    const double x = point.x;
    const double y = point.y;
    x_min = x;
    x_max = x;
    y_min = y;
    y_max = y;
  }
  irs::sko_calc_t<double, double> sko_calc(a_points.size());
  for (size_type i = 0; i < a_points.size(); i++) {
    const cell_t::point_type& point = a_points[i];
    const double x = point.x;
    const double y = point.y;
    x_min = std::min(x, x_min);
    x_max = std::max(x, x_max);
    y_min = std::min(y, y_min);
    y_max = std::max(y, y_max);
    sko_calc.add(y);
  }

  double y_average = 0;
  if (!a_points.empty()) {
    y_average = sko_calc.average();
  }

  double sko = 0;
  double sko_percent = 0;

  double y_reference = y_average;
  if ((y_average == 0) && !a_points.empty()) {
    // Ищем ближайшее ненулевое значение
    const cell_t::point_type& point_0 = a_points[0];
    double y_absolute_min = fabs(point_0.y);
    for (size_type i = 0; i < a_points.size(); i++) {
      const cell_t::point_type& point = a_points[i];
      const double y = point.y;
      y_absolute_min = std::min(fabs(y), y_min);
    }
    y_reference = y_absolute_min;
  }
  double delta_2 = 0;
  if (y_reference != 0) {
    sko = sko_calc;
    sko_percent = sko/fabs(y_reference)*100;
    delta_2 = std::fabs(y_max - y_min)/std::fabs(y_reference)*100/2;
  }

  if (a_calc_mode == mode_sko) {
    return sko_percent;
  }

  if (a_calc_mode == mode_delta_2) {
    return delta_2;
  }

  if (!a_points.empty()) {
    const double student_t_95 = student_t_inverse_distribution_2x(
      irs::confidence_level_0_95, a_points.size());
    const double student_t_99 = student_t_inverse_distribution_2x(
      irs::confidence_level_0_99, a_points.size());
    const double student_t_99_9 = student_t_inverse_distribution_2x(
      irs::confidence_level_0_999, a_points.size());
    double confidence_interval_95 = sko_percent*student_t_95;
    double confidence_interval_99 = sko_percent*student_t_99;
    double confidence_interval_99_9 = sko_percent*student_t_99_9;

    if (a_calc_mode == mode_student_t_95) {
      return confidence_interval_95;
    }
    if (a_calc_mode == mode_student_t_99) {
      return confidence_interval_99;
    }
    if (a_calc_mode == mode_student_t_999) {
      return confidence_interval_99_9;
    }
  }

  return 0;
}

void TParametersForm::fill_header(
  const irs::matrix_t<cell_t>& a_table,
  irs::table_t<table_cell_t>* ap_table_result) const
{
  ap_table_result->set_col_count(a_table.col_count());
  ap_table_result->set_row_count(a_table.row_count());

  for (int c = 1; c < a_table.col_count(); c++) {
    const cell_t& cell = a_table[c][0];
    if (cell.init) {
      ap_table_result->write_cell(c, 0, table_cell_t(true, cell.value));
    }
  }
  for (int r = 1; r < a_table.row_count(); r++) {
    const cell_t& cell = a_table[0][r];
    if (cell.init) {
      ap_table_result->write_cell(0, r, table_cell_t(true, cell.value));
    }
  }
}

void TParametersForm::calc_min_max(const irs::table_t<table_cell_t>& a_table)
{
  m_min_value = 0;
  m_max_value = 0;
  bool min_max_init = false;

  for (size_type c = 1; c < a_table.get_col_count(); c++) {
    for (size_type r = 1; r < a_table.get_row_count(); r++) {
      const table_cell_t& cell = a_table.read_cell(c, r);
      if (cell.init) {
        double result = cell.value;

        if (!min_max_init) {
          m_min_value = result;
          m_max_value = result;
          min_max_init = true;
        } else {
          m_min_value = fabs(result) < fabs(m_min_value) ? result: m_min_value;
          m_max_value = fabs(result) > fabs(m_max_value) ? result: m_max_value;
        }
      }
    }
  }
}

void TParametersForm::out_to_string_grid(
  const irs::table_t<table_cell_t>& a_table)
{
  StringGrid->ColCount = a_table.get_col_count();
  StringGrid->RowCount = a_table.get_row_count();

  for (size_type i = 1; i < a_table.get_col_count(); i++) {
    StringGrid->ColWidths[i] = col_width;
  }

  const inf_in_param_t inf_param = get_inf_in_param();
  const String param_1 = irs::str_conv<String>(inf_param.type_variable_param1);
  const String param_2 = irs::str_conv<String>(inf_param.type_variable_param2);

  for (size_type c = 1; c < a_table.get_col_count(); c++) {
    const table_cell_t& cell = a_table.read_cell(c, 0);
    if (cell.init) {
      StringGrid->Cells[c][0] = FloatToStr(cell.value) + irst(" ") + param_1;
    }
  }
  for (size_type r = 1; r < a_table.get_row_count(); r++) {
    const table_cell_t& cell = a_table.read_cell(0, r);
    if (cell.init) {
      StringGrid->Cells[0][r] = FloatToStr(cell.value) + irst(" ") + param_2;
    }
  }

  for (size_type c = 1; c < a_table.get_col_count(); c++) {
    for (size_type r = 1; r < a_table.get_row_count(); r++) {
      const table_cell_t& cell = a_table.read_cell(c, r);
      if (cell.init) {
        double result = cell.value;
        StringGrid->Cells[c][r] = FloatToStr(result);
      } else {
        StringGrid->Cells[c][r] = String();
      }
    }
  }


  double min_value = 0;
  double max_value = 0;
  calc_min_max_errors(a_table, &min_value, &max_value);
  min_value = fabs(min_value);
  max_value = fabs(max_value);



  m_table_colors.set_col_count(a_table.get_col_count());
  m_table_colors.set_row_count(a_table.get_row_count());

  double max_norm = (max_value - min_value);

  for (size_type c = 1; c < a_table.get_col_count(); c++) {
    for (size_type r = 1; r < a_table.get_row_count(); r++) {
      const table_cell_t cell = a_table.read_cell(c, r);

      if (cell.init && (max_norm != 0)) {
        const double value = cell.value;

        double value_norm = fabs(value) - min_value;
        double ratio = irs::bound(1 - value_norm/max_norm, 0., 1.);


        int blue = static_cast<int>(255*ratio);
        int green = 150 + static_cast<int>(105*ratio);
        int red = 255;

        TColor color = static_cast<TColor>((blue << 16) | (green << 8) | red);
        m_table_colors.write_cell(c, r, color);

      } else {
        m_table_colors.write_cell(c, r, static_cast<TColor>(0xFFFFFF));
      }
    }
  }
}

void TParametersForm::calc(const calc_mode_t a_mode)
{
  const irs::matrix_t<cell_t>* p_table = get_table();

  if (!p_table) {
    return;
  }

  const type_anchor_t type_anchor = get_type_anchor();

  irs::table_t<table_cell_t> table;

  switch (a_mode) {
    case mode_error: {
      table = calc_table_errors(*p_table, type_anchor);
    } break;
    case mode_sko:
    case mode_delta_2:
    case mode_student_t_95:
    case mode_student_t_99:
    case mode_student_t_999:{
      table = calc_table_values(*p_table, a_mode);
    } break;
  }


  calc_min_max(table);

  out_to_string_grid(table);

}
//---------------------------------------------------------------------------
void __fastcall TParametersForm::FormShow(TObject *Sender)
{
  update();
}
//---------------------------------------------------------------------------

void __fastcall TParametersForm::StringGridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State)
{
  if (!ColorEnabledCheckBox->Checked) {
    return;
  }
  if ((ACol == 0) || (ARow == 0)) {
    return;
  }
  if ((m_table_colors.get_col_count() <
      static_cast<size_type>(StringGrid->ColCount)) &&
    (m_table_colors.get_row_count() <
      static_cast<size_type>(StringGrid->RowCount))) {
    return;
  }

  TColor color = m_table_colors.read_cell(ACol, ARow);
  StringGrid->Canvas->Brush->Color = color;
  StringGrid->Canvas->FillRect(Rect);
  StringGrid->Canvas->TextOutW(
    Rect.Left, Rect.Top, StringGrid->Cells[ACol][ARow]);
}
//---------------------------------------------------------------------------

void __fastcall TParametersForm::ColorEnabledCheckBoxClick(TObject *Sender)
{
  StringGrid->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TParametersForm::ExportButtonClick(TObject *Sender)
{
  String file_name = get_file_name();
  /*if (!file_name.IsEmpty()) {
    file_name = get_ultra_short_file_name(file_name);
    String suffix = m_modes_file_name_suffix.
    file_name += irst(".csv");
  }*/
  save_string_grid_to_csv_with_dialog(StringGrid, file_name);
}
//---------------------------------------------------------------------------

