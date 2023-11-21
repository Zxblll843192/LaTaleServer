// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionAttr.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/

#pragma once 

//typedef struct _AUCTION_HEADER
//{
//	__int64 iAuctionID;				// ���Ű
//	UINT8	iType;					// ���Ÿ��
//	UINT8	iDuration;				// AUCTION_DURATION (�Ǹ��ڰ� ������)
//	TCHAR	szName[LEN_NAME+1];		// �Ǹ��� or �ְ�������(��ϸ���Ʈ)
//	UINT32	iRemainTime;			// ���糲���ð�
//
//	__int64 iBidPrice;				// ���۰� Ȥ�� ��ȸ������
//	__int64 iBuyOutPrice;			// �ﱸ��
//	__int64 iCurrPrice;				// ���簡
//	USERID  iCurrUserID;			// ���������ڰ���Ű
//} AUCTION_HEADER, *PAUCTION_HEADER;

enum AUCTION_TYPE ;
class SPItem ;
class SPAuctionAttr
{

public:	
	SPAuctionAttr() ;
	~SPAuctionAttr() ;

	void Init() ;
	void Clear() ;

	bool SetAuctionAttr(AUCTION_HEADER* pHeader, AUCTION_GOODS_ITEM* pGoodsItem) ;
	bool SetAuctionAttr(AUCTION_HEADER* pHeader, AUCTION_GOODS_POINT* pGoodsItem) ;
	bool SetChangeHeader(AUCTION_HEADER* pHeader);		// For Header Information Change

	AUCTION_TYPE GetType()			{	return m_iAuctionType ;		}

	// For Interface
	SPItem*		GetItemInfo() ;			// SPItem*
	AUCTION_HEADER*	GetHeader() ;		// Auction Information
	INT64		GetAuctionID() ;		// Auction ID
	const char* GetItemName() ;			// Item Name
	int			GetItemQuality() ;		// Item Rare
	int			GetItemLevel() ;		// Level
	int			GetItemDuration() ;		// Duration
	UINT32		GetFinishTime() ;		// FinishTime
	const char* GetBidderName() ;		// BidUser Name
	const char* GetSellerName() ;		// SaleUser Name
	USERID		GetBidderUserID() ;		// BidUserID
	USERID		GetSellerUserID() ;		// SaleUserID
	INT64		GetCurBidPrice() ;		// Current BidPrice
	INT64		GetNextBidPrice() ;		// Next BidPrice
	INT64		GetSpotPrice() ;		// SPotPrice
	int			GetCategory() ;			// ��� ī�װ�

	int			GetSellPoint()		{	return m_iSellPoint;	}		// ���� �Ĵ� ��� �ݾ�
	int			GetFeePoint()		{	return m_iFeePoint ;	}

private:
	bool SetItem(ITEM* pItem) ;
	bool SetItem(int iSellPoint, int iFeePoint) ;
	bool SetHeader(AUCTION_HEADER* pHeader);


private:
	AUCTION_TYPE	m_iAuctionType ;		//
	AUCTION_HEADER	m_ctAuctionHeader ;

	SPItem*	m_pAuctionItem;
	int		m_iSellPoint;			// Ely, Cash, Mileage
	int		m_iFeePoint;			// ������
	int		m_iRecvTime ;			// ���� �ð� ����� ���� �ʿ�(Buy, Sale List)

};
