#pragma once

class SPWindow;
class SPWindowStatic;
class SPWindowEdit;
//class SPWindowEditMultiLine;
class SPWindowButton;

#define WIID_PETSHOP_SELL_TOP			(WIID_PETSHOP_SELL	+	10)
#define WIID_PETSHOP_SELL_CENTER		(WIID_PETSHOP_SELL	+	20)

#define WIID_PETSHOP_SELL_TITLE		(WIID_PETSHOP_SELL	+	22)
#define WIID_PETSHOP_SELL_CLOSE		(WIID_PETSHOP_SELL	+	25)

#define WIID_PETSHOP_SELL_MIDDLE		(WIID_PETSHOP_SELL	+	30)
#define WIID_PETSHOP_SELL_NAME			(WIID_PETSHOP_SELL	+	33)
#define WIID_PETSHOP_SELL_NAME_EDIT	(WIID_PETSHOP_SELL	+	35)

#define WIID_PETSHOP_SELL_ITEM_SKIN	(WIID_PETSHOP_SELL	+	40)		//4���� ���� ������ ����Ʈ ����Ʈ ��Ų
#define WIID_PETSHOP_SELL_ITEM_ENABLE	(WIID_PETSHOP_SELL +	40)		//4���� �������� �ִ� ��� �߰� ��Ų
#define WIID_PETSHOP_SELL_ITEM_LINE	(WIID_PETSHOP_SELL	+	50)		//4���� ���� ������ ���
#define WIID_PETSHOP_SELL_ITEM_ICONLINE (WIID_PETSHOP_SELL	+	55) //4���� ������ ������ ���� �ܰ� ����
#define WIID_PETSHOP_SELL_ITEM_ICON	(WIID_PETSHOP_SELL	+	60)		//4���� ������ ������ 
#define WIID_PETSHOP_SELL_ITEM_NAME	(WIID_PETSHOP_SELL	+	70)		//4���� ������ ��
#define WIID_PETSHOP_SELL_ITEM_EMPTY	(WIID_PETSHOP_SELL	+	80)		//4���� ������ ���� ���� ���
#define	WIID_PETSHOP_SELL_ITEM_ELY		(WIID_PETSHOP_SELL	+	90)		//4���� ������ ����
#define	WIID_PETSHOP_SELL_ITEM_ELY_ICON	(WIID_PETSHOP_SELL	+	100)
#define WIID_PETSHOP_SELL_ITEM_BUTTON	(WIID_PETSHOP_SELL	+	110)	//4���� ������ ���� ��ư

#define WIID_PETSHOP_SELL_PREV			(WIID_PETSHOP_SELL	+	140)	//
#define WIID_PETSHOP_SELL_PAGE			(WIID_PETSHOP_SELL	+	145)	//
#define WIID_PETSHOP_SELL_NEXT			(WIID_PETSHOP_SELL	+	150)	//

#define WIID_PETSHOP_SELL_OK			(WIID_PETSHOP_SELL	+	160)	//
#define WIID_PETSHOP_SELL_CANCEL		(WIID_PETSHOP_SELL	+	165)	//

#define WIID_PETSHOP_SELL_BOTTOM		(WIID_PETSHOP_SELL	+	170)


/**
 * <br>
*/
enum PETSHOP_STATE {
	PETSHOP_STATE_NULL = 0,				/**< �ƹ��� ���µ� �ƴ� <br> */
	PETSHOP_STATE_CREATE = 1,				/**< ���� ���� �غ� ���� <br> */
	PETSHOP_STATE_CREATE_REQUEST = 2,		/**< ���� ���� ��û <br> */
	PETSHOP_STATE_SELL = 3,				/**< ���� ���� ��û�� �������� ���� ���� ��� <br> */
};

