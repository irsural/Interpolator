//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <irsalg.h>
#include <measmul.h>
#include <irssysutils.h>
#include <irscalc.h>
#include <tstlan5lib.h>

#include "servisfunction.h"
#include "configtableconflict.h"

#include <irsfinal.h>


const double epsion = 1e-15;
const double not_a_number = 2e300;
//---------------------------------------------------------------------------
//table_string_grid_t
table_string_grid_t::table_string_grid_t(TStringGrid* const ap_table):
  mp_table(ap_table),
  m_edit_mode_table(false)
{
}
void table_string_grid_t::out_display(
  const vector<irs::matrix_t<cell_t> >& av_data,
  const inf_in_param_t& a_inf_in_param)
{
  unsigned int size_z = av_data.size();
  unsigned int size_x = 0;
  unsigned int size_y = 0;
  if(size_z > 0){
    size_x = av_data[0].col_count();
    size_y = av_data[0].row_count();
  }

  mp_table->RowCount = size_z*size_y;
  mp_table->ColCount = size_x;
  int y1 = 0;
  for(unsigned int z = 0; z < size_z; z++){
    for(unsigned int y = 0; y < size_y; y++){
      for(unsigned int x = 0; x < size_x; x++){
        String cell_str;
        cell_t cell = av_data[z][x][y];
        if(cell.init){
          string_type value_str;
          irs::number_to_string(cell.value, &value_str/*, m_precision*/);
          bool select_cell_x = (x > 0) && (y == 0);
          bool select_cell_y = (x == 0) && (y > 0);
          string_type type_variable;
          if (select_cell_x) {
            type_variable = a_inf_in_param.type_variable_param1;
          } else if (select_cell_y) {
            type_variable = a_inf_in_param.type_variable_param2;
          } else {
            if (a_inf_in_param.type_anchor == PARAMETR1) {
              type_variable = a_inf_in_param.type_variable_param1;
            } else if (a_inf_in_param.type_anchor == PARAMETR2) {
              type_variable = a_inf_in_param.type_variable_param2;
            } else {
              type_variable = a_inf_in_param.type_variable_param3;
            }
          }
          mp_table->Cells[x][y1] = (value_str/*+" "+type_variable*/).c_str();
        }else{
          mp_table->Cells[x][y1] = String();
        }
      }
      y1++;
    }
  }
}
int table_string_grid_t::col()
{
  return mp_table->Col;
}
int table_string_grid_t::row()
{
  return mp_table->Row;
}
irs::rect_t table_string_grid_t::selection() const
{
  TGridRect r = mp_table->Selection;
  return irs::rect_t(r.Left, r.Top, r.Right, r.Bottom);
}
void table_string_grid_t::set_col(const int a_col)
{
  mp_table->Col = a_col;
}
void table_string_grid_t::set_row(const int a_row)
{
  mp_table->Row = a_row;
}
void table_string_grid_t::out_display_cell(
  const int a_col_displ, const int a_row_displ, const displ_cell_t a_cell)
{
  String cell_str;
  if(a_cell.init == true){
    cell_str =  FloatToStr(a_cell.value);
  }
  mp_table->Cells[a_col_displ][a_row_displ] = cell_str;
}
void table_string_grid_t::out_display_cur_cell(const displ_cell_t a_cell)
{
  int col = mp_table->Col;
  int row = mp_table->Row;
  String cell_str;
  if(a_cell.init == true){
    cell_str = FloatToStr(a_cell.value);
  }
  mp_table->Cells[col][row] = cell_str;
}
void table_string_grid_t::out_display_cell_variable_precision(
  const int a_col_displ,
  const int a_row_displ,
  const displ_cell_t a_cell,
  const string_type& a_type_variable)
{
  mp_table->Cells[a_col_displ][a_row_displ] =
    get_display_cell_variable_precision(a_col_displ,
    a_row_displ, a_cell, a_type_variable).c_str();
}
table_string_grid_t::string_type
table_string_grid_t::get_display_cell_variable_precision(
  const int a_col_displ,
  const int a_row_displ,
  const displ_cell_t a_cell,
  const string_type& a_type_variable)
{
  string_type cell_str;
  if (a_cell.init == true) {
    irs::number_to_string(a_cell.value, &cell_str, m_precision);
    cell_str += string_type(irst(" ")) + a_type_variable.c_str();
  } else {
    cell_str.clear();
  }
  return cell_str;
}

displ_cell_t table_string_grid_t::in_display_cur_cell()
{
  int col = mp_table->Col;
  int row = mp_table->Row;
  String cell_str = mp_table->Cells[col][row];
  displ_cell_t cell;
  if(cell_str.IsEmpty()){
    cell.value = 0.0;
    cell.init = false;
  }else{
    string_type str_value = irs::str_conv<string_type>(cell_str);
    double value = 0.0;
    bool success = str_value.to_number(value);
    if(success){
      cell.value = value;
      cell.init = true;
    }else{
      cell.init = false;
    }
  }
  return cell;
}

void table_string_grid_t::set_edit_mode_table()
{
  m_edit_mode_table = true;
  mp_table->FixedCols = 0;
  mp_table->FixedRows = 0;
}
void table_string_grid_t::reset_edit_mode_table()
{
  m_edit_mode_table = false;
  mp_table->FixedCols = 1;
  mp_table->FixedRows = 1;
}
bool table_string_grid_t::get_edit_mode_table()
  {return m_edit_mode_table;}
int table_string_grid_t::col_count() const
  {return mp_table->ColCount;}
int table_string_grid_t::row_count() const
  {return mp_table->RowCount;}
//класс table_data_t
table_data_t::table_data_t(display_table_t* ap_display_table,
  String a_name):
  mp_error_trans(irs::error_trans()),
  m_min_fractional_part_count(0.00000000001),
  //m_nan(2e300),
  mp_display_table(ap_display_table),
  m_name(a_name),
  m_file_namedir(),
  mv_table(),
  mv_saved_table(),
  m_cur_col(0),
  m_cur_row(0),
  m_cur_table(0),
  m_inf_in_param(),
  m_cells_config(),
  m_is_cells_config_read_only(false),
  m_table_modifi_stat(false)
{ 
  irs:: matrix_t<cell_t> matrix(2,2);
  mv_table.push_back(matrix);
  mp_display_table->out_display(mv_table, m_inf_in_param);
  mv_coord_special_cells.resize(0);
}

void table_data_t::cell_out_display(
  const int a_col_displ, const int a_row_displ)
{
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];
    mp_display_table->out_display_cell(a_col_displ,a_row_displ, cur_cell);
  }
}

void table_data_t::cur_cell_out_display()
{
  int cur_col = mp_display_table->col();
  int cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    cell_t cur_cell = mv_table[cur_table][cur_col][cur_row];
    mp_display_table->out_display_cur_cell(cur_cell);
  }
}

void table_data_t::cell_out_display_variable_precision(
  const int a_col_displ,
  const int a_row_displ)
{
  int table_count = mv_table.size();
  if(table_count > 0) {
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    string_type type_variable;
    bool select_cell_x = (a_col_displ > 0) && (cur_row == 0);
    bool select_cell_y = (a_col_displ == 0) && (cur_row > 0);

    if (select_cell_x) {
      type_variable = m_inf_in_param.type_variable_param1;
    } else if (select_cell_y) {
      type_variable = m_inf_in_param.type_variable_param2;
    } else {
      if (m_inf_in_param.type_anchor == PARAMETR1) {
        type_variable = m_inf_in_param.type_variable_param1;
      } else if (m_inf_in_param.type_anchor == PARAMETR2) {
        type_variable = m_inf_in_param.type_variable_param2;
      } else {
        type_variable = m_inf_in_param.type_variable_param3;
      }
    }

    if (select_cell_x || select_cell_y) {
      int row_displ_begin = cur_row;
      for(int i = 0; i < table_count; i++){
        cell_t cur_cell = mv_table[i][a_col_displ][cur_row];
        int row_displ = row_displ_begin+i*row_count;
        mp_display_table->out_display_cell_variable_precision(
          a_col_displ, row_displ, cur_cell, type_variable);
      }
    } else {
      cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];
      mp_display_table->out_display_cell_variable_precision(
        a_col_displ, a_row_displ, cur_cell, type_variable);
    }
  }
}

void table_data_t::cur_cell_in_display()
{
  int cur_col = mp_display_table->col();
  int cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    displ_cell_t cur_cell = mp_display_table->in_display_cur_cell();
    bool select_cell_x = (cur_col > 0) && (cur_row == 0);
    bool select_cell_y = (cur_col == 0) && (cur_row > 0);
    if(select_cell_x || select_cell_y){
      for(int i = 0; i < table_count; i++){
        cell_t cell = mv_table[i][cur_col][cur_row];
        cell.value = cur_cell.value;
        cell.init = cur_cell.init;
        mv_table[i][cur_col][cur_row] = cell;

        if (!m_is_cells_config_read_only && i == 0) {
          IRS_ASSERT(m_cells_config.get_col_count() ==
            static_cast<size_type>(mv_table[0].col_count()));
          IRS_ASSERT(m_cells_config.get_row_count() ==
            static_cast<size_type>(mv_table[0].row_count()));
          cell_config_calibr_t cell_cfg;
          cell_cfg.is_value_initialized = cur_cell.init;
          cell_cfg.value = cur_cell.value;
          m_cells_config.write_cell(cur_col, cur_row, cell_cfg);
        }
      }
    } else {
      cell_t cell = mv_table[cur_table][cur_col][cur_row];
      cell.value = cur_cell.value;
      cell.init = cur_cell.init;
      mv_table[cur_table][cur_col][cur_row] = cell;
    }
  }
}

table_data_t::string_type table_data_t::get_cell_display_variable_precision(
  const int a_col_displ,
  const int a_row_displ)
{
  string_type value;
  int table_count = mv_table.size();
  if(table_count > 0) {
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    string_type type_variable;
    bool select_cell_x = (a_col_displ > 0) && (cur_row == 0);
    bool select_cell_y = (a_col_displ == 0) && (cur_row > 0);
    if (select_cell_x) {
      type_variable = m_inf_in_param.type_variable_param1;
    } else if (select_cell_y) {
      type_variable = m_inf_in_param.type_variable_param2;
    } else {
      if (m_inf_in_param.type_anchor == PARAMETR1) {
        type_variable = m_inf_in_param.type_variable_param1;
      } else if (m_inf_in_param.type_anchor == PARAMETR2) {
        type_variable = m_inf_in_param.type_variable_param2;
      } else {
        type_variable = m_inf_in_param.type_variable_param3;
      }
    }
    if(select_cell_x || select_cell_y){
      int row_displ_begin = cur_row;
      cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];
      int row_displ = row_displ_begin+cur_table*row_count;
      value = mp_display_table->get_display_cell_variable_precision(
        a_col_displ, row_displ, cur_cell, type_variable);
    } else {
      /////////////
      /*double ref_value = 0;
      switch (m_inf_in_param.type_anchor) {
        case PARAMETR1: {
          cell_t cur_cell = mv_table[cur_table][a_col_displ][0];
          if (cur_cell.init == true) {
            ref_value = cur_cell.value;
          }
        } break;
        case PARAMETR2: {
          cell_t cur_cell = mv_table[cur_table][0][cur_row];
          ref_value = cur_cell.value;
        } break;
        case PARAMETR3: {
          cell_t cur_cell = mv_table[cur_table][0][0];
        } break;
      }
      cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];

      double result = 0;
      if (cur_cell.init == true) {
        if (ref_value != 0) {
          result = fabs(ref_value - cur_cell.value)/ref_value*100;
        }
      }

      cur_cell.value = result;
      value = mp_display_table->get_display_cell_variable_precision(
        a_col_displ, a_row_displ, cur_cell, string_type(irst("%")));*/
      /////////////

      cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];
      value = mp_display_table->get_display_cell_variable_precision(
        a_col_displ, a_row_displ, cur_cell, type_variable);
    }
  }
  return value;
}

void table_data_t::create_col_table()
{
  const int create_col_count = 1;
  int cur_col = mp_display_table->col();
  int cur_row = mp_display_table->row();
  int table_count = mv_table.size();
  if (table_count > 0 && cur_col > 0 && cur_row > 0) {
    cell_t cell;
    cell.value = 0;
    cell.init = false;
    for (int i = 0; i < table_count; i++) {
      mv_table[i].newcols(cur_col, create_col_count, cell);
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);

    if (!m_is_cells_config_read_only) {
      m_cells_config.set_col_count(mv_table[0].col_count());

      for (size_type col = m_cells_config.get_col_count() - 1;
        col > static_cast<size_type>(cur_col); col--) {

        for (size_type row = 0; row < m_cells_config.get_row_count(); row++) {
          cell_config_calibr_t cell_config = m_cells_config.read_cell(col - 1, row);
          m_cells_config.write_cell(col, row, cell_config);
        }
      }
      m_cells_config.write_cell(cur_col, 0, cell_config_calibr_t());
    }
  }
}

void table_data_t::create_group_col_table(
  double a_num_begin,
  double a_num_finite,
  double a_step,
  type_step_t a_type_step_col)
{
  double cur_number_x = 0;
  cur_number_x = a_num_begin;
  int all_col_count = 0;
  int new_col_count = 0;
  int select_col = 0;
  int previous_col_count = 0;
  int integer_part_count = 0;
  long double count = 0;
  select_col = mp_display_table->col();
  previous_col_count = mv_table[0].col_count();
  if (select_col < 1)
    select_col = 1;
  // вычисляем количество добовляемых столбцов
  if (a_type_step_col == INCREMENT_STEP)
    count = (a_num_finite - a_num_begin) / a_step + 1;
  else if (a_type_step_col == DECREMENT_STEP)
    count = (a_num_begin - a_num_finite) / a_step + 1;
  else if (a_type_step_col == MULTIPLIER_STEP)
    count = 1 + logl(a_num_finite / a_num_begin) / logl(a_step);
  if (count < 2) {
    new_col_count = 2;
  } else {
    integer_part_count = count;
    if (count - integer_part_count < m_min_fractional_part_count)
      new_col_count = integer_part_count;
    else
      new_col_count = integer_part_count + 1;
  }
  all_col_count = previous_col_count + new_col_count;
  if (all_col_count <= m_max_col_count && !mv_table.empty()) {
    unsigned int size = mv_table.size();
    cell_t cell;
    cell.value = 0;
    cell.init = true;
    //заполняем шапку таблицы новыми значениями
    for (unsigned int i = 0; i < size; i++){
      cur_number_x = a_num_begin;
      mv_table[i].newcols(select_col, new_col_count, cell);
      for (int x = select_col; x < select_col + new_col_count - 1; x++) {
        cell.value = cur_number_x;
        mv_table[i][x][0] = cell;
        if (a_type_step_col == INCREMENT_STEP)
          cur_number_x = cur_number_x + a_step;
        else if (a_type_step_col == DECREMENT_STEP)
          cur_number_x = cur_number_x - a_step;
        else if (a_type_step_col == MULTIPLIER_STEP)
          cur_number_x = cur_number_x*a_step;
      }
      cell.value = a_num_finite;
      mv_table[i][select_col+new_col_count - 1][0] = cell;
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);

    if (!m_is_cells_config_read_only) {
      m_cells_config.set_col_count(mv_table[0].col_count());

      // Сдвигаем настройки ячеек вправо, на количество вставленных столбцов
      for (size_type col = m_cells_config.get_col_count() - 1;
        col > static_cast<size_type>(select_col + new_col_count); col--) {

        for (size_type row = 0; row < m_cells_config.get_row_count(); row++) {
          cell_config_calibr_t cell_config =
            m_cells_config.read_cell(col - new_col_count, row);
          m_cells_config.write_cell(col, row, cell_config);
        }
      }

      // В новые столбцы записываем выделенный столбец
      for (size_type col = select_col + 1;
        col < static_cast<size_type>(select_col + new_col_count); col++) {

        for (size_type row = 0; row < m_cells_config.get_row_count(); row++) {
          cell_config_calibr_t cell_config =
            m_cells_config.read_cell(select_col, row);
          m_cells_config.write_cell(col, row, cell_config);
        }
      }

      for (size_type col = select_col;
        col < static_cast<size_type>(select_col + new_col_count); col++) {

        cell_t cell = mv_table[0][col][0];

        cell_config_calibr_t cell_config;
        cell_config.is_value_initialized = cell.init;
        cell_config.value = cell.value;
        m_cells_config.write_cell(col, 0, cell_config);
      }
    }
  }               
}

void table_data_t::delete_col_table()
{
  int cur_col = 0;
  cur_col = mp_display_table->col();
  if (cur_col > 0)
  {
    int table_count = mv_table.size();
    if (table_count > 0) {
      if (mv_table[0].col_count() > 2){
        for (int i = 0; i < table_count; i++){
          mv_table[i].delcols(cur_col, cur_col);
        }
        if (!m_is_cells_config_read_only) {
          m_cells_config.col_erase(cur_col);
        }
        mp_display_table->out_display(mv_table, m_inf_in_param);
      }
    }
  }
}

void table_data_t::create_row_table()
{
  const create_row_count = 1;
  int cur_col_displ = mp_display_table->col();
  int cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0 && cur_col_displ > 0 && cur_row_displ > 0 ) {
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_row = val.rem;
    if (cur_row != 0){
      cell_t cell;
      cell.value = 0;
      cell.init = false;
      for(int i = 0; i < table_count; i++){
        mv_table[i].newrows(cur_row, create_row_count, cell);
      }
    }
    if (!m_is_cells_config_read_only) {
      m_cells_config.set_row_count(mv_table[0].row_count());
      for (size_type col = 0;
        col < static_cast<size_type>(m_cells_config.get_col_count()); col++) {

        for (size_type row = m_cells_config.get_row_count() - 1;
          row > static_cast<size_type>(cur_row_displ); row--) {

          cell_config_calibr_t cell_config = m_cells_config.read_cell(col, row - 1);
          m_cells_config.write_cell(col, row, cell_config);
        }
      }
      m_cells_config.write_cell(0, cur_row_displ, cell_config_calibr_t());
    }
  }
  mp_display_table->out_display(mv_table, m_inf_in_param);
}

void table_data_t::create_group_row_table(
  double a_num_begin,
  double a_num_finite,
  double a_step,
  type_step_t a_type_step_row)
{
  double cur_number_y = 0;
  cur_number_y = a_num_begin;
  int all_row_count = 0;
  int new_row_count = 0;
  int cur_row_displ = 0;
  int previous_row_count = 0;
  int integer_part_count = 0;
  long double count = 0;
  unsigned int table_count = mv_table.size();
  if(table_count > 0){
    cur_row_displ = mp_display_table->row();
    previous_row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, previous_row_count);
    int cur_row = val.rem;
    if(cur_row < 1)
      cur_row = 1;
    //вычисляем количество добовляемых строк
    if(a_type_step_row == INCREMENT_STEP)
      count = (a_num_finite-a_num_begin)/a_step+1;
    else if(a_type_step_row == DECREMENT_STEP)
      count = (a_num_begin-a_num_finite)/a_step+1;
    else if(a_type_step_row == MULTIPLIER_STEP){
      count = 1+logl(a_num_finite/a_num_begin)/logl(a_step);
    }
    if(count < 2){ new_row_count = 2;
    }else{
      integer_part_count = count;
      if(count-integer_part_count < m_min_fractional_part_count)
        new_row_count = integer_part_count;
      else
        new_row_count = integer_part_count + 1;
    }
    all_row_count = previous_row_count + new_row_count;
    if(all_row_count <= m_max_row_count){
      cell_t cell;
      cell.value = 0;
      cell.init = true;
      //заполняем левый столбец таблицы новыми значениями
      for(unsigned int i = 0; i < table_count; i++){
        cur_number_y = a_num_begin;
        mv_table[i].newrows(cur_row, new_row_count, cell);
        for(int y = cur_row; y < cur_row+new_row_count-1; y++){
          cell.value = cur_number_y;
          mv_table[i][0][y] = cell;
          if(a_type_step_row == INCREMENT_STEP)
            cur_number_y = cur_number_y+a_step;
          else if(a_type_step_row == DECREMENT_STEP)
            cur_number_y = cur_number_y-a_step;
          else if(a_type_step_row == MULTIPLIER_STEP)
            cur_number_y = cur_number_y*a_step;
        }
        cell.value = a_num_finite;
        mv_table[i][0][cur_row+new_row_count-1] = cell;
      }
      mp_display_table->out_display(mv_table, m_inf_in_param);

      if (!m_is_cells_config_read_only) {
        m_cells_config.set_row_count(mv_table[0].row_count());

        // Сдвигаем настройки ячеек вниз, на количество вставленных строк
        for (size_type row = m_cells_config.get_row_count() - 1;
          row > static_cast<size_type>(cur_row + new_row_count); row--) {

          for (size_type col = 0; col < m_cells_config.get_col_count(); col++) {
            cell_config_calibr_t cell_config =
              m_cells_config.read_cell(col, row - new_row_count);
            m_cells_config.write_cell(col, row, cell_config);
          }
        }

        // В новые строки записываем выделенную строку
        for (size_type row = cur_row + 1;
          row < static_cast<size_type>(cur_row + new_row_count); row++) {

          for (size_type col = 0; col < m_cells_config.get_col_count(); col++) {
            cell_config_calibr_t cell_config =
              m_cells_config.read_cell(col, cur_row);
            m_cells_config.write_cell(col, row, cell_config);
          }
        }

        for (size_type row = cur_row;
          row < static_cast<size_type>(cur_row + new_row_count); row++) {

          cell_t cell = mv_table[0][0][row];

          cell_config_calibr_t cell_config;
          cell_config.is_value_initialized = cell.init;
          cell_config.value = cell.value;
          m_cells_config.write_cell(0, row, cell_config);
        }
      }
    }
  }
}

