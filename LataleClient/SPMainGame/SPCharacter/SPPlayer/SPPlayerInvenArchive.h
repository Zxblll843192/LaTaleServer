

/**
* @class	SPPlayerInvenArchive
* @brief	Player Inventory Archive class
* @author	kkandori
* @date		Jan, 20, 2005
*/

#pragma once

#define MAX_INVENTORY_NUM		16

struct SPItemSet;
class SPItemCluster;

//#include "SPDebug.h"

const int MAX_INVENTORY_SLOT		= 80;		/**< �ִ� �κ��丮 ���� <br> ����ɼ� �ֽ� <br> */
const int MAX_INVENWEAR_SLOT		= 40;
const int VIEW_SLOT					= 16;
const int DEFAULT_INVENTORY_SLOT	= 28;		/**< �⺻ �κ��丮 ���� <br> ����ɼ� �ֽ� <br> */
const int DEFAULT_EQUIP_SLOT		= 16;		/**< �⺻ ��� ���� <br> */
const int INVENTORY_LINE			= 4;		/**< �κ��丮 �� ���κ� ���� �� <br> */
const int EQUIP_LINE				= 3;		/**< ��� �� ���κ� ���� �� <br> */

const int INVENTORY_TYPE			= 6;		/**< �κ��丮 ������ ���� (���, �Һ�, ��Ÿ , �̺�Ʈ, ��, �Ͽ�¡�� ��������)<br> */
const int EQUIP_TYPE				= 3;		/**< ��� ������ ���� (���, �ּ�, �� ��) <br> */
const int MAX_INVENTORY_TYPE		= 10;		/**< �κ��丮 ������ ���� (�κ��丮 ���� + ��� ����) <br> */

const int DEFAULT_INVENTORY_PET_SLOT	= 4;	/**< �κ��丮 ��� ������ <br> */

const int DEFAULT_STORAGE_SIZE		= 4;		/**< �⺻ â�� ������ <br> */
const int VIEW_STORAGE_SLOT			= 16;		/**< â�� �� ���� <br> */
const int STORAGE_LINE				= 4;		/**< â���� �� ���κ� ���� �� <br> */

const int MAX_PC_TRADE_SLOT			= 4;		/**< �ŷ� �ִ� ���� ������ <br> */

const int MAX_ITEM_BLOCK			= 8;		/**< ��þƮ, ��ȭ, �ð����� �� ������ ���� ��� <br> */

const int DEFAULT_PET_SLOT			= 1;		/**< �⺻ PET ��� ���� <br> */
const int MAX_PET_INVENTORY_SLOT	= 3;


/**
 * ���� �޽���â�� � ������ �����ִ����� �̿��Ѵ� <br>
 * ���� OnYes, OnNo �ڵ忡���� �� �÷��׸� ����ϵ��� �����Ұ� <br>
*/
enum NOTICE_USE {
    NOTICE_USE_NULL					,		/**< NULL <br> */
	NOTICE_USE_ITEM_TRASH			,		/**< Item Trash <br> */
	NOTICE_USE_ITEM_TRASH_FAIL		,		/**< ������ �ı� �ȵ� <br> */
	NOTICE_USE_ITEM_PARTITION		,		/**< Item Partition <br> */
	NOTICE_USE_TRADE_REQUEST		,		/**< Trade ��û <br> */
	NOTICE_USE_PARTY_INVITE			,		/**< ��Ƽ �ʴ� <br> */	
	NOTICE_USE_PLAYER_DEAD			,		/**< �÷��̾� ��� <br> */
	NOTICE_USE_PLAYER_DEAD_REDUCE	,		/**< ��Ż�� ��� �г�Ƽ ���Ҹ� �Ұ����� <br> */
	NOTICE_USE_PLAYER_DEAD_PVP		,		/**< PVP �� ����� <br> */
	NOTICE_USE_PLAYER_REVIVE		,		/**< �÷��̾� ��Ȱ <br> */  
	NOTICE_USE_GUILD_INVITE			,		/**< ��� �ʴ� <br>*/
	NOTICE_USE_GUILD_EXCEDE			,		/**< ��� Ż�� <br>*/
	NOTICE_USE_PVP_INVITE			,		/**< 1:1 PVP �ʴ�<br>*/
	NOTICE_USE_SUMMON_INVITE		,		/**< PC��ȯ �ʴ�<br>*/
	NOTICE_USE_LOVE_SUMMON			,		/**< ���� ��ȯ <br> */ 
	NOTICE_USE_LOVE_DIVORCE			,		/**< �̺� ��û <br> */  
	NOTICE_USE_MAX,							/**< Notice Max <br> */
};


enum WINDOW_STATE
{
	WINDOW_NULL		=	0,
	WINDOW_ONE			 ,
	WINDOW_TWO			 ,
	WINDOW_THREE		 ,
};

enum PET_PLACE;

/** 
 * ������ ������ �Ⱦ��� �������� ��ġ (�����̳� Ÿ�԰� �ش� ���� �ε����� ����ϴ� ����ü ) <br>
*/
typedef struct _SPSelectItem {
	CONTAINER_TYPE m_iContainer;				/**< �Ⱦ� �������� �����̳� ���� <br> */
	int m_iSlotIndex;							/**< �Ⱦ� �������� ���� �ε��� <br> */

	_SPSelectItem() {
		Clear();
	}

	~_SPSelectItem() {
		Clear();
	}

	void Clear() {
		m_iContainer = CONTAINER_TYPE_INVALID;
		m_iSlotIndex = -1;
		//
		//DXUTOutputDebugString("SelectItem Clear Container[%d], Index[%d]\n", m_iContainer, m_iSlotIndex);
	}

	void SetSelectItem(CONTAINER_TYPE iContainerType, int iSlotIndex) {
		Clear();
		
		m_iContainer = iContainerType;
		m_iSlotIndex = iSlotIndex;
	}

	CONTAINER_TYPE GetContainerType() {
		return m_iContainer;
	}

	int GetSlotIndex() {
		return m_iSlotIndex;
	}

	/**
	 *	SPSelectItem�� ���� �����Ǿ� �ִ��� 
	 @param NONE
	 @return bool true�̸� ��� �ִ� ������.
	*/
	bool IsNull() {
		if(m_iContainer == CONTAINER_TYPE_INVALID && m_iSlotIndex == -1)
			return true;

		return false;
	}
} SPSelectItem;


class SPItem;
class SPItemStatus;