class SPWindowPetShopSeller : public SPWindow 
{
public:
	SPWindowPetShopSeller( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);
	virtual ~SPWindowPetShopSeller();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	void SetPet( SPPet	*pet, PET_PLACE iPlace )
	{
		m_pPet = pet;
		m_iCurPetPlace = iPlace;
	}

public:
	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);	

	/**
	 * ���� ��Ʈ�� ���� <br>
	 @param 
	 @return
	*/
	void InitSubControl();
	
	/**
	 * 4���� ����Ʈ ������ ������Ʈ <br>
	 @param 
	 @return
	*/
	void UpdateList();

	/**
	 * ������ �ݰų� ����ϴ� ��� ó�� <br> 
	 @param 
	 @return
	*/
	void CloseShop(bool bAutoClose = false);

	/**
	 * 16���� Ely���� 0���� �ʱ�ȭ <br>
	 @param 
	 @return
	*/
	void ClearEly();
	
	/**
	 * 16���� �Ǹ� �����۶��� �ʱ�ȭ <br>
	 @param 
	 @return
	*/
	void ClearSellItem();

	/**
	 * 
	 @param 
	 @return
	*/
	void SetSellCount(int iPage);
	
	/**
	 * �Ǹ� ������ ����Ʈ�� ���� <br>
	 @param 
	 @return
	*/
	bool CreateSellItemList();

	/**
	 * �Ǹ� ������ ����(������ ������)�� �ʱ�ȭ <br>
	 @param 
	 @return
	*/
	bool InitFMSELLITEM(int iSlotIndex, FM_SELLITEM* pSellItem);

	/**
	 * �Ǹ� ������ ����(������ ������)��  ���� <br>
	 @param 
	 @return
	*/
	bool SetFMSLEEITEM(FM_SELLITEM* pSellItem, SPSelectItem* pSelectItem, INT64 iSellPrice);

	/**
	 * �ش� �ǸŸ���Ʈ���� �ε����� ���ϴ� �Ǹ� ������ ������ Ȯ�� <br>
	 @param  int iSlotIndex �ǸŸ���Ʈ���� �ε���
	 @return
	*/
	FM_SELLITEM* GetFMSELLITEM(int iSlotIndex);
	
	/**
	 * ���� ������ ������ ��û <br>
	 @param 
	 @return
	*/
	bool SendPetShopOpen();

	/**
	 * ���� ������ ������ ��û <br>
	 @param 
	 @return
	*/
	bool SendPetShopClose();

	/**
	 * ���μ������� ���� �ŷ��Ҽ� �ִ� ��Ȳ���� üũ <br> 
	 @param 
	 @return
	*/
	bool IsTradeEnable();

	/**
	 * ���� ������ �ȸ��� ��Ŷ�̿ö����� �Ǹ� ǰ���� �����ִ��� Ȯ�� <br>
	 * true�� ��� ������ ������ ���� <br>
	 @param 
	 @return
	*/
	bool IsEmptyShop();

	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnShopOpen				(WPARAM wParam, LPARAM lParam);
	int OnShopClose				(WPARAM wParam, LPARAM lParam);
	int OnShopBuy				(WPARAM wParam, LPARAM lParam);
	int OnShopSetClose			(WPARAM wParam, LPARAM lParam);			/**< Esc�� �������̽��� ���� ���� ���� ��û <br> */
	int	OnEditSetFocus			(WPARAM wParam, LPARAM lParam);
	int	OnEditKillFocus			(WPARAM wParam, LPARAM lParam);
	int OnClose					(WPARAM wParam, LPARAM lParam);
	int OnPrev					(WPARAM wParam, LPARAM lParam);
	int OnNext					(WPARAM wParam, LPARAM lParam);
	int OnOk					(WPARAM wParam, LPARAM lParam);
	int OnCancel				(WPARAM wParam, LPARAM lParam);	
	int ItemClear				(WPARAM wParam, LPARAM lParam);			/**< ���� �÷��̾��� ������ ���� <br> */
	int	OnEditSetFocusRange		(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int	OnEditKillFocusRange	(unsigned int iUiID, WPARAM wParam, LPARAM lParam);	
	int OnItemClickUp			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnItemClickDown			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnUpdateEly				(unsigned int iUiID, WPARAM wParam, LPARAM lParam); //Ely Update
	int OnToolTipMove			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipEnter			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipOut			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);	