void table_data_t::delete_row_table()
{
  int cur_row_displ = 0;
  cur_row_displ = mp_display_table->row();
  if(cur_row_displ > 0)
  {
    int table_count = mv_table.size();
    if(table_count > 0){
      int row_count = mv_table[0].row_count();
      if(row_count > 2){
        div_t val = div(cur_row_displ, row_count);
        int cur_row = val.rem;
        for(int i = 0; i < table_count; i++){
          mv_table[i].delrows(cur_row, cur_row);
        }
        if (!m_is_cells_config_read_only) {
          m_cells_config.row_erase(cur_row_displ);
        }

        mp_display_table->out_display(mv_table, m_inf_in_param);
      }
    }
  }
}

void table_data_t::create_subtable()
{
  int cur_row_displ = 0;
  cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0){
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    int cur_num_table = div(cur_row_displ, row_count).quot;
    irs::matrix_t<cell_t> matrix(col_count, row_count);
    //копируем значения заголовков столбцов
    for(int x = 1; x < col_count; x++){
      matrix[x][0] = static_cast<cell_t>(mv_table[0][x][0]);
    }
    //копируем значения заголовков строк
    for(int y = 1; y < row_count; y++){
      matrix[0][y] = static_cast<cell_t>(mv_table[0][0][y]);
    }
    mv_table.insert(mv_table.begin()+cur_num_table, matrix);
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}

void table_data_t::delete_subtable()
{
 int cur_row_displ = 0;
  cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 1){
    int row_count = mv_table[0].row_count();
    int cur_num_table = div(cur_row_displ, row_count).quot;
    mv_table.erase(mv_table.begin()+cur_num_table);
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}

//---------------------------------------------------------------------------

void table_data_t::create_new_table(const inf_in_param_t& a_inf_in_param,
    const irs::table_t<cell_config_calibr_t>& a_cells_config)
{
  clear_table_def();
  m_inf_in_param = a_inf_in_param;
  m_cells_config = a_cells_config;
  set_config_table_to_data(&mv_table[0]);
  mv_saved_table.clear();
  mp_display_table->out_display(mv_table, m_inf_in_param);
  //mv_saved_table = mv_table;
}

void table_data_t::save_table_to_json_file(const string_type& a_file_name)
{
  Json::Value data;

  unsigned int param_count = 0;
  if (m_inf_in_param.number_in_param == TWO_PARAM) {
    param_count = 2;
  } else {
    param_count = 3;
  }
  data["parameter_count"] = param_count;

  const unsigned int size_x = mv_table[0].col_count();
  const unsigned int size_y = mv_table[0].row_count();
  const unsigned int size_z = mv_table.size();


  switch (m_inf_in_param.number_in_param) {
    case TWO_PARAM: {
      Json::Value col_parameters(Json::arrayValue);
      save_table_to_json(0, &col_parameters);
      data["parameters"] = col_parameters;
    } break;
    case THREE_PARAM: {
      Json::Value top_parameters(Json::arrayValue);
      for (unsigned int z = 0; z < size_z; z++) {
        Json::Value param;
        const cell_t cell = mv_table[z][0][0];
        if (cell.init) {
          param["param"] =
            irs::encode_utf_8(irs::num_to_str_classic(cell.value));
        }
        Json::Value col_parameters(Json::arrayValue);
        save_table_to_json(z, &col_parameters);
        param["parameters"] = col_parameters;
        top_parameters.append(param);
      }
      data["parameters"] = top_parameters;
    } break;
  }

  ofstream ofile;
  ofile.open(IRS_SIMPLE_FROM_TYPE_STR(a_file_name.c_str()),
    ios::in|ios::out|ios::trunc);
  //ofile.open(IRS_SIMPLE_FROM_TYPE_STR(irst("D:\\333.json")),
    //ios::in|ios::out|ios::trunc);
  if (!ofile.good()) {
    throw runtime_error("Не удалось сохранить файл");
  }
  ofile << data << std::endl;

  #ifdef debug_version_digital_interpolator
  mv_saved_table = mv_table;
  #endif
}

void table_data_t::save_table_to_json(size_type a_index,
  Json::Value* ap_parameters)
{
  ap_parameters->clear();
  const unsigned int col_count = mv_table[a_index].col_count();
  const unsigned int row_count = mv_table[a_index].row_count();

  for(unsigned int col = 1; col < col_count; col++) {
    Json::Value col_param;
    const cell_t col_cell = mv_table[a_index][col][0];
    if (col_cell.init) {
      col_param["param"] =
        irs::encode_utf_8(irs::num_to_str_classic(col_cell.value));
    }
    Json::Value row_parameters(Json::arrayValue);
    for(unsigned int row = 1; row < row_count; row++) {
      Json::Value param;
      const cell_t row_cell = mv_table[a_index][0][row];
      if (row_cell.init) {
        param["param"] =
          irs::encode_utf_8(irs::num_to_str_classic(row_cell.value));
      }
      const cell_t cell = mv_table[a_index][col][row];
      if (cell.init == true) {
        Json::Value result;
        result["value"] =
          irs::encode_utf_8(irs::num_to_str_classic(cell.value));
        result["sko"] =
          irs::encode_utf_8(irs::num_to_str_classic(cell.sko));
        result["min"] =
          irs::encode_utf_8(irs::num_to_str_classic(cell.min));
        result["max"] =
          irs::encode_utf_8(irs::num_to_str_classic(cell.max));

        Json::Value points_x_y_value(Json::arrayValue);
        save_points(cell.points, &points_x_y_value);


        /*const cell_t::points_type& points = cell.points;
        for (size_type i = 0; i < points.size(); i++) {
          const cell_t::point_type& point = points[i];
          Json::Value point_value;
          string_type x_str;
          num_to_str_classic(point.x, &x_str);
          point_value["x"] = encode_utf_8(x_str);
          string_type y_str;
          num_to_str_classic(point.y, &y_str);
          point_value["y"] = encode_utf_8(y_str);
          points_x_y_value.append(point_value);
        } */
        result["points"] = points_x_y_value;

        param["result"] = result;
      }
      row_parameters.append(param);
    }
    col_param["parameters"] = row_parameters;
    ap_parameters->append(col_param);
  }
}

void table_data_t::save_points(const cell_t::points_type&
  a_points, Json::Value* ap_points_value) const
{
  ap_points_value->clear();
  for (size_type i = 0; i < a_points.size(); i++) {
    const cell_t::point_type& point = a_points[i];
    Json::Value point_value;
    string_type x_str;
    num_to_str_classic(point.x, &x_str);
    point_value["x"] = encode_utf_8(x_str);
    string_type y_str;
    num_to_str_classic(point.y, &y_str);
    point_value["y"] = encode_utf_8(y_str);
    ap_points_value->append(point_value);
  }
}

void table_data_t::save_table_to_file(const string_type& a_file_name)
{
  save_table_to_json_file(a_file_name);
}

void table_data_t::save_table_to_ini_file(const string_type a_file_name)
{
  //запись в ini файл размеров кватерниона
  irs::handle_t<TIniFile> inifile(new TIniFile(a_file_name.c_str()));
  unsigned int param_count = 0;
  if(m_inf_in_param.number_in_param == TWO_PARAM){
    param_count = 2;
  }else{
    param_count = 3;
  }
  inifile->WriteInteger("Setting", "parameter_count", param_count);
  unsigned int size_x = mv_table[0].col_count();
  inifile->WriteInteger("Setting", "size_x", size_x);
  unsigned int size_y = mv_table[0].row_count();
  inifile->WriteInteger("Setting", "size_y", size_y);
  unsigned int size_z = mv_table.size();
  inifile->WriteInteger("Setting", "size_z", size_z);

  //запись значений ячеек кватерниона
  for(unsigned int z = 0; z < size_z; z++) {
    String table_name = irs::str_conv<String>(
      string_type(irst("table")) + irs::num_to_str(z));
    for(unsigned int y = 0; y < size_y; y++) {
      std::stringstream row_str;
      row_str.imbue(locale::classic());
      for(unsigned int x = 0; x < size_x; x++){
        double value_cell;
         cell_t cell = mv_table[z][x][y];
        if(cell.init == true){
          value_cell = cell.value;
        }else{
          value_cell = not_a_number;
        }
        row_str<<setw(m_field_width)<<left<<setprecision(m_precision)<<
          value_cell;
      }
      String row_name = irs::str_conv<String>(
        string_type(irst("row"))+ irs::num_to_str(y));
      inifile->WriteString(table_name, row_name,
        irs::str_conv<String>(row_str.str()));
    }
  }
  #ifdef  debug_version_digital_interpolator
  mv_saved_table = mv_table;
  #endif
}

void table_data_t::save_table_to_microsoft_excel_csv_file(
  const string_type a_file_name)
{
  std::string file_name = irs::str_conv<std::string>(a_file_name);
  ofstream_type outfile(file_name.c_str(), std::ofstream::out|std::ofstream::trunc);
  if (!outfile){
    outfile.close();
    ShowMessage("Файл создать не удалось!");
    return;
  }
  int table_count = mv_table.size();
  if (table_count > 0) {
    int row_count = mv_table[0].row_count();
    int col_count = mv_table[0].col_count();
    //запись значений ячеек кватерниона
    for( int table = 0; table < table_count; table++){
      for (int row = 0; row < row_count; row++) {
        int delimiter_char_count = 0;
        for (int col = 0; col < col_count; col++) {
          cell_t cell = mv_table[table][col][row];
          if (cell.init == true) {
            for (int i = 0; i < delimiter_char_count; i++) {
              outfile << irst(';');
            }
            delimiter_char_count = 0;    
            outfile << setprecision(m_precision) << cell.value;
            delimiter_char_count++;
          }else{
            delimiter_char_count++;
          }
        }
        outfile << endl;
      }
    }
  }
  outfile.close();
}
void table_data_t::save_table_to_m_file(const string_type a_file_name) const
{
  #ifdef NOP
  string file_name = "";
  file_name = a_file_name;
  int index = file_name.rfind(".");
  if(index != string::npos){
    file_name.erase(index, file_name.size()-index);
  }
  file_name = file_name+".m";
  ofstream outfile(file_name.c_str());
  if(!outfile){
    ShowMessage("Файл создать не удалось!");
    return;
  }
  //запись значений координат X
  String num_str;
  outfile<<"x = ["<<flush;
  for(int x = 0; x < mp_table->ColCount-2; x++){
    num_str = mp_table->Cells[x+2][1];
    if(num_str != ""){
      if(x != mp_table->ColCount-3){
        outfile<<setprecision(m_precision)<<StrToFloat(num_str)<<flush;
        outfile<<","<<" "<<flush;
      }else{
        outfile<<setprecision(m_precision)<<StrToFloat(num_str)<<flush;
        outfile<<"];"<<flush;
      }
    }else{
      if(x != mp_table->ColCount-3){
        outfile<<setprecision(m_precision)<<StrToFloat(not_a_number)<<flush;
        outfile<<","<<" "<<flush;
      }else{
        outfile<<setprecision(m_precision)<<StrToFloat(not_a_number)<<flush;
        outfile<<"];"<<flush;
      }
    }
  }
  outfile<<endl;
  //запись значени координат y
  outfile<<"y = ["<<flush;
  for(int y = 0; y < mp_table->RowCount-2; y++){
    num_str = mp_table->Cells[1][y+2];
    if(num_str != ""){
      if(y != mp_table->RowCount-3){
        outfile<<setprecision(m_precision)<<StrToFloat(num_str)<<flush;
        outfile<<","<<" "<<flush;
      }else{
        outfile<<setprecision(m_precision)<<StrToFloat(num_str)<<flush;
        outfile<<"];"<<flush;
      }
    }else{
      if(y != mp_table->RowCount-3){
        outfile<<setprecision(m_precision)<<StrToFloat(not_a_number)<<flush;
        outfile<<","<<" "<<flush;
      }else{
        outfile<<setprecision(m_precision)<<StrToFloat(not_a_number)<<flush;
        outfile<<"];"<<flush;
      }
    }
  }
  outfile<<endl;
  //запись значений координат z
  int y_count = 0;
  for(int y = 0; y < mp_table->RowCount-2; y++){
    outfile<<(AnsiString("y")+StrToInt(y+1)+" = [").c_str()<<flush;
    y_count++;
    for(int x = 0; x < mp_table->ColCount-2; x++){
      num_str = mp_table->Cells[x+2][y+2];
      if(num_str != ""){
        if(x != mp_table->ColCount-3){
          outfile<<setprecision(m_precision)<<StrToFloat(num_str)<<flush;
          outfile<<","<<" "<<flush;
        }else{
          outfile<<setprecision(m_precision)<<StrToFloat(num_str)<<flush;
          outfile<<"];"<<flush;
        }
      }else{
        if(x != mp_table->ColCount-3){
          outfile<<setprecision(m_precision)<<StrToFloat(not_a_number)<<flush;
          outfile<<","<<" "<<flush;
        }else{
          outfile<<setprecision(m_precision)<<StrToFloat(not_a_number)<<flush;
          outfile<<"];"<<flush;
        }
      }
    }
    outfile<<endl;
  }
  outfile<<"[X,Y] = meshgrid(x,y);"<<endl;
  outfile<<"z = ["<<flush;
  for(int i = 1; i <= y_count; i++){
    outfile<<"y"<<IntToStr(i).c_str()<<flush;
    if(i != y_count)
      outfile<<"; "<<flush;
    else
      outfile<<"];"<<endl;
  }
  outfile<<"mesh(x,y,z)"<<endl;
  outfile.close();
  #endif //NOP
}

bool table_data_t::load_table_from_file(const string_type& a_file_name,
  const inf_in_param_t& a_inf_in_param,
  const irs::table_t<cell_config_calibr_t>& a_cells_config)
{
  m_file_namedir = String();
  //m_inf_in_param = a_inf_in_param;
  //m_cells_config = a_cells_config;
  create_new_table(a_inf_in_param, a_cells_config);

  std::vector<irs::matrix_t<cell_t> > table;
  number_in_param_t param_count_from_file = TWO_PARAM;

  ::load_table_from_file(param_count_from_file, a_file_name, table);

  if (table.size() > 0) {
    irs::matrix_t<cell_t>& t = table[0];

    bool are_headers_different = !displ_table_matches_config_table(t, m_cells_config);

    if (are_headers_different) {
      irs::handle_t<TConfigTableConflictF> conflict_dialog(
        new TConfigTableConflictF(NULL));
      //config_form->set_path_program(m_path_prog);

      int button_result = conflict_dialog->ShowModal();
      if (button_result == mrOk) {
        m_is_cells_config_read_only = false;
        switch(conflict_dialog->get_result())
        {
          case TConfigTableConflictF::r_data_table_to_config: {
            set_data_table_to_config(&t);
          } break;
          case TConfigTableConflictF::r_config_table_to_data: {
            set_config_table_to_data(&t);
          } break;
          case TConfigTableConflictF::r_dont_modify_config: {
            m_is_cells_config_read_only = true;
          } break;
        }
      } else {
        return false;
      }
    }/* else {
      set_config_table_to_data(&t);
    }*/
  }

  if (m_inf_in_param.number_in_param == param_count_from_file) {
    mv_table.clear();
    #ifdef debug_version_digital_interpolator
    mv_saved_table.clear();
    mv_saved_table = table;
    #endif
    mv_table = table;
    mp_display_table->out_display(mv_table, m_inf_in_param);
    m_file_namedir = irs::str_conv<String>(a_file_name);
    return true;
  } else {
    MessageDlg(irst("Не совпадает количество входных параметров в конфигурации и в файле данных"),
      mtError, TMsgDlgButtons() << mbOK, 0);
    DGI_MSG("Не совпадает количество входных параметров в конфигурации и в файле данных");
    // надо вывести сообщение о несоответствии загруженного файла выбранной конфигурации    
    return false;
  }
}

void load_table_from_json(
  const Json::Value& a_parameters, irs::matrix_t<cell_t>* ap_matrix)
{
  typedef size_t size_type;
  irs::matrix_t<cell_t> matrix;
  const size_type col_count = a_parameters.size();
  for (size_type col = 0; col < col_count; col++) {
    Json::Value col_param = a_parameters[col];
    cell_t cell;
    if (!col_param["param"].empty()) {
      std::string param_str = col_param["param"].asString();
      double param = 0;
      if (irs::str_to_num_classic(param_str, &param)) {
        cell.init = true;
        cell.value = param;
      }
    }


    Json::Value row_parameters = col_param["parameters"];
    const size_type row_count = row_parameters.size();

    matrix.resize(col_count + 1, row_count + 1);
    matrix[col + 1][0] = cell;

    if (col == 0) {
      // Заполняем вертикальну шапку (для строк) таблицы один раз
      for(unsigned int row = 0; row < row_count; row++) {
        Json::Value row_param = row_parameters[row];
        cell_t cell;
        if (!row_param["param"].empty()) {
          std::string param_str = row_param["param"].asString();
          double param = 0;
          if (irs::str_to_num_classic(param_str, &param)) {
            cell.init = true;
            cell.value = param;
          }
        }
        matrix[0][row + 1] = cell;
      }
    }

    for(unsigned int row = 0; row < row_count; row++) {
      Json::Value row_param = row_parameters[row];
      cell_t cell;
      Json::Value result = row_param["result"];
      if (!result.empty()) {
        std::string value_str = result["value"].asString();
        if (irs::str_to_num_classic(value_str, &cell.value)) {
          cell.init = true;
          std::string sko_str = result["sko"].asString();
          std::string min_str = result["min"].asString();
          std::string max_str = result["max"].asString();

          irs::str_to_num_classic(sko_str, &cell.sko);
          irs::str_to_num_classic(min_str, &cell.min);
          irs::str_to_num_classic(max_str, &cell.max);
        }
        Json::Value points = result["points"];
        if (!points.empty()) {
          load_points(points, &cell.points);
        }
      }
      matrix[col + 1][row + 1] = cell;
    }
  }
  *ap_matrix = matrix;
}

void load_points(const Json::Value& a_points_value,
  cell_t::points_type* ap_points)
{
  typedef size_t size_type;

  ap_points->clear();

  if (!a_points_value.isArray()) {
    return;
  }

  for (size_type i = 0; i < a_points_value.size(); i++) {
    Json::Value point_value = a_points_value[i];

    std::string x_str = point_value["x"].asString();
    std::string y_str = point_value["y"].asString();
    cell_t::point_type point;
    if (irs::str_to_num_classic(x_str, &point.x) &&
        irs::str_to_num_classic(y_str, &point.y)) {
      ap_points->push_back(point);
    }
  }
}

