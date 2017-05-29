object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'PDU - '#1082#1086#1076#1080#1088#1086#1074#1072#1085#1080#1077' '#1080' '#1076#1082#1086#1076#1080#1088#1086#1074#1072#1085#1080#1077
  ClientHeight = 488
  ClientWidth = 477
  Color = clBtnFace
  Constraints.MaxHeight = 527
  Constraints.MaxWidth = 493
  Constraints.MinHeight = 527
  Constraints.MinWidth = 493
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 168
    Height = 13
    Caption = #1053#1086#1084#1077#1088' '#1086#1090#1087#1088#1072#1074#1080#1090#1077#1083#1103'/'#1087#1086#1083#1091#1095#1072#1090#1077#1083#1103':'
  end
  object Label2: TLabel
    Left = 272
    Top = 16
    Width = 100
    Height = 13
    Caption = #1053#1086#1084#1077#1088' '#1057#1052#1057'-'#1094#1077#1085#1090#1088#1072':'
  end
  object Label3: TLabel
    Left = 16
    Top = 72
    Width = 92
    Height = 13
    Caption = #1058#1077#1082#1089#1090' '#1089#1086#1086#1073#1097#1077#1085#1080#1103':'
  end
  object Label4: TLabel
    Left = 16
    Top = 269
    Width = 84
    Height = 13
    Caption = 'PDU-'#1089#1086#1086#1073#1097#1077#1085#1080#1077':'
  end
  object PhoneSR: TEdit
    Left = 16
    Top = 35
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '+79123456789'
  end
  object PhoneSMS: TEdit
    Left = 272
    Top = 35
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '+79107899999'
  end
  object TextMessage: TMemo
    Left = 16
    Top = 91
    Width = 441
    Height = 89
    TabOrder = 2
  end
  object btnCoding: TButton
    Left = 62
    Top = 200
    Width = 139
    Height = 55
    Caption = #1055#1077#1088#1077#1082#1086#1076#1080#1088#1086#1074#1072#1090#1100' '#1074'  PDU   '#8595
    TabOrder = 3
    WordWrap = True
    OnClick = btnCodingClick
  end
  object Button2: TButton
    Left = 272
    Top = 200
    Width = 137
    Height = 55
    Caption = #1055#1077#1088#1077#1082#1086#1076#1080#1088#1086#1074#1072#1090#1100' '#1080#1079' PDU   '#8593
    TabOrder = 4
    WordWrap = True
    OnClick = Button2Click
  end
  object PDUMessage: TMemo
    Left = 16
    Top = 288
    Width = 441
    Height = 185
    ScrollBars = ssVertical
    TabOrder = 5
  end
end
