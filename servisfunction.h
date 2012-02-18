//---------------------------------------------------------------------------
#ifndef servisfunctionH
#define servisfunctionH

#include <Grids.hpp>
#include <inifiles.hpp>
#include <string>
#include <strstream>
#include <algorithm>
#include <math.h>
#include <irsstd.h>
#include <irserror.h>
//#include <mathv.h>
#include <irscberror.h>
#include <mxini.h>
#include "addcolrow.h"
#include <irstable.h>
#include "table.h"
#include "dinamictypes.h"

//#include "newconfig.h"
#include "debugdigitalinterpolator.h"
//  Command bits
//using namespace std;
//---------------------------------------------------------------------------
enum m_copy_data{ON_COPY, OFF_COPY};
enum status_options_t{OFF_PROCESSING, ON_UPDAT, ON_READ};

struct options_optimize_type_mnk_t
{
  int index;
  bool table_raw_data;
  bool table_optimal_data;
  bool table_correct_data;
  bool result_save_file;
  AnsiString name_dir;
  AnsiString file_name;
};

struct options_optimize_type_correct_t
{
  int index;
  bool correct_x;
  AnsiString function_correct_x_str;
  bool correct_y;
  AnsiString function_correct_y_str;
  bool correct_z;
  AnsiString function_correct_z_str;
  bool table_raw_data;
  bool table_optimal_data;
  bool table_correct_data;
  bool result_save_file;
  AnsiString name_dir;
  AnsiString file_name;
};

struct options_calculating_coef_t
{
  int index;
  bool table_raw_data;
  bool table_optimal_data;
  bool table_correct_data;
  bool result_save_file;
  AnsiString name_dir;
  AnsiString file_name;
};
enum type_anchor_t { PARAMETR1, PARAMETR2, PARAMETR3 };
enum number_in_param_t{TWO_PARAM = 2, THREE_PARAM = 3};
struct inf_in_param_t
{
  irs::string type_variable_param1;
  irs::string type_variable_param2;
  irs::string type_variable_param3;
  type_anchor_t type_anchor;
  number_in_param_t number_in_param;
  inf_in_param_t():type_anchor(PARAMETR2), number_in_param(TWO_PARAM)
  {}
};

struct coord_t
{
  int x;
  int y;
  coord_t():x(0), y(0)
  {}
};
struct coord3d_t
{
  int x;
  int y;
  int z;
  coord3d_t():x(0),y(0),z(0)
  {}
};

struct param_cur_cell_t
{
  cell_t col_value;
  cell_t row_value;
  cell_t top_value;
  param_cur_cell_t():col_value(), row_value(), top_value()
  {}
};
class display_table_t
{
public:
  virtual void out_display(
    const vector<irs::matrix_t<cell_t> >& av_data,
    const inf_in_param_t& a_inf_in_param) = 0;
  virtual int col() = 0;
  virtual int row() = 0;
  virtual void set_col(const int a_col) = 0;
  virtual void set_row(const int a_row) = 0;
  virtual void out_display_cell(
    const int a_col_displ, const int a_row_displ, const cell_t a_cell) = 0;
  virtual void out_display_cur_cell(const cell_t a_cell) = 0;
  virtual cell_t in_display_cur_cell() = 0;
  virtual void out_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const cell_t a_cell,
    const irs::string& a_type_variable) = 0;
  virtual void set_edit_mode_table() = 0;
  virtual void reset_edit_mode_table() = 0;
  virtual bool get_edit_mode_table() = 0 ;
  virtual int col_count() const = 0;
  virtual int row_count() const = 0;
};
class table_string_grid_t:public display_table_t
{ 
  private:
    static const int m_precision = 5;
    TStringGrid* const mp_table;
    bool m_edit_mode_table;
  public:
  table_string_grid_t(TStringGrid* const ap_table);
  void out_display(
    const vector<irs::matrix_t<cell_t> >& av_data,
    const inf_in_param_t& a_inf_in_param);
  int col();
  int row();
  void set_col(const int a_col);
  void set_row(const int a_row);
  void out_display_cell(
    const int a_col_displ, const int a_row_displ, const cell_t a_cell);
  void out_display_cur_cell(const cell_t a_cell);
  void out_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const cell_t a_cell,
    const irs::string& a_type_variable);
  cell_t in_display_cur_cell();
  void set_edit_mode_table();
  void reset_edit_mode_table();
  bool get_edit_mode_table();
  int col_count() const;
  int row_count() const;
};