namespace {

  class parse_json_error_t: std::runtime_error
  {
  public:
    explicit parse_json_error_t(const std::string& what_arg):
      std::runtime_error(what_arg)
    {}
  };

} // unnamed namespace

void load_table_from_json_file(
  number_in_param_t& a_number_in_param,
  const irs::string_t& a_file_name,
  std::vector<irs::matrix_t<cell_t> >& a_table)
{
  typedef size_t size_type;
  typedef irs::string_t string_type;

  std::ifstream ifile;
  ifile.open(IRS_SIMPLE_FROM_TYPE_STR(a_file_name.c_str()), ios::in);
  if (!ifile.good()) {
    throw runtime_error("Не удалось загрузить файл");
  }
  Json::Reader reader;
  Json::Value data;
  const bool collect_comments = false;
  const bool parsed_success = reader.parse(ifile, data, collect_comments);
  if(!parsed_success) {
    std::cout << "Failed to parse JSON" <<
      std::endl << reader.getFormatedErrorMessages() <<
      std::endl;
    throw parse_json_error_t("Не удалось разобрать файл");
  }

  const unsigned int param_count = data["parameter_count"].asUInt();

  number_in_param_t param_count_from_file = TWO_PARAM;
  if (param_count == 2)  {
    param_count_from_file = TWO_PARAM;
  } else if(param_count == 3) {
    param_count_from_file = THREE_PARAM;
  }

  a_number_in_param = param_count_from_file;

  /*if (m_inf_in_param.number_in_param != param_count_from_file) {
    return;
    // сообщение о несоответствии загруженного файла выбранной конфигурации
  } */

  a_table.clear();
  //std::vector<irs::matrix_t<cell_t> > table;
  switch (param_count_from_file) {
    case TWO_PARAM: {
      Json::Value col_parameters = data["parameters"];
      irs::matrix_t<cell_t> matrix;
      load_table_from_json(col_parameters, &matrix);
      a_table.push_back(matrix);
    } break;
    case THREE_PARAM: {
      Json::Value top_parameters = data["parameters"];
      const size_type table_count = top_parameters.size();
      a_table.reserve(table_count);
      for (unsigned int z = 0; z < table_count; z++) {
        Json::Value parameter = top_parameters[z];
        std::string param_str = parameter["param"].asString();
        cell_t cell;
        double param = 0;
        if (irs::str_to_num_classic(param_str, &param)) {
          cell.init = true;
          cell.value = param;
        }

        Json::Value col_parameters = parameter["parameters"];

        irs::matrix_t<cell_t> matrix;
        load_table_from_json(col_parameters, &matrix);
        matrix[0][0] = cell;
        a_table.push_back(matrix);
      }
    } break;
  }
}

/*void table_data_t::load_table_from_ini_file(const string_type& a_file_name)
{
  std::vector<irs::matrix_t<cell_t> > table;
  number_in_param_t param_count_from_file = TWO_PARAM;
  load_table_from_ini_file(param_count_from_file, a_file_name, table);
  if (m_inf_in_param.number_in_param == param_count_from_file) {
    mv_table.clear();
    #ifdef  debug_version_digital_interpolator
    mv_saved_table.clear();
    mv_saved_table = table;
    #endif
    mv_table = table;
    mp_display_table->out_display(mv_table, m_inf_in_param);
  } else {
    // сообщение о несоответствии загруженного файла выбранной конфигурации
  }
} */

