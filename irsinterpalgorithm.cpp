//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "irsinterpalgorithm.h"
//#include "irsdigint.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


//класс InterpolatorAlgothm
irs::interpolator_algorithm::interpolator_algorithm():
  mv_col_raw_data(0),
  mv_row_raw_data(0),
  mv_col_data(0),
  mv_row_data(0),
  mv_coef_k(0),
  mv_coef_b(0)
{
}
irs::interpolator_algorithm::~interpolator_algorithm()
{
}
//стирание данных
void irs::interpolator_algorithm::clear_data()
{
  mv_col_raw_data.resize(0);
  mv_row_raw_data.resize(0);
  mv_col_data.resize(0);
  mv_row_data.resize(0);
  mv_coef_k.resize(0);
  mv_coef_b.resize(0);
}
void irs::interpolator_algorithm::
  write_raw_data(double ap_col_raw_data, double ap_row_raw_data)
{
  mv_col_raw_data.push_back(ap_col_raw_data);
  mv_row_raw_data.push_back(ap_row_raw_data);
}
void irs::interpolator_algorithm::copy_raw_data()
{
  mv_col_data=mv_col_raw_data;
  mv_row_data=mv_row_raw_data;
}
bool irs::interpolator_algorithm::interpolation_line()
{
  if(mv_col_data.size()==0||mv_row_data.size()==0)
    return 1;
  mv_coef_k.resize(0);
  mv_coef_b.resize(0);
  for(unsigned int x=1, y=1; x<mv_col_data.size();x++,y++)
  {
    //дополнительна€ проверка от собственных ошибок
    if((mv_col_data[x]-mv_col_data[x-1])==0||
      (mv_col_raw_data[x-1]-mv_col_data[x])==0)
      return 1;
    mv_coef_k.push_back((mv_row_data[y]-mv_row_data[y-1])/
      (mv_col_data[x]-mv_col_data[x-1]));
    mv_coef_b.push_back((mv_row_data[y]*mv_col_data[x-1]-
      mv_col_data[x]*mv_row_data[y-1])/
      (mv_col_data[x-1]-mv_col_data[x]));
  }
  return 0;
}
bool irs::interpolator_algorithm::interpolation_mnk()
{
  if(mv_col_raw_data.size()==0||mv_row_raw_data.size()==0)
    return 1;
  int N=0;  //количество точек в пр€мой
  double S_xy=0.0f, S_x2=0.0f, S_x=0.0f, S_y=0.0f, k=0.0f, b=0.0f;
  for(unsigned int x=0, y=0; x<mv_col_raw_data.size();x++,y++,N++)
  {
    S_xy=S_xy+mv_col_raw_data[x]*mv_row_raw_data[y];
    S_x2=S_x2+mv_col_raw_data[x]*mv_col_raw_data[x];
    S_x=S_x+mv_col_raw_data[x];
    S_y=S_y+mv_row_raw_data[y];
  }
  k=(S_xy-S_x*S_y/N)/(S_x2-S_x*S_x/N);
  b=(S_y-k*S_x)/N;
  //вычисление координат начала и конца пр€мой
  mv_col_data.resize(0.0f);
  mv_row_data.resize(0.0f);
  mv_col_data.push_back(mv_col_raw_data[0]);
  mv_col_data.push_back(mv_col_raw_data[mv_col_raw_data.size()-1]);
  mv_row_data.push_back(k*mv_col_raw_data[0]+b);
  mv_row_data.push_back(k*mv_col_raw_data[mv_col_raw_data.size()-1]+b);
  return 0;
}

bool irs::interpolator_algorithm::optimization_graf(double delta_y)
{
  //поиск точек вышедших за пределы точности
  vector<double> number_x_f;
  vector<double> number_y_f;
  double Module=0.0f;//, k_current=0.0f, b_current=0.0f;
  interpolation_mnk();
  interpolation_line();
  for(unsigned int x=0, y=0; x<mv_col_raw_data.size();x++,y++)
  {
    Module=mv_row_raw_data[y]-(mv_coef_k[0]*mv_col_raw_data[x]+mv_coef_b[0]);
    if(Module<0)
      Module=Module*(-1);
    //формируем массив оптимизированной функции
    if(Module>delta_y)//если вышли за пределы по точности +-delta_y
    {
      if(x>0) //если точка не перва€
      {
        number_x_f.push_back(mv_col_raw_data[x-1]);
        number_y_f.push_back(mv_coef_k[0]*mv_col_raw_data[x-1]+mv_coef_b[0]);
      }
      number_x_f.push_back(mv_col_raw_data[x]);
      number_y_f.push_back(mv_row_raw_data[y]);
      if(x<mv_col_raw_data.size()-1)
      {
        number_x_f.push_back(mv_col_raw_data[x+1]);
        number_y_f.push_back(mv_coef_k[0]*mv_col_raw_data[x+1]+mv_coef_b[0]);
      }
    }
    else if(x==0)
    {
      number_x_f.push_back(mv_col_raw_data[x]);
      number_y_f.push_back(mv_coef_k[0]*mv_col_raw_data[x]+mv_coef_b[0]);
    }
    else if(x==mv_col_raw_data.size()-1)
    {
      number_x_f.push_back(mv_col_raw_data[x]);
      number_y_f.push_back(mv_coef_k[0]*mv_col_raw_data[x]+mv_coef_b[0]);
    }
  }
  //копируем:)
  mv_col_data=number_x_f;
  mv_row_data=number_y_f;
  //вычисл€ем коэффициенты пр€мых
  interpolation_line();
  return 1;
}
