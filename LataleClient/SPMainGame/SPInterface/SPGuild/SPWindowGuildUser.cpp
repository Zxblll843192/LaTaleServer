// Copyright (C) DURAGON
//***************************************************************************
// System Name : GUILD USER UNIT
// Comment     : 
// Creation    : DURAGON 2007-4-04    11:18 
//***************************************************************************

#include "SPCommon.h"
#include "SPUtil.h"

#include "SPWindowDEF.h"
#include "SPWindow.h"
#include "SPWindowButton.h"
#include "SPWindowStatic.h"

#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"
#include "SPResourceManager.h"
#include "SPItemAttr.h"
#include "SPItemStatus.h"
#include "SPWindowToolTip.h"

#include "SPGOBManager.h"

#include "PacketID.h"

#include "GlobalDefines_Share.h"
#include "SPGuildArchive.h"
#include "SPWindowGuildUser.h"

#include "SPLocalizeManager.h"

SPWindowGuildUser::SPWindowGuildUser(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent)
: SPWindow( WNDID_GUILD_INFO , InstanceID, iX, iY, iCX, iCY, pParent )	
, m_pSelectBtn(NULL)
, m_pClass(NULL)
, m_pName(NULL)
, m_pLevel(NULL)
, m_pChannel(NULL)
, m_pRank(NULL)
{
	Init();
}

SPWindowGuildUser::~SPWindowGuildUser()
{
	Clean();
}

void SPWindowGuildUser::Init()
{
	m_strToolTip	=	"[SPWindowGuildUser]";
	m_bOnline		= false ;
	m_bShowToolTip	= true ;
	m_bShowEnable	= false ;		// List�� �ޱ������� ShowEnable(false)
	m_bSelectable	= false ;

	g_pVideo->GetTextureMgr()->LoadTexture( "DATA/INTERFACE/CONCEPT/UI105.PNG" , &m_pBGTexture );

	ReposOwnImage();

	SetRect( &m_rcBGSrc[0]	, 484 , 282 , 486 , 298 );			//	��� ����
	SetRect( &m_rcBGSrc[1]	, 488 , 282 , 490 , 298 );			//	��� �߰�
	SetRect( &m_rcBGSrc[2]	, 492 , 282 , 494 , 298 );			//	��� ������

	m_cOnLineColor	=	RGBA(49, 76, 97, 255) ;
	m_cOffLineColor	=	RGBA(189,189,189,255); //(49, 76, 97, 153) ;

	int	iInstanceID	=	m_InstanceID	+	1;			// +1
	m_iStartID		=	iInstanceID;

	SPWindowButton*	pWindowButton	=	NULL;

	m_pClass	=	new	SPWindowStatic( iInstanceID , 11 , 0 , 16 , 16 , this );		// ��������
	iInstanceID++;			// +2

	m_pName		=	new	SPWindowStatic( iInstanceID , 45 , 3 , 113 , 12 , this );		// ���̵�
	m_pName->SetFontColor(RGBA(49, 76, 97, 255)) ;
	m_pName->SetWindowText(NULL) ;
	m_pName->SetFontShadow( false );
	iInstanceID++;			// +3

	m_pLevel	=	new	SPWindowStatic( iInstanceID , 162 , 3 , 38 , 12 , this );		// ����
	m_pLevel->SetFontColor(RGBA(49, 76, 97, 255)) ;
	m_pLevel->SetFontShadow( false );
	iInstanceID++;			// +4

	m_pGPoint	=	new	SPWindowStatic( iInstanceID , 204 , 3 , 57 , 12 , this );		// �⿩��
	m_pGPoint->SetFontColor(RGBA(49, 76, 97, 255)) ;
	m_pGPoint->SetFontShadow( false );
	iInstanceID++;			// +5

	m_pChannel	=	new	SPWindowStatic( iInstanceID , 265 , 3 , 38 , 12 , this );		// ä��
	m_pChannel->SetFontColor(RGBA(49, 76, 97, 255)) ;
	m_pChannel->SetFontShadow( false );
	iInstanceID++;			// +6

	m_pSelectBtn	=	new	SPWindowButton( iInstanceID , 315 , 0 , 22 , 16 , this );	// �������� -> Control Message
	m_pSelectBtn->SetImage			( "DATA/INTERFACE/CONCEPT/UI105.PNG" , 142 , 57 );
	m_pSelectBtn->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI105.PNG" , 165 , 57 );
	m_pSelectBtn->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI105.PNG" , 188 , 57 );
	m_pSelectBtn->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI105.PNG" , 211 , 57 );
	iInstanceID++;			// +7

	m_pSelectBG	=	new	SPWindowStatic( iInstanceID , 315 , 0 , 24 , 16 , this );		// ���� ���
	m_pSelectBG->SetImage			( "DATA/INTERFACE/CONCEPT/UI105.PNG" , 282 , 183 );
	m_pSelectBG->SetShowEnable(false) ;
	iInstanceID++;			// +8

	m_pRank		=	new	SPWindowStatic( iInstanceID , 318 , 2 , 16 , 13 , this );		// ���� Image
	m_pRank->SetFontShadow( false );

	m_iEndID	=	iInstanceID;
	m_pUserInfo	=	NULL;
}

