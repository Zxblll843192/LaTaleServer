// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionManager.cpp
//	created:	2008/2/26   Time:11:00
//	purpose:	
//*********************************************************************/

#include "SPCommon.h"
#include "SPUtil.h"
#include "PacketID.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"
#include "SockWnd.h"
#include "SPNetworkManager.h"

#include "SPLDTFile.h"
#include "SPLDTManager.h"
#include "SPResourceDef.h"
#include "SPResourceManager.h"

#include "SPItem.h"
#include "SPItemAttr.h"
#include "SPItemStatus.h"
#include "SPItemCluster.h"

#include "SPCommandConvert.h"
#include "SPGOBStatus.h"
#include "SPGOBManager.h"
#include "SPGOBCoordPhysics.h"
#include "SPGameObject.h"
#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPPlayerInvenArchive.h"
#include "SPPlayer.h"

#include "SPRenderModelDEF.h"
#include "SPRenderModel.h"

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"

#include "SPWindow.h"
#include "SPLocalizeManager.h"
#include "GlobalDefines_Share.h"

#include "SPAuctionDef.h"
#include "SPAuctionAttr.h"
#include "SPAuctionArchive.h"
//#include "SPAuctionMock.h"
#include "SPAuctionManager.h"
#include "GlobalDefines_Share.h"

#include "_Error_log.h"





SPAuctionManager* g_pkAuctionManager = NULL;
SPAuctionManager* SPAuctionManager::m_pkInstance = NULL;
//------------------------------------------------------------------------------------
SPAuctionManager* SPAuctionManager::GetInstance()
{
	if( m_pkInstance == NULL )
	{
		m_pkInstance = new SPAuctionManager;
		g_pkAuctionManager = m_pkInstance;
	}

	return m_pkInstance;
}

//------------------------------------------------------------------------------------
void SPAuctionManager::Release()
{
	if( m_pkInstance )
	{
		g_pkAuctionManager = NULL; 

		delete m_pkInstance;
		m_pkInstance = NULL;
	}
}

//------------------------------------------------------------------------------------
SPAuctionManager::SPAuctionManager()
: m_pSearchArchive(NULL)
, m_pBuyArchive(NULL)
, m_pSaleArchive(NULL)
, m_bOpen(true)
, m_bTest(false)
{
}

//------------------------------------------------------------------------------------
SPAuctionManager::~SPAuctionManager()
{
	Clear();
}

//------------------------------------------------------------------------------------
void SPAuctionManager::Clear()
{
	for( int i = 0; i < 5; i++ )	{
		SAFE_DELETE( m_ctAuactionType[i] ) ;
	}
	SAFE_DELETE( m_pSearchArchive) ;
	SAFE_DELETE( m_pBuyArchive) ;
	SAFE_DELETE( m_pSaleArchive) ;
}

//------------------------------------------------------------------------------------
bool SPAuctionManager::Init()
{
	m_iAuctionTypeCount = 0 ;
	m_bOpen = true ;
	m_iSearch = 0 ;
	m_iSysAuctionMoneyID	= 0 ;	// GlobalSys�� ������
	m_iSysGamePriceID		= 0 ;	// GlobalSys�� ������
	m_iSysStandardPriceID	= 0 ;	// GlobalSys�� ������
	m_iSysStartMoneyID		= 0 ;	// GlobalSys�� ������(���۰�)

	m_pSearchArchive	= new SPAuctionArchive ;
	m_pSearchArchive->SetAuctionList(AUCTION_ARCH_PART, 6) ;
	m_pBuyArchive		= new SPAuctionArchive ;
	m_pBuyArchive->SetAuctionList(AUCTION_ARCH_ALL, 7) ;
	m_pSaleArchive		= new SPAuctionArchive ;
	m_pSaleArchive->SetAuctionList(AUCTION_ARCH_ALL, 7) ;

	LoadAuctionTypeLDT() ;

	return true ;
}

//------------------------------------------------------------------------------------

/**
	�Ǹ����� ���� AUCTION_TYPE.LDT Load
*/
bool SPAuctionManager::LoadAuctionTypeLDT()
{
	int i ;

	// LDT Struct �ʱ�ȭ
	for( i = 0; i < 5; i++ )	{
		m_ctAuactionType[i] = new AUCTION_TYPE_INFO ;
		m_ctAuactionType[i]->Clear() ;
	}

	std::string strLDTFile;
	strLDTFile = "DATA/LDT/AUCTION_TYPE.LDT";

	SPLDTFile* pkLDTFile = NULL;
	if( !g_pResourceManager->GetLDTFromFileName(strLDTFile.c_str(), &pkLDTFile) )
	{
		ErrorFLogs->Error_Log("Can't Find AUCTION_TYPE.LDT[%s]", strLDTFile.c_str()) ;
		return false;
	}

	int iDataNum;
	int iIndex = 0 ;
	long lItemID;
	int iCategoryIndex = 0 ;

	LDT_Field Field;
	iDataNum = pkLDTFile->GetItemCount();
	m_iAuctionTypeCount = iDataNum ;
	for( i = 0; i < iDataNum; i++ )
	{
		lItemID = pkLDTFile->GetPrimaryKey(i);

		Field.Init() ;					// �Ǹ�����
		pkLDTFile->GetField(lItemID, 0, Field);
		m_ctAuactionType[iIndex]->iSaleType = (AUCTION_TYPE)Field.uData.lValue ;

		// ���� �����ʹ� �ȵǹǷ� �߸��� �����ʹ� ��ŵ
		if( m_ctAuactionType[iIndex]->iSaleType <= AUCTION_TYPE_NULL )
			continue ;

		Field.Init() ;					// ��Ϻ� �������
		pkLDTFile->GetField(lItemID, 1, Field);
		m_ctAuactionType[iIndex]->bRegistCharge = Field.uData.lValue ? true : false ;
		Field.Init() ;					// ��Ϻ� �Һ������
		pkLDTFile->GetField(lItemID, 2, Field);
		m_ctAuactionType[iIndex]->iConsumeItem = Field.uData.lValue;
		Field.Init() ;					// �ܱ� ��Ϻ� ����
		pkLDTFile->GetField(lItemID, 3, Field);
		m_ctAuactionType[iIndex]->iShortRate = Field.uData.lValue ;
		Field.Init() ;					// �߱� ��Ϻ� ����
		pkLDTFile->GetField(lItemID, 4, Field);
		m_ctAuactionType[iIndex]->iMiddleRate = Field.uData.lValue ;
		Field.Init() ;					// ��� ��Ϻ� ����
		pkLDTFile->GetField(lItemID, 5, Field);
		m_ctAuactionType[iIndex]->iLongRate = Field.uData.lValue ;
		++iIndex ;

	}
	SAFE_RELEASE(pkLDTFile) ;

	//////////////////////////////////////////////////////////////////////////
	// Auction ������, ���۰��� ���� Global_sys.ldt �б�	
	g_pResourceManager->GetLDTFromFileName( RES_FNAME_LDT_GLOBAL_SYS , &pkLDTFile );
	if( pkLDTFile == NULL )
	{
		return false ;
	}

	Field.Init() ;
	pkLDTFile->GetField( 91 , 0 ,	Field );		//	Auction Money ID
	m_iSysAuctionMoneyID	=	Field.uData.lValue;

	Field.Init() ;
	pkLDTFile->GetField( 92 , 0 ,	Field );		//	m_iSysGamePriceID
	m_iSysGamePriceID	=	Field.uData.lValue;

	Field.Init() ;
	pkLDTFile->GetField( 93 , 0 ,	Field );		//	m_iSysStandardPriceID
	m_iSysStandardPriceID	=	Field.uData.lValue;

	Field.Init() ;
	pkLDTFile->GetField( 94 , 0 ,	Field );		//	m_iSysStartMoneyID
	m_iSysStartMoneyID	=	Field.uData.lValue;
	SAFE_RELEASE(pkLDTFile) ;

	return true ;
}

