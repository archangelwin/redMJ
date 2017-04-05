
----------------------------------------------------------------------------------------------------

USE lobbyGameUserDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GP_LogonByAccounts]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[GSP_GP_LogonByAccounts]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

CREATE PROC GSP_GP_LogonByAccounts
	@strAccounts VARCHAR(32),
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
DECLARE @ErrorDescribe VARCHAR(255)
DECLARE @AllLogonTimes INT

-- ���ű���
DECLARE @GroupName VARCHAR(32)

-- ִ���߼�
BEGIN

	-- Ч���ַ

	-- ��ѯ�û�
	SELECT @UserID=UserID, @Accounts=Accounts, @LogonPass=LogonPass, @Gender=Gender,@LogonNullity=LogonNullity, 
	@UserRight=UserRight, @MasterRight=MasterRight, @FaceID=FaceID, @GroupID=GroupID,@MemberOrder=MemberOrder, 
	@MemberOverDate=MemberOverDate, @Experience=Experience, @LastLogonDate=LastLogonDate, @LastLogonIP=LastLogonIP , @AllLogonTimes=AllLogonTimes
	FROM UserAccounts WHERE Accounts=@strAccounts
	
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
	IF @MemberOrder>0 AND (GetDate()>@MemberOverDate) 
	BEGIN
		SET @MemberOrder=0
		UPDATE UserAccounts SET MemberOrder=0 WHERE Accounts=@strAccounts
	END

	-- ��ȡ������Ϣ
	SET @GroupName=''

	----------����Session-------------------------------------------(+)
	declare @d datetime
	declare @SessionId varchar(1024)
	set @d=GETDATE()
	set @SessionId = 's' + cast(RAND() as varchar) +
		cast(RAND() as varchar) +
		cast(DATEPART(millisecond,@d) as varchar) +
		cast(DATEPART(month,@d) as varchar) +
		cast(ABS(COS(DATEPART(millisecond,@d))) as varchar) +
		cast(DATEPART(year,@d) as varchar) +
		cast(DATEPART(day,@d) as varchar) + cast(RAND() as varchar) +
		cast(DATEPART(week,@d) as varchar) + cast(RAND() as varchar) +
		cast(DATEPART(Hour,@d) as varchar) +
		cast(DATEPART(minute,@d) as varchar) + cast(RAND() as varchar) +
		cast(DATEPART(second,@d) as varchar) +
		cast(DATEPART(quarter,@d) as varchar) + cast(RAND() as varchar) +
		cast(DATEPART(dayofyear,@d) as varchar) + cast(RAND() as varchar) + cast(getdate() as varchar)
	set @SessionId = replace(@SessionId,' ','')
	set @SessionId = replace(@SessionId,':','')
	set @SessionId = replace(@SessionId,'-','')
	set @SessionId = replace(@SessionId,'.','')
	set @SessionId=left(@SessionId,128)
	----------����Session-------------------------------------------(-)

	-- �������ݿ�
	UPDATE UserAccounts SET AllLogonTimes=AllLogonTimes+1,LastLogonDate=GETDATE(),LastLogonIP=@strClientIP,SessionId=@SessionId
	WHERE UserID=@UserID

	-- �������
	SELECT @UserID AS UserID, @Accounts AS Accounts, @FaceID AS FaceID, @Gender AS Gender, @UserRight AS UserRight, 
	@MasterRight AS MasterRight, @GroupID AS GroupID, @GroupName AS GroupName,@MemberOrder AS MemberOrder, 
	@Experience AS Experience, @LastLogonDate AS LastLogonDate, @LastLogonIP AS LastLogonIP, @SessionId AS SessionId
	
END

RETURN 0

----------------------------------------------------------------------------------------------------

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

