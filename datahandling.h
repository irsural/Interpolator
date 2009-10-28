//---------------------------------------------------------------------------

#ifndef datahandlingH
#define datahandlingH
//---------------------------------------------------------------------------

#include <irsdefs.h>
#include <irsstd.h>
#include <irscpp.h>
#include <irsstd.h>
#include <irsfunnel.h>
#include <mxnetc.h>
#include <inifiles.hpp>
#include <timer.h>
#include <irscberror.h>
#include <irstime.h>
#include <cbcomp.h>
#include <irsalg.h>
#include <irstable.h>

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
#include "newconfig.h"
//#include "configdevice.h"
#include "modifidatatable.h"
#include "About.h"

enum mode_program_t {
  mode_prog_multi_channel,
  mode_prog_single_channel};
enum status_process_meas_t{
  spm_off_process,
  spm_jump_next_elem,
  spm_wait_ext_trig_set_range,
  spm_set_range,
  spm_wait_set_range,
  spm_mode_setting,
  spm_wait_mode_setting,
  spm_wait_ext_trig_control_wait_mode_setting,
  spm_control_wait_mode_setting,
  spm_wait_external_trig_meas,
  spm_execute_meas,
  spm_wait_execute_meas,
  spm_wait_external_trig_processing_data,
  spm_processing_data,
  spm_wait_ext_trig_process_data_to_next_elem,
  spm_reset};
