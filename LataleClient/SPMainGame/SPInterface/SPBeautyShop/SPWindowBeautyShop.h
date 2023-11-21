
#ifndef __SPWINDOW_BEAUTYSHOP_H__
#define __SPWINDOW_BEAUTYSHOP_H__

//------------------------------------------------------------------------------------

// ������ â
#define WIID_BEAUTYSHOP_CHANGE_CLOSE			(WIID_BEAUTYSHOP + 1)	///< �ݱ�
#define WIID_BEAUTYSHOP_CHAR_RESET				(WIID_BEAUTYSHOP + 2)	///< RESET ��ư

#define WIID_BEAUTYSHOP_CATEGORY_EXPLAIN		(WIID_BEAUTYSHOP + 11)	///< ī�װ� ����(5)
#define WIID_BEAUTYSHOP_DETAIL_EXPLAIN			(WIID_BEAUTYSHOP + 21)	///< ���� ����(5)
#define WIID_BEAUTYSHOP_DETAIL_TOOLTIP			(WIID_BEAUTYSHOP + 31)	///< ToolTip ��ư(5)

#define WIID_BEAUTYSHOP_CATEGORY_LEFT			(WIID_BEAUTYSHOP + 41)	///< ����ư(5)
#define WIID_BEAUTYSHOP_CATEGORY_RIGHT			(WIID_BEAUTYSHOP + 51)	///< ����ư(5)
#define WIID_BEAUTYSHOP_DETAIL_LEFT				(WIID_BEAUTYSHOP + 61)	///< ����ư(5)
#define WIID_BEAUTYSHOP_DETAIL_RIGHT			(WIID_BEAUTYSHOP + 71)	///< ����ư(5)

#define WIID_BEAUTYSHOP_COMMIT_BTN				(WIID_BEAUTYSHOP + 81)	///< ���� ��ư(5)



enum BS_ERROR_DLGTYPE	{
	BS_ERRDLG_NONE = 0,
	BS_ERRDLG_CHANGE_CHOICE,		// �����->�Ϲ� ���� ����â
};

struct BS_ERRDLG_STATE
{
	int iDlgType ;		/// dialog Type
	int iSelectlayer ;	///< Select Layer
	BS_ERRDLG_STATE(){
		Clear();
	}
	void Clear(){
		iDlgType = BS_ERRDLG_NONE ;
		iSelectlayer = 0 ;
	}
	void Set(int _type, int _layer)
	{
		iDlgType = _type ;
		iSelectlayer = _layer ;
	}
} ;


//------------------------------------------------------------------------------------
#define BS_INDEX_MAX				5		///< ���, �÷�, ��, ����, ����
//------------------------------------------------------------------------------------
class SPWindow;
class SPPlayer;
class SPItem;
class BeautyShopUnit;
class BeautyShopManager;
struct BS_CODE_PARSE ;
class SPWindowBeautyShop : public SPWindow
{
public:
	SPWindowBeautyShop(WND_ID WndClassID, INSTANCE_ID InstanceID);
	SPWindowBeautyShop(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);
	virtual ~SPWindowBeautyShop();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);

protected:
	//enum	{
	//	BS_GROUP_HAIR = 0,
	//	BS_GROUP_HCOL ,
	//	BS_GROUP_EXPR,
	//	BS_GROUP_E_COL,
	//	BS_GROUP_SKIN,
	//	BS_GROUP_MAX,
	//};
	
	
	///================ Message Map ====================

	SPIMESSAGE_OBJ_MAP_DECLARE()
	
	virtual int OnExit(WPARAM wParam, LPARAM lParam);

	virtual int OnYes( WPARAM wParam, LPARAM lParam);
	virtual int OnNo( WPARAM wParam, LPARAM lParam);

	virtual int OnChangeCategoryLeftClick(unsigned int, WPARAM, LPARAM);
	virtual int OnChangeCategoryRightClick(unsigned int, WPARAM, LPARAM);
	virtual int OnChangeDetailLeftClick(unsigned int, WPARAM, LPARAM);
	virtual int OnChangeDetailRightClick(unsigned int, WPARAM, LPARAM);

	virtual int OnItemDetailToolTipEnter(unsigned int, WPARAM, LPARAM);
	virtual int OnItemDetailToolTipOut(unsigned int, WPARAM, LPARAM);
	virtual int OnItemDetailToolTipMove(unsigned int, WPARAM, LPARAM);

	virtual int OnBeautyShopItemCommit(unsigned int, WPARAM, LPARAM);

	virtual int OnCharacterRefresh(WPARAM, LPARAM);
	virtual int OnRecvFigureChange(WPARAM wParam, LPARAM lParam) ;

	///================ End Message Map ====================

	void RenderBackground(float fTime);

	// init
	void InitBackground() ;
	void InitCharWindow();
	void InitBeautyShopWindow();
	void initCurUserLayer(bool bUpdate = true);	///< ���� ������� Layer ����
	void GetCurPlayerLayer();				///< ĳ���� Layer ���� ������

	void SetCurSelectLayer(int _iLayer);		///< Category ���� 
	void SetChangeCharacterLayer(int _iLayer);	///< ĳ���� ����
	void SetEquipCharacterLayer() ;				///< Equip & Fashion �缳��

	void SetLayerButton(int _iLayer, bool bEnable);			///< �ش� Layer�� Button�� Ȱ��ȭ/��Ȱ��ȭ
	int OnCommitCheck(unsigned int _index, bool bChecked = false);	///< ����� ������ üũ ��ƾ
	int SetErrorDlg(int iErrorCode, int _index);			///<  Error Dialog ����
	
	void InitPlayerAnimation();										///< ĳ���� �ִϸ��̼� �ʱ�ȭ
	void SetAniSeq(unsigned int uiAniIndex, bool bLoop = true);			///< �ش� Index�� �ִϸ��̼� ����

protected:
	BeautyShopManager* m_pBSData ;
	bool				m_bShowToolTip;

	// Player
	SPPlayer* m_pkPlayer;
	unsigned int m_uiAniIndex;
	unsigned int m_uiBeforeAniIndex;
	float m_fAniAccmulateTime;
	float m_fAniMaxTime;

	// Background
	SPTexture* m_pkBGTexture;	// UI104.png
	RECT m_rcSrcCharBack[5];	// UP, Middle, Lower, Title, Background
	RECT m_rcDstCharBack[5];	// UP, Middle, Lower, Title, Background
	RECT m_rcSrcDlgBack[29];	// Background, TextBG, Group
	RECT m_rcDstDlgBack[29];	// Background, TextBG, Group

	// Char Change
	std::vector< unsigned int > m_vCurBasicID;				// for Current Basic

	int m_iCurGender ;				///< ���� ����
	int	m_iCurSelButton ;						///< ���� ������ ��ư Index
	bool m_bCurEnable[BS_INDEX_MAX] ;			///< layer��ư Enable ����
	std::string m_strCategory[BS_INDEX_MAX] ;	///< ī�װ� String
	std::string m_strDetail[BS_INDEX_MAX] ;		///< ���� String

	BS_ERRDLG_STATE m_iErrorDlgState ;	///< ErrorDialog ����
};

#endif