void SPWindowGuildUser::Clean()
{
	SPWindow::Clean();
	m_pUserInfo = NULL ;
	m_pSelectBG	= NULL ;
	m_pSelectBtn= NULL ;
	m_pClass	= NULL ;
	m_pName		= NULL ;
	m_pLevel	= NULL ;
	m_pChannel	= NULL ;
	m_pRank		= NULL ;

	SAFE_RELEASE( m_pBGTexture );
}

void SPWindowGuildUser::Show(bool bWithChild)
{
	if( m_pUserInfo == NULL )
		return ;
	SPWindow::Show(bWithChild);

	int	iCursorX	=	g_pInterfaceManager->GetCursorX();
	int	iCursorY	=	g_pInterfaceManager->GetCursorY();

	// Select Button 
	if( m_bSelectable && m_pUserInfo->byGrade != GUILD_GRADE_01)		
	{
		m_pSelectBtn->SetShowEnable(true) ;
		m_pSelectBtn->Show() ;
	}
	else
	{
		m_pSelectBtn->SetShowEnable(false) ;
		m_pSelectBtn->Hide() ;
	}

	if( IsCursorIn( iCursorX , iCursorY ) == TRUE )
	{
		OnCursorEnter( NULL , NULL );
	}
}

void SPWindowGuildUser::Hide(bool bSendServer)
{
	SPWindow::Hide(bSendServer);

	int	iCursorX	=	g_pInterfaceManager->GetCursorX();
	int	iCursorY	=	g_pInterfaceManager->GetCursorY();

	if( IsCursorIn( iCursorX , iCursorY ) == TRUE )
	{
		OnCursorOut( NULL , NULL );
	}
}

void SPWindowGuildUser::ReposOwnImage()
{
	SetRect( &m_rcBGDest[0]	, m_iAX					, m_iAY		, m_iAX + 2					, m_iAY + m_iSY );		//	BG Left
	SetRect( &m_rcBGDest[1]	, m_rcBGDest[0].right	, m_iAY 	, m_rcBGDest[0].right + 341	, m_iAY + m_iSY );		//	BG Middle
	SetRect( &m_rcBGDest[2]	, m_rcBGDest[1].right	, m_iAY		, m_rcBGDest[1].right + 2	, m_iAY + m_iSY );		//	BG Right
}

void SPWindowGuildUser::RefreshRelationCoord()
{
	SPWindow::RefreshRelationCoord();
	ReposOwnImage();
}

void SPWindowGuildUser::Process(float fTime)
{
	SPWindow::Process( fTime );
}

