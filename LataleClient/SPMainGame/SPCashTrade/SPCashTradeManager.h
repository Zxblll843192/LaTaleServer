#pragma once


#define		__FIELD_CASH_TRADE__		279


/**
 * ĳ�� ���� ��� <br> 
*/
enum CASH_TRADE_PLACE {
	CASH_TRADE_PLACE_NULL,				/**< <br> */
	CASH_TRADE_PLACE_SHOP,				/**< ĳ�ü� <br> */
	CASH_TRADE_PLACE_FIELD,				/**< �ʵ� <br> */
};


/**
 * ĳ�� ���� ��û ���� ��� <br> 
*/
enum CASH_TRADE_STATE {
	CASH_TRADE_STATE_NULL,				/**< ĳ�� ������ �ƴ� <br> */
	CASH_TRADE_STATE_WAIT,				/**< ĳ�� ���� ���� ����� <br> */
};


/**
 * ĳ�� ���� Ÿ�� <br> 
*/
enum CASH_TRADE_TYPE {
	CASH_TRADE_TYPE_NULL,				/**< <br> */
	CASH_TRADE_TYPE_BUY,				/**< �ܼ� ���� <br> */
	CASH_TRADE_TYPE_GIFT,				/**< ���� ���� <br> */
};


class SPHotItemInfo;
class SPHotItemManager;
struct SPCashItemAttr;


/**
 * Ŭ���̾�Ʈ�� ĳ�ü� ���� ���� <br> 
*/
struct SPCashShopVerInfo {
	int		m_iShopMajor;			/**< ������ ���� <br> */
	int		m_iShopMinor;			/**< ���̳� ���� <br> */
	int		m_iHotListVer;			/**< ��õ��ǰ ���� <br> */

	SPCashShopVerInfo() {
		Clear();
	}

	~SPCashShopVerInfo() {
		Clear();
	}

	void Clear() {
		m_iShopMajor		= -1;
		m_iShopMinor		= -1;
		m_iHotListVer		= -1;
	}

	void SetVerInfo(int iMajor, int iMinor, int iHotVer) {
		m_iShopMajor		= iMajor;
		m_iShopMinor		= iMinor;
		m_iHotListVer		= iHotVer;
	}

	void SetMajorVer(int iMajor) {
		m_iShopMajor		= iMajor;
	}

	void SetMinorVer(int iMinor) {
		m_iShopMinor		= iMinor;
	}

	void SetHotVer(int iHotVer) {
		m_iHotListVer		= iHotVer;
	}
};


/**
 * ĳ�� �ŷ� ����� ������ ��� <br> 
*/
struct SPCashTradeResultInfo {
	int				m_iCashShopID;				/**< �ŷ� ǰ�� <br> */
	std::string		m_strReceiver;				/**< ������ ��� ���� �� <br> ������ �ڱ��ڽ� ���� <br> */

	SPCashTradeResultInfo() {
		Clear();
	}

	~SPCashTradeResultInfo() {
		Clear();
	}

	void Clear() {
		m_iCashShopID	= 0;
		m_strReceiver.clear();
	}
};


class SPCashTradeManager{
public:
	static SPCashTradeManager* GetInstance();
	static void Release();

	void Init();

	void Reset();

	bool LoadCashShopVersionLDT();
	
	CASH_TRADE_PLACE GetCashTradePlace();
	CASH_TRADE_STATE GetCashTradeState();
	CASH_TRADE_TYPE	 GetCashTradeType();

	void SetVerInfo(int iMajor, int iMinor, int iHotVer);
	void SetMajorVer(int iMajor);
	void SetMinorVer(int iMinor);
	void SetHotVer(int iHotVer);

	SPCashShopVerInfo GetCashVerInfo()			{	return m_CashShopVerInfo; 	}
	SPCashTradeResultInfo* GetCashTradeResult()	{	return &m_CashTradeResult;	}

