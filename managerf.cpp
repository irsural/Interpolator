//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "managerf.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TManagerDGIF *ManagerDGIF;
//---------------------------------------------------------------------------
__fastcall TManagerDGIF::TManagerDGIF(TComponent* Owner)
  : TForm(Owner),
  m_start_prog(true),
  mv_fade_data(),
  m_value_interval_read_out_param(0.2),
  m_time_constant_filter(20),
  mv_value_out_filter(m_channel_count),
  m_on_control_wait_mode_setting(false),
  m_interval_read_out_param(irs::make_cnt_s(m_value_interval_read_out_param)),
  m_between_reg_ready_and_filter_preset_sec(irs::make_cnt_s(5)),
  m_timer_delay_filter_preset(m_between_reg_ready_and_filter_preset_sec),
  m_filename_options_channel1(irst("options1.ini")),
  m_filename_options_channel2(irst("options2.ini")),
  m_filename_options_channel3(irst("options3.ini")),
  m_filename_options_channel4(irst("options4.ini")),
  m_filename_options_channel5(irst("options5.ini")),
  m_filename_options_channel6(irst("options6.ini")),
  mp_channel_1(NULL),
  mp_channel_2(NULL),
  mp_channel_3(NULL),
  mp_channel_4(NULL),
  mp_channel_5(NULL),
  mp_channel_6(NULL),
  m_log(LogMemo, irst("Log_manager.txt")),
  m_log_message(&m_log),
  m_on_change_mode_prog(false),
  m_on_close_subordinate_form(false),
  m_num_ref_channel(0),
  mv_out_param_channels(6,0),
  mv_value_out_edit(),
  mv_value_out_filter_edit(),
  m_on_auto_meas_previous_value(false),
  m_filter_phase_norm_begin(0),
  m_filter_phase_norm_end(+360)
{
  m_log << String(irst("Старт"));

  irs::fade_data_t fade_data;
  fade_data.x1 = 0;
  fade_data.y1 = 0;
  fade_data.t = 0;
  mv_fade_data.resize(m_channel_count, fade_data);
  m_interval_read_out_param.start();

  mv_channels.push_back(&mp_channel_1);
  mv_channels.push_back(&mp_channel_2);
  mv_channels.push_back(&mp_channel_3);
  mv_channels.push_back(&mp_channel_4);
  mv_channels.push_back(&mp_channel_5);
  mv_channels.push_back(&mp_channel_6);

  mv_value_out_edit.push_back(ValueOutEdit1);
  mv_value_out_edit.push_back(ValueOutEdit2);
  mv_value_out_edit.push_back(ValueOutEdit3);
  mv_value_out_edit.push_back(ValueOutEdit4);
  mv_value_out_edit.push_back(ValueOutEdit5);
  mv_value_out_edit.push_back(ValueOutEdit6);

  mv_value_out_filter_edit.push_back(ValueOutFilterEdit1);
  mv_value_out_filter_edit.push_back(ValueOutFilterEdit2);
  mv_value_out_filter_edit.push_back(ValueOutFilterEdit3);
  mv_value_out_filter_edit.push_back(ValueOutFilterEdit4);
  mv_value_out_filter_edit.push_back(ValueOutFilterEdit5);
  mv_value_out_filter_edit.push_back(ValueOutFilterEdit6);

  m_main_opt_ini_file.set_ini_name(irst("options_manager_channel.ini"));
  m_main_opt_ini_file.set_section(irst("options"));
  m_main_opt_ini_file.add(SingleModeProgramCB->Name, SingleModeProgramCB);
  m_main_opt_ini_file.add(OnChannel1CB->Name, OnChannel1CB);
  m_main_opt_ini_file.add(OnChannel2CB->Name, OnChannel2CB);
  m_main_opt_ini_file.add(OnChannel3CB->Name, OnChannel3CB);
  m_main_opt_ini_file.add(OnChannel4CB->Name, OnChannel4CB);
  m_main_opt_ini_file.add(OnChannel5CB->Name, OnChannel5CB);
  m_main_opt_ini_file.add(OnChannel6CB->Name, OnChannel6CB);
  m_main_opt_ini_file.add(RefChannel1RB->Name, RefChannel1RB);
  m_main_opt_ini_file.add(RefChannel2RB->Name, RefChannel2RB);
  m_main_opt_ini_file.add(RefChannel3RB->Name, RefChannel3RB);
  m_main_opt_ini_file.add(RefChannel4RB->Name, RefChannel4RB);
  m_main_opt_ini_file.add(RefChannel5RB->Name, RefChannel5RB);
  m_main_opt_ini_file.add(RefChannel6RB->Name, RefChannel6RB);
  m_main_opt_ini_file.add(SubsidiaryChannel1RB->Name, SubsidiaryChannel1RB);
  m_main_opt_ini_file.add(SubsidiaryChannel2RB->Name, SubsidiaryChannel2RB);
  m_main_opt_ini_file.add(SubsidiaryChannel3RB->Name, SubsidiaryChannel3RB);
  m_main_opt_ini_file.add(SubsidiaryChannel4RB->Name, SubsidiaryChannel4RB);
  m_main_opt_ini_file.add(SubsidiaryChannel5RB->Name, SubsidiaryChannel5RB);
  m_main_opt_ini_file.add(SubsidiaryChannel6RB->Name, SubsidiaryChannel6RB);
  m_main_opt_ini_file.add(CalibrChannel1RB->Name, CalibrChannel1RB);
  m_main_opt_ini_file.add(CalibrChannel2RB->Name, CalibrChannel2RB);
  m_main_opt_ini_file.add(CalibrChannel3RB->Name, CalibrChannel3RB);
  m_main_opt_ini_file.add(CalibrChannel4RB->Name, CalibrChannel4RB);
  m_main_opt_ini_file.add(CalibrChannel5RB->Name, CalibrChannel5RB);
  m_main_opt_ini_file.add(CalibrChannel6RB->Name, CalibrChannel6RB);
  m_main_opt_ini_file.add(RefChannel1RB->Name, RefChannel1RB);
  m_main_opt_ini_file.add(FilterOnCB->Name, FilterOnCB);
  m_main_opt_ini_file.add(CheckBoxPhasaNorm180->Name, CheckBoxPhasaNorm180);
  //m_main_opt_ini_file.add(ConstTimerFilterLE->Name, ConstTimerFilterLE);

  m_main_opt_ini_file.add(ModeCurrentRB->Name, ModeCurrentRB);
  m_main_opt_ini_file.add(
    ModePhaseVoltageType1RB->Name, ModePhaseVoltageType1RB);
  m_main_opt_ini_file.add(
    ModePhaseVoltageType2RB->Name, ModePhaseVoltageType2RB);
  m_main_opt_ini_file.add(ModePhaseCurrentRB->Name, ModePhaseCurrentRB);

  m_main_opt_ini_file.load();

  if (OnChannel1CB->Checked) {
    RefChannel1RB->Enabled = true;
  } else {
    RefChannel1RB->Enabled = false;
  }
  if (OnChannel2CB->Checked) {
    RefChannel2RB->Enabled = true;
  } else {
    RefChannel2RB->Enabled = false;
  }
  if (OnChannel3CB->Checked) {
    RefChannel3RB->Enabled = true;
  } else {
    RefChannel3RB->Enabled = false;
  }
  if (OnChannel4CB->Checked) {
    RefChannel4RB->Enabled = true;
  } else {
    RefChannel4RB->Enabled = false;
  }
  if (OnChannel5CB->Checked) {
    RefChannel5RB->Enabled = true;
  } else {
    RefChannel5RB->Enabled = false;
  }
  if (OnChannel6CB->Checked) {
    RefChannel6RB->Enabled = true;  
  } else {
    RefChannel6RB->Enabled = false;
  }
  if (CheckBoxPhasaNorm180->Checked) {
    m_filter_phase_norm_begin = -180;
    m_filter_phase_norm_end = +180;
  } else {
    m_filter_phase_norm_begin = 0;
    m_filter_phase_norm_end = +360;
  }

  irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, &m_log_message);

  // Настройка компонентов формы
  ConstTimerFilterLE->Text = irs::str_conv<String>(
    irs::num_to_str(m_time_constant_filter));
}
__fastcall TManagerDGIF::~TManagerDGIF()
{
  int a = 0;
}