//////////////////////////////////////////////////////////////////////////
//	Localize�� ���� �о���� ������ ����
/**
	[������ ����]
*/
int	SPAuctionManager::GetAuctionFeeRate()
{
	return SPLocalizeManager::GetInstance()->GetAuctionFeeRate() ;
}
/**
	[�ܱ�] �ð� ����
*/
int	SPAuctionManager::GetAuctionTimeShort()
{
	return SPLocalizeManager::GetInstance()->GetAuctionTimeShort() ;
}
/**
	[�߱�]�ð� ����
*/
int	SPAuctionManager::GetAuctionTimeMiddle()
{
	return SPLocalizeManager::GetInstance()->GetAuctionTimeMiddle() ;
}
/**
	[�����]�ð� ����
*/
int	SPAuctionManager::GetAuctionTimeLong()
{
	return SPLocalizeManager::GetInstance()->GetAuctionTimeLong() ;
}

/**
	Global_Sys.LDT���� ���� ������
 */
int	SPAuctionManager::GetSysMoneyID()
{
	return m_iSysAuctionMoneyID ;
}
int	SPAuctionManager::GetSysGamePriceID()
{
	return m_iSysGamePriceID ;
}
int	SPAuctionManager::GetSysStandardPriceID()
{
	return m_iSysStandardPriceID ;
}
int	SPAuctionManager::GetSysStartMoneyID()
{
	return m_iSysStartMoneyID ;
}


//---------------------------------------------------------------------
/**
	Player Money����
 */
INT64 SPAuctionManager::GetPlayerEly()
{
	SPPlayer* pLocalPlayer = g_pGOBManager->GetLocalPlayer() ;
	if( pLocalPlayer ) 
		return pLocalPlayer->GetCheckStatusValue(CHECK_STATUS_MONEY) ;

	return 0 ;
}

int	SPAuctionManager::GetPlayerCash()
{
	SPPlayer* pLocalPlayer = g_pGOBManager->GetLocalPlayer() ;
	if( pLocalPlayer ) 
		return pLocalPlayer->GetStatus()->GetStatusValue(STATUS_CASH) ;

	return 0 ;
}

int	SPAuctionManager::GetPlayerMilige()
{
	SPPlayer* pLocalPlayer = g_pGOBManager->GetLocalPlayer() ;
	if( pLocalPlayer )
		return pLocalPlayer->GetStatus()->GetStatusValue(STATUS_MILE) ;

	return 0 ;
}


void SPAuctionManager::UpdatePlayerEly(INT64 iEly)
{
	SPPlayer* pLocalPlayer = g_pGOBManager->GetLocalPlayer() ;
	if( pLocalPlayer )	{
		pLocalPlayer->GetStatus()->SetStatusValueEX(STATUS_EX_ELY, iEly) ;
	}
}

void SPAuctionManager::UpdatePlayerCash(int iCash, int iMilige)
{
	SPPlayer* pLocalPlayer = g_pGOBManager->GetLocalPlayer() ;
	if( pLocalPlayer )	{
		pLocalPlayer->GetStatus()->SetStatusValue(STATUS_CASH, iCash) ;
		pLocalPlayer->GetStatus()->SetStatusValue(STATUS_MILE, iMilige) ;
	}
}

//------------------------------------------------------------------------------------
void SPAuctionManager::Process(float fTime)
{
}


/**
	������ ��� Ÿ�Կ� ���� ������ �д´�.
*/
AUCTION_TYPE_INFO*	SPAuctionManager::GetAuctionTypeInfo(int iAuctionTypeID)
{
	for( int i = 0; i < m_iAuctionTypeCount ; i++ )
	{
		if( m_ctAuactionType[i]->iSaleType == iAuctionTypeID )
		{
			return m_ctAuactionType[i] ;
		}
	}
	return NULL ;
}

/**
	index�� ���ؼ� ������ TypeID�� ���´�.
	@param int iIndex : 1BASE Index
 */
int SPAuctionManager::GetAuctionTypeID(int iIndex)
{
	if( m_iAuctionTypeCount < iIndex || iIndex <= 0 )
		return 0 ;
	return m_ctAuactionType[iIndex-1]->iSaleType ;
}

int	SPAuctionManager::GetAuctionTypeCount()
{
	return m_iAuctionTypeCount ;
}


/**
	Auction�� ���� Valid üũ
	1) ���۰�, ��Ϻ���� ���� Global_Sys üũ 
 */
bool SPAuctionManager::CheckAuctionValid()
{
	if( m_iSysAuctionMoneyID < MIN_AUCTION_STARTPRICE_FACTOR || m_iSysAuctionMoneyID > MAX_AUCTION_STARTPRICE_FACTOR )	{
		return false ;
	}
	if( m_iSysGamePriceID < MIN_AUCTION_GAMEPRICE_FACTOR || m_iSysGamePriceID > MAX_AUCTION_GAMEPRICE_FACTOR )	{
		return false ;
	}
	if( m_iSysStandardPriceID < MIN_AUCTION_STANDARDPRICE_FACTOR || m_iSysStandardPriceID > MAX_AUCTION_STANDARDPRICE_FACTOR )	{
		return false ;
	}
	return true ;
}


/**
	Archive Reset ���� Ȯ��
	NeedReset�� ��� ������ ����Ʈ ��û
 */
bool SPAuctionManager::CheckArchiveReset(int iTab)
{
	if( iTab == 1 )			// Buy
	{
		return m_pBuyArchive->GetNeedReset() ;
	}
	else if( iTab == 2 )	// Sale
	{
		return m_pSaleArchive->GetNeedReset() ;
	}
	return false ;
}


/**
	Player����� Auction Reset
 */
void SPAuctionManager::SetAuctionReset()
{
	m_bOpen = true ;
	m_pSearchArchive->ClearList() ;
	m_pBuyArchive->ClearList() ;
	m_pBuyArchive->SetNeedReset(true) ;
	m_pSaleArchive->ClearList() ;
	m_pSaleArchive->SetNeedReset(true) ;
}

/**
	Server Down or Open �� ���� ����
 */
void SPAuctionManager::SetServerOpen(bool bOpen)
{
	m_bOpen = bOpen ;
}

bool SPAuctionManager::GetServerOpen()
{
	return m_bOpen ;
}


//////////////////////////////////////////////////////////////////////////
// Archive
SPAuctionArchive*	SPAuctionManager::GetAuctionSearchArchive()
{
	return m_pSearchArchive ;
}
SPAuctionArchive*	SPAuctionManager::GetAuctionBuyArchive()
{
	return m_pBuyArchive ;
}
SPAuctionArchive*	SPAuctionManager::GetAuctionSaleArchive()
{
	return m_pSaleArchive ;
}

/**
	Archive List�� ��� ������ �⺻ Sort�� ���ֵ��� �Ѵ�.
	Archive Sort Reset (0:Buy, 1:Sale)
	����Ʈ�� ��� �������� Sort�� �ϰ� List�� ������Ʈ �Ѵ�.
 */