	/**
	 * �ε��� ���� ���¸� Ȯ���ϱ� ���� �뵵 <br> 
	 @param 
	 @return  
	*/
	void ResetSocket()							{	m_bSocketFail = false;	}
	
	/**
	 * �ε��� ���� �������� Ȯ���Ѵ� <br> 
	 @param 
	 @return  
	*/
	bool IsSocketFail()							{	return m_bSocketFail;	}
	
	bool IsMinorLoad()							{	return m_bMinorLoad;	}
	bool IsHotListLoad()						{	return m_bHotListLoad;	}

	/**
	 * �ε��� ��Ʈ��ũ �̻�� ����� �ʱ�ȭ �Ѵ� <br>
	 * ��� ���¸� Ǯ���� �Ѵ� <br>
	 @param 
	 @return  
	*/
	void SetSocketFail();
	
	/**
	 * ��õ��ǰ �Ŵ����� Ȯ���Ѵ� <br>
	 @param 
	 @return  
	*/
	SPHotItemManager* GetHotItemManager()		{	return m_pHotItemManager;}

	/**
	 * �ش� ID �� ĳ�ü� ������ ���� �ǻ縦 ���´� <br>
	 * ������ ����� �������̽� ���� <br>
	 @param int iShopID
	 @return  
	*/
	bool SetSelectCashItem(int iShopID, bool bShowSelectWnd = true);
	
	/**
	 * ���� ���Ÿ� ���� ������ ĳ�þ����� ������ Ȯ���Ѵ� <br>
	 @param 
	 @return  
	*/
	SPCashItemAttr* GetSelectCashItem();
	
	/**
	 * ���� ���Ÿ� ���� ������ ĳ�þ����� ������ �ʱ�ȭ�Ѵ� <br>
	 @param 
	 @return  
	*/
	bool ClearSelectCashItem();	

	/**
	 * ����, ���� �� ���� ��Ŷ�� ���� <br> 
	 @param 
	 @return  
	*/
	void SetBuyPacketReceive();
	
	/**
	 * ��� ���ϸ��̼��� �Ϸ���� ���� <br>
	 @param 
	 @return  
	*/
	void SetWaitAniComplete();
	

	/**
	 * ĳ�� ���� �������� �̵� <br> 
	 @param 
	 @return  
	*/
	bool PleaseBuyMoney();

	/**
	 * �� Ŭ���̾�Ʈ�� ĳ�ü� ������ �˸� <br> 
	 @param 
	 @return  
	*/
	bool SendCashShopVersion();
	
	/**
	 * ĳ�ü� Ŭ���̾�Ʈ ���� Ȯ�� ���� <br> 
	 @param 
	 @return  
	*/
	bool OnCashShopVersion(CPacket* pPacket);
	
	/**
	 * �ʵ� ���Ž� �ش� ĳ�� �������� ���� ������ ��û�Ѵ� <br> 
	 @param CASH_TRADE_TYPE iTradeType
	 @return  bool
	*/
	bool SendCashShopPrice(CASH_TRADE_TYPE iTradeType);
	
	/**
	 * �ʵ� ���Ž� ĳ�� ������ ���� ���� ���� <br> 
	 @param 
	 @return  
	*/
	bool OnCashShopPrice(CPacket* pPacket);
	
	/**
	 * ��õ ��ǰ ����Ʈ�� ������Ʈ �Ѵ� <br>
	 @param 
	 @return  
	*/
	bool OnCashShopHotItemUpdate(CPacket* pPacket);

	/**
	* ��õ ��ǰ ����Ʈ Show ���¸� On/Off �Ѵ� <br> 
	@param 
	@return  
	*/
	bool OnSetHotItemStatus(CPacket* pPacket);
	
	/**
	 * ĳ�ü� ������ ������Ʈ <br> 
	 @param 
	 @return  
	*/
	bool OnCashShopItemUpdate(CPacket* pPacket);
	

