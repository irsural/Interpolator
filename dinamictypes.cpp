//---------------------------------------------------------------------------
#include "dinamictypes.h"

irs::string_t lang_type_to_str(lang_type_t a_type)
{
  irs::string_t typename_str;
  switch(a_type){
    case type_none:{
      typename_str = irst("type_none");
    } break;
    case type_irs_bool:{
      typename_str = irst("type_irs_bool");
    } break;
    case type_irs_i8:{
      typename_str = irst("type_irs_i8");
    } break;
    case type_irs_u8:{
      typename_str = irst("type_irs_u8");
    } break;
    case type_irs_i16:{
      typename_str = irst("type_irs_i16");
    } break;
    case type_irs_u16:{
      typename_str = irst("type_irs_u16");
    } break;
    case type_irs_i32:{
      typename_str = irst("type_irs_i32");
    } break;
    case type_irs_u32:{
      typename_str = irst("type_irs_u32");
    } break;
    case type_irs_i64:{
      typename_str = irst("type_irs_i64");
    } break;
    case type_irs_u64:{
      typename_str = irst("type_irs_u64");
    } break;
    case type_float:{
      typename_str = irst("type_float");
    } break;
    case type_double:{
      typename_str = irst("type_double");
    } break;
    case type_long_double:{
      typename_str = irst("type_long_double");
    } break;
    default :{
      irs::error_trans_base_t* error_trans = irs::error_trans();
      error_trans->throw_error(
        irs::ec_standard, __FILE__, __LINE__,
          "Отсутствует текстовое представление значения "
          "переменной перечисляемого типа");
    }
  }
  return typename_str;
}
bool str_to_lang_type(const irs::string_t& a_str, lang_type_t& a_type_irs)
{
  bool fsuccess = true;
  if(a_str == irst("type_none")){
    a_type_irs = type_none;
  } else if(a_str == irst("type_irs_bool")){
    a_type_irs = type_irs_bool;
  } else if(a_str == irst("type_irs_i8")){
    a_type_irs = type_irs_i8;
  } else if(a_str == irst("type_irs_u8")){
    a_type_irs = type_irs_u8;
  } else if(a_str == irst("type_irs_i16")){
    a_type_irs = type_irs_i16;
  } else if(a_str == irst("type_irs_u16")){
    a_type_irs = type_irs_u16;
  } else if(a_str == irst("type_irs_i32")){
    a_type_irs = type_irs_i32;
  } else if(a_str == irst("type_irs_u32")){
    a_type_irs = type_irs_u32;
  } else if(a_str == irst("type_irs_i64")){
    a_type_irs = type_irs_i64;
  } else if(a_str == irst("type_irs_u64")){
    a_type_irs = type_irs_u64;
  } else if(a_str == irst("type_float")){
    a_type_irs = type_float;
  } else if(a_str == irst("type_double")){
    a_type_irs = type_double;
  } else if(a_str == irst("type_long_double")){
    a_type_irs = type_long_double;
  } else{
    fsuccess = false;
  }                            
  return fsuccess;
}


int size_of_type(lang_type_t a_type) //размер переменной
{
	switch (a_type) {
    case type_irs_bool:
    case type_irs_i8:
		case type_irs_u8: {
			return sizeof(irs_u8);
		}
    case type_irs_i16:
		case type_irs_u16: {
			return sizeof(irs_u16);
		}
    case type_irs_i32:
		case type_irs_u32: {
			return sizeof(irs_u32);
		}
    case type_irs_i64:
    case type_irs_u64: {
			return sizeof(irs_u64);
		}
		case type_float: {
      return sizeof(float);
		}
		case type_double: {
      return sizeof(double);
		}
    case type_long_double: {
      return sizeof(long double);
		}
    default: {
      IRS_LIB_ASSERT_MSG("Неучтенный тип");
    }
	}
  return 0;
}

dynamic_conn_data_t::dynamic_conn_data_t():
  m_type(type_first),
  m_index(0),
  m_data(0)
{
}
dynamic_conn_data_t::operator long double()
{
  switch (m_type) {
    case type_irs_bool: {
      irs_u8 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_i8: {
      irs_i8 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_u8: {
      irs_u8 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_i16: {
      irs_i16 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_u16: {
      irs_u16 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_i32: {
      irs_i32 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_u32: {
      irs_u32 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_i64: {
      irs_i64 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_irs_u64: {
      irs_u64 var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_float: {
      float var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_double: {
      double var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    case type_long_double: {
      long double var = 0;
      m_data->read((irs_u8 *)&var, m_index, size_of_type(m_type));
      return var;
    }
    default: {
      IRS_LIB_ASSERT_MSG("Неучтенный тип");
    }
  }
  return 0;
}
long double dynamic_conn_data_t::operator=(long double a_val)
{
  switch (m_type) {
    case type_irs_bool: {
      irs_u8 var = (a_val == 0) ? 0 : 1;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_i8: {
      irs_i8 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_u8: {
      irs_u8 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_i16: {
      irs_i16 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_u16: {
      irs_u16 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_i32: {
      irs_i32 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_u32: {
      irs_u32 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_i64: {
      irs_i64 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_irs_u64: {
      irs_u64 var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_float: {
      float var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_double: {
      double var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    case type_long_double: {
      long double var = a_val;
      m_data->write((irs_u8 *)&var, m_index, size_of_type(m_type));
    } break;
    default: {
      IRS_LIB_ASSERT_MSG("Неучтенный тип");
    }
  }
  return a_val;
}

void dynamic_conn_data_t::connect(lang_type_t a_type, irs::mxdata_t *a_data,
  irs_uarc a_index)
{
  m_type = a_type;
  m_index = a_index;
  m_data = a_data;
}

dynamic_array_data_t::dynamic_array_data_t(lang_type_t a_type):
  m_type(a_type),
  m_data_index(0),
  m_array_size(0),
	m_data(0),
  m_elem_size(0),
	m_elem()
{
}
irs_uarc dynamic_array_data_t::connect(
  lang_type_t a_type,
  irs::mxdata_t *a_data,
  irs_uarc a_data_index,
  irs_uarc a_array_size)
{
  m_elem_size = size_of_type(a_type);
  m_type = a_type;
  m_data = a_data;
  m_data_index = a_data_index;
  m_array_size = a_array_size;
  return a_data_index + m_elem_size*m_array_size;
}

dynamic_conn_data_t& dynamic_array_data_t::operator[](irs_uarc a_index)
{
  m_elem.connect(m_type, m_data, m_data_index + a_index*m_elem_size);
  return m_elem;
}



//---------------------------------------------------------------------------


