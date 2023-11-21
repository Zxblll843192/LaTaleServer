// Copyright (C) DURAGON
//***************************************************************************
// System Name : GUILD BASE
// Comment     : 
// Creation    : DURAGON 2007-4-04    11:18 
//***************************************************************************

#include "SPCommon.h"

#include "SPWindowDEF.h"
#include "SPWindow.h"
#include "SPWindowStatic.h"
#include "SPWindowSlider.h"
#include "SPWindowButton.h"
#include "SPWindowEdit.h"
//#include "SPWindowList.h"
#include "SPWindowFriendUser.h"
#include "SPWindowChat.h"
#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"

#include <algorithm>

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"
#include "SockWnd.h"
#include "SPNetworkManager.h"

#include "SPGameObjectDEF.h"
#include "SPGameObject.h"
#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPPlayer.h"
#include "SPPlayerInvenArchive.h"
#include "SPGOBManager.h"
#include "SPGOBStatus.h"
#include "SPCheckManager.h"
#include "SPLDTFile.h"
#include "SPLDTManager.h"

#include "SPItem.h"
#include "SPItemAttr.h"
#include "SPItemStatus.h"

#include "SPResourceManager.h"
#include "SPEventDEF.h"			// for close
#include "SPEventManager.h"
#include "SPEventNpcHandler.h"
#include "SPLocalizeManager.h"
#include "SPPvpManager.h"

#include "SPUtil.h"
#include "SPDebug.h"
#include "GlobalDefines_Share.h"
#include "SPGuildLDT.h"
#include "SPGuildArchive.h"
#include "SPCropArchive.h"
//#include "SPWindowGuild.h"
#include "_Error_log.h"


// SPGuildArchive*	SPGuildArchive::m_pInstance=0;




SPGuildArchive::SPGuildArchive()
: m_bBasicInfo(false)
//, m_bListInfo(false)
//, m_bShowOffline(true)
//, m_iCurPage(0)
, m_bChgSlogun(false)
, m_bChgGrade(false)
, m_bInvite(false)
, m_bExpel(false)
, m_bChgPlant(false)
, m_pCropArchive(NULL)
{
}

SPGuildArchive::~SPGuildArchive()
{
	DeleteBasicInfo() ;
	DeleteCommonInfo() ;
	//DeleteMemberList() ;

	SAFE_DELETE(m_pCropArchive) ;
	// SAFE_DELETE(m_pGuildLDT) ;
}

//
//void SPGuildArchive::Release()
//{
//	if( m_pInstance )
//	{
//		delete m_pInstance;
//		m_pInstance = NULL;
//	}
//}
//
//SPGuildArchive*	SPGuildArchive::GetInstance()
//{	
//	if(m_pInstance==0)
//		m_pInstance = new SPGuildArchive;
//	return (SPGuildArchive*)m_pInstance;
//}


void SPGuildArchive::Init()
{
	if( SPLocalizeManager::GetInstance()->IsEnableValue(LV_GUILD) )	{
		m_pCropArchive		= new SPGuildCrops ;
		m_pCropArchive->Init() ;
	}
}


void SPGuildArchive::Process(float fTime) 
{
	int iUpdate = 0 ;
	if( SPLocalizeManager::GetInstance()->IsEnableValue(LV_GUILD) )
	{
		if( GetCropArchive()->CropProcess(fTime, iUpdate) )
		{
			if( iUpdate == CROP_UPDATE_LEVEL )	{
				UpdateCropLevelImage(true) ;
			}
			g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_CROP_UPDATE, CROP_UPDATE_TIME, 0);
			g_pInterfaceManager->SPChildWndSendMessage(WIID_CROPS, SPIM_GUILD_CROP_UPDATE, CROP_UPDATE_TIME, 0);
		}
	}
}



void SPGuildArchive::DeleteBasicInfo()
{
	m_bBasicInfo		= false ;	// �������� ����
	m_iGuildLevel		= 0 ;		// ��� ����

	m_iGuildID			= 0 ;		// ��� ID
	m_iGuildEmblem[0]	= 0 ;		// �ں� ID
	m_iGuildEmblem[1]	= 0 ;		// �ں� ID
	m_iGuildProperty	= 0 ;		// ��� ����
	m_iGuildGrade		= 0 ;		// ��峻 ��å (1:�渶)
	m_iGuildTotalPoint	= 0 ;		// ��� �� ����ġ
	m_iNextLevelPoint	= 1 ;
	m_strGuildName.clear() ;		// ��� �̸�
}

void SPGuildArchive::DeleteCommonInfo()
{
	m_strGuildSlogun.clear() ;		// ��� ���ΰ�
	m_strSendSlogun.clear() ;		// �渶�� Send�ϴ� ���ΰ�
}



/**
	��� Ż��, ����Ǵ� ��� ��� ���� ����
	1) ��� ����â�� �� �ִ� ��� Hide
	2) Player ��� ���� ����
	3) ��� Archive ���� ����
*/
void SPGuildArchive::RemoveGuildInfo()
{
	if( g_pInterfaceManager->GetGuildInfoWindow() == NULL )		return ;

	if( g_pInterfaceManager->GetGuildInfoWindow()->IsShow() )	
		g_pInterfaceManager->GetGuildInfoWindow()->Hide() ;

	if( g_pInterfaceManager->IsCutIn() )		
		g_pEventManager->SetCutInState(CUT_IN_STATE_RELEASE);		

	DeleteBasicInfo() ;
	DeleteCommonInfo() ;
	//DeleteMemberList() ;
	SetCropInformation(CROP_SET_CLEAR) ;		// Destroy
}




