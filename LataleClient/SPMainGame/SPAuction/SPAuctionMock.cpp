// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionMock.cpp
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"

#include "SPItemAttr.h"
#include "SPItemStatus.h"
#include "SPItem.h"
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

#include "SPAuctionDef.h"
#include "SPAuctionManager.h"
#include "SPAuctionMock.h"

#include "_Error_log.h"



SPAuctionMock::SPAuctionMock()
{

}

SPAuctionMock::~SPAuctionMock()
{
	Clear() ;
}


void SPAuctionMock::Init()
{
	m_iAuctionID = 100000 ;
}


void SPAuctionMock::Clear()
{
}

/*
	typedef struct _AUCTION_HEADER
	{
	__int64 iAuctionID;				// ���Ű
	UINT8	iType;					// ���Ÿ��
	UINT8	iDuration;				// AUCTION_DURATION (�Ǹ��ڰ� ������)
	TCHAR	szName[LEN_NAME+1];		// �Ǹ��� or �ְ�������(��ϸ���Ʈ)
	UINT32	iRemainTime;			// ���糲���ð�

	__int64 iBidPrice;				// ���۰� Ȥ�� ��ȸ������
	__int64 iBuyOutPrice;			// �ﱸ��
	__int64 iCurrPrice;				// ���簡
	USERID  iCurrUserID;			// ���������ڰ���Ű
	} AUCTION_HEADER, *PAUCTION_HEADER;

	// ��Űŷ�Ÿ�Ժ��߰�����Ÿ
	typedef struct _AUCTION_GOODS_ITEM : public _AUCTION_HEADER
	{
	ITEM stAuctionItem;
	} AUCTION_GOODS_ITEM, *PAUCTION_GOODS_ITEM;

	typedef struct _AUCTION_GOODS_POINT : public _AUCTION_HEADER
	{
	int SellPoint; // Ely, Cash, Mileage
	int FeePoint;  // ������
	} AUCTION_GOODS_POINT, *PAUCTION_GOODS_POINT;
*/

/**
	AUCTION_SC_SEARCH_INFO,
	// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
	// int				iNumOfTotalCount;					// �Ѱ���
	// int				iStartNumber;						// ��������ó������ �Ѱ����� ���°���� �ش��ϴ���
	// UINT8			iNumOfAuction;						// ���۵ɿ�����������
*/
void SPAuctionMock::SendAuctionSearchList(int iStart, int iSize)
{
	AUCTION_HEADER		ctSendHeader;
	AUCTION_GOODS_ITEM	ctSendData ;
	CPacket packet;
	int k ;
	int iTotalCnt = 100 ;
	k = MakeRandomValue(0, 15) ;

	packet.Clean() ;
	packet.AddUINT32( iTotalCnt ) ;
	packet.AddUINT32( iStart ) ;
	packet.AddUINT8( iSize );
	for( int i = 0; i < iSize; i++ )
	{
		MakeAuctionListHeader(ctSendHeader) ;
		if( false == MakeAuctionListItem(ctSendData.stAuctionItem, k++) )
		{
			ErrorFLogs->Error_Log("MakeAuctionListItem Failed!!! [%d,%d]", i, iSize) ;
			return ;
		}
		packet.AddData( &ctSendHeader, sizeof(AUCTION_HEADER));
		packet.AddData( &ctSendData, sizeof(AUCTION_GOODS_ITEM));
	}
	g_pkAuctionManager->OnRecvAuctionSearchList(&packet) ;
}


