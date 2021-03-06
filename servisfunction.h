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
#include <irsrect.h>
#include <irstable.h>
#include <tstlan5lib.h>
#include <json/json.h>
//#include <irsdevices.h>
#include "addcolrow.h"
#include "table.h"
#include "dinamictypes.h"
#include "debugdigitalinterpolator.h"
#include "connectionlog.h"

//#include <boost/filesystem/path.hpp>

#include <irsfinal.h>

#define debug_version_digital_interpolator

#define DGI_MSG(msg) IRS_DBG_MSG(msg)

//  Command bits
//using namespace std;
//---------------------------------------------------------------------------

extern const double epsilon;

// ��������� ��� ����������� "�� �����"
extern const double not_a_number;

template<class T>
double get_epsilon(const T& a_t)
{
  return pow(10, -1.0 * (irs::get_num_precision_def(a_t) - 1));
}

template<class T>
bool is_equals(const T a1, const T a2)
{
  return irs::compare_value(a1, a2, get_epsilon(a1)) == irs::equals_value;
}



template<class N>
String num_to_cbstr(const N& a_num, const locale& a_loc = irs::loc().get())
{
  typename irs::base_str_type<String>::type base_str;
  number_to_string(a_num, &base_str, a_loc);
  return irs::str_conv<String>(base_str);
}


template <class T>
inline std::string num_to_u8(const T& a_num)
{
  return irs::encode_utf_8(irs::num_to_str_classic(a_num));
}

template<class T>
inline bool jsonv_get_num( const Json::Value& a_value, T* ap_result )
{
  if( !a_value.isString() )
    return false;

  T value = 0;
  if( irs::str_to_num_classic( a_value.asString(), &value ) ) {
    *ap_result = value;
    return true;
  }

  return false;
}


inline String jsonv_safe_get_cbstr( const Json::Value& a_value, const String& a_default )
{
  if( !a_value.isString() )
    return a_default;

  return irs::decode_utf_8<String>( a_value.asString() );
}


inline bool jsonv_get_cbstr( const Json::Value& a_value, String* ap_result )
{
  if( !a_value.isString() )
    return false;

  *ap_result = irs::decode_utf_8<String>( a_value.asString() );

  return true;
}


inline bool jsonv_get_str( const Json::Value& a_value, irs::string_t* ap_result )
{
  if( !a_value.isString() )
    return false;

  *ap_result = irs::decode_utf_8<irs::string_t>( a_value.asString() );

  return true;
}


/*inline Json::Value jsonv_safe_get_jsonv( const Json::Value& a_value )
{
  return a_value.empty() ? Json::Value() : a_value;
}*/

enum m_copy_data{
  ON_COPY, OFF_COPY
};


enum status_options_t {
  OFF_PROCESSING,
  ON_UPDATE,
  ON_READ
};


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
  int col;
  int row;
  param_cur_cell_t():col_value(), row_value(), top_value(), col(0), row(0)
  {}
};


struct displ_cell_t
{
  double value;
  bool init;
  displ_cell_t():
    value(0),
    init(false)
  {
  }
  displ_cell_t(const cell_t& a_cell):
    value(a_cell.value),
    init(a_cell.init)
  {
  }
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
  virtual irs::rect_t selection() const = 0;
  virtual void set_col(const int a_col) = 0;
  virtual void set_row(const int a_row) = 0;
  virtual void out_display_cell(
    const int a_col_displ, const int a_row_displ, const displ_cell_t a_cell) = 0;
  virtual void out_display_cur_cell(const displ_cell_t a_cell) = 0;
  virtual void out_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const displ_cell_t a_cell,
    const string_type& a_type_variable) = 0;
  virtual string_type get_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const displ_cell_t a_cell,
    const string_type& a_type_variable) = 0;
  virtual displ_cell_t in_display_cur_cell() = 0;
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
  irs::rect_t selection() const;
  void set_col(const int a_col);
  void set_row(const int a_row);
  void out_display_cell(
    const int a_col_displ, const int a_row_displ, const displ_cell_t a_cell);
  void out_display_cur_cell(const displ_cell_t a_cell);
  void out_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const displ_cell_t a_cell,
    const string_type& a_type_variable);
  string_type get_display_cell_variable_precision(
    const int a_col_displ,
    const int a_row_displ,
    const displ_cell_t a_cell,
    const string_type& a_type_variable);
  displ_cell_t in_display_cur_cell();
  void set_edit_mode_table();
  void reset_edit_mode_table();
  bool get_edit_mode_table();
  int col_count() const;
  int row_count() const;
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

