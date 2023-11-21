// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-08 ���� 10:26:19
//***************************************************************************

#pragma once

//#define WIID_MINIMAP_BASE			(WIID_MINIMAP	+	10 )	//��Ʈ�� ����
#define WIID_MINIMAP_ICON			(WIID_MINIMAP	+	20 )	//�׸� ������
#define WIID_MINIMAP_NAME			(WIID_MINIMAP	+	30 )	//�� �̸�
#define WIID_MINIMAP_NAME_BOLD		(WIID_MINIMAP	+	31 )	//�� �̸� ���ϰ�
#define WIID_MINIMAP_INFO_BG		(WIID_MINIMAP	+	40 )	//�� ��ȣ ���
#define WIID_MINIMAP_INFO			(WIID_MINIMAP	+	41 )	//�� ��ȣ(��ǥ)
#define WIID_MINIMAP_BUTTON			(WIID_MINIMAP	+	50 )	//�̴ϸ� �ݱ� ���� ��ư
#define WIID_MINIMAP_VIEW			(WIID_MINIMAP	+	60 )	//�̴ϸ� View

#define MINIMAP_BG_COUNT			3

class SPWindow;
class SPWindowMiniMapView;

enum GROUP_TYPE;

class SPWindowMiniMap : public SPWindow {

public:
	SPWindowMiniMap(WND_ID WndClassID, INSTANCE_ID InstanceID);
	SPWindowMiniMap(WND_ID WndClassID, INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowMiniMap();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);					//	�����ְ� �Ⱥ����ְ� üũ�ϱ�����

	void	ResetData();

public:


protected:

	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()

	virtual int OnCursorEnter	( WPARAM, LPARAM );
	virtual int OnCursorOut		( WPARAM, LPARAM );
	virtual int OnCursorLDown	( WPARAM, LPARAM );
	virtual int OnCursorLUp		( WPARAM, LPARAM );
	virtual int OnMiniMapButton	( WPARAM, LPARAM );		//	�̴ϸ� ��ư

	int OnSetStageID			( WPARAM wParam, LPARAM lParam); //StageID, GroupID �Ѵ� �޴´�.
	int OnRefreshMiniMapGOB		( WPARAM wParam, LPARAM lParam); //WPARAM�� Add,Del �Ӽ� LPARAM�� GOB������
	int OnRefreshIconTeam		( WPARAM wParam, LPARAM lParam); //WPARAM�� Add , Del Ÿ�� , LPARAM�� GU_ID
	int	OnPurgeAll				( WPARAM wParam, LPARAM lParam );	// ä�ΰ� �̵��� ������ �ʱ�ȭ AJJIYA [8/3/2005]

	int	OnWorldMap				( WPARAM wParam, LPARAM lParam );
	int	OnStageMap				( WPARAM wParam, LPARAM lParam );

	// }}
	
protected:
	void UpdateMapInfo();
	void UpdatePos();
	void ShowMiniMapButton( bool bStatus );
	void ShowThemeIcon( int iResID , int iResIndex );
	void ReposOwnImage();

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//

	std::string m_strMapName;		/**< Map Name <br> */
	char m_szMapInfo[128];			/**< Map Information <br> */
	
	int m_iStageID;					/**< Stage ID <br> */
	int m_iMapGroupID;				/**< Map Group ID <br> */
	int m_iMapID;					/**< Map ID <br> */
	int m_iMapIDMax;				/**< Map ID Max <br> */
	float m_fPosX;					/**< Local Player Pos X <br> */
	float m_fPosY;					/**< Local Player Pos Y <br> */	
	int m_iGroupHeight;				/**< Group Height <br> */

	float m_fCamX;
	float m_fCamY;
	
	SPTexture* m_pTheme;			/**< Theme Icon Image <br> */

	SPWindowMiniMapView*	m_pView;	/**< MiniMap View Window <br> */
	SPWindowButton*			m_pMiniMapClose;
	
	//std::vector<SPTexture*> m_vpMiniMap;
	bool					m_bBuildingIn;					//	�������̸� �̴ϸ��� ǥ������ �ʴ´�.
	bool					m_bMiniMapViewStatus;			//	���� �̴ϸ� ����.
	SPWindowStatic*			m_pMiniMapInfo;					//	�̴ϸ� ��ǥ ����

	SPTexture*				m_pBGTexture;
	RECT					m_rcBGDest[ MINIMAP_BG_COUNT ];
	RECT					m_rcBGSrc[ MINIMAP_BG_COUNT ];


};
