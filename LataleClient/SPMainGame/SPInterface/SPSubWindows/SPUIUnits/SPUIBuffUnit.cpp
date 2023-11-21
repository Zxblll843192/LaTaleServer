// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-10-10    16:08 
//***************************************************************************

#include "SPCommon.h"
#include "SPUIUnit.h"

#include "SPResourceManager.h"

#include "SPItemCluster.h"
#include "SPGOBManager.h"
#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPGameObject.h"
#include "SPPlayer.h"

#include "SPEffect.h"
#include "SPEffectArchive.h"

#include "SPUIBuffUnit.h"

SPUIBuffUnit::SPUIBuffUnit()
{
	Init();
}

SPUIBuffUnit::~SPUIBuffUnit()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////////
//
//	�⺻ �������̽�
//

void SPUIBuffUnit::Init()
{
	SPUIUnit::Init();

	m_iTime				=	0;
	m_iTimeLength		=	0;

	for( int i = 0 ; i < TIME_LENGTH_MAX ; i++ )
	{
		m_rtTimeSrc[ i ].left		=	0;
		m_rtTimeSrc[ i ].top		=	0;
		m_rtTimeSrc[ i ].right		=	0;
		m_rtTimeSrc[ i ].bottom		=	0;

		m_ptTimePos[ i ].x			=	0;
		m_ptTimePos[ i ].y			=	0;
	}

	m_bEffect			=	FALSE;
	m_fLimitTime		=	0.5f;
	m_fAccmulateTime	=	0.0f;
}

void SPUIBuffUnit::Clear()
{
	SPUIUnit::Clear();
}

void SPUIBuffUnit::Process( float fTime )
{
	SPUIUnit::Process( fTime );

	if( m_bTimeCheck == TRUE )
		ProcessEffect( fTime );
}

void SPUIBuffUnit::Render()
{
	if( IsTexture() == FALSE || IsRender() == FALSE || g_pVideo == NULL )
		return;

	g_pVideo->Flush();

	SPUIUnit::Render();

	RenderTime();
}

