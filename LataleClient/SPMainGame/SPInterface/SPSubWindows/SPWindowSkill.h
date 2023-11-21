// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 2006-06-19 ������ AJJIYA
// Creation    : AJJIYA 2005-6-30    17:18 
//***************************************************************************

#pragma once

#define SKILL_BG_COUNT							9

#define SKILL_MAIN_MENU_MAX						10
#define SKILL_SUB_MENU_MAX						10

#define SKILL_CLASS_SEPARATION					100
#define SKILL_SUB_SEPARATION					100

#define SKILL_GRID_X_COUNT						4
#define SKILL_GRID_Y_COUNT						3

#define SKILL_GRID_X_SIZE						56
#define SKILL_GRID_Y_SIZE						68

#define SKILL_GRID_X_OFFSET						10
#define SKILL_GRID_Y_OFFSET						69

#define SKILL_UNIT_X_OFFSET						12
#define SKILL_UNIT_Y_OFFSET						14

#define LS_REQUIRE_COUNT						8

class SPWindow;
class SPWindowButton;
class SPUIUnitManager;

class SPWindowSkill : public SPWindow 
{
public:
	SPWindowSkill								( WND_ID WndClassID , INSTANCE_ID InstanceID );
	SPWindowSkill								( INSTANCE_ID InstanceID , int iX , int iY , int iCX , int iCY , SPWindow* pParent = NULL );
	virtual ~SPWindowSkill						();

	virtual	void		Init					();
	virtual	void		Clean					();
	virtual void		Show					( bool bWithChild = true );
	virtual void		Hide					( bool bSendServer = true );

	virtual	void		Process					( float fTime );
	virtual	void		Render					( float fTime );
	virtual void		RefreshRelationCoord	();

protected:

	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()

	virtual int 		OnBeginMove				( WPARAM, LPARAM );	// metalgeni [6/2/2006]
	virtual int 		OnEndMove				( WPARAM, LPARAM );	
	virtual int 		OnMove					( WPARAM, LPARAM );

	int					OnDragnDropEnd			( WPARAM wParam, LPARAM lParam );

	int					OnWheelUp				( WPARAM wParam, LPARAM lParam );
	int					OnWheelDown				( WPARAM wParam, LPARAM lParam );

	int					OnPurge					( WPARAM wParam, LPARAM lParam );
	int					OnWndPosUpdate			( WPARAM wParam, LPARAM lParam );

	int					OnStatusRefresh			( WPARAM wParam, LPARAM lParam );
	int					OnSkillUpdate			( WPARAM wParam, LPARAM lParam );

	int					OnGetSkillLVUP			( WPARAM wParam, LPARAM lParam );
	int					OnGetSkillLearn			( WPARAM wParam, LPARAM lParam );

	int					OnLearnSkillYes			( WPARAM wParam, LPARAM lParam );

	int					OnClose					( WPARAM wParam, LPARAM lParam );

	int					OnSliderUp				( WPARAM wParam, LPARAM lParam );
	int					OnSliderDown			( WPARAM wParam, LPARAM lParam );

	int					OnSliderBar				( WPARAM wParam, LPARAM lParam );

	int					OnGetUIUnitManager		( WPARAM wParam, LPARAM lParam );