class SPPlayerInvenArchive
{
public:
	SPPlayerInvenArchive(SPGameObject* pParent);
	virtual ~SPPlayerInvenArchive();

	virtual void	Init();
	void			Clear();	


	/**
	* �������� �����Ѵ�. <br>
	* �ش� �Լ��� ȣ�� ���ο��� �κ��丮 �������� �������ְ� <br>
	* ��� ������ �ƹ�Ÿ ���� �޽����� �߻���Ų�� <br>
	@param CONTAINER_ITEM item ������ �������� ���̽�
	@param bool bReloadEquipShow = false ���� ������� �ʴ� �Ķ������
	@return bool
	@warning ��� ���� �Ǵ� ��Ȳ�� ������ �����Ұ� ��.��
	*/
	bool ItemSetting( CONTAINER_ITEM item, bool bSetEquip = true);

	/**
	* �������� �����Ѵ� <br>
	* ���ذ��� �Ǵ� ���� ������ �̷������ <br>
	@param TRASH_ITEM item
	@return bool
	@warning �Լ��� ������ ���� �����ε��� ������ 0���̽��� ������ �����ȴ�
	*/
	bool TrashItem(TRASH_ITEM item);

	/**
	 * �־��� �����̳� Ÿ���� �κ� ���� ������ �ʱ�ȭ �Ѵ� <br> 
	 @param CONTAINER_TYPE eType
	 @return  NULL
	*/
	void ClearInventory(CONTAINER_TYPE eType);

	/**
	 * â�� �������̽� ���� <br>
	 @param NULL
	 @return  int 
	*/
	int ReflashStorage();

public:	
	int	OnSendMessage(SPGM msg, LPARAM lParam);
	
protected:
	/**
	 * �ش� �ε����� ���� ������ Ȱ��ȭ ��Ų�� <br>
	 @param int iCurSlot
	 @return NONE
	*/
	void SetActiveWeaponSlot(int iCurSlot);	
	
	/**
	 * ������ �б⿡ ���� ó�� �� ��Ŷ���� <br> 
	 @param NONE
	 @return int
	*/
	int	SetTrash();	

	/////// Inventory	
	/**
	 * �������κ��丮 â�� Ŭ�� �޼����� �޴´�. <br>
	 @param int iSlotIndex ���ø� ��ġ <br>
	 @return int
	 @warning �ش� �ε����� 0���̽��̴� 
	*/
	int	ItemGridClickDown(int iSlotIndex);	
	int	ItemGridClickUp(int iSlotIndex);
	int	ItemGridCursorMove(LPARAM lParam);	
	int	ItemPickUp(int iSlotIndex);	
	int ItemGridDBK(int iSlotIndex);				/**< ������ �׸��� ����Ŭ���� ��� �ڵ� ����<br> */

	int ItemPageUp();
	int ItemPageDown();
	int ItemSetPage(int iPage);
	
	/**
	 * ���� Ʈ���̵� ��Ȳ���� ������ �Ǹ�â�� �ٷ� ��� <br>
	 @param int iSlotIndex ����� �������� �ε��� 
	 @return int
	 @warning �ε����� 0���̽�
	*/
	int	ItemGridRClick(int iSlotIndex);
	
	/**
	 * ���� ������ �������� ���� ���� ���� <br>
	 @param CONTAINER_TYPE
	 @return NONE
	*/
	void SetCurrentItemPage(CONTAINER_TYPE);

	/**
	 * ���� ��� �������� ���� ���� ���� <br>
	 @param CONTAINER_TYPE
	 @return NONE
	*/
	void SetCurrentEquipPage(CONTAINER_TYPE);	
	

	/**
	 * ������ �κ��丮 ���� ��ȯ <br>
	 @param  LPARAM lParam
	 @return int
	*/
	int	OnChangeInventory( LPARAM lParam);
	
	/**
	* �κ��丮�� �ٽ� �׸����� �Ѵ� <br>
	@param  NONE
	@return int
	*/
	int ReflashInventory();
	
	/**
	 * �� �������� �ٲ۴�. <br>
	 @param CHANGE_SLOT item
	 @return NONE
	 @warning �Լ��� ������ ���� �����ε��� ������ 0���̽��� ������ �����ȴ�
	*/
	void SlotChange(CHANGE_SLOT item);

	/**
	 * �־��� ������ �� �������� ��ģ�� <br> 
	 @param CHANGE_SLOT item
	 @return NONE
	 @warning �Լ��� ������ ���� �����ε��� ������ 0���̽��� ������ �����ȴ�
	*/
	void SlotMerge(CHANGE_SLOT item);
	

	/**
	 * ���� �������κ��丮�� ������ �����Ѵ�. <br>
	 @param NONE
	 @return NONE
	*/
	void SettingCurrentInventory();
	
	/**
	 *  ���� ����κ��丮�� ������ �����Ѵ�. <br>
	 @param NONE
	 @return NONE
	*/
	void SettingCurrentEquip();		

	/////// Equip
	/**
	 * ��� �κ��丮 ���� ��ȯ <br>
	 @param LPARAM lParam
	 @return int
	*/
	int	OnChangeEquip( LPARAM lParam );

	/**
	 * ��� �κ��丮 â�� Ŭ�� �޼����� �޴´�. <br>
	 @param int iSlotIndex
	 @return int
	 @warning �ش� ���� �ε����� 0���̽��̴�
	*/
	int	EquipGridClickDown(int iSlotIndex);
	int	EquipGridClickUp(int iSlotIndex);
	int	EquipGridCursorMove(LPARAM lParam);
	int	EquipPickUp(int iSlotIndex);
	int EquipGridRClickUp(int iSlotIndex);

	/**
	 * ���� 1 �� ���� Ŭ�� �޼����� �޴´�. <br>
	 @param int iSlotIndex
	 @return int
	 @warning �ش� ���� �ε����� 0���̽��̸� �����Ϳ� ���߷��� �ణ�� ��ȯ�� �ʿ��ϴ� 
	*/
	int	Weapon1ClickDown(int iSlotIndex);
	int	Weapon1ClickUp(int iSlotIndex);
	int	Weapon1CursorMove(LPARAM lParam);
	int	Weapon1PickUp(int iSlotIndex);
	int	Weapon1RClickUp(int iSlotIndex);
	