void SPAuctionMock::SendAuctionBuyList(int iSize)
{
	AUCTION_HEADER		ctSendHeader;
	AUCTION_GOODS_ITEM	ctSendData ;
	CPacket packet;
	int k ;
	k = MakeRandomValue(0, 15) ;

	packet.Clean() ;
	packet.AddUINT8( (UINT8)iSize );
	for( int i = 0; i < iSize; i++ )
	{
		MakeAuctionListHeader(ctSendHeader) ;
		ctSendHeader.iCurrUserID = g_pNetworkManager->GetUserID() ;		// ���� ����
		strcpy( ctSendHeader.szBidder, g_pNetworkManager->GetCharName().c_str()) ;

		if( false == MakeAuctionListItem(ctSendData.stAuctionItem, k++) )
		{
			ErrorFLogs->Error_Log("MakeAuctionListItem Failed!!! [%d,%d]", i, iSize) ;
			return ;
		}
		packet.AddData( &ctSendHeader, sizeof(AUCTION_HEADER));
		packet.AddData( &ctSendData, sizeof(AUCTION_GOODS_ITEM));
	}
	g_pkAuctionManager->OnRecvAuctionBuyList(&packet) ;
}


void SPAuctionMock::SendAuctionSaleList(int iSize)
{
	AUCTION_HEADER		ctSendHeader;
	AUCTION_GOODS_ITEM	ctSendData ;
	CPacket packet;
	int k ;
	k = MakeRandomValue(0, 15) ;

	packet.Clean() ;
	packet.AddUINT8( (UINT8)iSize );
	for( int i = 0; i < iSize; i++ )
	{
		MakeAuctionListHeader(ctSendHeader) ;
		ctSendHeader.iSellerID = g_pNetworkManager->GetUserID() ;		// ���� �Ǹ�
		strcpy( ctSendHeader.szSeller, g_pNetworkManager->GetCharName().c_str()) ;

		if( false == MakeAuctionListItem(ctSendData.stAuctionItem, k++) )
		{
			ErrorFLogs->Error_Log("MakeAuctionListItem Failed!!! [%d,%d]", i, iSize) ;
			return ;
		}
		packet.AddData( &ctSendHeader, sizeof(AUCTION_HEADER));
		packet.AddData( &ctSendData, sizeof(AUCTION_GOODS_ITEM));
	}
	g_pkAuctionManager->OnRecvAuctionSaleList(&packet) ;
}



/**
	������ ��������� �޾Ƽ� ����� �˷��ִ� ��Ŷ
 */