/**
	������ �޾Ƽ� �����Ͱ� ���õǸ� Window�� �˷��־�� �Ѵ�.
*/
void SPGuildArchive::SetEnableBasicInfo(bool bEnable)
{
	m_bBasicInfo = bEnable ;
	g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_INFO_ENABLE, 0, 0, true);
}




/**
	��忡 ���ԵǾ� �ִ��� ���� Ȯ��
*/
bool SPGuildArchive::GetBasicAvailable()
{
	return m_bBasicInfo ;
}

/**
	�۹��� �ִ��� ���� Ȯ��
*/
bool SPGuildArchive::hasCorps()
{
	return m_pCropArchive->hasCorps() ;
}


/**
	@return ��������� ������ Property
	��������� ������ -1
*/
int SPGuildArchive::GetGuildProperty()
{
	return ( GetBasicAvailable() ) ? m_iGuildProperty : 0 ;
}
/**
	��峻 ���� �޾ƿ���
	@return 0 : ���� �ƴ�
	@return 1 ~ 6 : ��� �� ����
*/
int SPGuildArchive::GetGuildGrade()
{
	return ( GetBasicAvailable() ) ? m_iGuildGrade : 0 ;
}
/**
	�ڽ��� ���� ����� ����
	@return 0 : ���� �ƴ�
	@return 1 ~ 5 : ��� ����
*/
int SPGuildArchive::GetGuildLevel()
{
	return ( GetBasicAvailable() ) ? m_iGuildLevel : 0 ;
}
/**
	����� ���� �� ����ġ
*/
int SPGuildArchive::GetGuildTotalPoint()
{
	return ( GetBasicAvailable() ) ? m_iGuildTotalPoint : 0 ;
}
int SPGuildArchive::GetGuildPointProtege()
{
	if( !GetBasicAvailable() )	return 0 ;
	if( m_iNextLevelPoint <= 0 )	m_iNextLevelPoint = 1 ;
	float fTotalProtege = ( m_iGuildTotalPoint > 0 ) ? ((float)m_iGuildTotalPoint * 100 / m_iNextLevelPoint) : 0 ;
	int iTotalProtege = (int)fTotalProtege ;
	if( iTotalProtege > 100 )	
		return 100 ;
	if( iTotalProtege < 0 )
		return 0 ;

	return iTotalProtege ;
}
/**
	��� �� ����ġ ���� -> WindowGuild���� Member ������ ���ؼ� ����
*/
void SPGuildArchive::SetGuildTotalPoint(int iGPoint)
{
	if( iGPoint > -1 )	m_iGuildTotalPoint = iGPoint ;
}
void SPGuildArchive::UpdateGuildTotalPoint(int iGPoint)
{
	if( (m_iGuildTotalPoint + iGPoint) > 0 )	
		m_iGuildTotalPoint += iGPoint ;
}
/**
	��� ���ΰ� ��������
	@return NULL : ���� �ƴ�
	@return const char* : ���ΰ�
*/
const char* SPGuildArchive::GetGuildSlogun()
{
	return ( GetBasicAvailable() ) ? m_strGuildSlogun.c_str() : NULL ;
}
/**
	���� ��������
	@return NULL : ���� �ƴ�
	@return const char* : ����
*/
const char* SPGuildArchive::GetGuildName()
{
	return ( GetBasicAvailable() ) ? m_strGuildName.c_str() : NULL ;
}
/**
	��� ���� Number ��������
	@param int iNo : ù��° or �ι�°
	@return int : ���� ���� ��ȣ
*/
int SPGuildArchive::GetGuildEmblem(int iNo)
{
	return ( iNo >= 0 && iNo < 3 ) ? m_iGuildEmblem[iNo] : 0 ;
}
/**
	������ �δ���ȣ ��������
	@param int iGLevel : ��� ����
	@param int iGType : ��� Ÿ��
	@return 0 : ���� �ƴ�
	@return int : ���� �δ� ��ȣ
*/
int	SPGuildArchive::GetDungeonNo(int iGLevel, int iGType)
{
	if( iGLevel < 1 || iGType < GUILD_PROPERTY_NORMAL )		
	{
		ErrorFLogs->Error_Log("Error::Guild Level[%d], Type [%d] is Invalid!!", iGLevel, iGType) ;
		return 0 ;
	}
	
	int iKey = iGLevel * 10 + iGType ;
	PGUILD_ATTR pGuildData ;
	pGuildData = g_pkGuildManager->FindGuildAttribute(iKey) ;

	if( pGuildData )
		return pGuildData->iDungeonNo ;
	else
		return 0 ;
}
/**
	���� ������ ������ �δ� ��ȣ ��������
	@return 0 : ���� �ƴ�
	@return int : ���� �δ� ��ȣ
*/
int SPGuildArchive::GetMyGuildDungeon()
{
	return ( GetBasicAvailable() ) ? GetDungeonNo(m_iGuildLevel, m_iGuildProperty) : 0 ;
}

/**
	EventID�� ���ؼ� �ش� ������ �۹� �̹����� ��´�.
*/
bool SPGuildArchive::GetCropImageByEvent(UINT32 iEventID, int iCLevel, DISPLAY_CROP_UNIT& dpCrop )
{
	if( iCLevel < 0 || iCLevel >= CROP_LEVEL_MAX )
		iCLevel = m_iGuildLevel ;
	return g_pkGuildManager->GetCropImageByEvent(iEventID, iCLevel, dpCrop) ;
}