void	SPAuctionManager::SetDefaultSort(int iArchiveType)
{
	SPWindow* pWindowAuction = g_pInterfaceManager->GetAuctionWindow() ;
	if( iArchiveType == 0 )	{
		m_pBuyArchive->SetDefaultSort(true) ;
		if(pWindowAuction && pWindowAuction->IsShow()) {
			
			pWindowAuction->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
		}
	}
	else	{
		m_pSaleArchive->SetDefaultSort(true) ;
		if(pWindowAuction && pWindowAuction->IsShow()) {
			pWindowAuction->SPSendMessage(SPIM_AUCTION_SALE_LIST, (WPARAM)0, (LPARAM)0);
		}
	}
}


/**
	Finish�� ���� ��Ȳ�ϰ��, Auction Archive�� �����͸� ������ �������θ� �˷��ش�.
	�ڽ��� ���ۿ� ���Ѱ�� SearchArchive�� �����ϰ�, Ÿ�ο� ���Ѱ�� ���� �ʴ´�.
	@param INT64 iAuctionID : ã�� AuctionID
	@param bool bSearch : SearchArchive�� ��������
	@return int : Update Count
*/
int SPAuctionManager::UpdateAuctionFinish(INT64 iAuctionID, bool bSearch)
{
	int iRet = 0 ;
	SPAuctionAttr* pAttr = NULL ;
	if( iAuctionID < 0 )
		return 0 ;

	if( bSearch )	{
		if( m_pSearchArchive->DeleteAuctionItem(iAuctionID, true) )
			++iRet ;
	}
	if( m_pBuyArchive->DeleteAuctionItem(iAuctionID, true) )
		++iRet ;
	if( m_pSaleArchive->DeleteAuctionItem(iAuctionID, true)  )
		++iRet ;
	return iRet ;
}


/**
	��� ��� ��� (��Ϻ���� Ely, AUCTION_TYPE.LDT �������� ó��)
	AUCTION_TYPE_ITEM_BY_ELY : Auction_Enrol = [{(Item_Lv*1.5)+(Item_Quilty*5)*(���۰�*0.2)+(������*10)}/2] * �Ⱓ����
	AUCTION_TYPE_ELY_BY_CASH : ����
	AUCTION_TYPE_CASH_BY_ELY : Auction_Enrol = {(Cash_money*30)+(���۰�*0.2)} * �Ⱓ����
	AUCTION_TYPE_ELY_BY_MILEAGE : ����
	AUCTION_TYPE_MILEAGE_BY_ELY : Auction_Enrol = {(Mile_Money*25)*(���۰�*0..2)} * �Ⱓ����
*/
INT64 SPAuctionManager::ComputeEnrolFee(AUCTION_TYPE eType, INT64 iStart, int iDuration, int iValue, int iLv/*=0*/, int iGamePrice/*=0*/, int iItemCount/*=0*/)
{
	AUCTION_TYPE_INFO* pTypeInfo = NULL ;
	INT64 iRetFee = 0 ;
	INT64 iEnrolFee = 0 ;

	pTypeInfo = GetAuctionTypeInfo(eType) ;
	if( pTypeInfo == NULL )	{
		ErrorFLogs->Error_Log("Can't Find Auction type info [%d]", eType) ;
		return -1 ;
	}

	if( pTypeInfo->bRegistCharge == false )		// ��Ϻ���� ���õ��� ���� ���
		return 0 ;

	INT64 iItemFee = 0 ;
	INT64 iStandFee = 0 ;
	switch(eType)
	{
	case AUCTION_TYPE_ITEM_BY_ELY:			// �Ǹ� : ������,	���ż��� : Ely
		// Auction_Enrol = [{(Item_Lv*1.5)+(Item_Quilty*5)+(Auction_Money*0.2)+(������*10)}/40]
		// iEnrolFee = (INT64)( ((float)iLv*1.5f + (iQuality*5) + iStart*0.2f + iDurability*10 ) / 40 + 0.5f ) ;
		iItemFee = (INT64)GET_AUCTION_ENROLFEE_ITEM(iStart, m_iSysAuctionMoneyID, iGamePrice, m_iSysGamePriceID, iItemCount) ;
		iStandFee = (INT64)GET_AUCTION_ENROLFEE_ITEM_STANDARD(iLv, m_iSysStandardPriceID) ;
		iEnrolFee = (INT64)max( iItemFee, iStandFee ) ;
		break ;
	case AUCTION_TYPE_CASH_BY_ELY:			// �Ǹ� : Cash,		���ż��� : Ely
		// Auction_Enrol = {(Cash_money*30)+(���۰�*0.2)}/2
		// iEnrolFee = (INT64)( (iValue*30 + (float)iStart*0.2f) /2 + 0.5f ) ;
		iEnrolFee = (INT64)GET_AUCTION_ENROLFEE_CASH(iStart,  iValue) ;
		break ;
	case AUCTION_TYPE_MILEAGE_BY_ELY:		// �Ǹ� : Mileage,	���ż��� : Ely
		// Auction_Enrol = {(Mile_Money*25)+(���۰�*0.2)}/2
		// iEnrolFee = (INT64)( (iValue*25 + (float)iStart*0.2f) /2 + 0.5f ) ;
		iEnrolFee = (INT64)GET_AUCTION_ENROLFEE_MILE(iStart,  iValue) ;
		break ;
	case AUCTION_TYPE_ELY_BY_CASH:			// �Ǹ� : Ely,		���ż��� : Cash
	case AUCTION_TYPE_ELY_BY_MILEAGE:		// �Ǹ� : Ely,		���ż��� : Mileage
		// Auction_Enrol = {(Game_Money*0.05)+(���۰�*2)}/2
		// iEnrolFee = (INT64)( ((float)iValue*0.05f + iStart*2) /2 + 0.5f ) ;
		iEnrolFee = (INT64)GET_AUCTION_ENROLFEE_ELY(iStart,  iValue) ;
		break ;
	}
	// ���� ��Ϻ�� = Auction_Enrol + (Auction_Enrol*Auction_Time*0.01)		//pTypeInfo->GetPeriodRate(iDuration) 
	// iRetFee = (INT64)(iEnrolFee + (iEnrolFee * pTypeInfo->GetPeriodRate(iDuration) * 0.01f) + 0.5f ) ;
	iRetFee = (INT64)GET_AUCTION_ENROLFEE(iEnrolFee, pTypeInfo->GetPeriodRate(iDuration)) ;
	return iRetFee ;
}

//------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
// Send Packet
/**
	Auction Search
	@param int iCategory	: Category Key
	@param int iLvMin	: �ּҷ���
	@param int iLvMax	: �ִ뷹��
	@param int iQuality	: ǰ��
	@param const char* szText= NULL: �˻� �̸�
*/
void	SPAuctionManager::SendAuctionSearch(AUCTION_SEARCH_KEY* pSearchKey)
{
	AUCTION_SORT_KEY eSortKey ;
	int iSortAscend ;
	CPacket packet;

	m_pSearchArchive->GetLatestSortKey(eSortKey, iSortAscend) ;

	packet.AddUINT32( AUCTION_CS_SEARCH );	
	packet.AddUINT32( pSearchKey->iCategoryID );	
	packet.AddUINT8( eSortKey );
	packet.AddUINT8( iSortAscend );
	if( CHECK_AUCTION_ITEM_CATEGORY(pSearchKey->iCategoryID))
	{
		packet.AddData(pSearchKey->szName, MAX_ITEM_NAME) ;
		packet.AddUINT16(pSearchKey->iMinLevel) ;
		packet.AddUINT16(pSearchKey->iMaxLevel) ;
		packet.AddUINT8(pSearchKey->iQuality) ;
	}
	else
	{
		packet.AddUINT32(pSearchKey->iMoneyMin) ;
		packet.AddUINT32(pSearchKey->iMoneyMax) ;
	}

	m_iSearch = 1;
	SENDPACKET(packet);
}