	int					OnMainMenuLButtonUp		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnSubMenuLButtonUp		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnContentLButtonUp		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnContentLButtonDown	( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnContentCursorMove		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnContentCursorEnter	( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnContentCursorOut		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnContentWheelUp		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int					OnContentWheelDown		( unsigned int iID, WPARAM wParam , LPARAM lParam );


	// }}

	//////////////////////////////////////////////////////////////////////////
	
	enum SKILL_INSTANCE_ID
	{
		WIID_SKILL_CLOSE						=	WIID_SKILL	+	1						,
		WIID_SKILL_ICON_IMAGE																,
		WIID_SKILL_TEXT_IMAGE																,
		WIID_SKILL_POINT_LABEL																,
		WIID_SKILL_POINT_TEXT																,
		WIID_SKILL_SCROLL_UP																,
		WIID_SKILL_SCROLL_DOWN																,
		WIID_SKILL_SCROLL_BAR																,

		WIID_SKILL_MAIN_MENU_START				=	WIID_SKILL	+	5000					,
		WIID_SKILL_MAIN_MENU_END				=	WIID_SKILL_MAIN_MENU_START	+	9999	,
		WIID_SKILL_SUB_MENU_START															,
		WIID_SKILL_SUB_MENU_END					=	WIID_SKILL_SUB_MENU_START	+	9999	,
		WIID_SKILL_CONTENT_START															,
		WIID_SKILL_CONTENT_END					=	WIID_SKILL_CONTENT_START	+	9999	,
	};

	enum SKILL_BUTTON
	{
		SKILL_BUTTON_ENABLE						=	0										,
		SKILL_BUTTON_DISABLE																,
		SKILL_BUTTON_HIT																	,	//	MouseOver
		SKILL_BUTTON_CLICK																	,
		SKILL_BUTTON_CHECK																	,	//	Select
		SKILL_BUTTON_COUNT																	,
	};

	struct UI_IMAGE_DATA
	{
		std::string				m_strImage;		//	�̹��� ��� ( DATA/INTERFACE/CONCEPT/UI102.PNG )
		RECT					m_rcSrc;		//	�̹��� �ҽ� ����
	};

	struct UI_SUBID
	{
		int						m_iSubID;							//	���� ���̵�
		int						m_iPosX;							//	��� X ��ġ ( ��� ��ǥ )
		int						m_iPosY;							//	��� Y ��ġ ( ��� ��ǥ )
	};

	typedef std::vector< UI_SUBID >									STD_VECTOR_UI_SUBID;

	struct UI_MAIN_MENU
	{
		int						m_iItemID;							//	������ ���̵�
		int						m_iClassType;						//	ĳ���� ����
		int						m_iDestXPos;						//	��ư ��� X ��ġ
		int						m_iDestYPos;						//	��ư ��� Y ��ġ
		int						m_iXSize;							//	��ư X ������
		int						m_iYSize;							//	��ư Y ������
		UI_IMAGE_DATA			m_stButton[ SKILL_BUTTON_COUNT ];	//	��ư �̹��� ����
		STD_VECTOR_UI_SUBID		m_vUISubID;							//	Sub UI
	};

	typedef	std::multimap< int , UI_MAIN_MENU >						STD_MULTIMAP_UI_MAIN_MENU;

	enum SKILL_CONTENT_VIEW
	{
		SCV_NULL							=	0				,	//	ǥ�� ����
		SCV_TREE												,	//	Tree ���·� ǥ��
		SCV_LIST												,	//	��ų ��� ������� ǥ��
		SCV_CARD												,	//	��ų ��� Diable�� ǥ�� ������ Enable
		SCV_ITEM												,	//	������ ��ų
		SCV_COUNT												,
	};

	struct UI_SUB_MENU
	{
		SKILL_CONTENT_VIEW		m_eMenuType;						//	������ ǥ�� ���
		int						m_iXSize;							//	��ư X ������
		int						m_iYSize;							//	��ư Y ������
		UI_IMAGE_DATA			m_stButton[ SKILL_BUTTON_COUNT ];	//	��ư �̹��� ����
	};

	typedef	std::map< int , UI_SUB_MENU >							STD_MAP_UI_SUB_MENU;

	struct UI_CONTENT
	{
		int						m_iSubID;
		int						m_iGridIndex;
		DWORD					m_dwImageSetting;
		int						m_iSkillID;
	};

	typedef	std::map< int , UI_CONTENT >							STD_MAP_UI_CONTENT;

	struct UI_CONTENT_BUNDLE
	{
		int						m_iEndPage;
		STD_MAP_UI_CONTENT		m_mUIContent;
	};

	typedef	std::map< int , UI_CONTENT_BUNDLE >						STD_MAP_UI_CONTENT_BUNDLE;

	struct UI_TREE
	{
		int						m_iItemID;							//	������ ���̵�
		int						m_iDestXPos;						//	��� X ��ġ
		int						m_iDestYPos;						//	��� Y ��ġ
		int						m_iXSize;							//	X ������
		int						m_iYSize;							//	Y ������
		UI_IMAGE_DATA			m_stImage;							//	�̹��� ����
	};

	typedef std::vector< UI_TREE >									STD_VECTOR_UI_TREE;

	enum SKILL_CONTENT_LABEL
	{
		SCL_BG									=	0					,	//	��ų ���� Index ( 0 : �Ϲ� ) ( 1 : ��ų����0 ) ( 2 : ��������� )
		SCL_CUR_LEVEL10													,	//	���� ���� �ʴ���
		SCL_CUR_LEVEL1													,	//	���� ���� �ϴ���
		SCL_LEVEL_SLASH													,	//	���� ������ ( / )
		SCL_MAX_LEVEL10													,	//	�ִ� ���� �ʴ���
		SCL_MAX_LEVEL1													,	//	�ִ� ���� �ϴ���
		SCL_LEVEL_UP													,	//	���� �� ��ư
		SCL_NOT_LEARN													,	//	��ų �� ������� ? / ?
		SCL_COUNT														,	//	�̹�����
	};

	enum SKILL_CONTENT_GRID_VIEW											//	SKILL_TREE_SETTING.LDT �� ����
	{
		SCGV_NULL								=	0					,
		SCGV_SLOT_NOT_LEARN						=	28					,	//	LDT No. 29	������ ���� �̹��� ? / ?
		SCGV_SLOT_GENERAL						=	29					,	//	LDT No. 30	������ ���� �̹��� �Ϲ�
		SCGV_SLOT_LEVEL0						=	30					,	//	LDT No. 31	������ ���� �̹��� ��ų����0
		SCGV_SLOT_EMPTY							=	31					,	//	LDT No. 32	������ ���� �̹��� ���������
		SCGV_COUNT														,

	};

	struct UI_CONTENT_WINDOW
	{
		SPWindow*				m_pContent[ SCL_COUNT ];
		SPWindow*				m_pImages[ SCGV_COUNT ];					//	���� �̹�����
	};

	typedef std::vector< UI_CONTENT_WINDOW >						STD_VECTOR_UI_CONTENT_WINDOW;
	typedef	std::map< int , int >									STD_MAP_UI_CONTENT_PAGE;

	struct SKILL_LEARN_REQUIRE
	{
		int						m_iRequireType;								//	���� Ÿ��
		int						m_iRequireID;								//	���� ���̵�
		int						m_iRequireValue1;							//	���� ��
		int						m_iRequireValue2;							//	���� ��
		std::string				m_strErrorMsg;								//	���� �޼��� ����
	};

	struct SKILL_LEARN_LDT_DATA 
	{
		int						m_iKeyID;									//	��ų ���̵�
		std::string				m_strName;									//	�̸�
		UINT64					m_uiConsumptionEly;							//	�Һ� ����
		int						m_iConsumptionItemID;						//	�Һ� ������
//		int						m_iConsumptionItemCount;					//	�Һ� ������ ����
		SKILL_LEARN_REQUIRE		m_stRequireCondition[ LS_REQUIRE_COUNT ];	//	���� ����
		std::string				m_strDesc;									//	����
		std::string				m_strErrorEly;								//	���� �޼��� ����
		std::string				m_strErrorItem;								//	���� �޼��� ������
		int						m_iFXGroupID;								//	ȹ��� ������� FXGroupID
		std::string				m_strSuccess;								//	ȹ��� ������� ä�� ���ڿ�
	};

	typedef	std::map< int , SKILL_LEARN_LDT_DATA >						STD_MAP_LEARN_LDT_DATA;


	//////////////////////////////////////////////////////////////////////////
	//
	//	�Լ���
	//

	void						LoadLDTMainMenu			();
	void						LoadLDTSubMenu			();
	void						LoadLDTContent			();
	void						LoadLDTTreeSetting		( STD_VECTOR_UI_TREE& vTreeSetting );
	void						LoadLDTLearnSkill		();

	void						CreateWindowMainMenu	();
	void						CreateWindowSubMenu		();
	void						CreateWindowContent		();

	void						UpdateAll				();
	void						UpdateMainMenu			( int iClassType );
	void						UpdateSubMenu			( UI_MAIN_MENU* pUIMainMenu );
	void						UpdateContent			( int iCurSubMenu , int iCurContentPage );
	void						UpdateContentTree		( int iCurSubMenu , int iCurContentPage );
	void						UpdateContentList		( int iCurSubMenu , int iCurContentPage );
	void						UpdateContentCard		( int iCurSubMenu , int iCurContentPage );
	void						UpdateContentItem		( int iCurSubMenu , int iCurContentPage );

	//////////////////////////////////////////////////////////////////////////
	//
	//	MainMenu	Interface
	//

	void						AddMainMenu				( int iKey , UI_MAIN_MENU& stMainMenuData );

	int							GetMainMenuCount		();
	int							GetMainMenuCount		( int iKey );
	int							GetMainMenuSubCount		( int iKey , int iNumber );
	UI_MAIN_MENU*				GetMainMenu				( int iKey , int iNumber );

	//////////////////////////////////////////////////////////////////////////
	//
	//	SubMenu	Interface
	//

	void						AddSubMenu				( int iKey , UI_SUB_MENU& stSubMenuData );

	int							GetSubMenuCount			();
	UI_SUB_MENU*				GetSubMenu				( int iKey );

	//////////////////////////////////////////////////////////////////////////
	//
	//	SubMenu Page Interface
	//

	void						SetSubMenuPage			( int iKey , int iPage );
	int*						GetSubMenuPage			( int iKey );
	void						DelSubMenuPage			();

	//////////////////////////////////////////////////////////////////////////
	//
	//	Content	Interface
	//

	int							GetContentKey			( int iSubID , int iGridIndex );
	int							GetContentKeyToSub		( int iKey );

	void						AddContent				( int iKey , UI_CONTENT& stContent );

	int							GetContentBundleCount	();
	int							GetContentEndPage		( int iSubID );
	int							GetContentCount			( int iSubID );

	UI_CONTENT_BUNDLE*			GetContentBundle		( int iSubID );
	UI_CONTENT*					GetContent				( int iKey );

	//////////////////////////////////////////////////////////////////////////
	//
	//	Content Page Interface
	//

	int							GetContentPageKey		( int iMainID , int iSubID );
	void						SetContentPage			( int iKey , int iPage );
	int*						GetContentPage			( int iKey );
	void						DelContentPage			();

	//////////////////////////////////////////////////////////////////////////
	
	void						DataReset				();
	void						ReposOwnImage			();

	void						HideContentWindow		( int iPos );
	void						SetContentWindow		( int iPos , int iSkillID , bool bShow , bool bLearnShow );
	void						SetContentImageWindow	( int iPos , DWORD dwImageSetting );
	void						SetSkillPoints			();
	void						SetSkillUIInfo			( int iID , int iUIUnitPos , int iCoolTimeID , bool bQuickSlotUse , int iDisableIcon , int iDisableIconIndex , int iDisableAlpha , int iItemID , int iContainerType , int iSlotIndex );

	//////////////////////////////////////////////////////////////////////////

	void						AddLearnSkillLdt		( SKILL_LEARN_LDT_DATA& stSkillLearnLDtData );
	void						ClearLearnSkillLdt		( SKILL_LEARN_LDT_DATA& stSkillLearnLDtData );
	SKILL_LEARN_LDT_DATA*		GetLearnSKillLdt		( int iSkillID );
	void						SetLearnSkillMsg		( int iSkillID );
	void						SetLearnSkillRequire	( std::string& strMessage , int iType , int iID , int iValue1 , int iValueSlv1 , int iValue2 , int iValueSlv2 , int iLevel , int iGSNumber );



	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	STD_MULTIMAP_UI_MAIN_MENU		m_mmUIMainMenu;
	STD_MAP_UI_SUB_MENU				m_mUISubMenu;
	STD_MAP_UI_CONTENT_BUNDLE		m_mUIContent;

	SPTexture*						m_pBGTexture;
	RECT							m_rcBGDest[ SKILL_BG_COUNT ];
	RECT							m_rcBGSrc[ SKILL_BG_COUNT ];

	SPWindowButton*					m_pMainMenuButton[ SKILL_MAIN_MENU_MAX ];
	SPWindowButton*					m_pSubMenuButton[ SKILL_SUB_MENU_MAX ];

	int								m_iCurClassType;
	UI_MAIN_MENU*					m_pCurMainMenu;
	int								m_iCurSubMenu;
	STD_MAP_UI_CONTENT_PAGE			m_mCurSubMenuPage;
	STD_MAP_UI_CONTENT_PAGE			m_mCurContentPage;

	SPUIUnitManager					m_UIUnitManager;
	STD_VECTOR_UI_CONTENT_WINDOW	m_vUIContentWindow;

	BOOL							m_bLMouseDown;
	LPARAM							m_lParam;

	STD_MAP_LEARN_LDT_DATA			m_mLearnSkill;
	int								m_iLearnSkillID;




};
