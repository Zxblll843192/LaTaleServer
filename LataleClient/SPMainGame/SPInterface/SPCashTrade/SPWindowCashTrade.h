#pragma once


#define WIID_CASH_TRADE_TOP						(WIID_CASH_TRADE	+	10 )
#define WIID_CASH_TRADE_CENTER					(WIID_CASH_TRADE	+	20 )
#define WIID_CASH_TRADE_BOTTOM					(WIID_CASH_TRADE	+	30 )

#define WIID_CASH_TRADE_OK						(WIID_CASH_TRADE	+	40 )
#define WIID_CASH_TRADE_CANCEL					(WIID_CASH_TRADE	+	41 )
#define WIID_CASH_TRADE_HELP					(WIID_CASH_TRADE	+	42 )

#define WIID_CASH_TRADE_ITEMSKIN				(WIID_CASH_TRADE	+	50 )
#define WIID_CASH_TRADE_ITEM					(WIID_CASH_TRADE	+	51 )
#define WIID_CASH_TRADE_ITEMNAME				(WIID_CASH_TRADE	+	52 )

#define WIID_CASH_TRADE_COSTSKIN				(WIID_CASH_TRADE	+	60 )
#define WIID_CASH_TRADE_COST					(WIID_CASH_TRADE	+	61 )
#define WIID_CASH_TRADE_COSTICON				(WIID_CASH_TRADE	+	62 )

#define WIID_CASH_TRADE_CUR_CASH_TEXTIMG 		(WIID_CASH_TRADE	+	70 )		/**< ������ ���� �ؽ�Ʈ �̹��� <br> */
#define WIID_CASH_TRADE_CUR_CASH				(WIID_CASH_TRADE	+	71 )
#define WIID_CASH_TRADE_CUR_CASH_ICON			(WIID_CASH_TRADE	+	72 )

#define WIID_CASH_TRADE_USE_CASH_TEXTIMG		(WIID_CASH_TRADE	+	80 )		/**< ����� ���� �ؽ�Ʈ �̹��� <br> */
#define WIID_CASH_TRADE_USE_CASH				(WIID_CASH_TRADE	+	81 )
#define WIID_CASH_TRADE_USE_CASH_ICON			(WIID_CASH_TRADE	+	82 )

#define WIID_CASH_TRADE_USE_POINT_TEXTIMG		(WIID_CASH_TRADE	+	90 )		/**< ����� ����Ʈ �ؽ�Ʈ �̹��� <br> */
#define WIID_CASH_TRADE_USE_POINT				(WIID_CASH_TRADE	+	91 )
#define WIID_CASH_TRADE_USE_POINT_ICON			(WIID_CASH_TRADE	+	92 )
#define WIID_CASH_TRADE_USE_POINT_INC			(WIID_CASH_TRADE	+	93 )		/**< ����Ʈ ���� <br> */
#define WIID_CASH_TRADE_USE_POINT_DEC			(WIID_CASH_TRADE	+	94 )		/**< ����Ʈ ���� <br> */

#define WIID_CASH_TRADE_PAY_TEXTIMG				(WIID_CASH_TRADE	+	100 )		/**< ������ �ݾ� �ؽ�Ʈ �̹��� <br> */
#define WIID_CASH_TRADE_PAY						(WIID_CASH_TRADE	+	101 )
#define WIID_CASH_TRADE_PAY_ICON				(WIID_CASH_TRADE	+	102 )

#define WIID_CASH_TRADE_CHANGE_TEXTIMG			(WIID_CASH_TRADE	+	110 )		/**< ������ �ݾ� �ؽ�Ʈ �̹��� <br> */
#define WIID_CASH_TRADE_CHANGE					(WIID_CASH_TRADE	+	111 )
#define WIID_CASH_TRADE_CHANGE_ICON				(WIID_CASH_TRADE	+	112 )

struct SPCashItemAttr;

class SPWindowCashTrade : public SPWindow {

public:	
	SPWindowCashTrade(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowCashTrade();

	virtual void Init();
	virtual void Clean();

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);


	virtual void Process(float fTime);
	virtual void Render(float fTime);

protected:
	void InitSubControl();
	
	void UpdatePointControl(SPCashItemAttr* pCashItem);	

	bool UpdateControl();

	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnOk					(WPARAM wParam, LPARAM lParam);
	int OnCancel				(WPARAM wParam, LPARAM lParam);
	int OnPointInc				(WPARAM wParam, LPARAM lParam);
	int OnPointDec				(WPARAM wParam, LPARAM lParam);
	// }}

private:
	int			m_iPointTradeUnit;

	SPWindow*	m_pItemName;						/**< ������ �̸� <br> */
	SPWindow*	m_pCost;							/**< ������ ���� <br> */
	SPWindow*	m_pCostIcon;						/**< ������ ���� ���� ĳ������ ����Ʈ���� <br> */
	SPWindow*	m_pItemIcon;						/**< ������ ������ <br> */

	SPWindow*	m_pCurCash;							/**< ������ ���� <br> */
	SPWindow*	m_pUseCash;							/**< ����� ���� <br> */
	int			m_iUseCash;							/**< <br> */
	
	SPWindow*	m_pUsePoint;						/**< ����� ����Ʈ <br> */
	int			m_iUsePoint;						/**< ����� ����Ʈ <br> */	

	SPWindow*	m_pPayCash;							/**< ������ �ݾ� <br> */
	SPWindow*	m_pPayIcon;							/**< ������ �ݾ� ������ <br> */
	
	SPWindow*	m_pChangeCash;						/**< ������ �ܾ� <br> */
	int			m_iChangeCash;						/**< <br> */
	SPWindow*	m_pChangeIcon;						/**< ������ �ܾ� ������ <br> */

	SPWindow*	m_pHelp;
};
