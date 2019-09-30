//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "newconfig.h"
#include "dinamictypes.h"
#include "servisfunction.h"

#include "showmessages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TNewConfigF *NewConfigF;
void fill_combo_box_lang_type(TComboBox* ap_combo_box)
{
  lang_type_t type = type_last;
  const int end_for = static_cast<int>(type);
  type = type_none;
  const int begin_for = static_cast<int>(type) + 1;
  irs::string_t type_str;
  type_str = lang_type_to_str(type);
  for(int i = begin_for; i < end_for; i++){
    type = static_cast<lang_type_t>(i);
    type_str = lang_type_to_str(type);
    ap_combo_box->Items->Add(type_str.c_str());
    //mv_list_combo_box.push_back(type_str.rec_str());
  }
  ap_combo_box->ItemIndex = 0;
}
//---------------------------------------------------------------------------
__fastcall TNewConfigF::TNewConfigF(TComponent* Owner,
  TDataHandlingF* ap_data_handing)
  : TForm(Owner),
  mp_data_handing(ap_data_handing),
  m_prog_name(irst("Digital interpolator")),
  m_file_name_service(),
  //m_path_prog(),
  //m_default_ext(irst("cpc")),
  //m_default_filename(irst("config1.cpc")),
  //m_foldername_conf(irst("configuration")),
  //m_device_default_ext(irst("ini")),
  //m_device_suffix(irst("_device")),
  //m_ref_device_default_ext(irst("ini")),
  //m_ref_device_suffix("_reference_device"),

  m_device_options_section(irst("device")),

  m_config_calibr(),
  m_cells_range(),
  //m_fileid_conf(irst("Конфигурация настроек калибровки.")),
  m_name_config(),
  //mp_conf_device_ini_file(0),
  //mp_config_ini_file(0),
  //mv_list_combo_box(),
  m_edit_mode(NEW_CONFIG),
  m_on_close(true),
  m_name_new_conf(),
  m_device_list()
{
  /*SaveDialogConfig->DefaultExt = m_default_ext;
  SaveDialogConfig->Filter =
    irst("Файлы конфигурации (*.") + m_default_ext + irst(")|*.") +
      m_default_ext +
      irst("|Все файлы (*.*)|*.*");
  SaveDialogConfig->FileName = m_default_filename;*/

  m_device_list.push_back(irst("mxnet"));
  m_device_list.push_back(irst("modbus udp"));
  m_device_list.push_back(irst("modbus tcp"));
  m_device_list.push_back(irst("modbus usb hid"));

  for (size_type i = 0; i < m_device_list.size(); i++) {
    DeviceComboBox->Items->Add(irs::str_conv<String>(m_device_list[i]));
    RefDeviceComboBox->Items->Add(irs::str_conv<String>(m_device_list[i]));
  }
  DeviceComboBox->ItemIndex = 0;
  RefDeviceComboBox->ItemIndex = 0;

  MeasTypeCB->Items->Clear();
  type_meas_t type_meas = tm_first;
  int index = static_cast<int>(type_meas);
  while(true){
    type_meas = static_cast<type_meas_t>(index);
    string_type type_meas_str = type_meas_to_str(type_meas);
    MeasTypeCB->Items->Add(type_meas_str.c_str());
    if(type_meas == tm_last)
      break;
    index++;
  }
  MeasTypeCB->ItemIndex = 0;
  // настройка списка параметров
  ListParameterSG->Col = 0;
  ListParameterSG->Row = 1;
  ListParameterSG->RowCount = m_basic_parameter_count+1;
  ListParameterSG->Cells[0][0] = "Название*";
  ListParameterSG->Cells[1][0] = "Единицы измерения";
  ListParameterSG->Cells[2][0] = "Тип переменной*";
  ListParameterSG->Cells[3][0] = "Привязка*";
  ListParameterSG->Cells[4][0] = "Индекс, байт*";
  ListParameterSG->Cells[5][0] = "Коэффициент*";
  ListParameterSG->Cells[6][0] = "Рабочее значение*";
  ListParameterSG->Cells[7][0] = "Значение по умолчанию*";

  ListParameterSG->Cells[0][1] = "Параметр 1";
  ListParameterSG->Cells[0][2] = "Параметр 2";
  ListParameterSG->Cells[0][3] = "Параметр 3";
  ListParameterSG->Cells[0][4] = "Параметр 4";
  ParamsExCSpinEdit->Value = 1;

  // Настройка списка битов
  ListByteSG->Col = 0;
  ListByteSG->Row = m_basic_bit_count+1;
  ListByteSG->RowCount = m_basic_bit_count+1;

  ListByteSG->Cells[0][0] = "Название*";
  ListByteSG->Cells[1][0] = "Индекс, байт*";
  ListByteSG->Cells[2][0] = "Индекс, бит(0-7)*";
  ListByteSG->Cells[3][0] = "Рабочее значение*";
  ListByteSG->Cells[4][0] = "Значение по умолчанию*";

  ListByteSG->Cells[0][1] = "Бит готовности регулятора";
  ListByteSG->Cells[0][2] = "Бит режима расстройки";
  ListByteSG->Cells[0][3] = "Бит режима коррекции";
  ListByteSG->Cells[0][4] = "Бит ошибки";
  ListByteSG->Cells[0][5] = "Бит сброса ошибки";
  ListByteSG->Cells[0][6] = "Бит предустановки фазы";
  //ListByteSG->Cells[0][7] = "Бит тестового режима";

  // Настройка списка параметров EEPROM
  TypeSubDiapasonParam2RB->Checked = true;
  CSpinEdit1->Value = 1;
  SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
  SubDiapasonSG->Cells[0][0] = "Номер*";
  SubDiapasonSG->Cells[1][0] = "Н. индекс*";
  SubDiapasonSG->Cells[2][0] = "Размер*";
  SubDiapasonSG->Cells[3][0] = "Н. знач.*";
  SubDiapasonSG->Cells[4][0] = "К. знач.*";
  SubDiapasonSG->Cells[0][1] = "1";
  SubDiapasonSG->Cells[1][1] = "";
  SubDiapasonSG->Cells[2][1] = "";
  SubDiapasonSG->Cells[3][1] = "";
  SubDiapasonSG->Cells[4][1] = "";
}

void TNewConfigF::draw_cell_illegal(
  TObject *Sender, int ACol, int ARow, TRect &Rect)
{
  //цвет фона
  ((TStringGrid*)Sender)->Canvas->Brush->Color = clBtnFace;//clMoneyGreen;
  //цвет текста
  ((TStringGrid*)Sender)->Canvas->Font->Color = clBlack;
  //заливаем фон
  ((TStringGrid*)Sender)->Canvas->FillRect(Rect);
  //красим текст
  ((TStringGrid*)Sender)->Canvas->TextOutW(
    Rect.Left, Rect.Top, ((TStringGrid*)Sender)->Cells[ACol][ARow]);
}
bool TNewConfigF::cell_illegal_ListParameterSG_stat(
  const int a_col, const int a_row)
{
  bool cell_illegal_stat =false;
  // запрещение стобца "значение по умолчанию" для статических параметров
  if ((a_row > 0) && (a_row < m_basic_parameter_count+1)) {
    if (a_col == 6) {
      cell_illegal_stat = true;
    }
  }
  // запрещение стобца "привязка" для третьего и четвертого параметров
  if (a_row > 2) {
    if (a_col == 3) {
      cell_illegal_stat = true;
    }
  }
  // запрещение стобца "коэффициент" для динамически-добавляемых параметров
  if (a_row > m_basic_parameter_count) {
    if (a_col == 5) {
      cell_illegal_stat = true;
    }
  }
  // запрещение стобца "значение по умолчанию" для четвертого параметра
  if (a_row == 4) {
    if (a_col == 7) {
      cell_illegal_stat = true;
    }
  }
  return cell_illegal_stat;
}

