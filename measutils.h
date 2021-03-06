//---------------------------------------------------------------------------

#ifndef measutilsH
#define measutilsH

#include <vector>
#include <measmul.h>

#include <hardflow.h>


//---------------------------------------------------------------------------

enum interface_multim_t {
  im_first = 1,
  im_gpib = im_first,
  im_usb = 2,
  im_com = 3,
  im_last = im_com};

irs::string_t interface_multim_to_str(const interface_multim_t a_interface_mul);
interface_multim_t str_to_interface_multim(
  const irs::string_t& a_str_interface_multim);


enum type_multimetr_t{
  tmul_first = 3,
  tmul_none_multimeter = tmul_first,
  tmul_agilent_3458a = tmul_none_multimeter + 1,
  tmul_v7_78_1 = tmul_agilent_3458a + 1,
  tmul_ch3_85_3r = tmul_v7_78_1 + 1,
  tmul_dummy = tmul_ch3_85_3r + 1,
  tmul_last = tmul_dummy};

irs::string_t type_multimetr_to_str(const type_multimetr_t a_type_multimetr);
type_multimetr_t str_to_type_multimeter(
  const irs::string_t& a_str_type_multimetr);

class value_meas_t
{
private:                
  type_meas_t m_type_meas;
  enum status_process_t{OFF_PROCESS, WAIT_MEAS, MEAS};
  status_process_t m_status_process;
  meas_status_t m_meas_status;
  bool m_on_meas;
  bool m_on_wait_meas;
  bool m_on_connect_multimetr;
  unsigned int m_num;
  unsigned int m_denom;
  counter_t m_test_to;
  //��� ������ � ������������
  //��������� ������ ��� �����������
  irs::handle_t<irs::hardflow_t> m_hardflow;
  //irs::handle_t<mxmultimeter_t> m_multimeter;
  mxmultimeter_t* m_multimeter;
  //������ �����������
  static const mul_addr = 22;
  //meas_status_t cur_status;
  double* mp_value;

public:
  //�����������
  value_meas_t();
  //����������
  ~value_meas_t();
  //inline int set_connect_multimetr(type_multimetr_t a_type_multimetr,
    //multimeter_mode_type_t a_multimeter_mode_type);
  inline void set_connect_multimeter(mxmultimeter_t* ap_mxmultimeter);
  inline void disconnect_multimeter();
  inline void execute_meas(const type_meas_t a_type_meas, double* ap_value);
  inline void abort_meas();
  inline void set_range(const type_meas_t a_type_meas, const double a_range);
  inline meas_status_t get_status_meas();
  //inline double get_value();
  /*��������� ������� �������� ����� ��������� �������� ������ � ����������
  ���������� � ��������*/
  void set_time_wait_meas(int a_time);
  void process_meas();
  void tick();
};
/*inline int value_meas_t::set_connect_multimetr(
  type_multimetr_t a_type_multimetr,
  multimeter_mode_type_t a_multimeter_mode_type)
{
  const multimeter_mode_type_t mode = a_multimeter_mode_type;
  m_multimeter.reset();
  m_hardflow.reset(NULL);

  switch(a_type_multimetr)
  {
    case tmul_agilent_3458a:{
      //m_hardflow.reset(NULL);
      m_multimeter.reset(new mx_agilent_3458a_t(MXIFA_MULTIMETER, mul_addr,
        mode));
      m_on_connect_multimetr = true;
    } break;
    case tmul_v7_78_1:{
      //m_hardflow.reset(NULL);
      m_multimeter.reset(new irs::v7_78_1_t(MXIFA_MULTIMETER, mul_addr, mode));
      m_multimeter->set_aperture(100);
      m_on_connect_multimetr = true;
    } break;
    case tmul_ch3_85_3r: {
      m_hardflow.reset(new irs::com_flow_t(
        "com1", CBR_9600, FALSE, NOPARITY, 8, ONESTOPBIT, DTR_CONTROL_DISABLE));
      m_multimeter.reset(new irs::akip_ch3_85_3r_t(m_hardflow.get(), mode));
      m_on_connect_multimetr = true;
    } break;
    case tmul_dummy: {
      //m_hardflow.reset(IRS_NULL);
      m_multimeter.reset(new irs::dummy_multimeter_t());
      m_on_connect_multimetr = true;
    } break;
    default: {
      m_on_connect_multimetr = false;
    }
  }
  return 0;
}*/
inline void value_meas_t::set_connect_multimeter(mxmultimeter_t* ap_mxmultimeter)
{
  m_multimeter = ap_mxmultimeter;

  if (m_multimeter) {
    if (dynamic_cast<irs::akip_v7_78_1_t*>(m_multimeter)) {
      m_multimeter->set_aperture(100);
    }
    m_on_connect_multimetr = true;
  } else {
    m_on_connect_multimetr = false;
  }
}
inline void value_meas_t::disconnect_multimeter()
{
  /*if (!m_multimeter.is_empty()) {
    m_multimeter->abort();
  }
  m_multimeter.reset(NULL);
  m_hardflow.reset(NULL);*/
  m_multimeter = NULL;
  m_status_process = OFF_PROCESS;
  m_on_connect_multimetr = false;
  m_meas_status = meas_status_success;
  m_on_meas = false;
}
inline void value_meas_t::execute_meas(
  const type_meas_t a_type_meas, double* ap_value)
{
  m_type_meas = a_type_meas;
  mp_value = ap_value;
  m_on_meas = true;
}
inline void value_meas_t::abort_meas()
{
  m_multimeter->abort();
  m_status_process = OFF_PROCESS;
  m_meas_status = meas_status_success;
  m_on_meas = false;
}
inline void value_meas_t::set_range(
  const type_meas_t a_type_meas, const double a_range)
{
  if (m_on_connect_multimetr && (m_type_meas != tm_value))
    m_multimeter->set_range(a_type_meas, a_range);
}
inline meas_status_t value_meas_t::get_status_meas()
  {return m_meas_status;}

#endif
