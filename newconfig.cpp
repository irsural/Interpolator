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
  //m_fileid_conf(irst("������������ �������� ����������.")),
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
    irst("����� ������������ (*.") + m_default_ext + irst(")|*.") +
      m_default_ext +
      irst("|��� ����� (*.*)|*.*");
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
  // ��������� ������ ����������
  ListParameterSG->Col = 0;
  ListParameterSG->Row = 1;
  ListParameterSG->RowCount = m_basic_parameter_count+1;
  ListParameterSG->Cells[0][0] = "��������*";
  ListParameterSG->Cells[1][0] = "������� ���������";
  ListParameterSG->Cells[2][0] = "��� ����������*";
  ListParameterSG->Cells[3][0] = "��������*";
  ListParameterSG->Cells[4][0] = "������, ����*";
  ListParameterSG->Cells[5][0] = "�����������*";
  ListParameterSG->Cells[6][0] = "������� ��������*";
  ListParameterSG->Cells[7][0] = "�������� �� ���������*";

  ListParameterSG->Cells[0][1] = "�������� 1";
  ListParameterSG->Cells[0][2] = "�������� 2";
  ListParameterSG->Cells[0][3] = "�������� 3";
  ListParameterSG->Cells[0][4] = "�������� 4";
  ParamsExCSpinEdit->Value = 1;

  // ��������� ������ �����
  ListByteSG->Col = 0;
  ListByteSG->Row = m_basic_bit_count+1;
  ListByteSG->RowCount = m_basic_bit_count+1;

  ListByteSG->Cells[0][0] = "��������*";
  ListByteSG->Cells[1][0] = "������, ����*";
  ListByteSG->Cells[2][0] = "������, ���(0-7)*";
  ListByteSG->Cells[3][0] = "������� ��������*";
  ListByteSG->Cells[4][0] = "�������� �� ���������*";

  ListByteSG->Cells[0][1] = "��� ���������� ����������";
  ListByteSG->Cells[0][2] = "��� ������ ����������";
  ListByteSG->Cells[0][3] = "��� ������ ���������";
  ListByteSG->Cells[0][4] = "��� ������";
  ListByteSG->Cells[0][5] = "��� ������ ������";
  ListByteSG->Cells[0][6] = "��� ������������� ����";
  //ListByteSG->Cells[0][7] = "��� ��������� ������";

  // ��������� ������ ���������� EEPROM
  TypeSubDiapasonParam2RB->Checked = true;
  CSpinEdit1->Value = 1;
  SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
  SubDiapasonSG->Cells[0][0] = "�����*";
  SubDiapasonSG->Cells[1][0] = "�. ������*";
  SubDiapasonSG->Cells[2][0] = "������*";
  SubDiapasonSG->Cells[3][0] = "�. ����.*";
  SubDiapasonSG->Cells[4][0] = "�. ����.*";
  SubDiapasonSG->Cells[0][1] = "1";
  SubDiapasonSG->Cells[1][1] = "";
  SubDiapasonSG->Cells[2][1] = "";
  SubDiapasonSG->Cells[3][1] = "";
  SubDiapasonSG->Cells[4][1] = "";
}

