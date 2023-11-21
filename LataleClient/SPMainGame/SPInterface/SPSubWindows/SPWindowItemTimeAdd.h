#pragma once


#define WIID_ITEM_TIMEADD_TOP				(WIID_ITEM_TIMEADD	+	1)
#define WIID_ITEM_TIMEADD_CENTER			(WIID_ITEM_TIMEADD	+	2)
#define WIID_ITEM_TIMEADD_BOTTOM			(WIID_ITEM_TIMEADD	+	3)
#define WIID_ITEM_TIMEADD_TITLE				(WIID_ITEM_TIMEADD	+	5)
#define WIID_ITEM_TIMEADD_CLOSE				(WIID_ITEM_TIMEADD	+	6)

#define WIID_ITEM_TIMEADD_LINE1				(WIID_ITEM_TIMEADD	+	8)
#define WIID_ITEM_TIMEADD_LINE2				(WIID_ITEM_TIMEADD	+	9)

#define WIID_ITEM_TIMEADD_SKIN				(WIID_ITEM_TIMEADD	+	10)			//��� ����

#define WIID_ITEM_TIMEADD_SLOTLINE			(WIID_ITEM_TIMEADD	+	20)			//3���� ���� �ܰ���
#define WIID_ITEM_TIMEADD_SLOTICON			(WIID_ITEM_TIMEADD	+	30)			//3���� ���� ������
#define WIID_ITEM_TIMEADD_SLOTBUTTON		(WIID_ITEM_TIMEADD	+	40)			//3���� ���� ��ư

#define WIID_ITEM_TIMEADD_CURSOR1			(WIID_ITEM_TIMEADD	+	100)
#define WIID_ITEM_TIMEADD_CURSOR2			(WIID_ITEM_TIMEADD	+	110)
#define WIID_ITEM_TIMEADD_TOOLTIP			(WIID_ITEM_TIMEADD	+	120)

#define WIID_ITEM_TIMEADD_PLUS				(WIID_ITEM_TIMEADD	+	150)
#define WIID_ITEM_TIMEADD_EQUAL				(WIID_ITEM_TIMEADD	+	160)
#define WIID_ITEM_TIMEADD_QUESTION			(WIID_ITEM_TIMEADD	+	165)

#define WIID_ITEM_TIMEADD_OK				(WIID_ITEM_TIMEADD	+	170)
#define WIID_ITEM_TIMEADD_CANCEL			(WIID_ITEM_TIMEADD	+	180)



const int MAX_TIMEADD_SLOT					= 3;								//���԰���
class SPWindow;
class SPWindowButton;

enum TIMEADD_STATUS {
	TIMEADD_STATUS_FIRST			= 0,
	TIMEADD_STATUS_SECOND			= 1,
	TIMEADD_STATUS_READY			= 2,
	TIMEADD_STATUS_RESULT			= 3,
	TIMEADD_STATUS_END				= 4,
};

#include "SPPlayerInvenArchive.h"


class SPWindowItemTimeAdd : public SPWindow
{

public:
	SPWindowItemTimeAdd(WND_ID WndClassID, INSTANCE_ID InstanceID);
	SPWindowItemTimeAdd(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowItemTimeAdd();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);


protected:
	void ProcessCursor(float fTime);
	void CreateSubWindow();	
	void SetStatus(TIMEADD_STATUS iStatus);
	void ClearAllSlotInterface();
	void ClearSlotInterface(int iIndex);
	void SetSlotInterface(int iIndex, SPItem* pItem);

	bool SetFirstItem();
	bool SetSecondItem();
	bool CheckTimeAddItem(SPItem* pItem);

	bool SendAddTime();

	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnResult(WPARAM wParam, LPARAM lParam);
	int OnClose(WPARAM wParam, LPARAM lParam);
	int OnOK(WPARAM wParam, LPARAM lParam);
	int OnCancel(WPARAM wParam, LPARAM lParam);	
	int OnLButtonUp(WPARAM wParam, LPARAM lParam);
	int OnItemClick(unsigned int iUiID, WPARAM wParam, LPARAM lParam);	
	int OnToolTipMove			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipEnter			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipOut			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	

private:	
	SPTexture* m_pQuestion;
	SPTexture* m_pDisable;		
	RECT	m_rtSrcDisable;												/**< ��Ȱ�� ǥ���� �ҽ� <br> */
	
	int		m_iCursorDirection;
	float	m_fCursorAccmulateTime;
	int		m_iFrame;

	SPWindow* m_pIcon[MAX_TIMEADD_SLOT];
	SPWindow* m_pCursorFirst;
	SPWindow* m_pCursorSecond;
	SPWindow* m_pToolTip;
	SPWindowButton* m_pOK;
	SPWindowButton* m_pCancel;
	
	SPItem*	m_pItem[MAX_TIMEADD_SLOT];									/**< ������ ������ ������� �ʴ´� !!! <br> */
	SPItem* m_pItemResult;												/**< ������ ������ ������ ǥ���� <br> */
	SPSelectItem m_SelectItem[MAX_TIMEADD_SLOT];
	
	RECT	m_rtMarkSrc[4];												/**< ICON MARK Src <br> */	
	
	RECT	m_rtStack[MAX_TIMEADD_SLOT];								//List Item Stack Count

	bool	m_bItemAble[MAX_TIMEADD_SLOT];								/**< ���� �÷��� �������� ���� ���밡���� ���������� <br> */
	int		m_iStack[MAX_TIMEADD_SLOT];									/**< ���� Item�� ���� <br> */
	ICON_MARK	m_iItemMark[MAX_TIMEADD_SLOT];							/**< ICON MARK <br> */
	
	TIMEADD_STATUS	m_iTimeAddStatus;

	bool	m_bUse;
};