void SPWindowGuildUser::Render(float fTime)
{
	if( m_bShow == FALSE )			return;
	if( m_bShowEnable == false )	return ;


	g_pVideo->Flush();

	if( m_WindowState == WND_STATE_CLICK || m_WindowState == WND_STATE_HITTEST )
	{
		if( m_pBGTexture )
		{
			for( int i = 0 ; i < GUILD2_SELECT_BG_COUNT ; i++ )
			{
				m_pBGTexture->SetColor();
				m_pBGTexture->RenderTexture( &m_rcBGDest[i] , &m_rcBGSrc[i] );
			}
			g_pVideo->Flush();
		}
	}



	SPWindow::Render(fTime);
}

bool SPWindowGuildUser::IsGuildUserInfo()
{
	bool bResult	=	false;

	std::string	strName	=	GetName() ;
	if( strName.empty() == false )
		bResult	=	true;

	return bResult;
}


/**
Guild User Information�� �޾Ƽ� ó���ϴ� �ֿ���
typedef struct _GUILD_CMEMBER
{
INT32	iCharID;			// ĳ������ DBŰ
INT32	iUserID;			// Account�� DBŰ(���������� ã�����Ѱ�)
char	szName[LEN_NAME+1];	// ĳ����
int		byClass;			// ����
int		wLevel;				// ����
int		wServerID;			// �������̵�(ä������ǥ�ø� ���ؼ�)
int		byGradeInGuild;		// ��峻 ��å(1:�渶, 2:�α渶, 3~6:ȸ��)
} GUILD_CMEMBER, *PGUILD_MEMBER;
*/
void SPWindowGuildUser::SetGuildInfo(int iIndex, int iGuildProperty, PGUILD_MEMBER pGuildUserInfo )
{
	m_pUserInfo = pGuildUserInfo ;		// ToolTip ó���� ���ؼ� ��¿�� ����.. �Ѥ�;;
	if( m_pUserInfo == NULL )
		return ;

	SetIClassImage( (int)m_pUserInfo->byClass ) ;
	SetName( m_pUserInfo->szName );
	SetLevel( m_pUserInfo->wLevel ) ;
	SetGPoint( m_pUserInfo->iPoint ) ;
	SetChannel( m_pUserInfo->wServerID ) ;
	SetRankImage(iGuildProperty, (int)m_pUserInfo->byGrade ) ;
}

/**
������ �̹��� ������
[CLASS_A],		395, 324, 411, 340);		// ������
[CLASS_B],		412, 324, 428, 340);		// �����
[CLASS_C],		395, 307, 411, 323);		// ������
[CLASS_D],		412, 307, 428, 323);		// ������
*/
void SPWindowGuildUser::SetIClassImage( int iClassType )
{
	m_pClass->SPSendMessage(SPIM_SET_IMAGECLEAR);
	const char*	pTextureName;
	RECT*		pTextureSrc;
	pTextureName	=	g_pInterfaceManager->GetClassTextureName( (CLASS_TYPE)iClassType );
	pTextureSrc		=	g_pInterfaceManager->GetClassTextureSrc( (CLASS_TYPE)iClassType );
	if( pTextureName != NULL && pTextureSrc != NULL )
		m_pClass->SetImage( pTextureName , pTextureSrc->left , pTextureSrc->top );
}

void SPWindowGuildUser::SetName( const char* pstrName )
{
	m_pName->SetWindowText( pstrName );
	if( m_pUserInfo->byGrade == GUILD_GRADE_01)
		m_pName->SetFont(FONT_12_BOLD);
	else
		m_pName->SetFont(FONT_12_NORMAL);
}

void SPWindowGuildUser::SetLevel( int uiLevel )
{
	TCHAR szTemp[4] ;
	wsprintf(szTemp, "%d", uiLevel) ;
	m_pLevel->SetWindowText( szTemp );
	if( m_pUserInfo->byGrade == GUILD_GRADE_01)
		m_pLevel->SetFont(FONT_12_BOLD);
	else
		m_pLevel->SetFont(FONT_12_NORMAL) ;
}

