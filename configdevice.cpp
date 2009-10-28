//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configdevice.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// class list_box_ex_t
list_box_ex_t::list_box_ex_t(
  table_display_t<irs::string>* ap_table
):
  mp_table(ap_table)
{
}

void list_box_ex_t::add_row()
{
  irs_u32 col_count = mp_table->col_count();
  irs_u32 row_count = mp_table->row_count();
  irs::matrix_t<irs::string> matrix(col_count, row_count);
  for (irs_u32 y = 0; y < row_count; y++){
    for (irs_u32 x = 0; x < col_count; x++){
      irs::string cell = "";
      mp_table->read_cell(cell, x, y);
      matrix[x][y] = cell;
    }
  }
  mp_table->set_row_count(row_count+1);
  for (irs_u32 y = 0; y < row_count; y++){
    for (irs_u32 x = 0; x < col_count; x++){
      irs::string cell = matrix[x][y];
      mp_table->write_cell(cell, x, y);
    }
  }
  row_count += 1;
  irs_u32 row_end = row_count - 1;
  for (irs_u32 i = 0; i < col_count; i++){
    mp_table->write_cell("", i, row_end);
  }
}

void list_box_ex_t::add_row(const vector<irs::string>& av_row)
{
  irs_u32 col_count = mp_table->col_count();
  irs_u32 row_count = mp_table->row_count();
  irs::matrix_t<irs::string> matrix(col_count, row_count);
  for (irs_u32 y = 0; y < row_count; y++){
    for (irs_u32 x = 0; x < col_count; x++){
      irs::string cell = "";
      mp_table->read_cell(cell, x, y);
      matrix[x][y] = cell;
    }
  }
  mp_table->set_row_count(row_count+1);
  for (irs_u32 y = 0; y < row_count; y++){
    for (irs_u32 x = 0; x < col_count; x++){
      irs::string cell = matrix[x][y];
      mp_table->write_cell(cell, x, y);
    }
  }
  row_count += 1;
  irs_u32 min_count = min(col_count, av_row.size());
  irs_u32 row_end = row_count - 1;
  for (irs_u32 i = 0; i < min_count; i++){
    mp_table->write_cell(av_row[i], i, row_end);
  }
}

void list_box_ex_t::del_row()
{
  irs_u32 cur_row = mp_table->row();
  irs_u32 col_count = mp_table->col_count();
  irs_u32 row_count = mp_table->row_count();
  if (row_count > 1) {
    irs::matrix_t<irs::string> matrix(col_count, row_count - 1);
    int y_index = 0;
    for (irs_u32 y = 0, y_end = row_count; y < y_end; y++){
      if (y != cur_row){
        for (irs_u32 x = 0; x < col_count; x++){
          irs::string cell = "";
          mp_table->read_cell(cell, x, y);
          matrix[x][y_index] = cell;
        }
        y_index++;
      }
    }

    mp_table->set_row_count(row_count - 1);
    row_count -= 1;
    for (irs_u32 y = 0; y < row_count; y++){
      for (irs_u32 x = 0; x < col_count; x++){
        irs::string cell = matrix[x][y];
        mp_table->write_cell(cell, x, y);
      }
    }
  } else if (row_count == 1) {
    mp_table->set_row_count(row_count - 1);
  }
}

void list_box_ex_t::del_all_row()
{
  mp_table->set_row_count(0);
}

void list_box_ex_t::read_row(const int a_index, vector<irs::string>& av_row)
{
  int row_count = mp_table->row_count();
  if (a_index < row_count){
    irs_u32 col_count = mp_table->col_count();
    irs_u32 min_count = min(col_count, av_row.size());
    for (irs_u32 i = 0; i < min_count; i++){
      irs::string cell = "";
      mp_table->read_cell(cell, i, a_index);
      av_row[i] = cell;
    }
  }
}
void list_box_ex_t::write_row(
  const int a_index, const vector<irs::string>& av_row)
{
  int row_count = mp_table->row_count();
  if (a_index < row_count){
    irs_u32 col_count = mp_table->col_count();
    irs_u32 min_count = min(col_count, av_row.size());
    for (irs_u32 i = 0; i < min_count; i++){
      irs::string cell = av_row[i];
      mp_table->write_cell(cell, i, a_index);
    }
  }
}

