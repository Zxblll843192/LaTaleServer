// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionDef.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/

#pragma once

enum AUCTION_ARCH_DATA
{
	AUCTION_ARCH_NULL = 0,
	AUCTION_ARCH_ALL,			// ��ü ��ϰ���
	AUCTION_ARCH_PART,			// �Ϻ� ��� ����
} ;

enum AUCTION_ARCH_TAB
{
	AUCTOIN_ARCH_NULL = 0,
	AUCTOIN_ARCH_SEARCH ,
	AUCTOIN_ARCH_BUY ,
	AUCTOIN_ARCH_SALE ,
} ;

struct AUCTION_TYPE_INFO
{
	AUCTION_TYPE	iSaleType ;			// ��� Ÿ�� (PacketID.h)
	bool			bRegistCharge ;		// ��Ϻ�� ¡������
	UINT32			iConsumeItem ;		// ��� �Һ������
	int				iShortRate ;		// �ܱ� ��Ϻ� ����
	int				iMiddleRate ;		// �߱� ��Ϻ� ����
	int				iLongRate ;			// ��� ��Ϻ� ����

	void Clear()
	{
		iSaleType = AUCTION_TYPE_NULL ;
		bRegistCharge = false ;
		iConsumeItem = 0 ;
		iShortRate = 0 ;
		iMiddleRate = 0 ;
		iLongRate = 0 ;
	}
	int GetPeriodRate(int iPeriod)
	{
		if( iPeriod == 0)		return iShortRate ;
		else if( iPeriod == 1)	return iMiddleRate ;
		else					return iLongRate ;
	}
};


struct AUCTION_LIST_INFO
{
	AUCTION_TYPE	iSaleType ;			// ��� Ÿ�� (PacketID.h)
	bool			bRegistCharge ;		// ��Ϻ�� ¡������
	UINT32			iConsumeItem ;		// ��� �Һ������
	float			fShortRate ;		// �ܱ� ��Ϻ� ����
	float			fMiddleRate ;		// �߱� ��Ϻ� ����
	float			fLongRate ;			// ��� ��Ϻ� ����

	void Clear()
	{
		iSaleType = AUCTION_TYPE_NULL ;
		bRegistCharge = false ;
		iConsumeItem = 0 ;
		fShortRate = 0 ;
		fMiddleRate = 0 ;
		fLongRate = 0 ;
	}
};


/**
	��ſ��� ����Ǵ� Search Condition
*/
struct AUCTION_SEARCH_KEY
{
	int		iCategoryID ;
	short	iMinLevel ;		// �ּҷ��� (1)
	short	iMaxLevel ;		// �ִ뷹�� (999)
	INT8	iQuality ;
	int		iMoneyMin ;		// �Ӵϰ˻�
	int		iMoneyMax ;		// �Ӵϰ˻�
	TCHAR	szName[MAX_ITEM_NAME+1] ;

	void Clear()
	{
		iCategoryID	= 0 ;
		iMinLevel	= 1 ;
		iMaxLevel	= 999 ;
		iQuality	= 0 ;	// Total(0)
		iMoneyMin	= 0 ;
		iMoneyMax	= 0 ;
		memset(&szName, 0, MAX_ITEM_NAME+1);
	}
	void Copy(AUCTION_SEARCH_KEY* Src) {
		iCategoryID = Src->iCategoryID ;
		iMinLevel	= Src->iMinLevel ;
		iMaxLevel	= Src->iMaxLevel ;
		iQuality	= Src->iQuality ;
		iMoneyMin	= Src->iMoneyMin ;
		iMoneyMax	= Src->iMoneyMax ;
		strcpy(szName, Src->szName) ;
	}
};