/**
��� �⿩�� ��� %�� ����� ���ؼ� ��ü ����Ʈ�� �ʿ��ϴ�.
*/
void SPWindowGuildUser::SetGPoint( int iGPoint )
{
	float fGProtege = 0 ;
	int iGProtege = 0 ;
	TCHAR szTemp[8] ;
	SPGuildArchive* pkGuildArchive = g_pGOBManager->GetGuildArchive() ;
	if( pkGuildArchive == NULL )
		return ;

	int iGTPoint = pkGuildArchive->GetGuildTotalPoint() ;
	if( iGTPoint > 0 )
		fGProtege = ((float)iGPoint * 100 / iGTPoint) ;
	iGProtege = (int)fGProtege ;
	wsprintf(szTemp, "%0d%%", iGProtege) ;
	m_pGPoint->SetWindowText( szTemp );
}

void SPWindowGuildUser::SetChannel( int uiChannel )
{
	TCHAR szTemp[16] ;
	if( uiChannel > 0 )			// ON-Line
	{
		SetOnline(true);
		if( uiChannel > INDUN_PVP_CHANNEL_MAX )		{
			if( g_pResourceManager->GetGlobalString(51000005) )
				wsprintf( szTemp , "%s", g_pResourceManager->GetGlobalString(51000005) );
			else
				wsprintf( szTemp , "%s", "PVP" );
		}
		else if( uiChannel > INDUN_CHANNEL_MAX )	{
			if( g_pResourceManager->GetGlobalString(50000012) )
				wsprintf( szTemp , "%s", g_pResourceManager->GetGlobalString(50000012) );
			else
				wsprintf( szTemp , "%s", "IN" );
		}
		else
			wsprintf( szTemp , "%3d", uiChannel % 100 );
		m_pChannel->SetWindowText( szTemp );
	}
	else						// OFF-Line
	{
		SetOnline(false);
		wsprintf( szTemp , ".");
		m_pChannel->SetWindowText( szTemp );
	}
}

/**
��� Ÿ�Ժ�, �ڽ��� ������ ���� ������ ����
*/
void SPWindowGuildUser::SetRankImage(int iProperty, int iRank )
{
	int iX, iY ;
	switch( iProperty )
	{
	case 1:				// �Ϲ���
		iX = 410;		iY = 138;
		break ;
	case 2 :			// õ����
		iX = 410;		iY = 110;
		break ;
	case 3:				// �Ǹ���
		iX = 410;		iY = 124;
		break ;
	default:			// �Ϲ���
		iX = 410;		iY = 138;
		break ;
	}
	iX += (17 * (iRank - 1)) ;		// iRank �� 1���� �����ΰ��
	m_pRank->SPSendMessage(SPIM_SET_IMAGECLEAR);
	m_pRank->SetImage( "DATA/INTERFACE/CONCEPT/UI105.PNG" , iX , iY );
}

/**
OnLine  : OnLine  ���ڻ�����
OffLine : Offline ���ڻ�����
*/
void SPWindowGuildUser::SetOnline( bool bOnline )
{
	m_bOnline = bOnline ;
	if( bOnline == TRUE )	{
		m_pName->SetFontColor( m_cOnLineColor );
		m_pLevel->SetFontColor( m_cOnLineColor );
		m_pChannel->SetFontColor( m_cOnLineColor );
	}
	else	{
		m_pName->SetFontColor( m_cOffLineColor );
		m_pLevel->SetFontColor( m_cOffLineColor );
		m_pChannel->SetFontColor( m_cOffLineColor );
	}
}



void SPWindowGuildUser::ShowToolTip( bool bShowToolTip )
{
	m_bShowToolTip	=	bShowToolTip;
}

const char* SPWindowGuildUser::GetName()
{
	return	m_pName->GetWindowText();
}

int SPWindowGuildUser::GetGrade() 
{
	if( m_pUserInfo )
	{
		return (int)m_pUserInfo->byGrade ;
	}
	return -1 ;
}

void SPWindowGuildUser::SetSelButton(bool bSet) 
{
	m_bSelectable = bSet ;
}

bool SPWindowGuildUser::GetSelButton() 
{
	return m_bSelectable ;
}


