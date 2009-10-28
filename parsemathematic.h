//---------------------------------------------------------------------------

#ifndef parsemathematicH
#define parsemathematicH
#include <vcl.h>
//---------------------------------------------------------------------------
class mathparse
{
private:
  AnsiString reinterpretator(AnsiString a_str);
  double parse_operator(const AnsiString a_str);
  int count_operator_str(const AnsiString a_str);
  double output_computation(const AnsiString a_left_operand,
    const AnsiString a_rigth_operand,
    const char ch_operator);
  AnsiString converter_operator(const AnsiString a_str);
public:  
  double parse(const AnsiString a_str);

};
#endif
