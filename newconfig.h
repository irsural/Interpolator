//---------------------------------------------------------------------------

#ifndef newconfigH
#define newconfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <inifiles.hpp>
#include <Grids.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
#pragma hdrstop

#include <vector>
#include <cbsysutils.h>
#include <irsdevices.h>
#include "measutils.h"
#include "servisfunction.h"
#include "datahandling.h"
#include "mxini.h"
#define newconfig_new_version_12_09_2008


enum edit_mode_t{NEW_CONFIG, EXISTENT_CONFIG};
void fill_combo_box_lang_type(TComboBox* ap_combo_box);

//---------------------------------------------------------------------------
class TNewConfigF : public TForm
{
__published:	// IDE-managed Components
  TLabeledEdit *NameConfigLE;
  TButton *CreateConfigButton;
  TButton *ExitButton;
  TPanel *Panel2;
  TLabel *IndexEEPROMLabel;
  TEdit *ValueIndexEEPROMEdit;
  TPanel *Panel3;
  TPanel *Panel4;
  TLabel *Label3;
  TEdit *IndexWorkTimeEdit;
  TComboBox *MeasTypeCB;
  TLabeledEdit *Delay_MeasLE;
  TLabel *Label1;
  TLabeledEdit *CountResetOverBitLE;
  TCheckBox *ReferenceChannelCheckB;
  TGroupBox *GroupBox1;
  TCSpinEdit *CSpinEdit1;
  TStringGrid *SubDiapasonSG;
  TLabel *Label9;
  TRadioButton *TypeSubDiapasonParam1RB;
  TRadioButton *TypeSubDiapasonParam2RB;
  TStringGrid *ListByteSG;
  TStringGrid *ListParameterSG;
  TGroupBox *MultimeterSettingsGroupBox;
  TGroupBox *GroupBox2;
  TCheckBox *TemperatureControlVariableCheckBox;
  TLabeledEdit *TemperatureVariableIndexByteLabeledEdit;
  TLabeledEdit *ReferenceTemperetureLabeledEdit;
  TLabeledEdit *DifferenceTemperatureLabeledEdit;
  TGroupBox *GroupBox3;
  TCheckBox *OutParameterControlCheckBox;
  TLabeledEdit *MaxRelativeDifferenceOutParameterLabeledEdit;
  TLabeledEdit *TimeCalcDifferenceLabeledEdit;
  TPageControl *PageControl1;
  TTabSheet *MeasAndCalibrationSettingsTabSheet;
  TTabSheet *SecondaryNetworkVariablesTabSheet;
  TTabSheet *PrimaryNetworkVariablesTabSheet;
  TCheckBox *ConsiderOutParameterForMeasurementCheckBox;
  TCheckBox *OutParameterFilterCheckBox;
  TLabel *Label5;
  TEdit *FilterSamplingTimeEdit;
  TGroupBox *GroupBox4;
  TEdit *FilterPointCountEdit;
  TLabel *Label8;
  TComboBox *DeviceComboBox;
  TLabel *DeviceLabel;
  TButton *ChangeDeviceConfigButton;
  TLabel *RefDeviceLabel;
  TComboBox *RefDeviceComboBox;
  TButton *ChangeRefDeviceConfigButton;
  TButton *ChangeNameButton;
  TLabeledEdit *MeasIntervalLabeledEdit;
  TComboBox *DeviceNameComboBox;
  TComboBox *RefDeviceNameComboBox;
  TLabel *DeviceNameLabel;
  TGroupBox *DevideGroupBox;
  TGroupBox *RefDeviceGroupBox;
  TPanel *Panel1;
  TLabel *CellsRangeLabel;
  TCheckBox *TemperatureControlCheckBox;
  TCheckBox *RangeCheckBox;
  TEdit *RangeEdit;
  TLabel *Label2;
  TCSpinEdit *BitsExCSpinEdit;
  TCSpinEdit *ParamsExCSpinEdit;
  TLabel *Label4;
  void __fastcall CreateConfigButtonClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall ReferenceChannelCheckBClick(TObject *Sender);
  void __fastcall CSpinEdit1Change(TObject *Sender);
  void __fastcall BitsExCSpinEditChange(TObject *Sender);
  void __fastcall ListByteSGDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall ListByteSGSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
  void __fastcall ParamsExCSpinEditChange(TObject *Sender);
  void __fastcall ListParameterSGDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
  void __fastcall ListParameterSGSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall TemperatureControlVariableCheckBoxClick(TObject *Sender);
  void __fastcall ConsiderOutParameterForMeasurementCheckBoxClick(
          TObject *Sender);
  void __fastcall OutParameterFilterCheckBoxClick(TObject *Sender);
  void __fastcall ChangeNameButtonClick(TObject *Sender);
  void __fastcall ChangeDeviceConfigButtonClick(TObject *Sender);
  void __fastcall DeviceComboBoxChange(TObject *Sender);
  void __fastcall ExitButtonClick(TObject *Sender);
  void __fastcall ChangeRefDeviceConfigButtonClick(TObject *Sender);
  void __fastcall DeviceNameComboBoxChange(TObject *Sender);
  void __fastcall RefDeviceNameComboBoxChange(TObject *Sender);
  void __fastcall RefDeviceComboBoxChange(TObject *Sender);
  void __fastcall TemperatureControlCheckBoxClick(TObject *Sender);
  void __fastcall RangeCheckBoxClick(TObject *Sender);
private:	// User declarations
  typedef std::size_t size_type;
  typedef irs::string_t string_type;
  static const int m_basic_parameter_count = 4;
  static const int m_basic_bit_count = 6;

