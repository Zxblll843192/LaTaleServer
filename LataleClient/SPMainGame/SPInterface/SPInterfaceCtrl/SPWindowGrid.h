
#pragma once

#include "SPItemAttr.h"
#include "SPItemCluster.h"
#include "SPCoolTimeManager.h"
/**
 *
*/
enum STATUS_UI_UNIT {
	STATUS_UI_UNIT_NONE			=	0x0000	,
	STATUS_UI_UNIT_RENDER		=	0x0100	,
	STATUS_UI_UNIT_DRAGNDROP	=	0x0200	,
	STATUS_UI_UNIT_COOLTIME		=	0x0400	,
	STATUS_UI_UNIT_NO_DRAGNDROP	=	0x0800	,
	STATUS_UI_UNIT_NO_TOOLTIP	=	0x1000	,
	STATUS_UI_UNIT_MASK			=	0xFF00	,
	STATUS_UI_UNIT_ENABLE		=	0x0001	,
	STATUS_UI_UNIT_DISABLE		=	0x0002	,
};


/**
 *
*/
enum CELL_SHOW {
	CELL_SHOW_NULL		= 0,		/**< CELL ���� �����ٰ� ���� <br> */
	CELL_SHOW_HIDE		= 1,		/**< CELL ���� ������ �������� ���� <br> */
	CELL_SHOW_DISABLE	= 2,		/**< CELL ���� ������ ��Ȱ�� <br> */
	CELL_SHOW_ENABLE	= 3,		/**< CELL �� �����鼭 Ȱ�� <br> */
	CELL_SHOW_MAX		= 4,		/**< �ƽ� <br> */
};



//////////////////////////////////////////////////////////////////////////

typedef struct tagGRIDCELL
{
	int			m_iUID;							/**< Item ID <br> */
	SPTexture*	m_pImage;
	POINT		m_ptSrcPos;
	//UINT8		m_iCellCnt;						/**< Stack Count <br> */
	UINT8		m_iStackCount;					/**< Stack Count <br> */
	CELL_SHOW	m_CellShow;						/**< Cell�� Show ���¸� ���� <br> */
	bool		m_bEnable;
	DWORD		m_dwStatus;						//	���� Unit�� ����
	ICON_MARK	m_iMark;						/**< ICON Mark <br> */
	COOLTIME_INFO* m_pCoolTime;					/**< CoolTime Info <br> */

	
	tagGRIDCELL()
	{
		CellClear();
		
		//m_iUID = m_ptSrcPos.x = m_ptSrcPos.y = 0;
		//m_iStackCount = 1;
		//m_pImage = NULL;
		//m_CellShow = CELL_SHOW_NULL;			/**< Show Status <br> */
	};

	void SetCellData(SPTexture* pImage, int iItemUID, int iXSrc, int iYSrc, UINT8 iStackCount, bool bEnable, bool fCoolTime = 0.0f) {
		m_iUID = iItemUID;
		m_pImage = pImage;
		m_ptSrcPos.x = iXSrc;
		m_ptSrcPos.y = iYSrc;
		m_iStackCount = iStackCount;
		m_CellShow = CELL_SHOW_ENABLE;		//[2005/5/21]
		m_bEnable = bEnable;		
		m_iMark = g_pItemCluster->GetItemIconMark(iItemUID);
		m_pCoolTime = NULL;
	}

	void CellClear() {
		m_iUID = 0;
		m_pImage = NULL;
		m_ptSrcPos.x = 0;
		m_ptSrcPos.y = 0;
		m_iStackCount = 0;
		m_CellShow = CELL_SHOW_ENABLE;
		m_bEnable = true;
		m_dwStatus = STATUS_UI_UNIT_NONE;
		m_iMark = ICON_MARK_NULL;
		m_pCoolTime = NULL;
	}

	void AddStatus( DWORD dwStatus )
	{
		if( ( dwStatus & STATUS_UI_UNIT_MASK ) == STATUS_UI_UNIT_NONE )
		{
			m_dwStatus	=	m_dwStatus & STATUS_UI_UNIT_MASK | dwStatus;
		}
		else
		{
			m_dwStatus	|=	dwStatus;
		}
	}

	void DelStatus( DWORD dwStatus )
	{
		if( GetStatus( dwStatus ) == TRUE )
			m_dwStatus	^=	dwStatus;
	}

	BOOL GetStatus( DWORD dwStatus )
	{
		return ( ( m_dwStatus & dwStatus ) == dwStatus );
	}

}GRIDCELL;

//////////////////////////////////////////////////////////////////////////

class SPWindow;
class SPItemCluster;

class SPWindowGrid : public SPWindow {
public:

	SPWindowGrid(WND_ID WndClassID, INSTANCE_ID InstanceID);
	SPWindowGrid(WND_ID WndClassID, INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent, int iXNum, int iYNum, int iXGap=0, int iYGap=0,int iCellSize=0);
	~SPWindowGrid();