/**
	Crop Level�� ���� Image Update
*/
int	SPGuildArchive::UpdateCropLevelImage(bool bShowText)
{
	int iCropLevel = m_pCropArchive->GetCropLevel() ;
	if( iCropLevel < 0 || iCropLevel >= CROP_LEVEL_MAX )	{
		ErrorFLogs->Error_Log("##UpdateCropLevelImage Fail : Level Invalid[%d]", iCropLevel) ;
		return 0 ;
	}

	// Background Crop Update
	UpdateCropNPC(iCropLevel) ;

	// Window Crop Update
	UpdateWindowCropNPC(iCropLevel) ;
	
	// Cut-in Image & Text Update
	if(g_pEventManager->GetCutInState() == CUT_IN_STATE_GUILD_CROPS) {
		UpdateCutInNPC(iCropLevel) ;
	}

	

	return 1;
}


/**
	MapEvent���� CropImageID�� �ش��ϴ� NPC�� UPdate �Ѵ�
*/
void SPGuildArchive::UpdateCropNPC( int iCropLevel )
{
	CLASS_ID ClassID ;
	INSTANCE_ID InstanceID ;

	m_pCropArchive->GetCropClassID(InstanceID, ClassID) ;
	if( InstanceID == 0 || ClassID == 0 ) {
		ErrorFLogs->Error_Log("##Crop InstanceID[%d], ClassID[%d] Invalid", InstanceID, ClassID) ;
		return ;
	}
	UINT32 iUpdateImageID = m_pCropArchive->GetCropImageID(iCropLevel) ;
	if( iUpdateImageID != 0 )
		g_pGOBManager->UpdateEventNPC(InstanceID, ClassID, iUpdateImageID) ;
}
/**
	Cut-in�̹����� �ش� ������ ������Ʈ �Ѵ�.
*/
void SPGuildArchive::UpdateCutInNPC( int iCropLevel )
{
	UINT32 iCutInImageID = m_pCropArchive->GetCropCutinImageID(iCropLevel) ;
	if( iCutInImageID != 0 )
		g_pEventManager->GetEventHandler()->SetNpcTalkImage(iCutInImageID);
	SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_SHOPTALK);
	pWindow->Show();
	pWindow->SPSendMessage(SPIM_SET_SHOPTALK_MSG, (WPARAM)m_pCropArchive->GetCropCutinTalk(iCropLevel), 0);
}
/**
	Window�� CropLevelUp�� �˷��� �̹����� �����ϵ��� �Ѵ�.
*/
void SPGuildArchive::UpdateWindowCropNPC( int iCropLevel )
{
	g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_CROP_UPDATE, CROP_UPDATE_LEVEL, iCropLevel);
	g_pInterfaceManager->SPChildWndSendMessage(WIID_CROPS, SPIM_GUILD_CROP_UPDATE, CROP_UPDATE_LEVEL, iCropLevel);
}



/**
	GuildLevelUp ���� ���� ������Ʈ
*/
void SPGuildArchive::UpdateGuildLevel(int iLevel)
{
	m_iGuildLevel = iLevel ;

	int iKeyNext = 0 ;
	// �ְ����̸� ���� ������ Limit�� �����Ѵ�.
	if( m_iGuildLevel == g_pkGuildManager->GetLimitGuildLevel() )
		iKeyNext = m_iGuildLevel * 10 + m_iGuildProperty ;
	else
		iKeyNext = (m_iGuildLevel+1) * 10 + m_iGuildProperty ;

	PGUILD_ATTR pGuildData ;
	pGuildData = g_pkGuildManager->FindGuildAttribute(iKeyNext) ;
	if( pGuildData == NULL )
		return ;

	m_iNextLevelPoint = pGuildData->iPointLimit ;
}




/**
	��� ��ɺ� ������ �ִ��� ���� 
*/
bool SPGuildArchive::GetInvitable()
{
	return m_bInvite ;		// �ʴ� ����
}
//bool SPGuildArchive::GetMasterChangable()
//{
//	return m_bChgMaster ;	// ���� ���� ����
//}
bool SPGuildArchive::GetSlogunChangable()
{
	return m_bChgSlogun ;	// ���ΰ� ���� ����
}
bool SPGuildArchive::GetRankChangable()
{
	return m_bChgGrade ;	// ���� ���� ����
}
bool SPGuildArchive::GetExpelable()
{
	return m_bExpel ;	// ���� ����
}
bool SPGuildArchive::GetCorpsChangable()
{
	return m_bChgPlant ;	// �۹� ���� ���� ����
}
int	SPGuildArchive::GetNourishTime()
{
	return m_pCropArchive->GetNourishTime() ;	// �۹��� ���� ����ð�
}

SPGuildCrops* SPGuildArchive::GetCropArchive()
{
	return m_pCropArchive ;
}