/*���������� ������ ������ TComboBox, ����� ������� ����� a_text*/
int get_index_row_combo_box_str(
  const TComboBox* const ap_combo_box,
  const String& a_text);


class log_message_t: public irs::cbuilder::log_msg_t
{
  //log_t* mp_log;
public:
  log_message_t(/*log_t* ap_log*/)//: mp_log(ap_log)
  {}
  virtual void send_msg(const irs::string& a_msg_str)
  {
    irs::mlog() << a_msg_str << endl;
    //(*mp_log) << a_msg_str.c_str();
  }
};


struct parameter1_t
{
  String name;
  lang_type_t type;
  String unit;
  bool anchor;
  irs_i32 index;
  long double koef;
  double default_val;
  parameter1_t():
    name(),
    type(type_none),
    unit(),
    anchor(false),
    index(0),
    koef(1),
    default_val(0)
  {}
  parameter1_t(
    const String a_name,
    const lang_type_t a_type,
    const String a_unit,
    const bool anchors,
    const irs_i32 a_index,
    const long double a_koef,
    const double a_default_val):
    name(a_name),
    type(a_type),
    unit(a_unit),
    anchor(anchors),
    index(a_index),
    koef(a_koef),
    default_val(a_default_val)
  {}
  void clear()
  {
    *this = parameter1_t();
  }

  bool operator==(const parameter1_t& a_param) const
  {
    return name   == a_param.name &&
      type        == a_param.type &&
      unit        == a_param.unit &&
      anchor      == a_param.anchor &&
      index       == a_param.index &&
      is_equals(koef, a_param.koef) &&
      is_equals(default_val, a_param.default_val);
  }
};


struct parameter2_t
{
  String name;
  lang_type_t type;
  String unit;
  irs_i32 index;
  long double koef;
  double default_val;

  parameter2_t():
    name(),
    type(type_none),
    unit(),
    index(0),
    koef(1),
    default_val(0)
  {}

  parameter2_t(
    const String a_name,
    const lang_type_t a_type,
    const String a_unit,
    const irs_i32 a_index,
    const long double a_koef,
    double a_default_val):
    name(a_name),
    type(a_type),
    unit(a_unit),
    index(a_index),
    koef(a_koef),
    default_val(a_default_val)
  {}

  void clear()
  {
    *this = parameter2_t();
  }

  bool operator==(const parameter2_t& a_param) const
  {
    return name   == a_param.name &&
      type        == a_param.type &&
      unit        == a_param.unit &&
      index       == a_param.index &&
      is_equals(koef, a_param.koef) &&
      is_equals(default_val, a_param.default_val);
  }
};


struct parameter3_t
{
  String name;
  lang_type_t type;
  String unit;
  irs_i32 index;
  ///long double koef_shunt; // ������ ��� �������� �� ������ ini-������

  parameter3_t(
  ):
    name(),
    type(type_none),
    unit(),
    index(0)/* ,
    koef_shunt(1)*/
  {}

  parameter3_t(
    const String a_name,
    const lang_type_t a_type,
    const String a_unit,
    const irs_i32 a_index,
    const long double a_koef_shunt):
    name(a_name),
    type(a_type),
    unit(a_unit),
    index(a_index)/*,
    koef_shunt(a_koef_shunt)*/
  {}

  void clear()
  {
    *this = parameter3_t();
  }

