
#include <vector>
#include <string>

#include "SPCommon.h"
#include "SPUtil.h"

#include "SPDebug.h"

#include "SPMainGameDEF.H"
#include "SPGameObjectDEF.h"

#include "SPSubGameManager.h"
#include "SPGameObject.h"
#include "SPManager.h"
#include "SPGOBManager.h"
#include "SPMouseCursor.h"
#include "SPIMEPool.h"

#include "SPResourceManager.h"

#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPGOBModelUnit.h"
#include "SPAvatarModelUnit.h"

#include "SPStage.h"
#include "SPStageManager.h"
#include "SPTerrainAttribute.h"

#include "SPGOBStatus.h"
#include "SPPlayerStatus.h"
#include "SPPlayerStatusModel.h"
#include "SPGOBCoordPhysics.h"
#include "SPPlayer.h"

#include "SPTeamArchive.h"

#include "SPWindowDEF.h"
#include "SPInterfaceManager.h"

#include "SPWindow.h"
#include "SPWindowButton.h"
#include "SPWindowStatic.h"
#include "SPWindowGauge.h"
#include "SPWindowEdit.h"
#include "SPNoticeBox.h"

//#include "PacketID.h"
#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"
#include "SockWnd.h"
#include "SPNetworkManager.h"

#include "SPTitleAttr.h"
#include "SPTitleArchive.h"
#include "SPTitleRenderDEF.h"
#include "SPTitleRenderBase.h"
#include "SPTitleManager.h"

#include "SPItemAttr.h"
#include "SPIndun.h"
#include "SPIndunManager.h"

#include "SPTeamArchive.h"

#include "SPComboBoxDEF.h"
#include "SPWindowComboBox.h"
#include "SPComboBoxItemBase.h"
#include "SPComboBoxItemTexture.h"
#include "SPComboBoxItemTitle.h"

#include "SPLocalizeManager.h"
#include "SPTimer.h"
#include "_Error_log.h"

#include "SPPvpManager.h"

#include "SPWindowStatus.h"

#define COLOR_NORMAL	D3DXCOLOR(0.19f, 0.29f, 0.38f, 1.0f) 
#define COLOR_UP		D3DXCOLOR(0.0f, 0.4f, 0.7f, 1.0f)
#define COLOR_DOWN		D3DXCOLOR(0.0f, 0.29f, 0.38f, 1.0f)
#define COLOR_NAME		D3DXCOLOR(0.56f, 0.38f, 0.38f, 1.0f)



SPWindowStatus::SPWindowStatus(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent)
: SPWindow(WNDID_STATUS, InstanceID, iX, iY, iCX, iCY, pParent)	
, m_pImageSrcBack(NULL)
, m_bIndunNotice(false)
{	
	Init();
}

SPWindowStatus::~SPWindowStatus()
{
	Clean();
}


void SPWindowStatus::Clean()
{
	SAFE_DELETE(m_pResetTimer) ;
	SPWindow::Clean();
}


void SPWindowStatus::Process(float fTime)
{	
	if( m_bMove == true) {	
		POINT ptStep;
		ptStep.x = g_pInterfaceManager->GetCursorX() - m_ptMoveStart.x;
		ptStep.y = g_pInterfaceManager->GetCursorY() - m_ptMoveStart.y;
		SetAbsCoord(ptStep.x, ptStep.y);
		RefreshRelationCoord();		
	}

	if( IsShow() && m_pResetTimer->CheckTimer(fTime) == true )
	{
		RefreshIndunResetButton() ;
	}

	std::vector<SPWindow*>::reverse_iterator RIter = m_vpChildWindow.rbegin();
	for(;RIter != m_vpChildWindow.rend(); ++RIter) {
		(*RIter)->Process(fTime);
	}
}

void SPWindowStatus::Render(float fTime)
{
	if( m_bShow == false )
		return;

	m_pComboBoxTitle->NoRender();

	//////////////////////////////////////////////////////////////////////////
	// Background
	g_pVideo->Flush();
	for(int i = 0; i < _BG_MAX_; i++)	
	{
		m_pImageSrcBack->RenderTexture(&m_rcBG[i], &m_rcSrc[i]);
	}

	SPWindow::Render(fTime);

	// AJJIYA [11/7/2005]
	// ����ó��.
	if(m_bShow == true )
	{
		m_pComboBoxTitle->Show( false );
		m_pComboBoxTitle->Render(fTime);
	}
}


void SPWindowStatus::RefreshRelationCoord()
{
	SPWindow::RefreshRelationCoord();
	ReposOwnImage();	
}


void SPWindowStatus::Show(bool bWithChild)
{	
	if( m_pResetTimer)	m_pResetTimer->Clear() ;
	SPWindow::Show(bWithChild);

	Refresh();
}

void SPWindowStatus::Hide( bool bSendServer )
{
	if(m_bShow)
		g_pInterfaceManager->RegisterSoundUnit("DATA/SOUND/SYSTEM_CLOSE_WINDOW.WAV");

	SPWindow::Hide();

	//	AJJIYA [9/8/2005]
	//	â ������ ���ؼ�!!
	g_pInterfaceManager->OrderWindowPosMove();
}