/**
	Auction Search ���� ������ �����ö�
	@param int iCategory	: Category Key
	@param int iWantIndex	: ���ϴ� ���� Index
	@param int iLvMin	: �ּҷ���
	@param int iLvMax	: �ִ뷹��
	@param int iQuality	: ǰ��
	@param const char* szText= NULL: �˻� �̸�
*/
void	SPAuctionManager::SendAuctionSearchNext(int iWantIndex, AUCTION_SEARCH_KEY* pSearchKey)
{
	AUCTION_SORT_KEY eSortKey ;
	int iSortAscend ;
	CPacket packet;

	m_pSearchArchive->GetLatestSortKey(eSortKey, iSortAscend) ;

	packet.AddUINT32( AUCTION_CS_GETNEXT );	
	packet.AddUINT32( iWantIndex );	
	packet.AddUINT32( pSearchKey->iCategoryID );	
	packet.AddUINT8( eSortKey );
	packet.AddUINT8( iSortAscend );
	if( CHECK_AUCTION_ITEM_CATEGORY(pSearchKey->iCategoryID) )
	{
		packet.AddData(pSearchKey->szName, MAX_ITEM_NAME) ;
		packet.AddUINT16(pSearchKey->iMinLevel) ;
		packet.AddUINT16(pSearchKey->iMaxLevel) ;
		packet.AddUINT8(pSearchKey->iQuality) ;
	}
	else 
	{
		packet.AddUINT32(pSearchKey->iMoneyMin) ;
		packet.AddUINT32(pSearchKey->iMoneyMax) ;
	}

	m_iSearch = 0;
	SENDPACKET(packet);
}


/**
	Search ���� Sort�� �ϴ� ��� : ������ ù�������� ����. 
	@param int iCategory	: Category Key
	@param int iLvMin	: �ּҷ���
	@param int iLvMax	: �ִ뷹��
	@param int iQuality	: ǰ��
	@param const char* szText= NULL: �˻� �̸�
*/
void	SPAuctionManager::SendAuctionSearchSort(AUCTION_SEARCH_KEY* pSearchKey)
{
	AUCTION_SORT_KEY eSortKey ;
	int iSortAscend ;
	CPacket packet;

	m_pSearchArchive->GetLatestSortKey(eSortKey, iSortAscend) ;

	packet.AddUINT32( AUCTION_CS_SORTING );	
	packet.AddUINT32( pSearchKey->iCategoryID );	
	packet.AddUINT8( eSortKey );
	packet.AddUINT8( iSortAscend );
	if( CHECK_AUCTION_ITEM_CATEGORY(pSearchKey->iCategoryID) )
	{
		packet.AddData(pSearchKey->szName, MAX_ITEM_NAME) ;
		packet.AddUINT16(pSearchKey->iMinLevel) ;
		packet.AddUINT16(pSearchKey->iMaxLevel) ;
		packet.AddUINT8(pSearchKey->iQuality) ;
	}
	else 	
	{
		packet.AddUINT32(pSearchKey->iMoneyMin) ;
		packet.AddUINT32(pSearchKey->iMoneyMax) ;
	}

	m_iSearch = 2;		// Sort�� ��쿡�� SearchList�� �ʱ�ȭ �Ǿ����(Page����)
	SENDPACKET(packet);
}




/**
	[���� ��Ȳ] ��û
*/
void	SPAuctionManager::SendAuctionBuyRequest()
{
	m_pBuyArchive->ClearList() ;
	m_pBuyArchive->SetNeedReset(false) ;

	CPacket packet;
	packet.AddUINT32( AUCTION_CS_INFO_4BIDDER );

	SENDPACKET(packet);
}


/**
	[����ϱ�] ��û
*/
void	SPAuctionManager::SendAuctionSaleRequest()
{
	m_pSaleArchive->ClearList() ;
	m_pSaleArchive->SetNeedReset(false) ;

	CPacket packet;
	packet.AddUINT32( AUCTION_CS_INFO_4SELLER );	

	SENDPACKET(packet);
}



/**
	����
	@param int iSelectedTab
	@param INT64 iAuctionID
	@param INT64 iBidPrice	: �ﱸ�� ��� �ﱸ���� �Է�(�ﱸ���� ������ �ﱸ�� ó���ȴٰ���)
*/
void	SPAuctionManager::SendAuctionBidBuy(SPAuctionAttr* pAuctionAttr)
{
	CPacket packet;
	packet.AddUINT32( AUCTION_CS_BID );	
	packet.AddUINT64( pAuctionAttr->GetAuctionID() );
	packet.AddUINT32( pAuctionAttr->GetCategory() ) ;
	packet.AddUINT64( pAuctionAttr->GetNextBidPrice() );	

	SENDPACKET(packet);
}


/**
	��ñ��� ��û
	:: �ﱸ�ÿ��� SearchList�� �˻��ؼ� ���� �ﱸ�� ���� �ִ°��� �ִ��� Ȯ���ؾ� �Ѵ�.
	@param AUCTION_SEARCH_KEY* pSearchKey : Search������Ʈ�� ���� Key����
	@param int iWantIndex	: Search�� ���� ���� �ִ� ������
	@param INT64 iAuctionID	: Auction ID
	@param INT64 iSpotPrice	: �ﱸ ����
 */
void	SPAuctionManager::SendAuctionSpotBuy(AUCTION_SEARCH_KEY* pSearchKey, int iWantIndex, SPAuctionAttr* pAuctionAttr)
{
	INT8	iRefresh = 0 ;
	AUCTION_SORT_KEY eSortKey ;
	int iSortAscend ;
	CPacket packet;

	if( pAuctionAttr == NULL )
		return ;

	m_pBuyArchive->GetLatestSortKey(eSortKey, iSortAscend) ;

	packet.AddUINT32( AUCTION_CS_BUYOUT );	
	packet.AddUINT64( pAuctionAttr->GetAuctionID() );
	packet.AddUINT32( pAuctionAttr->GetCategory() ) ;
	packet.AddUINT64( pAuctionAttr->GetSpotPrice() );	
	
	// Search�� �ش� ���ǰ���� ������ Update
	if( m_pSearchArchive->FindAuctionItem(pAuctionAttr->GetAuctionID()) )	{
		int iSearchPage = iWantIndex / 6 ;		// AUCTION_SEARCH_LIST ;
		if( m_pSearchArchive->IsPartLastPage(iSearchPage) == true )
			iRefresh = 1 ;
	}
	packet.AddUINT8( iRefresh );

	packet.AddUINT32( iWantIndex );
	packet.AddUINT32( pSearchKey->iCategoryID );
	packet.AddUINT8( eSortKey );
	packet.AddUINT8( iSortAscend );
	if( CHECK_AUCTION_ITEM_CATEGORY(pSearchKey->iCategoryID) )
	{
		packet.AddData(pSearchKey->szName, MAX_ITEM_NAME) ;
		packet.AddUINT16(pSearchKey->iMaxLevel) ;
		packet.AddUINT16(pSearchKey->iMaxLevel) ;
		packet.AddUINT8(pSearchKey->iQuality) ;
	}
	else 
	{
		packet.AddUINT32(pSearchKey->iMoneyMin) ;
		packet.AddUINT32(pSearchKey->iMoneyMax) ;
	}

	SENDPACKET(packet);
}




