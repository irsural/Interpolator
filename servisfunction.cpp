//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <irsalg.h>
#include <measmul.h>
#include <irssysutils.h>
#include <irscalc.h>
#include <tstlan5lib.h>

#include "servisfunction.h"

#include <irsfinal.h>


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
//return;
  //mp_table->Repaint();
  unsigned int size_z = av_data.size();
  unsigned int size_x = 0;
  unsigned int size_y = 0;
  if(size_z > 0){
    size_x = av_data[0].col_count();
    size_y = av_data[0].row_count();
  }
  mp_table->ColCount = size_x;
  mp_table->RowCount = size_z*size_y;
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
  if (cur_col != 0){
    int table_count = mv_table.size();
    cell_t cell;
    cell.value = 0;
    cell.init = false;
    for(int i = 0; i < table_count; i++){
      mv_table[i].newcols(cur_col, create_col_count, cell);
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);
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
  if(select_col < 1)
    select_col = 1;
  //вычисляем количество добовляемых столбцов
  if(a_type_step_col == INCREMENT_STEP)
    count = (a_num_finite-a_num_begin)/a_step+1;
  else if(a_type_step_col == DECREMENT_STEP)
    count = (a_num_begin-a_num_finite)/a_step+1;
  else if(a_type_step_col == MULTIPLIER_STEP)
    count = 1+logl(a_num_finite/a_num_begin)/logl(a_step);
  if(count < 2){ new_col_count = 2;
  }else{
    integer_part_count = count;
    if(count-integer_part_count < m_min_fractional_part_count)
      new_col_count = integer_part_count;
    else
      new_col_count = integer_part_count + 1;
  }
  all_col_count = previous_col_count + new_col_count;
  if(all_col_count <= m_max_col_count){
    unsigned int size = mv_table.size();
    cell_t cell;
    cell.value = 0;
    cell.init = true;
    //заполняем шапку таблицы новыми значениями
    for(unsigned int i = 0; i < size; i++){
      cur_number_x = a_num_begin;
      mv_table[i].newcols(select_col, new_col_count, cell);
      for(int x = select_col; x < select_col+new_col_count-1; x++){
        cell.value = cur_number_x;
        mv_table[i][x][0] = cell;
        if(a_type_step_col == INCREMENT_STEP)
          cur_number_x = cur_number_x+a_step;
        else if(a_type_step_col == DECREMENT_STEP)
          cur_number_x = cur_number_x-a_step;
        else if(a_type_step_col == MULTIPLIER_STEP)
          cur_number_x = cur_number_x*a_step;
      }
      cell.value = a_num_finite;
      mv_table[i][select_col+new_col_count-1][0] = cell;
    }
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }               
}
void table_data_t::delete_col_table()
{
  int cur_col = 0;
  cur_col = mp_display_table->col();
  if(cur_col > 0)
  {
    int table_count = mv_table.size();
    if(table_count > 0){
      if(mv_table[0].col_count() > 2){
        for(int i = 0; i < table_count; i++){
          mv_table[i].delcols(cur_col, cur_col);
        }
        mp_display_table->out_display(mv_table, m_inf_in_param);
      }
    }
  }
}
void table_data_t::create_row_table()
{
  const create_row_count = 1;
  int cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0){
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

void table_data_t::create_new_table()
{
  clear_table_def();
  mv_saved_table = mv_table;
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
  const unsigned int size_z = mv_table.size();

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

void table_data_t::load_table_from_file(const string_type& a_file_name)
{
  std::vector<irs::matrix_t<cell_t> > table;
  number_in_param_t param_count_from_file = TWO_PARAM;

  ::load_table_from_file(param_count_from_file, a_file_name, table);
  /*try {
    load_table_from_json_file(param_count_from_file, a_file_name, subtable);
  } catch (...) {
    load_table_from_ini_file(param_count_from_file, a_file_name, subtable);
  } */

  if (m_inf_in_param.number_in_param == param_count_from_file) {
    mv_table.clear();
    #ifdef debug_version_digital_interpolator
    mv_saved_table.clear();
    mv_saved_table = table;
    #endif
    mv_table = table;
    mp_display_table->out_display(mv_table, m_inf_in_param);
  } else {
    // сообщение о несоответствии загруженного файла выбранной конфигурации
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
    throw std::runtime_error("Неудалось разобрать файл");
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
  }
}
void table_data_t::clear_table_def()
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
    mp_display_table->out_display(mv_table, m_inf_in_param);
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

void table_data_t::set_file_namedir(String a_file_namedir)
{
  m_file_namedir = a_file_namedir;
}

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
  } catch (...) {
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

//-------------------------------------------------------------------------
//struct config_calibr_t
config_calibr_t::config_calibr_t():
  type_meas(irs::str_conv<String>(type_meas_to_str(tm_first))),
  device_name(),
  reference_device_name(),
  ip_adress(irst("192.168.0.200")),
  port(5005),
  in_parametr1(),
  in_parametr2(),
  in_parametr3(),
  out_parametr(),
  v_parametr_ex(),
  bit_pos_mismatch_state(),
  bit_pos_correct_mode(),
  bit_pos_operating_duty(),
  bit_pos_error_bit(),
  bit_pos_reset_over_bit(),
  bit_pos_phase_preset_bit(),
  bit_type2_array(),
  index_work_time(0),
  index_pos_eeprom(0),
  out_param_config_for_measurement(),
  out_param_control_config(),
  temperature_control(),
  type_sub_diapason(tsd_parameter2),
  v_sub_diapason_calibr(),
  meas_range_koef(1.),
  delay_meas(0),
  meas_interval(0),
  count_reset_over_bit(0),
  active_filename(),
  reference_channel()
{
}
void config_calibr_t::clear()
{
  *this = config_calibr_t();
}
bool config_calibr_t::save(const string_type& a_filename)
{
  bool fsuccess = true;
  if (a_filename.empty()) {
    fsuccess = false;
    return fsuccess;
  }
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_filename.c_str());
  ini_file.clear_control();
  add_static_param(&ini_file);
  ini_file.save();
  ini_file.clear_control();

  ini_file.set_section(irst("Конфигурация устройства"));
  ini_file.add(irst("Имя"), &device_name);

  ini_file.set_section(irst("Конфигурация опорного устройства"));
  ini_file.add(irst("Имя"), &reference_device_name);

  string_type in_parametr1_unit_str =
    lang_type_to_str(in_parametr1.unit);
  string_type in_parametr2_unit_str =
    lang_type_to_str(in_parametr2.unit);
  string_type in_parametr3_unit_str =
    lang_type_to_str(in_parametr3.unit);
  string_type out_parametr_unit_str =
    lang_type_to_str(out_parametr.unit);
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
  int sub_diapason_count = v_sub_diapason_calibr.size();
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
    int index_start = v_sub_diapason_calibr[i].index_start;
    int size = v_sub_diapason_calibr[i].size;
    double value_begin = v_sub_diapason_calibr[i].value_begin;
    double value_end = v_sub_diapason_calibr[i].value_end;
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
  int param_ex_count = v_parametr_ex.size();
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

    String name = v_parametr_ex[i].name.c_str();
    String unit = lang_type_to_str(v_parametr_ex[i].unit).c_str();
    String type_variable = v_parametr_ex[i].type_variable.c_str();
    irs_i32 index = v_parametr_ex[i].index;
    double value_working = v_parametr_ex[i].value_working;
    double value_default = v_parametr_ex[i].value_default;

    ini_file.add(name_key, &name);
    ini_file.add(unit_key, &unit);
    ini_file.add(type_variable_key, &type_variable);
    ini_file.add(index_key, &index);
    ini_file.add(value_working_key, &value_working);
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
    bool value_working = bit_type2_array[i].value_working;
    bool value_def = bit_type2_array[i].value_def;
    ini_file.add(bitname_key, &bitname);
    ini_file.add(byte_index_key, &index_byte);
    ini_file.add(bit_index_key, &index_bit);
    ini_file.add(value_working_key, &value_working);
    ini_file.add(value_def_key, &value_def);
    ini_file.save();
    ini_file.clear_control();
  }
  return fsuccess;
}
bool config_calibr_t::load(const string_type& a_filename)
{
  bool fsuccess = true;
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_filename.c_str());
  ini_file.clear_control();
  add_static_param(&ini_file);
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
      str_to_lang_type(in_parametr1_unit_str.c_str(), in_parametr1.unit);
  }
  if (fsuccess) {
    str_to_lang_type(in_parametr2_unit_str.c_str(), in_parametr2.unit);
  }
  if (fsuccess) {
    str_to_lang_type(in_parametr3_unit_str.c_str(), in_parametr3.unit);
  }
  if (fsuccess) {
    str_to_lang_type(out_parametr_unit_str.c_str(), out_parametr.unit);
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
    v_sub_diapason_calibr.clear();
    if (num_param_sub_diapason == 1) {
      type_sub_diapason = tsd_parameter1;
    } else {
      type_sub_diapason = tsd_parameter2;
    }
    ini_file.set_section(irst("Опции"));
    for (int i = 0; i < sub_diapason_count; i++) {
      sub_diapason_calibr_t sub_diapason_calibr;
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
      v_sub_diapason_calibr.push_back(sub_diapason_calibr);
    }
    // загрузка доп.параметров
    ini_file.clear_control();
    ini_file.set_section(irst("Опции"));
    int param_ex_count = 0;
    ini_file.add(irst("Количество доп.параметров"), &param_ex_count);
    ini_file.load();
    ini_file.clear_control();
    v_parametr_ex.clear();
    ini_file.set_section(irst("Опции"));
    for (int i = 0; i < param_ex_count; i++) {
      parametr_ex_t parametr_ex;
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
      ini_file.add(type_variable_key, &parametr_ex.type_variable);
      ini_file.add(index_key, &parametr_ex.index);
      ini_file.add(value_working_key, &parametr_ex.value_working);
      ini_file.add(value_default_key, &parametr_ex.value_default);
      ini_file.load();
      ini_file.clear_control();
      fsuccess = str_to_lang_type(unit_str.c_str(), parametr_ex.unit);
      if (!fsuccess) {
        break;
      }
      v_parametr_ex.push_back(parametr_ex);
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
      ini_file.add(value_working_key, &bit_type2_pos.value_working);
      ini_file.add(value_def_key, &bit_type2_pos.value_def);
      ini_file.load();
      ini_file.clear_control();
      bit_type2_pos.bitname = bitname.c_str();
      bit_type2_array.push_back(bit_type2_pos);
    }
  }
  if (!fsuccess) {
    // освобождение ресурсов ресурсов
    ini_file.clear_control();
    clear();
  }
  return fsuccess;
}
void config_calibr_t::add_static_param(irs::ini_file_t* ap_ini_file)
{
  ap_ini_file->set_section(irst("Свойства сетевого подключения"));
  ap_ini_file->add(irst("IP-адрес"), &ip_adress);
  ap_ini_file->add(irst("Порт"),&port);

  ap_ini_file->set_section(irst("Входной параметр 1"));
  ap_ini_file->add(irst("Имя параметра"), &in_parametr1.name);
  ap_ini_file->add(irst("Единицы измерения"), &in_parametr1.type_variable);

  //ap_ini_file->add("Тип параметра", &in_parametr1.unit);
  ap_ini_file->add(irst("Привязка"), &in_parametr1.anchor);
  ap_ini_file->add(irst("Индекс"), &in_parametr1.index);
  ap_ini_file->add(irst("Коэффициент"), &in_parametr1.koef);
  ap_ini_file->add(irst("Значение по умолчанию"), &in_parametr1.default_val);

  ap_ini_file->set_section(irst("Входной параметр 2"));
  ap_ini_file->add(irst("Имя параметра"), &in_parametr2.name);
  ap_ini_file->add(irst("Единицы измерения"), &in_parametr2.type_variable);
  //ap_ini_file->add("Тип параметра", &in_parametr2.unit);
  ap_ini_file->add(irst("Привязка"), &in_parametr2.anchor);
  ap_ini_file->add(irst("Индекс"), &in_parametr2.index);
  ap_ini_file->add(irst("Коэффициент"), &in_parametr2.koef);
  ap_ini_file->add(irst("Значение по умолчанию"), &in_parametr2.default_val);

  ap_ini_file->set_section(irst("Входной параметр 3"));
  ap_ini_file->add(irst("Имя параметра"), &in_parametr3.name);
  ap_ini_file->add(irst("Единицы измерения"), &in_parametr3.type_variable);
  //ap_ini_file->add("Тип параметра", &in_parametr3.unit);
  ap_ini_file->add(irst("Индекс"), &in_parametr3.index);
  ap_ini_file->add(irst("Коффициент"), &in_parametr3.koef);
  ap_ini_file->add(irst("Значение по умолчанию"), &in_parametr3.default_val);

  ap_ini_file->set_section(irst("Выходной параметр"));
  ap_ini_file->add(irst("Имя параметра"), &out_parametr.name);
  ap_ini_file->add(irst("Единицы измерения"), &out_parametr.type_variable);
  //ap_ini_file->add("Тип параметра", &out_parametr.unit);
  ap_ini_file->add(irst("Индекс"), &out_parametr.index);
  ap_ini_file->add(irst("Коэффициент шунта"), &out_parametr.koef_shunt);

  ap_ini_file->set_section(irst("Опции"));
  ap_ini_file->add(irst("Вид измерения"), &type_meas);
  ap_ini_file->add(irst("Коэффициент диапазона измерения"), &meas_range_koef);
  ap_ini_file->add(irst("Задержка измерения"), &delay_meas);
  ap_ini_file->add(irst("Время измерений"), &meas_interval);
  ap_ini_file->add(irst("Количество допустимых сбросов ошибок"),
    &count_reset_over_bit);
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

  ap_ini_file->set_section(irst("Опции выходного параметра для измерения"));
  ap_ini_file->add(irst("Учитывать выходной параметр при измерении"),
    &out_param_config_for_measurement.consider_out_param);
  ap_ini_file->add(irst("Включить фильтрацию выходного параметра"),
    &out_param_config_for_measurement.out_param_filter_enabled);
  ap_ini_file->add(irst("Время дискретизации"),
    &out_param_config_for_measurement.filter_sampling_time);
  ap_ini_file->add(irst("Количество точек"),
    &out_param_config_for_measurement.filter_point_count);

  ap_ini_file->set_section(irst("Контроль выходного параметра"));
  ap_ini_file->add(irst("Включение"),
    &out_param_control_config.enabled);
  ap_ini_file->add(irst("Допустимое относительное отклонение"),
    &out_param_control_config.max_relative_difference);
  ap_ini_file->add(irst("Временное окно"), &out_param_control_config.time);

  ap_ini_file->set_section(irst("Контроль температуры"));
  ap_ini_file->add(irst("Включение"),
    &temperature_control.enabled);
  ap_ini_file->add(irst("Индекс"), &temperature_control.index);
  ap_ini_file->add(irst("Уставка"), &temperature_control.reference);
  ap_ini_file->add(irst("Допустимое отклонение"),
    &temperature_control.difference);
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
    a_config_calibr.in_parametr1.unit,
    ap_data,
    index,
    x_count);
  index = y_points.connect(
    a_config_calibr.in_parametr2.unit,
    ap_data,
    index,
    y_count);
  irs_uarc koef_array_size = x_count * y_count * a_number_of_koef_per_point;

  koef_array.connect(
    a_config_calibr.out_parametr.unit,
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
