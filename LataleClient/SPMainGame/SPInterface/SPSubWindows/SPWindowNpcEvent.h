#pragma once


#define WIID_NPC_EVENT_TITLE							(WIID_NPC_EVENT + 1)
#define WIID_NPC_EVENT_EXIT								(WIID_NPC_EVENT + 5)
#define WIID_NPC_EVENT_LINE								(WIID_NPC_EVENT + 7)

#define WIID_NPC_EVENT_BASE								(WIID_NPC_EVENT + 9)

#define WIID_NPC_EVENT_LIST_TITLE_SKIN					(WIID_NPC_EVENT + 10)	//�̺�Ʈ ������ ��� BG
#define WIID_NPC_EVENT_LIST_TITLE						(WIID_NPC_EVENT + 11)

#define WIID_NPC_EVENT_LIST_SKIN						(WIID_NPC_EVENT + 20)
#define WIID_NPC_EVENT_LIST_BUTTON						(WIID_NPC_EVENT + 30)
#define WIID_NPC_EVENT_LIST_ICONSKIN					(WIID_NPC_EVENT + 40)
#define WIID_NPC_EVENT_LIST_ICON						(WIID_NPC_EVENT + 50)
#define WIID_NPC_EVENT_LIST_NAME						(WIID_NPC_EVENT + 60)
#define WIID_NPC_EVENT_LIST_SELECT						(WIID_NPC_EVENT + 70)

#define WIID_NPC_EVENT_PAGE_SKIN						(WIID_NPC_EVENT + 100)
#define WIID_NPC_EVENT_PAGE_PREV						(WIID_NPC_EVENT + 101)
#define WIID_NPC_EVENT_PAGE_NEXT						(WIID_NPC_EVENT + 102)

#define WIID_NPC_EVENT_ARROW							(WIID_NPC_EVENT + 110)	//�ﰢ ȭ��ǥ �̹���

#define WIID_NPC_EVENT_REQ_ITEM_SKIN					(WIID_NPC_EVENT + 120)	//�ʿ� ������ ���� 
#define WIID_NPC_EVENT_REQ_ITEM_TEXT_SKIN				(WIID_NPC_EVENT + 125)
#define WIID_NPC_EVENT_REQ_ITEM_TEXT					(WIID_NPC_EVENT + 126)

#define WIID_NPC_EVENT_REQ_ITEM_ELY_SKIN				(WIID_NPC_EVENT + 130)
#define WIID_NPC_EVENT_REQ_ITEM_ELY						(WIID_NPC_EVENT + 131)
#define WIID_NPC_EVENT_REQ_ITEM_ELY_IMG_L				(WIID_NPC_EVENT + 132)	//L ElyImage
#define WIID_NPC_EVENT_REQ_ITEM_ELY_IMG_R				(WIID_NPC_EVENT + 133)	//R ElyImage

#define WIID_NPC_EVENT_REQ_ITEM_PVP_SKIN				(WIID_NPC_EVENT + 135)
#define WIID_NPC_EVENT_REQ_ITEM_PVP						(WIID_NPC_EVENT + 136)
#define WIID_NPC_EVENT_REQ_ITEM_PVP_IMG_L				(WIID_NPC_EVENT + 137)	//L PvpPoint Image
#define WIID_NPC_EVENT_REQ_ITEM_PVP_IMG_R				(WIID_NPC_EVENT + 138)	//R PvpPoint Image

#define WIID_NPC_EVENT_REQ_ITEM_ICONSKIN				(WIID_NPC_EVENT + 140)	//�ʿ� ������ ����Ʈ ��
#define WIID_NPC_EVENT_REQ_ITEM_ICONBUTTON				(WIID_NPC_EVENT + 150)
#define WIID_NPC_EVENT_REQ_ITEM_ICON					(WIID_NPC_EVENT + 160)

#define WIID_NPC_EVENT_TIP_SKIN							(WIID_NPC_EVENT + 180)	//�� ��� ����
#define WIID_NPC_EVENT_TIP								(WIID_NPC_EVENT + 181)
#define WIID_NPC_EVENT_REQ_ITEM_PLUS1					(WIID_NPC_EVENT + 181)	//+ǥ��
#define WIID_NPC_EVENT_REQ_ITEM_PLUS2					(WIID_NPC_EVENT + 182)
#define WIID_NPC_EVENT_REQ_ITEM_PLUS3					(WIID_NPC_EVENT + 183)

