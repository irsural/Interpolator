//---------------------------------------------------------------------------


#include "parsemathematic.h"
AnsiString mathparse::reinterpretator(AnsiString a_str)
{
  AnsiString str="";
  AnsiString str_buf="";
  union
  {
    double var_float;
    __int64 var_integer;
  };
  a_str=converter_operator(a_str);
  for(int i=1; i<=a_str.Length(); i++)
  {  
    //если это цифра
    if((a_str[i]>='0'&&a_str[i]<='9')||a_str[i]==','||a_str[i]=='E'||
      a_str[i]=='e'||((a_str[i]=='+'||a_str[i]=='-')&&
      (a_str[i-1]=='E'||a_str[i-1]=='e')))
    {
      str_buf=str_buf+a_str[i];
      if(i==a_str.Length())
      {
        if(str_buf[1]=='-')
        {
          str=str+"-";
          str_buf.Delete(1,1);
          var_float=StrToFloat(str_buf);
          str=str+IntToStr(var_integer);
        }
        else
        {
          var_float=StrToFloat(str_buf);
          str=str+IntToStr(var_integer);
        }
        break;
      }
    }
    else
    {
      if(str_buf.Length()!=0)
      {
        if(str_buf[1]=='-')
        {
          str=str+"-";
          str_buf.Delete(1,1);
          var_float=StrToFloat(str_buf);
          str=str+IntToStr(var_integer);
        }
        else
        {
          var_float=StrToFloat(str_buf);
          str=str+IntToStr(var_integer);
        }
        str_buf="";
      }
      str=str+a_str[i];
    }
  }
  return str;
}
double mathparse::parse(const AnsiString a_str)
{
  AnsiString str;
  str=reinterpretator(a_str);
  //str=a_str;
  AnsiString sub_str;
  int count_operator=count_operator_str(str);
  union
  {
    double var_float;
    __int64 var_integer;
  };
  int position_left=0;
  int position_right=0;
  double result=0;

  for(int i=1; i<=str.Length(); i++)  //поиск скобок
  {
    if(str[i]=='(')
      position_left=i;
    else if(str[i]==')')
    {
      position_right=i;
      sub_str=str.SubString(position_left+1,
        ((position_right-1)-position_left));
      str.Delete(position_left,position_right-(position_left-1));
      result=parse_operator(sub_str);
      sub_str="";
      if(result<0)
      {
        result=result*(-1);
        var_float=result;
        sub_str="-"+IntToStr(var_integer);
      }
      else
      {
        var_float=result;
        sub_str=IntToStr(var_integer);  //IntToStr
      }
      str.Insert(sub_str, position_left);
      str=converter_operator(str);
      count_operator=count_operator_str(str);
      if(count_operator!=0)
        i=0;
      else
      {
        if(str[1]=='-')
        {
          str.Delete(1,1);
          var_integer=StrToInt64(str);
          result=var_float*(-1);
        }
        else
        {
          var_integer=StrToInt64(str);
          result=var_float;
        }
        break;
      }
    }
    else if(i==str.Length())
    {
      result=parse_operator(str);
      break;
    }
  }
  return result;
}
double mathparse::parse_operator(const AnsiString a_str)
{
  union
  {
    double var_float;
    __int64 var_integer;
  };
  //int pos_arithmetic_operator_back=0;
  AnsiString str=a_str;
  AnsiString sub_str="";
  int pos_current_arithmetic_operator=0;
  int count_operator=count_operator_str(str);
  int number_current_operator=0;
  int left_border_str=0;
  int rigth_border_str=0;
  AnsiString left_operand="";
  AnsiString right_operand="";
  double left_operand_float=0;
  double right_operand_float=0;
  double result_float=0;
  char str_operator='\0';
  int back_index=0;
  bool first_operator=false;
  str=converter_operator(str);
  for(int i=2; i<=str.Length(); i++)
    if(str[i]=='*'||str[i]=='/')
    {
      first_operator=true;
      break;
    }
  for(int i=2; i<=str.Length(); i++)//поиск операции
  {
    if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')&&
    !(str[i+1]=='e'||str[i+1]=='E'))
    {
      if((back_index+1)!=i)
      {
        number_current_operator++;
        pos_current_arithmetic_operator=i;
      }
      back_index=i;
      //если это высокоприоритетные операторы или
      //последний оператор в строке или высокоприоритетных больше нету
      if((str[i]=='*'||str[i]=='/')||
        (count_operator==number_current_operator)||(first_operator==false))
      {
        str_operator=str[i];
        //считываем левый и правый операнд
        if((pos_current_arithmetic_operator-2)==0)
        {
          left_operand=str.SubString(1, 1);
          left_border_str=1;
        }
        else
          for(int i=pos_current_arithmetic_operator-2; i>0; i--)
          {
            if(!(str[i]>='0'&&str[i]<='9'))
            {
              left_operand=str.SubString(
                i+1, pos_current_arithmetic_operator-(i+1));
              left_border_str=i+1;
             break;
            }
            else if(i==2)
            {
              i=1;
              left_operand=str.SubString(
                i, pos_current_arithmetic_operator-i);
              left_border_str=i;
             break;
            }
          }
        if((pos_current_arithmetic_operator+2)==(str.Length()+1))
        {
          right_operand=str.SubString(pos_current_arithmetic_operator+1, 1);
          rigth_border_str=str.Length();
        }
        else
          for(int i=pos_current_arithmetic_operator+2;i<=str.Length(); i++)
          {
            if(!(str[i]>='0'&&str[i]<='9'))
            {
              right_operand=str.SubString(
                pos_current_arithmetic_operator+1,
                  (i-1)-pos_current_arithmetic_operator);
              rigth_border_str=i-1;
             break;
            }
            else if(i==str.Length()-1)
            {
              i=str.Length();
              right_operand=str.SubString(
                pos_current_arithmetic_operator+1,
                  i-pos_current_arithmetic_operator);
              rigth_border_str=i;
             break;
            }
          }
        if(left_operand[1]=='-')
        {
          left_operand.Delete(1,1);
          var_integer=StrToInt64(left_operand);
          left_operand_float=var_float*(-1); 
        }
        else
        {
          var_integer=StrToInt64(left_operand);
          left_operand_float=var_float;
        }
        if(right_operand[1]=='-')
        {
          right_operand.Delete(1,1);
          var_integer=StrToInt64(right_operand);
          right_operand_float=var_float*(-1);
        }
        else
        {
          var_integer=StrToInt64(right_operand);
          right_operand_float=var_float;
        }
        result_float=output_computation(left_operand_float,
          right_operand_float,
          str_operator);
        sub_str="";
        if(result_float<0)
        {
          result_float=result_float*(-1);
          var_float=result_float;
          sub_str="-"+IntToStr(var_integer);  //IntToStr
        }
        else
        {
          var_float=result_float;
          sub_str=IntToStr(var_integer);  //IntToStr
        }
        str.Delete(left_border_str, rigth_border_str-(left_border_str-1));
        str.Insert(sub_str, left_border_str);
        str=converter_operator(str);
        count_operator=count_operator_str(str);
        first_operator=false;
        for(int i=2; i<=str.Length(); i++)
          if(str[i]=='*'||str[i]=='/')
          {
            first_operator=true;
            break;
          }
        if(count_operator!=0)
        {
          i=1;
          number_current_operator=0;
          back_index=0;
        }
        else
        {
          if(str[1]=='-')
          {
            str.Delete(1,1);
            var_integer=StrToInt64(str);
            result_float=var_float*(-1);
          }
          else
          {
            var_integer=StrToInt64(str);
            result_float=var_float;
          }  
          break;
        }
      }
    }
    else if(i==str.Length())
    {
      if(str[1]=='-')
      {
        str.Delete(1,1);
        var_integer=StrToInt64(str);
        result_float=var_float*(-1);
      }
      else
      {
        var_integer=StrToInt64(str);
        result_float=var_float;
      }
      break;
    }
  }
  return result_float;
}
int mathparse::count_operator_str(const AnsiString a_str)
{
  int count=0;
  int back_index=0;
  for(int i=2; i<=a_str.Length(); i++)
    if(a_str[i]=='+'||a_str[i]=='-'||a_str[i]=='*'||a_str[i]=='/')
    {
      if((back_index+1)!=i)
      {
        count++;
      }
      back_index=i;
    }
  return count;
}
 double mathparse::output_computation(AnsiString a_left_operand,
  AnsiString a_rigth_operand,
  char ch_operator)
{
  double result=0.0f;
  double left_operand_float=StrToFloat(a_left_operand);
  double rigth_operand_float=StrToFloat(a_rigth_operand);
  switch(ch_operator)
  {
    case '+':{ result=left_operand_float+rigth_operand_float;
    } break;
    case '-':{ result=left_operand_float-rigth_operand_float;
    } break;
    case '*':{ result=left_operand_float*rigth_operand_float;
    } break;
    case '/':{ result=left_operand_float/rigth_operand_float;
    } break;
  }
  return result;
}
AnsiString mathparse::converter_operator(const AnsiString a_str)
{
  AnsiString str=a_str;
  AnsiString buf_str;
  int back_index=-1;
  for(int i=1; i<=str.Length(); i++)
  {
    if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'/*&&
      !(str[i+1]=='e'||str[i+1]=='E')*/)
    {
      if((back_index+1)==i)
      {
        if((str[i-1]=='+'&&str[i]=='+')||(str[i-1]=='-'&&str[i]=='-'))
        {
          str.Delete(i-1,2);
          str.Insert("+", i-1);
          back_index=-1;
          i=1;
          continue;
        }
        else if(str[i-1]=='+'&&str[i]=='-'&&str[i+1]=='-')
        {
          str.Delete(i-1,3);
          str.Insert("+", i-1);
          back_index=-1;
          i=1;
          continue;
        }
      }
      back_index=i;
    }
  }
  return str;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


 