// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowAuction.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/


#pragma once

// Money Frame
#define WIID_AUCTION_MONEY_FRAME				(WIID_AUCTION + 1)
#define WIID_AUCTION_MONEY_FRAME_LEFT			(WIID_AUCTION + 2)
#define WIID_AUCTION_MONEY_FRAME_RIGHT			(WIID_AUCTION + 3)
#define WIID_AUCTION_MONEY_ELY_BG				(WIID_AUCTION + 4)
#define WIID_AUCTION_MONEY_ELY_TITLE			(WIID_AUCTION + 5)
#define WIID_AUCTION_MONEY_ELY_TEXT				(WIID_AUCTION + 6)
#define WIID_AUCTION_MONEY_ELY_ICON				(WIID_AUCTION + 7)
#define WIID_AUCTION_MONEY_POINT_BG				(WIID_AUCTION + 8)
#define WIID_AUCTION_MONEY_POINT_TITLE			(WIID_AUCTION + 9)
#define WIID_AUCTION_MONEY_POINT_TEXT			(WIID_AUCTION + 10)
#define WIID_AUCTION_MONEY_POINT_ICON			(WIID_AUCTION + 11)
#define WIID_AUCTION_MONEY_OZ_BG				(WIID_AUCTION + 12)
#define WIID_AUCTION_MONEY_OZ_TITLE				(WIID_AUCTION + 13)
#define WIID_AUCTION_MONEY_OZ_TEXT				(WIID_AUCTION + 14)
#define WIID_AUCTION_MONEY_OZ_ICON				(WIID_AUCTION + 15)

// MainFrame
#define WIID_AUCTION_MAIN_TAB				(WIID_AUCTION + 22)		// (+3)
#define WIID_AUCTION_MAIN_EQUIP				(WIID_AUCTION + 25)
#define WIID_AUCTION_MAIN_ITEM				(WIID_AUCTION + 26)
#define WIID_AUCTION_MAIN_CLOSE				(WIID_AUCTION + 27)
#define WIID_AUCTION_MAIN_TITLE_ICON		(WIID_AUCTION + 28)
#define WIID_AUCTION_MAIN_TITLE_TEXT		(WIID_AUCTION + 29)
#define WIID_AUCTION_MAIN_TITLE_LINE		(WIID_AUCTION + 30)

//////////////////////////////////////////////////////////////////////////
// Search
#define WIID_AUCTION_SEARCH_FRAME			(WIID_AUCTION + 101)
#define WIID_AUCTION_SEARCH_SEL_BG			(WIID_AUCTION + 102)		// ���� ���õ� �޴� ǥ��
#define WIID_AUCTION_SEARCH_SEL_ICON		(WIID_AUCTION + 103)
#define WIID_AUCTION_SEARCH_SEL_TEXT		(WIID_AUCTION + 104)
#define WIID_AUCTION_SEARCH_SEL_LINE		(WIID_AUCTION + 105)		// (+2)
#define WIID_AUCTION_SEARCH_MENU_BUTTON		(WIID_AUCTION + 111)		// AUCTION_MAX_MENU (+8)
#define WIID_AUCTION_SEARCH_MENU_ICON		(WIID_AUCTION + 121)		// AUCTION_MAX_MENU (+8)
#define WIID_AUCTION_SEARCH_MENU_TEXT		(WIID_AUCTION + 131)		// AUCTION_MAX_MENU (+8)
#define WIID_AUCTION_POPUP_FRAME			(WIID_AUCTION + 35)			// Search PopUP Menu
//#define WIID_AUCTION_POPUP_SELECT			(WIID_AUCTION + 36)			// PopUP Menu Select
#define WIID_AUCTION_POPUP_LIST				(WIID_AUCTION + 36)			// 3*20 (+60)

#define WIID_AUCTION_SEARCH_LIST_LINE		(WIID_AUCTION + 31)			// ����Ʈ ��� ����
#define WIID_AUCTION_SEARCH_LIST_BG			(WIID_AUCTION + 32)			// ����Ʈ ���

