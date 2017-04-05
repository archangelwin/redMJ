
----------------------------------------------------------------------------------------------------

USE WHServerInfoDB
GO

----------------------------------------------------------------------------------------------------

-- ɾ������
DELETE GameTypeInfo
DELETE GameKindInfo
GO

----------------------------------------------------------------------------------------------------

-- ��������
INSERT GameTypeInfo (TypeID, TypeName, SortID, Enable) VALUES ( 1, '����' , 100, 1)
INSERT GameTypeInfo (TypeID, TypeName, SortID, Enable) VALUES ( 2, '�˿���',200, 1)
INSERT GameTypeInfo (TypeID, TypeName, SortID, Enable) VALUES ( 3, '�齫��',300, 1)
INSERT GameTypeInfo (TypeID, TypeName, SortID, Enable) VALUES ( 4, '������',400, 1)

----------------------------------------------------------------------------------------------------

-- ͨ����Ϸ
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 1, 2, '���', 'ShowHand.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 2, 1, '�й�����', 'ChinaChess.exe', 65542, 100, 1, 'WHTreasureDB')

INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 3, 1, 'Χ��', 'WeiQi.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 4, 2, '�ڿ�', 'SX_Trench.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 5, 1, '��������', 'Chess.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 6, 2, '������', 'Land.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 7, 3, '�齫', 'Sparrow.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 8, 2, '�ܵÿ�', 'QuickRun.exe', 65542, 100, 1, 'WHTreasureDB')

-- ������Ϸ
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 9, 2, '�����', 'Hoe.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 10, 2, '�ڽܿ�', 'BlackJack.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 11, 2, '����', 'UpGrade.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 12, 1, '�Ĺ�����', 'FourEnsign.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 13, 2, 'թ��', 'GoldFlower.exe', 65542, 100, 1, 'WHTreasureDB')

INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 14, 2, '����', 'UncoverPig.exe', 65542, 100, 1, 'WHTreasureDB')
INSERT GameKindInfo (KindID, TypeID, KindName, ProcessName, MaxVersion, SortID, Enable, databaseName) VALUES ( 15, 2, '����', 'Fast.exe', 65542, 100, 1, 'WHTreasureDB')



----------------------------------------------------------------------------------------------------

GO