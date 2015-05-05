//---------------------------------------------------------------------------
#ifndef tableH
#define tableH

#include <irstable.h>
struct coord_cell_t
{
  int col;
  int row;
  coord_cell_t():col(0), row(0)
  {
  }
  bool operator== (coord_cell_t a_coord_cell)
  {
    if((col == a_coord_cell.col) && (row == a_coord_cell.row))
      return true;
    else
      return false;
  }
  bool operator!= (coord_cell_t a_coord_cell)
  {
    if((col != a_coord_cell.col) && (row != a_coord_cell.row))
      return true;
    else
      return false;
  }
};

class cell_double_t
{
private:
  static const double m_epsilon;
  double m_value;
  bool m_init;
public:
  cell_double_t();
  cell_double_t(double a_value, bool a_init);
  bool init();
  double value();
  irs::string str_value(
    const int a_precision = 5,
    const irs::num_mode_t a_num_mode = irs::num_mode_general,
    const irs::num_base_t a_num_base = irs::num_base_dec);
  const cell_double_t& operator=(const cell_double_t& a_cell);
  void operator=(const double& a_value);
  void operator=(const irs::string& a_str_value);
  bool operator==(const cell_double_t& a_cell) const;
  bool operator!=(const cell_double_t& a_cell) const;
  bool operator<(const cell_double_t& a_cell) const;
};

struct cell_t
{
  static const double m_epsilon;
  double value;
  bool init;
  cell_t():value(0.0), init(false)
  {}
  cell_t(double a_value, bool a_init
  ):
    value(a_value),
    init(a_init)
  {}
  const cell_t& operator=(const cell_t& a_cell)
  {
    value = a_cell.value;
    init = a_cell.init;
    return *this;
  }
  bool operator==(const cell_t& a_cell) const
  {
    if(init != a_cell.init)
      return false;
    else if((init == true) &&
      (irs::compare_value(value, a_cell.value, m_epsilon) == irs::equals_value))
      return true;
    else if (init == false)
      return true;
    else
      return false;
  }
  bool operator!=(const cell_t& a_cell) const
  {
    return !operator==(a_cell);
  }
  bool operator<(const cell_t& a_cell) const
  {
    if((init == true) && (a_cell.init == true) &&
      (irs::compare_value(value, a_cell.value, m_epsilon)
        == irs::less_than_value)){
      return true;
    }else{
      return false;
    }
  }
};

// Тип перехода к следующему элементу
enum type_jump_next_elem_t{
  HORIZONTAL_DOWN,
  HORIZONTAL_DOWN_SMOOTH,
  HORIZONTAL_UP,
  HORIZONTAL_UP_SMOOTH,
  VERTICAL_FORWARD,
  VERTICAL_FORWARD_SMOOTH,
  VERTICAL_BACK,
  VERTICAL_BACK_SMOOTH
};
irs::string_t type_jump_next_elem_to_str(
  const type_jump_next_elem_t a_type_jump_next_elem);
type_jump_next_elem_t str_to_type_jump_next_elem(
  const irs::string_t& a_type_jump_next_elem_str);

