IF EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = N'WHGameUserDB')
	DROP database [WHGameUserDB]
GO

CREATE database [WHGameUserDB]  ON (NAME = N'WHGameUserDB_Data', FILENAME = N'E:\棋牌原代码\cf\Data\WHGameUserDB_Data.MDF' , SIZE = 2, FILEGROWTH = 10%) LOG ON (NAME = N'WHGameUserDB_Log', 
	FILENAME = N'E:\棋牌原代码\cf\Data\WHGameUserDB_Log.LDF' , SIZE = 1, FILEGROWTH = 10%)
	COLLATE Chinese_PRC_CI_AS
GO

exec sp_dboption N'WHGameUserDB', N'autoclose', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'bulkcopy', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'trunc. log', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'torn page detection', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'read only', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'dbo use', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'single', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'autoshrink', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'ANSI null default', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'recursive triggers', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'ANSI nulls', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'concat null yields null', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'cursor close on commit', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'default to local cursor', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'quoted identifier', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'ANSI warnings', N'false'
GO

exec sp_dboption N'WHGameUserDB', N'auto create statistics', N'true'
GO

exec sp_dboption N'WHGameUserDB', N'auto update statistics', N'true'
GO

if( (@@microsoftversion / power(2, 24) = 8) and (@@microsoftversion & 0xffff >= 724) )
	exec sp_dboption N'WHGameUserDB', N'db chaining', N'false'
GO

use [WHGameUserDB]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[UserAccounts]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[UserAccounts]
GO

CREATE TABLE [dbo].[UserAccounts] (
	[UserID] [int] IDENTITY (1, 1) NOT NULL ,
	[Accounts] [varchar] (32) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[RegAccounts] [varchar] (32) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[LogonPass] [char] (32) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[InsurePass] [char] (32) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[Gender] [bit] NOT NULL ,
	[LogonNullity] [bit] NOT NULL ,
	[ServiceNullity] [bit] NOT NULL ,
	[UserRight] [int] NOT NULL ,
	[MasterRight] [int] NOT NULL ,
	[FaceID] [int] NOT NULL ,
	[GroupID] [int] NOT NULL ,
	[MemberOrder] [int] NOT NULL ,
	[Experience] [int] NOT NULL ,
	[AllLogonTimes] [int] NOT NULL ,
	[MemberOverDate] [datetime] NOT NULL ,
	[RegisterDate] [datetime] NOT NULL ,
	[LastLogonDate] [datetime] NOT NULL ,
	[RegisterIP] [varchar] (15) COLLATE Chinese_PRC_CI_AS NOT NULL ,
	[LastLogonIP] [varchar] (15) COLLATE Chinese_PRC_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[UserAccounts] WITH NOCHECK ADD 
	CONSTRAINT [PK_UserAccounts_UserID] PRIMARY KEY  CLUSTERED 
	(
		[UserID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[UserAccounts] ADD 
	CONSTRAINT [DF_UserAccounts_Gender] DEFAULT (0) FOR [Gender],
	CONSTRAINT [DF_UserAccounts_LogonNullity] DEFAULT (0) FOR [LogonNullity],
	CONSTRAINT [DF_UserAccounts_ServiceNullity] DEFAULT (0) FOR [ServiceNullity],
	CONSTRAINT [DF_UserAccounts_GamePopedom] DEFAULT (0) FOR [UserRight],
	CONSTRAINT [DF_UserAccounts_MasterPopedom] DEFAULT (0) FOR [MasterRight],
	CONSTRAINT [DF_UserAccounts_FaceID] DEFAULT (0) FOR [FaceID],
	CONSTRAINT [DF_UserAccounts_GroupID] DEFAULT (0) FOR [GroupID],
	CONSTRAINT [DF_UserAccounts_MemberOrder] DEFAULT (0) FOR [MemberOrder],
	CONSTRAINT [DF_UserAccounts_Experience] DEFAULT (0) FOR [Experience],
	CONSTRAINT [DF_UserAccounts_AllLogonTimes] DEFAULT (0) FOR [AllLogonTimes],
	CONSTRAINT [DF_UserAccounts_MemberOverDate] DEFAULT (1980 - 1 - 1) FOR [MemberOverDate],
	CONSTRAINT [DF_UserAccounts_RegisterDate] DEFAULT (getdate()) FOR [RegisterDate],
	CONSTRAINT [DF_UserAccounts_LastLogonDate] DEFAULT (getdate()) FOR [LastLogonDate]
GO

 CREATE  UNIQUE  INDEX [IX_UserAccounts_Accounts] ON [dbo].[UserAccounts]([Accounts]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_UserAccounts_GroupID] ON [dbo].[UserAccounts]([GroupID]) ON [PRIMARY]
GO

 CREATE  INDEX [IX_UserAccounts_RegAccounts] ON [dbo].[UserAccounts]([RegAccounts]) ON [PRIMARY]
GO


exec sp_addextendedproperty N'MS_Description', N'用户帐号', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'Accounts'
GO
exec sp_addextendedproperty N'MS_Description', N'总登陆次数', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'AllLogonTimes'
GO
exec sp_addextendedproperty N'MS_Description', N'经验值', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'Experience'
GO
exec sp_addextendedproperty N'MS_Description', N'头像 ID', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'FaceID'
GO
exec sp_addextendedproperty N'MS_Description', N'用户性别', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'Gender'
GO
exec sp_addextendedproperty N'MS_Description', N'社团 ID', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'GroupID'
GO
exec sp_addextendedproperty N'MS_Description', N'保险密码', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'InsurePass'
GO
exec sp_addextendedproperty N'MS_Description', N'上次登陆时间', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'LastLogonDate'
GO
exec sp_addextendedproperty N'MS_Description', N'上次登陆 IP', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'LastLogonIP'
GO
exec sp_addextendedproperty N'MS_Description', N'禁止登陆标志', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'LogonNullity'
GO
exec sp_addextendedproperty N'MS_Description', N'登陆密码', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'LogonPass'
GO
exec sp_addextendedproperty N'MS_Description', N'管理权限', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'MasterRight'
GO
exec sp_addextendedproperty N'MS_Description', N'会员等级', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'MemberOrder'
GO
exec sp_addextendedproperty N'MS_Description', N'会员到期时间', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'MemberOverDate'
GO
exec sp_addextendedproperty N'MS_Description', N'注册帐号', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'RegAccounts'
GO
exec sp_addextendedproperty N'MS_Description', N'注册时间', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'RegisterDate'
GO
exec sp_addextendedproperty N'MS_Description', N'注册 IP', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'RegisterIP'
GO
exec sp_addextendedproperty N'MS_Description', N'禁止服务标志', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'ServiceNullity'
GO
exec sp_addextendedproperty N'MS_Description', N'用户 ID', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'UserID'
GO
exec sp_addextendedproperty N'MS_Description', N'用户权限', N'user', N'dbo', N'table', N'UserAccounts', N'column', N'UserRight'


GO