	/**
	 * ���� 2 �� ���� Ŭ�� �޼����� �޴´�. <br>
	 @param int iSlotIndex
	 @return int
	 @warning �ش� ���� �ε����� 0���̽��̸� �����Ϳ� ���߷��� �ణ�� ��ȯ�� �ʿ��ϴ� 
	*/
	int	Weapon2ClickDown(int iSlotIndex);
	int	Weapon2ClickUp(int iSlotIndex);
	int	Weapon2CursorMove(LPARAM lParam);
	int	Weapon2PickUp(int iSlotIndex);
	int	Weapon2RClickUp(int iSlotIndex);
	
	/**
	 * â�� ���� ũ�� �޽����� �޴´� <br>
	 @param
	 @return
	*/
	int	StorageClickDown(int iSlotIndex);
	int	StorageClickUp(int iSlotIndex);
	int	StorageCursorMove(LPARAM lParam);
	int	StoragePickUp(int iSlotIndex);
	int StoragePageUp();
	int StoragePageDown();
	int StorageSetPage(int iPage);	

	/**
	* �꿡 ���� ũ�� �޽����� �޴´� <br>
	@param
	@return
	*/
	int PetClickDown(int iSlotIndex);
	int PetClickUp(int iSlotIndex);
	int PetCursorMove(LPARAM lParam);
	int	PetPickUp(int iSlotIndex);

	/**
	 * ���� ��ȯ <br>
	 @param NONE
	 @return NONE
	*/
	void WeaponToggle();
	
	/**
	 * ���� ��ȯ <br> 
	 @param NONE
	 @return NONE
	*/
	void WeaponChange();
	
	/**
	 * ���� ���� ���� ��ȯ �۾� <br> 
	 @param NONE
	 @return NONE
	*/
	void WeaponChangeInterface();	
	

//------ Receive
	// Inventory
	int	OnSetInventory		( LPARAM lParam );	/**< �κ��丮 ���� (1��) <br> */
	int	OnSetInventoryEx	( LPARAM lParam );	/**< �κ��丮 ���� (�ټ�) <br> */
	int	OnSetChangeSlot		( LPARAM lParam );	/**< ������ ���� ��ȯ <br> */
	int OnSetDivideSlot		( LPARAM lParam );	/**< ������ ���� <br> */
	int	OnSetTrash			( LPARAM lParam );	/**< ������ �ı� <br> */
	int OnSetTrashByTime	( LPARAM lParam );	/**< ������ ���ӽð��� ���� ���� <br> */
	int	OnSetExceptionMsg	( LPARAM lParam );	/**< ����.. <br> ������ ���� <br> */
	int OnSetUsing			( LPARAM lParam );	/**< ������ ��� <br> */
	int OnSetExpire			( LPARAM lParam );	/**< ������ ���ӽð��� ���� ���� <br> */
	int OnAddTime			( LPARAM lParam );	/**< ������ ���ӽð� ���� <br> */
	int OnSetExp			( LPARAM lParam );	/**< ������ ����ġ ���� <br> */
	int OnAddSp				( LPARAM lParam );	/**< ������ SP ���� <br> */
	int OnSetChatUsing		( LPARAM lParam );	/**< Mic ������ ��� ���� <br> */
	int	OnSetFindUsing		( LPARAM lParam );  //�����˵��ߵ���Ŀ
	// Equipment

//------ Send
	// Inventory
	int	SendReqLooting		(LOOTING_ITEM item);    /**< ������ ���� ��û <br> */
	int	SendReqChangeSlot	(CHANGE_SLOT   item);	/**< �������� ���� ��ȯ ��û <br> */
	int SendReqDivide		(CHANGE_SLOT item);		/**< ������ ������ ��� ��û <br> */
	int	SendReqTrash		(TRASH_ITEM item);		/**< �ı� ��û <br> */

	
	/**
	 * Notice �� Yes ���� ó���� <br>
	 @param
	 @return
	*/
	int OnYes			(LPARAM lParam);

	/**
	 * Notice �� No ���� ó���� <br>
	 @param
	 @return
	*/
	int OnNo			(LPARAM lParam);

//////////////////////////////////////////////////////////////////////////
private:
	//PC TRADE
	int	OnTradeRequest		(LPARAM lParam);		/**< ������ �ŷ� ��û <br> */
	int	OnTradeResponse		(LPARAM lParam);		/**< ������ �ŷ� ��û ���� <br> */
	int OnTradePushMoney	(LPARAM lParam);		/**< �ŷ��� Ely ���� <br> */
	int OnTradePushItem		(LPARAM lParam);		/**< �ŷ��� Item ���� <br> */
	int OnTradePopItem		(LPARAM lParam);		/**< �ŷ��� Item ���� <br> */
	int OnTradeAccept		(LPARAM lParam);		/**< �ŷ� �Ϸ� ��û <br> */
	int OnTradeCancel		(LPARAM lParam);		/**< �ŷ� ��� <br> */
	int OnTradeWait			(LPARAM lParam);		/**< �ŷ� ��� <br> */

	//NPC TRADE 
	int OnNpcTrade			(LPARAM lParam);		/**< NPC���� ������ �� ��� ���� <br> */

	//Another PC Item Info
	int OnPlayerInfoEquip	(LPARAM lParam);		/**< Another PC Item Info <br> */

public:
	bool SendTradeResponse	(bool bAccept = false);		
	
	bool IsSendTradeRequest();						/**< ���� �÷��̾ Ʈ���̵� ��û ��Ŷ�� ���´��� <br> */
	void SetSendTradeRequest(bool bSend);			/**< ���� �÷��̾��� Ʈ���̵� ��û ��Ŷ ó�� ��Ȳ�� ���� <br> */

	//[xialin 2008/07/21] add
	void ClearWearItem();
	void DeleteWearItem();

public:
	/**
	* ���� �÷��̾��� ��� ������ �κ��丮 ������ �����Ѵ� <br>
	* �����ϴ� ������ �κ��丮 ������ ���� �����̴� <br>
	@param CONTAINER_TYPE
	@return NONE
	@warning ����� ��� �÷��̾ �����ϸ鼭 ������ �����Ѵ� 
	*/
	bool CreateLocalInventory();
	
	/**
	* ���� ������ �������� ���� ���� ���� <br>
	@param CONTAINER_TYPE
	@return NONE
	*/
	CONTAINER_TYPE	GetCurrentItemPage()	{ return m_iCurrentInventoryType;};

	/**
	* ���� ��� �������� ���� ���� ���� <br>
	@param CONTAINER_TYPE
	@return NONE
	*/
	CONTAINER_TYPE	GetCurrentEquipPage()	{ return m_iCurrentFigureType;};		

