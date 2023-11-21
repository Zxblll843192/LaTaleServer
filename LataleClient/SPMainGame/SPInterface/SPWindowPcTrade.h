#pragma once

//#define WIID_PC_TRADE_TOP				(WIID_PC_TRADE	+	1)		//��Ų TOP
#define WIID_PC_TRADE_CENTER			(WIID_PC_TRADE	+	2)		//��Ų CENTER
//#define WIID_PC_TRADE_SUB_TOP			(WIID_PC_TRADE	+	3)		//��Ų SUB_TOP
//#define WIID_PC_TRADE_SUB_HLINE1		(WIID_PC_TRADE	+	4)		//��Ų SUB_HLINE1
//#define WIID_PC_TRADE_SUB_BOTTOM		(WIID_PC_TRADE	+	5)		//��Ų SUB_BOTTOM
//#define WIID_PC_TRADE_SUB_HLINE2		(WIID_PC_TRADE	+	6)		//��Ų SUB_HLINE2
//#define WIID_PC_TRADE_BOTTOM			(WIID_PC_TRADE	+	7)		//��Ų BOTTOM

#define WIID_PC_TRADE_TITLE				(WIID_PC_TRADE	+	10)		//����
#define WIID_PC_TRADE_LINE1				(WIID_PC_TRADE	+	11)		//�����ϴ� ���1
#define WIID_PC_TRADE_HIDE				(WIID_PC_TRADE	+	20)		//�����ư
#define WIID_PC_TRADE_ACCEPT			(WIID_PC_TRADE	+	30)		//������ư
#define WIID_PC_TRADE_CANCEL			(WIID_PC_TRADE	+	40)		//��ҹ�ư
#define WIID_PC_TRADE_HELP				(WIID_PC_TRADE	+	50)		//����

//#define WIID_PC_TRADE_STATUS_WAIT		(WIID_PC_TRADE	+	100)	//�� �ŷ��غ����_�غ���
#define WIID_PC_TRADE_STATUS_ACCEPT		(WIID_PC_TRADE	+	110)	//�� �ŷ��غ����_�غ�Ϸ�
#define WIID_PC_TRADE_NAME_WAIT			(WIID_PC_TRADE	+	120)	//�� �̸� �غ��� 
#define WIID_PC_TRADE_NAME_ACCEPT		(WIID_PC_TRADE	+	121)	//�� �̸� �غ�Ϸ�
#define WIID_PC_TRADE_VLINE1			(WIID_PC_TRADE	+	130)	//������1
//#define WIID_PC_TRADE_PC_STATUS_WAIT	(WIID_PC_TRADE	+	140)	//��� �ŷ��غ����_�غ���
#define WIID_PC_TRADE_PC_STATUS_ACCEPT	(WIID_PC_TRADE	+	150)	//��� �ŷ��غ����_�غ�Ϸ�
#define WIID_PC_TRADE_PC_NAME_WAIT		(WIID_PC_TRADE	+	160)	//��� �̸� �غ�
#define WIID_PC_TRADE_PC_NAME_ACCEPT	(WIID_PC_TRADE	+	161)	//��� �̸� �غ� �Ϸ�

//#define WIID_PC_TRADE_PC_TEXT			(WIID_PC_TRADE	+	200)	//��� �ŷ��ؽ�Ʈ
#define WIID_PC_TRADE_PC_ITEM_BTN		(WIID_PC_TRADE	+	210)	//��� �������� ��ư(������)
#define WIID_PC_TRADE_PC_ITEM_ICONLINE	(WIID_PC_TRADE	+	220)	//��� �������� ICON������(�迭. 10���Ѱ�)
#define WIID_PC_TRADE_PC_ITEM_ICON		(WIID_PC_TRADE	+	230)	//��� �������� ICON(�迭. 10���Ѱ�)
#define WIID_PC_TRADE_PC_ITEM_TEXT		(WIID_PC_TRADE	+	240)	//��� �������� Text(�迭. 10���Ѱ�)

