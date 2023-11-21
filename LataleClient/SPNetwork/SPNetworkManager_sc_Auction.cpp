
#include "SPCommon.h"
//
#include "SPGameObjectDEF.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPGOBManager.h"

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPWindow.h"
#include "SPInterfaceManager.h"
#include "SPResourceDef.h"
#include "SPResourceManager.h"

//
#include "SPGameObject.h"
#include "SPGOBStatus.h"
#include "SPGOBClusterDef.h"
#include "SPGOBCluster.h"
#include "SPGobModelUnit.h"
#include "SPAvatarModelUnitDef.h"
#include "SPAvatarModelUnit.h"
#include "SPPlayer.h"
#include "GlobalDefines_Share.h"
#include "SPGuildArchive.h"
#include "SPSubGameManager.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"
#include "SPAuctionManager.h"

#include "_Error_log.h"

extern SPNetworkManager* g_pNetworkManager;

#define ERROR_AUCTION_SERVER_DOWN	52000075			// ��� ���� Down

// AUCTION_SC_OPEN,
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
DEFINE_SC_PACKET_PROC(AUCTION_SC_OPEN)
{
	g_pkAuctionManager->OnRecvAuctioinOpen() ;
}


// AUCTION_SC_CREATE,
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// iErrorID == 0
// AUCTION_HEADER	stAuctionHeader;					// �⺻����
// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)
// __int64			iCurrEly;							// ���糲���� (��ϼ����� or �ø� ���� ���ϰ� ���� �������ִµ�)
// TRASH_ITEM		stUseItem;							// �ʿ������
//-------------------------------------------------
//	stAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY
//		TRASH_ITEM			stUpItem;					// �ø�Z�����ۻ�������
//	else
//		CHARACTER_CASH_INFO stCash;						// ����ĳ������
// iErrorID != 0
// CHARACTER_CASH_INFO stCash;	
DEFINE_SC_PACKET_PROC(AUCTION_SC_CREATE)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	SPWindow*			pAuctionWindow ;
	SPWindow*			pAuctionMsg;
	CHARACTER_CASH_INFO ctCashInfo ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionWindow	= g_pInterfaceManager->GetAuctionWindow() ;
	pAuctionMsg		= g_pInterfaceManager->GetAuctionMsgWindow() ;
	GU_ID LocalGUID = g_pGOBManager->GetLocalPlayer()->GetGUID() ;
	if( ObjectGUID != LocalGUID )	{
		ErrorFLogs->Error_Log("AUCTION_SC_CREATE ObjectGUID ERROR[%I64d]-[%I64d]", ObjectGUID, LocalGUID) ;
		// Progress Close
		if( pAuctionMsg )
			pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, ErrorID, 0) ;
		return ;
	}

	// Error�� ��� ErrorID �ڿ� CHARACTER_CASH_INFO�� �־ ĳ������ ������Ʈ
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_CREATE ERROR [%d]", ErrorID) ;
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		// Player CASH_INFO ������Ʈ
		packet->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
		g_pkAuctionManager->UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;
		if( pAuctionWindow )
			pAuctionWindow->SPSendMessage(SPIM_AUCTION_MONEY_UPDATE, (WPARAM)0, (LPARAM)0);
	}
	else	{
		g_pkAuctionManager->OnRecvAuctionCreate((void*)packet) ;	
	}

	// Progress Close
	if( pAuctionMsg )
		pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, ErrorID, 0) ;
}



// AUCTION_CS_CANCEL
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// iErrorID == 0
// __int64			iAuctionID;							// ���Ű
// CHARACTER_CASH_INFO stCash;							// 
// iErrorID != 0
// CHARACTER_CASH_INFO stCash;							//							// 
DEFINE_SC_PACKET_PROC(AUCTION_SC_CANCEL)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	CHARACTER_CASH_INFO ctCashInfo ;
	SPWindow* pAuctionWindow ;
	SPWindow* pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionWindow = g_pInterfaceManager->GetAuctionWindow() ;
	pAuctionMsg	   = g_pInterfaceManager->GetAuctionMsgWindow() ;
	// Error�� ��� ErrorID �ڿ� CHARACTER_CASH_INFO�� �־ ĳ������ ������Ʈ
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_CANCEL ERROR [%d]", ErrorID) ;

		// Player CASH_INFO ������Ʈ
		packet->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
		g_pkAuctionManager->UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;
		if( pAuctionWindow )
			pAuctionWindow->SPSendMessage(SPIM_AUCTION_MONEY_UPDATE, (WPARAM)0, (LPARAM)0);
		
		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
	else	{
		g_pkAuctionManager->OnRecvAuctionCancel((void*)packet) ;	
	}

	// Progress Close
	if( pAuctionMsg )
		pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, ErrorID, 0) ;
}