int list_box_ex_t::row_count() const
{
  return mp_table->row_count();
}

int list_box_ex_t::row() const
{
  return mp_table->row();
}

void list_box_ex_t::clear_row(const int a_row)
{
  int col_count = mp_table->col_count();
  for (int i = 0; i < col_count; i++) {
    mp_table->write_cell("", i, a_row);
  }
}

void list_box_ex_t::clear()
{
  int col_count = mp_table->col_count();
  int row_count = mp_table->row_count();
  for (int y = 0; y < row_count; y++) {
    for (int x = 0; x < col_count; x++) {
      mp_table->write_cell("", x, y);
    }
  }
}

manager_config_device_t::manager_config_device_t()
{
}

manager_config_device_t::load()
{
}

manager_config_device_t::save()
{
}

manager_config_device_t::read()
{
}

manager_config_device_t::write()
{
}

manager_config_device_t::edit()
{
}

TConfDeviceF *ConfDeviceF;
//---------------------------------------------------------------------------
__fastcall TConfDeviceF::TConfDeviceF(TComponent* Owner)
  : TForm(Owner),
  m_string_grid_in_param(InParamSG),
  m_string_grid_out_param(OutParamSG),
  m_string_grid_inf_byte(InfByteSG),
  m_string_grid_inf_byte_ex(InfByteExSG),
  m_table_in_param(&m_string_grid_in_param),
  m_table_out_param(&m_string_grid_out_param),
  m_table_inf_byte(&m_string_grid_inf_byte),
  m_table_inf_byte_ex(&m_string_grid_inf_byte_ex),
  index_out_param(1),
  index_inf_byte_ex(1)
{
  MeasTypeCB->Items->Clear();
  type_meas_t type_meas = tm_first;
  int tmeas_index = static_cast<int>(type_meas);
  while(true){
    type_meas = static_cast<type_meas_t>(tmeas_index);
    irs::string type_meas_str = type_meas_to_str(type_meas);
    MeasTypeCB->Items->Add(type_meas_str.c_str());
    if(type_meas == tm_last)
      break;
    tmeas_index++;
  }
  MeasTypeCB->ItemIndex = 0;

  InterfaceMulCB->Clear();
  interface_multim_t interface_multim = im_gpib;
  int im_index = static_cast<int>(interface_multim);
  while(true){
    interface_multim = static_cast<interface_multim_t>(im_index);
    irs::string interface_multim_str =
      interface_multim_to_str(interface_multim);
    InterfaceMulCB->Items->Add(interface_multim_str.c_str());
    if(interface_multim == im_last)
      break;
    im_index++;
  }
  InterfaceMulCB->ItemIndex = 0;

  MultimetrListCLB->Clear();
  type_multimetr_t type_multimetr = tmul_agilent_3458a;
  int tmul_index = static_cast<int>(type_multimetr);
  while(true){
    type_multimetr = static_cast<type_multimetr_t>(tmul_index);
    irs::string type_multimetr_str = type_multimetr_to_str(type_multimetr);
    MultimetrListCLB->Items->Add(type_multimetr_str.c_str());
    if(type_multimetr == tmul_last)
      break;
    tmul_index++;
  }
  MultimetrListCLB->ItemIndex = 0;

  std::vector<irs::string> headline_in_param;
  headline_in_param.push_back("Имя параметра");
  headline_in_param.push_back("Единицы измерения");
  headline_in_param.push_back("Тип переменной");
  headline_in_param.push_back("Привязка");
  headline_in_param.push_back("Индекс, байт");
  headline_in_param.push_back("Коэффициент");
  headline_in_param.push_back("Значение по умолчанию");
  std::vector<irs::string> headline_out_param;
  headline_out_param.push_back("Имя параметра");
  headline_out_param.push_back("Единицы измерения");
  headline_out_param.push_back("Тип переменной");
  headline_out_param.push_back("Индекс, байт");
  std::vector<irs::string> headline_byte;
  headline_byte.push_back("Имя бита");
  headline_byte.push_back("Индекс, байт");
  headline_byte.push_back("Индекс, бит");
  headline_byte.push_back("Рабочее значение");
  headline_byte.push_back("Значение по умолчанию");
  std::vector<irs::string> headline_byte_ex;
  headline_byte_ex.push_back("Имя бита");
  headline_byte_ex.push_back("Индекс, байт");
  headline_byte_ex.push_back("Индекс, бит");
  headline_byte_ex.push_back("Рабочее значение");
  headline_byte_ex.push_back("Значение по умолчанию");

  m_string_grid_in_param.set_min_col_count(3);
  m_string_grid_in_param.set_min_row_count(3);
  m_string_grid_out_param.set_min_col_count(2);
  m_string_grid_out_param.set_min_row_count(2);
  m_string_grid_inf_byte.set_min_col_count(5);
  m_string_grid_inf_byte.set_min_row_count(5);
  m_string_grid_inf_byte_ex.set_min_col_count(2);
  m_string_grid_inf_byte_ex.set_min_row_count(2);
  m_table_in_param.del_all_row();
  m_table_out_param.del_all_row();
  m_table_inf_byte.del_all_row();
  m_table_inf_byte_ex.del_all_row();
  m_table_in_param.add_row(headline_in_param);
  m_table_out_param.add_row(headline_out_param);
  m_table_out_param.add_row();
  m_table_inf_byte.add_row(headline_byte);
  m_table_inf_byte_ex.add_row(headline_byte_ex);
  m_table_inf_byte_ex.add_row();
}
//---------------------------------------------------------------------------
void __fastcall TConfDeviceF::Button10Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------



