// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-5-10    18:08 
//***************************************************************************

#pragma once

#include <string>

class SPWindowMiniMapToolTip {
public:
	SPWindowMiniMapToolTip();
	~SPWindowMiniMapToolTip();

	//	��ǥ�� ���� ��ǥ
	void	Init( const char* pStrResource = NULL );

	void	Render();

	void	SetToolTipText( const char* pStrToolTip );
	void	SetPosX( int iPosX )	{	m_iPosX = iPosX;	}
	void	SetPosY( int iPosY )	{	m_iPosY = iPosY;	}
	void	Show()					{	m_bShow = true;		}
	void	Hide()					{	m_bShow = false;	}

protected:

	void	Destory			();

	bool	SetImage		( const char* szImagePath );

	void	GetToolTipRect	( RECT& rtTooTip );

	SPTexture*		m_pToolTipImage;

	RECT			m_rtImageSrcLeft;
	RECT			m_rtImageSrcMiddle;
	RECT			m_rtImageSrcRight;
	
	RECT			m_rtImageDestLeft;
	RECT			m_rtImageDestMiddle;
	RECT			m_rtImageDestRight;

	D3DXCOLOR		m_RGBA;
	bool			m_bShow;

	int				m_iPosX;		//	���� ��ǥ X
	int				m_iPosY;		//	���� ��ǥ Y
	std::string		m_strToolTip;	//	���� ����
	D3DXCOLOR		m_FontColor;	//	��Ʈ ����
	bool			m_bFontShadow;	//	��Ʈ �׸���

};
