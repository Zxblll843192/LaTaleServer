#pragma once


#define WIID_EFFECTITEM_UPGRADE_TOP				(WIID_EFFECTITEM_UPGRADE	+	1)
#define WIID_EFFECTITEM_UPGRADE_CENTER				(WIID_EFFECTITEM_UPGRADE	+	2)
#define WIID_EFFECTITEM_UPGRADE_BOTTOM				(WIID_EFFECTITEM_UPGRADE	+	3)
#define WIID_EFFECTITEM_UPGRADE_TITLE				(WIID_EFFECTITEM_UPGRADE	+	5)
#define WIID_EFFECTITEM_UPGRADE_CLOSE				(WIID_EFFECTITEM_UPGRADE	+	6)

#define WIID_EFFECTITEM_UPGRADE_LINE1				(WIID_EFFECTITEM_UPGRADE	+	8)
#define WIID_EFFECTITEM_UPGRADE_LINE2				(WIID_EFFECTITEM_UPGRADE	+	9)

#define WIID_EFFECTITEM_UPGRADE_SKIN				(WIID_EFFECTITEM_UPGRADE	+	10)			//��� ����

#define WIID_EFFECTITEM_UPGRADE_SLOTLINE			(WIID_EFFECTITEM_UPGRADE	+	20)			//3���� ���� �ܰ���
#define WIID_EFFECTITEM_UPGRADE_SLOTICON			(WIID_EFFECTITEM_UPGRADE	+	30)			//3���� ���� ������
#define WIID_EFFECTITEM_UPGRADE_SLOTBUTTON			(WIID_EFFECTITEM_UPGRADE	+	40)			//3���� ���� ��ư

#define WIID_EFFECTITEM_UPGRADE_CURSOR1			(WIID_EFFECTITEM_UPGRADE	+	100)
#define WIID_EFFECTITEM_UPGRADE_CURSOR2			(WIID_EFFECTITEM_UPGRADE	+	110)
#define WIID_EFFECTITEM_UPGRADE_TOOLTIP			(WIID_EFFECTITEM_UPGRADE	+	120)

#define WIID_EFFECTITEM_UPGRADE_PLUS				(WIID_EFFECTITEM_UPGRADE	+	150)
#define WIID_EFFECTITEM_UPGRADE_EQUAL				(WIID_EFFECTITEM_UPGRADE	+	160)
#define WIID_EFFECTITEM_UPGRADE_QUESTION			(WIID_EFFECTITEM_UPGRADE	+	165)

#define WIID_EFFECTITEM_UPGRADE_OK					(WIID_EFFECTITEM_UPGRADE	+	170)
#define WIID_EFFECTITEM_UPGRADE_CANCEL				(WIID_EFFECTITEM_UPGRADE	+	180)



const int MAX_LEVELUP_SLOT					= 3;								//���԰���
class SPWindow;
class SPWindowButton;

enum LEVELUP_STATUS {
	LEVELUP_STATUS_FIRST			= 0,
	LEVELUP_STATUS_SECOND			= 1,
	LEVELUP_STATUS_READY			= 2,
	LEVELUP_STATUS_RESULT			= 3,
	LEVELUP_STATUS_END				= 4,
};

#include "SPPlayerInvenArchive.h"

struct EffectUpdateCfg
{
	int iUpgradeID;
	int iItemID;
	int iMaterialID;
	int iIcon_First_icon;
	int iIcon_First_index;
	int iIcon_Second_icon;
	int iIcon_Second_index;
	int iChance;
	string strInfo_First;
	string strInfo_Second;
	void reset(void)
	{
		iUpgradeID = -1;
		iItemID = -1;
		iMaterialID = -1;
		iIcon_First_icon = -1;
		iIcon_First_index = -1;
		iIcon_Second_icon = -1;
		iIcon_Second_index = -1;
		iChance = 0;
		strInfo_First.clear();
		strInfo_Second.clear();
	}
	EffectUpdateCfg( void )
	{
		reset();
	}
};

class SPWindowEffectItemUpgrade : public SPWindow
{

public:
	SPWindowEffectItemUpgrade(WND_ID WndClassID, INSTANCE_ID InstanceID);
	SPWindowEffectItemUpgrade(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowEffectItemUpgrade();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);


protected:
	void ProcessCursor(float fTime);
	void CreateSubWindow();	
	void SetStatus(LEVELUP_STATUS iStatus);
	void ClearAllSlotInterface();
	void ClearSlotInterface(int iIndex);
	void SetSlotInterface(int iIndex, SPItem* pItem);

	bool SetFirstItem();
	bool SetSecondItem();

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
	int OnUpgradeAck			(WPARAM wParam, LPARAM lParam);

protected:
	bool initLDT( void );
	bool isItemUpgradable( int iItemID, EffectUpdateCfg &cfg );
	bool isItemSuitableMaterial( int iItemID, int iMaterialID, EffectUpdateCfg &cfg );
	bool doUpgrade(void);

	vector< EffectUpdateCfg > m_vecEffectCfg;
private:	
	SPTexture* m_pQuestion;
	SPTexture* m_pDisable;		
	RECT	m_rtSrcDisable;												/**< ��Ȱ�� ǥ���� �ҽ� <br> */

	int		m_iCursorDirection;
	float	m_fCursorAccmulateTime;
	int		m_iFrame;

	SPWindow* m_pIcon[MAX_LEVELUP_SLOT];
	SPWindow* m_pCursorFirst;
	SPWindow* m_pCursorSecond;
	SPWindow* m_pToolTip;
	SPWindowButton* m_pOK;
	SPWindowButton* m_pCancel;

	SPItem*	m_pItem[MAX_LEVELUP_SLOT];									/**< ������ ������ ������� �ʴ´� !!! <br> */
	SPItem* m_pItemResult;												/**< ������ ������ ������ ǥ���� <br> */
	SPSelectItem m_SelectItem[MAX_LEVELUP_SLOT];

	RECT	m_rtMarkSrc[4];												/**< ICON MARK Src <br> */	

	RECT	m_rtStack[MAX_LEVELUP_SLOT];								//List Item Stack Count

	bool	m_bItemAble[MAX_LEVELUP_SLOT];								/**< ���� �÷��� �������� ���� ���밡���� ���������� <br> */
	int		m_iStack[MAX_LEVELUP_SLOT];									/**< ���� Item�� ���� <br> */
	ICON_MARK	m_iItemMark[MAX_LEVELUP_SLOT];							/**< ICON MARK <br> */

	LEVELUP_STATUS	m_iLevelUpStatus;

	bool	m_bUse;

	//--------------------------------------------------
	// added by jmulro, for wat wat wat
	EffectUpdateCfg m_curSelect;
	//--------------------------------------------------
};