  bool operator==(const parameter3_t& a_param) const
  {
    return name   == a_param.name &&
      type        == a_param.type &&
      unit        == a_param.unit &&
      index       == a_param.index/* &&
      is_equals(koef_shunt, a_param.koef_shunt)*/;
  }
};


struct parameter_ex_t
{
  String name;
  lang_type_t type;         // ��� ����������
  String unit;              // ������� ���������
  irs_i32 index;            // ������ �����
  //double value_working;     // ������� ��������
  double value_default;     // �������� �� ���������
  parameter_ex_t():
    name(),
    type(type_none),
    unit(),
    index(0),
    //value_working(0.0),
    value_default(0.0)
  {}
  parameter_ex_t(
    const String a_name,
    const lang_type_t a_type,
    const String a_unit,
    const irs_i32 a_index,
    //double a_value_working,
    double a_value_default
  ):
    name(a_name),
    type(a_type),
    unit(a_unit),
    index(a_index),
    //value_working(a_value_working),
    value_default(a_value_default)
  {}
  void clear()
  {
    *this = parameter_ex_t();
  }

  const operator==(const parameter_ex_t& a_param) const
  {
    return name     == a_param.name &&
      type          == a_param.type &&
      unit          == a_param.unit &&
      index         == a_param.index &&
      //is_equals(value_working, a_param.value_working) &&
      is_equals(value_default, a_param.value_default);
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

  bool operator==(const bit_type1_pos_t& a_bit) const
  {
    return index_byte == a_bit.index_byte &&
      index_bit       == a_bit.index_bit;
  }
};


struct bit_type2_pos_t
{
  typedef irs::string_t string_type;
  string_type bitname;
  int index_byte;
  int index_bit;
  //bool value_working;
  bool value_def;

  bit_type2_pos_t(
  ):
    bitname(),
    index_byte(0),
    index_bit(0),
    //value_working(false),
    value_def(false)
  {}

  bit_type2_pos_t(
    const string_type a_name_str,
    const irs_i32 a_index_byte,
    const irs_i32 a_index_bit,
    //const bool a_value_working,
    const bool a_value_def):
    bitname(a_name_str),
    index_byte(a_index_byte),
    index_bit(a_index_bit),
    //value_working(a_value_working),
    value_def(a_value_def)
  {}

  void clear()
  {
    *this = bit_type2_pos_t();
  }

  bool operator==(const bit_type2_pos_t& a_bit) const
  {
    return bitname  == a_bit.bitname &&
      index_byte    == a_bit.index_byte &&
      index_bit     == a_bit.index_bit &&
      //value_working == a_bit.value_working &&
      value_def     == a_bit.value_def;
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

  bool operator==(const reference_channel_t& a_channel) const
  {
    return enabled  == a_channel.enabled &&
      ip_adress     == a_channel.ip_adress &&
      port          == a_channel.port;
  }
};


enum type_sub_diapason_t{
  tsd_parameter1,
  tsd_parameter2
};


struct eeprom_range_t
{
  int index_start;
  int size;
  double value_begin;
  double value_end;

  eeprom_range_t(
  ):
    index_start(0),
    size(0),
    value_begin(0.0),
    value_end(0.0)
  {}

  eeprom_range_t(int a_index_start, int a_size, double a_value_begin, double a_value_end
  ):
    index_start(a_index_start),
    size(a_size),
    value_begin(a_value_begin),
    value_end(a_value_end)
  {
  }

  void clear()
  {
    *this = eeprom_range_t();           
  }

  bool operator==(const eeprom_range_t& a_eeprom) const
  {
    return index_start  == a_eeprom.index_start &&
      size              == a_eeprom.size &&
      is_equals(value_begin, a_eeprom.value_begin) &&
      is_equals(value_end, a_eeprom.value_end);
  }
};


struct out_param_measuring_conf_t
{
  bool consider_out_param;
  bool filter_enabled;
  double filter_sampling_time;
  irs_u32 filter_point_count;
  out_param_measuring_conf_t():
    consider_out_param(true),
    filter_enabled(true),
    filter_sampling_time(0.1),
    filter_point_count(100)
  {
  }