/**
	��� �ƾ��� ��� (Type is AUCTION_TYPE_ITEM_BY_ELY)
	@param INT64 iMoney : �Ǹ� �ݾ�
	@param INT64 iBidMoney : ���۰�(������)
	@param INT64 iSpotMoney : �ﱸ��
	@param int iDuragon	: ��űⰣ (AUCTION_DURATION) : packetID.h
*/
void	SPAuctionManager::SendAuctionSaleItem(SPItem* pItem, INT64 iStMoney, INT64 iSpotMoney, int iDuration, INT64 iEnrolFee)
{
	if( pItem == NULL )
		return ;
	AUCTION_TYPE_INFO* pAuctionTypeInfo = g_pkAuctionManager->GetAuctionTypeInfo(AUCTION_TYPE_ITEM_BY_ELY) ;
	if( pAuctionTypeInfo == NULL )
		return ;

	TRASH_ITEM	stConsumeItem;
	ITEMNO		iConsumeNo = 0;
	CONTAINER_SLOT	stItemSlot ;
	ITEMNO			iItemNo = 0;

	SPPlayerInvenArchive* pkInvenArchive = g_pGOBManager->GetLocalPlayer()->GetInvenArchive() ;
	if(pkInvenArchive == NULL)
		return ;

	if( pAuctionTypeInfo->iConsumeItem > 0 )	{
		SPItem* pSearchItem = pkInvenArchive->GetSPItem(INVENTORY_EVENT, pAuctionTypeInfo->iConsumeItem ) ;
		if( pSearchItem == NULL || pSearchItem->GetSlotIndex() < 0 ) {
			return ;
		}
		stConsumeItem.iContainerSlot.ContainerType = pSearchItem->GetContainerType() ;
		stConsumeItem.iContainerSlot.SlotIndex = pSearchItem->GetSlotIndex() + 1 ;
		stConsumeItem.iCount = 1 ;
		iConsumeNo = *(ITEMNO*)pSearchItem->GetItemStatus()->SPSendMessage(MV_ITEM_GET_ITEMNO);
	}
	else
	{
		stConsumeItem.iContainerSlot.ContainerType = CONTAINER_TYPE_INVALID ;
		stConsumeItem.iContainerSlot.SlotIndex = 0 ;
		stConsumeItem.iCount = 0 ;
	}

	stItemSlot.ContainerType = pItem->GetContainerType() ;
	stItemSlot.SlotIndex = pItem->GetSlotIndex() + 1;
	iItemNo = *(ITEMNO*)pItem->GetItemStatus()->SPSendMessage(MV_ITEM_GET_ITEMNO);

	CPacket packet;
	packet.AddUINT32( AUCTION_CS_CREATE );
	packet.AddUINT8((INT8)AUCTION_TYPE_ITEM_BY_ELY) ;
	packet.AddUINT8((INT8)iDuration) ;
	packet.AddUINT64(iStMoney) ;
	packet.AddUINT64(iSpotMoney) ;
	packet.AddUINT64(iEnrolFee) ;
	packet.AddData( &stConsumeItem, sizeof(TRASH_ITEM));
	packet.AddUINT64((UINT64)iConsumeNo);
	packet.AddData( &stItemSlot, sizeof(CONTAINER_SLOT));
	packet.AddUINT64((UINT64)iItemNo);

	SENDPACKET(packet);
}


/**
	��� �Ӵ� ���
	@param int iType : �Ǹ�Ÿ�� (AUCTION_TYPE) : PaketID.h
	@param int iMoney : �Ǹ� �ݾ� (�ִ� 9��)
	@param INT64 iBidMoney : ���۰�(������)
	@param INT64 iSpotMoney : �ﱸ��
	@param int iDuragon	: ��űⰣ (AUCTION_DURATION) : packetID.h
*/
void	SPAuctionManager::SendAuctionSaleMoney(int iType, int iMoney, INT64 iStMoney, INT64 iSpotMoney, int iDuration, INT64 iEnrolFee)
{
	int iFeePoint = 0 ;
	AUCTION_TYPE_INFO* pAuctionTypeInfo = g_pkAuctionManager->GetAuctionTypeInfo((AUCTION_TYPE)iType) ;
	if( pAuctionTypeInfo == NULL )
		return ;
	
	TRASH_ITEM	stConsumeItem;
	ITEMNO		iConsumeNo = 0;
	AUCTION_GOODS_POINT	stSellPoint ;

	SPPlayerInvenArchive* pkInvenArchive = g_pGOBManager->GetLocalPlayer()->GetInvenArchive() ;
	if(pkInvenArchive == NULL)
		return ;

	if( pAuctionTypeInfo->iConsumeItem > 0 )	{
		SPItem* pSearchItem = pkInvenArchive->GetSPItem(INVENTORY_EVENT, pAuctionTypeInfo->iConsumeItem ) ;
		if( pSearchItem == NULL || pSearchItem->GetSlotIndex() < 0 ) {
			return ;
		}
		stConsumeItem.iContainerSlot.ContainerType = pSearchItem->GetContainerType() ;
		stConsumeItem.iContainerSlot.SlotIndex = pSearchItem->GetSlotIndex() + 1 ;
		stConsumeItem.iCount = 1 ;
		iConsumeNo = *(ITEMNO*)pSearchItem->GetItemStatus()->SPSendMessage(MV_ITEM_GET_ITEMNO);
	}
	else
	{
		stConsumeItem.iContainerSlot.ContainerType = CONTAINER_TYPE_INVALID ;
		stConsumeItem.iContainerSlot.SlotIndex = 0 ;
		stConsumeItem.iCount = 0 ;
	}

	//? �Ǹż������ ���??
	stSellPoint.SellPoint = iMoney ;
	if( iType == AUCTION_TYPE_CASH_BY_ELY || iType == AUCTION_TYPE_MILEAGE_BY_ELY )	{
		SET_AUCTION_FEE(iMoney, GetAuctionFeeRate(), iFeePoint) ;
		stSellPoint.FeePoint = iFeePoint ;
	}
	else
		stSellPoint.FeePoint = 0 ;

	CPacket packet;
	packet.AddUINT32( AUCTION_CS_CREATE );
	packet.AddUINT8((INT8)iType) ;
	packet.AddUINT8((INT8)iDuration) ;
	packet.AddUINT64(iStMoney) ;
	packet.AddUINT64(iSpotMoney) ;
	packet.AddUINT64(iEnrolFee) ;
	packet.AddData( &stConsumeItem, sizeof(TRASH_ITEM));
	packet.AddUINT64((UINT64)iConsumeNo);
	packet.AddData( &stSellPoint, sizeof(AUCTION_GOODS_POINT));

	SENDPACKET(packet);
}


/**
	��� ��� ���
	@param int iAuctionID
*/
void	SPAuctionManager::SendAuctionSaleCancel(SPAuctionAttr* pAuctionAttr)
{
	if( pAuctionAttr == NULL )
		return ;

	CPacket packet;
	packet.AddUINT32( AUCTION_CS_CANCEL );
	packet.AddUINT64( pAuctionAttr->GetAuctionID() );
	packet.AddUINT32( pAuctionAttr->GetCategory() ) ;

	SENDPACKET(packet);
}




