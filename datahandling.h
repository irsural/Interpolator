
//---------------------------------------------------------------------------

#ifndef datahandlingH
#define datahandlingH
//---------------------------------------------------------------------------

#include <irsdefs.h>
#include <irsstd.h>
#include <irscpp.h>
#include <irsstd.h>
#include <irsfunnel.h>
#include <irsdevices.h>
#include <mxnetc.h>
#include <inifiles.hpp>
#include <timer.h>
#include <irscberror.h>
#include <irstime.h>
#include <cbcomp.h>
#include <irsalg.h>
#include <irstable.h>
#include <imp_filt.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <CheckLst.hpp>
#include <MxChart.h>
#include <Buttons.hpp>
#include <float.h>
#include <Math.hpp>
#include <ActnCtrls.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <ActnMenus.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <StdActns.hpp>
#include <SysUtils.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>



//#pragma hdrstop
#include "mxini.h"
#include "servisfunction.h"
//#include "avtomeas.h"
#include "copytable.h"
#include "optionsprog.h"
#include "addcolrow.h"
#include "measutils.h"
//#include "newconfig.h"
//#include "dinamictypes.h"
#include "debugdigitalinterpolator.h"

//#include "configdevice.h"
#include "modifidatatable.h"
#include "connectionlog.h"
#include "comparison.h"
#include "parameters.h"
#include "About.h"
#include <System.Actions.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>

enum mode_program_t {
  mode_prog_multi_channel,
  mode_prog_single_channel
};

enum status_process_meas_t {
  spm_off_process,
  spb_wait_connect,
  spb_wait_ext_trig_set_apply_params_and_bits,
  spb_wait_apply_extra_params_and_bits,
  spm_jump_next_elem,
  spm_wait_ext_trig_off_signal,
  spm_wait_off_signal,
  spm_wait_ext_trig_set_range,
  spm_set_range,
  spm_wait_set_range,
  spm_mode_setting,
  spm_wait_mode_setting,
  spm_wait_ext_trig_control_wait_mode_setting,
  spm_control_wait_mode_setting,
  spm_wait_external_trig_meas,
  sps_start_meas,
  spm_execute_meas,
  spm_wait_execute_meas,
  spm_wait_external_trig_processing_data,
  spm_processing_data,
  spm_processing_filter_data,
  spm_wait_ext_trig_process_data_to_next_elem,
  spm_reset,                                      // -> spm_wait_set_extra_vars
  spm_wait_set_extra_vars                         // -> spm_off_process
};

template <class T>
class stability_control_t
{
public:
  stability_control_t(T a_reference = 0, T a_deviation = 0,
    double a_tability_min_time = 5);
  void set_reference(T a_reference);
  void set_diviation(T a_diviation);
  void set_current(T a_current);
  double get_stable_state_time() const;
  bool stable_state() const;
  void set_stability_min_time(double a_min_time);
  void reset();
private:
  stability_control_t();
  T difference(T a_first, T a_second) const;
  T m_reference;
  T m_diviation;
  irs::measure_time_t m_time;
  //! \brief ����������� �����, ��� �����������, ��� �������� ���������
  double m_stability_min_time;
};

template <class T>
stability_control_t<T>::stability_control_t(T a_reference,
  T a_deviation, double a_tability_min_time
):
  m_reference(a_reference),
  m_diviation((m_diviation < 0) ? (m_diviation*-1) : m_diviation),
  m_time(),
  m_stability_min_time(a_tability_min_time)
{ 
  m_time.start();
}

template <class T>
void stability_control_t<T>::set_reference(T a_reference)
{
  m_reference = a_reference;
}

template <class T>
void stability_control_t<T>::set_diviation(T a_diviation)
{
  m_diviation = a_diviation;
}

template <class T>
void stability_control_t<T>::set_current(T a_current)
{
  if (difference(m_reference, a_current) > m_diviation) {
    m_time.start();
  }
}

template <class T>
double stability_control_t<T>::get_stable_state_time() const
{
  return m_time.get();
}

template <class T>
bool stability_control_t<T>::stable_state() const
{
  return m_time.get() >= m_stability_min_time;
}

template <class T>
void stability_control_t<T>::set_stability_min_time(double a_min_time)
{
  m_stability_min_time = a_min_time;
}

template <class T>
void stability_control_t<T>::reset()
{
  m_time.start();
}

template <class T>
T stability_control_t<T>::difference(T a_first, T a_second) const
{
  return (a_first < a_second) ? (a_second - a_first) : (a_first - a_second);
}

//---------------------------------------------------------------------------
class test1_t
{
public:
  test1_t()
  {
  }
  ~test1_t()
  {
    int a = 0;
  }
};