void SPAuctionMock::ProcessAuctionCreate(CPacket* pRecvPacket)
{
	UINT8	iType;				//�ŷ�Ÿ��(AUCTION_TYPE)
	UINT8	iDuration;			//�ⰣŸ��(AUCTION_DURATION )
	UINT64	iStartingPrice;		//���۰�
	UINT64	iBuyOutPrice;		//�ﱸ��
	UINT64	iEnrolPrice;		//��ϼ�����
	TRASH_ITEM	stUseItem;		//�ʿ��������ġ�� ����(1)
	ITEMNO	iUseItemNo;			//�ʿ������Ű
	CONTAINER_SLOT		stUpItemPos;
	ITEMNO	iUpItemNo;
	AUCTION_GOODS_POINT stUpPoint;

	pRecvPacket->ExtractUINT8((UINT8*)&iType);
	pRecvPacket->ExtractUINT8((UINT8*)&iDuration);
	pRecvPacket->ExtractUINT64((UINT64*)&iStartingPrice);
	pRecvPacket->ExtractUINT64((UINT64*)&iBuyOutPrice);
	pRecvPacket->ExtractUINT64((UINT64*)&iEnrolPrice);
	pRecvPacket->ExtractStruct(&stUseItem, sizeof(TRASH_ITEM));
	pRecvPacket->ExtractUINT64((UINT64*)&iUseItemNo);
	ErrorFLogs->Error_Log("AuctionCreate Type[%d], �Ⱓ[%d], ���۰�[%d], �ﱸ��[%d], ��Ϻ�[%d], ��Ͼ�����[%d]", 
							iType, iDuration, iStartingPrice, iBuyOutPrice, iEnrolPrice, iUseItemNo) ;
	if( iType == AUCTION_TYPE_ITEM_BY_ELY )	{
		pRecvPacket->ExtractStruct(&stUpItemPos, sizeof(CONTAINER_SLOT));
		pRecvPacket->ExtractUINT64((UINT64*)&iUpItemNo);
		ErrorFLogs->Error_Log("AuctionCreate ��Ͼ����� Slot[%d] Index[%d] ITEMNO[%d]", 
			stUpItemPos.ContainerType, stUpItemPos.SlotIndex, iUpItemNo) ;
	}
	else	{
		pRecvPacket->ExtractStruct(&stUpPoint, sizeof(AUCTION_GOODS_POINT));
		ErrorFLogs->Error_Log("AuctionCreate ��ϱݾ� [%d] ������[%d]", stUpPoint.SellPoint, stUpPoint.FeePoint) ;
	}

	// Make Return packet

	CPacket SendPacket;
	AUCTION_HEADER		ctSendHeader;
	AUCTION_GOODS_ITEM	ctSendData ;
	CHARACTER_CASH_INFO ctCash ;
	TRASH_ITEM			stUpItem;		
	INT64 iEly = 0 ;
	PACK_OPT*			pOpt = NULL ;

	ctSendHeader.iAuctionID = ++m_iAuctionID ;
	ctSendHeader.iType = iType ;
	ctSendHeader.iDuration = iDuration ;
	ctSendHeader.iCurrPrice = iStartingPrice ;
	ctSendHeader.iBidPrice = iStartingPrice + 100 ;
	ctSendHeader.iBuyOutPrice = iBuyOutPrice ;
	ctSendHeader.iCurrUserID = 0 ;
	memset(ctSendHeader.szBidder, 0, LEN_NAME+1) ;
	ctSendHeader.iSellerID = g_pNetworkManager->GetUserID() ;
	strcpy( ctSendHeader.szSeller, g_pNetworkManager->GetCharName().c_str() ) ;

	if( iType == AUCTION_TYPE_ITEM_BY_ELY )	{
		SPPlayerInvenArchive* pInven = NULL;
		if(g_pGOBManager->GetLocalPlayer())
			pInven = g_pGOBManager->GetLocalPlayer()->GetInvenArchive();
		else 
			return ;
		SPItem* pItem = pInven->GetInventoryItem(stUpItemPos.ContainerType, stUpItemPos.SlotIndex);	
		if( pItem == NULL )
			return ;

		ctSendData.stAuctionItem.iBackPrice = pItem->GetItemStatus()->GetItemBackPrice() ;
		ctSendData.stAuctionItem.iItemID = pItem->GetItemStatus()->GetItemID() ;
		ctSendData.stAuctionItem.iItemExp = pItem->GetItemStatus()->GetExp() ;
		ctSendData.stAuctionItem.iItemNo = *(ITEMNO*)pItem->GetItemStatus()->SPSendMessage(MV_ITEM_GET_ITEMNO);
		ctSendData.stAuctionItem.iItemSP = pItem->GetItemStatus()->GetSp();
		ctSendData.stAuctionItem.iLifeTime = pItem->GetItemStatus()->GetLifeTime();
		ctSendData.stAuctionItem.iOptPoint = (short)pItem->GetItemStatus()->SPSendMessage(MV_ITEM_GET_OPTPOINT);
		ctSendData.stAuctionItem.iRare = pItem->GetItemStatus()->GetRareLevel();
		ctSendData.stAuctionItem.iStackCount = pItem->GetItemStatus()->GetStackCount();
		
		for( int i = 0 ; i < MAX_ITEM_OPT ; ++i )
		{
			pOpt =  pItem->GetItemStatus()->GetOption(i);
			ctSendData.stAuctionItem.Opt[i].iID = pOpt->iID ;
			ctSendData.stAuctionItem.Opt[i].iValue = pOpt->iValue ;
		}
	}
	else	{
		ctCash.iCash = 10000000 ;
		ctCash.iMile = 10000000 ;
	}


	// �ø�������
	stUpItem.iContainerSlot.ContainerType = stUpItemPos.ContainerType ;
	stUpItem.iContainerSlot.SlotIndex = stUpItemPos.SlotIndex ;
	stUpItem.iCount = 1 ;

	SendPacket.AddData( &ctSendHeader, sizeof(AUCTION_HEADER));
	SendPacket.AddData( &ctSendData, sizeof(AUCTION_GOODS_ITEM));
	SendPacket.AddUINT64( iEly );
	SendPacket.AddData( &stUseItem, sizeof(TRASH_ITEM));
	if( iType == AUCTION_TYPE_ITEM_BY_ELY )
		SendPacket.AddData( &stUseItem, sizeof(TRASH_ITEM));
	else
		SendPacket.AddData( &ctCash, sizeof(CHARACTER_CASH_INFO));


	g_pkAuctionManager->OnRecvAuctionCreate((void*)&SendPacket) ;
}