class table_data_t
{
private:
  irs::error_trans_base_t *mp_error_trans;
  const long double m_min_fractional_part_count;
  // константа для обозначения "не чисел"
  const double m_nan;
  // ширина поля в файле для чисел двойной точности
  static const int m_field_width = 30;
  // точность вывода чисел в файл
  static const int m_precision = 10;
  // максимально возможное число столбцов
  static const int m_max_col_count = 50000;
  // максимально возможное число строк
  static const int m_max_row_count = 50000;
  unsigned int m_index;
  display_table_t* mp_display_table;
  AnsiString m_name;
  table_data_t();
  table_data_t(table_data_t&);
  vector<coord_t> mv_coord_special_cells;
  AnsiString m_file_namedir;

  std::vector<irs::matrix_t<cell_t> > mv_table;
  #ifdef  debug_version_digital_interpolator
  // Копия таблицы для обнаружения изменений основной таблицы
  std::vector<irs::matrix_t<cell_t> > mv_fixed_table;
  #endif
  int m_cur_col;
  int m_cur_row;
  int m_cur_table;
  inf_in_param_t m_inf_in_param;
  bool m_table_modifi_stat;
public:
  inline std::vector<irs::matrix_t<cell_t> > read_table() const;
  table_data_t(display_table_t* ap_display_table, AnsiString a_name);
  inline unsigned int index() const;
  inline TStringGrid* pointer_table() const;
  inline AnsiString name() const;
  inline coord_t coord_special_cell(const int a_n) const;
  inline int size_special_cells() const;
  inline void cell_out_display(const int a_col_displ, const int a_row_displ);
  inline irs::string get_cell_value_str_table_data(
    const int a_col_displ, const int a_row_displ);
  inline void cur_cell_out_display();
  void cell_out_display_variable_precision(
    const int a_col_displ,
    const int a_row_displ);
  inline void cur_cell_in_display();
  void create_col_table();
  void create_group_col_table(
    double a_num_begin,
    double a_num_finite,
    double a_step,
    type_step_t a_type_step_col);
  void delete_col_table();
  void delete_row_table();
  void create_row_table();
  void create_group_row_table(
    double a_num_begin,
    double a_num_finite,
    double a_step,
    type_step_t a_type_step_row);

  void create_subtable();
  void delete_subtable();
  void save_table_to_file(const string a_file_name);
  // Сохраняет таблицу в Microsoft Excel (*.csv) файл
  void save_table_to_microsoft_excel_csv_file(const string a_file_name);
  // для сохранения в М-файл Matlab
  void save_table_to_m_file(const irs::string a_file_name) const;
  void load_table_from_file(const string a_file_name);
  // загрузить подтаблицу из файла
  void load_subtable_from_file(const string a_file_name);
  const table_data_t&
    operator=(const table_data_t& a_table_source);
  // очистка всех ячеек таблицы. количество столбцов и строк остается прежним
  void clear_table() const;
  // количество стоблцов и строк привести к дефолтному + очистка всех ячеек
  void clear_table_def();
  // очистка ячеек, не являющихся параметричиская
  void clear_content_table();
  // очистка содержимого столбца
  void clear_conrent_cur_col_table();
  // очистка содержимого строки
  void clear_countnt_cur_row_table();
  // поиск выбросов кривой, входной параметр - допустимый перепад
  void search_pip(const double a_limit);
  void clear_coord_special_cells();
  void set_file_namedir(AnsiString a_file_namedir);
  AnsiString get_file_namedir();
  inline int table_count() const;
  inline int col_count() const;
  inline int row_count() const;
  inline param_cur_cell_t get_param_cell(
    const int a_col_displ, const int a_row_displ);
  //inline int table_count() const;
  // устанавливает номер столбеца активной ячейки
  inline void set_col_table_data(const int a_col);
  // устанавливает номер строки активной ячейки
  inline void set_row_table_data(const int a_row);
  // устанавливает номер таблицы аткивной ячейки
  inline void set_num_table_data(const int a_table);
  // устанавливает столбец в пользовательской таблице
  inline void set_col_displ(const int a_col);
  // устанавливает строку в пользовательской таблице
  inline void set_row_displ(const int a_row);
  // возвращает номер столбца, выбранного в пользовательской таблице
  inline int get_col_displ() const;
  // возвращает номер строки, выбранной в пользовательской таблице
  inline int get_row_displ() const;
  inline int get_col_count_displ() const;
  inline int get_row_count_displ() const;
  // возвращает координаты ячейки в таблице данных
  inline coord3d_t get_coord_cell_table(
    const int a_col_displ, const int a_row_displ) const;
  // возвращает координаты ячейки в таблице дисплея
  inline coord_t get_coord_cell_table_displ(
    const coord3d_t& a_coord_cell) const;