	/**
	* Ȯ�彽���� �����Ѵ� <br> 
	* Ȯ�彽���� ĳ���� ���ý� ������ ���;� �Ѵ� <br> 
	* �� �� �־��� ������ ��ŭ �� �����Ѵ� <br> 
	@param CONTAINER_TYPE iType
	@param int iExtendSize = 0
	@return NONE
	*/
	void SetExtendSlot(CONTAINER_TYPE iType, int iTotalCount = 0, int iExtendSize = 0);

	/**
	 * ������ <br> 
	 @param
	 @return
	*/
	void PrintInventoryInfo();

	/**
	 * player �κ��丮 ������ ����� <br> 
	 @param CONTAINER_TYPE iType				�����̳� ����
	 @param std::vector<SPItem*>* vpInventory	�����͸���Ʈ�� ���� �κ��丮 ���� ������
	 @return
	*/
	bool CreateInventory(CONTAINER_TYPE iType, std::vector<SPItem*>* vpInventory, int iSize = DEFAULT_INVENTORY_SLOT);	

	/**
	* ��� �κ��丮�� ������ Ÿ���� �������� �ð��� ���ҽ�Ų�� <br> 
	@param int iTime = 60					//�̺�Ʈ ������ �ϰ������� 60�� ����
	@return
	*/
	void DecreaseLifeTime(int iTime = 60);

	/**
	*  �������� �����ϴ��� Ȯ���Ѵ� <br>
	@param int iIndex
	@param CONTAINER_TYPE iType
	@return bool ����� true
	*/
	bool IsItemExist(int iIndex, CONTAINER_TYPE iType);

	/**
	 * �κ��丮 �������� �������� ���´� <br>
	 @param CONTAINER_TYPE iType		�����̳� Ÿ��
	 @param int iSlotIndex				���� �ε���
	 @return SPItem*
	*/
	SPItem* GetInventoryItem(CONTAINER_TYPE iType, int iSlotIndex);

	/**
	* ���ø� �������� ���� ���������͸� �����´� <br>
	@param NONE
	@return SPSelectItem ���ø� �������� ��ġ ����
	*/
	SPSelectItem GetPickupItem();

	/**
	 * �ش� �����̳��� �κ��丮 ũ�⸦ ���´� <br>
	 @param CONTAINER_TYPE iType
	 @return int
	*/
	int	GetInventorySize(CONTAINER_TYPE iType);

	/**
	 * �ش� �������� ���� ������(��ũ�ѹ� ����)�� ���´� <br>
	 @param CONTAINER_TYPE iType
	 @return int
	*/
	int GetInventoryCurPage(CONTAINER_TYPE iType);

	/**
	* �ش� �����̳��� �κ��丮������ ��� ���������� �� �ִ��� Ȯ���Ѵ� <br> 
	@param CONTAINER_TYPE iContainerType
	@return bool ����� true
	*/
	bool IsFullInventory(CONTAINER_TYPE iContainerType);

	/**
	 * �ش� �����̳��� �κ��丮������ ������ ����ִ��� Ȯ���Ѵ� <br> 
	 @param CONTAINER_TYPE iContainerType
	 @return  ��� �˻��ؼ� �ƹ��͵� ����� true
	*/
	bool IsEmptyInventory(CONTAINER_TYPE iContainerType);

	/**
	* �ش� �����̳��� �κ��丮 ���Կ� �ش� �������� �����ϸ� <br>
	* �ش� �������� ���ؿ� ������ �ִ��� Ȯ���Ѵ� <br>
	@param CONTAINER_TYPE iContainerType �����̳� Ÿ��
	@param int iItemID Ȯ���� ������ ID
	@return true�� ��� ������ ������ ����
	*/
	bool IsEnableSpace(CONTAINER_TYPE iContainerType, int iItemID, int iStack = 1);

	/**
	 * �ش� �����̳��� �κ��丮�� ��� �ִ� ������ ����� Ȯ���Ѵ� <br>
	 @param CONTAINER_TYPE iContainerType
	 @return int
	*/
	int GetEmptySlotCount(CONTAINER_TYPE iContainerType);

	/**
	 * �־��� ItemID �� Stack������ ����(���ų� ū) ������ ��ȯ <br>
	 * Inventory�� Ȯ�� ������ Item�� ã�� ��� true���� pSelectItem�� ������ ����Ͽ� ��ȯ <br> 
	 * �տ��� ���� ã�� <br>
	 @param int iItemID
	 @param int iStack = 1
	 @param SPSelectItem* pSelectItem = NULL			true�� ���ο� ������ ���
	 @return  bool
	*/
	bool FindInvenItem(int iItemID, int iStack = 1, SPSelectItem* pSelectItem = NULL);


	/**  
	 * �־��� ItemID�� Stack������ �����ϴ� SPItem�� ��ȯ <br> 
	 * ������� �ʿ信 ���� �ش� ������ SPItem�� Block���� <br> 
	 @param int iItemID
	 @param int iStack = 1
	 @param UINT8 iRare = 1				(1���� ��� üũ ����)
	 @param int iBlockIndex = MAX_ITEM_BLOCK (0 ~ MAX_ITEM_BLOCK�� ���� �����ϸ� �������� ��)
	 @return 
	*/  
	SPItem* GetFindItem(int iItemID, int iStack = 1, int iRare = 0, int iBlockIndex = MAX_ITEM_BLOCK);

	//
	SPItem * GetInvenItem(int iItemID);   //[xialin 2008/07/25]add

	/**
	 * �־��� ItemID �� �ش��ϴ� SetItem�� � �����ϰ� �ִ��� Ȯ�� <br> 
	 @param int iItemID
	 @return  int
	*/
	int GetSetItemPieces(int iItemID);

	/**
	 * �־��� ItemID�� �ش��ϴ� �������� ��Ʈ �������� �ϳ����� Ȯ�� <br>
	 @param int iItemID
	 @return  bool
	*/
	bool IsSetItem(int iItemID);

	/**
	 * �־��� ItemID�� �ش��ϴ� Set�� ���� ���� ������ �������ش� <br>
	 * ���ŵ� ���밹���� ItemCluster�� SPItemSet->m_iCurrentPieces �� ����Ѵ� <br>
	 @param int iItemID
	 @return  
	*/
	void CheckSetItem(int iItemID);
	