void TNewConfigF::draw_cell_illegal(
  TObject *Sender, int ACol, int ARow, TRect &Rect)
{
  //���� ����
  ((TStringGrid*)Sender)->Canvas->Brush->Color = clBtnFace;//clMoneyGreen;
  //���� ������
  ((TStringGrid*)Sender)->Canvas->Font->Color = clBlack;
  //�������� ���
  ((TStringGrid*)Sender)->Canvas->FillRect(Rect);
  //������ �����
  ((TStringGrid*)Sender)->Canvas->TextOutA(
    Rect.Left, Rect.Top, ((TStringGrid*)Sender)->Cells[ACol][ARow]);
}
bool TNewConfigF::cell_illegal_ListParameterSG_stat(
  const int a_col, const int a_row)
{
  bool cell_illegal_stat =false;
  // ���������� ������ "�������� �� ���������" ��� ����������� ����������
  if ((a_row > 0) && (a_row < m_basic_parameter_count+1)) {
    if (a_col == 6) {
      cell_illegal_stat = true;
    }
  }
  // ���������� ������ "��������" ��� �������� � ���������� ����������
  if (a_row > 2) {
    if (a_col == 3) {
      cell_illegal_stat = true;
    }
  }
  // ���������� ������ "�����������" ��� �����������-����������� ����������
  if (a_row > m_basic_parameter_count) {
    if (a_col == 5) {
      cell_illegal_stat = true;
    }
  }
  // ���������� ������ "�������� �� ���������" ��� ���������� ���������
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

// �������� ������ ���������� � ������ � ���������
void __fastcall TNewConfigF::CreateConfigButtonClick(TObject *Sender)
{ 
  std::vector<string_type> messages;
  m_name_config = NameConfigLE->Text;
  //m_config_calibr.ip_adress = IPAdressLE->Text;
  /*if (!irs::cbuilder::str_to_number(PortLE->Text,  m_config_calibr.port)) {
    messages.push_back(irst("������� ������ ����."));
  }*/

  m_config_calibr.type_meas = MeasTypeCB->Text.c_str();
  if (!irs::cbuilder::str_to_number(
    MeasRangeKoefLabeledEdit->Text,
    m_config_calibr.meas_range_koef)) {
    messages.push_back(irst("������� ������ ����������� ��������� ���������."));
  }
  if (!irs::cbuilder::str_to_number(
    Delay_MeasLE->Text, m_config_calibr.delay_meas)) {
    messages.push_back(irst("������� ������� �������� ���������."));
  }
  if (!irs::cbuilder::str_to_number(
    CountResetOverBitLE->Text, m_config_calibr.count_reset_over_bit)) {
    messages.push_back(
      irst("������� ������� ���������� ������������ ���������."));
  }
  if (!irs::cbuilder::str_to_number(
    IndexWorkTimeEdit->Text, m_config_calibr.index_work_time)) {
    messages.push_back(irst("������� ������ ������ \"work time\"."));
  }
  if (!irs::cbuilder::str_to_number(
    ValueIndexEEPROMEdit->Text, m_config_calibr.index_pos_eeprom)) {
    messages.push_back(irst("������� ������ ������ \"eeprom\"."));
  }

  m_config_calibr.out_param_config_for_measurement.consider_out_param =
    ConsiderOutParameterForMeasurementCheckBox->Checked;
  m_config_calibr.out_param_config_for_measurement.
  out_param_filter_enabled =
    OutParameterFilterCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    FilterSamplingTimeEdit->Text,
    m_config_calibr.out_param_config_for_measurement.filter_sampling_time)) {
    messages.push_back(irst("������� ������� ����� ������������� ��� ������� ")
      irst("��������� ��������"));
  }
  if (!irs::cbuilder::str_to_number(
    FilterPointCountEdit->Text,
    m_config_calibr.out_param_config_for_measurement.filter_point_count)) {
    messages.push_back(irst("������� ������� ����� ������������� ��� ������� ")
      irst("��������� ��������"));
  }

  m_config_calibr.out_param_control_config.enabled =
    OutParameterControlCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    MaxRelativeDifferenceOutParameterLabeledEdit->Text,
    m_config_calibr.out_param_control_config.max_relative_difference)) {
    messages.push_back(
      irst("������� ������� ���������� ������������� ���������� ")
      irst("��������� ���������"));
  }
  if (!irs::cbuilder::str_to_number(
    TimeCalcDifferenceLabeledEdit->Text,
    m_config_calibr.out_param_control_config.time)) {
    messages.push_back(irst("������� ������� ��������� ����"));
  }

  m_config_calibr.temperature_control.enabled =
    TemperatureControlCheckBox->Checked;
  if (!irs::cbuilder::str_to_number(
    TemperatureVariableIndexByteLabeledEdit->Text,
    m_config_calibr.temperature_control.index)) {
    messages.push_back(irst("������� ������ ������ \"�����������\"."));
  }
  if (!irs::cbuilder::str_to_number(
    ReferenceTemperetureLabeledEdit->Text,
    m_config_calibr.temperature_control.reference)) {
    messages.push_back(irst("������� ������� ������� �����������"));
  }
  if (!irs::cbuilder::str_to_number(
    DifferenceTemperatureLabeledEdit->Text,
    m_config_calibr.temperature_control.difference)) {
    messages.push_back(
      irst("������� ������� ���������� ���������� �����������"));
  }

  // �������� ������ ����������
  // �������� 1
  m_config_calibr.in_parametr1.name = ListParameterSG->Cells[0][1];

  m_config_calibr.in_parametr1.type_variable = ListParameterSG->Cells[1][1];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][1].c_str(), m_config_calibr.in_parametr1.unit)) {
    messages.push_back(irst("������� ������ ��� ��������� 1."));
  }


  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[3][1], m_config_calibr.in_parametr1.anchor)) {
    messages.push_back(irst("������� ������ ��� �������� ��������� 1."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][1], m_config_calibr.in_parametr1.index)) {
    messages.push_back(irst("������� ������ ������ ��������� 1."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][1], m_config_calibr.in_parametr1.koef)) {
    messages.push_back(irst("������� ������ ����������� ��������� 1."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][1], m_config_calibr.in_parametr1.default_val)) {
    messages.push_back(
      irst("������� ������� �������� �� ��������� ��������� 1."));
  }
  // �������� 2
  m_config_calibr.in_parametr2.name = ListParameterSG->Cells[0][2];
  m_config_calibr.in_parametr2.type_variable = ListParameterSG->Cells[1][2];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][2].c_str(), m_config_calibr.in_parametr2.unit)) {
    messages.push_back(irst("������� ������ ��� ��������� 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[3][2], m_config_calibr.in_parametr2.anchor)) {
    messages.push_back(irst("������� ������ ��� �������� ��������� 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][2], m_config_calibr.in_parametr2.index)) {
    messages.push_back(irst("������� ������ ������ ��������� 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][2], m_config_calibr.in_parametr2.koef)) {
    messages.push_back(irst("������� ������ ����������� ��������� 2."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][2], m_config_calibr.in_parametr2.default_val)) {
    messages.push_back(
      irst("������� ������� �������� �� ��������� ��������� 2."));
  }
  // �������� 3
  m_config_calibr.in_parametr3.name = ListParameterSG->Cells[0][3];
  m_config_calibr.in_parametr3.type_variable = ListParameterSG->Cells[1][3];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][3].c_str(), m_config_calibr.in_parametr3.unit)) {
    messages.push_back(irst("������� ������ ��� ��������� 3."));
  }

  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][3], m_config_calibr.in_parametr3.index)) {
    messages.push_back(irst("������� ������ ������ ��������� 3."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][3], m_config_calibr.in_parametr3.koef)) {
    messages.push_back("������� ������ ����������� ��������� 3.");
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[7][3], m_config_calibr.in_parametr3.default_val)) {
    messages.push_back(
      irst("������� ������� �������� �� ��������� ��������� 3."));
  }

  // �������� 4
  m_config_calibr.out_parametr.name = ListParameterSG->Cells[0][4];
  m_config_calibr.out_parametr.type_variable = ListParameterSG->Cells[1][4];
  if (!str_to_lang_type(
    ListParameterSG->Cells[2][4].c_str(), m_config_calibr.out_parametr.unit)) {
    messages.push_back(irst("������� ������ ��� ��������� 3."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[4][4], m_config_calibr.out_parametr.index)) {
    messages.push_back(irst("������� ������ ������ ��������� 4."));
  }
  if (!irs::cbuilder::str_to_number(
    ListParameterSG->Cells[5][4], m_config_calibr.out_parametr.koef_shunt)) {
    messages.push_back(irst("������� ������ ����������� ��������� 4."));
  }

  // ��������� ���.����������
  int parameter_ex_count = ParamsExCSpinEdit->Value;
  m_config_calibr.v_parametr_ex.clear();

  for (int i = 0; i < parameter_ex_count; i++) {
    int row = i+m_basic_parameter_count+1;
    string_type param_ex_number_str = i;

    parametr_ex_t parametr_ex;
    // ��������
    parametr_ex.name = ListParameterSG->Cells[0][row];
    // ������� ���������
    parametr_ex.type_variable = ListParameterSG->Cells[1][row];
    if (!parametr_ex.name.IsEmpty()) {
      bool all_str_to_number_success = true;
      // ��� ����������
      //if (ListParameterSG->Cells[2][row] != "") {
        if (!str_to_lang_type(
          ListParameterSG->Cells[2][row].c_str(), parametr_ex.unit)) {
          all_str_to_number_success = false;
          string_type message = irst("������� ������ ��� ���. ��������� �") +
            param_ex_number_str + irst(".");
          messages.push_back(message);
        }
      /*} else {

      }*/
      // ������
      //if (ListParameterSG->Cells[4][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[4][row], parametr_ex.index))
        {
          all_str_to_number_success = false;
          string_type message = irst("������� ������ ������ ���. ��������� �") +
            param_ex_number_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      // ������� ��������
      //if (ListParameterSG->Cells[6][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[6][row], parametr_ex.value_working))
        {
          all_str_to_number_success = false;
          string_type message =
            irst("������� ������� ������� �������� ���. ��������� �") +
            param_ex_number_str + irst(".");
          messages.push_back(message);
        }
      /*} else {
        all_str_to_number_success = false;
      }*/
      // �������� �� ���������
      //f (ListParameterSG->Cells[7][row] != "") {
        if (!irs::cbuilder::str_to_number(
          ListParameterSG->Cells[7][row], parametr_ex.value_default))
        {
          all_str_to_number_success = false;
          string_type message =
            irst("������� ������� �������� �� ��������� ���. ��������� �") +
            param_ex_number_str + irst(".");
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

  // ��� ���������� ����������
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][1],
    m_config_calibr.bit_pos_operating_duty.index_byte))
  {
    messages.push_back(irst("������� ������ ������ �����, ")
      irst("� ������� ��������� ��� ��������� ����������."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][1],
    m_config_calibr.bit_pos_operating_duty.index_bit))
  {
    messages.push_back(
      irst("������� ������ ������ ���� ��������� ����������."));
  }

  // ��� ������ ����������
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][2],
    m_config_calibr.bit_pos_mismatch_state.index_byte))
  {
    messages.push_back(irst("������� ������ ������ �����, ")
      irst("� ������� ��������� ��� ������ ����������."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][2],
    m_config_calibr.bit_pos_mismatch_state.index_bit))
  {
    messages.push_back(irst("������� ������ ������ ���� ������ ����������."));
  }

  // ��� ������ ���������
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][3],
    m_config_calibr.bit_pos_correct_mode.index_byte)) {
    messages.push_back(irst("������� ������ ������ �����, ")
      irst("� ������� ��������� ��� ������ ���������."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][3],
    m_config_calibr.bit_pos_correct_mode.index_bit)) {
    messages.push_back(irst("������� ������ ������ ���� ������ ���������."));
  }

  // ��� ������
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][4],
    m_config_calibr.bit_pos_error_bit.index_byte)) {
    messages.push_back(irst("������� ������ ������ �����, ")
      irst("� ������� ��������� ��� ������."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][4],
    m_config_calibr.bit_pos_error_bit.index_bit))
  {
    messages.push_back(irst("������� ������ ������ ���� ������."));
  }

  // ��� ������ ������
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][5],
    m_config_calibr.bit_pos_reset_over_bit.index_byte))
  {
    messages.push_back(irst("������� ������ ������ �����, ")
      irst("� ������� ��������� ��� ������ ������."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][5],
    m_config_calibr.bit_pos_reset_over_bit.index_bit))
  {
    messages.push_back(irst("������� ������ ������ ���� ������ ������."));
  }

  // ��� ������������� ����
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[1][6],
    m_config_calibr.bit_pos_phase_preset_bit.index_byte))
  {
    messages.push_back(irst("������� ������ ������ �����, ")
      irst("� ������� ��������� ��� ������������� ����."));
  }
  if (!irs::cbuilder::str_to_number(ListByteSG->Cells[2][6],
    m_config_calibr.bit_pos_phase_preset_bit.index_bit))
  {
    messages.push_back(irst("������� ������ ������ ���� ������������� ����."));
  }

  // ��������� ���.�����
  int bit_type2_count = BitsExCSpinEdit->Value;
  m_config_calibr.bit_type2_array.clear();

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
          string_type message = irst("������� ������ ������ �����, ")
            irst("� ������� ��������� ���. ��� �") + bit_ex_index_str +
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
          string_type message = irst("������� ������ ������ ���. ���� �") +
            bit_ex_index_str + irst(".");
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
          string_type message =
            irst("������� ������� ������� �������� ���. ���� �") +
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
            irst("������� ������� �������� �� ��������� ���. ���� �") +
            bit_ex_index_str + irst(".");
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
    string_type index_start_str = SubDiapasonSG->Cells[1][row].c_str();
    string_type size_str = SubDiapasonSG->Cells[2][row].c_str();
    string_type value_begin_str = SubDiapasonSG->Cells[3][row].c_str();
    string_type value_end_str = SubDiapasonSG->Cells[4][row].c_str();

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
  //m_config_calibr.reference_channel.ip_adress = IPAdressRefChannelLE->Text;
  /*irs::cbuilder::str_to_number(
    PortRefChannelLE->Text, m_config_calibr.reference_channel.port);*/

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
    const String filename =
      m_file_name_service.make_config_full_file_name(m_name_config);
    m_name_new_conf = m_name_config;
    m_config_calibr.save(filename.c_str());
    m_on_close = true;
    /*bool on_create_file = true;
    m_on_close = false;
    m_name_new_conf = String();
    //create_configurations_dir();
    m_file_name_service.create_config_dir();
    //���� ���� ����������
    if(m_edit_mode == NEW_CONFIG){
      if(FileExists(filename)){
        String message_text = irst("���� \"") + filename +
          irst("\" ��� ����������.\n")
          irst("������ ��� ������������?");
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
      //������� ��� ������, ������� ������ ���������� �����
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
  if (FileExists(a_filename)){
    m_config_calibr.load(a_filename.c_str());
    //m_name_config = extract_short_filename(ExtractFileName(a_filename));
    m_name_config = m_file_name_service.get_config_name(a_filename);
    NameConfigLE->Text = m_name_config;
    String type = mp_data_handing->get_device_type();
    DeviceComboBox->ItemIndex = DeviceComboBox->Items->IndexOf(type);
    config_calibr_out_displ(m_config_calibr);
  }
}
void TNewConfigF::set_config_def()
{
  m_edit_mode = NEW_CONFIG;
  config_calibr_t config_calibr_def;
  config_calibr_def.ip_adress = irst("192.168.0.200");
  config_calibr_def.port = 5005;
  config_calibr_def.in_parametr1.name = irst("�������");
  config_calibr_def.in_parametr1.type_variable = irst("��");
  config_calibr_def.in_parametr1.unit = type_irs_u32;
  config_calibr_def.in_parametr1.anchor = false;
  config_calibr_def.in_parametr1.index = 0;
  config_calibr_def.in_parametr1.koef = 1;

  config_calibr_def.in_parametr2.name = irst("����������");
  config_calibr_def.in_parametr2.type_variable = irst("�");
  config_calibr_def.in_parametr2.unit = type_irs_u32;
  config_calibr_def.in_parametr2.anchor = true;
  config_calibr_def.in_parametr2.index = 0;
  config_calibr_def.in_parametr2.koef = 1;

  config_calibr_def.in_parametr3.name = irst("����");
  config_calibr_def.in_parametr3.type_variable = irst("������");
  config_calibr_def.in_parametr3.unit = type_irs_u32;
  config_calibr_def.in_parametr3.index = 0;
  config_calibr_def.in_parametr3.koef = 1;

  config_calibr_def.out_parametr.name = irst("����������");
  config_calibr_def.out_parametr.type_variable = irst("�");
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
  SubDiapasonSG->Cells[0][1] = irst("0");
  SubDiapasonSG->Cells[1][1] = String();
  SubDiapasonSG->Cells[2][1] = String();
  SubDiapasonSG->Cells[3][1] = String();
  SubDiapasonSG->Cells[4][1] = String();

  //config_calibr_def.mismatch_mode = true;
  config_calibr_def.meas_range_koef = 1.;
  config_calibr_def.delay_meas = 10;
  config_calibr_def.type_meas = irst("���������� ����������");
  config_calibr_def.count_reset_over_bit = 3;
  config_calibr_def.active_filename = irst("");

  //String name_config = irst("NewConfig");
  String name_config = generate_new_unique_name(irst("����� ������������"));
  m_name_config = name_config;
  NameConfigLE->Text = name_config;
  String file_name = make_config_full_file_name(name_config);
  //create_configurations_dir();
  m_file_name_service.create_config_dir();
  m_config_calibr.save(file_name.c_str());

  mp_data_handing->load_main_device(name_config);

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

  config_calibr_out_displ(config_calibr_def);
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
      throw Exception(irst("�� ������� ������� ���������� ") + dir);
    }
  }
} */