  // возвращает ячейку таблицы
  inline cell_t get_cell_table(
    const int a_col_displ, const int a_row_displ) const;
  // устанавливает значение ячейки в таблице - a_table,
  // стоблбце - a_col, строке - a_row
  inline void set_cell(
    const cell_t a_cell, const int a_table, const int a_col, const int a_row);
  inline void set_cell(
    const cell_t a_cell, const int a_col_displ, const int a_row_displ);
  inline void set_edit_mode_table();
  inline void reset_edit_mode_table();
  inline bool get_edit_mode_table();
  // возвращает true, если координаты (a_col_displ, a_row_displ)
  // относятся к ячейке x
  inline bool get_stat_cell_x(
    const int a_col_displ, const int a_row_displ) const;
  // x,y,z - входные переменные, p(x,y,z) - функция
  void get_points_func_p_of_x_cur_row(
    std::vector<cell_t>& a_p_points,
    std::vector<cell_t>& a_x_points,
    cell_t& a_z,
    int a_row_displ = -1) const;
  void get_points_func_p_of_y_cur_col(
    std::vector<cell_t>& a_p_points,
    std::vector<cell_t>& a_y_points,
    cell_t& a_z,
    int a_col_displ = -1) const;
  void get_points_func_p_of_y_cur_col_cur_table(
    std::vector<cell_t>& a_p_points,
    std::vector<cell_t>& a_y_points,
    cell_t& a_z,
    int a_col_displ = -1,
    int a_row_displ = -1) const;
  illegal_cells_t get_illegal_cells() const;

  void restruct_date_type_1();
  // Возвращает true, если таблица не отличается от загруженной или сохраненной
  // в файл
  inline bool no_modifi();
  inline void set_inf_in_param(const inf_in_param_t& a_inf_in_param);
  // Инвертировать значения ячеек таблицы, не являющихся параметрическими
  void inversion_sign_conrent_table();
  // Модифицировать содержимое ячеек таблицы, не являющихся параметрическими
  // Принимает строку вида Z + 2+X*Y;
  // Z - значение текущей ячейки, X - значение текущего параметра по столбцу,
  // Y - значение текущего параметра по строке.
  // После выполнения функции непараметрические ячейки таблицы будут содержать
  // данные вида Z = Z + 2+X*Y;
  void modifi_content_table(const irs::string& a_str);
private:
  void load_table_from_file(
    number_in_param_t& a_number_in_param,
    const string& a_file_name,
    std::vector<irs::matrix_t<cell_t> >& a_table);
  void concatenate_table_matrix(
    const irs::matrix_t<cell_t>& a_in_table1,
    const irs::matrix_t<cell_t>& a_in_table2,
    irs::matrix_t<cell_t>& a_out_table);
  void concatenate_table(
    const vector<irs::matrix_t<cell_t> >& av_in_table1,
    const vector<irs::matrix_t<cell_t> >& av_in_table2,
    vector<irs::matrix_t<cell_t> >& av_out_table);
};
inline std::vector<irs::matrix_t<cell_t> > table_data_t::read_table() const
  {return mv_table;}
