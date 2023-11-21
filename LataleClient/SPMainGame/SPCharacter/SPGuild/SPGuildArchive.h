// Copyright (C) DURAGON
//***************************************************************************
// System Name : GUILD BASE
// Comment     : 
// Creation    : DURAGON 2007-4-04    11:18 
//***************************************************************************
// Todo
// GuildMemberList�� SPWindowGuild �ʿ� �־ �� (Window�� ����Ҷ��� �ʿ���)
#pragma once

#include "GlobalDefines_Share.h"

enum GUILD_MEMBER_UPDATE_TYPE{	GUILD_MEMBER_USER = 0, GUILD_MEMBER_MASTER, } ;
enum GUILD_MENU_TYPE
{
	GUILD_MENU_LIST	= 0,			// ��� ���
	GUILD_MENU_STATUS,				// ��� ����
	GUILD_MENU_CROPS,				// ��� �۹�
};

enum GUILD_AUTHORITY_TYPE
{
//	GUILD_AUTHO_CHGMASTER	= 0x00000001,			// ���� ����
	GUILD_AUTHO_CROPS		= 0x00000001,			// �۹�
	GUILD_AUTHO_GRADE		= 0x00000002,			// ����
	GUILD_AUTHO_SLOGUN		= 0x00000004,			// ���ΰ�
	GUILD_AUTHO_EXPEL		= 0x00000008,			// ����
	GUILD_AUTHO_INVITE		= 0x00000020,			// �ʴ�
};

enum GUILD_USER_COUNT
{
	ALL_USER_COUNT	= 0 ,
	ON_USER_COUNT	= 1 ,
	OFF_USER_COUNT	= 2 ,
};

enum GUILD_PROPERTY
{
	GUILD_PROPERTY_NULL		= 0,
	GUILD_PROPERTY_NORMAL	= 1,	// �Ϲ���
	GUILD_PROPERTY_ANGEL	= 2,	// õ����
	GUILD_PROPERTY_DAEMON	= 3,	// �Ǹ���
	
} ;

enum GUILD_MEMBER_GRADE
{
	GUILD_GRADE_01 = 1,		// MASTER
	GUILD_GRADE_02,			// SUB MASTER
	GUILD_GRADE_03,
	GUILD_GRADE_04,
	GUILD_GRADE_05,
	GUILD_GRADE_06,			// BEGINER
	_MAX_GUILD_GRADE ,
};

enum GUILD_LIST_UPDATE_TYPE
{
	LIST_UPDATE_INIT	= 1,
	LIST_UPDATE_USERLIST,
	LIST_UPDATE_JOIN,
	LIST_UPDATE_SECEDE,
	LIST_UPDATE_CHANGE,
	LIST_UPDATE_SCROLL,
} ;

//@return	0	: ����
//@return 1	: ���� 1 (����)
//@return 2	: ���� 2 (�Ӵ�)
//@return 3	: ���� 3 (������)
//@return 4	: ���� 4
//@return 5	: ���� 5
//@return 6	: �̹� ��� ����
//@return 7	: ���� ����
//@return 8	: LDT Error
enum GUILD_CREATE_ERROR
{
	GUILD_CREATE_OK				= 0 ,
	ERROR_GUILD_CREATE_STAT		= 1 ,
	ERROR_GUILD_CREATE_MONEY	= 2 ,
	ERROR_GUILD_CREATE_ITEM		= 3 ,
	ERROR_GUILD_CREATE_REQ4		= 4 ,
	ERROR_GUILD_CREATE_REQ5		= 5 ,
	ERROR_GUILD_CREATE_ISHAVE	= 6 ,
	ERROR_GUILD_CREATE_GNAME	= 7 ,
	ERROR_GUILD_CREATE_LDT		= 8 ,
	ERROR_PKTSEND_FAIL			= 9 ,
} ;

#define MAX_GUILD_MEMBER_COUNT		50



struct CROP_INFO ;
struct DISPLAY_CROP_UNIT;
class SPItem ;
class SPWindow ;
class SPGuildCrops ;
class SPGuildLDT ;
class SPGuildArchive
{

public:
	static SPGuildArchive*	m_pInstance;
	static SPGuildArchive*	GetInstance();
	static void Release();

	SPGuildArchive();
	virtual ~SPGuildArchive();
	void	Init() ;
	void	Process(float fTime) ;

	////////////////////////////////////////////////////////////////////////////
	// For Information
	bool	CheckGuildLevel(int iLevel, int iLevel2 = 0) ;
	bool	CheckGuildType(int iType) ;
	int		CheckGuildCreate(int iType) ;
	int		CheckGuildLevelup(int& iRetValue) ;
	int		CheckGuildDestroy() ;
	
	// For Crop Packet Send
	bool	SendGuildCreate(int iType, int iEmblem1, int iEmblem2, const char* strGName) ;
	bool	SendGuildDestroy() ;
	bool	SendGuildCommonInfo() ;
	bool	SendGuildInvite(const char* szCharName) ;
	bool	SendGuildLeave() ;
	bool	SendGuildLevelup(int iNewLevel, int iItemID, int iItemCount) ;
	bool	SendGuildEmblemChange(int iEmblemID, int iItemID, int iItemCount) ;
	
	
	// For Crop Data Setting
	void	SetGuildBasicInfo(PPCGUILD pPCGuild) ;
	void	SetGuildCommonInfo(PGUILD_COMMON pPCGuild) ;
	bool	SetInviteName(const char* szRequestName) ;

