
----------------------------------------------------------------------------------------------------

USE lobbyGameUserDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GP_RegisterUser]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[GSP_GP_RegisterUser]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

CREATE PROC GSP_GP_RegisterUser
	@strAccounts VARCHAR(32),
	@strPassword CHAR(32),
	@strClientIP VARCHAR(15),
	@cbGender BIT,
	@nFaceID INT
WITH ENCRYPTION AS

SET NOCOUNT ON

-- ��������
DECLARE @UserID INT
DECLARE @Accounts VARCHAR(32)
DECLARE @LogonPass CHAR(32)
DECLARE @Gender BIT
DECLARE @LogonNullity BIT
DECLARE @UserRight INT
DECLARE @MasterRight INT
DECLARE @FaceID INT
DECLARE @GroupID INT
DECLARE @MemberOrder INT
DECLARE @MemberOverDate DATETIME
DECLARE @Experience INT
DECLARE @LastLogonDate DATETIME
DECLARE @LastLogonIP VARCHAR(15)
DECLARE @ExeSentence VARCHAR(512)
DECLARE @ErrorDescribe VARCHAR(128)

-- ���ű���
DECLARE @GroupName VARCHAR(32)

--Ч���û�����
DECLARE @SpecialCharCount INT
DECLARE @SpecialCharacter VARCHAR(32)

-- ִ���߼�

BEGIN

	-- Ч���ַ
	
	-- ��ѯ�û�
	IF EXISTS (SELECT UserID FROM UserAccounts WHERE Accounts=@strAccounts)
	BEGIN
		SET @ErrorDescribe='�û��Ѵ��ڣ��뻻��һ�û����ֳ����ٴ�ע�ᣡ'
		SELECT [ErrorDescribe]=@ErrorDescribe
		RETURN 1
	END

	-- ע���û�
	INSERT UserAccounts (Accounts,RegAccounts,LogonPass,InsurePass,Gender,FaceID,RegisterIP,LastLogonIP)
		VALUES (@strAccounts,@strAccounts,@strPassword,@strPassword,@cbGender,@nFaceID,@strClientIP,@strClientIP)
	IF @@ERROR<>0
	BEGIN
		SET @ErrorDescribe='�û��Ѵ��ڣ��뻻��һ�û����ֳ����ٴ�ע�ᣡ'
		SELECT [ErrorDescribe]=@ErrorDescribe
		RETURN 2
	END

	-- ��ѯ�û�
	SELECT @UserID=UserID, @Accounts=Accounts, @LogonPass=LogonPass, @Gender=Gender,@LogonNullity=LogonNullity, 
		@UserRight=UserRight, @MasterRight=MasterRight, @FaceID=FaceID, @GroupID=GroupID,@MemberOrder=MemberOrder, 
		@MemberOverDate=MemberOverDate, @Experience=Experience, @LastLogonDate=LastLogonDate, @LastLogonIP=LastLogonIP
		FROM UserAccounts WHERE Accounts=@strAccounts

	-- �������
	SELECT @UserID AS UserID, @Accounts AS Accounts, @FaceID AS FaceID, @Gender AS Gender, @UserRight AS UserRight, 
	@MasterRight AS MasterRight, @GroupID AS GroupID, @GroupName AS GroupName,@MemberOrder AS MemberOrder, 
	@Experience AS Experience, @LastLogonDate AS LastLogonDate, @LastLogonIP AS LastLogonIP

END

RETURN 0

----------------------------------------------------------------------------------------------------

GO

SET QUOTED_IDENTIFIER OFF 
GO

SET ANSI_NULLS ON 
GO