//////////////////////////////////////////////////////////////////////////
// Recv Packet
/**
	[AUCTION_SC_SEARCH_INFO]
	INT32	iListCnt
	AUCTION_GOODS_ITEM	ctAuctionItem (...)
*/
void	SPAuctionManager::OnRecvAuctionSearchList(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	INT32	iTotalCnt;		// ��ü ����
	INT32	iStart;			// ������ġ
	INT8	iListCnt;		// ����Ʈ ����
	SPAuctionAttr* pAuctionAttr ;
	AUCTION_HEADER		ctAuctionHeader ;
	AUCTION_GOODS_ITEM	ctAuctionItem ;
	AUCTION_GOODS_POINT ctAuctionPoint ;

	pRecvPacket = (CPacket*)pPacket ;
	if( pRecvPacket == NULL )
	{
		ErrorFLogs->Error_Log("#AuctionList::OnRecvAuctionSearchList is NULL") ;
		return ;
	}
	pRecvPacket->ExtractUINT32((UINT32*)&iTotalCnt);
	pRecvPacket->ExtractUINT32((UINT32*)&iStart);
	pRecvPacket->ExtractUINT8((UINT8*)&iListCnt);
	//ErrorFLogs->Error_Log("#AuctionList::Total[%d], Start[%d], Size [%d]", iTotalCnt, iStart, iListCnt) ;

	m_pSearchArchive->ClearList() ;
	m_pSearchArchive->SetAuctionList(AUCTION_ARCH_PART, 6, iTotalCnt, iStart, iListCnt) ;
	for(int i = 0; i < iListCnt; i++)
	{
		pAuctionAttr = new SPAuctionAttr ;
		pRecvPacket->ExtractStruct(&ctAuctionHeader, sizeof(AUCTION_HEADER));

		// Auction Type���� ��Ŷ�� ����
		if( ctAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY )	{
			pRecvPacket->ExtractStruct(&ctAuctionItem, sizeof(AUCTION_GOODS_ITEM));
			pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionItem) ;
		}
		else	{
			pRecvPacket->ExtractStruct(&ctAuctionPoint, sizeof(AUCTION_GOODS_POINT));
			pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionPoint) ;
		}

		m_pSearchArchive->AddAuctionList(pAuctionAttr) ;
	}

	// ���� �˻������� SortKey�� �缳�� ���ش�.
	if( m_iSearch == 1 )		
		m_pSearchArchive->SetDefaultSort(false) ;
	// Interface Window Update Message
	SPWindow* pWindowAuction = g_pInterfaceManager->GetAuctionWindow() ;
	if(pWindowAuction && pWindowAuction->IsShow()) {
		pWindowAuction->SPSendMessage(SPIM_AUCTION_SEARCH_LIST, (WPARAM)m_iSearch, (LPARAM)m_iSearch);
		m_iSearch = 0 ;
	}
}


/**
	[AUCTION_SC_BIDLIST]
	���� ���� ����� �޴´�
	���� ����� Client���� �����ȴ�.
*/
void	SPAuctionManager::OnRecvAuctionBuyList(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	UINT8	iListCnt;							// ����Ʈ ����
	SPAuctionAttr* pAuctionAttr ;
	AUCTION_HEADER		ctAuctionHeader ;
	AUCTION_GOODS_ITEM	ctAuctionItem ;
	AUCTION_GOODS_POINT ctAuctionPoint ;


	pRecvPacket = (CPacket*)pPacket ;
	if( pRecvPacket == NULL )
	{
		ErrorFLogs->Error_Log("#AuctionList::OnRecvAuctionBuyList is NULL") ;
		return ;
	}
	pRecvPacket->ExtractUINT8((UINT8*)&iListCnt);
	//ErrorFLogs->Error_Log("#AuctionList::Size [%d]", iListCnt) ;

	//m_pBuyArchive->ClearList() ;
	for(int i = 0; i < iListCnt; i++)
	{
		pAuctionAttr = new SPAuctionAttr ;
		pRecvPacket->ExtractStruct(&ctAuctionHeader, sizeof(AUCTION_HEADER));

		// Auction Type���� ��Ŷ�� ����
		if( ctAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY )	{
			pRecvPacket->ExtractStruct(&ctAuctionItem, sizeof(AUCTION_GOODS_ITEM));
			pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionItem) ;
		}
		else	{
			pRecvPacket->ExtractStruct(&ctAuctionPoint, sizeof(AUCTION_GOODS_POINT));
			pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionPoint) ;
		}

		m_pBuyArchive->AddAuctionList(pAuctionAttr) ;
	}
}


/**
	[AUCTION_SC_SELLLIST]
	���� �Ǹ� ����� �޴´�
	�Ǹ� ����� Client���� �����ȴ�.
*/
void	SPAuctionManager::OnRecvAuctionSaleList(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	UINT8	iListCnt;							// ����Ʈ ����
	SPAuctionAttr* pAuctionAttr ;
	AUCTION_HEADER		ctAuctionHeader ;
	AUCTION_GOODS_ITEM	ctAuctionItem ;
	AUCTION_GOODS_POINT ctAuctionPoint ;

	pRecvPacket = (CPacket*)pPacket ;
	if( pRecvPacket == NULL )
	{
		ErrorFLogs->Error_Log("#AuctionList::OnRecvAuctionSaleList is NULL") ;
		return ;
	}
	pRecvPacket->ExtractUINT8((UINT8*)&iListCnt);
	//ErrorFLogs->Error_Log("#AuctionList::Size [%d]", iListCnt) ;

	//m_pSaleArchive->ClearList() ;
	for(int i = 0; i < iListCnt; i++)
	{
		pAuctionAttr = new SPAuctionAttr ;
		pRecvPacket->ExtractStruct(&ctAuctionHeader, sizeof(AUCTION_HEADER));

		// Auction Type���� ��Ŷ�� ����
		if( ctAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY )	{
			pRecvPacket->ExtractStruct(&ctAuctionItem, sizeof(AUCTION_GOODS_ITEM));
			pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionItem) ;
		}
		else	{
			pRecvPacket->ExtractStruct(&ctAuctionPoint, sizeof(AUCTION_GOODS_POINT));
			pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionPoint) ;
		}

		m_pSaleArchive->AddAuctionList(pAuctionAttr) ;
	}
}


/**
	[AUCTION_SC_OPEN]
	��ż����� Reset���� Archive�� Reset�� �ʿ��� ���
 */
void	SPAuctionManager::OnRecvAuctioinOpen()
{
	if( m_pSaleArchive )
		m_pSaleArchive->SetNeedReset(true) ;
	if( m_pBuyArchive )
		m_pBuyArchive->SetNeedReset(true) ;
	SetServerOpen(true) ;

	if( g_pResourceManager->GetGlobalString(52000085))
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000085));
	else	{
		TCHAR szMesg[64] ;
		sprintf(szMesg, "Auction Server is Open") ;
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMesg) ;
	}
}


/**
	[AUCTION_SC_CREATE]
	��� ���
 */