//---------------------------------------------------------------------------
class TDataHandlingF : public TForm
{
__published:	// IDE-managed Components
  TPanel *TableValuePanel;
  TStringGrid *RawDataStringGrid;
  TGroupBox *OptionsGroupBox;
  TPanel *ButtomPanel;
  TTimer *FormDataHandingTimer1;
  TButton *OptionsOptimizeButton;
  TMemo *LogMemo;
  TActionManager *ActionManager1;
  TImageList *ImageList2;
  TActionToolBar *ActionToolBar1;
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
  TActionToolBar *ActionToolBar2;
  TCoolBar *CoolBar1;
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
  TActionToolBar *ActionToolBar3;
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
  TAction *EditModeAction;
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
  TImageList *ImageList1;
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
  TActionToolBar *ActionToolBar4;
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
  TButton *Button1;
  TAction *ModifiTableDataAction;
  TMenuItem *ModifiTableDataM;
  TAction *AboutAction;
  TMenuItem *N17;
  TMenuItem *AboutM;
  void __fastcall RawDataStringGridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall RawDataStringGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDataHandingTimer1Timer(TObject *Sender);
  void __fastcall ClearTableButtonClick(TObject *Sender);
  void __fastcall OptionsOptimizeButtonClick(TObject *Sender);
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
  void __fastcall EditModeActionExecute(TObject *Sender);
  void __fastcall RawDataStringGridGetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
  void __fastcall CreateConfigButtonClick(TObject *Sender);
  void __fastcall EditConfigButtonClick(TObject *Sender);
  void __fastcall CorrectModeActionExecute(TObject *Sender);
  void __fastcall MismatchModeActionExecute(TObject *Sender);
  void __fastcall CloseFormButtonClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall WriteDataActionExecute(TObject *Sender);
  void __fastcall Panel1Resize(TObject *Sender);
  void __fastcall ConfigCBChange(TObject *Sender);
  void __fastcall PatternOfMeasuringInstrumentCBChange(TObject *Sender);
  void __fastcall SetPhaseMeasActionExecute(TObject *Sender);
  void __fastcall SetPhaseAverageMeasActionExecute(TObject *Sender);
  void __fastcall SetTimeIntervalMeasActionExecute(TObject *Sender);
  void __fastcall SetTimeIntervalAverageMeasActionExecute(TObject *Sender);
  void __fastcall AddTableActionExecute(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
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

private:	// User declarations
  //��� ���������
  AnsiString m_prog_name;
  mode_program_t m_mode_program;
  //����������, ��� ��������� ���������
  AnsiString m_path_prog;
  //��� ����� �������� ���������
  AnsiString m_name_main_opt_ini_file;
  //����� ������ � ini-������ �������� ���������
  irs::ini_file_t m_main_opt_ini_file;
  //����� ������ � ini-������ ������������ ����������
  //  irs::ini_file_t m_conf_device_ini_file;
  //����� �����
  log_t m_log;
  log_message_t m_log_message;
  TForm* mp_manager_channel;
  //��� �������� ��������� ��� �������� �����������
  const AnsiString m_foldername_conf;
  //���������� ����� ������������ �������� ����������
  const AnsiString m_default_ext;
  //������������� ����� ������������ �������� ����������
  const AnsiString m_fileid_conf;
  config_calibr_t m_config_calibr, m_conf_calibr_buf,
    m_config_calibr_ref_channel;

  inf_in_param_t m_inf_in_param;
  struct data_map_t
  {
    dynamic_conn_data_t x_in;
    dynamic_conn_data_t y_in;
    dynamic_conn_data_t q_in;
    dynamic_conn_data_t y_out;
    irs::conn_data_t<irs_u32> work_time;
    irs::conn_data_t<irs_u32> status;
    irs::bit_data_t mismatch_state_bit;
    irs::bit_data_t correct_mode_bit;
    irs::bit_data_t operating_duty_bit;
    irs::bit_data_t error_bit;
    irs::bit_data_t reset_over_bit;
    irs::bit_data_t phase_preset_bit;
    vector<dynamic_conn_data_t> v_extra_param;
    vector<irs::bit_data_t> v_extra_bit;
    void connect(irs::mxdata_t *ap_data,
      config_calibr_t& a_config_calibr)
    {
      x_in.connect(
        a_config_calibr.in_parametr1.unit,
        ap_data,
        a_config_calibr.in_parametr1.index);

      y_in.connect(
        a_config_calibr.in_parametr2.unit,
        ap_data,
        a_config_calibr.in_parametr2.index);

      if(a_config_calibr.in_parametr1.anchor == false
        && a_config_calibr.in_parametr2.anchor == false){
        q_in.connect(
          a_config_calibr.in_parametr3.unit,
          ap_data,
          a_config_calibr.in_parametr3.index);
      }
      y_out.connect(
        a_config_calibr.out_parametr.unit,
        ap_data,
        a_config_calibr.out_parametr.index);

      int extra_param_count = a_config_calibr.v_parametr_ex.size();
      v_extra_param.resize(extra_param_count);
      for (int i = 0; i < extra_param_count; i++) {
        v_extra_param[i].connect(
          a_config_calibr.v_parametr_ex[i].unit,
          ap_data,
          a_config_calibr.v_parametr_ex[i].index);
      }

      work_time.connect(ap_data,
        a_config_calibr.index_work_time);
      mismatch_state_bit.connect(
        ap_data,
        a_config_calibr.bit_pos_mismatch_state.index_byte,
        a_config_calibr.bit_pos_mismatch_state.index_bit);
      correct_mode_bit.connect(
        ap_data,
        a_config_calibr.bit_pos_correct_mode.index_byte,
        a_config_calibr.bit_pos_correct_mode.index_bit);
      operating_duty_bit.connect(
        ap_data,
        a_config_calibr.bit_pos_operating_duty.index_byte,
        a_config_calibr.bit_pos_operating_duty.index_bit);
      error_bit.connect(
        ap_data,
        a_config_calibr.bit_pos_error_bit.index_byte,
        a_config_calibr.bit_pos_error_bit.index_bit);
      reset_over_bit.connect(
        ap_data,
        a_config_calibr.bit_pos_reset_over_bit.index_byte,
        a_config_calibr.bit_pos_reset_over_bit.index_bit);
      phase_preset_bit.connect(
        ap_data,
        a_config_calibr.bit_pos_phase_preset_bit.index_byte,
        a_config_calibr.bit_pos_phase_preset_bit.index_bit);

      int extra_bit_count = a_config_calibr.bit_type2_array.size();
      v_extra_bit.resize(extra_bit_count);
      for (int i = 0; i < extra_bit_count; i++) {
        v_extra_bit[i].connect(
          ap_data,
          a_config_calibr.bit_type2_array[i].index_byte,
          a_config_calibr.bit_type2_array[i].index_bit);
      }
    }
  };


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

  const AnsiString m_name_file_options_ini;// = "options.ini";
  static const m_index_funnel = 40;
  correct_map_t correct_map, m_correct_map_local;
  //vector<correct_map_t> mv_correct_map, mv_correct_map_local;
  data_map_t m_data_map;
  auto_ptr<data_map_t> mp_data_map_ref_channel;
  mxnetc m_mxnet;
  auto_ptr<mxnetc> mp_mxnet_ref_channel;
  irs::mxdata_to_mxnet_t m_mxnet_data;
  auto_ptr<irs::mxdata_to_mxnet_t> mp_mxnet_data_ref_channel;
  auto_ptr<irs::funnel_client_t> mp_eeprom;
  auto_ptr<irs::local_data_t> mp_local_data;
  irs::conn_data_t<irs_u32> work_time;

  table_data_t* mp_active_table;
  status_connect_t status_connect;
  status_connect_eeprom_t status_connect_eeprom;
  AnsiString m_cur_config_device, m_cur_config_multimetr;
  // ������������ ���������� ������� ���������
  bool m_load_conf_calibr_device_success;
  // ����, ���� ��� ������� ������������� ���������� ������
  // � ������������� ����������
  bool m_bad_cells;
  //���������� ������������ ������������
  bool m_on_block_reconfiguration;
  // ��� �������� ����� ������������
  AnsiString m_cur_filename_conf_calibr_device;

  bool m_on_write_data_eeprom;
  bool m_on_verification_data_eeprom;
  bool m_on_out_data;
  bool m_on_correct;
  bool m_correct_mode_previous_stat;

  status_options_t m_status_options;

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

  vector<AnsiString> mv_list_config_calibr;

  //��������� ��������
  struct chart_t
  {
  private:
    irs::chart::builder_chart_window_t builder_chart_window_z_of_x;
    irs::chart::builder_chart_window_t builder_chart_window_z_of_y;
    //��������� ������ ��������
    irs::chart_window_t* p_chart_window_z_of_x;
    irs::chart_window_t* p_chart_window_z_of_y;
    vector<irs::string> z_of_x_charts;
    vector<irs::string> z_of_y_charts;
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
      const irs::string& a_name_graph,
      const std::vector<cell_t>& a_p_points,
      const std::vector<cell_t>& a_x_points,
      const inf_in_param_t& a_inf_in_param,
      const double a_norm_koef);
    void add_chart_z_of_y(
      const irs::string& a_name_graph,
      const std::vector<cell_t>& a_p_points,
      const std::vector<cell_t>& a_y_points,
      const inf_in_param_t& a_inf_in_param,
      const double a_norm_koef);

    void save_name_chart_z_of_x(const irs::string& a_name_chart);
    void save_name_chart_z_of_y(const irs::string& a_name_chart);
  } m_chart;
  irs::loop_timer_t m_timer_chart_auto_update;