	/**
	* Quick Slot���� ������ ����Ұ��... <br>
	@param int iItemID
	@param CONTAINER_TYPE iContainerType
	@return bool
	*/
	bool ItemQuickUse(CONTAINER_TYPE iContainerType, int iItemID);
	
	/**
	 * ������ ��� <br> 
	 * �Լ� ���ο��� ����ó���� �ѵ� ������ �����ϵ��� �Ѵ� <br>
	 @param CONTAINER_TYPE iContainerType
	 @param int iSlotIndex
	 @return bool
	*/
	bool ItemUse(CONTAINER_TYPE iContainerType, int iSlotIndex);
	
	/**
	 * ������ �����Ŷ�� ���������� �ٸ� �۾��� ���־�� �ϴ� ��� ó�� <br>
	 * ����� Mic�����۸� �ش��Ѵ� <br> 
	 @param CONTAINER_TYPE iContainerType
	 @param int iSlotIndex
	 @return bool  
	*/
	bool ItemPreUse(CONTAINER_TYPE iContainerType, int iSlotIndex);
	
	bool ItemPreUseEx( CONTAINER_TYPE iContainerType, int iSlotIndex );					//����

	bool FWItemPreUseEx( CONTAINER_TYPE iContainerType, int iSlotIndex );

	bool SItemPreUseEx( CONTAINER_TYPE iContainerType, int iSlotIndex );
	/**
	* ��Ÿ���� ������ <br>
	@param TRASH_ITEM item
	@return bool
	*/
	bool RunCoolTime(TRASH_ITEM item);
	
	/**
	 * ���� �������� ������ Ȱ�����⽽���� �����ϵ��� ��û�Ѵ� <br>
	 @param NONE
	 @return int
	*/
	int	SendReqWeaponExchange();

	/**
	* Ȱ���� ���� ���� ��ġ�� ���´� 1, 2 <br>
	@param NONE
	@return int
	*/
	int	GetActiveWeaponSlot();

	/**
	* �Ǹ�â�� �ö� �������� ��ġ ������ ����Ű�� <br>
	* �ش� ��ġ�� �������� ��Ȱ��ȭ�� ǥ���ϵ��� �����Ѵ� <br>
	@param SPSelectItem SellItem		�Ǹ��� ������ ��ġ ����
	@return NONE
	*/
	void SetSellSelectItem(SPSelectItem SellItem, bool bSell = true);

	/**
	 * �����̳� �� ������ ItemID�� ���ϴ� SPItem* �� ���´� <br> 
	 * Quick Slot�� <br> 
	 @param CONTAINER_TYPE iType
	 @param int iItemID
	 @param int iStack					�־��� �������� ���ð� ũ�ų� ���ƾ� �Ѵ� ����Ʈ 1��
	 @return SPItem*
	*/
	SPItem* GetSPItem(CONTAINER_TYPE iType, int iItemID, int iStack = 1);
	
	/**
	 * �ش� �����̳� �� ������ ItemID�� ���ϴ� �͵��� �� Stack Count �� ����<br> 
	 @param CONTAINER_TYPE iType
	 @param int iItemID
	 @param bool bCheckRequire			true�� ��� �ð����ѿ� �ɸ� �������� �����Ѵ�
	 @return int
	*/
	int	GetTotalStackCount(CONTAINER_TYPE iType, int iItemID, bool bCheckRequire = true);	

	/**
	 * �ش� �����̳� �� �־��� �������� ������ ���Ǻ��� ũ�ų� ������ Ȯ�� <br> 
	 * ���� ������ üũ�Ѵ� <br>
	 * ����Ʈ �� <br>
	 @param CONTAINER_TYPE iType		�����̳� Ÿ��
	 @param int iItemID					������ ���̵�
	 @param int iCheckStack				Ȯ���� ���ü�
	 @return bool						iCheckStack���� ũ�� true
	*/
	bool IsBiggerStack(CONTAINER_TYPE iType, int iItemID, int iCheckStack);

    /**
	* �ش� �����̳� �� �־��� �������� ������ ���Ǻ��� ũ�ų� ������ Ȯ�� <br> 
	* ó�� ���Ժ��� ������ ������� 5���� ���� üũ�Ѵ� <br>
	* ����Ʈ �� <br>
	@param CONTAINER_TYPE iType		�����̳� Ÿ��
	@param int iItemID					������ ���̵�
	@param int iCheckStack				Ȯ���� ���ü�
	@return bool						iCheckStack���� ũ�� true
    */
	bool IsBiggerStack5(CONTAINER_TYPE iType, int iItemID, int iCheckStack);

	/**
	 * �־��� Ÿ�Կ� �ǰ� ���(����,�м�)�� ���� ��Ȳ�� Ȯ���Ѵ� <br>	 
	 @param  int iCheckType			1, 3�� ��� ���� 2,4�ΰ�� �м�
	 @param  int iCheckSlotIndex = 0  EQUIP_SLOT_MAX - 1 �� ��� ��� ���� �׿� 0-15���� ����üũ
	 @return  bool					������ ������ ��� true
	*/
	bool CheckEquipInven(int iCheckType, int iCheckSlotIndex = 0);

	/**
	 * �־��� Ÿ�Կ� �ǰ� ����� ���� ��� ID���� Ȯ���Ѵ� <br>
	 @param  int iCheckType			1, 3�� ��� ���� 2,4�ΰ�� �м�
	 @param  int iCheckSlotIndex = 0  0-15���� ����üũ
     @param	 int iCheckMotionID = 0	Ȯ���� ��� ��
	 @return  bool					������ ������ ��� true
	*/
	bool CheckEquipMotion(int iCheckType, int iCheckSlotIndex = 0, int iCheckMotionID = 0);

	/**
	 * �Ⱦ��� �������� ItemID�� ���´� <br>
	 * Quick Slot�� <br>
	 @param NONE
	 @return int (0�ΰ�� ���� ������ �ִ°���)
	*/
	int GetPickUpItemID();

	/**
	* �ı� ���������� ��� �Ȱ����� Ȯ�� <br>
	@param 
	@return 
	*/
	bool IsTrashItem() {
		return m_TrashItem.IsNull();
	}

	/**
	* �������� �����ҽ� ��â ���ɼ��� ���� ���� �˻縦 �Ѵ� <br>
	@param int iItemID = 0 �˻��� ������ ID (0�ΰ�� Pick Up�� �������� �˻�)
	@param bool bPvp = false	PVP ��Ȳ�� üũ���� (true�ΰ�� Pvp ���� üũ)
	@return bool
	*/
	bool CheckPCStatus(int iItemID = 0, bool bPvp = false);

