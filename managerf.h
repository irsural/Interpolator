//---------------------------------------------------------------------------

#ifndef managerfH
#define managerfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <irsdsp.h>
#include <timer.h>
#include <irsalg.h>
#include "datahandling.h"
//#include <irsstdg.h>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TManagerDGIF : public TForm
{
__published:	// IDE-managed Components
  TButton *OnVisibleChannel1B;
  TButton *OnVisibleChannel2B;
  TButton *OnVisibleChannel3B;
  TButton *OnVisibleChannel4B;
  TButton *OnVisibleChannel5B;
  TButton *OnVisibleChannel6B;
  TCheckBox *OnChannel1CB;
  TCheckBox *OnChannel2CB;
  TCheckBox *OnChannel3CB;
  TCheckBox *OnChannel4CB;
  TCheckBox *OnChannel5CB;
  TCheckBox *OnChannel6CB;
  TRadioButton *RefChannel1RB;
  TRadioButton *RefChannel2RB;
  TRadioButton *RefChannel3RB;
  TRadioButton *RefChannel4RB;
  TRadioButton *RefChannel5RB;
  TRadioButton *RefChannel6RB;
  TLabel *Label1;
  TMemo *LogMemo;
  TCheckBox *SingleModeProgramCB;
  TTimer *Timer1;
  TTimer *OnChangeVisibleFormTimer;
  TGroupBox *GroupBox1;
  TRadioButton *ModePhaseVoltageType1RB;
  TRadioButton *ModePhaseVoltageType2RB;
  TRadioButton *ModePhaseCurrentRB;
  TLabel *Label2;
  TLabel *Label3;
  TRadioButton *SubsidiaryChannel2RB;
  TRadioButton *SubsidiaryChannel3RB;
  TRadioButton *SubsidiaryChannel4RB;
  TRadioButton *SubsidiaryChannel5RB;
  TRadioButton *SubsidiaryChannel6RB;
  TRadioButton *CalibrChannel1RB;
  TRadioButton *CalibrChannel2RB;
  TRadioButton *CalibrChannel3RB;
  TRadioButton *CalibrChannel4RB;
  TRadioButton *CalibrChannel5RB;
  TRadioButton *CalibrChannel6RB;
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *Panel3;
  TRadioButton *SubsidiaryChannel1RB;
  TRadioButton *ModeCurrentRB;
  TLabeledEdit *ConstTimerFilterLE;
  TCheckBox *FilterOnCB;
  TEdit *ValueOutFilterEdit1;
  TEdit *ValueOutFilterEdit2;
  TEdit *ValueOutFilterEdit3;
  TEdit *ValueOutFilterEdit4;
  TEdit *ValueOutFilterEdit5;
  TEdit *ValueOutFilterEdit6;
  TLabel *Label4;
  TEdit *ValueOutEdit1;
  TEdit *ValueOutEdit2;
  TEdit *ValueOutEdit3;
  TEdit *ValueOutEdit4;
  TEdit *ValueOutEdit5;
  TEdit *ValueOutEdit6;
  TLabel *Label5;
  TCheckBox *CheckBoxPhasaNorm180;
  void __fastcall OnVisibleChannel1BClick(TObject *Sender);
  void __fastcall OnVisibleChannel2BClick(TObject *Sender);
  void __fastcall OnVisibleChannel3BClick(TObject *Sender);
  void __fastcall OnVisibleChannel4BClick(TObject *Sender);
  void __fastcall OnVisibleChannel5BClick(TObject *Sender);
  void __fastcall OnVisibleChannel6BClick(TObject *Sender);
  void __fastcall OnChannel1CBClick(TObject *Sender);
  void __fastcall OnChannel2CBClick(TObject *Sender);
  void __fastcall OnChannel3CBClick(TObject *Sender);
  void __fastcall OnChannel4CBClick(TObject *Sender);
  void __fastcall OnChannel5CBClick(TObject *Sender);
  void __fastcall OnChannel6CBClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall SingleModeProgramCBClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall RefChannel1RBClick(TObject *Sender);
  void __fastcall RefChannel2RBClick(TObject *Sender);
  void __fastcall RefChannel3RBClick(TObject *Sender);
  void __fastcall RefChannel4RBClick(TObject *Sender);
  void __fastcall RefChannel5RBClick(TObject *Sender);
  void __fastcall RefChannel6RBClick(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall OnChangeVisibleFormTimerTimer(TObject *Sender);
  void __fastcall ModePhaseVoltageType1RBClick(TObject *Sender);
  void __fastcall ModePhaseVoltageType2RBClick(TObject *Sender);
  void __fastcall ModePhaseCurrentRBClick(TObject *Sender);
  void __fastcall ModeCurrentRBClick(TObject *Sender);
  void __fastcall ConstTimerFilterLEExit(TObject *Sender);
  void __fastcall ConstTimerFilterLEKeyPress(TObject *Sender, char &Key);
  void __fastcall CheckBoxPhasaNorm180Click(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
  typedef irs::string_t string_type;
  bool m_start_prog;
  //класс работы с ini-файлом настроек программы
  irs::ini_file_t m_main_opt_ini_file;
  static const int m_channel_count = 6;
  std::vector<irs::fade_data_t> mv_fade_data;
  const double m_value_interval_read_out_param;
  double m_time_constant_filter;
  std::vector<double> mv_value_out_filter;

  bool m_on_control_wait_mode_setting;
  irs::loop_timer_t m_interval_read_out_param;
  counter_t m_between_reg_ready_and_filter_preset_sec;
  irs::timer_t m_timer_delay_filter_preset;
  const string_type m_filename_options_channel1;
  const string_type m_filename_options_channel2;
  const string_type m_filename_options_channel3;
  const string_type m_filename_options_channel4;
  const string_type m_filename_options_channel5;
  const string_type m_filename_options_channel6;

  irs::handle_t<TDataHandlingF> mp_channel_1;
  irs::handle_t<TDataHandlingF> mp_channel_2;
  irs::handle_t<TDataHandlingF> mp_channel_3;
  irs::handle_t<TDataHandlingF> mp_channel_4;
  irs::handle_t<TDataHandlingF> mp_channel_5;
  irs::handle_t<TDataHandlingF> mp_channel_6;
  std::vector<irs::handle_t<TDataHandlingF>* > mv_channels;
  static const bool m_block_message = 0;
  //log_t m_log;
  log_message_t m_log_message;

  enum { m_memobuf_size = 500 };
  irs::union_streambuf m_stream_buf;
  irs::handle_t <ofstream> mp_log_stream;
  irs::handle_t<irs::memobuf> mp_memo_buf;

  bool m_on_change_mode_prog;
  bool m_on_close_subordinate_form;
  int m_num_ref_channel;
  std::vector<double> mv_out_param_channels;
  std::vector<TEdit*> mv_value_out_edit;
  std::vector<TEdit*> mv_value_out_filter_edit;

  bool m_on_auto_meas_previous_value;

  double m_filter_phase_norm_begin;
  double m_filter_phase_norm_end;

public:		// User declarations
private:

  __fastcall TManagerDGIF(TComponent* Owner);
  __fastcall ~TManagerDGIF();
  void tick();
  void meas_tick();
  // Переустановить опорный канал
  void reset_ref_channel(const int a_num_ref_channel);
  // Возвращает указатель на опорный канал
  TDataHandlingF* get_ptr_ref_channel();
  void processing_data();
  void processing_data_current();
  void processing_data_phase_volt_type_1();
  void processing_data_phase_volt_type_2();
  void processing_data_phase_current();
  void processing_data_current_cur_channel(
    TDataHandlingF* a_channel,
    const coord_cell_t& a_coord_cur_cell,
    const double a_value_meas_ref_channel,
    const double a_value_out_param);
  void processing_data_phase_cur_channel(
    TDataHandlingF* a_channel, const coord_cell_t& a_coord_cur_cell);
  void set_param_channels(const param_cur_cell_t& a_param_cur_cell);
  void set_phase_preset_channels();
  double filter_phase_normalize(double a_value);
};
//---------------------------------------------------------------------------
extern PACKAGE TManagerDGIF *ManagerDGIF;
//---------------------------------------------------------------------------
#endif
