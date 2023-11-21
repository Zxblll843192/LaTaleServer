#pragma once

#define WIID_NPCTRADE_TOP			(WIID_NPCTRADE	+	1)		//
#define WIID_NPCTRADE_CENTER		(WIID_NPCTRADE	+	2)		//
#define WIID_NPCTRADE_BOTTOM		(WIID_NPCTRADE	+	3)		//

#define WIID_NPCTRADE_TITLE			(WIID_NPCTRADE	+	5)		//Ÿ��Ʋ
#define WIID_NPCTRADE_EXIT			(WIID_NPCTRADE	+	6)		//������

#define WIID_NPCTRADE_MIDDLE		(WIID_NPCTRADE	+	10)		//��� ��Ų

//#define WIID_NPCTRADE_COUNT			(WIID_NPCTRADE	+	10)	//Item ���� ����
//#define WIID_NPCTRADE_COUNTER		(WIID_NPCTRADE	+	15)		//Itme ���� ǥ��
//#define WIID_NPCTRADE_DOWNCOUNT		(WIID_NPCTRADE	+	20)	//Item ���� ����

#define WIID_NPCTRADE_LIST_IMG_BASE (WIID_NPCTRADE	+	11)		//����Ʈ �ܰ� �̹���
#define WIID_NPCTRADE_LIST_IMG		(WIID_NPCTRADE	+	12)		//����Ʈ �̹���

#define WIID_NPCTRADE_PRICE_IMG_BASE	(WIID_NPCTRADE	+	15)	//���� �ܰ� �̹���
#define WIID_NPCTRADE_PRICE_IMG		(WIID_NPCTRADE	+	16)		//���� �̹���

#define WIID_NPCTRADE_BUY			(WIID_NPCTRADE	+	25)		//Item ���� ��ư

#define WIID_NPCTRADE_ITEM_SKIN		(WIID_NPCTRADE	+	30)		//6���� ������ ����Ʈ �� ���� �� ���� ������ �ٴ�
#define WIID_NPCTRADE_ITEM_SEL		(WIID_NPCTRADE	+	50)		//6���� ������ ����Ʈ ���ý� ����Ʈ 
#define WIID_NPCTRADE_ITEM_GRID		(WIID_NPCTRADE	+	70)		//6���� ������ ������ �ٴ� �̹��� 
#define WIID_NPCTRADE_ITEM_ICON		(WIID_NPCTRADE	+	90)		//6���� ������ ������ ��ư
#define WIID_NPCTRADE_ITEM_NAME		(WIID_NPCTRADE	+	110)	//6���� ������ �̸� ǥ��
#define WIID_NPCTRADE_ITEM_CASH		(WIID_NPCTRADE	+	130)	//6���� ������ ���� ǥ��
#define WIID_NPCTRADE_ITEM_ELY_IMG	(WIID_NPCTRADE	+	150)	//6���� ������ ���� �̹���
#define WIID_NPCTRADE_ITEM_BUTTON	(WIID_NPCTRADE	+	170)	//6���� ������ ���� ��ư

#define WIID_NPCTRADE_PAGEUP		(WIID_NPCTRADE	+	200)		//������ ����
#define WIID_NPCTRADE_PAGE			(WIID_NPCTRADE	+	210)		//������
#define WIID_NPCTRADE_PAGEDOWN		(WIID_NPCTRADE	+	220)		//������ ����

#define WIID_USER_ELY_TEXT_IMG		(WIID_NPCTRADE	+	230)		//������ ����
#define WIID_USER_ELY				(WIID_NPCTRADE	+	235)		//������ ����
#define WIID_USER_ELY_IMG			(WIID_NPCTRADE	+	236)		//������ ����


const int	TRADE_PAGE = 10;					/**< ���������� �������� �������� ���� ������ <br> */
const int	MAX_BUY_COUNT = 99;				/**< �ѹ��� ���� ������ �ִ� �������� ���� <br> */

class SPWindow;
class SPWindowEdit;
struct SPNpcShop;

#include "SPPlayerInvenArchive.h"