	/**  
	 * �κ��丮 ���, �мǿ� ��ȥ �������� �����ϰ� �ִ��� Ȯ���Ѵ� <br>
	 @param  
	 @return bool								����� true
	*/  
	bool CheckEquipWeddingItem();

	/**
	 * Ʈ���̵忡 �ö� ��� ������ ���� ����Ʈ�� �����Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void ClearAllTradeItem();

	/**
	 * �ش��ε����� Ʈ���̵� ������ ������ �����Ѵ� <br>
	 @param int iIndex = -1
	 @return bool
	*/
	bool ClearTradeItem(int iIndex = -1);

	/**
	 * ���� �Ⱦ��� �������� �����Ѵٸ� Ʈ���̵尡 ������ ������������ Ȯ���Ѵ� <br> 
	 @param
	 @return
	*/
	bool IsTradeEnable(CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID, int iSlotIndex = -1);

	/**
	 * �ش� Ʈ���̵� ������ ������ ������ ������ �����Ѵ� <br>
	 @param int iIndex
	 @param CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID
	 @param int iSlotIndex = -1
	 @return bool
	*/
	bool SetTradeItem(int iIndex, CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID, int iSlotIndex = -1);

	/**
	 * �ش��ε����� Ʈ���̵� ������ ������ �����´� <br>
	 @param int iIndex
	 @return SPSelectItem*
	*/
	SPSelectItem* GetTradeItem(int iIndex);

	/**
	 * �ش� �����̳��� ���� �������� ���� Ʈ���̵� �� ������������ Ȯ���Ѵ� <br>
	 @param CONTAINER_TYPE iType
	 @param int iSlotIndex
	 @return int Ʈ���̵� ����Ʈ���� �ε��� (���°�� -1)
	*/
	int IsTradeItem(CONTAINER_TYPE iType, int iSlotIndex);
	
	/**
	 * ���λ����� �ö� ��� ������ ���� ����Ʈ�� �����Ѵ� <br>
	 @param 
	 @return
	*/
	void ClearAllUserShopItem();
	
	/**
	 * �ش��ε����� �ø� ������ ���� �� �����Ѵ� <br>
	 @param 
	 @return
	*/
	bool ClearUserShopItem(int iIndex = -1);
	
	/**
	 * ���λ��� ������ �ø� ���� <br>
	 @param int iIndex					���λ��� ����Ʈ�� �ε���
	 @param CONTAINER_TYPE iType		�ش� �������� �����̳� Ÿ��
	 @param int iSlotIndex				�ش� �������� ���� �ε���
	 @return bool
	*/
	bool SetUserShopItem(int iIndex, CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID, int iSlotIndex = -1);

	/**
	 * �������� �Ⱦ� ��Ű�� ���ϵ��� �ϴ� ��� ���� ���� ��� <br>
	 * �������� ������ ���λ��� ������ ������ �Ǹ� ���� ���� üũ�� �����ϵ��� �Ǿ� ���� <br>
	 @param int iIndex					���λ��� ����Ʈ�� �ε���
	 @param CONTAINER_TYPE iType		�ش� �������� �����̳� Ÿ��
	 @param int iSlotIndex				�ش� �������� ���� �ε���
	 @return bool
	 @warning SetBlockItem �� �̿��Ұ�
	*/
	bool SetUserShopItemFake(int iIndex, CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID, int iSlotIndex = -1);
	
	/**
	 * ���λ��� ����Ʈ���� �ø� ������ ������ Ȯ�� <br>
	 @param int iIndex
	 @return SPSelectItem*
	*/
	SPSelectItem* GetUserShopItem(int iIndex);
	
	/**
	 * �־��� ��ġ�� �κ��丮 �������� ���� ���λ����� �ö� �ִ��� Ȯ���Ѵ� <br>
	 @param CONTAINER_TYPE iType
	 @param int iSlotIndex
	 @return int  -1�� ��� ��ϵǾ� ���� ���� ������
	*/
	int	IsUserShopItem(CONTAINER_TYPE iType, int iSlotIndex);

	void ClearAllPetShopItem( PET_PLACE iPlace );
	bool ClearPetShopItem( PET_PLACE iPlace, int iIndex = -1 );
	bool SetPetShopItem( PET_PLACE iPlace, int iIndex, CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID, int iSlotIndex = -1 );
	bool SetPetShopItemFake( PET_PLACE iPlace, int iIndex, CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID, int iSlotIndex = -1 );
	SPSelectItem *GetPetShopItem( PET_PLACE iPlace, int iIndex );
	int IsPetShopItem( CONTAINER_TYPE iType, int iSlotIndex );
	
	/**
	 * �������� �Ⱦ� ��Ű�� ���ϵ��� �ϴ� ��� ���� ���� ��� <br>
	 @param 
	 @return  
	*/
	bool SetBlockItem(int iIndex, CONTAINER_TYPE iType = CONTAINER_TYPE_INVALID, int iSlotIndex = -1);
	
	/**
	 * ��� �� �������� Ǯ���ش� <br>
	 @param 
	 @return  
	*/
	void ClearAllBlockItem();
	
	/**
	 * �־��� ��ġ�� �������� ���� Ǯ���ش� <br>
	 @param 
	 @return  
	*/
	bool ClearBlockItem(int iIndex = -1);
	
	/**
	 * �־��� ��ġ�� ���� ������ ������ Ȯ���Ѵ� <br>
	 @param 
	 @return  
	*/
	SPSelectItem* GetBlockItem(int iIndex);
	
	/**
	 * �־��� ��ġ�� �������� ���� ���Ǿ� �ִ��� Ȯ���Ѵ� <br> 
	 @param 
	 @return  
	*/
	int	IsBlockItem(CONTAINER_TYPE iType, int iSlotIndex);

	/**
	 * �� ���� ���������� ��� <br>
	 * ��Ͻ� ������ ���� <br> 
	 @param CONTAINER_TYPE iType
	 @param int iSlotIndex
	 @return bool
	*/
	bool SetPetFeedItem(PET_PLACE iPlace, CONTAINER_TYPE iType, int iSlotIndex);

	/**
	 * �� ���� ���������� ��� ���� <br>
	 @param NULL
	 @return NULL
	*/
	void ClearPetFeedItem( PET_PLACE iPlace );

	void ClearPetFeedAll( void );

