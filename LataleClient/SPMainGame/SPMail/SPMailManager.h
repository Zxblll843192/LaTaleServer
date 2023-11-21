#pragma once

class SPMailAttr;
class SPMailArchive;

enum MAIL_VOLUME {
	MAIL_VOLUME_NULL = 0,
	MAIL_VOLUME_SMALL = 1,
	MAIL_VOLUME_MIDDLE = 2,
	MAIL_VOLUME_LARGE = 3,
	MAIL_VOLUME_MAX,
};

class SPMailManager {
public:
	SPMailManager();
	~SPMailManager();

	void Clear();

	int AddMail(SPMailAttr* pMail);

	int AddNewMail(SPMailAttr* pMail);

	void SetMailLoad(bool bLoad) { m_bMailLoad = bLoad; }
	
	bool IsMailListLoad() {	return m_bMailLoad; }

	int	GetMailListSize();
	
	/**
	 * ���� ����Ʈ �����찡 ������ �ڵ������� ���ο� ������ ���°����� ó���� <br> 
	 @param 
	 @return
	*/
	void SetNewMail(bool bNew = false);	
	
	/**
	 * ���ο� ������ �ִ��� Ȯ�� <br> 
	 @param 
	 @return
	*/
	bool IsNewMail() { return m_bNewMail; }

	/**
	* 
	@param 
	@return
	*/
	MAIL_VOLUME GetMailVolume();

	/**
	* ���ϸ���Ʈ�� ������ �������� �ִ°�� ������ ǥ�� ������Ʈ <br> 
	@param 
	@return
	*/
	void CheckNewMail();

	/**
	* �ش� ��ġ�� ���� �����͸� �����´� <br> 
	@param 
	@return
	*/
	SPMailAttr* GetMail(int iIndex);

	/**
	 * 
	 @param 
	 @return
	*/
	void SetSelectMail(int iIndex);

	/**
	* ���õǾ��� ������ ������ <br> 
	@param 
	@return
	*/
	SPMailAttr* GetSelectMail()		{ return m_pSelectMail; }

	/**
	* ���õǾ��� ������ �ε��� ��ȣ <br>
	@param 
	@return
	*/
	int	GetSelectMailIndex()		{ return m_iSelectMail; }

	/**
	 * ���� ����Ʈ ��û <br> 
	 @param 
	 @return
	*/
	void SendGetMailList();

	/**
	 * MailList �������̽� ������Ʈ ��û <br> 
	 @param bool bMsg				���Ͼ˶� ��
	 @return
	*/
	void OnUpdateMailList(bool bMsg = false);

	/**
	 * ���� ���� ���� ��û <br>  
	 @param 
	 @return
	*/
	void SendGetMailBody(int iSelectIndex);
	
	/**
	 * ÷�ι� �ޱ� ��û <br>  
	 @param 
	 @return
	*/
	void SendReceiveBody(int iSelectIndex = -1);

	/**
	 * ���� ���� ��û <br> 
	 @param 
	 @return
	*/
	void SendDeleteMail(int iSelectIndex = -1);

	/**
	 * �ش� ���� ���̵��� ������ ���� <br> 
	 @param 
	 @return
	*/
	bool OnDeleteMail(UINT64 iMailID);

	/**
	 * �ش� ������ ������ ���� ��� ������ ���� <br>
	 @param 
	 @return
	*/
	void OnReadMail(UINT64 iMailID);

	/**
	 * �ش� ���� ���̵��� ������ ÷�� ������ �ʱ�ȭ <br> 
	 @param 
	 @return
	*/
	bool OnClearMailHeader(UINT64 iMailID);		
	

private:
	SPMailArchive* m_pMailArchive;

	bool			m_bMailLoad;			/**< ������ �ε�Ǿ����� <br> */
	int				m_iSelectMail;			/**< UI�� ���õǾ��� ���� �ε��� <br> */
	SPMailAttr*		m_pSelectMail;
	bool			m_bNewMail;				/**< ���ο� ���� ����, ����Ʈ �������� �ʱ�ȭ <br> */
};