	/**
	 * ���� ��û <br>
	 @param CASH_TRADE_PLACE iPlace
	 @param int iPackageID
	 @param int iShopPrice
	 @param int iSalePrice
	 @param int iMaxOz
	 @param int iMaxMileage
	 @param int iBuyOz = 0
	 @param int iBuyMileage = 0
	 @return  
	*/
	bool SendCashShopBuy(CASH_TRADE_PLACE iPlace, int iPackageID, 
							int iShopPrice,	int iSalePrice, int iMaxOz, int iMaxMileage, 
							int iBuyOz = 0, int iBuyMileage = 0);
	
	/**
	 * ���� ��û ���� <br> 
	 @param 
	 @return  
	*/
	bool OnCashShopBuy(CPacket* pPacket);
	
	/**
	 * ���� ���� ��û <br> 
	 * ĳ�ü������� ��� <br> 
	 @param CASH_TRADE_PLACE iPlace
	 @param int iPackageID
	 @param int iShopPrice
	 @param int iSalePrice
	 @param int iMaxOz
	 @param	int iMaxMileage
	 @param int iBuyOz = 0
	 @param int iBuyMileage = 0
	 @return bool  
	*/
	bool SendCashShopPresent(CASH_TRADE_PLACE iPlace, int iPackageID,
								int iShopPrice,	int iSalePrice, int iMaxOz, int iMaxMileage,
								std::string strName, std::string strMsg,
								int iBuyOz = 0, int iBuyMileage = 0);
	
	/**
	 * ���� ���� ��û ���� <br> 
	 @param 
	 @return  
	*/
	bool OnCashShopGift(CPacket* pPacket);

	/**
	 * �� ��� �߰� ��û <br> 
	 * ĳ�ü������� ��� <br> 
	 @param CASH_TRADE_PLACE iPlace
	 @param int iPackageID
	 @return  bool
	*/
	bool SendWishAdd(CASH_TRADE_PLACE iPlace, int iPackageID);	
	
	/**
	 * �� ��� �߰� ��û ���� <br> 
	 @param 
	 @return  
	*/
	bool OnCashWishAdd(CPacket* pPacket);

private:
	SPCashTradeManager();
	~SPCashTradeManager();
	

protected:
	/**
	 * �κ��丮 ���� üũ <br> 
	 @param 
	 @return  
	*/
	bool IsEnableInventory();

	/**
	* �κ��丮 ������ ���ڸ� ��� ���� �޽��� <br> 
	@param 
	@return  
	*/
	void SetInvenFullMsg(int i);

	/**
	 *
	 @param 
	 @return  
	*/
	bool IsSendCheck();

	/**
	 * ����, ���� ��Ŷ�� ��� ���·� ó�� <br> 
	 @param 
	 @return  
	*/
	void ShowResultAction();

	/**
	 * ����, ���� ��Ŷ�� ������ ��� ó�� <br> 
	 @param 
	 @return  
	*/
	void ShowResultFail();

private:
	CASH_TRADE_PLACE		m_iCashTradePlace;
	CASH_TRADE_STATE		m_iCashTradeState;
	CASH_TRADE_TYPE			m_iCashTradeType;

	static SPCashTradeManager*	m_pInstance;

	SPCashShopVerInfo		m_CashShopVerInfo;

	bool					m_bSocketFail;				/**< �ε��� ���� ������ ��� true <br> */
	bool					m_bMinorLoad;
	bool					m_bHotListLoad;

	SPHotItemManager*		m_pHotItemManager;

	SPCashItemAttr*			m_pSelectCashItem;			/**< ���� �Ϸ��� ��ǰ�� ������ ��� <br> */	

	SPCashTradeResultInfo	m_CashTradeResult;			/**< ��� ������ ��� <br> */

	bool					m_bBuyPacketReceive;		/**< ���� ���� ��Ŷ�� ���� �� �޾Ҵ��� <br> */
	bool					m_bWaitAniComplete;			/**< ���� ��� ���ϸ��̼��� �Ϸ� �ߴ��� <br> */
};

extern SPCashTradeManager* g_pCashTradeManager;