  bool m_successfully_mode_setting;

  //����������, ������������ ������� ��������� ����������
  bool m_on_connect_mxnet_data;
  bool m_on_connect_eeprom;

  //������ ����� ������� ��������������� ��������� ����������
  bool m_on_start_new_auto_meas;
  //������� �������
  bool m_on_auto_meas;
  //���������� �������
  bool m_on_stop_process_avto_volt_meas;
  //������� ��������������� ��������� � �������� ������
  bool m_on_process_auto_meas_active_cell;

  //��� ������������� ��������������� ������
  bool on_reg_ready_back_cycle;

  enum device_mode_status_t{DM_SUCCESS, DM_BUSY};

  bool m_on_jump_smooth;

  type_jump_next_elem_t m_type_jump_next_elem;
  AnsiString m_str_type_jump_next_elem;
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
  const cur_elem_t m_start_elem;
  cur_elem_t m_start_inverse_elem;
  cur_elem_t m_cur_elem;
  cur_elem_t m_max_cur_elem;
  cur_elem_t m_min_cur_elem;

  //��������� ������
  bool m_on_reg_ready;

  counter_t m_delay_start_control_reg;
  counter_t m_delay_operating_duty;
  counter_t m_delay_control_error_bit;
  counter_t m_delay_next_cell;

