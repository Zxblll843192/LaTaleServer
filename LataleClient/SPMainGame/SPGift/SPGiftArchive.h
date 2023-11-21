#pragma once

class SPGiftAttr;

class SPGiftArchive {
public:
	SPGiftArchive();
	~SPGiftArchive();

	/**
	 * ��� ���� ����Ʈ�� �����Ѵ� <br> 
	 @param 
	 @return
	*/
	void DeleteAllGift();

	/**
	 * ���� ����Ʈ�� ������ �߰��Ѵ� <br>
	 @param 
	 @return
	*/
	int AddGift(SPGiftAttr* pGiftAttr);

	/**
	 * ���� ������ �����´� <br>
	 @param 
	 @return
	*/
	int	GetSize();

	/**
	 * ���� �����͸� �����´� <br>
	 @param 
	 @return
	*/
	SPGiftAttr* GetGiftAttr(int iIndex);

	/**
	 * �ش�Ű�� ������ ����Ʈ���� �����Ѵ� <br> 
	 @param 
	 @return
	*/
	bool DeleteGift(INT64 iKey);

private:
	std::vector<SPGiftAttr*>	m_vpGift;		/**< ������ �߰��Ѵ� <br> */
};