//---------------------------------------------------------------------------
void table_data_t::load_subtable_from_file(const string_type& a_file_name)
{
  std::vector<irs::matrix_t<cell_t> > subtable;
  number_in_param_t param_count_from_file = TWO_PARAM;

  ::load_table_from_file(param_count_from_file, a_file_name, subtable);
  /*try {
    load_table_from_json_file(param_count_from_file, a_file_name, subtable);
  } catch (...) {
    load_table_from_ini_file(param_count_from_file, a_file_name, subtable);
  }*/

  //load_table_from_ini_file(param_count_from_file, a_file_name, subtable);
  if(m_inf_in_param.number_in_param != param_count_from_file){
    // сообщение о несоответствии загруженного файла выбранной конфигурации
  }else{
    switch(m_inf_in_param.number_in_param){
      case TWO_PARAM:{
        irs::matrix_t<cell_t> concat_table;
        concatenate_table_matrix(mv_table[0], subtable[0], concat_table);
        mv_table[0] = concat_table;
      } break;
      case THREE_PARAM:{
        std::vector<irs::matrix_t<cell_t> > concat_table;
        concatenate_table(mv_table, subtable, concat_table);
        mv_table = concat_table;
      } break;
    }
    #ifdef  debug_version_digital_interpolator
    mv_saved_table.clear();
    mv_saved_table = mv_table;
    #endif
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}


//---------------------------------------------------------------------------
const table_data_t& table_data_t::
  operator=(const table_data_t& a_table_source)
{
  mv_table = a_table_source.mv_table;
  mp_display_table->out_display(mv_table, m_inf_in_param);
  return *this;
}
//---------------------------------------------------------------------------
void table_data_t::clear_table()
{
  int table_count = mv_table.size();
  if(table_count > 0){
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    cell_t cell;
    cell.value = 0;
    cell.init = false;
    for(int table = 0; table < table_count; table++){
      for(int col = 0; col < col_count; col++){
        for(int row = 0; row < row_count; row++){
          mv_table[table][col][row] = cell;
        }
      }
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);

    if (!m_is_cells_config_read_only) {
      for (size_type col = 0; col < m_cells_config.get_col_count(); col++) {
        m_cells_config.write_cell(col, 0, cell_config_calibr_t());
      }
      for (size_type row = 1; row < m_cells_config.get_row_count(); row++) {
        m_cells_config.write_cell(0, row, cell_config_calibr_t());
      }
    }
  }
}
void table_data_t::clear_table_def(bool a_out_display)
{
  int table_count = mv_table.size();
  if(table_count > 0){
    const int col_count = 2;
    const int row_count = 2;
    for(int table = 0; table < table_count; table++){
      mv_table[table].resize(col_count, row_count);
    }
    cell_t clean_cell;
    clean_cell.value = 0;
    clean_cell.init = false;
    for(int table = 0; table < table_count; table++){
      for(int col = 0; col < col_count; col++){
        for(int row = 0; row < row_count; row++){
          mv_table[table][col][row] = clean_cell;
        }
      }
    }
    if (a_out_display) {
      mp_display_table->out_display(mv_table, m_inf_in_param);
    }

    if (!m_is_cells_config_read_only) {
      m_cells_config.set_col_count(mv_table[0].col_count());
      m_cells_config.set_row_count(mv_table[0].row_count());
      for (size_type col = 0; col < m_cells_config.get_col_count(); col++) {
        m_cells_config.write_cell(col, 0, cell_config_calibr_t());
      }
      for (size_type row = 1; row < m_cells_config.get_row_count(); row++) {
        m_cells_config.write_cell(0, row, cell_config_calibr_t());
      }
    }
  }
}
void table_data_t::clear_content_table()
{
  int table_count = mv_table.size();
  if(table_count > 0){
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    cell_t cell;
    cell.value = 0;
    cell.init = false;
    for(int table = 0; table < table_count; table++){
      for(int col = 1; col < col_count; col++){
        for(int row = 1; row < row_count; row++){
          mv_table[table][col][row] = cell;
        }
      }
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}
//---------------------------------------------------------------------------
void table_data_t::clear_conrent_cur_col_table()
{
  int cur_col = mp_display_table->col();
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    cell_t cell;
    cell.value = 0;
    cell.init = false;
    for(int table = 0; table < table_count; table++){
      for(int row = 1; row < row_count; row++){
        mv_table[table][cur_col][row] = cell;
      }
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}

void table_data_t::clear_countnt_cur_row_table()
{
  int cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0){
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    if (cur_row != 0) {
      cell_t cell;
      cell.value = 0;
      cell.init = false;
      for(int col = 1; col < col_count; col++){
        mv_table[cur_table][col][cur_row] = cell;
      }
      mp_display_table->out_display(mv_table, m_inf_in_param);
    }
  }
}
//---------------------------------------------------------------
void table_data_t::search_pip(const double a_limit)
{
  /*
  double difference = 0.0f;
  const int col_shift = 2;
  const int row_shift = 2;
  coord_t coord;
  mv_coord_special_cells.resize(0);
  for(int x = col_shift+1; x < mp_table->ColCount; x++){
    for(int y = row_shift; y < mp_table->RowCount; y++){
      difference = StrToFloat(mp_table->Cells[x][y])-
        StrToFloat(mp_table->Cells[x-1][y]);
      if(difference < 0)
        difference*=(-1);
      if(difference > a_limit){
        coord.x = x;
        coord.y = y;
        mv_coord_special_cells.push_back(coord);
        coord.x = x-1;
        coord.y = y;
        mv_coord_special_cells.push_back(coord);
      }
    }
  }*/
}
//-------------------------------------------------------------
void table_data_t::clear_coord_special_cells()
{
  mv_coord_special_cells.resize(0);
}

/*void table_data_t::set_file_namedir(String a_file_namedir)
{
  m_file_namedir = a_file_namedir;
}*/

String table_data_t::get_file_namedir()
{
  return m_file_namedir;
}

void table_data_t::clear_file_name()
{
  m_file_namedir = String();
}
/*void table_data_t::out_display(const vector<matrix_t<cell_t> >& av_data)
{
  unsigned int size_z = mv_table.size();
  unsigned int size_x = 0;
  unsigned int size_y = 0;
  if(size_z > 0){
    size_x = mv_table[0].col_count();
    size_y = mv_table[0].row_count();
  }
  mp_table->ColCount = size_x;
  mp_table->RowCount = size_z*size_y;
  int y1 = 0;
  for(unsigned int z = 0; z < size_z; z++){
    for(unsigned int y = 0; y < size_y; y++){
      for(unsigned int x = 0; x < size_x; x++){
        cell_t cell = mv_table[z][x][y];
        if(cell.init == true)
          mp_table->Cells[x][y1] = cell.value;
        else
          mp_table->Cells[x][y1] = "";
      }
      y1++;
    }
  }
} */

void table_data_t::get_points_func_p_of_x_cur_row(
  std::vector<cell_t>& a_p_points,
  std::vector<cell_t>& a_x_points,
  cell_t& a_z,
  int a_row_displ) const
{
  a_p_points.clear();
  a_x_points.clear();
  int cur_row_displ = 0;
  if(a_row_displ < 0)
    cur_row_displ = mp_display_table->row();
  else
    cur_row_displ = a_row_displ;
  int table_count = mv_table.size();
  if(table_count > 0){
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    a_z = mv_table[cur_table][0][0];
    for(int cur_col = 1; cur_col < col_count; cur_col++){
      cell_t cur_cell_x = mv_table[cur_table][cur_col][0];
      cell_t cur_cell_p = mv_table[cur_table][cur_col][cur_row];
      a_x_points.push_back(cur_cell_x);
      a_p_points.push_back(cur_cell_p);
    }
  }
}

void table_data_t::get_points_func_p_of_y_cur_col(
  std::vector<cell_t>& a_p_points,
  std::vector<cell_t>& a_y_points,
  cell_t& a_z,
  int a_col_displ) const
{
  a_p_points.clear();
  a_y_points.clear();
  int cur_col_displ = 0;
  if(a_col_displ < 0)
    cur_col_displ = mp_display_table->col();
  else
    cur_col_displ = a_col_displ;

  int cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_table = val.quot;
    a_z = mv_table[cur_table][0][0];
    for(int cur_row = 1; cur_row < row_count; cur_row++){
      cell_t cur_cell_y = mv_table[cur_table][0][cur_row];
      cell_t cur_cell_p = mv_table[cur_table][cur_col_displ][cur_row];
      a_y_points.push_back(cur_cell_y);
      a_p_points.push_back(cur_cell_p);
    }
  }
}
void table_data_t::get_points_func_p_of_y_cur_col_cur_table(
  std::vector<cell_t>& a_p_points,
  std::vector<cell_t>& a_y_points,
  cell_t& a_z,
  int a_col_displ,
  int a_row_displ) const
{
  a_p_points.clear();
  a_y_points.clear();
  int cur_col_displ = 0;
  if(a_col_displ < 0)
    cur_col_displ = mp_display_table->col();
  else
    cur_col_displ = a_col_displ;

  int cur_row_displ = 0;
  if(a_row_displ < 0)
    cur_row_displ = mp_display_table->row();
  else
    cur_row_displ = a_row_displ;

  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_table = val.quot;
    a_z = mv_table[cur_table][0][0];
    for(int cur_row = 1; cur_row < row_count; cur_row++){
      cell_t cur_cell_y = mv_table[cur_table][0][cur_row];
      cell_t cur_cell_p = mv_table[cur_table][cur_col_displ][cur_row];
      a_y_points.push_back(cur_cell_y);
      a_p_points.push_back(cur_cell_p);
    }
  }
}

illegal_cells_t table_data_t::get_illegal_cells() const
{
  illegal_cells_t illegal_cells;
  illegal_cells.cols.push_back(0);
  irs_u32 table_data_row_count = row_count();
  irs_u32 table_displ_row_count = get_row_count_displ();
  irs_u32 illegal_row_count = table_displ_row_count/table_data_row_count;
  for(irs_u32 i = 0; i < illegal_row_count; i++){
    illegal_cells.rows.push_back(i*table_data_row_count);
  }
  return illegal_cells;
}

void load_table_from_file(
  number_in_param_t& a_number_in_param,
  const irs::string_t& a_file_name,
  std::vector<irs::matrix_t<cell_t> >& a_table)
{
  try {
    load_table_from_json_file(a_number_in_param, a_file_name, a_table);
  } catch (parse_json_error_t /*&ex*/) {
    load_table_from_ini_file(a_number_in_param, a_file_name, a_table);
  }
}

void load_table_from_ini_file(
  number_in_param_t& a_number_in_param,
  const irs::string_t& a_file_name,
  std::vector<irs::matrix_t<cell_t> >& a_table)
{
  typedef irs::string_t string_type;

  //чтение из ini файла размеров кватерниона
  irs::handle_t<TIniFile> inifile(new TIniFile(a_file_name.c_str()));

  unsigned int param_count = 100;
  param_count = inifile->ReadInteger(irst("Setting"),
    irst("parameter_count"), param_count);
  if(param_count == 2){
    a_number_in_param = TWO_PARAM;
  }else if(param_count == 3){
    a_number_in_param = THREE_PARAM;
  }

  unsigned int size_x = 0;
  size_x = inifile->ReadInteger(irst("Setting"), "size_x", size_x);
  unsigned int size_y = 0;
  size_y = inifile->ReadInteger(irst("Setting"), "size_y", size_y);
  unsigned int size_z = 0;
  size_z = inifile->ReadInteger(irst("Setting"), "size_z", size_z);
  a_table.clear();
  a_table.reserve(size_z);
  // чтение значений ячеек кватерниона
  for(unsigned int z = 0; z < size_z; z++){
    irs::matrix_t<cell_t> matrix(size_x, size_y);
    String table_name = String(irst("table")) +
      irs::str_conv<String>(irs::num_to_str(z));
    for(unsigned int y = 0; y < size_y; y++){
      String row_str_string;
      String row_name = String(irst("row")) +
        irs::str_conv<String>(irs::num_to_str(y));
      row_str_string =
        inifile->ReadString(table_name, row_name, row_str_string);
      std::stringstream row_str(irs::str_conv<std::string>(row_str_string));
      row_str.imbue(locale::classic());
      for (unsigned int x = 0; x < size_x; x++) {
        double value_cell;
         row_str >> value_cell;
         cell_t cell;
         cell.value = value_cell;
        if (value_cell != not_a_number){
          cell.init = true;
        } else {
          cell.init = false;
        }
        matrix[x][y] = cell;
      }
    }
    a_table.push_back(matrix);
  }
}

void table_data_t::concatenate_table_matrix(
    const irs::matrix_t<cell_t>& a_in_table1,
    const irs::matrix_t<cell_t>& a_in_table2,
    irs::matrix_t<cell_t>& a_out_table)
{ 
  vector<cell_t> param_col;
  vector<cell_t> param_row;
  irs_u32 size = a_in_table1.col_count();
  for(irs_u32 i = 1; i < size; i++){
    cell_t cell = a_in_table1[i][0];
    if(cell.init != false){
      param_col.push_back(cell);
    }
  }
  size = a_in_table2.col_count();
  for(irs_u32 i = 1; i < size; i++){
    cell_t cell = a_in_table2[i][0];
    bool attend_cell = false;
    irs_u32 size_param_col = param_col.size();
    for(irs_u32 i2 = 0; i2 < size_param_col; i2++){
      if(param_col[i2] == cell){
        attend_cell = true;
        break;
      }
    }
    if(attend_cell != true){
      if(cell.init != false){
        param_col.push_back(cell);
      }
    }
  }
  sort(param_col.begin(), param_col.end());
  size = a_in_table1.row_count();
  for(irs_u32 i = 1; i < size; i++){
    cell_t cell = a_in_table1[0][i];
    if(cell.init != false){
      param_row.push_back(cell);
    }
  }
  size = a_in_table2.row_count();
  for(irs_u32 i = 1; i < size; i++){
    cell_t cell = a_in_table2[0][i];
    bool attend_cell = false;
    irs_u32 size_param_row = param_row.size();
    for(irs_u32 i2 = 0; i2 < size_param_row; i2++){
      if(param_row[i2] == cell){
        attend_cell = true;
        break;
      }
    }
    if(attend_cell != true){
      if(cell.init != false){
        param_row.push_back(cell);
      }
    }
  }
  sort(param_row.begin(), param_row.end());
  a_out_table.resize(param_col.size()+1, param_row.size()+1);
  irs_u32 a_out_table_col_count = a_out_table.col_count();
  irs_u32 a_out_table_row_count = a_out_table.row_count();
  for(irs_u32 i = 1; i < a_out_table_col_count; i++){
    a_out_table[i][0] = param_col[i-1];
  }
  for(irs_u32 i = 1; i < a_out_table_row_count; i++){
    a_out_table[0][i] = param_row[i-1];
  }
  cell_t cell_top = a_in_table2[0][0];
  a_out_table[0][0] = cell_top;
  for(irs_u32 x = 1; x < a_out_table_col_count; x++){
    for(irs_u32 y = 1; y < a_out_table_row_count; y++){
      bool attend_cell_a_in_table1 = false;
      bool attend_cell_a_in_table2 = false;
      irs_u32 a_in_table2_col_count = a_in_table2.col_count();
      irs_u32 a_in_table2_row_count = a_in_table2.row_count();
      for(irs_u32 i1 = 1; i1 < a_in_table2_col_count; i1++){
        cell_t cell_out_table = a_out_table[x][0];
        cell_t cell_in_table2 = a_in_table2[i1][0];
        if(cell_in_table2 == cell_out_table){
          for(irs_u32 i2 = 1; i2 < a_in_table2_row_count; i2++){
            cell_out_table = a_out_table[0][y];
            cell_in_table2 = a_in_table2[0][i2];
            if(cell_in_table2 == cell_out_table){
              a_out_table[x][y] = cell_t(a_in_table2[i1][i2]);
              attend_cell_a_in_table2 = true;
              break;
            }
          }
          break;
        }
      }
      if (attend_cell_a_in_table2 != true) {
        irs_u32 a_in_table1_col_count = a_in_table1.col_count();
        irs_u32 a_in_table1_row_count = a_in_table1.row_count();
        for (irs_u32 i1 = 1; i1 < a_in_table1_col_count; i1++) {
          cell_t cell_out_table = a_out_table[x][0];
          cell_t cell_in_table1 = a_in_table1[i1][0];
          if (cell_in_table1 == cell_out_table){
            for (irs_u32 i2 = 1; i2 < a_in_table1_row_count; i2++) {
              cell_out_table = a_out_table[0][y];
              cell_in_table1 = a_in_table1[0][i2];
              if (cell_in_table1 == cell_out_table) {
                a_out_table[x][y] = cell_t(a_in_table1[i1][i2]);
                attend_cell_a_in_table1 = true;
                break;
              }
            }
            break;
          }
        }
      }
      if ((attend_cell_a_in_table1 == false) &&
        (attend_cell_a_in_table2 == false)) {
        cell_t cell;
        cell.init = false;
        a_out_table[x][y] = cell;
      }
    }
  }

}

void table_data_t::concatenate_table(
    const vector<irs::matrix_t<cell_t> >& av_in_table1,
    const vector<irs::matrix_t<cell_t> >& av_in_table2,
    vector<irs::matrix_t<cell_t> >& av_out_table)
{
  vector<cell_t> param_top;
  irs_u32 size = av_in_table1.size();
  for(irs_u32 i = 0; i < size; i++){
    cell_t cell = av_in_table1[i][0][0];
    if(cell.init == true)
      param_top.push_back(cell);
  }
  size = av_in_table2.size();
  for(irs_u32 i1 = 0; i1 < size; i1++){
    cell_t cell = av_in_table2[i1][0][0];
    bool attend_cell = false;
    irs_u32 size_param_top = param_top.size();
    for(irs_u32 i2 = 0; i2 < size_param_top; i2++) {
      if(param_top[i2] == cell) {
        attend_cell = true;
        break;
      }
    }
    if(attend_cell != true) {
      if(cell.init != false) {
        param_top.push_back(cell);
      }
    }
  }
  sort(param_top.begin(), param_top.end());
  av_out_table.clear();
  size = param_top.size();
  av_out_table.resize(size);

  for(irs_u32 i = 0; i < size; i++){
    cell_t cell = param_top[i];
    //av_out_table[i][0][0] = cell;
    bool attend_cell_a_in_table1 = false;
    bool attend_cell_a_in_table2 = false;
    irs_u32 av_in_table1_top_count = av_in_table1.size();
    irs_u32 av_in_table2_top_count = av_in_table2.size();
    irs_u32 index_in_table1 = 0;
    irs_u32 index_in_table2 = 0;
    for(irs_u32 i1 = 0; i1 < av_in_table1_top_count; i1++){
      cell_t cell_in_table1 = av_in_table1[i1][0][0];
      if(cell_in_table1 == cell){
        index_in_table1 = i1;
        attend_cell_a_in_table1 = true;
      }
    }
    for(irs_u32 i2 = 0; i2 < av_in_table2_top_count; i2++){
      cell_t cell_in_table2 = av_in_table2[i2][0][0];
      if(cell_in_table2 == cell){
        index_in_table2 = i2;
        attend_cell_a_in_table2 = true;
      }
    }
    if(attend_cell_a_in_table1 == true && attend_cell_a_in_table2 == true) {
      concatenate_table_matrix(
        av_in_table1[index_in_table1],
        av_in_table2[index_in_table2],
        av_out_table[i]);
    }else if(attend_cell_a_in_table1 == true){
      av_out_table[i] = av_in_table1[index_in_table1];
    }else if(attend_cell_a_in_table2 == true){
      av_out_table[i] = av_in_table2[index_in_table2];
    }
  }
}
void table_data_t::restruct_date_type_1()
{
  int table_count = mv_table.size();
  if (table_count > 0) {
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    const int start_table_index = 1;
    for (int i = start_table_index; i < table_count; i++) {
      cell_t cell_addition = mv_table[i][0][0];
      double addition = 0;
      if (cell_addition.init) addition = cell_addition.value;
      for (int col = 1; col < col_count; col++) {
        for (int row = 1; row < row_count; row++) {
          cell_t cur_cell = mv_table[0][col][row];
          cell_t new_value_cell(0, true);
          if (cur_cell.init) {
            new_value_cell.value = cur_cell.value+addition;
            mv_table[i][col][row] = new_value_cell;
          }
        }
      }
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}

void table_data_t::inversion_sign_conrent_table()
{
  int table_count = mv_table.size();
  if(table_count > 0){
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    for(int table = 0; table < table_count; table++){
      for(int col = 1; col < col_count; col++){
        for(int row = 1; row < row_count; row++){
          cell_t cell;
          cell = mv_table[table][col][row];
          cell.value = -cell.value;
          mv_table[table][col][row] = cell;
        }
      }
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}

void table_data_t::modify_content_table(const string_type& a_str)
{
  const string_type z_name = irst("z");
  const string_type x_name = irst("x");
  const string_type y_name = irst("y");
  const int z_name_size = z_name.size();
  const int x_name_size = x_name.size();
  const int y_name_size = y_name.size();
  int table_count = mv_table.size();
  if(table_count > 0){
    irs::calc::calculator_t calculator;
    calculator.function_add(irst("phasen180"),
        new irs::calc::func_r_double_a_double_t(irs::phase_normalize_180));
    //calculator. add_func_r_double_a_double(
      //"phasen180",
      //irs::phase_normalize_180);
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    for(int table = 0; table < table_count; table++){
      for(int col = 1; col < col_count; col++){
        for(int row = 1; row < row_count; row++){
          cell_t cell_param_col = mv_table[table][col][0];
          cell_t cell_param_row = mv_table[table][0][row];
          cell_t cell = mv_table[table][col][row];
          bool replace_str_success = true;
          string_type mathem_expression_str = a_str;
          size_type z_param_pos = mathem_expression_str.find(z_name);
          while(z_param_pos != irs::string::npos) {
            if (cell.init) {
              string_type param_z_str = cell.value;
              mathem_expression_str.replace(
                z_param_pos, z_name_size, param_z_str);
              z_param_pos = mathem_expression_str.find(z_name);
            } else {
              replace_str_success = false;
              break;
            }
          }
          size_type x_param_pos = mathem_expression_str.find(x_name);
          while (x_param_pos != irs::string::npos) {
            if (cell_param_col.init) {
              string_type param_col_str = cell_param_col.value;
              mathem_expression_str.replace(
                x_param_pos, x_name_size, param_col_str);
            }  else {
              replace_str_success = false;
              break;
            }
            x_param_pos = mathem_expression_str.find(x_name);
          }
          size_type y_param_pos = mathem_expression_str.find(y_name);
          while (y_param_pos != irs::string::npos) {
            if (cell_param_row.init) {
              string_type param_row_str = cell_param_row.value;
              mathem_expression_str.replace(
                y_param_pos, y_name_size, param_row_str);
            } else {
              replace_str_success = false;
              break;
            }
            y_param_pos = mathem_expression_str.find(y_name);
          }

          if (replace_str_success) {
            irs::variant::variant_t value;
            if (calculator.calc(&mathem_expression_str, &value)) {
              if (value.convert_to(irs::variant::var_type_double)) {
                cell.value = value.as_double();
                cell.init = true;
                mv_table[table][col][row] = cell;
              }
            }
          }
        }
      }
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }
}


void table_data_t::copy_cells_config(const coord_t& a_src_cell, const TRect& a_range)
{
  if (m_is_cells_config_read_only)
    return;

  
  if (is_cells_config_range_valid(a_range) && is_cells_config_coord_valid(a_src_cell)) {
    //irs::is_in_range(a_src_cell.x, 1, static_cast<int>(m_cells_config.get_col_count()) - 1) &&
    //irs::is_in_range(a_src_cell.y, 1, static_cast<int>(m_cells_config.get_row_count()) - 1)) {

    cell_config_calibr_t cell_config = m_cells_config.read_cell(a_src_cell.x, a_src_cell.y);

    size_type start_col = static_cast<size_type>(a_range.Left);
    size_type stop_col = static_cast<size_type>(a_range.Right);
    size_type start_row = static_cast<size_type>(a_range.Top);
    size_type stop_row = static_cast<size_type>(a_range.Bottom);
    for (size_type col_i = start_col; col_i <= stop_col; col_i++) {
      for (size_type row_i = start_row; row_i <= stop_row; row_i++) {
        m_cells_config.write_cell(col_i, row_i, cell_config);
      }
    }
  }   
}


bool table_data_t::is_cells_config_coord_valid(const coord_t& a_coord) const
{
  return irs::is_in_range(a_coord.x, 1, static_cast<int>(m_cells_config.get_col_count()) - 1) &&
    irs::is_in_range(a_coord.y, 1, static_cast<int>(m_cells_config.get_row_count()) - 1);
}



bool table_data_t::is_cells_config_range_valid(const TRect& a_rect) const
{
  int table_count = mv_table.size();
  if(table_count > 0) {
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();

    return irs::is_in_range<int>(a_rect.Left, 1, col_count - 1 ) &&
      irs::is_in_range<int>(a_rect.Top, 1, row_count - 1 ) &&
      irs::is_in_range<int>(a_rect.Right, 1, col_count - 1 ) &&
      irs::is_in_range<int>(a_rect.Bottom, 1, row_count - 1 );
  }

  return false;  
}

/*static*/ bool table_data_t::displ_table_matches_config_table(
  const irs::matrix_t<cell_t>& a_table,
  const irs::table_t<cell_config_calibr_t>& a_cells_config)
{
  bool are_headers_different = false;
    
  if (static_cast<size_type>(a_table.col_count()) ==
      a_cells_config.get_col_count() &&
    static_cast<size_type>(a_table.row_count()) ==
      a_cells_config.get_row_count()) {

    IRS_ASSERT(a_table.col_count() > 1 && a_table.row_count() > 1);

    for (int col = 0; col < a_table.col_count(); col++) {
      cell_t data_cell = a_table[col][0];
      cell_config_calibr_t cell_config =
        a_cells_config.read_cell(col, 0);

      if (data_cell.init != cell_config.is_value_initialized ||
        !is_equals(data_cell.value, cell_config.value)) {
        are_headers_different = true;
        break;
      }
    }

    if (!are_headers_different) {
      for (int row = 1; row < a_table.row_count(); row++) {
        cell_t data_cell = a_table[0][row];
        cell_config_calibr_t cell_config = a_cells_config.read_cell(0, row);
        if (data_cell.init != cell_config.is_value_initialized ||
          !is_equals(data_cell.value, cell_config.value)) {
          are_headers_different = true;
          break;
        }
      }
    }
  } else {
    are_headers_different = true;
  }

  return !are_headers_different;
}


void table_data_t::set_data_table_to_config(irs::matrix_t<cell_t>* ap_table)
{
  size_type col_count = max<size_type>(ap_table->col_count(),
    m_cells_config.get_col_count());
  size_type row_count = max<size_type>(ap_table->row_count(),
    m_cells_config.get_row_count());

  const size_type old_config_col_count = m_cells_config.get_col_count();
  const size_type old_config_row_count = m_cells_config.get_row_count();

  if (static_cast<size_type>(ap_table->col_count()) < col_count) {
    ap_table->newcols(ap_table->col_count(), col_count - ap_table->col_count(),
      cell_t());
  }

  if (static_cast<size_type>(ap_table->row_count()) < row_count) {
    ap_table->newrows(ap_table->row_count(), row_count - ap_table->row_count(),
      cell_t());
  }

  m_cells_config.set_col_count(col_count);
  m_cells_config.set_row_count(row_count);

  for (int col = 0; col < ap_table->col_count(); col++) {
    cell_t data_cell = (*ap_table)[col][0];
    cell_config_calibr_t cell_config;
    cell_config.is_value_initialized = data_cell.init;
    cell_config.value = data_cell.value;

    m_cells_config.write_cell(col, 0, cell_config);
  }

  for (int row = 1; row < ap_table->row_count(); row++) {
    cell_t data_cell = (*ap_table)[0][row];
    cell_config_calibr_t cell_config;
    cell_config.is_value_initialized = data_cell.init;
    cell_config.value = data_cell.value;

    m_cells_config.write_cell(0, row, cell_config);
  }

  IRS_ASSERT(old_config_col_count > 1 );
  IRS_ASSERT(old_config_row_count > 1 );

  for (size_type col = old_config_col_count; col < col_count; col++) {
    for (size_type row = 1; row < old_config_row_count; row++) {

      cell_config_calibr_t cell_config =
        m_cells_config.read_cell(old_config_col_count - 1, row);
      m_cells_config.write_cell(col, row, cell_config);
    }
  }

  for (size_type col = 1; col < col_count; col++) {
    for (size_type row = old_config_row_count; row < row_count; row++) {

      cell_config_calibr_t cell_config =
        m_cells_config.read_cell(col, old_config_row_count - 1);
      m_cells_config.write_cell(col, row, cell_config);
    }
  }

  config_calibr_t::check_cells_config(m_cells_config);
}

void table_data_t::set_config_table_to_data(irs::matrix_t<cell_t>* ap_table)
{
  size_type col_count = max<size_type>(ap_table->col_count(),
    m_cells_config.get_col_count());
  size_type row_count = max<size_type>(ap_table->row_count(),
    m_cells_config.get_row_count());

  const size_type old_config_col_count = m_cells_config.get_col_count();
  const size_type old_config_row_count = m_cells_config.get_row_count();

  if (static_cast<size_type>(ap_table->col_count()) < col_count) {
    ap_table->newcols(ap_table->col_count(), col_count - ap_table->col_count(),
      cell_t());
  }

  if (static_cast<size_type>(ap_table->row_count()) < row_count) {
    ap_table->newrows(ap_table->row_count(), row_count - ap_table->row_count(),
      cell_t());
  }

  m_cells_config.set_col_count(col_count);
  m_cells_config.set_row_count(row_count);

  for (int col = 0; col < ap_table->col_count(); col++) {
    cell_t data_cell;
    cell_config_calibr_t cell_config = m_cells_config.read_cell(col, 0);
    data_cell.init = cell_config.is_value_initialized;
    data_cell.value = cell_config.value;

    (*ap_table)[col][0] = data_cell;
  }

  for (int row = 1; row < ap_table->row_count(); row++) {
    cell_t data_cell;
    cell_config_calibr_t cell_config = m_cells_config.read_cell(0, row);
    data_cell.init = cell_config.is_value_initialized;
    data_cell.value = cell_config.value;

    (*ap_table)[0][row] = data_cell;    
  }

  IRS_ASSERT(old_config_col_count > 1 );
  IRS_ASSERT(old_config_row_count > 1 );

  for (size_type col = old_config_col_count; col < col_count; col++) {
    for (size_type row = 1; row < old_config_row_count; row++) {

      cell_config_calibr_t cell_config =
        m_cells_config.read_cell(old_config_col_count - 1, row);
      m_cells_config.write_cell(col, row, cell_config);
    }
  }

  for (size_type col = 1; col < col_count; col++) {
    for (size_type row = old_config_row_count; row < row_count; row++) {

      cell_config_calibr_t cell_config =
        m_cells_config.read_cell(col, old_config_row_count - 1);
      m_cells_config.write_cell(col, row, cell_config);
    }
  }

  config_calibr_t::check_cells_config(m_cells_config);
}

//class table_data_size_t
table_data_size_t::table_data_size_t(table_data_t* ap_table_data
):
  mp_table_data(ap_table_data)
{
}

table_data_size_t::size_type table_data_size_t::get_col_count() const
{
  size_type col_count =  mp_table_data->get_col_count_displ();
  return col_count;
}

table_data_size_t::size_type table_data_size_t::get_row_count() const
{
  size_type row_count = mp_table_data->get_row_count_displ();
  return row_count;
}

//-------------------------------------------------------------
log_t::log_t(TMemo* ap_memo, string_type a_file_name):
  m_error_open_file_log(0),
  #ifdef type_log_stream
  m_buflog(ap_memo),
  m_log_display(&m_buflog),
  #else
  mp_memo(ap_memo),
  #endif
  m_outfile(IRS_SIMPLE_FROM_TYPE_STR(a_file_name.c_str()), ios::app)
{
  if(!m_outfile)
    m_error_open_file_log = false;
  else
    m_error_open_file_log = true;
  //m_outfile.seekp(0, ios::end);
}
log_t::~log_t()
{
  m_outfile.close();
}

void log_t::operator<<(String a_str)
{
  String time_str;
  String date_time_str;

  TDateTime time;
  TDateTime date_time;
  time = Time();
  date_time = Now();
  time_str = TimeToStr(time);
  date_time_str = DateTimeToStr(date_time);
  if(m_error_open_file_log == true) {
    m_outfile << setw(m_field_width_file_date_time) << left <<
      date_time_str.c_str() << a_str.c_str() << endl;
  }
  #ifdef type_log_stream
  m_log_display << setw(m_field_width_display_time) << left <<
    time_str.c_str() << a_str.c_str()<<endl;
  #else
  ostringstream_type ostr;
  ostr << setw(m_field_width_file_date_time) << left <<
    date_time_str.c_str() << a_str.c_str();
  mp_memo->Lines->Add(irs::str_conv<String>(ostr.str()));
  #endif
}

//извлекает из имени файла(без пути) имя файла без расширения
String extract_short_filename(const String& a_filename)
{
  String ext_filename = ExtractFileExt(a_filename);
  String short_filename;
  int length_filename = a_filename.Length();
  int length_ext = ext_filename.Length();
  if(length_filename > length_ext){
    short_filename = a_filename.SubString(1,length_filename-length_ext);
  }
  return short_filename;
}
//-------------------------------------------------------------------------
int get_index_row_combo_box_str(
  const TComboBox* const ap_combo_box,
  const String& a_text)
{
  int index = 0;
  for(int i = 0; i < ap_combo_box->Items->Count; i++){
    //AnsiString fff = ap_combo_box->Items->Strings[i];
    if(ap_combo_box->Items->Strings[i] == a_text){
      index = i;
      break;
    }
  }
  return index;
}


//cell_config_calibr_t
cell_config_calibr_t::cell_config_calibr_t():
  value(0),
  is_value_initialized(false),
  /*input_param1_coef(1),
  input_param2_coef(1),
  input_param3_coef(1),*/
  output_param_coef(1),
  ex_param_work_values(),
  ex_bit_work_values(),
  type_meas(irs::str_conv<String>(type_meas_to_str(tm_first))),
  range_enabled(false),
  range(1),
  delay_meas(0),
  meas_interval(0),
  count_reset_over_bit(0),
  out_param_measuring_conf(),
  out_param_control_config(),
  temperature_control()
{
}


void cell_config_calibr_t::clear()
{
  *this = cell_config_calibr_t();
}


bool cell_config_calibr_t::operator==(const cell_config_calibr_t& a_config) const
{
  if (ex_param_work_values.size() != a_config.ex_param_work_values.size()) {
    return false;
  }

  if (!std::equal(ex_param_work_values.begin(), ex_param_work_values.end(),
    a_config.ex_param_work_values.begin(), is_equals<double>)) {
    return false;
  }


  if( ex_bit_work_values != a_config.ex_bit_work_values) {
    return false;
  }

  return is_equals(value, a_config.value) &&
      is_value_initialized == a_config.is_value_initialized &&
      type_meas == a_config.type_meas &&
      range_enabled == a_config.range_enabled &&
      is_equals(range, a_config.range) &&
      delay_meas == a_config.delay_meas &&
      is_equals(meas_interval, a_config.meas_interval) &&
      count_reset_over_bit == a_config.count_reset_over_bit &&
      is_equals(output_param_coef, a_config.output_param_coef) &&
      out_param_measuring_conf == a_config.out_param_measuring_conf &&
      out_param_control_config == a_config.out_param_control_config &&
      temperature_control == a_config.temperature_control;
}


bool cell_config_calibr_t::operator!=(const cell_config_calibr_t& a_config) const
{
  return !operator==(a_config);
}


void cell_config_calibr_t::load_from_json( const Json::Value& a_data, bool a_is_header_cell )
{
  clear();

  if (a_is_header_cell) {
    if(!a_data["value"].empty() && jsonv_get_num(a_data["value"], &value)) {
      is_value_initialized = true;
    }
  } else {
    {
      Json::Value param = a_data["output_parameter"];
      if (!param.empty()) {
        irs::str_to_num_classic(param["coefficient"].asString(), &output_param_coef);
      }

      if (a_data["ex_param_work_values"].isArray()) {
        Json::Value values = a_data["ex_param_work_values"];
        for (size_t i = 0; i < values.size(); i++) {
          Json::Value value = values[i];
          double work_value = 0;
          jsonv_get_num(value, &work_value);
          ex_param_work_values.push_back(work_value);
        }
      }

      if (a_data["ex_bit_work_values"].isArray()) {
        Json::Value values = a_data["ex_bit_work_values"];
        for (size_t i = 0; i < values.size(); i++) {
          Json::Value value = values[i];
          bool work_value = 0;
          jsonv_get_num(value, &work_value);
          ex_bit_work_values.push_back(work_value);
        }
      }

      {
        Json::Value data = a_data["measurement"];
        jsonv_get_cbstr(data["type"], &type_meas);
        jsonv_get_num(data["range_enabled"], &range_enabled);
        jsonv_get_num(data["range"], &range);
        jsonv_get_num(data["delay"], &delay_meas);
        jsonv_get_num(data["time"], &meas_interval);
        jsonv_get_num(data["error_amount_max"], &count_reset_over_bit);
      }

      {
        Json::Value data = a_data["output_parameter_options"];
        jsonv_get_num(data["consider"], &out_param_measuring_conf.consider_out_param);

        Json::Value filter = data["filter"];
        jsonv_get_num(filter["enabled"], &out_param_measuring_conf.filter_enabled);
        jsonv_get_num(filter["sampling_time"], &out_param_measuring_conf.filter_sampling_time);
        jsonv_get_num(filter["point_count"], &out_param_measuring_conf.filter_point_count);

        Json::Value control = data["control"];
        jsonv_get_num(control["enabled"], &out_param_control_config.enabled);
        jsonv_get_num(control["relative_deviation_max"], &out_param_control_config.max_relative_difference);
        jsonv_get_num(control["time"], &out_param_control_config.time);
      }

      {
        Json::Value data = a_data["temperature_control"];

        jsonv_get_num(data["enabled"],        &temperature_control.enabled);
        jsonv_get_num(data["reference"],      &temperature_control.reference);
        jsonv_get_num(data["deviation_max"],  &temperature_control.difference);
      }
    }
  }
}


Json::Value cell_config_calibr_t::save_to_json(bool is_header_cell) const
{
  Json::Value root;

  if (is_header_cell){
    root["value"] = num_to_u8(value);
  } else {
    {
      Json::Value data;
      data["coefficient"] = num_to_u8(output_param_coef);
      root["output_parameter"] = data;
    }

    {
      Json::Value ex_params(Json::arrayValue);
      for (size_type i = 0; i < ex_param_work_values.size(); i++) {
        Json::Value value = num_to_u8(ex_param_work_values[i]);
        ex_params.append(value);
      }
      root["ex_param_work_values"] = ex_params;     
    }

    {
      Json::Value ex_bits(Json::arrayValue);
      for (size_type i = 0; i < ex_bit_work_values.size(); i++) {
        Json::Value value = num_to_u8(ex_bit_work_values[i]);
        ex_bits.append(value);
      }
      root["ex_bit_work_values"] = ex_bits;     
    }

    {
      Json::Value data;
      data["type"] = irs::encode_utf_8(type_meas);
      data["range_enabled"] = num_to_u8(range_enabled);
      data["range"] = num_to_u8(range);
      data["delay"] = num_to_u8(delay_meas);
      data["time"] = num_to_u8(meas_interval);
      data["error_amount_max"] = num_to_u8(count_reset_over_bit);

      root["measurement"] = data;
    }

    {
      Json::Value data;
      data["consider"] = num_to_u8(out_param_measuring_conf.consider_out_param);
      Json::Value filter;
      filter["enabled"] = num_to_u8(out_param_measuring_conf.filter_enabled);
      filter["sampling_time"] = num_to_u8(out_param_measuring_conf.filter_sampling_time);
      filter["point_count"] = num_to_u8(out_param_measuring_conf.filter_point_count);
      data["filter"] = filter;

      Json::Value control;
      control["enabled"] = num_to_u8(out_param_control_config.enabled);
      control["relative_deviation_max"] = num_to_u8(out_param_control_config.max_relative_difference);
      control["time"] = num_to_u8(out_param_control_config.time);
      data["control"] = control;

      root["output_parameter_options"] = data;
    }

    {
      Json::Value data;
      data["enabled"] = num_to_u8(temperature_control.enabled);
      data["reference"] = num_to_u8(temperature_control.reference);
      data["deviation_max"] = num_to_u8(temperature_control.difference);

      root["temperature_control"] = data;
    }
  }

  return root;
}

//-------------------------------------------------------------------------
//struct config_calibr_t
config_calibr_t::config_calibr_t():
  device_name(),
  reference_device_name(),
  ip_adress(irst("192.168.0.200")),
  port(5005),
  in_parameter1(),
  in_parameter2(),
  in_parameter3(),
  out_parameter(),
  v_parameter_ex(),
  bit_pos_mismatch_state(),
  bit_pos_correct_mode(),
  bit_pos_operating_duty(),
  bit_pos_error_bit(),
  bit_pos_reset_over_bit(),
  bit_pos_phase_preset_bit(),
  bit_type2_array(),
  index_work_time(0),
  index_pos_eeprom(0),
  temperature_ctrl_common_cfg(),
  type_sub_diapason(tsd_parameter2),
  eeprom_ranges(),
  active_filename(),
  reference_channel(),
  cells_config()
{
  in_parameter2.anchor = 1; // TWO_PARAM
}


void config_calibr_t::clear()
{
  *this = config_calibr_t();
}

namespace {

Json::Value bit_to_json(const bit_type1_pos_t& bit)
{
   Json::Value data;
   data["byte_index"] = num_to_u8(bit.index_byte);
   data["bit_index"] = num_to_u8(bit.index_bit);
   return data;
}

bool jsonv_get_bit(const Json::Value& a_value, bit_type1_pos_t* ap_bit)
{
  if( !a_value["byte_index"].isString() || !a_value["bit_index"].isString() )
    return false;

  bit_type1_pos_t bit;
  if( !irs::str_to_num_classic( a_value["byte_index"].asString(), &bit.index_byte ) ) {
    return false;
  }

  if( !irs::str_to_num_classic( a_value["bit_index"].asString(), &bit.index_bit ) ) {
    return false;
  }

  *ap_bit = bit;
  return true;
}

} // unnamed namespace

bool config_calibr_t::save(const string_type& a_filename)
{
  if (a_filename.empty()) {
    return false;
  }

  ofstream ofile;
  string_type filename = a_filename;
  ofile.open(IRS_SIMPLE_FROM_TYPE_STR(filename.c_str()), ios::in|ios::out|ios::trunc);

  if (!ofile.good()) {
    throw runtime_error("Не удалось сохранить файл");
  }

  return save_to_json(&ofile);
}


bool config_calibr_t::save_to_json(std::ostream* ap_ostr)
{
  check_config(*this);

  bool fsuccess = true;

  Json::Value root;

  {
    Json::Value data;
    data["name"] = irs::encode_utf_8(device_name);
    root["device"] = data;
  }

  {
    Json::Value data;
    data["enabled"] = num_to_u8(reference_channel.enabled);
    data["name"] = irs::encode_utf_8(reference_device_name);
    root["reference_device"] = data;
  }

  // input_parameter1
  {
    Json::Value data;
    data["type"] = irs::encode_utf_8(lang_type_to_str(in_parameter1.type));
    data["name"] = irs::encode_utf_8(in_parameter1.name);
    data["unit"] = irs::encode_utf_8(in_parameter1.unit);
    data["binding"] = num_to_u8(in_parameter1.anchor);
    data["index"] = num_to_u8(in_parameter1.index);
    data["coefficient"] = num_to_u8(in_parameter1.koef);
    data["default_value"] = num_to_u8(in_parameter1.default_val);
    root["input_parameter1"] = data;
  }

  // input_parameter2
  {
    Json::Value data;
    data["type"] = irs::encode_utf_8(lang_type_to_str(in_parameter2.type));
    data["name"] = irs::encode_utf_8(in_parameter2.name);
    data["unit"] = irs::encode_utf_8(in_parameter2.unit);
    data["binding"] = num_to_u8(in_parameter2.anchor);
    data["index"] = num_to_u8(in_parameter2.index);
    data["coefficient"] = num_to_u8(in_parameter2.koef);
    data["default_value"] = num_to_u8(in_parameter2.default_val);
    root["input_parameter2"] = data;
  }

  // input_parameter3
  {
    Json::Value data;
    data["type"] = irs::encode_utf_8(lang_type_to_str(in_parameter3.type));
    data["name"] = irs::encode_utf_8(in_parameter3.name);
    data["unit"] = irs::encode_utf_8(in_parameter3.unit);
    data["index"] = num_to_u8(in_parameter3.index);
    data["coefficient"] = num_to_u8(in_parameter3.koef);
    data["default_value"] = num_to_u8(in_parameter3.default_val);
    root["input_parameter3"] = data;
  }

  // output_parameter
  {
    Json::Value data;
    data["type"] = irs::encode_utf_8(lang_type_to_str(out_parameter.type));
    data["name"] = irs::encode_utf_8(out_parameter.name);
    data["unit"] = irs::encode_utf_8(out_parameter.unit);
    data["index"] = num_to_u8(out_parameter.index);

    root["output_parameter"] = data;
  }


  // EEPROM
  {
    Json::Value data;
    data["pos_index"] = num_to_u8(index_pos_eeprom);   // Индекс воронки

    int subrange_amount = eeprom_ranges.size();
    int num_param_subrange = type_sub_diapason == tsd_parameter1 ? 1 : 2;
    //data["range_amount"] = num_to_u8(subrange_amount);
    data["range_type"] = num_to_u8(num_param_subrange);

    Json::Value ranges(Json::arrayValue);

    for (int i = 0; i < subrange_amount; i++) {
      Json::Value range;

      int index_start = eeprom_ranges[i].index_start;
      int size = eeprom_ranges[i].size;
      double value_begin = eeprom_ranges[i].value_begin;
      double value_end = eeprom_ranges[i].value_end;

      range["position"] = num_to_u8(index_start);
      range["size"] = num_to_u8(size);
      range["min"] = num_to_u8(value_begin);
      range["max"] = num_to_u8(value_end);

      ranges.append(range);
    }

    data["ranges"] = ranges;
    root["eeprom"] = data;
  }

  // доп.параметры
  {
    int extra_param_amount = v_parameter_ex.size();

    Json::Value params(Json::arrayValue);
    for (int i = 0; i < extra_param_amount; i++) {
      Json::Value param;

      String name = v_parameter_ex[i].name.c_str();
      String type = lang_type_to_str(v_parameter_ex[i].type).c_str();
      String unit = v_parameter_ex[i].unit.c_str();
      irs_i32 index = v_parameter_ex[i].index;
      double value_default = v_parameter_ex[i].value_default;

      param["name"] = irs::encode_utf_8(name);
      param["type"] = irs::encode_utf_8(type);
      param["unit"] = irs::encode_utf_8(unit);
      param["byte_index"] = num_to_u8(index);
      param["default_value"] = num_to_u8(value_default);
      params.append(param);
    }
    root["extra_parameters"] = params;
  }

  // сетевые переменные
  {
    Json::Value data;
    data["work_time"] = num_to_u8(index_work_time);
    root["bytes"] = data;
  }

  // сетевые биты
  {
    Json::Value data;
    data["mismatch_state"] = bit_to_json(bit_pos_mismatch_state);
    data["correct_mode"] = bit_to_json(bit_pos_correct_mode);
    data["operating_duty"] = bit_to_json(bit_pos_operating_duty);
    data["error_bit"] = bit_to_json(bit_pos_error_bit);
    data["reset_over_bit"] = bit_to_json(bit_pos_reset_over_bit);
    data["phase_preset_bit"] = bit_to_json(bit_pos_phase_preset_bit);

    root["bits"] = data;
  }

  // доп.сетевые биты
  {
    int bit_type2_amount = bit_type2_array.size();
    Json::Value bits(Json::arrayValue);
    for (int i = 0; i < bit_type2_amount; i++) {
      Json::Value bit;

      String bitname = bit_type2_array[i].bitname.c_str();
      int index_byte = bit_type2_array[i].index_byte;
      int index_bit = bit_type2_array[i].index_bit;
      bool value_def = bit_type2_array[i].value_def;

      bit["name"] = irs::encode_utf_8(bitname);
      bit["byte_index"] = num_to_u8(index_byte);
      bit["bit_index"] = num_to_u8(index_bit);
      bit["defalut_value"] = num_to_u8(bit_type2_array[i].value_def);
      bits.append(bit);
    }
    root["extra_bits"] = bits;
  }

  {
    Json::Value data;
    data["enabled"] = num_to_u8(temperature_ctrl_common_cfg.enabled);
    data["index"] = num_to_u8(temperature_ctrl_common_cfg.index);

    root["temperature_ctrl_common_cfg"] = data;
  }

  // Оптимизация. Ищем, настройки какой ячейки встречаются чаще всего и сохраняем
  //  эти настройки отдельно. При загрузке настроек сначала инициализируем все
  //  ячейки этими настройками, а затем перезаписываем ячейки с отличающимися
  //  настройками. Это позволит уменьшить объем данных. Если в таблице один
  //  диапазон, то будут записаны настройки только одной ячейки
  cell_config_calibr_t default_cell_config;
  size_t default_config_amount = 0;
  {
    cell_config_calibr_t default_config;

    const size_t col_count = cells_config.get_col_count();
    const size_t row_count = cells_config.get_row_count();

    size_t best_col = 0;
    size_t best_row = 0;

    for (size_t col = 1; col < col_count; col++) {
      for (size_t row = 1; row < row_count; row++) {
        const cell_config_calibr_t cell = cells_config.read_cell(col, row);
        size_t amount = 0;
        size_t col2 = col;
        size_t row2 = row + 1;
        if(row >= row_count)
        {
          col2++;
          row2 = 0;
        }
        for (; col2 < col_count; col2++) {
          for (; row2 < row_count; row2++) {
            if (cell == cells_config.read_cell(col2, row2)) {
              amount++;
              if(amount > default_config_amount)
              {
                 best_col = col2;
                 best_row = row2;
                 default_config_amount = amount;
                 default_cell_config = cell;
              }
            }
          }
        }
      }
    }
    if(default_config_amount > 0) {
      root["default_cell_config"] = default_cell_config.save_to_json(false);
    }
  }

  {
    const size_t col_count = cells_config.get_col_count();
    const size_t row_count = cells_config.get_row_count();

    Json::Value cells_data;
    cells_data["col_count"] = num_to_u8(col_count);
    cells_data["row_count"] = num_to_u8(row_count);

    // Записываем таблицу настроек в виде массива столбцов. Каждый столбец
    // состоит из массива ячеек, соответствующих строкам. Значение и индекс
    // столбца записываются в столбец, а значение и индекс строки в
    // каждую ячейку
    Json::Value cols_data(Json::arrayValue);

    for (size_t col_i = 0; col_i < col_count; col_i++) {
      Json::Value col_data;
      const cell_config_calibr_t col_header = cells_config.read_cell(col_i, 0);
      if (col_header.is_value_initialized) {
        col_data["col"] = col_header.save_to_json(true);
      }
      col_data["col_i"] = num_to_u8(col_i);

      Json::Value cells_data(Json::arrayValue);
      for(size_t row_i = col_i == 0 ? 0 : 1; row_i < row_count; row_i++) {
        Json::Value cell_data;
        const cell_config_calibr_t row_cell = cells_config.read_cell(col_i, row_i);
        if (col_i == 0 && row_cell.is_value_initialized) {
          cell_data["row"] = row_cell.save_to_json(true);
        } else if(col_i > 0 && row_i > 0) {
          const cell_config_calibr_t cell = cells_config.read_cell(col_i, row_i);
          if (cell != default_cell_config) {
            cell_data["config"] = cell.save_to_json(false);
          }
        }
        if(!cell_data.empty()) {
          cell_data["row_i"] = num_to_u8(row_i);
          cells_data.append(cell_data);
        }
      }
      col_data["cells"] = cells_data;
      cols_data.append(col_data);
    }

    cells_data["cols"] = cols_data;
    root["cells_config"] = cells_data;
  }

  root["last_active_file"] = irs::encode_utf_8(active_filename);

  /*ofstream ofile;
  string_type filename = a_filename;
  change_file_ext(string_type("jsontest"), &filename);
  ofile.open(IRS_SIMPLE_FROM_TYPE_STR(filename.c_str()), ios::in|ios::out|ios::trunc);

  if (!ofile.good()) {
    throw runtime_error("Не удалось сохранить файл");
  }

  ofile << root << std::endl;*/

  *ap_ostr << root << std::endl;

  return true;
}

bool config_calibr_t::save_to_ini(const string_type& a_filename)
{
  bool fsuccess = true;
  if (a_filename.empty()) {
    fsuccess = false;
    return fsuccess;
  }

  cell_config_calibr_t cell_config_calibr;

  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_filename.c_str());
  ini_file.clear_control();
  add_static_param(&ini_file, &cell_config_calibr);
  ini_file.save();
  ini_file.clear_control();

  ini_file.set_section(irst("Конфигурация устройства"));
  ini_file.add(irst("Имя"), &device_name);

  ini_file.set_section(irst("Конфигурация опорного устройства"));
  ini_file.add(irst("Имя"), &reference_device_name);

  string_type in_parametr1_unit_str = lang_type_to_str(in_parameter1.type);
  string_type in_parametr2_unit_str = lang_type_to_str(in_parameter2.type);
  string_type in_parametr3_unit_str = lang_type_to_str(in_parameter3.type);
  string_type out_parametr_unit_str = lang_type_to_str(out_parameter.type);
  ini_file.set_section(irst("Входной параметр 1"));
  ini_file.add(irst("Тип параметра"), &in_parametr1_unit_str);
  ini_file.set_section(irst("Входной параметр 2"));
  ini_file.add(irst("Тип параметра"), &in_parametr2_unit_str);
  ini_file.set_section(irst("Входной параметр 3"));
  ini_file.add(irst("Тип параметра"), &in_parametr3_unit_str);
  ini_file.set_section(irst("Выходной параметр"));
  ini_file.add(irst("Тип параметра"), &out_parametr_unit_str);
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section(irst("Опции"));
  int sub_diapason_count = eeprom_ranges.size();
  ini_file.add(String(irst("Количество поддиапазонов")), &sub_diapason_count);
  int num_param_sub_diapason = 0;
  ini_file.add(irst("Тип поддиапазона"), &num_param_sub_diapason);
  if (type_sub_diapason == tsd_parameter1) {
    num_param_sub_diapason = 1;
  } else {
    num_param_sub_diapason = 2;
  }
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section(irst("Опции"));
  for (int i = 0; i < sub_diapason_count; i++) {
    String diapason_id_key = irst(" д") + IntToStr(i);
    String index_start_key = irst("Начальный индекс") + diapason_id_key;
    String size_key = irst("Размер") + diapason_id_key;
    String value_begin_key = irst("Начальное значение") + diapason_id_key;
    String value_end_key = irst("Конечное значение") + diapason_id_key;
    int index_start = eeprom_ranges[i].index_start;
    int size = eeprom_ranges[i].size;
    double value_begin = eeprom_ranges[i].value_begin;
    double value_end = eeprom_ranges[i].value_end;
    ini_file.add(index_start_key, &index_start);
    ini_file.add(size_key, &size);
    ini_file.add(value_begin_key, &value_begin);
    ini_file.add(value_end_key, &value_end);
    ini_file.save();
    ini_file.clear_control();
  }
  // сохранение доп.параметров
  ini_file.clear_control();
  ini_file.set_section(irst("Опции"));
  int param_ex_count = v_parameter_ex.size();
  ini_file.add(irst("Количество доп.параметров"), &param_ex_count);
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section(irst("Опции"));
  for (int i = 0; i < param_ex_count; i++) {
    String param_ex_id_key = irst(" доп.параметр") + IntToStr(i);
    String name_key = irst("Имя параметра") + param_ex_id_key;
    String unit_key = irst("Единицы измерения") + param_ex_id_key;
    String type_variable_key = irst("Тип параметра") + param_ex_id_key;
    String index_key = irst("Индекс байта") + param_ex_id_key;
    String value_working_key = irst("Рабочее значение") + param_ex_id_key;
    String value_default_key = irst("Значение по умолчанию") + param_ex_id_key;

    String name = v_parameter_ex[i].name.c_str();
    String unit = lang_type_to_str(v_parameter_ex[i].type).c_str();
    String type_variable = v_parameter_ex[i].unit.c_str();
    irs_i32 index = v_parameter_ex[i].index;
    //double value_working = v_parameter_ex[i].value_working;
    double value_default = v_parameter_ex[i].value_default;

    ini_file.add(name_key, &name);
    ini_file.add(unit_key, &unit);
    ini_file.add(type_variable_key, &type_variable);
    ini_file.add(index_key, &index);
    //ini_file.add(value_working_key, &value_working);
    ini_file.add(value_default_key, &value_default);
    ini_file.save();
    ini_file.clear_control();
  }
  // сохранение доп.битов
  ini_file.clear_control();
  ini_file.set_section(irst("Опции"));
  int bit_type2_count = bit_type2_array.size();
  ini_file.add(irst("Количество доп.битов"), &bit_type2_count);
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section(irst("Опции"));
  for (int i = 0; i < bit_type2_count; i++) {
    String bit_type2_id_key = irst(" доп.бит") + IntToStr(i);
    String bitname_key = irst("Имя бита") + bit_type2_id_key;
    String byte_index_key = irst("Индекс байта") + bit_type2_id_key;
    String bit_index_key = irst("Индекс бита") + bit_type2_id_key;
    String value_working_key = irst("Рабочее значение") + bit_type2_id_key;
    String value_def_key = irst("Значение по умолчанию") + bit_type2_id_key;
    String bitname = bit_type2_array[i].bitname.c_str();
    int index_byte = bit_type2_array[i].index_byte;
    int index_bit = bit_type2_array[i].index_bit;
    //bool value_working = bit_type2_array[i].value_working;
    bool value_def = bit_type2_array[i].value_def;
    ini_file.add(bitname_key, &bitname);
    ini_file.add(byte_index_key, &index_byte);
    ini_file.add(bit_index_key, &index_bit);
    //ini_file.add(value_working_key, &value_working);
    ini_file.add(value_def_key, &value_def);
    ini_file.save();
    ini_file.clear_control();
  }
  return fsuccess;
}


bool config_calibr_t::load( const string_type& a_filename )
{
  //return load_from_ini(a_filename);

  std::ifstream ifile;
  string_type filename = a_filename;
  //change_file_ext( string_type( "jsontest" ), &filename );
  ifile.open( IRS_SIMPLE_FROM_TYPE_STR( filename.c_str() ), ios::in );
  if (!ifile.good()) {
    throw runtime_error( "Не удалось загрузить файл" );
  }

  try {
    return load_from_json(&ifile);
  } catch (parse_json_error_t /*&ex*/) {
    return load_from_ini( a_filename );
  }
}


//
bool config_calibr_t::load_from_json(std::istream* ap_ostr)
{
  clear();

  Json::Reader reader;
  Json::Value root;
  const bool collect_comments = false;
  const bool parsed_success = reader.parse( *ap_ostr, root, collect_comments );
  if (!parsed_success) {
    std::cout << "Failed to parse JSON" <<
      std::endl << reader.getFormatedErrorMessages() <<
      std::endl;
    throw parse_json_error_t("Не удалось разобрать файл как json");
  }

  {
    Json::Value data = root["device"];
    jsonv_get_cbstr(data["name"], &device_name);
  }

  {
    Json::Value data = root["reference_device"];
    jsonv_get_num(data["enabled"], &reference_channel.enabled);
    jsonv_get_cbstr(data["name"], &reference_device_name);
  }

  // input_parameter1
  {
    Json::Value data = root["input_parameter1"];

    if (!str_to_lang_type(jsonv_safe_get_cbstr(data["type"], String()).c_str(),
      in_parameter1.type)) {
      return false;
    }

    jsonv_get_cbstr(data["name"],         &in_parameter1.name);
    jsonv_get_cbstr(data["unit"],         &in_parameter1.unit);
    jsonv_get_num(data["binding"],        &in_parameter1.anchor);
    jsonv_get_num(data["index"],          &in_parameter1.index);
    jsonv_get_num(data["coefficient"],    &in_parameter1.koef);
    jsonv_get_num(data["default_value"],  &in_parameter1.default_val);
  }

  // input_parameter2
  {
    Json::Value data = root["input_parameter2"];

    if (!str_to_lang_type(jsonv_safe_get_cbstr(data["type"], String()).c_str(),
      in_parameter2.type)) {
      return false;
    }

    jsonv_get_cbstr(data["name"],         &in_parameter2.name);
    jsonv_get_cbstr(data["unit"],         &in_parameter2.unit);
    jsonv_get_num(data["binding"],        &in_parameter2.anchor);
    jsonv_get_num(data["index"],          &in_parameter2.index);
    jsonv_get_num(data["coefficient"],    &in_parameter2.koef);
    jsonv_get_num(data["default_value"],  &in_parameter2.default_val);
  }

  // input_parameter3
  {
    Json::Value data = root["input_parameter3"];

    if (!str_to_lang_type(jsonv_safe_get_cbstr(data["type"], String()).c_str(),
      in_parameter3.type)) {
      return false;
    }

    jsonv_get_cbstr(data["name"],         &in_parameter3.name);
    jsonv_get_cbstr(data["unit"],         &in_parameter3.unit);
    jsonv_get_num(data["index"],          &in_parameter3.index);
    jsonv_get_num(data["coefficient"],    &in_parameter3.koef);
    jsonv_get_num(data["default_value"],  &in_parameter3.default_val);
  }

  // output_parameter
  {
    Json::Value data = root["output_parameter"];

    if (!str_to_lang_type(jsonv_safe_get_cbstr(data["type"], String()).c_str(),
      out_parameter.type)) {
      return false;
    }

    jsonv_get_cbstr(data["name"], &out_parameter.name);
    jsonv_get_cbstr(data["unit"], &out_parameter.unit);
    jsonv_get_num(data["index"], &out_parameter.index);
  }

  // EEPROM
  {
    Json::Value data = root["eeprom"];
    jsonv_get_num(data["pos_index"], &index_pos_eeprom);      // Индекс воронки
    //int subrange_amount = 0;
    int num_param_subrange = 1;
    //jsonv_get_num(data["range_amount"], &subrange_amount);
    jsonv_get_num(data["range_type"], &num_param_subrange);
    type_sub_diapason = num_param_subrange == 1 ? tsd_parameter1 : tsd_parameter2;

    //eeprom_ranges.clear();
    if (data["ranges"].isArray()) {
      Json::Value ranges = data["ranges"];
      for (size_t i = 0; i < ranges.size(); i++) {
        Json::Value range = ranges[i];

        eeprom_range_t range_calibr;
        jsonv_get_num(range["position"],  &range_calibr.index_start);
        jsonv_get_num(range["size"],      &range_calibr.size);
        jsonv_get_num(range["min"],       &range_calibr.value_begin);
        jsonv_get_num(range["max"],       &range_calibr.value_end);

        eeprom_ranges.push_back(range_calibr);
      }
    }
  }

  // доп.параметры
  {
    if (root["extra_parameters"].isArray())
    {
      Json::Value params = root["extra_parameters"];
      for (size_t i = 0; i < params.size(); i++) {
        Json::Value param = params[i];
        parameter_ex_t param_ex;

        if( !str_to_lang_type(jsonv_safe_get_cbstr(param["type"], String() ).c_str(),
          param_ex.type)) {
          return false;
        }

        jsonv_get_cbstr(param["name"],        &param_ex.name);
        jsonv_get_cbstr(param["unit"],        &param_ex.unit);
        jsonv_get_num(param["byte_index"],    &param_ex.index);
        //jsonv_get_num(param["work_value"],    &param_ex.value_working);
        jsonv_get_num(param["default_value"], &param_ex.value_default);

        v_parameter_ex.push_back(param_ex);
      }
    }
  }

  // сетевые переменные
  {
    Json::Value data = root["bytes"];
    jsonv_get_num(data["work_time"], &index_work_time);
  }

  // сетевые биты
  {
    Json::Value data = root["bits"];

    jsonv_get_bit(data["mismatch_state"],   &bit_pos_mismatch_state);
    jsonv_get_bit(data["correct_mode"],     &bit_pos_correct_mode);
    jsonv_get_bit(data["operating_duty"],   &bit_pos_operating_duty);
    jsonv_get_bit(data["error_bit"],        &bit_pos_error_bit);
    jsonv_get_bit(data["reset_over_bit"],   &bit_pos_reset_over_bit);
    jsonv_get_bit(data["phase_preset_bit"], &bit_pos_phase_preset_bit);
  }

  // доп.сетевые биты
  {
    if (root["extra_bits"].isArray()) {
      Json::Value bits = root["extra_bits"];

      for (size_t i = 0; i < bits.size(); i++) {
        Json::Value bit_data = bits[i];
        bit_type2_pos_t bit;

        jsonv_get_str(bit_data["name"],           &bit.bitname);
        jsonv_get_num(bit_data["byte_index"],     &bit.index_byte);
        jsonv_get_num(bit_data["bit_index"],      &bit.index_bit);
        //jsonv_get_num(bit_data["work_value"],     &bit.value_working);
        jsonv_get_num(bit_data["defalut_value"],  &bit.value_def);

        bit_type2_array.push_back(bit);
      }
    }
  }

  {
    Json::Value data = root["temperature_ctrl_common_cfg"];

    jsonv_get_num(data["enabled"],        &temperature_ctrl_common_cfg.enabled);
    jsonv_get_num(data["index"],          &temperature_ctrl_common_cfg.index);
  }

  cell_config_calibr_t default_config;
  default_config.load_from_json(root["default_cell_config"], false);

  Json::Value cells_data = root["cells_config"];
  size_t col_count = 0;
  size_t row_count = 0;
  jsonv_get_num(cells_data["col_count"], &col_count);
  jsonv_get_num(cells_data["row_count"], &row_count);

  if (col_count < min_col_count)
    return false;

  if (row_count < min_row_count)
    return false;

  cells_config.resize(col_count, row_count, default_config);
  for (size_type col_i = 0; col_i < cells_config.get_col_count(); col_i++ )
    cells_config.write_cell(col_i, 0, cell_config_calibr_t());
  for (size_type row_i = 1; row_i < cells_config.get_row_count(); row_i++ )
    cells_config.write_cell(0, row_i, cell_config_calibr_t());

  Json::Value cols_data = cells_data["cols"];
  if (cols_data.isArray()) {
    for (size_t col_i = 0; col_i < cols_data.size(); col_i++) {
      Json::Value col_data = cols_data[col_i];

      size_t col_idx = 0;
      jsonv_get_num(col_data["col_i"], &col_idx);

      if (!col_data["col"].empty()) {
        cell_config_calibr_t col_header;
        col_header.load_from_json(col_data["col"], true);
        cells_config.write_cell(col_idx, 0, col_header);
      }

      Json::Value cells = col_data["cells"];
      if (!cells.isArray()) {
        continue;
      }

      for (size_t row_i = 0; row_i < cells.size(); row_i++) {

        Json::Value cell_data = cells[row_i];
        size_t row_idx = 0;
        jsonv_get_num(cell_data["row_i"], &row_idx);

        if (col_idx == 0) {
          if (!cell_data["row"].empty()) {
            cell_config_calibr_t row_header;
            row_header.load_from_json(cell_data["row"], true);
            cells_config.write_cell(0, row_idx, row_header);
          }
        } else if (!cell_data["config"].empty()) {
          cell_config_calibr_t cell;
          cell.load_from_json(cell_data["config"], false);
          cells_config.write_cell(col_idx, row_idx, cell);
        }
      }
    }
  }

  jsonv_get_cbstr(root["last_active_file"], &active_filename);

  return true;
}


//
bool config_calibr_t::operator==(const config_calibr_t& a_config)
{
  return device_name == a_config.device_name &&
    reference_device_name == a_config.reference_device_name &&
    ip_adress == a_config.ip_adress &&
    port == a_config.port &&
    in_parameter1 == a_config.in_parameter1 &&
    in_parameter2 == a_config.in_parameter2 &&
    in_parameter3 == a_config.in_parameter3 &&
    out_parameter == a_config.out_parameter &&
    v_parameter_ex == a_config.v_parameter_ex &&

    bit_pos_mismatch_state == a_config.bit_pos_mismatch_state &&
    bit_pos_correct_mode == a_config.bit_pos_correct_mode &&
    bit_pos_operating_duty == a_config.bit_pos_operating_duty &&
    bit_pos_error_bit == a_config.bit_pos_error_bit &&
    bit_pos_reset_over_bit == a_config.bit_pos_reset_over_bit &&
    bit_pos_phase_preset_bit == a_config.bit_pos_phase_preset_bit &&
    bit_type2_array == a_config.bit_type2_array &&

    index_work_time == a_config.index_work_time &&
    index_pos_eeprom == a_config.index_pos_eeprom &&

    //out_param_measuring_conf == a_config.out_param_measuring_conf &&
    //out_param_control_config == a_config.out_param_control_config &&
    temperature_ctrl_common_cfg == a_config.temperature_ctrl_common_cfg &&

    type_sub_diapason == a_config.type_sub_diapason &&
    eeprom_ranges == a_config.eeprom_ranges &&

    active_filename == a_config.active_filename &&
    reference_channel == a_config.reference_channel &&
    cells_config == a_config.cells_config;
}


/*bool config_calibr_t::is_equal(const config_calibr_t& a_config)
{
  return type_meas == a_config.type_meas &&
    device_name == a_config.device_name &&
    reference_device_name == a_config.reference_device_name &&
    ip_adress == a_config.ip_adress &&
    port == a_config.port &&
    in_parameter1 == a_config.in_parameter1 &&
    in_parameter2 == a_config.in_parameter2 &&
    in_parameter3 == a_config.in_parameter3 &&
    out_parameter == a_config.out_parameter &&
    v_parameter_ex == a_config.v_parameter_ex &&
    bit_pos_mismatch_state == a_config.bit_pos_mismatch_state &&
    bit_pos_correct_mode == a_config.bit_pos_correct_mode &&
    bit_pos_operating_duty == a_config.bit_pos_operating_duty &&
    bit_pos_error_bit == a_config.bit_pos_error_bit &&
    bit_pos_reset_over_bit == a_config.bit_pos_reset_over_bit &&
    bit_pos_phase_preset_bit == a_config.bit_pos_phase_preset_bit &&
    bit_type2_array == a_config.bit_type2_array &&
    index_work_time == a_config.index_work_time &&
    index_pos_eeprom == a_config.index_pos_eeprom &&
    out_param_measuring_conf == a_config.out_param_measuring_conf &&
    out_param_control_config == a_config.out_param_control_config &&
    temperature_control == a_config.temperature_control &&
    type_sub_diapason == a_config.type_sub_diapason &&
    eeprom_ranges == a_config.eeprom_ranges &&
    delay_meas == a_config.delay_meas &&
    meas_interval == a_config.meas_interval &&
    count_reset_over_bit == a_config.count_reset_over_bit &&
    active_filename == a_config.active_filename &&
    reference_channel == a_config.reference_channel &&
    cells_config == a_config.cells_config;
}*/

/*static */ irs::table_t<cell_config_calibr_t> config_calibr_t::get_default_cells_config()
{
  irs::table_t<cell_config_calibr_t> cells_cfg;
  cells_cfg.set_col_count(default_col_count);
  cells_cfg.set_row_count(default_row_count);
  cells_cfg.write_cell(1, 1, cell_config_calibr_t());
  return cells_cfg;
}


/*static*/ void config_calibr_t::check_config(const config_calibr_t& a_config_calibr)
{
  check_cells_config(a_config_calibr.cells_config);

  IRS_ASSERT(a_config_calibr.cells_config.get_col_count() > 1 );
  IRS_ASSERT(a_config_calibr.cells_config.get_row_count() > 1 );

  const cell_config_calibr_t ref_cell_cfg = a_config_calibr.cells_config.read_cell(1, 1);
  IRS_ASSERT(ref_cell_cfg.ex_param_work_values.size() == a_config_calibr.v_parameter_ex.size());
  IRS_ASSERT(ref_cell_cfg.ex_bit_work_values.size() == a_config_calibr.bit_type2_array.size());
}


/*static*/ void config_calibr_t::check_cells_config(const irs::table_t<cell_config_calibr_t>& a_cells_config)
{
  IRS_ASSERT(a_cells_config.get_col_count() > 1 );
  IRS_ASSERT(a_cells_config.get_row_count() > 1 );

  const cell_config_calibr_t ref_cell_cfg = a_cells_config.read_cell(1, 1);

  // Проверяем, что количество доп.параметров и доп.битов одинаковое во всех ячейках
  for (size_type col = 1; col < a_cells_config.get_col_count(); col++) {
    for (size_type row = 1; row < a_cells_config.get_row_count(); row++) {
      cell_config_calibr_t cell_cfg = a_cells_config.read_cell(col, row);
      IRS_ASSERT(cell_cfg.ex_param_work_values.size() == ref_cell_cfg.ex_param_work_values.size());
      IRS_ASSERT(cell_cfg.ex_bit_work_values.size() == ref_cell_cfg.ex_bit_work_values.size());
    }
  }   
}

/*static*/ void config_calibr_t::save_load_test()
{
  config_calibr_t cfg;
  cfg.device_name = irst("Калибратор");
  cfg.reference_device_name = irst("Калибратор2");
  //cfg.ip_adress = irst("192.168.1.1");
  //cfg.port = 9999;

  cfg.in_parameter1 = parameter1_t("Частота", type_float, irst("Гц"), false, 1, 2.123, 3.1);
  cfg.in_parameter2 = parameter1_t("Ток", type_double, irst("А"), true, 2, 3.234, 0.3);
  cfg.in_parameter3 = parameter2_t("Фаза", type_long_double, irst("Гр"), 3, 1.123456789, 90.5 );
  cfg.out_parameter = parameter3_t("Ток", type_double, irst("А"), 4, 234.456);

  cfg.v_parameter_ex.push_back(
    parameter_ex_t(irst("Доп.парам1"), type_long_double, "", 5, 3.1));
  cfg.v_parameter_ex.push_back(
    parameter_ex_t(irst("Доп.парам2"), type_float, "", 5, 4.1213));

  cfg.bit_pos_mismatch_state = bit_type1_pos_t(1, 1);
  cfg.bit_pos_correct_mode = bit_type1_pos_t(3, 2);
  cfg.bit_pos_operating_duty = bit_type1_pos_t(5, 3);
  cfg.bit_pos_error_bit = bit_type1_pos_t(7, 4);
  cfg.bit_pos_reset_over_bit = bit_type1_pos_t(9, 5);
  cfg.bit_pos_phase_preset_bit = bit_type1_pos_t(11, 6);

  cfg.bit_type2_array.push_back(bit_type2_pos_t(irst("Доп.1"),1, 3, false));
  cfg.bit_type2_array.push_back(bit_type2_pos_t(irst("Доп.2"), 3, 4, true));

  cfg.index_work_time = 10;
  cfg.index_pos_eeprom = 15;

  temperature_control_common_cfg_t tccc_control;
  tccc_control.enabled = true;
  tccc_control.index = 123;
  cfg.temperature_ctrl_common_cfg = tccc_control;

  cfg.eeprom_ranges.push_back(eeprom_range_t(1, 100, 10.123, 20.123));
  cfg.eeprom_ranges.push_back(eeprom_range_t(2, 20, 11.123, 21.123));

  cfg.type_sub_diapason = tsd_parameter1;
  cfg.active_filename = irst("C:\\temp\\1.cpc");

  cfg.cells_config.resize(3, 3, cell_config_calibr_t());
  cell_config_calibr_t col_1_header;
  col_1_header.value = 1.0123;
  col_1_header.is_value_initialized = true;
  cfg.cells_config.write_cell(1, 0, col_1_header);

  cell_config_calibr_t col_2_header;
  col_2_header.value = 2.1123567;
  col_2_header.is_value_initialized = true;
  cfg.cells_config.write_cell(1, 0, col_2_header);

  cell_config_calibr_t row_1_header;
  row_1_header.value = 3.133567;
  row_1_header.is_value_initialized = true;
  cfg.cells_config.write_cell(0, 1, row_1_header);

  /*cell_config_calibr_t row_2_header;
  row_2_header.value = 4.123567;
  row_2_header.is_value_initialized = true;
  cfg.cells_config.write_cell(0, 2, row_2_header);*/

  cell_config_calibr_t cell_11;
  /*cell_11.input_param1_coef = 1.123;
  cell_11.input_param2_coef = 2.3234;
  cell_11.input_param3_coef = 3.3234; */
  cell_11.output_param_coef = 4.3234;
  cell_11.ex_param_work_values.push_back(1.123456789123456789);
  cell_11.ex_param_work_values.push_back(100.265259);
  cell_11.ex_bit_work_values.push_back(true);
  cell_11.ex_bit_work_values.push_back(false);
  cell_11.type_meas = irs::str_conv<String>(type_meas_to_str(tm_volt_ac)),
  cell_11.range_enabled = true;
  cell_11.range = 3.1;
  cell_11.delay_meas = 123;
  cell_11.meas_interval = 1.23345678999;
  cell_11.count_reset_over_bit = 23;
  out_param_measuring_conf_t meas_conf;
  meas_conf.consider_out_param = true;
  meas_conf.filter_enabled = true;
  meas_conf.filter_sampling_time = false;
  meas_conf.filter_point_count = true;
  cell_11.out_param_measuring_conf = meas_conf;
  temperature_control_config_t t_control;
  t_control.enabled = true;
  t_control.reference = 90.1;
  t_control.difference = 0.2;
  cell_11.temperature_control = t_control;

  out_param_control_conf_t control_conf;
  control_conf.enabled = true;
  control_conf.max_relative_difference = 0.12345678912345678;
  control_conf.time = 100.5;
  cell_11.out_param_control_config = control_conf;

  cfg.cells_config.write_cell(1, 1, cell_11);

  cell_config_calibr_t cell_12 = cell_11;
  cfg.cells_config.write_cell(1, 2, cell_12);

  cell_config_calibr_t cell_21 = cell_11;
  cfg.cells_config.write_cell(2, 1, cell_21);

  cell_config_calibr_t cell_22;
  /*cell_22.input_param1_coef = 10.123;
  cell_22.input_param2_coef = 20.3234;
  cell_22.input_param3_coef = 30.3234;*/
  cell_22.output_param_coef = 40.3234;
  cell_22.ex_param_work_values.push_back(154.24456);
  cell_22.ex_param_work_values.push_back(34.2359);
  cell_22.ex_bit_work_values.push_back(true);
  cell_22.ex_bit_work_values.push_back(true);
  temperature_control_config_t t_control22;
  t_control22.enabled = false;
  t_control22.reference = 40.1;
  t_control22.difference = 0.1;
  cell_22.temperature_control = t_control22;
  cfg.cells_config.write_cell(2, 2, cell_22);

  std::stringstream str;

  //cfg.save("testcfgjson.json");
  cfg.save_to_json(&str);
  config_calibr_t readed_cfg;
  //readed_cfg.load("testcfgjson.json");
  readed_cfg.load_from_json(&str);

  int t = 0;
  for(size_type col_i = 0; col_i < cfg.cells_config.get_col_count(); col_i++)
  {
    for(size_type row_i = 0; row_i < cfg.cells_config.get_row_count(); row_i++)
    {
      cell_config_calibr_t cell = cfg.cells_config.read_cell(col_i, row_i);
      cell_config_calibr_t readed_cell =
        readed_cfg.cells_config.read_cell(col_i, row_i);
      if(cell != readed_cell)
        t = 1;
    }
  }

  IRS_LIB_ASSERT(cfg == readed_cfg);
}

bool config_calibr_t::load_from_ini(const string_type& a_filename)
{
  bool fsuccess = true;

  cell_config_calibr_t cell_config_calibr;

  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_filename.c_str());
  ini_file.clear_control();
  add_static_param(&ini_file, &cell_config_calibr);
  ini_file.load();
  ini_file.clear_control();

  ini_file.set_section(irst("Конфигурация устройства"));
  ini_file.add(irst("Имя"), &device_name);

  ini_file.set_section(irst("Конфигурация опорного устройства"));
  ini_file.add(irst("Имя"), &reference_device_name);

  string_type in_parametr1_unit_str;
  string_type in_parametr2_unit_str;
  string_type in_parametr3_unit_str;
  string_type out_parametr_unit_str;
  ini_file.set_section(irst("Входной параметр 1"));
  ini_file.add(irst("Тип параметра"), &in_parametr1_unit_str);
  ini_file.set_section("Входной параметр 2");
  ini_file.add(irst("Тип параметра"), &in_parametr2_unit_str);
  ini_file.set_section("Входной параметр 3");
  ini_file.add(irst("Тип параметра"), &in_parametr3_unit_str);
  ini_file.set_section("Выходной параметр");
  ini_file.add(irst("Тип параметра"), &out_parametr_unit_str);
  ini_file.load();
  ini_file.clear_control();
  if (fsuccess) {
    fsuccess =
      str_to_lang_type(in_parametr1_unit_str.c_str(), in_parameter1.type);
  }
  if (fsuccess) {
    str_to_lang_type(in_parametr2_unit_str.c_str(), in_parameter2.type);
  }
  if (fsuccess) {
    str_to_lang_type(in_parametr3_unit_str.c_str(), in_parameter3.type);
  }
  if (fsuccess) {
    str_to_lang_type(out_parametr_unit_str.c_str(), out_parameter.type);
  }
  if (fsuccess) {
    ini_file.set_section(irst("Опции"));
    int sub_diapason_count = 0;
    ini_file.add(irst("Количество поддиапазонов"),
      &sub_diapason_count);
    int num_param_sub_diapason = 0;
    ini_file.add(irst("Тип поддиапазона"), &num_param_sub_diapason);
    ini_file.load();
    ini_file.clear_control();
    eeprom_ranges.clear();
    if (num_param_sub_diapason == 1) {
      type_sub_diapason = tsd_parameter1;
    } else {
      type_sub_diapason = tsd_parameter2;
    }
    ini_file.set_section(irst("Опции"));
    for (int i = 0; i < sub_diapason_count; i++) {
      eeprom_range_t sub_diapason_calibr;
      String diapason_id_key = irst(" д") + IntToStr(i);
      String index_start_key = irst("Начальный индекс") + diapason_id_key;
      String size_key = irst("Размер") + diapason_id_key;
      String value_begin_key = irst("Начальное значение") + diapason_id_key;
      String value_end_key = irst("Конечное значение") + diapason_id_key;
      ini_file.add(index_start_key, &sub_diapason_calibr.index_start);
      ini_file.add(size_key, &sub_diapason_calibr.size);
      ini_file.add(value_begin_key, &sub_diapason_calibr.value_begin);
      ini_file.add(value_end_key, &sub_diapason_calibr.value_end);
      ini_file.load();
      ini_file.clear_control();
      eeprom_ranges.push_back(sub_diapason_calibr);
    }
    // загрузка доп.параметров
    ini_file.clear_control();
    ini_file.set_section(irst("Опции"));
    int param_ex_count = 0;
    ini_file.add(irst("Количество доп.параметров"), &param_ex_count);
    ini_file.load();
    ini_file.clear_control();
    v_parameter_ex.clear();
    ini_file.set_section(irst("Опции"));
    for (int i = 0; i < param_ex_count; i++) {
      parameter_ex_t parametr_ex;
      double ex_param_work_value = 0;
      String param_ex_id_key = irst(" доп.параметр") + IntToStr(i);
      String name_key = irst("Имя параметра") + param_ex_id_key;
      String unit_key = irst("Единицы измерения") + param_ex_id_key;
      String type_variable_key = irst("Тип параметра") + param_ex_id_key;
      String index_key = irst("Индекс байта") + param_ex_id_key;
      String value_working_key = irst("Рабочее значение") + param_ex_id_key;
      String value_default_key = irst("Значение по умолчанию") + param_ex_id_key;

      String unit_str;

      ini_file.add(name_key, &parametr_ex.name);
      ini_file.add(unit_key, &unit_str);
      ini_file.add(type_variable_key, &parametr_ex.unit);
      ini_file.add(index_key, &parametr_ex.index);
      ini_file.add(value_working_key, &ex_param_work_value);
      ini_file.add(value_default_key, &parametr_ex.value_default);
      ini_file.load();
      ini_file.clear_control();
      fsuccess = str_to_lang_type(unit_str.c_str(), parametr_ex.type);
      if (!fsuccess) {
        break;
      }
      v_parameter_ex.push_back(parametr_ex);      
      cell_config_calibr.ex_param_work_values.push_back(ex_param_work_value);
    }
  }
  if (fsuccess) {
    // загрузка доп.битов
    ini_file.clear_control();
    ini_file.set_section(irst("Опции"));
    int bit_type2_count = 0;
    ini_file.add(irst("Количество доп.битов"), &bit_type2_count);
    ini_file.load();
    ini_file.clear_control();
    bit_type2_array.clear();
    ini_file.set_section(irst("Опции"));
    for (int i = 0; i < bit_type2_count; i++) {
      bit_type2_pos_t bit_type2_pos;
      bool bit_type2_pos_work_value = false;
      String bit_type2_id_key = irst(" доп.бит") + IntToStr(i);
      String bitname_key = irst("Имя бита") + bit_type2_id_key;
      String byte_index_key = irst("Индекс байта") + bit_type2_id_key;
      String bit_index_key = irst("Индекс бита") + bit_type2_id_key;
      String value_working_key = irst("Рабочее значение") + bit_type2_id_key;
      String value_def_key = irst("Значение по умолчанию") + bit_type2_id_key;
      String bitname;
      ini_file.add(bitname_key, &bitname);
      ini_file.add(byte_index_key, &bit_type2_pos.index_byte);
      ini_file.add(bit_index_key, &bit_type2_pos.index_bit);
      ini_file.add(value_working_key, &bit_type2_pos_work_value);
      ini_file.add(value_def_key, &bit_type2_pos.value_def);
      ini_file.load();
      ini_file.clear_control();
      bit_type2_pos.bitname = bitname.c_str();
      bit_type2_array.push_back(bit_type2_pos);
      cell_config_calibr.ex_bit_work_values.push_back(bit_type2_pos_work_value);
    }
  }

  if (fsuccess) {
    cells_config.set_col_count(default_col_count);
    cells_config.set_row_count(default_row_count);
    cells_config.write_cell(1, 1, cell_config_calibr);
  }

  if (!fsuccess) {
    // освобождение ресурсов
    ini_file.clear_control();
    clear();
  }
  return fsuccess;
}
void config_calibr_t::add_static_param(irs::ini_file_t* ap_ini_file,
  cell_config_calibr_t* ap_cell_config_calibr)
{
  ap_ini_file->set_section(irst("Свойства сетевого подключения"));
  ap_ini_file->add(irst("IP-адрес"), &ip_adress);
  ap_ini_file->add(irst("Порт"),&port);

  ap_ini_file->set_section(irst("Входной параметр 1"));
  ap_ini_file->add(irst("Имя параметра"), &in_parameter1.name);
  ap_ini_file->add(irst("Единицы измерения"), &in_parameter1.unit);
  //ap_ini_file->add("Тип параметра", &in_parameter1.unit);
  ap_ini_file->add(irst("Привязка"), &in_parameter1.anchor);
  ap_ini_file->add(irst("Индекс"), &in_parameter1.index);
  ap_ini_file->add(irst("Коэффициент"), &in_parameter1.koef);
  ap_ini_file->add(irst("Значение по умолчанию"), &in_parameter1.default_val);

  ap_ini_file->set_section(irst("Входной параметр 2"));
  ap_ini_file->add(irst("Имя параметра"), &in_parameter2.name);
  ap_ini_file->add(irst("Единицы измерения"), &in_parameter2.unit);
  //ap_ini_file->add("Тип параметра", &in_parameter2.unit);
  ap_ini_file->add(irst("Привязка"), &in_parameter2.anchor);
  ap_ini_file->add(irst("Индекс"), &in_parameter2.index);
  ap_ini_file->add(irst("Коэффициент"), &in_parameter2.koef);
  ap_ini_file->add(irst("Значение по умолчанию"), &in_parameter2.default_val);

  ap_ini_file->set_section(irst("Входной параметр 3"));
  ap_ini_file->add(irst("Имя параметра"), &in_parameter3.name);
  ap_ini_file->add(irst("Единицы измерения"), &in_parameter3.unit);
  //ap_ini_file->add("Тип параметра", &in_parameter3.unit);
  ap_ini_file->add(irst("Индекс"), &in_parameter3.index);
  ap_ini_file->add(irst("Коффициент"), &in_parameter3.koef);
  ap_ini_file->add(irst("Значение по умолчанию"), &in_parameter3.default_val);

  ap_ini_file->set_section(irst("Выходной параметр"));
  ap_ini_file->add(irst("Имя параметра"), &out_parameter.name);
  ap_ini_file->add(irst("Единицы измерения"), &out_parameter.unit);
  //ap_ini_file->add("Тип параметра", &out_parameter.unit);
  ap_ini_file->add(irst("Индекс"), &out_parameter.index);
  ap_ini_file->add(irst("Коэффициент шунта"),
    &ap_cell_config_calibr->output_param_coef);

  ap_ini_file->set_section(irst("Опции"));
  ap_ini_file->add(irst("Вид измерения"), &ap_cell_config_calibr->type_meas);
  ap_ini_file->add(irst("Задержка измерения"), &ap_cell_config_calibr->delay_meas);
  ap_ini_file->add(irst("Время измерений"), &ap_cell_config_calibr->meas_interval);
  ap_ini_file->add(irst("Количество допустимых сбросов ошибок"),
    &ap_cell_config_calibr->count_reset_over_bit);
  /*ap_ini_file->add("Режим расстройки",
    &mismatch_mode);*/
  ap_ini_file->add(irst("Индекс счетчика"), &index_work_time);
  //ap_ini_file->add("Индекс коррекции в воронке", &index_pos_offset_eeprom);
  ap_ini_file->add(irst("Индекс воронки"), &index_pos_eeprom);
  //ap_ini_file->add("Максимальный размер коррекции", &max_size_correct);

  ap_ini_file->add(irst("Режим расстройки. Индекс байта"),
    &bit_pos_mismatch_state.index_byte);
  ap_ini_file->add(irst("Режим расстройки. Индекс бита"),
    &bit_pos_mismatch_state.index_bit);
  ap_ini_file->add(irst("Режим коррекции. Индекс байта"),
    &bit_pos_correct_mode.index_byte);
  ap_ini_file->add(irst("Режим коррекции. Индекс бита"),
    &bit_pos_correct_mode.index_bit);
  ap_ini_file->add(irst("Готовность регулятора. Индекс байта"),
    &bit_pos_operating_duty.index_byte);
  ap_ini_file->add(irst("Готовность регулятора. Индекс бита"),
    &bit_pos_operating_duty.index_bit);
  ap_ini_file->add(irst("Бит наличия ошибки. Индекс байта"),
    &bit_pos_error_bit.index_byte);
  ap_ini_file->add(irst("Бит наличия ошибки. Индекс бита"),
    &bit_pos_error_bit.index_bit);
  ap_ini_file->add(irst("Бит сброса ошибки. Индекс байта"),
    &bit_pos_reset_over_bit.index_byte);
  ap_ini_file->add(irst("Бит сброса ошибки. Индекс бита"),
    &bit_pos_reset_over_bit.index_bit);
  ap_ini_file->add(irst("Бит предустановки фазы. Индекс байта"),
    &bit_pos_phase_preset_bit.index_byte);
  ap_ini_file->add(irst("Бит предустановки фазы. Индекс бита"),
    &bit_pos_phase_preset_bit.index_bit);

  ap_ini_file->add(irst("Последний активный файл"), &active_filename);

  ap_ini_file->set_section(irst("Опции опорного канала"));
  ap_ini_file->add(irst("Статус включения"), &reference_channel.enabled);
  ap_ini_file->add(irst("IP-адрес"), &reference_channel.ip_adress);
  ap_ini_file->add(irst("Порт"), &reference_channel.port);

  /*ap_ini_file->set_section(irst("Опции выходного параметра для измерения"));
  ap_ini_file->add(irst("Учитывать выходной параметр при измерении"),
    &out_param_measuring_conf.consider_out_param);
  ap_ini_file->add(irst("Включить фильтрацию выходного параметра"),
    &out_param_measuring_conf.filter_enabled);
  ap_ini_file->add(irst("Время дискретизации"),
    &out_param_measuring_conf.filter_sampling_time);
  ap_ini_file->add(irst("Количество точек"),
    &out_param_measuring_conf.filter_point_count);

  ap_ini_file->set_section(irst("Контроль выходного параметра"));
  ap_ini_file->add(irst("Включение"),
    &out_param_control_config.enabled);
  ap_ini_file->add(irst("Допустимое относительное отклонение"),
    &out_param_control_config.max_relative_difference);
  ap_ini_file->add(irst("Временное окно"), &out_param_control_config.time);*/

  ap_ini_file->set_section(irst("Контроль температуры"));
  ap_ini_file->add(irst("Включение"),
    &temperature_ctrl_common_cfg.enabled);
  ap_ini_file->add(irst("Индекс"), &temperature_ctrl_common_cfg.index);
  /*ap_ini_file->add(irst("Уставка"), &temperature_control.reference);
  ap_ini_file->add(irst("Допустимое отклонение"),
    &temperature_control.difference);*/
}

//-------------------------------------------------------------------------
bool correct_map_t::connect(
  irs::mxdata_t *ap_data,
  irs_uarc a_start_index,
  config_calibr_t& a_config_calibr,
  const irs_uarc a_number_of_koef_per_point
  )
{
  bool fsuccess = true;
  irs_uarc index = a_start_index;
  index = map_id.connect(ap_data, index);
  index = x_count.connect(ap_data, index);
  index = y_count.connect(ap_data, index);

  index = x_points.connect(
    a_config_calibr.in_parameter1.type,
    ap_data,
    index,
    x_count);
  index = y_points.connect(
    a_config_calibr.in_parameter2.type,
    ap_data,
    index,
    y_count);
  irs_uarc koef_array_size = x_count * y_count * a_number_of_koef_per_point;

  koef_array.connect(
    a_config_calibr.out_parameter.type,
    ap_data,
    index,
    koef_array_size);

  return fsuccess;
}

// class param_filter_t
param_filter_t::param_filter_t(double a_sampling_time,
  size_type a_num_of_points
):
  m_sample_timer(new irs::loop_timer_t(irs::make_cnt_s(a_sampling_time))),
  m_sko_calc(a_num_of_points),
  m_started(false),
  m_last_value(0)
{
}

void param_filter_t::set_sampling_time(double a_sampling_time)
{
  m_sample_timer.reset(new irs::loop_timer_t(irs::make_cnt_s(a_sampling_time)));
}

void param_filter_t::resize(size_type a_point_count)
{
  m_sko_calc.resize(a_point_count);
}

void param_filter_t::add(double a_value)
{
  m_last_value = a_value;
}

double param_filter_t::get_value() const
{
  return m_sko_calc.average();
}

void param_filter_t::restart()
{
  m_started = true;
  m_sko_calc.clear();
}

void param_filter_t::stop()
{
  m_started = false;
}

bool param_filter_t::started() const
{
  return m_started;
}

void param_filter_t::tick()
{
  if (m_sample_timer->check()) {
    if (m_started) {
      m_sko_calc.add(m_last_value);
    }
  }
}

#ifdef NOP
irs::string_t absolute_file_name_to_relative(
  const irs::string_t& a_path,
  const irs::string_t& a_base)
{
  namespace fs = boost::filesystem;

  std::wstring full_file_name_str =
    irs::str_conv<irs::string_t>(a_path);
  std::wstring base_str = irs::str_conv<irs::string_t>(a_base);

  fs::wpath base(base_str);
  fs::wpath file_name(full_file_name_str);

  if (!base.has_root_path()) {
    return a_path;
  }

  // Здесь стоит проверить наличие слеша после буквы диска и добавить его, если
  // он отсутвует

  if (!file_name.has_root_path()) {
    return a_path;
  }

  if (base.root_path() != file_name.root_path()) {
    return a_path;
  }

  const std::wstring _dot  = std::wstring(1, fs::dot<fs::wpath>::value);
  const std::wstring _dots = std::wstring(2, fs::dot<fs::wpath>::value);
  const std::wstring _sep = std::wstring(1, fs::slash<fs::wpath>::value);
  const std::wstring _dots_sep = _dots + _sep;

  fs::wpath::iterator base_it = base.begin();
  fs::wpath::iterator file_name_it = file_name.begin();
  while ((base_it != base.end()) && (file_name_it != file_name.end())) {
    std::wstring elem = *base_it;
    if (*base_it != *file_name_it) {
      break;
    }
    ++base_it;
    ++file_name_it;
  }

  fs::wpath relative_path;
  for (; base_it != base.end(); ++base_it) {

    if (*base_it == _dot) {
      continue;
    } else if (*base_it == _sep) {
      continue;
    }

    relative_path /= _dots_sep;
  }

  /*fs::wpath::iterator path_it_start = file_name_it;
  for (; file_name_it != file_name.end(); ++file_name_it) {
    if (file_name_it != path_it_start)
      relative_path /= irst("/");
    if (*file_name_it == _dot)
      continue;
    if (*file_name_it == _sep)
      continue;
    relative_path /= *file_name_it;
  }*/


  for (; file_name_it != file_name.end(); ++file_name_it) {
    relative_path /= *file_name_it;
  }

  std::wstring relative_str = relative_path.native_file_string();
  return irs::str_conv<irs::string_t>(relative_str);
}
#endif

// struct file_name_service_t
file_name_service_t::file_name_service_t():
  m_path_prog(ExtractFilePath(Application->ExeName)),
  m_default_ext(irst("cpc")),
  m_multimeter_config_ext(irst("ini")),
  m_default_filename(irst("config1.cpc")),
  m_foldername_conf(irst("configuration")),
  m_multimeter_foldername_conf(irst("multimeters")),
  m_device_foldername_conf(irst("devices")),
  m_device_default_ext(irst("ini")),
  m_device_grid_options_default_ext(
    irs::str_conv<String>(irs::tstlan::get_grid_options_file_ext())),
  m_device_suffix(irst("_device")),
  m_ref_device_default_ext(irst("ini")),
  m_ref_device_suffix(irst("_reference_device")),
  m_device_options_section(irst("device"))
{
}

String file_name_service_t::get_config_ext() const
{
  return m_default_ext;
}

String file_name_service_t::get_config_dir() const
{
  return m_path_prog + m_foldername_conf;
}

String file_name_service_t::get_multimeter_config_ext() const
{
  return m_multimeter_config_ext;
}

String file_name_service_t::get_multimeter_config_dir() const
{
  return m_path_prog + m_multimeter_foldername_conf;
}

String file_name_service_t::get_device_config_dir() const
{
  return m_path_prog + m_device_foldername_conf;
}

String file_name_service_t::get_device_config_ext() const
{
  return m_device_default_ext;
}

String file_name_service_t::make_config_full_file_name(
  String a_config_name) const
{
  return m_path_prog + m_foldername_conf +
    irst("\\") + a_config_name + irst(".") + m_default_ext;
}

String file_name_service_t::make_device_config_full_file_name(
  String a_config_name) const
{
  return m_path_prog + m_device_foldername_conf +
    irst("\\") + a_config_name + irst(".") + m_device_default_ext;
}

String file_name_service_t::make_ref_device_config_full_file_name(
  String a_config_name) const
{
  return m_path_prog + m_device_foldername_conf +
    irst("\\") + a_config_name + irst(".") + m_ref_device_default_ext;
}

String file_name_service_t::make_device_grid_config_full_name(
  String a_config_name) const
{
  return m_path_prog + m_foldername_conf +
    irst("\\") + a_config_name + m_device_suffix  + irst(".") +
    m_device_grid_options_default_ext;
}

String file_name_service_t::make_ref_device_grid_config_full_name(
  String a_config_name) const
{
  return m_path_prog + m_foldername_conf +
    irst("\\") + a_config_name + m_ref_device_suffix  + irst(".") +
    m_device_grid_options_default_ext;
}


String file_name_service_t::get_device_options_section() const
{
  return m_device_options_section;
}

String file_name_service_t::get_config_name(
  const String& a_full_file_name) const
{
  return extract_short_filename(ExtractFileName(a_full_file_name));
}



String file_name_service_t::make_multimeter_config_full_file_name(
  String a_config_name)  const
{
  return m_path_prog + m_multimeter_foldername_conf +
    irst("\\") + a_config_name + irst(".") + m_multimeter_config_ext;
}

void file_name_service_t::create_config_dir()
{
  String dir = get_config_dir();
  if (!DirectoryExists(dir)) {
    if (!ForceDirectories(dir)) {
      throw Exception(irst("Не удалось создать директорию ") + dir);
    }
  }
}

// Возвращает относительный путь, если возможно, в противном случае
// возвращает исходный путь
String file_name_service_t::make_relative_file_name(
  const String& a_full_file_name) const
{
  irs::string_t absolute = irs::str_conv<irs::string_t>(a_full_file_name);
  irs::string_t base = irs::str_conv<irs::string_t>(m_path_prog);
  irs::string_t relative = irs::absolute_path_to_relative(absolute, base);

  return irs::str_conv<String>(relative);
}

/*bool file_name_service_t::path_is_relative(const String& a_path)
{
  const irs::string_t path = irs::str_conv<irs::string_t>(a_path);
  if (path.size() > 0) {
    if (path[0] == irst('\\')) {
      return false;
    }
  }
  if (path.size() > 1) {
    if (irs::isalphat(path[0]) && (path[1] == irst(':'))) {
      return false;
    }
  }
  return true;
}*/

String file_name_service_t::make_absolute_path(
  const String& a_relative_path)
{
  const irs::string_t base = irs::str_conv<irs::string_t>(m_path_prog);
  const irs::string_t relative_path =
    irs::str_conv<irs::string_t>(a_relative_path);

  irs::string_t result;
  result = irs::relative_path_to_absolute(relative_path, base);
  return irs::str_conv<String>(result);
}

/*String file_name_service_t::make_absolute_path_if_relative(
  const String& a_relative_path)
{
  //const irs::string_t dir = irs::str_conv<irs::string_t>(m_path_prog);
  String result;
  if (path_is_relative(a_relative_path)) {
    result = make_absolute_path(a_relative_path);
  } else {
    result = a_relative_path;
  }
  return result;
}*/

String file_name_service_t::ensure_dir_end(const String& a_dir)
{
  String dir;
  if (!a_dir.IsEmpty()) {
    if (is_path_name_separator(a_dir[a_dir.Length() - 1])) {
      dir = a_dir;
    } else {
      dir = a_dir + path_name_separator();
    }
  } else {
    IRS_LIB_ERROR(irs::ec_standard, "Для пустого имени операция не определена");
  }
  return dir;
}

file_name_service_t::char_type
file_name_service_t::path_name_separator()
{
  return irst('\\');
}

bool file_name_service_t::is_path_name_separator(const char_type a_ch)
{
  return (a_ch == irst('\\')) || (a_ch == irst('/'));
}

// class vars_ini_file_t
vars_ini_file_t::vars_ini_file_t(const string_type& a_file_name):
  m_section_prefix(),
  m_section_name(irst("vars")),
  m_section_full_name(m_section_prefix + m_section_name),
  m_name_row_count(irst("_row_count")),
  m_type_column_prefix(irst("Type_")),
  mp_encoding(TEncoding::Default),
  mp_ini_file(new TMemIniFile(a_file_name.c_str(), mp_encoding))
{
}

vars_ini_file_t::size_type vars_ini_file_t::load_row_count()
{
  return mp_ini_file->ReadInteger(m_section_full_name.c_str(),
    m_name_row_count.c_str(),
    0);
}

irs::tstlan::type_t vars_ini_file_t::load_type(
  size_type a_row_index)
{
  string_type name = m_type_column_prefix + string_type(a_row_index);
  String type_bstr =
    mp_ini_file->ReadString(
      m_section_full_name.c_str(), name.c_str(), irst(""));
  irs::tstlan::type_t type;
  if (!str_to_type(irs::str_conv<string_type>(type_bstr), &type)) {
    type = irs::tstlan::type_i32;
  }
  return type;
}

// class netconn_t
netconn_t::netconn_t():
  items(),
  mp_data(IRS_NULL)
{
}

void netconn_t::add_conn(vector<irs::bit_data_t>& a_vec, int a_var_index,
  int& a_conn_index, int& a_bit_index)
{
  if ((size_t)a_conn_index < mp_data->size()) {
    items[a_var_index].type = irs::tstlan::type_bit;
    items[a_var_index].index = a_vec.size();
    items[a_var_index].conn_index = a_conn_index;
    items[a_var_index].bit_index = a_bit_index;
    a_vec.push_back(irs::bit_data_t());
    a_conn_index = a_vec.back().connect(mp_data, a_conn_index,
      a_bit_index);
    a_bit_index++;
    if (a_bit_index >= bit_in_byte) {
      a_bit_index = 0;
      a_conn_index++;
    }

  } else {
    items[a_var_index].type = irs::tstlan::type_unknown;
    items[a_var_index].index = 0;
    items[a_var_index].conn_index = 0;
    items[a_var_index].bit_index = 0;
  }
}

int netconn_t::connect(irs::mxdata_t* ap_data, const string_type& a_file_name)
{
  vars_ini_file_t vars_ini_file(a_file_name);

  const size_type row_count = vars_ini_file.load_row_count();

  mp_data = ap_data;

  bit_vec.clear();
  bool_vec.clear();
  i8_vec.clear();
  u8_vec.clear();
  i16_vec.clear();
  u16_vec.clear();
  i32_vec.clear();
  u32_vec.clear();
  i64_vec.clear();
  u64_vec.clear();
  float_vec.clear();
  double_vec.clear();
  long_double_vec.clear();

  items.clear();
  items.resize(row_count);

  int conn_index = 0;
  int bit_index = 0;
  for (int row = 0; row < static_cast<int>(row_count); row++) {
    const type_type type = vars_ini_file.load_type(row);

    const int var_index = row;
    int conn_index_grid = conn_index;
    int bit_index_grid = bit_index;
    bool is_cur_item_bit = false;

    switch (type) {
      case irs::tstlan::type_bit: {
        add_conn(bit_vec, var_index, conn_index, bit_index);
        is_cur_item_bit = true;
      } break;
      case irs::tstlan::type_bool: {
        add_conn(bool_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_bool);
      } break;
      case irs::tstlan::type_i8: {
        add_conn(i8_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_i8);
      } break;
      case irs::tstlan::type_u8: {
        add_conn(u8_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_u8);
      } break;
      case irs::tstlan::type_i16: {
        add_conn(i16_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_i16);
      } break;
      case irs::tstlan::type_u16: {
        add_conn(u16_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_u16);
      } break;
      case irs::tstlan::type_i32: {
        add_conn(i32_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_i32);
      } break;
      case irs::tstlan::type_u32: {
        add_conn(u32_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_u32);
      } break;
      case irs::tstlan::type_i64: {
        add_conn(i64_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_i64);
      } break;
      case irs::tstlan::type_u64: {
        add_conn(u64_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_u64);
      } break;
      case irs::tstlan::type_float: {
        add_conn(float_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_float);
      } break;
      case irs::tstlan::type_double: {
        add_conn(double_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_double);
      } break;
      case irs::tstlan::type_long_double: {
        add_conn(long_double_vec, var_index, conn_index, bit_index,
          irs::tstlan::type_long_double);
      } break;
    }

    if (!is_cur_item_bit) {
      if (bit_index_grid != 0) {
        bit_index_grid = 0;
        conn_index_grid++;
      }
    }
  }
  return conn_index;
}

// class device2_t
device2_t::device2_t(irs::chart_window_t* ap_chart,
  file_name_service_t* ap_file_name_service
):
  mp_chart(ap_chart),
  mp_file_name_service(ap_file_name_service),
  m_config_calibr(),
  m_type(),
  mp_tstlan4lib(),
  mp_mxdata_assembly(),
  mp_connection_log(),
  m_data_map()
{
}

device2_t::~device2_t()
{
  /*m_tstlan4lib.reset();
  m_mxdata_assembly.reset();
  m_connection_log.reset();*/
}

/*void device2_t::set_configuration(config_calibr_t a_config_calibr)
{
  m_config_calibr = a_config_calibr;
} */

void device2_t::enable(config_calibr_t a_config_calibr)
{
  if (!created()) {
    return;
  }
  if (mp_mxdata_assembly->enabled()) {
    return;
  }
  m_config_calibr = a_config_calibr;
  mp_mxdata_assembly->enabled(true);
  m_data_map.reset_connection();
}

void device2_t::disable()
{
  if (!created()) {
    return;
  }
  if (!mp_mxdata_assembly->enabled()) {
    return;
  }
  mp_mxdata_assembly->enabled(false);
  m_data_map.reset_connection();
}

String device2_t::get_name()
{
  String name;
  if (!mp_tstlan4lib.is_empty()) {
    name = mp_file_name_service->get_config_name(
      irs::str_conv<String>(mp_tstlan4lib->ini_name()));
  }
  return name;
}

String device2_t::get_type() const
{
  return irs::str_conv<String>(m_type);
}

data_map_t* device2_t::get_data()
{
  return &m_data_map;
}

irs::mxdata_t* device2_t::get_mxdata()
{
  IRS_LIB_ASSERT(created());
  return mp_mxdata_assembly->mxdata();
}

bool device2_t::created() const
{
  return !mp_mxdata_assembly.is_empty();
}

bool device2_t::enabled() const
{
  if (!created()) {
    return false;
  }
  return mp_mxdata_assembly->enabled();
}

bool device2_t::connected() const
{
  if (created()) {
    //if (mp_mxdata_assembly->enabled()) {
      if (mp_mxdata_assembly->mxdata()) {
        return m_data_map.is_connected() &&
          mp_mxdata_assembly->mxdata()->connected();
      }
    //}
  }

  /*bool connected = false;
  if (mp_mxdata_assembly->mxdata()) {
    connected = m_data_map.is_connected() &&
      mp_mxdata_assembly->mxdata()->connected();
  } */
  return false;
  //return m_data_map.is_connected();
}

void device2_t::load(const String& a_device_file_name)
{
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_device_file_name);
  ini_file.set_section(mp_file_name_service->get_device_options_section());
  device_options_t device_options;
  device_options.type = irst("mxnet");
  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);
  if (FileExists(a_device_file_name)) {
    ini_file.load();
  } else {
    ini_file.save();
  }
  reset(a_device_file_name.c_str(), device_options);
}

void device2_t::create_config_from_old(const String& a_device_file_name,
  const String& a_type,
  const String& a_ip_address,
  const irs_u32 a_port)
{
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_device_file_name);
  ini_file.set_section(mp_file_name_service->get_device_options_section());
  device_options_t device_options;
  device_options.type = irst("mxnet");
  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);

  if (FileExists(a_device_file_name)) {
    ini_file.load();
  } else {
    ini_file.save();
  }

  device_options.type = a_type.c_str();
  ini_file.save();
  reset(a_device_file_name.c_str(), device_options);

  //change_device_type(a_config_name, a_type);

  mp_mxdata_assembly->options()->set_option(irst("IP"),
    irs::str_conv<string_type>(a_ip_address));
  mp_mxdata_assembly->options()->set_option(irst("Порт"),
    irs::num_to_str(a_port));

  reset(a_device_file_name.c_str(), device_options);
}

