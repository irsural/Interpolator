object ConfDeviceF: TConfDeviceF
  Left = -1
  Top = 199
  BorderStyle = bsSingle
  Caption = 'ConfDeviceF'
  ClientHeight = 780
  ClientWidth = 1245
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 8
    Width = 166
    Height = 13
    Caption = #1057#1087#1080#1089#1086#1082' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1081' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
  end
  object PageControl1: TPageControl
    Left = 240
    Top = 0
    Width = 1001
    Height = 745
    ActivePage = TabSheet1
    MultiLine = True
    TabIndex = 1
    TabOrder = 0
    TabPosition = tpBottom
    object TabSheet3: TTabSheet
      Caption = 'TabSheet3'
      ImageIndex = 2
      object ListView1: TListView
        Left = 8
        Top = 104
        Width = 601
        Height = 433
        Columns = <>
        TabOrder = 0
      end
      object IPAdressLE: TLabeledEdit
        Left = 8
        Top = 72
        Width = 121
        Height = 21
        EditLabel.Width = 49
        EditLabel.Height = 13
        EditLabel.Caption = 'IP - '#1072#1076#1088#1077#1089
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
      end
      object NameConfigLE: TLabeledEdit
        Left = 8
        Top = 24
        Width = 529
        Height = 21
        Color = clBtnFace
        EditLabel.Width = 97
        EditLabel.Height = 13
        EditLabel.Caption = #1048#1084#1103' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1080
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 2
      end
      object PortLE: TLabeledEdit
        Left = 160
        Top = 72
        Width = 121
        Height = 21
        EditLabel.Width = 25
        EditLabel.Height = 13
        EditLabel.Caption = #1055#1086#1088#1090
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
      end
      object IDConfLE: TLabeledEdit
        Left = 576
        Top = 24
        Width = 201
        Height = 21
        EditLabel.Width = 80
        EditLabel.Height = 13
        EditLabel.Caption = #1048#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 4
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'TabSheet1'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 993
        Height = 121
        Caption = #1042#1093#1086#1076#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
        TabOrder = 0
        object InParamSG: TStringGrid
          Left = 8
          Top = 17
          Width = 897
          Height = 96
          ColCount = 7
          DefaultColWidth = 156
          DefaultRowHeight = 17
          FixedCols = 0
          RowCount = 4
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
          TabOrder = 0
          ColWidths = (
            156
            109
            124
            156
            156
            156
            156)
        end
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 560
        Width = 993
        Height = 153
        Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1073#1080#1090#1099
        TabOrder = 1
        object InfByteExSG: TStringGrid
          Left = 9
          Top = 16
          Width = 896
          Height = 129
          DefaultColWidth = 159
          DefaultRowHeight = 17
          FixedCols = 0
          TabOrder = 0
        end
        object DelInfByteExButton: TButton
          Left = 912
          Top = 48
          Width = 75
          Height = 25
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 1
          OnClick = DelInfByteExButtonClick
        end
        object AddInfByteExButton: TButton
          Left = 912
          Top = 16
          Width = 75
          Height = 25
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 2
          OnClick = AddInfByteExButtonClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 1
        Top = 120
        Width = 992
        Height = 241
        Caption = #1042#1099#1093#1086#1076#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
        TabOrder = 2
        object OutParamSG: TStringGrid
          Left = 8
          Top = 16
          Width = 897
          Height = 217
          ColCount = 4
          DefaultColWidth = 159
          DefaultRowHeight = 17
          FixedCols = 0
          RowCount = 3
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          TabOrder = 0
        end
        object AddOutParamButton: TButton
          Left = 912
          Top = 16
          Width = 75
          Height = 25
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 1
          OnClick = AddOutParamButtonClick
        end
        object DelOutParamButton: TButton
          Left = 912
          Top = 48
          Width = 75
          Height = 25
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 2
          OnClick = DelOutParamButtonClick
        end
      end
      object GroupBox7: TGroupBox
        Left = 0
        Top = 352
        Width = 993
        Height = 209
        Caption = #1054#1073#1103#1079#1072#1090#1077#1083#1100#1085#1099#1077' '#1073#1080#1090#1099
        TabOrder = 3
        object InfByteSG: TStringGrid
          Left = 8
          Top = 16
          Width = 897
          Height = 185
          DefaultColWidth = 159
          DefaultRowHeight = 17
          FixedCols = 0
          RowCount = 6
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'TabSheet2'
      ImageIndex = 1
      object Label3: TLabel
        Left = 8
        Top = 16
        Width = 174
        Height = 13
        Caption = #1057#1087#1080#1089#1086#1082' '#1080#1079#1084#1077#1088#1080#1090#1077#1083#1100#1085#1099#1093' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
      end
      object Label4: TLabel
        Left = 304
        Top = 16
        Width = 78
        Height = 13
        Caption = #1042#1080#1076' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      end
      object MultimetrListCLB: TCheckListBox
        Left = 0
        Top = 32
        Width = 265
        Height = 673
        ItemHeight = 13
        TabOrder = 0
      end
      object Edit1: TEdit
        Left = 576
        Top = 192
        Width = 217
        Height = 21
        TabOrder = 1
      end
      object Edit2: TEdit
        Left = 576
        Top = 216
        Width = 217
        Height = 21
        TabOrder = 2
      end
      object Edit3: TEdit
        Left = 576
        Top = 240
        Width = 217
        Height = 21
        TabOrder = 3
      end
      object CheckBox2: TCheckBox
        Left = 304
        Top = 192
        Width = 249
        Height = 17
        Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1074#1088#1077#1084#1077#1085#1080' '#1089#1095#1077#1090#1072
        TabOrder = 4
      end
      object CheckBox3: TCheckBox
        Left = 304
        Top = 216
        Width = 249
        Height = 17
        Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1074#1093#1086#1076#1085#1086#1075#1086' '#1089#1086#1087#1088#1086#1090#1080#1074#1083#1077#1085#1080#1103
        TabOrder = 5
      end
      object CheckBox4: TCheckBox
        Left = 304
        Top = 240
        Width = 249
        Height = 17
        Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1091#1088#1086#1074#1085#1103' '#1079#1072#1087#1091#1089#1082#1072
        TabOrder = 6
      end
      object GroupBox4: TGroupBox
        Left = 304
        Top = 72
        Width = 185
        Height = 89
        Caption = 'AC/DC '#1088#1077#1078#1080#1084
        TabOrder = 7
        object CheckBox5: TCheckBox
          Left = 16
          Top = 24
          Width = 145
          Height = 17
          Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' AC '#1088#1077#1078#1080#1084
          TabOrder = 0
        end
        object CheckBox6: TCheckBox
          Left = 16
          Top = 56
          Width = 137
          Height = 17
          Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' DC '#1088#1077#1078#1080#1084
          TabOrder = 1
        end
      end
      object GroupBox5: TGroupBox
        Left = 576
        Top = 72
        Width = 249
        Height = 89
        Caption = #1058#1080#1087' '#1092#1088#1086#1085#1090#1072
        TabOrder = 8
        object CheckBox7: TCheckBox
          Left = 16
          Top = 24
          Width = 209
          Height = 17
          Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1099#1081' '#1092#1088#1086#1085#1090
          TabOrder = 0
        end
        object CheckBox8: TCheckBox
          Left = 16
          Top = 56
          Width = 209
          Height = 17
          Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1086#1090#1088#1080#1094#1072#1090#1077#1083#1100#1085#1099#1081' '#1092#1088#1086#1085#1090
          TabOrder = 1
        end
      end
      object MeasTypeCB: TComboBox
        Left = 304
        Top = 32
        Width = 273
        Height = 21
        ItemHeight = 0
        TabOrder = 9
      end
      object GroupBox6: TGroupBox
        Left = 296
        Top = 328
        Width = 537
        Height = 377
        Caption = #1048#1085#1090#1077#1088#1092#1077#1081#1089' '#1087#1086#1076#1082#1083#1102#1095#1077#1085#1080#1103
        TabOrder = 10
        object InterfaceMulCB: TComboBox
          Left = 16
          Top = 24
          Width = 281
          Height = 21
          ItemHeight = 0
          TabOrder = 0
        end
      end
    end
  end
  object Button10: TButton
    Left = 1168
    Top = 752
    Width = 75
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 1
    OnClick = Button10Click
  end
  object CheckListBox1: TCheckListBox
    Left = 0
    Top = 24
    Width = 233
    Height = 657
    ItemHeight = 13
    TabOrder = 2
  end
  object Button2: TButton
    Left = 136
    Top = 720
    Width = 97
    Height = 25
    Caption = #1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1072#1090#1100
    TabOrder = 3
  end
  object Button3: TButton
    Left = 136
    Top = 688
    Width = 97
    Height = 25
    Caption = #1057#1086#1079#1076#1072#1090#1100
    TabOrder = 4
  end
  object Button4: TButton
    Left = 0
    Top = 688
    Width = 97
    Height = 25
    Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
    TabOrder = 5
  end
end
