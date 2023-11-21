// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-9-29    11:32 
//***************************************************************************

#include "SPCommon.h"
#include "SPUIUnit.h"

#include "SPMonsterModelUnitDef.h"
#include "SPMOBCluster.h"

#include "SPUIGOBUnit.h"

SPUIGOBUnit::SPUIGOBUnit()
{
	Init();
}

SPUIGOBUnit::~SPUIGOBUnit()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////////
//
//	�⺻ �������̽�
//

void SPUIGOBUnit::Init()
{
	SPUIUnit::Init();

	m_eClassID	=	CLASS_ID_NULL;
}

void SPUIGOBUnit::Clear()
{
	SPUIUnit::Clear();
}

void SPUIGOBUnit::Process( float fTime )
{
	SPUIUnit::Process( fTime );
}

void SPUIGOBUnit::Render()
{
	if( IsTexture() == FALSE || IsRender() == FALSE || g_pVideo == NULL )
		return;

	g_pVideo->Flush();

	SPUIUnit::Render();

	g_pVideo->Flush();
}

BOOL SPUIGOBUnit::Use()
{
	if( SPUIUnit::Use() == FALSE )
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//	Class ���̵� �������̽�
//

void SPUIGOBUnit::SetClassID( CLASS_ID eClassID )
{
	m_eClassID	=	eClassID;
}

CLASS_ID SPUIGOBUnit::GetClassID()
{
	return m_eClassID;
}

//////////////////////////////////////////////////////////////////////////
//
//	�ڱ� �ڽ� ���� �������̽�
//

SPUIUnit* SPUIGOBUnit::ClonePtr()
{
	return new SPUIGOBUnit;
}

BOOL SPUIGOBUnit::Copy( SPUIUnit** ppDestUIUnit )
{
	SPUIGOBUnit*	pUIGOBUnit	=	(SPUIGOBUnit*)(*ppDestUIUnit);

	if( pUIGOBUnit == NULL )
		return FALSE;

	if( SPUIUnit::Copy( ppDestUIUnit ) == FALSE )
		return FALSE;

	pUIGOBUnit->SetClassID( GetClassID() );
	pUIGOBUnit->SetName( GetName() );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//	���̵�� ���ҽ� �� �ε�
//

BOOL SPUIGOBUnit::ReResourceLoad()
{
	SPMOBUIInfo*	pMOBUIInfo	=	g_pMOBCluster->GetMOBUIInfo( m_eClassID );

	if( pMOBUIInfo == NULL )
		return FALSE;

	SetName( pMOBUIInfo->m_strMOBName.c_str() );

	return SetResource( pMOBUIInfo->m_iMOBIcon , pMOBUIInfo->m_iMOBIconIndex );
}

//////////////////////////////////////////////////////////////////////////
//
//	GOB �̸� �������̽�
//

void SPUIGOBUnit::SetName( const char* pstrName )
{
	m_strName	=	pstrName;
}

const char* SPUIGOBUnit::GetName()
{
	return m_strName.c_str();
}
