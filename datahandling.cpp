//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "datahandling.h"
#include <irscpp.h>
#include <tstlan5lib.h>
#include <irsalg.h>
#include "newconfig.h"
#include "configtableconflict.h"


#include <irsfinal.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDataHandlingF *DataHandlingF;
//---------------------------------------------------------------------------
__fastcall TDataHandlingF::TDataHandlingF(
  TComponent* Owner,
  TForm* ap_manager_channel,
  const mode_program_t a_mode_program,
  const bool m_on_ref_channel,
  const irs::string_t a_name,
  const irs::string_t a_opt_ini,
  const int a_num_mxifa_mxnetc)
  : TForm(Owner),

  m_prog_name(irst("Digital interpolator")),
  m_mode_program(a_mode_program),
  m_file_name_service(),
  m_name_main_opt_ini_file(a_opt_ini.c_str()),
  m_main_opt_ini_file(),
  m_log_message(/*&m_log*/),

  m_stream_buf(100),
  mp_log_stream(new ofstream("Log.txt", ios::out | ios::app)),
  mp_memo_buf(new irs::memobuf(LogMemo, m_memobuf_size)),

  mp_manager_channel(ap_manager_channel),
  m_value_meas(),
  m_fileid_conf(irst("Конфигурация настроек калибровки.")),
  m_config_calibr(),
  m_conf_calibr_buf(),
  m_config_calibr_ref_channel(),
  m_test1(),
  m_inf_in_param(),
  mp_options_prog_ini_file(0),
  status_connect(WAIT_CONNECT),
  status_connect_eeprom(sce_off),

  m_name_file_options_ini(irst("interpoptions.ini")),
  m_correct_map(),
  m_correct_map_local(),
  mp_data_map_ref_channel(NULL),
  m_device_chart(10000, 1000,
    irs::chart::builder_chart_window_t::stay_on_top_off),
  m_device(&m_device_chart, &m_file_name_service),

  m_ref_device(&m_device_chart, &m_file_name_service),

  mp_mxnet_ref_channel(NULL),
  mp_mxnet_data_ref_channel(NULL),

  //обращение к массиву в памяти контроллера
  mp_eeprom(IRS_NULL),
  mp_local_data(IRS_NULL),
  mp_mxmultimeter_assembly(),
  m_cur_config_device(),
  m_cur_config_multimetr(),
  m_load_conf_calibr_device_success(false),
  m_bad_cells(false),
  m_on_block_reconfiguration(false),
  m_cur_index_conf_calibr(0),
  m_cur_filename_conf_calibr_device(String()),

  m_on_write_data_eeprom(false),
  m_on_verification_data_eeprom(false),
  m_on_out_data(false),

  m_on_correct(false),
  m_correct_mode_previous_stat(false),

  m_is_autosave_meas_enabled(false),
  m_measure_method(mm_impulse_filter),
  m_need_size_memory(0),
  m_on_mismatch_state(false),
  m_on_mismatch_state_previous(false),
  m_non_first_connect_mxnet_data(false),
  m_on_reset_functional_bits(false),

  mv_col_user_data(0),
  mv_row_user_data(0),
  mv_top_user_data(0),
  mv_col_optimal_data(0),
  mv_row_optimal_data(0),
  mv_top_optimal_data(0),
  mv_coef_data(),

  mv_list_config_calibr(0),

  m_chart(),
  mp_meas_point_chart(NULL),
  m_timer_chart_auto_update(irs::make_cnt_ms(1000)),
  m_successfully_mode_setting(false),

  m_on_connect_mxnet_data(false),
  m_on_connect_eeprom(false),

  m_on_start_new_auto_meas(false),
  m_auto_meas_is_running(false),
  m_on_stop_process_auto_volt_meas(false),
  m_on_process_auto_meas_active_cell(false),
  on_reg_ready_back_cycle(false),

  m_status_process_meas(spm_off_process),
  m_on_jump_smooth(true),
  m_type_jump_next_elem(VERTICAL_FORWARD_SMOOTH),
  m_str_type_jump_next_elem(
    type_jump_next_elem_to_str(m_type_jump_next_elem).c_str()),

  m_type_meas(tm_volt_dc),

  m_out_param_stability_control(0, 0, 0),
  m_out_param_stable_min_time(),
  m_temperature_stability_control(0, 0, temperature_stability_min_time),
  m_temperature_stable_min_time(),
  m_on_reg_ready(false),

  m_delay_start_control_reg(irs::make_cnt_ms(5000)),
  m_delay_operating_duty(irs::make_cnt_ms(2000)),
  m_delay_control_error_bit(irs::make_cnt_ms(5000)),
  m_delay_next_cell(irs::make_cnt_ms(5000)),
  m_restart_timer(irs::make_cnt_s(60)),
  m_need_restart(false),
  m_timer_delay_control(m_delay_start_control_reg),
  m_timer_delay_operating_duty(m_delay_operating_duty),
  m_timer_delay_control_error_bit(m_delay_control_error_bit),
  m_timer_delay_next_cell(m_delay_next_cell),
  m_timer_waiting_set_extra_vars(irs::make_cnt_s(3)),
  m_reset_time_meas(false),
  m_time_meas(),
  m_count_point_meas(0),
  m_previous_count_point_meas(0),
  m_cell_per_sec(0.0),
  m_cell_count_end(0),
  m_previous_time_meas_sec(0.0),
  m_status_copy_table(OFF_COPY),
  table_string_grid1(RawDataStringGrid),
  m_table_raw_data(&table_string_grid1, irst("Таблица исходных значений")),
  m_table_data_size(&m_table_raw_data),
  m_manager_traffic_cell(&m_table_data_size),
  mp_active_table(&m_table_raw_data),
  m_start_col(1),
  m_start_row(1),
  m_cells_range(1, 1, 1, 1),
  m_copied_cell_config(),
  m_meas_cells_range(1, 1, 1, 1),
  m_start_cell(),
  mv_config_table_copy(0),
  m_memory_capacity(128),      // max 4080
  m_param_cur_cell(),
  m_cur_cell_cfg(),
  m_prev_cell_cfg(),
  m_select_col(0),
  m_select_row(0),
  m_start_num_col(0),
  m_end_num_col(0),
  m_step_num_col(0),
  m_type_step_col(INCREMENT_STEP),
  m_start_num_row(0),
  m_end_num_row(0),
  m_step_num_row(0),
  m_type_step_row(INCREMENT_STEP),
  m_successfully_add_col(false),
  m_successfully_add_row(false),

  m_add_col_or_row_successfuly(false),
  m_enabled_fixes_cells(true),
  m_value_meas_multimetr(0.),
  m_cur_cell_table1(1, 1, irst(""), false),
  m_default_param_cur_cell(),
  m_cur_count_reset_over_bit(0),
  m_y_out(0.),
  m_y_out_filter(),
  m_impulse_filter(),
  m_meas_value_filter(1000000),
  m_meas_value_filter_timer(irs::make_cnt_s(0)),
  m_meas_value_filter_elapsed_time(),
  m_on_close_form_stat(false),
  m_on_external(false),
  m_exec_progress(CommentProgressL, PercentProgressL, ProgressBar1),
  m_index_pos_offset_eeprom(0),
  m_max_size_correct(0),
  m_calibr_data_stat(calibr_data_stat_off),
  m_process_calibr_data_stat(pcds_off),
  m_cur_sub_diapason(0),
  m_on_auto_verify(true)
{
  m_stream_buf.insert(mp_log_stream->rdbuf());
  m_stream_buf.insert(mp_memo_buf.get());

  irs::mlog().rdbuf(&m_stream_buf);
  irs::mlog() << boolalpha;

  DGI_MSG("Старт");

  if (m_mode_program == mode_prog_single_channel) {
    // обработчик ошибок
    //irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, &m_log_message);
  } else {
    m_prog_name = a_name.c_str();
    ModeProgramCB->Enabled = false;
    if (m_on_ref_channel == false) {
      unset_ref_channel();
    }
  }

  // Если папка существует, то определяет, существует ли каталог
  load_config_calibr_to_display();

  load_multimeters_list();

  //устанавливаем имя файла настроек программы
  m_main_opt_ini_file.set_ini_name(m_name_main_opt_ini_file);
  m_main_opt_ini_file.set_section("Опции");

  m_main_opt_ini_file.add(String(irst("Текущая конфигурация")), ConfigCB);
  m_main_opt_ini_file.add(
    String(irst("Текущий мультиметр")),
    PatternOfMeasuringInstrumentCB);
  m_main_opt_ini_file.add(
    String(irst("Режим коррекции")), &m_on_correct);
  m_main_opt_ini_file.add(
    String(irst("Режим расстройки")), &m_on_mismatch_state);
  m_main_opt_ini_file.add(
    String(irst("Стиль движения")), &m_str_type_jump_next_elem);
  m_main_opt_ini_file.add(
    String(irst("Автообновление графиков")), &m_chart.on_auto_update);
  m_main_opt_ini_file.add(
    String(irst("Автоматическое сохранение измерений")), &m_is_autosave_meas_enabled);
  m_main_opt_ini_file.add(
    String(irst("Метод усреднения")), &m_measure_method);

  m_main_opt_ini_file.load();
  reset_mxmultimeter_assembly();
  correct_mode_change_stat(m_on_correct);
  mismatch_mode_change_stat(m_on_mismatch_state);
  set_setting_for_type_jump_next_cell(m_str_type_jump_next_elem);
  if (m_measure_method == mm_impulse_filter) {
    measureMethodImpulseFilterCheckbox->Checked = true;
  } else {
    measureMethodAverageCheckbox->Checked = true;
  }
  AutoUpdateChartAction->Checked = m_chart.on_auto_update;
  AutoSaveMeasAction->Checked = m_is_autosave_meas_enabled;
  load_config_calibr();
  set_connect_if_enabled();

  init_to_cnt();
  m_timer_chart_auto_update.start();
  m_exec_progress.hide();
  m_exec_progress.clear();

  config_calibr_t::save_load_test();
}



void TDataHandlingF::load_multimeters_list()
{
  PatternOfMeasuringInstrumentCB->Clear();
  TSearchRec sr;
  String dir = m_file_name_service.get_multimeter_config_dir();
  String config_ext = m_file_name_service.get_multimeter_config_ext();
  String filter = dir + String(irst("\\*")) + irst(".") + config_ext;

  if (FindFirst(filter, faAnyFile, sr) == 0) {
    String multimeter_name = extract_short_filename(sr.Name);
    PatternOfMeasuringInstrumentCB->Items->Add(multimeter_name);
    while (FindNext(sr) == 0) {
      String multimeter_name = extract_short_filename(sr.Name);
      PatternOfMeasuringInstrumentCB->Items->Add(multimeter_name);
    }
  }

  FindClose(sr);
}

__fastcall TDataHandlingF::~TDataHandlingF()
{
  void* p = RawDataStringGrid;

  reset_connect_multimetr();
  deinit_to_cnt();
  m_main_opt_ini_file.save();
  m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str());

  if (m_mode_program == mode_prog_single_channel) {
    // обработчик ошибок
    //irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, IRS_NULL);
  }
}
//загрузка конфигураций калибровки на экран
void TDataHandlingF::load_config_calibr_to_display()
{
  String dir = m_file_name_service.get_config_dir();
  if(DirectoryExists(dir)){
    mv_list_config_calibr.clear();
    ConfigCB->Clear();
    const String ext = m_file_name_service.get_config_ext();
    TSearchRec sr;
    String filter = dir + String(irst("\\*")) + irst(".") + ext;
    if(FindFirst(filter, faAnyFile, sr) == 0){
      ConfigCB->Items->Add(extract_short_filename(sr.Name));
      mv_list_config_calibr.push_back(dir + irst("\\") + sr.Name);
      while(FindNext(sr) == 0){
        ConfigCB->Items->Add(extract_short_filename(sr.Name));
        mv_list_config_calibr.push_back(dir + irst("\\") + sr.Name);
      }
      ConfigCB->ItemIndex = 0;
    }
    FindClose(sr);
  }
}

void TDataHandlingF::select_config(const String& a_config_name)
{
  const int index = ConfigCB->Items->IndexOf(a_config_name);
  select_config(index);
}

void TDataHandlingF::select_config(int a_index)
{
  if ((a_index >= 0) && (a_index < ConfigCB->Items->Count)) {
    ConfigCB->ItemIndex = a_index;
  } else {
    ConfigCB->ItemIndex = 0;
  }
}

String TDataHandlingF::get_selected_config()
{
  if (ConfigCB->ItemIndex >= 0) {
    return ConfigCB->Items->Strings[ConfigCB->ItemIndex];
  }
  return String();
}

String TDataHandlingF::get_selected_config_filename() const
{
  const int index_file = ConfigCB->ItemIndex;
  const int file_count = static_cast<int>(mv_list_config_calibr.size());
  if((index_file >= 0) && (index_file < file_count)) {
    return mv_list_config_calibr[index_file];
  }
  return String();
}

//загрузка конфигурации калибровки
void TDataHandlingF::load_config_calibr()
{
  DGI_MSG("Загрузка конфигурации калибровки.");
  m_conf_calibr_buf.clear();
  m_load_conf_calibr_device_success = false;
  int index_file = ConfigCB->ItemIndex;
  // если выбран файл
  if (index_file >= 0) {
    // если файл существует
    String filename_conf = mv_list_config_calibr[index_file];
    if (FileExists(filename_conf)) {
      m_cur_index_conf_calibr = index_file;
      m_cur_filename_conf_calibr_device = filename_conf.c_str();
      m_conf_calibr_buf.load(m_cur_filename_conf_calibr_device.c_str());
      m_config_calibr = m_conf_calibr_buf;

      m_inf_in_param.type_variable_param1 =
        m_config_calibr.in_parameter1.unit.c_str();
      m_inf_in_param.type_variable_param2 =
        m_config_calibr.in_parameter2.unit.c_str();
      m_inf_in_param.type_variable_param3 =
        m_config_calibr.in_parameter3.unit.c_str();
      if (m_config_calibr.in_parameter1.anchor == true) {
        m_inf_in_param.type_anchor = PARAMETR1;
        m_inf_in_param.number_in_param = TWO_PARAM;
      } else if(m_config_calibr.in_parameter2.anchor == true) {
        m_inf_in_param.type_anchor = PARAMETR2;
        m_inf_in_param.number_in_param = TWO_PARAM;
      } else {
        m_inf_in_param.type_anchor = PARAMETR3;
        m_inf_in_param.number_in_param = THREE_PARAM;
      }

      load_devices();

      m_default_param_cur_cell.col_value.value =
        m_config_calibr.in_parameter1.default_val;

      m_default_param_cur_cell.col_value.init = true;

      m_default_param_cur_cell.row_value.value =
        m_config_calibr.in_parameter2.default_val;

      m_default_param_cur_cell.row_value.init = true;

      m_default_param_cur_cell.top_value.value =
        m_config_calibr.in_parameter3.default_val;

      m_default_param_cur_cell.top_value.init = true;

      // Загрузка последнего активного файла
      const String file_namedir = m_file_name_service.make_absolute_path(
        m_config_calibr.active_filename);

      if (FileExists(file_namedir)) {
        const String cur_file_name = mp_active_table->get_file_namedir();
        // Всегда перезагружаем активный файл, так как конфигурация ячеек могла
        // быть изменена и нам надо обновить ее в mp_active_table
        bool load_result = mp_active_table->load_table_from_file(file_namedir.c_str(),
          m_inf_in_param, m_config_calibr.cells_config);
      } else {
        mp_active_table->clear_file_name();
        mp_active_table->create_new_table(m_inf_in_param,
          m_config_calibr.cells_config);
      }
      Caption = m_prog_name + String(irst(" - ")) + file_namedir;

      OutParamControlGroupBox->Visible = has_cells_out_param_ctrl_enabled();
      temperature_control_common_cfg_t temperature_cfg =
        m_config_calibr.temperature_ctrl_common_cfg;
      
      TemperatureControlGroupBox->Visible = temperature_cfg.enabled;   
      m_load_conf_calibr_device_success = true;

      DGI_MSG("Загрузка конфигурации калибровки успешно завершена.");

      // загрузка конфигурации опорного канала
      if (m_config_calibr.reference_channel.enabled) {
        m_config_calibr_ref_channel = m_config_calibr;
        m_config_calibr_ref_channel.ip_adress =
          m_config_calibr_ref_channel.reference_channel.ip_adress;
        m_config_calibr_ref_channel.port =
          m_config_calibr_ref_channel.reference_channel.port;
        m_config_calibr_ref_channel.reference_channel.enabled = false;
      }

    }else{
      DGI_MSG("Загрузка конфигурации прервана.");
      DGI_MSG(irs::str_conv<irs::string>(
        irst("Файл \"") + filename_conf + irst("\" отсутствует") + irst(".")));
      MessageDlg(irst("Файл \"") + filename_conf + irst("\" отсутствует") +
        irst("."),
        mtError,
        TMsgDlgButtons()<<mbOK,
        0);
    }
  }
}

void TDataHandlingF::set_connect_if_enabled(bool a_forced_connect)
{
  if (ConnectAction->Checked) {
    set_connect_calibr_device(a_forced_connect);
  }
}

void TDataHandlingF::set_connect_calibr_device(
  bool a_forced_connect)
{
  if ((!m_on_block_reconfiguration) || (a_forced_connect == true)) {
    int index_file = ConfigCB->ItemIndex;
    if (index_file >= 0) {

      load_config_calibr();

      bool reset_connect = false;
      if (a_forced_connect) {
        reset_connect = true;
      }
      m_cur_config_device = m_config_calibr.device_name;

      if (!m_device.created()) {
        reset_connect = true;
      }
      if (reset_connect) {
        load_devices();
        //m_cur_config_device = select_config_device;
        // В этой функции пересоздается устройство
        //load_config_calibr();
        DGI_MSG("Установка соединения с устройством");
      }
      m_device.enable(m_config_calibr);
      if (m_config_calibr.reference_channel.enabled) {
        m_ref_device.enable(m_config_calibr_ref_channel);
      }
      m_on_reset_functional_bits = true;
    }
  }
}

bool TDataHandlingF::set_connect_multimeter(const String& a_type_meas)
{
  type_meas_t type_meas = tm_volt_dc;
  IRS_ASSERT(str_to_type_meas(a_type_meas.c_str(), type_meas));
  m_type_meas = type_meas;
  /*String cur_multimetr = get_selected_multimeter();
  multimeter_mode_type_t mode = mul_mode_type_active;
  if (m_type_meas == tm_value) {
    mode = mul_mode_type_passive;
  }
  m_value_meas.set_connect_multimeter(
    str_to_type_multimeter(cur_multimetr.c_str()), mode);*/
  if (!mp_mxmultimeter_assembly.is_empty()) {
    multimeter_mode_type_t mode = mul_mode_type_active;
    if (m_type_meas == tm_value) {
      mode = mul_mode_type_passive;
    }
    //try {
    mp_mxmultimeter_assembly->enable(mode);
    m_value_meas.set_connect_multimeter(
      mp_mxmultimeter_assembly->mxmultimeter());
    /*} catch (Exception& e) {
      Application->ShowException(&e);
      m_value_meas.disconnect_multimetr();
      return false;
    }*/
  }
  return true;
}

String TDataHandlingF::get_selected_multimeter()
{
  int index_multimetr = PatternOfMeasuringInstrumentCB->ItemIndex;
  return PatternOfMeasuringInstrumentCB->Items->Strings[index_multimetr];
}

void TDataHandlingF::reset_connect_calibr_device()
{
  //m_data_map.reset_connection();
  m_device.disable();
  /*if (!mp_ref_device.is_empty()) {
    mp_ref_device->mxdata_assembly->enabled(false);
  } */
  m_ref_device.disable();
}

void TDataHandlingF::reset_connect_multimetr()
{
  m_cur_config_multimetr = irst("");
  m_value_meas.disconnect_multimeter();
  PatternOfMeasuringInstrumentCB->Enabled = true;
}