/**
	��忡�� ���������� ������ �����Ѵ�.
*/
void SPGuildArchive::SetGuildAuthority(int iGrade)
{
	// Grade���� AuthorityLDT ������ ������ �о �����Ѵ�.
	if( iGrade < GUILD_GRADE_01 || iGrade >= _MAX_GUILD_GRADE )
		return ;
	m_iGuildGrade = iGrade ;
	int iAuthority = g_pkGuildManager->GetGuildAuthority(iGrade) ;
	
//	m_bChgMaster	= (iAuthority & GUILD_AUTHO_CHGMASTER )	? true : false ;
	m_bChgPlant		= (iAuthority & GUILD_AUTHO_CROPS )		? true : false ;
	m_bChgGrade		= (iAuthority & GUILD_AUTHO_GRADE )		? true : false ;
	m_bChgSlogun	= (iAuthority & GUILD_AUTHO_SLOGUN )	? true : false ;
	m_bExpel		= (iAuthority & GUILD_AUTHO_EXPEL )		? true : false ;
	m_bInvite		= (iAuthority & GUILD_AUTHO_INVITE )	? true : false ;

	ErrorFLogs->Error_Log("Set GuildAuthority Grade[%d], Plant[%d], Grade[%d], Slogun[%d], Expel[%d], Invite[%d]",
							iGrade, m_bChgPlant, m_bChgGrade, m_bChgSlogun, m_bExpel, m_bInvite) ;
}







/**
	���� ���� ����� ������ �����Ѵ�.
*/
bool SPGuildArchive::SetBasicInfo(long iGID, int iGEmblem1, int iGEmblem2, int iGrade, int iProperty, int iGLevel, const char* strGName, int iGPoint/*= 0*/)
{
	m_iGuildID			= iGID ;				// ��� ID
	m_iGuildEmblem[0]	= iGEmblem1 ;			// �ں� ID
	m_iGuildEmblem[1]	= iGEmblem2 ;			// �ں� ID
	m_iGuildGrade		= iGrade ;				// ��峻 ��å
	m_iGuildProperty	= iProperty ;			// ��� ����
	m_strGuildName		= strGName ;			// ��� �̸�
	m_iGuildPoint		= iGPoint ;				// ��� ����Ʈ
	UpdateGuildLevel(iGLevel) ;					// ��� ����

	SetGuildAuthority(m_iGuildGrade) ;
	ErrorFLogs->Error_Log("SetBasicInfo: GID[%ld] EmblemID[%d, %d] Property[%d] Grade[%d] GLevel[%d] GName[%s] GPoint[%d]", m_iGuildID, m_iGuildEmblem[0], m_iGuildEmblem[1], m_iGuildProperty, m_iGuildGrade, m_iGuildLevel, m_strGuildName.c_str(), iGPoint) ;
	return ( iGID ) ? true : false ;
}

/**
	���� ���� ����� ������ �����Ѵ�.
*/
bool SPGuildArchive::SetBasicInfo(long iGID, int iGEmblem1, int iGEmblem2, int iGEmblem3, int iGrade, int iProperty, int iGLevel, const char* strGName, int iGPoint/*= 0*/)
{
	m_iGuildID			= iGID ;				// ��� ID
	m_iGuildEmblem[0]	= iGEmblem1 ;			// �ں� ICON
	m_iGuildEmblem[1]	= iGEmblem2 ;			// �ں� BG
	m_iGuildEmblem[2]	= iGEmblem3 ;			// �ں� FX
	m_iGuildGrade		= iGrade ;				// ��峻 ��å
	m_iGuildProperty	= iProperty ;			// ��� ����
	m_strGuildName		= strGName ;			// ��� �̸�
	m_iGuildPoint		= iGPoint ;				// ��� ����Ʈ
	UpdateGuildLevel(iGLevel) ;					// ��� ����

	SetGuildAuthority(m_iGuildGrade) ;
	ErrorFLogs->Error_Log("SetBasicInfo: GID[%ld] EmblemID[%d, %d] Property[%d] Grade[%d] GLevel[%d] GName[%s] GPoint[%d]", m_iGuildID, m_iGuildEmblem[0], m_iGuildEmblem[1], m_iGuildProperty, m_iGuildGrade, m_iGuildLevel, m_strGuildName.c_str(), iGPoint) ;
	return ( iGID ) ? true : false ;
}

void SPGuildArchive::SetProperty(const char* strGSlogun)
{
	m_strGuildSlogun	= strGSlogun ;		// ��� ���ΰ�
	ErrorFLogs->Error_Log("SetProperty: Slogun[%s]", m_strGuildSlogun.c_str()) ;
}


/**
	Crop�� �ð��� �����Ѵ�.
	@param int iCmd : 0(�ʱ�ȭ), 1(����), 2(�ð� ������Ʈ)
*/
void SPGuildArchive::SetCropInformation(int iCmd, int iCropID/*=0*/, int iRemainTime/*=0*/, int iNourishTime/*=0*/, int iHastenSumTime/*=0*/)
{
	m_pCropArchive->SetCropInformation(iCmd, iCropID, iRemainTime, iNourishTime, iHastenSumTime) ;
	if( iCmd == CROP_SET_DATA || iCmd == CROP_SET_INITIALIZE )	{
		UpdateCropLevelImage(false) ;
	}
	else if ( iCmd == CROP_SET_NOURISH )
	{
		if( m_pCropArchive->CheckCropLevelup() == true ) {
			UpdateCropLevelImage(true) ;
		}
	}
}

/**
	���� ���� �Ϸ�
*/
void SPGuildArchive::SetCropGrowthComplete()
{
	m_pCropArchive->SetGrowthComplete() ;
}


/**
	Guild Master���� ���θ� Ȯ���Ѵ�.
	@param const char strName = NULL : default �ڽ�
	@return bool : Master ����
*/
bool SPGuildArchive::IsMaster(const char* strUserName /* = NULL*/)
{
	if( GetBasicAvailable() == false )	
		return false ;

	return ( m_iGuildGrade == GUILD_GRADE_01 ) ? true : false ;
}







