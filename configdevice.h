//---------------------------------------------------------------------------

#ifndef configdeviceH
#define configdeviceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <irsstdg.h>
#include <vector>
//#include "avtomeas.h"
#include "newconfig.h"
#include "tablel.h"

//---------------------------------------------------------------------------
enum option_multimetr_t{
  om_first = 1,
  om_set_dc = tm_first,
  om_set_ac = 2,
  om_set_positive = 3,
  om_set_negative = 4,
  om_set_aperture = 5,
  om_set_input_impedance = 6,
  om_set_start_level = 7,
  om_last = om_set_start_level};
class list_box_ex_t
{
private:
  table_display_t* mp_table;
  list_box_ex_t();
public:
  list_box_ex_t(
    table_display_t* ap_table);
  void add_row();
  void add_row(const vector<irs::string>& av_row);
  void del_row();
  void del_all_row();
  void read_row(const int a_index, vector<irs::string>& av_row);
  void write_row(const int a_index, const vector<irs::string>& av_row);
  int row_count() const;
  int row() const;
  void clear_row(const int a_row);
  void clear();
};
struct in_parameter_t
{
  irs::string name;
  irs::string unit;
  irs::string type_variable;
  bool anchor;
  irs_i32 index;
  long double koef;
  double default_val;
};
struct out_parameter_t
{
  irs::string name;
  irs::string unit;
  irs::string type_variable;
  int index;
};
struct inf_byte_t
{
  int index_byte;
  int index_bit;
};
// тип опции мультиметра без параметров
struct option_multimetr_not_param_t
{
  bool enabled;
  option_multimetr_t option_multimetr;
};
// тип опции мультиметра с одним параметром
struct option_multimetr_one_param_t
{
  bool enabled;
  option_multimetr_t option_multimetr;
  double parameter;
};

struct measuring_instrument_t
{
  type_multimetr_t type_multimetr;
  type_meas_t m_type_meas;
  std::vector<option_multimetr_not_param_t> v_options_multim_not_param;
  std::vector<option_multimetr_one_param_t> v_options_multim_one_param;
};
struct config_device_t
{
  irs::string ip_adress;
  int port;
  std::vector<in_parameter_t> in_parameters;
  std::vector<out_parameter_t> out_parameters;
  std::vector<inf_byte_t> inf_bytes;
  std::vector<measuring_instrument_t> measuring_instruments;
  int index_work_time;
  int index_pos_eeprom;
  int index_pos_offset_eeprom;
  int max_size_correct;
  int delay_meas;
  int count_reset_over_bit;
  irs::string active_file;
};

class manager_config_device_t
{
private:
  config_device_t m_config_device;
  //класс работы с ini-файлом конфигураций устройства
  //irs::ini_file_t m_conf_device_ini_file;
public:
  manager_config_device_t();
  load();
  save();
  read();
  write();
  edit();
};



class TConfDeviceF : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *InParamSG;
  TLabeledEdit *NameConfigLE;
  TLabeledEdit *IPAdressLE;
  TLabeledEdit *PortLE;
  TGroupBox *GroupBox1;
  TGroupBox *GroupBox2;
  TStringGrid *OutParamSG;
  TButton *AddOutParamButton;
  TButton *DelOutParamButton;
  TStringGrid *InfByteExSG;
  TGroupBox *GroupBox3;
  TButton *DelInfByteExButton;
  TButton *AddInfByteExButton;
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TTabSheet *TabSheet2;
  TTabSheet *TabSheet3;
  TCheckListBox *MultimetrListCLB;
  TLabel *Label3;
  TEdit *Edit1;
  TEdit *Edit2;
  TEdit *Edit3;
  TCheckBox *CheckBox2;
  TCheckBox *CheckBox3;
  TCheckBox *CheckBox4;
  TGroupBox *GroupBox4;
  TCheckBox *CheckBox5;
  TCheckBox *CheckBox6;
  TGroupBox *GroupBox5;
  TCheckBox *CheckBox7;
  TCheckBox *CheckBox8;
  TComboBox *MeasTypeCB;
  TLabel *Label4;
  TButton *Button10;
  TListView *ListView1;
  TGroupBox *GroupBox6;
  TComboBox *InterfaceMulCB;
  TGroupBox *GroupBox7;
  TStringGrid *InfByteSG;
  TLabeledEdit *IDConfLE;
  TCheckListBox *CheckListBox1;
  TLabel *Label1;
  TButton *Button2;
  TButton *Button3;
  TButton *Button4;
  void __fastcall Button10Click(TObject *Sender);
  void __fastcall AddOutParamButtonClick(TObject *Sender);
  void __fastcall DelOutParamButtonClick(TObject *Sender);
  void __fastcall AddInfByteExButtonClick(TObject *Sender);
  void __fastcall DelInfByteExButtonClick(TObject *Sender);
private:	// User declarations
  string_grid_t m_string_grid_in_param;
  string_grid_t m_string_grid_out_param;
  string_grid_t m_string_grid_inf_byte;
  string_grid_t m_string_grid_inf_byte_ex;
  list_box_ex_t m_table_in_param;
  list_box_ex_t m_table_out_param;
  list_box_ex_t m_table_inf_byte;
  list_box_ex_t m_table_inf_byte_ex;
  int index_out_param;
  int index_inf_byte_ex;

public:		// User declarations
  __fastcall TConfDeviceF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfDeviceF *ConfDeviceF;
//---------------------------------------------------------------------------
#endif