  bool operator==(const out_param_measuring_conf_t& a_conf) const
  {
    return consider_out_param == a_conf.consider_out_param &&
      filter_enabled          == a_conf.filter_enabled &&
      is_equals(filter_sampling_time, a_conf.filter_sampling_time) &&
      filter_point_count      == a_conf.filter_point_count;
  }
};


struct temperature_control_common_cfg_t
{
  bool enabled;
  irs_u32 index;
  
  temperature_control_common_cfg_t():
    enabled(false),
    index(0)
  {
  }

  bool operator==(const temperature_control_common_cfg_t& a_conf) const
  {
    return enabled == a_conf.enabled &&
      index        == a_conf.index;
  }
};


struct temperature_control_config_t
{
  bool enabled;
  double reference;
  double difference;
  temperature_control_config_t():
    enabled(false),
    reference(65),
    difference(0.5)
  {
  }

  bool operator==(const temperature_control_config_t& a_conf) const
  {
    return enabled == a_conf.enabled &&
      is_equals(reference, a_conf.reference) &&
      is_equals(difference, a_conf.difference);
  }
};


struct out_param_control_conf_t
{ 
  bool enabled;
  double max_relative_difference;
  double time;

  out_param_control_conf_t():
    enabled(false),
    max_relative_difference(0.00003), 
    time(15)
  {
  }

  bool operator==(const out_param_control_conf_t& a_conf) const
  {
    return enabled == a_conf.enabled &&
      is_equals(max_relative_difference, a_conf.max_relative_difference) &&
      is_equals(time, a_conf.time);
  }
};


struct cell_config_calibr_t
{
  typedef std::size_t size_type;

  double value;               // for header cells
  bool is_value_initialized;  // for header cells

  long double output_param_coef;
  vector<double> ex_param_work_values;  // ������� �������� �������������� ����������
  vector<bool> ex_bit_work_values;      // ������� �������� �������������� �����

  String type_meas;
  bool range_enabled;
  double range;
  irs_u32 delay_meas;
  double meas_interval;
  irs_u32 count_reset_over_bit;

  out_param_measuring_conf_t out_param_measuring_conf;
  out_param_control_conf_t out_param_control_config;
  temperature_control_config_t temperature_control;

  cell_config_calibr_t();
  void clear();
  bool operator==(const cell_config_calibr_t& a_config) const;
  bool operator!=(const cell_config_calibr_t& a_config) const;
  void load_from_json( const Json::Value& a_data, bool a_is_header_cell );
  Json::Value save_to_json(bool a_is_header_cell) const;
};


struct config_calibr_t
{
  typedef std::size_t size_type;
  typedef irs::string_t string_type;
  String device_name;
  String reference_device_name;
  String ip_adress;
  irs_u32 port;
  parameter1_t in_parameter1;
  parameter1_t in_parameter2;
  parameter2_t in_parameter3;
  parameter3_t out_parameter;
  vector<parameter_ex_t> v_parameter_ex;

  bit_type1_pos_t bit_pos_mismatch_state;
  bit_type1_pos_t bit_pos_correct_mode;
  bit_type1_pos_t bit_pos_operating_duty;
  bit_type1_pos_t bit_pos_error_bit;
  bit_type1_pos_t bit_pos_reset_over_bit;
  bit_type1_pos_t bit_pos_phase_preset_bit;
  vector<bit_type2_pos_t> bit_type2_array;

  irs_u32 index_work_time;
  irs_u32 index_pos_eeprom;

  temperature_control_common_cfg_t temperature_ctrl_common_cfg;
  type_sub_diapason_t type_sub_diapason;
  std::vector<eeprom_range_t> eeprom_ranges;
  String active_filename;
  reference_channel_t reference_channel;