#define WIID_AUCTION_SEARCH_LIST_QUALITY	(WIID_AUCTION + 151)		// ǰ��
#define WIID_AUCTION_SEARCH_LIST_LEVEL		(WIID_AUCTION + 152)		// ����
#define WIID_AUCTION_SEARCH_LIST_DURATION	(WIID_AUCTION + 153)		// ������
#define WIID_AUCTION_SEARCH_LIST_FINISHTIME	(WIID_AUCTION + 154)		// ����
#define WIID_AUCTION_SEARCH_LIST_SELLER		(WIID_AUCTION + 155)		// �Ǹ���
#define WIID_AUCTION_SEARCH_LIST_PRICE		(WIID_AUCTION + 156)		// ���� ������
#define WIID_AUCTION_SEARCH_SORT_ARROW		(WIID_AUCTION + 161)		// Sort Arrow(+6)
#define WIID_AUCTION_SEARCH_LIST			(WIID_AUCTION + 171)		// 18*6 = (+108)
#define WIID_AUCTION_SEARCH_PAGE			(WIID_AUCTION + 821)		// �ϴ� ������ (+20)

#define WIID_AUCTION_SEARCH_BT_ITEM			(WIID_AUCTION + 301)		// ������ �˻� ���
#define WIID_AUCTION_SEARCH_BT_LEVEL_TITLE	(WIID_AUCTION + 302)		// ����
#define WIID_AUCTION_SEARCH_BT_LEVEL_DASH	(WIID_AUCTION + 303)
#define WIID_AUCTION_SEARCH_BT_LEVEL_MIN	(WIID_AUCTION + 304)
#define WIID_AUCTION_SEARCH_BT_LEVEL_MAX	(WIID_AUCTION + 306)
#define WIID_AUCTION_SEARCH_BT_QUAL_TITLE	(WIID_AUCTION + 308)		// ǰ��
#define WIID_AUCTION_SEARCH_BT_QUAL_COMBO	(WIID_AUCTION + 321)		// ǰ�� �޺� (+20)
#define WIID_AUCTION_SEARCH_BT_USEABLE_TITLE	(WIID_AUCTION + 309)	// ��� ���� ����
#define WIID_AUCTION_SEARCH_BT_USEABLE_BTN		(WIID_AUCTION + 310)	
#define WIID_AUCTION_SEARCH_BT_NAME_TITLE	(WIID_AUCTION + 311)		// �˻� ����
#define WIID_AUCTION_SEARCH_BT_NAME_BG		(WIID_AUCTION + 312)
#define WIID_AUCTION_SEARCH_BT_NAME_EDIT	(WIID_AUCTION + 313)

#define WIID_AUCTION_SEARCH_BT_MONEY		(WIID_AUCTION + 351)		// �ݾװ˻� ���
#define WIID_AUCTION_SEARCH_BT_MONEY_MIN	(WIID_AUCTION + 352)		// �ݾװ˻�(MIN) (+2)
#define WIID_AUCTION_SEARCH_BT_MONEY_DASH	(WIID_AUCTION + 354)		// �ݾװ˻�
#define WIID_AUCTION_SEARCH_BT_MONEY_MAX	(WIID_AUCTION + 355)		// �ݾװ˻�(MAX) (+2)
#define WIID_AUCTION_SEARCH_BT_MONEY_ICON	(WIID_AUCTION + 357)		// �ݾ� ������

#define WIID_AUCTION_SEARCH_BT_SEARCH		(WIID_AUCTION + 361)		// ã��
#define WIID_AUCTION_SEARCH_BT_CLOSE		(WIID_AUCTION + 362)		// ������

//////////////////////////////////////////////////////////////////////////
// Buy
#define WIID_AUCTION_BUY_FRAME				(WIID_AUCTION + 400)
#define WIID_AUCTION_BUY_LIST_LINE			(WIID_AUCTION + 401)		// ����Ʈ ��� ����
#define WIID_AUCTION_BUY_LIST_BG			(WIID_AUCTION + 402)		// ����Ʈ ���
#define WIID_AUCTION_BUY_BT_CLOSE			(WIID_AUCTION + 403)		// ������

#define WIID_AUCTION_BUY_LIST_QUALITY		(WIID_AUCTION + 411)		// ǰ��
#define WIID_AUCTION_BUY_LIST_LEVEL			(WIID_AUCTION + 412)		// ����
#define WIID_AUCTION_BUY_LIST_DURATION		(WIID_AUCTION + 413)		// ������
#define WIID_AUCTION_BUY_LIST_FINISHTIME	(WIID_AUCTION + 414)		// ����
#define WIID_AUCTION_BUY_LIST_SELLER		(WIID_AUCTION + 415)		// �Ǹ���
#define WIID_AUCTION_BUY_LIST_PRICE			(WIID_AUCTION + 416)		// ���� ������
#define WIID_AUCTION_BUY_SORT_ARROW			(WIID_AUCTION + 421)		// ���� ������ (+6)
#define WIID_AUCTION_BUY_LIST				(WIID_AUCTION + 441)		// 18*7 = (+126)
#define WIID_AUCTION_BUY_PAGE				(WIID_AUCTION + 851)		// �ϴ� ������ (+20)


//////////////////////////////////////////////////////////////////////////
// Sale
#define WIID_AUCTION_SALE_FRAME				(WIID_AUCTION + 600)

#define WIID_AUCTION_REGI_TITLE				(WIID_AUCTION + 601)		//  ���â
#define WIID_AUCTION_REGI_FRAME				(WIID_AUCTION + 602)
#define WIID_AUCTION_REGI_SALE_TITLE		(WIID_AUCTION + 603)
#define WIID_AUCTION_REGI_SALE_TEXT			(WIID_AUCTION + 604)
#define WIID_AUCTION_REGI_SALE_LEFT			(WIID_AUCTION + 605)
#define WIID_AUCTION_REGI_SALE_RIGHT		(WIID_AUCTION + 606)

#define WIID_AUCTION_REGI_ITEM_BG			(WIID_AUCTION + 608)		// ������ ���
#define WIID_AUCTION_REGI_ITEM				(WIID_AUCTION + 609)
#define WIID_AUCTION_REGI_ITEM_COUNT10		(WIID_AUCTION + 610)
#define WIID_AUCTION_REGI_ITEM_COUNT01		(WIID_AUCTION + 611)
#define WIID_AUCTION_REGI_ITEM_ARROW		(WIID_AUCTION + 612)
#define WIID_AUCTION_REGI_ITEM_HELP			(WIID_AUCTION + 613)
#define WIID_AUCTION_REGI_ITEM_HELP_MSG		(WIID_AUCTION + 614)
#define WIID_AUCTION_REGI_MONEY				(WIID_AUCTION + 615)		// ū �Ӵ� ������
#define WIID_AUCTION_REGI_MONEY_BG			(WIID_AUCTION + 616)		// ĳ��, ����Ʈ, ���� ���
#define WIID_AUCTION_REGI_MONEY_EDIT		(WIID_AUCTION + 617)
#define WIID_AUCTION_REGI_MONEY_ICON		(WIID_AUCTION + 618)
#define WIID_AUCTION_REGI_MONEY_HELP		(WIID_AUCTION + 619)

#define WIID_AUCTION_REGI_PRICE_FRAME		(WIID_AUCTION + 621)		// ��� ���� ���
#define WIID_AUCTION_REGI_PRICE_ST_TEXT		(WIID_AUCTION + 622)		// ��� ���۰�
#define WIID_AUCTION_REGI_PRICE_ST_BG		(WIID_AUCTION + 623)
#define WIID_AUCTION_REGI_PRICE_ST_EDIT		(WIID_AUCTION + 624)
#define WIID_AUCTION_REGI_PRICE_ST_ICON		(WIID_AUCTION + 625)
#define WIID_AUCTION_REGI_SPOT_ST_TEXT		(WIID_AUCTION + 626)		// ��� ���Ű�
#define WIID_AUCTION_REGI_SPOT_ST_BG		(WIID_AUCTION + 627)
#define WIID_AUCTION_REGI_SPOT_ST_EDIT		(WIID_AUCTION + 628)
#define WIID_AUCTION_REGI_SPOT_ST_ICON		(WIID_AUCTION + 629)
#define WIID_AUCTION_REGI_DURATION_BG		(WIID_AUCTION + 631)		// ��� �Ⱓ
#define WIID_AUCTION_REGI_DURATION_TITLE	(WIID_AUCTION + 632)
#define WIID_AUCTION_REGI_DURATION_TEXT		(WIID_AUCTION + 633)		// (+3)
#define WIID_AUCTION_REGI_DURATION_BTN		(WIID_AUCTION + 636)		// (+3)
#define WIID_AUCTION_REGI_DEPOSIT_BG		(WIID_AUCTION + 641)		// ������
#define WIID_AUCTION_REGI_DEPOSIT_TITLE		(WIID_AUCTION + 642)
#define WIID_AUCTION_REGI_DEPOSIT_TEXT		(WIID_AUCTION + 643)
#define WIID_AUCTION_REGI_DEPOSIT_ICON		(WIID_AUCTION + 644)

