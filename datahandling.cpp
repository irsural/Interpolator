//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "datahandling.h"d
#include <irscpp.h>
//#include "mathv.h"



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
  const irs::string a_name,
  const irs::string a_opt_ini,
  const int a_num_mxifa_mxnetc)
  : TForm(Owner),

  m_prog_name("Digital interpolator"),
  m_mode_program(a_mode_program),
  m_path_prog(""),
  m_name_main_opt_ini_file(a_opt_ini.c_str()),
  m_main_opt_ini_file(),
  //m_conf_device_ini_file(),
  m_log(LogMemo, "Log.txt"),
  m_log_message(&m_log),
  mp_manager_channel(ap_manager_channel),
  m_value_meas(),
  m_foldername_conf("configuration"),
  m_default_ext("cpc"),
  m_fileid_conf("Конфигурация настроек калибровки."),
  m_config_calibr(),
  m_conf_calibr_buf(),
  m_inf_in_param(),
  mp_options_prog_ini_file(0),
  status_connect(WAIT_CONNECT),
  status_connect_eeprom(sce_off),

  m_name_file_options_ini("interpoptions.ini"),
  m_data_map(),
  mp_data_map_ref_channel(NULL),
  m_mxnet(a_num_mxifa_mxnetc),
  m_mxnet_data(&m_mxnet, MS_TO_CNT(2000)),
  mp_mxnet_ref_channel(NULL),
  mp_mxnet_data_ref_channel(NULL),

  //обращение к массиву в памяти контроллера
  mp_eeprom(IRS_NULL),
  mp_local_data(IRS_NULL),
  m_cur_config_device(""),
  m_cur_config_multimetr(""),
  m_load_conf_calibr_device_success(false),
  m_bad_cells(false),
  m_on_block_reconfiguration(false),
  m_cur_filename_conf_calibr_device(""),

  m_on_write_data_eeprom(false),
  m_on_verification_data_eeprom(false),
  m_on_out_data(false),

  m_on_correct(false),
  m_correct_mode_previous_stat(false),

  m_status_options(OFF_PROCESSING),

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
  ///////////////////////////////////////////////////////////////////////
  //m_my_file_name("Data.txt"),
  m_chart(),
  m_timer_chart_auto_update(irs::make_cnt_ms(1000)),
  m_successfully_mode_setting(false),

  m_on_connect_mxnet_data(false),
  m_on_connect_eeprom(false),

  m_on_start_new_auto_meas(false),
  m_on_auto_meas(false),
  m_on_stop_process_avto_volt_meas(false),
  m_on_process_auto_meas_active_cell(false),
  on_reg_ready_back_cycle(false),

  m_status_process_meas(spm_off_process),
  m_on_jump_smooth(true),
  m_type_jump_next_elem(VERTICAL_FORWARD_SMOOTH),
  m_str_type_jump_next_elem(
    type_jump_next_elem_to_str(m_type_jump_next_elem).c_str()),

  m_type_meas(tm_volt_dc),

  m_start_elem(1,1),
  m_start_inverse_elem(m_start_elem),
  m_cur_elem(m_start_elem),
  m_max_cur_elem(m_start_elem),
  m_min_cur_elem(m_start_elem),

  //m_temperature_allowable(false),
  m_out_param_stability_control(0, 0, 0),
  m_out_param_stable_min_time(),
  m_temperature_stability_control(0, 0, temperature_stability_min_time),
  m_temperature_stable_min_time(),
  m_on_reg_ready(false),

  m_delay_start_control_reg(irs::make_cnt_ms(5000)),
  m_delay_operating_duty(irs::make_cnt_ms(2000)),
  m_delay_control_error_bit(irs::make_cnt_ms(5000)),
  m_delay_next_cell(irs::make_cnt_ms(5000)),
  m_timer_delay_control(m_delay_start_control_reg),
  m_timer_delay_operating_duty(m_delay_operating_duty),
  m_timer_delay_control_error_bit(m_delay_control_error_bit),
  m_timer_delay_next_cell(m_delay_next_cell),
  m_time_meas(),
  m_count_point_meas(0),
  m_previous_count_point_meas(0),
  m_cell_per_sec(0.0),
  m_cell_count_end(0),
  m_previous_time_meas_sec(0.0),
  m_status_copy_table(OFF_COPY),
  table_string_grid1(RawDataStringGrid),
  m_table_raw_data(&table_string_grid1,
    "Таблица исходных значений"),
  m_table_data_size(&m_table_raw_data),
  m_manager_traffic_cell(&m_table_data_size),
  mp_active_table(&m_table_raw_data),
  mv_config_table_copy(0),
  m_memory_capacity(128),      // max 4080
  m_param_cur_cell(),
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
  m_cur_cell_table1(1, 1, "", false),
  m_on_get_edit_text_event_sg(false),
  m_on_key_char_down(false),
  m_default_param_cur_cell(),
  m_cur_count_reset_over_bit(0),
  y_out(0.),
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
  if (m_mode_program == mode_prog_single_channel) {
    // обработчик ошибок
    irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, &m_log_message);
  } else {
    m_prog_name = a_name.c_str();
    ModeProgramCB->Enabled = false;
    if (m_on_ref_channel == false) {
      unset_ref_channel();
    }
  }
  AnsiString ExeName = Application->ExeName;
  m_path_prog = ExtractFilePath(ExeName);
  AnsiString file_namedir_ini = m_path_prog + m_name_file_options_ini;
  //если папка существует
  //определяет, существует ли каталог
  AnsiString dir_config = m_path_prog + m_foldername_conf;
  if(DirectoryExists(dir_config)){
    load_config_calibr_to_display(dir_config);
  }

  PatternOfMeasuringInstrumentCB->Clear();
  type_multimetr_t type_multimetr = tmul_first;
  int index = static_cast<int>(type_multimetr);
  while(true){
    type_multimetr = static_cast<type_multimetr_t>(index);
    irs::string type_multimetr_str = type_multimetr_to_str(type_multimetr);
    PatternOfMeasuringInstrumentCB->Items->Add(type_multimetr_str.c_str());
    if(type_multimetr == tmul_last)
      break;
    index++;
  }
  /*PatternOfMeasuringInstrumentCB->Items->Add(
    "Вольтметр Универсальный Agilent 3458A");
  PatternOfMeasuringInstrumentCB->Items->Add(
    "Вольтметр универсальный Акип B7-78/1; M3500A");
  PatternOfMeasuringInstrumentCB->Items->Add(
    "Частотомер электронно-счетный Акип Ч3-85/3R;");*/
  PatternOfMeasuringInstrumentCB->ItemIndex = 0;
  //устанавливаем имя файла настроек программы
  m_main_opt_ini_file.set_ini_name(m_name_main_opt_ini_file);
  m_main_opt_ini_file.set_section("Опции");

  m_main_opt_ini_file.add(AnsiString("Текущая конфигурация"), ConfigCB);
  m_main_opt_ini_file.add(
    AnsiString("Текущий мультиметр"),
    PatternOfMeasuringInstrumentCB);
  m_main_opt_ini_file.add(
    AnsiString("Режим коррекции"), &m_on_correct);
  m_main_opt_ini_file.add(
    AnsiString("Режим расстройки"), &m_on_mismatch_state);
  m_main_opt_ini_file.add(
    AnsiString("Стиль движения"), &m_str_type_jump_next_elem);
  m_main_opt_ini_file.add(
    AnsiString("Автообновление графиков"), &m_chart.on_auto_update);

  m_main_opt_ini_file.load();
  correct_mode_change_stat(m_on_correct);
  mismatch_mode_change_stat(m_on_mismatch_state);
  set_setting_for_type_jump_next_cell(m_str_type_jump_next_elem);
  AutoUpdateChartAction->Checked = m_chart.on_auto_update;

  set_connect_calibr_device();
  init_to_cnt();
  m_timer_chart_auto_update.start();
  m_exec_progress.hide();
  m_exec_progress.clear();
  FileOpen->Enabled;
  
}
__fastcall TDataHandlingF::~TDataHandlingF()
{
  reset_connect_multimetr();
  deinit_to_cnt();
  m_main_opt_ini_file.save();
  m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str());
  //save_cur_config_device();
  if (m_mode_program == mode_prog_single_channel) {
    // обработчик ошибок
    irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, IRS_NULL);
  }
  //irs::cbuilder::set_error_handler(irs::cbuilder::ht_log, NULL);
}
//загрузка конфигураций калибровки на экран
void TDataHandlingF::load_config_calibr_to_display(const AnsiString a_dir)
{
  mv_list_config_calibr.clear();
  ConfigCB->Clear();
  TSearchRec sr;
  AnsiString filter = a_dir+AnsiString("\\*")+"."+m_default_ext;
  if(FindFirst(filter, faAnyFile, sr) == 0){
    ConfigCB->Items->Add(extract_short_filename(sr.Name));
    mv_list_config_calibr.push_back(a_dir+"\\"+sr.Name);
    while(FindNext(sr) == 0){
      ConfigCB->Items->Add(extract_short_filename(sr.Name));
      mv_list_config_calibr.push_back(a_dir+"\\"+sr.Name);
    }
    ConfigCB->ItemIndex = 0;
  }
  FindClose(sr);
}
//загрузка конфигурации калибровки
void TDataHandlingF::load_config_calibr()
{
  m_log<<"Загрузка конфигурации калибровки.";
  m_conf_calibr_buf.clear();
  m_load_conf_calibr_device_success = false;
  int index_file = ConfigCB->ItemIndex;
  // если выбран файл
  if(index_file >= 0){
  // если файл существует
    AnsiString filename_conf = mv_list_config_calibr[index_file];
    if(FileExists(filename_conf)){
      //m_conf_device_ini_file.set_ini_name(filename_conf);
      //m_conf_device_ini_file.load();
      m_cur_filename_conf_calibr_device = filename_conf.c_str();
      m_conf_calibr_buf.load(m_cur_filename_conf_calibr_device.c_str());
      m_config_calibr = m_conf_calibr_buf;

      m_inf_in_param.type_variable_param1 =
        m_config_calibr.in_parametr1.type_variable.c_str();
      m_inf_in_param.type_variable_param2 =
        m_config_calibr.in_parametr2.type_variable.c_str();
      m_inf_in_param.type_variable_param3 =
        m_config_calibr.in_parametr3.type_variable.c_str();
      if (m_config_calibr.in_parametr1.anchor == true) {
        m_inf_in_param.type_anchor = PARAMETR1;
        m_inf_in_param.number_in_param = TWO_PARAM;
      } else if(m_config_calibr.in_parametr2.anchor == true) {
        m_inf_in_param.type_anchor = PARAMETR2;
        m_inf_in_param.number_in_param = TWO_PARAM;
      } else {
        m_inf_in_param.type_anchor = PARAMETR3;
        m_inf_in_param.number_in_param = THREE_PARAM;
      }
      m_log << ("Ip устройства " + m_config_calibr.ip_adress);
      m_log << ("Порт устройства "+IntToStr(m_config_calibr.port));
      m_mxnet.set_dest_port(m_config_calibr.port);
      mxip_t ip = {{192, 168, 0, 38}};
      cstr_to_mxip(ip, m_config_calibr.ip_adress.c_str());
      m_mxnet.set_dest_ip(ip);
      type_meas_t type_meas = tm_volt_dc;
      IRS_ASSERT(
        str_to_type_meas(m_config_calibr.type_meas.c_str(), type_meas));
      set_type_meas(type_meas);
      set_deley_volt_meas(m_config_calibr.delay_meas);
      m_default_param_cur_cell.col_value.value =
        m_config_calibr.in_parametr1.default_val;
      m_default_param_cur_cell.col_value.init = true;
      m_default_param_cur_cell.row_value.value =
        m_config_calibr.in_parametr2.default_val;
      m_default_param_cur_cell.row_value.init = true;
      m_default_param_cur_cell.top_value.value =
        m_config_calibr.in_parametr3.default_val;
      m_default_param_cur_cell.top_value.init = true;
      //m_on_mismatch_state = m_config_calibr.mismatch_mode;
      //mismatch_mode_change_stat(m_on_mismatch_state);
      m_cur_config_device = extract_short_filename(
        ExtractFileName(mv_list_config_calibr[index_file]));
      mp_active_table->set_inf_in_param(m_inf_in_param);
      // загрузка последнего активного файла
      AnsiString file_namedir = m_config_calibr.active_filename;
      if(FileExists(file_namedir)){
        mp_active_table->set_file_namedir(file_namedir);
        mp_active_table->load_table_from_file(file_namedir.c_str());
      }else{
        mp_active_table->clear_table_def();
      }
      Caption = m_prog_name+AnsiString(" - ")+file_namedir;

      out_param_control_config_t out_param_ctrl_cfg =
        m_config_calibr.out_param_control_config;
      if (out_param_ctrl_cfg.enabled) {
        m_out_param_stability_control.set_stability_min_time(
          out_param_ctrl_cfg.time);
      }
      OutParamControlGroupBox->Visible = out_param_ctrl_cfg.enabled;
      temperature_control_config_t temperature_ctrl_cft =
        m_config_calibr.temperature_control;
      if (temperature_ctrl_cft.enabled) {
        m_temperature_stability_control.set_reference(
          temperature_ctrl_cft.reference);
        m_temperature_stability_control.set_diviation(
          temperature_ctrl_cft.difference);      
        ReferenceTemperatureLabeledEdit->Text =
          FloatToStr(temperature_ctrl_cft.reference);
        DifferenceTemperatureLabeledEdit->Text =
          FloatToStr(temperature_ctrl_cft.difference);
      }
      TemperatureControlGroupBox->Visible = temperature_ctrl_cft.enabled;   
      m_load_conf_calibr_device_success = true;
      m_on_reset_functional_bits = true;
      m_log<<"Загрузка конфигурации калибровки успешно завершена.";

      // загрузка конфигурации опорного канала
      if (m_config_calibr.reference_channel.enabled) {
        mp_mxnet_ref_channel.reset(new mxnetc(MXIFA_MXNETC_2));
        mp_mxnet_data_ref_channel.reset(new irs::mxdata_to_mxnet_t(
          mp_mxnet_ref_channel.get(), MS_TO_CNT(2000)));

        m_config_calibr_ref_channel = m_config_calibr;
        m_config_calibr_ref_channel.ip_adress =
          m_config_calibr_ref_channel.reference_channel.ip_adress;
        m_config_calibr_ref_channel.port =
          m_config_calibr_ref_channel.reference_channel.port;
        m_config_calibr_ref_channel.reference_channel.enabled = false;
        mp_mxnet_ref_channel->set_dest_port(m_config_calibr_ref_channel.port);
        mxip_t ip = {{192, 168, 0, 38}};
        cstr_to_mxip(ip, m_config_calibr_ref_channel.ip_adress.c_str());
        mp_mxnet_ref_channel->set_dest_ip(ip);
      }

    }else{
      m_log << "Загрузка конфигурации прервана.";
      m_log << ("Файл \""+ filename_conf +"\" отсутствует"+".");
      MessageDlg("Файл \""+ filename_conf +"\" отсутствует"+".",
        mtError,
        TMsgDlgButtons()<<mbOK,
        0);

    }
  }
}

