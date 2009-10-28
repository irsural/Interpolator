//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "showmessages.h"
#include <iostream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMessagesForm *MessagesForm;
//---------------------------------------------------------------------------
__fastcall TMessagesForm::TMessagesForm(TComponent* Owner)
  : TForm(Owner)
{
}

void TMessagesForm::show_messages(const std::vector<irs::string>& a_messages)
{
  int message_count = a_messages.size();
  irs::string message_count_str = message_count;
  Caption = "Messages: " + static_cast<AnsiString>(message_count_str.c_str());
  MessagesMemo->Clear();
  for (int i = 0; i < message_count; i++) {  
    MessagesMemo->Lines->Add(a_messages[i].c_str());
  }
}
//---------------------------------------------------------------------------
void __fastcall TMessagesForm::Button1Click(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------
