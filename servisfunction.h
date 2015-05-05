//---------------------------------------------------------------------------
#ifndef servisfunctionH
#define servisfunctionH

#include <irsdefs.h>

#include <Grids.hpp>
#include <inifiles.hpp>
#include <string>
#include <strstream>
#include <algorithm>
#include <math.h>
#include <irsstd.h>
#include <irserror.h>
#include <irscberror.h>
#include <irssysutils.h>
#include <mxini.h>
#include <irsalg.h>
#include "addcolrow.h"
#include <irstable.h>
#include <tstlan5lib.h>
//#include <irsdevices.h>
#include "table.h"
#include "dinamictypes.h"
#include "debugdigitalinterpolator.h"
#include "connectionlog.h"

#include <irsfinal.h>
//  Command bits
//using namespace std;
//---------------------------------------------------------------------------

template<class N>
String num_to_cbstr(const N& a_num, const locale& a_loc = irs::loc().get())
{
  typename irs::base_str_type<String>::type base_str;
  number_to_string(a_num, &base_str, a_loc);
  return irs::str_conv<String>(base_str);
}

enum m_copy_data{ON_COPY, OFF_COPY};
enum status_options_t{OFF_PROCESSING, ON_UPDAT, ON_READ};

struct options_optimize_type_mnk_t
{
  int index;
  bool table_raw_data;
  bool table_optimal_data;
  bool table_correct_data;
  bool result_save_file;
  String name_dir;
  String file_name;
};

struct options_optimize_type_correct_t
{
  int index;
  bool correct_x;
  String function_correct_x_str;
  bool correct_y;
  String function_correct_y_str;
  bool correct_z;
  String function_correct_z_str;
  bool table_raw_data;
  bool table_optimal_data;
  bool table_correct_data;
  bool result_save_file;
  String name_dir;
  String file_name;
};