inline unsigned int table_data_t::index() const
  {return m_index;}
inline TStringGrid* table_data_t::pointer_table() const
  {/*return mp_table;*/ return IRS_NULL;}
inline AnsiString table_data_t::name() const
  {return m_name;}
inline coord_t table_data_t::coord_special_cell(const int a_n) const
  {return mv_coord_special_cells[a_n];}
inline int table_data_t::size_special_cells() const
  {return mv_coord_special_cells.size();}
inline void table_data_t::cell_out_display(
  const int a_col_displ, const int a_row_displ)
{
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];
    mp_display_table->out_display_cell(a_col_displ,a_row_displ,cur_cell);
  }
}
inline irs::string table_data_t::get_cell_value_str_table_data(
  const int a_col_displ, const int a_row_displ)
{
  irs::string cell_value_str = "";
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    cell_t cur_cell = mv_table[cur_table][a_col_displ][cur_row];
    if(cur_cell.init) {
      irs::num_to_str(cur_cell.value, &cell_value_str);
    } else {
      cell_value_str = "";
    }
  }
  return cell_value_str;
}
inline void table_data_t::cur_cell_out_display()
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

inline void table_data_t::cur_cell_in_display()
{
  int cur_col = mp_display_table->col();
  int cur_row_displ = mp_display_table->row();
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(cur_row_displ, row_count);
    int cur_table = val.quot;
    int cur_row = val.rem;
    cell_t cur_cell = mp_display_table->in_display_cur_cell();
    bool select_cell_x = (cur_col > 0) && (cur_row == 0);
    bool select_cell_y = (cur_col == 0) && (cur_row > 0);
    if(select_cell_x || select_cell_y){
      for(int i = 0; i < table_count; i++){
        mv_table[i][cur_col][cur_row] = cur_cell;
      }
    }else{
      mv_table[cur_table][cur_col][cur_row] = cur_cell;
    }
  }
}
inline int table_data_t::table_count() const
  {return mv_table.size();}
inline int table_data_t::col_count() const
{
  int col_count = 0;
  if(mv_table.size() > 0)
    col_count = mv_table[0].col_count();
  else
    col_count = 0;
  return col_count;
}
inline int table_data_t::row_count() const
{
  int row_count = 0;
  if(mv_table.size() > 0)
    row_count = mv_table[0].row_count();
  else
    row_count = 0;
  return row_count;
}
inline param_cur_cell_t table_data_t::get_param_cell(
  const int a_col_displ, const int a_row_displ)
{
  int table_count = mv_table.size();
  param_cur_cell_t param_cur_cell;
  if(table_count > 0){
    int row_count =  mv_table[0].row_count();
    div_t div_value = div(a_row_displ, row_count);
    int num_table = div_value.quot;
    int cur_row = div_value.rem;
    param_cur_cell.col_value = mv_table[num_table][a_col_displ][0];
    param_cur_cell.row_value = mv_table[num_table][0][cur_row];   
    param_cur_cell.top_value = mv_table[num_table][0][0];
  }
  return param_cur_cell;
}
/*inline int table_data_t::table_count() const
  {return mv_table.size();}*/
inline void table_data_t::set_col_table_data(const int a_col)
  {m_cur_col = a_col;}
inline void table_data_t::set_row_table_data(const int a_row)
  {m_cur_row = a_row;}
inline void table_data_t::set_num_table_data(const int a_table)
  {m_cur_table = a_table;}
inline void table_data_t::set_col_displ(const int a_col)
  {mp_display_table->set_col(a_col);}
inline void table_data_t::set_row_displ(const int a_row)
  {mp_display_table->set_row(a_row);}
inline int table_data_t::get_col_displ() const
  {return mp_display_table->col();}
inline int table_data_t::get_row_displ() const
  {return mp_display_table->row();}
