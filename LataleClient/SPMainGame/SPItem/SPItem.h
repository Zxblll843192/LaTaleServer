#pragma once

#include <vector>
#include <string>

using namespace std;

struct SPItemAttr;
class SPItemStatus;

/**
* @class SPItem
* @brief �÷��̾ ����ϴ� Item 
* @author Jinhee
* @version 00.00.01
* @date 2005.6.16
* @bug ����
* @warning ����
*/
class SPItem {
public:
	/**
	 * ������
	 @param NONE
	 @return NONE
	*/
	SPItem();
	
	/**
	 * ������ <br> 
	 * �������� ���� Container Type �� �����Ǵ� SlotIndex(��ġ)�� ���ϰ� ���� <br> 
	 @param CONTAINER_TYPE iContainerType
	 @parma int iSlotIndex
	 @return NONE
	*/
	SPItem(CONTAINER_TYPE iContainerType, int iSlotIndex);
	
	/**
	 * ���� <br> 
	 @param NONE
	 @return NONE
	*/
	~SPItem();
	
	
	/**
	 * ItemAttr �� ���� <br> 
	 * ContainerType�� Container_item �� �ǰ��� <br> 
	 * ItemStatus �� ���ؼ� ���� �Ǿ������� ���� <br> 
	 * ���� ���� ��� ����... <br> 
	 @param CONTAINER_TYPE iContainerType
	 @param CONTAINER_ITEM* item = NULL
	 @return bool
	*/
	bool SetItemAttr(CONTAINER_TYPE iContainerType, CONTAINER_ITEM* item = NULL);

	/**
	 * ItemStatus �� ���� <br>
	 * ContainerType�� �ǰ��� ������ <br> 
	 @param CONTAINER_TYPE iContainerType
	 @param CONTAINER_ITEM* item = NULL
	 @return bool
	*/
	bool CreateItemStatus(CONTAINER_TYPE iContainerType, CONTAINER_ITEM* item = NULL);

	/**
	 * ItemID�� Rear���� ������ �ӽ��� ItemStatus������ ���� <br>
	 * ������ <br>
	 @param int iItemID
	 @param int iRear = 1
	 @return bool 
	*/	
	bool SetItemStatus(int iItemID, int iRear = 1);

	/**
	 * ItemStatus �� �����Ѵ� <br>
	 @param CONTAINER_ITEM* item
	 @return bool
	*/
	bool SetItemStatus(CONTAINER_ITEM* item);

	/**
	 * ItemStatus �� �����Ѵ� <br>
	 @param ITEM* item
	 @return bool
	*/
	bool SetItemStatus(ITEM* Item, int iIndex = 0);

	/**
	 * ItemStatus �� �����Ѵ� <br>
	 @ param 
	 @ return
	*/
	bool SetItemStatus(FIGURE_ITEM* Item, int iIndex = 0);

	/**
	 * ������ ���� <br> 
	 * �����̳� Ÿ�԰� ���� �ε��� ����� <br> 
	 @param CONTAINER_TYPE iType
	 @param int iSlotIndex
	 @param SPItem* pItem = NULL
	 @return bool
	*/
	bool SetItem(CONTAINER_TYPE iType, int iSlotIndex, SPItem* pItem = NULL);

	/**
	 * ���õ� �������� Ŭ���� ���ش� <br>
	 @param  NONE
	 @return bool
	*/	
	bool SetClear();
	
	/**
	 * ������ Attribute �� �����´� <br> 
	 @param NONE
	 @return SPItemAttr*
	*/
	SPItemAttr*	GetItemAttr();

	/**
	 * ������ Status�� �����´� <br>
	 @param NONE
	 @return SPItemStatus*
	*/
	SPItemStatus* GetItemStatus();

	/**
	 * �� �������� ��� �ִ��� Ȯ���Ѵ� <br>
	 @ param  NONE
	 @ return bool  true�� ��� ��� �ִ� �������� 
	*/
	bool IsEmptyItem();

	/**
	 * �����̳� Ÿ���� �����´� <br>
	 @param NONE
	 @return CONTAINER_TYPE
	*/
	CONTAINER_TYPE GetContainerType();
	
	/**
	 * ���� �ε����� �����´� <br>
	 @param NONE
	 @return int
	*/
	int	GetSlotIndex();

	/**
	 * �� ���� �ε����� �����´� <br> 
	 @param NONE
	 @return int
	*/
	int GetQuickSlotIndex();
	
	/**
	 * SPItem�� CONTAINER_ITEM���� �籸���Ѵ� <br> 
	 * SPPlayerInventory�� MakeContainerItem()�Լ��� ����� ������ �Ѵ� <br> 
	 @param CONTAINER_ITEM& item
	 @return bool
	*/
	bool ConvertContainerItem(CONTAINER_ITEM* item);
	
	/**
	 * ItemStauts�� �޽����� ���� ���� �޾ƿ´� <br>
	 @param MODEL_VALUE_TYPE iMsgID
	 @return int
	*/
	int GetItemStatusValue(MODEL_VALUE_TYPE iMsgID);

	/**
	 * ItemStauts�� �޽����� ���� ���� �����Ѵ� <br>
	 @param MODEL_VALUE_TYPE iMsgID
	 @param int iValue = 0
	 @return int
	*/
	int SetItemStatusValue(MODEL_VALUE_TYPE iMsgID, int iValue = 0);

	/**
	 * 
	 @param 
	 @return
	*/
	bool DecreaseLifeTime(int iTime);

protected:
	/**
	 * Item �ɹ��� �ʱ�ȭ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void Init();
	
	/**
	* Item ������ ����� 
	@param NONE
	@return NONE
	*/
	void Clear();

private:
	//SPItemAttr*		m_pItemAttr;			/**< Item Table���� ���� <br> */
	SPItemStatus*	m_pItemStatus;				/**< ���� Player�� ���� ��Ȳ������ Item ���� <br> */
	
	CONTAINER_TYPE	m_iContainerType;			/**< �������� ��ġ�� �����̳��� Ÿ�� <br> */
	int				m_iSlotIndex;				/**< �������� ��ġ�� ������ ��ġ <br> */

	unsigned int	m_iInstanceID;				/**< Server���� ��������� �𸣴� Instance ID <br> */	
	
	int				m_iQuickSlotIndex;			/**< Quick Slot �� �ö� ��� Quick Slot Index <br> */
};

