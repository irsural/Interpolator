object NewConfigF: TNewConfigF
  Left = 314
  Top = 148
  BorderStyle = bsSingle
  Caption = #1053#1086#1074#1072#1103' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1103
  ClientHeight = 631
  ClientWidth = 1044
  Color = clBtnFace
  Constraints.MinHeight = 550
  Constraints.MinWidth = 1037
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  DesignSize = (
    1044
    631)
  PixelsPerInch = 96
  TextHeight = 13
  object InformationPanel: TPanel
    Left = 0
    Top = 0
    Width = 1044
    Height = 33
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Caption = #1050#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1103' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object CreateConfigButton: TButton
    Left = 881
    Top = 599
    Width = 73
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #1054#1050
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = CreateConfigButtonClick
  end
  object ExitButton: TButton
    Left = 967
    Top = 599
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object Panel2: TPanel
    Left = 0
    Top = 33
    Width = 1044
    Height = 48
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 3
    object NameConfigLE: TLabeledEdit
      Left = 24
      Top = 20
      Width = 529
      Height = 21
      EditLabel.Width = 97
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1080
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 137
    Width = 1044
    Height = 456
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 4
    object PageControl1: TPageControl
      Left = 8
      Top = 8
      Width = 1033
      Height = 441
      ActivePage = SecondaryNetworkVariablesTabSheet
      TabIndex = 1
      TabOrder = 0
      object PrimaryNetworkVariablesTabSheet: TTabSheet
        Caption = #1054#1089#1085#1086#1074#1085#1099#1077' '#1089#1077#1090#1077#1074#1099#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1099#1077
        ImageIndex = 2
        object ListParameterSG: TStringGrid
          Left = 0
          Top = 0
          Width = 1025
          Height = 305
          Align = alTop
          ColCount = 8
          DefaultColWidth = 150
          DefaultRowHeight = 17
          FixedCols = 0
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          TabOrder = 0
          OnDrawCell = ListParameterSGDrawCell
          OnSelectCell = ListParameterSGSelectCell
          ColWidths = (
            150
            113
            136
            85
            115
            108
            150
            150)
        end
      end
      object SecondaryNetworkVariablesTabSheet: TTabSheet
        Caption = #1042#1089#1087#1086#1084#1086#1075#1072#1090#1077#1083#1100#1085#1099#1077' '#1089#1077#1090#1077#1074#1099#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1099#1077
        ImageIndex = 1
        object ListByteSG: TStringGrid
          Left = 0
          Top = 0
          Width = 1025
          Height = 409
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
          ColWidths = (
            258
            78
            90
            115
            132)
        end
      end
      object MeasAndCalibrationSettingsTabSheet: TTabSheet
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1080' '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1080
        DesignSize = (
          1025
          413)
        object Label3: TLabel
          Left = 675
          Top = 24
          Width = 86
          Height = 13
          Anchors = [akLeft, akBottom]
          Caption = #1048#1085#1076#1077#1082#1089' '#1089#1095#1077#1090#1095#1080#1082#1072
        end
        object MultimeterSettingsGroupBox: TGroupBox
          Left = 0
          Top = 8
          Width = 297
          Height = 405
          Anchors = [akLeft, akBottom]
          Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079#1084#1077#1088#1080#1090#1077#1083#1100#1085#1086#1075#1086' '#1087#1088#1080#1073#1086#1088#1072
          TabOrder = 0
          object Label1: TLabel
            Left = 8
            Top = 24
            Width = 78
            Height = 13
            Caption = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
          end
          object MeasTypeCB: TComboBox
            Left = 8
            Top = 40
            Width = 281
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 0
          end
          object Delay_MeasLE: TLabeledEdit
            Left = 8
            Top = 120
            Width = 281
            Height = 21
            EditLabel.Width = 134
            EditLabel.Height = 13
            EditLabel.Caption = #1047#1072#1076#1077#1088#1078#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', '#1089#1077#1082
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
            Text = '1'
          end
          object CountResetOverBitLE: TLabeledEdit
            Left = 8
            Top = 160
            Width = 281
            Height = 21
            EditLabel.Width = 232
            EditLabel.Height = 13
            EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1086#1087#1099#1090#1086#1082' '#1087#1077#1088#1077#1079#1072#1087#1091#1089#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 2
          end
          object MeasRangeKoefLabeledEdit: TLabeledEdit
            Left = 8
            Top = 80
            Width = 281
            Height = 21
            EditLabel.Width = 232
            EditLabel.Height = 13
            EditLabel.Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1079#1085#1072#1095#1077#1085#1080#1103' '#1091#1089#1090#1072#1085#1086#1074#1082#1080' '#1076#1080#1072#1087#1072#1079#1086#1085#1072
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 3
          end
        end
        object GroupBox1: TGroupBox
          Left = 304
          Top = 16
          Width = 361
          Height = 397
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
            Left = 8
            Top = 88
            Width = 345
            Height = 193
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
            Left = 264
            Top = 40
            Width = 89
            Height = 17
            Caption = #1055#1072#1088#1072#1084#1077#1090#1088' 1'
            TabOrder = 2
          end
          object TypeSubDiapasonParam2RB: TRadioButton
            Left = 264
            Top = 64
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
          Left = 768
          Top = 16
          Width = 121
          Height = 21
          Anchors = [akLeft, akBottom]
          TabOrder = 2
          Text = '16'
        end
        object GroupBox2: TGroupBox
          Left = 672
          Top = 156
          Width = 337
          Height = 121
          Caption = #1050#1086#1085#1090#1088#1086#1083#1100' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' '#1090#1077#1088#1084#1086#1089#1090#1072#1090#1072' '#1080#1079#1084#1077#1088#1080#1090#1077#1083#1100#1085#1086#1081' '#1095#1072#1089#1090#1080
          TabOrder = 3
          object TemperatureControlCheckBox: TCheckBox
            Left = 8
            Top = 16
            Width = 193
            Height = 17
            Caption = #1042#1082#1083#1102#1095#1080#1090#1100' '#1082#1086#1085#1090#1088#1086#1083#1100' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099
            TabOrder = 0
            OnClick = TemperatureControlCheckBoxClick
          end
          object TemperatureVariableIndexByteLabeledEdit: TLabeledEdit
            Left = 8
            Top = 48
            Width = 153
            Height = 21
            EditLabel.Width = 155
            EditLabel.Height = 13
            EditLabel.Caption = #1048#1085#1076#1077#1082#1089' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1081' ('#1074' '#1073#1072#1081#1090#1072#1093')'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
          object ReferenceTemperetureLabeledEdit: TLabeledEdit
            Left = 8
            Top = 88
            Width = 153
            Height = 21
            EditLabel.Width = 113
            EditLabel.Height = 13
            EditLabel.Caption = #1059#1089#1090#1072#1074#1082#1072' '#1090#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 2
          end
          object DifferenceTemperatureLabeledEdit: TLabeledEdit
            Left = 168
            Top = 88
            Width = 153
            Height = 21
            EditLabel.Width = 125
            EditLabel.Height = 13
            EditLabel.Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1086#1077' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1077
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 3
          end
        end
        object GroupBox3: TGroupBox
          Left = 672
          Top = 284
          Width = 337
          Height = 81
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
            Top = 48
            Width = 153
            Height = 21
            EditLabel.Width = 148
            EditLabel.Height = 13
            EditLabel.Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1086#1077' '#1086#1090#1085'. '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1077
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
          object TimeCalcDifferenceLabeledEdit: TLabeledEdit
            Left = 168
            Top = 48
            Width = 153
            Height = 21
            EditLabel.Width = 96
            EditLabel.Height = 13
            EditLabel.Caption = #1042#1088#1077#1084#1077#1085#1085#1086#1077' '#1086#1082#1085#1086', '#1089
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 2
          end
        end
        object GroupBox4: TGroupBox
          Left = 672
          Top = 40
          Width = 337
          Height = 113
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
            Left = 168
            Top = 64
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
            Width = 153
            Height = 21
            TabOrder = 2
          end
          object FilterPointCountEdit: TEdit
            Left = 168
            Top = 80
            Width = 161
            Height = 21
            TabOrder = 3
          end
        end
      end
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 81
    Width = 1044
    Height = 56
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 5
    object Label4: TLabel
      Left = 704
      Top = 8
      Width = 147
      Height = 13
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1076#1086#1087'. '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
    end
    object Label2: TLabel
      Left = 864
      Top = 8
      Width = 115
      Height = 13
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1076#1086#1087'. '#1073#1080#1090#1086#1074
    end
    object IPAdressLE: TLabeledEdit
      Left = 24
      Top = 24
      Width = 121
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = 'IP - '#1072#1076#1088#1077#1089
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      Text = '127.0.0.1'
    end
    object PortLE: TLabeledEdit
      Left = 152
      Top = 24
      Width = 121
      Height = 21
      EditLabel.Width = 25
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1086#1088#1090
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      Text = '5500'
    end
    object ReferenceChannelCheckB: TCheckBox
      Left = 344
      Top = 24
      Width = 97
      Height = 17
      Caption = #1054#1087#1086#1088#1085#1099#1081' '#1082#1072#1085#1072#1083
      TabOrder = 2
      OnClick = ReferenceChannelCheckBClick
    end
    object IPAdressRefChannelLE: TLabeledEdit
      Left = 448
      Top = 24
      Width = 121
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = 'IP - '#1072#1076#1088#1077#1089
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
    end
    object PortRefChannelLE: TLabeledEdit
      Left = 576
      Top = 24
      Width = 121
      Height = 21
      EditLabel.Width = 25
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1086#1088#1090
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
    end
    object BitsExCSpinEdit: TCSpinEdit
      Left = 864
      Top = 24
      Width = 121
      Height = 22
      MaxValue = 1000000
      MinValue = 1
      TabOrder = 5
      OnChange = BitsExCSpinEditChange
    end
    object ParamsExCSpinEdit: TCSpinEdit
      Left = 704
      Top = 24
      Width = 153
      Height = 22
      MaxValue = 1000000
      MinValue = 1
      TabOrder = 6
      OnChange = ParamsExCSpinEditChange
    end
  end
  object SaveDialogConfig: TSaveDialog
    DefaultExt = 'ini'
    FileName = 'config1.ini'
    Filter = #1060#1072#1081#1083#1099' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1080' (*.ini)|*.ini|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Left = 680
    Top = 48
  end
end