class TDataHandlingF : public TForm
{
__published:	// IDE-managed Components
  TPanel *TableValuePanel;
  TStringGrid *RawDataStringGrid;
  TGroupBox *OptionsGroupBox;
  TPanel *ButtomPanel;
  TTimer *FormDataHandingTimer;
  TMemo *LogMemo;
  TActionManager *ActionManager1;
  TImageList *ActionManagerImageList;
  TFileOpen *FileOpen;
  TFileSaveAs *FileSaveAs;
  TAction *FileSave;
  TAction *CreateColAction;
  TAction *DeleteColAction;
  TAction *CreateRowAction;
  TAction *DeleteRowAction;
  TAction *AddGroupCellsAction;
  TAction *FileReOpen;
  TAction *StartAutoVoltMeasAction;
  TAction *StopVoltMeasAction;
  TAction *StartAutoVoltMeasActiveCellsAction;
  TAction *OnCorrectAction;
  TAction *OnMismathAction;
  TMainMenu *MainMenu1;
  TMenuItem *FileOpenM;
  TMenuItem *N2;
  TMenuItem *FileReOpenM;
  TMenuItem *FileSaveM;
  TMenuItem *N5;
  TMenuItem *N6;
  TMenuItem *CreateColM;
  TMenuItem *DeleteColM;
  TMenuItem *CreateRowM;
  TMenuItem *DeleteRowM;
  TMenuItem *AddGroupCellsM;
  TMenuItem *N13;
  TMenuItem *StartAutoVoltMeasM;
  TMenuItem *StartAutoVoltMeasActiveCellsM;
  TMenuItem *StopVoltMeasM;
  TMenuItem *N1;
  TMenuItem *SetJumpHorizontalDownM;
  TMenuItem *SetJumpHorizontalUpM;
  TMenuItem *SetJumpVerticalForwardM;
  TMenuItem *SetJumpVerticalBackM;
  TMenuItem *N9;
  TMenuItem *SetJumpSmoothM;
  TAction *SetJumpHorizontalDownAction;
  TAction *SetJumpHorizontalUpAction;
  TAction *SetJumpVerticalForwardAction;
  TAction *SetJumpVerticalBackAction;
  TAction *SetJumpSmoothAction;
  TMenuItem *TypeMeas;
  TMenuItem *VoltDCMeasM;
  TMenuItem *VoltACMeasM;
  TMenuItem *CurrentDCMeasM;
  TMenuItem *Resistance2xMeasM;
  TMenuItem *Resistance4xMeasM;
  TAction *SetVoltDCMeasAction;
  TAction *SetVoltACMeasAction;
  TAction *SetCurrentDCMeasAction;
  TAction *SetResistance2xMeasAction;
  TAction *SetResistance4xMeasAction;
  TAction *SetCurrentACMeasAction;
  TAction *SetFrequencyMeasAction;
  TMenuItem *CurrentACMeasM;
  TMenuItem *FrequencyMeasM;
  TMenuItem *U1;
  TMenuItem *ZX1;
  TMenuItem *ZY1;
  TMenuItem *ZX2;
  TMenuItem *ZY2;
  TMenuItem *N3;
  TAction *AddSubtableAction;
  TMenuItem *AddSubtableM;
  TAction *DelSubtableAction;
  TMenuItem *DelSubtableM;
  TMenuItem *EditModeM;
  TMenuItem *N4;
  TPanel *Panel1;
  TPanel *LeftPanel;
  TComboBox *ConfigCB;
  TButton *EditConfigButton;
  TPanel *Panel3;
  TButton *CreateConfigButton;
  TPanel *RightPanel;
  TComboBox *PatternOfMeasuringInstrumentCB;
  TPanel *Panel5;
  TLabeledEdit *CurrentStatusLabeledEdit;
  TImageList *MainMenuImageList;
  TMenuItem *OptionsMeas;
  TMenuItem *CorrectModeM;
  TMenuItem *MismatchModeM;
  TAction *CorrectModeAction;
  TAction *MismatchModeAction;
  TButton *CloseFormButton;
  TMenuItem *N7;
  TMenuItem *WriteDataM;
  TAction *WriteDataAction;
  TAction *SetPhaseMeasAction;
  TAction *SetPhaseAverageMeasAction;
  TAction *SetTimeIntervalMeasAction;
  TAction *SetTimeIntervalAverageMeasAction;
  TMenuItem *PhaseMeasM;
  TMenuItem *PhaseAverageMeasM;
  TMenuItem *TimeIntervalMeasM;
  TMenuItem *TimeIntervalAverageMeasM;
  TOpenDialog *FileOpenDialog1;
  TAction *AddTableAction;
  TMenuItem *N8;
  TMenuItem *N10;
  TCheckBox *ModeProgramCB;
  TAction *RestructDataType1Action;
  TMenuItem *RestructDataType1M;
  TMenuItem *N11;
  TMenuItem *TableDefM;
  TMenuItem *ClearTableM;
  TMenuItem *CleaContentTableM;
  TAction *ClearTableAction;
  TAction *TableDefAction;
  TAction *ClearContentTableAction;
  TMenuItem *N12;
  TMenuItem *N14;
  TMenuItem *Exele1;
  TAction *AutoUpdateChartAction;
  TLabeledEdit *TimeMeasLE;
  TLabeledEdit *IntervalTimeMeasLE;
  TLabeledEdit *WorkTimeDeviceLE;
  TSaveDialog *SaveFileDialog;
  TAction *ExportTableToMExcelCsvFileAction;
  TAction *ClearContentColTableAction;
  TAction *ClearContentRowTableAction;
  TMenuItem *CleaContentColTableM;
  TMenuItem *CleaContentRowTableM;
  TAction *InversionSignConrentTableAction;
  TMenuItem *N15;
  TProgressBar *ProgressBar1;
  TLabel *CommentProgressL;
  TLabel *PercentProgressL;
  TAction *VerificationDataAction;
  TMenuItem *N16;
  TAction *ModifiTableDataAction;
  TMenuItem *ModifiTableDataM;
  TAction *AboutAction;
  TMenuItem *N17;
  TMenuItem *AboutM;
  TGroupBox *TemperatureControlGroupBox;
  TLabeledEdit *ReferenceTemperatureLabeledEdit;
  TLabeledEdit *CurrentTemperatureLabeledEdit;
  TLabeledEdit *DifferenceTemperatureLabeledEdit;
  TGroupBox *OutParamControlGroupBox;
  TLabeledEdit *CurrentOutParamLabeledEdit;
  TLabeledEdit *ReferenceOutParamLabeledEdit;
  TLabeledEdit *AbsoluteDiffOutParamLabeledEdit;
  TLabeledEdit *RemainingTimeForStableState;
  TMenuItem *N18;
  TMenuItem *TSTLANMenuItem;
  TMenuItem *ConnectionLogMenuItem;
  TMenuItem *ConnectMenuItem;
  TAction *ConnectAction;
  TAction *TSTLANAction;
  TAction *ConnectionLogAction;
  TButton *DeleteConfigButton;
  TButton *ShowMultimeterOptionsButton;
  TAction *ShowMeasPointChartAction;
  TMenuItem *N19;
  TMenuItem *N20;
  TMenuItem *N21;
  TMenuItem *ComparsionMenuItem;
  TMenuItem *ParametersMenuItem;
  TAction *SetTableToSettingsAction;
  TMenuItem *N22;
  TAction *LockMeasCellsRangeAction;
  TActionToolBar *ActionToolBar5;
  TAction *Action2;
  TAction *AutoSaveMeasAction;
  TMenuItem *N23;
  TMenuItem *N25;
  TAction *CopyCellsConfligAction;
  TAction *PasteCellsConfigAction;
  TMenuItem *N24;
  TMenuItem *N26;
  TPopupMenu *TablePopupMenu;
  TMenuItem *N27;
  TMenuItem *N28;
  TAction *SelectAllCellsAction;
  TMenuItem *N29;
  TMenuItem *N30;
  TAction *ShowSameCellConfigsAction;
  TMenuItem *N31;
  TMenuItem *N33;
  TMenuItem *measureMethodAverageCheckbox;
  TMenuItem *measureMethodImpulseFilterCheckbox;
  void __fastcall RawDataStringGridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall RawDataStringGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDataHandingTimerTimer(TObject *Sender);
  void __fastcall ClearTableButtonClick(TObject *Sender);
  void __fastcall RawDataStringGridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
  //void __fastcall OnCorrectSpeedButtonClick(TObject *Sender);
  void __fastcall AddGroupCellsButtonClick(TObject *Sender);
  //void __fastcall OnMismathSpeedButtonClick(TObject *Sender);
  void __fastcall CreateColActionExecute(TObject *Sender);
  void __fastcall DeleteColActionExecute(TObject *Sender);
  void __fastcall CreateRowActionExecute(TObject *Sender);
  void __fastcall DeleteRowActionExecute(TObject *Sender);
  void __fastcall AddGroupCellsActionExecute(TObject *Sender);
  void __fastcall StartAutoVoltMeasActionExecute(TObject *Sender);
  void __fastcall StopVoltMeasActionExecute(TObject *Sender);
  void __fastcall StartAutoVoltMeasActiveCellsActionExecute(
          TObject *Sender);
  void __fastcall FileSaveExecute(TObject *Sender);
  void __fastcall FileSaveAsAccept(TObject *Sender);
  void __fastcall FileSaveAsBeforeExecute(TObject *Sender);
  void __fastcall FileReOpenExecute(TObject *Sender);
  void __fastcall FileOpenAccept(TObject *Sender);
  void __fastcall SetJumpHorizontalDownActionExecute(TObject *Sender);
  void __fastcall SetJumpHorizontalUpActionExecute(TObject *Sender);
  void __fastcall SetJumpVerticalForwardActionExecute(TObject *Sender);
  void __fastcall SetJumpVerticalBackActionExecute(TObject *Sender);
  void __fastcall SetJumpSmoothActionExecute(TObject *Sender);
  void __fastcall SetVoltDCMeasActionExecute(TObject *Sender);
  void __fastcall SetVoltACMeasActionExecute(TObject *Sender);
  void __fastcall SetCurrentDCMeasActionExecute(TObject *Sender);
  void __fastcall SetResistance2xMeasActionExecute(TObject *Sender);
  void __fastcall SetResistance4xMeasActionExecute(TObject *Sender);
  void __fastcall SetCurrentACMeasActionExecute(TObject *Sender);
  void __fastcall SetFrequencyMeasActionExecute(TObject *Sender);
  void __fastcall Button4Click(TObject *Sender);
  void __fastcall Button6Click(TObject *Sender);
  void __fastcall Button7Click(TObject *Sender);
  void __fastcall Button5Click(TObject *Sender);
  void __fastcall ZX1Click(TObject *Sender);
  void __fastcall ZY1Click(TObject *Sender);
  void __fastcall ZX2Click(TObject *Sender);
  void __fastcall ZY2Click(TObject *Sender);
  void __fastcall N3Click(TObject *Sender);
  void __fastcall AddSubtableActionExecute(TObject *Sender);
  void __fastcall DelSubtableActionExecute(TObject *Sender);
  void __fastcall RawDataStringGridGetEditText(TObject *Sender, int ACol,
          int ARow, UnicodeString &Value);
  void __fastcall CreateConfigButtonClick(TObject *Sender);
  void __fastcall EditConfigButtonClick(TObject *Sender);
  void __fastcall CorrectModeActionExecute(TObject *Sender);
  void __fastcall MismatchModeActionExecute(TObject *Sender);
  void __fastcall CloseFormButtonClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall WriteDataActionExecute(TObject *Sender);
  void __fastcall Panel1Resize(TObject *Sender);
  void __fastcall ConfigCBChange(TObject *Sender);
  void __fastcall SetPhaseMeasActionExecute(TObject *Sender);
  void __fastcall SetPhaseAverageMeasActionExecute(TObject *Sender);
  void __fastcall SetTimeIntervalMeasActionExecute(TObject *Sender);
  void __fastcall SetTimeIntervalAverageMeasActionExecute(TObject *Sender);
  void __fastcall AddTableActionExecute(TObject *Sender);
  void __fastcall ModeProgramCBClick(TObject *Sender);
  void __fastcall RestructDataType1ActionExecute(TObject *Sender);
  void __fastcall ClearTableActionExecute(TObject *Sender);
  void __fastcall TableDefActionExecute(TObject *Sender);
  void __fastcall ClearContentTableActionExecute(TObject *Sender);
  void __fastcall AutoUpdateChartActionExecute(TObject *Sender);
  void __fastcall ExportTableToMExcelCsvFileActionExecute(TObject *Sender);
  void __fastcall ClearContentColTableActionExecute(TObject *Sender);
  void __fastcall ClearContentRowTableActionExecute(TObject *Sender);
  void __fastcall InversionSignConrentTableActionExecute(TObject *Sender);
  void __fastcall VerificationDataActionExecute(TObject *Sender);
  void __fastcall ModifiTableDataActionExecute(TObject *Sender);
  void __fastcall AboutActionExecute(TObject *Sender);
  void __fastcall RawDataStringGridExit(TObject *Sender);
  void __fastcall ConnectionLogMenuItemClick(TObject *Sender);
  void __fastcall ConnectActionExecute(TObject *Sender);
  void __fastcall TSTLANActionExecute(TObject *Sender);
  void __fastcall ConnectionLogActionExecute(TObject *Sender);
  void __fastcall DeleteConfigButtonClick(TObject *Sender);
  void __fastcall ShowMultimeterOptionsButtonClick(TObject *Sender);
  void __fastcall PatternOfMeasuringInstrumentCBChange(TObject *Sender);
  void __fastcall ShowMeasPointChartActionExecute(TObject *Sender);
  void __fastcall ComparsionMenuItemClick(TObject *Sender);
  void __fastcall ParametersMenuItemClick(TObject *Sender);
  void __fastcall RawDataStringGridMouseActivate(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
  void __fastcall LockMeasCellsRangeActionExecute(TObject *Sender);
  void __fastcall AutoSaveMeasActionExecute(TObject *Sender);
  void __fastcall CopyCellsConfligActionExecute(TObject *Sender);
  void __fastcall PasteCellsConfigActionExecute(TObject *Sender);
  void __fastcall SelectAllCellsActionExecute(TObject *Sender);
  void __fastcall ShowSameCellConfigsActionExecute(TObject *Sender);
  void __fastcall measureMethodAverageCheckboxClick(TObject *Sender);
  void __fastcall measureMethodImpulseFilterCheckboxClick(TObject *Sender);



private:	// User declarations
  typedef size_t size_type;
  typedef irs::string_t string_type;
  typedef irs::ostringstream_t ostringstream_type;
  //��� ���������
  String m_prog_name;
  mode_program_t m_mode_program;
  file_name_service_t m_file_name_service;
  //��� ����� �������� ���������
  String m_name_main_opt_ini_file;
  //����� ������ � ini-������ �������� ���������
  irs::ini_file_t m_main_opt_ini_file;

  //����� �����
  //log_t m_log;
  log_message_t m_log_message;

  enum { m_memobuf_size = 500 };
  irs::union_streambuf m_stream_buf;
  irs::handle_t <ofstream> mp_log_stream;
  irs::handle_t<irs::memobuf> mp_memo_buf;

  TForm* mp_manager_channel;
  //������������� ����� ������������ �������� ����������
  const String m_fileid_conf;
  config_calibr_t m_config_calibr;
  config_calibr_t m_conf_calibr_buf;
  config_calibr_t m_config_calibr_ref_channel;

  test1_t m_test1;  
  inf_in_param_t m_inf_in_param;
  ///


  TIniFile* mp_options_prog_ini_file;
  // ��� ������ � ������������
  // ��������� ������ ��� �����������
  value_meas_t m_value_meas;
  enum status_connect_t{WAIT_CONNECT, CONNECT, OUT_DATA};
  enum status_connect_eeprom_t{
    sce_off,
    sce_create_interface_eeprom,
    sce_wait_connect_eeprom,
    sce_set_param_eeprom,
    sce_verification_eeprom,
    sce_wait_read_eeprom,
    sce_write_eeprom,
    sce_wait_write_eeprom,
    sce_reset};

  const String m_name_file_options_ini;// = "options.ini";
  enum {
    progress_percent_precision = 6,
    progress_percent_digits = 3
  };
  correct_map_t m_correct_map;
  correct_map_t m_correct_map_local;
  struct device_t
  {
    string_type type;
    irs::handle_t<irs::tstlan4_base_t> tstlan4lib;
    irs::handle_t<irs::mxdata_assembly_t> mxdata_assembly;
    irs::handle_t<TConnectionLogForm> connection_log;
    ~device_t()
    {
      tstlan4lib.reset();
      mxdata_assembly.reset();
      connection_log.reset();
    }
  };

  irs::handle_t<data_map_t> mp_data_map_ref_channel;
  irs::chart::builder_chart_window_t m_device_chart;
  device2_t m_device;

  device2_t m_ref_device;
  irs::handle_t<mxnetc> mp_mxnet_ref_channel;

  irs::handle_t<irs::mxdata_to_mxnet_t> mp_mxnet_data_ref_channel;

  irs::handle_t<irs::funnel_client_t> mp_eeprom;
  irs::handle_t<irs::local_data_t> mp_local_data;


  irs::handle_t<irs::mxmultimeter_assembly_t> mp_mxmultimeter_assembly;

  table_data_t* mp_active_table;
  int           m_start_col;
  int           m_start_row;
  TRect         m_cells_range;
  coord_cell_t  m_copied_cell_config;
  TRect         m_meas_cells_range;
  coord_cell_t  m_start_cell;

  status_connect_t status_connect;
  status_connect_eeprom_t status_connect_eeprom;
  String m_cur_config_device;
  String m_cur_config_multimetr;
  // ������������ ���������� ������� ���������
  bool m_load_conf_calibr_device_success;
  // ����, ���� ��� ������� ������������� ���������� ������
  // � ������������� ����������
  bool m_bad_cells;
  //���������� ������������ ������������
  bool m_on_block_reconfiguration;
  // ������ ������� ����������� ������������ � ComboBox
  int m_cur_index_conf_calibr;
  // ��� �������� ����� ������������
  String m_cur_filename_conf_calibr_device;

  bool m_on_write_data_eeprom;
  bool m_on_verification_data_eeprom;
  bool m_on_out_data;
  bool m_on_correct;
  bool m_correct_mode_previous_stat;
  bool m_is_autosave_meas_enabled;

  enum measure_method_t {
    mm_impulse_filter,
    mm_average
  };

  int m_measure_method;

  // ����������� ������ � ������ ��� ��������
  int m_need_size_memory;

  //����� ����������
  bool m_on_mismatch_state;
  bool m_on_mismatch_state_previous;

  bool m_non_first_connect_mxnet_data;

  // ������������ �������� �������������� �����(��� ���������, ��� ����������)
  bool m_on_reset_functional_bits;

  options_optimize_type_mnk_t m_options_mnk;
  options_optimize_type_correct_t m_options_correct;
  options_calculating_coef_t m_options_coef;

  vector<double> mv_col_user_data;  //���������� X
  vector<double> mv_row_user_data;  //���������� Y
  vector<double> mv_top_user_data;  //���������� Z
  vector<double> mv_col_optimal_data;
  vector<double> mv_row_optimal_data;
  vector<double> mv_top_optimal_data;
  vector<double> mv_coef_data;

  vector<String> mv_list_config_calibr;

  //��������� ��������
  struct chart_t
  {
  private:
    irs::chart::builder_chart_window_t builder_chart_window_z_of_x;
    irs::chart::builder_chart_window_t builder_chart_window_z_of_y;
    //��������� ������ ��������
    irs::chart_window_t* p_chart_window_z_of_x;
    irs::chart_window_t* p_chart_window_z_of_y;
    vector<string_type> z_of_x_charts;
    vector<string_type> z_of_y_charts;
  public:
    bool on_auto_update;
    bool adfa;
    chart_t();
    void add_chart_z_of_x_cur_cell(
      const table_data_t* ap_table_data, const inf_in_param_t& a_inf_in_param);
    void add_chart_z_of_y_cur_cell(
      const table_data_t* ap_table_data, const inf_in_param_t& a_inf_in_param);
    void add_all_chart_z_of_x(
      const table_data_t* ap_table_data,
      const inf_in_param_t& a_inf_in_param,
      const bool a_on_update = false);
    void add_all_chart_z_of_y(
      const table_data_t* ap_table_data,
      const inf_in_param_t& a_inf_in_param,
      const bool a_on_update = false);
    void clear_chart();
    void auto_update_on();
    void auto_update_off();
    bool get_auto_update_stat();
  private:
    void add_chart_z_of_x(
      const table_data_t* ap_table_data,
      const inf_in_param_t& a_inf_in_param,
      const int a_row_z_data,
      const bool a_on_update = false);
    void add_chart_z_of_y(
      const table_data_t* ap_table_data,
      const inf_in_param_t& a_inf_in_param,
      const int a_col_z_data,
      const int a_row_z_data,
      const bool a_on_update = false);
    void add_chart_z_of_x(
      const string_type& a_name_graph,
      const std::vector<cell_t>& a_p_points,
      const std::vector<cell_t>& a_x_points,
      const inf_in_param_t& a_inf_in_param,
      const double a_norm_koef);
    void add_chart_z_of_y(
      const string_type& a_name_graph,
      const std::vector<cell_t>& a_p_points,
      const std::vector<cell_t>& a_y_points,
      const inf_in_param_t& a_inf_in_param,
      const double a_norm_koef);

    void save_name_chart_z_of_x(const string_type& a_name_chart);
    void save_name_chart_z_of_y(const string_type& a_name_chart);
  }
  m_chart;

  irs::handle_t<irs::chart::builder_chart_window_t> mp_meas_point_chart;


  irs::loop_timer_t m_timer_chart_auto_update;

  bool m_successfully_mode_setting;

  //����������, ������������ ������� ��������� ����������
  bool m_on_connect_mxnet_data;
  bool m_on_connect_eeprom;

  //������ ����� ������� ��������������� ��������� ����������
  bool m_on_start_new_auto_meas;
  //������� �������
  bool m_auto_meas_is_running;
  //���������� �������
  bool m_on_stop_process_auto_volt_meas;
  //������� ��������������� ��������� � �������� ������
  bool m_on_process_auto_meas_active_cell;

  //��� ������������� ��������������� ������
  bool on_reg_ready_back_cycle;

  enum device_mode_status_t{DM_SUCCESS, DM_BUSY};

  bool m_on_jump_smooth;

  type_jump_next_elem_t m_type_jump_next_elem;
  String m_str_type_jump_next_elem;
  status_process_meas_t m_status_process_meas;

  type_meas_t m_type_meas;
  struct cur_elem_t
  {
    cur_elem_t()
    {}
    cur_elem_t(unsigned int a_col, unsigned int a_row):
      col(a_col),
      row(a_row)
    {}
    unsigned int col;
    unsigned int row;
  };

  stability_control_t<double> m_out_param_stability_control;
  irs::measure_time_t m_out_param_stable_min_time;

  enum { temperature_stability_min_time = 4 };
  stability_control_t<double> m_temperature_stability_control;
  irs::measure_time_t m_temperature_stable_min_time;
  // ��������� ������
  bool m_on_reg_ready;

  counter_t m_delay_start_control_reg;
  counter_t m_delay_operating_duty;
  counter_t m_delay_control_error_bit;
  counter_t m_delay_next_cell;

  irs::timer_t m_restart_timer;
  irs::timer_t m_timer_delay_control;
  irs::timer_t m_timer_delay_operating_duty;
  irs::timer_t m_timer_delay_control_error_bit;
  irs::timer_t m_timer_delay_next_cell;
  irs::timer_t m_timer_waiting_set_extra_vars;
  bool m_reset_time_meas;
  // ������� ������� ���������
  irs::measure_time_t m_time_meas;
  // ���������� ���������� �����
  int m_count_point_meas;
  // ���������� �����, ����������� ����� ���������� ���������
  int m_previous_count_point_meas;
  // ��������: ����� � �������
  double m_cell_per_sec;
  // ���������� ���������� ����� �� ����� �������
  int m_cell_count_end;
  // ����� ���������, ����������� ����� ��������� ���������� ������
  double m_previous_time_meas_sec;

  m_copy_data m_status_copy_table;
  table_string_grid_t table_string_grid1;
  table_data_t m_table_raw_data;
  table_data_size_t m_table_data_size;
  manager_traffic_cell_t m_manager_traffic_cell;
  vector<int> mv_config_table_copy;
  int m_memory_capacity;
  param_cur_cell_t m_param_cur_cell;
  cell_config_calibr_t m_cur_cell_cfg;
  cell_config_calibr_t m_prev_cell_cfg;
  inline void reset_stat_stop_process_avto_volt_meas();
  
  //��������� ���� ��������
  void set_type_jump(type_jump_next_elem_t a_type_jump_next_elem);
  void set_jump_smooth();
  void reset_jump_smooth();

  int m_select_col;
  int m_select_row;
  double m_start_num_col;
  double m_end_num_col;
  double m_step_num_col;
  type_step_t m_type_step_col;
  double m_start_num_row;
  double m_end_num_row;
  double m_step_num_row;
  bool m_successfully_add_col;
  bool m_successfully_add_row;
  type_step_t m_type_step_row;
  bool m_add_col_or_row_successfuly;
  bool m_enabled_fixes_cells;

  double m_value_meas_multimetr;

  struct cur_cell_t
  {
    int col;
    int row;
    string_type value_str;
    bool init;
    cur_cell_t():
      col(0),
      row(0),
      value_str(),
      init(false)
    {}
    cur_cell_t(
      const int a_col,
      const int a_row,
      const string_type a_value_str,
      const bool a_init):
      col(a_col), row(a_row),value_str(a_value_str), init(a_init)
    {}
  } m_cur_cell_table1;
  param_cur_cell_t m_default_param_cur_cell;
  irs_u32 m_cur_count_reset_over_bit;
  double m_y_out;
  param_filter_t m_y_out_filter;
  irs::filt_imp_noise_t m_impulse_filter;
  irs::fast_average_t<double, double> m_meas_value_filter;
  typedef irs::chart_data::point_t<double> point_type;
  typedef vector<point_type> points_type;
  vector<point_type> m_points;
  irs::timer_t m_meas_value_filter_timer;
  irs::measure_time_t m_meas_value_filter_elapsed_time;
  // ���������� ������������ ������ ��� ��������������� ������
  // ������, ��������� �� ������� onClose
  bool m_on_close_form_stat;
  // ������� ������
  bool m_on_external;
  struct exec_progress_t {
    TLabel *p_comment;
    TLabel *p_percent_progress;
    TProgressBar *p_progress_bar;
  private:
    exec_progress_t();
  public:
    exec_progress_t(
      TLabel *ap_comment,
      TLabel *ap_percent_progressm,
      TProgressBar *ap_progress_bar
    ):
      p_comment(ap_comment),
      p_percent_progress(ap_percent_progressm),
      p_progress_bar(ap_progress_bar)
    {}
    void show()
    {
      if ((!p_comment->Visible) && (p_comment != IRS_NULL)) {
        p_comment->Visible = true;
      }
      if ((!p_percent_progress->Visible)  && (p_percent_progress != IRS_NULL)) {
        p_percent_progress->Visible = true;
      }
      if ((!p_progress_bar->Visible)  && (p_percent_progress != IRS_NULL)) {
        p_progress_bar->Visible = true;
      }
    }
    void hide()
    {
      if (p_comment->Visible && (p_comment != IRS_NULL)) {
        p_comment->Visible = false;
      }
      if (p_percent_progress->Visible  && (p_percent_progress != IRS_NULL)) {
        p_percent_progress->Visible = false;
      }
      if (p_progress_bar->Visible  && (p_percent_progress != IRS_NULL)) {
        p_progress_bar->Visible = false;
      }
    }
    void clear()
    {
      if (p_comment->Visible && (p_comment != IRS_NULL)) {
        p_comment->Caption = "";
      }
      if (p_percent_progress->Visible  && (p_percent_progress != IRS_NULL)) {
        p_percent_progress->Caption = "";
      }
      if (p_progress_bar->Visible  && (p_percent_progress != IRS_NULL)) {
        p_progress_bar->Position = 0;
      }
    }
  } m_exec_progress;
  int m_index_pos_offset_eeprom;
  int m_max_size_correct;
  enum calibr_data_stat_t{
    calibr_data_stat_off,
    calibr_data_stat_write,
    calibr_data_stat_verify};
  calibr_data_stat_t m_calibr_data_stat;
  enum process_calibr_data_stat_t {
    pcds_off,
    pcds_next_sub_diapason,
    pcds_get_sub_diapason,
    pcds_write_sub_diapason,
    pcds_verify_sub_diapason,
    pcds_wait_process_write_passed,
    pcds_wait_process_verify_passed,
    pcds_reset};
  process_calibr_data_stat_t m_process_calibr_data_stat;
  int m_cur_sub_diapason;
  bool m_on_auto_verify;

public:// User declarations
  __fastcall TDataHandlingF(
    TComponent* Owner,
    // �������� ������������ ������ ��� ��������������� ������
    TForm* a_manager_channel = NULL,
    // �������� ������������ ������ ��� ��������������� ������
    const mode_program_t a_mode_program = mode_prog_single_channel,
    // �������� ������������ ������ ��� ��������������� ������
    const bool m_on_ref_channel = false,
    // ��� ������
    const irs::string_t a_name = irs::string_t(),
    // �������� ������������ ������ ��� ��������������� ������
    const irs::string_t a_opt_ini = irst("options.ini"),
    // �������� ������������ ������ ��� ��������������� ������
    const int a_num_mxifa_mxnetc = MXIFA_MXNETC);
  __fastcall ~TDataHandlingF();
  //����� ������������ ���������� �� �����
  void load_config_calibr_to_display();
  void select_config(const String& a_config_name);
  void select_config(int a_index);
  String get_selected_config();
  String get_selected_config_filename() const;
  //�������� ������������ ����������
  void load_config_calibr();
  void set_connect_if_enabled(bool a_forced_connect = false);
  void set_connect_calibr_device(bool a_forced_connect = false);
  bool set_connect_multimeter(const String& a_type_meas);
  String get_selected_multimeter();
  void reset_connect_calibr_device();
  void reset_connect_multimetr();
  // ������������� ��� ���������� ����� ��������� �� ��������� a_correct_stat
  inline void set_correct_mode(
    const bool a_correct_stat, const bool a_forcibly = 0);
  inline void set_mismatch_state(
    const bool a_mismatch_state, const bool a_forcibly = 0);

  void calculation_koef(irs::matrix_t<cell_t> a_matrix);
  void tick();
  void eeprom_tick();
  inline void set_successfully_mode_setting_stat();
  inline int read_memory_capacity();
  void add_graph_z_of_x();
  void add_graph_z_of_y();
  void add_all_graph_z_of_x();
  void add_all_graph_z_of_y();
  void update_all_graph();
  void clear_all_graph();
private:
  irs_uarc number_of_koef_per_point() const;
  inline void save_cur_config_device();
public:

  void load_multimeters_list();

  // �������� ������ ������ �������������� ������� �� ���������������
  inline void edit_mode_table_change_stat();
  // �������� ������ ������ ��������� �� ���������������
  inline void correct_mode_change_stat();
  // ������������� ����������/�������� ����� ���������
  inline void correct_mode_change_stat(const bool a_correct_mode);
  // �������� ������ ������ �������������� �� ���������������
  inline void mismatch_mode_change_stat();
  // ������������� ����������/�������� ����� ����������
  inline void mismatch_mode_change_stat(const bool a_mismatch_mode);

  void meas_execute();
  meas_status_t meas_status();

  //������ ����� �����
  void special_style_cells(TStringGrid* a_table,
    int a_col,
    int a_row,
    TRect &a_rect);
  //��������� ��������� ������ StringGrid
  void processing_select_cell(TStringGrid* a_table,
    int a_col, int a_row, bool &a_can_select);

  //��������� ������� ������� Enter � ��������� ������� ������� ����������
  //������ "Ctrl + Enter"
  void processing_key_return_and_ctrl_down(
    TStringGrid* const a_table,
    WORD& a_key,
    const TShiftState Shift);
  void on_select_cell(int a_col, int a_row, const TShiftState Shift);
  void update_buttons_config();
  void select_cur_meas_cell();

  void process_volt_meas();
  void update_point_measurement_progress();
  void update_measurement_progress();
  void set_progress_bar_mode_calibration();
  void set_progress_bar_mode_program();
  void set_progress_bar_mode_verification();
  void set_progress_bar_value(double a_percent);
  void config_button_start_avto_volt_meas();
  void config_button_stop_avto_volt_meas();
  void tick2();
  void set_setting_for_type_jump_next_cell(
    const String& a_str_type_jump_next_elem);
  // ������� ���������� ����������
  double calc_meas_value(
    const double a_value_meas,
    const double out_param_value,
    const param_cur_cell_t& a_param_cell);
  void update_result(bool a_last_call);
  cell_t process_measured_points(bool a_last_call);
  void reset_chart(const int a_col_displ, const int a_row_displ);
  void update_chart(const int a_col_displ, const int a_row_displ);
  // ������������� ��������� ���������
  double set_range(const param_cur_cell_t& a_param_cur_cell);
  // �������� �������� �������� ���������� ���������
  double get_anchor_in_param(const param_cur_cell_t& a_param_cur_cell);
  enum status_range_t {range_stat_success, range_stat_busy};
  // �������� ������� ������������ ���������
  status_range_t get_status_range();

  // ������� ������������ ������ ��� ��������������� ������
  // ������� ����� �������
  void set_ref_channel();
  // ������� ������������ ������ ��� ��������������� ������
  // ������� ����� ��������� �� �������� ������
  void unset_ref_channel();
  // ������� ������������ ������ ��� ��������������� ������
  // ��������, ���� �� ������� �������� �����
  bool get_on_close_form_stat();

  inline double get_out_param();
  inline void set_cell(
    const cell_t a_cell, const int a_col_displ, const int a_row_displ);
  inline cell_t get_cell_table(
    const int a_col_displ, const int a_row_displ) const;
  // ������� ������������ ������ ��� ��������������� ������
  // ������� �������� ������� ���������
  //inline void exec_trigger_meas();
  // ������� ������������ ������ ��� ��������������� ������
  inline status_process_meas_t get_status_process_meas();
  // ������� ������������ ������ ��� ��������������� ������
  // ��������� ������� ������ ������ �� ������ �������� ���������
  // ������� ����������� ������ � ������ �������� �������� �������
  // ���������������� ����� �������� ���������
  inline void exec_ext_trig_process_meas(
    const status_process_meas_t a_status_process_meas);
  inline int table_displ_col_count();
  inline int table_displ_row_count();
  inline coord_cell_t table_displ_cur_cell() const;
  inline irs::rect_t table_displ_selection() const;
  inline irs::rect_t cells_range() const;
  inline irs::mx_rect_t<double> headers_range() const;
  inline bool is_auto_meas_running() const;
  // ������ ��������� ������� ������ ���������
  inline coord_cell_t get_coord_cur_cell_meas();
  inline void cell_out_display_variable_precision(
    const int a_col_displ, const int a_row_displ);
  inline void set_col_displ(const int a_col);
  inline void set_row_displ(const int a_row);
  inline void set_phase_preset_bit();
  inline param_cur_cell_t get_param_cell(const int a_col, const int a_row) const;
  
  inline cell_config_calibr_t get_cell_config(const coord_cell_t& a_coord) const;
  inline cell_config_calibr_t get_cell_config(const int a_col, const int a_row) const;
  inline cell_config_calibr_t get_cell_config(const param_cur_cell_t& a_param_cur_cell) const;
  bool has_cells_out_param_ctrl_enabled() const;
  bool is_cells_range_valid(const TRect& a_rect) const;
  bool is_meas_cells_range_locked() const;
  bool try_to_lock_meas_cells_range();
  bool lock_meas_cells_range_if_need();
  void set_control_parameters(const cell_config_calibr_t& a_cell_cfg);
  // ��������� ��������� �������
  void out_param(const param_cur_cell_t& a_param_cur_cell);
  void out_default_param();
  // ����� ��������� � ��� � ������� ���������� ��������� ������
  void out_message_log_cur_param_cell(const param_cur_cell_t& a_param_cur_cell);
  // �������� �� ��������� � ������ ���������� �����
  // ���������� false, ���� ������������ ������� ��������
  //bool save_unsaved_changes_dialogsold();
  bool save_unsaved_changes_dialogs();
  //bool save_unsaved_data_changes_dialog(bool* ap_changes_were_forgotten);
  bool save_cells_config_dialog();
  bool save_cells_config_if_need();
  bool cells_config_is_changed() const;
  bool data_should_be_saved_dialog() const;
  // ��������� �� �����
  irs::matrix_t<cell_t> get_sub_diapason_table_data(const int a_sub_diapason);
  void tick_calibr_data();
  void modifi_table_data();
  // ���������� ������� �������� ���. ����������
  void set_value_working_extra_params(const coord_cell_t& a_coord);
  // ���������� �������� �� ��������� ���. ����������
  void set_value_default_extra_params();

  // ���������� ������� �������� ���. �����
  void set_value_working_extra_bits(const coord_cell_t& a_coord);
  // ���������� �������� �� ��������� ���. �����
  void set_value_default_extra_bits();
  void show_main_device_options();
  void show_ref_device_options();

  void load_devices();
  //! \brief ������������� �������� ����������
  void load_main_device();
  //! \brief ������������� �������� ����������
  void load_ref_device();

  //! \brief ��������� ��������� ���������� � ����������� �� �����. ���� ����
  //!   �����������
  void load_main_device(const String& a_config_name);
  //! \brief ��������� ��������� ���������� � ����������� �� �����. ���� ����
  //!   �����������
  void load_ref_device(const String& a_config_name);
  //void load_device(const String& a_device_file_name, device_t* ap_device);

  bool is_main_device_config_exists(const String& a_config_name) const;
  bool is_ref_device_config_exists(const String& a_config_name) const;
  void create_main_device_config_from_old(const String& a_config_name,
    const String& a_type,
    const config_calibr_t& a_config_calibr);
  void create_ref_device_config_from_old(const String& a_config_name,
    const String& a_type,
    const config_calibr_t& a_config_calibr);

  void change_main_device_type(const String& a_config_name,
    const String& a_type);
  void change_ref_device_type(const String& a_config_name,
    const String& a_type);
  void load_device_config_file(const String& a_config_name);
  void delete_device_config(const String& a_config_name);
  void reset_main_device(const string_type& a_device_file_name,
    const device_options_t& a_device);
  void reset_ref_device(const string_type& a_ref_device_file_name,
    const device_options_t& a_ref_device);
  void unset_ref_device();
  String get_device_name();
  String get_device_type() const;
  String get_ref_device_name();
  String get_ref_device_type() const;
  void reset_mxmultimeter_assembly();
  irs::handle_t<irs::mxmultimeter_assembly_t> make_mxmultimeter_assembly(
    const irs::string_t& a_device_name,
    const irs::string_t& a_device_type);
};

inline void TDataHandlingF::set_correct_mode(
  const bool a_correct_stat, const bool a_forcibly)
{
  if((a_correct_stat != m_correct_mode_previous_stat) || (a_forcibly == true)){
    m_correct_mode_previous_stat = a_correct_stat;
    if(a_correct_stat) {
      m_device.get_data()->correct_mode_bit = 0;
      if (m_config_calibr.reference_channel.enabled) {
        mp_data_map_ref_channel->correct_mode_bit = 0;
      }
    } else {
      m_device.get_data()->correct_mode_bit = 1;
      if (m_config_calibr.reference_channel.enabled) {
        mp_data_map_ref_channel->correct_mode_bit = 1;
      }
    }
  }
}

inline void TDataHandlingF::save_cur_config_device()
{
  int index_file = ConfigCB->ItemIndex;
  // ���� ������ ����
  if (index_file >= 0) {
    // ���� ���� ����������
    String filename_conf = mv_list_config_calibr[index_file];
    if(FileExists(filename_conf)){
      m_config_calibr.save(filename_conf.c_str());
    }
  }
}

inline void TDataHandlingF::set_mismatch_state(
  const bool a_mismatch_state, const bool a_forcibly)
{
  if(
    (a_mismatch_state != m_on_mismatch_state_previous) || (a_forcibly == true)){
    m_on_mismatch_state_previous = a_mismatch_state;
    if(a_mismatch_state) {
      m_device.get_data()->mismatch_state_bit = 1;
      DGI_MSG("mismatch_state_bit = 1");
      if (m_config_calibr.reference_channel.enabled) {
        mp_data_map_ref_channel->mismatch_state_bit = 1;
      }
    } else {
      m_device.get_data()->mismatch_state_bit = 0;
      DGI_MSG("mismatch_state_bit = 0");
      if (m_config_calibr.reference_channel.enabled) {
        mp_data_map_ref_channel->mismatch_state_bit = 0;
      }
    }
  }
}

inline void TDataHandlingF::set_successfully_mode_setting_stat()
  {m_successfully_mode_setting = true;}
inline int TDataHandlingF::read_memory_capacity()
  {return m_memory_capacity;}

inline void TDataHandlingF::reset_stat_stop_process_avto_volt_meas()
{
  m_on_stop_process_auto_volt_meas = false;
}

inline void TDataHandlingF::edit_mode_table_change_stat()
{
  bool edit_mode = !mp_active_table->get_edit_mode_table();
  if (edit_mode) {
    mp_active_table->set_edit_mode_table();
    mp_active_table->set_col_displ(0);
    mp_active_table->set_row_displ(0);
  } else {
    mp_active_table->reset_edit_mode_table();
    mp_active_table->set_col_displ(1);
    mp_active_table->set_row_displ(1);
  }
}

inline void TDataHandlingF::correct_mode_change_stat()
{
  m_on_correct = !m_on_correct;
  if(m_on_correct){
    CorrectModeAction->Checked = true;
  }else{
    CorrectModeAction->Checked = false;
  }
}

inline void TDataHandlingF::correct_mode_change_stat(const bool a_correct_mode)
{
  if(a_correct_mode){
    CorrectModeAction->Checked = true;
  }else{
    CorrectModeAction->Checked = false;
  }
}
inline void TDataHandlingF::mismatch_mode_change_stat()
{
  m_on_mismatch_state = !m_on_mismatch_state;
  if(m_on_mismatch_state){
    MismatchModeAction->Checked = true;
  }else{
    MismatchModeAction->Checked = false;
  }
}

inline void TDataHandlingF::mismatch_mode_change_stat(
  const bool a_mismatch_mode)
{
  if(a_mismatch_mode){
    MismatchModeAction->Checked = true;
  }else{
    MismatchModeAction->Checked = false;
  }
}

inline double TDataHandlingF::get_out_param()
{
  double out_param = m_device.get_data()->y_out;
  return out_param;
}

inline void TDataHandlingF::set_cell(
  const cell_t a_cell, const int a_col_displ, const int a_row_displ)
{
  mp_active_table->set_cell(a_cell, a_col_displ, a_row_displ);
}

inline cell_t TDataHandlingF::get_cell_table(
  const int a_col_displ, const int a_row_displ) const
{
  cell_t cell = mp_active_table->get_cell_table(a_col_displ, a_row_displ);
  return cell;
}

inline status_process_meas_t TDataHandlingF::get_status_process_meas()
{
  return m_status_process_meas;
}

inline void TDataHandlingF::exec_ext_trig_process_meas(
  const status_process_meas_t a_status_process_meas)
{
  if (m_status_process_meas == a_status_process_meas) {
    m_on_external = true;
  }
}
inline int TDataHandlingF::table_displ_col_count()
{
  return mp_active_table->get_col_count_displ();
}
inline int TDataHandlingF::table_displ_row_count()
{
  return mp_active_table->get_row_count_displ();
}
inline coord_cell_t TDataHandlingF::table_displ_cur_cell() const
{
  coord_cell_t coord;
  coord.col = mp_active_table->get_col_displ();
  coord.row = mp_active_table->get_row_displ();
  return coord;
}

irs::rect_t TDataHandlingF::table_displ_selection() const
{
  return mp_active_table->get_selection_displ();
}

inline irs::rect_t TDataHandlingF::cells_range() const
{
  //irs::rect_t selection = mp_active_table->get_selection_displ();
  irs::rect_t selection;
  selection = irs::rect_t( Max(m_cells_range.Left, 1), Max(m_cells_range.Top, 1),
    Max(m_cells_range.Right, 1), Max(m_cells_range.Bottom, 1) );
  return selection;
}

inline irs::mx_rect_t<double> TDataHandlingF::headers_range() const
{
  irs::rect_t selection = cells_range();

  param_cur_cell_t left_top = mp_active_table->get_param_cell(
    selection.left, selection.top);

  param_cur_cell_t right_bottom = mp_active_table->get_param_cell(
    selection.right, selection.bottom);

  irs::mx_rect_t<double> headers_range;
  headers_range.left = left_top.col_value.value;
  headers_range.top = left_top.row_value.value;
  headers_range.right = right_bottom.col_value.value;
  headers_range.bottom = right_bottom.row_value.value;

  return headers_range;
}

inline bool TDataHandlingF::is_auto_meas_running() const
{
  return m_auto_meas_is_running;
}
inline coord_cell_t TDataHandlingF::get_coord_cur_cell_meas()
{
  coord_cell_t coord_cell = m_manager_traffic_cell.get_coord_cell();
  return coord_cell;
}
inline void TDataHandlingF::cell_out_display_variable_precision(
  const int a_col_displ, const int a_row_displ)
{
  mp_active_table->cell_out_display_variable_precision(
    a_col_displ, a_row_displ);
}
inline void TDataHandlingF::set_col_displ(const int a_col)
{
  mp_active_table->set_col_displ(a_col);
}
inline void TDataHandlingF::set_row_displ(const int a_row)
{
  mp_active_table->set_row_displ(a_row);
}
inline void TDataHandlingF::set_phase_preset_bit()
{
  m_device.get_data()->phase_preset_bit = 1;
}
inline param_cur_cell_t TDataHandlingF::get_param_cell(
  const int a_col, const int a_row) const
{
  return mp_active_table->get_param_cell(a_col, a_row);
}

inline cell_config_calibr_t TDataHandlingF::get_cell_config(const coord_cell_t& a_coord) const
{
  return m_config_calibr.cells_config.read_cell(a_coord.col, a_coord.row);
}

inline cell_config_calibr_t TDataHandlingF::get_cell_config(
  const int a_col, const int a_row) const
{
  return m_config_calibr.cells_config.read_cell(a_col, a_row);
}

inline cell_config_calibr_t TDataHandlingF::get_cell_config(
  const param_cur_cell_t& a_param_cur_cell) const
{
  return get_cell_config(a_param_cur_cell.col, a_param_cur_cell.row);
}

//---------------------------------------------------------------------------
extern PACKAGE TDataHandlingF *DataHandlingF;
//---------------------------------------------------------------------------
#endif