void __fastcall TConfDeviceF::AddOutParamButtonClick(TObject *Sender)
{
  std::vector<irs::string> out_param_def;
  irs::string str_index = index_out_param++;
  out_param_def.push_back("p_"+str_index);
  out_param_def.push_back("unknown");
  out_param_def.push_back("irs_u32");
  out_param_def.push_back("0");
  m_table_out_param.add_row(out_param_def);
}
//---------------------------------------------------------------------------

void __fastcall TConfDeviceF::DelOutParamButtonClick(TObject *Sender)
{
  int row = m_table_out_param.row();
  int row_count = m_table_out_param.row_count();
  if (row > 0) {
    if (row_count > 2) {
      m_table_out_param.del_row();
    } else if (row_count == 2 && row == 1) {
      m_table_out_param.clear_row(row);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TConfDeviceF::AddInfByteExButtonClick(TObject *Sender)
{
  std::vector<irs::string> inf_byte_ex_def;
  irs::string str_index = index_inf_byte_ex++;
  inf_byte_ex_def.push_back("byte_ex_"+str_index);
  inf_byte_ex_def.push_back("0");
  inf_byte_ex_def.push_back("0");
  inf_byte_ex_def.push_back("1");
  inf_byte_ex_def.push_back("0");
  m_table_inf_byte_ex.add_row(inf_byte_ex_def);
}
//---------------------------------------------------------------------------

void __fastcall TConfDeviceF::DelInfByteExButtonClick(TObject *Sender)
{
  int row = m_table_inf_byte_ex.row();
  int row_count = m_table_inf_byte_ex.row_count();
  if (row > 0) {
    if (row_count > 2) {
      m_table_inf_byte_ex.del_row();
    } else if (row_count == 2 && row == 1) {
      m_table_inf_byte_ex.clear_row(row);
    }
  }
}
//---------------------------------------------------------------------------

