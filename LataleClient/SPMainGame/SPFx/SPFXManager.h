// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPFXManager
// Comment     : 
// Creation    : metalgeni 2004-08-23 ���� 2:56:36
//***************************************************************************


#pragma once 

#ifdef _DEFINE_DEPRECATED_HASH_CLASSES
#undef _DEFINE_DEPRECATED_HASH_CLASSES
#define _DEFINE_DEPRECATED_HASH_CLASSES 0	
#endif

#include <hash_map>

enum MOTION_FX_TYPE
{
	MOTION_FX_NULL	,
	MOTION_FX_PC	,
	MOTION_FX_MOB	,
	MOTION_FX_NPC	,
};

class SPFXUnit;
class SPFXGroupUnit;
class SPFXParticleObject;

enum SP_FX_UNIT;

#include "SPFXFactory.h"

class SPFXManager : public SPManager
{
public:
	SPFXManager							();
	virtual ~SPFXManager				();

	virtual bool	Init				();
	virtual void	Clean				();
	virtual void	Process				( float fTime );
	virtual	void	Render				( float fTime );
	virtual int		SPPerformMessage	( UINT msg , WPARAM wparam = 0 , LPARAM lParam = 0 );

	SPFXModel*		GetFXModel			( UINT uiFXID );
	SPFXGroup*		GetFXGroup			( SPID_FX_GROUP eFXGroupID );
	SPFXGroup*		GetFXGroup			( unsigned int uiAniIndex , CLASS_ID eClassID );
	SPFXGroup*		GetFXGroupNotDel	( unsigned int uiAniIndex , CLASS_ID eClassID );

	bool			LoadExtraFXLDT		( const char* pszFXModel , const char* pszFXGroup , const char* pszFXPath );
	void			ClearExtraFX		();

	SPFXUnit*		CreateFXUnit		( SP_FX_UNIT eFXUnitType );

	SPFXGroup*		GetFXGroup			( UINT uiFXGroupID , GU_ID tID , bool bEnumType , bool bNotDel );

	//////////////////////////////////////////////////////////////////////////

	bool				CreateFXGroupUnitBuffer			( int iCount );
	bool				DeleteFXGroupUnitBuffer			( int iCount );
	SPFXGroupUnit*		GetFXGroupUnitBuffer			( bool bCreate = true );

	//////////////////////////////////////////////////////////////////////////

	bool				CreateFXUnitBuffer				( SP_FX_UNIT eFXUnitType , int iCount );
	bool				DeleteFXUnitBuffer				( SP_FX_UNIT eFXUnitType , int iCount );
	SPFXUnit*			GetFXUnitBuffer					( SP_FX_UNIT eFXUnitType , bool bCreate = true );

	//////////////////////////////////////////////////////////////////////////

	bool				CreateFXParticleObjectBuffer	( int iCount );
	bool				DeleteFXParticleObjectBuffer	( int iCount );
	SPFXParticleObject*	GetFXParticleObjectBuffer		( bool bCreate = true );

	//////////////////////////////////////////////////////////////////////////

private:

	bool			LoadFXList			( const char* pszFXList );
	bool			LoadFXGroup			( const char* pszFXGroup , stdext::hash_map<SPID_FX_GROUP, SPFXGroup*>& hmFXGroup , const char* pszFXPath );
	bool			LoadFXModel			( const char* pszFXModel , std::map<UINT,SPFXModel*>& mpFXLocalModel , const char* pszFXPath );
	bool			LoadMotionFX		( const char* pStrFileName , stdext::hash_map<unsigned int, unsigned int>&	hmMotionFX , MOTION_FX_TYPE eMotionType );

	SPFXGroup*		GetPCFXGroup		( unsigned int uiAniIndex );
	SPFXGroup*		GetPCFXGroupNotDel	( unsigned int uiAniIndex );

	SPFXGroup*		GetMOBFXGroup		( unsigned int uiAniIndex , unsigned int uiClassID );
	SPFXGroup*		GetNPCFXGroup		( unsigned int uiAniIndex , unsigned int uiClassID );

	//
	// AJJIYA [5/17/2005]
	// LDT���� Ŭ���� ���̵� �����ؼ� ���� ID ������ �����ش�.
	unsigned int	GetLDTMOBID			( unsigned int uiRecord , unsigned int uiField );
	unsigned int	GetLDTNPCID			( unsigned int uiRecord , unsigned int uiField );

	//
	// AJJIYA [5/17/2005]
	// Ŭ���� ���̵� �޾Ƽ� �ؽ��ʿ��� Ű�� ��ȯ���ش�.
	unsigned int	GetHashMapMOBID		( unsigned int uiClassID , unsigned int uiAniIndex );
	unsigned int	GetHashMapNPCID		( unsigned int uiClassID , unsigned int uiAniIndex );

	//////////////////////////////////////////////////////////////////////////
	//
	//	���� ����
	//

	stdext::hash_map	<SPID_FX_GROUP, SPFXGroup*>		m_hmFXGroup;
	std::map			<UINT, SPFXModel*>				m_mpFXLocalModel;

	//////////////////////////////////////////////////////////////////////////

	stdext::hash_map	<SPID_FX_GROUP, SPFXGroup*>		m_hmExtraFXGroup;
	std::map			<UINT, SPFXModel*>				m_mpExtraFXLocalModel;

	//	LDT���� ĳ���� ���ϸ��̼� ���¿� ���� FXGroup�� ������ ���´�.	���°� �ٲ� ������ ����!
	stdext::hash_map	<unsigned int, unsigned int>	m_hmMotionFX_PC;
	//	LDT���� ĳ���� ���ϸ��̼� ���¿� ���� FXGroup�� ������ ���´�.	���°� �ٲ� �������� �ʴ´�. ������ ������ �����̴�.
	stdext::hash_map	<unsigned int, unsigned int>	m_hmMotionFX_PC_NotDel;

	//	LDT���� ���� �������� ���ϸ��̼� ������ FXGroup�� ������ ���´�.
	stdext::hash_map	<unsigned int, unsigned int>	m_hmMotionFX_MOB;
	//	LDT���� NPC ���ϸ��̼� ���¿� ���� FXGroup�� ������ ���´�.
	stdext::hash_map	<unsigned int, unsigned int>	m_hmMotionFX_NPC;

	//////////////////////////////////////////////////////////////////////////

	SPFXFactory< SPFXUnit* , SP_FX_UNIT >				m_FXUnitFactory;	//	FXUnit	Factory

	//////////////////////////////////////////////////////////////////////////

	typedef	std::vector	< SPFXGroupUnit* >				STD_VECTOR_FX_GROUP_UNIT;

	STD_VECTOR_FX_GROUP_UNIT							m_vpFXGroupUnit_Pool;	//	FXGroupUnit Memory Buffer
	int													m_iFXGroupUnitCountMax;	//	FXGroupUnit Memory Buffer Max Count

	STD_VECTOR_SPFXUNIT									m_vpFXUnit_Pool[ FXUNIT_COUNT ];
	int													m_iFXUnitCountMax[ FXUNIT_COUNT ];

	STD_VECTOR_SPFXPARTICLEOBJECT						m_vpFXParticleObject_Pool;
	int													m_iFXParticleObjectCountMax;

};

extern SPFXManager* g_pFXManager;