/**
	���� ��Ŷ
 */
void SPAuctionMock::ProcessAuctionBid(CPacket* pRecvPacket)
{
	return ;
}

/**
	�ﱸ ��Ŷ
 */
void SPAuctionMock::ProcessAuctionSpot(CPacket* pRecvPacket)
{
	return ;
}

/**
	���� ��� ��Ŷ
 */
void SPAuctionMock::ProcessAuctionCancel(CPacket* pRecvPacket)
{
	return ;
}


//////////////////////////////////////////////////////////////////////////
// ��Ŷ�� ����� ���� ���� ����
void SPAuctionMock::MakeAuctionListHeader(AUCTION_HEADER& ctHeader)
{
	int iRand ;
	std::string strBidderName ;
	std::string strSellerName ;
	ctHeader.iAuctionID = MakeRandomValue((INT64)100, (INT64)100000) ;
	ctHeader.iType = AUCTION_TYPE_ITEM_BY_ELY ;
	iRand = MakeRandomValue(0, 3) ;
	ctHeader.iDuration = AUCTION_DURATION(iRand) ;
	MakePreviousBidderString(strBidderName) ;
	MakePreviousSellerString(strSellerName) ;
	strcpy( ctHeader.szSeller, strBidderName.c_str()) ;
	strcpy( ctHeader.szBidder, strSellerName.c_str()) ;
	ctHeader.iRemainTime	= MakeRandomValue( (INT32)100, (INT32)1000) ;
	ctHeader.iBidPrice		= MakeRandomValue( (INT64)10000, (INT64)10000000) ;
	ctHeader.iBuyOutPrice	= MakeRandomValue( ctHeader.iBidPrice, (INT64)100000000) ;
	ctHeader.iCurrPrice		= MakeRandomValue( (INT64)10000, (INT64)100000000) ;
	ctHeader.iCurrUserID	= MakeRandomValue( (UINT32)10000, (UINT32)1000000) ;
	ctHeader.iSellerID		= MakeRandomValue( (UINT32)10000, (UINT32)1000000) ;
}


bool SPAuctionMock::MakeAuctionListItem(ITEM& ctItem, int iIndex)
{
	iIndex ? MakePreviousItemID(ctItem.iItemID, iIndex) : MakePreviousItemID(ctItem.iItemID) ;
	SPItemAttr* pItemAttr = NULL;
	if( g_pItemCluster->GetItemInfo(ctItem.iItemID, pItemAttr) ) {
		ctItem.iStackCount	= pItemAttr->m_iStackLimit;		// ������ ����
		ctItem.iLifeTime	= pItemAttr->m_iLifeTime;			// ���� Ÿ���̹Ƿ� ���� ���� �ü� ����. DB �� ��������.
		ctItem.iRare		= MakeRandomValue((INT8)0, (INT8)6);				// ���
		ctItem.Opt[0].iID	= pItemAttr->m_iOptionID1;	// �ɼ�
		ctItem.Opt[1].iID	= pItemAttr->m_iOptionID2;	// �ɼ�
		ctItem.Opt[2].iID	= pItemAttr->m_iOptionID3;	// �ɼ�
		ctItem.Opt[3].iID	= pItemAttr->m_iOptionID4;	// �ɼ�
		ctItem.Opt[4].iValue	= 0;	// �ɼ�
		ctItem.Opt[0].iValue	= 0;	// �ɼ�
		ctItem.Opt[1].iValue	= 0;	// �ɼ�
		ctItem.Opt[2].iValue	= 0;	// �ɼ�
		ctItem.Opt[3].iValue	= 0;	// �ɼ�
		ctItem.Opt[4].iValue	= 0;	// �ɼ�
		ctItem.iItemNo		= pItemAttr->m_iNum;
		ctItem.iBackPrice	= pItemAttr->m_iCashPrice;			// 
		ctItem.iOptPoint	= pItemAttr->m_iCashPoint;
		ctItem.iItemExp		= 0;			// �����۰���ġ
		ctItem.iItemSP		= 0;			// ������SP
		return true ;
	}
	return false ;
}


