// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionMock.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/


#pragma once 

enum AUCTION_TYPE ;
class SPItem ;
class SPAuctionMock
{

public:	
	SPAuctionMock() ;
	~SPAuctionMock() ;

	void Init() ;
	void Clear() ;

	void SendAuctionSearchList(int iStart, int iSize) ;
	void SendAuctionBuyList(int iSize) ;
	void SendAuctionSaleList(int iSize) ;

	void ProcessAuctionCreate(CPacket* pRecvPacket) ;		// ��ǰ��� ��Ŷ
	void ProcessAuctionBid(CPacket* pRecvPacket) ;			// ���� ��Ŷ
	void ProcessAuctionSpot(CPacket* pRecvPacket) ;			// �ﱸ ��Ŷ
	void ProcessAuctionCancel(CPacket* pRecvPacket) ;		// ���� ��� ��Ŷ

	void MakeAuctionListMoney(int& iMoney, int& iFeeMoney) ;
	bool MakeAuctionListItem(ITEM& ctItem, int iIndex = 0);

	void MakeAuctionListHeader(AUCTION_HEADER& ctHeader);

	void MakePreviousBidderString(std::string& str) ;
	void MakePreviousSellerString(std::string& str) ;
	void MakePreviousItemID(ITEMID& iID) ;
	void MakePreviousItemID(ITEMID& iID, int iIndex) ;

	template<class T> 
		T MakeRandomValue(T tStart, T tEnd) ;

private:
	INT64 m_iAuctionID ;
};