private:
	SPTexture*		m_pTexture;
	SPWindowEdit*	m_pName;
	
	SPWindowButton* m_pClose;

	SPWindow*		m_pItemSkin[MAX_USER_SHOP_LIST];			/**< ����Ʈ ��Ų <br> */
	SPWindowButton* m_pItem[MAX_USER_SHOP_LIST];				/**< ����Ʈ ��ư <br> */
	SPWindow*		m_pItemIconLine[MAX_USER_SHOP_LIST];		/**< ����Ʈ ������ ������ �׵θ� <br> */
	SPWindow*		m_pItemIcon[MAX_USER_SHOP_LIST];			/**< ����Ʈ ������ ������ <br> */
	SPWindow*		m_pItemName[MAX_USER_SHOP_LIST];			/**< ����Ʈ ������ �� <br> */
	SPWindow*		m_pItemEmpty[MAX_USER_SHOP_LIST];			/**< ����Ʈ ������ ���� ǥ�� <br> */
	SPWindowEdit*	m_pItemEly[MAX_USER_SHOP_LIST];				/**< ����Ʈ �� �Է� <br> */
	SPWindow*		m_pItemElyIcon[MAX_USER_SHOP_LIST];			/**< ����Ʈ �� ������ <br> */

	SPWindowButton* m_pPrev;
	SPWindowButton* m_pNext;
	SPWindow*		m_pPage;									/**< Page <br> */

	SPWindowButton* m_pOK;										/**< ���� <br> */
	SPWindowButton* m_pCancel;									/**< ��� <br> */

	SPTexture*		m_pDisable;									/**< ��Ȱ�� ǥ���� <br> */
	RECT			m_rtSrcDisable;								/**< ��Ȱ�� ǥ���� �ҽ� <br> */
	
	//bool			m_bItemEnable[MAX_USER_SHOP_LIST];			/**< �������� �ִ��� <br> */
	bool			m_bItemAble[MAX_USER_SHOP_LIST];			/**< ���� �÷��� �������� ���� ���밡���� ���������� <br> */
	int				m_iStack[MAX_USER_SHOP_LIST];				/**< ���� �÷��̾�� ���� <br> */
	RECT			m_rtStack[MAX_USER_SHOP_LIST];				/**< ����ǥ���� ���� ���� Icon ������ ���� <br> */
	ICON_MARK		m_iItemMark[MAX_USER_SHOP_LIST];			/**< ICON MARK <br> */

	RECT			m_rtMarkSrc[4];								/**< ICON MARK Src <br> */

	int				m_iSellCount;								/**< ���� �Ǹ��Ҽ� �ִ� �ִ� ������ <br> */
	int				m_iMaxPage;									/**< �ִ� ������ <br> */
	int				m_iCurPage;									/**< ���� ������ <br> */
	int				m_iSelectItem;								/**< �������̽��� ����Ʈ�� ������ �ε��� <br> */
	int				m_iSelectIndex;								/**< �����ͻ� ����Ʈ�� ���õ� �ε��� <br> */	

	PETSHOP_STATE	m_iPetShopState;							/**< ���� ���� ���� ��Ȳ <br> */
	INT64			m_iEly[FM_MAX_SELLITEM];					/**< �������� <br> */
	std::string		m_strBuyer[FM_MAX_SELLITEM];				/**< ������ ���� <br> */

	float			m_fStartPosX;								/**< �ŷ��� �����Ҷ� �� ��ġ X <br> */
	float			m_fStartPosY;								/**< �ŷ��� �����Ҷ� �� ��ġ Y <br> */
	bool			m_bAutoClose;								/**< ���� ������ �ڵ����� ������� <br> ����� ������ ������� ���� ���� */	

	int				m_iPetShopType;							/**< �� ���� Ÿ�� <br> */
	
	bool			m_bSendClose;								/**< ���� ��Ŷ�� ������� true <br> */

	std::vector<FM_SELLITEM*> m_vpSellItem;						/**< �Ǹ��� ������ ����Ʈ <br> */
	SPPet			*m_pPet;
	PET_PLACE		m_iCurPetPlace;
};