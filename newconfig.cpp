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
  std::string type_str = "";
  type_str = lang_type_to_str(type);
  for(int i = begin_for; i < end_for; i++){
    type = static_cast<lang_type_t>(i);
    type_str = lang_type_to_str(type);
    ap_combo_box->Items->Add(type_str.c_str());
    //mv_list_combo_box.push_back(type_str.c_str());
  }
  ap_combo_box->ItemIndex = 0;
}
//---------------------------------------------------------------------------
__fastcall TNewConfigF::TNewConfigF(TComponent* Owner)
  : TForm(Owner),
  m_prog_name("Digital interpolator"),
  m_path_prog(""),
  m_default_ext("cpc"),
  m_default_filename("config1.cpc"),
  m_foldername_conf("configuration"),
  m_config_calibr(),
  m_fileid_conf("Конфигурация настроек калибровки."),
  m_name_config(""),
  //mp_conf_device_ini_file(0),
  //mp_config_ini_file(0),
  //mv_list_combo_box(),
  m_edit_mode(NEW_CONFIG),
  m_on_close(true),
  m_name_new_conf("")
{
  SaveDialogConfig->DefaultExt = m_default_ext;
  SaveDialogConfig->Filter =
    "Файлы конфигурации (*."+m_default_ext+")|*."+m_default_ext+
    "|Все файлы (*.*)|*.*";
  SaveDialogConfig->FileName = m_default_filename;

  MeasTypeCB->Items->Clear();
  type_meas_t type_meas = tm_first;
  int index = static_cast<int>(type_meas);
  while(true){
    type_meas = static_cast<type_meas_t>(index);
    irs::string type_meas_str = type_meas_to_str(type_meas);
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
  ((TStringGrid*)Sender)->Canvas->TextOutA(
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
    TemperatureControlCheckBox->Checked;
  ReferenceTemperetureLabeledEdit->Enabled =
    TemperatureControlCheckBox->Checked;
  DifferenceTemperatureLabeledEdit->Enabled =
    TemperatureControlCheckBox->Checked;
}

// Выгрузка списка параметров с экрана в структуру
void __fastcall TNewConfigF::CreateConfigButtonClick(TObject *Sender)
{ 
  std::vector<irs::string> messages;
  m_name_config = NameConfigLE->Text;
  m_config_calibr.ip_adress = IPAdressLE->Text;
  if (!irs::cbuilder::str_to_number(PortLE->Text,  m_config_calibr.port)) {
    messages.push_back("Неверно указан порт.");
  }
  m_config_calibr.type_meas = MeasTypeCB->Text.c_str();
  if (!irs::cbuilder::str_to_number(
    MeasRangeKoefLabeledEdit->Text,
    m_config_calibr.meas_range_koef)) {
    messages.push_back("Неверно указан коэффициент диапазона измерения.");
  }
  if (!irs::cbuilder::str_to_number(
    Delay_MeasLE->Text, m_config_calibr.delay_meas)) {
    messages.push_back("Неверно указана задержка измерения.");
  }
  if (!irs::cbuilder::str_to_number(
    CountResetOverBitLE->Text, m_config_calibr.count_reset_over_bit)) {
    messages.push_back("Неверно указано количество перезапусков измерения.");
  }
  if (!irs::cbuilder::str_to_number(
    IndexWorkTimeEdit->Text, m_config_calibr.index_work_time)) {
    messages.push_back("Неверно указан индекс \"work time\".");
  }
  if (!irs::cbuilder::str_to_number(
    ValueIndexEEPROMEdit->Text, m_config_calibr.index_pos_eeprom)) {
    messages.push_back("Неверно указан индекс \"eeprom\".");
  }

  m_config_calibr.out_param_config_for_measurement.consider_out_param =
    ConsiderOutParameterForMeasurementCheckBox->Checked;
  m_config_calibr.out_param_config_for_measurement.
  out_param_filter_enabled =
    OutParameterFilterCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    FilterSamplingTimeEdit->Text,
    m_config_calibr.out_param_config_for_measurement.filter_sampling_time)) {
    messages.push_back("Неверно указано время дискретизации для фильтра "
      "выходного значения");
  }
  if (!irs::cbuilder::str_to_number(
    FilterPointCountEdit->Text,
    m_config_calibr.out_param_config_for_measurement.filter_point_count)) {
    messages.push_back("Неверно указано время дискретизации для фильтра "
      "выходного значения");
  }

  m_config_calibr.out_param_control_config.enabled =
    OutParameterControlCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    MaxRelativeDifferenceOutParameterLabeledEdit->Text,
    m_config_calibr.out_param_control_config.max_relative_difference)) {
    messages.push_back("Неверно указано допустимое относительное отклонение "
      "выходного параметра");
  }
  if (!irs::cbuilder::str_to_number(
    TimeCalcDifferenceLabeledEdit->Text,
    m_config_calibr.out_param_control_config.time)) {
    messages.push_back("Неверно указано временное окно");
  }

  m_config_calibr.temperature_control.enabled =
    TemperatureControlCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    TemperatureVariableIndexByteLabeledEdit->Text,
    m_config_calibr.temperature_control.index)) {
    messages.push_back("Неверно указан индекс \"температура\".");
  }
  if (!irs::cbuilder::str_to_number(
    ReferenceTemperetureLabeledEdit->Text,
    m_config_calibr.temperature_control.reference)) {
    messages.push_back("Неверно указана уставка температуры");
  }
  if (!irs::cbuilder::str_to_number(
    DifferenceTemperatureLabeledEdit->Text,
    m_config_calibr.temperature_control.difference)) {
    messages.push_back("Неверно указано допустимое отклонение температуры");
  }

  // Выгрузка списка параметров
  // Параметр 1
  m_config_calibr.in_parametr1.name = ListParameterSG->Cells[0][1];

  m_config_calibr.in_parametr1.type_variable = ListParameterSG->Cells[1][1];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][1].c_str(), m_config_calibr.in_parametr1.unit)) {
    messages.push_back("Неверно указан тип параметра 1.");
  }


  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[3][1], m_config_calibr.in_parametr1.anchor)) {
    messages.push_back("Неверно указан тип привязки параметра 1.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][1], m_config_calibr.in_parametr1.index)) {
    messages.push_back("Неверно указан индекс параметра 1.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][1], m_config_calibr.in_parametr1.koef)) {
    messages.push_back("Неверно указан коэффициент параметра 1.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][1], m_config_calibr.in_parametr1.default_val)) {
    messages.push_back("Неверно указано значение по умолчанию параметра 1.");
  }
  // Параметр 2
  m_config_calibr.in_parametr2.name = ListParameterSG->Cells[0][2];
  m_config_calibr.in_parametr2.type_variable = ListParameterSG->Cells[1][2];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][2].c_str(), m_config_calibr.in_parametr2.unit)) {
    messages.push_back("Неверно указан тип параметра 2.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[3][2], m_config_calibr.in_parametr2.anchor)) {
    messages.push_back("Неверно указан тип привязки параметра 2.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][2], m_config_calibr.in_parametr2.index)) {
    messages.push_back("Неверно указан индекс параметра 2.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][2], m_config_calibr.in_parametr2.koef)) {
    messages.push_back("Неверно указан коэффициент параметра 2.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][2], m_config_calibr.in_parametr2.default_val)) {
    messages.push_back("Неверно указано значение по умолчанию параметра 2.");
  }
  // Параметр 3
  m_config_calibr.in_parametr3.name = ListParameterSG->Cells[0][3];
  m_config_calibr.in_parametr3.type_variable = ListParameterSG->Cells[1][3];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][3].c_str(), m_config_calibr.in_parametr3.unit)) {
    messages.push_back("Неверно указан тип параметра 3.");
  }

  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][3], m_config_calibr.in_parametr3.index)) {
    messages.push_back("Неверно указан индекс параметра 3.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][3], m_config_calibr.in_parametr3.koef)) {
    messages.push_back("Неверно указан коэффицинет параметра 3.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][3], m_config_calibr.in_parametr3.default_val)) {
    messages.push_back("Неверно указано значение по умолчанию параметра 3.");
  }

  // Параметр 4
  m_config_calibr.out_parametr.name = ListParameterSG->Cells[0][4];
  m_config_calibr.out_parametr.type_variable = ListParameterSG->Cells[1][4];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][4].c_str(), m_config_calibr.out_parametr.unit)) {
    messages.push_back("Неверно указан тип параметра 3.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][4], m_config_calibr.out_parametr.index)) {
    messages.push_back("Неверно указан индекс параметра 4.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][4], m_config_calibr.out_parametr.koef_shunt)) {
    messages.push_back("Неверно указан коэффициент параметра 4.");
  }

  // обработка доп.параметров
  int parameter_ex_count = ParamsExCSpinEdit->Value;
  m_config_calibr.v_parametr_ex.clear();

  for (int i = 0; i < parameter_ex_count; i++) {
    int row = i+m_basic_parameter_count+1;
    irs::string param_ex_number_str = i;

    parametr_ex_t parametr_ex;
    // название
    parametr_ex.name = ListParameterSG->Cells[0][row];
    // единицы измерения
    parametr_ex.type_variable = ListParameterSG->Cells[1][row];
    if (parametr_ex.name != "") {
      bool all_str_to_number_success = true;
      // тип переменной
      //if (ListParameterSG->Cells[2][row] != "") {
        if (!str_to_lang_type(
          ListParameterSG->Cells[2][row].c_str(), parametr_ex.unit)) {
          all_str_to_number_success = false;
          irs::string message = "Неверно указан тип доп. параметра №"+
            param_ex_number_str + ".";
          messages.push_back(message);
        }
      /*} else {

      }*/
      // индекс
      //if (ListParameterSG->Cells[4][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[4][row], parametr_ex.index))
        {
          all_str_to_number_success = false;
          irs::string message = "Неверно указан индекс доп. параметра №"+
            param_ex_number_str + ".";
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      // рабочее значение
      //if (ListParameterSG->Cells[6][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[6][row], parametr_ex.value_working))
        {
          all_str_to_number_success = false;
          irs::string message =
            "Неверно указано рабочее значение доп. параметра №"+
            param_ex_number_str + ".";
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      // значение по умолчанию
      //f (ListParameterSG->Cells[7][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[7][row], parametr_ex.value_default))
        {
          all_str_to_number_success = false;
          irs::string message =
            "Неверно указано значение по умолчанию доп. параметра №"+
            param_ex_number_str + ".";
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      if (all_str_to_number_success) {
        m_config_calibr.v_parametr_ex.push_back(parametr_ex);
      }
    }
  }

  // Бит готовности регулятора
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][1],
    m_config_calibr.bit_pos_operating_duty.index_byte))
  {
    messages.push_back("Неверно указан индекс байта, "
      "в котором находится бит готовноти регулятора.");
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][1],
    m_config_calibr.bit_pos_operating_duty.index_bit))
  {
    messages.push_back("Неверно указан индекс бита готовноти регулятора.");
  }

  // Бит режима расстройки
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][2],
    m_config_calibr.bit_pos_mismatch_state.index_byte))
  {
    messages.push_back("Неверно указан индекс байта, "
      "в котором находится бит режима расстройки.");
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][2],
    m_config_calibr.bit_pos_mismatch_state.index_bit))
  {
    messages.push_back("Неверно указан индекс бита режима расстройки.");
  }

  // Бит режима коррекции
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][3],
    m_config_calibr.bit_pos_correct_mode.index_byte)) {
    messages.push_back("Неверно указан индекс байта, "
      "в котором находится бит режима коррекции.");
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][3],
    m_config_calibr.bit_pos_correct_mode.index_bit)) {
    messages.push_back("Неверно указан индекс бита режима коррекции.");
  }

  // Бит ошибки
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][4],
    m_config_calibr.bit_pos_error_bit.index_byte)) {
    messages.push_back("Неверно указан индекс байта, "
      "в котором находится бит ошибки.");
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][4],
    m_config_calibr.bit_pos_error_bit.index_bit))
  {
    messages.push_back("Неверно указан индекс бита ошибки.");
  }

  // Бит сброса ошибки
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][5],
    m_config_calibr.bit_pos_reset_over_bit.index_byte))
  {
    messages.push_back("Неверно указан индекс байта, "
      "в котором находится бит сброса ошибки.");
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][5],
    m_config_calibr.bit_pos_reset_over_bit.index_bit))
  {
    messages.push_back("Неверно указан индекс бита сброса ошибки.");
  }

  // Бит предустановки фазы
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][6],
    m_config_calibr.bit_pos_phase_preset_bit.index_byte))
  {
    messages.push_back("Неверно указан индекс байта, "
      "в котором находится бит предустановки фазы.");
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][6],
    m_config_calibr.bit_pos_phase_preset_bit.index_bit))
  {
    messages.push_back("Неверно указан индекс бита предустановки фазы.");
  }

  // Обработка доп.битов
  int bit_type2_count = BitsExCSpinEdit->Value;
  m_config_calibr.bit_type2_array.clear();

  for (int i = 0; i < bit_type2_count; i++) {
    int row = i+m_basic_bit_count+1;
    irs::string bit_ex_index_str = i;
    irs::string bitname_str = ListByteSG->Cells[0][row].c_str();
    bit_type2_pos_t bit_type2_pos;
    bit_type2_pos.bitname = bitname_str;
    if (bitname_str != "") {
      bool all_str_to_number_success = true;
      //if (ListByteSG->Cells[1][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListByteSG->Cells[1][row], bit_type2_pos.index_byte))
        {
          all_str_to_number_success = false;
          irs::string message = "Неверно указан индекс байта, "
            "в котором находится доп. бит №" + bit_ex_index_str + ".";
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
          irs::string message = "Неверно указан индекс доп. бита №" +
            bit_ex_index_str + ".";
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      //if (ListByteSG->Cells[3][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListByteSG->Cells[3][row], bit_type2_pos.value_working))
        {
          all_str_to_number_success = false;
          irs::string message = "Неверно указано рабочее значение доп. бита №" +
            bit_ex_index_str + ".";
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
          irs::string message =
            "Неверно указано значение по умолчанию доп. бита №" +
            bit_ex_index_str + ".";
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/

      if (all_str_to_number_success) {
        m_config_calibr.bit_type2_array.push_back(bit_type2_pos);
      }
    }
  }

  if (TypeSubDiapasonParam1RB->Checked) {
    m_config_calibr.type_sub_diapason = tsd_parameter1;
  } else {
    m_config_calibr.type_sub_diapason = tsd_parameter2;
  }
  int sub_diapason = CSpinEdit1->Value;
  m_config_calibr.v_sub_diapason_calibr.clear();
  for (int i = 0; i < sub_diapason; i++) {
    int row = i+1;
    sub_diapason_calibr_t sub_diapason_calibr;
    irs::string index_start_str = SubDiapasonSG->Cells[1][row].c_str();
    irs::string size_str = SubDiapasonSG->Cells[2][row].c_str();
    irs::string value_begin_str = SubDiapasonSG->Cells[3][row].c_str();
    irs::string value_end_str = SubDiapasonSG->Cells[4][row].c_str();

    if (index_start_str.to_number(sub_diapason_calibr.index_start)) {
      if (size_str.to_number(sub_diapason_calibr.size)) {
        if (value_begin_str.to_number(sub_diapason_calibr.value_begin)) {
          if (value_end_str.to_number(sub_diapason_calibr.value_end)) {
            m_config_calibr.v_sub_diapason_calibr.push_back(
              sub_diapason_calibr);
          }
        }
      }
    }
  }

  m_config_calibr.reference_channel.enabled = ReferenceChannelCheckB->Checked;
  m_config_calibr.reference_channel.ip_adress = IPAdressRefChannelLE->Text;
  irs::cbuilder::str_to_number(
    PortRefChannelLE->Text, m_config_calibr.reference_channel.port);

  if (messages.size() > 0) {
    auto_ptr<TMessagesForm> display_message(new TMessagesForm(NULL));
    display_message->show_messages(messages);
    if (!display_message->Visible) {
      display_message->ShowModal();
      m_on_close = false;
    }
  } else {

    AnsiString filename = m_path_prog+"\\"+m_foldername_conf+"\\"+
    m_name_config+"."+m_default_ext;
    bool on_create_file = true;
    bool dir_config_exists = false;
    m_on_close = false;
    m_name_new_conf = "";
    //определяет, существует ли каталог
    AnsiString dir_config = m_path_prog+"\\"+m_foldername_conf;
    if(!DirectoryExists(dir_config)){
      if(CreateDir(dir_config))
        dir_config_exists = true;
    }else
      dir_config_exists = true;

    if(dir_config_exists){
      //если файл существует
      if(m_edit_mode == NEW_CONFIG){
        if(FileExists(filename)){
          AnsiString message_text = "Файл \""+ filename +"\" уже существует.\n"
            "Хотите его перезаписать?";
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
      }
    }
  }
}
//---------------------------------------------------------------------------
void TNewConfigF::edit_config(const AnsiString& a_filename)
{
  m_edit_mode = EXISTENT_CONFIG;
  if(FileExists(a_filename)){
    m_config_calibr.load(a_filename.c_str());
    m_name_config = extract_short_filename(ExtractFileName(a_filename));
    NameConfigLE->Text = m_name_config;
    config_calibr_out_displ(m_config_calibr);
  }
}
void TNewConfigF::set_config_def()
{
  m_edit_mode = NEW_CONFIG;
  config_calibr_t config_calibr_def;
  config_calibr_def.ip_adress = "192.168.0.200";
  config_calibr_def.port = 5005;
  config_calibr_def.in_parametr1.name = "Частота";
  config_calibr_def.in_parametr1.type_variable = "Гц";
  config_calibr_def.in_parametr1.unit = type_irs_u32;
  config_calibr_def.in_parametr1.anchor = false;
  config_calibr_def.in_parametr1.index = 0;
  config_calibr_def.in_parametr1.koef = 1;

  config_calibr_def.in_parametr2.name = "Напряжение";
  config_calibr_def.in_parametr2.type_variable = "В";
  config_calibr_def.in_parametr2.unit = type_irs_u32;
  config_calibr_def.in_parametr2.anchor = true;
  config_calibr_def.in_parametr2.index = 0;
  config_calibr_def.in_parametr2.koef = 1;

  config_calibr_def.in_parametr3.name = "Фаза";
  config_calibr_def.in_parametr3.type_variable = "градус";
  config_calibr_def.in_parametr3.unit = type_irs_u32;
  config_calibr_def.in_parametr3.index = 0;
  config_calibr_def.in_parametr3.koef = 1;

  config_calibr_def.out_parametr.name = "Напряжение";
  config_calibr_def.out_parametr.type_variable = "В";
  config_calibr_def.out_parametr.unit = type_irs_u32;
  config_calibr_def.out_parametr.index = 0;
  config_calibr_def.out_parametr.koef_shunt = 1;

  config_calibr_def.index_work_time = 1;
  config_calibr_def.index_pos_eeprom = 1;
  config_calibr_def.out_param_control_config.enabled = false;
  config_calibr_def.out_param_control_config.max_relative_difference = 0.00003;
  config_calibr_def.out_param_control_config.time = 15;
  config_calibr_def.temperature_control.enabled = false;
  config_calibr_def.temperature_control.index = 0;
  config_calibr_def.temperature_control.reference = 65;
  config_calibr_def.temperature_control.difference = 0.5;
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

  TypeSubDiapasonParam2RB->Checked = true;
  CSpinEdit1->Value = 1;
  SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
  SubDiapasonSG->Cells[0][1] = "0";
  SubDiapasonSG->Cells[1][1] = "";
  SubDiapasonSG->Cells[2][1] = "";
  SubDiapasonSG->Cells[3][1] = "";
  SubDiapasonSG->Cells[4][1] = "";

  //config_calibr_def.mismatch_mode = true;
  config_calibr_def.meas_range_koef = 1.;
  config_calibr_def.delay_meas = 10;
  config_calibr_def.type_meas = "Постоянное напряжение";
  config_calibr_def.count_reset_over_bit = 3;
  config_calibr_def.active_filename = "";

  AnsiString name_config = "NewConfig";
  NameConfigLE->Text = name_config;
  config_calibr_out_displ(config_calibr_def);

}

// Выгрузка значений параметров на экран
void TNewConfigF::config_calibr_out_displ(
  const config_calibr_t& a_config_calibr)
{
  IPAdressLE->Text = a_config_calibr.ip_adress;
  PortLE->Text = irs::cbuilder::number_to_str(a_config_calibr.port);

  AnsiString type_meas_str = a_config_calibr.type_meas;
  MeasTypeCB->ItemIndex =
    get_index_row_combo_box_str(MeasTypeCB,type_meas_str);

  MeasRangeKoefLabeledEdit->Text =
    irs::cbuilder::number_to_str(a_config_calibr.meas_range_koef);
  Delay_MeasLE->Text =
    irs::cbuilder::number_to_str(a_config_calibr.delay_meas);

  CountResetOverBitLE->Text = irs::cbuilder::number_to_str(
    a_config_calibr.count_reset_over_bit);
  IndexWorkTimeEdit->Text = irs::cbuilder::number_to_str(
    a_config_calibr.index_work_time);
  ValueIndexEEPROMEdit->Text = irs::cbuilder::number_to_str(
    a_config_calibr.index_pos_eeprom);

  ConsiderOutParameterForMeasurementCheckBox->Checked =
    m_config_calibr.out_param_config_for_measurement.
    consider_out_param;
  OutParameterFilterCheckBox->Checked =
    m_config_calibr.out_param_config_for_measurement.
    out_param_filter_enabled;
  FilterSamplingTimeEdit->Text = irs::cbuilder::number_to_str(
    m_config_calibr.out_param_config_for_measurement.filter_sampling_time);
  FilterPointCountEdit->Text = irs::cbuilder::number_to_str(
    m_config_calibr.out_param_config_for_measurement.filter_point_count);

  OutParameterControlCheckBox->Checked =
    m_config_calibr.out_param_control_config.enabled;
  MaxRelativeDifferenceOutParameterLabeledEdit->Text =
    irs::cbuilder::number_to_str(
    a_config_calibr.out_param_control_config.max_relative_difference);
  TimeCalcDifferenceLabeledEdit->Text = irs::cbuilder::number_to_str(
    a_config_calibr.out_param_control_config.time);

  TemperatureControlCheckBox->Checked =
    a_config_calibr.temperature_control.enabled;
  TemperatureVariableIndexByteLabeledEdit->Text = irs::cbuilder::number_to_str(
    a_config_calibr.temperature_control.index);
  ReferenceTemperetureLabeledEdit->Text = irs::cbuilder::number_to_str(
    a_config_calibr.temperature_control.reference);
  DifferenceTemperatureLabeledEdit->Text = irs::cbuilder::number_to_str(
    a_config_calibr.temperature_control.difference);  
  temperature_control_components_update();
  // Загрузка списка параметров
  // Параметр 1
  ListParameterSG->Cells[0][1] = m_config_calibr.in_parametr1.name;
  ListParameterSG->Cells[1][1] = m_config_calibr.in_parametr1.type_variable;
  ListParameterSG->Cells[2][1] =
    lang_type_to_str(m_config_calibr.in_parametr1.unit).c_str();
  ListParameterSG->Cells[3][1] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr1.anchor);

  ListParameterSG->Cells[4][1] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr1.index);
  ListParameterSG->Cells[5][1] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr1.koef);
  ListParameterSG->Cells[7][1] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr1.default_val);
  // Параметр 2
  ListParameterSG->Cells[0][2] = m_config_calibr.in_parametr2.name;
  ListParameterSG->Cells[1][2] = m_config_calibr.in_parametr2.type_variable;
  ListParameterSG->Cells[2][2] =
    lang_type_to_str(m_config_calibr.in_parametr2.unit).c_str();
  ListParameterSG->Cells[3][2] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr2.anchor);
  ListParameterSG->Cells[4][2] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr2.index);
  ListParameterSG->Cells[5][2] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr2.koef);
  ListParameterSG->Cells[7][2] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr2.default_val);
  // Параметр 3
  ListParameterSG->Cells[0][3] = m_config_calibr.in_parametr3.name;
  ListParameterSG->Cells[1][3] = m_config_calibr.in_parametr3.type_variable;
  ListParameterSG->Cells[2][3] =
    lang_type_to_str(m_config_calibr.in_parametr3.unit).c_str();
  ListParameterSG->Cells[4][3] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr3.index);
  ListParameterSG->Cells[5][3] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr3.koef);
  ListParameterSG->Cells[7][3] =
    irs::cbuilder::number_to_str(m_config_calibr.in_parametr3.default_val);

  // Параметр 4
  ListParameterSG->Cells[0][4] = m_config_calibr.out_parametr.name;
  ListParameterSG->Cells[1][4] = m_config_calibr.out_parametr.type_variable;
  ListParameterSG->Cells[2][4] =
    lang_type_to_str(m_config_calibr.out_parametr.unit).c_str();
  ListParameterSG->Cells[4][4] =
    irs::cbuilder::number_to_str(m_config_calibr.out_parametr.index);
  ListParameterSG->Cells[5][4] =
    irs::cbuilder::number_to_str(m_config_calibr.out_parametr.koef_shunt);

  // Обработка доп.параметров
  int parameter_ex_count = m_config_calibr.v_parametr_ex.size();
  if (parameter_ex_count > 0) {
    ParamsExCSpinEdit->Value = parameter_ex_count;
    ListParameterSG->RowCount =
      ParamsExCSpinEdit->Value+m_basic_parameter_count+1;
    for (int i  = 0; i < parameter_ex_count; i++) {
      int row = i+m_basic_parameter_count+1;
      // название
      ListParameterSG->Cells[0][row] = m_config_calibr.v_parametr_ex[i].name;
      // единицы измерения
      ListParameterSG->Cells[1][row] =
        m_config_calibr.v_parametr_ex[i].type_variable;
      // тип переменной
      ListParameterSG->Cells[2][row] =
        lang_type_to_str(m_config_calibr.v_parametr_ex[i].unit).c_str();
      // индекс, байт
      ListParameterSG->Cells[4][row] =
        irs::cbuilder::number_to_str(m_config_calibr.v_parametr_ex[i].index);
      // рабочее значение
      ListParameterSG->Cells[6][row] = irs::cbuilder::number_to_str(
        m_config_calibr.v_parametr_ex[i].value_working);
      // значение по умолчанию
      ListParameterSG->Cells[7][row] = irs::cbuilder::number_to_str(
        m_config_calibr.v_parametr_ex[i].value_default);
    }
  } else {
    ParamsExCSpinEdit->Value = 1;
    ListParameterSG->RowCount =
      m_basic_parameter_count+ParamsExCSpinEdit->Value+1;
    int row = m_basic_parameter_count+1;
      // название
      ListParameterSG->Cells[0][row] = "";
      // единицы измерения
      ListParameterSG->Cells[1][row] = "";
      // тип переменной
      ListParameterSG->Cells[2][row] = "";
      // индекс, байт
      ListParameterSG->Cells[4][row] = "";
      // коэффициент
      ListParameterSG->Cells[5][row] = "";
      // рабочее значение
      ListParameterSG->Cells[6][row] = "" ;
      // значение по умолчанию
      ListParameterSG->Cells[7][row] = "";
  }

  // Бит готовности регулятора
  ListByteSG->Cells[1][1] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_operating_duty.index_byte);
  ListByteSG->Cells[2][1] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_operating_duty.index_bit);
  // Бит режима расстройки
  ListByteSG->Cells[1][2] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_mismatch_state.index_byte);
  ListByteSG->Cells[2][2] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_mismatch_state.index_bit);
  // Бит режима коррекции
  ListByteSG->Cells[1][3] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_correct_mode.index_byte);
  ListByteSG->Cells[2][3] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_correct_mode.index_bit);
  // Бит ошибки
  ListByteSG->Cells[1][4] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_error_bit.index_byte);
  ListByteSG->Cells[2][4] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_error_bit.index_bit);
  // Бит сброса ошибки
  ListByteSG->Cells[1][5] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_reset_over_bit.index_byte);
  ListByteSG->Cells[2][5] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_reset_over_bit.index_bit);
  // Бит предустановки фазы
  ListByteSG->Cells[1][6] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_phase_preset_bit.index_byte);
  ListByteSG->Cells[2][6] = irs::cbuilder::number_to_str(
    a_config_calibr.bit_pos_phase_preset_bit.index_bit);

  // обработка доп.битов
  int bit_type2_count = m_config_calibr.bit_type2_array.size();

  if (bit_type2_count > 0) {
    BitsExCSpinEdit->Value = bit_type2_count;
    ListByteSG->RowCount = BitsExCSpinEdit->Value+m_basic_bit_count+1;
    for (int i = 0; i < bit_type2_count; i++) {
      int row = i+m_basic_bit_count+1;
      ListByteSG->Cells[0][row] =
        m_config_calibr.bit_type2_array[i].bitname.c_str();
      ListByteSG->Cells[1][row] = irs::cbuilder::number_to_str(
        m_config_calibr.bit_type2_array[i].index_byte);
      ListByteSG->Cells[2][row] = irs::cbuilder::number_to_str(
        m_config_calibr.bit_type2_array[i].index_bit);
      ListByteSG->Cells[3][row] = irs::cbuilder::number_to_str(
        m_config_calibr.bit_type2_array[i].value_working);
      ListByteSG->Cells[4][row] = irs::cbuilder::number_to_str(
        m_config_calibr.bit_type2_array[i].value_def);
    }
  } else {
    BitsExCSpinEdit->Value = 1;
    ListByteSG->RowCount = m_basic_bit_count+BitsExCSpinEdit->Value+1;
    const int row = m_basic_bit_count+1;
    ListByteSG->Cells[0][row] = "";
    ListByteSG->Cells[1][row] = "";
    ListByteSG->Cells[2][row] = "";
    ListByteSG->Cells[3][row] = "";
    ListByteSG->Cells[4][row] = "";
  }

  if (m_config_calibr.type_sub_diapason == tsd_parameter1) {
    TypeSubDiapasonParam1RB->Checked = true;
  } else {
    TypeSubDiapasonParam2RB->Checked = true;
  }
  int sub_diapason = m_config_calibr.v_sub_diapason_calibr.size();
  if (sub_diapason > 0) {
    CSpinEdit1->Value = sub_diapason;
    SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
    for (int i = 0; i < sub_diapason; i++) {
      int row = i+1;
      SubDiapasonSG->Cells[0][row] = irs::cbuilder::number_to_str(i+1);
      SubDiapasonSG->Cells[1][row] = irs::cbuilder::number_to_str(
        m_config_calibr.v_sub_diapason_calibr[i].index_start);
      SubDiapasonSG->Cells[2][row] = irs::cbuilder::number_to_str(
        m_config_calibr.v_sub_diapason_calibr[i].size);
      SubDiapasonSG->Cells[3][row] = irs::cbuilder::number_to_str(
        m_config_calibr.v_sub_diapason_calibr[i].value_begin);
      SubDiapasonSG->Cells[4][row] = irs::cbuilder::number_to_str(
        m_config_calibr.v_sub_diapason_calibr[i].value_end);
    }
  } else {
    CSpinEdit1->Value = 1;
    SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
    const int row = 1;
    SubDiapasonSG->Cells[0][row] = "1";
    SubDiapasonSG->Cells[1][row] = "";
    SubDiapasonSG->Cells[2][row] = "";
    SubDiapasonSG->Cells[3][row] = "";
    SubDiapasonSG->Cells[4][row] = "";
  }


  ReferenceChannelCheckB->Checked = a_config_calibr.reference_channel.enabled;
  IPAdressRefChannelLE->Text = a_config_calibr.reference_channel.ip_adress;
  PortRefChannelLE->Text = irs::cbuilder::number_to_str(
    a_config_calibr.reference_channel.port);
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
  if (ReferenceChannelCheckB->Checked == true){
    IPAdressRefChannelLE->Enabled = true;
    PortRefChannelLE->Enabled = true;
  } else {
    IPAdressRefChannelLE->Enabled = false;
    PortRefChannelLE->Enabled = false;
  }
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

void __fastcall TNewConfigF::TemperatureControlCheckBoxClick(
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