/**
	��� ���� üũ ( ��� ���� üũ )
*/
bool SPGuildArchive::CheckGuildLevel(int iLevel, int iLevel2)
{
	if( iLevel2 <= 0 )
		return ( m_iGuildLevel >= iLevel ) ? true : false ;
	else
		return ( m_iGuildLevel >= iLevel && m_iGuildLevel <= iLevel2 ) ? true : false ;
}
/**
	��� ���� üũ ( ��� Ÿ�� üũ )
	��� �ý��ۿ� ���ؼ� ����Ǿ����� �� ����
	(1:�߸�, 2:����, 3: ȥ��, 4: �߸�����, 5:�߸�ȥ��, 6:����ȥ��, 7:�߸�����ȥ��)

*/
bool SPGuildArchive::CheckGuildType(int iType)
{
	bool bRet = false ;
	switch(iType)
	{
	case 1:			// �߸�
	case 2:			// ����
	case 3:			// ȥ��
		return ( m_iGuildProperty == iType ) ? true : false ;
		break ;
	case 4:			// �߸�����
		return ( m_iGuildProperty == GUILD_PROPERTY_NORMAL || m_iGuildProperty == GUILD_PROPERTY_ANGEL ) ? true : false ;
		break ;
	case 5:			// �߸�ȥ��
		return ( m_iGuildProperty == GUILD_PROPERTY_NORMAL || m_iGuildProperty == GUILD_PROPERTY_DAEMON ) ? true : false ;
		break ;
	case 6:			// ����ȥ��
		return ( m_iGuildProperty == GUILD_PROPERTY_DAEMON || m_iGuildProperty == GUILD_PROPERTY_ANGEL ) ? true : false ;
		break ;
	case 7:			// �߸�����ȥ��
		return ( m_iGuildProperty != GUILD_PROPERTY_NULL ) ? true : false ;
		break ;
	}
	return false ;
}


/**
	��� �������� üũ
	LDT�� ������ ���� ���ǿ� �´��� üũ�Ѵ�.
	1) ��� ���Կ��� üũ
	2) ������ ���� üũ
	3) ���� �Ӵ� üũ
	@return	GUILD_CREATE_OK				: ����
	@return ERROR_GUILD_CREATE_STAT		: ���� 1 (����)
	@return ERROR_GUILD_CREATE_MONEY	: ���� 2 (�Ӵ�)
	@return ERROR_GUILD_CREATE_ITEM		: ���� 3 (������)
	@return ERROR_GUILD_CREATE_REQ4		: ���� 4
	@return ERROR_GUILD_CREATE_REQ5		: ���� 5
	@return ERROR_GUILD_CREATE_ISHAVE	: �̹� ��� ����
	@return ERROR_GUILD_CREATE_GNAME	: ���� ����
	@return ERROR_GUILD_CREATE_LDT		: LDT Error
*/
int SPGuildArchive::CheckGuildCreate(int iType)
{
	if( GetBasicAvailable() )	return ERROR_GUILD_CREATE_ISHAVE ;

	PGUILD_ATTR pGuildData ;
	int iKey = 10 + iType ;
	pGuildData = g_pkGuildManager->FindGuildAttribute(iKey) ;
	if( pGuildData == NULL )	return ERROR_GUILD_CREATE_LDT ;

	for( int i = 0; i < 5; i++)
	{
		if( false == g_pCheckManager->CheckCondition(pGuildData->stCreateRequire[i].iRequireType
													, pGuildData->stCreateRequire[i].iRequireID
													, pGuildData->stCreateRequire[i].iRequireValue1
													, pGuildData->stCreateRequire[i].iRequireValue2) )
		{
			return i + 1 ;
		}
	}

	return GUILD_CREATE_OK ;
}


/**
	��� ������ üũ
	���� Require üũ�� ���� �׸� üũ ( Master Check �� GuildLevelUp Show���� )
	-> Create_ItemID �� �Ҹ��ϰԵ� : ������ �ش� �������� ��ġ�� ã�Ƽ� TRASH_ITEM �� ä���� ������
	@return ERROR_GUILD_CREATE_STAT		: ���� 1 (NULL)
	@return ERROR_GUILD_CREATE_MONEY	: ���� 2 (GuildLevel)
	@return ERROR_GUILD_CREATE_ITEM		: ���� 3 (������)
	@return ERROR_GUILD_CREATE_REQ4		: ���� 4 (Money)
	@return ERROR_GUILD_CREATE_REQ5		: ���� 5
	@return ERROR_GUILD_POINT			: ��� ����Ʈ ����
*/
int SPGuildArchive::CheckGuildLevelup(int& iRetValue)
{
	PGUILD_ATTR pGuildData ;
	int iKey = (m_iGuildLevel+1) * 10 + m_iGuildProperty ;		// Next Level Check
	pGuildData = g_pkGuildManager->FindGuildAttribute(iKey) ;
	if( pGuildData == NULL )	
		return ERROR_GUILD_CREATE_LDT ;

	for( int i = 0; i < 5; i++)
	{
		if( false == g_pCheckManager->CheckCondition(pGuildData->stCreateRequire[i].iRequireType
			, pGuildData->stCreateRequire[i].iRequireID
			, pGuildData->stCreateRequire[i].iRequireValue1
			, pGuildData->stCreateRequire[i].iRequireValue2) )
		{
			iRetValue = pGuildData->stCreateRequire[i].iRequireValue1;
			return i + 1 ;
		}
	}

	if( SendGuildLevelup(m_iGuildLevel+1, pGuildData->iCreateItemID, pGuildData->iCreateItemCount) == false )
		return ERROR_PKTSEND_FAIL ;

	return GUILD_CREATE_OK ;
}



