// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionManager.h
//	created:	2008/2/26   Time:11:00
//	purpose:	
//*********************************************************************/

#pragma once 

struct AUCTION_SEARCH_KEY ;
struct AUCTION_TYPE_INFO ;
class SPAuctionAttr ;
class SPAuctionArchive ;
class SPItem ;
class SPAuctionManager
{
public:

	static SPAuctionManager* GetInstance();
	static void Release();

	bool	Init();
	void	Clear();
	void	Process(float fTime);

	SPAuctionArchive* GetAuctionSearchArchive() ;
	SPAuctionArchive* GetAuctionBuyArchive() ;
	SPAuctionArchive* GetAuctionSaleArchive() ;

	bool	CheckAuctionValid() ;					// Auction ���ۿ� �ʿ��� Valid üũ
	bool	CheckArchiveReset(int iTab) ;			// Archive ������ �ʿ����� üũ
	void	SetAuctionReset() ;						// Player����� Archive Reset
	void	SetServerOpen(bool bOpen) ;				// Set Auction Server Open
	bool	GetServerOpen() ;						// Get Auction Server Open

	// Packet
	void	SendAuctionSearch(AUCTION_SEARCH_KEY* pSearchKey) ;						// �˻�
	void	SendAuctionSearchNext(int iWantIndex, AUCTION_SEARCH_KEY* pSearchKey) ;	// ����
	void	SendAuctionSearchSort(AUCTION_SEARCH_KEY* pSearchKey) ;					// Sort
	void	SendAuctionBuyRequest() ;				// ������Ȳ ����Ʈ ��û
	void	SendAuctionSaleRequest() ;				// ����ϱ�(���) ����Ʈ ��û
	void	SendAuctionBidBuy(SPAuctionAttr* pAuctionAttr) ;				// ����
	void	SendAuctionSpotBuy(AUCTION_SEARCH_KEY* pSearchKey, int iWantIndex, SPAuctionAttr* pAuctionAttr) ;	// ��ñ���
	void	SendAuctionSaleItem(SPItem* pItem, INT64 iStMoney, INT64 iSpotMoney, int iDuration, INT64 iEnrolFee) ;			// ������ ���
	void	SendAuctionSaleMoney(int iType, int iMoney, INT64 iStMoney, INT64 iSpotMoney, int iDuration, INT64 iEnrolFee) ;	// �Ӵ� ���
	void	SendAuctionSaleCancel(SPAuctionAttr* pAuctionAttr) ;		// ��� ���

	void	OnRecvAuctionSearchList(void* pPacket) ;	// Search ���
	void	OnRecvAuctionBuyList(void* pPacket) ;		// ���� ���
	void	OnRecvAuctionSaleList(void* pPacket) ;		// �Ǹ� ���
	void	OnRecvAuctioinOpen() ;						// ��ż��� Reset
	void	OnRecvAuctionCreate(void* pPacket) ;		// ��� ���
	void	OnRecvAuctionFinish(void* pPacket) ;		// ��� ���(����, ��ҽ�:����, �Ǹ���)
	void	OnRecvAuctionFinishSell(void* pPacket) ;	// ���� ���(������:����, �Ǹ���)
	void	OnRecvAuctionCancel(void* pPacket) ;		// ��� ���(�����)
	void	OnRecvAuctionBuyOut(void* pPacket) ;		// �ﱸ ���(������)
	void	OnRecvAuctionBidUpdate(void* pPacket) ;		// ���� ���(����, �Ǹ�, ����������)
	void	OnRecvAuctionBidDelete(void* pPacket) ;		// ���� ���(����������)


	//////////////////////////////////////////////////////////////////////////
	// for Auction Type
	AUCTION_TYPE_INFO*	GetAuctionTypeInfo(int iAuctionTypeID) ;
	int		GetAuctionTypeID(int iIndex);		// ������ Type�� ������
	int		GetAuctionTypeCount() ;
	int		GetAuctionFeeRate() ;		// ��� ������
	int		GetAuctionTimeShort() ;		// ��� �ð�(�ܱ�)
	int		GetAuctionTimeMiddle() ;	// ��� �ð�(�߱�)
	int		GetAuctionTimeLong() ;		// ��� �ð�(�����)
	int		GetSysMoneyID() ;
	int		GetSysGamePriceID() ;
	int		GetSysStandardPriceID() ;
	int		GetSysStartMoneyID() ;
	INT64	GetPlayerEly() ;		// Player Ely ����
	int		GetPlayerCash() ;		// Player Cash ����
	int		GetPlayerMilige() ;		// Player Milige ����
	void	UpdatePlayerEly(INT64 iEly) ;					// PlayerStatus ���� ������Ʈ
	void	UpdatePlayerCash(int iCash, int iMilige) ;		// PlayerStatus ���� ������Ʈ
	INT64	ComputeEnrolFee(AUCTION_TYPE eType, INT64 iStart, int iDuration, int iValue, int iLv=0, int iGamePrice=0, int iGameCount=0);	// ��Ϻ��		
	int		UpdateAuctionFinish(INT64 iAuctionID, bool bSearch) ;		// ������ ������Archive �� Return
	void	SetDefaultSort(int iArchiveType) ;				// Archive Sort Reset (0:Buy, 1:Sale)

protected:
	SPAuctionManager();
	virtual ~SPAuctionManager();

	bool LoadAuctionTypeLDT();


protected:
	static SPAuctionManager*	m_pkInstance;

	SPAuctionArchive*	m_pSearchArchive ;		// �˻� ���
	SPAuctionArchive*	m_pBuyArchive ;			// ���� ���
	SPAuctionArchive*	m_pSaleArchive ;		// �Ǹ� ���

	bool				m_bOpen ;				// ����� ���� ����
	bool				m_bValid;				// ����� ���� ����
	int					m_iSearch ;				// Search���� (0:GetNext, 1:Search, 2:Sort))
	int					m_iAuctionTypeCount ;
	int					m_iSysAuctionMoneyID ;	// GlobalSys�� ������
	int					m_iSysGamePriceID ;		// GlobalSys�� ������
	int					m_iSysStandardPriceID ;	// GlobalSys�� ������
	int					m_iSysStartMoneyID ;	// GlobalSys�� ������(���۰�)
	AUCTION_TYPE_INFO*	m_ctAuactionType[5] ;
	bool				m_bTest ;				// �׽�Ʈ ������ ó������

};

extern SPAuctionManager* g_pkAuctionManager;