	void	SetCropInformation(int iCmd, int iCropID=0, int iRemainTime=0, int iNourishTime=0, int iHastenSumTime=0) ;
	void	SetCropGrowthComplete() ;
	void	SetInGuildRoom(bool bSet)	{		m_bInGuildRoom = bSet ;		}
	bool	GetInGuildRoom()			{		return m_bInGuildRoom ;		}

	SPGuildCrops*	GetCropArchive() ;

	// For Get Crop&Guild Data
	bool	GetBasicAvailable() ;
	bool	IsMaster(const char* strUserName = NULL) ;
	bool	GetInvitable() ;
	bool	GetSlogunChangable() ;
	bool	GetRankChangable() ;
	bool	GetExpelable() ;
	bool	GetCorpsChangable() ;
	int		GetGuildProperty() ;
	int		GetGuildGrade() ;
	int		GetGuildLevel() ;
	int		GetGuildTotalPoint() ;
	int		GetGuildPointProtege() ;
	int		GetGuildEmblem(int iNo) ;
	int		GetGuildNextPoint()		{	return m_iNextLevelPoint;	}
	
	const char*		GetInviteName() ;
	const char*		GetGuildSlogun() ;
	const char*		GetGuildName() ;
	int				GetMyGuildDungeon() ;
	void	SetGuildTotalPoint(int iGPoint) ;				// for Receive Member list
	void	UpdateGuildTotalPoint(int iGPoint) ;			// for Add or Delete Member
	void	UpdateGuildLevel(int iLevel) ;
	
	bool	ChangeSlogun(int iMode, const char* strSlogun) ;
	bool	UpdateMyGrade(int iGrade) ;
	bool	UpdateMyEmblem(int iGMark1, int iGMark2, int iGMark3) ;
	void	SetGuildAuthority(int iGrade) ;
	void	RemoveGuildInfo() ;
	void	ClearInviteName() ;

	//////////////////////////////////////////////////////////////////////////
	// Crop
	bool	hasCorps() ;
	int		UseCropItem(SPItem* pItem) ;						// ����ɱ�
	int		UseNourishItem(int iUseType, SPItem* pItem) ;		// ���

	bool	GetCropImageByEvent(UINT32 iEventID, int iGLevel, DISPLAY_CROP_UNIT& dpCrop ) ;
	int		GetNourishTime() ;	

	void	ReceiveCropRegist() ;		// Crop
	void	ReceiveCropNourish() ;
	void	ReceiveCropEliminate() ;
	bool	SendCropRegist(UINT32 iCropID, TRASH_ITEM stConsumeItem) ;			// Crop
	bool	SendCropNourish(UINT32 iBoosterID, TRASH_ITEM stConsumeItem) ;
	bool	SendCropEliminate() ;

	// Update NPC Image
	int		UpdateCropLevelImage(bool bShowText);
	void	UpdateCropNPC( int iCropLevel) ;
	void	UpdateCutInNPC( int iCropLevel ) ;
	void	UpdateWindowCropNPC( int iCropLevel ) ;

private:
	void	SetEnableBasicInfo(bool bEnable) ;
	bool	SetBasicInfo(long lGID, int iGEmblem1, int iGEmblem2, int iGrade, int iProperty, int iGLevel, const char* strGName, int iGPoint = 0) ;
	bool	SetBasicInfo(long iGID, int iGEmblem1, int iGEmblem2, int iGEmblem3, int iGrade, int iProperty, int iGLevel, const char* strGName, int iGPoint/*= 0*/);
	void	SetProperty( const char* strGSlogun) ;

	void	DeleteBasicInfo() ;
	void	DeleteCommonInfo() ;
	int		GetDungeonNo(int iGLevel, int iGType) ;

protected:
	SPGuildCrops*			m_pCropArchive ;		// �۹� ����
	SPGuildLDT*				m_pGuildLDT ;			// Guild LDT ����
	

	bool					m_bBasicInfo ;			// �������� ����
	bool					m_bHasCorps ;			// �۹��� �ִ��� ����
	bool					m_bInGuildRoom ;		// ��������

	std::string				m_strRequestName ;

	//////////////////////////////////////////////////////////////////////////
	// Authority (����)
	bool					m_bChgMaster ;			// ���� ���� ����
	bool					m_bChgPlant ;			// �۹� ����
	bool					m_bChgSlogun ;			// ���ΰǺ��� ����
	bool					m_bChgGrade ;			// �������� ����
	bool					m_bInvite ;				// �ʴ� ����
	bool					m_bExpel ;				// ���� ����

	//////////////////////////////////////////////////////////////////////////
	// Guild Basic
	long					m_iGuildID;				// ��� ID
	int						m_iGuildEmblem[3] ;		// �ں� ID
	int						m_iGuildProperty ;		// ��� ����
	int						m_iGuildGrade ;			// ��峻 ��å (1:�渶)
	std::string				m_strGuildName;			// ��� �̸�
	int						m_iGuildPoint ;			// ��� ����Ʈ
	int						m_iGuildTotalPoint ;	// ��� ����ġ
	int						m_iNextLevelPoint ;		// �������� ���� ����ġ

	//////////////////////////////////////////////////////////////////////////
	// Guild Property
	int						m_iGuildLevel;			// ��� ����
	std::string				m_strGuildSlogun;		// ��� ���ΰ�
	std::string				m_strSendSlogun ;		// �渶�� Send�ϴ� ���ΰ�

};