#define WIID_PC_TRADE_PC_ELY_BACK		(WIID_PC_TRADE	+	250)	//��� �ŷ� Ely ���
#define WIID_PC_TRADE_PC_ELY			(WIID_PC_TRADE	+	255)	//��� �ŷ� Ely
#define WIID_PC_TRADE_PC_ELYIMG			(WIID_PC_TRADE	+	260)	//��� �ŷ� Ely�̹���

#define WIID_PC_TRADE_PC_CASH_BACK		(WIID_PC_TRADE	+	270)	//��� �ŷ� Cash ��� 
#define WIID_PC_TRADE_PC_CASH			(WIID_PC_TRADE	+	271)	//��� �ŷ� Cash
#define WIID_PC_TRADE_PC_CASHIMG		(WIID_PC_TRADE	+	272)	//��� �ŷ� Cash�̹���
#define WIID_PC_TRADE_PC_CASHDIS		(WIID_PC_TRADE	+	273)	//��� �ŷ� Cash Disable ǥ��

#define WIID_PC_TRADE_PC_POINT_BACK		(WIID_PC_TRADE	+	280)	//��� �ŷ� Point ���
#define WIID_PC_TRADE_PC_POINT			(WIID_PC_TRADE	+	281)	//��� �ŷ� Point
#define WIID_PC_TRADE_PC_POINTIMG		(WIID_PC_TRADE	+	282)	//��� �ŷ� Point�̹���
#define WIID_PC_TRADE_PC_POINTDIS		(WIID_PC_TRADE	+	283)	//��� �ŷ� Point Disable ǥ��

#define WIID_PC_TRADE_PC_FEE_TEXT		(WIID_PC_TRADE	+	290)	//��� �ŷ� ������ �����̹���
#define WIID_PC_TRADE_PC_FEE_BACK		(WIID_PC_TRADE	+	291)	//��� �ŷ� Fee ���
#define WIID_PC_TRADE_PC_FEE			(WIID_PC_TRADE	+	292)	//��� �ŷ� Fee
#define WIID_PC_TRADE_PC_FEEIMG			(WIID_PC_TRADE	+	293)	//��� �ŷ� Fee�̹���

//#define WIID_PC_TRADE_VLINE2			(WIID_PC_TRADE	+	300)	//������2
//#define WIID_PC_TRADE_TEXT				(WIID_PC_TRADE	+	400)	//�� �ŷ��ؽ�Ʈ
#define WIID_PC_TRADE_ITEM_BTN			(WIID_PC_TRADE	+	410)	//�� �������� ��ư(������)
#define WIID_PC_TRADE_ITEM_ICONLINE		(WIID_PC_TRADE	+	420)	//�� �������� ICON������(�迭. 10���Ѱ�)
#define WIID_PC_TRADE_ITEM_ICON			(WIID_PC_TRADE	+	430)	//�� �������� ICON(�迭. 10���Ѱ�)
#define WIID_PC_TRADE_ITEM_TEXT			(WIID_PC_TRADE	+	440)	//�� �������� Text(�迭. 10���Ѱ�)

#define WIID_PC_TRADE_ELY_BASE			(WIID_PC_TRADE	+	450)	//�� �ŷ� Ely Base Skin
#define WIID_PC_TRADE_ELY				(WIID_PC_TRADE	+	451)	//�� �ŷ� Ely	//Edit Control
#define WIID_PC_TRADE_ELYIMG			(WIID_PC_TRADE	+	460)	//�� �ŷ� Ely�̹���

#define WIID_PC_TRADE_CASH_BACK			(WIID_PC_TRADE	+	470)	//�� �ŷ� Cash �Է� ����
#define WIID_PC_TRADE_CASH				(WIID_PC_TRADE	+	471)	//�� �ŷ� Cash Edit
#define WIID_PC_TRADE_CASH_UNIT			(WIID_PC_TRADE	+	472)	//�� �ŷ� Cash ���� ǥ��
#define WIID_PC_TRADE_CASHIMG			(WIID_PC_TRADE	+	473)	//�� �ŷ� Cash�̹���
#define WIID_PC_TRADE_CASHDIS			(WIID_PC_TRADE	+	474)	//�� �ŷ� Cash��Ȱ��

#define WIID_PC_TRADE_POINT_BACK		(WIID_PC_TRADE	+	480)	//�� �ŷ� Point �Է� ����
#define WIID_PC_TRADE_POINT				(WIID_PC_TRADE	+	481)	//�� �ŷ� Point
#define WIID_PC_TRADE_POINT_UNIT		(WIID_PC_TRADE	+	482)	//�� �ŷ� Point ���� ǥ��
#define WIID_PC_TRADE_POINTIMG			(WIID_PC_TRADE	+	483)	//�� �ŷ� Point�̹���
#define WIID_PC_TRADE_POINTDIS			(WIID_PC_TRADE	+	484)	//�� �ŷ� Point��Ȱ��

#define WIID_PC_TRADE_FEE_TEXT			(WIID_PC_TRADE	+	490)	//�� �ŷ� ������ ���� �̹���
#define WIID_PC_TRADE_FEE_BACK			(WIID_PC_TRADE	+	491)	//�� �ŷ� Fee ����
#define WIID_PC_TRADE_FEE				(WIID_PC_TRADE	+	492)	//�� �ŷ� Fee
#define WIID_PC_TRADE_FEEIMG			(WIID_PC_TRADE	+	493)	//�� �ŷ� Fee�̹���


/*
#define WIID_PC_TRADE_ITEM_ICON			(WIID_PC_TRADE	+	40)		//�� �������� ICON
#define WIID_PC_TRADE_ITEM_TEXT			(WIID_PC_TRADE	+	50)		//�� �������� Text
#define WIID_PC_TRADE_ITEM_BTN			(WIID_PC_TRADE	+	60)		//�� �������� ��ư

#define WIID_PC_TRADE_PC_NAME			(WIID_PC_TRADE	+	65)		//��� �̸�
#define WIID_PC_TRADE_PC_ITEM_ICON		(WIID_PC_TRADE	+	70)		//��� �������� ICON
#define WIID_PC_TRADE_PC_ITEM_TEXT		(WIID_PC_TRADE	+	80)		//��� �������� Text
#define WIID_PC_TRADE_PC_ITEM_BTN		(WIID_PC_TRADE	+	90)		//��� �������� ��ư

#define WIID_PC_TRADE_HIDE				(WIID_PC_TRADE	+	100)	//����
#define WIID_PC_TRADE_ACCEPT			(WIID_PC_TRADE	+	110)	//Local User ����
#define WIID_PC_TRADE_PC_ACCEPT			(WIID_PC_TRADE	+	120)	//��� ����

#define WIID_PC_TRADE_ELY				(WIID_PC_TRADE	+	130)	//�� �ŷ� Ely	//Edit Control
#define WIID_PC_TRADE_PC_ELY			(WIID_PC_TRADE	+	140)	//��� �ŷ� Ely	//Static Control
*/

const int MAX_PC_TRADE_COUNT = 4;	// �ִ� Ʈ���̵� ������ ��
//const float ENABLE_X = 400.0f;
//const float ENABLE_Y = 300.0f;

//
//enum PC_TRADE_ACCEPT {
//	PC_TRADE_ACCEPT_DISABLE = 0,
//	PC_TRADE_ACCEPT_ENABLE = 1,
//	PC_TRADE_ACCEPT_ACCEPT = 2,
//};

enum ICON_MARK;
class SPItem;
class SPWindow;
class SPWindowButton;
class SPWindowEdit;


enum TRADE_MODE {
	TRADE_MODE_NULL = 0,
	TRADE_MODE_WAIT = 1,
};


enum TRADE_USER {
	TRADE_USER_LOCAL	= 0,
	TRADE_USER_PC		= 1,
};


/**
 * ĳ�� Ʈ���̵�� ����������
*/
enum TRADE_FEE {
	TRADE_FEE_NULL,
	TRADE_FEE_CASH,
	TRADE_FEE_POINT,
};