//---------------------------------------------------------------------------
void __fastcall TManagerDGIF::OnVisibleChannel1BClick(TObject *Sender)
{
  if (mp_channel_1.get()) {
    mp_channel_1->Show();
  }
}
//---------------------------------------------------------------------------
void __fastcall TManagerDGIF::OnVisibleChannel2BClick(TObject *Sender)
{
  if (mp_channel_2.get()) {
    mp_channel_2->Show();
  }
}
//---------------------------------------------------------------------------
void __fastcall TManagerDGIF::OnVisibleChannel3BClick(TObject *Sender)
{
  if (mp_channel_3.get()) {
    mp_channel_3->Show();
  }
}
//---------------------------------------------------------------------------
void __fastcall TManagerDGIF::OnVisibleChannel4BClick(TObject *Sender)
{
  if (mp_channel_4.get()) {
    mp_channel_4->Show();
  }
}
//---------------------------------------------------------------------------
void __fastcall TManagerDGIF::OnVisibleChannel5BClick(TObject *Sender)
{
  if (mp_channel_5.get()) {
    mp_channel_5->Show();
  }
}
//---------------------------------------------------------------------------
void __fastcall TManagerDGIF::OnVisibleChannel6BClick(TObject *Sender)
{
  if (mp_channel_6.get()) {
    mp_channel_6->Show();
  }
}
//---------------------------------------------------------------------------
void __fastcall TManagerDGIF::OnChannel1CBClick(TObject *Sender)
{
  // если не включен одноканальный режим работы программы
  if (!SingleModeProgramCB->Checked) {
    if (OnChannel1CB->Checked == true) {
      if (mp_channel_1.get() == NULL) {
        bool ref_channel = (m_num_ref_channel == 1);
        mp_channel_1.reset(new TDataHandlingF(
          0,
          NULL,
          mode_prog_multi_channel,
          ref_channel,
          irst("Channel 1"),
          m_filename_options_channel1,
          MXIFA_MXNETC));
        RefChannel1RB->Enabled = true;
      }
    } else {
      mp_channel_1.reset(NULL);
      RefChannel1RB->Enabled = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::OnChannel2CBClick(TObject *Sender)
{
  if (!SingleModeProgramCB->Checked) {
    if (OnChannel2CB->Checked) {
      if (mp_channel_2.get() == NULL) {
        bool ref_channel = (m_num_ref_channel == 2);
        mp_channel_2.reset(new TDataHandlingF(
          0,
          NULL,
          mode_prog_multi_channel,
          ref_channel,
          irst("Channel 2"),
          m_filename_options_channel2,
          MXIFA_MXNETC_2));
        RefChannel2RB->Enabled = true;
      }
    } else {
      mp_channel_2.reset(NULL);
      RefChannel2RB->Enabled = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::OnChannel3CBClick(TObject *Sender)
{
  if (!SingleModeProgramCB->Checked) {
    if (OnChannel3CB->Checked == true) {
      if (mp_channel_3.get() == NULL) {
        bool ref_channel = (m_num_ref_channel == 3);
        mp_channel_3.reset(new TDataHandlingF(
          0,
          NULL,
          mode_prog_multi_channel,
          ref_channel,
          irst("Channel 3"),
          m_filename_options_channel3,
          MXIFA_MXNETC_3));
        RefChannel3RB->Enabled = true;
      }
    } else {
      mp_channel_3.reset(NULL);
      RefChannel3RB->Enabled = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::OnChannel4CBClick(TObject *Sender)
{
  if (!SingleModeProgramCB->Checked) {
    if (OnChannel4CB->Checked == true) {
      if (mp_channel_4.get() == NULL) {
        bool ref_channel = (m_num_ref_channel == 4);
        mp_channel_4.reset(new TDataHandlingF(
          0,
          NULL,
          mode_prog_multi_channel,
          ref_channel,
          irst("Channel 4"),
          m_filename_options_channel4,
          MXIFA_MXNETC_4));
        RefChannel4RB->Enabled = true;
      }
    } else {
      mp_channel_4.reset(NULL);
      RefChannel4RB->Enabled = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::OnChannel5CBClick(TObject *Sender)
{
  if (!SingleModeProgramCB->Checked) {
    if (OnChannel5CB->Checked == true) {
      if (mp_channel_5.get() == NULL) {
        bool ref_channel = (m_num_ref_channel == 5);
        mp_channel_5.reset(new TDataHandlingF(
          0,
          NULL,
          mode_prog_multi_channel,
          ref_channel,
          irst("Channel 5"),
          m_filename_options_channel5,
          MXIFA_MXNETC_5));
        RefChannel5RB->Enabled = true;
      }
    } else {
      mp_channel_5.reset(NULL);
      RefChannel5RB->Enabled = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::OnChannel6CBClick(TObject *Sender)
{
  if (!SingleModeProgramCB->Checked) {
    if (OnChannel6CB->Checked == true) {
      if (mp_channel_6.get() == NULL) {
        bool ref_channel = (m_num_ref_channel == 6);
        mp_channel_6.reset(new TDataHandlingF(
          0,
          NULL,
          mode_prog_multi_channel,
          ref_channel,
          irst("Channel 6"),
          m_filename_options_channel6,
          MXIFA_MXNETC_6));
        RefChannel6RB->Enabled = true;
      }
    } else {
      mp_channel_6.reset(NULL);
      RefChannel6RB->Enabled = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  m_main_opt_ini_file.save();
}
//---------------------------------------------------------------------------


void __fastcall TManagerDGIF::SingleModeProgramCBClick(TObject *Sender)
{
  if (SingleModeProgramCB->Checked) {
    // переход программы в одноканальный режим
    const int channel_count = mv_channels.size();
    for (int i = 0; i < channel_count; i++) {
      mv_channels[i]->reset(IRS_NULL);
    }
    irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, NULL);
    mp_channel_1.reset(new TDataHandlingF(0, ManagerDGIF));
    mp_channel_1->Visible = true;
    ManagerDGIF->Visible = false;
  }
}
//---------------------------------------------------------------------------



void __fastcall TManagerDGIF::FormShow(TObject *Sender)
{
  // если не старт программы
  if (!m_start_prog) {
    m_on_change_mode_prog = true;
  } else {
    m_start_prog = false;
  }
}
//---------------------------------------------------------------------------
void TManagerDGIF::tick()
{
  bool on_close_subordinate_form_1 = false;
  if (mp_channel_1.get()) {
    on_close_subordinate_form_1 = mp_channel_1->get_on_close_form_stat();
  }

  if ((m_on_change_mode_prog) && (SingleModeProgramCB->Checked)) {
    m_on_change_mode_prog = false;
    mp_channel_1.reset(IRS_NULL);
    irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, &m_log_message);
    SingleModeProgramCB->Checked = false;
    bool ref_channel = (m_num_ref_channel == 1);
    if (OnChannel1CB->Checked) {
      mp_channel_1.reset(new TDataHandlingF(
        0,
        NULL,
        mode_prog_multi_channel,
        ref_channel,
        irst("Channel 1"),
        m_filename_options_channel1,
        MXIFA_MXNETC));
    }
    if (OnChannel2CB->Checked) {
      bool ref_channel = (m_num_ref_channel == 2);
      mp_channel_2.reset(new TDataHandlingF(
        0,
        NULL,
        mode_prog_multi_channel,
        ref_channel,
        irst("Channel 2"),
        m_filename_options_channel2,
        MXIFA_MXNETC_2));
    }
    if (OnChannel3CB->Checked) {
      bool ref_channel = (m_num_ref_channel == 3);
      mp_channel_3.reset(new TDataHandlingF(
        0,
        NULL,
        mode_prog_multi_channel,
        ref_channel,
        irst("Channel 3"),
        m_filename_options_channel3,
        MXIFA_MXNETC_3));
    }
    if (OnChannel4CB->Checked) {
      bool ref_channel = (m_num_ref_channel == 4);
      mp_channel_4.reset(new TDataHandlingF(
        0,
        NULL,
        mode_prog_multi_channel,
        ref_channel,
        irst("Channel 4"),
        m_filename_options_channel4,
        MXIFA_MXNETC_4));
    }
    if (OnChannel5CB->Checked) {
      bool ref_channel = (m_num_ref_channel == 5);
      mp_channel_5.reset(new TDataHandlingF(
        0,
        NULL,
        mode_prog_multi_channel,
        ref_channel,
        irst("Channel 5"),
        m_filename_options_channel5,
        MXIFA_MXNETC_5));
    }
    if (OnChannel6CB->Checked) {
      bool ref_channel = (m_num_ref_channel == 6);
      mp_channel_6.reset(new TDataHandlingF(
        0,
        NULL,
        mode_prog_multi_channel,
        ref_channel,
        irst("Channel 6"),
        m_filename_options_channel6,
        MXIFA_MXNETC_6));
    }
  } else if ((on_close_subordinate_form_1) && (SingleModeProgramCB->Checked)) {
    Close();
  }
}
void TManagerDGIF::meas_tick()
{
  if (!SingleModeProgramCB->Checked) {
    TDataHandlingF* m_cur_ref_channel = get_ptr_ref_channel();
    if (m_cur_ref_channel != IRS_NULL) {
      bool on_auto_meas = m_cur_ref_channel->is_auto_meas_running();
      if (on_auto_meas != m_on_auto_meas_previous_value) {
        for (int channel = 0; channel < m_channel_count; channel++) {
          if ((*mv_channels[channel]).get() != IRS_NULL) {
            if (on_auto_meas) {
              m_on_control_wait_mode_setting = false;
              (*mv_channels[channel])->set_value_working_extra_params();
              (*mv_channels[channel])->set_value_working_extra_bits();
            } else {
              (*mv_channels[channel])->set_value_default_extra_params();
              (*mv_channels[channel])->set_value_default_extra_bits();
            }
          }
        }
      }
      m_on_auto_meas_previous_value = on_auto_meas;
      if (on_auto_meas) {
        status_process_meas_t status_process_meas =
          m_cur_ref_channel->get_status_process_meas();
        switch (status_process_meas) {
          case spm_wait_ext_trig_set_range: {
            coord_cell_t coord_cell =
              m_cur_ref_channel->get_coord_cur_cell_meas();
            param_cur_cell_t param_cur_cell =
              m_cur_ref_channel->get_param_cell(coord_cell.col, coord_cell.row);
            set_param_channels(param_cur_cell);
            m_cur_ref_channel->exec_ext_trig_process_meas(spm_set_range);
          } break;
          case spm_wait_ext_trig_control_wait_mode_setting: {
            set_phase_preset_channels();
            m_cur_ref_channel->exec_ext_trig_process_meas(
              spm_control_wait_mode_setting);
            m_timer_delay_filter_preset.start();
            m_on_control_wait_mode_setting = true;
          } break;
          case spm_wait_external_trig_meas: {
            m_on_control_wait_mode_setting = false;
            processing_data();
            m_cur_ref_channel->exec_ext_trig_process_meas(spm_execute_meas);
          } break;
          case spm_wait_external_trig_processing_data: {
            m_cur_ref_channel->exec_ext_trig_process_meas(spm_processing_data);
          } break;
          case spm_wait_ext_trig_process_data_to_next_elem: {
            processing_data();
            m_cur_ref_channel->exec_ext_trig_process_meas(spm_jump_next_elem);
          } break;
        }
        /*if (on_mode_wait_external_treg) {
           processing_data();
          m_cur_ref_channel->exec_trigger_meas();
        } */
        // Предустановка фазы
        if (m_timer_delay_filter_preset.check()) {
          m_log << "Предустановка фильтра";
          for (int channel = 0; channel < m_channel_count; channel++) {
            if ((*mv_channels[channel]).get() != IRS_NULL) {
              double in_x = (*mv_channels[channel])->get_out_param();
              double in_x_norm = filter_phase_normalize(in_x);
              /*const double a_phase_begin = -180;
              const double a_phase_end = +180;
              double in_x = (*mv_channels[channel])->get_out_param();
              double in_x_norm = irs::phase_normalize(
                in_x, a_phase_begin, a_phase_end);*/

              mv_fade_data[channel].x1 = in_x_norm;
              mv_fade_data[channel].y1 = in_x_norm;
              mv_fade_data[channel].t =
                m_time_constant_filter/m_value_interval_read_out_param;
            }
          }
        }
        if (m_on_control_wait_mode_setting) {
          if (m_interval_read_out_param.check())
          for (int channel = 0; channel < m_channel_count; channel++) {
            if ((*mv_channels[channel]).get() != IRS_NULL) {
              irs::fade_data_t fade_data = mv_fade_data[channel];
              double in_x = (*mv_channels[channel])->get_out_param();
              double in_x_norm = filter_phase_normalize(in_x);
              /*
              const double a_phase_begin = -180;
              const double a_phase_end = +180;
              double in_x_norm = irs::phase_normalize(
                in_x, a_phase_begin, a_phase_end);
              */
              mv_value_out_filter[channel] = fade(&fade_data, in_x_norm);
              mv_fade_data[channel] = fade_data;
              mv_value_out_edit[channel]->Text =
                num_to_cbstr(in_x_norm);
              mv_value_out_filter_edit[channel]->Text =
                num_to_cbstr(mv_value_out_filter[channel]);
            }
          }
        }
      }
    }
  }
}

void __fastcall TManagerDGIF::Timer1Timer(TObject *Sender)
{
  try {
    tick();
    meas_tick();
  } catch (Exception &exception) {
    Timer1->Enabled = false;
    Application->ShowException(&exception);
    exit(1);
  } catch (...) {
    Timer1->Enabled = false;
    try {
      throw Exception("");
    } catch (Exception &exception) {
      Application->ShowException(&exception);
    }
    exit(1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::RefChannel1RBClick(TObject *Sender)
{
  m_num_ref_channel = 1;
  if (!SingleModeProgramCB->Checked) reset_ref_channel(m_num_ref_channel);
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::RefChannel2RBClick(TObject *Sender)
{
  m_num_ref_channel = 2;
  if (!SingleModeProgramCB->Checked) reset_ref_channel(m_num_ref_channel);
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::RefChannel3RBClick(TObject *Sender)
{
  m_num_ref_channel = 3;
  if (!SingleModeProgramCB->Checked) reset_ref_channel(m_num_ref_channel);
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::RefChannel4RBClick(TObject *Sender)
{
  m_num_ref_channel = 4;
  if (!SingleModeProgramCB->Checked) reset_ref_channel(m_num_ref_channel);
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::RefChannel5RBClick(TObject *Sender)
{
  m_num_ref_channel = 5;
  if (!SingleModeProgramCB->Checked) reset_ref_channel(m_num_ref_channel);
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::RefChannel6RBClick(TObject *Sender)
{
  m_num_ref_channel = 6;
  if (!SingleModeProgramCB->Checked) reset_ref_channel(m_num_ref_channel);
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::Button2Click(TObject *Sender)
{
  OnChannel1CB->Checked = true;
}
//---------------------------------------------------------------------------
void TManagerDGIF::reset_ref_channel(const int a_num_ref_channel)
{
  if (mp_channel_1.get()) {
    if (a_num_ref_channel == 1) {
      mp_channel_1->set_ref_channel();
    } else {
      mp_channel_1->unset_ref_channel();
    }
  }
  if (mp_channel_2.get()) {
    if (a_num_ref_channel == 2) {
      mp_channel_2->set_ref_channel();
    } else {
      mp_channel_2->unset_ref_channel();
    }
  }
  if (mp_channel_3.get()) {
    if (a_num_ref_channel == 3) {
      mp_channel_3->set_ref_channel();
    } else {
      mp_channel_3->unset_ref_channel();
    }
  }
  if (mp_channel_4.get()) {
    if (a_num_ref_channel == 4) {
      mp_channel_4->set_ref_channel();
    } else {
      mp_channel_4->unset_ref_channel();
    }
  }
  if (mp_channel_5.get()) {
    if (a_num_ref_channel == 5) {
      mp_channel_5->set_ref_channel();
    } else {
      mp_channel_5->unset_ref_channel();
    }
  }
  if (mp_channel_6.get()) {
    if (a_num_ref_channel == 6) {
      mp_channel_6->set_ref_channel();
    } else {
      mp_channel_6->unset_ref_channel();
    }
  }
}

void __fastcall TManagerDGIF::OnChangeVisibleFormTimerTimer(TObject *Sender)
{
  try {
    if (ManagerDGIF->Visible) {
      if (SingleModeProgramCB->Checked) {
        ManagerDGIF->Visible = false;
      }
      OnChangeVisibleFormTimer->Enabled = false;
    }
  } catch (Exception &exception) {
    OnChangeVisibleFormTimer->Enabled = false;
    Application->ShowException(&exception);
    exit(1);
  } catch (...) {
    OnChangeVisibleFormTimer->Enabled = false;
    try {
      throw Exception("");
    } catch (Exception &exception) {
      Application->ShowException(&exception);
    }
    exit(1);
  }
}
TDataHandlingF* TManagerDGIF::get_ptr_ref_channel()
{
  TDataHandlingF* ref_channel_form = NULL;
  switch (m_num_ref_channel) {
    case 1: { ref_channel_form = mp_channel_1.get();
    } break;
    case 2: { ref_channel_form = mp_channel_2.get();
    } break;
    case 3: { ref_channel_form = mp_channel_3.get();
    } break;
    case 4: { ref_channel_form = mp_channel_4.get();
    } break;
    case 5: { ref_channel_form = mp_channel_5.get();
    } break;
    case 6: { ref_channel_form = mp_channel_6.get();
    } break;
  }
  return ref_channel_form;
}
void TManagerDGIF::processing_data()
{
  if (ModeCurrentRB->Checked) {
    processing_data_current();
  } else if (ModePhaseVoltageType1RB->Checked) {
    processing_data_phase_volt_type_1();
  } else if (ModePhaseVoltageType2RB->Checked) {
    processing_data_phase_volt_type_2();
  } else {
    processing_data_phase_current();
  }
}
void TManagerDGIF::processing_data_current()
{
  TDataHandlingF* m_cur_ref_channel = get_ptr_ref_channel();
  coord_cell_t coord_cell = m_cur_ref_channel->get_coord_cur_cell_meas();
  //double value_meas = m_cur_ref_channel->get_value_meas();

  status_process_meas_t status_process_meas =
    m_cur_ref_channel->get_status_process_meas();
  if (status_process_meas == spm_wait_external_trig_meas) {
    if ((mp_channel_1.get()) && (mp_channel_1.get() != m_cur_ref_channel)) {
      mv_out_param_channels[0] = mp_channel_1->get_out_param();
    }
    if ((mp_channel_2.get()) && (mp_channel_2.get() != m_cur_ref_channel)) {
      mv_out_param_channels[1] = mp_channel_2->get_out_param();
    }
    if ((mp_channel_3.get()) && (mp_channel_3.get() != m_cur_ref_channel)) {
      mv_out_param_channels[2] = mp_channel_3->get_out_param();
    }
    if ((mp_channel_4.get()) && (mp_channel_4.get() != m_cur_ref_channel)) {
      mv_out_param_channels[3] = mp_channel_4->get_out_param();
    }
    if ((mp_channel_5.get()) && (mp_channel_5.get() != m_cur_ref_channel)) {
      mv_out_param_channels[4] = mp_channel_5->get_out_param();
    }
    if ((mp_channel_6.get()) && (mp_channel_6.get() != m_cur_ref_channel)) {
      mv_out_param_channels[5] = mp_channel_6->get_out_param();
    }
  } else if (
    status_process_meas == spm_wait_ext_trig_process_data_to_next_elem) {
    cell_t cell =
      m_cur_ref_channel->get_cell_table(coord_cell.col, coord_cell.row);
    double value_meas = 0;
    if (cell.init) {
      value_meas = cell.value;
    }
    if ((mp_channel_1.get()) && (mp_channel_1.get() != m_cur_ref_channel)) {
        processing_data_current_cur_channel(
          mp_channel_1.get(), coord_cell, value_meas, mv_out_param_channels[0]);
    }
    if ((mp_channel_2.get()) && (mp_channel_2.get() != m_cur_ref_channel)) {
      processing_data_current_cur_channel(
        mp_channel_2.get(), coord_cell, value_meas, mv_out_param_channels[1]);
    }
    if ((mp_channel_3.get()) && (mp_channel_3.get() != m_cur_ref_channel)) {
      processing_data_current_cur_channel(
        mp_channel_3.get(), coord_cell, value_meas, mv_out_param_channels[2]);
    }
    if ((mp_channel_4.get()) && (mp_channel_4.get() != m_cur_ref_channel)) {
      processing_data_current_cur_channel(
        mp_channel_4.get(), coord_cell, value_meas, mv_out_param_channels[3]);
    }
    if ((mp_channel_5.get()) && (mp_channel_5.get() != m_cur_ref_channel)) {
      processing_data_current_cur_channel(
        mp_channel_5.get(), coord_cell, value_meas, mv_out_param_channels[4]);
    }
    if ((mp_channel_6.get()) && (mp_channel_6.get() != m_cur_ref_channel)) {
      processing_data_current_cur_channel(
        mp_channel_6.get(), coord_cell, value_meas, mv_out_param_channels[5]);
    }
  }
}
void TManagerDGIF::processing_data_phase_volt_type_1()
{
  TDataHandlingF* m_cur_ref_channel = get_ptr_ref_channel();
  coord_cell_t coord_cell = m_cur_ref_channel->get_coord_cur_cell_meas();
  for (int index_chnl = 0; index_chnl < m_channel_count; index_chnl++) {
    if (((*mv_channels[index_chnl]).get() != NULL) &&
      ((*mv_channels[index_chnl]).get() != m_cur_ref_channel)) {
      processing_data_phase_cur_channel(mv_channels[index_chnl]->get(), coord_cell);
    }
  }
}
void TManagerDGIF::processing_data_phase_volt_type_2()
{
  TDataHandlingF* subsidiary_channel = IRS_NULL;
  TDataHandlingF* calibr_channel = IRS_NULL;
  if (SubsidiaryChannel1RB->Checked) {
    subsidiary_channel = mp_channel_1.get();
  } else if (SubsidiaryChannel2RB->Checked) {
    subsidiary_channel = mp_channel_2.get();
  } else if (SubsidiaryChannel3RB->Checked) {
    subsidiary_channel = mp_channel_3.get();
  } else if (SubsidiaryChannel4RB->Checked) {
    subsidiary_channel = mp_channel_4.get();
  } else if (SubsidiaryChannel5RB->Checked) {
    subsidiary_channel = mp_channel_5.get();
  } else if (SubsidiaryChannel6RB->Checked) {
    subsidiary_channel = mp_channel_6.get();
  }

  if (CalibrChannel1RB->Checked) {
    calibr_channel = mp_channel_1.get();
  } else if (CalibrChannel2RB->Checked) {
    calibr_channel = mp_channel_2.get();
  } else if (CalibrChannel3RB->Checked) {
    calibr_channel = mp_channel_3.get();
  } else if (CalibrChannel4RB->Checked) {
    calibr_channel = mp_channel_4.get();
  } else if (CalibrChannel5RB->Checked) {
    calibr_channel = mp_channel_5.get();
  } else if (CalibrChannel6RB->Checked) {
    calibr_channel = mp_channel_6.get();
  }

  TDataHandlingF* m_cur_ref_channel = get_ptr_ref_channel();
  coord_cell_t coord_cell = m_cur_ref_channel->get_coord_cur_cell_meas();
  cell_t cell_cur =  subsidiary_channel->get_cell_table(
    coord_cell.col, coord_cell.row);
  double cur_value_cell = 0;
  if (cell_cur.init) cur_value_cell = cell_cur.value;
  double new_value_out_param_subs_channel = subsidiary_channel->get_out_param();
  double out_param_calibr_channel = calibr_channel->get_out_param();
  /*double new_val_out_param_subs_channel_norm =
    phase_normalize(new_value_out_param_subs_channel);
  double out_param_calibr_channel_norm =
    phase_normalize(out_param_calibr_channel);
  */
  const double a_phase_begin = -180;
  const double a_phase_end = +180;

  double new_val_out_param_subs_channel_norm = irs::phase_normalize(
    new_value_out_param_subs_channel, a_phase_begin , a_phase_end);
  double out_param_calibr_channel_norm = irs::phase_normalize(
    out_param_calibr_channel, a_phase_begin , a_phase_end);

  cell_t cell;
  cell.init = true;
  cell.value = cur_value_cell-new_val_out_param_subs_channel_norm+
    out_param_calibr_channel_norm;
  calibr_channel->set_col_displ(coord_cell.col);
  calibr_channel->set_row_displ(coord_cell.row);
  calibr_channel->set_cell(cell, coord_cell.col, coord_cell.row);
  calibr_channel->cell_out_display_variable_precision(
    coord_cell.col, coord_cell.row);

}
void TManagerDGIF::processing_data_phase_current()
{
  TDataHandlingF* m_cur_ref_channel = get_ptr_ref_channel();
  coord_cell_t coord_cell = m_cur_ref_channel->get_coord_cur_cell_meas();
  for (int index_chnl = 0; index_chnl < m_channel_count; index_chnl++) {
    if ((*mv_channels[index_chnl]).get() != NULL) {
      processing_data_phase_cur_channel(mv_channels[index_chnl]->get(), coord_cell);
    }
  }
}
void TManagerDGIF::processing_data_current_cur_channel(
  TDataHandlingF* a_channel,
  const coord_cell_t& a_coord_cur_cell,
  const double a_value_meas_ref_channel,
  const double a_value_out_param)
{
  int col_count = a_channel->table_displ_col_count();
  int row_count = a_channel->table_displ_row_count();
  if (
    (a_coord_cur_cell.col < col_count) && (a_coord_cur_cell.row < row_count)) {
    param_cur_cell_t param_cur_cell = a_channel->get_param_cell(
      a_coord_cur_cell.col,a_coord_cur_cell.row);
    //double out_value = a_channel->get_out_param();
    cell_t cell;
    cell.init = true;
    cell.value = a_channel->calc_meas_value(
      a_value_meas_ref_channel, a_value_out_param, param_cur_cell);
    a_channel->set_col_displ(a_coord_cur_cell.col);
    a_channel->set_row_displ(a_coord_cur_cell.row);
    a_channel->set_cell(cell, a_coord_cur_cell.col, a_coord_cur_cell.row);
    a_channel->cell_out_display_variable_precision(
      a_coord_cur_cell.col, a_coord_cur_cell.row);
  }
}
void TManagerDGIF::processing_data_phase_cur_channel(
    TDataHandlingF* a_channel, const coord_cell_t& a_coord_cur_cell)
{
  int col_count = a_channel->table_displ_col_count();
  int row_count = a_channel->table_displ_row_count();
  if (
    (a_coord_cur_cell.col < col_count) && (a_coord_cur_cell.row < row_count)) {
    double out_param = 0.;
    if (FilterOnCB->Checked) {
      for (int channel_ind = 0; channel_ind < m_channel_count; channel_ind++) {
        if (a_channel == mv_channels[channel_ind]->get()) {
          out_param = mv_value_out_filter[channel_ind];
          break;
        }
      }
    } else {
      out_param = a_channel->get_out_param();
    }
    //double phase_normal = phase_normalize(out_param);
    const double a_phase_begin = -180;
    const double a_phase_end = +180;
    double phase_normal = irs::phase_normalize(
      out_param, a_phase_begin , a_phase_end);
    //phase_normal = -phase_normal;
    cell_t cell;
    cell.init = true;
    cell.value = phase_normal;
    a_channel->set_col_displ(a_coord_cur_cell.col);
    a_channel->set_row_displ(a_coord_cur_cell.row);
    a_channel->set_cell(cell, a_coord_cur_cell.col, a_coord_cur_cell.row);
    a_channel->cell_out_display_variable_precision(
      a_coord_cur_cell.col, a_coord_cur_cell.row);
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::ModePhaseVoltageType1RBClick(TObject *Sender)
{
  if (ModePhaseVoltageType1RB->Checked) {
    SubsidiaryChannel1RB->Enabled = false;
    SubsidiaryChannel2RB->Enabled = false;
    SubsidiaryChannel3RB->Enabled = false;
    SubsidiaryChannel4RB->Enabled = false;
    SubsidiaryChannel5RB->Enabled = false;
    SubsidiaryChannel6RB->Enabled = false;
    CalibrChannel1RB->Enabled = false;
    CalibrChannel2RB->Enabled = false;
    CalibrChannel3RB->Enabled = false;
    CalibrChannel4RB->Enabled = false;
    CalibrChannel5RB->Enabled = false;
    CalibrChannel6RB->Enabled = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::ModePhaseVoltageType2RBClick(TObject *Sender)
{
  if (ModePhaseVoltageType2RB->Checked) {
    SubsidiaryChannel1RB->Enabled = true;
    SubsidiaryChannel2RB->Enabled = true;
    SubsidiaryChannel3RB->Enabled = true;
    SubsidiaryChannel4RB->Enabled = true;
    SubsidiaryChannel5RB->Enabled = true;
    SubsidiaryChannel6RB->Enabled = true;
    CalibrChannel1RB->Enabled = true;
    CalibrChannel2RB->Enabled = true;
    CalibrChannel3RB->Enabled = true;
    CalibrChannel4RB->Enabled = true;
    CalibrChannel5RB->Enabled = true;
    CalibrChannel6RB->Enabled = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::ModePhaseCurrentRBClick(TObject *Sender)
{
  if (ModePhaseCurrentRB->Checked) {
    SubsidiaryChannel1RB->Enabled = false;
    SubsidiaryChannel2RB->Enabled = false;
    SubsidiaryChannel3RB->Enabled = false;
    SubsidiaryChannel4RB->Enabled = false;
    SubsidiaryChannel5RB->Enabled = false;
    SubsidiaryChannel6RB->Enabled = false;
    CalibrChannel1RB->Enabled = false;
    CalibrChannel2RB->Enabled = false;
    CalibrChannel3RB->Enabled = false;
    CalibrChannel4RB->Enabled = false;
    CalibrChannel5RB->Enabled = false;
    CalibrChannel6RB->Enabled = false;
  }
}

void TManagerDGIF::set_param_channels(const param_cur_cell_t& a_param_cur_cell)
{
  const TDataHandlingF* const m_cur_ref_channel = get_ptr_ref_channel();

  if ((mp_channel_1.get() != IRS_NULL) &&
    (mp_channel_1.get() != m_cur_ref_channel)) {
    mp_channel_1->out_param(a_param_cur_cell);
  }
  if ((mp_channel_2.get() != IRS_NULL) &&
    (mp_channel_2.get() != m_cur_ref_channel)) {
    mp_channel_2->out_param(a_param_cur_cell);
  }
  if ((mp_channel_3.get() != IRS_NULL) &&
    (mp_channel_3.get() != m_cur_ref_channel)) {
    mp_channel_3->out_param(a_param_cur_cell);
  }
  if ((mp_channel_4.get() != IRS_NULL) &&
    (mp_channel_4.get() != m_cur_ref_channel)) {
    mp_channel_4->out_param(a_param_cur_cell);
  }
  if ((mp_channel_5.get() != IRS_NULL) &&
    (mp_channel_5.get() != m_cur_ref_channel)) {
    mp_channel_5->out_param(a_param_cur_cell);
  }
  if ((mp_channel_6.get() != IRS_NULL) &&
    (mp_channel_6.get() != m_cur_ref_channel)) {
    mp_channel_6->out_param(a_param_cur_cell);
  }
}
void TManagerDGIF::set_phase_preset_channels()
{
  const TDataHandlingF* const m_cur_ref_channel = get_ptr_ref_channel();
  if ((mp_channel_1.get() != IRS_NULL) &&
    (mp_channel_1.get() != m_cur_ref_channel)) {
    mp_channel_1->set_phase_preset_bit();
  }
  if ((mp_channel_2.get() != IRS_NULL) &&
    (mp_channel_2.get() != m_cur_ref_channel)) {
    mp_channel_2->set_phase_preset_bit();
  }
  if ((mp_channel_3.get() != IRS_NULL) &&
    (mp_channel_3.get() != m_cur_ref_channel)) {
    mp_channel_3->set_phase_preset_bit();
  }
  if ((mp_channel_4.get() != IRS_NULL) &&
    (mp_channel_4.get() != m_cur_ref_channel)) {
    mp_channel_4->set_phase_preset_bit();
  }
  if ((mp_channel_5.get() != IRS_NULL) &&
    (mp_channel_5.get() != m_cur_ref_channel)) {
    mp_channel_5->set_phase_preset_bit();
  }
  if ((mp_channel_6.get() != IRS_NULL) &&
    (mp_channel_6.get() != m_cur_ref_channel)) {
    mp_channel_6->set_phase_preset_bit();
  }
}

double TManagerDGIF::filter_phase_normalize(double a_value)
{
  double m_filter_phase_norm_begin = 0;
  double m_filter_phase_norm_end = +360;
  double phase_normal = irs::phase_normalize(
    a_value, m_filter_phase_norm_begin , m_filter_phase_norm_end);
  return phase_normal;
}

//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::ModeCurrentRBClick(TObject *Sender)
{
  if (ModeCurrentRB->Checked) {
    SubsidiaryChannel1RB->Enabled = false;
    SubsidiaryChannel2RB->Enabled = false;
    SubsidiaryChannel3RB->Enabled = false;
    SubsidiaryChannel4RB->Enabled = false;
    SubsidiaryChannel5RB->Enabled = false;
    SubsidiaryChannel6RB->Enabled = false;
    CalibrChannel1RB->Enabled = false;
    CalibrChannel2RB->Enabled = false;
    CalibrChannel3RB->Enabled = false;
    CalibrChannel4RB->Enabled = false;
    CalibrChannel5RB->Enabled = false;
    CalibrChannel6RB->Enabled = false;
  }
}
//---------------------------------------------------------------------------



void __fastcall TManagerDGIF::ConstTimerFilterLEExit(TObject *Sender)
{
  double buf_time_constant_filter = m_time_constant_filter;
  if (irs::cbuilder::str_to_number(
    ConstTimerFilterLE->Text, m_time_constant_filter))
  {
    ConstTimerFilterLE->Text =
      num_to_cbstr(m_time_constant_filter);
  } else {
    m_time_constant_filter = buf_time_constant_filter;
    ShowMessage("Неверно указано значение постоянной времени.");
    ConstTimerFilterLE->Text =
      num_to_cbstr(m_time_constant_filter);
  }
}
//---------------------------------------------------------------------------

void __fastcall TManagerDGIF::ConstTimerFilterLEKeyPress(TObject *Sender,
      char &Key)
{
  // Если нажата клавиша Enter
  if (Key == VK_RETURN) {
    double buf_time_constant_filter = m_time_constant_filter;
    if (irs::cbuilder::str_to_number(
      ConstTimerFilterLE->Text, m_time_constant_filter))
    {
      ConstTimerFilterLE->Text =
        num_to_cbstr(m_time_constant_filter);
    } else {
      ShowMessage("Неверно указано значение постоянной времени.");
      m_time_constant_filter = buf_time_constant_filter;
      ConstTimerFilterLE->Text =
        num_to_cbstr(m_time_constant_filter);
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TManagerDGIF::CheckBoxPhasaNorm180Click(TObject *Sender)
{
  if (CheckBoxPhasaNorm180->Checked) {
    m_filter_phase_norm_begin = -180;
    m_filter_phase_norm_end = +180;
  } else {
    m_filter_phase_norm_begin = 0;
    m_filter_phase_norm_end = +360;
  }  
}
//---------------------------------------------------------------------------


void __fastcall TManagerDGIF::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  if (!SingleModeProgramCB->Checked) {
    for (size_t i = 0; i < mv_channels.size(); i++) {
      if (!mv_channels[i]->is_empty()) {
        TDataHandlingF* data_handing = mv_channels[i]->get();
        if (!data_handing->save_unsaved_changes_dialog()) {
          CanClose = false;
          break;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

