#pragma once


#define WIID_NPC_PORTAL_TITLE						(WIID_NPC_PORTAL + 1)
#define WIID_NPC_PORTAL_EXIT						(WIID_NPC_PORTAL + 5)
#define WIID_NPC_PORTAL_LINE						(WIID_NPC_PORTAL + 7)

#define WIID_NPC_PORTAL_BASE						(WIID_NPC_PORTAL + 9)

#define WIID_NPC_PORTAL_LIST_SKIN					(WIID_NPC_PORTAL + 10)
#define WIID_NPC_PORTAL_LIST_BUTTON					(WIID_NPC_PORTAL + 20)
#define WIID_NPC_PORTAL_LIST_ICON					(WIID_NPC_PORTAL + 30)
#define WIID_NPC_PORTAL_LIST_NAME					(WIID_NPC_PORTAL + 40)
#define WIID_NPC_PORTAL_LIST_ELY					(WIID_NPC_PORTAL + 50)
#define WIID_NPC_PORTAL_LIST_ELY_IMAGE				(WIID_NPC_PORTAL + 60)
#define WIID_NPC_PORTAL_LIST_ITEM_SKIN				(WIID_NPC_PORTAL + 70)
#define WIID_NPC_PORTAL_LIST_ITEM					(WIID_NPC_PORTAL + 80)
#define WIID_NPC_PORTAL_LIST_SELECT					(WIID_NPC_PORTAL + 90)

#define WIID_NPC_PORTAL_SLIDER						(WIID_NPC_PORTAL + 100)
#define WIID_NPC_PORTAL_UP							(WIID_NPC_PORTAL + 101)
#define WIID_NPC_PORTAL_DOWN						(WIID_NPC_PORTAL + 102)
#define WIID_NPC_PORTAL_MOVE						(WIID_NPC_PORTAL + 110)



const int PORTAL_PAGE			= 8;				/**< ��ȭ�鿡 ���̴� ����Ʈ�� ���� <br> */

class SPWindow;
class SPWindowButton;
class SPWindowSlider;

//#include "SPQuestAttr.h"
#include "SPEventDEF.h"
//#include "SPEvent"
//struct SPRequire;
//struct SPNpcPortalInfo;


class SPWindowNpcPortal : public SPWindow {

public:
	SPWindowNpcPortal( INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowNpcPortal();

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
	 * ����Ʈ �ʱ�ȭ <br> 
	 @param 
	 @return  
	*/
	void ResetControl();
	
	/**
	 * �־��� �ε����� ����Ʈ�� �ʱ�ȭ <br> 
	 @param 
	 @return  
	*/
	void ClearControl(int iIndex);
	
	/**
	 * ȭ����� ����Ʈ�� ������Ʈ <br> 
	 @param 
	 @return  
	*/
	void UpdateControl();
	
	/**
	 * �־��� ��Ʈ�ѿ� ��Ż ������ �������� ���� <br> 
	 @param 
	 @return  
	*/
	void SetDestIcon(SPNpcPortalInfo* pInfo, SPWindow* pWindow);	

protected:
	// {{ ShopTalk Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnExit				(WPARAM wParam, LPARAM lParam);						/**< ���� ��ư <br> */
	int OnListUp			(WPARAM wParam, LPARAM lParam);						/**< ����Ʈ �� ��ư <br> */
	int OnListDown			(WPARAM wParam, LPARAM lParam);						/**< ����Ʈ �ٿ� ��ư <br> */
	int OnSliderPageUp		(WPARAM wParam, LPARAM lParam);
	int OnSliderPageDown	(WPARAM wParam, LPARAM lParam);
	int OnSliderPageNum		(WPARAM wParam, LPARAM lParam);
	int OnPageUp			(unsigned int uiID, WPARAM wParam, LPARAM lParam);
	int OnPageDown			(unsigned int uiID, WPARAM wParam, LPARAM lParam);
	int OnPortalClick		(unsigned int uiID, WPARAM wParam, LPARAM lParam);
	int OnMove				(WPARAM wParam, LPARAM lParam);						/**< �̵� ��ư <br> */
	//}}


private:
	SPTexture*		m_pTextureBase;					/**< ������ ������ ���ҽ� <br> */
	RECT			m_rtSrcBase[WINDOW_BASE_MAX];	/**< ������ ���� �ҽ� ���� <br> */
	RECT			m_rtDestBase[WINDOW_BASE_MAX];	/**< ������ ���� ��� <br> */	
	
	SPWindow*		m_pSelect[PORTAL_PAGE];			/**< ����Ʈ ����ǥ���� <br> */
	SPWindow*		m_pButton[PORTAL_PAGE];			/**< ����Ʈ �̺�Ʈ ó���� <br> */
	SPWindow*		m_pDestIcon[PORTAL_PAGE];		/**< ������ ������ <br> */
	SPWindow*		m_pName[PORTAL_PAGE];			/**< ������ �̸� <br> */
	SPWindow*		m_pEly[PORTAL_PAGE];			/**< �̵� ��� <br> */
	SPWindow*		m_pElyImage[PORTAL_PAGE];		/**< �̵� ���� ���� ������ �̹��� <br> */
	SPWindow*		m_pItemIcon[PORTAL_PAGE];		/**< ������ ������ <br> */
	SPWindow*		m_pItemSkin[PORTAL_PAGE];		/**< ������ ������ ��Ų <br> */
	SPWindowSlider* m_pSlider;

	int				m_iMaxPage;						/**< �ִ� ������ <br> */
	int				m_iCurPage;						/**< ���� ������ <br> */
	int				m_iSelect;						/**< ����Ʈ �� ���� ������ġ <br> */
	int				m_iSelectIndex;					/**< ������ ���� �� ��ġ <br> */
	
	SPTexture*		m_pDisable;						/**< Disable ǥ���� Texture <br> */	
	RECT			m_rtMarkSrc[4];					/**< Icon Mark Src <br> */
	ICON_MARK		m_iMark[PORTAL_PAGE];			/**< Icon Mark <br> */
};