  enum{
    min_col_count = 2,
    min_row_count = 2,
    default_col_count = min_col_count,
    default_row_count = min_row_count,
  };
  // ��������� ���������� ��� ������ ������
  irs::table_t<cell_config_calibr_t> cells_config;

  config_calibr_t();
  void clear();
  bool save(const string_type& a_filename);
  bool load(const string_type& a_filename);
  bool operator==(const config_calibr_t& a_config);
  //bool is_equal(const config_calibr_t& a_config);
  static irs::table_t<cell_config_calibr_t> get_default_cells_config();
  static void check_config(const config_calibr_t& a_config_calibr);
  static void check_cells_config(const irs::table_t<cell_config_calibr_t>& a_cells_config);
  static void save_load_test();
private:
  bool save_to_json(std::ostream* ap_ostr);
  bool load_from_json(std::istream* ap_ostr);
  bool save_to_ini(const string_type& a_filename);
  bool load_from_ini( const string_type& a_filename );
  void add_static_param(irs::ini_file_t* ap_ini_file,
    cell_config_calibr_t* ap_cell_config_calibr);
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
  // ��������� ��� ����������� "�� �����"
  // const double m_nan;
  // ������ ���� � ����� ��� ����� ������� ��������
  static const int m_field_width = 30;
  // �������� ������ ����� � ����
  static const int m_precision = 15;
  // ����������� ��������� ����� ��������
  static const int m_max_col_count = 50000;
  // ����������� ��������� ����� �����
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
  // ����� ������� ��� ����������� ��������� �������� �������
  std::vector<irs::matrix_t<cell_t> > mv_saved_table;
  #endif
  int m_cur_col;
  int m_cur_row;
  int m_cur_table;
  inf_in_param_t m_inf_in_param;
  irs::table_t<cell_config_calibr_t> m_cells_config;
  bool m_is_cells_config_read_only;

  bool m_table_modifi_stat;
public:
  inline const std::vector<irs::matrix_t<cell_t> >& read_table() const;
  table_data_t(display_table_t* ap_display_table, String a_name);
  inline unsigned int index() const;
  inline TStringGrid* pointer_table() const;
  inline String name() const;
  inline coord_t coord_special_cell(const int a_n) const;
  inline int size_special_cells() const;


  void cell_out_display(const int a_col_displ, const int a_row_displ);
  void cur_cell_out_display();
  void cell_out_display_variable_precision(
    const int a_col_displ,
    const int a_row_displ);

  // !\brief ���������� �������� �� ������ ���������� ������� �� ����������
  void cur_cell_in_display();

  string_type get_cell_display_variable_precision(
    const int a_col_displ,
    const int a_row_displ);

  inline string_type get_cell_value_str_table_data(
    const int a_col_displ, const int a_row_displ);

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

  void create_new_table(const inf_in_param_t& a_inf_in_param,
    const irs::table_t<cell_config_calibr_t>& a_cells_config);

  void save_table_to_json_file(const string_type& a_file_name);

  void save_table_to_file(const string_type& a_file_name);
  // ��������� ������� � Microsoft Excel (*.csv) ����
  void save_table_to_microsoft_excel_csv_file(const string_type a_file_name);
  // ��� ���������� � �-���� Matlab
  void save_table_to_m_file(const string_type a_file_name) const;