inline int table_data_t::get_col_count_displ() const
  {return mp_display_table->col_count();}
inline int table_data_t::get_row_count_displ() const
  {return mp_display_table->row_count();}

inline coord3d_t table_data_t::get_coord_cell_table(
  const int a_col_displ, const int a_row_displ) const
{
  coord3d_t coord_cell;
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    coord_cell.z = val.quot;
    coord_cell.y = val.rem;
    coord_cell.x = a_col_displ;
  }
  return coord_cell;
}
inline coord_t table_data_t::get_coord_cell_table_displ(
  const coord3d_t& a_coord_cell) const
{
  coord_t coord_cell_displ;
  coord_cell_displ.x = a_coord_cell.x;
  coord_cell_displ.y = 0;
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    coord_cell_displ.y = row_count*a_coord_cell.z+a_coord_cell.y;
  }
  return coord_cell_displ;
}

inline cell_t table_data_t::get_cell_table(
  const int a_col_displ, const int a_row_displ) const
{
  int table_count = mv_table.size();
  cell_t cell;
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int num_table = val.quot;
    int row_table = val.rem;
    cell = mv_table[num_table][a_col_displ][row_table];
  }
  return cell;
}

inline void table_data_t::set_cell(
  const cell_t a_cell, const int a_table, const int a_col, const int a_row)
{
  mv_table[a_table][a_col][a_row] = a_cell;
}

inline void table_data_t::set_cell(
  const cell_t a_cell, const int a_col_displ, const int a_row_displ)
{
  int table_count = mv_table.size();
  if(table_count > 0){
    int row_count = mv_table[0].row_count();
    div_t val = div(a_row_displ, row_count);
    int num_table = val.quot;
    int row_table = val.rem;
    mv_table[num_table][a_col_displ][row_table] = a_cell;
  }
}

inline bool table_data_t::get_stat_cell_x(
      const int a_col_displ, const int a_row_displ) const
{
  coord3d_t coord_cell = get_coord_cell_table(a_col_displ, a_row_displ);
  bool select_cell_x = (coord_cell.x > 0) && (coord_cell.y == 0);
  return select_cell_x;
}

inline void table_data_t::set_edit_mode_table()
  {mp_display_table->set_edit_mode_table();}
inline void table_data_t::reset_edit_mode_table()
  {mp_display_table->reset_edit_mode_table();}
inline bool table_data_t::get_edit_mode_table()
  {return mp_display_table->get_edit_mode_table();}
inline bool table_data_t::no_modifi()
{
  #ifdef  debug_version_digital_interpolator
  IRS_ASSERT((!m_table_modifi_stat) && (mv_table == mv_fixed_table));
  #endif
  return (!m_table_modifi_stat);
}
inline void table_data_t::set_inf_in_param(const inf_in_param_t& a_inf_in_param)
{
  m_inf_in_param = a_inf_in_param;
}

class table_data_size_t: public irs::table_size_read_only_t
{
private:
  table_data_t* mp_table_data;
  table_data_size_t();
public:
  table_data_size_t(table_data_t* ap_table_data);
  virtual size_type get_col_count() const;
  virtual size_type get_row_count() const;
};

//#define type_log_stream
class log_t
{
private:           
  bool m_error_open_file_log;
  static const int m_field_width_display_time = 15;
  static const int m_field_width_file_date_time = 30;
  #ifdef type_log_stream
  irs::memobuf m_buflog;
  ostream m_log_display;
  #else
  TMemo* mp_memo;
  #endif
  ofstream m_outfile;
  log_t();
public:
  void operator<<(String a_str);
  log_t(TMemo* ap_memo, string a_file_name);
  ~log_t();
};

AnsiString extract_short_filename(const AnsiString& a_filename);
/*Возвращает индекс строки TComboBox, текст которой равен a_text*/
int get_index_row_combo_box_str(
  const TComboBox* const ap_combo_box,
  const AnsiString& a_text); 

class log_message_t: public irs::cbuilder::log_msg_t
{
  log_t* mp_log;
public:
  log_message_t(log_t* ap_log): mp_log(ap_log)
  {}
  virtual void send_msg(const irs::string& a_msg_str)
  {
    (*mp_log) << a_msg_str.c_str();
  }
};

