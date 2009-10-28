//---------------------------------------------------------------------------
#ifndef irsinterpimagingH
#define irsinterpimagingH
//---------------------------------------------------------------------------
struct mValuesXY  //����� �������� X,Y ��� ���������� �������
{
  float* X;
  float* Y;
  unsigned int LengthXY;//����� ������� X,Y. �� ����� ����������.
};
class mControlImaging
{
  private:
    const TImage* mp_Image;
    //����� ��������(������� �������������� �������� X,Y)
    const mValuesXY* mp_RawValueXY;
    unsigned int m_LengthRawValue; //����� ��������
    //����� ��������(������������ �������� X,Y)
    mValuesXY* mp_OptimizedValueXY;
    unsigned int m_LengthOptimizedValue; //����� ��������
    //��������� ����������� �� ���������
    ControlImaging();
  public:
    mControlImaging(const TImage* ap_Image);
    void WriteRawValuesXY(const mValuesXY* ap_RawValueXY,
      const unsigned int a_LengthRawValue);
    //void OptimizationValuesXY()
};
#endif