/**
* @class SPWindowShopTalk
* @brief NPC ���� ����Ʈ�� ��� ��� �޽���â
* @author Jinhee
* @version 00.00.01
* @date 2005.5.16
* @bug ����
* @warning 
*/
class SPWindowNpcTrade : public SPWindow {

public:	
	SPWindowNpcTrade(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowNpcTrade();

	virtual void Init();
	virtual void Clean();
	//virtual void SetFocus();
	virtual void Process(float fTime);
	virtual void Render(float fTime);
	virtual void RenderText();

	virtual void Show(bool bWithChild = true);	
	//virtual bool IsShow();
	//virtual void Hide();  // ������� ������ �� ����..

public:

protected:
	/**
	 * ���� ��Ʈ���� ����� <br> 
	 @param NONE
	 @return NONE
	*/
	void CreateSubControl();
	
	/**
	 * ������ ����Ʈ ��Ʈ�ѵ��� �ʱ�ȭ �Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void ResetItemListControl();
	
	/**
	 * ������ ����Ʈ�� ������Ʈ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void UpdateItemList();	

	/**
	 * ���� PC�� �������ͽ��� üũ�Ͽ� NPC�����۸���Ʈ�� �������� <br>
	 * ���� ����Ҽ� �ִ����� �����Ѵ� <br>
	 @param int iItemID
	 @return 
	*/
	bool CheckItemStatus(int iItemID);

	/**
	 * ������ ���� ī���͸� ������Ʈ �Ѵ� <br> 
	 * //[2006/6/23] ��� ����
	 @param NONE
	 @return NONE
	*/
	//void UpdateBuyCount();	
	
	/**
	* ItemButton control List �� select ���¸� ��� �����Ѵ� <br>
	@param NONE
	@return NONE
	*/
	void ResetItemButton();

	/**
	 * �Ǹ��� �Ǵ� �Ǹ� ���� ������ ���õ� ������ ������ �ʱ�ȭ �Ѵ� <br>
	 @param
	 @return
	*/
	void ResetSelectItem();

	/**
	 * ���� �Ǹſ����� Ȯ���Ѵ� <br>
	 @param NONE
	 @return bool �Ǹ� ��Ŷ�� ������� true
	*/
	bool IsQuickItemSell();

protected:
	// {{ ShopTalk Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()

	int OnUpdateShopData		( WPARAM wParam, LPARAM lParam );	//shop Data �� ������Ʈ
	int OnClose					( WPARAM wParam, LPARAM lParam );	//
	int OnPageUp				( WPARAM wParam, LPARAM lParam );	//Page Up
	int OnPageDown				( WPARAM wParam, LPARAM lParam );	//Page Down
	int OnCount					( WPARAM wParam, LPARAM lParam );	//Buy Count ����
	int OnCountDown				( WPARAM wParam, LPARAM lParam );	//Buy Count ����
	int OnUpdateCount			(WPARAM wParam, LPARAM lParam);		/**< Count ���� �Է½� <br> */
	int OnInputFocus			(WPARAM wParam, LPARAM lParam);		/**< ����Ʈ ��Ʈ���� ��Ŀ���� �޴� ��� <br> */
	int OnBuyItem				( WPARAM wParam, LPARAM lParam );	//���� ��ư
	
	int OnLBuyItemClick			( unsigned int uiID, WPARAM wParam, LPARAM lParam );	//������ ������ Ŭ�� (��Ʈ�� Ŭ��)
	int OnRBuyItemClick     	( unsigned int uiID, WPARAM wParam, LPARAM lParam );	//������ ������ Ŭ�� (��Ʈ�� Ŭ��)

	int OnToolTipMove			(unsigned int, WPARAM, LPARAM);
	int OnToolTipEnter			(unsigned int, WPARAM, LPARAM);
	int OnToolTipOut			(unsigned int, WPARAM, LPARAM);
	int OnLButtonUp				(WPARAM wParam, LPARAM lParam);

	//virtual int OnShopTalkClose		( WPARAM wParam, LPARAM lParam );
	//virtual int OnShopTalkShow		( WPARAM wParam, LPARAM lParam );
	//virtual int OnShopTalkTextSet	( WPARAM wParam, LPARAM lParam );


protected:	
	SPTexture* m_pDisable;						/**< Disable ǥ���� Texture <br> */	
	SPWindow* m_pBuy;							/**< button Window Buy <br> */ 
	
	SPWindowStatic* m_pSkin[TRADE_PAGE];
	SPWindow* m_pIcon[TRADE_PAGE];				/**< Static Window Item Icon <br> */	
	SPWindow* m_pName[TRADE_PAGE];				/**< Static Window Item Name <br> */
	SPWindow* m_pCash[TRADE_PAGE];				/**< Static window Item Cash <br> */
	SPWindow* m_pButton[TRADE_PAGE];			/**< button window Item Button <br> */

	RECT m_rtStack[TRADE_PAGE];
	int	m_iStack[TRADE_PAGE];					/**< Static ǥ�� <br> */
	
	SPWindow* m_pPageUp;						/**< Static Window Page up <br> */
	SPWindow* m_pPageInfo;						/**< Static window Page <br> */
	SPWindow* m_pPageDown;						/**< Static Window Page Down <br> */

	SPWindow* m_pUserEly;						/**< ���� ���� Ely <br> */

	bool	m_bSend;							/**< Message Send <br> */

	SPNpcShop* m_pNpcShop;						/**< Static window Item Cash <br> */
	int	m_iMaxPage;								/**< MAX Page <br> */
	int m_iPage;								/**< current Page <br> */

	char m_szPage[64];							/**< page Info <br> */

	int m_iBuyCount;							/**< Buy Item Counter <br> */
	char m_szBuyCount[64];						/**< Buy Count Info <br> */
	
	int m_iSelectItemIndex;						/**< ���� �Ǹ��ϱ� ���� ������ Item List���� Index <br> */
	int m_iViewItemIndex;						/**< ��Ʈ�ѿ� �����ֱ� ���� ������ ��Ʈ�� List���� Index <br> */

	bool m_bAble[TRADE_PAGE];					/**< false�϶� ��Ȱ��ȭ ǥ�� <br> */
	RECT m_rtSrcDisable;						/**< Diable Textrue Src <br> */

	SPSelectItem m_PickUpItem;					/**< �κ��丮���� �Ⱦ��� ������ ��ũ <br> */

	RECT m_rtMarkSrc[4];						/**< Icon Mark Src <br> */
	ICON_MARK m_iMark[TRADE_PAGE];				/**< Icon Mark <br> */

protected:


};
