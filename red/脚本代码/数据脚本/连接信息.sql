
----------------------------------------------------------------------------------------------------

USE WHServerInfoDB
GO

----------------------------------------------------------------------------------------------------

-- 删除数据
DELETE SQLdatabaseInfo
GO

----------------------------------------------------------------------------------------------------

-- 连接信息
INSERT SQLdatabaseInfo (databasePort, databaseAddr, databaseUser, databasePass) VALUES (1433, '127.0.0.1', '027129486b47d67febe8', '0435291a6b5ad6e2ebc7')

----------------------------------------------------------------------------------------------------

GO