  bool load_table_from_file(const string_type& a_file_name,
    const inf_in_param_t& a_inf_in_param,
    const irs::table_t<cell_config_calibr_t>& a_cells_config);
  //void load_table_from_json_file(const string_type a_file_name);
  //void load_table_from_ini_file(const string_type& a_file_name);
  // ��������� ���������� �� �����
  void load_subtable_from_file(const string_type& a_file_name);
  const table_data_t&
    operator=(const table_data_t& a_table_source);
  // ������� ���� ����� �������. ���������� �������� � ����� �������� �������
  void clear_table();
  // ���������� �������� � ����� �������� � ���������� + ������� ���� �����
  void clear_table_def();
  // ������� �����, �� ���������� ���������������
  void clear_content_table();
  // ������� ����������� �������
  void clear_conrent_cur_col_table();
  // ������� ����������� ������
  void clear_countnt_cur_row_table();
  // ����� �������� ������, ������� �������� - ���������� �������
  void search_pip(const double a_limit);
  void clear_coord_special_cells();
  //void set_file_namedir(String a_file_namedir);
  String get_file_namedir();
  void clear_file_name();
  inline int table_count() const;
  inline int col_count() const;
  inline int row_count() const;
  inline param_cur_cell_t get_param_cell(
    const int a_col_displ, const int a_row_displ) const;
  //inline int table_count() const;
  // ������������� ����� �������� �������� ������
  inline void set_col_table_data(const int a_col);
  // ������������� ����� ������ �������� ������
  inline void set_row_table_data(const int a_row);
  // ������������� ����� ������� �������� ������
  inline void set_num_table_data(const int a_table);
  // ������������� ������� � ���������������� �������
  inline void set_col_displ(const int a_col);
  // ������������� ������ � ���������������� �������
  inline void set_row_displ(const int a_row);
  // ���������� ����� �������, ���������� � ���������������� �������
  inline int get_col_displ() const;
  // ���������� ����� ������, ��������� � ���������������� �������
  inline int get_row_displ() const;
  inline irs::rect_t get_selection_displ() const;
  inline int get_col_count_displ() const;
  inline int get_row_count_displ() const;
  // ���������� ���������� ������ � ������� ������
  inline coord3d_t get_coord_cell_table(
    const int a_col_displ, const int a_row_displ) const;
  // ���������� ���������� ������ � ������� �������
  inline coord_t get_coord_cell_table_displ(
    const coord3d_t& a_coord_cell) const;

  // ���������� ������ �������
  inline cell_t get_cell_table(
    const int a_col_displ, const int a_row_displ) const;
  // ������������� �������� ������ � ������� - a_table,
  // �������� - a_col, ������ - a_row
  inline void set_cell(
    const cell_t a_cell, const int a_table, const int a_col, const int a_row);
  inline void set_cell(
    const cell_t a_cell, const int a_col_displ, const int a_row_displ);
  inline void set_edit_mode_table();
  inline void reset_edit_mode_table();
  inline bool get_edit_mode_table();
  // ���������� true, ���� ���������� (a_col_displ, a_row_displ)
  // ��������� � ������ x
  inline bool get_stat_cell_x(
    const int a_col_displ, const int a_row_displ) const;
  // x,y,z - ������� ����������, p(x,y,z) - �������
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
  // ���������� true, ���� ������� �� ���������� �� ����������� ��� �����������
  // � ����
  inline bool have_unsaved_changes() const;
  inline const inf_in_param_t& get_inf_in_param() const;
  //inline void set_inf_in_param(const inf_in_param_t& a_inf_in_param);
  const irs::table_t<cell_config_calibr_t>& table_data_t::get_cells_config() const;
  bool is_cells_config_read_only() const;
  //void table_data_t::set_cells_config(const irs::table_t<cell_config_calibr_t>& a_cells_config);
  // ������������� �������� ����� �������, �� ���������� ����������������
  void inversion_sign_conrent_table();
  // �������������� ���������� ����� �������, �� ���������� ����������������
  // ��������� ������ ���� Z + 2+X*Y;
  // Z - �������� ������� ������, X - �������� �������� ��������� �� �������,
  // Y - �������� �������� ��������� �� ������.
  // ����� ���������� ������� ����������������� ������ ������� ����� ���������
  // ������ ���� Z = Z + 2+X*Y;
  void modify_content_table(const string_type& a_str);

