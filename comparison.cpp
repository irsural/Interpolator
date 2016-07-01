//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <csvwork.h>

#include "servisfunction.h"

#include "comparison.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TComparsionDataForm *ComparsionDataForm;
//---------------------------------------------------------------------------
__fastcall TComparsionDataForm::TComparsionDataForm(TComponent* Owner)
  : TForm(Owner),
  m_min_value(0),
  m_max_value(0),
  m_table_values(),
  m_table_colors()
{
}
//---------------------------------------------------------------------------
void __fastcall TComparsionDataForm::OpenFirstDataFileButtonClick(TObject *Sender)
{
  if (OpenDialog->Execute()){
    FirstDataFileNameEdit->Text = OpenDialog->FileName;
  }
}
//---------------------------------------------------------------------------
void __fastcall TComparsionDataForm::OpenSecondDataFileButtonClick(TObject *Sender)
{
  if (OpenDialog->Execute()){
    SecondDataFileNameEdit->Text = OpenDialog->FileName;
  }
}
//---------------------------------------------------------------------------
void __fastcall TComparsionDataForm::СompareButtonClick(TObject *Sender)
{
  if (!FileExists(FirstDataFileNameEdit->Text) ||
      !FileExists(SecondDataFileNameEdit->Text)) {
    Application->MessageBox(
      irst("Отсутсвует один или оба файла"),
      irst("Ошибка"),  MB_OK + MB_ICONERROR);
    return;
  }

  const string_type first_file_name =
    irs::str_conv<string_type>(FirstDataFileNameEdit->Text);
  std::vector<irs::matrix_t<cell_t> > first_table;
  number_in_param_t param_count_from_file = TWO_PARAM;
  ::load_table_from_file(param_count_from_file, first_file_name, first_table);

  const string_type second_file_name =
    irs::str_conv<string_type>(SecondDataFileNameEdit->Text);
  std::vector<irs::matrix_t<cell_t> > second_table;
  ::load_table_from_file(param_count_from_file, second_file_name, second_table);

  const size_type table_count = min(first_table.size(), second_table.size());

  std::vector<irs::matrix_t<cell_t> > result_table;
  if (first_table.empty() || second_table.empty()) {
    return;
  }
  size_type table_i = 0;
  //for (size_type table_i = 0; table_i < table_count; table_i++) {
    irs::matrix_t<cell_t>& t_1 = first_table[table_i];
    irs::matrix_t<cell_t>& t_2 = second_table[table_i];
    const size_type col_count = min(t_1.col_count(), t_2.col_count());
    const size_type row_count = min(t_1.row_count(), t_2.row_count());

    //irs::table_t<table_cell_t> table_values;
    m_table_values.clear();

    m_table_values.set_col_count(col_count);
    m_table_values.set_row_count(row_count);

    StringGrid->ColCount = col_count;
    StringGrid->RowCount = row_count;

    for (size_type i = 0; i < col_count; i++) {
      StringGrid->ColWidths[i] = col_width;
    }

    for (size_type c = 1; c < col_count; c++) {
      const cell_t& cell_1 = t_1[c][0];
      if (cell_1.init) {
        StringGrid->Cells[c][0] = FloatToStr(cell_1.value);
      }
    }
    for (size_type r = 1; r < row_count; r++) {
      const cell_t& cell_1 = t_1[0][r];
      if (cell_1.init) {
        StringGrid->Cells[0][r] = FloatToStr(cell_1.value);
      }
    }

    m_min_value = 0;
    m_max_value = 0;
    bool min_max_init = false;

    for (size_type c = 1; c < col_count; c++) {
      for (size_type r = 1; r < row_count; r++) {
        cell_t& cell_1 = t_1[c][r];
        cell_t& cell_2 = t_2[c][r];
        if (cell_1.init && cell_2.init) {
          double result = 100;
          if (cell_1.value != 0) {
            result = ((cell_1.value - cell_2.value)/cell_1.value)*100;
          }

          if (!min_max_init) {
            m_min_value = result;
            m_max_value = result;
            min_max_init = true;
          } else {
            m_min_value = fabs(result) < fabs(m_min_value) ? result: m_min_value;
            m_max_value = fabs(result) > fabs(m_max_value) ? result: m_max_value;
          }

          m_table_values.write_cell(c, r, table_cell_t(true, result));
          StringGrid->Cells[c][r] = FloatToStr(result);
        } else {
          StringGrid->Cells[c][r] = String();
        }
      }
    }
    MinLabeledEdit->Text = FloatToStr(m_min_value);
    MaxLabeledEdit->Text = FloatToStr(m_max_value);
  //}






  update_color();
  //mp_active_table->set_file_namedir(file_namedir);
  //mp_active_table->load_table_from_file(file_namedir.c_str());
}