BOOL SPUIBuffUnit::Use()
{
	if( SPUIUnit::Use() == FALSE )
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//	�ڱ� �ڽ� ���� �������̽�
//

SPUIUnit* SPUIBuffUnit::ClonePtr()
{
	return new SPUIBuffUnit;
}

BOOL SPUIBuffUnit::Copy( SPUIUnit** ppDestUIUnit )
{
	SPUIBuffUnit*	pUIBufUnit	=	(SPUIBuffUnit*)(*ppDestUIUnit);

	if( pUIBufUnit == NULL )
		return FALSE;

	if( SPUIUnit::Copy( ppDestUIUnit ) == FALSE )
		return FALSE;

	pUIBufUnit->SetBuffID( GetBuffID() );
	pUIBufUnit->SetTimeCheck( GetTimeCheck() );
	pUIBufUnit->SetTimeData( GetTime() );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//	���ҽ� �� �ε�
//

//BOOL SPUIBuffUnit::ReResourceLoad()
//{
//	return TRUE;
//}

//////////////////////////////////////////////////////////////////////////
//
//	���� ��Ƽ��Ƽ ����ũ ���̵� �������̽�
//

void SPUIBuffUnit::SetBuffID( unsigned int uiBuffID )
{
	m_uiBuffID	=	uiBuffID;
}

unsigned int SPUIBuffUnit::GetBuffID()
{
	return m_uiBuffID;
}

//////////////////////////////////////////////////////////////////////////
//
//	���� ����Ʈ ���� �������̽�
//

BOOL SPUIBuffUnit::SetEffect( SPEffect* pEffect )
{
	if( pEffect == NULL )
		return FALSE;

	EFFECT_TYPE		eEffect_Type	=	pEffect->GetType();

	if( eEffect_Type != ET_KEEP && eEffect_Type != ET_TOGGLE && eEffect_Type != ET_PASSIVE )
		return FALSE;

	EFFECT_BUFF*	pEffect_Buff	=	pEffect->GetBuff();

	if( pEffect_Buff == NULL )
		return FALSE;

	int iResID		=	pEffect_Buff->iIcon;
	int iResIndex	=	pEffect_Buff->iIconIndex;

	if( iResID <= 0 || iResIndex <= 0 )
		return FALSE;

	const char*	szFileName	=	g_pResourceManager->GetGlobalFileName( iResID );

	if( szFileName == NULL )
		return FALSE;

	std::string strResourceFile = szFileName;

	if( strResourceFile.empty() )
		return FALSE;

	if( SetTexture( strResourceFile.c_str() ) == FALSE )
		return FALSE;

	//	������ 0�� �ƴ� 1���� �����ϱ⿡ 1�� ���ش�!!!
	iResIndex--;

	int iIconSizeX = 25;
	int	iIconSizeY = 25;

	int iIconWidth	= m_pTexture->GetLenX() / iIconSizeX;
	int iIconYIndex = iResIndex / iIconWidth;
	int iIconXIndex = iResIndex - iIconYIndex * iIconWidth;

	RECT	rtSrc;

	rtSrc.left		=	iIconXIndex * iIconSizeX;
	rtSrc.top		=	iIconYIndex * iIconSizeY;
	rtSrc.right		=	rtSrc.left	+ iIconSizeX;
	rtSrc.bottom	=	rtSrc.top	+ iIconSizeY;

	SetRectSrc( rtSrc );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//	Ÿ�� üũ ���� �������̽�
//

void SPUIBuffUnit::SetTimeCheck( BOOL bTimeCheck )
{
	m_bTimeCheck	=	bTimeCheck;
}

BOOL SPUIBuffUnit::GetTimeCheck()
{
	return m_bTimeCheck;
}

//////////////////////////////////////////////////////////////////////////
//
//	Ÿ�� ���ҽ� ���� �����
//

void SPUIBuffUnit::SetTimeData( int iTime )
{
	m_iTime	=	iTime;

	//	5�� �̻� 60�� ������ ��츸 ǥ��
	if( m_iTime <= 5 || iTime > 3600 )
	{
		m_iTimeLength	=	0;
		return;
	}

	if( m_iTime > TIME_COUNT_MAX )
		m_iTime = TIME_COUNT_MAX;

	BUFF_FONT_COLOR	eFontColor	=	BUFF_FONT_COLOR_WHITE;

	if( m_iTime > 60 )
	{
		eFontColor	=	BUFF_FONT_COLOR_GREEN;
		iTime		=	m_iTime	/	60;
	}
	else
		eFontColor	=	BUFF_FONT_COLOR_WHITE;

	char		szBuf[_MAX_PATH]	=	{};
	std::string	strBufOneChiper;

	itoa( iTime , szBuf , 10 );

	int			iOneChiper;
	m_iTimeLength		=	(int)strlen( szBuf );

	for( int i = 0 ; i < m_iTimeLength ; i++ )
	{
		strBufOneChiper	=	szBuf[ i ];
		iOneChiper		=	atoi( strBufOneChiper.c_str() );

		m_rtTimeSrc[ i ].left		= iOneChiper			*	BUFF_FONT_WIDTH;
		m_rtTimeSrc[ i ].right		= m_rtTimeSrc[ i ].left	+	BUFF_FONT_WIDTH;
		m_rtTimeSrc[ i ].top		= (int)eFontColor		*	BUFF_FONT_HEIGHT;
		m_rtTimeSrc[ i ].bottom		= m_rtTimeSrc[ i ].top	+	BUFF_FONT_HEIGHT;

		m_ptTimePos[ i ].x	=	m_ptPos.x	+	( m_rtTimeSrc[ i ].right	-	m_rtTimeSrc[ i ].left) * i;
		m_ptTimePos[ i ].y	=	m_ptPos.y	+	m_ptSize.y	-	( m_rtTimeSrc[ i ].bottom	-	m_rtTimeSrc[ i ].top );

		if( i != 0 )
			m_ptTimePos[ i ].x	-=	2;
	}
}

int SPUIBuffUnit::GetTime()
{
	return m_iTime;
}

//////////////////////////////////////////////////////////////////////////
//
//	Ÿ�� ���� �������̽�
//

void SPUIBuffUnit::RenderTime()
{
	if( GetTimeCheck() == FALSE || m_iTimeLength <= 0 || g_pVideo == NULL || g_pItemCluster == NULL )
		return;

	SPTexture*	pNumTexture	=	g_pItemCluster->GetNumTexture();

	if( pNumTexture == NULL )
		return;

	g_pVideo->Flush();

	m_cRGBA.a	=	1.0f;

	pNumTexture->SetColor( m_cRGBA );

	for( int i = 0 ; i < m_iTimeLength ; i++ )
		pNumTexture->RenderTexture( m_ptTimePos[ i ].x , m_ptTimePos[ i ].y , &m_rtTimeSrc[ i ] );

	pNumTexture->SetColor();
}

//////////////////////////////////////////////////////////////////////////
//
//	�����̴� ȿ�� ���μ��� �������̽�
//

void SPUIBuffUnit::ProcessEffect( float fTime )
{
	m_fAccmulateTime	+=	fTime;

	if( m_fAccmulateTime >= m_fLimitTime)
	{
		m_fAccmulateTime	=	0.0f;
		m_bEffect			=	!m_bEffect;
	}

	if( m_iTime <= 10 )
		RunEffect();
}

//////////////////////////////////////////////////////////////////////////
//
//	����Ʈ ���� �������̽�
//

void SPUIBuffUnit::RunEffect()
{
	if( m_bEffect == TRUE && m_iTime > 0 )
		m_cRGBA.a	=	0.5f;
	else
		m_cRGBA.a	=	1.0f;
}
