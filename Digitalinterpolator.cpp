//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//#include "irsdigint.h"
#include <timer.h>
#include <irsstd.h>
USEFORM("addcolrow.cpp", AddCorRowF);
USEFORM("copytable.cpp", CopyTableForm);
USEFORM("datahandling.cpp", DataHandlingF);
USEFORM("newconfig.cpp", NewConfigF);
USEFORM("optionsoptimize.cpp", OptionsF);
USEFORM("managerf.cpp", ManagerDGIF);
USEFORM("modifidatatable.cpp", ModifiDataTableF);
USEFORM("showmessages.cpp", MessagesForm);
USEFORM("About.cpp", AboutForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
    /*mx_time_int_local_t mx_time_int_local(TIME_TO_CNT(0,1));
    mx_time_int_local.start();
    */
     Application->Initialize();
     Application->CreateForm(__classid(TManagerDGIF), &ManagerDGIF);
     Application->CreateForm(__classid(TOptionsF), &OptionsF);
     Application->CreateForm(__classid(TCopyTableForm), &CopyTableForm);
     Application->CreateForm(__classid(TNewConfigF), &NewConfigF);
     Application->CreateForm(__classid(TAddCorRowF), &AddCorRowF);
     Application->CreateForm(__classid(TMessagesForm), &MessagesForm);
     Application->CreateForm(__classid(TAboutForm), &AboutForm);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