#define WIID_AUCTION_REGI_OK_BUTTON			(WIID_AUCTION + 646)		// ��� ���
#define WIID_AUCTION_REGI_CANCEL_BUTTON		(WIID_AUCTION + 647)		// ��� ��� �ʱ�ȭ

#define WIID_AUCTION_SALE_LIST_LINE1		(WIID_AUCTION + 651)		// ����Ʈ ���� ����
#define WIID_AUCTION_SALE_LIST_LINE2		(WIID_AUCTION + 652)		// ����Ʈ ��� ����
#define WIID_AUCTION_SALE_LIST_BG			(WIID_AUCTION + 653)		// ����Ʈ ���
#define WIID_AUCTION_SALE_BT_CLOSE			(WIID_AUCTION + 655)		// ������
#define WIID_AUCTION_SALE_TIP_BG			(WIID_AUCTION + 656)		// �������
#define WIID_AUCTION_SALE_TIP_MSG			(WIID_AUCTION + 657)		// �����޽���

#define WIID_AUCTION_SALE_LIST_QUALITY		(WIID_AUCTION + 661)		// ǰ��
#define WIID_AUCTION_SALE_LIST_FINISHTIME	(WIID_AUCTION + 662)		// ����
#define WIID_AUCTION_SALE_LIST_SELLER		(WIID_AUCTION + 663)		// �Ǹ���
#define WIID_AUCTION_SALE_LIST_PRICE		(WIID_AUCTION + 664)		// ���� ������
#define WIID_AUCTION_SALE_SORT_ARROW		(WIID_AUCTION + 671)		// ���� ������ (+6)
#define WIID_AUCTION_SALE_LIST				(WIID_AUCTION + 681)		// 18*7 = (+126)
#define WIID_AUCTION_SALE_PAGE				(WIID_AUCTION + 881)		// �ϴ� ������ (+20)


#define AUCTION_BG_IMG				10			// ��� �̹��� ���� (9+1)
#define AUCTION_MAX_MENU			8			// ī�װ� �޴��� ������ �ִ� 8
#define AUCTION_SEARCH_LIST			6			// �˻��ϱ� ��� ����
#define AUCTION_BUY_LIST			7			// ������Ȳ ��� ����
#define AUCTION_SALE_LIST			7			// ����ϱ� ��� ����
#define AUCTION_MAX_LIST_ITEM		18			// �Ѹ�ϴ� 18���� ������
#define AUCTION_BUNDLE_PAGE			10			// 10������ ������ ������
#define AUCTION_SEARCH_TIMER		3.0f		// SearchTimer



enum AUCTION_TAB
{
	AUCTION_SEARCH_TAB	= 0,
	AUCTION_BUY_TAB		= 1,
	AUCTION_SALE_TAB	= 2,
} ;


//////////////////////////////////////////////////////////////////////////
//	
//////////////////////////////////////////////////////////////////////////
// �޴��� Detail
struct AUCTION_MENU_DETAIL
{
	int			iDetail_ID ;		// Detail ID (�Һз� ID)
	std::string strDetail ;			// �Һз� �̸�
	RECT		rcIconSrc ;			// ���� ������ ��ǥ
	RECT		rcBigIconSrc ;		// ū ������ ��ǥ
};

// ��� �޴� LDT
struct AUCTION_SEARCH_MENU
{
	int			iItemID ;			// ItemID
	int			iCategory_ID ;		// Category ID
	std::string	strCategory ;		// ��з� �̸�
	RECT		rcIconSrc ;			// ������ ��ǥ
	std::vector<AUCTION_MENU_DETAIL*>	vpDetail ; 