void TDataHandlingF::calculation_koef(irs::matrix_t<cell_t> a_matrix)
{ 
  const int size_of_ident = sizeof(irs_u32);
  const int size_of_size_x = sizeof(irs_u32);
  const int size_of_size_y = sizeof(irs_u32);
  lang_type_t x_elem_type = m_config_calibr.in_parametr1.unit;
  lang_type_t y_elem_type = m_config_calibr.in_parametr2.unit;
  lang_type_t z_elem_type = m_config_calibr.out_parametr.unit;


  mv_col_optimal_data.clear();
  mv_row_optimal_data.clear();
  mv_coef_data.clear();


  int x_elem_size = size_type(x_elem_type);
  int y_elem_size = size_type(y_elem_type);
  int z_elem_size = size_type(z_elem_type);


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
  if(!m_bad_cells) {
    m_need_size_memory = size_of_ident + size_of_size_x + size_of_size_y +
    x_elem_size*mv_col_optimal_data.size()+
    y_elem_size*mv_row_optimal_data.size()+
    z_elem_size*mv_coef_data.size();
  }else{
    m_need_size_memory = 0;
  }
}

void TDataHandlingF::tick()
{
  m_on_block_reconfiguration = m_on_auto_meas;
  if(m_load_conf_calibr_device_success){
    for (int i = 0; i < 10; i++) {
      m_mxnet.tick();
    }
    //mp_eeprom->tick();
    m_mxnet_data.tick();
    if (m_config_calibr.reference_channel.enabled) {
      for (int i = 0; i < 10; i++) {
        mp_mxnet_ref_channel->tick();
      }
      mp_mxnet_data_ref_channel->tick();
    }
    #ifdef debug_irsdigint
    m_on_out_data = false;
    #endif //debug_irsdigint
    if(m_mxnet_data.connected()) {
      WorkTimeDeviceLE->Text = (AnsiString)m_data_map.work_time;
      if (m_config_calibr.out_param_control_config.enabled) {
        if (m_on_auto_meas) {
          double out_param = m_data_map.y_out;
          coord_cell_t coord_cur_cell =
            m_manager_traffic_cell.get_coord_cell();
          param_cur_cell_t param_cur_cell =
            mp_active_table->get_param_cell(
            coord_cur_cell.col, coord_cur_cell.row);
          double difference = get_anchor_in_param(param_cur_cell)*
            m_config_calibr.out_param_control_config.max_relative_difference;
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
            m_config_calibr.out_param_control_config.time -
            m_out_param_stability_control.get_stable_state_time());
          RemainingTimeForStableState->Text =
            IntToStr(static_cast<int>(remaining_time));
        }
      }
      if (m_config_calibr.temperature_control.enabled) {
        double temperature = m_data_map.temperature;
        bool temperature_allowable = fabs(temperature -
          m_config_calibr.temperature_control.reference) <=
          m_config_calibr.temperature_control.difference;
        m_temperature_stability_control.set_current(temperature);
        CurrentTemperatureLabeledEdit->Text = FloatToStr(temperature);
        if (temperature_allowable) {
          CurrentTemperatureLabeledEdit->Font->Color = clBlue;
        } else {
          CurrentTemperatureLabeledEdit->Font->Color = clRed;
        }
      }
      if (m_data_map.operating_duty_bit == 1) {
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
        if(m_mxnet_data.connected()){
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
        if(!m_mxnet_data.connected())
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
          m_data_map.x_in =
            m_param_cur_cell.col_value.value;
          m_data_map.y_in =
            m_param_cur_cell.row_value.value;
          if (m_config_calibr.reference_channel.enabled) {
             mp_data_map_ref_channel->x_in =
              m_param_cur_cell.col_value.value;
             mp_data_map_ref_channel->y_in =
              m_param_cur_cell.row_value.value;
          }
          if (m_inf_in_param.number_in_param == THREE_PARAM) {
            m_data_map.q_in = m_param_cur_cell.top_value.value;
            if (m_config_calibr.reference_channel.enabled) {
              mp_data_map_ref_channel->q_in = m_param_cur_cell.top_value.value;
            }
          }
        }
        m_on_out_data = false;
        status_connect = CONNECT;
      } break;
    }
    switch(m_status_options)
    {
      case OFF_PROCESSING:{
        m_status_options = OptionsF->status_options();
      } break;
      case ON_UPDAT:{
        m_options_mnk = OptionsF->read_options_mnk();
        m_options_correct = OptionsF->read_options_correct();
        m_options_coef = OptionsF->read_options_coef();
        //сохранение в файл
        //...
        OptionsF->reset_status_options();
        m_status_options = OFF_PROCESSING;
      } break;
      case ON_READ:{
        OptionsF->write_options_mnk(m_options_mnk);
        OptionsF->write_options_correct(m_options_correct);
        OptionsF->write_options_coef(m_options_coef);
        OptionsF->reset_status_options();
        m_status_options = OFF_PROCESSING;
      } break;
    }
  }//if(m_load_conf_calibr_device_success)

  if (m_on_connect_mxnet_data) {
    switch(status_connect_eeprom){
      case sce_off: {
        if(m_on_write_data_eeprom) {
          if(m_bad_cells){
            status_connect_eeprom = sce_reset;
            m_log << "Произошел сбой при расчете коэффициентов. "
            "Запись прервана";
          } else if(
            irs_i32(m_max_size_correct -
              m_need_size_memory) < 0){
            status_connect_eeprom = sce_reset;
            m_log << "Нехватает памяти для прошивки";
            m_log << ("Обьем данных "+IntToStr(m_need_size_memory)+" байт");
            m_log << ("Доступный размер памяти "+
              IntToStr(m_max_size_correct)+" байт");
          } else if (m_need_size_memory > 0) {
            m_log << "Происходит запись в еепром.";
            m_log << ("Индек смещения " +
              IntToStr(m_index_pos_offset_eeprom));
            m_log << ("Обьем данных "+IntToStr(m_need_size_memory)+" байт");
            m_log << ("Доступный размер памяти "+
              IntToStr(m_max_size_correct)+" байт");
            status_connect_eeprom = sce_create_interface_eeprom;
          } else {
            m_log << "Нет данных для записи.";
            status_connect_eeprom = sce_reset;
          }
        } else if (m_on_verification_data_eeprom) {
          if(m_bad_cells){
            status_connect_eeprom = sce_reset;
            m_log << "Произошел сбой при расчете коэффициентов. "
              "Верификация данных прервана";
          }else if(
            irs_i32(m_max_size_correct -
              m_need_size_memory) < 0){
            status_connect_eeprom = sce_reset;
            m_log << "Обьем данных превышает"
            "допустимый обьем памяти.";
            m_log << ("Обьем данных " + IntToStr(m_need_size_memory) + " байт");
            m_log << ("Доступный размер памяти " +
            IntToStr(m_max_size_correct) + " байт");
          }else if (m_need_size_memory > 0) {
            m_log << "Началась верификация данных.";
            m_log << ("Индек смещения " +
              IntToStr(m_index_pos_offset_eeprom));
            m_log << ("Обьем данных " + IntToStr(m_need_size_memory) + " байт");
            m_log << ("Доступный размер памяти " +
            IntToStr(m_max_size_correct) + " байт");
            status_connect_eeprom = sce_create_interface_eeprom;
          } else {
            m_log << "Нет данных для верификации.";
            status_connect_eeprom = sce_reset;
          }
        }     
      } break;
      case sce_create_interface_eeprom: {
        mp_eeprom.reset(new irs::funnel_client_t(
          &m_mxnet_data,
          m_config_calibr.index_pos_eeprom,
          MS_TO_CNT(200),
          m_index_pos_offset_eeprom,
          m_need_size_memory,
          irs::fcm_reduce));
        status_connect_eeprom = sce_wait_connect_eeprom;
      } break;
      case sce_wait_connect_eeprom: {
        if (mp_eeprom->connected()) {
          correct_map.connect(
            mp_eeprom.get(), 0, m_config_calibr);
          m_on_connect_eeprom = true;
          status_connect_eeprom = sce_set_param_eeprom;
        }
        mp_eeprom->tick();
      } break;
      case sce_set_param_eeprom: {
        correct_map.connect(
          mp_eeprom.get(), 0, m_config_calibr);
        correct_map.map_id = 1;
        correct_map.x_count = mv_col_optimal_data.size();
        correct_map.y_count = mv_row_optimal_data.size();
        correct_map.connect(
          mp_eeprom.get(), 0, m_config_calibr);
        if (m_on_write_data_eeprom) {
          status_connect_eeprom = sce_write_eeprom;
        } else if(m_on_verification_data_eeprom){
          mp_eeprom->reset_stat_read_complete();
          m_exec_progress.show();
          m_exec_progress.p_comment->Caption = "Процесс верификации данных.";
          m_exec_progress.p_percent_progress->Caption = "0%";
          m_exec_progress.p_progress_bar->Position = 0;
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
            mp_local_data.get(), 0, m_config_calibr);
          m_correct_map_local.map_id = 1;
          m_correct_map_local.x_count = mv_col_optimal_data.size();
          m_correct_map_local.y_count = mv_row_optimal_data.size();
          m_correct_map_local.connect(
            mp_local_data.get(), 0, m_config_calibr);
          int vcol_opt_size = mv_col_optimal_data.size();
          for(int i = 0; i < vcol_opt_size; i++){
            m_correct_map_local.x_points[i] =
              mv_col_optimal_data[i]*m_config_calibr.in_parametr1.koef;
          }
          int vrow_opt_size = mv_row_optimal_data.size();
          for(int i = 0; i < vrow_opt_size; i++){
            m_correct_map_local.y_points[i] =
              mv_row_optimal_data[i]*m_config_calibr.in_parametr2.koef;
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
          m_exec_progress.p_progress_bar->Position = percent;
        }
      } break;
      case sce_verification_eeprom: {
        bool data_equal = true;
        if (correct_map.map_id != m_correct_map_local.map_id) {
          data_equal = false;
        } else if (correct_map.x_count != m_correct_map_local.x_count) {
          data_equal = false;
        } else if (correct_map.y_count != m_correct_map_local.y_count) {
          data_equal = false;
        }
        if (data_equal) {
          int x_points_cm_size = correct_map.x_points.size();
          int x_points_cml_size = m_correct_map_local.x_points.size();
          if (x_points_cm_size != x_points_cml_size) {
            data_equal = false;
          } else {
            for (int i = 0; i < x_points_cm_size; i++) {
              if (correct_map.x_points[i] !=
                m_correct_map_local.x_points[i]) {
                data_equal = false;
                break;
              }
            }
          }
        }
        if (data_equal) {
          int y_points_cm_size = correct_map.y_points.size();
          int y_points_cml_size = m_correct_map_local.y_points.size();

          if (y_points_cm_size != y_points_cml_size) {
            data_equal = false;
          } else {
            for (int i = 0; i < y_points_cm_size; i++) {
              if (correct_map.y_points[i] !=
                m_correct_map_local.y_points[i]) {
                data_equal = false;
                break;
              }
            }
          }
        }
        if (data_equal) {
          int koef_array_cm_size = correct_map.koef_array.size();
          int koef_array_cml_size = m_correct_map_local.koef_array.size();
          if (koef_array_cm_size != koef_array_cml_size) {
            data_equal = false;
          } else {
            for (int i = 0; i < koef_array_cm_size; i++) {
              if (correct_map.koef_array[i] !=
                m_correct_map_local.koef_array[i]) {
                data_equal = false;
                break;
              }
            }
          }
        }
        if (data_equal) {
          m_log << "Верификация данных завершена.";
          m_log << "Различий не выявлено.";
        } else {
          m_log << "Верификация данных завершена.";
          m_log << "Найдены различия в данных.";
        }
        status_connect_eeprom = sce_reset;
        //status_connect_eeprom = sce_off;
      } break;
      case sce_write_eeprom: {
        int vcol_opt_size = mv_col_optimal_data.size();
        for(int i = 0; i < vcol_opt_size; i++){
          correct_map.x_points[i] =
            mv_col_optimal_data[i]*m_config_calibr.in_parametr1.koef;
        }
        int vrow_opt_size = mv_row_optimal_data.size();
        for(int i = 0; i < vrow_opt_size; i++){
          correct_map.y_points[i] =
            mv_row_optimal_data[i]*m_config_calibr.in_parametr2.koef;
        }
        int vcoef_data_size = mv_coef_data.size();
        for(int i = 0; i < vcoef_data_size; i++)
          correct_map.koef_array[i] = mv_coef_data[i];

        m_exec_progress.show();
        m_exec_progress.p_comment->Caption = "Процесс прошивки.";
        m_exec_progress.p_percent_progress->Caption = "0%";
        m_exec_progress.p_progress_bar->Position = 0;
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
          m_exec_progress.p_progress_bar->Position = percent;
        } else {
          m_exec_progress.hide();
          m_exec_progress.clear();
          //m_on_write_data_eeprom = false;
          //m_on_verification_data_eeprom = true;
          status_connect_eeprom = sce_reset;
          m_log << "Прошивка данных завершена.";
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
  const WORD a_key,
  const TShiftState Shift)
{ 
  if (a_key == VK_RETURN) {
    if (m_cur_cell_table1.init){
      irs::string latest_entry_previous_cell_str =
        RawDataStringGrid->Cells
        [m_cur_cell_table1.col][m_cur_cell_table1.row].c_str();
      if(m_cur_cell_table1.value_str != latest_entry_previous_cell_str){
        mp_active_table->cur_cell_in_display();
      }
      //mp_active_table->cell_out_display_variable_precision(
        //m_cur_cell_table1.col, m_cur_cell_table1.row);
      m_cur_cell_table1.init = false;
      m_on_get_edit_text_event_sg = false;


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
    }
  } else {
    m_on_key_char_down = true;
  }
}
//---------------------------------------------------------------------------

void TDataHandlingF::process_volt_meas()
{
  if(m_on_process_auto_meas_active_cell == true){
    if (m_on_auto_meas == true) {
      if(m_status_process_meas != spm_jump_next_elem){
        m_on_process_auto_meas_active_cell = false;
      }
    }else{
      m_on_start_new_auto_meas = true;
    }
  }
  if(m_on_stop_process_avto_volt_meas == true){
    reset_stat_stop_process_avto_volt_meas();
    m_on_auto_meas = false;
    //config_button_stop_avto_volt_meas();
    m_status_process_meas = spm_reset;
    m_log << "Стоп.";
  }
  if (m_on_auto_meas) {
    config_button_start_avto_volt_meas();
    m_timer_delay_control_error_bit.check();
    if (m_data_map.error_bit == 1 &&
      m_timer_delay_control_error_bit.stopped()) {
      if (m_cur_count_reset_over_bit < m_config_calibr.count_reset_over_bit) {
        m_cur_count_reset_over_bit++;
        m_data_map.reset_over_bit = 1;
        m_on_process_auto_meas_active_cell = true;
        if (m_mode_program == mode_prog_single_channel) {
          m_status_process_meas = spm_set_range;
        } else {
          m_status_process_meas =
            spm_wait_ext_trig_set_range;
          m_log << "Ожидание внешнего запуска установки диапазона измерений.";
        }
        //m_status_process_meas = spm_jump_next_elem;
        m_timer_delay_control_error_bit.set(m_delay_control_error_bit);
        m_timer_delay_next_cell.set(m_delay_next_cell);
        m_log << "Сброс ошибки.";
        m_log << ("Ждем " + FloatToStr(
          (CNT_TO_DBLTIME(m_delay_next_cell))) +
          " секунд перед продолжением измерений.");
      } else {
        m_timer_delay_control_error_bit.set(m_delay_control_error_bit);
        m_log << "Прибор не можнет выйти на рабочий режим.";
        m_log << "Автоматическое измерение завершилось с ошибкой.";
        m_status_process_meas = spm_reset;
      }
    }
  }
  switch(m_status_process_meas)
  {
    case spm_off_process: {
      if (m_on_start_new_auto_meas == true) {
        m_count_point_meas = 0;
        m_previous_count_point_meas = 0;
        set_connect_multimetr();
        reset_start_new_avto_volt_meas_stat();
        m_on_auto_meas = true;
        m_manager_traffic_cell.set_min_col(1);
        m_manager_traffic_cell.set_min_row(1);
        illegal_cells_t illegal_cells =
          mp_active_table->get_illegal_cells();
        m_manager_traffic_cell.set_illegal_cell(illegal_cells);
        m_cur_count_reset_over_bit = 0;
        set_value_working_extra_params();
        set_value_working_extra_bits();
        if (m_type_jump_next_elem == HORIZONTAL_DOWN ||
          m_type_jump_next_elem == HORIZONTAL_DOWN_SMOOTH ||
          m_type_jump_next_elem == VERTICAL_FORWARD ||
          m_type_jump_next_elem == VERTICAL_FORWARD_SMOOTH){
          m_manager_traffic_cell.set_current_cell(
            m_start_elem.col, m_start_elem.row);
        } else {
          m_manager_traffic_cell.set_current_cell(
            m_start_inverse_elem.col, m_start_inverse_elem.row);
        }
        if (m_on_process_auto_meas_active_cell) {
          m_manager_traffic_cell.set_current_cell(
            mp_active_table->get_col_displ(),
            mp_active_table->get_row_displ());
          m_on_process_auto_meas_active_cell = false;
          m_log << "Запуск автоматического измерения с активной ячейки.";
        } else {
          coord_cell_t coord_cur_cell =
            m_manager_traffic_cell.get_coord_cell();
          mp_active_table->set_col_displ(coord_cur_cell.col);
          mp_active_table->set_row_displ(coord_cur_cell.row);
          m_log << "Запуск автоматического измерения.";
        }
        if (m_mode_program == mode_prog_single_channel) {
          m_status_process_meas = spm_set_range;
        } else {
          m_status_process_meas =
            spm_wait_ext_trig_set_range;
          m_log << "Ожидание внешнего запуска установки диапазона измерений.";
        }
        m_cell_count_end = m_manager_traffic_cell.get_cell_count_end();
        m_cell_count_end++;
        m_time_meas.start();
        m_exec_progress.show();
        m_exec_progress.p_comment->Caption = "Процесс калибровки.";
        m_exec_progress.p_percent_progress->Caption = "0%";
        m_exec_progress.p_progress_bar->Position = 0;
      }
    } break;
    case spm_jump_next_elem:{
      m_timer_delay_next_cell.check();
      if(m_timer_delay_next_cell.stopped()){
        bool next_elem_successfully = false;
        next_elem_successfully = m_manager_traffic_cell.next_cell();
        if (next_elem_successfully == false) {
          m_status_process_meas = spm_reset;
          m_log << "Автоматическое измерение успешно завершено.";
        } else {
          m_log << "Переход к следующей точке измерения.";
          coord_cell_t coord_cur_cell =
            m_manager_traffic_cell.get_coord_cell();
          mp_active_table->set_col_displ(coord_cur_cell.col);
          mp_active_table->set_row_displ(coord_cur_cell.row);
          if (m_mode_program == mode_prog_single_channel) {
            m_status_process_meas = spm_set_range;
          } else {
            m_status_process_meas =
              spm_wait_ext_trig_set_range;
            m_log << "Ожидание внешнего запуска установки диапазона измерений.";
          }
        }
      }
    } break;
    case spm_wait_ext_trig_set_range: {
      if (m_on_external) {
        m_on_external = false;
        m_status_process_meas = spm_set_range;
      }
    } break;
    case spm_set_range: {
      coord_cell_t coord_cur_cell =
        m_manager_traffic_cell.get_coord_cell();
      param_cur_cell_t param_cur_cell =
        mp_active_table->get_param_cell(
          coord_cur_cell.col, coord_cur_cell.row);
      const double range = set_range(param_cur_cell);
      const double reference = get_anchor_in_param(param_cur_cell);
      m_out_param_stability_control.set_reference(reference);
      m_out_param_stability_control.set_diviation(reference*
        m_config_calibr.out_param_control_config.max_relative_difference);
      m_status_process_meas = spm_wait_set_range;
      ostringstream msg;
      msg << "Установка диапазона измерения: " << range;
      m_log << irs::str_conv<AnsiString>(msg.str());
    } break;
    case spm_wait_set_range: {
      status_range_t status_range = get_status_range();
      if (status_range == range_stat_success) {   
        m_status_process_meas = spm_mode_setting;
        m_log << "Установка диапазона измерения завершена.";
      }
    } break;
    case spm_mode_setting: {
      coord_cell_t coord_cur_cell =
        m_manager_traffic_cell.get_coord_cell();
      param_cur_cell_t param_cur_cell =
        mp_active_table->get_param_cell(
          coord_cur_cell.col, coord_cur_cell.row);
      out_param(param_cur_cell);
      m_log << ("Ждем " + FloatToStr(
        (CNT_TO_DBLTIME(m_delay_start_control_reg))) +
        " секунд перед проверкой рабочего режима.");
      m_timer_delay_control.set(m_delay_start_control_reg);
      m_status_process_meas = spm_wait_mode_setting;
    } break;
    //установка режима
    case spm_wait_mode_setting: {
      #ifdef debug_datahanding
        m_on_reg_ready = true;
      #endif
      if (m_timer_delay_control.check()) {
        if (m_config_calibr.temperature_control.enabled) {
          m_log<<"Ждем установления рабочего режима и температуры.";
        } else {
          m_log<<"Ждем установления рабочего режима.";
        }
      }
      if ((m_timer_delay_control.stopped() == true)) {
        if (m_on_out_data == false) {
          bool all_ready = true;
          if (m_config_calibr.temperature_control.enabled) {
            all_ready = all_ready &&
              m_temperature_stability_control.stable_state();
            m_temperature_stable_min_time.start();
          }
          if (m_config_calibr.out_param_control_config.enabled) {
            all_ready = all_ready &&
              m_out_param_stability_control.stable_state();
            m_out_param_stable_min_time.start();
          }
          all_ready = all_ready && m_on_reg_ready;
          if (all_ready) {
            m_log<<"Рабочий режим установлен";
            if (m_mode_program == mode_prog_single_channel) {
              m_timer_delay_operating_duty.set(m_delay_operating_duty);
              m_log << ("Ждем " + FloatToStr(
                CNT_TO_DBLTIME(m_delay_operating_duty)) +
                " секунд.");
              m_status_process_meas = spm_control_wait_mode_setting;
            } else {
              m_log << "Ожидание внешнего запуска контрольного "
                "установления рабочего режима.";
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
        m_timer_delay_operating_duty.set(m_delay_operating_duty);
        m_log << ("Ждем " + FloatToStr(
          (CNT_TO_DBLTIME(m_delay_operating_duty))) +
          " секунд.");
        m_status_process_meas = spm_control_wait_mode_setting;
      }
    } break;
    // режим контрольного ожидания установления рабочего режима
    case spm_control_wait_mode_setting: {
      m_timer_delay_operating_duty.check();
      if (m_config_calibr.temperature_control.enabled) {
        if (m_temperature_stability_control.get_stable_state_time() <
          m_temperature_stable_min_time.get()) {
          m_log<<"Температура вышла за допустимые значения.";
          m_status_process_meas = spm_wait_mode_setting;
        }
        if (m_out_param_stability_control.get_stable_state_time() <
          m_out_param_stable_min_time.get()) {
          m_log<<"Значение выходного параметра вышло за допустимые значения.";
          m_status_process_meas = spm_wait_mode_setting;
        }
      }
      if (m_status_process_meas == spm_control_wait_mode_setting) {
        if (m_on_reg_ready) {
          if (m_timer_delay_operating_duty.stopped()) {
            m_log<<"Рабочий режим подтвержден.";
            if (m_mode_program == mode_prog_single_channel) {
              m_status_process_meas = spm_execute_meas;
            } else {
              m_status_process_meas = spm_wait_external_trig_meas;
              m_log<<"Ожидание внешнего запуска измерения.";
            }
          }
        } else {
          m_log << "Рабочий режим не подтвержден.";
          m_log << ("Ждем " + FloatToStr(
            (CNT_TO_DBLTIME(m_delay_start_control_reg))) +
            " секунд перед проверкой рабочего режима.");
          m_timer_delay_control.set(m_delay_start_control_reg);
          m_status_process_meas = spm_wait_mode_setting;
        }
      }
    } break;
    // ожидание внешнего внешнего запуска измерения
    case spm_wait_external_trig_meas: {
      if (m_on_external) {
        m_status_process_meas = spm_execute_meas;
        m_on_external = false;
      }
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
        if(meas_stat == meas_status_success){
          if (m_mode_program == mode_prog_single_channel) {
            m_status_process_meas = spm_processing_data;
          } else {
            m_status_process_meas = spm_wait_external_trig_processing_data;
          }
        }
        else if(meas_stat == meas_status_error){
          m_status_process_meas = spm_reset;
        }
    } break;
    case spm_wait_external_trig_processing_data: {
      if (m_on_external) {
        meas_status_t meas_stat = meas_status();
        if(meas_stat == meas_status_success){
          m_status_process_meas = spm_processing_data;
        }
        else if(meas_stat == meas_status_error){
          m_status_process_meas = spm_reset;
          m_log << "Ошибка измерения.";
          m_log << "Автоматическое измерение завершилось с ошибкой.";
        }
        m_on_external = false;
      }
    } break;
    case spm_processing_data: {
      int index_multimetr = PatternOfMeasuringInstrumentCB->ItemIndex;
      AnsiString cur_multim =
        PatternOfMeasuringInstrumentCB->Items->Strings[index_multimetr];
      if (str_to_type_multimeter(cur_multim.c_str()) != tmul_none_multimeter) {
        double calc_value = calc_meas_value(
          m_value_meas_multimetr, y_out, m_param_cur_cell);
        cell_t cell(calc_value, true);
        coord_cell_t coord_cur_cell =
          m_manager_traffic_cell.get_coord_cell();
        mp_active_table->set_cell(cell, coord_cur_cell.col, coord_cur_cell.row);
        //mp_active_table->cell_out_display_variable_precision(
          //coord_cur_cell.col, coord_cur_cell.row);
      }
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
      m_value_meas.disconnect_multimetr();
      m_param_cur_cell = m_default_param_cur_cell;
      m_on_out_data = true;
      m_on_auto_meas = false;
      m_on_process_auto_meas_active_cell = false;
      config_button_stop_avto_volt_meas();
      m_status_process_meas = spm_off_process;
      TimeMeasLE->Text = String();
      IntervalTimeMeasLE->Text = String();
      CurrentOutParamLabeledEdit->Text = String();
      ReferenceOutParamLabeledEdit->Text = String();
      AbsoluteDiffOutParamLabeledEdit->Text = String();
      RemainingTimeForStableState->Text = String();
      m_exec_progress.hide();
      m_exec_progress.clear();
    } break;
  }
  if (m_on_auto_meas) {
    double time_meas_sec = m_time_meas.get();
    irs::millisecond_t time_meas_ms =
      static_cast<irs::millisecond_t>(time_meas_sec*1000);
    const bool show_ms = false;
    irs::string time_meas_str =  irs::ms_to_strtime(time_meas_ms, show_ms);
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
          // Процент выполнения калибровки
          int percent = 100*m_count_point_meas/
            (m_cell_count_end+m_count_point_meas);
          m_exec_progress.p_percent_progress->Caption = IntToStr(percent) + "%";
          m_exec_progress.p_progress_bar->Position = percent;
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
      irs::string time_interval_end_meas_str =
        irs::ms_to_strtime(time_interval_end_meas_ms, show_ms);
      IntervalTimeMeasLE->Text = time_interval_end_meas_str.c_str();
    } else {
      IntervalTimeMeasLE->Text = "--:--:--";
    }
  }
}
//---------------------------------------------------------------------------
void TDataHandlingF::config_button_start_avto_volt_meas()
{
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
  //EditConfigButton->Enabled = false;
}
void TDataHandlingF::config_button_stop_avto_volt_meas()
{
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
}

//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::RawDataStringGridSelectCell(
      TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
  if(m_cur_cell_table1.init){
    irs::string latest_entry_previous_cell_str =
      RawDataStringGrid->Cells
      [m_cur_cell_table1.col][m_cur_cell_table1.row].c_str();
    if(m_cur_cell_table1.value_str != latest_entry_previous_cell_str){
      mp_active_table->cur_cell_in_display();
      RawDataStringGrid->Repaint();
    }
    //mp_active_table->cell_out_display_variable_precision(
      //m_cur_cell_table1.col, m_cur_cell_table1.row);
    m_cur_cell_table1.init = false;
    m_on_get_edit_text_event_sg = false;
  }
  processing_select_cell(RawDataStringGrid, ACol, ARow, CanSelect);
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
  if (m_on_get_edit_text_event_sg){
    m_on_get_edit_text_event_sg = false;
    if (!m_cur_cell_table1.init) {
      m_cur_cell_table1.init = true;
      if (!m_on_key_char_down) {
        m_cur_cell_table1.value_str =
          mp_active_table->get_cell_value_str_table_data(
          m_cur_cell_table1.col, m_cur_cell_table1.row);
        mp_active_table->cell_out_display(
          m_cur_cell_table1.col, m_cur_cell_table1.row);
      } else {
        m_on_key_char_down = false;
      }
    }
  }
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
  const AnsiString& a_str_type_jump_next_elem)
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
  double out_value = a_value_meas*
    m_config_calibr.out_parametr.koef_shunt/out_param_value;
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
  return out_value;
}

double TDataHandlingF::set_range(const param_cur_cell_t& a_param_cur_cell)
{
  const double koef = m_config_calibr.meas_range_koef;
  double range = get_anchor_in_param(a_param_cur_cell)*koef;
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
void TDataHandlingF::set_type_meas(type_meas_t a_type_meas)
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
}
//---------------------------------------------------------------------------
void TDataHandlingF::special_style_cells(TStringGrid* a_table,
  int a_col,
  int a_row,
  TRect &a_rect)
{
  TStringGrid* table = a_table;
  coord3d_t coord_cell =
    mp_active_table->get_coord_cell_table(a_col, a_row);
  int row_table = coord_cell.y;
  int col_table = coord_cell.x;
  bool select_cell_in_x = (col_table > 0) && (row_table == 0);
  bool select_cell_in_y = (col_table == 0) && (row_table > 0);
  bool select_cell_in_z = (col_table == 0) && (row_table == 0);
  AnsiString value = mp_active_table->get_cell_display_variable_precision(
    a_col, a_row).c_str();
  if((!select_cell_in_x) && (!select_cell_in_y) && (!select_cell_in_z)){
    if((a_col == table->Col) && (a_row == table->Row)){
      //цвет фона
      table->Canvas->Brush->Color = clMoneyGreen;
      //цвет текста
      table->Canvas->Font->Color = clBlack;
      //cтиль текста (жирный)
      //RawDataStringGrid->Canvas->Font->Style << fsBold;
      //заливаем фон
      table->Canvas->FillRect(a_rect);
      //красим текст
      table->Canvas->TextOutA(
        a_rect.Left, a_rect.Top, value/*table->Cells[a_col][a_row]*/);
    } else {
      table->Canvas->FillRect(a_rect);
      table->Canvas->TextOutA(a_rect.Left, a_rect.Top, value);
    }
  } else {
    //цвет фона
    table->Canvas->Brush->Color = clBtnFace;
    //цвет текста
    table->Canvas->Font->Color = clBlack;
    //заливаем фон
    table->Canvas->FillRect(a_rect);
    //красим текст
    table->Canvas->TextOutA(
      a_rect.Left, a_rect.Top, value/*table->Cells[a_col][a_row]*/);
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::FormDataHandingTimer1Timer(TObject *Sender)
{
  try{
    tick();
    tick2();
  } catch (Exception &exception) {
    FormDataHandingTimer1->Enabled = false;
    Application->ShowException(&exception);
    exit(1);
  } catch (...) {
    FormDataHandingTimer1->Enabled = false;
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
  //config_button_start_avto_volt_meas();
  m_on_start_new_auto_meas = true;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::StopVoltMeasActionExecute(TObject *Sender)
{
  //config_button_stop_avto_volt_meas();
  m_on_stop_process_avto_volt_meas = true;
}
//---------------------------------------------------------------------------



void __fastcall TDataHandlingF::StartAutoVoltMeasActiveCellsActionExecute(
      TObject *Sender)
{
  //config_button_start_avto_volt_meas();
  m_on_process_auto_meas_active_cell = true;
}
//---------------------------------------------------------------------------


void __fastcall TDataHandlingF::FileSaveExecute(TObject *Sender)
{
  AnsiString file_namedir = "";
  file_namedir = mp_active_table->get_file_namedir();
  if(file_namedir != ""){
    mp_active_table->save_table_to_file(file_namedir.c_str());
    mp_active_table->save_table_to_m_file(file_namedir.c_str());
  }else{
    FileSaveAs->Execute();
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileSaveAsAccept(TObject *Sender)
{
  AnsiString file_namedir = "";
  file_namedir = FileSaveAs->Dialog->FileName;
  mp_active_table->set_file_namedir(file_namedir);
  mp_active_table->save_table_to_file(file_namedir.c_str());
  m_config_calibr.active_filename = file_namedir;
  Caption = m_prog_name + AnsiString(" - ") + file_namedir;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileSaveAsBeforeExecute(TObject *Sender)
{   
  AnsiString file_namedir = "";
  file_namedir = mp_active_table->get_file_namedir();
  if(file_namedir == ""){
    FileSaveAs->Dialog->FileName = "Data.dgi";
  }
  else{
    FileSaveAs->Dialog->FileName = file_namedir;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileReOpenExecute(TObject *Sender)
{
  AnsiString file_namedir = "";
  file_namedir = mp_active_table->get_file_namedir();
  if(file_namedir != ""){
    mp_active_table->load_table_from_file(file_namedir.c_str());
  }else{
    FileOpen->Execute();
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::FileOpenAccept(TObject *Sender)
{
  AnsiString file_namedir = "";
  file_namedir = FileOpen->Dialog->FileName;
  mp_active_table->set_file_namedir(file_namedir);
  mp_active_table->load_table_from_file(file_namedir.c_str());
  m_config_calibr.active_filename = file_namedir;
  Caption = m_prog_name+AnsiString(" - ")+file_namedir;
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
  set_type_meas(tm_volt_dc);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetVoltACMeasActionExecute(TObject *Sender)
{
  set_type_meas(tm_volt_ac);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetCurrentDCMeasActionExecute(
      TObject *Sender)
{
  set_type_meas(tm_current_dc);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetResistance2xMeasActionExecute(TObject *Sender)
{
  set_type_meas(tm_current_ac);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::SetResistance4xMeasActionExecute(
      TObject *Sender)
{
  set_type_meas(tm_resistance_2x);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::SetCurrentACMeasActionExecute(
      TObject *Sender)
{
  set_type_meas(tm_resistance_4x);
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::SetFrequencyMeasActionExecute(
      TObject *Sender)
{
  set_type_meas(tm_frequency);
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
      TObject *Sender, int ACol, int ARow, AnsiString &Value)
{
  m_on_get_edit_text_event_sg = true;
  m_cur_cell_table1.col = ACol;
  m_cur_cell_table1.row = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::CreateConfigButtonClick(TObject *Sender)
{
  if (m_cur_filename_conf_calibr_device != "") {
    if (m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str())) {
      m_log << "Текущая конфигурация успешно сохранена.";
    }
  }
  NewConfigF->set_path_program(m_path_prog);
  NewConfigF->set_config_def();
  if(NewConfigF->Visible == false){
    int button_result = NewConfigF->ShowModal();
    if (button_result == mrOk) {
      m_on_block_reconfiguration = true;
      //перезагружаем список доступных конфигураций
      AnsiString dir_config = m_path_prog+"\\"+m_foldername_conf;
      if (DirectoryExists(dir_config)) {
        load_config_calibr_to_display(dir_config);
        m_on_block_reconfiguration = false;
        AnsiString name_new_config = NewConfigF->get_name_new_conf();
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
      bool forsed_connect = true;
      // устанавливаем принудительно реконнект
      set_connect_calibr_device(forsed_connect);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataHandlingF::EditConfigButtonClick(TObject *Sender)
{
  if (m_cur_filename_conf_calibr_device != "") {
    if (m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str())) {
      m_log << "Текущая конфигурация успешно сохранена.";
    }
  }
  NewConfigF->set_path_program(m_path_prog);
  if(NewConfigF->Visible == false) {
    int index = ConfigCB->ItemIndex;
    if(index >= 0) {
      NewConfigF->edit_config(mv_list_config_calibr[index]);
      int button_result = NewConfigF->ShowModal();
      if (button_result == mrOk) {
        m_on_block_reconfiguration = true;
        //перезагружаем список доступных конфигураций
        AnsiString dir_config = m_path_prog+"\\"+m_foldername_conf;
        if (DirectoryExists(dir_config)) {
          load_config_calibr_to_display(dir_config);
          m_on_block_reconfiguration = false;
          AnsiString name_new_config = NewConfigF->get_name_new_conf();
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
        const bool forsed_connect = true;
        // устанавливаем принудительно реконнект
        set_connect_calibr_device(forsed_connect);
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
    m_on_close_form_stat = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::WriteDataActionExecute(TObject *Sender)
{
  if (m_calibr_data_stat == calibr_data_stat_off) {
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
  m_config_calibr.save(m_cur_filename_conf_calibr_device.c_str());
  //save_cur_config_device();
  set_connect_calibr_device();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::PatternOfMeasuringInstrumentCBChange(
      TObject *Sender)
{
  //set_connect_multimetr();
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetPhaseMeasActionExecute(TObject *Sender)
{
  set_type_meas(tm_phase);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetPhaseAverageMeasActionExecute(
      TObject *Sender)
{
  set_type_meas(tm_phase_average);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetTimeIntervalMeasActionExecute(
      TObject *Sender)
{
  set_type_meas(tm_time_interval);
}
//---------------------------------------------------------------------------

void __fastcall TDataHandlingF::SetTimeIntervalAverageMeasActionExecute(
      TObject *Sender)
{
  set_type_meas(tm_time_interval_average);
}


TDataHandlingF::device_mode_status_t
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
}

void TDataHandlingF::meas_execute()
{
  m_value_meas.execute_meas(m_type_meas, &m_value_meas_multimetr);
  y_out = m_data_map.y_out;
  m_log << "Происходит измерение.";
}

meas_status_t TDataHandlingF::meas_status()
{
  meas_status_t meas_status = meas_status_busy;
  meas_status = m_value_meas.get_status_meas();
  if(meas_status == meas_status_success){
    m_log << "Измерение успешно завершено!";
  }
  else if(meas_status == meas_status_error){
    m_log << "Измерение завершилось с ошибкой!";
  }
  return meas_status;
}   

void __fastcall TDataHandlingF::AddTableActionExecute(TObject *Sender)
{
  AnsiString file_namedir = "";
  file_namedir = mp_active_table->get_file_namedir();
  if(file_namedir != ""){
    if(FileOpenDialog1->Execute()){
      AnsiString file_namedir = FileOpenDialog1->FileName;
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
void TDataHandlingF::out_param(const param_cur_cell_t& a_param_cur_cell)
{
  m_param_cur_cell = a_param_cur_cell;
  m_param_cur_cell.col_value.value =
    m_param_cur_cell.col_value.value*m_config_calibr.in_parametr1.koef;
  m_param_cur_cell.row_value.value =
    m_param_cur_cell.row_value.value*m_config_calibr.in_parametr2.koef;
  if(m_inf_in_param.number_in_param == THREE_PARAM){
    m_param_cur_cell.top_value.value =
      m_param_cur_cell.top_value.value*m_config_calibr.in_parametr3.koef;
  }
  m_on_out_data = true;
  m_log << "Установка параметров рабочего режима";
  out_message_log_cur_param_cell(a_param_cur_cell);

}
void TDataHandlingF::out_message_log_cur_param_cell(
  const param_cur_cell_t& a_param_cur_cell)
{
  const int precision = 5;
  irs::string message_param;
  if (m_inf_in_param.type_anchor == PARAMETR3) {
    if (a_param_cur_cell.top_value.init) {
      ostrstream ostr_top;
      ostr_top << setprecision(precision) << a_param_cur_cell.top_value.value <<
        ends;
      irs::string top_value_str = ostr_top.str();
      ostr_top.freeze(false);
      message_param += top_value_str+" "+m_inf_in_param.type_variable_param3;
      message_param += "; ";
    }
  }
  if (a_param_cur_cell.row_value.init) {
    ostrstream ostr_row;
    ostr_row << setprecision(precision) << a_param_cur_cell.row_value.value <<
      ends;
    irs::string row_value_str = ostr_row.str();
    ostr_row.freeze(false);
    message_param += row_value_str+" "+m_inf_in_param.type_variable_param2;
    message_param += "; ";
  }
  if (a_param_cur_cell.col_value.init) {
    ostrstream ostr_col;
    ostr_col << setprecision(precision) << a_param_cur_cell.col_value.value <<
      ends;
    irs::string col_value_str = ostr_col.str();
    ostr_col.freeze(false);
    message_param += col_value_str+" "+m_inf_in_param.type_variable_param1;
    message_param += ";";
  } 
  m_log << message_param.c_str();
}
bool TDataHandlingF::save_dirty_data()
{
  bool fsuccess = true;
  if (!(mp_active_table->no_modifi())) {
    MessageDlg("The list has ",
      mtInformation, TMsgDlgButtons(), 0);
    int status = MessageDlg(
      "Сохранить изменения в файл?",
      mtConfirmation,
      TMsgDlgButtons() << mbYes << mbNo << mbCancel,
      0);
    switch (status) {
      case mrYes: {
        FileSave->OnExecute;
        if (mp_active_table->no_modifi())
          fsuccess = true;
        else
          fsuccess = false;
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
    m_config_calibr.v_sub_diapason_calibr[a_sub_diapason_index].value_begin;
  const double value_end =
    m_config_calibr.v_sub_diapason_calibr[a_sub_diapason_index].value_end;

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
          m_process_calibr_data_stat = pcds_get_sub_diapason;
        } break;
      }
    } break;
    case pcds_next_sub_diapason: {
      m_cur_sub_diapason++;
      m_process_calibr_data_stat = pcds_get_sub_diapason;
    } break;
    case pcds_get_sub_diapason: {
      int sub_diapason_count = m_config_calibr.v_sub_diapason_calibr.size();
      if (m_cur_sub_diapason < sub_diapason_count) {
        m_log << ("Обрабатывается диапазон №" +
          IntToStr(m_cur_sub_diapason + 1));
        irs::matrix_t<cell_t> sub_diapason =
          get_sub_diapason_table_data(m_cur_sub_diapason);
        calculation_koef(sub_diapason);
        m_index_pos_offset_eeprom =
          m_config_calibr.v_sub_diapason_calibr[m_cur_sub_diapason].index_start;
        m_max_size_correct =
          m_config_calibr.v_sub_diapason_calibr[m_cur_sub_diapason].size;
        if (m_calibr_data_stat == calibr_data_stat_write) {
          m_process_calibr_data_stat = pcds_write_sub_diapason;
        } else {
          m_process_calibr_data_stat = pcds_verify_sub_diapason;
        }
      } else {
        m_process_calibr_data_stat = pcds_reset;
        m_log << "Обработка всех диапазонов завершена";
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
      m_calibr_data_stat = calibr_data_stat_off;
      m_process_calibr_data_stat = pcds_off;
      m_cur_sub_diapason = 0;
    } break;
  }
}
void TDataHandlingF::modifi_table_data()
{
  irs::string str;
  auto_ptr<TModifiDataTableF> modifi_data_table(new TModifiDataTableF(0, &str));
  if (!modifi_data_table->Visible) {
    int result = modifi_data_table->ShowModal();
    if (result == mrOk) {
      if (str != "") {
        mp_active_table->modifi_content_table(str);
      }  
    }
  }
}
void TDataHandlingF::set_value_working_extra_params()
{
  int parametr_ex_count = m_config_calibr.v_parametr_ex.size();
  int extra_param_count = m_data_map.v_extra_param.size();
  if (parametr_ex_count == extra_param_count) {
    for (int i = 0; i < extra_param_count; i++) {
      m_data_map.v_extra_param[i] =
        m_config_calibr.v_parametr_ex[i].value_working;
      irs::string value_working_str =
        m_config_calibr.v_parametr_ex[i].value_working;
      AnsiString message = m_config_calibr.v_parametr_ex[i].name;
      message = message + " установлен в " + value_working_str.c_str();
      m_log << message;
    }
  }
}

void TDataHandlingF::set_value_default_extra_params()
{
  int parametr_ex_count = m_config_calibr.v_parametr_ex.size();
  int extra_param_count = m_data_map.v_extra_param.size();
  if (parametr_ex_count == extra_param_count) {
    for (int i = 0; i < extra_param_count; i++) {
      m_data_map.v_extra_param[i] =
        m_config_calibr.v_parametr_ex[i].value_default ;
      irs::string value_default_str =
        m_config_calibr.v_parametr_ex[i].value_default;
      AnsiString message = m_config_calibr.v_parametr_ex[i].name;
      message = message + " установлен в " + value_default_str.c_str();
      m_log << message;
    }
  }
}

void TDataHandlingF::set_value_working_extra_bits()
{
  int bit_type2_count = m_config_calibr.bit_type2_array.size();
  int extra_bit_count = m_data_map.v_extra_bit.size();
  if (bit_type2_count == extra_bit_count) {
    for (int i = 0; i < extra_bit_count; i++) {
      m_data_map.v_extra_bit[i] =
        m_config_calibr.bit_type2_array[i].value_working;
      irs::string value_working_str =
        m_config_calibr.bit_type2_array[i].value_working;
      AnsiString message = m_config_calibr.bit_type2_array[i].bitname.c_str();
      message = message + " установлен в " + value_working_str.c_str();
      m_log << message;
    }
  }
}
void TDataHandlingF::set_value_default_extra_bits()
{
  int bit_type2_count = m_config_calibr.bit_type2_array.size();
  int extra_bit_count = m_data_map.v_extra_bit.size();
  IRS_ASSERT(bit_type2_count == extra_bit_count);
  if (bit_type2_count == extra_bit_count) {
    for (int i = 0; i < extra_bit_count; i++) {
      m_data_map.v_extra_bit[i] =
        m_config_calibr.bit_type2_array[i].value_def;
      irs::string value_default_str =
        m_config_calibr.bit_type2_array[i].value_def;
      AnsiString message = m_config_calibr.bit_type2_array[i].bitname.c_str();
      message = message + " установлен в " + value_default_str.c_str();
      m_log << message;
    }
  }
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
    irs::string name_graph, row_value_str, z_value_str;
    ostrstream ostr_row, ostr_z;
    ostr_row << setprecision(precision_name_graph) << row_value << ends;
    row_value_str = ostr_row.str();
    ostr_row.freeze(false);
    double norm_koef = 1;
    if(a_inf_in_param.type_anchor == PARAMETR2){
      norm_koef = row_value;
    }else if(a_inf_in_param.type_anchor == PARAMETR3){
      if(z.init){
        if (z.value != 0) norm_koef = z.value;
        ostr_z << setprecision(precision_name_graph) << z.value << ends;
        z_value_str = ostr_z.str();
        ostr_z.freeze(false);
        name_graph = z_value_str+" "+a_inf_in_param.type_variable_param3+ ", ";
      }
    }
    name_graph += row_value_str+" "+a_inf_in_param.type_variable_param2;
    if (!a_on_update) {
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
    irs::string name_graph, col_value_str, z_value_str;
    ostrstream ostr_col, ostr_z;

    ostr_col << setprecision(precision_name_graph) << col_value << ends;
    col_value_str = ostr_col.str();
    ostr_col.freeze(false);
    double norm_koef = 1;
    if(a_inf_in_param.type_anchor == PARAMETR1) {
      norm_koef = col_value;
    }else if(a_inf_in_param.type_anchor == PARAMETR3){
      if(z.init){
        if (z.value != 0) norm_koef = z.value;
        ostr_z << setprecision(precision_name_graph) << z.value << ends;
        z_value_str = ostr_z.str();
        ostr_z.freeze(false);
        name_graph =
          z_value_str+" "+a_inf_in_param.type_variable_param3+ ", ";
      }
    }
    name_graph += col_value_str+" "+a_inf_in_param.type_variable_param1;
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
  const irs::string& a_name_chart)
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
  const irs::string& a_name_chart)
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
  const irs::string& a_name_graph,
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
          a_name_graph.c_str(), x_cell_value, p_cell_value);
      }
    }
  }
}
void TDataHandlingF::chart_t::add_chart_z_of_y(
  const irs::string& a_name_graph,
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
  SaveFileDialog->Filter = "Текстовые файлы Microsoft Excel (*.csv)"
    "|*.csv|Все файлы (*.*)|*.*";
  SaveFileDialog->DefaultExt = "csv";
  SaveFileDialog->FileName = "Новый файл.csv";
  if (SaveFileDialog->Execute()) {
    irs::string file_name = SaveFileDialog->FileName.c_str();
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
  auto_ptr<TAboutForm> AboutForm(new TAboutForm(IRS_NULL));
  AboutForm->ShowModal();
}
//---------------------------------------------------------------------------