void TDataHandlingF::calculation_koef(irs::matrix_t<cell_t> a_matrix)
{
  const int size_of_ident = sizeof(irs_u32);
  const int size_of_size_x = sizeof(irs_u32);
  const int size_of_size_y = sizeof(irs_u32);
  lang_type_t x_elem_type = m_config_calibr.in_parameter1.type;
  lang_type_t y_elem_type = m_config_calibr.in_parameter2.type;
  lang_type_t z_elem_type = m_config_calibr.out_parameter.type;


  mv_col_optimal_data.clear();
  mv_row_optimal_data.clear();
  mv_coef_data.clear();


  const int x_elem_size = size_of_type(x_elem_type);
  const int y_elem_size = size_of_type(y_elem_type);
  const int z_elem_size = size_of_type(z_elem_type);


  m_bad_cells = false;


  int col_count = a_matrix.col_count();
  int row_count = a_matrix.row_count();
  if (col_count == 0 || row_count == 0) {
    m_bad_cells = true;
  }


  for(int x = 1; x < col_count; x++){
    cell_t cell_col = a_matrix[x][0];
    mv_col_optimal_data.push_back(cell_col.value);
    if(!cell_col.init){
      m_bad_cells = true;
      break;
    }
  }


  if(!m_bad_cells){
    for(int row = 1; row < row_count; row++){
      cell_t cell_row = a_matrix[0][row];
      mv_row_optimal_data.push_back(cell_row.value);
      if(!cell_row.init){
        m_bad_cells = true;
        break;
      }
    }
  }
  // если два параметра
  if(m_inf_in_param.number_in_param == TWO_PARAM){
    // если привязка к первому параметру
    if(m_inf_in_param.type_anchor == PARAMETR1){
      for(int y = 1; y < row_count; y++){
        if(m_bad_cells)
          break;
        for(int x = 1; x < col_count; x++) {
          cell_t cell = a_matrix[x][y];
          double numerator = cell.value;
          cell_t cell_col = a_matrix[x][0];
          double denominator = cell_col.value;
          if((denominator == 0) || (!cell.init) || (!cell_col.init)){
            m_bad_cells = true;
            break;
          }
          double coef_k = numerator/denominator;
          mv_coef_data.push_back(coef_k);
        }
      }
    }else{
      for(int y = 1; y < row_count; y++){
        if(m_bad_cells)
          break;
        cell_t cell_row = a_matrix[0][y];
        double denominator = cell_row.value;
        for(int x = 1; x < col_count; x++){
          cell_t cell = a_matrix[x][y];
          double numerator = cell.value;
          if(denominator == 0 || (!cell_row.init) || (!cell.init)){
            m_bad_cells = true;
            break;
          }
          double coef_k = numerator/denominator;
          mv_coef_data.push_back(coef_k);
        }
      }
    }
  }else{
    //int table_count = v_table.size();
    std::vector<irs::matrix_t<cell_t> > v_table;
    v_table.push_back(a_matrix);
    // Достраиваем вторую таблицу
    irs::matrix_t<cell_t> sub_table;
    sub_table = a_matrix;
    const double phase_value = 180;
    cell_t cell_phase;
    cell_phase.init = true;
    cell_phase.value = phase_value;
    sub_table[0][0] = cell_phase;
    for (int col = 1; col < col_count; col++) {
      for (int row = 1; row < row_count; row++) {
        cell_t cell = sub_table[col][row];
        if (cell.init) {
          cell.value += phase_value;
          sub_table[col][row] = cell;
        } else {
          m_bad_cells = true;
          break;
        }
      }
    }
    if(!m_bad_cells) {
      v_table.push_back(sub_table);
    }


    cell_t cell_top1 = v_table[0][0][0];
    double y1 = cell_top1.value;
    cell_t cell_top2 = v_table[1][0][0];
    double y2 = cell_top2.value;
    if((!cell_top1.init) || (!cell_top2.init)) {
      m_bad_cells = true;
    }
    vector<double> v_coef_k_data;
    vector<double> v_coef_b_data;
    for(int y = 1; y < row_count; y++){
      if(m_bad_cells)
        break;
      for(int x = 1; x < col_count; x++){
        cell_t cell_x1 = v_table[0][x][y];
        double x1 = cell_x1.value;
        cell_t cell_x2 = v_table[1][x][y];
        double x2 = cell_x2.value;
        if ((!cell_x1.init) || (!cell_x2.init) || (x1 == x2)) {
          m_bad_cells = true;
          break;
        }
        double k = 0.;
        double b = 0.;
        irs::koef_line(y1, x1, y2, x2, k, b);
        v_coef_k_data.push_back(k);
        v_coef_b_data.push_back(b);
      }
    }
    if(!m_bad_cells) {
      int coef_k_size = v_coef_k_data.size();
      int coef_b_size = v_coef_b_data.size();
      for (int i = 0; i < coef_k_size; i++) {
        mv_coef_data.push_back(v_coef_k_data[i]);
      }
      for (int i = 0; i < coef_b_size; i++) {
        mv_coef_data.push_back(v_coef_b_data[i]);
      }
    }
  }
  if (!m_bad_cells) {
    const size_type col_count = mv_col_optimal_data.size();
    const size_type row_count = mv_row_optimal_data.size();
    const size_type coef_count = mv_coef_data.size();
    m_need_size_memory = size_of_ident + size_of_size_x + size_of_size_y +
      x_elem_size*mv_col_optimal_data.size()+
      y_elem_size*mv_row_optimal_data.size()+
      z_elem_size*mv_coef_data.size();
  } else {
    m_need_size_memory = 0;
  }
}

void TDataHandlingF::tick()
{
  m_on_block_reconfiguration = m_auto_meas_is_running;
  if (m_load_conf_calibr_device_success && m_device.enabled()) {
    m_device.tick();
    m_ref_device.tick();

    if (m_config_calibr.reference_channel.enabled) {
      for (int i = 0; i < 10; i++) {
        mp_mxnet_ref_channel->tick();
      }
      mp_mxnet_data_ref_channel->tick();
    }
    #ifdef debug_irsdigint
    m_on_out_data = false;
    #endif //debug_irsdigint

    if  (m_device.connected()) {

      m_y_out_filter.add(m_device.get_data()->y_out);
      m_y_out_filter.tick();

      //return;
      const irs_u32 work_time = m_device.get_data()->work_time;
      WorkTimeDeviceLE->Text = num_to_cbstr(work_time);
      if (m_cur_cell_cfg.out_param_control_config.enabled) {
        if (m_auto_meas_is_running) {
          double out_param = m_device.get_data()->y_out;
          coord_cell_t coord_cur_cell = m_manager_traffic_cell.get_coord_cell();
          param_cur_cell_t param_cur_cell =
            mp_active_table->get_param_cell(
            coord_cur_cell.col, coord_cur_cell.row);
          double difference = get_anchor_in_param(param_cur_cell)*
            m_cur_cell_cfg.out_param_control_config.max_relative_difference;
          bool out_param_allowable =
            fabs(out_param - get_anchor_in_param(param_cur_cell)) <= difference;
          m_out_param_stability_control.set_current(out_param);
          CurrentOutParamLabeledEdit->Text = FloatToStr(out_param);
          if (out_param_allowable) {
            CurrentOutParamLabeledEdit->Font->Color = clBlue;
          } else {
            CurrentOutParamLabeledEdit->Font->Color = clRed;
          }
          ReferenceOutParamLabeledEdit->Text = FloatToStr(
            get_anchor_in_param(param_cur_cell));
          AbsoluteDiffOutParamLabeledEdit->Text = FloatToStr(difference);

          double remaining_time = max(0.,
            m_cur_cell_cfg.out_param_control_config.time -
            m_out_param_stability_control.get_stable_state_time());
          RemainingTimeForStableState->Text =
            IntToStr(static_cast<int>(remaining_time));
        }
      }
      if (m_config_calibr.temperature_ctrl_common_cfg.enabled) {
        const double temperature = m_device.get_data()->temperature;
        CurrentTemperatureLabeledEdit->Text = FloatToStr(temperature);
        if (m_cur_cell_cfg.temperature_control.enabled) {

          bool temperature_allowable = fabs(temperature -
            m_cur_cell_cfg.temperature_control.reference) <=
            m_cur_cell_cfg.temperature_control.difference;
          m_temperature_stability_control.set_current(temperature);
          
          if (temperature_allowable) {
            CurrentTemperatureLabeledEdit->Font->Color = clBlue;
          } else {
            CurrentTemperatureLabeledEdit->Font->Color = clRed;
          }
        } else {
          CurrentTemperatureLabeledEdit->Font->Color = clBlack;
        }
      }
      if (m_device.get_data()->operating_duty_bit == 1) {
        m_on_reg_ready = true;
      } else {
        m_on_reg_ready = false;
      }

      CurrentStatusLabeledEdit->Font->Color = clBlue;
      CurrentStatusLabeledEdit->Text = "Соединение установлено!";
      bool forcibly_set_mismatch_state = false;
      bool forcibly_set_correct_mode = false;
      if (m_on_reset_functional_bits){
        m_on_reset_functional_bits = false;
        forcibly_set_mismatch_state = true;
        forcibly_set_correct_mode = true;
      }else{
        forcibly_set_mismatch_state = false;
        forcibly_set_correct_mode = false;
      }
      set_mismatch_state(m_on_mismatch_state, forcibly_set_mismatch_state);
      set_correct_mode(m_on_correct, forcibly_set_correct_mode);
    }else{
      CurrentStatusLabeledEdit->Font->Color=clRed;
      CurrentStatusLabeledEdit->Text = "Соединение разорвано!";
    }
    switch(status_connect)
    {
      case WAIT_CONNECT:      //ожидание коннекта
        //if(m_device.mxdata_assembly->mxdata()->connected()){
        if(m_device.connected()){
          status_connect = CONNECT;
          m_on_connect_mxnet_data = true;
          if(!m_non_first_connect_mxnet_data){
            m_non_first_connect_mxnet_data = true;
            bool forcibly = true;
            set_mismatch_state(m_on_mismatch_state, forcibly);
            set_correct_mode(m_on_correct, forcibly);
          }
        }
        break;
      case CONNECT:{         //устойчивое состояние: считывание данных
        //if(!m_device.mxdata_assembly->mxdata()->connected())
        if(!m_device.connected())
        {
          m_on_connect_mxnet_data = false;
          m_on_connect_eeprom = false;
          status_connect = WAIT_CONNECT;
        } else {
          if(m_on_out_data)
          {
            status_connect = OUT_DATA;
          }
        }
      } break;
      case OUT_DATA: {
        if (m_param_cur_cell.col_value.init == true &&
          m_param_cur_cell.row_value.init == true) {
          if(!m_device.connected()) {
            int a = 0;
          }
          m_device.get_data()->x_in =
            m_param_cur_cell.col_value.value;
          m_device.get_data()->y_in =
            m_param_cur_cell.row_value.value;
          if (m_config_calibr.reference_channel.enabled) {
             mp_data_map_ref_channel->x_in =
              m_param_cur_cell.col_value.value;
             mp_data_map_ref_channel->y_in =
              m_param_cur_cell.row_value.value;
          }
          if (m_inf_in_param.number_in_param == THREE_PARAM) {
            m_device.get_data()->q_in = m_param_cur_cell.top_value.value;
            if (m_config_calibr.reference_channel.enabled) {
              mp_data_map_ref_channel->q_in = m_param_cur_cell.top_value.value;
            }
          }
        }
        m_on_out_data = false;
        status_connect = CONNECT;
      } break;
    }
    /*switch(m_status_options)
    {
      case OFF_PROCESSING:{
        m_status_options = mp_options_form->status_options();
      } break;
      case ON_UPDATE:{
        m_options_mnk = mp_options_form->read_options_mnk();
        m_options_correct = mp_options_form->read_options_correct();
        m_options_coef = mp_options_form->read_options_coef();
        //сохранение в файл
        //...
        mp_options_form->reset_status_options();
        m_status_options = OFF_PROCESSING;
      } break;
      case ON_READ:{
        mp_options_form->write_options_mnk(m_options_mnk);
        mp_options_form->write_options_correct(m_options_correct);
        mp_options_form->write_options_coef(m_options_coef);
        mp_options_form->reset_status_options();
        m_status_options = OFF_PROCESSING;
      } break;
    } */
  }//if(m_load_conf_calibr_device_success)
  else {
    CurrentStatusLabeledEdit->Font->Color = clBlack;
    CurrentStatusLabeledEdit->Text = irst("Соединение выключено!");
  }

  eeprom_tick();

  if (m_timer_chart_auto_update.check()) {
    if (m_chart.get_auto_update_stat()) {
      bool on_update = true;
      m_chart.add_all_chart_z_of_x(mp_active_table, m_inf_in_param, on_update);
      m_chart.add_all_chart_z_of_y(mp_active_table, m_inf_in_param, on_update);
    }
  }
  #ifdef  debug_version_digital_interpolator
  //mp_active_table->no_modifi();
  #endif
  tick_calibr_data();

  if (ShowMeasPointChartAction->Checked) {
    // Если пользователь закрыл окно, удаляем объект графика и
    // сбрасываем галочку в меню
    if (!mp_meas_point_chart->visible()) {
      mp_meas_point_chart.reset();
      ShowMeasPointChartAction->Checked = false;
    }
  }
}

void TDataHandlingF::eeprom_tick()
{
  if (m_on_connect_mxnet_data) {
    switch(status_connect_eeprom){
      case sce_off: {
        if(m_on_write_data_eeprom) {
          if(m_bad_cells){
            status_connect_eeprom = sce_reset;
            DGI_MSG("Произошел сбой при расчете коэффициентов. " <<
              "Запись прервана");
          } else if(
            irs_i32(m_max_size_correct -
              m_need_size_memory) < 0){
            status_connect_eeprom = sce_reset;
            DGI_MSG("Нехватает памяти для прошивки");
            DGI_MSG("Обьем данных " << m_need_size_memory << " байт");
            DGI_MSG("Доступный размер памяти "<<
              m_max_size_correct << " байт");
          } else if (m_need_size_memory > 0) {
            DGI_MSG("Происходит запись в еепром.");
            DGI_MSG("Индек смещения " << m_index_pos_offset_eeprom);
            DGI_MSG("Обьем данных "+ m_need_size_memory << " байт");
            DGI_MSG("Доступный размер памяти " <<
              m_max_size_correct << " байт");
            status_connect_eeprom = sce_create_interface_eeprom;
          } else {
            DGI_MSG("Нет данных для записи.");
            status_connect_eeprom = sce_reset;
          }
        } else if (m_on_verification_data_eeprom) {
          if(m_bad_cells){
            status_connect_eeprom = sce_reset;
            DGI_MSG("Произошел сбой при расчете коэффициентов. " <<
              "Верификация данных прервана");
          }else if(
            irs_i32(m_max_size_correct -
              m_need_size_memory) < 0){
            status_connect_eeprom = sce_reset;
            DGI_MSG("Обьем данных превышает допустимый обьем памяти.");
            DGI_MSG("Обьем данных " << m_need_size_memory << " байт");
            DGI_MSG("Доступный размер памяти " << m_max_size_correct <<
              " байт");
          }else if (m_need_size_memory > 0) {
            DGI_MSG("Началась верификация данных.");
            DGI_MSG("Индек смещения " << m_index_pos_offset_eeprom);
            DGI_MSG("Обьем данных " << m_need_size_memory << " байт");
            DGI_MSG("Доступный размер памяти " << m_max_size_correct <<
              " байт");
            status_connect_eeprom = sce_create_interface_eeprom;
          } else {
            DGI_MSG("Нет данных для верификации.");
            status_connect_eeprom = sce_reset;
          }
        }
      } break;
      case sce_create_interface_eeprom: {
        mp_eeprom.reset(new irs::funnel_client_t(
          m_device.get_mxdata(),
          m_config_calibr.index_pos_eeprom,
          MS_TO_CNT(200),
          m_index_pos_offset_eeprom,
          m_need_size_memory,
          irs::fcm_reduce));
        status_connect_eeprom = sce_wait_connect_eeprom;
      } break;
      case sce_wait_connect_eeprom: {
        if (mp_eeprom->connected()) {
          m_correct_map.connect(
            mp_eeprom.get(), 0, m_config_calibr, number_of_koef_per_point());
          m_on_connect_eeprom = true;
          status_connect_eeprom = sce_set_param_eeprom;
        }
        mp_eeprom->tick();
      } break;
      case sce_set_param_eeprom: {
        m_correct_map.connect(
          mp_eeprom.get(), 0, m_config_calibr, number_of_koef_per_point());
        m_correct_map.map_id = 1;
        m_correct_map.x_count = mv_col_optimal_data.size();
        m_correct_map.y_count = mv_row_optimal_data.size();
        m_correct_map.connect(
          mp_eeprom.get(), 0, m_config_calibr, number_of_koef_per_point());
        if (m_on_write_data_eeprom) {
          status_connect_eeprom = sce_write_eeprom;
        } else if(m_on_verification_data_eeprom){
          mp_eeprom->reset_stat_read_complete();
          set_progress_bar_mode_verification();
          //m_exec_progress.show();
          //m_exec_progress.p_comment->Caption = "Процесс верификации данных.";
          //m_exec_progress.p_percent_progress->Caption = "0%";
          //m_exec_progress.p_progress_bar->Position = 0;
          //set_progress_bar_value(0);
          status_connect_eeprom = sce_wait_read_eeprom;
        } else {
          status_connect_eeprom = sce_reset;
        }
      } break;
      case sce_wait_read_eeprom: {
        if (mp_eeprom->read_complete()) {
          mp_local_data.reset(
            new irs::local_data_t(m_max_size_correct));
          m_correct_map_local.connect(
            mp_local_data.get(), 0, m_config_calibr,
            number_of_koef_per_point());
          m_correct_map_local.map_id = 1;
          m_correct_map_local.x_count = mv_col_optimal_data.size();
          m_correct_map_local.y_count = mv_row_optimal_data.size();
          m_correct_map_local.connect(
            mp_local_data.get(), 0, m_config_calibr,
            number_of_koef_per_point());
          int vcol_opt_size = mv_col_optimal_data.size();
          for(int i = 0; i < vcol_opt_size; i++){
            m_correct_map_local.x_points[i] =
              mv_col_optimal_data[i]*m_config_calibr.in_parameter1.koef;
          }
          int vrow_opt_size = mv_row_optimal_data.size();
          for(int i = 0; i < vrow_opt_size; i++){
            m_correct_map_local.y_points[i] =
              mv_row_optimal_data[i]*m_config_calibr.in_parameter2.koef;
          }
          int vcoef_data_size = mv_coef_data.size();
          for(int i =  0; i < vcoef_data_size; i++)
            m_correct_map_local.koef_array[i] = mv_coef_data[i];
          //status_connect_eeprom = sce_reset;
          //m_on_verification_data_eeprom = false;
          status_connect_eeprom = sce_verification_eeprom;
        } else {
          mp_eeprom->tick();
          int need_read_byte_size = mp_eeprom->get_read_size();
          int percent = 100*(m_need_size_memory-need_read_byte_size)/
            m_need_size_memory;
          if (percent < 0) {
            percent = 0;
          } else if (percent > 100){
            percent = 100;
          }
          m_exec_progress.p_percent_progress->Caption =
            IntToStr(percent)+"%";
          //m_exec_progress.p_progress_bar->Position = percent;
          set_progress_bar_value(percent);
        }
      } break;
      case sce_verification_eeprom: {
        bool data_equal = true;
        if (m_correct_map.map_id != m_correct_map_local.map_id) {
          data_equal = false;
        } else if (m_correct_map.x_count != m_correct_map_local.x_count) {
          data_equal = false;
        } else if (m_correct_map.y_count != m_correct_map_local.y_count) {
          data_equal = false;
        }
        if (data_equal) {
          int x_points_cm_size = m_correct_map.x_points.size();
          int x_points_cml_size = m_correct_map_local.x_points.size();
          if (x_points_cm_size != x_points_cml_size) {
            data_equal = false;
          } else {
            for (int i = 0; i < x_points_cm_size; i++) {
              if (m_correct_map.x_points[i] !=
                m_correct_map_local.x_points[i]) {
                data_equal = false;
                break;
              }
            }
          }
        }
        if (data_equal) {
          int y_points_cm_size = m_correct_map.y_points.size();
          int y_points_cml_size = m_correct_map_local.y_points.size();

          if (y_points_cm_size != y_points_cml_size) {
            data_equal = false;
          } else {
            for (int i = 0; i < y_points_cm_size; i++) {
              if (m_correct_map.y_points[i] !=
                m_correct_map_local.y_points[i]) {
                data_equal = false;
                break;
              }
            }
          }
        }
        if (data_equal) {
          int koef_array_cm_size = m_correct_map.koef_array.size();
          int koef_array_cml_size = m_correct_map_local.koef_array.size();
          if (koef_array_cm_size != koef_array_cml_size) {
            data_equal = false;
          } else {
            for (int i = 0; i < koef_array_cm_size; i++) {
              const long double remote_k = m_correct_map.koef_array[i];
              const long double local_k = m_correct_map_local.koef_array[i];
              if (remote_k != local_k) {
                data_equal = false;
                break;
              }
            }
          }
        }
        if (data_equal) {
          DGI_MSG("Верификация данных завершена.");
          DGI_MSG("Различий не выявлено.");
        } else {
          DGI_MSG("Верификация данных завершена.");
          DGI_MSG("Найдены различия в данных!!!");
        }
        status_connect_eeprom = sce_reset;
        //status_connect_eeprom = sce_off;
      } break;
      case sce_write_eeprom: {
        int vcol_opt_size = mv_col_optimal_data.size();
        for(int i = 0; i < vcol_opt_size; i++){
          m_correct_map.x_points[i] =
            mv_col_optimal_data[i]*m_config_calibr.in_parameter1.koef;
        }
        int vrow_opt_size = mv_row_optimal_data.size();
        for(int i = 0; i < vrow_opt_size; i++){
          m_correct_map.y_points[i] =
            mv_row_optimal_data[i]*m_config_calibr.in_parameter2.koef;
        }
        int vcoef_data_size = mv_coef_data.size();
        for(int i = 0; i < vcoef_data_size; i++)
          m_correct_map.koef_array[i] = mv_coef_data[i];

        set_progress_bar_mode_program();
        //m_exec_progress.show();
        //m_exec_progress.p_comment->Caption = "Процесс прошивки.";
        //m_exec_progress.p_percent_progress->Caption = "0%";
        //m_exec_progress.p_progress_bar->Position = 0;
        //set_progress_bar_value(0);
        status_connect_eeprom = sce_wait_write_eeprom;
      } break;
      case sce_wait_write_eeprom: {
        int need_write_byte_size = mp_eeprom->get_write_size();
        if (need_write_byte_size > 0) {
          mp_eeprom->tick();
          int percent = 100*(m_need_size_memory-need_write_byte_size)/
            m_need_size_memory;
          m_exec_progress.p_percent_progress->Caption =
            IntToStr(percent)+"%";
          //m_exec_progress.p_progress_bar->Position = percent;
          set_progress_bar_value(percent);
        } else {
          m_exec_progress.hide();
          m_exec_progress.clear();
          //m_on_write_data_eeprom = false;
          //m_on_verification_data_eeprom = true;
          status_connect_eeprom = sce_reset;
          DGI_MSG("Прошивка данных завершена.");
        }

      } break;
      case sce_reset: {
        mp_eeprom.reset(IRS_NULL);
        m_on_write_data_eeprom = false;
        m_on_verification_data_eeprom = false;
        m_exec_progress.clear();
        m_exec_progress.hide();
        status_connect_eeprom = sce_off;
      } break;
    }
  }
}
//---------------------------------------------------------------------------

