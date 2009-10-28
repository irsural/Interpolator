//---------------------------------------------------------------------------
#ifndef irsinterpimagingH
#define irsinterpimagingH
//---------------------------------------------------------------------------
struct mValuesXY  //набор значений X,Y для построения графика
{
  float* X;
  float* Y;
  unsigned int LengthXY;//длина массива X,Y. Их длины одинаковые.
};
class mControlImaging
{
  private:
    const TImage* mp_Image;
    //набор графиков(входные необработанные значения X,Y)
    const mValuesXY* mp_RawValueXY;
    unsigned int m_LengthRawValue; //число графиков
    //набор графиков(обработанные значения X,Y)
    mValuesXY* mp_OptimizedValueXY;
    unsigned int m_LengthOptimizedValue; //число графиков
    //запрещаем конструктор по умолчанию
    ControlImaging();
  public:
    mControlImaging(const TImage* ap_Image);
    void WriteRawValuesXY(const mValuesXY* ap_RawValueXY,
      const unsigned int a_LengthRawValue);
    //void OptimizationValuesXY()
};
#endif
