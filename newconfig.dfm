object NewConfigF: TNewConfigF
  Left = 540
  Top = 68
  BorderStyle = bsSingle
  Caption = #1050#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1103' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080
  ClientHeight = 591
  ClientWidth = 896
  Color = clBtnFace
  Constraints.MinHeight = 550
  Constraints.MinWidth = 800
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  ShowHint = True
  OnClose = FormClose
  DesignSize = (
    896
    591)
  PixelsPerInch = 96
  TextHeight = 13
  object CreateConfigButton: TButton
    Left = 734
    Top = 558
    Width = 73
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1054#1050
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = CreateConfigButtonClick
    ExplicitLeft = 869
    ExplicitTop = 605
  end
  object ExitButton: TButton
    Left = 813
    Top = 558
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 1
    OnClick = ExitButtonClick
    ExplicitLeft = 948
    ExplicitTop = 605
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 896
    Height = 48
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 2
    ExplicitTop = 27
    ExplicitWidth = 963
    object Label2: TLabel
      Left = 719
      Top = 6
      Width = 90
      Height = 13
      Caption = #1050#1086#1083'-'#1074#1086' '#1076#1086#1087'. '#1073#1080#1090#1086#1074
    end
    object Label4: TLabel
      Left = 577
      Top = 6
      Width = 122
      Height = 13
      Caption = #1050#1086#1083'-'#1074#1086' '#1076#1086#1087'. '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
    end
    object NameConfigLE: TLabeledEdit
      Left = 8
      Top = 21
      Width = 409
      Height = 21
      EditLabel.Width = 97
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1080
      ReadOnly = True
      TabOrder = 0
    end
    object ChangeNameButton: TButton
      Left = 423
      Top = 21
      Width = 34
      Height = 21
      Caption = '...'
      TabOrder = 1
      OnClick = ChangeNameButtonClick
    end
    object BitsExCSpinEdit: TCSpinEdit
      Left = 719
      Top = 20
      Width = 121
      Height = 22
      MaxValue = 1000000
      MinValue = 1
      TabOrder = 2
      OnChange = BitsExCSpinEditChange
    end
    object ParamsExCSpinEdit: TCSpinEdit
      Left = 577
      Top = 20
      Width = 121
      Height = 22
      MaxValue = 1000000
      MinValue = 1
      TabOrder = 3
      OnChange = ParamsExCSpinEditChange
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 148
    Width = 896
    Height = 404
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 3
    ExplicitTop = 187
    ExplicitWidth = 1000
    object PageControl1: TPageControl
      Left = 8
      Top = 6
      Width = 881
      Height = 395
      ActivePage = MeasAndCalibrationSettingsTabSheet
      TabOrder = 0
      object PrimaryNetworkVariablesTabSheet: TTabSheet
        Caption = #1057#1077#1090#1077#1074#1099#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1099#1077
        ImageIndex = 2
        ExplicitWidth = 947
        object ListParameterSG: TStringGrid
          Left = 0
          Top = 0
          Width = 873
          Height = 364
          Align = alTop
          ColCount = 8
          DefaultColWidth = 150
          DefaultRowHeight = 17
          FixedCols = 0
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          TabOrder = 0
          OnDrawCell = ListParameterSGDrawCell
          OnSelectCell = ListParameterSGSelectCell
          ExplicitWidth = 869
          ColWidths = (
            122
            72
            120
            74
            115
            108
            108
            135)
        end
      end
      object SecondaryNetworkVariablesTabSheet: TTabSheet
        Caption = #1057#1077#1090#1077#1074#1099#1077' '#1073#1080#1090#1099
        ImageIndex = 1
        ExplicitWidth = 947
        object ListByteSG: TStringGrid
          Left = 0
          Top = 0
          Width = 873
          Height = 364
          Align = alTop
          Anchors = [akLeft, akTop, akRight, akBottom]
          DefaultColWidth = 150
          DefaultRowHeight = 17
          FixedCols = 0
          RowCount = 9
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          TabOrder = 0
          OnDrawCell = ListByteSGDrawCell
          OnSelectCell = ListByteSGSelectCell
          ExplicitWidth = 947
          ColWidths = (
            258
            78
            90
            115
            132)
        end
      end
      object MeasAndCalibrationSettingsTabSheet: TTabSheet
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '#1080' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080
        ExplicitWidth = 947
        DesignSize = (
          873
          367)
        object Label3: TLabel
          Left = 373
          Top = 328
          Width = 86
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = #1048#1085#1076#1077#1082#1089' '#1089#1095#1077#1090#1095#1080#1082#1072
        end
        object MultimeterSettingsGroupBox: TGroupBox
          Left = 1
          Top = 3
          Width = 248
          Height = 289
          Anchors = [akLeft, akBottom]
          Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079#1084#1077#1088#1080#1090#1077#1083#1100#1085#1086#1075#1086' '#1087#1088#1080#1073#1086#1088#1072
          TabOrder = 0
          object Label1: TLabel
            Left = 13
            Top = 24
            Width = 78
            Height = 13
            Caption = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
          end
          object MeasTypeCB: TComboBox
            Left = 13
            Top = 40
            Width = 224
            Height = 21
            Style = csDropDownList
            TabOrder = 0
          end
          object Delay_MeasLE: TLabeledEdit
            Left = 13
            Top = 153
            Width = 224
            Height = 21
            EditLabel.Width = 134
            EditLabel.Height = 13
            EditLabel.Caption = #1047#1072#1076#1077#1088#1078#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', '#1089#1077#1082
            TabOrder = 1
            Text = '1'
          end
          object CountResetOverBitLE: TLabeledEdit
            Left = 13
            Top = 257
            Width = 224
            Height = 21
            EditLabel.Width = 207
            EditLabel.Height = 13
            EditLabel.Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1087#1099#1090#1086#1082' '#1087#1077#1088#1077#1079#1072#1087#1091#1089#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
            TabOrder = 2
          end
          object MeasIntervalLabeledEdit: TLabeledEdit
            Left = 13
            Top = 205
            Width = 224
            Height = 21
            Hint = 
              #1052#1091#1083#1100#1090#1080#1084#1077#1090#1088' '#1089#1076#1077#1083#1072#1077#1090' '#1089#1090#1086#1083#1100#1082#1086' '#1080#1079#1084#1077#1088#1077#1085#1080#1081', '#1089#1082#1086#1083#1100#1082#1086' '#1091#1089#1087#1077#1077#1090' '#1079#1072' '#1091#1082#1072#1079#1072#1085#1085#1086 +
              #1077' '#1074' '#1101#1090#1086#1084' '#1087#1086#1083#1077' '#1074#1088#1077#1084#1103', '#1085#1086' '#1085#1077' '#1084#1077#1085#1100#1096#1077' '#1095#1077#1084' '#1086#1076#1085#1086' '#1080#1079#1084#1077#1088#1077#1085#1080#1077
            EditLabel.Width = 218
            EditLabel.Height = 13
            EditLabel.Caption = #1042#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', '#1089#1077#1082' ("0" = 1 '#1080#1079#1084#1077#1088#1077#1085#1080#1077')'
            TabOrder = 3
          end
          object RangeCheckBox: TCheckBox
            Left = 13
            Top = 77
            Width = 268
            Height = 17
            Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1076#1080#1072#1087#1072#1079#1086#1085
            TabOrder = 4
            OnClick = RangeCheckBoxClick
          end
          object RangeEdit: TEdit
            Left = 13
            Top = 100
            Width = 224
            Height = 21
            Enabled = False
            TabOrder = 5
          end
        end
        object GroupBox1: TGroupBox
          Left = 255
          Top = 3
          Width = 338
          Height = 289
          Anchors = [akLeft, akBottom]
          Caption = 'EEPROM'
          TabOrder = 1
          object Label9: TLabel
            Left = 8
            Top = 56
            Width = 140
            Height = 13
            Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1086#1076#1076#1080#1072#1087#1072#1079#1086#1085#1086#1074
          end
          object IndexEEPROMLabel: TLabel
            Left = 8
            Top = 18
            Width = 83
            Height = 13
            Caption = #1048#1085#1076#1077#1082#1089' '#1074#1086#1088#1086#1085#1082#1080
          end
          object CSpinEdit1: TCSpinEdit
            Left = 160
            Top = 48
            Width = 89
            Height = 22
            EditorEnabled = False
            MaxValue = 1000000
            MinValue = 1
            TabOrder = 0
            Value = 1
            OnChange = CSpinEdit1Change
          end
          object SubDiapasonSG: TStringGrid
            Left = 3
            Top = 100
            Width = 329
            Height = 181
            DefaultRowHeight = 17
            RowCount = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            TabOrder = 1
            ColWidths = (
              64
              64
              64
              64
              64)
          end
          object TypeSubDiapasonParam1RB: TRadioButton
            Left = 64
            Top = 77
            Width = 89
            Height = 17
            Caption = #1055#1072#1088#1072#1084#1077#1090#1088' 1'
            TabOrder = 2
          end
          object TypeSubDiapasonParam2RB: TRadioButton
            Left = 160
            Top = 77
            Width = 89
            Height = 17
            Caption = #1055#1072#1088#1072#1084#1077#1090#1088' 2'
            TabOrder = 3
          end
          object ValueIndexEEPROMEdit: TEdit
            Left = 160
            Top = 18
            Width = 89
            Height = 21
            TabOrder = 4
            Text = '17'
          end
        end
        object IndexWorkTimeEdit: TEdit
          Left = 472
          Top = 326
          Width = 121
          Height = 21
          Anchors = [akLeft, akBottom]
          TabOrder = 2
          Text = '16'
        end
        object GroupBox2: TGroupBox
          Left = 599
          Top = 119
          Width = 272
          Height = 149
          Caption = #1050#1086#1085#1090#1088#1086#1083#1100' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' '#1090#1077#1088#1084#1086#1089#1090#1072#1090#1072' '#1080#1079#1084#1077#1088#1080#1090'. '#1095#1072#1089#1090#1080
          TabOrder = 3
          object TemperatureControlVariableCheckBox: TCheckBox
            Left = 8
            Top = 16
            Width = 193
            Height = 17
            Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1082#1086#1085#1090#1088#1086#1083#1100' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099
            TabOrder = 0
            OnClick = TemperatureControlVariableCheckBoxClick
          end
          object TemperatureVariableIndexByteLabeledEdit: TLabeledEdit
            Left = 8
            Top = 53
            Width = 121
            Height = 21
            EditLabel.Width = 155
            EditLabel.Height = 13
            EditLabel.Caption = #1048#1085#1076#1077#1082#1089' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1081' ('#1074' '#1073#1072#1081#1090#1072#1093')'
            TabOrder = 1
          end
          object ReferenceTemperetureLabeledEdit: TLabeledEdit
            Left = 8
            Top = 121
            Width = 121
            Height = 21
            EditLabel.Width = 113
            EditLabel.Height = 13
            EditLabel.Caption = #1059#1089#1090#1072#1074#1082#1072' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099
            TabOrder = 2
          end
          object DifferenceTemperatureLabeledEdit: TLabeledEdit
            Left = 140
            Top = 121
            Width = 121
            Height = 21
            EditLabel.Width = 125
            EditLabel.Height = 13
            EditLabel.Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1086#1077' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1077
            TabOrder = 3
          end
          object TemperatureControlCheckBox: TCheckBox
            Left = 9
            Top = 83
            Width = 272
            Height = 17
            Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1076#1083#1103' '#1074#1099#1076#1077#1083#1077#1085#1085#1086#1075#1086' '#1076#1080#1072#1087#1072#1079#1086#1085#1072' '#1103#1095#1077#1077#1082
            TabOrder = 4
            OnClick = TemperatureControlCheckBoxClick
          end
        end
        object GroupBox3: TGroupBox
          Left = 599
          Top = 274
          Width = 272
          Height = 79
          Caption = #1050#1086#1085#1090#1088#1086#1083#1100' '#1074#1099#1093#1086#1076#1085#1086#1075#1086' '#1079#1085#1072#1095#1077#1085#1080#1103
          TabOrder = 4
          object OutParameterControlCheckBox: TCheckBox
            Left = 8
            Top = 16
            Width = 305
            Height = 17
            Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1082#1086#1085#1090#1088#1086#1083#1100' '#1074#1099#1093#1086#1076#1085#1086#1075#1086' '#1079#1085#1072#1095#1077#1085#1080#1103
            TabOrder = 0
          end
          object MaxRelativeDifferenceOutParameterLabeledEdit: TLabeledEdit
            Left = 8
            Top = 51
            Width = 121
            Height = 21
            EditLabel.Width = 127
            EditLabel.Height = 13
            EditLabel.Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1086#1077' '#1086#1090#1085'. '#1086#1090#1082#1083#1086#1085'.'
            TabOrder = 1
          end
          object TimeCalcDifferenceLabeledEdit: TLabeledEdit
            Left = 140
            Top = 51
            Width = 121
            Height = 21
            EditLabel.Width = 96
            EditLabel.Height = 13
            EditLabel.Caption = #1042#1088#1077#1084#1077#1085#1085#1086#1077' '#1086#1082#1085#1086', '#1089
            TabOrder = 2
          end
        end
        object GroupBox4: TGroupBox
          Left = 599
          Top = 3
          Width = 272
          Height = 110
          Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1074#1099#1093#1086#1076#1085#1086#1075#1086' '#1079#1085#1072#1095#1077#1085#1080#1103' '#1076#1083#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
          TabOrder = 5
          object Label5: TLabel
            Left = 8
            Top = 64
            Width = 113
            Height = 13
            Hint = #1055#1077#1088#1080#1086#1076' '#1084#1077#1078#1076#1091' '#1086#1090#1089#1095#1077#1090#1072#1084#1080
            Caption = #1042#1088#1077#1084#1103' '#1076#1080#1089#1082#1088#1077#1090#1080#1079#1072#1094#1080#1080
          end
          object Label8: TLabel
            Left = 143
            Top = 63
            Width = 90
            Height = 13
            Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1090#1086#1095#1077#1082
          end
          object ConsiderOutParameterForMeasurementCheckBox: TCheckBox
            Left = 8
            Top = 16
            Width = 321
            Height = 17
            Hint = 
              #1050#1086#1088#1088#1077#1082#1090#1080#1088#1086#1074#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1085#1086#1075#1086' '#1079#1085#1072#1095#1077#1085#1080#1103' '#1089' '#1084#1091#1083#1100#1090#1080#1084#1077#1090#1088#1072' '#1074' '#1089#1086#1086#1090#1074#1077#1090#1089#1090#1074#1080#1080' ' +
              #1089' '#1074#1099#1093#1086#1076#1085#1099#1084' '#1079#1085#1072#1095#1077#1085#1080#1077#1084' '#1074#1085#1091#1090#1088#1077#1085#1085#1077#1075#1086' '#1080#1079#1084#1077#1088#1080#1090#1077#1083#1103
            Caption = #1059#1095#1080#1090#1099#1074#1072#1090#1100' '#1074#1099#1093#1086#1076#1085#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077' '#1087#1088#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1080
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnClick = ConsiderOutParameterForMeasurementCheckBoxClick
          end
          object OutParameterFilterCheckBox: TCheckBox
            Left = 8
            Top = 40
            Width = 321
            Height = 17
            Hint = 
              #1050#1086#1088#1088#1077#1082#1090#1080#1088#1086#1074#1082#1072' '#1074#1099#1093#1086#1076#1085#1086#1075#1086' '#1079#1085#1072#1095#1077#1085#1080#1103' '#1074' '#1089#1086#1086#1090#1074#1077#1090#1089#1090#1074#1080#1080' '#1089' '#1086#1090#1092#1080#1083#1100#1090#1088#1086#1074#1072#1085#1085#1099 +
              #1084' '#1074#1099#1093#1086#1076#1085#1099#1084' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1084
            Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1092#1080#1083#1100#1090#1088#1072#1094#1080#1102' '#1074#1099#1093#1086#1076#1085#1086#1075#1086' '#1079#1085#1072#1095#1077#1085#1080#1103
            TabOrder = 1
            OnClick = OutParameterFilterCheckBoxClick
          end
          object FilterSamplingTimeEdit: TEdit
            Left = 8
            Top = 80
            Width = 121
            Height = 21
            TabOrder = 2
          end
          object FilterPointCountEdit: TEdit
            Left = 140
            Top = 80
            Width = 121
            Height = 21
            TabOrder = 3
          end
        end
      end
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 48
    Width = 896
    Height = 74
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 4
    ExplicitTop = 69
    object DevideGroupBox: TGroupBox
      Left = 8
      Top = 6
      Width = 417
      Height = 59
      Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1086
      TabOrder = 0
      object DeviceNameLabel: TLabel
        Left = 17
        Top = 15
        Width = 22
        Height = 13
        Caption = #1048#1084#1103
      end
      object DeviceLabel: TLabel
        Left = 248
        Top = 15
        Width = 82
        Height = 13
        Caption = #1058#1080#1087' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103
      end
      object DeviceNameComboBox: TComboBox
        Left = 17
        Top = 30
        Width = 225
        Height = 21
        Style = csDropDownList
        TabOrder = 0
        OnChange = DeviceNameComboBoxChange
      end
      object ChangeDeviceConfigButton: TButton
        Left = 337
        Top = 30
        Width = 75
        Height = 21
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
        TabOrder = 1
        OnClick = ChangeDeviceConfigButtonClick
      end
      object DeviceComboBox: TComboBox
        Left = 248
        Top = 30
        Width = 83
        Height = 21
        Style = csDropDownList
        TabOrder = 2
        OnChange = DeviceComboBoxChange
      end
    end
    object RefDeviceGroupBox: TGroupBox
      Left = 431
      Top = 6
      Width = 413
      Height = 59
      Caption = #1054#1087#1086#1088#1085#1086#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1086
      TabOrder = 1
      object RefDeviceLabel: TLabel
        Left = 246
        Top = 15
        Width = 82
        Height = 13
        Caption = #1058#1080#1087' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103
      end
      object RefDeviceNameComboBox: TComboBox
        Left = 15
        Top = 30
        Width = 225
        Height = 21
        Style = csDropDownList
        TabOrder = 0
        OnChange = RefDeviceNameComboBoxChange
      end
      object ReferenceChannelCheckB: TCheckBox
        Left = 15
        Top = 13
        Width = 97
        Height = 17
        Caption = #1054#1087#1086#1088#1085#1099#1081' '#1082#1072#1085#1072#1083
        TabOrder = 1
        OnClick = ReferenceChannelCheckBClick
      end
      object ChangeRefDeviceConfigButton: TButton
        Left = 334
        Top = 30
        Width = 75
        Height = 21
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
        TabOrder = 2
        OnClick = ChangeRefDeviceConfigButtonClick
      end
      object RefDeviceComboBox: TComboBox
        Left = 246
        Top = 30
        Width = 83
        Height = 21
        Style = csDropDownList
        TabOrder = 3
        OnChange = RefDeviceComboBoxChange
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 122
    Width = 896
    Height = 26
    Align = alTop
    TabOrder = 5
    ExplicitTop = 161
    ExplicitWidth = 1031
    object CellsRangeLabel: TLabel
      Left = 8
      Top = 6
      Width = 54
      Height = 13
      Caption = 'CellsRange'
    end
  end
end