/**
	��� �ı� ���� üũ
	@return 0 : ����
	@return 1 : ���� �ƴ�
	@return 2 : ������ �ƴ�
*/
int SPGuildArchive::CheckGuildDestroy()
{
	if( !GetBasicAvailable() )			return 1 ;
	if( !IsMaster()	)					return 2 ;
	return 0 ;
}





//////////////////////////////////////////////////////////////////////////
//
//	Packet
//
//////////////////////////////////////////////////////////////////////////
bool SPGuildArchive::SendGuildCreate(int iType, int iEmblem1, int iEmblem2, const char* strGName)
{
	UINT8 byData ;
	UINT8 arrGMark[2] ;
	CPacket packet;
	
	byData		= (UINT8) iType ;
	arrGMark[0] = (UINT8) iEmblem1 ;
	arrGMark[1] = (UINT8) iEmblem2 ;

	packet.AddUINT32( GUILD_CS_CREATE );	
	packet.AddData( strGName, GUILD_MAX_NAME+1);
	packet.AddUINT8( byData ) ;
	packet.AddData( arrGMark, sizeof(BYTE) * 2);

	byData = 1 ;		
	packet.AddUINT8( byData ) ;			// ��� ��ũ
	SENDPACKET(packet) ;

	return true ;
}

/**
	��� �ı��� ���� ��Ŷ�� ������ ������.
	1) ������ ������ �̿ܿ� �ٸ������ ������ ���� -> Ŭ���̾�Ʈ�� ����Ʈ ������ Ȯ�κҰ�
*/
bool SPGuildArchive::SendGuildDestroy()
{
	CPacket packet;
	packet.AddUINT32( GUILD_CS_DESTROY );	

	SENDPACKET(packet) ;
	return true ;
}


/**
	��� �ʴ� ��Ŷ ������
*/
bool SPGuildArchive::SendGuildInvite(const char* szCharName)
{
	if( strlen(szCharName) < MIN_LEN_NAME )		
		return false ;

	// If PVP Zone then Block
	if( g_pkPvpManager->IsPvpZone() )
	{
		char	szMsg[256];
		if( g_pResourceManager->GetGlobalString(51000021) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(51000021));
		else
			wsprintf(szMsg, "[Guild]You can't use it in PVP zone!!");
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMsg);
		return false ;
	}

	// [2007.09.06]for China Request : 2Byte Guild can't invite other user
	if( SPLocalizeManager::GetInstance()->GetCountryType() == CT_CHINA )
	{
		if( m_strGuildName.length() < MIN_LEN_GUILDNAME )
		{
			if( g_pResourceManager->GetGlobalString(27000107) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000107) );
			return false ;
		}
	}
	if( GetBasicAvailable() == false)	
	{
		if( g_pResourceManager->GetGlobalString(27000006) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000006) );
		return false ;
	}
	if( GetInvitable() == false )
	{
		if( g_pResourceManager->GetGlobalString(27000006) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000006) );
		return false ;
	}
	
	CPacket packet;
	packet.AddUINT32( GUILD_CS_REQUEST );	
	packet.AddData( szCharName, LEN_NAME+1);

	SENDPACKET(packet) ;
	return true ;
}

/**
	��� Ż�� ( LocalPlayer���� �޽��� â�� ���� Ȯ���� ��Ŷ ����)
*/
bool SPGuildArchive::SendGuildLeave()
{
	if( GetBasicAvailable() == false)	
	{
		if( g_pResourceManager->GetGlobalString(27000006) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000006) );
		return false ;
	}

	g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_GUILD_SECEDE_ME, 0);
	return true ;
}

// GUILD_CS_RANKUP,
// UINT8			byNewGRank;							// New��巩ũ
// TRASH_ITEM		stConsumeItem;						// �Ҹ�Ǵ¾�����
bool SPGuildArchive::SendGuildLevelup(int iNewLevel, int iItemID, int iItemCount)
{
	CPacket		packet;
	TRASH_ITEM	stConsumeItem;

	SPPlayerInvenArchive* pkInvenArchive = g_pGOBManager->GetLocalPlayer()->GetInvenArchive() ;
	if(pkInvenArchive == NULL)
		return false ;

	if( iItemID > 0 )	{
		SPItem* pSearchItem = pkInvenArchive->GetSPItem(INVENTORY_EVENT, iItemID ) ;
		if( pSearchItem == NULL || pSearchItem->GetSlotIndex() < 0 ) {
			return false ;
		}
		stConsumeItem.iContainerSlot.ContainerType = pSearchItem->GetContainerType() ;
		stConsumeItem.iContainerSlot.SlotIndex = pSearchItem->GetSlotIndex() + 1 ;
		stConsumeItem.iCount = iItemCount ;
	}
	else
	{
		stConsumeItem.iContainerSlot.ContainerType = CONTAINER_TYPE_INVALID ;
		stConsumeItem.iContainerSlot.SlotIndex = 0 ;
		stConsumeItem.iCount = 0 ;
	}

	packet.AddUINT32( GUILD_CS_RANKUP );
	packet.AddUINT8( iNewLevel );
	packet.AddData( &stConsumeItem, sizeof(TRASH_ITEM));

	SENDPACKET(packet) ;
	return true ;
}




