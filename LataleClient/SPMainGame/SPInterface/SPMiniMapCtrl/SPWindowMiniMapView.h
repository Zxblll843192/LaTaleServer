// Copyright (C) jinhee
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : jinhee 2005-04-14 ���� 10:26:19
//***************************************************************************

#pragma once

// .NET2003 ���� �ؽø� ��붧����.. 
#ifdef _DEFINE_DEPRECATED_HASH_CLASSES
#undef _DEFINE_DEPRECATED_HASH_CLASSES
#define _DEFINE_DEPRECATED_HASH_CLASSES 0	
#endif

#include <hash_map>

const int MINI_MAP_DEST_WIDTH = 185 - 1;
const int MINI_MAP_DEST_HEIGHT = 74;

const int MINIMAP_SCALE_X	=	16;
const int MINIMAP_SCALE_Y	=	16;

const int MINIMAP_OUTLINE	=	3;

class SPStage;
class SPMapGroup;
class SPWindow;
class SPWindowMiniMapIcon;
class SPWindowMiniMapToolTip;

struct SAVE_POINT
{
	UINT16	uiStageID;		
	UINT16	uiMapGroupID;		
	UINT16	uiMapID;			
	float	fPosX;
//	float	fPosY;
	BOOL	bCal;
};

typedef	std::multimap< GU_ID , SAVE_POINT >		STD_MULTIMAP_SAVEPOINT;
typedef std::vector< SAVE_POINT* >				STD_VECTOR_SAVEPOINT;

class SPWindowMiniMapView :	public SPWindow {
public:
	SPWindowMiniMapView(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent);
	~SPWindowMiniMapView();

	virtual void Init();
	virtual void Clean();	
	virtual void Process(float fTime);	
	virtual void Render(float fTime);	

	virtual bool SetImage(const char* szImage, int iSrcX=0, int iSrcY=0);
	virtual void SetImage(SPTexture* pImage, int iSrcX= 0, int iSrcY=0);

	/**
	 * �ش� �׷��� �̴ϸ� �̹��� ���� �ε��Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void SetMiniMapImageList();			//[2005/4/14]

	/**
	 * �ش� �׷��� �̴ϸ� �̹����� �ʱ�ȭ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void ResetMiniMapImageList();		//[2005/4/14]
	
	/**
	 * �̴ϸ� �̹��� ����� ���� ���� ��� �۾��� �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void SetRenderProcess();

	/**
	 * �̴ϸ� �̹��� ���� <br>
	 @param NONE
	 @return NONE
	*/
	bool RenderMiniMap();

	//	����󿡼��� ���� �÷��̾ ������ �̴ϸ� ����
	RECT GetMiniMapRect()	{	return m_rtMiniMap;	}

protected:

	SPIMESSAGE_OBJ_MAP_DECLARE()
	// {{ Message Map	
	int OnCursorEnter		( WPARAM, LPARAM );
	int OnCursorOut			( WPARAM, LPARAM );
	int OnSetImageIndex		( WPARAM wParam, LPARAM lParam);
	int OnRefreshMiniMapGOB	( WPARAM wParam, LPARAM lParam); //WPARAM�� GOB Ÿ��, LPARAM�� GOB������
	int OnRefreshIconTeam	( WPARAM wParam, LPARAM lParam); //WPARAM�� Add , Del Ÿ�� , LPARAM�� GU_ID
	int OnPurgeAll			( WPARAM wParam, LPARAM lParam );	// ä�� ����� ������ �ʱ�ȭ AJJIYA [8/3/2005]
	// }}

protected:

	void	IconClean();								//	Icon �����
	void	IconProcess( float fTime );					//	Icon ������
	void	IconRender();								//	Icon ����
	void	IconRectInCheck( int iCurX , int iCurY );	//	Icon ������ ���콺 ��ġ ����

	//	������� �ʿ��� �̴ϸ��� �����ִ� �κ��� ����Ѵ�.
	RECT	GetMiniMapRect		( int iLocalPlayerPosX , int iLocalPlayerPosY );

	//	SAVE_POINT�� ���� LDT �ε�
	void	InitSavePoint		();
	void	LoadSavePoint		();
	void	AddSavePoint		( SAVE_POINT& SavePointInfo );
	void	CleanSavePoint		();
	void	GetSavePoint		( int iStageID , int iMapGroupID );
	void	RenderSavePoint		( float fTime );

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	RECT							m_rtMiniMap;			//	����󿡼� ���� �̴ϸ��� ����
	bool							m_bShowToolTip;			//	���� ǥ�� ����
	SPWindowMiniMapToolTip			m_ToolTip;
	
	SPWindowMiniMapIcon				m_LocalPlayer;			//	���� �÷��̾�� ���� �д�.
	
	stdext::hash_map< INSTANCE_ID , SPWindowMiniMapIcon*>	m_hmGOBIcon;	//	Instance_ID�� GOB�� ������ ����.
	
	STD_MULTIMAP_SAVEPOINT									m_mmSavePoints;	//	���������� �ʱ׷�ID�� �̿��Ͽ� �����Ѵ�.
	STD_VECTOR_SAVEPOINT									m_vSavePoints;	//	���� ������ �Ǿ���� ���̺� ����Ʈ.
	SPWindow*												m_pSaveLine;
	SPWindow*												m_pSavePoint;
	SPWindow*												m_pSavePlayer;
	int														m_iMaxLine;
	int														m_iSavePointSizeX;
	int														m_iSaveLineOffSetX;
	int														m_iSaveLineOffSetY;


	struct IMAGE_ATTR {
		SPTexture*	pImage;
		POINT		SrcPoint;
	};
	std::vector<IMAGE_ATTR> m_vpImageAttr;

	std::vector<SPTexture*> m_vpImage; /**< MiniMap Image List <br> */

	int m_iCurImage;
	
	int m_iStage;					/**< Current Stage ID <br> */
	int m_iMapGroup;				/**< Current Map Group ID <br> */

	SPMapGroup* m_pMapGroup;		/**< Current Map Group <br> */
	int m_iFirstMapID;				/**< First Map Index <br> */
	int m_iSecondMapID;				/**< Second Map Index <br> */
	
	RECT m_rtDestRect;				/**< Dest MiniMap Rect <br> */

	RECT m_rtFirstSrc;				/**< First MiniMap Source Rect <br> */
	RECT m_rtSecondSrc;				/**< Second MiniMap Source Rect <br> */
	RECT m_rtFirstDest;				/**< First MiniMap Dest Rect <br> */
	RECT m_rtSecondDest;			/**< Second MiniMap Dest Rect <br> */
	
	int m_iPosX;					/**< Local Player Pos X <br> */
	int m_iPosY;					/**< Local Player Pos Y <br> */

	int m_iGroupWidth;				/**< map Group Width <br> */
	int m_iGroupHeight;				/**< map Group Height <br> */
	int m_iMapWidth;				/**< Map Widht <br> */
	int m_iMapHeight;				/**< Map Height <br> */

	SPTexture*		m_pImageOutLine;		// �̴ϸ� �׵θ� �̹��� [1/30/2007 AJJIYA]
	RECT			m_rcDestOutLine[ MINIMAP_OUTLINE ];	// �̴ϸ� �׵θ� ��� ���� [1/30/2007 AJJIYA]
	RECT			m_rcSrcOutLine[ MINIMAP_OUTLINE ];	// �̴ϸ� �׵θ� �ҽ� ���� [1/30/2007 AJJIYA]

};