void SPWindowGuildUser::SetWndState( WND_STATE eWndState )
{
	m_WindowState	=	eWndState;
}

void SPWindowGuildUser::ShowSelectBG(bool bShow)
{
	//if( SPLocalizeManager::GetInstance()->GetSiteType() != SITE_SANDA )
	//{
	m_pSelectBG->SetShowEnable(bShow) ;
	bShow ? m_pSelectBG->Show() : m_pSelectBG->Hide() ;
	//}
}


SPIMESSAGE_OBJ_MAP_BEGIN( SPWindowGuildUser )

// For Mouse Move
SPIMESSAGE_COMMAND(	SPIM_CURSOR_ENTER		,										OnCursorEnter	)
SPIMESSAGE_COMMAND(	SPIM_CURSOR_OUT			,										OnCursorOut		)
SPIMESSAGE_COMMAND(	SPIM_CURSOR_MOVE		,										OnCursorMove	)
SPIMESSAGE_CONTROL_RANGE( SPIM_CURSOR_ENTER	,	m_iStartID	,	m_iEndID		,	OnCursorEnter	)
SPIMESSAGE_CONTROL_RANGE( SPIM_CURSOR_OUT	,	m_iStartID	,	m_iEndID		,	OnCursorOut		)
SPIMESSAGE_CONTROL_RANGE( SPIM_CURSOR_MOVE	,	m_iStartID	,	m_iEndID		,	OnCursorMove	)

// For Select
SPIMESSAGE_COMMAND(	SPIM_LBUTTON_UP			,										OnLButtonUp		)
SPIMESSAGE_CONTROL( SPIM_LBUTTON_UP			,	m_InstanceID+6					,	OnBGButtonUp	)
SPIMESSAGE_CONTROL_RANGE( SPIM_LBUTTON_UP	,	m_iStartID	,	m_iEndID		,	OnLButtonUp		)

SPIMESSAGE_COMMAND( SPIM_WHEEL_UP			,										OnWheelUp		)
SPIMESSAGE_COMMAND( SPIM_WHEEL_DOWN			,										OnWheelDown		)
SPIMESSAGE_CONTROL_RANGE( SPIM_WHEEL_UP		,	m_iStartID	,	m_iEndID		,	OnWheelUp		)
SPIMESSAGE_CONTROL_RANGE( SPIM_WHEEL_DOWN	,	m_iStartID	,	m_iEndID		,	OnWheelDown		)

SPIMESSAGE_OBJ_MAP_END	( SPWindow	)


int SPWindowGuildUser::OnCursorEnter( WPARAM wParam, LPARAM lParam )
{
	int	iCursorX	=	g_pInterfaceManager->GetCursorX();
	int	iCursorY	=	g_pInterfaceManager->GetCursorY();

	if( IsCursorIn( iCursorX , iCursorY ) == FALSE )
		return 1;

	if( m_WindowState != WND_STATE_CLICK )
		m_WindowState	=	WND_STATE_HITTEST;

	if( IsShow() == false )
		return 1;

	return 1;
}

int SPWindowGuildUser::OnCursorOut( WPARAM wParam, LPARAM lParam )
{
	int	iType	=	(int)wParam;

	if( m_WindowState != WND_STATE_CLICK || iType != 0 )
		m_WindowState	=	WND_STATE_NORMAL;

	if( IsShow() == false )
		return 1;

	return 1;
}