	void Init() {
		iItemID			= 0 ;
		iCategory_ID	= 0 ;
		vpDetail.clear();
	}
	void Clear()
	{
		std::vector<AUCTION_MENU_DETAIL*>::iterator Iter = vpDetail.begin() ;
		for( ; Iter != vpDetail.end(); ++Iter )
		{
			SAFE_DELETE( *Iter ) ;
		}
		vpDetail.clear() ;
		iItemID			= 0 ;
		iCategory_ID	= 0 ;
	}
};




//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
enum CASH_TRADE ;
class SPWindow;
class SPWindowEdit;
class SPWindowAuctionListUNIT;
class SPWindowAuctionSaleUNIT;
class SPWindowRowUNIT;
class SPAuctionAttr ;
class SPItem;
class SPTimer;
struct AUCTION_TYPE_INFO;
struct AUCTION_SEARCH_KEY ;
enum AUCTION_SORT_KEY ;
class SPWindowAuction : public SPWindow
{
public:
	SPWindowAuction(WND_ID WndClassID , INSTANCE_ID InstanceID );
	SPWindowAuction( INSTANCE_ID InstanceID , int iX , int iY , int iCX , int iCY , SPWindow* pParent = NULL );
	virtual ~SPWindowAuction();

	virtual void	Init();
	virtual void	Clean();

	virtual void	Process( float fTime );
	virtual void	Render( float fTime );

	virtual void	Show( bool bWithChild = true );
	virtual void	Hide(bool bSendServer = true);

private:
	void InitMoneyFrame() ;
	void InitAllMoneyFrame() ;		// Ely & Point & Cash (ALL)
	void InitElyPointFrame() ;		// Ely & Point
	void InitElyCashFrame() ;		// Ely & Cash
	void InitElyFrame() ;			// Ely��

	void InitAuctionFrame() ;
	void InitBackground() ;

	void InitAuctionSearch() ;
	void InitAuctionSearchMenu() ;
	void InitAuctionPopMenu() ;

	void InitAuctionBuy() ;
	void InitAuctionSale() ;

	void InitShowAuctionSearch() ;
	void ShowAuctionSearch() ;
	void ShowAuctionBuy() ;
	void ShowAuctionSale() ;

	void UpdateSortArrow(AUCTION_TAB eTab) ;			// �Ǻ� Sort Arrow ����
	void UpdateMoneyFrame(CASH_TRADE eTrade) ;			// Localize�� ���� MoneyFrame Update

	//////////////////////////////////////////////////////////////////////////
	// Search
	void LoadMenuLDT() ;
	void SetPopMenu(int iSelCategory) ;						// Set & Show PopUp Menu (Animation-Set)
	void ShowPopMenu(int iSelCategory) ;					// Show Menu
	void HidePopMenu() ;									// Hide Menu
	void SetSelectedTitle(bool bClear=false) ;				// ���õ� �޴� ǥ��
	void ShowSearchList(int iPage) ;						// �ش� ������ ���̱�
	bool UpdateSearchKey() ;								// SearchKey ������ �����´�.
	void SetSearchBottomMenu(int iCategory, int iDetail, bool bInit=true) ;	// �ϴ��� ���ΰ˻� ǥ��
	void SetSearchSortButton(int iCategory) ;				// ī�װ����� Sort��ư�� ���� ǥ��
	bool CheckAuctionBidable(SPAuctionAttr* pItemAttr, bool isBid) ;	// ����/�ﱸ ���ɿ��� üũ
	void SetShowSearchGuide(bool bShowSearchGuide)			{	m_bShowSearchGuide = bShowSearchGuide ;		}

	//////////////////////////////////////////////////////////////////////////
	// Buy
	void ShowBuyList(int iPage) ;