void	SPAuctionManager::OnRecvAuctionCreate(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	SPAuctionAttr* pAuctionAttr ;
	AUCTION_HEADER		ctAuctionHeader ;
	AUCTION_GOODS_ITEM	ctAuctionItem ;
	AUCTION_GOODS_POINT ctAuctionPoint ;
	UINT64				iPlayerEly = 0;
	TRASH_ITEM			ctTrashItem ;
	TRASH_ITEM			ctUploadItem ;
	CHARACTER_CASH_INFO ctCashInfo ;

	SPPlayerInvenArchive* pkInvenArchive = g_pGOBManager->GetLocalPlayer()->GetInvenArchive();
	if( pkInvenArchive == NULL )
		return ;

	pRecvPacket = (CPacket*)pPacket ;
	pAuctionAttr = new SPAuctionAttr ;
	pRecvPacket->ExtractStruct(&ctAuctionHeader, sizeof(AUCTION_HEADER));

	// Auction Type���� ��Ŷ�� ����
	if( ctAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY )	{
		pRecvPacket->ExtractStruct(&ctAuctionItem, sizeof(AUCTION_GOODS_ITEM));
		pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionItem) ;
	}
	else	{
		pRecvPacket->ExtractStruct(&ctAuctionPoint, sizeof(AUCTION_GOODS_POINT));
		pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionPoint) ;
	}
	if( m_pSaleArchive->AddAuctionList(pAuctionAttr) == false )
		SAFE_DELETE(pAuctionAttr) ;

	// Ely ���� ������Ʈ
	pRecvPacket->ExtractUINT64(&iPlayerEly);
	UpdatePlayerEly(iPlayerEly) ;

	// ��Ͽ� �Һ�Ǵ� ��Ͼ����� ����
	pRecvPacket->ExtractStruct( &ctTrashItem , sizeof( TRASH_ITEM ) );
	ctTrashItem.iContainerSlot.SlotIndex -= 1;
	pkInvenArchive->TrashItem(ctTrashItem);

	// ����� ������ �Ǵ� �Ӵ� ���� ����
	// Auction Type���� ��Ŷ�� ����
	if( ctAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY )	{
		pRecvPacket->ExtractStruct( &ctUploadItem , sizeof( TRASH_ITEM ) );
		ctUploadItem.iContainerSlot.SlotIndex -= 1;
		pkInvenArchive->TrashItem(ctUploadItem);
	}
	else	{
		// Ely & Cash ���� ������Ʈ
		pRecvPacket->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
		UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;
	}
	
	// Interface Window Update Message
	SPWindow* pWindowAuction = g_pInterfaceManager->GetAuctionWindow() ;
	if(pWindowAuction && pWindowAuction->IsShow()) {
		pWindowAuction->SPSendMessage(SPIM_AUCTION_SALE_LIST, (WPARAM)0, (LPARAM)0);
		//pWindowAuction->SPSendMessage(SPIM_AUCTION_MONEY_UPDATE, (WPARAM)0, (LPARAM)0);
	}
	// ��� OK Message
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000016));
}



/**
	[AUCTION_SC_FINISH]
	��� ���(����, ����, ��ҽ�: �Ǹ���, ������ -> �ﱸ�� ����ó��)	
	@param void* pPacket
 */
void	SPAuctionManager::OnRecvAuctionFinish(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	UINT64				iAuctionID = 0;
	CHARACTER_CASH_INFO ctCashInfo ;

	pRecvPacket = (CPacket*)pPacket ;
	pRecvPacket->ExtractUINT64(&iAuctionID);

	// Cash ���� ������Ʈ
	pRecvPacket->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
	UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;

	// �ش� ��ǰ ���� ��, �����Ȱ��� �ִٸ� �����ִ� WindowUpdate
	int iTab = UpdateAuctionFinish(iAuctionID, false) ;
	if( iTab > 0 )	{
		SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_AUCTION);
		if(pWindow && pWindow->IsShow()) {
			pWindow->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
			pWindow->SPSendMessage(SPIM_AUCTION_SALE_LIST, (WPARAM)0, (LPARAM)0);
		}
	}
}


/**
	[AUCTION_SC_FINISH_SELL]
	�����Ϸ�
	//		- ������ �Ǹ���/�����ڿ���
	//		- �ﱸ�� �Ǹ��ڿ���	
	@param void* pPacket
 */
void	SPAuctionManager::OnRecvAuctionFinishSell(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	UINT64			iAuctionID = 0;
	USERID			iBuyerID;							// ������
	CHARACTER_CASH_INFO ctCashInfo ;
	D3DXCOLOR color( 0.62745f , 1.0f, 0.0f, 1.0f);
	TCHAR			szMessage[256] ;
	SPAuctionAttr* pAuctionAttr = NULL ;

	pRecvPacket = (CPacket*)pPacket ;
	pRecvPacket->ExtractUINT64(&iAuctionID);
	pRecvPacket->ExtractUINT32(&iBuyerID);

	// Cash ���� ������Ʈ
	pRecvPacket->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
	UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;
	
	if( iBuyerID == g_pNetworkManager->GetUserID() )	{
		// ���� ���� �޽��� [52000005]
		pAuctionAttr = m_pBuyArchive->FindAuctionItem(iAuctionID) ;
		if( pAuctionAttr )	{
			_stprintf(szMessage, g_pResourceManager->GetGlobalString(52000005), pAuctionAttr->GetItemName()) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMessage);
			g_pInterfaceManager->SPChildWndSendMessage( WIID_SYSTEM_MESSAGE , SPIM_SYSTEM_MESSAGE_ADD , (WPARAM)szMessage , (LPARAM)&color );
		}
	}
	else {
		// �Ǹ� �Ϸ� �޽��� [52000094]
		pAuctionAttr = m_pSaleArchive->FindAuctionItem(iAuctionID) ;
		if( pAuctionAttr )	{
			_stprintf(szMessage, g_pResourceManager->GetGlobalString(52000094), pAuctionAttr->GetItemName()) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMessage);
			g_pInterfaceManager->SPChildWndSendMessage( WIID_SYSTEM_MESSAGE , SPIM_SYSTEM_MESSAGE_ADD , (WPARAM)szMessage , (LPARAM)&color );
		}
	}

	// �ش� ��ǰ ���� ��, �����Ȱ��� �ִٸ� �����ִ� WindowUpdate
	int iTab = UpdateAuctionFinish(iAuctionID, false) ;
	if( iTab > 0 )	{
		SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_AUCTION);
		if(pWindow && pWindow->IsShow()) {
			pWindow->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
			pWindow->SPSendMessage(SPIM_AUCTION_SALE_LIST, (WPARAM)0, (LPARAM)0);
		}
	}
}


/**
	[AUCTION_SC_CANCEL]
	��� ���(�����)
	@param void* pPacket
 */
void	SPAuctionManager::OnRecvAuctionCancel(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	UINT64				iAuctionID = 0;
	CHARACTER_CASH_INFO ctCashInfo ;

	pRecvPacket = (CPacket*)pPacket ;
	pRecvPacket->ExtractUINT64(&iAuctionID);

	// Cash ���� ������Ʈ
	pRecvPacket->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
	UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;

	// �ش� ��ǰ ���� ��, �����Ȱ��� �ִٸ� �����ִ� WindowUpdate
	int iTab = UpdateAuctionFinish(iAuctionID, true) ;
	if( iTab > 0 )	{
		SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_AUCTION);
		if(pWindow && pWindow->IsShow()) {
			//pWindow->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
			pWindow->SPSendMessage(SPIM_AUCTION_SALE_LIST, (WPARAM)0, (LPARAM)0);
		}
	}
	if( g_pResourceManager->GetGlobalString(52000006))		// ��� ��� �޽���
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000006));
}




/**
	[AUCTION_SC_BUYOUT]
	��ñ��Ž� �����ڸ� ����
 */