struct illegal_cells_t
{
  vector<coord_cell_t> cells;
  vector<int> cols;
  vector<int> rows;
  illegal_cells_t(
  ):
    cells(),
    cols(),
    rows()
  {
  }
};
class manager_traffic_cell_t
{
private:
  irs::table_size_read_only_t* mp_table;
  type_jump_next_elem_t m_type_jump_next_elem;
  coord_cell_t m_current_cell;
  coord_cell_t m_start_cell;
  int min_col;
  int min_row;
  int max_col;
  int max_row;
  illegal_cells_t m_illegal_cells;
  manager_traffic_cell_t();
  enum type_border_table_t{TBT_DEFAULT, TBT_USER};
  type_border_table_t m_type_min_col;
  type_border_table_t m_type_min_row;
  type_border_table_t m_type_max_col;
  type_border_table_t m_type_max_row;
public:
  manager_traffic_cell_t(irs::table_size_read_only_t* ap_table);
  inline void set_type_traffic(
    const type_jump_next_elem_t a_type_jump_next_elem);
  inline void set_current_cell(
    const unsigned int a_col, const unsigned int a_row);
  // Установка типа движения
  void set_traffic_smooth();
  void unset_traffic_smooth();
  inline bool next_cell();
  inline coord_cell_t get_coord_cell();
  inline void set_illegal_cell(const illegal_cells_t& a_illegal_cells);
  inline void set_min_col(const unsigned int a_col);
  inline void unset_min_col();
  inline void set_min_row(const unsigned int a_row);
  inline void unset_min_row();
  inline void set_max_col(const unsigned int a_col);
  inline void unset_max_col();
  inline void set_max_row(const unsigned int a_row);
  inline void unset_max_row();
  // Возвращает оставшееся количество ячеек относительно текущей
  // и до конца таблицы
  int get_cell_count_end();
private:
  void init_inf_table();
  // По горизонтали вниз, обычный переход
  bool next_cell_horizontal_down();
  // Плавный переход
  bool next_cell_horizontal_down_smooth();
  // По горизонтали вверх, обычный переход
  bool next_cell_horizontal_up();
  // Плавный переход
  bool next_cell_horizontal_up_smooth();
  // По вертикали вниз, обычный переход
  bool next_cell_vertical_forward();
  // Плавный переход
  bool next_cell_vertical_forward_smooth();
  // По вертикали вверх, обычный переход
  bool next_cell_vertical_back();
  // Плавный переход
  bool next_cell_vertical_back_smooth();
  // Проверка на запрещенную ячейку
  bool illegal_cell(const coord_cell_t a_cell);
};
inline void manager_traffic_cell_t::set_type_traffic(
  const type_jump_next_elem_t a_type_jump_next_elem)
{
  m_type_jump_next_elem = a_type_jump_next_elem;
}
inline void manager_traffic_cell_t::set_current_cell(
  const unsigned int a_col, const unsigned int a_row)
{
  m_current_cell.col = a_col;
  m_current_cell.row = a_row;
}
inline bool manager_traffic_cell_t::next_cell()
{
  bool next_cell_successfully = false;
  init_inf_table();
  switch(m_type_jump_next_elem)
  {
    case HORIZONTAL_DOWN:{
      next_cell_successfully = next_cell_horizontal_down();
    } break;
    case HORIZONTAL_DOWN_SMOOTH:{
      next_cell_successfully = next_cell_horizontal_down_smooth();
    } break;
    case HORIZONTAL_UP:{
      next_cell_successfully = next_cell_horizontal_up();
    } break;
    case HORIZONTAL_UP_SMOOTH:{
      next_cell_successfully = next_cell_horizontal_up_smooth();
    } break;
    case VERTICAL_FORWARD:{
      next_cell_successfully = next_cell_vertical_forward();
    } break;
    case VERTICAL_FORWARD_SMOOTH:{
      next_cell_successfully = next_cell_vertical_forward_smooth();
    } break;
    case VERTICAL_BACK:{
      next_cell_successfully = next_cell_vertical_back();
    } break;
    case VERTICAL_BACK_SMOOTH:{
      next_cell_successfully = next_cell_vertical_back_smooth();
    } break;
  }
  return next_cell_successfully;
}
inline coord_cell_t manager_traffic_cell_t::get_coord_cell()
{
  return m_current_cell;
}
inline void manager_traffic_cell_t::set_illegal_cell(
  const illegal_cells_t& a_illegal_cells)
{
  m_illegal_cells = a_illegal_cells;
}
inline void manager_traffic_cell_t::set_min_col(const unsigned int a_col)
{
  min_col = a_col;
  m_type_min_col = TBT_USER;
}
inline void manager_traffic_cell_t::unset_min_col()
{
  m_type_min_col = TBT_DEFAULT;
}
inline void manager_traffic_cell_t::set_min_row(const unsigned int a_row)
{
  min_row = a_row;
  m_type_min_row = TBT_USER;
}
inline void manager_traffic_cell_t::unset_min_row()
{
  m_type_min_row = TBT_DEFAULT;
}
inline void manager_traffic_cell_t::set_max_col(const unsigned int a_col)
{
  max_col = a_col;
  m_type_max_col = TBT_USER;
}
inline void manager_traffic_cell_t::unset_max_col()
{
  m_type_max_col = TBT_DEFAULT;
}
inline void manager_traffic_cell_t::set_max_row(const unsigned int a_row)
{
  max_row = a_row;
  m_type_max_row = TBT_USER;
}
inline void manager_traffic_cell_t::unset_max_row()
{
  m_type_max_row = TBT_DEFAULT;
}

class table_display_t: public irs::table_size_t
{
public:
  virtual void add_event(
    const irs::string& a_event_name, mxfact_event_t *ap_event) = 0;
  virtual void set_col(const int a_col) = 0;
  virtual void set_row(const int a_row) = 0;
  virtual size_type get_col() = 0;
  virtual size_type get_row() = 0;
  virtual void read_cell(
    const size_type a_col,
    const size_type a_row,
    const irs::string* ap_cell) const = 0;
  virtual void write_cell(
    const size_type a_col,
    const size_type a_row,
    const irs::string& a_cell) = 0;
};

#endif