	//////////////////////////////////////////////////////////////////////////
	// Sale
	void SetAuctionSaleType(bool bDefault = false) ;		// �Ǹ� Ÿ�� ����
	void SetAuctionSaleTypeIcon(AUCTION_TYPE eType) ;
	void SetSaleDuration(int iDuration = 0) ;				// ��űⰣ ����
	void SetSaleArrowIcon(int iIndex) ;						// Arrow Icon
	void ShowSaleList(int iPage) ;							// �ش� ������ ���̱�
	void InitBidMoney() ;									// ��Ű��� �ʱ�ȭ
	void UpdateEnrolFee(bool bInit=false) ;					// ��Ϻ����� ������Ʈ
	bool CheckCreateItem(AUCTION_TYPE_INFO* pAuctionTypeInfo) ;	// ������ ��� ��ȿüũ
	bool CheckSaleItem(bool bDrag=true , SPItem* pClickItem=NULL ) ;	// Drag or Shift+Click ������ üũ
	bool SetSaleItemInfo( SPItem* pkItem = NULL ) ;			// �Ǹ� ������ ����
	SPItem* GetDragItem();									// Drag Item Check
	void SetSaleItemCount(int iCount) ;						// �Ǹ� ������ ���� ǥ��
	void SetAuctionItemLock( SPItem* pkItem , int iIndex ) ;// ��� �������� Blocking
	void SetAcutionItemAllUnlock() ;




private:
	SPWindow*	m_pWindowSearch;
	SPWindow*	m_pWindowBuy;
	SPWindow*	m_pWindowSale;
	SPWindow*	m_pWindowSearchPopup;
	SPWindow*	m_pWindowSaleTip;
	SPWindow*	m_pAuctionMsg ;
	SPWindow*	m_pSearchSort[AUCTION_SORT_MAX] ;
	SPWindow*	m_pBuySort[AUCTION_SORT_MAX] ;
	SPWindow*	m_pSaleSort[AUCTION_SORT_MAX] ;

	SPWindowAuctionListUNIT*	m_pWindowSearchList[AUCTION_SEARCH_LIST];
	SPWindowAuctionListUNIT*	m_pWindowBuyList[AUCTION_BUY_LIST];
	SPWindowAuctionSaleUNIT*	m_pWindowSaleList[AUCTION_SALE_LIST];

	SPWindowEdit*	m_pWindowSearchEdit;

	SPTexture*	m_pTextureBG;
	SPTexture*	m_pTextureGuide ;
	RECT		m_rcBGDest[ AUCTION_BG_IMG ];
	RECT		m_rcBGSrc[ AUCTION_BG_IMG ];
	RECT		m_rcGuideDest ;
	RECT		m_rcGuideSrc ;

	float		m_fMoneyUpdateTime ;		// ��� �Ӵ����� ������Ʈ(0.1�ʸ���)

	int			m_iSearchMenuMax ;			// ���θ޴��� MAX (Set in LoadLDT)
	int			m_iSearchPopMax ;			// �˾��޴��� MAX (Set in LoadLDT)

	int			m_iSelectedTab ;			// ���� �������� ��(1:Search, 2:Buy, 3:Sale)
	int			m_iPreShowPopup ;			// ���� ������ Popup Category (�˾� �޴��� ���� ȿ���� ����)
	int			m_iSelectedCategory ;		// Category
	int			m_iSelectedDetail ;			// Popup Menu

	std::string				m_strMenuIconPath ;				// �޴� ������ �ҽ�����
	AUCTION_SEARCH_MENU		m_stMenu[AUCTION_MAX_MENU] ;
	std::vector<SPWindowRowUNIT*>	m_vpPopMenu ;
	int			m_iPopMenuMode ;		// �޴� ����
	int			m_iPopMenuSize ;		// �޴� ������
	int			m_iPopMenuDestSize ;	// �޴� ���� ������

	int			m_iSearchQuality ;		// �˻� ǰ��
	int			m_bSearchUsable ;		// ��밡�� ���� üũ
	AUCTION_SEARCH_KEY*	m_pSearchKey ;		// �˻� Key
	AUCTION_SEARCH_KEY*	m_pSuccessKey ;	// ������ ������ SearchKey

	SPTimer*	m_pSearchTimer ;		// Search Timer (5Sed)
	SPWindow*	m_pSearchButton ;		// Search Button

