//---------------------------------------------------------------------------

#ifndef showmessagesH
#define showmessagesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <vector>
#include <irsstdg.h>
//---------------------------------------------------------------------------
class TMessagesForm : public TForm
{
__published:	// IDE-managed Components
  TButton *Button1;
  TMemo *MessagesMemo;
  void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TMessagesForm(TComponent* Owner);
  void show_messages(const std::vector<irs::string>& a_messages);
};
//---------------------------------------------------------------------------
extern PACKAGE TMessagesForm *MessagesForm;
//---------------------------------------------------------------------------
#endif
