object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1057#1077#1088#1074#1077#1088
  ClientHeight = 298
  ClientWidth = 266
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Status: TLabel
    Left = 8
    Top = 16
    Width = 84
    Height = 13
    Caption = #1057#1090#1072#1090#1091#1089' '#1089#1077#1088#1074#1077#1088#1072':'
  end
  object StatusName: TLabel
    Left = 98
    Top = 16
    Width = 53
    Height = 13
    Caption = #1054#1090#1082#1083#1102#1095#1077#1085
  end
  object PortName: TLabel
    Left = 184
    Top = 16
    Width = 29
    Height = 13
    Caption = #1055#1086#1088#1090':'
  end
  object LogName: TLabel
    Left = 110
    Top = 92
    Width = 41
    Height = 30
    Caption = #1051#1086#1075
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 30
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object StartButton: TButton
    Left = 10
    Top = 48
    Width = 75
    Height = 25
    Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100
    TabOrder = 0
    OnClick = StartButtonClick
  end
  object CloseButton: TButton
    Left = 98
    Top = 48
    Width = 75
    Height = 25
    Caption = #1042#1099#1082#1083#1102#1095#1080#1090#1100
    Enabled = False
    TabOrder = 1
    OnClick = CloseButtonClick
  end
  object Port: TEdit
    Left = 219
    Top = 13
    Width = 41
    Height = 21
    MaxLength = 5
    TabOrder = 2
    Text = '5555'
  end
  object Log: TMemo
    Left = 8
    Top = 128
    Width = 250
    Height = 157
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object Server: TServerSocket
    Active = False
    Port = 1024
    ServerType = stNonBlocking
    OnClientConnect = ServerClientConnect
    OnClientDisconnect = ServerClientDisconnect
    OnClientRead = ServerClientRead
    OnClientError = ServerClientError
    Left = 192
    Top = 48
  end
end