void SPAuctionMock::MakeAuctionListMoney(int& iMoney, int& iFeeMoney)
{
	iMoney = MakeRandomValue((int)100, (int)20000000) ;
	iFeeMoney = MakeRandomValue((int)10, (int)200000) ;
}



//////////////////////////////////////////////////////////////////////////
// �� �׸��� �����ϰ� ����

void SPAuctionMock::MakePreviousItemID(ITEMID& iID)
{
	int iIDS[15] = {	160201701, 160201702, 160201703, 160201704, 160201705, 
		160201706, 160201707, 160201708, 160201709, 160201710, 
		160201711, 160201712, 160201713, 160201714, 160201715} ;

	int iIndex = MakeRandomValue(0, 15) ;
	iID = iIDS[iIndex];
}

void SPAuctionMock::MakePreviousItemID(ITEMID& iID, int iIndex)
{
	int iIDS[15] = {	160201701, 160201702, 160201703, 160201704, 160201705, 
		180190101, 180190102, 180190103, 180190108, 180190109, 
		180190114, 180190120, 160201713, 160201714, 160201715} ;

	int k = iIndex % 15 ;
	iID = iIDS[k];
}





void SPAuctionMock::MakePreviousBidderString(std::string& str)
{
	//TCHAR szText[15][LEN_NAME+1] = {	{"���̸���"}, {"����"}, {"��¼���"}, {"�׷��Ը���"}, {"������"},
	//{"�̷�����"}, {"�����̷�����"}, {"����"}, {"�����δ�"}, {"�Ծ�����"},
	//{"�ƽΰ�����"}, {"�ƺ������"}, {"ũ�����"}, {"�����ϳ�"}, {"�����̻�"}
	//};

	//int iIndex = MakeRandomValue(0, 15) ;
	//str = szText[iIndex] ;
}


void SPAuctionMock::MakePreviousSellerString(std::string& str)
{
	//TCHAR szText[15][LEN_NAME+1] = {	
	//	{"S���̸���"}, {"S����"}, {"S��¼���"}, {"S�׷��Ը���"}, {"S������"},
	//	{"S�̷�����"}, {"S�����̷�����"}, {"S����"}, {"S�����δ�"}, {"S�Ծ�����"},
	//	{"S�ƽΰ�����"}, {"S�ƺ������"}, {"Sũ�����"}, {"S�����ϳ�"}, {"S�����̻�"}
	//};

	//int iIndex = MakeRandomValue(0, 15) ;
	//str = szText[iIndex] ;
}


//////////////////////////////////////////////////////////////////////////
template<class T>
T SPAuctionMock::MakeRandomValue(T tStart, T tEnd)
{
	srand( (unsigned)time( NULL ) );
	float fRand = (float)rand() / RAND_MAX ;		// 0 ~ 1.0f
	//ErrorFLogs->Error_Log("Make RandomValue [%f]", fRand) ;
	return (T)( fRand*tEnd + tStart ) ; 
}