  irs::timer_t m_timer_delay_control, m_timer_delay_operating_duty;
  irs::timer_t m_timer_delay_control_error_bit;
  irs::timer_t m_timer_delay_next_cell;
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
  inline void reset_start_new_avto_volt_meas_stat();
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
    irs::string value_str;
    bool init;
    cur_cell_t():col(0), row(0),value_str(""),init(false)
    {}
    cur_cell_t(
      const int a_col,
      const int a_row,
      const irs::string a_value_str,
      const bool a_init):
      col(a_col), row(a_row),value_str(a_value_str), init(a_init)
    {}
  } m_cur_cell_table1;
  bool m_on_get_edit_text_event_sg;
  bool m_on_key_char_down;
  param_cur_cell_t m_default_param_cur_cell;
  irs_u32 m_cur_count_reset_over_bit;
  double y_out;
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
      //#ifdef NOP
      if ((!p_comment->Visible) && (p_comment != IRS_NULL)) {
        p_comment->Visible = true;
      }
      if ((!p_percent_progress->Visible)  && (p_percent_progress != IRS_NULL)) {
        p_percent_progress->Visible = true;
      }
      if ((!p_progress_bar->Visible)  && (p_percent_progress != IRS_NULL)) {
        p_progress_bar->Visible = true;
      }
      //#endif // NOP
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
public:		// User declarations
  __fastcall TDataHandlingF(
    TComponent* Owner,
    // �������� ������������ ������ ��� ��������������� ������
    TForm* a_manager_channel = NULL,
    // �������� ������������ ������ ��� ��������������� ������
    const mode_program_t a_mode_program = mode_prog_single_channel,
    // �������� ������������ ������ ��� ��������������� ������
    const bool m_on_ref_channel = false,
    // ��� ������
    const irs::string a_name = "",
    // �������� ������������ ������ ��� ��������������� ������
    const irs::string a_opt_ini = "options.ini",
    // �������� ������������ ������ ��� ��������������� ������
    const int a_num_mxifa_mxnetc = MXIFA_MXNETC);
  __fastcall ~TDataHandlingF();
  //����� ������������ ���������� �� �����
  void load_config_calibr_to_display(const AnsiString a_dir);
  //�������� ������������ ����������
  void load_config_calibr();
  inline void set_connect_calibr_device(bool a_forced_connect = false);
  inline void set_connect_multimetr();
  inline void reset_connect_multimetr();
  // ������������� ��� ���������� ����� ��������� �� ��������� a_correct_stat
  inline void set_correct_mode(
    const bool a_correct_stat, const bool a_forcibly = 0);
  inline void set_mismatch_state(
    const bool a_mismatch_state, const bool a_forcibly = 0);

  void calculation_koef(irs::matrix_t<cell_t> a_matrix);
  void tick();
  inline void set_successfully_mode_setting_stat();
  inline int read_memory_capacity();
  void add_graph_z_of_x();
  void add_graph_z_of_y();
  void add_all_graph_z_of_x();
  void add_all_graph_z_of_y();
  void update_all_graph();
  void clear_all_graph();
private:
  inline void save_cur_config_device();