void	SPAuctionManager::OnRecvAuctionBuyOut(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	UINT64				iAuctionID = 0;
	UINT64				iPlayerEly = 0;
	CHARACTER_CASH_INFO ctCashInfo ;
	D3DXCOLOR		color( 0.62745f , 1.0f, 0.0f, 1.0f);
	TCHAR			szMessage[256] ;
	SPAuctionAttr*	pAuctionAttr = NULL ;

	pRecvPacket = (CPacket*)pPacket ;
	pRecvPacket->ExtractUINT64(&iAuctionID);

	// Ely ���� ������Ʈ
	pRecvPacket->ExtractUINT64(&iPlayerEly);
	UpdatePlayerEly(iPlayerEly) ;

	// Cash ���� ������Ʈ
	pRecvPacket->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
	UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;

	// ���� ���� �޽��� [52000005]
	pAuctionAttr = m_pBuyArchive->FindAuctionItem(iAuctionID) ;
	if( pAuctionAttr == NULL )
		pAuctionAttr = m_pSearchArchive->FindAuctionItem(iAuctionID) ;
	if( pAuctionAttr )	{
		_stprintf(szMessage, g_pResourceManager->GetGlobalString(52000005), pAuctionAttr->GetItemName()) ;
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMessage);
		g_pInterfaceManager->SPChildWndSendMessage( WIID_SYSTEM_MESSAGE , SPIM_SYSTEM_MESSAGE_ADD , (WPARAM)szMessage , (LPARAM)&color );
	}

	// �ش� ��ǰ ���� ��, �����Ȱ��� �ִٸ� �����ִ� WindowUpdate
	int iTab =  UpdateAuctionFinish(iAuctionID, true) ;
	if( iTab > 0 )	{
		SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_AUCTION);
		if(pWindow && pWindow->IsShow()) {
			pWindow->SPSendMessage(SPIM_AUCTION_SEARCH_LIST, (WPARAM)0, (LPARAM)1);
			pWindow->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
			pWindow->SPSendMessage(SPIM_AUCTION_SALE_LIST, (WPARAM)0, (LPARAM)0);
		}
	}
}



/**
	[AUCTION_SC_BID]
	���� ���
	>> ���� ������	: ���� ���� �߰�
	>> �Ǹ���		: �Ǹ� ���� ����
	>> ����������	: ���� ���� ����
 */
void	SPAuctionManager::OnRecvAuctionBidUpdate(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	SPAuctionAttr* pAuctionAttr = NULL ;
	USERID			iMyUserID = 0 ;
	AUCTION_HEADER		ctAuctionHeader ;
	AUCTION_GOODS_ITEM	ctAuctionItem ;
	AUCTION_GOODS_POINT ctAuctionPoint ;
	UINT64				iPlayerEly = 0;
	CHARACTER_CASH_INFO ctCashInfo ;
	TCHAR				szItemName[MAX_ITEM_NAME] ;
	TCHAR				szMessage[256] ;

	SPPlayerInvenArchive* pkInvenArchive = g_pGOBManager->GetLocalPlayer()->GetInvenArchive();
	if( pkInvenArchive == NULL )
		return ;

	iMyUserID = g_pNetworkManager->GetUserID() ;

	pRecvPacket = (CPacket*)pPacket ;
	pAuctionAttr = new SPAuctionAttr ;
	pRecvPacket->ExtractStruct(&ctAuctionHeader, sizeof(AUCTION_HEADER));

	// Auction Type���� ��Ŷ�� ����
	if( ctAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY )	{
		pRecvPacket->ExtractStruct(&ctAuctionItem, sizeof(AUCTION_GOODS_ITEM));
		pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionItem) ;
	}
	else	{
		pRecvPacket->ExtractStruct(&ctAuctionPoint, sizeof(AUCTION_GOODS_POINT));
		pAuctionAttr->SetAuctionAttr(&ctAuctionHeader, &ctAuctionPoint) ;
	}
	_stprintf(szItemName, "%s", pAuctionAttr->GetItemName() ) ;
	
	// Ely ���� ������Ʈ
	pRecvPacket->ExtractUINT64(&iPlayerEly);
	UpdatePlayerEly(iPlayerEly) ;
	// Ely & Cash ���� ������Ʈ
	pRecvPacket->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
	UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;


	SPWindow* pWindow = g_pInterfaceManager->GetAuctionWindow() ;
	SPWindow* pWindowMsg = g_pInterfaceManager->GetAuctionMsgWindow() ;
	//pWindow->SPSendMessage(SPIM_AUCTION_MONEY_UPDATE, (WPARAM)0, (LPARAM)0);
	// �Ǹ����� ��� -> �Ǹ� ���� ����
	if( ctAuctionHeader.iSellerID == iMyUserID )	{
		m_pSaleArchive->UpdateAuctionArchive(ctAuctionHeader.iAuctionID, &ctAuctionHeader) ;
		if(pWindow && pWindow->IsShow()) {
			pWindow->SPSendMessage(SPIM_AUCTION_SALE_LIST, (WPARAM)0, (LPARAM)0);
			// �˻��� ������ ����
			if( m_pSearchArchive->UpdateAuctionArchive(ctAuctionHeader.iAuctionID, &ctAuctionHeader) )	
				pWindow->SPSendMessage(SPIM_AUCTION_SEARCH_LIST, (WPARAM)0, (LPARAM)0);
		}
		// ���ο� �����ڰ� �߻��߽��ϴ�.
		if( g_pResourceManager->GetGlobalString(52000007))	
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000007));
		SAFE_DELETE(pAuctionAttr) ;
	}
	// ���� ������ : ���� ���� �߰� & Search ����
	else if (ctAuctionHeader.iCurrUserID == iMyUserID )	{
		pWindowMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, 0, 0) ;
		if( m_pBuyArchive->AddAuctionList(pAuctionAttr, true) == false )
			SAFE_DELETE(pAuctionAttr) ;
		if(pWindow && pWindow->IsShow()) {
			pWindow->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
			// �˻��� ������ ����
			if( m_pSearchArchive->UpdateAuctionArchive(ctAuctionHeader.iAuctionID, &ctAuctionHeader) )
				pWindow->SPSendMessage(SPIM_AUCTION_SEARCH_LIST, (WPARAM)0, (LPARAM)0);
		}
		// %s ��� ��ǰ�� �����Ͽ����ϴ�.
		if( g_pResourceManager->GetGlobalString(52000003))	{
			_stprintf(szMessage, g_pResourceManager->GetGlobalString(52000003), szItemName) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMessage);
		}
	}
	// ���� ������ : ���� ���� ����
	else	{
		m_pBuyArchive->UpdateAuctionArchive(ctAuctionHeader.iAuctionID, &ctAuctionHeader) ;
		if(pWindow && pWindow->IsShow()) {
			pWindow->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
			// �˻��� ������ ����
			if( m_pSearchArchive->UpdateAuctionArchive(ctAuctionHeader.iAuctionID, &ctAuctionHeader) )
				pWindow->SPSendMessage(SPIM_AUCTION_SEARCH_LIST, (WPARAM)0, (LPARAM)0);
		}
		// %s ��ǰ�� ��ȸ���� �Ǿ����ϴ�. (Chat & SystemMessage)
		if( g_pResourceManager->GetGlobalString(52000004))	{
			_stprintf(szMessage, g_pResourceManager->GetGlobalString(52000004), szItemName) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMessage);
			D3DXCOLOR color( 0.62745f , 1.0f, 0.0f, 1.0f);
			g_pInterfaceManager->SPChildWndSendMessage( WIID_SYSTEM_MESSAGE , SPIM_SYSTEM_MESSAGE_ADD , (WPARAM)szMessage , (LPARAM)&color );
		}
		SAFE_DELETE(pAuctionAttr) ;
	}
}



/**
	[AUCTION_SC_BIDDEL]
	���� �������� ��� ��ȸ������ ���������� ������ �Ѵ�.
 */
void	SPAuctionManager::OnRecvAuctionBidDelete(void* pPacket)
{
	CPacket* pRecvPacket = NULL ;
	UINT64	iAuctionID = 0;
	SPWindow* pWindow = g_pInterfaceManager->GetAuctionWindow() ;

	pRecvPacket = (CPacket*)pPacket ;
	pRecvPacket->ExtractUINT64(&iAuctionID);

	m_pBuyArchive->DeleteAuctionItem(iAuctionID, true) ;
	if(pWindow && pWindow->IsShow()) {
		pWindow->SPSendMessage(SPIM_AUCTION_BUY_LIST, (WPARAM)0, (LPARAM)0);
	}
}



