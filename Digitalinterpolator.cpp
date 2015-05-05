//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <irscberror.h>
//#include "irsdigint.h"
#include <timer.h>
//#include <irsstd.h>
USEFORM("newconfig.cpp", NewConfigF);
USEFORM("optionsoptimize.cpp", OptionsF);
USEFORM("modifidatatable.cpp", ModifiDataTableF);
USEFORM("showmessages.cpp", MessagesForm);
USEFORM("connectionlog.cpp", ConnectionLogForm);
USEFORM("copytable.cpp", CopyTableForm);
USEFORM("About.cpp", AboutForm);
USEFORM("addcolrow.cpp", AddCorRowF);
USEFORM("datahandling.cpp", DataHandlingF);
USEFORM("managerf.cpp", ManagerDGIF);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

  irs::cbuilder::set_error_handler();
  irs::loc();
  try
  {
    /*mx_time_int_local_t mx_time_int_local(TIME_TO_CNT(0,1));
    mx_time_int_local.start();
    */
     Application->Initialize();
     Application->CreateForm(__classid(TManagerDGIF), &ManagerDGIF);
     Application->CreateForm(__classid(TCopyTableForm), &CopyTableForm);
     Application->CreateForm(__classid(TAddCorRowF), &AddCorRowF);
     Application->CreateForm(__classid(TMessagesForm), &MessagesForm);
     Application->CreateForm(__classid(TAboutForm), &AboutForm);
     Application->CreateForm(__classid(TConnectionLogForm), &ConnectionLogForm);
     Application->CreateForm(__classid(TDataHandlingF), &DataHandlingF);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