// GUILD_CS_CHANGEMARK,
// UINT32			uiGMarkID;							// ��帶ũLDT���̵�
// TRASH_ITEM		stConsumeItem;						// �Ҹ�Ǵ¾�����
bool SPGuildArchive::SendGuildEmblemChange(int iEmblemID, int iItemID, int iItemCount)
{
	CPacket		packet;
	TRASH_ITEM	stConsumeItem;

	SPPlayerInvenArchive* pkInvenArchive = g_pGOBManager->GetLocalPlayer()->GetInvenArchive() ;
	if(pkInvenArchive == NULL)
		return false ;

	if( iItemID > 0 )	{
		SPItem* pSearchItem = pkInvenArchive->GetSPItem(INVENTORY_EVENT, iItemID ) ;
		if( pSearchItem == NULL || pSearchItem->GetSlotIndex() < 0 ) {
			return false ;
		}
		stConsumeItem.iContainerSlot.ContainerType = pSearchItem->GetContainerType() ;
		stConsumeItem.iContainerSlot.SlotIndex = pSearchItem->GetSlotIndex() + 1 ;
		stConsumeItem.iCount = iItemCount ;
	}
	else
	{
		stConsumeItem.iContainerSlot.ContainerType = CONTAINER_TYPE_INVALID ;
		stConsumeItem.iContainerSlot.SlotIndex = 0 ;
		stConsumeItem.iCount = 0 ;
	}

	packet.AddUINT32( GUILD_CS_CHANGEMARK );
	packet.AddUINT32( iEmblemID );
	packet.AddData( &stConsumeItem, sizeof(TRASH_ITEM));

	SENDPACKET(packet) ;
	return true ;
}


/**
	��� �߰� ���� ��û ��Ŷ (��� ����, ���ΰ�)
*/
bool SPGuildArchive::SendGuildCommonInfo()
{
	DeleteCommonInfo() ;

	CPacket packet;
	packet.AddUINT32( GUILD_CS_GUILD_COMMON );	

	SENDPACKET(packet) ;
	return true ;
}






//////////////////////////////////////////////////////////////////////////
//
//	Crop
//
//////////////////////////////////////////////////////////////////////////