void TComparsionDataForm::update_color()
{
  vector<TColor> colors;
  colors.push_back(clWindow);
  colors.push_back(clYellow);
  colors.push_back(clMoneyGreen);
  colors.push_back(clSilver);

  m_color_edits.clear();

  m_color_edits.push_back(ColorLabeledEdit1);
  m_color_edits.push_back(ColorLabeledEdit2);
  m_color_edits.push_back(ColorLabeledEdit3);
  m_color_edits.push_back(ColorLabeledEdit4);

  IRS_LIB_ASSERT(colors.size() == m_color_edits.size());

  for (int i = 0; i < m_color_edits.size(); i++) {
    m_color_edits[i]->Color = colors[i];
  }

  const int border_count = colors.size();

  double k = 0;
  if ((m_max_value != 0) && (m_min_value != 0)) {
    k = log10((fabs(m_max_value)/fabs(m_min_value)))/border_count;
  } else if ((m_max_value != 0) && (m_min_value == 0)) {
    k = log10((fabs(m_max_value)))/border_count;
  }

  m_table_colors.clear();

  if (k != 0) {
    vector<double> borders;
    for (int i = 0; i < border_count; i++) {
      const double exponent = k*(i+1);
      const double border = m_min_value*pow(10, exponent);
      borders.push_back(fabs(border));
      m_color_edits[i]->EditLabel->Caption = irst(" <= ") +
        FloatToStr(fabs(border)) + irst(" %");
    }

    m_table_colors.set_col_count(m_table_values.get_col_count());
    m_table_colors.set_row_count(m_table_values.get_row_count());

    double max_norm = (fabs(m_max_value) - fabs(m_min_value));

    for (size_type c = 1; c < m_table_values.get_col_count(); c++) {
      for (size_type r = 1; r < m_table_values.get_row_count(); r++) {
        const table_cell_t cell = m_table_values.read_cell(c, r);

        if (ColorShadesRadioButton->Checked) {

          if (cell.init) {
            const double value = cell.value;


            double value_norm = fabs(value) - fabs(m_min_value);
            double ratio = irs::bound(1 - value_norm/max_norm, 0., 1.);


            int blue = static_cast<int>(255*ratio);
            int green = 150 + static_cast<int>(105*ratio);
            int red = 255;

            TColor color = (blue << 16) | (green << 8) | red;
            m_table_colors.write_cell(c, r, color);

          } else {
            m_table_colors.write_cell(c, r, 0xFFFFFF);
          }
        } else {

          if (cell.init) {
            const double value = cell.value;
            m_table_colors.write_cell(c, r, colors.back());
            for (size_type b = 0; b < borders.size(); b++) {
              const double border = borders[b];
              if (fabs(value) <= border) {
                m_table_colors.write_cell(c, r, colors[b]);
                break;
              }
            }
          } else {
            m_table_colors.write_cell(c, r, colors.front());
          }
        }
      }
    }
  }
  StringGrid->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TComparsionDataForm::ExportButtonClick(TObject *Sender)
{
  save_string_grid_to_csv_with_dialog(StringGrid);
  /*SaveDialog->Filter = irst("Текстовые файлы Microsoft Excel (*.csv)")
    irst("|*.csv|Все файлы (*.*)|*.*");
  SaveDialog->DefaultExt = irst("csv");
  SaveDialog->FileName = irst("Новый файл.csv");
  if (SaveDialog->Execute()) {
    const string_type file_name = SaveDialog->FileName.c_str();
    irs::csvwork::csv_file_synchro_t csv_file(file_name);

    irs::table_string_t table_string;

    table_string.set_col_count(StringGrid->ColCount);
    table_string.set_row_count(StringGrid->RowCount);
    for (size_type c = 0; c < table_string.get_col_count(); c++) {
      for (size_type r = 0; r < table_string.get_row_count(); r++) {
        const string_type cell_value =
          irs::str_conv<string_type>(StringGrid->Cells[c][r]);
        table_string.write_cell(c, r, cell_value);
      }
    }

    csv_file.save(table_string);
  }*/
}
//---------------------------------------------------------------------------

void __fastcall TComparsionDataForm::StringGridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State)
{
  if (!ColorEnabledCheckBox->Checked) {
    return;
  }
  if ((ACol == 0) || (ARow == 0)) {
    return;
  }
  if ((m_table_colors.get_col_count() < StringGrid->ColCount) &&
    (m_table_colors.get_row_count() < StringGrid->RowCount)) {
    return;
  }

  TColor color = m_table_colors.read_cell(ACol, ARow);
  StringGrid->Canvas->Brush->Color = color;
  StringGrid->Canvas->FillRect(Rect);
  StringGrid->Canvas->TextOutW(
    Rect.Left, Rect.Top, StringGrid->Cells[ACol][ARow]);
}
//---------------------------------------------------------------------------



void __fastcall TComparsionDataForm::ColorShadesRadioButtonClick(TObject *Sender)

{
  update_color();
}
//---------------------------------------------------------------------------

void __fastcall TComparsionDataForm::DifferentColorsRadioButtonClick(TObject *Sender)

{
  update_color();
}
//---------------------------------------------------------------------------

void __fastcall TComparsionDataForm::ColorEnabledCheckBoxClick(TObject *Sender)
{
  update_color();
}
//---------------------------------------------------------------------------

