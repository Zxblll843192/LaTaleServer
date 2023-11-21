#pragma once

class SPWindow;
class SPWindowStatic;
class SPWindowEdit;
class SPWindowEditMultiLine;
class SPWindowButton;

#define WIID_MAILLIST_SEND			(WIID_MAILLIST	+	1)		//���� ���� ��ư
#define WIID_MAILLIST_VIEW			(WIID_MAILLIST	+	2)		//���� ���� Ȯ��
#define WIID_MAILLIST_CLOSE			(WIID_MAILLIST	+	3)		//�ݱ�

#define WIID_MAILLIST_PAGEBASE		(WIID_MAILLIST	+	11)		//������ ���̽�
#define WIID_MAILLIST_TOP			(WIID_MAILLIST	+	15)
#define WIID_MAILLIST_CENTER		(WIID_MAILLIST	+	20)
//#define WIID_MAILLIST_BOTTOM		(WIID_MAILLIST	+	25)

#define WIID_MAILLIST_TITLE			(WIID_MAILLIST	+	21)		//Title
#define WIID_MAILLIST_MENU_BASE 	(WIID_MAILLIST	+	25)		//�޴�����

#define WIID_MAILLIST_UPLINE		(WIID_MAILLIST	+	26)		//��� ��輱
 

#define WIID_MAILLIST_PREV			(WIID_MAILLIST	+	30)		//������ ����
#define WIID_MAILLIST_PAGE			(WIID_MAILLIST	+	35)		//������
#define WIID_MAILLIST_NEXT			(WIID_MAILLIST	+	40)		//������ ����

#define WIID_MAILLIST_LISTVIEW		(WIID_MAILLIST	+	45)		//List
#define WIID_MAILLIST_LIST_SKIN		(WIID_MAILLIST	+	46)		//List Skin
#define WIID_MAILLIST_ITEM_SKIN		(WIID_MAILLIST	+	50)		//4���� ���� ����Ʈ �� ���� �� ���� ������ �ٴ�
#define WIID_MAILLIST_ITEM_SEL		(WIID_MAILLIST	+	60)		//4���� ������ ������ ��ư
#define WIID_MAILLIST_ITEM_ICON		(WIID_MAILLIST	+	70)		//4���� ������ ������ ��ư
#define WIID_MAILLIST_ITEM_SENDER	(WIID_MAILLIST	+	80)		//4���� ������ ������
#define WIID_MAILLIST_ITEM_NAME		(WIID_MAILLIST	+	90)		//4���� ������ ����
#define WIID_MAILLIST_ITEM_DATE		(WIID_MAILLIST	+	100)		//4���� ������ ���� ����
#define WIID_MAILLIST_ITEM_BUTTON	(WIID_MAILLIST	+	110)	//4���� ������ ���� ��ư
#define WIID_MAILLIST_ITEM_READ		(WIID_MAILLIST	+	120)	//4���� ������ ���� �����ΰ�?
#define WIID_MAILLIST_ITEM_ICON_LINE (WIID_MAILLIST	+	130)	//������ ������ �ܰ���
#define WIID_MAILLIST_ITEM_BOTTOM	(WIID_MAILLIST	+	150)	//List Bottom

#define WIID_MAILLIST_SENDVIEW		(WIID_MAILLIST	+	160)	//Send
#define WIID_MAILLIST_SEND_SKIN      (WIID_MAILLIST	+	161)	//Send Skin
#define WIID_MAILLIST_SEND_TITLEBASE (WIID_MAILLIST	+	165)	//���� Base
#define WIID_MAILLIST_SEND_TITLE	(WIID_MAILLIST	+	170)	//����
//#define WIID_MAILLIST_SEND_RECEIVERPLATE (WIID_MAILLIST	+	124)//������� -> �������
#define WIID_MAILLIST_SEND_RECEIVERBASE	(WIID_MAILLIST	+	185)//�޴»�� Base
#define WIID_MAILLIST_SEND_RECEIVER	(WIID_MAILLIST	+	190)	//�޴»��
#define WIID_MAILLIST_SEND_MSG		(WIID_MAILLIST	+	200)	//����
#define WIID_MAILLIST_SEND_MSG_BASE	(WIID_MAILLIST	+	201)	//����

#define WIID_MAILLIST_SEND_APPEND_1 (WIID_MAILLIST	+	205)	//÷�� �̹��� 1
#define WIID_MAILLIST_SEND_APPEND_2 (WIID_MAILLIST	+	206)	//���� �̹��� 2

#define WIID_MAILLIST_SEND_ITEM		(WIID_MAILLIST	+	210)	//Item Button
#define WIID_MAILLIST_SEND_ITEMICON (WIID_MAILLIST	+	220)	//Item Icon
#define WIID_MAILLIST_SEND_ITEMICON_LINE  (WIID_MAILLIST	+	221)	//Item Icon Line
#define WIID_MAILLIST_SEND_ITEMNAME (WIID_MAILLIST	+	230)	//Item Name

#define WIID_MAILLIST_SEND_ELYBASE	(WIID_MAILLIST	+	240)	//�ݾ� �̹��� 
#define WIID_MAILLIST_SEND_ELY		(WIID_MAILLIST	+	250)	//Ely
#define WIID_MAILLIST_SEND_ELY_IMG	(WIID_MAILLIST	+	251)	//Ely Image

#define WIID_MAILLIST_SEND_MAIL		(WIID_MAILLIST	+	290)	//Send Button
#define WIID_MAILLIST_SEND_CANCEL	(WIID_MAILLIST	+	291)	//Send Button

#define WIID_MAILLIST_SEND_BOTTOM	(WIID_MAILLIST	+	295)	//Send Bottom


const int MAX_MAIL_LIST				= 4;			/**< �� ����Ʈ�� ������ �ִ� ���� ���� <br> */
//const int MAX_MAIL_PAGE				= 3;			/**< 3 ������ ���� <br> */
const int MAX_MAIL_PAGE				= 10;			/**< 10 ������ ���� <br> */
//const int MAIL_FEE					= 50;			/**< ���� ������ <br> */
const int TITLE_LENGTH				= 24;			/**< ����Ʈ ���� �̸��� �ʹ� ���� �ڸ��� ���� <br> */

enum MAILLIST_MODE {	
	MAILLIST_MODE_VIEW				= 0,
	MAILLIST_MODE_SEND				= 1,
};

enum ICON_MARK;