/**
	[���� �ɱ�] ��Ŷ
*/
bool SPGuildArchive::SendCropRegist(UINT32 iCropID, TRASH_ITEM stConsumeItem)
{
	CPacket packet;
	packet.AddUINT32( GUILD_CS_PLANT );	
	packet.AddUINT32( iCropID );
	packet.AddData(&stConsumeItem, sizeof(TRASH_ITEM));
	(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
	return true ;
}


/**
	[���/������ �ֱ�]
*/
bool SPGuildArchive::SendCropNourish(UINT32 iBoosterID, TRASH_ITEM stConsumeItem)
{
	CPacket packet;
	packet.AddUINT32( GUILD_CS_NOURISH );	
	packet.AddUINT32( iBoosterID );
	packet.AddData(&stConsumeItem, sizeof(TRASH_ITEM));
	(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
	return true ;
}

/**
	[��� ���� ����]
*/
bool SPGuildArchive::SendCropEliminate()
{
	CPacket packet;
	packet.AddUINT32( GUILD_CS_GRUB );	
	(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
	return true ;
}



/**
	���� �ɱ�
	return int 0 : ����
	return int 1 : CropItem �� ã�� ���� (�ٸ� ������)
	return int 2 : Require 1
	return int 3 : Require 2
	return int 4 : Require 3
*/
int SPGuildArchive::UseCropItem(SPItem* pItem)
{
	TRASH_ITEM stConsumeItem ;
	CROP_INFO* pCrop = NULL ;
	if( g_pkGuildManager->FindCropInfobyConsumeID(pItem->GetItemStatus()->GetItemID(), pCrop) )
	{
		stConsumeItem.iContainerSlot.ContainerType = pItem->GetContainerType() ;
		stConsumeItem.iContainerSlot.SlotIndex = pItem->GetSlotIndex() + 1 ;	// Server�� 1Base
		stConsumeItem.iCount = 1 ;
		// Require Check
		for( int i = 0; i < CROP_REQUIRE_MAX; i++)
		{
			if( false == g_pCheckManager->CheckCondition(pCrop->stRequire[i].iRequireType
				, pCrop->stRequire[i].iRequireID
				, pCrop->stRequire[i].iRequireValue1
				, pCrop->stRequire[i].iRequireValue2) )
			{
				return i+2 ;
			}
		}
		SendCropRegist(pCrop->iItemID, stConsumeItem) ;
		return 0 ;
	}
	return 1 ;
}

/**
	��ᳪ ������ �������� Drag&Drop �Ǵ� ��� ó��
	@param iType  1:���, 2:������
	@return 0 : ����
	@return 1 : �ٸ� ������
	@return 2 : Ÿ���� �ٸ� (��� != ������)
	@return 3 : Timeless
*/
int SPGuildArchive::UseNourishItem(int iUseType, SPItem* pItem)
{
	TRASH_ITEM stConsumeItem ;
	BOOSTER_INFO* pUseBooster = NULL ;
	if( g_pkGuildManager->FindBoosterInfobyItem(pItem->GetItemStatus()->GetItemID(), pUseBooster) )
	{
		if( iUseType != pUseBooster->iType )
			return 2 ;
		if( m_pCropArchive->CheckAddBoosterTime(pUseBooster->iType, pUseBooster->iCalcTime) == true )
		{
			stConsumeItem.iContainerSlot.ContainerType = pItem->GetContainerType() ;
			stConsumeItem.iContainerSlot.SlotIndex = pItem->GetSlotIndex() + 1 ;	// Server�� 1Base
			stConsumeItem.iCount = 1 ;

			SendCropNourish(pUseBooster->lItemID, stConsumeItem) ;
			return 0 ;
		}
		return 3 ;
	}
	return 1 ;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Update
//
//////////////////////////////////////////////////////////////////////////
bool SPGuildArchive::ChangeSlogun(int iMode, const char* strSlogun)
{
	if( iMode == 0 )	// Send
	{
		m_strSendSlogun = strSlogun ;
		CPacket packet;
		packet.AddUINT32( GUILD_CS_UPDATE_SLOGAN );	
		packet.AddData( strSlogun, GUILD_MAX_SLOGAN+1);
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
	}
	else				// Recv
	{
		m_strGuildSlogun = m_strSendSlogun ;
		m_strSendSlogun.clear() ;
		//g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000024) );
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_REFRESH_COMMON, 0, 0);
	}
	return true ;
}


/**
	�ʴ뿡 ���� ����� �̸� ����
*/
bool SPGuildArchive::SetInviteName(const char* szRequestName)
{
	// 3����Ʈ���� 2����Ʈ�� ����. �Ϻ� ��û���� [8/20/2007 AJJIYA]
	if( strlen(szRequestName) < MIN_LEN_NAME)		return false ;
	m_strRequestName = szRequestName ;
	return true ;
}
void SPGuildArchive::ClearInviteName()
{
	m_strRequestName.clear() ;
}
const char* SPGuildArchive::GetInviteName()
{
	return m_strRequestName.c_str() ;
}

/**
	Guild ���� Grade�� ������Ʈ
*/
bool SPGuildArchive::UpdateMyGrade(int iGrade)
{
	if( iGrade < GUILD_GRADE_01 || iGrade > _MAX_GUILD_GRADE-1 )
		return false ;
	m_iGuildGrade = iGrade ;
	SetGuildAuthority(m_iGuildGrade) ;
	//�����λ�ı�
	if ( g_pCIGWLoaderDx9 )
	{
		TCHAR GuildGradeNew[10];
		sprintf( GuildGradeNew, "%d", m_iGuildGrade );
		g_pCIGWLoaderDx9->OnCommunityEventA( ceSetGuildTitle, GuildGradeNew );
	}
	return true ;
}


/**
	GuildEmblem ������Ʈ
*/
bool SPGuildArchive::UpdateMyEmblem(int iGMark1, int iGMark2, int iGMark3)
{
	int iChangeLayer = 0 ;
	GUILD_BROADCAST		stGuildBroad ;
	if( m_iGuildEmblem[0] != iGMark1 )	{
		iChangeLayer = 0 ;
		m_iGuildEmblem[0] = iGMark1 ;
	}
	if( m_iGuildEmblem[1] != iGMark2 )	{
		iChangeLayer = 1 ;
		m_iGuildEmblem[1] = iGMark2 ;
	}
	if( m_iGuildEmblem[2] != iGMark3 )	{
		iChangeLayer = 2 ;
		m_iGuildEmblem[2] = iGMark3 ;
	}

	stGuildBroad.arrGMark[0] = m_iGuildEmblem[0] ;
	stGuildBroad.arrGMark[1] = m_iGuildEmblem[1] ;
	stGuildBroad.arrGMark[2] = m_iGuildEmblem[2] ;
	stGuildBroad.byGRank = (UINT8)GetGuildLevel() ;
	stGuildBroad.byGType = (UINT8)GetGuildProperty() ;
	stGuildBroad.iGNum = m_iGuildID ;
	strcpy(stGuildBroad.szGName, GetGuildName()) ;

	g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)&stGuildBroad);
	g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_EMBLEM, SPIM_GUILD_EM_CHANGE_RESULT, iChangeLayer, 0);
	return true ;
}



//////////////////////////////////////////////////////////////////////////
//
//	Packet Receive Process
//	
//////////////////////////////////////////////////////////////////////////
/**
	PPCGUILD : BROADCAST �� COMMON�� �Բ� �´�.
	GameConnect, GuildCreate, GuildJoin�ÿ� ����.
*/
void SPGuildArchive::SetGuildBasicInfo(PPCGUILD pPCGuild)
{
	if( SPLocalizeManager::GetInstance()->IsEnableValue(LV_GUILD) )	{
		SetEnableBasicInfo( SetBasicInfo(pPCGuild->iGNum, pPCGuild->arrGMark[0], pPCGuild->arrGMark[1], pPCGuild->arrGMark[2], pPCGuild->byGrade, pPCGuild->byGType, pPCGuild->byGRank, pPCGuild->szGName, pPCGuild->iPoint) ) ;
		SetCropInformation(CROP_SET_DATA, pPCGuild->uiCropID, pPCGuild->uiRemainTime, pPCGuild->uiNourishTime, pPCGuild->uiHastenSumTime ) ;
	}
}


void SPGuildArchive::SetGuildCommonInfo(PGUILD_COMMON pPCGuild)
{
	if( SPLocalizeManager::GetInstance()->IsEnableValue(LV_GUILD) )	{
		SetProperty(pPCGuild->szGSlogan) ;
		if( g_pInterfaceManager->GetGuildInfoWindow()->IsShow() )
			g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_REFRESH_COMMON, 0, 0);
	}
	SetCropInformation(CROP_SET_DATA, pPCGuild->uiCropID, pPCGuild->uiRemainTime, pPCGuild->uiNourishTime, pPCGuild->uiHastenSumTime ) ;	// Set
}