/**
* @class SPWindowPcTrade
* @brief ���� Ʈ���̵� ������
* @author Jinhee
* @version 00.00.01
* @date 2005.7.18
* @bug ����
* @warning 
*/
class SPWindowPcTrade : public SPWindow {

public:
	SPWindowPcTrade( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowPcTrade();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);

	void Refresh();

protected:
	/**
	 * �ŷ� ��� PC�� ������ ������ üũ�Ѵ� <br> 
	 @param NONE
	 @return bool
	*/
	//bool CheckInterval();

	/**
	* CashTrade ���� üũ�Ѵ� <br>
	@param 
	@return  
	*/
	bool CheckCashTrade();

	/**
	* �� ������� �ŷ� ����� ��� ����ִ��� Ȯ���Ѵ� <br>
	@param NONE
	@return bool
	*/
	bool IsEmptyItem();

	/**
	 * Ʈ���̵� ��庰�� ������ ����� �� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void SetWindowBase();

	/**
	 * ���� ������ ��Ʈ���� �����Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void CreateSubWindow();

	/**
	 * ĳ�� �ŷ� ������ ������ ������ �ŷ� ���� ��Ʈ���� ����� ���� <br>
	 @param 
	 @return  
	*/
	std::string GetUnitString(int iUnit = 0, TRADE_FEE iMode = TRADE_FEE_NULL);

	/**
	 * Ʈ���̵� ��庰�� ������ ���� ��Ʈ���� ��ġ�Ѵ� <br>
	 @param 
	 @return  
	*/
	void ArrangeControl();

	/**
	 * �ŷ� ���� â ���� �۵� <br> ������ �ʱ�ȭ <br>
	 @param NONE
	 @return NONE
	*/
	void CloseTrade();
	
	/**
	 * �ŷ� ����� �����۰���(�����ֱ� ����)�� ���� <br>
	 @param NONE
	 @return NONE
	*/
	void InitPcItem();
	
	/**
	 * �ŷ� ����� ������ ������ ��� ���� <br>
	 @param NONE
	 @return NONE
	*/
	void DeleteAllPcItem();
	
	/**
	 * �ŷ� ����� ������ �����͸� ��� �ʱ�ȭ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void ClearAllPcItem();

	/**
	 * �ش� �ε����� ���� �������� �ʱ�ȭ �Ѵ� <br> 
	 @param int iIndex
	 @return bool
	*/
	bool ClearPcItem(int iIndex);

	/**
	 * ������ �������� �����ϰ� �������̽��� �����Ѵ� <br>
	 @param int iIndex
	 @param ITEM* Item
	 @return bool
	*/
	bool SetPcItem(int iIndex, ITEM* Item);	
	
	/**
	 * �� Ʈ���̵� �������� ���� <br>
	 * ������, �ؽ�Ʈ ���� �����ֱ����� ���� <br> 
	 * ���ﶧ�� �޽���(SPIM_TRADE_ITEM_CLEAR) �� �Լ�(ItemClear)�� �̿��Ѵ� <br> 
	 @param int iIndex
	 @return NONE
	*/
	void SetItemIcon(int iIndex);

	/**
	 * �� Cash, Point�� ���� ��Ʈ�� Ȱ���� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void UpdateCashControl();

	/**
	 * �δ��� ���� ĳ�� �Է��� �����ϵ��� ���� <br> 
	 @param 
	 @return  
	*/
	void SetEnableIndun();

	/**
	 * ������ Cash, Point �� ���� �����Ḧ �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void UpdatePcFee();

	/**
	 * �� Cash, Point �� ���� �����Ḧ �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void UpdateLocalFee();

	/**
	 * �� Cash, Point �Է� ��Ʈ�� Ȱ���� ���� �Ѵ� <br> 
	 @param 
	 @return  
	*/
	void UpdateEditControl();
	
	/**
	 * ������ �������̽��� �������� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void SetFeeShow(TRADE_USER iUser, bool bShow);

public:
	/**
	* ���� ������ �ش� ���ؽ��� �������� �÷ȳ��ٰ� �˸��� <br>
	@param int iIndex
	@return bool
	*/
	bool SendPushItem(int iIndex);
	
