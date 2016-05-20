//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <irscberror.h>
#include <timer.h>

//---------------------------------------------------------------------------
USEFORM("modifidatatable.cpp", ModifiDataTableF);
USEFORM("newconfig.cpp", NewConfigF);
USEFORM("managerf.cpp", ManagerDGIF);
USEFORM("showmessages.cpp", MessagesForm);
USEFORM("About.cpp", AboutForm);
USEFORM("addcolrow.cpp", AddCorRowF);
USEFORM("datahandling.cpp", DataHandlingF);
USEFORM("connectionlog.cpp", ConnectionLogForm);
USEFORM("copytable.cpp", CopyTableForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
  irs::cbuilder::set_error_handler();
  irs::loc();

  try
  {
     Application->Initialize();
     Application->MainFormOnTaskBar = true;
     Application->CreateForm(__classid(TManagerDGIF), &ManagerDGIF);
     Application->CreateForm(__classid(TCopyTableForm), &CopyTableForm);
     Application->CreateForm(__classid(TAddCorRowF), &AddCorRowF);
     Application->CreateForm(__classid(TMessagesForm), &MessagesForm);
     Application->CreateForm(__classid(TAboutForm), &AboutForm);
     Application->CreateForm(__classid(TConnectionLogForm), &ConnectionLogForm);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