void TDataHandlingF::set_type_jump(
  type_jump_next_elem_t a_type_jump_next_elem)
{
  m_type_jump_next_elem = a_type_jump_next_elem;
  m_str_type_jump_next_elem =
    type_jump_next_elem_to_str(m_type_jump_next_elem).c_str();
  m_manager_traffic_cell.set_type_traffic(m_type_jump_next_elem);
}
void TDataHandlingF::set_jump_smooth()
{
  switch(m_type_jump_next_elem)
  {
    case HORIZONTAL_DOWN:{
      m_type_jump_next_elem = HORIZONTAL_DOWN_SMOOTH;
    } break;
    case HORIZONTAL_UP:{
      m_type_jump_next_elem = HORIZONTAL_UP_SMOOTH;
    } break;
    case VERTICAL_FORWARD:{
      m_type_jump_next_elem = VERTICAL_FORWARD_SMOOTH;
    } break;
    case VERTICAL_BACK:{
      m_type_jump_next_elem = VERTICAL_BACK_SMOOTH;
    } break;
  }
  m_on_jump_smooth = true;
  m_str_type_jump_next_elem =
    type_jump_next_elem_to_str(m_type_jump_next_elem).c_str();
  m_manager_traffic_cell.set_type_traffic(m_type_jump_next_elem);
}
void TDataHandlingF::reset_jump_smooth()
{
  switch(m_type_jump_next_elem)
  {
    case HORIZONTAL_DOWN_SMOOTH:{
      m_type_jump_next_elem = HORIZONTAL_DOWN;
    } break;
    case HORIZONTAL_UP_SMOOTH:{
      m_type_jump_next_elem = HORIZONTAL_UP;
    } break;
    case VERTICAL_FORWARD_SMOOTH:{
      m_type_jump_next_elem = VERTICAL_FORWARD;
    } break;
    case VERTICAL_BACK_SMOOTH:{
      m_type_jump_next_elem = VERTICAL_BACK;
    } break;
  }
  m_on_jump_smooth = false;
  m_str_type_jump_next_elem =
    type_jump_next_elem_to_str(m_type_jump_next_elem).c_str();
  m_manager_traffic_cell.set_type_traffic(m_type_jump_next_elem);
}
//---------------------------------------------------------------------------
void TDataHandlingF::processing_select_cell(TStringGrid* a_table,
    int a_col, int a_row, bool &a_can_select)
{
}
//--------------------------------------------------------------------------
void TDataHandlingF::processing_key_return_and_ctrl_down(
  TStringGrid* const a_table,
  WORD& a_key,
  const TShiftState Shift)
{
  if (a_key == VK_RETURN) {
    if (m_cur_cell_table1.init){
      string_type latest_entry_previous_cell_str =
        RawDataStringGrid->Cells
        [m_cur_cell_table1.col][m_cur_cell_table1.row].c_str();
      if(m_cur_cell_table1.value_str != latest_entry_previous_cell_str){
        mp_active_table->cur_cell_in_display();
        RawDataStringGrid->Repaint();
      }
      m_cur_cell_table1.init = false;

      if(a_table->Row == 0)//если находимся в нулевой строке
      {
        if(a_table->Col < a_table->ColCount-1)
          a_table->Col++;  //сдвигаемся вправо
        else
        {
          a_table->Row++;
          a_table->Col = 0;
        }
      }
      else if(a_table->Col == 0)//если находимся в нулевом столбце
      {
        if(a_table->Row < a_table->RowCount-1)
        {
          coord3d_t coord_cell_table =
            mp_active_table->get_coord_cell_table(a_table->Col,a_table->Row);
          int num_table = coord_cell_table.z;
          int row_table = coord_cell_table.y;
          if((num_table > 0) && (row_table == 0)){
            int table_count = mp_active_table->table_count();
            if(num_table < table_count-1){
              int row_count = mp_active_table->row_count();
              a_table->Row+=row_count;  //сдвигаемся вниз
            }else{
              a_table->Row = 1;
              a_table->Col = 1;
            }

          }else{
            a_table->Row++;  //сдвигаемся вниз
          }
        }
        else
        {
          a_table->Col = 1;
          a_table->Row = 1;
        }
      }
      else if(a_table->Col < a_table->ColCount-1)
      {
        a_table->Col++; //cдвигаемся вправо
      }
      else if(a_table->Col >= a_table->ColCount-1)
      {
        if(a_table->Row < a_table->RowCount-1)
        {
          coord3d_t coord_cell_table =
            mp_active_table->get_coord_cell_table(a_table->Col,a_table->Row+1);
          int row_table = coord_cell_table.y;
          if(row_table != 0){
            a_table->Row++;
          }else{
            a_table->Row+=2;
          }
          a_table->Col = 1;

        }
      }
      on_select_cell(a_table->Col, a_table->Row, Shift);
    }
  } else if (a_key == VK_LEFT && !m_cur_cell_table1.init) {
    if(a_table->Col > 0) {
      a_table->Col--;
    }
    a_key = 0;
    on_select_cell(a_table->Col, a_table->Row, Shift);
  } else if (a_key == VK_RIGHT && !m_cur_cell_table1.init) {
    if(a_table->Col < a_table->ColCount - 1) {
      a_table->Col++;
    }
    a_key = 0;
    on_select_cell(a_table->Col, a_table->Row, Shift);
  } else if (a_key == VK_UP && !m_cur_cell_table1.init) {
    if(a_table->Row > 0) {
      a_table->Row--;
    }
    a_key = 0;
    on_select_cell(a_table->Col, a_table->Row, Shift);
  } else if (a_key == VK_DOWN && !m_cur_cell_table1.init) {
    if(a_table->Row < a_table->RowCount - 1) {
      a_table->Row++;
    }
    a_key = 0;
    on_select_cell(a_table->Col, a_table->Row, Shift);
  }/* else if (a_key == 'A' && Shift.Contains(ssCtrl)) {
    m_start_col = 1;
    m_start_row = 1;
    m_cells_range = TRect(1, 1, a_table->ColCount - 1, a_table->RowCount - 1);
    RawDataStringGrid->Invalidate();
    update_buttons_config();
  }*/
}
//---------------------------------------------------------------------------

void TDataHandlingF::on_select_cell(int a_col, int a_row, const TShiftState Shift)
{
  // Диапазоны обрабатываем только в том случае, если выбрана не ячейка шапки

  if(Shift.Contains(ssShift) && a_col > 0 && a_row > 0 &&
      m_start_col > 0 && m_start_row > 0) {

    m_cells_range.Left = std::min(m_start_col, a_col);
    m_cells_range.Top = std::min(m_start_row, a_row);
    m_cells_range.Right = std::max(m_start_col, a_col);
    m_cells_range.Bottom = std::max(m_start_row, a_row);
  } else if(a_col > 0 && a_row > 0) {
    m_start_col = a_col;
    m_start_row = a_row;
    m_cells_range.Left = a_col;
    m_cells_range.Top = a_row;
    m_cells_range.Right = a_col;
    m_cells_range.Bottom = a_row;
  } else {
    m_start_col = -1;
    m_start_row = -1;
    m_cells_range.Left = -1;
    m_cells_range.Top = -1;
    m_cells_range.Right = -1;
    m_cells_range.Bottom = -1;
  }

  RawDataStringGrid->Invalidate();

  update_buttons_config();

  // кнопки для старта измерения не блокируем, так как пользователю непонятно,
  // почему они заблокированы. При нажатии кнопок проверяется диапазон и
  // пользователю отобразится окно с ошибкой, если диапазон не выделен
  //
  /*if (!m_auto_meas_is_running) {
    StartAutoVoltMeasAction->Enabled = is_meas_cells_range_locked() ||
      is_cells_range_valid(m_cells_range);
    StartAutoVoltMeasActiveCellsAction->Enabled =
      StartAutoVoltMeasAction->Enabled;
  }*/
}



void TDataHandlingF::update_buttons_config()
{
  bool is_range_valid = is_cells_range_valid(m_cells_range);
  if (!LockMeasCellsRangeAction->Checked) {
    LockMeasCellsRangeAction->Enabled = is_range_valid;
  }

  coord_t coord;
  coord.x = m_copied_cell_config.col;
  coord.y = m_copied_cell_config.row;
  CopyCellsConfligAction->Enabled = is_range_valid;
  PasteCellsConfigAction->Enabled = is_range_valid &&
    mp_active_table->is_cells_config_coord_valid(coord);
}



void TDataHandlingF::select_cur_meas_cell()
{
  coord_cell_t coord_cur_cell = m_manager_traffic_cell.get_coord_cell();
  mp_active_table->set_col_displ(coord_cur_cell.col);
  mp_active_table->set_row_displ(coord_cur_cell.row);

  // подсветить текущую измеряемую ячейку
  m_start_col = coord_cur_cell.col;
  m_start_row = coord_cur_cell.row;
  m_cells_range.Left = m_start_col;
  m_cells_range.Right = m_start_col;
  m_cells_range.Top = m_start_row;
  m_cells_range.Bottom = m_start_row;
}