// �������� �������� ���������� �� �����
void TNewConfigF::config_calibr_out_displ(
  const config_calibr_t& a_config_calibr)
{
  //IPAdressLE->Text = a_config_calibr.ip_adress;
  //PortLE->Text = num_to_cbstr(a_config_calibr.port);

  String type_meas_str = a_config_calibr.type_meas;
  MeasTypeCB->ItemIndex =
    get_index_row_combo_box_str(MeasTypeCB,type_meas_str);

  MeasRangeKoefLabeledEdit->Text =
    num_to_cbstr(a_config_calibr.meas_range_koef);
  Delay_MeasLE->Text = num_to_cbstr(a_config_calibr.delay_meas);

  CountResetOverBitLE->Text = num_to_cbstr(
    a_config_calibr.count_reset_over_bit);
  IndexWorkTimeEdit->Text = num_to_cbstr(a_config_calibr.index_work_time);
  ValueIndexEEPROMEdit->Text = num_to_cbstr(a_config_calibr.index_pos_eeprom);

  ConsiderOutParameterForMeasurementCheckBox->Checked =
    m_config_calibr.out_param_config_for_measurement.
    consider_out_param;
  OutParameterFilterCheckBox->Checked =
    m_config_calibr.out_param_config_for_measurement.
    out_param_filter_enabled;
  FilterSamplingTimeEdit->Text = num_to_cbstr(
    m_config_calibr.out_param_config_for_measurement.filter_sampling_time);
  FilterPointCountEdit->Text = num_to_cbstr(
    m_config_calibr.out_param_config_for_measurement.filter_point_count);

  OutParameterControlCheckBox->Checked =
    m_config_calibr.out_param_control_config.enabled;
  MaxRelativeDifferenceOutParameterLabeledEdit->Text =
    num_to_cbstr(
    a_config_calibr.out_param_control_config.max_relative_difference);
  TimeCalcDifferenceLabeledEdit->Text = num_to_cbstr(
    a_config_calibr.out_param_control_config.time);

  TemperatureControlCheckBox->Checked =
    a_config_calibr.temperature_control.enabled;
  TemperatureVariableIndexByteLabeledEdit->Text = num_to_cbstr(
    a_config_calibr.temperature_control.index);
  ReferenceTemperetureLabeledEdit->Text = num_to_cbstr(
    a_config_calibr.temperature_control.reference);
  DifferenceTemperatureLabeledEdit->Text = num_to_cbstr(
    a_config_calibr.temperature_control.difference);  
  temperature_control_components_update();
  // �������� ������ ����������
  // �������� 1
  ListParameterSG->Cells[0][1] = m_config_calibr.in_parametr1.name;
  ListParameterSG->Cells[1][1] = m_config_calibr.in_parametr1.type_variable;
  ListParameterSG->Cells[2][1] =
    lang_type_to_str(m_config_calibr.in_parametr1.unit).c_str();
  ListParameterSG->Cells[3][1] =
    num_to_cbstr(m_config_calibr.in_parametr1.anchor);

  ListParameterSG->Cells[4][1] =
    num_to_cbstr(m_config_calibr.in_parametr1.index);
  ListParameterSG->Cells[5][1] =
    num_to_cbstr(m_config_calibr.in_parametr1.koef);
  ListParameterSG->Cells[7][1] =
    num_to_cbstr(m_config_calibr.in_parametr1.default_val);
  // �������� 2
  ListParameterSG->Cells[0][2] = m_config_calibr.in_parametr2.name;
  ListParameterSG->Cells[1][2] = m_config_calibr.in_parametr2.type_variable;
  ListParameterSG->Cells[2][2] =
    lang_type_to_str(m_config_calibr.in_parametr2.unit).c_str();
  ListParameterSG->Cells[3][2] =
    num_to_cbstr(m_config_calibr.in_parametr2.anchor);
  ListParameterSG->Cells[4][2] =
    num_to_cbstr(m_config_calibr.in_parametr2.index);
  ListParameterSG->Cells[5][2] =
    num_to_cbstr(m_config_calibr.in_parametr2.koef);
  ListParameterSG->Cells[7][2] =
    num_to_cbstr(m_config_calibr.in_parametr2.default_val);
  // �������� 3
  ListParameterSG->Cells[0][3] = m_config_calibr.in_parametr3.name;
  ListParameterSG->Cells[1][3] = m_config_calibr.in_parametr3.type_variable;
  ListParameterSG->Cells[2][3] =
    lang_type_to_str(m_config_calibr.in_parametr3.unit).c_str();
  ListParameterSG->Cells[4][3] =
    num_to_cbstr(m_config_calibr.in_parametr3.index);
  ListParameterSG->Cells[5][3] =
    num_to_cbstr(m_config_calibr.in_parametr3.koef);
  ListParameterSG->Cells[7][3] =
    num_to_cbstr(m_config_calibr.in_parametr3.default_val);

  // �������� 4
  ListParameterSG->Cells[0][4] = m_config_calibr.out_parametr.name;
  ListParameterSG->Cells[1][4] = m_config_calibr.out_parametr.type_variable;
  ListParameterSG->Cells[2][4] =
    lang_type_to_str(m_config_calibr.out_parametr.unit).c_str();
  ListParameterSG->Cells[4][4] =
    num_to_cbstr(m_config_calibr.out_parametr.index);
  ListParameterSG->Cells[5][4] =
    num_to_cbstr(m_config_calibr.out_parametr.koef_shunt);

  // ��������� ���.����������
  int parameter_ex_count = m_config_calibr.v_parametr_ex.size();
  if (parameter_ex_count > 0) {
    ParamsExCSpinEdit->Value = parameter_ex_count;
    ListParameterSG->RowCount =
      ParamsExCSpinEdit->Value+m_basic_parameter_count+1;
    for (int i  = 0; i < parameter_ex_count; i++) {
      int row = i+m_basic_parameter_count+1;
      // ��������
      ListParameterSG->Cells[0][row] = m_config_calibr.v_parametr_ex[i].name;
      // ������� ���������
      ListParameterSG->Cells[1][row] =
        m_config_calibr.v_parametr_ex[i].type_variable;
      // ��� ����������
      ListParameterSG->Cells[2][row] =
        lang_type_to_str(m_config_calibr.v_parametr_ex[i].unit).c_str();
      // ������, ����
      ListParameterSG->Cells[4][row] =
        num_to_cbstr(m_config_calibr.v_parametr_ex[i].index);
      // ������� ��������
      ListParameterSG->Cells[6][row] = num_to_cbstr(
        m_config_calibr.v_parametr_ex[i].value_working);
      // �������� �� ���������
      ListParameterSG->Cells[7][row] = num_to_cbstr(
        m_config_calibr.v_parametr_ex[i].value_default);
    }
  } else {
    ParamsExCSpinEdit->Value = 1;
    ListParameterSG->RowCount =
      m_basic_parameter_count+ParamsExCSpinEdit->Value+1;
    int row = m_basic_parameter_count+1;
      // ��������
      ListParameterSG->Cells[0][row] = String();
      // ������� ���������
      ListParameterSG->Cells[1][row] = String();
      // ��� ����������
      ListParameterSG->Cells[2][row] = String();
      // ������, ����
      ListParameterSG->Cells[4][row] = String();
      // �����������
      ListParameterSG->Cells[5][row] = String();
      // ������� ��������
      ListParameterSG->Cells[6][row] = String() ;
      // �������� �� ���������
      ListParameterSG->Cells[7][row] = String();
  }

  // ��� ���������� ����������
  ListByteSG->Cells[1][1] = num_to_cbstr(
    a_config_calibr.bit_pos_operating_duty.index_byte);
  ListByteSG->Cells[2][1] = num_to_cbstr(
    a_config_calibr.bit_pos_operating_duty.index_bit);
  // ��� ������ ����������
  ListByteSG->Cells[1][2] = num_to_cbstr(
    a_config_calibr.bit_pos_mismatch_state.index_byte);
  ListByteSG->Cells[2][2] = num_to_cbstr(
    a_config_calibr.bit_pos_mismatch_state.index_bit);
  // ��� ������ ���������
  ListByteSG->Cells[1][3] = num_to_cbstr(
    a_config_calibr.bit_pos_correct_mode.index_byte);
  ListByteSG->Cells[2][3] = num_to_cbstr(
    a_config_calibr.bit_pos_correct_mode.index_bit);
  // ��� ������
  ListByteSG->Cells[1][4] = num_to_cbstr(
    a_config_calibr.bit_pos_error_bit.index_byte);
  ListByteSG->Cells[2][4] = num_to_cbstr(
    a_config_calibr.bit_pos_error_bit.index_bit);
  // ��� ������ ������
  ListByteSG->Cells[1][5] = num_to_cbstr(
    a_config_calibr.bit_pos_reset_over_bit.index_byte);
  ListByteSG->Cells[2][5] = num_to_cbstr(
    a_config_calibr.bit_pos_reset_over_bit.index_bit);
  // ��� ������������� ����
  ListByteSG->Cells[1][6] = num_to_cbstr(
    a_config_calibr.bit_pos_phase_preset_bit.index_byte);
  ListByteSG->Cells[2][6] = num_to_cbstr(
    a_config_calibr.bit_pos_phase_preset_bit.index_bit);

  // ��������� ���.�����
  int bit_type2_count = m_config_calibr.bit_type2_array.size();

  if (bit_type2_count > 0) {
    BitsExCSpinEdit->Value = bit_type2_count;
    ListByteSG->RowCount = BitsExCSpinEdit->Value+m_basic_bit_count+1;
    for (int i = 0; i < bit_type2_count; i++) {
      int row = i+m_basic_bit_count+1;
      ListByteSG->Cells[0][row] =
        m_config_calibr.bit_type2_array[i].bitname.c_str();
      ListByteSG->Cells[1][row] = num_to_cbstr(
        m_config_calibr.bit_type2_array[i].index_byte);
      ListByteSG->Cells[2][row] = num_to_cbstr(
        m_config_calibr.bit_type2_array[i].index_bit);
      ListByteSG->Cells[3][row] = num_to_cbstr(
        m_config_calibr.bit_type2_array[i].value_working);
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
  int sub_diapason = m_config_calibr.v_sub_diapason_calibr.size();
  if (sub_diapason > 0) {
    CSpinEdit1->Value = sub_diapason;
    SubDiapasonSG->RowCount = CSpinEdit1->Value+1;
    for (int i = 0; i < sub_diapason; i++) {
      int row = i+1;
      SubDiapasonSG->Cells[0][row] = num_to_cbstr(i+1);
      SubDiapasonSG->Cells[1][row] = num_to_cbstr(
        m_config_calibr.v_sub_diapason_calibr[i].index_start);
      SubDiapasonSG->Cells[2][row] = num_to_cbstr(
        m_config_calibr.v_sub_diapason_calibr[i].size);
      SubDiapasonSG->Cells[3][row] = num_to_cbstr(
        m_config_calibr.v_sub_diapason_calibr[i].value_begin);
      SubDiapasonSG->Cells[4][row] = num_to_cbstr(
        m_config_calibr.v_sub_diapason_calibr[i].value_end);
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
  update_ref_device_options_enabled();
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
  if (ReferenceChannelCheckB->Checked == true){
    mp_data_handing->load_ref_device(m_name_config);
  }
  update_ref_device_options_enabled();
}

void TNewConfigF::update_ref_device_options_enabled()
{
  if (ReferenceChannelCheckB->Checked == true){
    RefDeviceComboBox->Enabled = true;
    ChangeRefDeviceConfigButton->Enabled = true;
  } else {
    RefDeviceComboBox->Enabled = false;
    ChangeRefDeviceConfigButton->Enabled = false;
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



void __fastcall TNewConfigF::ChangeNameButtonClick(TObject *Sender)
{
  m_name_config = NameConfigLE->Text;
  const String cur_file_name =
    m_file_name_service.make_config_full_file_name(m_name_config);
  const String cur_device_cfg_file_name =
    m_file_name_service.make_device_config_full_file_name(m_name_config);
  const String cur_grid_opt_file_name =
    m_file_name_service.make_device_grid_config_full_name(m_name_config);

  String new_config_name = m_name_config;
  while (InputQuery(irst("������� ���"), irst("��� ������������"),
      new_config_name)) {
    const String new_cfg_file_name =
      m_file_name_service.make_config_full_file_name(new_config_name);
    const String new_device_cfg_file_name =
      m_file_name_service.make_device_config_full_file_name(new_config_name);
    const String new_grid_opt_file_name =
      m_file_name_service.make_device_grid_config_full_name(new_config_name);

    if(FileExists(new_cfg_file_name) || FileExists(new_device_cfg_file_name)
        || FileExists(new_grid_opt_file_name)){
      Application->MessageBox(
        irst("������������ � ��������� ������ ��� ����������, ")
        irst("������� ������ ���"),
        irst("��� ������������"),
        MB_OK + MB_ICONINFORMATION);
    } else {
      if (!RenameFile(cur_file_name, new_cfg_file_name)) {
        Application->MessageBox(irst("������������� ���� �� �������"),
          irst("������"), MB_OK + MB_ICONERROR);
        break;
      }
      if (!RenameFile(cur_device_cfg_file_name, new_device_cfg_file_name)) {
        Application->MessageBox(irst("������������� ���� �� �������"),
          irst("������"), MB_OK + MB_ICONERROR);
        break;
      }
      RenameFile(cur_grid_opt_file_name, new_grid_opt_file_name);

      m_name_config = new_config_name;
      NameConfigLE->Text = new_config_name;
      mp_data_handing->load_main_device(m_name_config);

      // tstlan ��� ����������� ��������������� ����. ������� ��� ��� ���
      DeleteFile(cur_device_cfg_file_name);
      DeleteFile(cur_grid_opt_file_name);

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
  String name_config = NameConfigLE->Text;
  String type = DeviceComboBox->Text;
  mp_data_handing->change_main_device_type(name_config, type);
}
//---------------------------------------------------------------------------


void __fastcall TNewConfigF::ExitButtonClick(TObject *Sender)
{
  if (m_edit_mode == NEW_CONFIG) {
    mp_data_handing->delete_device_config(m_name_config);
  }
}
//---------------------------------------------------------------------------

void __fastcall TNewConfigF::ChangeRefDeviceConfigButtonClick(TObject *Sender)
{
  mp_data_handing->show_ref_device_options();
}
//---------------------------------------------------------------------------