	bool SetPetFeedEnergyItem( PET_PLACE iPlace, CONTAINER_TYPE iType, int iSlotIndex );
	void ClearPetFeedEnergyItem( PET_PLACE iPlace );
	void ClearPetFeedEnergyAll( void );

	/**
	 * �� ���̿����� ��ϵ� ���������� Ȯ��<br>
	 @param CONTAINER_TYPE iType
	 @param int iSlotIndex
	 @return bool
	*/
	bool IsPetFeedItem(CONTAINER_TYPE iType, int iSlotIndex);
	bool IsPetFeedEnergyItem(CONTAINER_TYPE iType, int iSlotIndex);

	/**
	 * ��ġ�� ������ ���� ����<br>
	 * ��Ͻ� ������ ���� <br> 
	 @param
	 @return
	*/
	bool SetMicItem(CONTAINER_TYPE iType, int iSlotIndex);

	bool SetFindItem( CONTAINER_TYPE iType, int iSlotIndex );
	
	bool SetFollowItem( CONTAINER_TYPE iType, int iSlotIndex );

	bool SetSnatchItem( CONTAINER_TYPE iType, int iSlotIndex );
	/**
	 * ��ġ�� ������ ��� ���� <br>
	 @param
	 @return
	*/
	void ClearMicItem();
	
	void ClearFindItem();

	void ClearFollowItem();

	void ClearSnatchItem();
	/**
	 * ��ġ�� ���������� ���� �Ǿ� �ִ��� Ȯ���Ѵ� <br>
	 @param
	 @return
	*/
	bool IsMicItem(CONTAINER_TYPE iType, int iSlotIndex);
	
	bool IsFindItem( CONTAINER_TYPE iType, int iSlotIndex );

	bool IsFollowItem( CONTAINER_TYPE iType, int iSlotIndex );

	bool IsSnatchItem( CONTAINER_TYPE iType, int iSlotIndex );
	/**
	 * ���� Notice Box�� ����Ȳ�� Ȯ���Ѵ� <br>
	 @param NONE
	 @return NOTICE_USE
	*/
	NOTICE_USE GetCurNoticeUse();
	
	/**
	 * ���� Notice Box�� ����Ȳ�� �����Ѵ� <br>
	 @param NOTICE_USE iNoticeUse
	 @return NONE
	*/
	void SetNoticeUse(NOTICE_USE iNoticeUse);	
	
	/**
	 * �ش��κ��丮 Ÿ���� �ִ� ������ �� Ȯ�� <br>
	 * �������� ��ũ�� ������ �ǹ� <br> 
	 @param int iType		�����̳� Ÿ��
	 @return  int
	*/
	int GetMaxInvenPage(int iType);

	/**
	* ����ũ �������� ����ϴ� ��� ��Ŷ�� ���� <br>
	* ȣ���� ����ũ �������̽����� �� <br>
	@param std::string Msg = ""		�Բ� ������ �޽���
	@return bool
	*/
	bool SendMicItemUseMsg(std::string Msg = "");

	bool SendBugle( std::string Msg = "");
	
	bool SendWhere ( std::string Msg = "", int iID = 0, WINDOW_STATE WinState = WINDOW_NULL );//[liuyang, 2008.9.2]add
		
	bool SendWhereEx( std::string Msg = "", int iID = 0, WINDOW_STATE WinState = WINDOW_NULL );//[liuyang, 2008.9.8]add
	
	bool FollowPeople( std::string Msg = "" );//[liuyang, 2008.10.10]

	bool SnatchFriend( std::string Msg = "" );//[liuyang, 2008.10.10]
protected:
	/**  
	*  
	@param  
	@return 
	*/  
	inline bool IsEnableContainer(CONTAINER_TYPE iContainerType);

	/**
	* �κ��丮 ���� ���� <br>
	@param NONE
	@return NONE
	*/
	void InitInventory();

	/**
	* ��� ���� ���� <br> 
	@param NONE
	@return NONE
	*/
	void InitFigure();

	/**
	* â�� ���� ���� <br>
	@param NONE
	@return NONE
	*/
	void InitStorage();
	
	/**
	 * ĳ�� �κ� ���� ���� <br>
	 @param 
	 @return  
	*/
	void InitCashItem();


	//[xialin 2008/07/21] add
	void InitWearItem();

	/**
	 * PET ��� ���� ���� <br>  
	 @param 
	 @return
	*/
	void InitPetEquip();

	/**
	 * ������ ��� Inventory�� �����Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void ClearAllInventory();

	/**
	 * ������ ��� Figure Inventory�� �����Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void ClearAllFigure();

	/**
	 * ������ ��� Storage �� �����Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void ClearAllStorage();

	/**
	 * ������ ��� Cash �� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void ClearCashItem();	

	/**
	 * ������ ��� Pet ��� �����Ѵ� <br> 
	 @param 
	 @return
	*/
	void ClearPetEquip();

	/**
	* �κ��丮�� ��� ��ũ�ѹٸ� ���� <br>
	@param NONE
	@return NONE
	*/
	void SetItemScroll(CONTAINER_TYPE iContainerType = CONTAINER_TYPE_INVALID);

	/**
	 * ���콺 �������� �����Ѵ� <br>
	 @param NONE
	 @return bool
	*/
	bool SetMouseIcon(/*SPItem* pItem*/);

	/**
	 * Pick Up�� �������� ���� ���������� ���� �Ѵ� <br>
	 @param NONE
	 @return bool
	*/
	bool RecoverIcon();

	/**
	* ���ø� �������� �����. <br>
	* �Ⱦ� ���¸� �����ϰ�, �Ⱦ� ��ġ ������ �����<br>
	* ���콺 Ŀ���� �ö� �������� ����� <br>
	@param NONE
	@return NONE
	*/
	void DeletePickupItem();	

	/** 
	 * �κ��丮 �������� �����Ѵ� <br>
	 @param CONTAINER_ITEM *pContainerItem
	 @return bool
	 @warning ���ο� �� ������ ����ó���� ����
	*/
	bool SetInventoryIcon(CONTAINER_ITEM *pContainerItem, bool bSetEquip = true);

	/**
	* ���� �������� ��� ó�� <br>
	@param CONTAINER_ITEM *pContainerItem
	@return bool
	*/
	bool SetEquipTakeOff( CONTAINER_ITEM *pContainerItem );