class SPWindowMailList : public SPWindow 
{
public:
	SPWindowMailList( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);
	virtual ~SPWindowMailList();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

protected:
	void InitSubWindow();
	void SetModeButton();
	
	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);

	/**
	 * Send ����� �������̽� �ʱ�ȭ <br> 
	 @param 
	 @return
	*/
	void ClearSend();

	/**
	 * MailList �������̽� ������Ʈ <br> 
	 @param 
	 @return
	*/
	void UpdateList();

	void ResetItemControl(bool bRestore = true);
	void RestoreInven();
	

	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnUpdateMailList	(WPARAM wParam, LPARAM lParam);			//�ܺο��� ����Ʈ ������ �䱸
	int OnClearSend			(WPARAM wParam, LPARAM lParam);			//Send�� Send �������̽� Ŭ����
	int	OnResetSendItem		(WPARAM wParam, LPARAM lParam);			//�κ��丮���� ���Ϸ� ������ �������� ��� �ϴ� ���
	int OnReadCheck			(WPARAM wParam, LPARAM lParam);			//�������� ���� ��� ���� üũ ����
	int OnTab				(WPARAM wParam, LPARAM lParam);
	int OnMailView			(WPARAM wParam, LPARAM lParam);
	int OnMailSend			(WPARAM wParam, LPARAM lParam);
	int OnPrev				(WPARAM wParam, LPARAM lParam);
	int OnNext				(WPARAM wParam, LPARAM lParam);
	int OnSend				(WPARAM wParam, LPARAM lParam);
	int OnItemClick			(unsigned int uiID, WPARAM wParam, LPARAM lParam );
	int OnToolTipMove		(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipEnter		(unsigned int iUiID, WPARAM wParam, LPARAM lParam);
	int OnToolTipOut		(unsigned int iUiID, WPARAM wParam, LPARAM lParam);	
	
	int OnUpdateEly			(WPARAM wParam, LPARAM lParam);
	int	OnButtonUpItem		(WPARAM wParam, LPARAM lParam);
	int OnSendItemToolTipMove	(WPARAM wParam, LPARAM lParam);
	int OnSendItemToolTipEnter	(WPARAM wParam, LPARAM lParam);
	int OnSendItemToolTipOut	(WPARAM wParam, LPARAM lParam);
	int OnLButtonUp			(WPARAM wParam, LPARAM lParam);
	int OnClose				(WPARAM wParam, LPARAM lParam);

private:
	MAILLIST_MODE	m_iMailListMode;
	int		m_iMaxPage;					/**< Mail List�� ������ȭ �� ���� �� �������� <br> */
	int		m_iCurPage;					/**< ���� ������ ������ �� <br> */
	int		m_iStartIndex;				/**< ����Ʈ ǥ���� ���� ? <br> */
	int		m_iSelectItem;				/**< 4���� ����Ʈ�� ���õ� ������ <br> */
	
	SPTexture* m_pDisable;
	SPTexture* m_pCheck;

	RECT			m_rtSrcCenter;
	RECT			m_rtDestCenter;

	SPWindowButton* m_pSend;
	SPWindowButton* m_pView;
	
	SPWindow*		m_pPageBase;
	SPWindowButton* m_pPrev;
	SPWindowButton* m_pNext;
	SPWindow*		m_pPage;	

	SPWindow*			m_pListView;
	SPWindow*			m_pListSelect[MAX_MAIL_LIST];			//���� ��Ų
	SPWindow*			m_pListIcon[MAX_MAIL_LIST];				//Icon
	SPWindow*			m_pListSender[MAX_MAIL_LIST];			//�߼���
	SPWindow*			m_pListName[MAX_MAIL_LIST];				//��������
	SPWindowButton*		m_pListButton[MAX_MAIL_LIST];			//��ư
	SPWindow*			m_pListDate[MAX_MAIL_LIST];				//����
	SPWindow*			m_pListCheck[MAX_MAIL_LIST];			//Read Check
	//SPWindow*			m_pListNCheck[MAX_MAIL_LIST];			//Not Read Check

	SPWindow*			m_pSendView;
	SPWindowEdit*		m_pTitle;								//����
	SPWindowEdit*		m_pReceiver;							//�޴»��
	SPWindowEditMultiLine*	m_pMsg;								//����
	
	SPWindowButton*		m_pItemButton;							//Item
	SPWindow*			m_pItemIcon;
	SPWindow*			m_pItemName;	
	
	SPWindowEdit*		m_pEly;									//Ely

	SPWindowButton*		m_pMailSend;							//Send Button
	
	RECT m_rtMarkSrc[4];										/**< ICON MARK Src <br> */

	RECT m_rtStack[MAX_MAIL_LIST];								//List Item Stack Count
	int	m_iStackCount[MAX_MAIL_LIST];							/**< ���� Item�� ���� <br> */
	
	RECT m_rtSrcCheck;											/**< Check ǥ�� �ҽ� <br> */
	RECT m_rtSrcNCheck;
	ICON_MARK	m_iStackMark[MAX_MAIL_LIST];					/**< ���� Item�� ��ũ <br> */
	bool m_bRead[MAX_MAIL_LIST];								/**< ���� ������ ���������� ǥ�� <br> */
	
	RECT m_rtItemStack;											//Send Item Stack Count
	int m_iItemCount;											//Send Item Stack Count
	ICON_MARK m_iItemMark;										//Send Item Mark

	SPSelectItem m_PickUpItem;
	SPItemStatus* m_pItemStatus;				/**< Sell ItemStatus <br> */
	CONTAINER_TYPE m_iStorage;					/**< Current STORAGE_PLAYER <br> */
};