/**
WindowControl�� ���� ���� ������ �ִ� ������ �����Ѵ�.
>>> pPlayerStatus�� ������ ����
*/
void SPWindowStatus::Refresh()
{
	if(g_pGOBManager->GetLocalPlayer() == NULL)
		return; 

	SPGOBStatus* pPlayerStatus	= g_pGOBManager->GetLocalPlayer()->GetStatus();

	INT64 iValue;
	INT64 iValue2;
	FLOAT fValue;
	char szTempData[255];
	SPWindow* pWindow;
	SIZE sizeFont;
	POINT	ptTemp;

	m_pResetTimer->Clear() ;

	//////////////////////////////////////////////////////////////////////////
	// ĳ���� �� (Char Name)
	pWindow = Find(WIID_STATUS_STC_ID	,false );
	if(pWindow) pWindow->SetWindowText( pPlayerStatus->GetGOBName() );

	//////////////////////////////////////////////////////////////////////////
	// Level
	pWindow = Find(WIID_LEVEL_TEXT		,false );
	iValue = pPlayerStatus->GetStatusValue(STATUS_LV); 
	sprintf(szTempData, "%d", iValue);
	if(pWindow) pWindow->SetWindowText(szTempData);


	//1	������
	//2	�����
	//3	������
	//4	Ž����
	UINT uiClassType = pPlayerStatus->GetStatusValue(STATUS_CLASS_TYPE);
	pWindow = Find(WIID_STC_JOB_ICON	,false );
	if( pWindow ) 		
		pWindow->SPSendMessage(SPIM_SET_IMAGEINDEX, uiClassType);

	//////////////////////////////////////////////////////////////////////////
	// �� (Famous)
	pWindow = Find(WIID_STATUS_FAME_VAL			,false);
	iValue = pPlayerStatus->GetStatusValue(STATUS_FAME_BASE); 
	sprintf(szTempData, "%d", iValue);
	if(pWindow) pWindow->SetWindowText(szTempData);

	pWindow = Find(WIID_STATUS_FAME_VAL_ADJ		,false );
	iValue = pPlayerStatus->GetStatusValue(STATUS_FAME); 
	iValue2 = pPlayerStatus->GetStatusValue(STATUS_FAME_BASE); 
	if(pWindow) {	
		if( iValue == iValue2) {
			pWindow->SetWindowText(NULL);
		} else {
			sprintf(szTempData, "(%+d)", iValue - iValue2);
			pWindow->SetWindowText(szTempData);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// HP
	pWindow = Find(WIID_STATUS_HP			,true );
	iValue = pPlayerStatus->GetStatusValue(STATUS_HP); 			
	iValue2 = pPlayerStatus->GetStatusValue(STATUS_MHP);	
	sprintf(szTempData, "%d / %d", (int)iValue, (int)iValue2);
	if(pWindow) {
		pWindow->SetWindowText(szTempData);	
		sizeFont = pWindow->GetSizeText(); 
		pWindow->GetRelCoord( (int&)ptTemp.x, (int&)ptTemp.y );
		ptTemp.x += (sizeFont.cx+8);
	} else {
		sizeFont.cx = 0;
		sizeFont.cy = 0;
	}

	pWindow = Find(WIID_STATUS_HP_ADJ	,true );
	pWindow->AdjustCoord(ptTemp.x, ptTemp.y);
	iValue = pPlayerStatus->GetStatusValue(STATUS_MHP_BASE); 			
	iValue2 = pPlayerStatus->GetStatusValue(STATUS_MHP); 	
	if(pWindow) {	
		if( iValue == iValue2) {
			pWindow->SetWindowText(NULL);
		} else {
			sprintf(szTempData, "(%+d)", iValue2 - iValue);
			pWindow->SetWindowText(szTempData);
			pWindow->SetFontColor( (iValue2 - iValue >= 0) ? COLOR_UP : COLOR_DOWN ) ;
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// SP
	pWindow = Find(WIID_STATUS_SP			,true );
	iValue = pPlayerStatus->GetStatusValue(STATUS_SP); 			
	iValue2 = pPlayerStatus->GetStatusValue(STATUS_MSP); 			
	sprintf(szTempData, "%d / %d", (int)iValue, (int)iValue2);
	if(pWindow) {
		pWindow->SetWindowText(szTempData);	
		sizeFont = pWindow->GetSizeText(); 
		pWindow->GetRelCoord( (int&)ptTemp.x, (int&)ptTemp.y );
		ptTemp.x += (sizeFont.cx+8);
	} else {
		sizeFont.cx = 0;
		sizeFont.cy = 0;
	}

	pWindow = Find(WIID_STATUS_SP_ADJ	,true );
	pWindow->AdjustCoord(ptTemp.x, ptTemp.y);
	iValue = pPlayerStatus->GetStatusValue(STATUS_MSP_BASE); 			
	iValue2 = pPlayerStatus->GetStatusValue(STATUS_MSP); 
	if(pWindow) {	
		if( iValue == iValue2) {
			pWindow->SetWindowText(NULL);
		} else {
			sprintf(szTempData, "(%+d)", iValue2 - iValue);
			pWindow->SetWindowText(szTempData);
			pWindow->SetFontColor( (iValue2 - iValue >= 0) ? COLOR_UP : COLOR_DOWN ) ;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// ����ġ (XP)
	pWindow = Find(WIID_STATUS_XP			,true );
	if((pPlayerStatus->GetCHAR_EXP()->uiCurExp ) == 0) {
		fValue = 0.0f;
	} else if((pPlayerStatus->GetCHAR_EXP()->uiMaxExp - pPlayerStatus->GetCHAR_EXP()->uiMinExp) == 
		(pPlayerStatus->GetCHAR_EXP()->uiCurExp - pPlayerStatus->GetCHAR_EXP()->uiMinExp)) {
			fValue = 1.0f;
		} else {
			fValue = 
				((float)(pPlayerStatus->GetCHAR_EXP()->uiCurExp - pPlayerStatus->GetCHAR_EXP()->uiMinExp) / 
				(pPlayerStatus->GetCHAR_EXP()->uiMaxExp - pPlayerStatus->GetCHAR_EXP()->uiMinExp) * 100.0f);	
		}			
		sprintf(szTempData, "%2.2f%%", fValue);	
		if(pWindow) pWindow->SetWindowText(szTempData);


		//////////////////////////////////////////////////////////////////////////
		// �ٷ� (Strength)
		pWindow = Find(WIID_STATUS_STRENGTH			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_ATK); 				
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_STRENGTH_ADJ	,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_ATK_BASE); 			
		iValue2 = pPlayerStatus->GetStatusValue(STATUS_ATK); 
		if(pWindow) {	
			if( iValue == iValue2) {
				pWindow->SetWindowText(NULL);
			} else {
				sprintf(szTempData, "(%+d)", iValue2 - iValue);
				pWindow->SetWindowText(szTempData);
				pWindow->SetFontColor( (iValue2 - iValue >= 0) ? COLOR_UP : COLOR_DOWN ) ;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// ü�� (Defence)
		pWindow = Find(WIID_STATUS_DEFENCE			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_DEF); 				
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_DEFENCE_ADJ	,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_DEF_BASE); 			
		iValue2 = pPlayerStatus->GetStatusValue(STATUS_DEF); 
		if(pWindow) {	
			if( iValue == iValue2) {
				pWindow->SetWindowText(NULL);
			} else {
				sprintf(szTempData, "(%+d)", iValue2 - iValue);
				pWindow->SetWindowText(szTempData);
				pWindow->SetFontColor( (iValue2 - iValue >= 0) ? COLOR_UP : COLOR_DOWN ) ;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// ������ (Magic)
		pWindow = Find(WIID_STATUS_MAGIC			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_ELE); 				
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_MAGIC_ADJ	,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_ELE_BASE); 			
		iValue2 = pPlayerStatus->GetStatusValue(STATUS_ELE); 
		if(pWindow) {	
			if( iValue == iValue2) {
				pWindow->SetWindowText(NULL);
			} else {
				sprintf(szTempData, "(%+d)", iValue2 - iValue);
				pWindow->SetWindowText(szTempData);
				pWindow->SetFontColor( (iValue2 - iValue >= 0) ? COLOR_UP : COLOR_DOWN ) ;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// ��� (Luck)
		pWindow = Find(WIID_STATUS_LUCK			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_LUK); 				
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_LUCK_ADJ	,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_LUK_BASE); 			
		iValue2 = pPlayerStatus->GetStatusValue(STATUS_LUK); 
		if(pWindow) {	
			if( iValue == iValue2) {
				pWindow->SetWindowText(NULL);
			} else {
				sprintf(szTempData, "(%+d)", iValue2 - iValue);
				pWindow->SetWindowText(szTempData);
				pWindow->SetFontColor( (iValue2 - iValue >= 0) ? COLOR_UP : COLOR_DOWN ) ;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// �Ӽ�����
		pWindow = Find(WIID_STATUS_EARTH			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_EARTH);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_FIRE			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_FIRE);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_WATER			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_WATER);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_WIND			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_WIND);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		//////////////////////////////////////////////////////////////////////////
		// ���ݷ� (Attack Normal ~ Attack Heavy)
		pWindow = Find(WIID_STATUS_ATTC_RANGE			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_NORMAL_ATK);
		iValue2 = pPlayerStatus->GetStatusValue(STATUS_HEAVY_ATK);
		sprintf(szTempData, "%d ~ %d", (int)iValue, (int)iValue2);
		if(pWindow) pWindow->SetWindowText(szTempData);

		//////////////////////////////////////////////////////////////////////////
		/// ���� �߰� �ʿ�
		pWindow = Find(WIID_STATUS_ARMOR	,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_AMOR);
		sprintf(szTempData, "%d", (int)iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		//////////////////////////////////////////////////////////////////////////
		// ���� Ư����
		pWindow = Find(WIID_STATUS_REGIST_EARTH			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_RES_EARTH);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_REGIST_WIND			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_RES_WIND);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_REGIST_WATER			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_RES_WATER);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		pWindow = Find(WIID_STATUS_REGIST_FIRE			,true );
		iValue = pPlayerStatus->GetStatusValue(STATUS_RES_FIRE);
		sprintf(szTempData, "%d", iValue);
		if(pWindow) pWindow->SetWindowText(szTempData);

		// Refresh Indun Reset Button
		RefreshIndunResetButton() ;

		if( SPLocalizeManager::GetInstance()->IsEnableValue( LV_PVP ) == true )
		{
			pWindow = Find( WIID_STATUS_PVP_LV_TEXT , true );
			if( pWindow != NULL )
			{
				std::string	strPVPLv	=	SPPvpManager::GetInstance()->GetPvpGloryLevelString();
				pWindow->SetWindowText( strPVPLv.c_str() );
			}

			pWindow = Find( WIID_STATUS_PVP_FAME_TEXT , true );
			if( pWindow != NULL )
				pWindow->SetWindowText( ConvertMoneyToString( pPlayerStatus->GetStatusValueEX( STATUS_EX_PVP_GLORY ) ) );

			pWindow = Find( WIID_STATUS_PVP_POINT_TEXT , true );
			if( pWindow != NULL )
				pWindow->SetWindowText( ConvertMoneyToString( pPlayerStatus->GetStatusValue( STATUS_PVP_POINT ) ) );
		}
}



/**
	IndunReset ��ư ó��
	1) �δ��̸� Disable
	2) ��Ƽ���� �ƴ� ��Ƽ���̸� Disable
	3) ResetTimer�� �����ϸ� Disable
*/
void SPWindowStatus::RefreshIndunResetButton()
{
	// 1) �δ��̸� Disable
	if( g_pkIndunManager && g_pkIndunManager->IsInIndun() )	{
		SetIndunResetButton(0) ;
		ErrorFLogs->Error_Log("Already Indun >> Button Disable") ;
		return ;
	}

	// 2) ��Ƽ���� �ƴ� ��Ƽ���̸� Disable
	SPTeamArchive* pTeamArchive = g_pGOBManager->GetLocalPlayer()->GetTeam() ;
	if( pTeamArchive && !pTeamArchive->IsMaster() )	{
		SetIndunResetButton(0) ;
		return ;
	}

	// 3) ResetTimer�� �����ϸ� Disable
	if( m_pResetTimer->IsEnable() && !m_pResetTimer->IsExpired())	{
		SetIndunResetButton(0) ;
		return ;
	}

	if( g_pSubGameManager->GetSubGameID() != SUBGAME_ZONE || g_pSubGameManager->GetGameState() != GS_GAME ) {
		SetIndunResetButton(0) ;
		return ;
	}

	SetIndunResetButton(1) ;
	return ;
}


/**
	IndunReset ����
	iSet 0 : Disable
	iSet 1 : Enable
	iSet 2 : Unvisible
*/
void SPWindowStatus::SetIndunResetButton(int iSet)
{
	SPWindowButton* pWindow = NULL ;
	pWindow = (SPWindowButton*)Find(WIID_STATUS_INDUN_RESET) ;
	if( pWindow == NULL )		return ;
	switch(iSet)
	{
	case 0:
		pWindow->Show() ;
		pWindow->SetEnable(false) ;
		break ;
	case 1:
		pWindow->Show() ;
		pWindow->SetEnable(true) ;
		break ;
	case 2:
		pWindow->Hide() ;
		break ;
	default :
		break ;
	}
}



SPIMESSAGE_OBJ_MAP_BEGIN	( SPWindowStatus )
SPIMESSAGE_COMMAND(	SPIM_REFRESH,			OnRefresh		)
SPIMESSAGE_COMMAND( SPIM_SET_EXIT_SHOW,		OnExitHide		)

SPIMESSAGE_COMMAND( SPIM_POS_UPDATE,		OnWndPosUpdate	)
SPIMESSAGE_COMMAND( SPIM_PURGE,				OnPurge			)

SPIMESSAGE_COMMAND( SPIM_TITLE_GET_LIST,	OnTitleGetList	)
SPIMESSAGE_COMMAND( SPIM_TITLE_CHANGE,		OnTitleChange	)
SPIMESSAGE_COMMAND( SPIM_TITLE_ADD,			OnTitleAdd		)

SPIMESSAGE_COMMAND( SPIM_COMBOBOX_LISTBOX_SHOW								,	OnComboBoxListShowShow	)

SPIMESSAGE_CONTROL(	SPIM_LBUTTON_UP,				WIID_STATUS_BTN_CLOSE	,	OnHide					)

SPIMESSAGE_CONTROL(	SPIM_LBUTTON_UP,				WIID_STATUS_INDUN_RESET	,	OnIndunReset			)
SPIMESSAGE_COMMAND( SPIM_NOTICE_YES,				OnYes)
SPIMESSAGE_COMMAND( SPIM_NOTICE_NO,					OnNo)
SPIMESSAGE_COMMAND( SPGM_NOTICE_NO,					OnNo)

SPIMESSAGE_CONTROL(	SPIM_TOOLTIP_MOVE,				WIID_STATUS_COMBO		,	OnComboBoxToolTipMove	)
SPIMESSAGE_CONTROL(	SPIM_TOOLTIP_OUT,				WIID_STATUS_COMBO		,	OnComboBoxToolTipOut	)

SPIMESSAGE_CONTROL(	SPIM_COMBOBOX_CHANGE_VALUE,		WIID_STATUS_COMBO		,	OnComboBoxSelect		)

//SPIMESSAGE_CONTROL_RANGE( SPIM_LBUTTON_UP,	WIID_STATUS_BTN_BASE,	WIID_STATUS_BTN_PVP, 	OnMenuTab	)
SPIMESSAGE_OBJ_MAP_END	( SPWindow	)






/**
	Indun Reset
	Notice -> Yes / No
*/
int SPWindowStatus::OnIndunReset	( WPARAM wParam, LPARAM lParam)
{
	// �̹� �δ� �������̸� ��ư ��Ȱ��ȭ
	if( g_pkIndunManager && g_pkIndunManager->IsInIndun() )	{
		SetIndunResetButton(0) ;
		return 0 ;
	}

	// ��Ƽ���� �ƴϸ� ���� ����
	SPPlayer* pPlayer = g_pGOBManager->GetLocalPlayer() ;
	if( !pPlayer )	{
		SetIndunResetButton(0) ;
		return 0 ;
	}
	SPTeamArchive* pTeamArchive = pPlayer->GetTeam() ;
	if( !pTeamArchive )	{
		SetIndunResetButton(0) ;
		return 0 ;
	}
	if( pTeamArchive && !pTeamArchive->IsMaster() )	{
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000006));
		SetIndunResetButton(0) ;
		return 0 ;
	}

	if( g_pSubGameManager->GetSubGameID() != SUBGAME_ZONE || g_pSubGameManager->GetGameState() != GS_GAME ) {
		SetIndunResetButton(0) ;
		return 0 ;
	}

	if( g_pResourceManager->GetGlobalString(50000008) ) {
		g_pInterfaceManager->SetNotice(g_pResourceManager->GetGlobalString(50000008), this, NOTICE_TYPE_YESNO);
		m_bIndunNotice = true ;
	}
	return 1;
}

int SPWindowStatus::OnYes	( WPARAM wParam, LPARAM lParam)
{
	//////////////////////////////////////////////////////////////////////////
	// My Indun Reset
	if( m_bIndunNotice == true)
	{
		// Send Indun Reset Packet
		CPacket packet;
		packet.AddUINT32( INDUN_CS_INIT );	
		SENDPACKET(packet) ;
		m_bIndunNotice = false ;
		m_pResetTimer->Start(1, 5.0f) ;			// 5��
	}
	return 1;
}

int SPWindowStatus::OnNo	( WPARAM wParam, LPARAM lParam)
{
	if( m_bIndunNotice == true)
		m_bIndunNotice = false ;
	return 1;
}



int SPWindowStatus::OnRefresh	( WPARAM wParam, LPARAM lParam)
{		
	if( IsShow() )		Refresh();
	return 1;
}


int SPWindowStatus::OnExitHide( WPARAM wParam, LPARAM lParam)
{
	bool bShow = (bool)lParam;

	if(bShow) {
		m_pHide->Show();
	}
	else {
		m_pHide->Hide();
	}
	return 1;
}

int SPWindowStatus::OnWndPosUpdate( WPARAM wParam, LPARAM lParam )
{
	m_pComboBoxTitle->PosUpdate();
	return 1;
}

int SPWindowStatus::OnPurge( WPARAM wParam, LPARAM lParam )
{
	m_pComboBoxTitle->DelAllItem();

	return 1;
}

int SPWindowStatus::OnTitleGetList( WPARAM wParam, LPARAM lParam )
{
	m_pComboBoxTitle->DelAllItem();

	SPTitleManager*	pTitleManager	=	SPTitleManager::GetInstance();

	if( pTitleManager != NULL )
	{
		SPTitleArchive*	pTitleArchive	=	pTitleManager->GetTitleArchive();

		if( pTitleArchive != NULL )
		{
			SPTitleData*			pTitleData;
			SPComboBoxItemTitle*	pItemTitle		=	NULL;
			SPTitleRenderBase*		pTitleRender	=	NULL;
			int						iCount			=	pTitleArchive->GetCount();

			iCount			=	pTitleArchive->GetCount();

			for ( int i = 0 ; i < iCount ; ++i )
			{
				pTitleData	=	pTitleArchive->GetTitleData( i );
				OnTitleAdd( (WPARAM)pTitleData , 1 );
			}

			SPTitleData	stTitleData;
			stTitleData.m_uiTitleID	=	TITLE_ID_NOTUSE;

			OnTitleAdd( (WPARAM)&stTitleData , 1 );
		}
	}

	SPPlayer*	pLocalPlayer	=	g_pGOBManager->GetLocalPlayer();

	if( pLocalPlayer != NULL )
	{
		SPGOBStatus*	pGOBStatus	=	pLocalPlayer->GetStatus();
		SPPlayerStatus*	pLocalPlayerStatus	=	(SPPlayerStatus*)pGOBStatus;

		if( pLocalPlayerStatus != NULL )
		{
			GU_ID	ObjectGUID	=	pLocalPlayer->GetGUID();
			UINT32	uiTitleID	=	pLocalPlayerStatus->GetTitleID();
			WPARAM	wParam	=	(WPARAM)( &ObjectGUID );
			LPARAM	lParam	=	(LPARAM)( &uiTitleID );
			OnTitleChange( wParam , lParam );
		}
	}

	return 1;
}

int SPWindowStatus::OnTitleChange( WPARAM wParam, LPARAM lParam )
{
	GU_ID	ObjectGUID		=	*( (GU_ID*)wParam );
	UINT32	uiTitleID		=	*( (UINT32*)lParam );
	int		iSelectTitle	=	-1;

	SPTitleManager*	pTitleManager	=	SPTitleManager::GetInstance();

	if( pTitleManager != NULL )
	{
		BOOL			bFind		=	FALSE;

		SPTitleAttr*	pTitleAttr	=	pTitleManager->GetTitleAttr( uiTitleID );

		if( pTitleAttr != NULL )
		{
			SPTitleArchive*	pTitleArchive	=	pTitleManager->GetTitleArchive();

			if( pTitleArchive != NULL )
			{
				int iTitleCount	=	pTitleArchive->GetCount();
				SPTitleData*	pTitleData	=	NULL;

				for( int iTitle = 0 ; iTitle < iTitleCount ; ++iTitle )
				{
					pTitleData	=	pTitleArchive->GetTitleData( iTitle );

					if( pTitleData != NULL )
					{
						if( pTitleData->m_uiTitleID == uiTitleID )
						{
							bFind	=	TRUE;
							break;
						}
					}
				}
			}
		}

		if( bFind == FALSE )
		{
			iSelectTitle	=	m_pComboBoxTitle->GetItemCount() - 1;
			SPPlayer*	pLocalPlayer	=	g_pGOBManager->GetLocalPlayer();

			if( pLocalPlayer != NULL )
			{
				SPTitleData	stTitleData;
				stTitleData.m_uiTitleID	=	TITLE_ID_NOTUSE;
				pLocalPlayer->SetTitle( stTitleData );
			}
		}
	}

	SPComboBoxItemBase*		pItemBase		=	NULL;
	SPComboBoxItemTitle*	pItemTitle		=	NULL;
	SPTitleRenderBase*		pTitleRender	=	NULL;

	int	iCount	=	m_pComboBoxTitle->GetItemCount();

	for( int i = 0 ; i < iCount ; ++i )
	{
		pItemBase	=	m_pComboBoxTitle->GetItem( i );
		pItemTitle	=	(SPComboBoxItemTitle*)pItemBase;

		if( pItemTitle == NULL )
			continue;

		pTitleRender	=	pItemTitle->GetTitleBase();

		if( pTitleRender == NULL )
			continue;

		if( pTitleRender->GetID() == uiTitleID )
		{
			iSelectTitle	=	i;
			break;
		}
	}

	if( iSelectTitle != -1 )
	{
		m_pComboBoxTitle->SetSelectNumber( iSelectTitle );
		m_pComboBoxTitle->AcceptSelectValueApply();
	}

	return 1;
}

int SPWindowStatus::OnTitleAdd( WPARAM wParam, LPARAM lParam )
{
	SPTitleData*	pTitleData	=	(SPTitleData*)wParam;

	if( pTitleData != NULL )
	{
		int	iType	=	(int)lParam;

		SPTitleManager*	pTitleManager	=	SPTitleManager::GetInstance();

		if( pTitleManager != NULL )
		{
			SPTitleRenderBase*		pTitleRender	=	pTitleManager->GetCreteTitleBase( pTitleData->m_uiTitleID , true );
			SPComboBoxItemTitle*	pItemTitle		=	new	SPComboBoxItemTitle;

			if( pTitleRender != NULL && pItemTitle != NULL )
			{
				pItemTitle->SetTitleBase( pTitleRender );

				if( iType == 1 )
					m_pComboBoxTitle->AddItem( pItemTitle );
				else
					m_pComboBoxTitle->AddItemTop( pItemTitle );
			}
		}
	}

	return 1;
}

int SPWindowStatus::OnComboBoxToolTipMove( WPARAM wParam, LPARAM lParam )
{
	SPWindow*		pToolTipWindow	=	g_pInterfaceManager->GetToolTipWindow();

	if( pToolTipWindow != NULL )
	{
		UINT32	uiTitleID	=	0;
		int		iSelectNum	=	(int)wParam;

		if( iSelectNum < 0 )
			return 1;

		SPComboBoxItemBase*		pItemBase	=	m_pComboBoxTitle->GetItem( iSelectNum );
		SPComboBoxItemTitle*	pItemTitle	=	(SPComboBoxItemTitle*)pItemBase;

		if( pItemTitle != NULL )
		{
			SPTitleRenderBase*	pTitleRenderBase	=	pItemTitle->GetTitleBase();

			if( pTitleRenderBase != NULL )
			{
				uiTitleID	=	pTitleRenderBase->GetID();

				pToolTipWindow->SPSendMessage( SPIM_TOOLTIP_MOVE, (WPARAM)uiTitleID, -4 );

			}
		}
	}

	return 1;
}

int SPWindowStatus::OnComboBoxToolTipOut( WPARAM wParam, LPARAM lParam )
{
	SPWindow*		pToolTipWindow	=	g_pInterfaceManager->GetToolTipWindow();

	if( pToolTipWindow != NULL )
		pToolTipWindow->SPSendMessage( SPIM_TOOLTIP_OUT, NULL , -2 );

	return 1;
}

int SPWindowStatus::OnComboBoxSelect( WPARAM wParam, LPARAM lParam )
{
	int	iSelect	=	(int)wParam;

	SPTitleData		stTitleData;

	stTitleData.m_uiTitleID	=	iSelect;

	SPComboBoxItemBase*		pItemBase	=	m_pComboBoxTitle->GetItem( iSelect );
	SPComboBoxItemTitle*	pItemTitle	=	(SPComboBoxItemTitle*)pItemBase;

	if( pItemTitle != NULL )
	{
		SPTitleRenderBase*	pTitleRenderBase	=	pItemTitle->GetTitleBase();

		if( pTitleRenderBase != NULL )
			stTitleData.m_uiTitleID	=	pTitleRenderBase->GetID();
	}

	SPPlayer*	pLocalPlayer	=	g_pGOBManager->GetLocalPlayer();

	if( pLocalPlayer != NULL )
	{
		SPGOBStatus* pGOBStatus	=	pLocalPlayer->GetStatus();

		if( pGOBStatus != NULL )
		{
			SPPlayerStatus*	pPlayerStatus	=	(SPPlayerStatus*)pGOBStatus;

			if( pPlayerStatus != NULL )
			{
				UINT32	uiTitleID	=	pPlayerStatus->GetTitleID();

				if( uiTitleID == stTitleData.m_uiTitleID )
					return 1;
			}
		}
	}

	SPTitleManager*	pTitleManager	=	SPTitleManager::GetInstance();

	if( pTitleManager != NULL )
	{
		pTitleManager->SendChangeTitle( stTitleData );
	}

	return 1;
}

int SPWindowStatus::OnComboBoxListShowShow( WPARAM wParam, LPARAM lParam )
{
	BOOL	bDropDownShow	=	(BOOL)wParam;

	m_pComboBoxTitle->SetListBoxRender( bDropDownShow );

	return 1;
}


/**
������ ��Ʈ�� �� �̹����� �ʱ�ȭ �Ѵ�.
>>> ��� �̹����� ���Ǵ� �͵��� �̹��� ó���� ���� [2006.11.23 Duragon]
*/
void SPWindowStatus::Init()
{	
	m_RGBA = RGBA(0xFF,0xFF,0xFF,0xFF);
	m_strToolTip = "[SPWindowStatus]";
	m_bHideEnable = true;
	m_pResetTimer = new SPTimer ;
	m_pResetTimer->Clear() ;

	Init_Background() ;		///< ��� ����
	ReposOwnImage();		///< ��� ��ǥ ����

	bool	bPvp	=	SPLocalizeManager::GetInstance()->IsEnableValue( LV_PVP );

	SPWindowButton* pButton;
	SPWindowStatic* pStatic;

	//////////////////////////////////////////////////////////////////////////
	// �ݱ� ��ư
	pButton = new SPWindowButton(WIID_STATUS_BTN_CLOSE		,	239,	10,		12,		12, this);
	pButton->SetImage		("DATA/INTERFACE/CONCEPT/UI102.PNG",	247,	217);	
	pButton->SetImageHit	("DATA/INTERFACE/CONCEPT/UI102.PNG",	247,	230);	
	pButton->SetImagePush	("DATA/INTERFACE/CONCEPT/UI102.PNG",	247,	243);	
	pButton->SetImageDisable("DATA/INTERFACE/CONCEPT/UI102.PNG",	247,	256);	
	pButton->Show();
	m_pHide = pButton;
	pButton = NULL;

	//////////////////////////////////////////////////////////////////////////	
	// Base Attribute Ability Window	
	m_pComboBoxTitle	=	new SPWindowComboBox( WIID_STATUS_COMBO , 119 , 48 , 131 , 17 , this );

	m_pComboBoxTitle->SetDropDownOffset( 131 - 11 , 6 );
	m_pComboBoxTitle->SetDropDownSize( 9 , 6 );
	m_pComboBoxTitle->SetDropDownTexture( COMBOBOX_DATA_TEXTURE_ENABLE	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 65 , 77 );
	m_pComboBoxTitle->SetDropDownTexture( COMBOBOX_DATA_TEXTURE_HIT		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 65 , 77 );
	m_pComboBoxTitle->SetDropDownTexture( COMBOBOX_DATA_TEXTURE_PUSH	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 75 , 77 );

	m_pComboBoxTitle->SetScroll( TRUE );
	m_pComboBoxTitle->SetScrollOffset( 0 , 5 , 5 , 5 );

	m_pComboBoxTitle->SetScrollUpSize( 12 , 11 );
	m_pComboBoxTitle->SetScrollUpTexture( COMBOBOX_DATA_TEXTURE_ENABLE		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 460 , 458 );
	m_pComboBoxTitle->SetScrollUpTexture( COMBOBOX_DATA_TEXTURE_HIT			, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 473 , 458 );
	m_pComboBoxTitle->SetScrollUpTexture( COMBOBOX_DATA_TEXTURE_PUSH		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 486 , 458 );
	m_pComboBoxTitle->SetScrollUpTexture( COMBOBOX_DATA_TEXTURE_DISABLE		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 499 , 458 );

	m_pComboBoxTitle->SetScrollDownSize( 12 , 11 );
	m_pComboBoxTitle->SetScrollDownTexture( COMBOBOX_DATA_TEXTURE_ENABLE		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 460 , 500 );
	m_pComboBoxTitle->SetScrollDownTexture( COMBOBOX_DATA_TEXTURE_HIT		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 473 , 500 );
	m_pComboBoxTitle->SetScrollDownTexture( COMBOBOX_DATA_TEXTURE_PUSH		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 486 , 500 );
	m_pComboBoxTitle->SetScrollDownTexture( COMBOBOX_DATA_TEXTURE_DISABLE	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 499 , 500 );

	m_pComboBoxTitle->SetScrollSliderSize( 12 , 24 );
	m_pComboBoxTitle->SetScrollSliderTexture( COMBOBOX_DATA_TEXTURE_ENABLE	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 460 , 470 );
	m_pComboBoxTitle->SetScrollSliderTexture( COMBOBOX_DATA_TEXTURE_HIT		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 473 , 470 );
	m_pComboBoxTitle->SetScrollSliderTexture( COMBOBOX_DATA_TEXTURE_PUSH		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 486 , 470 );
	m_pComboBoxTitle->SetScrollSliderTexture( COMBOBOX_DATA_TEXTURE_DISABLE	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 499 , 470 );

	m_pComboBoxTitle->SetScrollSliderBGTexture( COMBOBOX_DATA_TEXTURE_ENABLE	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 460 , 496 , 472 , 498 );
	m_pComboBoxTitle->SetScrollSliderBGTexture( COMBOBOX_DATA_TEXTURE_HIT	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 473 , 496 , 485 , 498 );
	m_pComboBoxTitle->SetScrollSliderBGTexture( COMBOBOX_DATA_TEXTURE_PUSH	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 486 , 496 , 498 , 498 );
	m_pComboBoxTitle->SetScrollSliderBGTexture( COMBOBOX_DATA_TEXTURE_DISABLE, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 499 , 496 , 511 , 498 );

	m_pComboBoxTitle->SetListBoxItemMargin( 1 , 1 , 1 , 1 );
	m_pComboBoxTitle->SetShowEditBoxText( FALSE );
	m_pComboBoxTitle->SetEditBoxOffset( 0 , 1 );
	m_pComboBoxTitle->SetEditBoxSize( 131, 17 );
	m_pComboBoxTitle->SetEditBoxTexture( COMBOBOX_DATA_TEXTURE_ENABLE	, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 17 , 77 , 32 , 92 );
	m_pComboBoxTitle->SetEditBoxTexture( COMBOBOX_DATA_TEXTURE_HIT		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 33 , 77 , 48 , 92 );
	m_pComboBoxTitle->SetEditBoxTexture( COMBOBOX_DATA_TEXTURE_PUSH		, "DATA/INTERFACE/CONCEPT/UI102.PNG" , 49 , 77 , 64 , 92 );

	m_pComboBoxTitle->SetListBoxOffset( 0, 17 );
	m_pComboBoxTitle->SetListBoxTexture( "DATA/INTERFACE/CONCEPT/UI102.PNG", 1 , 77 , 16 , 92 );
	m_pComboBoxTitle->SetRenderItemCountMax( 5 );

	m_pComboBoxTitle->SetSelectValueApply( FALSE );
	m_pComboBoxTitle->SetToolTipShow( TRUE );

	m_pComboBoxTitle->SetEditBoxItem( 0 );
	m_pComboBoxTitle->SetDropDownStatus( COMBOBOX_DATA_TEXTURE_ENABLE );	
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// ����
	pStatic = new SPWindowStatic(WIID_STC_JOB_ICON, 19, 48, 16, 16, this);

	const char*	pTextureName;
	RECT*		pTextureSrc;

	for( int i = 0 ; i < CLASS_MAX ; ++i )
	{
		pTextureName	=	g_pInterfaceManager->GetClassTextureName( (CLASS_TYPE)i );
		pTextureSrc		=	g_pInterfaceManager->GetClassTextureSrc( (CLASS_TYPE)i );

		if( pTextureName != NULL && pTextureSrc != NULL )
			pStatic->SetImage( pTextureName , pTextureSrc->left , pTextureSrc->top );
	}

	pStatic = new SPWindowStatic(WIID_STATUS_STC_ID, 55, 30, 195, 15, this);
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFont( FONT_12_BOLD );
	pStatic->SetFontColor(0xFFFFFFFF);
	pStatic->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI102.PNG",	316, 343, 511, 358);


	// ����
	pStatic = new SPWindowStatic(WIID_LEVEL_TEXT, 28, 32, 22, 12, this);
	pStatic->SetFontColor( COLOR_NORMAL );
	pStatic->SetFormat( DT_LEFT );


	//////////////////////////////////////////////////////////////////////////
	// HP, SP, XP
	pStatic = new SPWindowStatic(WIID_STATUS_HP, 50, 76+6, 63, 14, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor( D3DXCOLOR(0.19f, 0.29f, 0.38f, 1.0f) );
	pStatic->SetFormat( DT_LEFT );	

	pStatic = new SPWindowStatic(WIID_STATUS_HP_ADJ, 116, 76+6, 34, 14, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor( COLOR_UP );
	pStatic->SetFormat( DT_LEFT );	

	pStatic = new SPWindowStatic(WIID_STATUS_SP, 50, 91+6, 63, 14, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor( COLOR_NORMAL );
	pStatic->SetFormat( DT_LEFT );	

	pStatic = new SPWindowStatic(WIID_STATUS_SP_ADJ, 104, 91+6, 34, 14, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor( COLOR_UP );
	pStatic->SetFormat( DT_LEFT );	

	pStatic = new SPWindowStatic(WIID_STATUS_XP, 50, 106+6, 50, 14, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor( COLOR_NORMAL );
	pStatic->SetFormat( DT_LEFT );


	//////////////////////////////////////////////////////////////////////////
	// ��
	if( bPvp == false )
		pStatic = new SPWindowStatic(WIID_STATUS_FAME_VAL, 204, 76+6, 32, 13, this);
	else
		pStatic = new SPWindowStatic(WIID_STATUS_FAME_VAL, 209, 76+6, 32, 13, this);	

	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	if( bPvp == false )
		pStatic = new SPWindowStatic(WIID_STATUS_FAME_VAL_ADJ, 204, 76+6, 40, 13, this);	
	else
		pStatic = new SPWindowStatic(WIID_STATUS_FAME_VAL_ADJ, 209, 76+6, 40, 13, this);	

	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_UP);
	pStatic->SetFormat(DT_RIGHT);


	// WIID_STATUS_INDUN_RESET
	if( SPLocalizeManager::GetInstance()->IsEnableValue(LV_INDUN) )	{
		if( bPvp == false )
			pButton = new SPWindowButton(WIID_STATUS_INDUN_RESET		,	174,	109,	76,	17, this);
		else
			pButton = new SPWindowButton(WIID_STATUS_INDUN_RESET		,	174,	368,	76,	17, this);

		pButton->SetImage		("DATA/INTERFACE/CONCEPT/UI106.PNG",	309,	440);	
		pButton->SetImageHit	("DATA/INTERFACE/CONCEPT/UI106.PNG",	309,	458);	
		pButton->SetImagePush	("DATA/INTERFACE/CONCEPT/UI106.PNG",	309,	476);	
		pButton->SetImageDisable("DATA/INTERFACE/CONCEPT/UI106.PNG",	309,	494);	
	}

	//////////////////////////////////////////////////////////////////////////
	// �ٷ�, ü��, ������, ���
	pStatic = new SPWindowStatic(WIID_STATUS_STRENGTH, 57, 134+6, 26, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_STRENGTH_ADJ, 84, 134+6, 42, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_UP);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_DEFENCE, 57, 150+6, 26, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_DEFENCE_ADJ, 84, 150+6, 42, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_UP);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_MAGIC, 57, 166+6, 26, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_MAGIC_ADJ, 84, 166+6, 42, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_UP);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_LUCK, 57, 182+6, 26, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_LUCK_ADJ, 84, 182+6, 42, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_UP);
	pStatic->SetFormat(DT_LEFT);

	//////////////////////////////////////////////////////////////////////////
	// �Ӽ���
	pStatic = new SPWindowStatic(WIID_STATUS_EARTH, 209, 134+6, 23, 12, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_FIRE, 209, 150+6, 23, 12, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_WATER, 209, 166+6, 23, 12, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_WIND, 209, 182+6, 23, 12, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	//////////////////////////////////////////////////////////////////////////
	// ���ݷ�, ����
	pStatic = new SPWindowStatic(WIID_STATUS_ATTC_RANGE, 57, 219, 65, 12, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_CENTER);

	pStatic = new SPWindowStatic(WIID_STATUS_ARMOR, 68, 234, 33, 13, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	//////////////////////////////////////////////////////////////////////////
	// ����
	//#define		WIID_STATUS_REGIST_EARTH				(WIID_STATUS	+	141 )
	//#define		WIID_STATUS_REGIST_FIRE					(WIID_STATUS	+	142 )
	//#define		WIID_STATUS_REGIST_WATER				(WIID_STATUS	+	143 )
	//#define		WIID_STATUS_REGIST_WIND					(WIID_STATUS	+	144 )
	pStatic = new SPWindowStatic(WIID_STATUS_REGIST_EARTH, 215, 219, 27, 11, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_REGIST_FIRE, 215, 235, 27, 11, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_REGIST_WATER, 215, 251, 27, 11, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	pStatic = new SPWindowStatic(WIID_STATUS_REGIST_WIND, 215, 267, 27, 11, this);	
	pStatic->SetWindowType(WND_TYPE_TOPBASE);
	pStatic->SetFontColor(COLOR_NORMAL);
	pStatic->SetFormat(DT_LEFT);

	if( bPvp == true )
	{
		SPWindowStatic* pStaticPVP	=	new SPWindowStatic( WIID_STATUS_PVP_PANEL , 10 , 288 , 240 , 75 , this );
		pStaticPVP->SetWindowType( WND_TYPE_LEFTBASE );
		pStaticPVP->SetImageNormalHead( "DATA/INTERFACE/CONCEPT/UI107.PNG" , 225 , 129 , 228 , 204 );
		pStaticPVP->SetImageNormalBody( "DATA/INTERFACE/CONCEPT/UI107.PNG" , 230 , 129 , 232 , 204 );
		pStaticPVP->SetImageNormalTail( "DATA/INTERFACE/CONCEPT/UI107.PNG" , 234 , 129 , 237 , 204 );

		pStatic	=	new SPWindowStatic( WIID_STATUS_PVP_LV_ICON , 12 - 10 , 300 - 288 , 75 , 13 , pStaticPVP );
		pStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI107.PNG" ,	131 , 191 );

		pStatic	=	new SPWindowStatic( WIID_STATUS_PVP_FAME_ICON , 12 - 10 , 321 - 288 , 75 , 13 , pStaticPVP );
		pStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI107.PNG" ,	131 , 177 );

		pStatic	=	new SPWindowStatic( WIID_STATUS_PVP_POINT_ICON , 12 - 10 , 342 - 288 , 75 , 13 , pStaticPVP );
		pStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI107.PNG" ,	131 , 163 );

		pStatic	=	new SPWindowStatic( WIID_STATUS_PVP_LV_TEXT , 92 - 10 , 300 - 288 , 149 , 13 , pStaticPVP );
		pStatic->SetFontColor( D3DCOLOR_ARGB( 255 ,  48 , 74 , 97 ) );
		pStatic->SetFormat( DT_LEFT | DT_VCENTER );

		pStatic	=	new SPWindowStatic( WIID_STATUS_PVP_FAME_TEXT , 92 - 10 , 321 - 288 , 149 , 13 , pStaticPVP );
		pStatic->SetFontColor( D3DCOLOR_ARGB( 255 ,  48 , 74 , 97 ) );
		pStatic->SetFormat( DT_LEFT | DT_VCENTER );

		pStatic	=	new SPWindowStatic( WIID_STATUS_PVP_POINT_TEXT , 92 - 10 , 342 - 288 , 149 , 13 , pStaticPVP );
		pStatic->SetFontColor( D3DCOLOR_ARGB( 255 ,  48 , 74 , 97 ) );
		pStatic->SetFormat( DT_LEFT | DT_VCENTER );
	}
}


/**
��� �̹��� ���� �� ���� ����
�̹����� ���Ǵ� �͵��� ������ �и��ؼ� �ֵ��� �Ѵ�. [2006.11.23 Duragon]
*/
void SPWindowStatus::Init_Background()
{
	bool	bPvp	=	SPLocalizeManager::GetInstance()->IsEnableValue( LV_PVP );

	//////////////////////////////////////////////////////////////////////////
	// Background 
	g_pVideo->GetTextureMgr()->LoadTexture( "DATA/INTERFACE/CONCEPT/UI102.PNG" , &m_pImageSrcBack);		///< ���

	SetRect(&m_rcSrc[0],	1, 1, 261, 5);		///< ��� ��
	SetRect(&m_rcSrc[1],	1, 7, 261, 9);		///< ��� ��
	SetRect(&m_rcSrc[2],	1, 11, 261, 15);	///< ��� ��

	SetRect(&m_rcSrc[3],	2, 346, 32, 366);		///< Ÿ��Ʋ �̹���
	SetRect(&m_rcSrc[4],	1, 367, 68, 382);		///< Ÿ��Ʋ ���� �̹���
	SetRect(&m_rcSrc[5],	349, 312, 355, 318);	///<�ʷϹ��
	SetRect(&m_rcSrc[6],	435, 359, 460, 367);	///<���� ��� 
	SetRect(&m_rcSrc[7],	234, 30, 279, 45);		///<������� �̹���
	SetRect(&m_rcSrc[8],	204, 251, 229, 268);	///<Ÿ��Ʋ ������

	//////////////////////////////////////////////////////////////////////////
	// �߰� ���
	SetRect(&m_rcSrc[9],	349, 329, 355, 330);	///<�߰���� ��
	SetRect(&m_rcSrc[10],	349, 329, 355, 330);	///<�߰���� ��
	SetRect(&m_rcSrc[11],	349, 321, 355, 327);	///<�߰���� ��

	//////////////////////////////////////////////////////////////////////////
	// �߰� ����
	SetRect(&m_rcSrc[12],	359, 264, 392, 311);	///<HP,SP,XP ������

	if( bPvp == false )
		SetRect(&m_rcSrc[13],	359, 312, 392, 329);	///<�� ������
	else
		SetRect(&m_rcSrc[13],	163, 189, 208, 206);	///<�� ������

	SetRect(&m_rcSrc[14],	274, 188, 392, 263);	///<�ٷ�,ü��,������,��� �׵θ�
	SetRect(&m_rcSrc[15],	393, 188, 511, 263);	///<��,��,��,�ٶ� �׵θ�
	SetRect(&m_rcSrc[16],	393, 264, 511, 306);	///<���ݷ�,���� �׵θ�
	SetRect(&m_rcSrc[17],	393, 188, 511, 263);	///<���׼Ӽ� �׵θ�

	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	SetRect(&m_rcSrc[18],	348, 331, 358, 342);	///<����
	SetRect(&m_rcSrc[19],	348, 331, 358, 342);	///<����
	SetRect(&m_rcSrc[20],	348, 331, 358, 342);	///<����
	SetRect(&m_rcSrc[21],	348, 331, 358, 342);	///<����

	SetRect(&m_rcSrc[22],	204, 238, 230, 249);	///<����
	SetRect(&m_rcSrc[23],	204, 238, 230, 249);	///<����
	SetRect(&m_rcSrc[24],	204, 238, 230, 249);	///<����
	SetRect(&m_rcSrc[25],	204, 238, 230, 249);	///<����

}

/**
�������� ������ ��ǥ�� �̿��ؼ� ����� �̹����� ��ǥ�� �����Ѵ�.
*/
void SPWindowStatus::ReposOwnImage()
{
	COUNTRY_TYPE eLocale = SPLocalizeManager::GetInstance()->GetCountryType();
	bool	bPvp	=	SPLocalizeManager::GetInstance()->IsEnableValue( LV_PVP );
	//////////////////////////////////////////////////////////////////////////
	// ��� ���
	SetRect(&m_rcBG[0], m_iAX,		m_iAY,		m_iAX+260,	m_iAY+4);		///< ��� ��

	if( bPvp == false )
	{
		SetRect(&m_rcBG[1], m_iAX,		m_iAY+4,	m_iAX+260,	m_iAY+299);		///< ��� ��
		SetRect(&m_rcBG[2], m_iAX,		m_iAY+299,	m_iAX+260,	m_iAY+303);		///< ��� ��
	}
	else
	{
		SetRect(&m_rcBG[1], m_iAX,		m_iAY+4,	m_iAX+260,	m_iAY+4+393);		///< ��� ��
		SetRect(&m_rcBG[2], m_iAX,		m_iAY+397,	m_iAX+260,	m_iAY+397+4);		///< ��� ��
	}

	SetRect(&m_rcBG[3],	m_iAX+7,	m_iAY+6,	m_iAX+30+7,		m_iAY+20+6 );		///< Ÿ��Ʋ �̹���
	SetRect(&m_rcBG[4],	m_iAX+42,	m_iAY+8,	m_iAX+67+42,	m_iAY+15+8 );		///< Ÿ��Ʋ ���� �̹���
	SetRect(&m_rcBG[5], m_iAX+2,	m_iAY+26,	m_iAX+256+2,	m_iAY+44+26 );		///<�ʷϹ��
	SetRect(&m_rcBG[6], m_iAX+15,	m_iAY+58,	m_iAX+25+15,	m_iAY+8+58 );		///<���� ��� 
	SetRect(&m_rcBG[7], m_iAX+6,	m_iAY+30,	m_iAX+45+6,		m_iAY+15+30 );		///<������� �̹���
	SetRect(&m_rcBG[8], m_iAX+55,	m_iAY+49,	m_iAX+25+55,	m_iAY+17+49 );		///<Ÿ��Ʋ ������

	//////////////////////////////////////////////////////////////////////////
	// �߰� ���
	SetRect(&m_rcBG[9],	 m_iAX+2,	m_iAY+70,	m_iAX+256+2, m_iAY+1+70 );		///<�߰���� ��

	if( bPvp == false )
	{
		SetRect(&m_rcBG[10], m_iAX+2,	m_iAY+292,	m_iAX+256+2, m_iAY+1+292 );		///<�߰���� ��
		SetRect(&m_rcBG[11], m_iAX+2,	m_iAY+71,	m_iAX+256+2, m_iAY+221+71 );		///<�߰���� ��
	}
	else
	{
		SetRect(&m_rcBG[10], m_iAX+2,	m_iAY+390,	m_iAX+2+256, m_iAY+390+1 );		///<�߰���� ��
		SetRect(&m_rcBG[11], m_iAX+2,	m_iAY+71,	m_iAX+2+256, m_iAY+71+319 );		///<�߰���� ��
	}

	SetRect(&m_rcBG[12], m_iAX+10,	m_iAY+79,	m_iAX+33+10,	m_iAY+47+79 );		///<HP,SP,XP ������
	
	if( bPvp == false )
		SetRect(&m_rcBG[13], m_iAX+163,	m_iAY+79,	m_iAX+33+163,	m_iAY+17+79 );		///<�� ������
	else
		SetRect(&m_rcBG[13], m_iAX+163,	m_iAY+79,	m_iAX+45+163,	m_iAY+17+79 );		///<�� ������

	SetRect(&m_rcBG[14], m_iAX+10,	m_iAY+130,	m_iAX+118+10,	m_iAY+75+130 );		///<�ٷ�,ü��,������,��� �׵θ�
	SetRect(&m_rcBG[15], m_iAX+132,	m_iAY+130,	m_iAX+118+132,	m_iAY+75+130 );		///<��,��,��,�ٶ� �׵θ�
	SetRect(&m_rcBG[16], m_iAX+10,	m_iAY+209,	m_iAX+118+10,	m_iAY+42+209);		///<���ݷ�,���� �׵θ�
	SetRect(&m_rcBG[17], m_iAX+132,	m_iAY+209,	m_iAX+118+132,	m_iAY+75+209);		///<���Ӽ� �׵θ�

	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	SetRect(&m_rcBG[18],	m_iAX+148, m_iAY+223, m_iAX+148+10, m_iAY+223+11);	///<����
	SetRect(&m_rcBG[19],	m_iAX+148, m_iAY+239, m_iAX+148+10, m_iAY+239+11);	///<����
	SetRect(&m_rcBG[20],	m_iAX+148, m_iAY+255, m_iAX+148+10, m_iAY+255+11);	///<����
	SetRect(&m_rcBG[21],	m_iAX+148, m_iAY+271, m_iAX+148+10, m_iAY+271+11);	///<����

	SetRect(&m_rcBG[22],	m_iAX+175, m_iAY+219, m_iAX+175+26, m_iAY+219+11);	///<����
	SetRect(&m_rcBG[23],	m_iAX+175, m_iAY+235, m_iAX+175+26, m_iAY+235+11);	///<����
	SetRect(&m_rcBG[24],	m_iAX+175, m_iAY+251, m_iAX+175+26, m_iAY+251+11);	///<����
	// �Ϻ��� �ٶ����� -> ǳ����
	if( CT_JAPAN == eLocale || CT_CHINA == eLocale )
		SetRect(&m_rcBG[25],	m_iAX+175, m_iAY+267, m_iAX+175+26, m_iAY+267+11);	///<ǳ����
	else
		SetRect(&m_rcBG[25],	m_iAX+187, m_iAY+267, m_iAX+187+26, m_iAY+267+11);	///<�ٶ�����
}