	AUCTION_TYPE		m_iSaleType ;		// �Ǹ�����( ������/ĳ��/����Ʈ/����)
	int					m_iSaleIndex;		// �Ǹ����� Index 
	AUCTION_DURATION	m_iSaleDuration ;	// ��űⰣ ����( �ܱ�/�߱�/���)
	AUCTION_TYPE_INFO*	m_pSaleTypeInfo ;	// �Ǹ� ������ ����
	int					m_iSaleArrowIndex ;	// �Ǹ� ȭ��ǥ Index
	SPTimer*			m_pSaleTimer ;		// �Ǹ� ȭ��ǥ Timer
	SPTimer*			m_pSaleTipTimer ;	// ������ ����Ÿ�̸�
	SPItem*				m_pSaleItem ;		// �Ǹ� ������
	int					m_iSaleMoney ;		// �Ǹ� �ݾ�(�ִ� 9��)
	INT64				m_iSaleStartMoney ;	// ��� ���۰�
	INT64				m_iSaleSpotMoney ;	// ��� �ﱸ��
	INT64				m_iEnrolFee ;		// ��� ������

	int			m_iSearchCurPage ;		// �˻����� ���� �����ִ� ������
	int			m_iBuyCurPage ;			// �������� ���� �����ִ� ������
	int			m_iSaleCurPage ;		// ����ϱ⿡�� ���� �����ִ� ������
	bool		m_bShowSearchGuide ;	// �˻� ���� �����ֱ�
	bool		m_bTest ;				// �׽�Ʈ

protected:

	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	virtual int OnAuctionServerClose(WPARAM wParam, LPARAM lParam) ;		// Server Down
	virtual int OnAuctionMoneyUpdate(WPARAM wParam, LPARAM lParam) ;		// Money Update
	virtual int OnAuctionSetSearchName(WPARAM wParam, LPARAM lParam) ;		// Shift+Click -> Search Name
	//virtual int OnAuctionErrorNotice(WPARAM wParam, LPARAM lParam) ;		// MSG_TYPE, MSG

	virtual int OnSendAuctionSpotBuy(WPARAM wParam, LPARAM lParam) ;
	virtual int OnSendAuctionBidBuy(WPARAM wParam, LPARAM lParam) ;
	virtual int OnSendAuctionGetNext(WPARAM wParam, LPARAM lParam) ;
	virtual int OnSendAuctionSaleCancel(WPARAM wParam, LPARAM lParam) ;

	virtual int OnMainSearch(WPARAM wParam, LPARAM lParam);
	virtual int OnMainBuy(WPARAM wParam, LPARAM lParam);
	virtual int OnMainSale(WPARAM wParam, LPARAM lParam);
	virtual int OnMyEquip(WPARAM wParam, LPARAM lParam);
	virtual int OnMyInven(WPARAM wParam, LPARAM lParam);
	virtual int OnClose(WPARAM wParam, LPARAM lParam);
	virtual	int OnActivate(WPARAM wParam, LPARAM lParam) ;
	virtual	int OnFocus(WPARAM wParam, LPARAM lParam) ;

	// Search
	virtual int OnReceiveAuctionSearchList(WPARAM wParam, LPARAM lParam);		// ����Ʈ
	virtual int OnCategorySelect(unsigned int iID, WPARAM wParam, LPARAM lParam);
	virtual int OnDetailSelect(unsigned int iID, WPARAM wParam, LPARAM lParam);
	virtual	int OnCategoryIconCursorON(unsigned int iID, WPARAM wParam, LPARAM lParam) ;
	virtual int OnCategoryIconCursorOUT(unsigned int iID, WPARAM wParam, LPARAM lParam) ;
	virtual	int OnCategoryTextCursorON(unsigned int iID, WPARAM wParam, LPARAM lParam) ;
	virtual int OnCategoryTextCursorOUT(unsigned int iID, WPARAM wParam, LPARAM lParam) ;
	virtual int OnSearchListBidClick(unsigned int iID, WPARAM wParam, LPARAM lParam);	// ����
	virtual int OnSearchListSpotClick(unsigned int iID, WPARAM wParam, LPARAM lParam);	// ��ñ���
	virtual int OnSearchListClick(unsigned int iID, WPARAM wParam, LPARAM lParam);		// ����Ʈ ����
	virtual int OnSearchListPage(WPARAM wParam, LPARAM lParam);
	virtual int OnChangeSearchCombo(WPARAM wParam, LPARAM lParam);