#define WIID_NPC_EVENT_RECEIVE							(WIID_NPC_EVENT + 190)


const int EVENT_PAGE = 6;						/**< ���������� �������� �̺�Ʈ ������ ����� ���� <br> */
const int EVENT_REQ_ITEM = 4;					/**< �������� �ʿ� ������ ���� <br> ������ ��쿡�� 4�� �׿��� ��� 2�� <br> */


#include "SPItemStatus.h"
struct SPNpcEventToolTip {
	std::string		m_strTitle;					/**< Ÿ��Ʋ ���� ������ �������� ���� <br> */
	SPItemStatus	m_pItem;	
	std::string		m_strDesc;

	SPNpcEventToolTip(){
		Clear();
	}

	~SPNpcEventToolTip(){
		Clear();
	}	

	void Clear();
	void SetTitle(std::string strTitle);
};

class SPWindow;
class SPWindowButton;
#include "SPEventDEF.h"


class SPWindowNpcEvent : public SPWindow {
public:
	SPWindowNpcEvent( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowNpcEvent();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);

protected:
	/**
	 * ���� ��Ʈ�� ���� <br>
	 @param 
	 @return  
	*/
	void InitSubControl();
	
	/**
	 * ���� ��Ʈ�� ǥ�� ���� �ʱ�ȭ <br>
	 @param 
	 @return  
	*/
	void ResetSubControl();
	
	/**
	 * ���� ����Ʈ ��Ʈ�� ���� <br>
	 @param 
	 @return  
	*/
	void UpdateRewordList();
	
	/**
	 * �־��� �ε����� ����Ʈ ��Ʈ�� ���� �ʱ�ȭ <br>
	 @param 
	 @return  
	*/
	inline void ClearRewordList(int iIndex);
	
	/**
	 * �־��� �ε����� ����Ʈ ��Ʈ�ѿ� ������ ���� <br>
	 @param 
	 @return  
	*/
	bool SetRewordListIcon(SPNpcEventInfo* pInfo, int iListIndex);		
	
	/**
	 * �ʿ� ������ ����Ʈ ������ �ʱ�ȭ <br>
	 @param 
	 @return  
	*/
	void ResetRequrieList();
	
	/**
	 * �־��� �ε����� �ʿ� ����Ʈ ������ �ʱ�ȭ <br>
	 @param 
	 @return  
	*/
	inline void ClearRequireList(int iIndex);
	
	/**
	 * �ʿ� ����Ʈ ������ ���� <br>
	 @param  
	 @return  
	*/
	void UpdateRequireList();
	
	/**
	 * �־��� �ε����� ����Ʈ ��Ʈ�ѿ� ������ ���� <br>
	 @param 
	 @return  
	*/
	bool SetRequestListIcon(SPQuestItem* pItemInfo, int iListIndex);

	/**
	 * �ʿ� ������ Ȯ�� <br>
	 * ��Ȳ�� ���� ��� ������ Ȯ���Ѵ� <br>
	 @param 
	 @return  
	*/
	bool CheckRequire();
	
	/**
	 * �ʿ� �������� Ȯ�� <br>
	 * ��Ȳ�� ���� ��� �����۰� Ely ������ Ȯ���Ѵ� <br>
	 @param 
	 @return  
	*/
	bool CheckRequireItem();
	
	/**
	 * ������ ���� �κ��丮 ������Ȳ�� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	bool CheckRewordInvenSlot();
	
	/**
	 * �κ��丮 Ǯ�� �ý��� �޽��� ����� �Ѵ� <br>
	 @param 
	 @return  
	*/
	void SetInvenFullMsg(int i);

	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnExit						(WPARAM wParam, LPARAM lParam);						/**< ���� ��ư <br> */
	int OnPrev						(WPARAM wParam, LPARAM lParam);						/**< ���� ��ư <br> */
	int OnNext						(WPARAM wParam, LPARAM lParam);						/**< ���� ��ư <br> */
	int OnReceive					(WPARAM wParam, LPARAM lParam);						/**< �ޱ� ��ư <br> */
	int OnItemClick					(unsigned int uiID, WPARAM wParam, LPARAM lParam);
	int OnRewordToolTipMove			(unsigned int, WPARAM, LPARAM);
	int OnRewordToolTipEnter		(unsigned int, WPARAM, LPARAM);
	int OnRewordToolTipOut			(unsigned int, WPARAM, LPARAM);
	int OnReqToolTipMove			(unsigned int, WPARAM, LPARAM);
	int OnReqToolTipEnter			(unsigned int, WPARAM, LPARAM);
	int OnReqToolTipOut				(unsigned int, WPARAM, LPARAM);


private:
	SPTexture*		m_pTextureBase;							/**< ������ ������ ���ҽ� <br> */
	RECT			m_rtSrcBase[WINDOW_BASE_MAX];			/**< ������ ���� �ҽ� ���� <br> */
	RECT			m_rtDestBase[WINDOW_BASE_MAX];			/**< ������ ���� ��� <br> */	

