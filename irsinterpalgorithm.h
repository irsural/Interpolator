//---------------------------------------------------------------------------
#ifndef irsinterpalgorithmH
#define irsinterpalgorithmH
//---------------------------------------------------------------------------
#include <vector>
#include <deque>
using namespace std;


namespace irs{
  class interpolator_algorithm
  {
    private:
      //массивы необработанных данных
      vector<double> mv_col_raw_data; //X пользовательские данные
      vector<double> mv_row_raw_data; //Y
      vector<double> mv_col_data;   //X
      vector<double> mv_row_data;   //Y
      //длина масссивов необработанных данных
      vector<double> mv_coef_k;    //коэффициенты "k" прямых
      vector<double> mv_coef_b;    //коэффициенты "b" прямых
    public:
      interpolator_algorithm();
      ~interpolator_algorithm();
      void clear_data(); //очистка col, row координат и коэффициентов
      void write_raw_data(double av_col_raw_data, double av_row_raw_data);
      inline double read_coef_k_data(int a_index_coef_k_data);
      inline double read_coef_b_data(int a_index_coef_b_data);
      inline double read_col_data(int a_index_col_data);
      inline double read_row_data(int a_index_row_data);
      inline int get_size_coef_data();
      inline int get_size_data();
      /*копирует mv_col_raw_data, mv_row_raw_data в mv_col_data и mv_raw_data*/
      void copy_raw_data();
      /*записывает коэффициенты прямых в mv_coef_k и mv_coef_b,
      соединяющих точки mv_col_data, mv_row_data*/
      bool interpolation_line();
      /*записывает координаты прямой, апроксимирующей, по методу МНК,
      набор точек mv_col_raw_data, mv_row_raw_data,
      в mv_col_data и mv_row_data*/
      bool interpolation_mnk();
      /*оптимизирует функцию, записанную в mv_col_data и mv_row_data,
      путем соединения прямыми точек, вышедших за пределы по точности и
      записывает эту функцию в mv_col_data и mv_row_data. А также записывает
      коэффициенты прямых, соединяющих точки в mv_coef_k и mv_coef_b с помощью
      функции "bool interpolation_line();"*/
      bool optimization_graf(double delta_y);
  };
}
inline double irs::interpolator_algorithm::
  read_coef_k_data(int  a_index_coef_k_data)
  {return mv_coef_k[a_index_coef_k_data];}
inline double irs::interpolator_algorithm::
  read_coef_b_data(int a_index_coef_b_data)
  {return mv_coef_b[a_index_coef_b_data];}
inline double irs::interpolator_algorithm::read_col_data(int a_index_col_data)
  {return mv_col_data[a_index_col_data];}
inline double irs::interpolator_algorithm::read_row_data(int a_index_row_data)
  {return mv_row_data[a_index_row_data];}
inline int irs::interpolator_algorithm::get_size_coef_data()
  {return mv_coef_b.size();}
inline int irs::interpolator_algorithm::get_size_data()
  {return mv_col_data.size();}
#endif