void TDataHandlingF::process_volt_meas()
{
  if(m_on_process_auto_meas_active_cell == true) {
    if (m_auto_meas_is_running != true) {
      m_on_start_new_auto_meas = true;
      /*if(m_status_process_meas != spm_jump_next_elem){
        m_on_process_auto_meas_active_cell = false;
      } */
    }/* else {
      m_on_start_new_auto_meas = true;
    }  */
  }
  if (m_on_stop_process_auto_volt_meas == true) {
    m_on_start_new_auto_meas = false;
    reset_stat_stop_process_avto_volt_meas();
    m_auto_meas_is_running = false;
    //config_button_stop_avto_volt_meas();
    m_status_process_meas = spm_reset;
    DGI_MSG("Стоп.");
  }
  if (m_auto_meas_is_running) {
    config_button_start_avto_volt_meas();
    m_timer_delay_control_error_bit.check();
    if (m_device.connected()) {
      if ((m_device.get_data()->error_bit == 1) &&
        m_timer_delay_control_error_bit.stopped()) {
        if (m_cur_count_reset_over_bit < m_cur_cell_cfg.count_reset_over_bit) {
          m_cur_count_reset_over_bit++;
          m_device.get_data()->reset_over_bit = 1;
          //m_on_start_new_auto_meas = true;
          //m_on_process_auto_meas_active_cell = true;

          //m_status_process_meas = spm_off_process;
          m_status_process_meas = spb_wait_connect;

          /*if (m_mode_program == mode_prog_single_channel) {
            m_status_process_meas = spm_set_range;
          } else {
            m_status_process_meas =
              spm_wait_ext_trig_set_range;
            m_log << "Ожидание внешнего запуска установки диапазона измерений.";
          } */
          //m_status_process_meas = spm_jump_next_elem;
          m_timer_delay_control_error_bit.set(m_delay_control_error_bit);
          m_timer_delay_next_cell.set(m_delay_next_cell);
          DGI_MSG("Сброс ошибки.");
          DGI_MSG("Ждем " << CNT_TO_DBLTIME(m_delay_next_cell) <<
            " секунд перед продолжением измерений.");
        } else {
          m_timer_delay_control_error_bit.set(m_delay_control_error_bit);
          DGI_MSG("Прибор не можнет выйти на рабочий режим.");
          DGI_MSG("Автоматическое измерение завершилось с ошибкой.");
          m_status_process_meas = spm_reset;
        }
      }
    }
  }
  switch(m_status_process_meas)
  {
    case spm_off_process: {
      if (m_need_restart) {
        m_need_restart = false;
        StartAutoVoltMeasActiveCellsActionExecute(NULL);
      }
    
      if (m_on_start_new_auto_meas == true) {
        m_count_point_meas = 0;
        m_previous_count_point_meas = 0;
        set_connect_calibr_device();
        m_on_start_new_auto_meas = false;
        m_auto_meas_is_running = true;
             
        IRS_ASSERT(!mp_active_table->is_cells_config_read_only() &&
          m_config_calibr.cells_config == mp_active_table->get_cells_config());
        IRS_ASSERT(is_cells_range_valid(m_meas_cells_range));

        m_manager_traffic_cell.set_min_col(m_meas_cells_range.Left);
        m_manager_traffic_cell.set_min_row(m_meas_cells_range.Top);
        m_manager_traffic_cell.set_max_col(m_meas_cells_range.Right);
        m_manager_traffic_cell.set_max_row(m_meas_cells_range.Bottom);    
             
        illegal_cells_t illegal_cells =
          mp_active_table->get_illegal_cells();
        m_manager_traffic_cell.set_illegal_cell(illegal_cells);
        m_cur_count_reset_over_bit = 0;
        m_cur_cell_cfg.clear();
        m_prev_cell_cfg.clear();


        // Всегда начинаем с левой верхней ячейки?
        m_manager_traffic_cell.set_current_cell(
          m_meas_cells_range.Left, m_meas_cells_range.Top);
        /*if (m_type_jump_next_elem == HORIZONTAL_DOWN ||
          m_type_jump_next_elem == HORIZONTAL_DOWN_SMOOTH ||
          m_type_jump_next_elem == VERTICAL_FORWARD ||
          m_type_jump_next_elem == VERTICAL_FORWARD_SMOOTH){
          m_manager_traffic_cell.set_current_cell(
            m_meas_cells_range.Left, m_meas_cells_range.Top);
        } else {
          m_manager_traffic_cell.set_current_cell(
            m_meas_cells_range.Right, m_meas_cells_range.Bottom);
        }*/
        if (m_on_process_auto_meas_active_cell) {
          int col = m_start_cell.col;
          int row = m_start_cell.row;
          col = irs::bound<int>(col, m_meas_cells_range.Left, m_meas_cells_range.Right);
          row = irs::bound<int>(row, m_meas_cells_range.Top, m_meas_cells_range.Bottom);

          m_manager_traffic_cell.set_current_cell(col, row);
          m_on_process_auto_meas_active_cell = false;
          DGI_MSG("Запуск автоматического измерения с активной ячейки.");
        } else {
          DGI_MSG("Запуск автоматического измерения.");
        }
        select_cur_meas_cell();

        m_cur_cell_cfg = get_cell_config(m_manager_traffic_cell.get_coord_cell());
        m_prev_cell_cfg = m_cur_cell_cfg;
        set_connect_multimeter(m_cur_cell_cfg.type_meas);
        set_control_parameters(m_cur_cell_cfg);

        m_status_process_meas = spb_wait_connect;
        /*if (m_mode_program == mode_prog_single_channel) {
          m_status_process_meas = spm_set_range;
        } else {
          m_status_process_meas =
            spm_wait_ext_trig_set_range;
          m_log <<
            irst("Ожидание внешнего запуска установки диапазона измерений.");
        }*/
        m_cell_count_end = m_manager_traffic_cell.get_cell_count_end();
        m_cell_count_end++;
        m_reset_time_meas = true;
        set_progress_bar_mode_calibration();
      }
    } break;

    case spb_wait_connect: {
      if (m_device.connected()) {
        if (m_timer_delay_control_error_bit.stopped()) {
          set_value_working_extra_params(m_manager_traffic_cell.get_coord_cell());
          set_value_working_extra_bits(m_manager_traffic_cell.get_coord_cell());
          /*if (m_mode_program == mode_prog_single_channel) {
            m_status_process_meas = spm_set_range;
          } else {
            m_status_process_meas = spm_wait_ext_trig_set_range;
            m_log <<
              irst("Ожидание внешнего запуска установки диапазона измерений.");
          } */
          m_timer_waiting_set_extra_vars.start();

          if (m_reset_time_meas) {
            m_time_meas.start();
            m_reset_time_meas = false;
          }

          if (m_mode_program == mode_prog_single_channel) {
            m_status_process_meas = spb_wait_apply_extra_params_and_bits;
          } else {
            m_status_process_meas = spb_wait_ext_trig_set_apply_params_and_bits;
          }
        }
      }
    } break;

    case spb_wait_ext_trig_set_apply_params_and_bits: {
      if (m_on_external) {
        m_on_external = false;
        m_status_process_meas = spb_wait_apply_extra_params_and_bits;
      }
    } break;

    case spb_wait_apply_extra_params_and_bits: {
      m_timer_waiting_set_extra_vars.check();
      if (m_timer_waiting_set_extra_vars.stopped()) {
        if (m_mode_program == mode_prog_single_channel) {
          m_status_process_meas = spm_set_range;
        } else {
          m_status_process_meas = spm_wait_ext_trig_set_range;
          DGI_MSG("Ожидание внешнего запуска установки диапазона измерений.");
        }
      }
    } break;

    case spm_jump_next_elem:{
      m_timer_delay_next_cell.check();
      if(m_timer_delay_next_cell.stopped()){
        bool next_elem_successfully = false;
        next_elem_successfully = m_manager_traffic_cell.next_cell();

        if (next_elem_successfully == false) {
          m_status_process_meas = spm_reset;
          DGI_MSG("Автоматическое измерение успешно завершено.");
        } else {
          DGI_MSG("Переход к следующей точке измерения.");
          select_cur_meas_cell();

          m_cur_cell_cfg = get_cell_config(m_manager_traffic_cell.get_coord_cell());

          bool need_to_update_work_values = 
            m_cur_cell_cfg.ex_param_work_values != m_prev_cell_cfg.ex_param_work_values ||
            m_cur_cell_cfg.ex_bit_work_values != m_prev_cell_cfg.ex_bit_work_values;

          bool need_to_recreate_multimeter = m_cur_cell_cfg.type_meas != m_type_meas;

          m_prev_cell_cfg = m_cur_cell_cfg;
          set_control_parameters(m_cur_cell_cfg);

          if (need_to_recreate_multimeter) {
            DGI_MSG("Необходимо перенастроить мультиметр. Выключаем сигнал");
            set_value_default_extra_params();
            set_value_default_extra_bits();
            //m_value_meas.disconnect_multimetr();
            out_default_param();
            m_timer_waiting_set_extra_vars.start();
            if (m_mode_program == mode_prog_single_channel) {
              m_status_process_meas = spm_wait_off_signal;
            } else {
              m_status_process_meas = spm_wait_ext_trig_off_signal;
            }
            break;
          }
          if (need_to_update_work_values) {
            m_status_process_meas = spb_wait_connect;
            break;
          }

          if (m_mode_program == mode_prog_single_channel) {
            m_status_process_meas = spm_set_range;
          } else {
            m_status_process_meas = spm_wait_ext_trig_set_range;
            DGI_MSG("Ожидание внешнего запуска установки диапазона измерений.");
          }
        }
      }
    } break;

    case spm_wait_ext_trig_off_signal: {
      if (m_on_external) {
        m_on_external = false;
        m_status_process_meas = spm_wait_off_signal;
      }
    } break;

    case spm_wait_off_signal: {
      m_timer_waiting_set_extra_vars.check();
      if (m_timer_waiting_set_extra_vars.stopped()) {
        m_value_meas.disconnect_multimeter();
        set_connect_multimeter(m_cur_cell_cfg.type_meas);
        m_status_process_meas = spb_wait_connect;
        //m_status_process_meas = spm_wait_set_extra_vars;
      }      
    } break;

    case spm_wait_ext_trig_set_range: {
      if (m_on_external) {
        m_on_external = false;
        m_status_process_meas = spm_set_range;
      }
    } break;
    case spm_set_range: {
      coord_cell_t coord_cur_cell = m_manager_traffic_cell.get_coord_cell();
      param_cur_cell_t param_cur_cell = mp_active_table->get_param_cell(
          coord_cur_cell.col, coord_cur_cell.row);
      double range = 0;

      try {
        range = set_range(param_cur_cell);
      } catch (std::logic_error &ex) {
        DGI_MSG(ex.what());
        DGI_MSG("Автоматическое измерение завершилось с ошибкой.");
        m_status_process_meas = spm_reset;
        break;
      }

      const double reference = get_anchor_in_param(param_cur_cell);
      m_out_param_stability_control.set_reference(reference);
      m_out_param_stability_control.set_diviation(reference*
        m_cur_cell_cfg.out_param_control_config.max_relative_difference);
      m_status_process_meas = spm_wait_set_range;
      //ostringstream_type msg;
      //msg << irst("Установка диапазона измерения: ") << range;
      DGI_MSG("Установка диапазона измерения: " << range);      
    } break;

    case spm_wait_set_range: {
      status_range_t status_range = get_status_range();
      if (status_range == range_stat_success) {   
        m_status_process_meas = spm_mode_setting;
        DGI_MSG("Установка диапазона измерения завершена.");
      }
    } break;

    case spm_mode_setting: {
      coord_cell_t coord_cur_cell =
        m_manager_traffic_cell.get_coord_cell();
      param_cur_cell_t param_cur_cell =
        mp_active_table->get_param_cell(
          coord_cur_cell.col, coord_cur_cell.row);
      out_param(param_cur_cell);
      if (m_config_calibr.temperature_ctrl_common_cfg.enabled &&
          m_cur_cell_cfg.temperature_control.enabled) {
        DGI_MSG("Ждем установления рабочего режима и температуры.");
      } else {
        DGI_MSG("Ждем установления рабочего режима.");
      }
      m_status_process_meas = spm_wait_mode_setting;
    } break;

    //установка режима
    case spm_wait_mode_setting: {
      #ifdef debug_datahanding
        m_on_reg_ready = true;
      #endif

      if (m_restart_timer.check()) {
        //Баг с зависанием измерения
        DGI_MSG("----БАГ---- Перезапускаем измерение");
        //Останавливаем измерение
        m_on_stop_process_auto_volt_meas = true;
        //И сразу запускаем с той же ячейки
        m_need_restart = true;
      }

      m_timer_delay_control.check();
      if ((m_timer_delay_control.stopped() == true)) {
        if (m_on_out_data == false) {
          bool all_ready = true;
          if (m_config_calibr.temperature_ctrl_common_cfg.enabled &&
              m_cur_cell_cfg.temperature_control.enabled) {
            all_ready = all_ready &&
              m_temperature_stability_control.stable_state();
            m_temperature_stable_min_time.start();
          }
          if (m_cur_cell_cfg.out_param_control_config.enabled) {
            all_ready = all_ready &&
              m_out_param_stability_control.stable_state();
            m_out_param_stable_min_time.start();
          }
          all_ready = all_ready && m_on_reg_ready;
          if (all_ready) {
            DGI_MSG("Рабочий режим установлен");
            m_restart_timer.stop();

            if (m_mode_program == mode_prog_single_channel) {
              m_delay_operating_duty = irs::make_cnt_s((int)m_cur_cell_cfg.delay_meas);
              m_timer_delay_operating_duty.set(m_delay_operating_duty);
              DGI_MSG("Ждем " << CNT_TO_DBLTIME(m_delay_operating_duty) << " секунд.");
              m_status_process_meas = spm_control_wait_mode_setting;
            } else {
              DGI_MSG("Ожидание внешнего запуска контрольного " <<
                "установления рабочего режима.");
              m_status_process_meas =
                spm_wait_ext_trig_control_wait_mode_setting;
            }
            m_cur_count_reset_over_bit = 0;
          }
        }
      }
    } break;

    // режим ожидания внешнего запуска режима контрольного ожидания
    case spm_wait_ext_trig_control_wait_mode_setting: {
      if (m_on_external) {
        m_on_external = false;
        m_delay_operating_duty = irs::make_cnt_s((int)m_cur_cell_cfg.delay_meas);
        m_timer_delay_operating_duty.set(m_delay_operating_duty);
        DGI_MSG("Ждем " << CNT_TO_DBLTIME(m_delay_operating_duty) <<
          " секунд.");
        m_status_process_meas = spm_control_wait_mode_setting;
      }
    } break;

    // режим контрольного ожидания установления рабочего режима
    case spm_control_wait_mode_setting: {
      m_timer_delay_operating_duty.check();
      if (m_config_calibr.temperature_ctrl_common_cfg.enabled &&
          m_cur_cell_cfg.temperature_control.enabled) {
        if (m_temperature_stability_control.get_stable_state_time() <
          m_temperature_stable_min_time.get()) {
          m_timer_delay_control.set(m_delay_start_control_reg);
          DGI_MSG("Температура вышла за допустимые значения.");
          DGI_MSG("Ждем " << CNT_TO_DBLTIME(m_delay_start_control_reg) <<
            " секунд перед проверкой рабочего режима.");
          m_status_process_meas = spm_wait_mode_setting;
        }
      }
      if (m_cur_cell_cfg.out_param_control_config.enabled) {
        if (m_out_param_stability_control.get_stable_state_time() <
          m_out_param_stable_min_time.get()) {
          DGI_MSG("Значение выходного параметра вышло за допустимые значения.");
          DGI_MSG("Ждем " << CNT_TO_DBLTIME(m_delay_start_control_reg) <<
            " секунд перед проверкой рабочего режима.");
          m_timer_delay_control.set(m_delay_start_control_reg);
          m_status_process_meas = spm_wait_mode_setting;
        }
      }
      if (m_status_process_meas == spm_control_wait_mode_setting) {
        if (m_on_reg_ready) {
          if (m_timer_delay_operating_duty.stopped()) {
            DGI_MSG("Рабочий режим подтвержден.");
            if (m_mode_program == mode_prog_single_channel) {
              m_status_process_meas = sps_start_meas;
            } else {
              m_status_process_meas = spm_wait_external_trig_meas;
              DGI_MSG("Ожидание внешнего запуска измерения.");
            }
          }
        } else {
          DGI_MSG("Рабочий режим не подтвержден.");
          DGI_MSG("Ждем " << CNT_TO_DBLTIME(m_delay_start_control_reg) <<
            " секунд перед проверкой рабочего режима.");
          m_timer_delay_control.set(m_delay_start_control_reg);
          m_restart_timer.start();
          m_status_process_meas = spm_wait_mode_setting;
        }
      }
    } break;
    // ожидание внешнего внешнего запуска измерения
    case spm_wait_external_trig_meas: {
      if (m_on_external) {
        m_status_process_meas = sps_start_meas;
        m_on_external = false;
      }
    } break;
    case sps_start_meas: {
      m_points.clear();
      m_impulse_filter.clear();
      m_meas_value_filter.clear();
      m_meas_value_filter_timer.set(irs::make_cnt_s(m_cur_cell_cfg.meas_interval));
      m_meas_value_filter_timer.start();
      m_meas_value_filter_elapsed_time.start();
      m_status_process_meas = spm_execute_meas;
    } break;
    case spm_execute_meas: {
      meas_status_t meas_stat = m_value_meas.get_status_meas();
      if(meas_stat == meas_status_success){
        meas_execute();
        m_status_process_meas = spm_wait_execute_meas;
      }
    } break;
    case spm_wait_execute_meas: {
        meas_status_t meas_stat = meas_status();
        if (meas_stat == meas_status_success) {
          if (m_mode_program == mode_prog_single_channel) {
            m_status_process_meas = spm_processing_data;
          } else {
            m_status_process_meas = spm_wait_external_trig_processing_data;
          }
        } else if (meas_stat == meas_status_error) {
          m_status_process_meas = spm_reset;
        }
    } break;
    case spm_wait_external_trig_processing_data: {
      if (m_on_external) {
        meas_status_t meas_stat = meas_status();
        if (meas_stat == meas_status_success) {
          m_status_process_meas = spm_processing_data;
        } else if (meas_stat == meas_status_error) {
          m_status_process_meas = spm_reset;
          DGI_MSG("Ошибка измерения.");
          DGI_MSG("Автоматическое измерение завершилось с ошибкой.");
        }
        m_on_external = false;
      }
    } break;
    case spm_processing_data: {
      //String cur_multim = get_selected_multimeter();
      if (!mp_mxmultimeter_assembly.is_empty()) {
        m_y_out_filter.stop();
        double y_out = 0;
        if (m_cur_cell_cfg.out_param_measuring_conf.filter_enabled) {
          y_out = m_y_out_filter.get_value();
        } else {
          y_out = m_y_out;
        }

        const double calc_value = calc_meas_value(
          m_value_meas_multimetr, y_out, m_param_cur_cell);
        m_meas_value_filter.add(calc_value);
        point_type point;
        point.x = m_meas_value_filter_elapsed_time.get();
        point.y = calc_value;
        m_points.push_back(point);
      }
      update_point_measurement_progress();
      //m_log << "Обновление значения.";
      //--------------------------------------
      update_result(false);
      if (!mp_meas_point_chart.is_empty()) {
        int col = mp_active_table->get_col_displ();
        int row = mp_active_table->get_row_displ();
        coord_cell_t coord_cur_cell =
          m_manager_traffic_cell.get_coord_cell();
        if ((col == coord_cur_cell.col) && (row == coord_cur_cell.row)) {
          update_chart(col, row);
        }
      }
      //-------------------------------------

      m_meas_value_filter_timer.check();
      if (m_meas_value_filter_timer.stopped()) {
        m_status_process_meas = spm_processing_filter_data;
      } else {
        m_status_process_meas = spm_execute_meas;
      }
    } break;
    case spm_processing_filter_data: {
      m_y_out_filter.stop();
      update_result(true);
      m_count_point_meas++;
      if (m_mode_program == mode_prog_single_channel) {
        m_status_process_meas = spm_jump_next_elem;
      } else {
        m_status_process_meas = spm_wait_ext_trig_process_data_to_next_elem;
      }
    } break;
    case spm_wait_ext_trig_process_data_to_next_elem: {
      if (m_on_external) {
        m_status_process_meas = spm_jump_next_elem;
        m_on_external = false;
      }
    } break;
    case spm_reset: {
      set_value_default_extra_params();
      set_value_default_extra_bits();
      m_value_meas.disconnect_multimeter();
      /*if (!ConnectAction->Checked) {
        reset_connect_calibr_device();
      } */
      m_param_cur_cell = m_default_param_cur_cell;
      m_cur_cell_cfg.clear();
      m_prev_cell_cfg.clear();
      m_on_out_data = true;
      m_auto_meas_is_running = false;
      m_on_process_auto_meas_active_cell = false;
      config_button_stop_avto_volt_meas();
      //m_status_process_meas = spm_off_process;
      TimeMeasLE->Text = String();
      IntervalTimeMeasLE->Text = String();
      CurrentOutParamLabeledEdit->Text = String();
      ReferenceOutParamLabeledEdit->Text = String();
      AbsoluteDiffOutParamLabeledEdit->Text = String();
      RemainingTimeForStableState->Text = String();
      m_exec_progress.hide();
      m_exec_progress.clear();
      m_timer_waiting_set_extra_vars.start();
      m_status_process_meas = spm_wait_set_extra_vars;
    } break;
    case spm_wait_set_extra_vars: {
      if (m_timer_waiting_set_extra_vars.check()) {
        if (!ConnectAction->Checked) {
          reset_connect_calibr_device();
        }
        m_status_process_meas = spm_off_process;
      }
    } break;
  }
  if (m_auto_meas_is_running) {
    double time_meas_sec = m_time_meas.get();
    irs::millisecond_t time_meas_ms =
      static_cast<irs::millisecond_t>(time_meas_sec*1000);
    const bool show_ms = false;
    string_type time_meas_str = irs::ms_to_strtime(time_meas_ms, show_ms);
    TimeMeasLE->Text = time_meas_str.c_str();
    if (m_count_point_meas > 0) {
      double time_interval_end_meas_sec = 0.0;
      if(m_previous_count_point_meas != m_count_point_meas) {
        int cur_cell_count_end = m_manager_traffic_cell.get_cell_count_end();
        cur_cell_count_end++;
        if (m_cell_count_end > cur_cell_count_end) {
          m_previous_time_meas_sec = time_meas_sec;
          // Запоминаем
          m_previous_count_point_meas = m_count_point_meas;
          // Скорость: ячеек в секунду
          m_cell_per_sec = m_count_point_meas/time_meas_sec;
          // Оставшееся количество ячеек до конца таблицы
          m_cell_count_end = cur_cell_count_end;
          // Оставшееся время до конца измерений
          time_interval_end_meas_sec = m_cell_count_end/m_cell_per_sec;
          update_measurement_progress();
          // Процент выполнения калибровки
          /*int percent = 100*m_count_point_meas/
            (m_cell_count_end+m_count_point_meas);
          m_exec_progress.p_percent_progress->Caption = IntToStr(percent) + "%";
          m_exec_progress.p_progress_bar->Position = percent;*/
        }
      } else {
        time_interval_end_meas_sec = m_cell_count_end/m_cell_per_sec -
          (time_meas_sec - m_previous_time_meas_sec);
      }
      const double m_epsilon = 1.e-5;
      if (irs::compare_value(time_interval_end_meas_sec, 0.0, m_epsilon) ==
        irs::less_than_value) {
        time_interval_end_meas_sec = 0.0;
      }
      irs::millisecond_t time_interval_end_meas_ms =
        static_cast<irs::millisecond_t>(time_interval_end_meas_sec*1000);
      string_type time_interval_end_meas_str =
        irs::ms_to_strtime(time_interval_end_meas_ms, show_ms);
      IntervalTimeMeasLE->Text = time_interval_end_meas_str.c_str();
    } else {
      IntervalTimeMeasLE->Text = "--:--:--";
    }
  }
}

void TDataHandlingF::update_point_measurement_progress()
{
  const double one_point_progress = 1./(m_cell_count_end + m_count_point_meas);

  // Процент выполнения калибровки
  double progress = m_count_point_meas*one_point_progress;

  // Прогресс измерения одной точки
  double point_percent = 1;
  const double period = CNT_TO_DBLTIME(m_meas_value_filter_timer.get());
  if (period != 0) {
    const double elapsed_time = m_meas_value_filter_elapsed_time.get();
    const double point_percent = irs::bound(elapsed_time/period, 0., 1.);
  }

  progress += point_percent*one_point_progress;

  const double percent = irs::bound(100*progress, 0., 100.);

  m_exec_progress.p_percent_progress->Caption =
    FloatToStrF(
      percent, ffFixed,
      progress_percent_precision,
      progress_percent_digits) +
    "%";
  //m_exec_progress.p_progress_bar->Position = percent;
  set_progress_bar_value(percent);
}

void TDataHandlingF::update_measurement_progress()
{
  const double one_point_progress = 1./(m_cell_count_end + m_count_point_meas);
  // Процент выполнения калибровки
  double percent = 100.*m_count_point_meas*one_point_progress;

  m_exec_progress.p_percent_progress->Caption =
    FloatToStrF(percent, ffFixed,
      progress_percent_precision,
      progress_percent_digits) +
    "%";
  set_progress_bar_value(percent);
}

void TDataHandlingF::set_progress_bar_mode_calibration()
{
  m_exec_progress.show();
  m_exec_progress.p_comment->Caption = irst("Процесс калибровки.");
  m_exec_progress.p_percent_progress->Caption = irst("0%");
  set_progress_bar_value(0);
}

void TDataHandlingF::set_progress_bar_mode_program()
{
  m_exec_progress.show();
  m_exec_progress.p_comment->Caption = "Процесс прошивки.";
  m_exec_progress.p_percent_progress->Caption = "0%";
  set_progress_bar_value(0);
}

void TDataHandlingF::set_progress_bar_mode_verification()
{
  m_exec_progress.show();
  m_exec_progress.p_comment->Caption = "Процесс верификации данных.";
  m_exec_progress.p_percent_progress->Caption = "0%";
  set_progress_bar_value(0);
}

void TDataHandlingF::set_progress_bar_value(double a_percent)
{
  m_exec_progress.p_progress_bar->Position = irs::bound(
    a_percent*1000, 0., 100000.);
}


//---------------------------------------------------------------------------
void TDataHandlingF::config_button_start_avto_volt_meas()
{
  // кнопка "Блокировка диапазона измеряемых ячеек"
  LockMeasCellsRangeAction->Enabled = false;
  //кнопка "Старт" автоизмерения напряжения
  StartAutoVoltMeasAction->Enabled = false;
  //кнопка начать/продолжить с активной ячейки
  StartAutoVoltMeasActiveCellsAction->Enabled = false;
  //кнопка "Стоп" автоизмерения напряжения
  StopVoltMeasAction->Enabled = true;
  ConfigCB->Enabled = false;
  PatternOfMeasuringInstrumentCB->Enabled = false;
  FileOpen->Enabled = false;
  FileReOpen->Enabled = false;
  WriteDataAction->Enabled = false;
  AddTableAction->Enabled = false;
  VerificationDataAction->Enabled = false;
  CreateColAction->Enabled = false;
  DeleteColAction->Enabled = false;
  CreateRowAction->Enabled = false;
  DeleteRowAction->Enabled = false;
  AddGroupCellsAction->Enabled = false;
  AddSubtableAction->Enabled = false;
  DelSubtableAction->Enabled = false;
  RestructDataType1Action->Enabled = false;
  ClearTableAction->Enabled = false;
  TableDefAction->Enabled = false;
  ClearContentTableAction->Enabled = false;
  ClearContentColTableAction->Enabled = false;
  ClearContentRowTableAction->Enabled = false;
  InversionSignConrentTableAction->Enabled = false;
  ExportTableToMExcelCsvFileAction->Enabled = false;


  CreateConfigButton->Enabled = false;
  EditConfigButton->Enabled = false;
  DeleteConfigButton->Enabled = false;
  ShowMultimeterOptionsButton->Enabled = false;

  ConnectAction->Enabled = false;

  ShowSameCellConfigsAction->Checked = false;
}



