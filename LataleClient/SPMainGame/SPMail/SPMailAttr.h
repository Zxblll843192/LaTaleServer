#pragma once

enum MAIL_STATUS {
	MAIL_STATUS_NULL = 0,
	MAIL_STATUS_LIST = 1,
	MAIL_STATUS_VIEW_REQUEST = 2,
	MAIL_STATUS_VIEW = 3,
	MAIL_STATUS_DELETE = 4,
	MAIL_STATUS_MAX = 5,
};

class SPItem;

class SPMailAttr {
public:
	SPMailAttr();
	~SPMailAttr();

	void Init(MAIL_HEADER_ATTACHMENT* pHeaderAttach);

	void SetSubject(char* pSubject, int iLen);

	void SetBody(char* pMemo, int iLen);

	bool SetItem(/*CONTAINER_ITEM* pItem*/);

	/**
	 * ������ �޾Ҵ���? <br> 
	 @param 
	 @return
	*/
	bool IsSendBody() { return m_bSendBody; }

	/**
	 * �ش� ������ �о�ô���? <br>  
	 @param 
	 @return
	*/
	bool IsRead();
	

protected:
	
	void Clear();	
	

public:
	MAIL_HEADER_ATTACHMENT*	m_pHeader;

	//_MAIL_HEADER_ATTACHMENT_SS
	std::string			m_strSubject;		// ����
	int					m_iSubjectLen;		// ���� ����
	
	//Same as _MAIL_INFO_SS
	std::string			m_strReceiver;		// ������, null included
	std::string			m_strMemo;			// ���� (MAX_MAIl_BODY_LEN == 100)
	int					m_iMemoLen;			// ���� ����	

	int					m_iMailType ;		// ����Ÿ�� (���������� ȣȯ�� ���� ����)
	bool				m_bSendBody;		/**< ������ �޾Ҵ��� ? <br> */

	CONTAINER_ITEM		m_ContainerItem;
	SPItem*				m_pItem;			//
};