	/**
	* ���� ������ �ش� ���ؽ��� �������� ���� �ߴٰ� �˸��� <br>
	@param int iIndex
	@return bool
	*/
	bool SendPopItem(int iIndex);

	/**
	* ���� ������ ���� �÷����ٰ� �˸���  <br>
	@param INT64 uiMoney
	@param int iCash = 0
	@param int iPoint = 0
	@return bool
	*/
	bool SendPushMoney(INT64 uiMoney, int iCash = 0, int iPoint = 0);

	/**
	 * <br>
	 @param
	 @return
	*/
	bool SendTradeWait();
	
	/**
	* ���� ������ �ŷ��� ����Ѵٰ� �˸���  <br>
	@param NONE
	@return bool
	*/
	bool SendTradeCancel();
	
	/**
	* ���� ������ �ŷ��� �¶��Ѵٰ� �˸���  <br>
	@param NONE
	@return bool
	*/
	bool SendTradeAccept();

	/**
	* �� ����ڰ� �ŷ��� ������ ���������� üũ�Ѵ� <br>
	@param NONE
	@return bool
	*/
	bool IsTradeEnable();

	/**
	* ��� ������ �ŷ� �������� Ȯ���Ѵ� <br>
	@param int iIndex 
	@return SPItem*
	*/
	SPItem* GetPcItem(int iIndex);

	/**
	 * ��� ������ ĳ������ �����´� <br>
	 @param
	 @return char*
	*/
	const char*	GetPcName();

	/**
	 * ��� ������ �ŷ� �ݾ��� �����´� <br>
	 @param
	 @return INT64
	*/
	INT64	GetPcEly();

	/**
	 * �� �ŷ� �ݾ��� �����´� <br>
	 @param
	 @return INT64
	*/
	INT64	GetEly();

	int		GetCash();
	int		GetPcCash();
	int		GetPoint();
	int		GetPcPoint();
	int		GetFee();
	int		GetPcFee();
    

protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()

	virtual int OnCursorEnter	( WPARAM, LPARAM );
	virtual int OnCursorOut		( WPARAM, LPARAM );
	virtual int OnCursorLDown	( WPARAM, LPARAM );
	virtual int OnCursorLUp		( WPARAM, LPARAM );	
	virtual int OnRefresh		( WPARAM, LPARAM );		

	int ItemClear				(WPARAM wParam, LPARAM lParam);			/**< ���� �÷��̾��� ������ ���� <br> */

	virtual int OnHide			(WPARAM wParam, LPARAM lParam);
	virtual int OnSetPlayerID	(WPARAM wParam, LPARAM lParam);			/**< �ŷ� ����� GUID ���� <br> */

	int OnAccept				(WPARAM wParam, LPARAM lParam);			/**< �ŷ� �¶� <br> */

	int OnUpdateEly				(WPARAM wParam, LPARAM lParam);			/**< Ely Update <br> */
	int OnUpdateCash			(WPARAM wParam, LPARAM lParam);			/**< <br> */	
	int OnUpdatePoint			(WPARAM wParam, LPARAM lParam);			/**< <br> */
	int OnClickCash				(WPARAM wParam, LPARAM lParam);			/**< <br> */
	int OnClickPoint			(WPARAM wParam, LPARAM lParam);			/**< <br> */

	int OnToolTipMove			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipEnter			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipOut			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);

	int OnItemClickUp			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnItemClickDown			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);

	int OnPCToolTipMove			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnPCToolTipEnter		(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnPCToolTipOut			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);

	int OnPCItemClickUp			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	
	int OnPushItem				(WPARAM wParam, LPARAM lParam);			/**< ������ �ø��� ���� <br> */
	int OnPopItem				(WPARAM wParam, LPARAM lParam);			/**< ������ ������ ���� <br> */
	int OnPushMoney				(WPARAM wParam, LPARAM lParam);			/**< �� �ø��� ���� <br> */
	int OnTradeCancel			(WPARAM wParam, LPARAM lParam);			/**< �ŷ� ����� ���� <br> */
	int OnTradeWait				(WPARAM wParam, LPARAM lParam);			/**< �ŷ� ��� <br> */
	int OnTradeAccept			(WPARAM wParam, LPARAM lParam);			/**< �ŷ� �¶��� ���� <br> */

	int OnCloseTrade			(WPARAM wParam, LPARAM lParam);			/**< �ܺ�(��Ż)������ CloseTrade ȣ��� <br> */

	// }}