// AUCTION_SC_FINISH, (�Ǹ���, ����������, ���������� ���� -> �ش� ��� ����)
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// iErrorID == 0
// __int64			iAuctionID;							// ���Ű
// CHARACTER_CASH_INFO stCash;							// 
// iErrorID != 0
// CHARACTER_CASH_INFO stCash;							//							// 
DEFINE_SC_PACKET_PROC(AUCTION_SC_FINISH)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	CHARACTER_CASH_INFO ctCashInfo ;
	SPWindow* pAuctionWindow ;
	SPWindow* pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionWindow = g_pInterfaceManager->GetAuctionWindow() ;
	pAuctionMsg	   = g_pInterfaceManager->GetAuctionMsgWindow() ;
	// Error�� ��� ErrorID �ڿ� CHARACTER_CASH_INFO�� �־ ĳ������ ������Ʈ
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_FINISH ERROR [%d]", ErrorID) ;

		// Player CASH_INFO ������Ʈ
		packet->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
		g_pkAuctionManager->UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;
		if( pAuctionWindow )
			pAuctionWindow->SPSendMessage(SPIM_AUCTION_MONEY_UPDATE, (WPARAM)0, (LPARAM)0);
		
		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
	else	{
		g_pkAuctionManager->OnRecvAuctionFinish((void*)packet) ;	
	}
}



// �����Ϸ�
//		- ������ �Ǹ���/�����ڿ���
//		- �ﱸ�� �Ǹ��ڿ���
// AUCTION_SC_FINISH_SELL,
// GU_ID			iObjectID;
// __int64			iAuctionID;							// ���Ű
// CHARID			iBuyerID;							// ������
// CHARACTER_CASH_INFO stCash;							// 
DEFINE_SC_PACKET_PROC(AUCTION_SC_FINISH_SELL)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�

	packet->ExtractUINT64(&ObjectGUID);	
	g_pkAuctionManager->OnRecvAuctionFinishSell((void*)packet) ;	
}



// AUCTION_SC_BUYOUT,
//** Item Blocking �� ������ �ʿ���
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// iErrorID == 0
// __int64			iAuctionID;							// ���Ű
// __int64			iCurrMoney;							// ���Ű
// CHARACTER_CASH_INFO stCash;							// 
// iErrorID != 0
// CHARACTER_CASH_INFO stCash;							//
DEFINE_SC_PACKET_PROC(AUCTION_SC_BUYOUT)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	CHARACTER_CASH_INFO ctCashInfo ;
	SPWindow* pAuctionWindow ;
	SPWindow* pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionWindow = g_pInterfaceManager->GetAuctionWindow() ;
	pAuctionMsg	   = g_pInterfaceManager->GetAuctionMsgWindow() ;
	// Progress Close
	if( pAuctionMsg )
		pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, 0, 0) ;
	// Error�� ��� ErrorID �ڿ� CHARACTER_CASH_INFO�� �־ ĳ������ ������Ʈ
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_BUYOUT ERROR [%d]", ErrorID) ;

		// Player CASH_INFO ������Ʈ
		packet->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
		g_pkAuctionManager->UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;
		if( pAuctionWindow )
			pAuctionWindow->SPSendMessage(SPIM_AUCTION_MONEY_UPDATE, (WPARAM)0, (LPARAM)0);
		
		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		// 52000073(������ ����), 52000074(����������), 52000009(���¾�����) => ��˻�
		else if( ErrorID == 52000073 || ErrorID == 52000074 || ErrorID == 52000009)	{
			//pAuctionWindow->SPSendMessage(SPIM_AUCTION_ERROR_NOTICE, AUCTION_MSG_REFRESH, (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
			pAuctionMsg->SPSendMessage(SPIM_AUCTION_ERROR_NOTICE, 2, (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
	else	{
		g_pkAuctionManager->OnRecvAuctionBuyOut((void*)packet) ;	
	}
}


// AUCTION_SC_BID,	
//	>> ���� ������	: ���� ���� �߰�
//	>> �Ǹ���		: �Ǹ� ���� ����
//	>> ����������	: ���� ���� ����
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// AUCTION_HEADER	stAuctionHeader;					// �⺻����
// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)
// __int64			iCurrEly;							// ���糲���� (��ϼ����� or �ø� ���� ���ϰ� ���� �������ִµ�)
// CHARACTER_CASH_INFO stCash;							// ����ĳ������							
DEFINE_SC_PACKET_PROC(AUCTION_SC_BID)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	CHARACTER_CASH_INFO ctCashInfo ;
	SPWindow* pAuctionWindow ;
	SPWindow* pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionWindow = g_pInterfaceManager->GetAuctionWindow() ;
	pAuctionMsg	   = g_pInterfaceManager->GetAuctionMsgWindow() ;
	// Error�� ��� ErrorID �ڿ� CHARACTER_CASH_INFO�� �־ ĳ������ ������Ʈ
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_BID ERROR [%d]", ErrorID) ;
		// Progress Close
		if( pAuctionMsg )
			pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, ErrorID, 0) ;

		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		// 52000073(������ ����), 52000074(����������), 52000009(���¾�����) => ��˻�
		else if( ErrorID == 52000073 || ErrorID == 52000074 || ErrorID == 52000009)	{
			//pAuctionWindow->SPSendMessage(SPIM_AUCTION_ERROR_NOTICE, AUCTION_MSG_REFRESH, (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
			pAuctionMsg->SPSendMessage(SPIM_AUCTION_ERROR_NOTICE, 2, (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );

		// Player CASH_INFO ������Ʈ
		packet->ExtractStruct(&ctCashInfo, sizeof(CHARACTER_CASH_INFO));
		g_pkAuctionManager->UpdatePlayerCash(ctCashInfo.iCash, ctCashInfo.iMile) ;
		if( pAuctionWindow )
			pAuctionWindow->SPSendMessage(SPIM_AUCTION_MONEY_UPDATE, (WPARAM)0, (LPARAM)0);

	}
	else	{
		g_pkAuctionManager->OnRecvAuctionBidUpdate((void*)packet) ;	
	}
}


// AUCTION_SC_SEARCH_INFO,
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// int				iNumOfTotalCount;					// �Ѱ���
// int				iStartNumber;						// ��������ó������ �Ѱ����� ���°���� �ش��ϴ���
// UINT8			iNumOfAuction;						// ���۵ɿ�����������
	// AUCTION_HEADER	stAuctionHeader;					// �⺻����
	// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)
DEFINE_SC_PACKET_PROC(AUCTION_SC_SEARCH_INFO)
{
	GU_ID		ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	SPWindow*	pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	// Progress Close
	pAuctionMsg = g_pInterfaceManager->GetAuctionMsgWindow() ;
	if( pAuctionMsg )
		pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, 0, 0) ;

	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_SEARCH_INFO ERROR [%d]", ErrorID) ;

		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
	else {
		g_pkAuctionManager->OnRecvAuctionSearchList((void*)packet) ;
	}
}