  TDataHandlingF* mp_data_handing;

  String m_prog_name;
  file_name_service_t m_file_name_service;

  const String m_device_options_section;

  config_calibr_t m_config_calibr;
  irs::rect_t m_cells_range;
  String m_name_config;

  edit_mode_t m_edit_mode;
  bool m_on_close;
  String m_name_new_conf;
  vector<string_type> m_device_list;
  // Закрашиваем запрещенную ячейку определенным цветом
  void draw_cell_illegal(
    TObject *Sender, int ACol, int ARow, TRect &Rect);
  // Выдаем true, если ячейка запрещенная
  bool cell_illegal_ListParameterSG_stat(const int a_col, const int a_row);
  void out_parameter_options_components_update();
  void temperature_control_components_update();
  bool save_with_same_name_dialog() const;
  String get_config_full_file_name();
  String make_config_full_file_name(String a_config_name);
  String generate_new_unique_name(const String& a_device_name);
  String make_device_config_full_file_name(String a_config_name);
  void save_configuration(String a_config_name);
  void update_ref_device_options();
  void update_main_device();
  void update_ref_device();
  //void create_configurations_dir();
public:		// User declarations
  __fastcall TNewConfigF(TComponent* Owner, TDataHandlingF* ap_data_handing);
  //inline void set_path_program(const String& a_path);
  void edit_config(const String& a_filename);
  void set_config_def();

  void load_devices_list();

  //int lang_type_to_combo_box(const String& a_lang_type);
  inline void set_config_device(config_calibr_t* ap_config_calibr);
  inline void set_ini_file(irs::ini_file_t* ap_conf_device_ini_file);
  inline void set_edit_mode(const edit_mode_t a_edit_mode);
  void config_calibr_out_displ(const config_calibr_t& a_config_calibr);
  inline String get_name_new_conf();
};

//---------------------------------------------------------------------------
extern PACKAGE TNewConfigF *NewConfigF;
//---------------------------------------------------------------------------
/*inline void TNewConfigF::set_path_program(const String& a_path)
{
  m_path_prog = a_path;
} */
/*inline void TNewConfigF::set_config_device(config_calibr_t* ap_config_calibr)
{
  //mp_config_calibr = ap_config_calibr;
}*/
/*inline void TNewConfigF::set_ini_file(irs::ini_file_t* ap_conf_device_ini_file)
{
  //mp_conf_device_ini_file = ap_conf_device_ini_file;
} */
inline void TNewConfigF::set_edit_mode(const edit_mode_t a_edit_mode)
{
  m_edit_mode = a_edit_mode;
}
inline String TNewConfigF::get_name_new_conf()
{
  return m_name_new_conf;
}
#endif
