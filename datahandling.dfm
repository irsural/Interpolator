object DataHandlingF: TDataHandlingF
  Left = 392
  Top = 201
  Width = 815
  Height = 543
  Caption = 'DataHandlingF'
  Color = clWindow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object TableValuePanel: TPanel
    Left = 249
    Top = 30
    Width = 558
    Height = 418
    Align = alClient
    BevelOuter = bvLowered
    Constraints.MinWidth = 550
    TabOrder = 0
    object LogMemo: TMemo
      Left = 1
      Top = 267
      Width = 556
      Height = 150
      Align = alBottom
      Constraints.MaxHeight = 150
      Constraints.MinHeight = 130
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object RawDataStringGrid: TStringGrid
      Left = 1
      Top = 105
      Width = 556
      Height = 162
      Align = alClient
      Constraints.MinHeight = 150
      Constraints.MinWidth = 150
      FixedCols = 0
      FixedRows = 0
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      ParentFont = False
      TabOrder = 1
      OnDrawCell = RawDataStringGridDrawCell
      OnGetEditText = RawDataStringGridGetEditText
      OnKeyDown = RawDataStringGridKeyDown
      OnSelectCell = RawDataStringGridSelectCell
      ColWidths = (
        64
        64
        64
        64
        64)
      RowHeights = (
        24
        24
        24
        24
        24)
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 556
      Height = 104
      Align = alTop
      TabOrder = 2
      OnResize = Panel1Resize
      object LeftPanel: TPanel
        Left = 1
        Top = 1
        Width = 358
        Height = 102
        Align = alLeft
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 0
        DesignSize = (
          358
          102)
        object ConfigCB: TComboBox
          Left = 8
          Top = 36
          Width = 338
          Height = 21
          Style = csDropDownList
          Anchors = [akLeft, akRight]
          ItemHeight = 13
          TabOrder = 0
          OnChange = ConfigCBChange
        end
        object EditConfigButton: TButton
          Left = 269
          Top = 72
          Width = 75
          Height = 25
          Anchors = [akRight]
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 1
          OnClick = EditConfigButtonClick
        end
        object Panel3: TPanel
          Left = 8
          Top = 11
          Width = 338
          Height = 17
          Anchors = [akLeft, akRight]
          BevelOuter = bvLowered
          Caption = #1058#1077#1082#1091#1097#1072#1103' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1103
          TabOrder = 2
        end
        object CreateConfigButton: TButton
          Left = 189
          Top = 72
          Width = 75
          Height = 25
          Anchors = [akRight]
          Caption = #1057#1086#1079#1076#1072#1090#1100
          TabOrder = 3
          OnClick = CreateConfigButtonClick
        end
      end
      object RightPanel: TPanel
        Left = 359
        Top = 1
        Width = 196
        Height = 102
        Align = alClient
        Anchors = [akLeft, akRight, akBottom]
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 1
        DesignSize = (
          196
          102)
        object PatternOfMeasuringInstrumentCB: TComboBox
          Left = 8
          Top = 36
          Width = 173
          Height = 21
          Style = csDropDownList
          Anchors = [akLeft, akRight]
          ItemHeight = 13
          TabOrder = 0
          OnChange = PatternOfMeasuringInstrumentCBChange
        end
        object Panel5: TPanel
          Left = 8
          Top = 11
          Width = 171
          Height = 17
          Anchors = [akLeft, akRight]
          BevelOuter = bvLowered
          Caption = #1048#1079#1084#1077#1088#1080#1090#1077#1083#1100#1085#1086#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1086
          TabOrder = 1
        end
      end
    end
  end
  object OptionsGroupBox: TGroupBox
    Left = 0
    Top = 30
    Width = 249
    Height = 418
    Align = alLeft
    Caption = #1055#1072#1085#1077#1083#1100' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103
    Color = clBtnFace
    ParentColor = False
    TabOrder = 1
    object CurrentStatusLabeledEdit: TLabeledEdit
      Left = 6
      Top = 64
      Width = 235
      Height = 21
      AutoSelect = False
      Color = clScrollBar
      EditLabel.Width = 108
      EditLabel.Height = 13
      EditLabel.Caption = #1057#1074#1103#1079#1100' '#1089' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1086#1084
      LabelPosition = lpAbove
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 0
    end
    object ModeProgramCB: TCheckBox
      Left = 8
      Top = 24
      Width = 153
      Height = 17
      Caption = #1052#1085#1086#1075#1086#1082#1072#1085#1072#1083#1100#1085#1099#1081' '#1088#1077#1078#1080#1084
      TabOrder = 1
      OnClick = ModeProgramCBClick
    end
    object TimeMeasLE: TLabeledEdit
      Left = 8
      Top = 144
      Width = 233
      Height = 21
      Color = clScrollBar
      EditLabel.Width = 129
      EditLabel.Height = 13
      EditLabel.Caption = #1054#1073#1097#1077#1077' '#1074#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
    end
    object IntervalTimeMeasLE: TLabeledEdit
      Left = 8
      Top = 184
      Width = 233
      Height = 21
      Color = clScrollBar
      EditLabel.Width = 157
      EditLabel.Height = 13
      EditLabel.Caption = #1054#1089#1090#1072#1074#1096#1077#1077#1089#1103' '#1074#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
    end
    object WorkTimeDeviceLE: TLabeledEdit
      Left = 8
      Top = 104
      Width = 233
      Height = 21
      Color = clScrollBar
      EditLabel.Width = 150
      EditLabel.Height = 13
      EditLabel.Caption = #1042#1088#1077#1084#1103' '#1088#1072#1073#1086#1090#1099' '#1089' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1086#1084
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
    end
  end
  object ButtomPanel: TPanel
    Left = 0
    Top = 448
    Width = 807
    Height = 49
    Align = alBottom
    TabOrder = 2
    DesignSize = (
      807
      49)
    object CommentProgressL: TLabel
      Left = 8
      Top = 8
      Width = 85
      Height = 13
      Anchors = [akLeft, akBottom]
      Caption = 'CommentProgress'
    end
    object PercentProgressL: TLabel
      Left = 656
      Top = 24
      Width = 37
      Height = 13
      Anchors = [akRight, akBottom]
      Caption = 'Percent'
    end
    object CloseFormButton: TButton
      Left = 720
      Top = 15
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 0
      OnClick = CloseFormButtonClick
    end
    object ProgressBar1: TProgressBar
      Left = 8
      Top = 24
      Width = 641
      Height = 16
      Anchors = [akLeft, akRight, akBottom]
      Min = 0
      Max = 100
      TabOrder = 1
    end
  end
  object CoolBar1: TCoolBar
    Left = 0
    Top = 0
    Width = 807
    Height = 30
    AutoSize = True
    Bands = <
      item
        Control = ActionToolBar1
        ImageIndex = -1
        MinHeight = 26
        Width = 143
      end
      item
        Break = False
        Control = ActionToolBar3
        ImageIndex = -1
        MinHeight = 26
        Width = 103
      end
      item
        Break = False
        Control = ActionToolBar2
        ImageIndex = -1
        MinHeight = 26
        Width = 249
      end
      item
        Break = False
        Control = ActionToolBar4
        ImageIndex = -1
        Width = 302
      end>
    Color = clBtnFace
    Images = ImageList1
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    object ActionToolBar3: TActionToolBar
      Left = 154
      Top = 0
      Width = 90
      Height = 26
      ActionManager = ActionManager1
      Align = alClient
      AllowHiding = True
      Caption = 'ActionToolBar3'
      HorzSeparator = True
      Orientation = boLeftToRight
      PersistentHotKeys = False
      Spacing = 0
    end
    object ActionToolBar1: TActionToolBar
      Left = 9
      Top = 0
      Width = 130
      Height = 26
      ActionManager = ActionManager1
      AllowHiding = True
      Caption = 'ActionToolBar1'
      HorzSeparator = True
      Orientation = boLeftToRight
      PersistentHotKeys = False
      Spacing = 0
    end
    object ActionToolBar2: TActionToolBar
      Left = 259
      Top = 0
      Width = 236
      Height = 26
      ActionManager = ActionManager1
      AllowHiding = True
      Caption = 'ActionToolBar2'
      HorzSeparator = True
      Orientation = boLeftToRight
      PersistentHotKeys = False
      Spacing = 0
    end
    object ActionToolBar4: TActionToolBar
      Left = 510
      Top = 0
      Width = 289
      Height = 25
      ActionManager = ActionManager1
      AllowHiding = True
      Caption = 'ActionToolBar4'
      HorzSeparator = True
      Orientation = boLeftToRight
      PersistentHotKeys = False
      Spacing = 0
    end
  end
  object FormDataHandingTimer1: TTimer
    Interval = 10
    OnTimer = FormDataHandingTimer1Timer
    Left = 8
    Top = 344
  end
  object ActionManager1: TActionManager
    ActionBars = <
      item
        Items = <
          item
            Action = FileOpen
            ImageIndex = 0
            ShowCaption = False
            ShortCut = 16463
          end
          item
            Action = FileSave
            ImageIndex = 1
            ShowCaption = False
            ShortCut = 16467
          end
          item
            Action = FileSaveAs
            ImageIndex = 3
            ShowCaption = False
          end
          item
            Action = FileReOpen
            ImageIndex = 18
            ShowCaption = False
          end
          item
            Action = WriteDataAction
            ImageIndex = 22
            ShowCaption = False
          end>
        ActionBar = ActionToolBar1
      end
      item
        Items = <
          item
            Items = <
              item
                Action = FileOpen
                ImageIndex = 0
                ShortCut = 16463
              end
              item
                Action = FileReOpen
              end
              item
                Action = FileSave
                ImageIndex = 3
                ShortCut = 16467
              end
              item
                Action = FileSaveAs
                ImageIndex = 1
              end>
            Caption = #1060#1072#1081#1083
          end
          item
            Items = <
              item
                Action = CreateColAction
              end
              item
                Action = DeleteColAction
              end
              item
                Action = CreateRowAction
              end
              item
                Action = DeleteRowAction
              end
              item
                Action = AddGroupCellsAction
              end>
            Caption = #1055#1088#1072#1074#1082#1072
          end
          item
            Items = <
              item
                Action = StartAutoVoltMeasAction
              end
              item
                Action = StartAutoVoltMeasActiveCellsAction
              end
              item
                Action = StopVoltMeasAction
              end>
            Caption = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
          end>
      end
      item
      end
      item
        Items = <
          item
            Action = CreateColAction
            ImageIndex = 8
            ShowCaption = False
          end
          item
            Action = DeleteColAction
            ImageIndex = 6
            ShowCaption = False
          end
          item
            Action = CreateRowAction
            ImageIndex = 9
            ShowCaption = False
          end
          item
            Action = DeleteRowAction
            ImageIndex = 7
            ShowCaption = False
          end
          item
            Action = AddGroupCellsAction
            ImageIndex = 10
            ShowCaption = False
          end
          item
            Action = AddSubtableAction
            ImageIndex = 15
            ShowCaption = False
          end
          item
            Action = DelSubtableAction
            ImageIndex = 14
            ShowCaption = False
          end>
        ActionBar = ActionToolBar2
      end
      item
        Items = <
          item
            Action = StartAutoVoltMeasAction
            ImageIndex = 12
            ShowCaption = False
          end
          item
            Action = StartAutoVoltMeasActiveCellsAction
            ImageIndex = 16
            ShowCaption = False
          end
          item
            Action = StopVoltMeasAction
            ImageIndex = 11
            ShowCaption = False
          end>
        ActionBar = ActionToolBar3
      end
      item
        Items = <
          item
            Action = CorrectModeAction
            ImageIndex = 20
            ShowCaption = False
          end
          item
            Action = MismatchModeAction
            ImageIndex = 21
            ShowCaption = False
          end>
        ActionBar = ActionToolBar4
      end>
    Images = ImageList2
    Left = 40
    Top = 344
    object FileOpen: TFileOpen
      Category = #1060#1072#1081#1083
      Caption = '&'#1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1060#1072#1081#1083'...'
      Dialog.DefaultExt = 'dgi'
      Dialog.Filter = 'Digital interpolator (*.dgi)|*.dgi|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
      Dialog.FilterIndex = 0
      Hint = #1054#1090#1082#1088#1099#1090#1100'|'#1054#1090#1082#1088#1099#1090#1100' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1081' '#1092#1072#1081#1083
      ImageIndex = 0
      ShortCut = 16463
      OnAccept = FileOpenAccept
    end
    object FileReOpen: TAction
      Category = #1060#1072#1081#1083
      Caption = #1055#1077#1088#1077#1079#1072#1075#1088#1091#1079#1080#1090#1100' '#1060#1072#1081#1083
      Hint = #1055#1077#1088#1077#1079#1072#1075#1088#1091#1079#1080#1090#1100' '#1092#1072#1081#1083
      ImageIndex = 18
      OnExecute = FileReOpenExecute
    end
    object FileSave: TAction
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1092#1072#1081#1083
      ImageIndex = 1
      ShortCut = 16467
      OnExecute = FileSaveExecute
    end
    object FileSaveAs: TFileSaveAs
      Category = #1060#1072#1081#1083
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' &'#1050#1072#1082'...'
      Dialog.DefaultExt = 'dgi'
      Dialog.Filter = 'Digital interpolator (*.dgi)|*.dgi|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
      Dialog.FilterIndex = 0
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1072#1082'|'#1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1089#1091#1097#1077#1089#1090#1074#1091#1102#1097#1080#1081' '#1092#1072#1081#1083' '#1089' '#1085#1086#1074#1099#1084' '#1080#1084#1077#1085#1077#1084
      ImageIndex = 3
      BeforeExecute = FileSaveAsBeforeExecute
      OnAccept = FileSaveAsAccept
    end
    object CreateColAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1089#1090#1086#1083#1073#1077#1094
      Hint = #1057#1086#1079#1076#1072#1090#1100' '#1089#1090#1086#1083#1073#1077#1094' '#1074' '#1090#1072#1073#1083#1080#1094#1077
      ImageIndex = 8
      OnExecute = CreateColActionExecute
    end
    object DeleteColAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1086#1083#1073#1077#1094
      Hint = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1086#1083#1073#1077#1094' '#1074' '#1090#1072#1073#1083#1080#1094#1077
      ImageIndex = 6
      OnExecute = DeleteColActionExecute
    end
    object CreateRowAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1089#1090#1088#1086#1082#1091
      Hint = #1057#1086#1079#1076#1072#1090#1100' '#1089#1090#1088#1086#1082#1091' '#1074' '#1090#1072#1073#1083#1080#1094#1077
      ImageIndex = 9
      OnExecute = CreateRowActionExecute
    end
    object DeleteRowAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
      Hint = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1088#1086#1082#1091' '#1074' '#1090#1072#1073#1083#1080#1094#1077
      ImageIndex = 7
      OnExecute = DeleteRowActionExecute
    end
    object AddGroupCellsAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1075#1088#1091#1087#1087#1091' '#1103#1095#1077#1077#1082
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1075#1088#1091#1087#1087#1091' '#1089#1090#1088#1086#1083#1073#1094#1086#1074' '#1080'/'#1080#1083#1080' '#1089#1090#1088#1086#1082' '#1074' '#1090#1072#1073#1083#1080#1094#1091
      ImageIndex = 10
      OnExecute = AddGroupCellsActionExecute
    end
    object StartAutoVoltMeasAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1053#1072#1095#1072#1090#1100' '#1072#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1086#1077' '#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Hint = #1053#1072#1095#1072#1090#1100' '#1072#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      ImageIndex = 12
      OnExecute = StartAutoVoltMeasActionExecute
    end
    object StartAutoVoltMeasActiveCellsAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1053#1072#1095#1072#1090#1100'/'#1087#1088#1086#1076#1086#1083#1078#1080#1090#1100' '#1089' '#1090#1077#1082#1091#1097#1077#1081' '#1103#1095#1077#1081#1082#1080
      Hint = #1053#1072#1095#1072#1090#1100'/'#1087#1088#1086#1076#1086#1083#1078#1080#1090#1100' '#1089' '#1090#1077#1082#1091#1097#1077#1081' '#1103#1095#1077#1081#1082#1080
      ImageIndex = 16
      OnExecute = StartAutoVoltMeasActiveCellsActionExecute
    end
    object StopVoltMeasAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100
      Hint = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1072#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      ImageIndex = 11
      OnExecute = StopVoltMeasActionExecute
    end
    object OnCorrectAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = 'OnCorrectAction'
    end
    object OnMismathAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = 'OnMismathAction'
    end
    object SetJumpHorizontalDownAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1055#1086' '#1075#1086#1088#1080#1079#1086#1085#1090#1072#1083#1080' '#1074#1085#1080#1079
      GroupIndex = 100
      OnExecute = SetJumpHorizontalDownActionExecute
    end
    object SetJumpHorizontalUpAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1055#1086' '#1075#1086#1088#1080#1079#1086#1085#1090#1072#1083#1080' '#1074#1074#1077#1088#1093
      GroupIndex = 100
      OnExecute = SetJumpHorizontalUpActionExecute
    end
    object SetJumpVerticalForwardAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1055#1086' '#1074#1077#1088#1090#1080#1082#1072#1083#1080' '#1074#1087#1088#1072#1074#1086
      GroupIndex = 100
      OnExecute = SetJumpVerticalForwardActionExecute
    end
    object SetJumpVerticalBackAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1055#1086' '#1074#1077#1088#1090#1080#1082#1072#1083#1080' '#1074#1083#1077#1074#1086
      Checked = True
      GroupIndex = 100
      OnExecute = SetJumpVerticalBackActionExecute
    end
    object SetJumpSmoothAction: TAction
      Category = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      Caption = #1052#1103#1075#1082#1080#1081' '#1087#1077#1088#1077#1093#1086#1076
      Checked = True
      OnExecute = SetJumpSmoothActionExecute
    end
    object SetVoltDCMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1087#1086#1089#1090#1086#1103#1085#1085#1086#1075#1086' '#1085#1072#1087#1088#1103#1078#1077#1085#1080#1103
      Checked = True
      GroupIndex = 200
      OnExecute = SetVoltDCMeasActionExecute
    end
    object SetVoltACMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1075#1086' '#1085#1072#1087#1088#1103#1078#1077#1085#1080#1103
      GroupIndex = 200
      OnExecute = SetVoltACMeasActionExecute
    end
    object SetCurrentDCMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1087#1086#1089#1090#1086#1103#1085#1085#1086#1075#1086' '#1090#1086#1082#1072
      GroupIndex = 200
      OnExecute = SetCurrentDCMeasActionExecute
    end
    object SetResistance2xMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1089#1086#1087#1088#1086#1090#1080#1074#1083#1077#1085#1080#1103' '#1087#1086' 2-'#1093' '#1087#1088#1086#1074#1086#1076#1085#1086#1081' '#1089#1093#1077#1084#1077
      GroupIndex = 200
      OnExecute = SetResistance2xMeasActionExecute
    end
    object SetResistance4xMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1089#1086#1087#1088#1086#1090#1080#1074#1083#1077#1085#1080#1103' '#1087#1086' 4-'#1093' '#1087#1088#1086#1074#1086#1076#1085#1086#1081' '#1089#1093#1077#1084#1077
      GroupIndex = 200
      OnExecute = SetResistance4xMeasActionExecute
    end
    object SetCurrentACMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1075#1086' '#1090#1086#1082#1072
      GroupIndex = 200
      OnExecute = SetCurrentACMeasActionExecute
    end
    object SetFrequencyMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1095#1072#1089#1090#1086#1090#1099
      GroupIndex = 200
      OnExecute = SetFrequencyMeasActionExecute
    end
    object AddSubtableAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1086#1076#1090#1072#1073#1083#1080#1094#1091
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1086#1076#1090#1072#1073#1083#1080#1094#1091
      ImageIndex = 15
      OnExecute = AddSubtableActionExecute
    end
    object DelSubtableAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1087#1086#1076#1090#1072#1073#1083#1080#1094#1091
      Hint = #1059#1076#1072#1083#1080#1090#1100' '#1087#1086#1076#1090#1072#1073#1083#1080#1094#1091
      ImageIndex = 14
      OnExecute = DelSubtableActionExecute
    end
    object CorrectModeAction: TAction
      Category = #1054#1087#1094#1080#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
      Caption = #1056#1077#1078#1080#1084' '#1082#1086#1088#1088#1077#1082#1094#1080#1080
      Hint = #1056#1077#1078#1080#1084' '#1082#1086#1088#1088#1077#1082#1094#1080#1080'|'#1042#1082#1083#1102#1095#1080#1090#1100'|'#1074#1099#1082#1083#1102#1095#1080#1090#1100' '#1088#1077#1078#1080#1084' '#1082#1086#1088#1088#1077#1082#1094#1080#1080
      ImageIndex = 20
      OnExecute = CorrectModeActionExecute
    end
    object MismatchModeAction: TAction
      Category = #1054#1087#1094#1080#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
      Caption = #1056#1077#1078#1080#1084' '#1088#1072#1089#1089#1090#1088#1086#1081#1082#1080
      Hint = #1056#1077#1078#1080#1084' '#1088#1072#1089#1089#1090#1088#1086#1081#1082#1080'|'#1042#1082#1083#1102#1095#1080#1090#1100'/'#1074#1099#1082#1083#1102#1095#1080#1090#1100' '#1088#1077#1078#1080#1084' '#1088#1072#1089#1089#1090#1088#1086#1081#1082#1080
      ImageIndex = 21
      OnExecute = MismatchModeActionExecute
    end
    object WriteDataAction: TAction
      Category = #1060#1072#1081#1083
      Caption = #1055#1088#1086#1096#1080#1090#1100
      Hint = #1055#1088#1086#1096#1080#1090#1100'|'#1055#1088#1086#1096#1080#1090#1100' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1099
      ImageIndex = 22
      OnExecute = WriteDataActionExecute
    end
    object SetPhaseMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1092#1072#1079#1099
      OnExecute = SetPhaseMeasActionExecute
    end
    object SetPhaseAverageMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1091#1089#1088#1077#1076#1085#1077#1085#1085#1086#1081' '#1092#1072#1079#1099
      OnExecute = SetPhaseAverageMeasActionExecute
    end
    object SetTimeIntervalMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1074#1088#1077#1084#1077#1085#1085#1086#1075#1086' '#1080#1085#1090#1077#1088#1074#1072#1083#1072
      OnExecute = SetTimeIntervalMeasActionExecute
    end
    object SetTimeIntervalAverageMeasAction: TAction
      Category = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Caption = #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1091#1089#1088#1077#1076#1085#1077#1085#1085#1086#1075#1086' '#1074#1088#1077#1084#1077#1085#1085#1086#1075#1086' '#1080#1085#1090#1077#1088#1074#1072#1083#1072
      OnExecute = SetTimeIntervalAverageMeasActionExecute
    end
    object AddTableAction: TAction
      Category = #1060#1072#1081#1083
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
      OnExecute = AddTableActionExecute
    end
    object RestructDataType1Action: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077' '#1090#1072#1073#1083#1080#1094#1099' '#1089' '#1091#1095#1077#1090#1086#1084' 3-'#1075#1086' '#1087#1072#1088#1072#1084#1077#1090#1088#1072
      OnExecute = RestructDataType1ActionExecute
    end
    object ClearTableAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
      OnExecute = ClearTableActionExecute
    end
    object TableDefAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
      OnExecute = TableDefActionExecute
    end
    object ClearContentTableAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1089#1086#1076#1077#1088#1078#1080#1084#1086#1077' '#1090#1072#1073#1083#1080#1094#1099
      OnExecute = ClearContentTableActionExecute
    end
    object AutoUpdateChartAction: TAction
      Category = #1043#1088#1072#1092#1080#1082
      Caption = #1040#1074#1090#1086#1086#1073#1085#1086#1074#1083#1077#1085#1080#1077
      OnExecute = AutoUpdateChartActionExecute
    end
    object ExportTableToMExcelCsvFileAction: TAction
      Category = #1069#1082#1089#1087#1086#1088#1090
      Caption = #1069#1082#1089#1087#1086#1088#1090' '#1090#1072#1073#1083#1080#1094#1099' '#1074' Microsoft Excel (*.csv) '#1092#1072#1081#1083
      OnExecute = ExportTableToMExcelCsvFileActionExecute
    end
    object ClearContentColTableAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1089#1086#1076#1077#1088#1078#1080#1084#1086#1077' '#1089#1090#1086#1083#1073#1094#1072
      OnExecute = ClearContentColTableActionExecute
    end
    object ClearContentRowTableAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1089#1086#1076#1077#1088#1078#1080#1084#1086#1077' '#1089#1090#1088#1086#1082#1080
      OnExecute = ClearContentRowTableActionExecute
    end
    object InversionSignConrentTableAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1048#1085#1074#1077#1088#1089#1080#1103' '#1087#1086' '#1079#1085#1072#1082#1091' '#1089#1086#1076#1077#1088#1078#1080#1084#1086#1075#1086' '#1090#1072#1073#1083#1080#1094#1099
      OnExecute = InversionSignConrentTableActionExecute
    end
    object VerificationDataAction: TAction
      Category = #1060#1072#1081#1083
      Caption = #1042#1077#1088#1080#1092#1080#1082#1072#1094#1080#1103' '#1076#1072#1085#1085#1099#1093
      OnExecute = VerificationDataActionExecute
    end
    object ModifiTableDataAction: TAction
      Category = #1055#1088#1072#1074#1082#1072
      Caption = #1052#1086#1076#1080#1092#1080#1082#1072#1094#1080#1103' '#1076#1072#1085#1085#1099#1093' '#1074' '#1090#1072#1073#1083#1080#1094#1077
      OnExecute = ModifiTableDataActionExecute
    end
    object AboutAction: TAction
      Category = #1057#1087#1088#1072#1074#1082#1072
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnExecute = AboutActionExecute
    end
  end
  object ImageList2: TImageList
    ImageType = itMask
    ShareImages = True
    Left = 104
    Top = 344
    Bitmap = {
      494C010117001800040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000006000000001002000000000000060
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      000000000000FFFFFF0000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF000000
      0000000000000000000000000000F0FBFF00000000000000000000000000F0FB
      FF0000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF000000000000000000FFFFFF0000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00FFFFFF00000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000F0FBFF000000
      0000F0FBFF0000000000000000000000000000000000F0FBFF00000000000000
      000000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF000000
      000000000000F0FBFF000000000000000000F0FBFF0000000000F0FBFF000000
      000000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000F0FBFF000000
      00000000000000000000F0FBFF0000000000F0FBFF0000000000000000000000
      000000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF00000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFF0000FFFF00000000FF00FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      00000000FF00FFFF000000000000000000000000000000000000000000000000
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFF0000000000000000FF000000FF000000000000000000FFFF00000000
      FF0000000000FFFF000000000000000000000000000000000000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFF000000000000000000000000FF000000FF00000000000000FF000000
      FF0000000000FFFF000000000000000000000000000000000000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00FFFF00000000FF00FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000FF000000FF00FFFF00000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000FF000000FF00FFFF00000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00FFFF00000000FF00FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF000000000000000000000000FF0000000000000000000000FF000000
      FF0000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF0000000000000000FF00FFFF00000000000000000000FFFF00000000
      FF0000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF00000000FF000000FF00FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      00000000FF00FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000FF0000000000FFFF00000000000000000000FFFF00000000
      00000000FF000000FF00000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      00007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F00FFFFFF007F7F
      7F0000000000000000007F7F7F007F7F7F000000000000000000000000000000
      00000000000000000000BFBFBF00000000000000000000000000000000000000
      00007F7F7F007F7F7F00000000007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000000000FF0000000000000000000000
      000000000000000000000000FF00000000000000FF000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF007F7F7F007F7F7F000000000000000000000000000000
      000000000000BFBFBF00BFBFBF00000000000000000000000000000000000000
      00007F7F7F00FFFFFF00FFFFFF007F7F7F0000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00C0C0C000C0C0
      C000C0C0C000C0C0C0000000FF000000000000000000C0C0C0000000FF000000
      FF000000FF00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C0000000
      FF000000FF000000FF00000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF00000000000000000000000000000000FF000000FF000000
      000000000000C0C0C0000000FF000000000000000000C0C0C000000000000000
      00000000FF000000FF000000FF0000000000000000000000FF000000FF000000
      FF0000000000C0C0C00000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000000000000000FF000000
      0000000000000000FF00000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000FF000000FF000000FF00C0C0C0000000
      000000000000C0C0C00000000000000000007F7F7F00FFFFFF00000000000000
      0000000000000000000000000000000000007F7F7F00FFFFFF00000000000000
      00000000000000000000000000007F7F7F00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF0000000000000000000000
      0000FFFFFF0000000000000000007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000000000000000FF000000
      0000000000000000FF00000000000000000000000000C0C0C000000000000000
      0000000000000000FF000000FF0000000000000000000000FF000000FF000000
      FF0000000000C0C0C00000000000000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF007F7F7F00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF007F7F7F00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF007F7F7F0000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C0000000
      FF000000FF00C0C0C000000000000000000000000000C0C0C0000000FF000000
      FF000000FF00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C0000000
      FF000000FF000000FF0000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F00000000007F7F7F007F7F7F00000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F00FFFFFF000000000000000000BFBF
      BF00FF000000FF000000FF00000000000000FFFFFF007F7F7F007F7F7F000000
      00007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000C0C0C0000000
      FF000000FF00C0C0C00000000000000000000000FF000000FF000000FF000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF00000000FF00000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF007F7F7F00FFFFFF007F7F
      7F007F7F7F007F7F7F00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000FF000000FF0000000000FFFFFF00FFFFFF00FFFFFF000000
      00007F7F7F007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000C0C0C0000000
      FF000000FF00C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F007F7F7F007F7F7F00000000007F7F7F00000000007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000FF000000FF0000000000FFFFFF007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F00FFFFFF0000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000C0C0C0000000
      FF000000FF00C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF000000FF000000FF000000FF000000FF00FFFFFF00FFFFFF0000000000FFFF
      FF007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00C0C0
      C0000000FF000000FF00000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F00000000007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F00000000007F7F
      7F007F7F7F007F7F7F00FFFFFF0000000000FFFFFF0000000000000000000000
      0000000000000000FF000000FF0000000000FFFFFF007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000000000000000FF000000
      0000000000000000FF00000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF007F7F7F00FFFFFF00000000007F7F7F0000000000000000007F7F
      7F007F7F7F007F7F7F00FFFFFF0000000000FFFFFF00FFFFFF0000000000FFFF
      FF00000000000000FF000000FF0000000000FFFFFF00FFFFFF007F7F7F000000
      0000000000007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF00000000000000000000000000000000FF00C0C0C0000000
      0000000000000000FF00000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F00000000007F7F7F00FFFFFF007F7F7F0000000000FFFFFF007F7F7F007F7F
      7F007F7F7F007F7F7F000000000000000000FFFFFF00BFBFBF00000000000000
      0000000000000000FF000000FF0000000000FFFFFF007F7F7F007F7F7F007F7F
      7F00FFFFFF007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF00000000000000000000000000000000FF00C0C0C0000000
      000000000000C0C0C0000000FF000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF007F7F7F007F7F7F00000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F00000000000000000000000000FFFFFF00FFFFFF00000000000000
      00000000FF000000FF000000000000000000FFFFFF00FFFFFF007F7F7F000000
      00007F7F7F007F7F7F00000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000FF0000000000000000000000
      000000000000000000000000FF000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F007F7F7F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF0000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007F7F7F000000
      00007F7F7F007F7F7F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BFBFBF000000
      0000BFBFBF00BFBFBF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000840000008400
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BFBFBF00BFBF
      BF00BFBFBF00BFBFBF0000000000000000000000000000000000008484000084
      8400008484000084840000848400008484000084840000848400008484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00000000000084
      8400008484000084840000848400008484000084840000848400008484000084
      8400000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF0000000000000000000000
      00000000000000000000FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF000000
      0000008484000084840000848400008484000084840000848400008484000084
      8400008484000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000000000000000
      0000008484000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF008400000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000FFFF00FFFFFF0000FF
      FF00000000000084840000848400008484000084840000848400008484000084
      8400008484000084840000000000000000000000000000000000000000000000
      0000008484000084840000848400008484000084840000848400008484000084
      8400008484000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF0000000000000000000000
      00000000000000000000FFFFFF008400000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000000000000084
      8400008484000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF008400000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000BFBFBF0000000000FF000000FF000000FF00
      00000000FF00FF000000FF000000000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000008484000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF000000000000000000FFFF
      FF008400000084000000840000008400000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      FF000000FF000000FF00000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000008484000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0084000000FFFFFF00840000000000000000000000FFFFFF00000000000000
      00000000000000000000FFFFFF0000000000FFFFFF00000000000000FF000000
      FF000000FF000000FF000000FF00000000000000000000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF008400000084000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000C6C6C6000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000840000008400000084000000840000008400
      00008400000000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000FFFFFF000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000000000BFBF
      BF00FFFFFF0000000000FFFFFF000000000000000000000000007F7F7F000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000600000000100010000000000000300000000000000000000
      000000000000000000000000FFFFFF008001CFFFFFFF00008001CFFFFFFF0000
      FE7FC0FFFFFF0000FE7FC0FFEDB70000FE7FFCFFEDB70000FE7FFCFFC0030000
      FE7FFCFFC0030000CE73FC0FC0030000C663FC0FC0030000E247FFCFC0030000
      F00FFFCFC0030000F81FFE49EDB70000FC3FFE01EDB70000FE7FFF03FFFF0000
      8001FF87FFFF00008001FFCFFFFF0000FFFFFFFFFFFFFFFFFFFFF93FC3C38001
      C97FF93FC3C38001C93FF93FC3878001C91FF93FC3078001C90FF93FC30F8001
      C907F93FC01F8001C903F93FC00F8001C903F93FC0078001C907F93FC3878001
      C90FF93FC3C78001C91FF93FC3878001C93FF93FC0078001C97FF93FC00F8001
      FFFFF93FC01F8001FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF001F001
      FBFFF2FFF001F001F9FFF27FF049F249F8FFF23F80018001F87FF21F80018001
      F83FF20F92099249F81FF20780018001F81FF20780018001F83FF20F92499249
      F87FF21F80018001F8FFF23F80018001F9FFF27F9243924FFBFFF2FF800F800F
      FFFFFFFF800F800FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF800180018001FFFF
      800180018001C007999999999249C007999999998001C007800180018001C007
      800180019249C007999999998001C007999999998001C007999999999249C007
      800180018001C007800180018001C007999999999249C007999999998001C007
      800180018001FFFF80018001FFFFFFFFFF00F0F0FFFFBFFFFF0CF0F280010001
      FF00F0F0800180018000F0009999918900000000999998193F3E007680018001
      2400002080018001090000109981199921010111998199990280010080018001
      2400002080018001082101019999999921610919999999990883090180018001
      010713138001800103FF1F1FFF7DFFFFFFFFFF7EFFFFFF00FFFFBFFFFFFFFF00
      001FF003FE00FF00000FE003FE00FF000007E003FE0000000003E00380000000
      0001E003800000000000200380000000001FE00280000023001FE00380010001
      001FE003800300008FF1E00380070023FFF9E003807F0063FF75FFFF80FF00C3
      FF8FBF7D81FF0107FFFF7F7EFFFF03FF00000000000000000000000000000000
      000000000000}
  end
  object MainMenu1: TMainMenu
    Images = ImageList1
    Left = 136
    Top = 344
    object FileOpenM: TMenuItem
      Caption = #1060#1072#1081#1083
      object N2: TMenuItem
        Action = FileOpen
      end
      object FileReOpenM: TMenuItem
        Action = FileReOpen
      end
      object FileSaveM: TMenuItem
        Action = FileSave
      end
      object N5: TMenuItem
        Action = FileSaveAs
      end
      object N10: TMenuItem
        Caption = '-'
      end
      object N8: TMenuItem
        Action = AddTableAction
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object WriteDataM: TMenuItem
        Action = WriteDataAction
      end
      object N16: TMenuItem
        Action = VerificationDataAction
      end
    end
    object N6: TMenuItem
      Caption = #1055#1088#1072#1074#1082#1072
      object CreateColM: TMenuItem
        Action = CreateColAction
      end
      object DeleteColM: TMenuItem
        Action = DeleteColAction
      end
      object CreateRowM: TMenuItem
        Action = CreateRowAction
      end
      object DeleteRowM: TMenuItem
        Action = DeleteRowAction
      end
      object AddGroupCellsM: TMenuItem
        Action = AddGroupCellsAction
      end
      object AddSubtableM: TMenuItem
        Action = AddSubtableAction
      end
      object DelSubtableM: TMenuItem
        Action = DelSubtableAction
      end
      object TableDefM: TMenuItem
        Action = TableDefAction
      end
      object ClearTableM: TMenuItem
        Action = ClearTableAction
      end
      object CleaContentTableM: TMenuItem
        Action = ClearContentTableAction
      end
      object CleaContentColTableM: TMenuItem
        Action = ClearContentColTableAction
      end
      object CleaContentRowTableM: TMenuItem
        Action = ClearContentRowTableAction
      end
      object ModifiTableDataM: TMenuItem
        Action = ModifiTableDataAction
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object EditModeM: TMenuItem
        Caption = #1056#1077#1078#1080#1084' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103
        Hint = #1056#1077#1078#1080#1084' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103'|'#1042#1082#1083#1102#1095#1080#1090#1100'/'#1074#1099#1082#1083#1102#1095#1080#1090#1100' '#1088#1077#1078#1080#1084' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103
        ImageIndex = 19
      end
      object N11: TMenuItem
        Caption = '-'
      end
      object RestructDataType1M: TMenuItem
        Action = RestructDataType1Action
        Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077' '#1089' '#1091#1095#1077#1090#1086#1084' 3-'#1075#1086' '#1087#1072#1088#1072#1084#1077#1090#1088#1072
      end
      object N15: TMenuItem
        Action = InversionSignConrentTableAction
      end
    end
    object N13: TMenuItem
      Caption = #1040#1074#1090#1086#1080#1079#1084#1077#1088#1077#1085#1080#1077
      object StartAutoVoltMeasM: TMenuItem
        Action = StartAutoVoltMeasAction
      end
      object StartAutoVoltMeasActiveCellsM: TMenuItem
        Action = StartAutoVoltMeasActiveCellsAction
      end
      object StopVoltMeasM: TMenuItem
        Action = StopVoltMeasAction
      end
      object N1: TMenuItem
        Caption = #1057#1090#1080#1083#1100' '#1076#1074#1080#1078#1077#1085#1080#1103
        object SetJumpHorizontalDownM: TMenuItem
          Action = SetJumpHorizontalDownAction
          GroupIndex = 100
          RadioItem = True
        end
        object SetJumpHorizontalUpM: TMenuItem
          Action = SetJumpHorizontalUpAction
          GroupIndex = 100
          RadioItem = True
        end
        object SetJumpVerticalForwardM: TMenuItem
          Action = SetJumpVerticalForwardAction
          GroupIndex = 100
          RadioItem = True
        end
        object SetJumpVerticalBackM: TMenuItem
          Action = SetJumpVerticalBackAction
          GroupIndex = 100
          RadioItem = True
        end
        object N9: TMenuItem
          Caption = '-'
          GroupIndex = 100
        end
        object SetJumpSmoothM: TMenuItem
          Action = SetJumpSmoothAction
          GroupIndex = 100
        end
      end
    end
    object N14: TMenuItem
      Caption = #1069#1082#1089#1087#1086#1088#1090
      object Exele1: TMenuItem
        Action = ExportTableToMExcelCsvFileAction
      end
    end
    object TypeMeas: TMenuItem
      Caption = #1058#1080#1087' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
      Visible = False
      object VoltDCMeasM: TMenuItem
        Action = SetVoltDCMeasAction
        GroupIndex = 200
        RadioItem = True
      end
      object VoltACMeasM: TMenuItem
        Action = SetVoltACMeasAction
        GroupIndex = 200
        RadioItem = True
      end
      object CurrentDCMeasM: TMenuItem
        Action = SetCurrentDCMeasAction
        GroupIndex = 200
        RadioItem = True
      end
      object CurrentACMeasM: TMenuItem
        Action = SetCurrentACMeasAction
        GroupIndex = 200
        RadioItem = True
      end
      object Resistance2xMeasM: TMenuItem
        Action = SetResistance2xMeasAction
        GroupIndex = 200
        RadioItem = True
      end
      object Resistance4xMeasM: TMenuItem
        Action = SetResistance4xMeasAction
        GroupIndex = 200
        RadioItem = True
      end
      object FrequencyMeasM: TMenuItem
        Action = SetFrequencyMeasAction
        GroupIndex = 200
        RadioItem = True
      end
      object PhaseMeasM: TMenuItem
        Action = SetPhaseMeasAction
        GroupIndex = 200
      end
      object PhaseAverageMeasM: TMenuItem
        Action = SetPhaseAverageMeasAction
        GroupIndex = 200
      end
      object TimeIntervalMeasM: TMenuItem
        Action = SetTimeIntervalMeasAction
        GroupIndex = 200
      end
      object TimeIntervalAverageMeasM: TMenuItem
        Action = SetTimeIntervalAverageMeasAction
        GroupIndex = 200
      end
    end
    object OptionsMeas: TMenuItem
      Caption = #1054#1087#1094#1080#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1103
      object CorrectModeM: TMenuItem
        Action = CorrectModeAction
      end
      object MismatchModeM: TMenuItem
        Action = MismatchModeAction
      end
    end
    object U1: TMenuItem
      Caption = #1043#1088#1072#1092#1080#1082
      object ZX1: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1075#1088#1072#1092#1080#1082' Z(X)'
        OnClick = ZX1Click
      end
      object ZY1: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1075#1088#1072#1092#1080#1082' Z(Y)'
        OnClick = ZY1Click
      end
      object ZX2: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074#1089#1077' '#1075#1088#1072#1092#1080#1082#1080' Z(X)'
        OnClick = ZX2Click
      end
      object ZY2: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074#1089#1077' '#1075#1088#1072#1092#1080#1082#1080' Z(Y)'
        OnClick = ZY2Click
      end
      object N3: TMenuItem
        Caption = #1054#1095#1080#1089#1090#1080#1090#1100
        OnClick = N3Click
      end
      object N12: TMenuItem
        Action = AutoUpdateChartAction
      end
    end
    object N17: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object AboutM: TMenuItem
        Action = AboutAction
      end
    end
  end
  object ImageList1: TImageList
    ShareImages = True
    Left = 72
    Top = 344
    Bitmap = {
      494C010117001800040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000006000000001002000000000000060
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      000000000000FFFFFF0000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF000000
      0000000000000000000000000000F0FBFF00000000000000000000000000F0FB
      FF0000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF000000000000000000FFFFFF0000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00FFFFFF00000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000F0FBFF000000
      0000F0FBFF0000000000000000000000000000000000F0FBFF00000000000000
      000000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF000000
      000000000000F0FBFF000000000000000000F0FBFF0000000000F0FBFF000000
      000000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF00000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000F0FBFF000000
      00000000000000000000F0FBFF0000000000F0FBFF0000000000000000000000
      000000000000F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF00000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFF0000FFFF00000000FF00FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      00000000FF00FFFF000000000000000000000000000000000000000000000000
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFF0000000000000000FF000000FF000000000000000000FFFF00000000
      FF0000000000FFFF000000000000000000000000000000000000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFF000000000000000000000000FF000000FF00000000000000FF000000
      FF0000000000FFFF000000000000000000000000000000000000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00FFFF00000000FF00FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000FF000000FF00FFFF00000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000FF000000FF00FFFF00000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00FFFF00000000FF00FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF000000000000000000000000FF0000000000000000000000FF000000
      FF0000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF0000000000000000FF00FFFF00000000000000000000FFFF00000000
      FF0000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF00000000FF000000FF00FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      00000000FF00FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000FF0000000000FFFF00000000000000000000FFFF00000000
      00000000FF000000FF00000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000C0C0C0000000000000000000C0C0C0000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000FFFF0000000000000000
      0000FFFF00000000000000000000FFFF00000000000000000000FFFF00000000
      000000000000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      00007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F00FFFFFF007F7F
      7F0000000000000000007F7F7F007F7F7F000000000000000000000000000000
      00000000000000000000BFBFBF00000000000000000000000000000000000000
      00007F7F7F007F7F7F00000000007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000000000FF0000000000000000000000
      000000000000000000000000FF00000000000000FF000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF007F7F7F007F7F7F000000000000000000000000000000
      000000000000BFBFBF00BFBFBF00000000000000000000000000000000000000
      00007F7F7F00FFFFFF00FFFFFF007F7F7F0000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00C0C0C000C0C0
      C000C0C0C000C0C0C0000000FF000000000000000000C0C0C0000000FF000000
      FF000000FF00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C0000000
      FF000000FF000000FF00000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF00000000000000000000000000000000FF000000FF000000
      000000000000C0C0C0000000FF000000000000000000C0C0C000000000000000
      00000000FF000000FF000000FF0000000000000000000000FF000000FF000000
      FF0000000000C0C0C00000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000000000000000FF000000
      0000000000000000FF00000000000000000000000000C0C0C000000000000000
      000000000000C0C0C000000000000000FF000000FF000000FF00C0C0C0000000
      000000000000C0C0C00000000000000000007F7F7F00FFFFFF00000000000000
      0000000000000000000000000000000000007F7F7F00FFFFFF00000000000000
      00000000000000000000000000007F7F7F00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF0000000000000000000000
      0000FFFFFF0000000000000000007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000000000000000FF000000
      0000000000000000FF00000000000000000000000000C0C0C000000000000000
      0000000000000000FF000000FF0000000000000000000000FF000000FF000000
      FF0000000000C0C0C00000000000000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF007F7F7F00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF007F7F7F00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF007F7F7F0000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000C0C0C0000000
      FF000000FF00C0C0C000000000000000000000000000C0C0C0000000FF000000
      FF000000FF00C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C0000000
      FF000000FF000000FF0000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F00000000007F7F7F007F7F7F00000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F00FFFFFF000000000000000000BFBF
      BF00FF000000FF000000FF00000000000000FFFFFF007F7F7F007F7F7F000000
      00007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000C0C0C0000000
      FF000000FF00C0C0C00000000000000000000000FF000000FF000000FF000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF00000000FF00000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF007F7F7F00FFFFFF007F7F
      7F007F7F7F007F7F7F00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000FF000000FF0000000000FFFFFF00FFFFFF00FFFFFF000000
      00007F7F7F007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000C0C0C0000000
      FF000000FF00C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F007F7F7F007F7F7F00000000007F7F7F00000000007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000FF000000FF0000000000FFFFFF007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F00FFFFFF0000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000C0C0C0000000
      FF000000FF00C0C0C000000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF000000FF000000FF000000FF000000FF00FFFFFF00FFFFFF0000000000FFFF
      FF007F7F7F007F7F7F007F7F7F007F7F7F0000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000FF00C0C0
      C0000000FF000000FF00000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F00000000007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F00000000007F7F
      7F007F7F7F007F7F7F00FFFFFF0000000000FFFFFF0000000000000000000000
      0000000000000000FF000000FF0000000000FFFFFF007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF0000000000000000000000000000000000000000FF000000
      0000000000000000FF00000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF0000000000FFFF
      FF00FFFFFF007F7F7F00FFFFFF00000000007F7F7F0000000000000000007F7F
      7F007F7F7F007F7F7F00FFFFFF0000000000FFFFFF00FFFFFF0000000000FFFF
      FF00000000000000FF000000FF0000000000FFFFFF00FFFFFF007F7F7F000000
      0000000000007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF00000000000000000000000000000000FF00C0C0C0000000
      0000000000000000FF00000000000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF007F7F7F007F7F
      7F00000000007F7F7F00FFFFFF007F7F7F0000000000FFFFFF007F7F7F007F7F
      7F007F7F7F007F7F7F000000000000000000FFFFFF00BFBFBF00000000000000
      0000000000000000FF000000FF0000000000FFFFFF007F7F7F007F7F7F007F7F
      7F00FFFFFF007F7F7F007F7F7F000000000000000000FFFF0000000000000000
      000000000000FFFF00000000000000000000000000000000FF00C0C0C0000000
      000000000000C0C0C0000000FF000000000000000000FFFF0000000000000000
      000000000000FFFF000000000000000000000000000000000000FFFF00000000
      000000000000FFFF000000000000000000007F7F7F00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF007F7F7F007F7F7F00000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F00000000000000000000000000FFFFFF00FFFFFF00000000000000
      00000000FF000000FF000000000000000000FFFFFF00FFFFFF007F7F7F000000
      00007F7F7F007F7F7F00000000000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000FF0000000000000000000000
      000000000000000000000000FF000000000000000000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF000000000000000000007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F007F7F7F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF0000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007F7F7F000000
      00007F7F7F007F7F7F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BFBFBF000000
      0000BFBFBF00BFBFBF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000840000008400
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BFBFBF00BFBF
      BF00BFBFBF00BFBFBF0000000000000000000000000000000000008484000084
      8400008484000084840000848400008484000084840000848400008484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00000000000084
      8400008484000084840000848400008484000084840000848400008484000084
      8400000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000C6C6C6000000
      0000008484000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF0000000000000000000000
      00000000000000000000FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF000000
      0000008484000084840000848400008484000084840000848400008484000084
      8400008484000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000000000000000
      0000008484000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF008400000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000FFFF00FFFFFF0000FF
      FF00000000000084840000848400008484000084840000848400008484000084
      8400008484000084840000000000000000000000000000000000000000000000
      0000008484000084840000848400008484000084840000848400008484000084
      8400008484000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF0000000000000000000000
      00000000000000000000FFFFFF008400000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008484000084840000000000000000000000000000000000000000000084
      8400008484000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF008400000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000BFBFBF0000000000FF000000FF000000FF00
      00000000FF00FF000000FF000000000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000008484000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF000000000000000000FFFF
      FF008400000084000000840000008400000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      FF000000FF000000FF00000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000008484000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0084000000FFFFFF00840000000000000000000000FFFFFF00000000000000
      00000000000000000000FFFFFF0000000000FFFFFF00000000000000FF000000
      FF000000FF000000FF000000FF00000000000000000000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF008400000084000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000084840000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000C6C6C6000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000840000008400000084000000840000008400
      00008400000000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000FFFFFF000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000FFFFFF00FFFFFF000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000000000BFBF
      BF00FFFFFF0000000000FFFFFF000000000000000000000000007F7F7F000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000600000000100010000000000000300000000000000000000
      000000000000000000000000FFFFFF008001CFFFFFFF00008001CFFFFFFF0000
      FE7FC0FFFFFF0000FE7FC0FFEDB70000FE7FFCFFEDB70000FE7FFCFFC0030000
      FE7FFCFFC0030000CE73FC0FC0030000C663FC0FC0030000E247FFCFC0030000
      F00FFFCFC0030000F81FFE49EDB70000FC3FFE01EDB70000FE7FFF03FFFF0000
      8001FF87FFFF00008001FFCFFFFF0000FFFFFFFFFFFFFFFFFFFFF93FC3C38001
      C97FF93FC3C38001C93FF93FC3878001C91FF93FC3078001C90FF93FC30F8001
      C907F93FC01F8001C903F93FC00F8001C903F93FC0078001C907F93FC3878001
      C90FF93FC3C78001C91FF93FC3878001C93FF93FC0078001C97FF93FC00F8001
      FFFFF93FC01F8001FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF001F001
      FBFFF2FFF001F001F9FFF27FF049F249F8FFF23F80018001F87FF21F80018001
      F83FF20F92099249F81FF20780018001F81FF20780018001F83FF20F92499249
      F87FF21F80018001F8FFF23F80018001F9FFF27F9243924FFBFFF2FF800F800F
      FFFFFFFF800F800FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF800180018001FFFF
      800180018001C007999999999249C007999999998001C007800180018001C007
      800180019249C007999999998001C007999999998001C007999999999249C007
      800180018001C007800180018001C007999999999249C007999999998001C007
      800180018001FFFF80018001FFFFFFFFFF00F0F0FFFFBFFFFF0CF0F280010001
      FF00F0F0800180018000F0009999918900000000999998193F3E007680018001
      2400002080018001090000109981199921010111998199990280010080018001
      2400002080018001082101019999999921610919999999990883090180018001
      010713138001800103FF1F1FFF7DFFFFFFFFFF7EFFFFFF00FFFFBFFFFFFFFF00
      001FF003FE00FF00000FE003FE00FF000007E003FE0000000003E00380000000
      0001E003800000000000200380000000001FE00280000023001FE00380010001
      001FE003800300008FF1E00380070023FFF9E003807F0063FF75FFFF80FF00C3
      FF8FBF7D81FF0107FFFF7F7EFFFF03FF00000000000000000000000000000000
      000000000000}
  end
  object FileOpenDialog1: TOpenDialog
    Filter = 'Digital interpolator (*.dgi)|*.dgi|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Left = 168
    Top = 344
  end
  object SaveFileDialog: TSaveDialog
    Filter = 
      #1058#1077#1082#1089#1090#1086#1074#1099#1077' '#1092#1072#1081#1083#1099' Microsoft Excel (*.csv)|*.csv|'#1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.' +
      '*'
    Left = 200
    Top = 344
  end
end