void TDataHandlingF::config_button_stop_avto_volt_meas()
{
  // кнопка "Блокировка диапазона измеряемых ячеек"
  LockMeasCellsRangeAction->Enabled = true;
  //кнопка "Старт" автоизмерения напряжения
  StartAutoVoltMeasAction->Enabled = true;
  //кнопка начать/продолжить с активной ячейки
  StartAutoVoltMeasActiveCellsAction->Enabled = true;
  //кнопка "Стоп" автоизмерения напряжения
  StopVoltMeasAction->Enabled = false;
  ConfigCB->Enabled = true;
  PatternOfMeasuringInstrumentCB->Enabled = true;
  FileOpen->Enabled = true;
  FileReOpen->Enabled = true;
  WriteDataAction->Enabled = true;
  AddTableAction->Enabled = true;
  VerificationDataAction->Enabled = true;
  CreateColAction->Enabled = true;
  DeleteColAction->Enabled = true;
  CreateRowAction->Enabled = true;
  DeleteRowAction->Enabled = true;
  AddGroupCellsAction->Enabled = true;
  AddSubtableAction->Enabled = true;
  DelSubtableAction->Enabled = true;
  RestructDataType1Action->Enabled = true;
  ClearTableAction->Enabled = true;
  TableDefAction->Enabled = true;
  ClearContentTableAction->Enabled = true;
  ClearContentColTableAction->Enabled = true;
  ClearContentRowTableAction->Enabled = true;
  InversionSignConrentTableAction->Enabled = true;
  ExportTableToMExcelCsvFileAction->Enabled = true;

  CreateConfigButton->Enabled = true;
  EditConfigButton->Enabled = true;
  DeleteConfigButton->Enabled = true;
  ShowMultimeterOptionsButton->Enabled = true;

  ConnectAction->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::RawDataStringGridSelectCell(
      TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
  if (m_cur_cell_table1.init) {
    string_type latest_entry_previous_cell_str =
      RawDataStringGrid->Cells
      [m_cur_cell_table1.col][m_cur_cell_table1.row].c_str();
    if (m_cur_cell_table1.value_str != latest_entry_previous_cell_str) {
      mp_active_table->cur_cell_in_display();
      RawDataStringGrid->Repaint();
    }
    m_cur_cell_table1.init = false;
  }
  processing_select_cell(RawDataStringGrid, ACol, ARow, CanSelect);

  reset_chart(ACol, ARow);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::RawDataStringGridKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  processing_key_return_and_ctrl_down(RawDataStringGrid, Key, Shift);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::FormCreate(TObject *Sender)
{
  //настройка компонента RawDataStringGrid
  RawDataStringGrid->Col = 1;
  RawDataStringGrid->Row = 1;
  on_select_cell(RawDataStringGrid->Col, RawDataStringGrid->Row, TShiftState());

  
  //настройка меню
  //меню файл
  
  FileOpen->Visible = true;
  FileOpen->Enabled = true;
  FileReOpen->Visible = true;
  FileReOpen->Enabled = true;
  FileSave->Visible = true;
  FileSave->Enabled = true;
  FileSaveAs->Visible = true;
  FileSaveAs->Enabled = true;

  //меню Правка
  CreateColAction->Visible = true;
  CreateColAction->Enabled = true;
  DeleteColAction->Visible = true;
  DeleteColAction->Enabled = true;
  CreateRowAction->Visible = true;
  CreateRowAction->Enabled = true;
  DeleteRowAction->Visible = true;
  DeleteRowAction->Enabled = true;
  AddGroupCellsAction->Visible = true;
  AddGroupCellsAction->Enabled = true;

  //меню Автоизмерение
  //кнопка "Старт" автоизмерения напряжения
  StartAutoVoltMeasAction->Visible = true;
  StartAutoVoltMeasAction->Enabled = true;
  //кнопка "Стоп" автоизмерения напряжения
  StopVoltMeasAction->Visible = true;
  StopVoltMeasAction->Enabled = false;
  //кнопка начать/продолжить с активной ячейки
  StartAutoVoltMeasActiveCellsAction->Visible = true;
  StartAutoVoltMeasActiveCellsAction->Enabled = true;
}

//---------------------------------------------------------------------------
void TDataHandlingF::tick2()
{
  if (CopyTableForm)
    m_status_copy_table = CopyTableForm->read_status_copy_data();

  m_value_meas.tick();
  if(m_add_col_or_row_successfuly == true){
    int col_max = mp_active_table->col_count()-1;
    int row_max = mp_active_table->row_count()-1;
    m_add_col_or_row_successfuly = false;
    if(m_select_col > 0 && m_select_col <= col_max &&
      m_select_row > 0 && m_select_row <= row_max){
      if(m_successfully_add_col == true){
        if(m_start_num_col > 0 && m_end_num_col > 0 && m_step_num_col > 0){
          mp_active_table->set_col_displ(m_select_col);
          mp_active_table->set_row_displ(m_select_row);
          mp_active_table->create_group_col_table(
            m_start_num_col,
            m_end_num_col,
            m_step_num_col,
            m_type_step_col);
        }
      }
      if(m_successfully_add_row == true){
        if(m_start_num_row > 0 && m_end_num_row > 0 && m_step_num_row > 0){
          mp_active_table->set_col_displ(m_select_col);
          mp_active_table->set_row_displ(m_select_row);
          mp_active_table->create_group_row_table(
            m_start_num_row,
            m_end_num_row,
            m_step_num_row,
            m_type_step_row);
        }
      }
    }
    m_select_col = 0;
    m_select_row = 0;
    m_start_num_col = 0;
    m_end_num_col = 0;
    m_step_num_col = 0;
    m_type_step_col = INCREMENT_STEP;
    m_start_num_row = 0;
    m_end_num_row = 0;
    m_step_num_row = 0;
    m_type_step_row = INCREMENT_STEP;
    m_successfully_add_col = false;
    m_successfully_add_row = false;
  }
  process_volt_meas();
}

void TDataHandlingF::set_setting_for_type_jump_next_cell(
  const String& a_str_type_jump_next_elem)
{
  m_type_jump_next_elem =
    str_to_type_jump_next_elem(a_str_type_jump_next_elem.c_str());
  switch(m_type_jump_next_elem){
    case HORIZONTAL_DOWN:{
      SetJumpHorizontalDownAction->Checked = true;
      SetJumpSmoothAction->Checked = false;
      m_on_jump_smooth = false;
    } break;
    case HORIZONTAL_DOWN_SMOOTH:{
      SetJumpHorizontalDownAction->Checked = true;
      SetJumpSmoothAction->Checked = true;
      m_on_jump_smooth = true;
    } break;
    case HORIZONTAL_UP:{
      SetJumpHorizontalUpAction->Checked = true;
      SetJumpSmoothAction->Checked = false;
      m_on_jump_smooth = false;
    } break;
    case HORIZONTAL_UP_SMOOTH:{
      SetJumpHorizontalUpAction->Checked = true;
      SetJumpSmoothAction->Checked = true;
      m_on_jump_smooth = true;
    } break;
    case VERTICAL_FORWARD:{
      SetJumpVerticalForwardAction->Checked = true;
      SetJumpSmoothAction->Checked = false;
      m_on_jump_smooth = false;
    } break;
    case VERTICAL_FORWARD_SMOOTH:{
      SetJumpVerticalForwardAction->Checked = true;
      SetJumpSmoothAction->Checked = true;
      m_on_jump_smooth = true;
    } break;
    case VERTICAL_BACK:{
      SetJumpVerticalBackAction->Checked = true;
      SetJumpSmoothAction->Checked = false;
      m_on_jump_smooth = false;
    } break;
    case VERTICAL_BACK_SMOOTH:{
      SetJumpVerticalBackAction->Checked = true;
      SetJumpSmoothAction->Checked = true;
      m_on_jump_smooth = true;
    } break;
    default:{
      SetJumpHorizontalDownAction->Checked = true;
      SetJumpSmoothAction->Checked = false;
      m_on_jump_smooth = false;
    } break;
  }
  m_manager_traffic_cell.set_type_traffic(m_type_jump_next_elem);
}

double TDataHandlingF::calc_meas_value(
  const double a_value_meas,
  const double out_param_value,
  const param_cur_cell_t& a_param_cell)
{
  double shunt_coef = get_cell_config(a_param_cell).output_param_coef;
  double out_value = a_value_meas*shunt_coef;
  if (m_cur_cell_cfg.out_param_measuring_conf.consider_out_param) {
    if (out_param_value != 0) {
      out_value = out_value/out_param_value;
    } else {
      DGI_MSG("Ошибка. " <<
        "Выходное значение с устройства равно нулю и не учитывается");
    }
    if (m_inf_in_param.type_anchor == PARAMETR1) {
      if (a_param_cell.col_value.init) {
        out_value = m_param_cur_cell.col_value.value*out_value;
      }
    } else if(m_inf_in_param.type_anchor == PARAMETR2) {
      if (a_param_cell.row_value.init) {
        out_value = m_param_cur_cell.row_value.value*out_value;
      }
    } else if(m_inf_in_param.type_anchor == PARAMETR3) {
      if (a_param_cell.top_value.init) {
        out_value = m_param_cur_cell.top_value.value*out_value;
      }
    }
  }
  return out_value;
}

void TDataHandlingF::update_result(bool a_last_call)
{
  cell_t cell = process_measured_points(a_last_call);
  coord_cell_t coord_cur_cell =
    m_manager_traffic_cell.get_coord_cell();
  mp_active_table->set_cell(cell, coord_cur_cell.col, coord_cur_cell.row);
  mp_active_table->cell_out_display(
    coord_cur_cell.col, coord_cur_cell.row);

  if (m_is_autosave_meas_enabled) {
    String file_namedir = mp_active_table->get_file_namedir();
    if (!file_namedir.IsEmpty()) {
      mp_active_table->save_table_to_file(file_namedir.c_str());
    } else {
      DGI_MSG("Не удалось сохранить данные, так как имя файла не задано.");
    }
  }
}

cell_t TDataHandlingF::process_measured_points(bool a_last_call)
{
  vector<double> values;
  for (size_type i = 0; i < m_points.size(); i++) {
    values.push_back(m_points[i].y);
  }

  cell_t cell(0, true);
  cell.points = m_points;
  cell.sko = 0;
  if (values.size() > 0) {
    cell.value = values.front();
  }
  if (values.size() > 1) {
    double sko_before = 0;
    double average_before = 0;
    irs::sample_standard_deviation(values.begin(), values.end(),
      &sko_before, &average_before);

    cell.sko = sko_before;
    cell.min = *std::min_element(values.begin(), values.end());
    cell.max = *std::max_element(values.begin(), values.end());
    //cell.delta = std::fabs(value_max - value_min)/average_before;


    /*const double student_t_95 = irs::student_t_inverse_distribution_2x(
      confidence_level_0_95, values.size());

    const double student_t_99 = irs::student_t_inverse_distribution_2x(
      confidence_level_0_99, values.size());
    double confidence_interval_95 = sko_before*student_t_95;
    double confidence_interval_99 = sko_before*student_t_99;
    cell.confidence_interval_95 = confidence_interval_95;
    cell.confidence_interval_99 = confidence_interval_99;
      */
    const irs::level_of_significance_t level_of_significance =
      irs::level_of_significance_0_1;
    vector<double>::iterator it =
      eliminating_outliers_smirnov_criterion_multiple_pass(values.begin(),
      values.end(), level_of_significance);


    //m_log << (String(irst("Удалено выбросов: ")) +
      //IntToStr(distance(it, values.end())));
    values.erase(it, values.end());

    if (values.size() > 0) {
      double sko = 0;
      double average = 0;
      irs::sample_standard_deviation(values.begin(), values.end(),
        &sko, &average);
      int p = 0;
      int n = 0;
      double d_total = 0;
      for (size_type i = 0; i < values.size(); i++) {
        if (values[i] > average) {
          p++;
          d_total += fabs(values[i] - average);
        } else if (values[i] < average) {
          n++;
        }
      }
      // Уточненное среднее
      const double N_2 = values.size()*values.size();
      double result = average + ((p - n)*d_total)/N_2;

      if (a_last_call && m_measure_method == mm_impulse_filter) {
        //Если включен импульсный фильтр, то его нужно применить только в
        //последний вызов функции update_result
        if (values.size() < 3) {
          DGI_MSG("Ошибка: слишком мало измерений для импульсного фильтра, "
            "результат рассчитан по алгоритму среднего значения");
        } else {
          m_impulse_filter.assign(values);
          double average = result;
          result = m_impulse_filter.get();

          DGI_MSG("Значение (среднее): " << average);
          DGI_MSG("Значение (импульсный фильтр): " << result);
          DGI_MSG("Разница: " << (average - result) / average * 100);
        }
      }
      cell.value = result;
    }
  }
  return cell;
    //double calc_value = m_meas_value_filter.get();
}

void TDataHandlingF::reset_chart(
  const int a_col_displ, const int a_row_displ)
{
  // Обработка графика
  if (!mp_meas_point_chart.is_empty()) {
    mp_meas_point_chart->clear_param();
    param_cur_cell_t param = mp_active_table->get_param_cell(a_col_displ,
      a_row_displ);
    const string_type name =
      irs::num_to_str(param.col_value.value) +
      irst("; ") +
      irs::num_to_str(param.row_value.value);
    const string_type points_chart = name + irst(" точки");
    const string_type result_chart = name + irst(" значение");
    mp_meas_point_chart->add_param(points_chart);
    mp_meas_point_chart->add_param(result_chart);
    mp_meas_point_chart->group_all();
    update_chart(a_col_displ, a_row_displ);
  }
}

void TDataHandlingF::update_chart(const int a_col_displ, const int a_row_displ)
{
  // Обработка графика
  if (!mp_meas_point_chart.is_empty()) {
    //mp_meas_point_chart->clear_param();
    param_cur_cell_t param = mp_active_table->get_param_cell(a_col_displ,
      a_row_displ);
    const string_type name =
      irs::num_to_str(param.col_value.value) +
      irst("; ") +
      irs::num_to_str(param.row_value.value);

    const string_type points_chart = name + irst(" точки");
    //mp_meas_point_chart->add_param(points_chart);
    const cell_t cell = mp_active_table->get_cell_table(a_col_displ,
      a_row_displ);

    vector<double> x_array;
    vector<double> y_array;


    for (size_type i = 0; i < cell.points.size(); i++) {
      const cell_t::point_type point = cell.points[i];
      x_array.push_back(point.x);
      y_array.push_back(point.y);
    }
    mp_meas_point_chart->set(points_chart, x_array, y_array);



    const string_type result_chart = name + irst(" значение");
    //mp_meas_point_chart->add_param(result_chart);
    x_array.clear();
    y_array.clear();
    if (!cell.points.empty()) {
      x_array.push_back(cell.points.front().x);
      x_array.push_back(cell.points.back().x);
      y_array.push_back(cell.value);
      y_array.push_back(cell.value);
    }
    mp_meas_point_chart->set(result_chart, x_array, y_array);
    /*if (!x_array.empty()) {
      mp_meas_point_chart->add(result_chart, x_array.front(), cell.value);
      mp_meas_point_chart->add(result_chart, x_array.back(), cell.value);
    } */
    //mp_meas_point_chart->group_all();
  }
}

double TDataHandlingF::set_range(const param_cur_cell_t& a_param_cur_cell)
{
  const cell_config_calibr_t cell_config = get_cell_config(a_param_cur_cell);

  double range = 0;
  if (cell_config.range_enabled) {
    range = cell_config.range;
  } else {
    double coef =  get_cell_config(a_param_cur_cell).output_param_coef;
    if (coef == 0) {
      throw logic_error("Коэффициент выходного значения не должен быть равен нулю.");
    }
    range = get_anchor_in_param(a_param_cur_cell)/coef;
  }
  
  m_value_meas.set_range(m_type_meas, range);
  /*if (m_inf_in_param.type_anchor == PARAMETR1) {
    range = a_param_cur_cell.col_value.value*koef;
    m_value_meas.set_range(m_type_meas, range);
  } else if (m_inf_in_param.type_anchor == PARAMETR2) {
    range = a_param_cur_cell.row_value.value*koef;
    m_value_meas.set_range(m_type_meas, range);
  } else {
    range = a_param_cur_cell.top_value.value*koef;
    m_value_meas.set_range(m_type_meas, range);
  }*/
  return range;
}

double TDataHandlingF::get_anchor_in_param(
  const param_cur_cell_t& a_param_cur_cell)
{
  double value = 0;
  if (m_inf_in_param.type_anchor == PARAMETR1) {
    value = a_param_cur_cell.col_value.value;
  } else if (m_inf_in_param.type_anchor == PARAMETR2) {
    value = a_param_cur_cell.row_value.value;
  } else {
    value = a_param_cur_cell.top_value.value;
  }
  return value;
}

TDataHandlingF::status_range_t TDataHandlingF::get_status_range()
{
  status_range_t status_range = range_stat_success;
  return status_range;
}
void TDataHandlingF::set_ref_channel()
{
  StartAutoVoltMeasAction->Enabled = true;
  StartAutoVoltMeasActiveCellsAction->Enabled = true;
  StopVoltMeasAction->Enabled = false;
}
void TDataHandlingF::unset_ref_channel()
{
  StartAutoVoltMeasAction->Enabled = false;
  StartAutoVoltMeasActiveCellsAction->Enabled = false;
  StopVoltMeasAction->Enabled = false;
}
bool TDataHandlingF::get_on_close_form_stat()
{
  bool on_close_form_stat = m_on_close_form_stat;
  m_on_close_form_stat = false;
  return on_close_form_stat;
}
//---------------------------------------------------------------------------
/*void TDataHandlingF::set_type_meas(type_meas_t a_type_meas)
{
  m_type_meas = a_type_meas;
  switch(m_type_meas){
    case tm_volt_dc:{
      if(!VoltDCMeasM->Checked)
        VoltDCMeasM->Checked = true;
    } break;
    case tm_volt_ac:{
      if(!VoltACMeasM->Checked)
        VoltACMeasM->Checked = true;
    } break;
    case tm_current_dc:{
      if(!CurrentDCMeasM->Checked)
        CurrentDCMeasM->Checked = true;
    } break;
    case tm_current_ac:{
      if(!CurrentACMeasM->Checked)
        CurrentACMeasM->Checked = true;
    } break;
    case tm_resistance_2x:{
      if(!Resistance2xMeasM->Checked)
        Resistance2xMeasM->Checked = true;
    } break;
    case tm_resistance_4x:{
      if(!Resistance4xMeasM->Checked)
        Resistance4xMeasM->Checked = true;
    } break;
    case tm_frequency:{
      if(!FrequencyMeasM->Checked)
        FrequencyMeasM->Checked = true;
    } break;
    case tm_phase:{
      if(!PhaseMeasM->Checked)
        PhaseMeasM->Checked = true;
    } break;
    case tm_phase_average:{
      if(!PhaseAverageMeasM->Checked)
        PhaseAverageMeasM->Checked = true;
    } break;
    case tm_time_interval:{
      if(!TimeIntervalMeasM->Checked)
        TimeIntervalMeasM->Checked = true;
    } break;
    case tm_time_interval_average:{
      if(!TimeIntervalAverageMeasM->Checked)
        TimeIntervalAverageMeasM->Checked = true;
    } break;
  }
}     */
//---------------------------------------------------------------------------
void TDataHandlingF::special_style_cells(TStringGrid* a_table,
  int a_col,
  int a_row,
  TRect &a_rect)
{
  TStringGrid* table = a_table;
  coord3d_t coord_cell =
    mp_active_table->get_coord_cell_table(a_col, a_row);
  int col_table = coord_cell.x;
  int row_table = coord_cell.y;  
  bool select_cell_in_x = (col_table > 0) && (row_table == 0);
  bool select_cell_in_y = (col_table == 0) && (row_table > 0);
  bool select_cell_in_z = (col_table == 0) && (row_table == 0);
  String value = mp_active_table->get_cell_display_variable_precision(
    a_col, a_row).c_str();

  if (select_cell_in_x || select_cell_in_y || select_cell_in_z) {
    //цвет фона
    table->Canvas->Brush->Color = clBtnFace;
    //цвет текста
    table->Canvas->Font->Color = clBlack;
    //заливаем фон
    table->Canvas->FillRect(a_rect);
    //красим текст
    table->Canvas->TextOutW(a_rect.Left, a_rect.Top, value);
  } else {

    bool is_same_config = false;
    const irs::table_t<cell_config_calibr_t>& cells_config = mp_active_table->get_cells_config();
    if (ShowSameCellConfigsAction->Checked &&
      irs::is_in_range<int>(m_start_col + 1, 0, cells_config.get_col_count()) &&
      irs::is_in_range<int>(m_start_row + 1, 0, cells_config.get_row_count()) &&
      irs::is_in_range<int>(col_table, 0, cells_config.get_col_count()) &&
      irs::is_in_range<int>(row_table, 0, cells_config.get_row_count())) {

      is_same_config = cells_config.read_cell(m_start_col, m_start_row) ==
        cells_config.read_cell(col_table, row_table);
    }

    if (is_same_config ) {
      //цвет фона
      table->Canvas->Brush->Color = clLime;
      //цвет текста
      table->Canvas->Font->Color = clBlack;
      //заливаем фон
      table->Canvas->FillRect(a_rect);
      //красим текст
      table->Canvas->TextOutW(a_rect.Left, a_rect.Top, value);
    } else if (a_col >= m_cells_range.Left && a_col <= m_cells_range.Right &&
      a_row >= m_cells_range.Top && a_row <= m_cells_range.Bottom) {

      //цвет фона
      table->Canvas->Brush->Color = clMoneyGreen;
      //цвет текста
      table->Canvas->Font->Color = clBlack;
      //заливаем фон
      table->Canvas->FillRect(a_rect);
      //красим текст
      table->Canvas->TextOutW(a_rect.Left, a_rect.Top, value);
    } else if(is_meas_cells_range_locked() &&
      a_col >= m_meas_cells_range.Left &&
      a_col <= m_meas_cells_range.Right &&
      a_row >= m_meas_cells_range.Top &&
      a_row <= m_meas_cells_range.Bottom) {

      //цвет фона
      table->Canvas->Brush->Color = clYellow;
      //цвет текста
      table->Canvas->Font->Color = clBlack;
      //заливаем фон
      table->Canvas->FillRect(a_rect);
      //красим текст
      table->Canvas->TextOutW(a_rect.Left, a_rect.Top, value);
    } else {
      table->Canvas->FillRect(a_rect);
      table->Canvas->TextOutW(a_rect.Left, a_rect.Top, value);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::FormDataHandingTimerTimer(TObject *Sender)
{
  try{
    tick();
    tick2();
  } catch (Exception &exception) {
    FormDataHandingTimer->Enabled = false;
    Application->ShowException(&exception);
    m_on_stop_process_auto_volt_meas = true;
    FormDataHandingTimer->Enabled = true;
    //exit(1);
  } catch (...) {
    FormDataHandingTimer->Enabled = false;
    try {
      throw Exception("");
    } catch (Exception &exception) {
      Application->ShowException(&exception);
    }
    exit(1);
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::ClearTableButtonClick(TObject *Sender)
{
  mp_active_table->clear_table();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::RawDataStringGridDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
  special_style_cells(RawDataStringGrid, ACol, ARow, Rect);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::AddGroupCellsButtonClick(TObject *Sender)
{

  if(AddCorRowF->Visible == false){
    TStringGrid* p_cur_table = mp_active_table->pointer_table();
    m_select_col = p_cur_table->Col;
    m_select_row = p_cur_table->Row;
    AddCorRowF->dialog_user_add_col_row(
      &m_select_col,
      &m_select_row,
      &m_successfully_add_col,
      &m_successfully_add_row,
      &m_start_num_col,
      &m_end_num_col,
      &m_step_num_col,
      &m_type_step_col,
      &m_start_num_row,
      &m_end_num_row,
      &m_step_num_row,
      &m_type_step_row);
    AddCorRowF->add_col_row_successfully_stat(&m_add_col_or_row_successfuly);
    AddCorRowF->ShowModal();
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::CreateColActionExecute(TObject *Sender)
{
  mp_active_table->create_col_table();
  //Update
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::DeleteColActionExecute(TObject *Sender)
{
  mp_active_table->delete_col_table();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::CreateRowActionExecute(TObject *Sender)
{
  mp_active_table->create_row_table();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::DeleteRowActionExecute(TObject *Sender)
{
  mp_active_table->delete_row_table();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::AddGroupCellsActionExecute(TObject *Sender)
{
  if(AddCorRowF->Visible == false){
    m_select_col = mp_active_table->get_col_displ();
    m_select_row = mp_active_table->get_row_displ();
    AddCorRowF->dialog_user_add_col_row(
      &m_select_col,
      &m_select_row,
      &m_successfully_add_col,
      &m_successfully_add_row,
      &m_start_num_col,
      &m_end_num_col,
      &m_step_num_col,
      &m_type_step_col,
      &m_start_num_row,
      &m_end_num_row,
      &m_step_num_row,
      &m_type_step_row);
    AddCorRowF->add_col_row_successfully_stat(&m_add_col_or_row_successfuly);
    AddCorRowF->ShowModal();
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::StartAutoVoltMeasActionExecute(
      TObject *Sender)
{
  if (!data_should_be_saved_dialog()) {
    return;
  }

  if (lock_meas_cells_range_if_need()) {
    m_on_start_new_auto_meas = true;
  } else {
    MessageDlg(irst("Не выделен диапазон измеряемых ячеек"),
      mtInformation, TMsgDlgButtons() << mbOK, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::StopVoltMeasActionExecute(TObject *Sender)
{
  m_on_stop_process_auto_volt_meas = true;
}
//---------------------------------------------------------------------------



void __fastcall TDataHandlingF::StartAutoVoltMeasActiveCellsActionExecute(
      TObject *Sender)
{
  // Запоминаем выбранную ячейку, так как в начале измерения таблица с данными будет
  // перезагружена и будет выделена стартовая ячейка (1, 1)
  m_start_cell.col = mp_active_table->get_col_displ();
  m_start_cell.row = mp_active_table->get_row_displ();

  if (!data_should_be_saved_dialog()) {
    return;
  }

  if (lock_meas_cells_range_if_need()) {
    m_on_process_auto_meas_active_cell = true;
  } else {
    MessageDlg(irst("Не выделен диапазон измеряемых ячеек"),
      mtInformation, TMsgDlgButtons() << mbOK, 0);
  }
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::FileSaveExecute(TObject *Sender)
{
  String file_namedir;
  file_namedir = mp_active_table->get_file_namedir();
  if (!file_namedir.IsEmpty()) {

    save_cells_config_if_need();

    mp_active_table->save_table_to_file(file_namedir.c_str());
    mp_active_table->save_table_to_m_file(file_namedir.c_str());
    //mp_active_table->save_table_to_json_file(file_namedir.c_str());
  } else {
    FileSaveAs->Execute();
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileSaveAsAccept(TObject *Sender)
{
  String file_namedir = FileSaveAs->Dialog->FileName;
  //mp_active_table->set_file_namedir(file_namedir);
  mp_active_table->save_table_to_file(file_namedir.c_str());
  m_config_calibr.active_filename =
    m_file_name_service.make_relative_file_name(file_namedir);

  irs::table_t<cell_config_calibr_t> saved_cells_config = m_config_calibr.cells_config;
  if (!mp_active_table->is_cells_config_read_only()) {
    m_config_calibr.cells_config = mp_active_table->get_cells_config();
  }
  // Сохраняем изменения конфигурации (изменен активный документ)
  if (m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str())) {
    DGI_MSG("Текущая конфигурация успешно сохранена.");
  } else {
    if (!mp_active_table->is_cells_config_read_only()) {
      m_config_calibr.cells_config = saved_cells_config;
    }
    DGI_MSG("Не удалось сохранить изменения в конфигурации.");
  }
  Caption = m_prog_name + String(irst(" - ")) + file_namedir;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileSaveAsBeforeExecute(TObject *Sender)
{   
  String file_namedir;
  file_namedir = mp_active_table->get_file_namedir();
  if(file_namedir.IsEmpty()){
    FileSaveAs->Dialog->FileName = irst("Data.dgi");
  }
  else{
    FileSaveAs->Dialog->FileName = file_namedir;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileReOpenExecute(TObject *Sender)
{
  if (!save_unsaved_changes_dialogs()) {
    return;
  }
  String filename;
  filename = mp_active_table->get_file_namedir();
  if(!filename.IsEmpty()) {
    mp_active_table->load_table_from_file(filename.c_str(),
      m_inf_in_param, m_config_calibr.cells_config);
  } else {
    FileOpen->Execute();
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileOpenAccept(TObject *Sender)
{
  if (!save_unsaved_changes_dialogs()) {
    return;
  }
  String file_namedir = FileOpen->Dialog->FileName;
  //mp_active_table->set_file_namedir(file_namedir);
  if (mp_active_table->load_table_from_file(file_namedir.c_str(),
    m_inf_in_param, m_config_calibr.cells_config)) {

    m_config_calibr.active_filename =
      m_file_name_service.make_relative_file_name(file_namedir);
  } else {
    m_config_calibr.active_filename = irst("");
    file_namedir = irst("");
  }

  // Сохраняем изменения конфигурации (изменен активный документ)
  m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str());
  Caption = m_prog_name + String(irst(" - "))+file_namedir;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetJumpHorizontalDownActionExecute(
      TObject *Sender)
{
  if(!(SetJumpHorizontalDownM->Checked)){
    SetJumpHorizontalDownM->Checked = true;
    if(m_on_jump_smooth)
      set_type_jump(HORIZONTAL_DOWN_SMOOTH);
    else
      set_type_jump(HORIZONTAL_DOWN);
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetJumpHorizontalUpActionExecute(
      TObject *Sender)
{
  if(!(SetJumpHorizontalUpM->Checked)){
    SetJumpHorizontalUpM->Checked = true;
    if(m_on_jump_smooth)
      set_type_jump(HORIZONTAL_UP_SMOOTH);
    else
      set_type_jump(HORIZONTAL_UP);
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetJumpVerticalForwardActionExecute(
      TObject *Sender)
{
  if(!(SetJumpVerticalForwardM->Checked)){
    SetJumpVerticalForwardM->Checked = true;
    if(m_on_jump_smooth)
      set_type_jump(VERTICAL_FORWARD_SMOOTH);
    else
      set_type_jump(VERTICAL_FORWARD);
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetJumpVerticalBackActionExecute(
      TObject *Sender)
{
  if(!(SetJumpVerticalBackM->Checked)){
    SetJumpVerticalBackM->Checked = true;
    if(m_on_jump_smooth)
      set_type_jump(VERTICAL_BACK_SMOOTH);
    else
      set_type_jump(VERTICAL_BACK);
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetJumpSmoothActionExecute(TObject *Sender)
{
  if(SetJumpSmoothM->Checked == true){
    SetJumpSmoothM->Checked = false;
    m_on_jump_smooth = false;
    reset_jump_smooth();
  }else{
    SetJumpSmoothM->Checked = true;
    m_on_jump_smooth = true;
    set_jump_smooth();
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::SetVoltDCMeasActionExecute(TObject *Sender)
{
  //set_type_meas(tm_volt_dc);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetVoltACMeasActionExecute(TObject *Sender)
{
  //set_type_meas(tm_volt_ac);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetCurrentDCMeasActionExecute(
      TObject *Sender)
{
  //set_type_meas(tm_current_dc);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetResistance2xMeasActionExecute(TObject *Sender)
{
  //set_type_meas(tm_current_ac);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::SetResistance4xMeasActionExecute(
      TObject *Sender)
{
  //set_type_meas(tm_resistance_2x);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::SetCurrentACMeasActionExecute(
      TObject *Sender)
{
  //set_type_meas(tm_resistance_4x);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::SetFrequencyMeasActionExecute(
      TObject *Sender)
{
  //set_type_meas(tm_frequency);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::Button4Click(TObject *Sender)
{
  add_graph_z_of_y();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::Button6Click(TObject *Sender)
{
  m_chart.add_all_chart_z_of_x(mp_active_table, m_inf_in_param);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::Button7Click(TObject *Sender)
{
  m_chart.add_all_chart_z_of_y(mp_active_table, m_inf_in_param);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::Button5Click(TObject *Sender)
{
  m_chart.clear_chart();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::ZX1Click(TObject *Sender)
{
  m_chart.add_chart_z_of_x_cur_cell(mp_active_table, m_inf_in_param);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::ZY1Click(TObject *Sender)
{
  m_chart.add_chart_z_of_y_cur_cell(mp_active_table, m_inf_in_param);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::ZX2Click(TObject *Sender)
{
  m_chart.add_all_chart_z_of_x(mp_active_table, m_inf_in_param);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::ZY2Click(TObject *Sender)
{
  m_chart.add_all_chart_z_of_y(mp_active_table, m_inf_in_param);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::N3Click(TObject *Sender)
{
  clear_all_graph();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::AddSubtableActionExecute(TObject *Sender)
{
  mp_active_table->create_subtable();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::DelSubtableActionExecute(TObject *Sender)
{
  mp_active_table->delete_subtable();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::RawDataStringGridGetEditText(
      TObject *Sender, int ACol, int ARow, UnicodeString &Value)
{
  m_cur_cell_table1.col = ACol;
  m_cur_cell_table1.row = ARow;
  if (!m_cur_cell_table1.init) {
    m_cur_cell_table1.init = true;
    m_cur_cell_table1.value_str =
      mp_active_table->get_cell_value_str_table_data(
      m_cur_cell_table1.col, m_cur_cell_table1.row);
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::CreateConfigButtonClick(TObject *Sender)
{
  if (!save_unsaved_changes_dialogs()) {
    return;
  }

  //if (!save_cells_config_if_need())
   // return;
  /*if (!m_cur_filename_conf_calibr_device.IsEmpty()) {
    if (m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str())) {
      DGI_MSG("Текущая конфигурация успешно сохранена.");
    }
  }*/

  irs::handle_t<TNewConfigF> config_form(new TNewConfigF(NULL, this));
  //config_form->set_path_program(m_path_prog);
  config_form->set_config_def();
  //load_config_calibr_to_display();
  if (config_form->Visible == false) {
    int button_result = config_form->ShowModal();
    if (button_result == mrOk) {
      m_on_block_reconfiguration = true;
      //перезагружаем список доступных конфигураций
      String dir_config = m_file_name_service.get_config_dir();
      if (DirectoryExists(dir_config)) {
        load_config_calibr_to_display();
        m_on_block_reconfiguration = false;
        String name_new_config = config_form->get_name_new_conf();
        int index_pos_text = irs::cbuilder::combo_box_find_item(
          ConfigCB, name_new_config);
        if (index_pos_text == irs::cbuilder::npos) {
          if (ConfigCB->Items->Count > 0) {
            ConfigCB->ItemIndex = 0;
          }
        } else {
          ConfigCB->ItemIndex = index_pos_text;
        }
      }
      load_config_calibr();
      bool forsed_connect = true;
      // устанавливаем принудительно реконнект
      set_connect_if_enabled(forsed_connect);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::EditConfigButtonClick(TObject *Sender)
{
  if (mp_active_table->is_cells_config_read_only()) {
    MessageDlg(irst("Редактирование невозможно, так как файл данных был открыт ")
      irst("c опцией \"Открыть без возможности редактирования конфигурации\""),
      mtInformation, TMsgDlgButtons() << mbOK, 0);
    return;
  }

  if (!save_unsaved_changes_dialogs()) {
    return;
  }

  //if (!save_cells_config_if_need())
    //return;
  /*if (!m_cur_filename_conf_calibr_device.IsEmpty()) {
    irs::table_t<cell_config_calibr_t> saved_cells_config = m_config_calibr.cells_config;
    if (!mp_active_table->is_cells_config_read_only()) {
      m_config_calibr.cells_config = mp_active_table->get_cells_config();
    }
    if (m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str())) {
      DGI_MSG("Текущая конфигурация успешно сохранена.");
    } else {
      if (!mp_active_table->is_cells_config_read_only()) {
        m_config_calibr.cells_config = saved_cells_config;
      }
      DGI_MSG("Не удалось сохранить изменения в конфигурации.");
    }
  }*/

  irs::handle_t<TNewConfigF> config_form(new TNewConfigF(NULL, this));
  //config_form->set_path_program(m_path_prog);
  if(config_form->Visible == false) {
    int index = ConfigCB->ItemIndex;
    if (index >= 0) {
      config_form->edit_config(mv_list_config_calibr[index]);
      int button_result = config_form->ShowModal();
      if (button_result == mrOk) {
        m_on_block_reconfiguration = true;
        //перезагружаем список доступных конфигураций
        String dir_config = m_file_name_service.get_config_dir();
        if (DirectoryExists(dir_config)) {
          load_config_calibr_to_display();
          m_on_block_reconfiguration = false;
          String name_new_config = config_form->get_name_new_conf();
          int index_pos_text = irs::cbuilder::combo_box_find_item(
            ConfigCB, name_new_config);
          if (index_pos_text == irs::cbuilder::npos) {
            if (ConfigCB->Items->Count > 0) {
              ConfigCB->ItemIndex = 0;
            }
          } else {
            ConfigCB->ItemIndex = index_pos_text;
          }
        }
        load_config_calibr();
        const bool forsed_connect = true;
        // устанавливаем принудительно реконнект
        set_connect_if_enabled(forsed_connect);
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::CorrectModeActionExecute(TObject *Sender)
{
  correct_mode_change_stat();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::MismatchModeActionExecute(TObject *Sender)
{
  mismatch_mode_change_stat();
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::CloseFormButtonClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  m_main_opt_ini_file.save();
  m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str());
  //save_cur_config_device();

  if (m_mode_program == mode_prog_single_channel) {
    if (save_unsaved_changes_dialogs()) {
      m_on_close_form_stat = true;
    } else {
      Action = caNone;
    }
    //m_on_close_form_stat = true;
  }
  //Action = caNone;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::WriteDataActionExecute(TObject *Sender)
{
  if (m_calibr_data_stat == calibr_data_stat_off) {
    if (!data_should_be_saved_dialog()) {
      return;
    }

    m_calibr_data_stat = calibr_data_stat_write;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::Panel1Resize(TObject *Sender)
{
  LeftPanel->Width = Panel1->Width/2;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::ConfigCBChange(TObject *Sender)
{
  const String new_selected_cfg = get_selected_config_filename();
  if (m_cur_filename_conf_calibr_device != new_selected_cfg) {
    m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str());
    if (save_unsaved_changes_dialogs()) {
      load_config_calibr();
      set_connect_if_enabled();
    } else {
      // Возвращаем предыдущий выбранный конфиг, так как пользователь отменил
      // действие
      select_config(m_cur_index_conf_calibr);
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::SetPhaseMeasActionExecute(TObject *Sender)
{
  //set_type_meas(tm_phase);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetPhaseAverageMeasActionExecute(
      TObject *Sender)
{
  //set_type_meas(tm_phase_average);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetTimeIntervalMeasActionExecute(
      TObject *Sender)
{
  //set_type_meas(tm_time_interval);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetTimeIntervalAverageMeasActionExecute(
      TObject *Sender)
{
  //set_type_meas(tm_time_interval_average);
}


/*TDataHandlingF::device_mode_status_t
  TDataHandlingF::status_device_mode()
{
  device_mode_status_t device_mode_status = DM_BUSY;
  if (m_timer_delay_control.check()) {
    m_log<<"Ждем установления рабочего режима.";
  }
  m_timer_delay_operating_duty.check();
  if ((m_timer_delay_control.stopped() == true) &&
    (m_timer_delay_operating_duty.stopped() == true)) {
    if (m_on_out_data == false) {
      if (m_on_reg_ready) {
        if (on_reg_ready_back_cycle == true) {
          on_reg_ready_back_cycle = false;
          device_mode_status = DM_SUCCESS;
          m_log << "Рабочий режим подтвержден.";
        } else {
          on_reg_ready_back_cycle = true;
          m_timer_delay_operating_duty.set(m_delay_operating_duty);
          m_log << "Рабочий режим установлен";
          m_log << ("Ждем " + FloatToStr(
            (CNT_TO_DBLTIME(m_delay_operating_duty))) +
            " секунд.");
        }
      } else {
        if (on_reg_ready_back_cycle == true) {
          m_log << "Происходит установление рабочего режима.";
        }
        on_reg_ready_back_cycle = false;
      }
    }
  }
  return device_mode_status;
}   */

void TDataHandlingF::meas_execute()
{
  m_value_meas.execute_meas(m_type_meas, &m_value_meas_multimetr);
  m_y_out = m_device.get_data()->y_out;
  if (m_cur_cell_cfg.out_param_measuring_conf.consider_out_param &&
    m_cur_cell_cfg.out_param_measuring_conf.filter_enabled) {
    m_y_out_filter.restart();
  }
  //m_log << "Происходит измерение.";
}

meas_status_t TDataHandlingF::meas_status()
{
  meas_status_t meas_status = meas_status_busy;
  meas_status = m_value_meas.get_status_meas();
  if(meas_status == meas_status_success) {
    //m_log << "Измерение успешно завершено!";
  } else if(meas_status == meas_status_error) {
    DGI_MSG("Измерение завершилось с ошибкой!");
  }
  return meas_status;
}

void __fastcall TDataHandlingF::AddTableActionExecute(TObject *Sender)
{
  String file_namedir;
  file_namedir = mp_active_table->get_file_namedir();
  if(!file_namedir.IsEmpty()){
    if(FileOpenDialog1->Execute()){
      String file_namedir = FileOpenDialog1->FileName;
      mp_active_table->load_subtable_from_file(file_namedir.c_str());
    }
  }else{
    FileOpen->Execute();
  }
}
//---------------------------------------------------------------------------

 

void __fastcall TDataHandlingF::ModeProgramCBClick(TObject *Sender)
{
  if (ModeProgramCB->Checked) {
    mp_manager_channel->Visible = true;
  }
}



void TDataHandlingF::set_control_parameters(const cell_config_calibr_t& a_cell_cfg)
{
  out_param_measuring_conf_t out_param_cfg_for_meas = a_cell_cfg.out_param_measuring_conf;
  m_y_out_filter.set_sampling_time(out_param_cfg_for_meas.filter_sampling_time);
  m_y_out_filter.resize(out_param_cfg_for_meas.filter_point_count);

  out_param_control_conf_t out_param_ctrl_cfg = a_cell_cfg.out_param_control_config;
  if (out_param_ctrl_cfg.enabled) {
    m_out_param_stability_control.set_stability_min_time(out_param_ctrl_cfg.time);
  } else {
    CurrentOutParamLabeledEdit->Text = String();
    ReferenceOutParamLabeledEdit->Text = String();
    AbsoluteDiffOutParamLabeledEdit->Text = String();
    RemainingTimeForStableState->Text = String();
  }

  if (m_config_calibr.temperature_ctrl_common_cfg.enabled) {
    temperature_control_config_t temperature_cfg = a_cell_cfg.temperature_control;
    if (temperature_cfg.enabled) {
      m_temperature_stability_control.set_reference(temperature_cfg.reference);
      m_temperature_stability_control.set_diviation(temperature_cfg.difference);      
      ReferenceTemperatureLabeledEdit->Text = FloatToStr(temperature_cfg.reference);
      DifferenceTemperatureLabeledEdit->Text = FloatToStr(temperature_cfg.difference);
    } else {
      ReferenceTemperatureLabeledEdit->Text = String();
      DifferenceTemperatureLabeledEdit->Text = String(); 
    }
  }
}



void TDataHandlingF::out_param(const param_cur_cell_t& a_param_cur_cell)
{
  m_param_cur_cell = a_param_cur_cell;
  m_param_cur_cell.col_value.value =
    m_param_cur_cell.col_value.value*m_config_calibr.in_parameter1.koef;
  m_param_cur_cell.row_value.value =
    m_param_cur_cell.row_value.value*m_config_calibr.in_parameter2.koef;
  if(m_inf_in_param.number_in_param == THREE_PARAM){
    m_param_cur_cell.top_value.value =
      m_param_cur_cell.top_value.value*m_config_calibr.in_parameter3.koef;
  }
  m_on_out_data = true;
  DGI_MSG("Установка параметров рабочего режима");
  out_message_log_cur_param_cell(a_param_cur_cell);

}


void TDataHandlingF::out_default_param()
{
  m_param_cur_cell = m_default_param_cur_cell;
  m_on_out_data = true;
  DGI_MSG("Установка дефолтных параметров");
}


void TDataHandlingF::out_message_log_cur_param_cell(
  const param_cur_cell_t& a_param_cur_cell)
{
  const int precision = 5;
  string_type message_param;
  if (m_inf_in_param.type_anchor == PARAMETR3) {
    if (a_param_cur_cell.top_value.init) {
      ostringstream_type ostr_top;
      ostr_top << setprecision(precision) << a_param_cur_cell.top_value.value;
      string_type top_value_str = ostr_top.str();
      message_param += top_value_str + irst(" ") +
        m_inf_in_param.type_variable_param3;
      message_param += irst("; ");
    }
  }
  if (a_param_cur_cell.row_value.init) {
    ostringstream_type ostr_row;
    ostr_row << setprecision(precision) << a_param_cur_cell.row_value.value;
    string_type row_value_str = ostr_row.str();
    message_param += row_value_str + irst(" ") +
      m_inf_in_param.type_variable_param2;
    message_param += irst("; ");
  }
  if (a_param_cur_cell.col_value.init) {
    ostringstream_type ostr_col;
    ostr_col << setprecision(precision) << a_param_cur_cell.col_value.value;
    string_type col_value_str = ostr_col.str();
    message_param += col_value_str + irst(" ") +
      m_inf_in_param.type_variable_param1;
    message_param += irst(";");
  }
  DGI_MSG(irs::str_conv<irs::string>(message_param));
}

/*bool TDataHandlingF::save_unsaved_changes_dialogsold()
{
  // Вначале обрабатываем сохранения изменений в таблице.
  // Если их не было, то и в конфигурации ячеек не должно быть изменений и
  // функция save_cells_config_dialog ничего не будет делать

  bool changes_were_forgotten = false;
  if (!save_unsaved_data_changes_dialog(&changes_were_forgotten))
    return false;

  return changes_were_forgotten || save_cells_config_dialog();
}*/

bool TDataHandlingF::save_unsaved_changes_dialogs()
{
  if (!mp_active_table->have_unsaved_changes() && !cells_config_is_changed()) {
    return true;
  }

  string_type message;
  if (mp_active_table->have_unsaved_changes()) {
    string_type filename =
      irs::str_conv<string_type>(mp_active_table->get_file_namedir());
    if (!filename.empty()) {
      filename = string_type(irst(" \"")) + filename + irst("\"");
    }

    message = irst("Сохранить изменения в таблице данных") + filename;
  }

  if (cells_config_is_changed()) {
    if (message.empty()) {
      message = irst("Сохранить изменения в настройках ячеек");
    } else {
      message += irst(" и настройках ячеек");
    }
  }

  message += irst("?");

  const string_type caption = irs::str_conv<string_type>(m_prog_name);

  const int result = Application->MessageBox(message.c_str(), caption.c_str(),
    MB_YESNOCANCEL + MB_ICONQUESTION);

  switch (result) {

    case mrYes: {
      if (mp_active_table->have_unsaved_changes()) {
        FileSave->Execute();
      }

      if (mp_active_table->have_unsaved_changes()) {
        DGI_MSG("Не удалось сохранить изменения в таблице данных.");
        return false;
      } else {
        return save_cells_config_if_need();
      }

    } break;

    case mrNo: {
      return true;
    } break;

    case mrCancel: {
      return false;
    } break;

  }

  return true;
}

/*bool TDataHandlingF::save_unsaved_data_changes_dialog()
{
  bool fsuccess = true;

  if (mp_active_table->have_unsaved_changes()) {

    string_type filename =
      irs::str_conv<string_type>(mp_active_table->get_file_namedir());
    if (!filename.empty()) {
      filename = string_type(irst(" \"")) + filename + irst("\"");
    }
    const string_type message =
      irst("Сохранить изменения в таблице данных") + filename + irst("?");

    const string_type caption = irs::str_conv<string_type>(m_prog_name);

    const int result = Application->MessageBox(
      message.c_str(),
      caption.c_str(),
      MB_YESNOCANCEL + MB_ICONQUESTION);

    switch (result) {
      case mrYes: {
        int a = 0;
        FileSave->Execute();
        if (mp_active_table->have_unsaved_changes()) {
          DGI_MSG("Не удалось сохранить изменения в таблице данных.");
          fsuccess = false;
        } else {
          fsuccess = true;
        }
      } break;
      case mrNo: {
        fsuccess = true;
      } break;
      case mrCancel: {
        fsuccess = false;
      } break;
    } 
  }
  return fsuccess;
}*/


bool TDataHandlingF::save_cells_config_dialog()
{
  if (!save_cells_config_if_need()) {
    string_type filename = irs::str_conv<string_type>(
      m_cur_filename_conf_calibr_device);
    if (!filename.empty()) {
      filename = string_type(irst(" \"")) + filename + irst("\"");
    }
    const string_type message = string_type(
      irst("Не удалось сохранить изменения в таблице настроек ячеек ")) +
      irst("в конфигурацию ") + filename + irst(". Продолжить без сохранения?");

    const string_type caption = irs::str_conv<string_type>(m_prog_name);

    const int result = Application->MessageBox(
      message.c_str(),
      caption.c_str(),
      MB_YESNO + MB_ICONQUESTION);

    switch (result) {
      case mrYes: {
        return true;
      } break;
      case mrNo: {
        return false;
      } break;
    }  
  }

  return true;
}


bool TDataHandlingF::save_cells_config_if_need()
{
  irs::table_t<cell_config_calibr_t> saved_cells_config =
    m_config_calibr.cells_config;
  if (cells_config_is_changed()) {
    m_config_calibr.cells_config = mp_active_table->get_cells_config();

    if (!m_cur_filename_conf_calibr_device.IsEmpty() &&
      m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str())) {
      DGI_MSG("Изменения в таблице настроек ячеек успешно сохранены.");
    } else {
      m_config_calibr.cells_config = saved_cells_config;
      DGI_MSG("Не удалось сохранить изменения в таблице настроек ячеек.");
      return false;
    }
  }
  return true;
}


bool TDataHandlingF::cells_config_is_changed() const
{
  if (!mp_active_table->is_cells_config_read_only() &&
    m_config_calibr.cells_config != mp_active_table->get_cells_config()) {
    return true;
  }

  return false;
}


bool TDataHandlingF::data_should_be_saved_dialog() const
{
  if (mp_active_table->is_cells_config_read_only()) {
    MessageDlg(irst("Измерение невозможно, так как файл данных был открыт ")
      irst("c опцией \"Открыть без возможности редактирования конфигурации\""),
      mtInformation, TMsgDlgButtons() << mbOK, 0);
    return false;
  }

  // Не пытаемся здесь вызывать диалоги сохранения данных,
  // так как пользователь может отказаться от сохранения данных, что потребует
  // перезагрузку файла, что инициирует дилог "Конфликт таблиц" и опять придется
  // проверять is_cells_config_read_only
  if (mp_active_table->have_unsaved_changes() || cells_config_is_changed()) {
    MessageDlg(irst("Необходимо сохранить данные перед началом измерений"),
      mtInformation, TMsgDlgButtons() << mbOK, 0);
    return false;
  }

  return true;
}



irs::matrix_t<cell_t> TDataHandlingF::get_sub_diapason_table_data(
  const int a_sub_diapason_index)
{
  irs::matrix_t<cell_t> sub_diapason;
  /*int sub_diapason_count = m_config_calibr.sub_diapason_calibr.size();
  if (a_sub_diapason >= sub_diapason_count) {
    return matrix;
  }*/
  const double value_begin =
    m_config_calibr.eeprom_ranges[a_sub_diapason_index].value_begin;
  const double value_end =
    m_config_calibr.eeprom_ranges[a_sub_diapason_index].value_end;

  std::vector<irs::matrix_t<cell_t> > v_table =
    mp_active_table->read_table();
  int table_count = v_table.size();
  if (table_count > 0) {
    irs::matrix_t<cell_t> table = v_table[0];
    const int col_count = table.col_count();
    const int row_count = table.row_count();
    int value_begin_index = 0;
    int value_end_index = 0;
    if (m_config_calibr.type_sub_diapason == tsd_parameter1) {
      bool value_begin_index_success = false;
      bool value_end_index_success = false;
      for (int col = 1; col < col_count; col++) {
        cell_t cell = table[col][0];
        if (cell.init) {
          if (cell.value >= value_begin) {
            value_begin_index = col;
            value_begin_index_success = true;
            break;
          }
        }
      }
      for (int col = col_count-1; col > 0; col--) {
        cell_t cell = table[col][0];
        if (cell.init) {
          if (cell.value <= value_end) {
            value_end_index = col;
            value_end_index_success = true;
            break;
          }
        }
      }
      if (value_begin_index_success && value_end_index_success) {
        const int sub_diapason_col_count = value_end_index-value_begin_index+2;
        IRS_ASSERT(sub_diapason_col_count <= (value_end_index+1));
        sub_diapason.resize(sub_diapason_col_count, row_count);
        // Копируем top_value
        sub_diapason[0][0] = static_cast<cell_t>(table[0][0]);
        // Копируем row_value
        for (int row = 0; row < row_count; row++) {
          sub_diapason[0][row] = static_cast<cell_t>(table[0][row]);
        }
        // Копируем все остальное
        for (int col = value_begin_index, col_sd = 1; col <= value_end_index;
          col++, col_sd++) {
          for (int row = 0; row < row_count; row++) {
            sub_diapason[col_sd][row] =
              static_cast<cell_t>(table[col][row]);
          }
        }
      }
    } else {
      bool value_begin_index_success = false;
      bool value_end_index_success = false;
      for (int row = 1; row < row_count; row++) {
        cell_t cell = table[0][row];
        if (cell.init) {
          if (cell.value >= value_begin) {
            value_begin_index = row;
            value_begin_index_success = true;
            break;
          }
        }
      }
      for (int row = row_count-1; row > 0; row--) {
        cell_t cell = table[0][row];
        if (cell.init) {
          if (cell.value <= value_end) {
            value_end_index = row;
            value_end_index_success = true;
            break;
          }
        }
      }
      if (value_begin_index_success && value_end_index_success) {
        const int sub_diapason_row_count = value_end_index-value_begin_index+2;
        IRS_ASSERT(sub_diapason_row_count <= (value_end_index+1));
        sub_diapason.resize(col_count, sub_diapason_row_count);
        // Копируем top_value
        //#ifdef NOP
        sub_diapason[0][0] = static_cast<cell_t>(table[0][0]);
        // Копируем col_value
        for (int col = 0; col < col_count; col++) {
          sub_diapason[col][0] = static_cast<cell_t>(table[col][0]);
        }
        //#ifdef NOP
        // Копируем все остальное
        for (int col = 0; col < col_count; col++) {
          for (int row = value_begin_index, row_sd = 1; row <= value_end_index;
            row++, row_sd++) {
            sub_diapason[col][row_sd] =
              static_cast<cell_t>(table[col][row]);
          }
        }
        //#endif // NOP
      }
    }
  }
  return sub_diapason;
}
//---------------------------------------------------------------------------
void TDataHandlingF::tick_calibr_data()
{
  switch(m_process_calibr_data_stat){
    case pcds_off: {
      switch(m_calibr_data_stat){
        case calibr_data_stat_write:
        case calibr_data_stat_verify: {
          m_cur_sub_diapason = 0;
          set_connect_calibr_device();
          m_process_calibr_data_stat = pcds_get_sub_diapason;
        } break;
      }
    } break;
    case pcds_next_sub_diapason: {
      m_cur_sub_diapason++;
      m_process_calibr_data_stat = pcds_get_sub_diapason;
    } break;
    case pcds_get_sub_diapason: {
      int sub_diapason_count = m_config_calibr.eeprom_ranges.size();
      if (m_cur_sub_diapason < sub_diapason_count) {
        DGI_MSG("Обрабатывается диапазон №" << (m_cur_sub_diapason + 1));
        irs::matrix_t<cell_t> sub_diapason =
          get_sub_diapason_table_data(m_cur_sub_diapason);
        calculation_koef(sub_diapason);
        m_index_pos_offset_eeprom =
          m_config_calibr.eeprom_ranges[m_cur_sub_diapason].index_start;
        m_max_size_correct =
          m_config_calibr.eeprom_ranges[m_cur_sub_diapason].size;
        if (m_calibr_data_stat == calibr_data_stat_write) {
          m_process_calibr_data_stat = pcds_write_sub_diapason;
        } else {
          m_process_calibr_data_stat = pcds_verify_sub_diapason;
        }
      } else {
        m_process_calibr_data_stat = pcds_reset;
        DGI_MSG("Обработка всех диапазонов завершена");
      }
    } break;
    case pcds_write_sub_diapason: {
      if ((!m_on_write_data_eeprom) && (!m_on_verification_data_eeprom)) {
        m_on_write_data_eeprom = true;
        m_process_calibr_data_stat = pcds_wait_process_write_passed;
      }
    } break;
    case pcds_verify_sub_diapason: {
      if ((!m_on_write_data_eeprom) && (!m_on_verification_data_eeprom)) {
        m_on_verification_data_eeprom = true;
        m_process_calibr_data_stat = pcds_wait_process_verify_passed;
      }
    } break;
    case pcds_wait_process_write_passed: {
      if (!m_on_write_data_eeprom) {
        if (m_on_auto_verify) {
          m_process_calibr_data_stat = pcds_verify_sub_diapason;
        } else {
          m_process_calibr_data_stat = pcds_next_sub_diapason;
        }
      }
    } break;
    case pcds_wait_process_verify_passed: {
      if (!m_on_verification_data_eeprom) {
        m_process_calibr_data_stat = pcds_next_sub_diapason;
      }
    } break;
    case pcds_reset: {
      if (!ConnectAction->Checked) {
        reset_connect_calibr_device();
      }
      m_calibr_data_stat = calibr_data_stat_off;
      m_process_calibr_data_stat = pcds_off;
      m_cur_sub_diapason = 0;
    } break;
  }
}
void TDataHandlingF::modifi_table_data()
{
  string_type str;
  irs::handle_t<TModifiDataTableF> modifi_data_table(
    new TModifiDataTableF(0, &str));
  if (!modifi_data_table->Visible) {
    int result = modifi_data_table->ShowModal();
    if (result == mrOk) {
      if (!str.empty()) {
        mp_active_table->modify_content_table(str);
      }  
    }
  }
}
void TDataHandlingF::set_value_working_extra_params(const coord_cell_t& a_coord)
{
  if (!m_device.connected()) {
    return;
  }

  const cell_config_calibr_t cell_config = get_cell_config(a_coord);

  size_type parametr_ex_count = m_config_calibr.v_parameter_ex.size();
  size_type extra_param_count = m_device.get_data()->v_extra_param.size();
  if (parametr_ex_count == extra_param_count) {
    IRS_ASSERT(extra_param_count == cell_config.ex_param_work_values.size());

    for (size_type i = 0; i < extra_param_count; i++) {
      m_device.get_data()->v_extra_param[i] = cell_config.ex_param_work_values[i];
        //m_config_calibr.v_parameter_ex[i].value_working;
      string_type value_working_str = cell_config.ex_param_work_values[i];
        //m_config_calibr.v_parameter_ex[i].value_working;
      String message = m_config_calibr.v_parameter_ex[i].name;
      message = message + irst(" установлен в ") + value_working_str.c_str();
      DGI_MSG(irs::str_conv<irs::string>(message));
    }
  }
}

void TDataHandlingF::set_value_default_extra_params()
{
  if (!m_device.connected()) {
    return;
  }
  int parametr_ex_count = m_config_calibr.v_parameter_ex.size();
  int extra_param_count = m_device.get_data()->v_extra_param.size();
  if (parametr_ex_count == extra_param_count) {
    for (int i = 0; i < extra_param_count; i++) {
      m_device.get_data()->v_extra_param[i] =
        m_config_calibr.v_parameter_ex[i].value_default ;
      irs::string_t value_default_str =
        m_config_calibr.v_parameter_ex[i].value_default;
      String message = m_config_calibr.v_parameter_ex[i].name;
      message = message + irst(" установлен в ") + value_default_str.c_str();
      DGI_MSG(irs::str_conv<irs::string>(message));
    }
  }
}

void TDataHandlingF::set_value_working_extra_bits(const coord_cell_t& a_coord)
{
  if (!m_device.connected()) {
    //m_log << "Устройство не подключено, не можем записать значения битов";
    return;
  }

  const cell_config_calibr_t cell_config = get_cell_config(a_coord);

  size_type bit_type2_count = m_config_calibr.bit_type2_array.size();
  size_type extra_bit_count = m_device.get_data()->v_extra_bit.size();
  if (bit_type2_count == extra_bit_count) {
    IRS_ASSERT(extra_bit_count == cell_config.ex_bit_work_values.size());

    for (size_type i = 0; i < extra_bit_count; i++) {

      m_device.get_data()->v_extra_bit[i] = cell_config.ex_bit_work_values[i];
      irs::string_t value_working_str = cell_config.ex_bit_work_values[i];
      String message = m_config_calibr.bit_type2_array[i].bitname.c_str();
      message = message + irst(" установлен в ") + value_working_str.c_str();
      DGI_MSG(irs::str_conv<irs::string>(message));
    }
  }
}
void TDataHandlingF::set_value_default_extra_bits()
{
  if (!m_device.connected()) {
    //m_log << "Устройство не подключено, не можем записать значения битов";
    return;
  }
  int bit_type2_count = m_config_calibr.bit_type2_array.size();
  int extra_bit_count = m_device.get_data()->v_extra_bit.size();
  //IRS_ASSERT(bit_type2_count == extra_bit_count);
  if (bit_type2_count == extra_bit_count) {
    for (int i = 0; i < extra_bit_count; i++) {
      m_device.get_data()->v_extra_bit[i] =
        m_config_calibr.bit_type2_array[i].value_def;
      irs::string_t value_default_str =
        m_config_calibr.bit_type2_array[i].value_def;
      String message = m_config_calibr.bit_type2_array[i].bitname.c_str();
      message = message + irst(" установлен в ") + value_default_str.c_str();
      DGI_MSG(irs::str_conv<irs::string>(message));
    }
  }
}

void TDataHandlingF::show_main_device_options()
{
  m_device.show_options();
}

void TDataHandlingF::show_ref_device_options()
{
  if (m_ref_device.created()) {
    m_ref_device.show_options();
  }
}

void TDataHandlingF::load_devices()
{
  load_main_device();
  if (m_config_calibr.reference_channel.enabled) {
    load_ref_device();
  }
}

void TDataHandlingF::load_main_device()
{
  const String config_name = m_config_calibr.device_name;
  if (is_main_device_config_exists(config_name)) {
    load_main_device(config_name);
  } else {
    if (!config_name.IsEmpty()) {
      DGI_MSG("Конфигурация устройства отсутствует");
    }
  }
}

void TDataHandlingF::load_ref_device()
{
  const String config_name = m_config_calibr.reference_device_name;
  if (is_ref_device_config_exists(config_name)) {
    load_ref_device(config_name);
  } else {
    if (!config_name.IsEmpty()) {
      DGI_MSG("Конфигурация устройства отсутствует");
    }
  }
}

void TDataHandlingF::load_main_device(const String& a_config_name)
{
  /*if (a_config_name != get_selected_config()) {
    load_config_calibr_to_display();
    select_config(a_config_name);
  }*/

  String device_file_name =
    m_file_name_service.make_device_config_full_file_name(a_config_name);

  m_device.load(device_file_name.c_str());

}

void TDataHandlingF::load_ref_device(const String& a_config_name)
{
  /*if (a_config_name != get_selected_config()) {
    load_config_calibr_to_display();
    select_config(a_config_name);
  }*/

  String ref_device_file_name =
    m_file_name_service.make_ref_device_config_full_file_name(a_config_name);

  m_ref_device.load(ref_device_file_name.c_str());
}


bool TDataHandlingF::is_main_device_config_exists(
  const String& a_config_name) const
{
  String device_file_name =
    m_file_name_service.make_device_config_full_file_name(a_config_name);
  return FileExists(device_file_name);
}

bool TDataHandlingF::is_ref_device_config_exists(
  const String& a_config_name) const
{
  String device_file_name =
    m_file_name_service.make_ref_device_config_full_file_name(a_config_name);
  return FileExists(device_file_name);
}

void TDataHandlingF::create_main_device_config_from_old(
  const String& a_config_name,
  const String& a_type, const config_calibr_t& a_config_calibr)
{
  String device_file_name =
    m_file_name_service.make_device_config_full_file_name(a_config_name);
  m_device.create_config_from_old(device_file_name, a_type,
    a_config_calibr.ip_adress,
    a_config_calibr.port);
}

void TDataHandlingF::create_ref_device_config_from_old(
  const String& a_config_name,
  const String& a_type, const config_calibr_t& a_config_calibr)
{
  String device_file_name =
    m_file_name_service.make_ref_device_config_full_file_name(a_config_name);

  m_ref_device.create_config_from_old(device_file_name, a_type,
    a_config_calibr.reference_channel.ip_adress,
    a_config_calibr.reference_channel.port);
}

void TDataHandlingF::change_main_device_type(const String& a_config_name,
  const String& a_type)
{
  String device_file_name =
    m_file_name_service.make_device_config_full_file_name(a_config_name);
  m_device.change_type(device_file_name, a_type);
}

void TDataHandlingF::change_ref_device_type(const String& a_config_name,
  const String& a_type)
{
  String device_file_name =
    m_file_name_service.make_ref_device_config_full_file_name(a_config_name);
  m_ref_device.change_type(device_file_name, a_type);
}

void TDataHandlingF::load_device_config_file(const String& a_config_name)
{
  String device_file_name =
    m_file_name_service.make_device_config_full_file_name(a_config_name);
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(device_file_name);
  ini_file.set_section(m_file_name_service.get_device_options_section());
  device_options_t device_options;
  device_options.type = irst("mxnet");
  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);
  ini_file.load();
  if (!FileExists(device_file_name)) {
    ini_file.save();
  }
}

void TDataHandlingF::delete_device_config(const String& a_config_name)
{
  if (ConfigCB->ItemIndex >= 0) {
    const String cur_config_name =
      ConfigCB->Items->Strings[ConfigCB->ItemIndex];
    if (a_config_name == cur_config_name) {
      m_device.reset();
    }
  }
  const String cfg_file_name =
    m_file_name_service.make_config_full_file_name(a_config_name);

  DeleteFile(cfg_file_name);

  load_config_calibr_to_display();
  load_config_calibr();
  set_connect_if_enabled();
}

void TDataHandlingF::unset_ref_device()
{
  m_ref_device.reset();
}

String TDataHandlingF::get_device_name()
{
  return m_device.get_name();
}

String TDataHandlingF::get_device_type() const
{
  return m_device.get_type();
}

String TDataHandlingF::get_ref_device_name()
{
  return m_ref_device.get_name();
}

String TDataHandlingF::get_ref_device_type() const
{
  return m_ref_device.get_type();
}

void __fastcall TDataHandlingF::RestructDataType1ActionExecute(
      TObject *Sender)
{
  mp_active_table->restruct_date_type_1();
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::ClearTableActionExecute(TObject *Sender)
{
  mp_active_table->clear_table();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::TableDefActionExecute(TObject *Sender)
{
  mp_active_table->clear_table_def();  
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::ClearContentTableActionExecute(
      TObject *Sender)
{
  mp_active_table->clear_content_table();  
}
//---------------------------------------------------------------------------
// struct chart_t
TDataHandlingF::chart_t::chart_t(
):
  builder_chart_window_z_of_x(),
  builder_chart_window_z_of_y(),
  p_chart_window_z_of_x(&builder_chart_window_z_of_x),
  p_chart_window_z_of_y(&builder_chart_window_z_of_y),
  on_auto_update(false)
{
  p_chart_window_z_of_x->group_all();
  p_chart_window_z_of_y->group_all();
}
void TDataHandlingF::chart_t::add_chart_z_of_x_cur_cell(
  const table_data_t* ap_table_data, const inf_in_param_t& a_inf_in_param)
{
  int cur_row = ap_table_data->get_row_displ();
  if (!ap_table_data->get_stat_cell_x(1, cur_row)) {
    add_chart_z_of_x(ap_table_data, a_inf_in_param, cur_row);
  }
}
void TDataHandlingF::chart_t::add_chart_z_of_y_cur_cell(
  const table_data_t* ap_table_data, const inf_in_param_t& a_inf_in_param)
{ 
  int cur_col = ap_table_data->get_col_displ();
  int cur_row = ap_table_data->get_row_displ();
  if (!ap_table_data->get_stat_cell_x(1, cur_row)) {
    add_chart_z_of_y(ap_table_data, a_inf_in_param, cur_col, cur_row);
  }
}
void TDataHandlingF::chart_t::add_all_chart_z_of_x(
  const table_data_t* ap_table_data,
  const inf_in_param_t& a_inf_in_param,
  const bool a_on_update)
{
  p_chart_window_z_of_x->clear_param();
  int row_count = ap_table_data->get_row_count_displ();
  for (int row = 1; row < row_count; row++) {
    if (!ap_table_data->get_stat_cell_x(1, row)) {
      add_chart_z_of_x(ap_table_data, a_inf_in_param, row, a_on_update);
    }
  }
}
void TDataHandlingF::chart_t::add_all_chart_z_of_y(
  const table_data_t* ap_table_data,
  const inf_in_param_t& a_inf_in_param,
  const bool a_on_update)
{        
  p_chart_window_z_of_y->clear_param();
  int col_count = ap_table_data->get_col_count_displ();
  int table_count = ap_table_data->table_count();
  for (int table = 0; table < table_count; table++) {
    for (int col = 1; col < col_count; col++) {
      coord3d_t coord3d;
      coord3d.x = col;
      coord3d.y = 1;
      coord3d.z = table;
      coord_t coord = ap_table_data->get_coord_cell_table_displ(coord3d);
      add_chart_z_of_y(
        ap_table_data, a_inf_in_param, coord.x, coord.y, a_on_update);
    }
  }
}
void TDataHandlingF::chart_t::add_chart_z_of_x(
  const table_data_t* ap_table_data,
  const inf_in_param_t& a_inf_in_param,
  const int a_row_z_data,
  const bool a_on_update)
{
  static const precision_name_graph = 5;
  int cur_row = a_row_z_data;
  if(cur_row < 1) cur_row = 1;
  const int index_col_cell = 0;
  cell_t cur_row_cell =
    ap_table_data->get_cell_table(index_col_cell, cur_row);
  if(cur_row_cell.init){
    vector<cell_t> x_points;
    vector<cell_t> p_points;
    cell_t z;
    ap_table_data->get_points_func_p_of_x_cur_row(
      p_points, x_points, z, cur_row);
    double row_value = cur_row_cell.value;
    string_type name_graph;
    string_type row_value_str;
    string_type z_value_str;
    ostringstream_type ostr_row;
    ostringstream_type ostr_z;
    
    ostr_row << setprecision(precision_name_graph) << row_value;
    row_value_str = ostr_row.str();
    double norm_koef = 1;
    if(a_inf_in_param.type_anchor == PARAMETR2){
      norm_koef = row_value;
    }else if(a_inf_in_param.type_anchor == PARAMETR3){
      if(z.init){
        if (z.value != 0) norm_koef = z.value;
        ostr_z << setprecision(precision_name_graph) << z.value;
        z_value_str = ostr_z.str();
        name_graph = z_value_str + irst(" ") +
          a_inf_in_param.type_variable_param3 + irst(", ");
      }
    }

    name_graph += row_value_str + irst(" ") +
      a_inf_in_param.type_variable_param2 + irst(" (строка ") +
      irs::num_to_str(a_row_z_data) + irst(")");

    if (!a_on_update) {
    
      ostringstream_type out2(name_graph);
      add_chart_z_of_x(
        name_graph, p_points, x_points, a_inf_in_param, norm_koef);
      p_chart_window_z_of_x->show();
    } else {
      int size = z_of_x_charts.size();
      for (int i = 0; i < size; i++) {
        if (z_of_x_charts[i] == name_graph) {
          add_chart_z_of_x(
            name_graph, p_points, x_points, a_inf_in_param, norm_koef);
          break;
        }
      }
    }
  }
}

void TDataHandlingF::chart_t::add_chart_z_of_y(
  const table_data_t* ap_table_data,
  const inf_in_param_t& a_inf_in_param,
  const int a_col_z_data,
  const int a_row_z_data,
  const bool a_on_update)
{
  static const precision_name_graph = 5;
  int cur_col = a_col_z_data;
  int cur_row = a_row_z_data;
  if(cur_col < 1) cur_col = 1;
  const int index_row_cell = 0;
  cell_t cur_col_cell = ap_table_data->get_cell_table(cur_col, index_row_cell);
  if (cur_col_cell.init) {
    vector<cell_t> y_points;
    vector<cell_t> p_points;
    cell_t z;
    ap_table_data->get_points_func_p_of_y_cur_col_cur_table(
      p_points, y_points, z, cur_col, cur_row);

    double col_value = cur_col_cell.value;
    string_type name_graph, col_value_str, z_value_str;
    ostringstream_type ostr_col;
    ostringstream_type ostr_z;

    ostr_col << setprecision(precision_name_graph) << col_value;
    col_value_str = ostr_col.str();
    double norm_koef = 1;
    if(a_inf_in_param.type_anchor == PARAMETR1) {
      norm_koef = col_value;
    }else if(a_inf_in_param.type_anchor == PARAMETR3){
      if(z.init){
        if (z.value != 0) norm_koef = z.value;
        ostr_z << setprecision(precision_name_graph) << z.value;
        z_value_str = ostr_z.str();
        name_graph = z_value_str + irst(" ") +
          a_inf_in_param.type_variable_param3 + irst(", ");
      }
    }

    name_graph += col_value_str + irst(" ") +
      a_inf_in_param.type_variable_param1 + irst(" (колонка ") +
      irs::num_to_str(a_col_z_data) + irst(")");

    if (!a_on_update) {
      add_chart_z_of_y(
        name_graph, p_points, y_points, a_inf_in_param, norm_koef);
      p_chart_window_z_of_y->show();
    } else {
      int size = z_of_y_charts.size();
      for (int i = 0; i < size; i++) {
        if (z_of_y_charts[i] == name_graph) {
          add_chart_z_of_y(
            name_graph, p_points, y_points, a_inf_in_param, norm_koef);
          break;
        }
      }
    }
  }
}

void TDataHandlingF::chart_t::save_name_chart_z_of_x(
  const string_type& a_name_chart)
{
  bool on_present = false;
  int size = z_of_x_charts.size();
  for (int i = 0; i < size; i++) {
    if (z_of_x_charts[i] == a_name_chart) {
      on_present = true;
      break;
    }
  }
  if (!on_present) {
    z_of_x_charts.push_back(a_name_chart);
  }
}
void TDataHandlingF::chart_t::save_name_chart_z_of_y(
  const string_type& a_name_chart)
{
  bool on_present = false;
  int size = z_of_y_charts.size();
  for (int i = 0; i < size; i++) {
    if (z_of_y_charts[i] == a_name_chart) {
      on_present = true;
      break;
    }
  }
  if (!on_present) {
    z_of_y_charts.push_back(a_name_chart);
  }
}
void TDataHandlingF::chart_t::clear_chart()
{
  p_chart_window_z_of_x->clear_param();
  p_chart_window_z_of_y->clear_param();
  z_of_x_charts.clear();
  z_of_y_charts.clear();
}
void TDataHandlingF::chart_t::auto_update_on()
{
  on_auto_update = true;
}

void TDataHandlingF::chart_t::auto_update_off()
{
  on_auto_update = false;
}
bool TDataHandlingF::chart_t::get_auto_update_stat()
{
  return on_auto_update;
}

void TDataHandlingF::chart_t::add_chart_z_of_x(
  const string_type& a_name_graph,
  const std::vector<cell_t>& a_p_points,
  const std::vector<cell_t>& a_x_points,
  const inf_in_param_t& a_inf_in_param,
  const double a_norm_koef)
{
  int p_points_count = a_p_points.size();
  int x_points_count = a_x_points.size();
  if (p_points_count == x_points_count) {
    p_chart_window_z_of_x->add_param(a_name_graph);
    save_name_chart_z_of_x(a_name_graph);
    for(int i = 0; i < p_points_count; i++) {
      cell_t x_cell = a_x_points[i];
      cell_t p_cell = a_p_points[i];
      if((x_cell.init == true) && p_cell.init == true) {
        double x_cell_value = x_cell.value;
        double p_cell_value = p_cell.value;
        if(a_inf_in_param.type_anchor == PARAMETR1) {
          p_cell_value = p_cell_value/x_cell_value;
        }else{
          p_cell_value = p_cell_value/a_norm_koef;
        }
        p_chart_window_z_of_x->add(
          a_name_graph, x_cell_value, p_cell_value);
      }
    }
  }
}
void TDataHandlingF::chart_t::add_chart_z_of_y(
  const string_type& a_name_graph,
  const std::vector<cell_t>& a_p_points,
  const std::vector<cell_t>& a_y_points,
  const inf_in_param_t& a_inf_in_param,
  const double a_norm_koef)
{
  int p_points_count = a_p_points.size();
  int y_points_count = a_y_points.size();
  if (p_points_count == y_points_count) {
    p_chart_window_z_of_y->add_param(a_name_graph);
    save_name_chart_z_of_y(a_name_graph);
    for(int i = 0; i < p_points_count; i++) {
      cell_t y_cell = a_y_points[i];
      cell_t p_cell = a_p_points[i];
      if((y_cell.init == true) && p_cell.init == true) {
        double y_cell_value = y_cell.value;
        double p_cell_value = p_cell.value;
        if(a_inf_in_param.type_anchor == PARAMETR2) {
          p_cell_value = p_cell_value/y_cell_value;
        }else{
          p_cell_value = p_cell_value/a_norm_koef;
        }
        p_chart_window_z_of_y->add(
          a_name_graph.c_str(), y_cell_value, p_cell_value);
      }
    }
  }
}

void TDataHandlingF::add_graph_z_of_x()
{
}
void TDataHandlingF::add_graph_z_of_y()
{  
}
//---------------------------------------------------------------------------
void TDataHandlingF::add_all_graph_z_of_x()
{
}
//---------------------------------------------------------------------------
void TDataHandlingF::add_all_graph_z_of_y()
{
}
//---------------------------------------------------------------------------
void TDataHandlingF::update_all_graph()
{
}
void TDataHandlingF::clear_all_graph()
{
  m_chart.clear_chart();
}

irs_uarc TDataHandlingF::number_of_koef_per_point() const
{
  if (m_inf_in_param.number_in_param == THREE_PARAM) {
    return 2;
  }
  return 1;
}

void __fastcall TDataHandlingF::AutoUpdateChartActionExecute(
      TObject *Sender)
{
  m_chart.on_auto_update = !m_chart.on_auto_update;
  if (m_chart.on_auto_update) {
    AutoUpdateChartAction->Checked = true;
  } else {
    AutoUpdateChartAction->Checked = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::ExportTableToMExcelCsvFileActionExecute(
      TObject *Sender)
{
  SaveFileDialog->Filter = irst("Текстовые файлы Microsoft Excel (*.csv)")
    irst("|*.csv|Все файлы (*.*)|*.*");
  SaveFileDialog->DefaultExt = irst("csv");
  SaveFileDialog->FileName = irst("Новый файл.csv");
  if (SaveFileDialog->Execute()) {
    string_type file_name = SaveFileDialog->FileName.c_str();
    mp_active_table->save_table_to_microsoft_excel_csv_file(file_name);
  }
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::ClearContentColTableActionExecute(
      TObject *Sender)
{
  mp_active_table->clear_conrent_cur_col_table();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::ClearContentRowTableActionExecute(
      TObject *Sender)
{
  mp_active_table->clear_countnt_cur_row_table();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::InversionSignConrentTableActionExecute(
      TObject *Sender)
{
  mp_active_table->inversion_sign_conrent_table();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::VerificationDataActionExecute(
      TObject *Sender)
{
  if (m_calibr_data_stat == calibr_data_stat_off) {
    if (!data_should_be_saved_dialog()) {
      return;
    }

    m_calibr_data_stat = calibr_data_stat_verify;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::ModifiTableDataActionExecute(
      TObject *Sender)
{
  modifi_table_data();  
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::AboutActionExecute(TObject *Sender)
{
  irs::handle_t<TAboutForm> AboutForm(new TAboutForm(IRS_NULL));
  AboutForm->ShowModal();
}
//---------------------------------------------------------------------------







void __fastcall TDataHandlingF::RawDataStringGridExit(TObject *Sender)
{
  if(m_cur_cell_table1.init){
    string_type latest_entry_previous_cell_str =
      RawDataStringGrid->Cells
      [m_cur_cell_table1.col][m_cur_cell_table1.row].c_str();
    if (m_cur_cell_table1.value_str != latest_entry_previous_cell_str){
      mp_active_table->cur_cell_in_display();
      RawDataStringGrid->Repaint();
    }
    m_cur_cell_table1.init = false;
  }
}
//---------------------------------------------------------------------------














void __fastcall TDataHandlingF::ConnectionLogMenuItemClick(TObject *Sender)
{
  m_device.show_connection_log();
}
//---------------------------------------------------------------------------



void __fastcall TDataHandlingF::ConnectActionExecute(TObject *Sender)
{
  //m_device.mxdata_assembly->enabled(!ConnectAction->Checked);
  if (!ConnectAction->Checked) {
    set_connect_calibr_device();
  } else {
    reset_connect_calibr_device();
  }
  ConnectAction->Checked = !ConnectAction->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::TSTLANActionExecute(TObject *Sender)
{
  /*if (!m_device.tstlan4lib.is_empty()) {
    m_device.tstlan4lib->show();
  } */
  if (m_device.created()) {
    m_device.show_tstlan();
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::ConnectionLogActionExecute(TObject *Sender)
{
  //m_device.connection_log->Show();
  m_device.show_connection_log();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::DeleteConfigButtonClick(TObject *Sender)
{
  /*bool changes_were_forgotten = false;
  if (!save_unsaved_data_changes_dialog(&changes_were_forgotten)) {
    return;
  } */
  if (!save_unsaved_changes_dialogs()) {
    return;
  }

  const String config_name = get_selected_config();
  if (!config_name.IsEmpty()) {
    if (Application->MessageBox(
      irst("Вы действительно хотите удалить конфигурацию?"),
      irst("Вопрос"),  MB_OKCANCEL + MB_DEFBUTTON2 + MB_ICONQUESTION) ==
        IDOK) {
      delete_device_config(config_name);
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::ShowMultimeterOptionsButtonClick(TObject *Sender)

{
  if (!mp_mxmultimeter_assembly.is_empty()) {
    mp_mxmultimeter_assembly->show_options();
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::PatternOfMeasuringInstrumentCBChange(TObject *Sender)

{
  reset_mxmultimeter_assembly();
}
//---------------------------------------------------------------------------

void TDataHandlingF::reset_mxmultimeter_assembly()
{
  mp_mxmultimeter_assembly.reset();

  String name = get_selected_multimeter();
  String file_name =
    m_file_name_service.make_multimeter_config_full_file_name(name);
  if (FileExists(file_name)) {
    const String device_option_section =
      m_file_name_service.get_device_options_section();
    irs::ini_file_t ini_file;
    ini_file.set_ini_name(file_name);
    ini_file.set_section(device_option_section);
    string_type type;

    ini_file.add(irst("type"), &type);
    ini_file.load();
    mp_mxmultimeter_assembly = make_mxmultimeter_assembly(
      irs::str_conv<string_type>(file_name), irs::str_conv<string_type>(type));
  }
}

irs::handle_t<irs::mxmultimeter_assembly_t>
TDataHandlingF::make_mxmultimeter_assembly(
  const irs::string_t& a_device_name,
  const irs::string_t& a_device_type)
{
  return irs::mxmultimeter_assembly_types()->
    make_assembly(a_device_type, a_device_name);
}


/*bool TDataHandlingF::are_displ_table_and_config_table_different() const
{
  bool are_headers_different = false;
  
  if (mp_active_table->col_count() ==
      m_config_calibr.cells_config.get_col_count() &&
    mp_active_table->row_count() ==
      m_config_calibr.cells_config.get_row_count()) {

    IRS_ASSERT(col_count() > 1 && row_count() > 1);

    for (size_type col = 0; col < mp_active_table->col_count(); col++) {
      cell_t displ_cell = mp_active_table->get_cell_table(col, 0);
      cell_config_calibr_t cell_config =
        m_config_calibr.cells_config.read_cell(col, 0);
      if (displ_cell.init != cell_config.is_value_initialized ||
        is_equals(displ_cell.value, cell_config.value)) {
        are_headers_different = true;
        break;
      }
    }

    if (!are_headers_different) {
      for (size_type row = 1; row < mp_active_table->row_count(); row++) {
        cell_t displ_cell = mp_active_table->get_cell_table(0, row);
        cell_config_calibr_t cell_config =
          m_config_calibr.cells_config.read_cell(0, row);
        if (displ_cell.init != cell_config.is_value_initialized ||
          is_equals(displ_cell.value, cell_config.value)) {
          are_headers_different = true;
          break;
        }
      }  
    }

  } else {
    are_headers_different = true;
  }

  return is_headers_different;
}*/


void __fastcall TDataHandlingF::ShowMeasPointChartActionExecute(TObject *Sender)
{
  if (mp_meas_point_chart.is_empty()) {
    mp_meas_point_chart.reset(new irs::chart::builder_chart_window_t(10000, 1000,
      irs::chart::builder_chart_window_t::stay_on_top_off));
    mp_meas_point_chart->show();

    const int col = mp_active_table->get_col_displ();
    const int row = mp_active_table->get_row_displ();
    reset_chart(col, row);

    ShowMeasPointChartAction->Checked = true;
  } else {
    mp_meas_point_chart.reset();
    ShowMeasPointChartAction->Checked = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::ComparsionMenuItemClick(TObject *Sender)
{
  ComparsionDataForm->Show();
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::ParametersMenuItemClick(TObject *Sender)
{
  ParametersForm->set_table(&mp_active_table);
  ParametersForm->Show();
}
//---------------------------------------------------------------------------



void __fastcall TDataHandlingF::RawDataStringGridMouseActivate(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)

{
  int ACol = 0;
  int ARow = 0;
  RawDataStringGrid->MouseToCell(X, Y, ACol, ARow);
  on_select_cell(ACol, ARow, Shift);
}
//---------------------------------------------------------------------------



void __fastcall TDataHandlingF::LockMeasCellsRangeActionExecute(TObject *Sender)
{
  if(!(LockMeasCellsRangeAction->Checked)){
    try_to_lock_meas_cells_range();
  } else {
    LockMeasCellsRangeAction->Checked = false;
    m_meas_cells_range = TRect(-1, -1, -1, -1);
    RawDataStringGrid->Invalidate();
  }
}


bool TDataHandlingF::try_to_lock_meas_cells_range()
{
  if (is_cells_range_valid(m_cells_range)) {
    LockMeasCellsRangeAction->Checked = true;
    m_meas_cells_range = m_cells_range;
    RawDataStringGrid->Invalidate();
    return true;
  }

  return false;
}


bool TDataHandlingF::lock_meas_cells_range_if_need()
{
  if (is_meas_cells_range_locked())
    return true;

  return try_to_lock_meas_cells_range();
}



bool TDataHandlingF::is_meas_cells_range_locked() const
{
  return LockMeasCellsRangeAction->Checked &&
    is_cells_range_valid(m_meas_cells_range);
}


//
bool TDataHandlingF::has_cells_out_param_ctrl_enabled() const
{
  const irs::table_t<cell_config_calibr_t>& table = m_config_calibr.cells_config;
  for (size_type col_i = 1; col_i < table.get_col_count(); col_i++) {
    for (size_type row_i = 1; row_i < table.get_row_count(); row_i++) {
      const cell_config_calibr_t& cell = table.read_cell(col_i, row_i);
      if (cell.out_param_control_config.enabled) {
        return true;
      }
    }
  }
  return false;
}

//
bool TDataHandlingF::is_cells_range_valid(const TRect& a_rect) const
{
  return irs::is_in_range<int>(a_rect.Left,
      1, RawDataStringGrid->ColCount - 1 ) &&
    irs::is_in_range<int>(a_rect.Top,
      1, RawDataStringGrid->RowCount - 1 ) &&
    irs::is_in_range<int>(a_rect.Right,
      1, RawDataStringGrid->ColCount - 1 ) &&
    irs::is_in_range<int>(a_rect.Bottom,
      1, RawDataStringGrid->RowCount - 1 );
}
void __fastcall TDataHandlingF::AutoSaveMeasActionExecute(TObject *Sender)
{
  AutoSaveMeasAction->Checked = !AutoSaveMeasAction->Checked;
  m_is_autosave_meas_enabled = AutoSaveMeasAction->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::CopyCellsConfligActionExecute(TObject *Sender)
{
  if (is_cells_range_valid(m_cells_range)) {
    m_copied_cell_config.col = m_cells_range.Left;
    m_copied_cell_config.row = m_cells_range.Top;
    update_buttons_config();
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::PasteCellsConfigActionExecute(TObject *Sender)
{
  coord_t coord;
  coord.x = m_copied_cell_config.col;
  coord.y = m_copied_cell_config.row;
  mp_active_table->copy_cells_config(coord, m_cells_range);

  if (ShowSameCellConfigsAction->Checked) {
    RawDataStringGrid->Invalidate();
  }
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::SelectAllCellsActionExecute(TObject *Sender)
{
  m_start_col = 1;
  m_start_row = 1;
  m_cells_range = TRect(1, 1, RawDataStringGrid->ColCount - 1,
    RawDataStringGrid->RowCount - 1);
  RawDataStringGrid->Invalidate();
  update_buttons_config();
}
//-----------------------ShowSameCellConfigsActionExecute-------------------

void __fastcall TDataHandlingF::ShowSameCellConfigsActionExecute(TObject *Sender)
{
  ShowSameCellConfigsAction->Checked = !ShowSameCellConfigsAction->Checked;
  RawDataStringGrid->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::measureMethodAverageCheckboxClick(TObject *Sender)
{
  m_measure_method = mm_average;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::measureMethodImpulseFilterCheckboxClick(TObject *Sender)
{
  m_measure_method = mm_impulse_filter;
}
//---------------------------------------------------------------------------