void device2_t::change_type(const String& a_device_file_name,
  const String& a_type)
{
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_device_file_name);
  ini_file.set_section(mp_file_name_service->get_device_options_section());
  device_options_t device_options;
  device_options.type = irst("mxnet");
  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);
  ini_file.load();
  if (!FileExists(a_device_file_name)) {
    ini_file.save();
  }
  if (!a_type.IsEmpty()) {
    device_options.type = a_type.c_str();
    ini_file.save();
  }
  reset(a_device_file_name.c_str(), device_options);
}

void device2_t::show_options()
{
  IRS_LIB_ASSERT(created());
  mp_mxdata_assembly->show_options();
}

void device2_t::show_tstlan()
{
  IRS_LIB_ASSERT(created());
  mp_tstlan4lib->show();
}

void device2_t::show_connection_log()
{
  IRS_LIB_ASSERT(created());
  mp_connection_log->Show();
}

void device2_t::reset()
{
  m_data_map.reset_connection();
  if (!mp_mxdata_assembly.is_empty()) {
    mp_mxdata_assembly->enabled(false);
  }
  mp_tstlan4lib.reset();
  mp_mxdata_assembly.reset();
  mp_connection_log.reset();
}

void device2_t::reset(const string_type& a_device_file_name,
  const device_options_t& a_device)
{
  m_data_map.reset_connection();

  mp_tstlan4lib.reset();
  mp_tstlan4lib = make_tstlan4lib();

  if (!mp_tstlan4lib.is_empty()) {
    mp_tstlan4lib->ini_name(a_device_file_name);
    mp_tstlan4lib->load_conf();
    mp_mxdata_assembly.reset();
    mp_mxdata_assembly = irs::mxdata_assembly_types()->
      make_assembly(a_device.type, mp_tstlan4lib.get(),
        a_device_file_name);


    if (!mp_mxdata_assembly.is_empty()) {
      //ap_device->mxdata_assembly->enabled(a_device.enabled);
      m_type = a_device.type;
      mp_connection_log.reset(new TConnectionLogForm(NULL));
      mp_tstlan4lib->connect(mp_mxdata_assembly->mxdata());
    }
  }
}

