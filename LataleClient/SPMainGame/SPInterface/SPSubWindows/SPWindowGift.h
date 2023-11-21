#pragma once

class SPWindow;
class SPWindowStatic;
class SPWindowEdit;
class SPWindowButton;
class SPWindowSlider;

#define WIID_GIFT_TOP						(WIID_GIFT	+	1)
#define WIID_GIFT_CENTER					(WIID_GIFT	+	2)
#define WIID_GIFT_BOTTOM					(WIID_GIFT	+	3)

#define WIID_GIFT_TITLE						(WIID_GIFT	+	5)
#define WIID_GIFT_CLOSE						(WIID_GIFT	+	6)

#define WIID_GIFT_LINE_L_TOP				(WIID_GIFT	+	10)
#define WIID_GIFT_LINE_L_BOTTOM				(WIID_GIFT	+	11)
#define WIID_GIFT_LINE_R_TOP				(WIID_GIFT	+	15)
#define WIID_GIFT_LINE_R_BOTTOM				(WIID_GIFT	+	16)

#define WIID_GIFT_L_SKIN					(WIID_GIFT	+	20)
#define WIID_GIFT_R_SKIN					(WIID_GIFT	+	25)

#define WIID_GIFT_REWORD_IMG				(WIID_GIFT	+	30)
#define WIID_GIFT_LIST_IMG					(WIID_GIFT	+	30)

#define WIID_GIFT_LIST_SEL					(WIID_GIFT	+	90)
#define WIID_GIFT_LIST_ICON_LINE			(WIID_GIFT	+	100)
#define WIID_GIFT_LIST_ICON					(WIID_GIFT	+	110)		//����Ʈ ������
#define WIID_GIFT_LIST_NAME					(WIID_GIFT	+	120)		//����Ʈ ��
#define WIID_GIFT_LIST_ITEM					(WIID_GIFT	+	130)		//����Ʈ ������ ǥ��
#define WIID_GIFT_LIST_ELY					(WIID_GIFT	+	140)		//����Ʈ �� ǥ��
#define WIID_GIFT_LIST_BTN					(WIID_GIFT	+	150)		//����Ʈ ��ư
#define WIID_GIFT_LIST_SKIN					(WIID_GIFT	+	160)		//

#define WIID_GIFT_PREV						(WIID_GIFT	+	170)		//����Ʈ ����
#define WIID_GIFT_PAGE						(WIID_GIFT	+	175)		//����Ʈ ������ ����
#define WIID_GIFT_NEXT						(WIID_GIFT	+	180)		//����Ʈ ����
#define WIID_GIFT_NAME						(WIID_GIFT	+	185)		//���� �̸�
#define WIID_GIFT_REFLASH 					(WIID_GIFT	+	190)		//����Ʈ ����
#define WIID_GIFT_RECEIVE					(WIID_GIFT	+	195)		//�ޱ�

#define WIID_GIFT_TEXT						(WIID_GIFT	+	200)		//���� ����
#define WIID_GIFT_ELY						(WIID_GIFT	+	210)		//���� ����
#define WIID_GIFT_ELY_TEXT_IMG				(WIID_GIFT	+	211)		//����ݾ� �̹���
#define WIID_GIFT_ELY_IMG					(WIID_GIFT	+	212)		//���� �̹���

enum ICON_MARK;

const int MAX_GIFT_ITEM_PAGE = 6;			/**< �������� ǥ�õǴ� Gift Item�� ���� <br> */

class SPWindowGift : public SPWindow 
{
public:
	SPWindowGift( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);
	virtual ~SPWindowGift();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

protected:
	void InitSubWindow();
	
	/**
	 * Gfit List ���� <br>
	 @param 
	 @return
	*/
	void UpdateList();

	virtual void Show(bool bWithChild = true);
	//void Refresh();

	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnUpdateGiftList	(WPARAM wParam, LPARAM lParam);			//�ܺο��� ����Ʈ ������ �䱸
	int OnListReflash		(WPARAM wParam, LPARAM lParam);			//���Ź�ư
	int OnItemReceive		(WPARAM wParam, LPARAM lParam);
	int OnClose				(WPARAM wParam, LPARAM lParam);
	int OnPrev				(WPARAM wParam, LPARAM lParam);
	int OnNext				(WPARAM wParam, LPARAM lParam);	
	int OnItemClick			( unsigned int uiID, WPARAM wParam, LPARAM lParam );
	int OnToolTipMove			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipEnter			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipOut			(unsigned int iUiID, WPARAM wParam, LPARAM lParam);	

private:
	SPTexture* m_pDisable;

	SPWindow*		m_pName;
	SPWindow*		m_pText;
	SPWindow*		m_pPage;
	SPWindow*		m_pEly;
	SPWindowButton* m_pPrev;
	SPWindowButton* m_pNext;
	SPWindowButton*	m_pReflash;
	SPWindowButton* m_pReceive;    
	
	SPWindow*			m_pListSelect[MAX_GIFT_ITEM_PAGE];
	SPWindow*			m_pListIcon[MAX_GIFT_ITEM_PAGE];
	SPWindow*			m_pListName[MAX_GIFT_ITEM_PAGE];
	SPWindowButton*		m_pListButton[MAX_GIFT_ITEM_PAGE];
	//SPWindow*			m_pListItem[MAX_GIFT_ITEM_PAGE];
	//SPWindow*			m_pListEly[MAX_GIFT_ITEM_PAGE];
	RECT				m_rtDestItem[MAX_GIFT_ITEM_PAGE];
	RECT				m_rtDestEly[MAX_GIFT_ITEM_PAGE];
	RECT				m_rtSrcItem;
	RECT				m_rtSrcEly;

	bool	m_bListRequest;				/**< ���÷��� ��û ��ư�� �������� <br> */
	float	m_fListDeley;				/**< ���÷��� ��û ��ư ��Ȱ�� �ð� <br> */
	float	m_fListAccumulate;			/**< ���÷��� ��û �ð� ���ſ� <br> */

	int		m_iMaxPage;					/**< Gift Item List�� ������ȭ �� ���� �� �������� <br> */
	int		m_iCurPage;					/**< ���� ������ ������ �� <br> */
	int		m_iStartIndex;				/**< ����Ʈ ǥ���� ���� ? <br> */
	int		m_iSelectItem;				/**< 4���� ����Ʈ�� ���õ� ������ <br> */

	bool		m_bAble[MAX_GIFT_ITEM_PAGE];		/**< ���� Item�� ��밡������ <br> */
	ICON_MARK	m_iItemMark[MAX_GIFT_ITEM_PAGE];	/**< ���� Item�� ��ũ <br> */
	int			m_iStackCount[MAX_GIFT_ITEM_PAGE];	/**< ���� Item�� ���� <br> */

	RECT m_rtSrcDisable;							/**< ��Ȱ�� ǥ���� �ҽ� <br> */
	RECT m_rtMarkSrc[4];							/**< ICON MARK Src <br> */
	RECT m_rtStack[MAX_GIFT_ITEM_PAGE];				/**< ����ǥ���� ���� ���� Icon ������ ���� <br> */
};