
#include "table.h"

const double cell_t::m_epsilon = 1.e-15;

const irs::string_t str_horizontal_down = irst("по горизонтали, вниз");
const irs::string_t str_horizontal_down_smooth =
  irst("по горизонтали, вниз, плавно");
const irs::string_t str_horizontal_up = irst("по горизонтали, вверх");
const irs::string_t str_horizontal_up_smooth =
  irst("по горизонтали, вверх, плавно");
const irs::string_t str_vertical_forward = irst("по вертикали, вперед");
const irs::string_t str_vertical_forward_smooth =
  irst("по вертикали, вперед, плавно");
const irs::string_t str_vertical_back = irst("по вертикали, назад");
const irs::string_t str_vertical_back_smooth =
  irst("по вертикали, назад, плавно");

irs::string_t type_jump_next_elem_to_str(
  const type_jump_next_elem_t a_type_jump_next_elem)
{
  irs::string_t type_jump_next_elem_str;
  switch(a_type_jump_next_elem){
    case HORIZONTAL_DOWN:{
      type_jump_next_elem_str = str_horizontal_down;
    } break;
    case HORIZONTAL_DOWN_SMOOTH:{
      type_jump_next_elem_str = str_horizontal_down_smooth;
    } break;
    case HORIZONTAL_UP:{
      type_jump_next_elem_str = str_horizontal_up;
    } break;
    case HORIZONTAL_UP_SMOOTH:{
      type_jump_next_elem_str = str_horizontal_up_smooth;
    } break;
    case VERTICAL_FORWARD:{
      type_jump_next_elem_str = str_vertical_forward;
    } break;
    case VERTICAL_FORWARD_SMOOTH:{
      type_jump_next_elem_str = str_vertical_forward_smooth;
    } break;
    case VERTICAL_BACK:{
      type_jump_next_elem_str = str_vertical_back;
    } break;
    case VERTICAL_BACK_SMOOTH:{
      type_jump_next_elem_str = str_vertical_back_smooth;
    } break;
  }
  return type_jump_next_elem_str;
}
type_jump_next_elem_t str_to_type_jump_next_elem(
  const irs::string_t& a_type_jump_next_elem_str)
{
  type_jump_next_elem_t type_jump_next_elem = HORIZONTAL_DOWN;
  if(a_type_jump_next_elem_str == str_horizontal_down){
    type_jump_next_elem = HORIZONTAL_DOWN;
  }else if(a_type_jump_next_elem_str == str_horizontal_down_smooth){
    type_jump_next_elem = HORIZONTAL_DOWN_SMOOTH;
  }else if(a_type_jump_next_elem_str == str_horizontal_up){
    type_jump_next_elem = HORIZONTAL_UP;
  }else if(a_type_jump_next_elem_str == str_horizontal_up_smooth){
    type_jump_next_elem = HORIZONTAL_UP_SMOOTH;
  }else if(a_type_jump_next_elem_str == str_vertical_forward){
    type_jump_next_elem = VERTICAL_FORWARD;
  }else if(a_type_jump_next_elem_str == str_vertical_forward_smooth){
    type_jump_next_elem = VERTICAL_FORWARD_SMOOTH;
  }else if(a_type_jump_next_elem_str == str_vertical_back){
    type_jump_next_elem = VERTICAL_BACK;
  }else if(a_type_jump_next_elem_str == str_vertical_back_smooth){
    type_jump_next_elem = VERTICAL_BACK_SMOOTH;
  }
  return type_jump_next_elem;
}

//class manager_traffic_cell_t
manager_traffic_cell_t::manager_traffic_cell_t(irs::table_size_read_only_t*
  ap_table
):
  mp_table(ap_table),
  m_current_cell(),
  m_start_cell(),
  m_illegal_cells(),
  m_type_min_col(TBT_DEFAULT),
  m_type_min_row(TBT_DEFAULT),
  m_type_max_col(TBT_DEFAULT),
  m_type_max_row(TBT_DEFAULT)
{}

