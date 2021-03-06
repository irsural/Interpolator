object OptionsF: TOptionsF
  Left = 4
  Top = 336
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1054#1087#1090#1080#1084#1080#1079#1072#1094#1080#1103' '#1076#1072#1085#1085#1099#1093
  ClientHeight = 505
  ClientWidth = 743
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object OptionsTreeView: TTreeView
    Left = 0
    Top = 0
    Width = 177
    Height = 471
    Align = alLeft
    BevelInner = bvNone
    Indent = 19
    TabOrder = 0
    OnChange = OptionsTreeViewChange
    Items.Data = {
      03000000280000000000000000000000FFFFFFFFFFFFFFFF0000000000000000
      0FCEEFF2E8ECE8E7E0F6E8FF20CCCDCA220000000000000001000000FFFFFFFF
      FFFFFFFF000000000000000009CAEEF0F0E5EAF6E8FF2D000000000000000200
      0000FFFFFFFFFFFFFFFF000000000000000014D0E0F1F7E5F220EAEEFDF4F4E8
      F6E8E5EDF2EEE2}
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 471
    Width = 743
    Height = 34
    Align = alBottom
    TabOrder = 1
    object ApplyButton: TButton
      Left = 571
      Top = 5
      Width = 75
      Height = 25
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
      TabOrder = 0
      OnClick = ApplyButtonClick
    end
    object CloseFormButton: TButton
      Left = 660
      Top = 5
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 1
      OnClick = CloseFormButtonClick
    end
  end
  object PageControlPanel: TPanel
    Left = 177
    Top = 0
    Width = 566
    Height = 471
    Align = alClient
    BevelOuter = bvNone
    Caption = 'PageControlPanel'
    TabOrder = 2
    object OptimizeMNKOptionsPanel: TPanel
      Left = 0
      Top = 0
      Width = 566
      Height = 471
      Align = alClient
      TabOrder = 1
      object GroupBox1: TGroupBox
        Left = 9
        Top = 49
        Width = 550
        Height = 248
        Caption = 
          #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1074#1099#1074#1086#1076#1072' '#1085#1072' '#1101#1082#1088#1072#1085' '#1080' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080' '#1076#1072 +
          #1085#1085#1099#1093
        TabOrder = 0
        object OptDispOutMNKCheckBox1: TCheckBox
          Left = 8
          Top = 24
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1080#1089#1093#1086#1076#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
          TabOrder = 0
        end
        object OptDispOutMNKCheckBox2: TCheckBox
          Left = 8
          Top = 56
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1086#1087#1090#1080#1084#1080#1079#1080#1088#1086#1074#1072#1085#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
          TabOrder = 1
        end
        object OptDispOutMNKCheckBox3: TCheckBox
          Left = 8
          Top = 88
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1076#1072#1085#1085#1099#1093' '#1089' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1086#1081' '#1082#1086#1088#1088#1077#1082#1094#1080#1077#1081
          TabOrder = 2
        end
        object OptSveFileMNKCheckBox: TCheckBox
          Left = 8
          Top = 120
          Width = 470
          Height = 17
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
          TabOrder = 3
        end
        object DirNameMNKLabeledEdit: TLabeledEdit
          Left = 24
          Top = 160
          Width = 425
          Height = 21
          EditLabel.Width = 240
          EditLabel.Height = 13
          EditLabel.Caption = #1058#1077#1082#1091#1097#1072#1103' '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1092#1072#1081#1083#1072
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 4
        end
        object OpenDirMNKButton: TButton
          Left = 464
          Top = 152
          Width = 75
          Height = 25
          Caption = #1054#1073#1079#1086#1088
          TabOrder = 5
          OnClick = OpenDirMNKButtonClick
        end
        object FileNameMNKLabeledEdit: TLabeledEdit
          Left = 24
          Top = 208
          Width = 425
          Height = 21
          EditLabel.Width = 67
          EditLabel.Height = 13
          EditLabel.Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 6
        end
      end
      object Panel1: TPanel
        Left = 9
        Top = 9
        Width = 550
        Height = 32
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #1054#1087#1090#1080#1084#1080#1079#1072#1094#1080#1103' '#1052#1053#1050
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
    end
    object CorrectOptionsPanel: TPanel
      Left = 0
      Top = 0
      Width = 566
      Height = 471
      Align = alClient
      TabOrder = 0
      object OptionsDysplayOutGB: TGroupBox
        Left = 9
        Top = 209
        Width = 550
        Height = 248
        Caption = 
          #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1074#1099#1074#1086#1076#1072' '#1085#1072' '#1101#1082#1088#1072#1085' '#1080' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080' '#1076#1072 +
          #1085#1085#1099#1093
        TabOrder = 0
        object OptDispOutCorCheckBox1: TCheckBox
          Left = 8
          Top = 24
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1080#1089#1093#1086#1076#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
          TabOrder = 0
        end
        object OptDispOutCorCheckBox2: TCheckBox
          Left = 8
          Top = 56
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1086#1087#1090#1080#1084#1080#1079#1080#1088#1086#1074#1072#1085#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
          TabOrder = 1
        end
        object OptDispOutCorCheckBox3: TCheckBox
          Left = 8
          Top = 88
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1076#1072#1085#1085#1099#1093' '#1089' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1086#1081' '#1082#1086#1088#1088#1077#1082#1094#1080#1077#1081
          TabOrder = 2
        end
        object OptSveFileCorCheckBox: TCheckBox
          Left = 8
          Top = 120
          Width = 470
          Height = 17
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
          TabOrder = 3
        end
        object DirNameCorLabeledEdit: TLabeledEdit
          Left = 24
          Top = 160
          Width = 425
          Height = 21
          EditLabel.Width = 240
          EditLabel.Height = 13
          EditLabel.Caption = #1058#1077#1082#1091#1097#1072#1103' '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1092#1072#1081#1083#1072
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 4
        end
        object OpenDirCorButton: TButton
          Left = 464
          Top = 160
          Width = 75
          Height = 25
          Caption = #1054#1073#1079#1086#1088
          TabOrder = 5
          OnClick = OpenDirCorButtonClick
        end
        object FileNameCorLabeledEdit: TLabeledEdit
          Left = 24
          Top = 208
          Width = 425
          Height = 21
          EditLabel.Width = 67
          EditLabel.Height = 13
          EditLabel.Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 6
        end
      end
      object CorrectGroupBox: TGroupBox
        Left = 9
        Top = 49
        Width = 550
        Height = 153
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1082#1086#1088#1088#1077#1082#1094#1080#1080
        TabOrder = 1
        object CorrectXLabeledEdit: TLabeledEdit
          Left = 48
          Top = 36
          Width = 470
          Height = 21
          EditLabel.Width = 77
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1086#1088#1088#1077#1082#1094#1080#1103' X'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 0
        end
        object CorrectYLabeledEdit: TLabeledEdit
          Left = 48
          Top = 76
          Width = 470
          Height = 21
          EditLabel.Width = 77
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1086#1088#1088#1077#1082#1094#1080#1103' Y'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 1
        end
        object CorrectZLabeledEdit: TLabeledEdit
          Left = 48
          Top = 116
          Width = 470
          Height = 21
          EditLabel.Width = 77
          EditLabel.Height = 13
          EditLabel.Caption = #1050#1086#1088#1088#1077#1082#1094#1080#1103' Z'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
        end
        object EnabledCorrectXCheckBox: TCheckBox
          Left = 8
          Top = 40
          Width = 41
          Height = 17
          Caption = 'X ='
          TabOrder = 3
        end
        object EnabledCorrectYCheckBox: TCheckBox
          Left = 8
          Top = 80
          Width = 41
          Height = 17
          Caption = 'Y ='
          TabOrder = 4
        end
        object EnabledCorrectZCheckBox: TCheckBox
          Left = 8
          Top = 120
          Width = 41
          Height = 17
          Caption = 'Z ='
          TabOrder = 5
        end
      end
      object NameSelectOptiomsPanel: TPanel
        Left = 9
        Top = 9
        Width = 550
        Height = 32
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #1050#1086#1088#1088#1077#1082#1094#1080#1103
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
      end
    end
    object CalculatingCoefOptionsPanel: TPanel
      Left = 0
      Top = 0
      Width = 566
      Height = 471
      Align = alClient
      TabOrder = 2
      object Panel2: TPanel
        Left = 9
        Top = 9
        Width = 550
        Height = 32
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #1056#1072#1089#1095#1077#1090' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1074
        Color = clLime
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object GroupBox2: TGroupBox
        Left = 9
        Top = 49
        Width = 550
        Height = 248
        Caption = 
          #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1074#1099#1074#1086#1076#1072' '#1085#1072' '#1101#1082#1088#1072#1085' '#1080' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080' '#1076#1072 +
          #1085#1085#1099#1093
        TabOrder = 1
        object OptDispOutCoefCheckBox1: TCheckBox
          Left = 8
          Top = 24
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1080#1089#1093#1086#1076#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
          TabOrder = 0
        end
        object OptDispOutCoefCheckBox2: TCheckBox
          Left = 8
          Top = 56
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1086#1087#1090#1080#1084#1080#1079#1080#1088#1086#1074#1072#1085#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
          TabOrder = 1
        end
        object OptDispOutCoefCheckBox3: TCheckBox
          Left = 8
          Top = 88
          Width = 470
          Height = 17
          Caption = #1042#1099#1074#1077#1089#1090#1080' '#1074' '#1090#1072#1073#1083#1080#1094#1091' '#1076#1072#1085#1085#1099#1093' '#1089' '#1076#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1086#1081' '#1082#1086#1088#1088#1077#1082#1094#1080#1077#1081
          TabOrder = 2
        end
        object OptSveFileCoefCheckBox: TCheckBox
          Left = 8
          Top = 120
          Width = 470
          Height = 17
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
          TabOrder = 3
        end
        object DirNameCoefLabeledEdit: TLabeledEdit
          Left = 24
          Top = 160
          Width = 425
          Height = 21
          EditLabel.Width = 240
          EditLabel.Height = 13
          EditLabel.Caption = #1058#1077#1082#1091#1097#1072#1103' '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1092#1072#1081#1083#1072
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 4
        end
        object OpenDirCoefButton: TButton
          Left = 464
          Top = 160
          Width = 75
          Height = 25
          Caption = #1054#1073#1079#1086#1088
          TabOrder = 5
          OnClick = OpenDirCorButtonClick
        end
        object FileNameCoefLabeledEdit: TLabeledEdit
          Left = 24
          Top = 208
          Width = 425
          Height = 21
          EditLabel.Width = 67
          EditLabel.Height = 13
          EditLabel.Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 6
        end
      end
    end
  end
end