struct parametr1_t
{
  AnsiString name;
  lang_type_t unit;
  AnsiString type_variable;
  bool anchor;
  irs_i32 index;
  long double koef;
  double default_val;
  parametr1_t():
    name(),
    unit(type_none),
    type_variable(),
    anchor(false),
    index(0),
    koef(1),
    default_val(0)
  {}
  parametr1_t(
    const AnsiString a_name,
    const lang_type_t a_unit,
    const a_type_variable,
    const bool anchors,
    const irs_i32 a_index,
    const long double a_koef,
    const double a_default_val):
    name(a_name),
    unit(a_unit),
    type_variable(a_type_variable),
    anchor(anchors),
    index(a_index),
    koef(a_koef),
    default_val(a_default_val)
  {}
  void clear()
  {
    *this = parametr1_t();
  }
};
struct parametr2_t
{
  AnsiString name;
  lang_type_t unit;
  AnsiString type_variable;
  irs_i32 index;
  long double koef;
  double default_val;
  parametr2_t():
    name(),
    unit(type_none),
    type_variable(),
    index(0),
    koef(1),
    default_val(0)
  {}
  parametr2_t(
    const AnsiString a_name,
    const lang_type_t a_unit,
    const a_type_variable,
    const irs_i32 a_index,
    const long double a_koef,
    double a_default_val):
    name(a_name),
    unit(a_unit),
    type_variable(a_type_variable),
    index(a_index),
    koef(a_koef),
    default_val(a_default_val)
  {}
  void clear()
  {
    *this = parametr2_t();
  }
};
struct parametr3_t
{
  AnsiString name;
  lang_type_t unit;
  AnsiString type_variable;
  irs_i32 index;
  long double koef_shunt;
  parametr3_t(
  ):
    name(),
    unit(type_none),
    type_variable(),
    index(0),
    koef_shunt(1)
  {}
  parametr3_t(
    const AnsiString a_name,
    const lang_type_t a_unit,
    const a_type_variable,
    const irs_i32 a_index,
    const long double a_koef_shunt):
    name(a_name),
    unit(a_unit),
    type_variable(a_type_variable),
    index(a_index),
    koef_shunt(a_koef_shunt)
  {}
  void clear()
  {
    *this = parametr3_t();
  }
};
struct parametr_ex_t
{
  AnsiString name;
  lang_type_t unit;          // тип переменной
  AnsiString type_variable; // единицы измерения
  irs_i32 index;            // индекс байта
  double value_working;     // рабочее значение
  double value_default;     // значение по умолчанию
  parametr_ex_t():
    name(),
    unit(type_none),
    type_variable(),
    index(0),
    value_working(0.0),
    value_default(0.0)
  {}
  parametr_ex_t(
    const AnsiString a_name,
    const lang_type_t a_unit,
    const AnsiString a_type_variable,
    const irs_i32 a_index,
    const long double a_koef,
    double a_value_working,
    double a_value_default
  ):
    name(a_name),
    unit(a_unit),
    type_variable(a_type_variable),
    index(a_index),
    value_working(a_value_working),
    value_default(a_value_default)
  {}
  void clear()
  {
    *this = parametr_ex_t();
  }
};
struct bit_type1_pos_t
{
  irs_i32 index_byte;
  irs_i32 index_bit;
  bit_type1_pos_t():
    index_byte(0),
    index_bit(0)
  {}
  bit_type1_pos_t(const irs_i32 a_index_byte, const irs_i32 a_index_bit):
    index_byte(a_index_byte),
    index_bit(a_index_bit)
  {}
  void clear()
  {
    *this = bit_type1_pos_t(); 
  }
};

