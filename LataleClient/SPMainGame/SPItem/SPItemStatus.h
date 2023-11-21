// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPItemStatus
// Comment     : 
// Creation    : metalgeni 2004-11-05 ���� 10:26:19
//***************************************************************************

#pragma once

#include <string>

using namespace std;


enum EQUIP_ID;

class SPItemStatus {
public:
	SPItemStatus();
	SPItemStatus(ITEMSTATUS_ID );	
	SPItemStatus( const SPItemStatus& src );

	virtual ~SPItemStatus();
	virtual LRESULT SPSendMessage(MODEL_VALUE_TYPE mvMsg, LPARAM lParam = 0);

	bool		IsNULL();
	bool		SetItemID(UINT32 iItemID);
	SPItemAttr*	GetItemAttr();

	UINT32		GetItemID();
	int			GetStackCount();
	int			GetRareLevel();

	PACK_OPT*	GetOption(int iOrder);
	int			GetOptionCount();

	int			GetStatusCount();
	int			GetLifeTime();
	void		SetLifeTime(int iLifeTime);

	void		SetExp(INT64 iExp);
	INT64		GetExp();

	void		SetSp(INT16 iSp);	
	INT16		GetSp();

	/**
	 * �ð��� �������� ��ȿ���¸� �����Ѵ� <br>
	 * ����Ʈ ��ȿ���� ���� <br>
	 @param 
	 @return
	*/
	void		SetTimeAvailable(bool bAvailable = false);

	/**
	 * �ð��� �������� ��ȿ�� �������� Ȯ���Ѵ� <br> 
	 @param 
	 @return
	*/
	bool		IsTimeAvailable();

	/**
	 * LifeTime ���� <br> 
	 @param 
	 @return
	*/
	void		DecreaseLifeTime(int iTime);
	
	/**
	 *
	 @param
	 @return
	*/
	int			GetItemSlotIndex() { return m_iItemSlotIndex; }
	
	/**
	 *
	 @param
	 @return
	*/
	int			GetItemStatusID()  { return m_ItemStatusID; }

	/**
	 * <br>
	 @param
	 @return
	*/
	int			GetItemBackPrice()	{ return m_iBackPrice; }

	/**
	 * ��õ ��ǰ ���� ������ �ӽ÷� ������Ʈ ���ش� <br>
	 @param 
	 @return  
	*/
	void		SetHotDesc(std::string strDesc);
	
	void		SetLotteryName(std::string strName);
	/**
	 *
	 @param 
	 @return  
	*/
	std::string GetHotDesc()		{ return m_strHotDesc; }

	std::string GetLotteryName()	{ return m_strLotteryName; }

	virtual bool Copy(SPItemStatus* pSrc);

protected:
	//virtual bool Copy(SPItemStatus* pSrc);
	virtual void SetNull();


protected:
	
	UINT32			m_iItemID;
	SPItemAttr*		m_pItemAttr;

	// �������� �κе�
	ITEMSTATUS_ID	m_ItemStatusID;			// Item ���� //�̾ƴ϶� ��ġ�����̴�.  ������ Ȯ�忡 ���� �뵵����..

	//int			m_nItemSlotIndex;		// Item Slot index (�κ��丮 �׸��� ��ġ)
	int				m_iItemSlotIndex;

	//int			m_nStackCount;			// ���� - ���������̺����� ���ǹ��ϴ�..
	int				m_iStackCount;
	int				m_iLifeTime;			/**< ��ȿ�ð� <br> Ŭ���̾�Ʈ �����̹Ƿ� ������ ��ġ���� ���� <br> */
	int				m_iBackPrice;			// ���ȱ�
	ITEMNO			m_iItemNo;				// ������ ���� ��ȣ
	int				m_iOptPoint;			// ������

	UINT8			m_iRare;				// ���
	PACK_OPT		m_Opt[MAX_ITEM_OPT];	// �ɼ�

	bool			m_bTimeAvailable;		/**< ��ȿ�ð� <br> �������� �����ִ� ������ ���� <br> true�� ��� ��ȿ <br> */
	
	INT64			m_iItemExp;				// �����۰���ġ
	INT16			m_iItemSP;				// ������SP

	std::string		m_strHotDesc;			/**< ��õ ��ǰ ���� �޽����� ���� �ӽ� ���� <br> */

	std::string		m_strLotteryName;		/**[xialin 2008/10/22]add */
};












