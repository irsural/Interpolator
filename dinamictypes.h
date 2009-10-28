//---------------------------------------------------------------------------

#ifndef dinamictypesH
#define dinamictypesH

#include <irsstdg.h>
#include <irserror.h>
enum lang_type_t {
  type_first = 0,
  type_none = type_first,
  type_irs_bool = type_none+1,
  type_irs_i8 = type_irs_bool+1,
  type_irs_u8 = type_irs_i8+1,
  type_irs_i16 = type_irs_u8+1,
  type_irs_u16 = type_irs_i16+1,
  type_irs_i32 = type_irs_u16+1,
  type_irs_u32 = type_irs_i32+1,
  type_irs_i64 = type_irs_u32+1,
  type_irs_u64 = type_irs_i64+1,
  type_float = type_irs_u64+1,
  type_double = type_float+1,
  type_long_double = type_double+1,
  type_last = type_long_double};
  
irs::string lang_type_to_str(lang_type_t a_type);
bool str_to_lang_type(const irs::string& a_str, lang_type_t& a_type_irs);

int size_type(lang_type_t a_type); //размер переменной

class dynamic_conn_data_t //сервис переменной
{
private:
  lang_type_t m_type;
  irs_uarc m_index;
  irs::mxdata_t *m_data;
public:
  dynamic_conn_data_t();
	operator long double();
	long double operator=(long double a_val);
  void connect(lang_type_t, irs::mxdata_t *a_data, irs_uarc a_index);
};

class dynamic_array_data_t //сервис индекса
{
  //array_data_t
public:
private:
  lang_type_t m_type;
  irs_uarc m_data_index;
  irs_uarc m_array_size;//количество элементов
  irs::mxdata_t *m_data;
  dynamic_conn_data_t m_elem;
  int m_elem_size;
public:
  dynamic_array_data_t(lang_type_t a_type = type_none);
  irs_uarc connect(lang_type_t a_type,
    irs::mxdata_t *a_data,
    irs_uarc a_data_index,
    irs_uarc a_array_size);
  dynamic_conn_data_t &operator[](irs_uarc a_index);
  inline int size() const;
};
inline int dynamic_array_data_t::size() const
{return m_elem_size;}
//---------------------------------------------------------------------------
#endif