irs::handle_t<irs::tstlan4_base_t> device2_t::make_tstlan4lib()
{
  const counter_t update_time = irs::make_cnt_ms(100);
  const string_type ini_name = irst("tstlan.ini");
  typedef irs::tstlan::view_t view_type;
  irs::handle_t<irs::tstlan4_base_t> tstlan5(new irs::tstlan::view_t(
    irs::tstlan::view_t::ft_internal,
    mp_chart,
    ini_name,
    string_type(),
    update_time,
    irs::tstlan::view_t::global_log_unchange));
  return tstlan5;
}

void device2_t::tick()
{
  if (!created()) {
    return;
  }
  if (!mp_mxdata_assembly->enabled()) {
    return;
  }
  mp_mxdata_assembly->tick();
  mp_tstlan4lib->tick();

  mp_connection_log->add_errors(
    mp_mxdata_assembly->get_last_error_string_list());
  if (mp_mxdata_assembly->mxdata()) {
    if (mp_mxdata_assembly->mxdata()->connected()) {
      if (!m_data_map.is_connected()) {
        m_data_map.connect(mp_mxdata_assembly->mxdata(),
          m_config_calibr);
      }
    }
  }
}

void save_string_grid_to_csv_with_dialog(TStringGrid* ap_string_grid,
  const String& a_file_name_default)
{
  typedef size_t size_type;
  typedef irs::string_t string_type;

  irs::handle_t<TSaveDialog> SaveDialog(new TSaveDialog(NULL));

  SaveDialog->Filter = irst("Текстовые файлы Microsoft Excel (*.csv)")
    irst("|*.csv|Все файлы (*.*)|*.*");
  SaveDialog->DefaultExt = irst("csv");
  if (a_file_name_default.IsEmpty()) {
    SaveDialog->FileName = irst("Новый файл.csv");
  } else {
    SaveDialog->FileName = a_file_name_default;
  }
  if (SaveDialog->Execute()) {
    if (FileExists(SaveDialog->FileName)) {
      if (Application->MessageBox(
          irst("Такой файл уже существует. Перезаписать?"),
          irst("Вопрос"),  MB_OKCANCEL + MB_DEFBUTTON2 + MB_ICONQUESTION) !=
            IDOK) {
        return;
      }
    }
    const string_type file_name = SaveDialog->FileName.c_str();
    irs::csvwork::csv_file_synchro_t csv_file(file_name);

    irs::table_string_t table_string;

    table_string.set_col_count(ap_string_grid->ColCount);
    table_string.set_row_count(ap_string_grid->RowCount);
    for (size_type c = 0; c < table_string.get_col_count(); c++) {
      for (size_type r = 0; r < table_string.get_row_count(); r++) {
        const string_type cell_value =
          irs::str_conv<string_type>(ap_string_grid->Cells[c][r]);
        table_string.write_cell(c, r, cell_value);
      }
    }

    csv_file.save(table_string);
  }
}