void TNewConfigF::out_parameter_options_components_update()
{
  OutParameterFilterCheckBox->Enabled =
    ConsiderOutParameterForMeasurementCheckBox->Checked;
  FilterSamplingTimeEdit->Enabled =
    ConsiderOutParameterForMeasurementCheckBox->Checked &&
    OutParameterFilterCheckBox->Checked;
  FilterPointCountEdit->Enabled =
    ConsiderOutParameterForMeasurementCheckBox->Checked &&
    OutParameterFilterCheckBox->Checked;
}

void TNewConfigF::temperature_control_components_update()
{
  TemperatureVariableIndexByteLabeledEdit->Enabled =
    TemperatureControlVariableCheckBox->Checked;
  TemperatureControlCheckBox->Enabled =
    TemperatureControlVariableCheckBox->Checked;

  ReferenceTemperetureLabeledEdit->Enabled =
    TemperatureControlVariableCheckBox->Checked && TemperatureControlCheckBox->Checked;
  DifferenceTemperatureLabeledEdit->Enabled =
    TemperatureControlVariableCheckBox->Checked && TemperatureControlCheckBox->Checked;
}

// Выгрузка списка параметров с экрана в структуру
void __fastcall TNewConfigF::CreateConfigButtonClick(TObject *Sender)
{ 
  std::vector<string_type> messages;
  m_name_config = NameConfigLE->Text;

  cell_config_calibr_t cell_config = m_config_calibr.cells_config.
    read_cell(m_cells_range.left, m_cells_range.top);

  m_config_calibr.device_name = DeviceNameComboBox->Text;
  m_config_calibr.reference_device_name = RefDeviceNameComboBox->Text;

  //m_config_calibr.ip_adress = IPAdressLE->Text;
  /*if (!irs::cbuilder::str_to_number(PortLE->Text,  m_config_calibr.port)) {
    messages.push_back(irst("Неверно указан порт."));
  }*/

  cell_config.type_meas = MeasTypeCB->Text.c_str();

  cell_config.range_enabled = RangeCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    RangeEdit->Text, cell_config.range)) {
    messages.push_back(irst("Неверно указан диапазон измерения."));
  }

  if (!irs::cbuilder::str_to_number(
    Delay_MeasLE->Text, cell_config.delay_meas)) {
    messages.push_back(irst("Неверно указана задержка измерения."));
  }
  if (!irs::cbuilder::str_to_number(
    MeasIntervalLabeledEdit->Text, cell_config.meas_interval)) {
    messages.push_back(
      irst("Неверно указано время измерений."));
  }
  if (!irs::cbuilder::str_to_number(
    CountResetOverBitLE->Text, cell_config.count_reset_over_bit)) {
    messages.push_back(
      irst("Неверно указано количество перезапусков измерения."));
  }
  if (!irs::cbuilder::str_to_number(
    IndexWorkTimeEdit->Text, m_config_calibr.index_work_time)) {
    messages.push_back(irst("Неверно указан индекс \"work time\"."));
  }
  if (!irs::cbuilder::str_to_number(
    ValueIndexEEPROMEdit->Text, m_config_calibr.index_pos_eeprom)) {
    messages.push_back(irst("Неверно указан индекс \"eeprom\"."));
  }

  cell_config.out_param_measuring_conf.consider_out_param =
    ConsiderOutParameterForMeasurementCheckBox->Checked;
  cell_config.out_param_measuring_conf.filter_enabled =
    OutParameterFilterCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    FilterSamplingTimeEdit->Text,
    cell_config.out_param_measuring_conf.filter_sampling_time)) {
    messages.push_back(irst("Неверно указано время дискретизации для фильтра ")
      irst("выходного значения"));
  }
  if (!irs::cbuilder::str_to_number(
    FilterPointCountEdit->Text,
    cell_config.out_param_measuring_conf.filter_point_count)) {
    messages.push_back(irst("Неверно указано время дискретизации для фильтра ")
      irst("выходного значения"));
  }

  cell_config.out_param_control_config.enabled =
    OutParameterControlCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    MaxRelativeDifferenceOutParameterLabeledEdit->Text,
    cell_config.out_param_control_config.max_relative_difference)) {
    messages.push_back(
      irst("Неверно указано допустимое относительное отклонение ")
      irst("выходного параметра"));
  }
  if (!irs::cbuilder::str_to_number(
    TimeCalcDifferenceLabeledEdit->Text,
    cell_config.out_param_control_config.time)) {
    messages.push_back(irst("Неверно указано временное окно"));
  }

  m_config_calibr.temperature_ctrl_common_cfg.enabled =
    TemperatureControlVariableCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    TemperatureVariableIndexByteLabeledEdit->Text,
    m_config_calibr.temperature_ctrl_common_cfg.index)) {
    messages.push_back(irst("Неверно указан индекс \"температура\"."));
  }
  cell_config.temperature_control.enabled = TemperatureControlCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    ReferenceTemperetureLabeledEdit->Text,
    cell_config.temperature_control.reference)) {
    messages.push_back(irst("Неверно указана уставка температуры"));
  }
  if (!irs::cbuilder::str_to_number(
    DifferenceTemperatureLabeledEdit->Text,
    cell_config.temperature_control.difference)) {
    messages.push_back(
      irst("Неверно указано допустимое отклонение температуры"));
  }

  // Выгрузка списка параметров
  // Параметр 1
  m_config_calibr.in_parameter1.name = ListParameterSG->Cells[0][1];

  m_config_calibr.in_parameter1.unit = ListParameterSG->Cells[1][1];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][1].c_str(), m_config_calibr.in_parameter1.type)) {
    messages.push_back(irst("Неверно указан тип параметра 1."));
  }


  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[3][1], m_config_calibr.in_parameter1.anchor)) {
    messages.push_back(irst("Неверно указан тип привязки параметра 1."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][1], m_config_calibr.in_parameter1.index)) {
    messages.push_back(irst("Неверно указан индекс параметра 1."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][1], m_config_calibr.in_parameter1.koef)) {
    messages.push_back(irst("Неверно указан коэффициент параметра 1."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][1], m_config_calibr.in_parameter1.default_val)) {
    messages.push_back(
      irst("Неверно указано значение по умолчанию параметра 1."));
  }
  // Параметр 2
  m_config_calibr.in_parameter2.name = ListParameterSG->Cells[0][2];
  m_config_calibr.in_parameter2.unit = ListParameterSG->Cells[1][2];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][2].c_str(), m_config_calibr.in_parameter2.type)) {
    messages.push_back(irst("Неверно указан тип параметра 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[3][2], m_config_calibr.in_parameter2.anchor)) {
    messages.push_back(irst("Неверно указан тип привязки параметра 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][2], m_config_calibr.in_parameter2.index)) {
    messages.push_back(irst("Неверно указан индекс параметра 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][2], m_config_calibr.in_parameter2.koef)) {
    messages.push_back(irst("Неверно указан коэффициент параметра 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][2], m_config_calibr.in_parameter2.default_val)) {
    messages.push_back(
      irst("Неверно указано значение по умолчанию параметра 2."));
  }
  // Параметр 3
  m_config_calibr.in_parameter3.name = ListParameterSG->Cells[0][3];
  m_config_calibr.in_parameter3.unit = ListParameterSG->Cells[1][3];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][3].c_str(), m_config_calibr.in_parameter3.type)) {
    messages.push_back(irst("Неверно указан тип параметра 3."));
  }

  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][3], m_config_calibr.in_parameter3.index)) {
    messages.push_back(irst("Неверно указан индекс параметра 3."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][3], m_config_calibr.in_parameter3.koef)) {
    messages.push_back("Неверно указан коэффицинет параметра 3.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][3], m_config_calibr.in_parameter3.default_val)) {
    messages.push_back(
      irst("Неверно указано значение по умолчанию параметра 3."));
  }

  // Параметр 4
  m_config_calibr.out_parameter.name = ListParameterSG->Cells[0][4];
  m_config_calibr.out_parameter.unit = ListParameterSG->Cells[1][4];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][4].c_str(), m_config_calibr.out_parameter.type)) {
    messages.push_back(irst("Неверно указан тип параметра 3."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][4], m_config_calibr.out_parameter.index)) {
    messages.push_back(irst("Неверно указан индекс параметра 4."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][4], cell_config.output_param_coef)) {
    messages.push_back(irst("Неверно указан коэффициент параметра 4."));
  }

  if (cell_config.output_param_coef == 0.0) {
    messages.push_back(irst("Коэффициент параметра 4 не должен быть равен нулю."));
  }



  // обработка доп.параметров
  int parameter_ex_count = ParamsExCSpinEdit->Value;
  m_config_calibr.v_parameter_ex.clear();

  cell_config.ex_param_work_values.clear();

  for (int i = 0; i < parameter_ex_count; i++) {
    int row = i+m_basic_parameter_count+1;
    string_type param_ex_number_str = i;

    parameter_ex_t parameter_ex;
    // название
    parameter_ex.name = ListParameterSG->Cells[0][row];
    // единицы измерения
    parameter_ex.unit = ListParameterSG->Cells[1][row];
    if (!parameter_ex.name.IsEmpty()) {
      bool all_str_to_number_success = true;
      // тип переменной
      //if (ListParameterSG->Cells[2][row] != "") {
        if (!str_to_lang_type(
          ListParameterSG->Cells[2][row].c_str(), parameter_ex.type)) {
          all_str_to_number_success = false;
          string_type message = irst("Неверно указан тип доп. параметра №") +
            param_ex_number_str + irst(".");
          messages.push_back(message);
        }
      /*} else {

      }*/
      // индекс
      //if (ListParameterSG->Cells[4][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[4][row], parameter_ex.index))
        {
          all_str_to_number_success = false;
          string_type message = irst("Неверно указан индекс доп. параметра №") +
            param_ex_number_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      // рабочее значение
      //if (ListParameterSG->Cells[6][row] != "") {
        double work_value = 0;
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[6][row], work_value))
        {
          all_str_to_number_success = false;
          string_type message =
            irst("Неверно указано рабочее значение доп. параметра №") +
            param_ex_number_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      // значение по умолчанию
      //f (ListParameterSG->Cells[7][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[7][row], parameter_ex.value_default))
        {
          all_str_to_number_success = false;
          string_type message =
            irst("Неверно указано значение по умолчанию доп. параметра №") +
            param_ex_number_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      if (all_str_to_number_success) {
        m_config_calibr.v_parameter_ex.push_back(parameter_ex);
        cell_config.ex_param_work_values.push_back(work_value);
      }
    }
  }

  // Бит готовности регулятора
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][1],
    m_config_calibr.bit_pos_operating_duty.index_byte))
  {
    messages.push_back(irst("Неверно указан индекс байта, ")
      irst("в котором находится бит готовноти регулятора."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][1],
    m_config_calibr.bit_pos_operating_duty.index_bit))
  {
    messages.push_back(
      irst("Неверно указан индекс бита готовноти регулятора."));
  }

  // Бит режима расстройки
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][2],
    m_config_calibr.bit_pos_mismatch_state.index_byte))
  {
    messages.push_back(irst("Неверно указан индекс байта, ")
      irst("в котором находится бит режима расстройки."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][2],
    m_config_calibr.bit_pos_mismatch_state.index_bit))
  {
    messages.push_back(irst("Неверно указан индекс бита режима расстройки."));
  }

  // Бит режима коррекции
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][3],
    m_config_calibr.bit_pos_correct_mode.index_byte)) {
    messages.push_back(irst("Неверно указан индекс байта, ")
      irst("в котором находится бит режима коррекции."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][3],
    m_config_calibr.bit_pos_correct_mode.index_bit)) {
    messages.push_back(irst("Неверно указан индекс бита режима коррекции."));
  }

  // Бит ошибки
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][4],
    m_config_calibr.bit_pos_error_bit.index_byte)) {
    messages.push_back(irst("Неверно указан индекс байта, ")
      irst("в котором находится бит ошибки."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][4],
    m_config_calibr.bit_pos_error_bit.index_bit))
  {
    messages.push_back(irst("Неверно указан индекс бита ошибки."));
  }

  // Бит сброса ошибки
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][5],
    m_config_calibr.bit_pos_reset_over_bit.index_byte))
  {
    messages.push_back(irst("Неверно указан индекс байта, ")
      irst("в котором находится бит сброса ошибки."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][5],
    m_config_calibr.bit_pos_reset_over_bit.index_bit))
  {
    messages.push_back(irst("Неверно указан индекс бита сброса ошибки."));
  }

  // Бит предустановки фазы
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][6],
    m_config_calibr.bit_pos_phase_preset_bit.index_byte))
  {
    messages.push_back(irst("Неверно указан индекс байта, ")
      irst("в котором находится бит предустановки фазы."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][6],
    m_config_calibr.bit_pos_phase_preset_bit.index_bit))
  {
    messages.push_back(irst("Неверно указан индекс бита предустановки фазы."));
  }

  // Обработка доп.битов
  int bit_type2_count = BitsExCSpinEdit->Value;
  m_config_calibr.bit_type2_array.clear();
  cell_config.ex_bit_work_values.clear();

  for (int i = 0; i < bit_type2_count; i++) {
    int row = i+m_basic_bit_count+1;
    string_type bit_ex_index_str = i;
    string_type bitname_str = ListByteSG->Cells[0][row].c_str();
    bit_type2_pos_t bit_type2_pos;
    bit_type2_pos.bitname = bitname_str;
    if (!bitname_str.empty()) {
      bool all_str_to_number_success = true;
      //if (ListByteSG->Cells[1][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListByteSG->Cells[1][row], bit_type2_pos.index_byte))
        {
          all_str_to_number_success = false;
          string_type message = irst("Неверно указан индекс байта, ")
            irst("в котором находится доп. бит №") + bit_ex_index_str +
            irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      //if (ListByteSG->Cells[2][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListByteSG->Cells[2][row], bit_type2_pos.index_bit))
        {
          all_str_to_number_success = false;
          string_type message = irst("Неверно указан индекс доп. бита №") +
            bit_ex_index_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      //if (ListByteSG->Cells[3][row] != "") {
        bool work_value = 0;
        if (!irs::cbuilder::str_to_number(
          ListByteSG->Cells[3][row], work_value))
        {
          all_str_to_number_success = false;
          string_type message =
            irst("Неверно указано рабочее значение доп. бита №") +
            bit_ex_index_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      //if (ListByteSG->Cells[4][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListByteSG->Cells[4][row], bit_type2_pos.value_def))
        {
          all_str_to_number_success = false;
          string_type message =
            irst("Неверно указано значение по умолчанию доп. бита №") +
            bit_ex_index_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/

      if (all_str_to_number_success) {
        m_config_calibr.bit_type2_array.push_back(bit_type2_pos);
        cell_config.ex_bit_work_values.push_back(work_value);
      }
    }
  }

  if (TypeSubDiapasonParam1RB->Checked) {
    m_config_calibr.type_sub_diapason = tsd_parameter1;
  } else {
    m_config_calibr.type_sub_diapason = tsd_parameter2;
  }
  int sub_diapason = CSpinEdit1->Value;
  m_config_calibr.eeprom_ranges.clear();
  for (int i = 0; i < sub_diapason; i++) {
    int row = i+1;
    eeprom_range_t sub_diapason_calibr;
    string_type index_start_str = SubDiapasonSG->Cells[1][row].c_str();
    string_type size_str = SubDiapasonSG->Cells[2][row].c_str();
    string_type value_begin_str = SubDiapasonSG->Cells[3][row].c_str();
    string_type value_end_str = SubDiapasonSG->Cells[4][row].c_str();

    if (index_start_str.to_number(sub_diapason_calibr.index_start)) {
      if (size_str.to_number(sub_diapason_calibr.size)) {
        if (value_begin_str.to_number(sub_diapason_calibr.value_begin)) {
          if (value_end_str.to_number(sub_diapason_calibr.value_end)) {
            m_config_calibr.eeprom_ranges.push_back(
              sub_diapason_calibr);
          }
        }
      }
    }
  }

  m_config_calibr.reference_channel.enabled = ReferenceChannelCheckB->Checked;
  //m_config_calibr.reference_channel.ip_adress = IPAdressRefChannelLE->Text;
  /*irs::cbuilder::str_to_number(
    PortRefChannelLE->Text, m_config_calibr.reference_channel.port);*/

  for (size_type col = m_cells_range.left; col < m_cells_range.right + 1; col++) {
    for (size_type row = m_cells_range.top; row < m_cells_range.bottom + 1; row++) {
      m_config_calibr.cells_config.write_cell(col, row, cell_config);
    }
  }

  // Количество дополнительных параметров и битов должно быть одинаковым во всех ячейках
  for (size_type col = 1; col < m_config_calibr.cells_config.get_col_count(); col++) {
    for (size_type row = 1; row < m_config_calibr.cells_config.get_row_count(); row++) {
      if (!irs::is_in_range(col, m_cells_range.left, m_cells_range.right) ||
        !irs::is_in_range(row, m_cells_range.top, m_cells_range.bottom)) {

        cell_config_calibr_t cell_cfg = m_config_calibr.cells_config.read_cell(col, row);

        if (cell_cfg.ex_param_work_values.size() > cell_config.ex_param_work_values.size()) {
          cell_cfg.ex_param_work_values.resize(cell_config.ex_param_work_values.size());
        } else if(cell_cfg.ex_param_work_values.size() < cell_config.ex_param_work_values.size()) {
          size_type old_size = cell_cfg.ex_param_work_values.size();
          cell_cfg.ex_param_work_values.insert(
            cell_cfg.ex_param_work_values.begin() + old_size,
            cell_config.ex_param_work_values.begin() + old_size,
            cell_config.ex_param_work_values.end());
        }

        if (cell_cfg.ex_bit_work_values.size() > cell_config.ex_bit_work_values.size()) {
          cell_cfg.ex_bit_work_values.resize(cell_config.ex_bit_work_values.size());
        } else if(cell_cfg.ex_bit_work_values.size() < cell_config.ex_bit_work_values.size()) {
          size_type old_size = cell_cfg.ex_bit_work_values.size();
          cell_cfg.ex_bit_work_values.insert(
            cell_cfg.ex_bit_work_values.begin() + old_size,
            cell_config.ex_bit_work_values.begin() + old_size,
            cell_config.ex_bit_work_values.end());
        }

        m_config_calibr.cells_config.write_cell(col, row, cell_cfg);
      }      
    }
  }

  // Проверяем, что количество доп.параметров и доп.битов одинаковое во всех ячейках
  /*IRS_ASSERT(cell_config.ex_param_work_values.size() == m_config_calibr.v_parameter_ex.size());
  IRS_ASSERT(cell_config.ex_bit_work_values.size() == m_config_calibr.bit_type2_array.size());
  for (size_type col = 1; col < m_config_calibr.cells_config.get_col_count(); col++) {
    for (size_type row = 1; row < m_config_calibr.cells_config.get_row_count(); row++) {
      cell_config_calibr_t cell_cfg = m_config_calibr.cells_config.read_cell(col, row);
      IRS_ASSERT(m_config_calibr.v_parameter_ex.size() == cell_cfg.ex_param_work_values.size());
      IRS_ASSERT(m_config_calibr.bit_type2_array.size() == cell_cfg.ex_bit_work_values.size());
    }
  }*/
  config_calibr_t::check_config(m_config_calibr);

  if (messages.size() > 0) {
    irs::handle_t<TMessagesForm> display_message(new TMessagesForm(NULL));
    display_message->show_messages(messages);
    if (!display_message->Visible) {
      display_message->ShowModal();
      m_on_close = false;
    }
  } else {

    //String filename = m_path_prog + irst("\\") + m_foldername_conf +
      //irst("\\") + m_name_config + irst(".") + m_default_ext;

    m_file_name_service.create_config_dir();
    const String filename =
      m_file_name_service.make_config_full_file_name(m_name_config);
    m_name_new_conf = m_name_config;

    if (m_edit_mode == NEW_CONFIG) {
      if (FileExists(filename)) {
        if (!save_with_same_name_dialog()) {
          m_on_close = false;
          return;
        }
      }
    }

    m_config_calibr.save(filename.c_str());
    m_on_close = true;
    /*bool on_create_file = true;
    m_on_close = false;
    m_name_new_conf = String();
    //create_configurations_dir();
    m_file_name_service.create_config_dir();
    //если файл существует
    if(m_edit_mode == NEW_CONFIG){
      if(FileExists(filename)){
        String message_text = irst("Файл \"") + filename +
          irst("\" уже существует.\n")
          irst("Хотите его перезаписать?");
        int button_return =
          MessageDlg(
            message_text,
            mtConfirmation,
            TMsgDlgButtons() << mbYes << mbNo << mbCancel,
            0);
        if(button_return != mrYes){
          on_create_file = false;
          m_on_close = false;
        }
      }
    }
    if(on_create_file){
      //открыть для записи, удалить старое содержимое файла
      ofstream ofile(filename.c_str(),ios::out|ios::trunc);
      if (ofile) {
        ofile.close();
        //mp_conf_device_ini_file->set_ini_name(filename);
        //mp_conf_device_ini_file->save();
        m_config_calibr.save(filename.c_str());
      }
      m_name_new_conf = m_name_config;
      m_on_close = true;
    }*/
  }
}

bool TNewConfigF::save_with_same_name_dialog() const
{
  const int result = Application->MessageBox(
    irst("Конфигурация с таким именем уже есть, перезаписать ее?"),
    irst("Новая конфигурация"),
    MB_YESNO + MB_ICONQUESTION);

  switch (result) {
    case mrYes: {
      // Ничего не делаем
    } break;
    case mrNo: {
      return false;
    } break;
  }
  return true;
}

String TNewConfigF::get_config_full_file_name()
{
  return make_config_full_file_name(NameConfigLE->Text);
}

String TNewConfigF::make_config_full_file_name(String a_config_name)
{
  return m_file_name_service.make_config_full_file_name(a_config_name);
  /*return m_path_prog + irst("\\") + m_foldername_conf +
    irst("\\") + a_config_name + irst(".") + m_default_ext;*/
}

String TNewConfigF::make_device_config_full_file_name(String a_config_name)
{
  return m_file_name_service.make_device_config_full_file_name(a_config_name);
  /*return m_path_prog + irst("\\") + m_foldername_conf +
    irst("\\") + a_config_name + m_device_suffix  + irst(".") +
    m_device_default_ext;*/
}
//---------------------------------------------------------------------------
void TNewConfigF::edit_config(const String& a_filename)
{
  m_edit_mode = EXISTENT_CONFIG;
  if (FileExists(a_filename)) {
    load_devices_list();
    m_config_calibr.load(a_filename.c_str());
    //m_name_config = extract_short_filename(ExtractFileName(a_filename));
    m_name_config = m_file_name_service.get_config_name(a_filename);
    m_cells_range = mp_data_handing->cells_range();

    /////////////////////////
    IRS_ASSERT(mp_data_handing->table_displ_col_count() > 0);
    IRS_ASSERT(mp_data_handing->table_displ_row_count() > 0);

    size_type prev_col_count = m_config_calibr.cells_config.get_col_count();
    size_type prev_row_count = m_config_calibr.cells_config.get_row_count();

    m_config_calibr.cells_config.set_col_count(
      mp_data_handing->table_displ_col_count());
    m_config_calibr.cells_config.set_row_count(
      mp_data_handing->table_displ_row_count());

    size_type col_count = m_config_calibr.cells_config.get_col_count();
    size_type row_count = m_config_calibr.cells_config.get_row_count();

    if (col_count > 0 && row_count > 0)
    {
      for (size_type col = 0; col < col_count; col++) {
        cell_t cell = mp_data_handing->get_cell_table(col, 0);

        cell_config_calibr_t header_cell;
        header_cell.is_value_initialized = cell.init;
        header_cell.value = cell.value;
        m_config_calibr.cells_config.write_cell(col, 0, header_cell);
      }

      for (size_type row = 1; row < row_count; row++) {
        cell_t cell = mp_data_handing->get_cell_table(0, row);

        cell_config_calibr_t header_cell;
        header_cell.is_value_initialized = cell.init;
        header_cell.value = cell.value;
        m_config_calibr.cells_config.write_cell(0, row, header_cell);
      }
    }

    // Если количество столбцов увеличилось, то копируем настройки из
    // последнего столбца до изменений
    if (prev_col_count > 1) {
      for (size_type col = prev_col_count; col < col_count; col++) {
        for (size_type row = 1; row < min(row_count, prev_row_count); row++) {
          cell_config_calibr_t src_cell =
            m_config_calibr.cells_config.read_cell(prev_col_count - 1, row);
          m_config_calibr.cells_config.write_cell(col, row, src_cell);
        }
      }
    }

    // Если количество строк увеличилось, то копируем настройки из
    // последней строки до изменений
    if (prev_row_count > 1) {
      for (size_type col = 1; col < col_count; col++) {
        for (size_type row = prev_row_count; row < row_count; row++) {
          cell_config_calibr_t src_cell =
            m_config_calibr.cells_config.read_cell(col, prev_row_count - 1);
          m_config_calibr.cells_config.write_cell(col, row, src_cell);
        }
      }
    }
    /////////////////////////
    /*IRS_ASSERT(m_config_calibr.cells_config.get_col_count() ==
      mp_data_handing->table_displ_col_count());
    IRS_ASSERT(m_config_calibr.cells_config.get_row_count() ==
      mp_data_handing->table_displ_row_count());*/

    //irs::mx_rect_t<double> headers_range = mp_data_handing->headers_range();

    NameConfigLE->Text = m_name_config;

    const String device_name = mp_data_handing->get_device_name();
    DeviceNameComboBox->ItemIndex =
      DeviceNameComboBox->Items->IndexOf(device_name);
    const String type = mp_data_handing->get_device_type();
    DeviceComboBox->ItemIndex = DeviceComboBox->Items->IndexOf(type);

    const String ref_device_name = mp_data_handing->get_ref_device_name();
    RefDeviceNameComboBox->ItemIndex =
      RefDeviceNameComboBox->Items->IndexOf(ref_device_name);
    const String ref_type = mp_data_handing->get_ref_device_type();
    RefDeviceComboBox->ItemIndex = RefDeviceComboBox->Items->IndexOf(ref_type);

    config_calibr_out_displ(m_config_calibr);
  }
}

void TNewConfigF::set_config_def()
{
  m_edit_mode = NEW_CONFIG;

  load_devices_list();

  config_calibr_t config_calibr_def;
  config_calibr_def.ip_adress = irst("192.168.0.200");
  config_calibr_def.port = 5005;
  config_calibr_def.in_parameter1.name = irst("Частота");
  config_calibr_def.in_parameter1.unit = irst("Гц");
  config_calibr_def.in_parameter1.type = type_irs_u32;
  config_calibr_def.in_parameter1.anchor = false;
  config_calibr_def.in_parameter1.index = 0;
  config_calibr_def.in_parameter1.koef = 1;

  config_calibr_def.in_parameter2.name = irst("Напряжение");
  config_calibr_def.in_parameter2.unit = irst("В");
  config_calibr_def.in_parameter2.type = type_irs_u32;
  config_calibr_def.in_parameter2.anchor = true;
  config_calibr_def.in_parameter2.index = 0;
  config_calibr_def.in_parameter2.koef = 1;

  config_calibr_def.in_parameter3.name = irst("Фаза");
  config_calibr_def.in_parameter3.unit = irst("градус");
  config_calibr_def.in_parameter3.type = type_irs_u32;
  config_calibr_def.in_parameter3.index = 0;
  config_calibr_def.in_parameter3.koef = 1;

  config_calibr_def.out_parameter.name = irst("Напряжение");
  config_calibr_def.out_parameter.unit = irst("В");
  config_calibr_def.out_parameter.type = type_irs_u32;
  config_calibr_def.out_parameter.index = 0;
  //config_calibr_def.out_parameter.koef_shunt = 1;

  config_calibr_def.index_work_time = 1;
  config_calibr_def.index_pos_eeprom = 1;
  //config_calibr_def.out_param_control_config.enabled = false;
  //config_calibr_def.out_param_control_config.max_relative_difference = 0.00003;
  //config_calibr_def.out_param_control_config.time = 15;
  config_calibr_def.temperature_ctrl_common_cfg.enabled = false;
  config_calibr_def.temperature_ctrl_common_cfg.index = 0;
  //config_calibr_def.temperature_control.reference = 65;
  //config_calibr_def.temperature_control.difference = 0.5;
  //config_calibr_def.index_pos_offset_eeprom = 1;
  //config_calibr_def.max_size_correct = 4096;

  config_calibr_def.bit_pos_mismatch_state.index_byte = 0;
  config_calibr_def.bit_pos_mismatch_state.index_bit = 0;
  config_calibr_def.bit_pos_correct_mode.index_byte = 0;
  config_calibr_def.bit_pos_correct_mode.index_bit = 0;
  config_calibr_def.bit_pos_operating_duty.index_byte = 0;
  config_calibr_def.bit_pos_operating_duty.index_bit = 0;
  config_calibr_def.bit_pos_error_bit.index_byte = 0;
  config_calibr_def.bit_pos_error_bit.index_bit = 0;
  config_calibr_def.bit_pos_reset_over_bit.index_byte = 0;
  config_calibr_def.bit_pos_reset_over_bit.index_bit = 0;
  config_calibr_def.bit_pos_phase_preset_bit.index_byte = 0;
  config_calibr_def.bit_pos_phase_preset_bit.index_bit = 0;

  config_calibr_def.cells_config = config_calibr_t::get_default_cells_config();

  TypeSubDiapasonParam2RB->Checked = true;
  CSpinEdit1->Value = 1;
  SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
  SubDiapasonSG->Cells[0][1] = irst("0");
  SubDiapasonSG->Cells[1][1] = String();
  SubDiapasonSG->Cells[2][1] = String();
  SubDiapasonSG->Cells[3][1] = String();
  SubDiapasonSG->Cells[4][1] = String();

  //config_calibr_def.type_meas = irst("Постоянное напряжение");
  //config_calibr_def.mismatch_mode = true;
  //config_calibr_def.delay_meas = 10;
  //config_calibr_def.meas_interval = 0;
  //config_calibr_def.count_reset_over_bit = 3;
  config_calibr_def.active_filename = String();

  //String name_config = irst("NewConfig");
  String name_config = generate_new_unique_name(irst("Новая конфигурация"));
  m_name_config = name_config;
  NameConfigLE->Text = name_config;
  // Нет смысла сохранять
  /*String file_name = make_config_full_file_name(name_config);
  m_file_name_service.create_config_dir();
  m_config_calibr.save(file_name.c_str());
  mp_data_handing->load_main_device(name_config);
  */

  /*String device_cfg_file_name = make_device_config_full_file_name(name_config);
  irs::ini_file_t ini_file;
  ini_file.set_ini_name(device_cfg_file_name);
  ini_file.set_section(m_device_options_section);
  device_options_t device_options;
  device_options.type = m_device_list.front();

  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);
  ini_file.load();
  if (!FileExists(device_cfg_file_name.c_str())) {
    ini_file.save();
  }
  mp_data_handing->reset_device(device_cfg_file_name.c_str(), device_options);
  */

  m_config_calibr.cells_config = config_calibr_def.cells_config;
  m_cells_range = irs::rect_t(1, 1, 1, 1);

  config_calibr_out_displ(config_calibr_def);
}

void TNewConfigF::load_devices_list()
{
  DeviceNameComboBox->Clear();
  RefDeviceNameComboBox->Clear();

  TSearchRec sr;
  const String dir = m_file_name_service.get_device_config_dir();
  const String ext = m_file_name_service.get_device_config_ext();

  String filter = dir + String(irst("\\*")) + irst(".") + ext;
  if (FindFirst(filter, faAnyFile, sr) == 0) {
    const String name = m_file_name_service.get_config_name(sr.Name);
    DeviceNameComboBox->Items->Add(name);
    RefDeviceNameComboBox->Items->Add(name);
    while (FindNext(sr) == 0) {
      const String name = m_file_name_service.get_config_name(sr.Name);
      DeviceNameComboBox->Items->Add(name);
      RefDeviceNameComboBox->Items->Add(name);
    }
  }

  FindClose(sr);

  /* (DeviceNameComboBox->Items->Count > 0) {
    DeviceNameComboBox->ItemIndex = 0;
  }

  if (RefDeviceNameComboBox->Items->Count > 0) {
    RefDeviceNameComboBox->ItemIndex = 0;
  } */
}

void TNewConfigF::save_configuration(String a_config_name)
{
  /*irs::ini_file_t ini_file;
  ini_file.set_ini_name(a_config_name);
  ini_file.set_section(m_device_options_section);
  device_options_t device_options;

  ini_file.add(irst("enabled"), &device_options.enabled);
  ini_file.add(irst("type"), &device_options.type);
  ini_file.load();
  if (!FileExists(a_file_name.c_str())) {
    ini_file.save();
  } */
}

/*void TNewConfigF::create_configurations_dir()
{
  //String dir = m_path_prog + irst("\\") + m_foldername_conf;
  String dir m_file_name_service.get_config_dir();
  if (!DirectoryExists(dir)) {
    if (!ForceDirectories(dir)) {
      throw Exception(irst("Не удалось создать директорию ") + dir);
    }
  }
} */

// Выгрузка значений параметров на экран
void TNewConfigF::config_calibr_out_displ(
  const config_calibr_t& a_config_calibr)
{
  //IPAdressLE->Text = a_config_calibr.ip_adress;
  //PortLE->Text = num_to_cbstr(a_config_calibr.port);

  irs::stringstream_t ostr;
  ostr << irst("Диапазон - ") << m_cells_range.left << irst(":") <<
    m_cells_range.top << irst(" - ") << m_cells_range.right << irst(":") <<
    m_cells_range.bottom;
  CellsRangeLabel->Caption = irs::str_conv<String>(ostr.str());

  const cell_config_calibr_t cell_config = a_config_calibr.cells_config.
    read_cell(m_cells_range.left, m_cells_range.top);

  String type_meas_str = cell_config.type_meas;
  MeasTypeCB->ItemIndex = get_index_row_combo_box_str(MeasTypeCB,type_meas_str);

  RangeCheckBox->Checked = cell_config.range_enabled;
  RangeEdit->Text = num_to_cbstr(cell_config.range);
  RangeEdit->Enabled = RangeCheckBox->Checked;

  Delay_MeasLE->Text = num_to_cbstr(cell_config.delay_meas);
  MeasIntervalLabeledEdit->Text = num_to_cbstr(cell_config.meas_interval);

  CountResetOverBitLE->Text = num_to_cbstr(cell_config.count_reset_over_bit);

  IndexWorkTimeEdit->Text = num_to_cbstr(a_config_calibr.index_work_time);
  ValueIndexEEPROMEdit->Text = num_to_cbstr(a_config_calibr.index_pos_eeprom);

  ConsiderOutParameterForMeasurementCheckBox->Checked =
    cell_config.out_param_measuring_conf.consider_out_param;
  OutParameterFilterCheckBox->Checked =
    cell_config.out_param_measuring_conf.filter_enabled;
  FilterSamplingTimeEdit->Text = num_to_cbstr(
    cell_config.out_param_measuring_conf.filter_sampling_time);
  FilterPointCountEdit->Text = num_to_cbstr(
    cell_config.out_param_measuring_conf.filter_point_count);

  OutParameterControlCheckBox->Checked =
    cell_config.out_param_control_config.enabled;
  MaxRelativeDifferenceOutParameterLabeledEdit->Text = num_to_cbstr(
    cell_config.out_param_control_config.max_relative_difference);
  TimeCalcDifferenceLabeledEdit->Text = num_to_cbstr(
    cell_config.out_param_control_config.time);

  TemperatureControlVariableCheckBox->Checked =
    a_config_calibr.temperature_ctrl_common_cfg.enabled;
  TemperatureVariableIndexByteLabeledEdit->Text = num_to_cbstr(
    a_config_calibr.temperature_ctrl_common_cfg.index);
  TemperatureControlCheckBox->Checked =
    cell_config.temperature_control.enabled;
  ReferenceTemperetureLabeledEdit->Text = num_to_cbstr(
    cell_config.temperature_control.reference);
  DifferenceTemperatureLabeledEdit->Text = num_to_cbstr(
    cell_config.temperature_control.difference);
  temperature_control_components_update();
  // Загрузка списка параметров
  // Параметр 1
  ListParameterSG->Cells[0][1] = m_config_calibr.in_parameter1.name;
  ListParameterSG->Cells[1][1] = m_config_calibr.in_parameter1.unit;
  ListParameterSG->Cells[2][1] =
    lang_type_to_str(m_config_calibr.in_parameter1.type).c_str();
  ListParameterSG->Cells[3][1] =
    num_to_cbstr(m_config_calibr.in_parameter1.anchor);

  ListParameterSG->Cells[4][1] =
    num_to_cbstr(m_config_calibr.in_parameter1.index);
  //ListParameterSG->Cells[5][1] =
    //num_to_cbstr(m_config_calibr.in_parameter1.koef);
  ListParameterSG->Cells[5][1] = num_to_cbstr(m_config_calibr.in_parameter1.koef);
  ListParameterSG->Cells[7][1] =
    num_to_cbstr(m_config_calibr.in_parameter1.default_val);
  // Параметр 2
  ListParameterSG->Cells[0][2] = m_config_calibr.in_parameter2.name;
  ListParameterSG->Cells[1][2] = m_config_calibr.in_parameter2.unit;
  ListParameterSG->Cells[2][2] =
    lang_type_to_str(m_config_calibr.in_parameter2.type).c_str();
  ListParameterSG->Cells[3][2] =
    num_to_cbstr(m_config_calibr.in_parameter2.anchor);
  ListParameterSG->Cells[4][2] =
    num_to_cbstr(m_config_calibr.in_parameter2.index);
  ListParameterSG->Cells[5][2] = num_to_cbstr(m_config_calibr.in_parameter2.koef);
    //num_to_cbstr(m_config_calibr.in_parameter2.koef);
  ListParameterSG->Cells[7][2] =
    num_to_cbstr(m_config_calibr.in_parameter2.default_val);
  // Параметр 3
  ListParameterSG->Cells[0][3] = m_config_calibr.in_parameter3.name;
  ListParameterSG->Cells[1][3] = m_config_calibr.in_parameter3.unit;
  ListParameterSG->Cells[2][3] =
    lang_type_to_str(m_config_calibr.in_parameter3.type).c_str();
  ListParameterSG->Cells[4][3] =
    num_to_cbstr(m_config_calibr.in_parameter3.index);
  ListParameterSG->Cells[5][3] = num_to_cbstr(m_config_calibr.in_parameter3.koef);
    //num_to_cbstr(m_config_calibr.in_parameter3.koef);
  ListParameterSG->Cells[7][3] =
    num_to_cbstr(m_config_calibr.in_parameter3.default_val);

  // Параметр 4
  ListParameterSG->Cells[0][4] = m_config_calibr.out_parameter.name;
  ListParameterSG->Cells[1][4] = m_config_calibr.out_parameter.unit;
  ListParameterSG->Cells[2][4] =
    lang_type_to_str(m_config_calibr.out_parameter.type).c_str();
  ListParameterSG->Cells[4][4] =
    num_to_cbstr(m_config_calibr.out_parameter.index);
  ListParameterSG->Cells[5][4] = num_to_cbstr(cell_config.output_param_coef);
    //num_to_cbstr(m_config_calibr.out_parameter.koef_shunt);

  // Обработка доп.параметров
  size_type extra_param_count = m_config_calibr.v_parameter_ex.size();
  IRS_ASSERT(extra_param_count == cell_config.ex_param_work_values.size());
  if (extra_param_count > 0) {
    ParamsExCSpinEdit->Value = extra_param_count;
    ListParameterSG->RowCount =
      ParamsExCSpinEdit->Value+m_basic_parameter_count+1;
    for (size_type i = 0; i < extra_param_count; i++) {
      int row = i+m_basic_parameter_count+1;
      // название
      ListParameterSG->Cells[0][row] = m_config_calibr.v_parameter_ex[i].name;
      // единицы измерения
      ListParameterSG->Cells[1][row] =
        m_config_calibr.v_parameter_ex[i].unit;
      // тип переменной
      ListParameterSG->Cells[2][row] =
        lang_type_to_str(m_config_calibr.v_parameter_ex[i].type).c_str();
      // индекс, байт
      ListParameterSG->Cells[4][row] =
        num_to_cbstr(m_config_calibr.v_parameter_ex[i].index);
      // рабочее значение
      ListParameterSG->Cells[6][row] =
        num_to_cbstr(cell_config.ex_param_work_values[i]);
        //m_config_calibr.v_parameter_ex[i].value_working);
      // значение по умолчанию
      ListParameterSG->Cells[7][row] = num_to_cbstr(
        m_config_calibr.v_parameter_ex[i].value_default);
    }
  } else {
    ParamsExCSpinEdit->Value = 1;
    ListParameterSG->RowCount =
      m_basic_parameter_count+ParamsExCSpinEdit->Value+1;
    int row = m_basic_parameter_count+1;
      // название
      ListParameterSG->Cells[0][row] = String();
      // единицы измерения
      ListParameterSG->Cells[1][row] = String();
      // тип переменной
      ListParameterSG->Cells[2][row] = String();
      // индекс, байт
      ListParameterSG->Cells[4][row] = String();
      // коэффициент
      ListParameterSG->Cells[5][row] = String();
      // рабочее значение
      ListParameterSG->Cells[6][row] = String() ;
      // значение по умолчанию
      ListParameterSG->Cells[7][row] = String();
  }

  // Бит готовности регулятора
  ListByteSG->Cells[1][1] = num_to_cbstr(
    a_config_calibr.bit_pos_operating_duty.index_byte);
  ListByteSG->Cells[2][1] = num_to_cbstr(
    a_config_calibr.bit_pos_operating_duty.index_bit);
  // Бит режима расстройки
  ListByteSG->Cells[1][2] = num_to_cbstr(
    a_config_calibr.bit_pos_mismatch_state.index_byte);
  ListByteSG->Cells[2][2] = num_to_cbstr(
    a_config_calibr.bit_pos_mismatch_state.index_bit);
  // Бит режима коррекции
  ListByteSG->Cells[1][3] = num_to_cbstr(
    a_config_calibr.bit_pos_correct_mode.index_byte);
  ListByteSG->Cells[2][3] = num_to_cbstr(
    a_config_calibr.bit_pos_correct_mode.index_bit);
  // Бит ошибки
  ListByteSG->Cells[1][4] = num_to_cbstr(
    a_config_calibr.bit_pos_error_bit.index_byte);
  ListByteSG->Cells[2][4] = num_to_cbstr(
    a_config_calibr.bit_pos_error_bit.index_bit);
  // Бит сброса ошибки
  ListByteSG->Cells[1][5] = num_to_cbstr(
    a_config_calibr.bit_pos_reset_over_bit.index_byte);
  ListByteSG->Cells[2][5] = num_to_cbstr(
    a_config_calibr.bit_pos_reset_over_bit.index_bit);
  // Бит предустановки фазы
  ListByteSG->Cells[1][6] = num_to_cbstr(
    a_config_calibr.bit_pos_phase_preset_bit.index_byte);
  ListByteSG->Cells[2][6] = num_to_cbstr(
    a_config_calibr.bit_pos_phase_preset_bit.index_bit);

  // обработка доп.битов
  size_type bit_type2_count = m_config_calibr.bit_type2_array.size();
  IRS_ASSERT(bit_type2_count == cell_config.ex_bit_work_values.size());

  if (bit_type2_count > 0) {
    BitsExCSpinEdit->Value = bit_type2_count;
    ListByteSG->RowCount = BitsExCSpinEdit->Value+m_basic_bit_count+1;
    for (size_type i = 0; i < bit_type2_count; i++) {
      int row = i+m_basic_bit_count+1;
      ListByteSG->Cells[0][row] =
        m_config_calibr.bit_type2_array[i].bitname.c_str();
      ListByteSG->Cells[1][row] = num_to_cbstr(
        m_config_calibr.bit_type2_array[i].index_byte);
      ListByteSG->Cells[2][row] = num_to_cbstr(
        m_config_calibr.bit_type2_array[i].index_bit);
      ListByteSG->Cells[3][row] = num_to_cbstr(
        cell_config.ex_bit_work_values[i]);
      ListByteSG->Cells[4][row] = num_to_cbstr(
        m_config_calibr.bit_type2_array[i].value_def);
    }
  } else {
    BitsExCSpinEdit->Value = 1;
    ListByteSG->RowCount = m_basic_bit_count+BitsExCSpinEdit->Value+1;
    const int row = m_basic_bit_count+1;
    ListByteSG->Cells[0][row] = String();
    ListByteSG->Cells[1][row] = String();
    ListByteSG->Cells[2][row] = String();
    ListByteSG->Cells[3][row] = String();
    ListByteSG->Cells[4][row] = String();
  }

  if (m_config_calibr.type_sub_diapason == tsd_parameter1) {
    TypeSubDiapasonParam1RB->Checked = true;
  } else {
    TypeSubDiapasonParam2RB->Checked = true;
  }
  int sub_diapason = m_config_calibr.eeprom_ranges.size();
  if (sub_diapason > 0) {
    CSpinEdit1->Value = sub_diapason;
    SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
    for (int i = 0; i < sub_diapason; i++) {
      int row = i+1;
      SubDiapasonSG->Cells[0][row] = num_to_cbstr(i+1);
      SubDiapasonSG->Cells[1][row] = num_to_cbstr(
        m_config_calibr.eeprom_ranges[i].index_start);
      SubDiapasonSG->Cells[2][row] = num_to_cbstr(
        m_config_calibr.eeprom_ranges[i].size);
      SubDiapasonSG->Cells[3][row] = num_to_cbstr(
        m_config_calibr.eeprom_ranges[i].value_begin);
      SubDiapasonSG->Cells[4][row] = num_to_cbstr(
        m_config_calibr.eeprom_ranges[i].value_end);
    }
  } else {
    CSpinEdit1->Value = 1;
    SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
    const int row = 1;
    SubDiapasonSG->Cells[0][row] = irst("1");
    SubDiapasonSG->Cells[1][row] = String();
    SubDiapasonSG->Cells[2][row] = String();
    SubDiapasonSG->Cells[3][row] = String();
    SubDiapasonSG->Cells[4][row] = String();
  }


  ReferenceChannelCheckB->Checked = a_config_calibr.reference_channel.enabled;
  update_ref_device_options();
  //IPAdressRefChannelLE->Text = a_config_calibr.reference_channel.ip_adress;
  /*PortRefChannelLE->Text = num_to_cbstr(
    a_config_calibr.reference_channel.port);*/
}


void __fastcall TNewConfigF::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  if(!m_on_close){
    Action = caNone;
    m_on_close = true;
  }
}
//---------------------------------------------------------------------------


void __fastcall TNewConfigF::ReferenceChannelCheckBClick(TObject *Sender)
{
  if (ReferenceChannelCheckB->Checked == true) {
    update_ref_device();
    //mp_data_handing->load_ref_device(m_name_config);
  }
  update_ref_device_options();
}

void TNewConfigF::update_ref_device_options()
{
  if (ReferenceChannelCheckB->Checked == true) {
    RefDeviceNameComboBox->Enabled = true;
    RefDeviceComboBox->Enabled = true;
    ChangeRefDeviceConfigButton->Enabled = true;
  } else {
    RefDeviceNameComboBox->Enabled = false;
    RefDeviceComboBox->Enabled = false;
    ChangeRefDeviceConfigButton->Enabled = false;
  }
}

void TNewConfigF::update_main_device()
{
  const String device_name = DeviceNameComboBox->Text;
  //m_config_calibr.device_name = device_name;
  const String type = DeviceComboBox->Text;
  mp_data_handing->change_main_device_type(device_name, type);
}

void TNewConfigF::update_ref_device()
{
  const String device_name = RefDeviceNameComboBox->Text;
  //m_config_calibr.reference_device_name = device_name;
  const String type = RefDeviceComboBox->Text;
  mp_data_handing->change_ref_device_type(device_name, type);

  // Тип может быть не задан пользователем,
  // тогда после создания устройства мы берем тип, который задан по умолчанию
  const String ref_type = mp_data_handing->get_ref_device_type();
  RefDeviceComboBox->ItemIndex = RefDeviceComboBox->Items->IndexOf(ref_type);
}

//---------------------------------------------------------------------------

void __fastcall TNewConfigF::CSpinEdit1Change(TObject *Sender)
{
  if (CSpinEdit1->Value > 1000000)
    CSpinEdit1->Value = 1000000;
  else if (CSpinEdit1->Value < 1)
    CSpinEdit1->Value = 1;
  SubDiapasonSG->RowCount = CSpinEdit1->Value+1;

  for (int row = 1, row_end = SubDiapasonSG->RowCount; row < row_end; row++) {
    SubDiapasonSG->Cells[0][row] = IntToStr(row);
  }
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::BitsExCSpinEditChange(TObject *Sender)
{
  if (BitsExCSpinEdit->Value > 1000000)
    BitsExCSpinEdit->Value = 1000000;
  else if (BitsExCSpinEdit->Value < 1)
    BitsExCSpinEdit->Value = 1;
  ListByteSG->RowCount = BitsExCSpinEdit->Value+m_basic_bit_count+1;    
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ListByteSGDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  if ((ARow > 0) && (ARow < m_basic_bit_count+1)) {
    if ((ACol == 0) || (ACol == 3) || (ACol == 4)) {
      draw_cell_illegal(Sender, ACol, ARow, Rect);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ListByteSGSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  if ((ARow > 0) && (ARow < m_basic_bit_count+1)) {
    if ((ACol == 0) || (ACol == 3) || (ACol == 4)) {
      CanSelect = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ParamsExCSpinEditChange(TObject *Sender)
{
  if (ParamsExCSpinEdit->Value > 1000000) {
    ParamsExCSpinEdit->Value = 1000000;
  } else if (ParamsExCSpinEdit->Value < 1) {
    ParamsExCSpinEdit->Value = 1;
  }  
  ListParameterSG->RowCount =
    ParamsExCSpinEdit->Value+m_basic_parameter_count+1;
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ListParameterSGDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
  if (cell_illegal_ListParameterSG_stat(ACol, ARow)) {
    draw_cell_illegal(Sender, ACol, ARow, Rect);
  }
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ListParameterSGSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  /*if (cell_illegal_ListParameterSG_stat(ACol, ARow)) {
    CanSelect = false;
  }*/
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::TemperatureControlVariableCheckBoxClick(
      TObject *Sender)
{
  temperature_control_components_update();
}
//---------------------------------------------------------------------------




void __fastcall TNewConfigF::ConsiderOutParameterForMeasurementCheckBoxClick(
      TObject *Sender)
{
  out_parameter_options_components_update();  
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::OutParameterFilterCheckBoxClick(
      TObject *Sender)
{
  out_parameter_options_components_update();  
}
//---------------------------------------------------------------------------



void __fastcall TNewConfigF::ChangeNameButtonClick(TObject *Sender)
{
  m_name_config = NameConfigLE->Text;
  const String cur_file_name =
    m_file_name_service.make_config_full_file_name(m_name_config);
  String new_config_name = m_name_config;
  while (InputQuery(irst("Введите имя"), irst("Имя конфигурации"),
      new_config_name)) {
    const String new_cfg_file_name =
      m_file_name_service.make_config_full_file_name(new_config_name);

    if (FileExists(new_cfg_file_name)) {
      Application->MessageBox(
        irst("Конфигурация с указанным именем уже существует, ")
        irst("введите другое имя"),
        irst("Имя конфигурации"),
        MB_OK + MB_ICONINFORMATION);
    } else {
      if (m_edit_mode == EXISTENT_CONFIG) {
        if (!RenameFile(cur_file_name, new_cfg_file_name)) {
          Application->MessageBox(irst("Переименовать файл не удалось"),
            irst("Ошибка"), MB_OK + MB_ICONERROR);
          break;
        }
      }

      m_name_config = new_config_name;
      NameConfigLE->Text = new_config_name;
      break;
    }
  }
}

String TNewConfigF::generate_new_unique_name(const String& a_device_name)
{
  int i = 1;
  while (true) {
    const String new_config_name = a_device_name + irst("_") + IntToStr(i);
    const String new_full_file_name =
      make_config_full_file_name(new_config_name);
    if (!FileExists(new_full_file_name)){
      return new_config_name;
    }
    i++;
  }
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ChangeDeviceConfigButtonClick(TObject *Sender)
{
  mp_data_handing->show_main_device_options();
}
//---------------------------------------------------------------------------


void __fastcall TNewConfigF::DeviceComboBoxChange(TObject *Sender)
{
  //String name_config = NameConfigLE->Text;
  update_main_device();
}

//---------------------------------------------------------------------------


void __fastcall TNewConfigF::ExitButtonClick(TObject *Sender)
{
  /*if (m_edit_mode == NEW_CONFIG) {
    mp_data_handing->delete_device_config(m_name_config);
  }*/
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ChangeRefDeviceConfigButtonClick(TObject *Sender)
{
  mp_data_handing->show_ref_device_options();
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::DeviceNameComboBoxChange(TObject *Sender)
{
  update_main_device();
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::RefDeviceNameComboBoxChange(TObject *Sender)
{
  update_ref_device();
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::RefDeviceComboBoxChange(TObject *Sender)
{
  update_ref_device();
}
//---------------------------------------------------------------------------


void __fastcall TNewConfigF::TemperatureControlCheckBoxClick(TObject *Sender)
{
  temperature_control_components_update();
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::RangeCheckBoxClick(TObject *Sender)
{
  RangeEdit->Enabled = RangeCheckBox->Checked;
}
//---------------------------------------------------------------------------


