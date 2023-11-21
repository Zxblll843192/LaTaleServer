#pragma once

class SPGiftAttr;
class SPGiftArchive;

class SPGiftManager {
public:
	SPGiftManager();
	~SPGiftManager();

	/**
	 * �ʱ�ȭ �Ѵ� <br> 
	 @param 
	 @return
	*/
	void Clear();

	/**
	 * ������ �߰��Ѵ� <br> 
	 @param 
	 @return
	*/
	bool InsertGift(int iItemID, INT64 iKeyID);
	
	/**
	 * LDT���� �� ������ �ε� <br> 
	 @param 
	 @return
	*/
	bool LoadGiftLDT(int iItemID, SPGiftAttr* pGiftAttr);

	/**
	 * ����Ʈ �ε���� ����<br>
	 @param 
	 @return
	*/
	void SetGiftLoad(bool bLoad) { m_bGiftListLoad = bLoad;	}
	
	/**
	 * ����Ʈ�� �ε�Ǿ��ִ��� Ȯ�� <br>
	 @param 
	 @return
	*/
	bool IsGiftListLoad() { return m_bGiftListLoad; }

	/**
	 * ���� ����Ʈ ũ�� Ȯ�� <br> 
	 @param 
	 @return
	*/
	int	GetGiftListSize();

	/**
	 * �ش� ��ġ�� ���� �����͸� �����´� <br> 
	 @param 
	 @return
	*/
	SPGiftAttr* GetGift(int iIndex);

	/**
	 * �ش� Key�� ���� �����͸� �����Ѵ� <br> 
	 @param 
	 @return
	*/
	bool DeleteGiftItem(UINT64 iKey);

	/**
	 * ��������Ʈ�� ��û�Ѵ� <br> 
	 @param 
	 @return
	*/
	void SendGiftList();

	/**
	 * �ش� ��ġ�� ���� �ޱ� ��û�Ѵ� <br> 
	 @param 
	 @return
	*/
	void SendGetGiftItem(int iIndex);

	SPGiftArchive*	GetGiftArchive() { return m_pGiftArchive; }
	

private:
	SPGiftArchive*	m_pGiftArchive;			/**< Gift List Data <br> */

	SPLDTFile*		m_pLDTGiftData;			/**< Gift Data LDT <br> */

	bool			m_bGiftListLoad;		/**< Gift List�� �ε�Ǿ� �ִ��� <br> */
};