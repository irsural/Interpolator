object ParametersForm: TParametersForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
  ClientHeight = 486
  ClientWidth = 1019
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  DesignSize = (
    1019
    486)
  PixelsPerInch = 96
  TextHeight = 13
  object ParametersListBox: TListBox
    Left = 8
    Top = 8
    Width = 282
    Height = 145
    ItemHeight = 13
    TabOrder = 0
    OnClick = ParametersListBoxClick
  end
  object StringGrid: TStringGrid
    Left = 296
    Top = 8
    Width = 715
    Height = 470
    Anchors = [akLeft, akTop, akRight, akBottom]
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 1
    OnDrawCell = StringGridDrawCell
  end
  object ColorEnabledCheckBox: TCheckBox
    Left = 8
    Top = 159
    Width = 234
    Height = 17
    Caption = #1042#1099#1076#1077#1083#1080#1090#1100' '#1094#1074#1077#1090#1086#1084
    Checked = True
    State = cbChecked
    TabOrder = 2
    OnClick = ColorEnabledCheckBoxClick
  end
  object ExportButton: TButton
    Left = 8
    Top = 182
    Width = 75
    Height = 25
    Caption = #1069#1082#1089#1087#1086#1088#1090
    TabOrder = 3
    OnClick = ExportButtonClick
  end
end