	virtual void Init();
	virtual void Clean();	
	virtual void Show();
	virtual void Process(float fTime);	
	virtual void Render(float fTime);

	virtual	void CoolTimeProcess(float fTime);

	void	init(int iXNum, int iYNum, int iXGap=0, int iYGap=0, int iCellSize=0);

	bool	SetGridImage(const char* szImage, int iXSrc=0, int iYSrc=0, int iSizeX = 32, int iSizeY = 32);
	void	SetGridImageOffset(int iOffsetX, int iOffsetY);

	bool	SettingIconImage( SPTexture* pImage, int iItemUID, int iXSrc, int iYSrc, int iXPos, int iYPos, UINT8 iStackCount, bool bEnable = true);
	bool	SettingIconImage( SPTexture* pImage, int iItemUID, int iXSrc, int iYSrc, SLOT_INDEX iIndex, UINT8 iStackCount, bool bEnable = true);
	bool	ClearCell( int iIndex );	
	bool	ClearCellAll();	
	
	/**
	 * ������ Pick Up�� ������ ���� <br> 
	 @param 
	 @return
	*/
	bool	CellSelectSell( int iIndex, bool bSelect = true);			//[2005/5/20]
	
	/**
	 * ������ ���� ���� <br>
	 @param 
	 @return
	*/
	bool	SetItemStack(int iIndex, UINT8 iStackCount);						//[2005/5/23]

	/**
	 * ������ Ȱ�� / ��Ȱ�� ���� <br>
	 @param 
	 @return
	*/
	bool	CellEnable(int iIndex, bool bAble = true);

	/**
	 * <br>
	 @param
	 @return
	*/
	void	SetShowLine(int iLine = 0);


protected:

	SPIMESSAGE_OBJ_MAP_DECLARE()

	// {{ Message Map		
	virtual int OnLButtonDown	( WPARAM, LPARAM );
	virtual int OnLButtonUP		( WPARAM, LPARAM );
	virtual int OnLButtonDouble ( WPARAM, LPARAM );	//[2005/10/27]

	virtual int OnRButtonDown	( WPARAM, LPARAM );	//[2005/5/23] - jinhee
	virtual int OnRButtonUP		( WPARAM, LPARAM );	//[2005/5/23]

	virtual int OnCursorMove	( WPARAM, LPARAM );
	virtual int OnCursorEnter	( WPARAM, LPARAM );
	virtual int OnCursorOut		( WPARAM, LPARAM );

	virtual int OnToolTipMove	( WPARAM, LPARAM );
	virtual int OnToolTipEnter	( WPARAM, LPARAM );
	virtual int OnToolTipOut	( WPARAM, LPARAM );

	virtual int OnWheelUp		( WPARAM, LPARAM );	//[2005/7/6]
	virtual int OnWheelDown		( WPARAM, LPARAM );
	// }}

protected:

	bool	m_bDisable;
	bool	m_bPushed;
	//bool	m_bPick;

	int		m_iItemPushPosX;			/**< */
	int		m_iItemPushPosY;			/**< */
	//bool	m_bLButtonDown;				/**< */
	//bool	m_bSetClickPos;				/**< */
	bool	m_bClickMove;				/**< */

	int		m_nCellSize;			/**< �Ѽ��� ũ�� <br> */
	
	//[2005/6/21] m_ptNum �� m_iLineSize, m_iLineCount�� �и��Ͽ� �����Ѵ� 
	//POINT	m_ptNum;				/**< �� �׸��尡 ���ϴ� X�� ���� Y�� ���� <br> */	
	int		m_iLineSize;			/**< �� ���κ� ī��Ʈ <br> X�� ���� �� <br> */
	int		m_iLineCount;			/**< �׸��尡 �����ϴ� ���� <br> Y�� ���� �� <br> */
	
	POINT	m_ptGap;				/**< ���� �𸣰����� �׸��尣 ���ݿ� ���õǾ� �ִµ��ϴ� <br> */

	SPTexture* m_pGridTexture;		/**< �׸��� ���� <br> */
	RECT	m_rtGridSrc;				/**< �׸��� �ҽ� ���� <br> */
	POINT	m_ptGridOffset;

	SPTexture* m_pTexture;			/**< ��Ÿ�ӿ� <br> */
	RECT	m_rtSrc;				/**< ��Ÿ�ӿ� Src Rect <br> */
	RECT	m_rtMarkSrc[4];			/**< ������ Mark �� Rect <br> */
	
	std::vector<RECT> m_vCoolRect;	/**< ��Ÿ�ӿ� Dest Rect <br> */	
	std::vector<RECT> m_vDestRect;	/**< Dest Slot Rect <br> */

	std::vector< GRIDCELL >	vGRID;

	int		m_iShowCount;

};








