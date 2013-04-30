object MessagesForm: TMessagesForm
  Left = 253
  Top = 418
  Width = 811
  Height = 400
  Caption = 'Messages'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 720
    Top = 344
    Width = 75
    Height = 25
    Caption = #1054#1050
    Default = True
    TabOrder = 0
    OnClick = Button1Click
  end
  object MessagesMemo: TMemo
    Left = 0
    Top = 0
    Width = 803
    Height = 337
    Align = alTop
    ScrollBars = ssVertical
    TabOrder = 1
  end
end
