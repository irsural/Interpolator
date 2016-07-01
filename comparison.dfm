object ComparsionDataForm: TComparsionDataForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'ComparsionDataForm'
  ClientHeight = 513
  ClientWidth = 1112
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    1112
    513)
  PixelsPerInch = 96
  TextHeight = 13
  object FirstDataFileNameEdit: TEdit
    Left = 88
    Top = 8
    Width = 982
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
  end
  object SecondDataFileNameEdit: TEdit
    Left = 88
    Top = 35
    Width = 982
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 1
  end
  object OpenFirstDataFileButton: TButton
    Left = 1076
    Top = 8
    Width = 31
    Height = 21
    Anchors = [akTop, akRight]
    Caption = '...'
    TabOrder = 2
    OnClick = OpenFirstDataFileButtonClick
  end
  object OpenSecondDataFileButton: TButton
    Left = 1076
    Top = 35
    Width = 31
    Height = 21
    Anchors = [akTop, akRight]
    Caption = '...'
    TabOrder = 3
    OnClick = OpenSecondDataFileButtonClick
  end
  object Panel1: TPanel
    Left = 0
    Top = 62
    Width = 1112
    Height = 451
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 4
    object StringGrid: TStringGrid
      Left = 184
      Top = 0
      Width = 836
      Height = 445
      Align = alCustom
      Anchors = [akLeft, akTop, akRight, akBottom]
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      TabOrder = 0
      OnDrawCell = StringGridDrawCell
      ColWidths = (
        64
        64
        64
        64
        64)
    end
    object MinLabeledEdit: TLabeledEdit
      Left = 7
      Top = 56
      Width = 171
      Height = 21
      EditLabel.Width = 149
      EditLabel.Height = 13
      EditLabel.Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1086#1077' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1077', %'
      TabOrder = 1
    end
    object MaxLabeledEdit: TLabeledEdit
      Left = 7
      Top = 96
      Width = 171
      Height = 21
      EditLabel.Width = 154
      EditLabel.Height = 13
      EditLabel.Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086#1077' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1077', %'
      TabOrder = 2
    end
    object ColorEnabledCheckBox: TCheckBox
      Left = 6
      Top = 123
      Width = 122
      Height = 17
      Caption = #1042#1099#1076#1077#1083#1080#1090#1100' '#1094#1074#1077#1090#1086#1084
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = ColorEnabledCheckBoxClick
    end
    object ColorLabeledEdit1: TLabeledEdit
      Left = 23
      Top = 208
      Width = 155
      Height = 21
      EditLabel.Width = 86
      EditLabel.Height = 13
      EditLabel.Caption = 'ColorLabeledEdit1'
      TabOrder = 4
    end
    object ColorLabeledEdit2: TLabeledEdit
      Left = 23
      Top = 248
      Width = 155
      Height = 21
      EditLabel.Width = 86
      EditLabel.Height = 13
      EditLabel.Caption = 'ColorLabeledEdit2'
      TabOrder = 5
    end
    object ColorLabeledEdit3: TLabeledEdit
      Left = 23
      Top = 288
      Width = 155
      Height = 21
      EditLabel.Width = 86
      EditLabel.Height = 13
      EditLabel.Caption = 'ColorLabeledEdit3'
      TabOrder = 6
    end
    object ColorLabeledEdit4: TLabeledEdit
      Left = 23
      Top = 328
      Width = 155
      Height = 21
      EditLabel.Width = 86
      EditLabel.Height = 13
      EditLabel.Caption = 'ColorLabeledEdit4'
      TabOrder = 7
    end
    object ColorShadesRadioButton: TRadioButton
      Left = 23
      Top = 146
      Width = 155
      Height = 17
      Caption = #1054#1090#1090#1077#1085#1082#1080' '#1086#1076#1085#1086#1075#1086' '#1094#1074#1077#1090#1072
      Checked = True
      TabOrder = 8
      TabStop = True
      OnClick = ColorShadesRadioButtonClick
    end
    object DifferentColorsRadioButton: TRadioButton
      Left = 24
      Top = 168
      Width = 154
      Height = 17
      Caption = #1056#1072#1079#1085#1099#1084#1080' '#1094#1074#1077#1090#1072#1084#1080
      TabOrder = 9
      OnClick = DifferentColorsRadioButtonClick
    end
  end
  object СompareButton: TButton
    Left = 7
    Top = 8
    Width = 75
    Height = 48
    Caption = #1057#1088#1072#1074#1080#1085#1080#1090#1100
    TabOrder = 5
    OnClick = СompareButtonClick
  end
  object ExportButton: TButton
    Left = 1029
    Top = 62
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1069#1082#1089#1087#1086#1088#1090
    TabOrder = 6
    OnClick = ExportButtonClick
  end
  object OpenDialog: TOpenDialog
    Left = 216
    Top = 408
  end
  object SaveDialog: TSaveDialog
    Left = 280
    Top = 408
  end
end