  void copy_cells_config(const coord_t& a_src_cell, const TRect& a_rect);
  bool is_cells_config_coord_valid(const coord_t& a_coord) const;
  bool is_cells_config_range_valid(const TRect& a_rect) const;
private:
  static bool displ_table_matches_config_table(
    const irs::matrix_t<cell_t>& a_table,
    const irs::table_t<cell_config_calibr_t>& a_cells_config);
  void set_data_table_to_config(irs::matrix_t<cell_t>* ap_table);
  void set_config_table_to_data(irs::matrix_t<cell_t>* ap_table);

  void save_table_to_ini_file(const string_type a_file_name);
  void save_table_to_json(size_type a_index, Json::Value* ap_parameters);
  void save_points(const cell_t::points_type& a_points,
    Json::Value* ap_points_value) const;

  ///
  void concatenate_table_matrix(
    const irs::matrix_t<cell_t>& a_in_table1,
    const irs::matrix_t<cell_t>& a_in_table2,
    irs::matrix_t<cell_t>& a_out_table);
  void concatenate_table(
    const vector<irs::matrix_t<cell_t> >& av_in_table1,
    const vector<irs::matrix_t<cell_t> >& av_in_table2,
    vector<irs::matrix_t<cell_t> >& av_out_table);
};


void load_table_from_file(
  number_in_param_t& a_number_in_param,
  const irs::string_t& a_file_name,
  std::vector<irs::matrix_t<cell_t> >& a_table);


void load_table_from_json_file(
  number_in_param_t& a_number_in_param,
  const irs::string_t& a_file_name,
  std::vector<irs::matrix_t<cell_t> >& a_table);


void load_table_from_json(const Json::Value& a_parameters,
  irs::matrix_t<cell_t>* ap_matrix);


void load_points(const Json::Value& a_points_value,
  cell_t::points_type* ap_points);


void load_table_from_ini_file(
  number_in_param_t& a_number_in_param,
  const irs::string_t& a_file_name,
  std::vector<irs::matrix_t<cell_t> >& a_table);


inline const std::vector<irs::matrix_t<cell_t> >&
  table_data_t::read_table() const
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
  const int a_col_displ, const int a_row_displ) const
{
  int table_count = mv_table.size();
  param_cur_cell_t param_cur_cell;
  param_cur_cell.col = a_col_displ;
  param_cur_cell.row = a_row_displ;
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
{
  mp_display_table->set_col(a_col);
}


inline void table_data_t::set_row_displ(const int a_row)
{
  mp_display_table->set_row(a_row);
}


inline int table_data_t::get_col_displ() const
{
  return mp_display_table->col();
}


inline int table_data_t::get_row_displ() const
{
  return mp_display_table->row();
}

inline irs::rect_t table_data_t::get_selection_displ() const
{
  return mp_display_table->selection();
}

inline int table_data_t::get_col_count_displ() const
{
  return mp_display_table->col_count();
}


inline int table_data_t::get_row_count_displ() const
{
  return mp_display_table->row_count();
}


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


inline bool table_data_t::have_unsaved_changes() const
{
  return  (mv_table != mv_saved_table);
  /*#ifdef  debug_version_digital_interpolator
  IRS_ASSERT((!m_table_modifi_stat) && (mv_table == mv_saved_table));
  #endif
  return (!m_table_modifi_stat);*/
}


inline const inf_in_param_t& table_data_t::get_inf_in_param() const
{
  return m_inf_in_param;
}


/*inline void table_data_t::set_inf_in_param(const inf_in_param_t& a_inf_in_param)
{
  m_inf_in_param = a_inf_in_param;
}*/


inline const irs::table_t<cell_config_calibr_t>& table_data_t::get_cells_config() const
{
  return m_cells_config;
}

inline bool table_data_t::is_cells_config_read_only() const
{
  return m_is_cells_config_read_only;
}


/*inline void table_data_t::set_cells_config(const irs::table_t<cell_config_calibr_t>& a_cells_config)
{
  m_cells_config = a_cells_config;
}*/


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
    config_calibr_t& a_config_calibr,
    const irs_uarc a_number_of_koef_per_point);
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


// ������������� ������� �������� ����� � �����
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
// ������������� ������� �������� ������ � �����
template<class T>
inline bool StrToNumber(const AnsiString& a_str, T& a_number)
{
  irs::string str = a_str.c_str();
  return str.to_number(a_number);
}
  */

/*irs::string_t absolute_file_name_to_relative(
  const irs::string_t& a_full_file_name,
  const irs::string_t& a_base);
  */


class file_name_service_t
{
public:
  typedef irs::char_t char_type;
  file_name_service_t();
  String get_config_ext() const;
  String get_config_dir() const;
  String get_multimeter_config_ext() const;
  String get_multimeter_config_dir() const;
  String get_device_config_dir() const;
  String get_device_config_ext() const;
  String make_config_full_file_name(String a_config_name)  const;
  String make_device_config_full_file_name(String a_config_name) const;
  String make_ref_device_config_full_file_name(String a_config_name) const;
  String make_device_grid_config_full_name(String a_config_name) const;
  String make_ref_device_grid_config_full_name(String a_config_name) const;
  String get_device_options_section() const;
  String get_config_name(const String& a_full_file_name) const;
  String make_multimeter_config_full_file_name(String a_config_name)  const;
  void create_config_dir();

