//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "irsinterpimaging.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//класс ControlImaging
mControlImaging::mControlImaging(const TImage* ap_Image):
  mp_Image(ap_Image),
  mp_RawValueXY(NULL),
  m_LengthRawValue(0),
  mp_OptimizedValueXY(NULL),
  m_LengthOptimizedValue(NULL)
{}
void mControlImaging::WriteRawValuesXY(const mValuesXY* ap_RawValueXY,
      const unsigned int a_LengthRawValue)
{
  mp_RawValueXY=ap_RawValueXY;
  m_LengthRawValue=a_LengthRawValue;
}
