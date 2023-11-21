#pragma once


#define WIID_NPC_EVENTLIST_TITLE							(WIID_NPC_EVENTLIST + 1)
//#define WIID_NPC_EVENTLIST_EXIT								(WIID_NPC_EVENTLIST + 5)
#define WIID_NPC_EVENTLIST_LINE								(WIID_NPC_EVENTLIST + 7)

#define WIID_NPC_EVENTLIST_BASE								(WIID_NPC_EVENTLIST + 9)

//#define WIID_NPC_EVENTLIST_LIST_TITLE_SKIN					(WIID_NPC_EVENTLIST + 10)	//�̺�Ʈ ������ ��� BG
#define WIID_NPC_EVENTLIST_LIST_TITLE						(WIID_NPC_EVENTLIST + 11)

#define WIID_NPC_EVENTLIST_PAGE_SKIN						(WIID_NPC_EVENTLIST + 20)
#define WIID_NPC_EVENTLIST_PAGE								(WIID_NPC_EVENTLIST + 21)
#define WIID_NPC_EVENTLIST_PAGE_PREV						(WIID_NPC_EVENTLIST + 30)
#define WIID_NPC_EVENTLIST_PAGE_NEXT						(WIID_NPC_EVENTLIST + 40)

#define WIID_NPC_EVENTLIST_LIST_SKIN						(WIID_NPC_EVENTLIST + 300)		//11����
#define WIID_NPC_EVENTLIST_LIST_BUTTON						(WIID_NPC_EVENTLIST + 320)
#define WIID_NPC_EVENTLIST_LIST_ICON						(WIID_NPC_EVENTLIST + 340)
#define WIID_NPC_EVENTLIST_LIST_NAME						(WIID_NPC_EVENTLIST + 360)
#define WIID_NPC_EVENTLIST_LIST_SELECT						(WIID_NPC_EVENTLIST + 380)


const int EVENTLIST_PAGE			= 10;


class SPWindowNpcEventList : public SPWindow {
public:
	SPWindowNpcEventList( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowNpcEventList();

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

	void UpdateEventList();

	void UpdateControl();

	SPIMESSAGE_OBJ_MAP_DECLARE()
	//int OnExit						(WPARAM wParam, LPARAM lParam);						/**< ���� ��ư <br> */
	int OnPrev						(WPARAM wParam, LPARAM lParam);						/**< ���� ��ư <br> */
	int OnNext						(WPARAM wParam, LPARAM lParam);						/**< ���� ��ư <br> */	
	int OnItemClick					(unsigned int uiID, WPARAM wParam, LPARAM lParam);
	

private:
	SPTexture*		m_pTextureBase;							/**< ������ ������ ���ҽ� <br> */
	RECT			m_rtSrcBase[WINDOW_BASE_MAX];			/**< ������ ���� �ҽ� ���� <br> */
	RECT			m_rtDestBase[WINDOW_BASE_MAX];			/**< ������ ���� ��� <br> */	
	
	SPWindow*		m_pIcon[EVENTLIST_PAGE];				/**< ����Ʈ ������ <br> */
	SPWindow*		m_pSelect[EVENTLIST_PAGE];				/**< ����Ʈ ����ǥ���� <br> */
	SPWindow*		m_pButton[EVENTLIST_PAGE];				/**< ����Ʈ �̺�Ʈ ó���� <br> */
	SPWindow*		m_pName[EVENTLIST_PAGE];				/**< �̸� <br> */	

	SPWindow*		m_pPage;								/**< ���� ������ ����Ʈ ������ <br> */
	SPWindowButton*	m_pPrev;								/**< ���� ������ ����Ʈ ���� ��ư <br> */
	SPWindowButton*	m_pNext;								/**< ���� ������ ����Ʈ ���� ��ư <br> */

	int				m_iMaxPage;								/**< �ִ� ������ <br> */
	int				m_iCurPage;								/**< ���� ������ <br> */
	int				m_iSelect;								/**< ������ ����������̽� �� ������ �ε��� <br> ����, ������ ��� �����ټ� ���� <br> */
	int				m_iSelectIndex;							/**< ������ �����ͻ� ������ �ε��� <br> */

	char			m_szPage[12];							/**< ������ ���ڿ� <br> */
};

