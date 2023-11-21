#pragma once


#define WIID_CASH_TRADE_SELECT_BASE					(WIID_CASH_TRADE_SELECT	+	1 )
#define WIID_CASH_TRADE_SELECT_ITEM_NAME			(WIID_CASH_TRADE_SELECT	+	10 )

#define WIID_CASH_TRADE_SELECT_CLOSE				(WIID_CASH_TRADE_SELECT	+	20 )
#define WIID_CASH_TRADE_SELECT_WISH					(WIID_CASH_TRADE_SELECT	+	30 )		/**< �� <br> */
#define WIID_CASH_TRADE_SELECT_GIFT					(WIID_CASH_TRADE_SELECT	+	40 )
#define WIID_CASH_TRADE_SELECT_BUY					(WIID_CASH_TRADE_SELECT	+	50 )

#define WIID_CASH_TRADE_SELECT_MALE					(WIID_CASH_TRADE_SELECT	+	60 )		/**< ���� <br> */
#define WIID_CASH_TRADE_SELECT_FEMALE				(WIID_CASH_TRADE_SELECT	+	61 )

#define WIID_CASH_TRADE_SELECT_ITEMBUTTON			(WIID_CASH_TRADE_SELECT	+	70 )
#define WIID_CASH_TRADE_SELECT_ITEMSKIN				(WIID_CASH_TRADE_SELECT	+	71 )
#define WIID_CASH_TRADE_SELECT_ITEMICON				(WIID_CASH_TRADE_SELECT	+	72 )
#define WIID_CASH_TRADE_SELECT_ITEMEVENT			(WIID_CASH_TRADE_SELECT	+	73 )		/**< Event Icon <br> */

#define WIID_CASH_TRADE_SELECT_COSTSKIN				(WIID_CASH_TRADE_SELECT	+	80 )
#define WIID_CASH_TRADE_SELECT_COST					(WIID_CASH_TRADE_SELECT	+	81 )
#define WIID_CASH_TRADE_SELECT_COSTICON				(WIID_CASH_TRADE_SELECT	+	82 )


class SPWindowCashTradeSelect : public SPWindow {

public:	
	SPWindowCashTradeSelect(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowCashTradeSelect();

	virtual void Init();
	virtual void Clean();

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);


	virtual void Process(float fTime);
	virtual void Render(float fTime);

protected:
	void SetWindowBase();
	void InitSubControl();
	bool UpdateControl();

	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnClose					(WPARAM wParam, LPARAM lParam);
	int OnWish					(WPARAM wParam, LPARAM lParam);
	int OnGift					(WPARAM wParam, LPARAM lParam);
	int OnBuy					(WPARAM wParam, LPARAM lParam);
	// }}

private:
	SPTexture* m_pBaseSkin;
	RECT m_rtBaseSrc[WINDOW_BASE_MAX];
	RECT m_rtBaseDest[WINDOW_BASE_MAX];

	SPTexture* m_pDisable;							/**< ��Ȱ�� ǥ���� <br> */
	RECT m_rtSrcDisable;							/**< ��Ȱ�� ǥ���� �ҽ� <br> */
	RECT m_rtMarkSrc[4];							/**< ICON MARK Src <br> */

	SPWindow*	m_pItemName;						/**< ������ �̸� <br> */
	SPWindow*	m_pCost;							/**< ������ ���� <br> */
	SPWindow*	m_pCostIcon;						/**< ������ ���� ���� ĳ������ ����Ʈ���� <br> */
	SPWindow*	m_pMaleIcon;						/**< ������ ���� <br> */
	SPWindow*	m_pFeMaleIcon;						/**< ������ ���� <br> */
	SPWindow*	m_pItemIcon;						/**< ������ ������ <br> */
	SPWindow*	m_pItemEvent;						/**< ������ �̺�Ʈ ������ <br> */
};