public:
  inline void set_inf_in_param(const inf_in_param_t a_inf_in_param);

  inline void set_deley_volt_meas(const unsigned int a_delay);
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

  //void set_device_mode(const param_cur_cell_t& a_param_cur_cell);
  device_mode_status_t status_device_mode();

  void meas_execute();
  meas_status_t meas_status();

  void set_type_meas(type_meas_t a_type_meas);
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
    const WORD a_key,
    const TShiftState Shift);

  void process_volt_meas();
  void config_button_start_avto_volt_meas();
  void config_button_stop_avto_volt_meas();
  void tick2();
  void set_setting_for_type_jump_next_cell(
    const AnsiString& a_str_type_jump_next_elem);
  // ������� ���������� ����������
  double calc_meas_value(
    const double a_value_meas,
    const double out_param_value,
    const param_cur_cell_t& a_param_cell);
  // ������������� ��������� ���������
  void set_range(const param_cur_cell_t& a_param_cur_cell);
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

  inline bool get_stat_on_auto_meas();
  // ������ ��������� ������� ������ ���������
  inline coord_cell_t get_coord_cur_cell_meas();
  inline void cell_out_display_variable_precision(
    const int a_col_displ, const int a_row_displ);
  inline void set_col_displ(const int a_col);
  inline void set_row_displ(const int a_row);
  inline void set_phase_preset_bit();
  inline param_cur_cell_t get_param_cell(const int a_col, const int a_row);
  // ��������� ��������� �������
  void out_param(const param_cur_cell_t& a_param_cur_cell);
  // ����� ��������� � ��� � ������� ���������� ��������� ������
  void out_message_log_cur_param_cell(const param_cur_cell_t& a_param_cur_cell);
  // �������� �� ��������� � ������ ���������� �����
  bool save_dirty_data();
  // ��������� �� �����
  irs::matrix_t<cell_t> get_sub_diapason_table_data(const int a_sub_diapason);
  void tick_calibr_data();
  void modifi_table_data();
  // ���������� ������� �������� ���. ����������
  void set_value_working_extra_params();
  // ���������� �������� �� ��������� ���. ����������
  void set_value_default_extra_params();

  // ���������� ������� �������� ���. �����
  void set_value_working_extra_bits();
  // ���������� �������� �� ��������� ���. �����
  void set_value_default_extra_bits();

};
inline void TDataHandlingF::set_connect_calibr_device(
  bool a_forced_connect)
{
  if((!m_on_block_reconfiguration) || (a_forced_connect == true)){
    int index_file = ConfigCB->ItemIndex;
    if (index_file >= 0) {
      AnsiString select_config_device = extract_short_filename(
        ExtractFileName(mv_list_config_calibr[index_file]));
      if((m_cur_config_device != select_config_device) || (a_forced_connect)){
        m_log << "��������� ���������� � �����������";
        m_cur_config_device = select_config_device;
        load_config_calibr();
        m_data_map.connect(&m_mxnet_data, m_config_calibr);

        if (m_config_calibr.reference_channel.enabled) {
          mp_data_map_ref_channel->connect(
            mp_mxnet_data_ref_channel.get(), m_config_calibr_ref_channel);
        }
      }
    }  
  }
}
inline void TDataHandlingF::set_connect_multimetr()
{
  int index_multimetr = PatternOfMeasuringInstrumentCB->ItemIndex;
  AnsiString cur_multimetr =
    PatternOfMeasuringInstrumentCB->Items->Strings[index_multimetr];
  m_value_meas.set_connect_multimetr(
    str_to_type_multimeter(cur_multimetr.c_str()));

  /*
  if(!m_on_block_reconfiguration){


    m_cur_config_multimetr = index_multimetr;
    AnsiString select_multimetr = "";
    switch(index_multimetr){
      case 0:{
        select_multimetr =
          PatternOfMeasuringInstrumentCB->Items->Strings[index_multimetr];
        if(m_cur_config_multimetr != select_multimetr){
          m_value_meas.set_connect_multimetr(tmul_agilent_3458a);
          m_cur_config_multimetr = select_multimetr;
        }
      } break;
      case 1:{
        select_multimetr =
          PatternOfMeasuringInstrumentCB->Items->Strings[index_multimetr];
        if(m_cur_config_multimetr != select_multimetr){
          m_value_meas.set_connect_multimetr(tmul_v7_78_1);
          m_cur_config_multimetr = select_multimetr;
        }
      } break;
      case 2:{
        select_multimetr =
          PatternOfMeasuringInstrumentCB->Items->Strings[index_multimetr];
        if(m_cur_config_multimetr != select_multimetr){
          m_value_meas.set_connect_multimetr(tmul_ch3_85_3r);
          m_cur_config_multimetr = select_multimetr;
        }
      } break;
    }
  }*/
}
inline void TDataHandlingF::reset_connect_multimetr()
{
  m_cur_config_multimetr = "";
  m_value_meas.disconnect_multimetr();
  PatternOfMeasuringInstrumentCB->Enabled = true;
}
inline void TDataHandlingF::set_correct_mode(
  const bool a_correct_stat, const bool a_forcibly)
{
  if((a_correct_stat != m_correct_mode_previous_stat) || (a_forcibly == true)){
    m_correct_mode_previous_stat = a_correct_stat;
    if(a_correct_stat) {
      m_data_map.correct_mode_bit = 0;
      if (m_config_calibr.reference_channel.enabled) {
        mp_data_map_ref_channel->correct_mode_bit = 0;
      }
    } else {
      m_data_map.correct_mode_bit = 1;
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
    AnsiString filename_conf = mv_list_config_calibr[index_file];
    if(FileExists(filename_conf)){
      m_config_calibr.save(filename_conf.c_str());
      //m_conf_calibr_buf = m_config_calibr;
      //m_conf_calibr_buf.save(filename_conf.c_str());
    }
  }
  //m_conf_calibr_buf = m_config_calibr;
  //m_conf_device_ini_file.save();
}

inline void TDataHandlingF::set_mismatch_state(
  const bool a_mismatch_state, const bool a_forcibly)
{
  if(
    (a_mismatch_state != m_on_mismatch_state_previous) || (a_forcibly == true)){
    m_on_mismatch_state_previous = a_mismatch_state;
    if(a_mismatch_state) {
      m_data_map.mismatch_state_bit = 1;
      if (m_config_calibr.reference_channel.enabled) {
        mp_data_map_ref_channel->mismatch_state_bit = 1;
      }
    } else {
      m_data_map.mismatch_state_bit = 0;
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

inline void TDataHandlingF::reset_start_new_avto_volt_meas_stat()
{
  m_on_start_new_auto_meas = false;
}

inline void TDataHandlingF::reset_stat_stop_process_avto_volt_meas()
{
  m_on_stop_process_avto_volt_meas = false;
}

inline void TDataHandlingF::set_deley_volt_meas(const unsigned int a_delay)
{
  m_delay_operating_duty = irs::make_cnt_s((int)a_delay);
}
inline void TDataHandlingF::edit_mode_table_change_stat()
{
  bool edit_mode = !mp_active_table->get_edit_mode_table();
  if(edit_mode){
    EditModeAction->Checked = true;
    mp_active_table->set_edit_mode_table();
    mp_active_table->set_col_displ(0);
    mp_active_table->set_row_displ(0);
  }else{
    EditModeAction->Checked = false;
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
  double out_param = m_data_map.y_out;
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
/*inline void TDataHandlingF::exec_trigger_meas()
{
  m_on_external_trig_meas = true;
} */
inline status_process_meas_t TDataHandlingF::get_status_process_meas()
{
  return m_status_process_meas;
}
inline void TDataHandlingF::exec_ext_trig_process_meas(
  const status_process_meas_t a_status_process_meas)
{
  switch (a_status_process_meas) {
    case spm_set_range: {
      if (m_status_process_meas == spm_wait_ext_trig_set_range) {
        m_on_external = true;
      }
    } break;
    case spm_control_wait_mode_setting: {
      if (m_status_process_meas ==
        spm_wait_ext_trig_control_wait_mode_setting) {
        m_on_external = true;
      }
    } break;
    case spm_execute_meas: {
      if (m_status_process_meas == spm_wait_external_trig_meas) {
        m_on_external = true;
      }
    } break;
    case spm_processing_data: {
      if (m_status_process_meas == spm_wait_external_trig_processing_data) {
        m_on_external = true;
      }
    } break;
    case spm_jump_next_elem: {
      if (
      m_status_process_meas == spm_wait_ext_trig_process_data_to_next_elem) {
        m_on_external = true;
      }
    } break;
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
inline bool TDataHandlingF::get_stat_on_auto_meas()
{
  return m_on_auto_meas;
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
  m_data_map.phase_preset_bit = 1;
}
inline param_cur_cell_t TDataHandlingF::get_param_cell(
  const int a_col, const int a_row)
{
  return mp_active_table->get_param_cell(a_col, a_row);
}

//---------------------------------------------------------------------------
extern PACKAGE TDataHandlingF *DataHandlingF;
//---------------------------------------------------------------------------
#endif