	virtual int OnSortSearchQuality(WPARAM wParam, LPARAM lParam);		// ���� (ǰ��)
	virtual int OnSortSearchLevel(WPARAM wParam, LPARAM lParam);		// ���� (����)
	virtual int OnSortSearchDuration(WPARAM wParam, LPARAM lParam);		// ���� (������)
	virtual int OnSortSearchFinish(WPARAM wParam, LPARAM lParam);		// ���� (����)
	virtual int OnSortSearchPrice(WPARAM wParam, LPARAM lParam);		// ���� (������)

	virtual int OnSearchUsableCheck(WPARAM wParam, LPARAM lParam);		// ��밡���� ���� üũ
	virtual int OnSearchNameSetFocus(WPARAM wParam, LPARAM lParam);		// �˻� �̸� SetFocus
	virtual int OnSearchNameKillFocus(WPARAM wParam, LPARAM lParam);	// �˻� KillFocus
	virtual int OnSearchItem(WPARAM wParam, LPARAM lParam);				// ã�� ��ư


	// Buy
	virtual int OnReceiveAuctionBuyList(WPARAM wParam, LPARAM lParam);			// ����Ʈ
	//virtual int OnReceiveAuctionBuyUpdate(WPARAM wParam, LPARAM lParam);		// ����Ʈ ������Ʈ
	virtual int OnSortBuyQuality(WPARAM wParam, LPARAM lParam);		// ���� (ǰ��)
	virtual int OnSortBuyLevel(WPARAM wParam, LPARAM lParam);		// ���� (����)
	virtual int OnSortBuyDuration(WPARAM wParam, LPARAM lParam);	// ���� (������)
	virtual int OnSortBuyFinish(WPARAM wParam, LPARAM lParam);		// ���� (����)
	virtual int OnSortBuyPrice(WPARAM wParam, LPARAM lParam);		// ���� (������)
	virtual int OnBuyListBidClick(unsigned int iID, WPARAM wParam, LPARAM lParam);		// ����
	virtual int OnBuyListSpotClick(unsigned int iID, WPARAM wParam, LPARAM lParam);		// ��� ����
	virtual int OnBuyListPage(WPARAM wParam, LPARAM lParam);

	// Sale
	virtual int OnReceiveAuctionSaleList(WPARAM wParam, LPARAM lParam);			// ����Ʈ
	//virtual int OnReceiveAuctionSaleUpdate(WPARAM wParam, LPARAM lParam);		// ����Ʈ ������Ʈ
	virtual int OnSaleRegistryLeft(WPARAM wParam, LPARAM lParam);		// ���Ÿ�� ����(����)
	virtual int OnSaleRegistryRight(WPARAM wParam, LPARAM lParam);		// ���Ÿ�� ����(������)
	virtual int OnSaleItemButtonUp(WPARAM wParam, LPARAM lParam);		// ������ �巡��
	virtual int	OnSaleItemToolTipEnter(WPARAM wParam, LPARAM lParam);	// �Ǹ� ��� ������ Tooltip
	virtual int	OnSaleItemToolTipOut(WPARAM wParam, LPARAM lParam);		// �Ǹ� ��� ������ Tooltip
	virtual int	OnSaleItemToolTipMove(WPARAM wParam, LPARAM lParam);	// �Ǹ� ��� ������ Tooltip
	virtual int OnSaleMoneyKeyDown(WPARAM wParam, LPARAM lParam);		// ��� ���۱ݾ��Է�
	virtual int OnSaleDuration(unsigned int iID, WPARAM wParam, LPARAM lParam);		// ��� �Ⱓ����
	virtual int OnSaleRegistItem(WPARAM wParam, LPARAM lParam);			// ������ ����ϱ�
	virtual int OnSaleClearItem(WPARAM wParam, LPARAM lParam);			// ������ ������
	virtual int OnSortSaleQuality(WPARAM wParam, LPARAM lParam);		// ���� (ǰ��)
	virtual int OnSortSaleFinish(WPARAM wParam, LPARAM lParam);			// ���� (����)
	virtual int OnSortSalePrice(WPARAM wParam, LPARAM lParam);			// ���� (������)
	virtual int OnSaleListCancelClick(unsigned int iID, WPARAM wParam, LPARAM lParam);
	virtual int OnSaleListPage(WPARAM wParam, LPARAM lParam);

	// }}


};



