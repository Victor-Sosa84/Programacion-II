object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 433
  ClientWidth = 1006
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 752
    Top = 80
    Width = 211
    Height = 31
    Caption = 'Vectores en matrices'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object StringGrid1: TStringGrid
    Left = 280
    Top = 141
    Width = 401
    Height = 265
    DefaultColWidth = 40
    DefaultRowHeight = 40
    FixedCols = 0
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    ParentFont = False
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 224
    Top = 48
    Width = 121
    Height = 39
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 400
    Top = 48
    Width = 121
    Height = 39
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Text = 'Edit2'
  end
  object Edit3: TEdit
    Left = 400
    Top = 96
    Width = 121
    Height = 39
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Text = 'Edit3'
  end
  object Button1: TButton
    Left = 32
    Top = 22
    Width = 129
    Height = 35
    Caption = 'Cargar Filas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 63
    Width = 185
    Height = 35
    Caption = 'Cargar Columnas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 104
    Width = 233
    Height = 57
    Caption = 'Cargar Fila y Columna'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 8
    Top = 167
    Width = 169
    Height = 41
    Caption = 'Cargar Circulo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 8
    Top = 214
    Width = 193
    Height = 57
    Caption = 'Cuadrado Magico'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 792
    Top = 117
    Width = 129
    Height = 41
    Caption = 'Random'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 799
    Top = 164
    Width = 122
    Height = 41
    Caption = 'Sumar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 799
    Top = 211
    Width = 122
    Height = 44
    Caption = 'Mayor'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    OnClick = Button8Click
  end
  object Button9: TButton
    Left = 799
    Top = 261
    Width = 170
    Height = 41
    Caption = 'Mayor Al Final'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 12
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 799
    Top = 308
    Width = 129
    Height = 41
    Caption = 'BubbleSort'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 776
    Top = 355
    Width = 201
    Height = 38
    Caption = 'Cargar 1er parcial'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 16
    Top = 277
    Width = 201
    Height = 40
    Caption = 'Invertir Por Filas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 15
    OnClick = Button12Click
  end
  object Button13: TButton
    Left = 16
    Top = 323
    Width = 161
    Height = 38
    Caption = 'Cambiar Fila'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 16
    OnClick = Button13Click
  end
  object Button14: TButton
    Left = 8
    Top = 367
    Width = 203
    Height = 44
    Caption = 'Cargar 1er parcial'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 17
    OnClick = Button14Click
  end
end
