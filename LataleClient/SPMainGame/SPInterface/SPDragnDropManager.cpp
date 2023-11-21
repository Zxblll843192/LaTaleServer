// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-7-1    10:23 
//***************************************************************************

#include "SPCommon.h"

#include "SPWindowDEF.h"
#include "SPWindow.h"
#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"

#include "SPUIUnit.h"

#include "SPDragnDropManager.h"

SPDragnDropManager::SPDragnDropManager()
{
	Init();
}

SPDragnDropManager::~SPDragnDropManager()
{
}

//////////////////////////////////////////////////////////////////////////
//
//	�̱��� �������̽�
//

SPDragnDropManager* SPDragnDropManager::m_pDragnDropManagerInstance	=	NULL;

SPDragnDropManager* SPDragnDropManager::GetInstance()
{
	if( m_pDragnDropManagerInstance	==	NULL )
		m_pDragnDropManagerInstance	=	new	SPDragnDropManager;

	return	m_pDragnDropManagerInstance;
}

void SPDragnDropManager::DelInstance()
{
	delete m_pDragnDropManagerInstance;
}

//////////////////////////////////////////////////////////////////////////
//
//	�ʱ�ȭ
//

void SPDragnDropManager::Init()
{
	m_eStatus			=	DRAGNDROP_STATUS_ENABLE;
	m_pWindow			=	NULL;
	m_pUIUnit			=	NULL;
}

//////////////////////////////////////////////////////////////////////////
//
//	�巡�� ����
//

void SPDragnDropManager::End()
{
	if( IsDragging() == FALSE )
		return;

	if( m_pUIUnit == NULL || m_pWindow == NULL )
		return;

	g_pInterfaceManager->ClearMouse();

	m_pUIUnit->DelStatus( SPUIUnit::STATUS_UI_UNIT_DRAGNDROP );
	m_pWindow->SPSendMessage( SPIM_DRAGNDROP_END , -1 );

	Init();
}

//////////////////////////////////////////////////////////////////////////
//
//	�Ŵ��� ���� �������̽�
//

BOOL SPDragnDropManager::IsDragging()
{
	if( m_eStatus == DRAGNDROP_STATUS_ISDRAGGING )
		return TRUE;

	return FALSE;
}

BOOL SPDragnDropManager::IsEnable()
{
	if( m_eStatus == DRAGNDROP_STATUS_ENABLE )
		return TRUE;

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//
//	�巡�׾� ����� ����ϱ� ���� ���� �������̽�
//

BOOL SPDragnDropManager::Set( SPWindow* pWindow , SPUIUnit* pUIUnit )
{
	BOOL	bResult	=	TRUE;

	if( IsEnable() == FALSE || pWindow == NULL || pUIUnit == NULL || pUIUnit->GetStatus( SPUIUnit::STATUS_UI_UNIT_NO_DRAGNDROP ) == TRUE )
		return FALSE;

	bResult	&=	SetSPWindow	( pWindow );
	bResult	&=	SetUIUnit	( pUIUnit );

	if( bResult == TRUE )
	{
		m_eStatus	=	DRAGNDROP_STATUS_ISDRAGGING;
		g_pInterfaceManager->SetMousePickup( GetUIUnit()->GetTexture() , GetUIUnit()->GetRectSrc().left , GetUIUnit()->GetRectSrc().top );
		pUIUnit->AddStatus( SPUIUnit::STATUS_UI_UNIT_DRAGNDROP );
	}
	else
	{
		Init();
	}

	return bResult;
}

BOOL SPDragnDropManager::Get( SPWindow** ppWindow , SPUIUnit** ppUIUnit )
{
	if( IsDragging() == FALSE )
		return FALSE;

	*ppWindow	=	GetSPWindow();
	*ppUIUnit	=	GetUIUnit();

	if( *ppWindow == NULL || *ppUIUnit == NULL )
		return FALSE;

	g_pInterfaceManager->ClearMouse();

	m_pUIUnit->DelStatus( SPUIUnit::STATUS_UI_UNIT_DRAGNDROP );
	m_pWindow->SPSendMessage( SPIM_DRAGNDROP_END );

	Init();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//	�巡�׾� ����� ����ϱ� ���� ���� �������̽�
//

BOOL SPDragnDropManager::SetSPWindow( SPWindow* pWindow )
{
	if( pWindow == NULL )
		return FALSE;

	m_pWindow	=	pWindow;

	return TRUE;
}

BOOL SPDragnDropManager::SetUIUnit( SPUIUnit* pUIUnit )
{
	if( pUIUnit == NULL )
		return FALSE;

	m_pUIUnit	=	pUIUnit;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//	�巡�׾� ����� ����ϱ� ���� �������� �������̽�
//

SPWindow* SPDragnDropManager::GetSPWindow()
{
	return m_pWindow;
}

SPUIUnit* SPDragnDropManager::GetUIUnit()
{
	return m_pUIUnit;
}
