object ModifiDataTableF: TModifiDataTableF
  Left = 443
  Top = 404
  BiDiMode = bdRightToLeft
  BorderStyle = bsDialog
  Caption = #1048#1079#1084#1077#1085#1077#1085#1080#1077' '#1076#1072#1085#1085#1099#1093' '#1074' '#1090#1072#1073#1083#1080#1094#1077
  ClientHeight = 132
  ClientWidth = 649
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 61
    Width = 16
    Height = 13
    Caption = 'Z ='
  end
  object Label2: TLabel
    Left = 48
    Top = 16
    Width = 559
    Height = 13
    Caption = 
      'z - '#1079#1085#1072#1095#1077#1085#1080#1077' '#1090#1077#1082#1091#1097#1077#1081' '#1103#1095#1077#1081#1082#1080', x - '#1087#1072#1088#1072#1084#1077#1090#1088' '#1090#1077#1082#1091#1097#1077#1081' '#1103#1095#1077#1081#1082#1080' '#1087#1086' '#1089#1090#1086#1073 +
      #1094#1091', y - '#1087#1072#1088#1072#1084#1077#1090#1088' '#1090#1077#1082#1091#1097#1077#1081' '#1103#1095#1077#1081#1082#1080' '#1087#1086' '#1089#1090#1088#1086#1082#1077'.'
  end
  object Edit: TEdit
    Left = 40
    Top = 56
    Width = 593
    Height = 21
    TabOrder = 0
  end
  object OKButton: TButton
    Left = 472
    Top = 96
    Width = 75
    Height = 25
    Caption = #1054#1050
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = OKButtonClick
  end
  object CancelButton: TButton
    Left = 560
    Top = 96
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
end
