object ManagerDGIF: TManagerDGIF
  Left = 393
  Top = 222
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Manager channel'
  ClientHeight = 547
  ClientWidth = 760
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 632
    Top = 8
    Width = 100
    Height = 13
    Caption = #1053#1072' '#1074#1099#1093#1086#1076#1077' '#1092#1080#1083#1100#1090#1088#1072
  end
  object Label5: TLabel
    Left = 504
    Top = 8
    Width = 100
    Height = 13
    Caption = #1042#1099#1093#1086#1076#1085#1072#1103' '#1074#1077#1083#1080#1095#1080#1085#1072
  end
  object OnVisibleChannel1B: TButton
    Left = 416
    Top = 24
    Width = 75
    Height = 25
    Caption = #1050#1072#1085#1072#1083' 1'
    TabOrder = 0
    OnClick = OnVisibleChannel1BClick
  end
  object OnVisibleChannel2B: TButton
    Left = 416
    Top = 48
    Width = 75
    Height = 25
    Caption = #1050#1072#1085#1072#1083' 2'
    TabOrder = 1
    OnClick = OnVisibleChannel2BClick
  end
  object OnVisibleChannel3B: TButton
    Left = 416
    Top = 72
    Width = 75
    Height = 25
    Caption = #1050#1072#1085#1072#1083' 3'
    TabOrder = 2
    OnClick = OnVisibleChannel3BClick
  end
  object OnVisibleChannel4B: TButton
    Left = 416
    Top = 96
    Width = 75
    Height = 25
    Caption = #1050#1072#1085#1072#1083' 4'
    TabOrder = 3
    OnClick = OnVisibleChannel4BClick
  end
  object OnVisibleChannel5B: TButton
    Left = 416
    Top = 120
    Width = 75
    Height = 25
    Caption = #1050#1072#1085#1072#1083' 5'
    TabOrder = 4
    OnClick = OnVisibleChannel5BClick
  end
  object OnVisibleChannel6B: TButton
    Left = 416
    Top = 144
    Width = 75
    Height = 25
    Caption = #1050#1072#1085#1072#1083' 6'
    TabOrder = 5
    OnClick = OnVisibleChannel6BClick
  end
  object OnChannel1CB: TCheckBox
    Left = 8
    Top = 32
    Width = 65
    Height = 17
    Caption = #1050#1072#1085#1072#1083' 1'
    TabOrder = 6
    OnClick = OnChannel1CBClick
  end
  object OnChannel2CB: TCheckBox
    Left = 8
    Top = 56
    Width = 65
    Height = 17
    Caption = #1050#1072#1085#1072#1083' 2'
    TabOrder = 7
    OnClick = OnChannel2CBClick
  end
  object OnChannel3CB: TCheckBox
    Left = 8
    Top = 80
    Width = 65
    Height = 17
    Caption = #1050#1072#1085#1072#1083' 3'
    TabOrder = 8
    OnClick = OnChannel3CBClick
  end
  object OnChannel4CB: TCheckBox
    Left = 8
    Top = 104
    Width = 65
    Height = 17
    Caption = #1050#1072#1085#1072#1083' 4'
    TabOrder = 9
    OnClick = OnChannel4CBClick
  end
  object OnChannel5CB: TCheckBox
    Left = 8
    Top = 128
    Width = 65
    Height = 17
    Caption = #1050#1072#1085#1072#1083' 5'
    TabOrder = 10
    OnClick = OnChannel5CBClick
  end
  object OnChannel6CB: TCheckBox
    Left = 8
    Top = 152
    Width = 73
    Height = 17
    Caption = #1050#1072#1085#1072#1083' 6'
    TabOrder = 11
    OnClick = OnChannel6CBClick
  end
  object LogMemo: TMemo
    Left = 0
    Top = 458
    Width = 760
    Height = 89
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 12
  end
  object SingleModeProgramCB: TCheckBox
    Left = 8
    Top = 432
    Width = 145
    Height = 17
    Caption = #1054#1076#1085#1086#1082#1072#1085#1072#1083#1100#1085#1099#1081' '#1088#1077#1078#1080#1084
    TabOrder = 13
    OnClick = SingleModeProgramCBClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 192
    Width = 745
    Height = 113
    Caption = #1056#1077#1078#1080#1084' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
    TabOrder = 14
    object ModePhaseVoltageType1RB: TRadioButton
      Left = 8
      Top = 40
      Width = 321
      Height = 17
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1092#1072#1079#1099' '#1074' '#1088#1077#1078#1080#1084#1077' '#1085#1072#1087#1088#1103#1078#1077#1085#1080#1103' ('#1087#1077#1088#1074#1099#1081' '#1101#1090#1072#1087')'
      TabOrder = 0
      OnClick = ModePhaseVoltageType1RBClick
    end
    object ModePhaseVoltageType2RB: TRadioButton
      Left = 8
      Top = 64
      Width = 337
      Height = 17
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1092#1072#1079#1099' '#1074' '#1088#1077#1078#1080#1084#1077' '#1085#1072#1087#1088#1103#1078#1077#1085#1080#1103' ('#1074#1090#1086#1088#1086#1081' '#1101#1090#1072#1087')'
      TabOrder = 1
      OnClick = ModePhaseVoltageType2RBClick
    end
    object ModePhaseCurrentRB: TRadioButton
      Left = 8
      Top = 88
      Width = 273
      Height = 17
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1092#1072#1079#1099' '#1074' '#1088#1077#1078#1080#1084#1077' '#1090#1086#1082#1072
      TabOrder = 2
      OnClick = ModePhaseCurrentRBClick
    end
    object ModeCurrentRB: TRadioButton
      Left = 8
      Top = 16
      Width = 297
      Height = 17
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1090#1086#1082#1072
      TabOrder = 3
      OnClick = ModeCurrentRBClick
    end
  end
  object Panel1: TPanel
    Left = 80
    Top = 0
    Width = 105
    Height = 177
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 15
    object Label1: TLabel
      Left = 10
      Top = 8
      Width = 79
      Height = 13
      Caption = #1054#1087#1086#1088#1085#1099#1081' '#1082#1072#1085#1072#1083
    end
    object RefChannel1RB: TRadioButton
      Left = 48
      Top = 32
      Width = 17
      Height = 17
      TabOrder = 0
      OnClick = RefChannel1RBClick
    end
    object RefChannel2RB: TRadioButton
      Left = 48
      Top = 56
      Width = 17
      Height = 17
      TabOrder = 1
      OnClick = RefChannel2RBClick
    end
    object RefChannel3RB: TRadioButton
      Left = 48
      Top = 80
      Width = 17
      Height = 17
      TabOrder = 2
      OnClick = RefChannel3RBClick
    end
    object RefChannel4RB: TRadioButton
      Left = 48
      Top = 104
      Width = 17
      Height = 17
      TabOrder = 3
      OnClick = RefChannel4RBClick
    end
    object RefChannel5RB: TRadioButton
      Left = 48
      Top = 128
      Width = 17
      Height = 17
      TabOrder = 4
      OnClick = RefChannel5RBClick
    end
    object RefChannel6RB: TRadioButton
      Left = 48
      Top = 152
      Width = 17
      Height = 17
      TabOrder = 5
      OnClick = RefChannel6RBClick
    end
  end
  object Panel2: TPanel
    Left = 192
    Top = 0
    Width = 105
    Height = 177
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 16
    object Label2: TLabel
      Left = 4
      Top = 8
      Width = 93
      Height = 13
      Caption = #1042#1089#1087#1086#1084#1086#1075#1072#1090#1077#1083#1100#1085#1099#1081
    end
    object SubsidiaryChannel1RB: TRadioButton
      Left = 48
      Top = 32
      Width = 17
      Height = 17
      Caption = 'SubsidiaryChannel1RB'
      TabOrder = 0
    end
    object SubsidiaryChannel2RB: TRadioButton
      Left = 48
      Top = 56
      Width = 17
      Height = 17
      TabOrder = 1
    end
    object SubsidiaryChannel3RB: TRadioButton
      Left = 48
      Top = 80
      Width = 17
      Height = 17
      TabOrder = 2
    end
    object SubsidiaryChannel4RB: TRadioButton
      Left = 48
      Top = 104
      Width = 17
      Height = 17
      TabOrder = 3
    end
    object SubsidiaryChannel5RB: TRadioButton
      Left = 48
      Top = 128
      Width = 17
      Height = 17
      TabOrder = 4
    end
    object SubsidiaryChannel6RB: TRadioButton
      Left = 48
      Top = 152
      Width = 17
      Height = 17
      TabOrder = 5
    end
  end
  object Panel3: TPanel
    Left = 304
    Top = 0
    Width = 105
    Height = 177
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 17
    object Label3: TLabel
      Left = 11
      Top = 8
      Width = 70
      Height = 13
      Caption = #1050#1072#1083#1080#1073#1088#1091#1077#1084#1099#1081
    end
    object CalibrChannel4RB: TRadioButton
      Left = 48
      Top = 104
      Width = 17
      Height = 17
      TabOrder = 0
    end
    object CalibrChannel1RB: TRadioButton
      Left = 48
      Top = 32
      Width = 17
      Height = 17
      TabOrder = 1
    end
    object CalibrChannel2RB: TRadioButton
      Left = 48
      Top = 56
      Width = 17
      Height = 17
      TabOrder = 2
    end
    object CalibrChannel3RB: TRadioButton
      Left = 48
      Top = 80
      Width = 17
      Height = 17
      TabOrder = 3
    end
    object CalibrChannel5RB: TRadioButton
      Left = 48
      Top = 128
      Width = 17
      Height = 17
      TabOrder = 4
    end
    object CalibrChannel6RB: TRadioButton
      Left = 48
      Top = 152
      Width = 17
      Height = 17
      TabOrder = 5
    end
  end
  object ConstTimerFilterLE: TLabeledEdit
    Left = 8
    Top = 392
    Width = 137
    Height = 21
    EditLabel.Width = 132
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1086#1089#1090#1086#1103#1085#1085#1072#1103' '#1074#1088#1077#1084#1077#1085#1080', c'#1077#1082
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 18
    OnExit = ConstTimerFilterLEExit
    OnKeyPress = ConstTimerFilterLEKeyPress
  end
  object FilterOnCB: TCheckBox
    Left = 8
    Top = 328
    Width = 97
    Height = 17
    Caption = #1092#1080#1083#1100#1090#1088' '#1092#1072#1079#1099
    TabOrder = 19
  end
  object ValueOutFilterEdit1: TEdit
    Left = 632
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 20
  end
  object ValueOutFilterEdit2: TEdit
    Left = 632
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 21
  end
  object ValueOutFilterEdit3: TEdit
    Left = 632
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 22
  end
  object ValueOutFilterEdit4: TEdit
    Left = 632
    Top = 96
    Width = 121
    Height = 21
    TabOrder = 23
  end
  object ValueOutFilterEdit5: TEdit
    Left = 632
    Top = 120
    Width = 121
    Height = 21
    TabOrder = 24
  end
  object ValueOutFilterEdit6: TEdit
    Left = 632
    Top = 144
    Width = 121
    Height = 21
    TabOrder = 25
  end
  object ValueOutEdit1: TEdit
    Left = 504
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 26
  end
  object ValueOutEdit2: TEdit
    Left = 504
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 27
  end
  object ValueOutEdit3: TEdit
    Left = 504
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 28
  end
  object ValueOutEdit4: TEdit
    Left = 504
    Top = 96
    Width = 121
    Height = 21
    TabOrder = 29
  end
  object ValueOutEdit5: TEdit
    Left = 504
    Top = 120
    Width = 121
    Height = 21
    TabOrder = 30
  end
  object ValueOutEdit6: TEdit
    Left = 504
    Top = 144
    Width = 121
    Height = 21
    TabOrder = 31
  end
  object CheckBoxPhasaNorm180: TCheckBox
    Left = 8
    Top = 352
    Width = 169
    Height = 17
    Caption = #1053#1086#1088#1084#1072#1083#1080#1079#1072#1094#1080#1103' '#1092#1072#1079#1099' 180'
    TabOrder = 32
    OnClick = CheckBoxPhasaNorm180Click
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
    Left = 568
    Top = 384
  end
  object OnChangeVisibleFormTimer: TTimer
    Interval = 10
    OnTimer = OnChangeVisibleFormTimerTimer
    Left = 600
    Top = 384
  end
end