int SPWindowGuildUser::OnCursorMove( WPARAM wParam, LPARAM lParam )
{
	int	iCursorX	=	g_pInterfaceManager->GetCursorX();
	int	iCursorY	=	g_pInterfaceManager->GetCursorY();

	if( IsCursorIn( iCursorX , iCursorY ) == FALSE )
		return 1;

	if( m_WindowState != WND_STATE_CLICK )
		m_WindowState	=	WND_STATE_HITTEST;
	return 1;
}
int SPWindowGuildUser::OnCursorEnter( unsigned int iID, WPARAM wParam , LPARAM lParam )
{
	OnCursorEnter( wParam , lParam );

	// ������ ��Ʈ�� �������� ������ ����� �Ѵ�.
	if( iID == m_iEndID)
	{
		if( m_bShowToolTip == false )
			return 1;

		SPWindow*		pToolTipWindow	=	g_pInterfaceManager->GetToolTipWindow();

		if( pToolTipWindow == NULL )
			return 1;

		if( m_pUserInfo != NULL )
		{
			if( m_pUserInfo->wServerID <= 0 )
				return 1;
		}
	}

	if( iID == m_iEndID - 4 )		// �⿩��
	{
		SPSendMessageToParent(SPIM_TOOLTIP_MOVE, (WPARAM)m_pUserInfo, 0, this) ;
	}

	return 1;
}
int SPWindowGuildUser::OnCursorOut( unsigned int iID, WPARAM wParam , LPARAM lParam )
{
	OnCursorOut( wParam , lParam );

	// ������ ��Ʈ�� �������� ������ ����� �Ѵ�.
	if( iID == m_iEndID )
	{
		if( m_bShowToolTip == false )
			return 1;

		SPWindow*		pToolTipWindow	=	g_pInterfaceManager->GetToolTipWindow();

		if( pToolTipWindow == NULL )
			return 1;

		// pToolTipWindow->SPSendMessage( SPIM_TOOLTIP_OUT , NULL , NULL );
		// ���� Popup�� �ִٸ� ����Ʈ�� Popup�� �ݾƾ� �Ѵ�. => �θ� �޽����� ���� ó���Ѵ�.
	}
	if( iID == m_iEndID - 4 )		// �⿩��
	{
		SPSendMessageToParent(SPIM_TOOLTIP_OUT, 1, 0, this) ;
	}
	return 1;
}
int SPWindowGuildUser::OnCursorMove( unsigned int iID, WPARAM wParam , LPARAM lParam )
{
	OnCursorMove( wParam , lParam );
	return 1;
}



/**
����Ʈ Ŭ�� ���� ó��
*/
int SPWindowGuildUser::OnLButtonUp( WPARAM wParam, LPARAM lParam )
{
	SPSendMessageToParent( SPIM_LBUTTON_UP , wParam , lParam , this );
	m_WindowState	=	WND_STATE_CLICK;
	return 1;
}

int SPWindowGuildUser::OnBGButtonUp( WPARAM wParam, LPARAM lParam )
{
	OnLButtonUp( wParam , lParam );

	if( m_pUserInfo->byGrade != GUILD_GRADE_01)
		SPSendMessageToParent( SPIM_GUILD_RANK_CHANGE, wParam , lParam , this );
	return 1;
}

int SPWindowGuildUser::OnLButtonUp( unsigned int iID, WPARAM wParam , LPARAM lParam )
{
	OnLButtonUp( wParam , lParam );

	// ������ ���õǸ� ���û��·� �ٲ۵� Parent�� �˷��� �Ѵ�.
	if( iID == m_iEndID )
	{
		if( m_pUserInfo->byGrade != GUILD_GRADE_01)
			SPSendMessageToParent( SPIM_GUILD_RANK_CHANGE, wParam , lParam , this );
	}
	return 1;
}


/**
�� ��ũ�� ���� ó��
*/
int SPWindowGuildUser::OnWheelUp( WPARAM wParam, LPARAM lParam )
{
	SPSendMessageToParent( SPIM_WHEEL_UP , wParam , lParam , this );
	return 1;
}

int SPWindowGuildUser::OnWheelDown( WPARAM wParam, LPARAM lParam )
{
	SPSendMessageToParent( SPIM_WHEEL_DOWN , wParam , lParam , this );
	return 1;
}

int SPWindowGuildUser::OnWheelUp( unsigned int iID, WPARAM wParam , LPARAM lParam )
{
	OnWheelUp( wParam , lParam );
	return 1;
}

int SPWindowGuildUser::OnWheelDown( unsigned int iID, WPARAM wParam , LPARAM lParam )
{
	OnWheelDown( wParam , lParam );
	return 1;
}


