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
#pragma hdrstop

#include <vector>
#include <cbsysutils.h>
#include "measutils.h"
#include "servisfunction.h"
#include "mxini.h"
#define newconfig_new_version_12_09_2008


enum edit_mode_t{NEW_CONFIG, EXISTENT_CONFIG};
void fill_combo_box_lang_type(TComboBox* ap_combo_box);
//---------------------------------------------------------------------------
class TNewConfigF : public TForm
{
__published:	// IDE-managed Components
  TPanel *InformationPanel;
  TLabeledEdit *NameConfigLE;
  TButton *CreateConfigButton;
  TButton *ExitButton;
  TPanel *Panel2;
  TLabel *IndexEEPROMLabel;
  TEdit *ValueIndexEEPROMEdit;
  TPanel *Panel3;
  TSaveDialog *SaveDialogConfig;
  TPanel *Panel4;
  TLabeledEdit *IPAdressLE;
  TLabeledEdit *PortLE;
  TLabel *Label3;
  TEdit *IndexWorkTimeEdit;
  TComboBox *MeasTypeCB;
  TLabeledEdit *Delay_MeasLE;
  TLabel *Label1;
  TLabeledEdit *CountResetOverBitLE;
  TCheckBox *ReferenceChannelCheckB;
  TLabeledEdit *IPAdressRefChannelLE;
  TLabeledEdit *PortRefChannelLE;
  TGroupBox *GroupBox1;
  TCSpinEdit *CSpinEdit1;
  TStringGrid *SubDiapasonSG;
  TLabel *Label9;
  TRadioButton *TypeSubDiapasonParam1RB;
  TRadioButton *TypeSubDiapasonParam2RB;
  TStringGrid *ListByteSG;
  TCSpinEdit *BitsExCSpinEdit;
  TLabel *Label2;
  TStringGrid *ListParameterSG;
  TCSpinEdit *ParamsExCSpinEdit;
  TLabel *Label4;
  TGroupBox *MultimeterSettingsGroupBox;
  TLabeledEdit *MeasRangeKoefLabeledEdit;
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
private:	// User declarations
  static const int m_basic_parameter_count = 4;
  static const int m_basic_bit_count = 6;
  
  AnsiString m_prog_name;
  //рабочий каталог программы
  AnsiString m_path_prog;
  //расширение файла конфигурации процесса калибровки
  const AnsiString m_default_ext;
  //имя файла по умолчанию конфигурации процесса калибровки
  const AnsiString m_default_filename;
  //идентификатор файла конфигурации процесса калибровки
  const AnsiString m_fileid_conf;
  //имя каталога программы для хранения конфгураций
  const AnsiString m_foldername_conf;

  config_calibr_t m_config_calibr;
  AnsiString m_name_config;
  //класс работы с ini-файлом конфигураций устройства
  //irs::ini_file_t* mp_conf_device_ini_file;

  //TIniFile* mp_config_ini_file;

  //std::vector<AnsiString> mv_list_combo_box;
  edit_mode_t m_edit_mode;
  bool m_on_close;
  AnsiString m_name_new_conf;
  // Закрашиваем запрещенную ячейку определенным цветом
  void draw_cell_illegal(
    TObject *Sender, int ACol, int ARow, TRect &Rect);
  // Выдаем true, если ячейка запрещенная
  bool cell_illegal_ListParameterSG_stat(const int a_col, const int a_row);

  
public:		// User declarations
  __fastcall TNewConfigF(TComponent* Owner);
  inline void set_path_program(const AnsiString& a_path);
  void edit_config(const AnsiString& a_filename);
  void set_config_def();
  //int lang_type_to_combo_box(const AnsiString& a_lang_type);
  inline void set_config_device(config_calibr_t* ap_config_calibr);
  inline void set_ini_file(irs::ini_file_t* ap_conf_device_ini_file);
  inline void set_edit_mode(const edit_mode_t a_edit_mode);
  void config_calibr_out_displ(const config_calibr_t& a_config_calibr);
  inline AnsiString get_name_new_conf();

};

//---------------------------------------------------------------------------
extern PACKAGE TNewConfigF *NewConfigF;
//---------------------------------------------------------------------------
inline void TNewConfigF::set_path_program(const AnsiString& a_path)
{
  m_path_prog = a_path;
}
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
inline AnsiString TNewConfigF::get_name_new_conf()
{
  return m_name_new_conf;
}
#endif
