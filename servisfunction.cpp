//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <irsalg.h>
#include "servisfunction.h"
#include "irscalc.h"

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
  mp_table->ColCount = size_x;
  mp_table->RowCount = size_z*size_y;
  int y1 = 0;
  for(unsigned int z = 0; z < size_z; z++){
    for(unsigned int y = 0; y < size_y; y++){
      for(unsigned int x = 0; x < size_x; x++){
        AnsiString cell_str;
        cell_t cell = av_data[z][x][y];
        if(cell.init){
          irs::string value_str;
          ostrstream ostr;
          ostr << setprecision(m_precision) << cell.value << ends;
          value_str = ostr.str();
          ostr.freeze(false);
          bool select_cell_x = (x > 0) && (y == 0);
          bool select_cell_y = (x == 0) && (y > 0);
          irs::string type_variable;
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
          mp_table->Cells[x][y1] = (value_str+" "+type_variable).c_str();
        }else{
          mp_table->Cells[x][y1] = "";
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
  const int a_col_displ, const int a_row_displ, const cell_t a_cell)
{
  irs::string cell_str = "";
  if(a_cell.init == true){
    cell_str =  a_cell.value;     
  }else{
    cell_str = "";
  }
  mp_table->Cells[a_col_displ][a_row_displ] = cell_str.c_str();
}
void table_string_grid_t::out_display_cur_cell(const cell_t a_cell)
{
  int col = mp_table->Col;
  int row = mp_table->Row;
  irs::string cell_str = "";
  if(a_cell.init == true){
    cell_str = a_cell.value;
  }else{
    cell_str = "";
  }
  mp_table->Cells[col][row] = cell_str.c_str();
}
void table_string_grid_t::out_display_cell_variable_precision(
  const int a_col_displ,
  const int a_row_displ,
  const cell_t a_cell,
  const irs::string& a_type_variable)
{
  irs::string cell_str = "";
  if(a_cell.init == true){  
    ostrstream ostr;
    ostr << setprecision(m_precision) << a_cell.value << '\0';
    cell_str = ostr.str();
    ostr.freeze(false);
    cell_str += irs::string(" ")+a_type_variable.c_str();
  }else{
    cell_str = "";
  }
  mp_table->Cells[a_col_displ][a_row_displ] = cell_str.c_str();
}
cell_t table_string_grid_t::in_display_cur_cell()
{
  int col = mp_table->Col;
  int row = mp_table->Row;
  AnsiString cell_str = mp_table->Cells[col][row];
  cell_t cell;
  if(cell_str == ""){
    cell.value = 0.0;
    cell.init = false;
  }else{
    irs::string str_value = cell_str.c_str();
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
  AnsiString a_name):
  mp_error_trans(irs::error_trans()),
  m_min_fractional_part_count(0.00000000001),
  m_nan(2e300),    
  mp_display_table(ap_display_table),
  m_name(a_name),
  m_file_namedir(""),
  mv_table(),
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
void table_data_t::cell_out_display_variable_precision(
  const int a_col_displ,
  const int a_row_displ)
{
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    irs::string type_variable;
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
      for(int i = 0; i < table_count; i++){
        cell_t cur_cell = mv_table[i][a_col_displ][cur_row];
        int row_displ = row_displ_begin+i*row_count;
        mp_display_table->out_display_cell_variable_precision(
          a_col_displ, row_displ, cur_cell, type_variable);
      }
    }else{
      cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];
      mp_display_table->out_display_cell_variable_precision(
        a_col_displ, a_row_displ, cur_cell, type_variable);
    }
  }
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

void table_data_t::save_table_to_file(const string a_file_name)
{
  //запись в ini файл размеров кватерниона
  auto_ptr<TIniFile> inifile(new TIniFile(a_file_name.c_str()));
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
  for(unsigned int z = 0; z < size_z; z++){
    String table_name = "table"+ IntToStr(z);
    for(unsigned int y = 0; y < size_y; y++){
      std::strstream row_str;
      for(unsigned int x = 0; x < size_x; x++){
        double value_cell;
         cell_t cell = mv_table[z][x][y];
        if(cell.init == true){
          value_cell = cell.value;
        }else{
          value_cell = m_nan;
        }
        row_str<<setw(m_field_width)<<left<<setprecision(m_precision)<<
          value_cell;
      }
      row_str<<ends;
      String row_name = "row"+ IntToStr(y);
      inifile->WriteString(table_name, row_name, row_str.str());
      row_str.freeze(false);
    }
  }
  #ifdef  debug_version_digital_interpolator
  mv_fixed_table = mv_table;
  #endif
}
void table_data_t::save_table_to_microsoft_excel_csv_file(
  const string a_file_name)
{
  irs::string file_name = a_file_name;
  std::ofstream outfile(file_name.c_str(), ios::trunc);
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
              outfile << ';';
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
void table_data_t::save_table_to_m_file(const irs::string a_file_name) const
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
  AnsiString num_str = "";
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
        outfile<<setprecision(m_precision)<<StrToFloat(m_nan)<<flush;
        outfile<<","<<" "<<flush;
      }else{
        outfile<<setprecision(m_precision)<<StrToFloat(m_nan)<<flush;
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
        outfile<<setprecision(m_precision)<<StrToFloat(m_nan)<<flush;
        outfile<<","<<" "<<flush;
      }else{
        outfile<<setprecision(m_precision)<<StrToFloat(m_nan)<<flush;
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
          outfile<<setprecision(m_precision)<<StrToFloat(m_nan)<<flush;
          outfile<<","<<" "<<flush;
        }else{
          outfile<<setprecision(m_precision)<<StrToFloat(m_nan)<<flush;
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
void table_data_t::load_table_from_file(const string a_file_name)
{
  std::vector<irs::matrix_t<cell_t> > table;
  number_in_param_t param_count_from_file = TWO_PARAM;
  load_table_from_file(param_count_from_file, a_file_name, table);
  if(m_inf_in_param.number_in_param != param_count_from_file){
    // сообщение о несоответствии загруженного файла выбранной конфигурации
  }else{
    mv_table.clear();
    #ifdef  debug_version_digital_interpolator
    mv_fixed_table.clear();
    mv_fixed_table = table;
    #endif
    mv_table = table; 
    mp_display_table->out_display(mv_table, m_inf_in_param);
  }

}
//---------------------------------------------------------------------------
void table_data_t::load_subtable_from_file(const string a_file_name)
{
  std::vector<irs::matrix_t<cell_t> > subtable;
  number_in_param_t param_count_from_file = TWO_PARAM;
  load_table_from_file(param_count_from_file, a_file_name, subtable);
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
    mv_fixed_table.clear();
    mv_fixed_table = mv_table;
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
void table_data_t::clear_table() const
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
  {mv_coord_special_cells.resize(0);}

void table_data_t::set_file_namedir(AnsiString a_file_namedir)
  {m_file_namedir = a_file_namedir;}

AnsiString table_data_t::get_file_namedir()
  {return m_file_namedir;}
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

void table_data_t::load_table_from_file(
  number_in_param_t& a_number_in_param,
  const string& a_file_name,
  std::vector<irs::matrix_t<cell_t> >& a_table)
{
  //чтение из ini файла размеров кватерниона
  auto_ptr<TIniFile> inifile(new TIniFile(a_file_name.c_str()));

  unsigned int param_count = 100;
  param_count = inifile->ReadInteger("Setting", "parameter_count", param_count);
  if(param_count == 2){
    a_number_in_param = TWO_PARAM;
  }else if(param_count == 3){
    a_number_in_param = THREE_PARAM;
  }

  unsigned int size_x = 0;
  size_x = inifile->ReadInteger("Setting", "size_x", size_x);
  unsigned int size_y = 0;
  size_y = inifile->ReadInteger("Setting", "size_y", size_y);
  unsigned int size_z = 0;
  size_z = inifile->ReadInteger("Setting", "size_z", size_z);
  a_table.clear();
  a_table.reserve(size_z);

  //чтение значений ячеек кватерниона
  for(unsigned int z = 0; z < size_z; z++){
    irs::matrix_t<cell_t> matrix(size_x, size_y);
    String table_name = "table"+ IntToStr(z);
    for(unsigned int y = 0; y < size_y; y++){
      AnsiString row_str_string;
      std::strstream row_str;
      String row_name = "row"+ IntToStr(y);
      row_str_string =
        inifile->ReadString(table_name, row_name, row_str_string);
      row_str<<row_str_string.c_str()<<'\0';
      for(unsigned int x = 0; x < size_x; x++){
        double value_cell;
         row_str>>value_cell;
         cell_t cell;
         cell.value = value_cell;
        if(value_cell != m_nan){
          cell.init = true;
        }else{
          cell.init = false;
        }
        matrix[x][y] = cell;
      }
      row_str.freeze(false);
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

void table_data_t::modifi_content_table(const irs::string& a_str)
{
  const irs::string z_name = "z";
  const irs::string x_name = "x";
  const irs::string y_name = "y";
  const int z_name_size = z_name.size();
  const int x_name_size = x_name.size();
  const int y_name_size = y_name.size();
  int table_count = mv_table.size();
  if(table_count > 0){
    irs::calculator_t calculator;
    calculator.add_func_r_double_a_double(
      "phasen180",
      irs::phase_normalize_180);
    int col_count = mv_table[0].col_count();
    int row_count = mv_table[0].row_count();
    for(int table = 0; table < table_count; table++){
      for(int col = 1; col < col_count; col++){
        for(int row = 1; row < row_count; row++){
          cell_t cell_param_col = mv_table[table][col][0];
          cell_t cell_param_row = mv_table[table][0][row];
          cell_t cell = mv_table[table][col][row];
          bool replace_str_success = true;
          irs::string mathem_expression_str = a_str;
          int z_param_pos = mathem_expression_str.find(z_name);
          while(z_param_pos != irs::string::npos) {
            if (cell.init) {
              irs::string param_z_str = cell.value;
              mathem_expression_str.replace(
                z_param_pos, z_name_size, param_z_str);
              z_param_pos = mathem_expression_str.find(z_name);
            } else {
              replace_str_success = false;
              break;
            }
          }
          int x_param_pos = mathem_expression_str.find(x_name);
          while (x_param_pos != irs::string::npos) {
            if (cell_param_col.init) {
              irs::string param_col_str = cell_param_col.value;
              mathem_expression_str.replace(
                x_param_pos, x_name_size, param_col_str);
            }  else {
              replace_str_success = false;
              break;
            }
            x_param_pos = mathem_expression_str.find(x_name);
          }
          int y_param_pos = mathem_expression_str.find(y_name);
          while (y_param_pos != irs::string::npos) {
            if (cell_param_row.init) {
              irs::string param_row_str = cell_param_row.value;
              mathem_expression_str.replace(
                y_param_pos, y_name_size, param_row_str);
            } else {
              replace_str_success = false;
              break;
            }
            y_param_pos = mathem_expression_str.find(y_name);
          }

          if (replace_str_success) {
            if (calculator.calc(mathem_expression_str, cell.value)) {
              cell.init = true;
              mv_table[table][col][row] = cell;
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
log_t::log_t(TMemo* ap_memo, string a_file_name):
  m_error_open_file_log(0),
  #ifdef type_log_stream
  m_buflog(ap_memo),
  m_log_display(&m_buflog),
  #else
  mp_memo(ap_memo),
  #endif
  m_outfile(a_file_name.c_str(), ios::app)
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
void log_t::operator<<(AnsiString a_str)
{
  AnsiString time_str = "", date_time_str = "";

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
  std::ostrstream ostr;
  ostr << setw(m_field_width_file_date_time) << left <<
    date_time_str.c_str() << a_str.c_str() << ends;
  mp_memo->Lines->Add(ostr.str());
  ostr.rdbuf()->freeze(false);
  #endif
}
//извлекает из имени файла(без пути) имя файла без расширения
AnsiString extract_short_filename(const AnsiString& a_filename)
{
  AnsiString ext_filename = ExtractFileExt(a_filename);
  AnsiString short_filename = "";
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
  const AnsiString& a_text)
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
  ini_file()
{
}
void config_calibr_t::clear()
{
  type_meas = "";
  ip_adress = "";
  port = 5005;
  in_parametr1.clear();
  in_parametr2.clear();
  in_parametr3.clear();
  out_parametr.clear();
  bit_pos_mismatch_state.clear();
  bit_pos_correct_mode.clear();
  bit_pos_operating_duty.clear();
  bit_pos_error_bit.clear();
  bit_pos_reset_over_bit.clear();
  bit_pos_phase_preset_bit.clear();
  bit_type2_array.clear();
  index_work_time = 0;
  index_pos_eeprom = 0;
  type_sub_diapason = tsd_parameter2;
  v_sub_diapason_calibr.clear();
  delay_meas = 0;
  count_reset_over_bit = 0;  
  active_filename = "";
  reference_channel.enabled = false;
  reference_channel.ip_adress = "";
  reference_channel.port = 5005;
}
bool config_calibr_t::save(const irs::string& a_filename)
{
  bool fsuccess = true;
  if (a_filename == "") {
    fsuccess = false;
    return fsuccess;
  }
  ini_file.set_ini_name(a_filename.c_str());
  ini_file.clear_control();
  add_static_param();
  ini_file.save();
  ini_file.clear_control();
  irs::string in_parametr1_unit_str =
    lang_type_to_str(in_parametr1.unit);
  irs::string in_parametr2_unit_str =
    lang_type_to_str(in_parametr2.unit);
  irs::string in_parametr3_unit_str =
    lang_type_to_str(in_parametr3.unit);
  irs::string out_parametr_unit_str =
    lang_type_to_str(out_parametr.unit);
  ini_file.set_section("Входной параметр 1");
  ini_file.add("Тип параметра", &in_parametr1_unit_str);
  ini_file.set_section("Входной параметр 2");
  ini_file.add("Тип параметра", &in_parametr2_unit_str);
  ini_file.set_section("Входной параметр 3");
  ini_file.add("Тип параметра", &in_parametr3_unit_str);
  ini_file.set_section("Выходной параметр");
  ini_file.add("Тип параметра", &out_parametr_unit_str);
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section("Опции");
  int sub_diapason_count = v_sub_diapason_calibr.size();
  ini_file.add("Количество поддиапазонов", &(irs_i32)sub_diapason_count);
  int num_param_sub_diapason = 0;
  ini_file.add("Тип поддиапазона", &(irs_i32)num_param_sub_diapason);
  if (type_sub_diapason == tsd_parameter1) {
    num_param_sub_diapason = 1;
  } else {
    num_param_sub_diapason = 2;
  }
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section("Опции");
  for (int i = 0; i < sub_diapason_count; i++) {
    AnsiString diapason_id_key = " д" + IntToStr(i);
    AnsiString index_start_key = "Начальный индекс" + diapason_id_key;
    AnsiString size_key = "Размер" + diapason_id_key;
    AnsiString value_begin_key = "Начальное значение" + diapason_id_key;
    AnsiString value_end_key = "Конечное значение" + diapason_id_key;
    int index_start = v_sub_diapason_calibr[i].index_start;
    int size = v_sub_diapason_calibr[i].size;
    double value_begin = v_sub_diapason_calibr[i].value_begin;
    double value_end = v_sub_diapason_calibr[i].value_end;
    ini_file.add(index_start_key, &(irs_i32)index_start);
    ini_file.add(size_key, &(irs_i32)size);
    ini_file.add(value_begin_key, &value_begin);
    ini_file.add(value_end_key, &value_end);
    ini_file.save();
    ini_file.clear_control();
  }
  // сохранение доп.параметров
  ini_file.clear_control();
  ini_file.set_section("Опции");
  int param_ex_count = v_parametr_ex.size();
  ini_file.add("Количество доп.параметров", &(irs_i32)param_ex_count);
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section("Опции");
  for (int i = 0; i < param_ex_count; i++) {
    AnsiString param_ex_id_key = " доп.параметр" + IntToStr(i);
    AnsiString name_key = "Имя параметра" + param_ex_id_key;
    AnsiString unit_key = "Единицы измерения" + param_ex_id_key;
    AnsiString type_variable_key = "Тип параметра" + param_ex_id_key;
    AnsiString index_key = "Индекс байта" + param_ex_id_key;
    AnsiString value_working_key = "Рабочее значение" + param_ex_id_key;
    AnsiString value_default_key = "Значение по умолчанию" + param_ex_id_key;

    AnsiString name = v_parametr_ex[i].name.c_str();
    AnsiString unit = lang_type_to_str(v_parametr_ex[i].unit).c_str();
    AnsiString type_variable = v_parametr_ex[i].type_variable.c_str();
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
  ini_file.set_section("Опции");
  int bit_type2_count = bit_type2_array.size();
  ini_file.add("Количество доп.битов", &(irs_i32)bit_type2_count);
  ini_file.save();
  ini_file.clear_control();
  ini_file.set_section("Опции");
  for (int i = 0; i < bit_type2_count; i++) {
    AnsiString bit_type2_id_key = " доп.бит" + IntToStr(i);
    AnsiString bitname_key = "Имя бита" + bit_type2_id_key;
    AnsiString byte_index_key = "Индекс байта" + bit_type2_id_key;
    AnsiString bit_index_key = "Индекс бита" + bit_type2_id_key;
    AnsiString value_working_key = "Рабочее значение" + bit_type2_id_key;
    AnsiString value_def_key = "Значение по умолчанию" + bit_type2_id_key;
    AnsiString bitname = bit_type2_array[i].bitname.c_str();
    int index_byte = bit_type2_array[i].index_byte;
    int index_bit = bit_type2_array[i].index_bit;
    bool value_working = bit_type2_array[i].value_working;
    bool value_def = bit_type2_array[i].value_def;
    ini_file.add(bitname_key, &bitname);
    ini_file.add(byte_index_key, &(irs_i32)index_byte);
    ini_file.add(bit_index_key, &(irs_i32)index_bit);
    ini_file.add(value_working_key, &value_working);
    ini_file.add(value_def_key, &value_def);
    ini_file.save();
    ini_file.clear_control();
  }
  return fsuccess;
}
bool config_calibr_t::load(const irs::string& a_filename)
{
  bool fsuccess = true;
  ini_file.set_ini_name(a_filename.c_str());
  ini_file.clear_control();
  add_static_param();
  ini_file.load();
  ini_file.clear_control();
  irs::string in_parametr1_unit_str;
  irs::string in_parametr2_unit_str;
  irs::string in_parametr3_unit_str;
  irs::string out_parametr_unit_str;
  ini_file.set_section("Входной параметр 1");
  ini_file.add("Тип параметра", &in_parametr1_unit_str);
  ini_file.set_section("Входной параметр 2");
  ini_file.add("Тип параметра", &in_parametr2_unit_str);
  ini_file.set_section("Входной параметр 3");
  ini_file.add("Тип параметра", &in_parametr3_unit_str);
  ini_file.set_section("Выходной параметр");
  ini_file.add("Тип параметра", &out_parametr_unit_str);
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
    ini_file.set_section("Опции");
    int sub_diapason_count = 0;
    ini_file.add("Количество поддиапазонов", &(irs_i32)sub_diapason_count);
    int num_param_sub_diapason = 0;
    ini_file.add("Тип поддиапазона", &(irs_i32)num_param_sub_diapason);
    ini_file.load();
    ini_file.clear_control();
    v_sub_diapason_calibr.clear();
    if (num_param_sub_diapason == 1) {
      type_sub_diapason = tsd_parameter1;
    } else {
      type_sub_diapason = tsd_parameter2;
    }
    ini_file.set_section("Опции");
    for (int i = 0; i < sub_diapason_count; i++) {
      sub_diapason_calibr_t sub_diapason_calibr;
      AnsiString diapason_id_key = " д" + IntToStr(i);
      AnsiString index_start_key = "Начальный индекс" + diapason_id_key;
      AnsiString size_key = "Размер" + diapason_id_key;
      AnsiString value_begin_key = "Начальное значение" + diapason_id_key;
      AnsiString value_end_key = "Конечное значение" + diapason_id_key;
      ini_file.add(index_start_key, &(irs_i32)sub_diapason_calibr.index_start);
      ini_file.add(size_key, &(irs_i32)sub_diapason_calibr.size);
      ini_file.add(value_begin_key, &sub_diapason_calibr.value_begin);
      ini_file.add(value_end_key, &sub_diapason_calibr.value_end);
      ini_file.load();
      ini_file.clear_control();
      v_sub_diapason_calibr.push_back(sub_diapason_calibr);
    }
    // загрузка доп.параметров
    ini_file.clear_control();
    ini_file.set_section("Опции");
    int param_ex_count = 0;
    ini_file.add("Количество доп.параметров", &(irs_i32)param_ex_count);
    ini_file.load();
    ini_file.clear_control();
    v_parametr_ex.clear();
    ini_file.set_section("Опции");
    for (int i = 0; i < param_ex_count; i++) {
      parametr_ex_t parametr_ex;
      AnsiString param_ex_id_key = " доп.параметр" + IntToStr(i);
      AnsiString name_key = "Имя параметра" + param_ex_id_key;
      AnsiString unit_key = "Единицы измерения" + param_ex_id_key;
      AnsiString type_variable_key = "Тип параметра" + param_ex_id_key;
      AnsiString index_key = "Индекс байта" + param_ex_id_key;
      AnsiString value_working_key = "Рабочее значение" + param_ex_id_key;
      AnsiString value_default_key = "Значение по умолчанию" + param_ex_id_key;

      AnsiString unit_str;

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
    ini_file.set_section("Опции");
    int bit_type2_count = 0;
    ini_file.add("Количество доп.битов", &(irs_i32)bit_type2_count);
    ini_file.load();
    ini_file.clear_control();
    bit_type2_array.clear();
    ini_file.set_section("Опции");
    for (int i = 0; i < bit_type2_count; i++) {
      bit_type2_pos_t bit_type2_pos;
      AnsiString bit_type2_id_key = " доп.бит" + IntToStr(i);
      AnsiString bitname_key = "Имя бита" + bit_type2_id_key;
      AnsiString byte_index_key = "Индекс байта" + bit_type2_id_key;
      AnsiString bit_index_key = "Индекс бита" + bit_type2_id_key;
      AnsiString value_working_key = "Рабочее значение" + bit_type2_id_key;
      AnsiString value_def_key = "Значение по умолчанию" + bit_type2_id_key;
      AnsiString bitname;
      ini_file.add(bitname_key, &bitname);
      ini_file.add(byte_index_key, &(irs_i32)bit_type2_pos.index_byte);
      ini_file.add(bit_index_key, &(irs_i32)bit_type2_pos.index_bit);
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
void config_calibr_t::add_static_param()
{
  ini_file.set_section("Свойства сетевого подключения");
  ini_file.add("IP-адрес", &ip_adress);
  ini_file.add("Порт",&(irs_i32)port);

  ini_file.set_section("Входной параметр 1");
  ini_file.add("Имя параметра", &in_parametr1.name);
  ini_file.add("Единицы измерения", &in_parametr1.type_variable);

  //ini_file.add("Тип параметра", &in_parametr1.unit);
  ini_file.add("Привязка", &in_parametr1.anchor);
  ini_file.add("Индекс", &(irs_i32)in_parametr1.index);
  ini_file.add("Коэффициент", &in_parametr1.koef);
  ini_file.add("Значение по умолчанию", &in_parametr1.default_val);

  ini_file.set_section("Входной параметр 2");
  ini_file.add("Имя параметра", &in_parametr2.name);
  ini_file.add("Единицы измерения", &in_parametr2.type_variable);
  //ini_file.add("Тип параметра", &in_parametr2.unit);
  ini_file.add("Привязка", &in_parametr2.anchor);
  ini_file.add("Индекс", &(irs_i32)in_parametr2.index);
  ini_file.add("Коэффициент", &in_parametr2.koef);
  ini_file.add("Значение по умолчанию", &in_parametr2.default_val);

  ini_file.set_section("Входной параметр 3");
  ini_file.add("Имя параметра", &in_parametr3.name);
  ini_file.add("Единицы измерения", &in_parametr3.type_variable);
  //ini_file.add("Тип параметра", &in_parametr3.unit);
  ini_file.add("Индекс", &(irs_i32)in_parametr3.index);
  ini_file.add("Коффициент", &in_parametr3.koef);
  ini_file.add("Значение по умолчанию", &in_parametr3.default_val);

  ini_file.set_section("Выходной параметр");
  ini_file.add("Имя параметра", &out_parametr.name);
  ini_file.add("Единицы измерения", &out_parametr.type_variable);
  //ini_file.add("Тип параметра", &out_parametr.unit);
  ini_file.add("Индекс", &(irs_i32)out_parametr.index);
  ini_file.add("Коэффициент шунта", &out_parametr.koef_shunt);

  ini_file.set_section("Опции");
  ini_file.add("Вид измерения", &type_meas);
  ini_file.add("Задержка измерения", &delay_meas);
  ini_file.add("Количество допустимых сбросов ошибок", &count_reset_over_bit);
  /*ini_file.add("Режим расстройки",
    &mismatch_mode);*/
  ini_file.add("Индекс счетчика", &index_work_time);
  //ini_file.add("Индекс коррекции в воронке", &index_pos_offset_eeprom);
  ini_file.add("Индекс воронки", &index_pos_eeprom);
  //ini_file.add("Максимальный размер коррекции", &max_size_correct);

  ini_file.add("Режим расстройки. Индекс байта",
    &bit_pos_mismatch_state.index_byte);
  ini_file.add("Режим расстройки. Индекс бита",
    &bit_pos_mismatch_state.index_bit);
  ini_file.add("Режим коррекции. Индекс байта",
    &bit_pos_correct_mode.index_byte);
  ini_file.add("Режим коррекции. Индекс бита",
    &bit_pos_correct_mode.index_bit);
  ini_file.add("Готовность регулятора. Индекс байта",
    &bit_pos_operating_duty.index_byte);
  ini_file.add("Готовность регулятора. Индекс бита",
    &bit_pos_operating_duty.index_bit);
  ini_file.add("Бит наличия ошибки. Индекс байта",
    &bit_pos_error_bit.index_byte);
  ini_file.add("Бит наличия ошибки. Индекс бита",
    &bit_pos_error_bit.index_bit);
  ini_file.add("Бит сброса ошибки. Индекс байта",
    &bit_pos_reset_over_bit.index_byte);
  ini_file.add("Бит сброса ошибки. Индекс бита",
    &bit_pos_reset_over_bit.index_bit);
  ini_file.add("Бит предустановки фазы. Индекс байта",
    &bit_pos_phase_preset_bit.index_byte);
  ini_file.add("Бит предустановки фазы. Индекс бита",
    &bit_pos_phase_preset_bit.index_bit);

  ini_file.add("Последний активный файл", &active_filename);

  ini_file.set_section("Опции опорного канала");
  ini_file.add("Статус включения", &reference_channel.enabled);
  ini_file.add("IP-адрес", &reference_channel.ip_adress);
  ini_file.add("Порт", &(irs_i32)reference_channel.port);
}

//-------------------------------------------------------------------------
bool correct_map_t::connect(
  irs::mxdata_t *ap_data,
  irs_uarc a_start_index,
  config_calibr_t& a_config_calibr)
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
  irs_uarc koef_array_size = x_count * y_count;
  koef_array.connect(
    a_config_calibr.out_parametr.unit,
    ap_data,
    index,
    koef_array_size);

  return fsuccess;
}