private:
	GU_ID m_uiPlayerGUID;							/**< �ŷ� ����� GUID <br> */
	char m_szBuf[128];
	SPPlayer* m_pTargetPlayer;						/**< �ŷ� ����� Player���� <br> */

	int	m_iSrcPcAcceptX[3];
	int m_iSrcPcAcceptY;

	SPTexture* m_pBaseSkin;
	RECT m_rtBaseSrc[WINDOW_BASE_MAX];
	RECT m_rtBaseDest[WINDOW_BASE_MAX];
	
	SPWindowStatic* m_pHelp;						/**< ���� <br> */
	SPWindowButton* m_pAccept;						/**< �� �ŷ� �¶� ��ư <br> */
	//SPWindowStatic* m_pPcStatus_Wait;				// ��� ��������(�����)
	SPWindowStatic* m_pPcStatus_Accept;				// ��� ��������(����)
	//SPWindowStatic* m_pStatus_Wait;					// �� ��������(�����)
	SPWindowStatic* m_pStatus_Accept;				// �� ��������(����)

	float m_fStartPosX;								/**< �ŷ��� �����Ҷ� �� ��ġ X <br> */
	float m_fStartPosY;								/**< �ŷ��� �����Ҷ� �� ��ġ Y <br> */	
	bool m_bSendCancel;								/**< ���� ĵ����Ŷ�� �ѹ� ���´���? <br> */

	SPWindow* m_pItemIcon[MAX_PC_TRADE_COUNT];		/**< �� �ŷ� ������ ������ <br> */
	SPWindow* m_pItemText[MAX_PC_TRADE_COUNT];		/**< �� �ŷ� ������ �̸� <br> */
	SPWindow* m_pPCItemIcon[MAX_PC_TRADE_COUNT];	/**< ��� �ŷ� ������ ������ <br> */
	SPWindow* m_pPCItemText[MAX_PC_TRADE_COUNT];	/**< ��� �ŷ� ������ �̸� <br> */

	SPWindowEdit*	m_pEditEly;						/**< �� �ŷ� Ely <br> */
	SPWindowEdit*	m_pEditCash;					/**< �� �ŷ� Cash <br> */
	SPWindowEdit*	m_pEditPoint;					/**< �� �ŷ� Point <br> */	
	SPWindowStatic* m_pEditCashDis;					/**< �� �ŷ� Cash Disable <br> */
	SPWindowStatic* m_pEditPointDis;				/**< �� �ŷ� Point Disable <br> */
	SPWindowStatic* m_pFeeText;						/**< �� �ŷ� ������ ���ڿ� �̹��� <br> */
	SPWindowStatic* m_pFeeBack;						/**< �� �ŷ� Fee ���� <br> */
	SPWindowStatic* m_pFee;							/**< �� �ŷ� Fee <br> */
	SPWindowStatic* m_pFeeImg;						/**< �� �ŷ� Fee Img <br> */
	
	SPWindowStatic* m_pPcEly;						/**< ��� �ŷ� Ely <br> */
	SPWindowStatic* m_pPcCash;						/**< ��� �ŷ� Cash <br> */
	SPWindowStatic* m_pPcCashDis;					/**< ��� �ŷ� Cash Disable <br> */
	SPWindowStatic* m_pPcPoint;						/**< ��� �ŷ� Point <br> */
	SPWindowStatic* m_pPcPointDis;					/**< ��� �ŷ� Point Disable <br> */
	SPWindowStatic* m_pPcFeeText;					/**< ��� �ŷ� ������ ���ڿ� �̹��� <br> */
	SPWindowStatic* m_pPcFeeBack;					/**< ��� �ŷ� Fee ���� <br> */
	SPWindowStatic* m_pPcFee;						/**< ��� �ŷ� Fee <br> */
	SPWindowStatic* m_pPcFeeImg;					/**< ��� �ŷ� Fee Img <br> */

	UINT64	m_iTradeEly;							/**< �� �ŷ� Ely <br> */
	int		m_iTradeCash;							/**< �� �ŷ� Cash <br> */	
	int 	m_iTradePoint;							/**< �� �ŷ� Point <br> */
	int 	m_iTradeFee;							/**< �� �ŷ� Fee <br> */

	int			m_iCashUnitCount;					/**< ĳ�� �ŷ� ���� �ڸ��� ǥ�� ���� <br> */
	std::string m_strCashUnit;						/**< ĳ�� �ŷ� ���� ��� ��Ʈ�� <br> */
	int			m_iPointUnitCount;					/**< ����Ʈ �ŷ� ���� �ڸ��� ǥ�� ���� <br> */
	std::string m_strPointUnit;						/**< ����Ʈ �ŷ� ���� ��� ��Ʈ�� <br> */

	SPWindowStatic* m_pNameWait;					/**< �� �̸� ��� <br> */
	SPWindowStatic* m_pNameAccept;					/**< �� �̸� ���� <br> */
	SPWindowStatic* m_pPcNameWait;					/**< ��� �̸� ��� <br> */
	SPWindowStatic* m_pPcNameAccept;				/**< ��� �̸� ���� <br> */

	std::vector<SPItem*> m_vpPCItem;				/**< ��� �ŷ� ������ ����Ʈ <br> */
	
	INT64	m_iPcEly;								/**< ������ �� <br> */
	int 	m_iPcCash;								/**< ���� Cash <br> */
	int 	m_iPcPoint;								/**< ���� Point <br> */
	int 	m_iPcFee;								/**< ���� Fee <br> */
	
	bool m_bItemAble[MAX_PC_TRADE_COUNT];			/**< ���� �÷��� �������� ���� ���밡���� ���������� <br> */
	bool m_bPcItemAble[MAX_PC_TRADE_COUNT];			/**< ������ �÷��� �������� ���� ���밡���� ���������� <br> */	

	SPTexture* m_pDisable;							/**< ��Ȱ�� ǥ���� <br> */
	RECT m_rtSrcDisable;							/**< ��Ȱ�� ǥ���� �ҽ� <br> */

	ICON_MARK m_iItemMark[MAX_PC_TRADE_COUNT];		/**< ICON MARK <br> */
	ICON_MARK m_iPcItemMark[MAX_PC_TRADE_COUNT];	/**< ���� ICON MARK <br> */

	RECT m_rtMarkSrc[4];							/**< ICON MARK Src <br> */
	
	int m_iStack[MAX_PC_TRADE_COUNT];				/**< ���� �÷��̾�� ���� <br> */
	RECT m_rtStack[MAX_PC_TRADE_COUNT];				/**< ����ǥ���� ���� ���� Icon ������ ���� <br> */
	
	int m_iPcStack[MAX_PC_TRADE_COUNT];				/**< ���� �÷��̾�� ���� <br> */
	RECT m_rtPcStack[MAX_PC_TRADE_COUNT];			/**< ����ǥ���� ���� ���� Icon ������ ���� <br> */	

	bool	m_bChanged;								/**< ���� �� Ʈ���̵� ���¿� ��ȭ�� ������� <br> */
	float	m_fChangedDeley;						/**< Ʈ���̵� ���� ����� �����ð� ���� ��ư�� ��Ȱ�� <br> */
	float	m_fChangedAccumulate;					/**< ������ư ��Ȱ���� Ȱ������ Ǯ���ִ� Ÿ�̸� ��� <br> */	

	TRADE_MODE m_iTradeMode;						/**< Ʈ���̵� ��� <br> */
};