	SPWindow*		m_pTitle;								/**< Title <br> */

	SPWindow*		m_pSelect[EVENT_PAGE];					/**< ����Ʈ ����ǥ���� <br> */
	SPWindow*		m_pButton[EVENT_PAGE];					/**< ����Ʈ �̺�Ʈ ó���� <br> */
	SPWindow*		m_pName[EVENT_PAGE];					/**< �̸� <br> */	
	SPWindow*		m_pItemSkin[EVENT_PAGE];
	SPWindow*		m_pItemIcon[EVENT_PAGE];				/**< ������ ������ <br> */

	SPWindow*		m_pReqItemButton[EVENT_REQ_ITEM];		/**< �ʿ� ������ ������ <br> */
	SPWindow*		m_pReqItemIcon[EVENT_REQ_ITEM];			/**< �ʿ� ������ ������ <br> */
	
	SPWindow*		m_pPage;								/**< ���� ������ ����Ʈ ������ <br> */
	SPWindowButton*	m_pPrev;								/**< ���� ������ ����Ʈ ���� ��ư <br> */
	SPWindowButton*	m_pNext;								/**< ���� ������ ����Ʈ ���� ��ư <br> */

	SPWindow*		m_pReqEly;								/**< �ʿ� Ely <br> */
	UINT64			m_iTotalReqEly;							/**< �� �ʿ� Ely <br> ������ ���� ��� <br> */

	SPWindow*		m_pReqPvpPoint;							/**< �ʿ� PvpPoint <br> */
	UINT32			m_iTotalReqPvpPoint;					/**< �� �ʿ� PvPPoint <br> ������ ���� ��� <br> */

	SPWindow*		m_pTip;									/**< �� �޽��� <br> */
	SPWindowButton*	m_pRecevie;								/**< �ޱ� ��ư <br> */

	int				m_iMaxPage;								/**< �ִ� ������ <br> */
	int				m_iCurPage;								/**< ���� ������ <br> */
	int				m_iSelect;								/**< ������ ����������̽� �� ������ �ε��� <br> ����, ������ ��� �����ټ� ���� <br> */
	int				m_iSelectIndex;							/**< ������ �����ͻ� ������ �ε��� <br> */

	char			m_szPage[12];							/**< ������ ���ڿ� <br> */

	SPTexture*		m_pDisable;								/**< Disable ǥ���� Texture <br> */	
	RECT			m_rtSrcDisable;							/**< Diable Textrue Src <br> */
	RECT			m_rtMarkSrc[4];							/**< Icon Mark Src <br> */

	RECT			m_rtRewordStack[EVENT_PAGE];			/**< ���� ������ ���� ǥ�� ���� <br> */
	int				m_iRewordStack[EVENT_PAGE];				/**< Static ǥ�� <br> */
	bool			m_bRewordAble[EVENT_PAGE];				/**< false�϶� ��Ȱ��ȭ ǥ�� <br> */	
	ICON_MARK		m_iRewordMark[EVENT_PAGE];				/**< Icon Mark <br> */

	RECT			m_rtReqStack[EVENT_REQ_ITEM];
	int				m_iReqStack[EVENT_REQ_ITEM];
	bool			m_bReqAble[EVENT_REQ_ITEM];
	ICON_MARK		m_iReqMark[EVENT_REQ_ITEM];

	UINT8			m_iReqItemCount;						/**< �ʿ� ������ ���� <br> */
	TRASH_ITEM		m_ReqItem[EVENT_REQ_ITEM];				/**< �ʿ� ������ ���� ���� <br> */
	UINT64			m_iReqItemNo[EVENT_REQ_ITEM];			/**< �ʿ� ������ Item No ���� <br> */
	SPQuestItem		m_ReqToolTipItem[EVENT_REQ_ITEM];		/**< �ʿ� ������ ������ ���� <br> */
};