	/**
	 * Disable �Ǿ�� �� �����۵��� ������ ���������� ǥ���ϵ��� �Ѵ� <br>
	 * Npc Sell, PC Trade �� �ö��ִ� �����۵� <br>
	 * OnChangeInventory ���� ȣ���ϸ� Scroll �� ������ �����ؾ� �Ұ��̴� <br>
	 @param NONE
	 @return NONE
	*/
	void SetDisableIcon();
	
	/**
	 * �ش� �������� �����ϴ� ���(?) ���� ĭ��
	 @param
	 @return
	*/
	int GetSlotCount(CONTAINER_TYPE iType, int iSlotIndex);

	/**
	* �־��� setID �� ��Ʈ �������� � �����ϰ� �ִ��� Ȯ�� <br>
	* FIGURE_EQUIP,	FIGURE_FASHION �� �˻��Ͽ� Ȯ�� <br>
	 @param int iSetID Ȯ���� SetItemID
	 @return  int �����ϰ� �ִ� �ش� �¾������� ���� <br>
	*/
	int GetTotalSetItemPieces(int iSetID);

	/**
	 * ������ ��� �޽����� ������ �����Ѵ� <br>
	 @param CONTAINER_TYPE iContainerType
	 @param int iSlotIndex
	 @return bool
	*/
	bool SendItemUseMsg(CONTAINER_TYPE iContainerType, int iSlotIndex);	

	/**
	 * �����Կ� ������ �����̳ʰ� ������� �˸� <br> 
	 @param int iItemID
	 @return bool
	*/
	bool SendQuickSlotUpdate(int iItemID);		

	/**
	 * ������ �Ǹ�â, ����â � ��ũ�Ǵ� �����۵��� �ʱ�ȭ �Ѵ� <br> 
	 @param 
	 @return
	*/
	void ClearOutSideControl();

	/**
	 * ���� �÷��̾��� ���, �м� ������ ������Ʈ �Ѵ� <br> 
	 * �������̽� ǥ���� ������ <br>
	 * �ǱԾ� ������ ������Ʈ �Ѵ� <br> 
	 @param 
	 @return
	*/
	void ReflashFigure();	
	

public:
	bool				m_bPickup;					/**< �������� �鿩 �÷������� <br> */

private:
	SPGameObject*		m_pParent;					/**< ���� ���� Object (Player) <br> */
	
	bool				m_bClickMove;				/**< �巡�� ���� <br> */
	int					m_iItemLClickIndex;			/**< LButton���� Ŭ���� �κ��丮 �ε��� <br> */
	int					m_iEquipLClickIndex;		/**< LButton���� Ŭ���� ��� �ε��� <br> */
	int					m_iStorageLClickIndex;		/**< LButton���� Ŭ���� â�� �ε��� <br> */
	int					m_iPetLClickIndex;			/**< LButton���� Ŭ���� �� �ε��� <br> */	
	
	int					m_iCurrentWeaponSlot;		/**< ���� ���õ� ���� ���� <br> */

	std::vector<SPItem*> m_vpInventory[CONTAINER_MAX];	/**< �κ��丮, ���, â�� �� ��� ���� ���� <br> */

	int m_iInventorySlot[CONTAINER_MAX];			/**< �κ��丮 ���� �� <br> */	
	int m_iExtendSlot[CONTAINER_MAX];				/**< �κ��丮 ���� ���� Ȯ�� <br> */
	int m_iInvenPage[CONTAINER_MAX];				/**< �κ��丮 Type�� ��ũ�� ������ ������ <br> */	
	int m_iCurInvenPage[CONTAINER_MAX];				/**< �κ��丮 Type�� ��ũ�� ��ġ ���� <br> */
	
	int m_iStorageSlot;								/**< â�� ���� ���� <br> */
	int m_iStorageExtendSlot;						/**< â�� Ȯ�� ���� <br> */
	int m_iStoragePage;								/**< â�� ��ũ�� ������ ������ <br> */
	int m_iCurStoragePage;							/**< ���� â�� ��ũ�� ������ ������ <br> */
	
	//[2005/6/21] Current Select Container
	CONTAINER_TYPE m_iCurrentContainer;				/**< ��� �����̳��� ���� ���õȰ� <br> */
	CONTAINER_TYPE m_iCurrentInventoryType;			/**< ���� ���õ� �κ��丮 â Ÿ�� <br> */
	CONTAINER_TYPE m_iCurrentFigureType;			/**< ���� ���õ� ��� â Ÿ�� <br> */

	//[2005/6/22]
	SPSelectItem m_PickUpItem;						/**< ���� �Ⱦ��� ������ ��ũ ���� <br> */	

	SPSelectItem m_TrashItem;						/**< �ı��� �Ϸ��� �÷����� �������� ���� <br> */
	
	SPSelectItem m_SellItem;						/**< ���� �Ǹ� ������ ��ũ ���� <br> */

	SPSelectItem m_MicItem;							/**< ��ġ�� ������ ��ũ ���� <br> */
	
	SPSelectItem m_FindItem;						//����
	
	SPSelectItem m_FollowItem;						//׷��

	SPSelectItem m_SnatchItem;						//ץ��

	SPSelectItem m_TradeItem[MAX_PC_TRADE_SLOT];	/**< �ڽ��� �ŷ� �������� �ø��µ� ��� �������̽� �뵵..<br> */
	
	SPSelectItem m_UserShopItem[FM_MAX_SELLITEM];	/**< ���λ����� �÷����� ������ ����Ʈ <br> */
	SPSelectItem m_PetShopItem[PET_PLACE_TYPE_NUMBER][FM_MAX_SELLITEM];	//!< pet's shop items

	struct t_PetFeed
	{
		SPSelectItem	feedNormal;
		SPSelectItem	feedEnergy;
	};
	t_PetFeed m_vecPetFeeds[PET_PLACE_TYPE_NUMBER];

	SPSelectItem m_BlockItem[MAX_ITEM_BLOCK];		/**< <br> */

	bool	m_bSendRequest;							/**< �ڽ��� �ŷ� ��û ��Ŷ�� ���´��� <br> true�� ��� ��Ŷ�� ������ ������ ��ٸ��� ��Ȳ <br> */
	
	bool	m_bRequested;							/**< �ڽ��� �ŷ� ��û�� �޾� �ŷ���û �޽��� â�� �� ��� <br> */

	CHANGE_SLOT m_ChangeSlot;						/**< ������ ������ ��쿡�� ����Ѵ�... <br> */

	NOTICE_USE	m_iNoticeUse;						/**< ���� Noticeâ�� �̿� �뵵 <br> */
};