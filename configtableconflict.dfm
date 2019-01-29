object ConfigTableConflictF: TConfigTableConflictF
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1050#1086#1085#1092#1083#1080#1082#1090' '#1090#1072#1073#1083#1080#1094
  ClientHeight = 179
  ClientWidth = 310
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object DescriptionLabel: TLabel
    Left = 8
    Top = 8
    Width = 297
    Height = 36
    AutoSize = False
    Caption = 
      #1047#1072#1075#1086#1083#1086#1074#1082#1080' '#1086#1090#1082#1088#1099#1074#1072#1077#1084#1086#1081' '#1090#1072#1073#1083#1080#1094#1099' '#1085#1077' '#1089#1086#1074#1087#1072#1076#1072#1102#1090' '#1089' '#1079#1072#1075#1086#1083#1086#1074#1082#1072#1084#1080' '#1090#1072#1073#1083#1080#1094#1099 +
      ' '#1074' '#1085#1072#1089#1090#1088#1086#1081#1082#1072#1093'. '#1042#1099#1073#1077#1088#1080#1090#1077' '#1076#1077#1081#1089#1090#1074#1080#1077':'
    WordWrap = True
  end
  object OkButton: TButton
    Left = 149
    Top = 146
    Width = 75
    Height = 25
    Caption = #1054#1050
    ModalResult = 1
    TabOrder = 3
  end
  object CancelButton: TButton
    Left = 230
    Top = 146
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    Default = True
    ModalResult = 2
    TabOrder = 4
  end
  object TableToConfigRadioButton: TRadioButton
    Left = 8
    Top = 50
    Width = 297
    Height = 17
    Caption = #1055#1088#1080#1085#1103#1090#1100' '#1079#1072#1075#1086#1083#1086#1074#1082#1080' '#1086#1090#1082#1088#1099#1074#1072#1077#1084#1086#1081' '#1090#1072#1073#1083#1080#1094#1099
    Checked = True
    TabOrder = 0
    TabStop = True
  end
  object TableFromConfigRadioButton: TRadioButton
    Left = 8
    Top = 73
    Width = 297
    Height = 17
    Caption = #1047#1072#1084#1077#1085#1080#1090#1100' '#1079#1072#1075#1086#1083#1086#1074#1082#1080' '#1086#1090#1082#1088#1099#1074#1072#1077#1084#1086#1081' '#1090#1072#1073#1083#1080#1094#1099
    TabOrder = 1
  end
  object ConfigReadOnlyRadioButton: TRadioButton
    Left = 8
    Top = 96
    Width = 297
    Height = 17
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1073#1077#1079' '#1074#1086#1079#1084#1086#1078#1085#1086#1089#1090#1080' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103' '#1085#1072#1089#1090#1088#1086#1077#1082
    TabOrder = 2
  end
end