  // ���������� ������������� ����, ���� ��������, � ��������� ������
  // ���������� �������� ����
  String make_relative_file_name(const String& a_full_file_name) const;

  //! \brief ���������� \� true, ���� ������ ��� ����� �������������
  //bool path_is_relative(const String& a_path);

  //! \brief ���������� ���������� ���� �� ���������� ���������
  //!   � �������������� ����
  String make_absolute_path(const String& a_relative_path);

  //! \brief ���������� ���������� ����, ���� ������������ ���� ��������
  //!   ������������� � ���������� ��� ��� ��������� � ��������� ������
  //String make_absolute_path_if_relative(const String& a_relative_path);
private:
  String ensure_dir_end(const String& a_dir);
  char_type path_name_separator();
  bool is_path_name_separator(const char_type a_ch);
  //������� ������� ���������
  const String m_path_prog;
  //���������� ����� ������������ �������� ����������
  const String m_default_ext;
  const String m_multimeter_config_ext;
  //��� ����� �� ��������� ������������ �������� ����������
  const String m_default_filename;
  //��� �������� ��������� ��� �������� �����������
  const String m_foldername_conf;
  // ��� �������� ��� ������������ ������������
  const String m_multimeter_foldername_conf;
  // ��� �������� ��� ������������ ���������
  const String m_device_foldername_conf;
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
      a_config_calibr.in_parameter1.type,
      ap_data,
      a_config_calibr.in_parameter1.index);

    y_in.connect(
      a_config_calibr.in_parameter2.type,
      ap_data,
      a_config_calibr.in_parameter2.index);

    if(a_config_calibr.in_parameter1.anchor == false
      && a_config_calibr.in_parameter2.anchor == false){
      q_in.connect(
        a_config_calibr.in_parameter3.type,
        ap_data,
        a_config_calibr.in_parameter3.index);
    }
    y_out.connect(
      a_config_calibr.out_parameter.type,
      ap_data,
      a_config_calibr.out_parameter.index);

    int extra_param_count = a_config_calibr.v_parameter_ex.size();
    v_extra_param.resize(extra_param_count);
    for (int i = 0; i < extra_param_count; i++) {
      v_extra_param[i].connect(
        a_config_calibr.v_parameter_ex[i].type,
        ap_data,
        a_config_calibr.v_parameter_ex[i].index);
    }

    work_time.connect(ap_data,
      a_config_calibr.index_work_time);
    if (a_config_calibr.temperature_ctrl_common_cfg.enabled) {
      temperature.connect(ap_data,
      a_config_calibr.temperature_ctrl_common_cfg.index);
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
  String get_name();
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


void save_string_grid_to_csv_with_dialog(TStringGrid* ap_string_grid,
  const String& a_file_name_default = String());

#endif
