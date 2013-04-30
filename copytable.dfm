object CopyTableForm: TCopyTableForm
  Left = 616
  Top = 214
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077' '#1090#1072#1073#1083#1080#1094#1099
  ClientHeight = 172
  ClientWidth = 422
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel: TPanel
    Left = 0
    Top = 0
    Width = 422
    Height = 172
    Align = alClient
    BevelOuter = bvLowered
    Caption = 'Panel'
    TabOrder = 0
    DesignSize = (
      422
      172)
    object NameSoursLabel: TLabel
      Left = 8
      Top = 8
      Width = 57
      Height = 13
      Caption = #1048#1089#1090#1086#1095#1085#1080#1082' - '
    end
    object CopyTableButton: TButton
      Left = 248
      Top = 138
      Width = 75
      Height = 25
      Anchors = []
      BiDiMode = bdLeftToRight
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      ParentBiDiMode = False
      TabOrder = 0
      OnClick = CopyTableButtonClick
    end
    object Memo1: TMemo
      Left = 8
      Top = 29
      Width = 409
      Height = 20
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      Color = clBtnFace
      Lines.Strings = (
        #1042#1099#1073#1077#1088#1080#1090#1077' '#1090#1072#1073#1083#1080#1094#1091', '#1074' '#1082#1086#1090#1086#1088#1091#1102' '#1089#1083#1077#1076#1091#1077#1090' '#1089#1082#1086#1087#1080#1088#1086#1074#1072#1090#1100' '#1076#1072#1085#1085#1099#1077'.')
      TabOrder = 1
    end
    object CloseFormButton: TButton
      Left = 344
      Top = 138
      Width = 75
      Height = 25
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 2
      OnClick = CloseFormButtonClick
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 49
      Width = 420
      Height = 76
      Caption = #1055#1088#1080#1077#1084#1085#1080#1082
      TabOrder = 3
      object CopyCheckBox1: TCheckBox
        Left = 8
        Top = 16
        Width = 409
        Height = 17
        Caption = #1055#1088#1080#1077#1084#1085#1080#1082'1'
        TabOrder = 0
        OnClick = CopyCheckBox1Click
      end
      object CopyCheckBox2: TCheckBox
        Left = 8
        Top = 48
        Width = 409
        Height = 17
        Caption = #1055#1088#1080#1077#1084#1085#1080#1082'2'
        TabOrder = 1
        OnClick = CopyCheckBox2Click
      end
    end
  end
  object Timer1: TTimer
    Interval = 10
    Left = 384
    Top = 8
  end
end