void manager_traffic_cell_t::init_inf_table()
{
  if(m_type_min_col == TBT_DEFAULT)
    min_col = 0;
  if(m_type_min_row == TBT_DEFAULT)
    min_row = 0;
  if(m_type_max_col == TBT_DEFAULT)
    max_col = mp_table->get_col_count() - 1;
  if(m_type_max_row == TBT_DEFAULT)
    max_row = mp_table->get_row_count() - 1;

  if(
    (m_type_jump_next_elem == HORIZONTAL_DOWN) ||
    (m_type_jump_next_elem == HORIZONTAL_DOWN_SMOOTH) ||
    (m_type_jump_next_elem == VERTICAL_FORWARD) ||
    (m_type_jump_next_elem == VERTICAL_FORWARD_SMOOTH)){
    m_start_cell.col = min_col;
    m_start_cell.row = min_row;
  }else{
    m_start_cell.col = max_col;
    m_start_cell.row = max_row;
  }
  if(m_current_cell.col > max_col){
    m_current_cell.col = max_col;
  }
  if(m_current_cell.row > max_row){
    m_current_cell.row = max_row;
  }
}
//по горизонтали вниз, обычный переход
bool manager_traffic_cell_t::next_cell_horizontal_down()
{
  IRS_ASSERT((m_current_cell.col <= max_col) &&
    (m_current_cell.row <= max_row));
  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    if(cell.col < max_col){
      cell.col++;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else if(cell.row < max_row){
      cell.col = min_col;
      cell.row++;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    }
  }
  return jump_next_cell_success;
}
//плавный переход
bool manager_traffic_cell_t::next_cell_horizontal_down_smooth()
{
  IRS_ASSERT(m_current_cell.row <= max_row);

  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    // проверка на четное число
    bool even_number = (((cell.row - m_start_cell.row)%2) == 0);
    if(even_number){
      if(cell.col < max_col){
        cell.col++;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }else{
      if(cell.col > min_col){
        cell.col--;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }

    if(cell.row < max_row){
      cell.row++;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    }

  }
  return jump_next_cell_success;
}
//по горизонтали вверх, обычный переход
bool manager_traffic_cell_t::next_cell_horizontal_up()
{
  IRS_ASSERT((m_current_cell.col >= min_col) &&
    (m_current_cell.row >= min_row));
  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    if(cell.col > min_col){
      cell.col--;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else if(cell.row > min_row){
      cell.col = max_col;
      cell.row--;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    }
  }
  return jump_next_cell_success;
}
//плавный переход
bool manager_traffic_cell_t::next_cell_horizontal_up_smooth()
{
  IRS_ASSERT(m_current_cell.row >= min_row);
  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    // проверка на четное число
    bool even_number = (((cell.row - m_start_cell.row)%2) == 0);
    if(even_number){
      if(cell.col > min_col){
        cell.col--;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }else{
      if(cell.col < max_col){
        cell.col++;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }

    if(cell.row > min_row){
      cell.row--;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    }
  }
  return jump_next_cell_success;
}
//по вертикали вперед, обычный переход
bool manager_traffic_cell_t::next_cell_vertical_forward()
{
  IRS_ASSERT((m_current_cell.col <= max_col) &&
    (m_current_cell.row <= max_row));

  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    if(cell.row < max_row){
      cell.row++;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else if(cell.col < max_col){
      cell.row = min_row;
      cell.col++;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    }
  }
  return jump_next_cell_success;
}
//плавный переход
bool manager_traffic_cell_t::next_cell_vertical_forward_smooth()
{
  IRS_ASSERT(m_current_cell.col <= max_col);

  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    // проверка на четное число
    bool even_number = (((cell.col - m_start_cell.col)%2) == 0);
    if(even_number){
      if(cell.row < max_row){
        cell.row++;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }else{
      if(cell.row > min_row){
        cell.row--;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }

    if(cell.col < max_col){
      cell.col++;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    }
  }
  return jump_next_cell_success;
}
//по вертикали назад, обычный переход
bool manager_traffic_cell_t::next_cell_vertical_back()
{
  IRS_ASSERT((m_current_cell.col >= min_col) &&
    (m_current_cell.row >= min_row));

  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    if(cell.row > min_row){
      cell.row--;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else if(cell.col > min_col){
      cell.row = max_row;
      cell.col--;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    }
  }
  return jump_next_cell_success;
}
//плавный переход
bool manager_traffic_cell_t::next_cell_vertical_back_smooth()
{
  IRS_ASSERT(m_current_cell.col >= min_col);

  bool jump_next_cell_success = false;
  coord_cell_t cell = m_current_cell;
  while(true){
    // проверка на четное число
    bool even_number = (((cell.col - m_start_cell.col)%2) == 0);
    if(even_number){
      if(cell.row > min_row){
        cell.row--;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }else{
      if(cell.row < max_row){
        cell.row++;
        if(!illegal_cell(cell)){
          m_current_cell = cell;
          jump_next_cell_success = true;
          break;
        }
        continue;
      }
    }

    if(cell.col > min_col){
      cell.col--;
      if(!illegal_cell(cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
        break;
      }
    }else{
      if((!illegal_cell(cell)) && (cell != m_current_cell)){
        m_current_cell = cell;
        jump_next_cell_success = true;
      }else{
        jump_next_cell_success = false;
      }
      break;
    } 
  }
  return jump_next_cell_success;
}

bool manager_traffic_cell_t::illegal_cell(const coord_cell_t a_cell)
{
  // принадлежность к запрещенным ячейкам
  bool cell_accessory_illegal = false;
  unsigned int size_illegal_cells = m_illegal_cells.cells.size();
  for(unsigned int i = 0; i <  size_illegal_cells; i++){
    if(m_illegal_cells.cells[i] == a_cell){
      cell_accessory_illegal = true;
      break;
    }
  }
  if(cell_accessory_illegal != true){
    unsigned int size_illegal_cols = m_illegal_cells.cols.size();
    for(unsigned int i = 0; i <  size_illegal_cols; i++){
      if(m_illegal_cells.cols[i] == a_cell.col){
        cell_accessory_illegal = true;
        break;
      }
    }
  }
  if(cell_accessory_illegal != true){
    unsigned int size_illegal_rows = m_illegal_cells.rows.size();
    for(unsigned int i = 0; i <  size_illegal_rows; i++){
      if(m_illegal_cells.rows[i] == a_cell.row){
        cell_accessory_illegal = true;
        break;
      }
    }
  }    
  return cell_accessory_illegal;
}
int manager_traffic_cell_t::get_cell_count_end()
{
  coord_cell_t current_cell = m_current_cell;
  int cell_count = 0;
  while (next_cell()) {
    cell_count++;
  }
  m_current_cell = current_cell;
  return cell_count;
}