// AUCTION_SC_INFO_4BIDDER,
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// Error Process
DEFINE_SC_PACKET_PROC(AUCTION_SC_INFO_4BIDDER)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	SPWindow* pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionMsg = g_pInterfaceManager->GetAuctionMsgWindow() ;
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_CREATE ERROR [%d]", ErrorID) ;

		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
	else	{
		// �������� ��� ������� Default Sort�� ���ش�.
		g_pkAuctionManager->SetDefaultSort(0) ;
	}
}


// AUCTION_SC_BIDLIST,
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// UINT8			iNumOfAuction;						// ���۵ɿ�����������
	// AUCTION_HEADER	stAuctionHeader;					// �⺻����
	// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)
DEFINE_SC_PACKET_PROC(AUCTION_SC_BIDLIST)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	packet->ExtractUINT64(&ObjectGUID);	

	g_pkAuctionManager->OnRecvAuctionBuyList((void*)packet) ;
}


// AUCTION_SC_BIDDEL,	(���� ������)
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// __int64			iAuctionID;							// ���Ű
DEFINE_SC_PACKET_PROC(AUCTION_SC_BIDDEL)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	SPWindow* pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionMsg = g_pInterfaceManager->GetAuctionMsgWindow() ;
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_BIDDEL ERROR [%d]", ErrorID) ;

		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
	else	{
		g_pkAuctionManager->OnRecvAuctionBidDelete((void*)packet) ;
	}
}



// AUCTION_SC_INFO_4SELLER,
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	iErrorID;							// �������̵�
// Error Process
DEFINE_SC_PACKET_PROC(AUCTION_SC_INFO_4SELLER)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	SPWindow* pAuctionMsg ;
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);

	pAuctionMsg = g_pInterfaceManager->GetAuctionMsgWindow() ;
	if( ErrorID != 0 )	{
		ErrorFLogs->Error_Log("AUCTION_SC_INFO_4SELLER ERROR [%d]", ErrorID) ;

		// Server Down ó�� 
		if( ErrorID == ERROR_AUCTION_SERVER_DOWN )	{
			g_pkAuctionManager->SetServerOpen(false) ;
			if( pAuctionMsg )
				pAuctionMsg->SPSendMessage(SPIM_AUCTION_SERVER_CLOSE, ErrorID, 0) ;
		}
		else if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
	else	{
		// �������� ��� ������� Default Sort�� ���ش�.
		g_pkAuctionManager->SetDefaultSort(1) ;
	}
}



// AUCTION_SC_SELLLIST,
// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
// UINT8			iNumOfAuction;						// ���۵ɿ�����������
	// AUCTION_HEADER	stAuctionHeader;					// �⺻����
	// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)
DEFINE_SC_PACKET_PROC(AUCTION_SC_SELLLIST)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	packet->ExtractUINT64(&ObjectGUID);	

	g_pkAuctionManager->OnRecvAuctionSaleList((void*)packet) ;
}