struct options_calculating_coef_t
{
  int index;
  bool table_raw_data;
  bool table_optimal_data;
  bool table_correct_data;
  bool result_save_file;
  String name_dir;
  String file_name;
};
enum type_anchor_t { PARAMETR1, PARAMETR2, PARAMETR3 };
enum number_in_param_t{TWO_PARAM = 2, THREE_PARAM = 3};
struct inf_in_param_t
{
  typedef irs::string_t string_type;
  string_type type_variable_param1;
  string_type type_variable_param2;
  string_type type_variable_param3;
  type_anchor_t type_anchor;
  number_in_param_t number_in_param;
  inf_in_param_t():
    type_anchor(PARAMETR2),
    number_in_param(TWO_PARAM)
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
  typedef irs::string_t string_type;
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
    const string_type& a_type_variable) = 0;
  virtual string_type get_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const cell_t a_cell,
    const string_type& a_type_variable) = 0;
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
    const string_type& a_type_variable);
  string_type get_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const cell_t a_cell,
    const string_type& a_type_variable);
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
  typedef std::size_t size_type;
  typedef irs::char_t char_type;
  typedef irs::string_t string_type;
  typedef basic_fstream<char_type, char_traits<char_type> > ofstream_type;
  irs::error_trans_base_t *mp_error_trans;
  const long double m_min_fractional_part_count;
  // константа для обозначения "не чисел"
  const double m_nan;
  // ширина поля в файле для чисел двойной точности
  static const int m_field_width = 30;
  // точность вывода чисел в файл
  static const int m_precision = 15;
  // максимально возможное число столбцов
  static const int m_max_col_count = 50000;
  // максимально возможное число строк
  static const int m_max_row_count = 50000;
  unsigned int m_index;
  display_table_t* mp_display_table;
  String m_name;
  table_data_t();
  table_data_t(table_data_t&);
  vector<coord_t> mv_coord_special_cells;
  String m_file_namedir;

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
  table_data_t(display_table_t* ap_display_table, String a_name);
  inline unsigned int index() const;
  inline TStringGrid* pointer_table() const;
  inline String name() const;
  inline coord_t coord_special_cell(const int a_n) const;
  inline int size_special_cells() const;
  inline void cell_out_display(const int a_col_displ, const int a_row_displ);
  inline string_type get_cell_value_str_table_data(
    const int a_col_displ, const int a_row_displ);
  inline void cur_cell_out_display();
  void cell_out_display_variable_precision(
    const int a_col_displ,
    const int a_row_displ);
  string_type get_cell_display_variable_precision(
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
  void save_table_to_file(const string_type a_file_name);
  // Сохраняет таблицу в Microsoft Excel (*.csv) файл
  void save_table_to_microsoft_excel_csv_file(const string_type a_file_name);
  // для сохранения в М-файл Matlab
  void save_table_to_m_file(const string_type a_file_name) const;
  void load_table_from_file(const string_type a_file_name);
  // загрузить подтаблицу из файла
  void load_subtable_from_file(const string_type& a_file_name);
  const table_data_t&
    operator=(const table_data_t& a_table_source);
  // очистка всех ячеек таблицы. количество столбцов и строк остается прежним
  void clear_table();
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
  void set_file_namedir(String a_file_namedir);
  String get_file_namedir();
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
  void modifi_content_table(const string_type& a_str);
private:
  void load_table_from_file(
    number_in_param_t& a_number_in_param,
    const string_type& a_file_name,
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
inline String table_data_t::name() const
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
inline table_data_t::string_type
table_data_t::get_cell_value_str_table_data(
  const int a_col_displ, const int a_row_displ)
{
  string_type cell_value_str;
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
      cell_value_str.clear();
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
    const irs::matrix_t<cell_t>& matrix = mv_table[num_table];
    //cell = matrix[a_col_displ][row_table];
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
  typedef irs::char_t char_type;
  typedef irs::string_t string_type;
  typedef basic_fstream<char_type, char_traits<char_type> > ofstream_type;
  typedef irs::ostringstream_t ostringstream_type;
  bool m_error_open_file_log;
  static const int m_field_width_display_time = 15;
  static const int m_field_width_file_date_time = 30;
  #ifdef type_log_stream
  irs::memobuf m_buflog;
  ostream m_log_display;
  #else
  TMemo* mp_memo;
  #endif
  ofstream_type m_outfile;
  log_t();
public:
  void operator<<(String a_str);
  log_t(TMemo* ap_memo, string_type a_file_name);
  ~log_t();
};

String extract_short_filename(const String& a_filename);
/*Возвращает индекс строки TComboBox, текст которой равен a_text*/
int get_index_row_combo_box_str(
  const TComboBox* const ap_combo_box,
  const String& a_text);

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
  String name;
  lang_type_t unit;
  String type_variable;
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
    const String a_name,
    const lang_type_t a_unit,
    const String a_type_variable,
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
  String name;
  lang_type_t unit;
  String type_variable;
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
    const String a_name,
    const lang_type_t a_unit,
    const String a_type_variable,
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
  String name;
  lang_type_t unit;
  String type_variable;
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
    const String a_name,
    const lang_type_t a_unit,
    const String a_type_variable,
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
  String name;
  lang_type_t unit;          // тип переменной
  String type_variable; // единицы измерения
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
    const String a_name,
    const lang_type_t a_unit,
    const String a_type_variable,
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
  typedef irs::string_t string_type;
  string_type bitname;
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
    const string_type a_name_str,
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

struct out_param_config_for_measurement_t
{
  bool consider_out_param;
  bool out_param_filter_enabled;
  double filter_sampling_time;
  irs_u32 filter_point_count;
  out_param_config_for_measurement_t():
    consider_out_param(true),
    out_param_filter_enabled(true),
    filter_sampling_time(0.1),
    filter_point_count(100)
  {
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

struct out_param_control_config_t
{ 
  bool enabled;
  double max_relative_difference;
  double time;
  out_param_control_config_t():
    enabled(false),
    max_relative_difference(0.00003), 
    time(15)
  {
  }
};

struct config_calibr_t
{
  typedef irs::string_t string_type;
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
  out_param_config_for_measurement_t out_param_config_for_measurement;
  out_param_control_config_t out_param_control_config;
  temperature_control_config_t temperature_control;
  type_sub_diapason_t type_sub_diapason;
  std::vector<sub_diapason_calibr_t> v_sub_diapason_calibr;
  double meas_range_koef;
  irs_u32 delay_meas;
  irs_u32 count_reset_over_bit;
  String active_filename;
  reference_channel_t reference_channel;
  config_calibr_t();
  void clear();
  bool save(const string_type& a_filename);
  bool load(const string_type& a_filename);
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

class param_filter_t
{
public:
  typedef std::size_t size_type;
public:
  param_filter_t(double a_sampling_time = 0.1, size_type a_num_of_points = 100);
  void set_sampling_time(double a_sampling_time);
  void resize(size_type a_point_count);
  void add(double a_value);
  double get_value() const;
  void restart();
  void stop();
  bool started() const;
  void tick();
private:
  irs::handle_t<irs::loop_timer_t> m_sample_timer;
  irs::sko_calc_t<double, double> m_sko_calc;
  bool m_started;
  double m_last_value;
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


class file_name_service_t
{
public:
  file_name_service_t();
  String get_config_ext() const;
  String get_config_dir() const;
  String get_multimeter_config_ext() const;
  String get_multimeter_config_dir() const;
  String make_config_full_file_name(String a_config_name)  const;
  String make_device_config_full_file_name(String a_config_name) const;
  String make_ref_device_config_full_file_name(String a_config_name) const;
  String make_device_grid_config_full_name(String a_config_name) const;
  String make_ref_device_grid_config_full_name(String a_config_name) const;
  String get_device_options_section() const;
  String get_config_name(const String& a_full_file_name) const;
  String make_multimeter_config_full_file_name(String a_config_name)  const;
  void create_config_dir();
private:
  //рабочий каталог программы
  const String m_path_prog;
  //расширение файла конфигурации процесса калибровки
  const String m_default_ext;
  const String m_multimeter_config_ext;
  //имя файла по умолчанию конфигурации процесса калибровки
  const String m_default_filename;
  //имя каталога программы для хранения конфгураций
  const String m_foldername_conf;
  // Имя каталога для конфигураций мультиметров
  const String m_multimeter_foldername_conf;
  const String m_device_default_ext;
  const String m_device_grid_options_default_ext;
  const String m_device_suffix;
  const String m_ref_device_default_ext;
  const String m_ref_device_suffix;

  const String m_device_options_section;
};

class vars_ini_file_t
{
public:
  typedef irs_size_t size_type;
  typedef irs::string_t string_type;

  vars_ini_file_t(const string_type& a_file_name);
  size_type load_row_count();
  irs::tstlan::type_t load_type(size_type a_row_index);
private:
  const string_type m_section_prefix;
  const string_type m_section_name;
  const string_type m_section_full_name;
  const string_type m_name_row_count;
  const string_type m_type_column_prefix;
  TEncoding* mp_encoding;
  irs::handle_t<TCustomIniFile> mp_ini_file;
};

class netconn_t
{
public:
  typedef irs_size_t size_type;
  typedef irs::string_t string_type;
  typedef irs::tstlan::type_t type_type;
  struct item_t {
    type_type type;
    size_type index;
    size_type conn_index;
    size_type bit_index;
    item_t():
      type(irs::tstlan::type_unknown),
      index(0),
      conn_index(0),
      bit_index(0)
    {
    }
  }; //item_t

  static const int bit_in_byte = 8;
  netconn_t();
  template <class T>
  T read_value(size_type a_index) const;
  template <class T>
  void write_value(size_type a_index, T a_var);
  int connect(irs::mxdata_t* ap_data, const string_type& a_file_name);
private:
  void add_conn(vector<irs::bit_data_t>& a_vec, int a_var_index,
    int& a_conn_index, int& a_bit_index);

  template <class T>
  void add_conn(vector<irs::conn_data_t<T> >& a_vec, int a_var_index,
    int& a_conn_index, int& a_bit_index, type_type a_type)
  {
    if (a_bit_index != 0) {
      a_bit_index = 0;
      a_conn_index++;
    }
    if (a_conn_index + sizeof(T) <= mp_data->size()) {
      items[a_var_index].type = a_type;
      items[a_var_index].index = a_vec.size();
      items[a_var_index].conn_index = a_conn_index;
      items[a_var_index].bit_index = 0;
      a_vec.push_back(irs::conn_data_t<T>());
      a_conn_index = a_vec.back().connect(mp_data, a_conn_index);

    } else {
      items[a_var_index].type = irs::tstlan::type_unknown;
      items[a_var_index].index = 0;
      items[a_var_index].conn_index = 0;
      items[a_var_index].bit_index = 0;
    }
  }

  vector<irs::bit_data_t> bit_vec;
  vector<irs::conn_data_t<bool> > bool_vec;
  vector<irs::conn_data_t<irs_i8> > i8_vec;
  vector<irs::conn_data_t<irs_u8> > u8_vec;
  vector<irs::conn_data_t<irs_i16> > i16_vec;
  vector<irs::conn_data_t<irs_u16> > u16_vec;
  vector<irs::conn_data_t<irs_i32> > i32_vec;
  vector<irs::conn_data_t<irs_u32> > u32_vec;
  vector<irs::conn_data_t<irs_i64> > i64_vec;
  vector<irs::conn_data_t<irs_u64> > u64_vec;
  vector<irs::conn_data_t<float> > float_vec;
  vector<irs::conn_data_t<double> > double_vec;
  vector<irs::conn_data_t<long double> > long_double_vec;

  vector<item_t> items;
  irs::mxdata_t* mp_data;
}; //netconn_t

template <class T>
T netconn_t::read_value(size_type a_index) const
{
  T val = 0;
  netconn_t::item_t item = items[a_index];
  switch (item.type) {
    case type_bit: {
      val = static_cast<T>(bit_vec[item.index]);
    } break;
    case type_bool: {
      val = static_cast<T>(bool_vec[item.index]);
    } break;
    case type_i8: {
      val = static_cast<T>(i8_vec[item.index]);
    } break;
    case type_u8: {
      val = static_cast<T>(u8_vec[item.index]);
    } break;
    case type_i16: {
      val = static_cast<T>(i16_vec[item.index]);
    } break;
    case type_u16: {
      val = static_cast<T>(u16_vec[item.index]);
    } break;
    case type_i32: {
      val = static_cast<T>(i32_vec[item.index]);
    } break;
    case type_u32: {
      val = static_cast<T>(u32_vec[item.index]);
    } break;
    case type_i64: {
      val = static_cast<T>(i64_vec[item.index]);
    } break;
    case type_u64: {
      val = static_cast<T>(u64_vec[item.index]);
    } break;
    case type_float: {
      val = static_cast<T>(float_vec[item.index]);
    } break;
    case type_double: {
      val = static_cast<T>(double_vec[item.index]);
    } break;
    case type_long_double: {
      val = static_cast<T>(long_double_vec[item.index]);
    } break;
  }
  return val;
}

template <class T>
void netconn_t::write_value(size_type a_index, T a_value)
{
  item_t item = items[a_index];
  switch (item.type) {
    case type_bit: {
      if (a_value != 0) {
        m_netconn.bit_vec[item.index] = 1;
      } else {
        m_netconn.bit_vec[item.index] = 0;
      }
    } break;
    case type_bool: {
      m_netconn.bool_vec[item.index] = static_cast<bool>(a_value);
    } break;
    case type_i8: {
      m_netconn.i8_vec[item.index] = static_cast<irs_i8>(a_value);
    } break;
    case type_u8: {
      m_netconn.u8_vec[item.index] = static_cast<irs_u8>(a_value);
    } break;
    case type_i16: {
      m_netconn.i16_vec[item.index] = static_cast<irs_i16>(a_value);
    } break;
    case type_u16: {
      m_netconn.u16_vec[item.index] = static_cast<irs_u16>(a_value);
    } break;
    case type_i32: {
      m_netconn.i32_vec[item.index] = static_cast<irs_i32>(a_value);
    } break;
    case type_u32: {
      m_netconn.u32_vec[item.index] = static_cast<irs_u32>(a_value);
    } break;
    case type_i64: {
      m_netconn.i64_vec[item.index] = static_cast<irs_i64>(a_value);
    } break;
    case type_u64: {
      m_netconn.u64_vec[item.index] = static_cast<irs_u64>(a_value);
    } break;
    case type_float: {
      m_netconn.float_vec[item.index] = static_cast<float>(a_value);
    } break;
    case type_double: {
      m_netconn.double_vec[item.index] = static_cast<double>(a_value);
    } break;
    case type_long_double: {
      m_netconn.long_double_vec[item.index] = static_cast<long double>(a_value);
    } break;
  }
}

struct data_map_t
{
private:
  bool connected;
public:
  dynamic_conn_data_t x_in;
  dynamic_conn_data_t y_in;
  dynamic_conn_data_t q_in;
  dynamic_conn_data_t y_out;
  irs::conn_data_t<irs_u32> work_time;
  irs::conn_data_t<irs_u32> status;
  irs::conn_data_t<float> temperature;
  irs::bit_data_t mismatch_state_bit;
  irs::bit_data_t correct_mode_bit;
  irs::bit_data_t operating_duty_bit;
  irs::bit_data_t error_bit;
  irs::bit_data_t reset_over_bit;
  irs::bit_data_t phase_preset_bit;
  vector<dynamic_conn_data_t> v_extra_param;
  vector<irs::bit_data_t> v_extra_bit;
  data_map_t():
    connected(false),
    x_in(),
    y_in(),
    q_in(),
    y_out(),
    work_time(),
    status(),
    temperature(),
    mismatch_state_bit(),
    correct_mode_bit(),
    operating_duty_bit(),
    error_bit(),
    reset_over_bit(),
    phase_preset_bit(),
    v_extra_param(),
    v_extra_bit()
  {
  }
  bool is_connected() const
  {
    return connected;
  }
  void connect(irs::mxdata_t *ap_data,
    config_calibr_t& a_config_calibr)
  {
    connected = (ap_data != NULL);
    x_in.connect(
      a_config_calibr.in_parametr1.unit,
      ap_data,
      a_config_calibr.in_parametr1.index);

    y_in.connect(
      a_config_calibr.in_parametr2.unit,
      ap_data,
      a_config_calibr.in_parametr2.index);

    if(a_config_calibr.in_parametr1.anchor == false
      && a_config_calibr.in_parametr2.anchor == false){
      q_in.connect(
        a_config_calibr.in_parametr3.unit,
        ap_data,
        a_config_calibr.in_parametr3.index);
    }
    y_out.connect(
      a_config_calibr.out_parametr.unit,
      ap_data,
      a_config_calibr.out_parametr.index);

    int extra_param_count = a_config_calibr.v_parametr_ex.size();
    v_extra_param.resize(extra_param_count);
    for (int i = 0; i < extra_param_count; i++) {
      v_extra_param[i].connect(
        a_config_calibr.v_parametr_ex[i].unit,
        ap_data,
        a_config_calibr.v_parametr_ex[i].index);
    }

    work_time.connect(ap_data,
      a_config_calibr.index_work_time);
    if (a_config_calibr.temperature_control.enabled) {
      temperature.connect(ap_data, a_config_calibr.temperature_control.index);
    }
    mismatch_state_bit.connect(
      ap_data,
      a_config_calibr.bit_pos_mismatch_state.index_byte,
      a_config_calibr.bit_pos_mismatch_state.index_bit);
    correct_mode_bit.connect(
      ap_data,
      a_config_calibr.bit_pos_correct_mode.index_byte,
      a_config_calibr.bit_pos_correct_mode.index_bit);
    operating_duty_bit.connect(
      ap_data,
      a_config_calibr.bit_pos_operating_duty.index_byte,
      a_config_calibr.bit_pos_operating_duty.index_bit);
    error_bit.connect(
      ap_data,
      a_config_calibr.bit_pos_error_bit.index_byte,
      a_config_calibr.bit_pos_error_bit.index_bit);
    reset_over_bit.connect(
      ap_data,
      a_config_calibr.bit_pos_reset_over_bit.index_byte,
      a_config_calibr.bit_pos_reset_over_bit.index_bit);
    phase_preset_bit.connect(
      ap_data,
      a_config_calibr.bit_pos_phase_preset_bit.index_byte,
      a_config_calibr.bit_pos_phase_preset_bit.index_bit);

    int extra_bit_count = a_config_calibr.bit_type2_array.size();
    v_extra_bit.resize(extra_bit_count);
    for (int i = 0; i < extra_bit_count; i++) {
      v_extra_bit[i].connect(
        ap_data,
        a_config_calibr.bit_type2_array[i].index_byte,
        a_config_calibr.bit_type2_array[i].index_bit);
    }
  }
  void reset_connection()
  {
    connected = false;
  }
};

struct device_options_t
{
  typedef irs::string_t string_type;
  string_type type;
  bool enabled;
  device_options_t():
    type(),
    enabled(false)
  {
    vector<string_type> type_list;
    irs::mxdata_assembly_types()->enum_types(&type_list);
    if (!type_list.empty()) {
      type = type_list.front();
    }
  }
};

class device2_t
{
public:
  typedef irs::string_t string_type;
  device2_t(irs::chart_window_t* ap_chart,
    file_name_service_t* ap_file_name_service);
  ~device2_t();
  //void set_configuration(config_calibr_t a_config_calibr);
  void enable(config_calibr_t a_config_calibr);
  void disable();
  String get_type() const;
  data_map_t* get_data();
  irs::mxdata_t* get_mxdata();
  bool created() const;
  bool enabled() const;
  bool connected() const;
  void load(const String& a_device_file_name);
  void create_config_from_old(const String& a_device_file_name,
    const String& a_type,
    const String& a_ip_address,
    const irs_u32 a_port);
  void change_type(const String& a_device_file_name,
    const String& a_type);
  void show_options();
  void show_tstlan();
  void show_connection_log();
  void reset();
  void tick();
private:
  void reset(const string_type& a_device_file_name,
    const device_options_t& a_device);
  irs::handle_t<irs::tstlan4_base_t> make_tstlan4lib();

  irs::chart_window_t* mp_chart;
  file_name_service_t* mp_file_name_service;
  config_calibr_t m_config_calibr;
  string_type m_type;
  irs::handle_t<irs::tstlan4_base_t> mp_tstlan4lib;
  irs::handle_t<irs::mxdata_assembly_t> mp_mxdata_assembly;
  irs::handle_t<TConnectionLogForm> mp_connection_log;
  data_map_t m_data_map;
};

#endif
