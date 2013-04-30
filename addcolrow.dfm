object AddCorRowF: TAddCorRowF
  Left = 370
  Top = 290
  Width = 635
  Height = 358
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1089#1090#1086#1083#1073#1094#1086#1074' '#1080' '#1089#1090#1088#1086#1082
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 627
    Height = 81
    Align = alTop
    Caption = #1052#1077#1089#1090#1086' '#1074#1089#1090#1072#1074#1082#1080
    TabOrder = 0
    object ColLabeledE: TLabeledEdit
      Left = 10
      Top = 35
      Width = 100
      Height = 21
      EditLabel.Width = 42
      EditLabel.Height = 13
      EditLabel.Caption = #1057#1090#1086#1083#1073#1077#1094
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      Text = '2'
    end
    object RowLabeledE: TLabeledEdit
      Left = 160
      Top = 35
      Width = 100
      Height = 21
      EditLabel.Width = 36
      EditLabel.Height = 13
      EditLabel.Caption = #1057#1090#1088#1086#1082#1072
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      Text = '2'
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 81
    Width = 627
    Height = 216
    Align = alTop
    Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1103' '#1089#1090#1086#1083#1073#1094#1086#1074' '#1080' '#1089#1090#1088#1086#1082
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object NameTypeStepColLabel: TLabel
      Left = 500
      Top = 55
      Width = 47
      Height = 13
      Caption = #1058#1080#1087' '#1096#1072#1075#1072
    end
    object NameTypeStepRowLabel: TLabel
      Left = 500
      Top = 145
      Width = 47
      Height = 13
      Caption = #1058#1080#1087' '#1096#1072#1075#1072
    end
    object AddGroupColCheckBox: TCheckBox
      Left = 8
      Top = 20
      Width = 201
      Height = 17
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1090#1086#1083#1073#1094#1099
      TabOrder = 0
      OnClick = AddGroupColCheckBoxClick
    end
    object AddGroupRowCheckBox: TCheckBox
      Left = 8
      Top = 110
      Width = 201
      Height = 17
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1090#1088#1086#1082#1080
      TabOrder = 1
      OnClick = AddGroupRowCheckBoxClick
    end
    object StartNumColLabeledE: TLabeledEdit
      Left = 50
      Top = 70
      Width = 100
      Height = 21
      EditLabel.Width = 87
      EditLabel.Height = 13
      EditLabel.Caption = #1053#1072#1095#1072#1083#1100#1085#1086#1077' '#1095#1080#1089#1083#1086
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      Text = '1'
    end
    object EndNumColLabeledE: TLabeledEdit
      Left = 200
      Top = 70
      Width = 100
      Height = 21
      EditLabel.Width = 80
      EditLabel.Height = 13
      EditLabel.Caption = #1050#1086#1085#1077#1095#1085#1086#1077' '#1095#1080#1089#1083#1086
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      Text = '2'
    end
    object StepNumColLabeledE: TLabeledEdit
      Left = 350
      Top = 70
      Width = 100
      Height = 21
      EditLabel.Width = 79
      EditLabel.Height = 13
      EditLabel.Caption = #1064#1072#1075' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      Text = '1'
    end
    object StartNumRowLabeledE: TLabeledEdit
      Left = 50
      Top = 160
      Width = 100
      Height = 21
      EditLabel.Width = 87
      EditLabel.Height = 13
      EditLabel.Caption = #1053#1072#1095#1072#1083#1100#1085#1086#1077' '#1095#1080#1089#1083#1086
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 5
      Text = '1'
    end
    object EndNumRowLabeledE: TLabeledEdit
      Left = 200
      Top = 160
      Width = 100
      Height = 21
      EditLabel.Width = 80
      EditLabel.Height = 13
      EditLabel.Caption = #1050#1086#1085#1077#1095#1085#1086#1077' '#1095#1080#1089#1083#1086
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 6
      Text = '2'
    end
    object StepNumRowLabeledE: TLabeledEdit
      Left = 350
      Top = 160
      Width = 100
      Height = 21
      EditLabel.Width = 79
      EditLabel.Height = 13
      EditLabel.Caption = #1064#1072#1075' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 7
      Text = '1'
    end
    object TypeStepColCB: TComboBox
      Left = 500
      Top = 70
      Width = 100
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ItemIndex = 0
      ParentFont = False
      TabOrder = 8
      Text = #1048#1085#1082#1088#1077#1084#1077#1085#1090
      Items.Strings = (
        #1048#1085#1082#1088#1077#1084#1077#1085#1090
        #1044#1077#1082#1088#1080#1084#1077#1085#1090
        #1052#1085#1086#1078#1080#1090#1077#1083#1100)
    end
    object TypeStepRowCB: TComboBox
      Left = 500
      Top = 160
      Width = 100
      Height = 21
      ItemHeight = 13
      TabOrder = 9
      Text = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
      Items.Strings = (
        #1048#1085#1082#1088#1077#1084#1077#1085#1090
        #1044#1077#1082#1088#1080#1084#1077#1085#1090
        #1052#1085#1086#1078#1080#1090#1085#1083#1100)
    end
  end
  object OKButton: TButton
    Left = 440
    Top = 304
    Width = 75
    Height = 25
    Caption = #1054#1050
    TabOrder = 2
    OnClick = OKButtonClick
  end
  object CloseFormButton: TButton
    Left = 552
    Top = 304
    Width = 75
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 3
    OnClick = CloseFormButtonClick
  end
end
