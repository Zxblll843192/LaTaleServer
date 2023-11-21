#pragma once

class SPMailArchive {
public:
	SPMailArchive();
	~SPMailArchive();

	/**
	 * ���� ����Ʈ�� �޴� ��� <br> 
	 * ���� ��� �߰� <br>
	 @param 
	 @return
	*/
	int AddMail(SPMailAttr* pMail);
	
	/**
	 * �������� �޴� ��� <br>
	 * ����Ʈ�� �տ� �߰� <br>
	 @param 
	 @return
	*/
	int AddNewMail(SPMailAttr* pMail);
	
	/**
	 * ��� ������ ���� <br>
	 @param 
	 @return
	*/
	void DeleteAllMail();
	
	/**
	 * ���� ����Ʈ�� ũ�⸦ ��ȯ <br>
	 @param 
	 @return
	*/
	int GetSize();

	/**
	 * �־��� �ε��� ��ġ�� MailAttr�� ��ȯ <br>
	 @param 
	 @return
	*/
	SPMailAttr* GetMailAttr(int iIndex);

	/**
	 * �־��� ���� ID�� MailAttr�� ��ȯ <br>
	 @param 
	 @return
	*/
	SPMailAttr* FindMail(UINT64 iMailID);

	/**
	 * �־��� ���� ID�� MailAttr���� ��� ������ ������, ���������� ���� <br> 
	 @param 
	 @return
	*/
	bool ClearMailHeader(UINT64 iMailID);
	
	/**
	 * �־��� ���� ID�� ������ ���� <br>
	 @param 
	 @return
	*/
	bool DeleteMail(UINT64 iMailID);

	/**
	 * �������� ��Ʈ <br> 
	 @param 
	 @return
	*/
	bool SetSort();

	/**
	 * ����Ʈ���� ���� ���� ������ �ִ��� Ȯ���Ѵ� <br> 
	 * �ϳ��� ���� ���� ������ �ִ°�� false <br>
	 @param 
	 @return
	*/
	bool CheckReadMail();

protected:
	

private:
	std::vector<SPMailAttr*>	m_vpMail;
};