// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : LataleServerTest�� ���� �Ƚ�Ŵ..... AJJIYA
// Creation    : AJJIYA 2005-11-15    14:33 
//***************************************************************************

#pragma once

#include "./NPGameGuard/NPGameLib.h"

// 2008.05.26 dhpark ������ ����
#include "SecurityDefines.h"

class SPGameGuard
{
private:
	SPGameGuard					();

	static	SPGameGuard*		m_pGameGuardInstance;

	CNPGameLib*					m_pNPGameLib;

public:
	virtual ~SPGameGuard		();

	static	SPGameGuard*		GetInstance(void);
	static	void				DelInstance(void);

	BOOL	Init				();

	void	AfterCreateWindow	();

	void	SetHwnd				( HWND hWnd );
	void	SetUserID			( const char* szUserID );
	//void	SetAuth				( GG_AUTH_DATA& stAuthData );
	void	Auth				(SECURITY_PACKDATA* pPackData);	// 2008.05.26 dhpark ������ ����

	LPCSTR	GetInfo				();

};