struct bit_type2_pos_t
{
  irs::string bitname;
  int index_byte;
  int index_bit;
  bool value_working;
  bool value_def;
  bit_type2_pos_t(
  ):
    bitname(),
    index_byte(0),
    index_bit(0),
    value_working(false),
    value_def(false)
  {}
  bit_type2_pos_t(
    const irs::string a_name_str,
    const irs_i32 a_index_byte,
    const irs_i32 a_index_bit,
    const bool a_value_working,
    const bool a_value_def):
    bitname(a_name_str),
    index_byte(a_index_byte),
    index_bit(a_index_bit),
    value_working(a_value_working),
    value_def(a_value_def)
  {}
  void clear()
  {
    *this = bit_type2_pos_t();   
  }
};

struct reference_channel_t
{
  bool enabled;
  String ip_adress;
  irs_u32 port;
  reference_channel_t():
    enabled(false),
    ip_adress(),
    port(5005)
  {
  }
};

enum type_sub_diapason_t{
  tsd_parameter1,
  tsd_parameter2
};

struct sub_diapason_calibr_t
{
  int index_start;
  int size;
  double value_begin;
  double value_end;
  sub_diapason_calibr_t(
  ):
    index_start(0),
    size(0),
    value_begin(0.0),
    value_end(0.0)
  {}
  void clear()
  {
    *this = sub_diapason_calibr_t();           
  }
};

struct temperature_control_config_t
{
  bool enabled;
  irs_u32 index;
  double reference;
  double difference;
  temperature_control_config_t():
    enabled(false),
    index(0),
    reference(65),
    difference(0.5)
  {
  }
};

struct config_calibr_t
{
  String type_meas;
  String ip_adress;
  irs_u32 port;
  parametr1_t in_parametr1;
  parametr1_t in_parametr2;
  parametr2_t in_parametr3;
  parametr3_t out_parametr;
  vector<parametr_ex_t> v_parametr_ex;
  bit_type1_pos_t bit_pos_mismatch_state;
  bit_type1_pos_t bit_pos_correct_mode;
  bit_type1_pos_t bit_pos_operating_duty;
  bit_type1_pos_t bit_pos_error_bit;
  bit_type1_pos_t bit_pos_reset_over_bit;
  bit_type1_pos_t bit_pos_phase_preset_bit;
  vector<bit_type2_pos_t> bit_type2_array;
  irs_u32 index_work_time;
  irs_u32 index_pos_eeprom;
  temperature_control_config_t temperature_control;
  type_sub_diapason_t type_sub_diapason;
  std::vector<sub_diapason_calibr_t> v_sub_diapason_calibr;
  double meas_range_koef;
  irs_u32 delay_meas;
  irs_u32 count_reset_over_bit;
  AnsiString active_filename;
  reference_channel_t reference_channel;
  config_calibr_t();
  void clear();
  bool save(const irs::string& a_filename);
  bool load(const irs::string& a_filename);
private:
  void add_static_param(irs::ini_file_t* ap_ini_file);
};

struct correct_data_t
{
  int map_id;
  int col_count;
  int row_count;
  vector<double> v_col_data;
  vector<double> v_row_data;
  vector<double> koef_array;
};
struct correct_map_t
{
  irs::conn_data_t<irs_u32> map_id;
  irs::conn_data_t<irs_u32> x_count;
  irs::conn_data_t<irs_u32> y_count;
  dynamic_array_data_t x_points;
  dynamic_array_data_t y_points;
  dynamic_array_data_t koef_array;
  correct_map_t(
  ):
    map_id(),
    x_count(),
    y_count()
  {
  }
  bool connect(
    irs::mxdata_t *ap_data,
    irs_uarc a_start_index,
    config_calibr_t& a_config_calibr);
};

// Универсальная функция перевода чисел в текст
/*template<class T>
inline AnsiString NumberToStr(
  const T a_num,
  const int a_precision = -1,
  const num_mode_t a_num_mode = num_mode_normal)
{
  irs::string str_value = a_num;
  AnsiString astring_value = str_value.c_str();
  return astring_value;
}
// Универсальная функция перевода текста в число
template<class T>
inline bool StrToNumber(const AnsiString& a_str, T& a_number)
{
  irs::string str = a_str.c_str();
  return str.to_number(a_number);
}
  */



#endif
