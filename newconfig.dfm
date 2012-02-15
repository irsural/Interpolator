object NewConfigF: TNewConfigF
  Left = 412
  Top = 132
  BorderStyle = bsSingle
  Caption = #1053#1086#1074#1072#1103' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1103
  ClientHeight = 847
  ClientWidth = 1029
  Color = clBtnFace
  Constraints.MinHeight = 885
  Constraints.MinWidth = 1045
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  DesignSize = (
    1029
    847)
  PixelsPerInch = 96
  TextHeight = 13
  object InformationPanel: TPanel
    Left = 0
    Top = 0
    Width = 1029
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
    Left = 866
    Top = 815
    Width = 73
    Height = 25
    Anchors = [akBottom]
    Caption = #1054#1050
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = CreateConfigButtonClick
  end
  object ExitButton: TButton
    Left = 952
    Top = 815
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
    Width = 1029
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
    Width = 1029
    Height = 669
    Align = alTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 4
    DesignSize = (
      1029
      669)
    object Label3: TLabel
      Left = 688
      Top = 360
      Width = 86
      Height = 13
      Anchors = [akLeft, akBottom]
      Caption = #1048#1085#1076#1077#1082#1089' '#1089#1095#1077#1090#1095#1080#1082#1072
    end
    object GroupBox1: TGroupBox
      Left = 312
      Top = 357
      Width = 361
      Height = 305
      Anchors = [akLeft, akBottom]
      Caption = 'EEPROM'
      TabOrder = 0
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
    object ListByteSG: TStringGrid
      Left = 2
      Top = 169
      Width = 1025
      Height = 181
      Align = alTop
      Anchors = [akLeft, akTop, akRight, akBottom]
      DefaultColWidth = 150
      DefaultRowHeight = 17
      FixedCols = 0
      RowCount = 9
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      TabOrder = 1
      OnDrawCell = ListByteSGDrawCell
      OnSelectCell = ListByteSGSelectCell
      ColWidths = (
        258
        78
        90
        115
        132)
    end
    object IndexWorkTimeEdit: TEdit
      Left = 792
      Top = 361
      Width = 121
      Height = 21
      Anchors = [akLeft, akBottom]
      TabOrder = 2
      Text = '16'
    end
    object ListParameterSG: TStringGrid
      Left = 2
      Top = 2
      Width = 1025
      Height = 167
      Align = alTop
      ColCount = 8
      DefaultColWidth = 150
      DefaultRowHeight = 17
      FixedCols = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      TabOrder = 3
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
    object MultimeterSettingsGroupBox: TGroupBox
      Left = 8
      Top = 357
      Width = 297
      Height = 305
      Anchors = [akLeft, akBottom]
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079#1084#1077#1088#1080#1090#1077#1083#1100#1085#1086#1075#1086' '#1087#1088#1080#1073#1086#1088#1072
      TabOrder = 4
      object Label1: TLabel
        Left = 8
        Top = 16
        Width = 78
        Height = 13
        Caption = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
      end
      object MeasTypeCB: TComboBox
        Left = 8
        Top = 32
        Width = 281
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
      end
      object Delay_MeasLE: TLabeledEdit
        Left = 8
        Top = 112
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
        Top = 152
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
        Top = 72
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
  end
  object Panel4: TPanel
    Left = 0
    Top = 81
    Width = 1029
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
