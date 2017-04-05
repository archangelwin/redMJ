
----------------------------------------------------------------------------------------------------

USE LobbyGameUserDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GP_LogonByUserID]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[GSP_GP_LogonByUserID]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

CREATE PROC GSP_GP_LogonByUserID
	@dwUserID INT,
	@strPassword VARCHAR(32),
	@strClientIP VARCHAR(15)
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
DECLARE @ErrorDescribe VARCHAR(256)

-- ���ű���
DECLARE @GroupName VARCHAR(32)

-- ִ���߼�
BEGIN

	-- Ч���ַ

	-- ��ѯ�û�
	SELECT @UserID=UserID, @Accounts=Accounts, @LogonPass=LogonPass, @Gender=Gender, @LogonNullity=LogonNullity, 
	@UserRight=UserRight, @MasterRight=MasterRight, @FaceID=FaceID, @GroupID=GroupID, @MemberOrder=MemberOrder, 
	@MemberOverDate=MemberOverDate, @Experience=Experience, @LastLogonDate=LastLogonDate, @LastLogonIP=LastLogonIP
	FROM UserAccounts WHERE UserID=@dwUserID
	
	-- �ж��û��Ƿ����
	IF @UserID IS NULL
	BEGIN
		SET @ErrorDescribe='�ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		SELECT [ErrorDescribe]=@ErrorDescribe
		RETURN 1
	END
	
	-- �ж��Ƿ��ֹ��½
	IF @LogonNullity<>0
	BEGIN
		SET @ErrorDescribe='����ʻ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		SELECT [ErrorDescribe]=@ErrorDescribe
		RETURN 2
	END
	
	-- �ж��û�����
	IF @LogonPass<>@strPassword
	BEGIN
		SET @ErrorDescribe='�ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		SELECT [ErrorDescribe]=@ErrorDescribe
		RETURN 3
	END
	
	-- �жϻ�Ա�ȼ�
	IF GETDATE()>@MemberOverDate SET @MemberOrder=0
	
	-- ��ȡ������Ϣ
	SET @GroupName=''

	-- �������ݿ�
	UPDATE UserAccounts SET AllLogonTimes=AllLogonTimes+1,LastLogonDate=GETDATE(),LastLogonIP=@strClientIP
	WHERE UserID=@UserID
	
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

