// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-08 ���� 10:26:19
//***************************************************************************


#pragma once

#include "SPWindowListDEF.h"

struct LIST_ICON
{
	std::string					m_strImageName;			//	�ؽ�ó �̸�
	RECT						m_rcSrc;				//	�ؽ�ó ���� ����

	SPTexture*					m_pImage;				//	������ �ؽ�ó
	int							m_iSX;					//	������ �ؽ�ó ������ ����
	int							m_iSY;					//	������ �ؽ�ó ������ ����
	bool						m_bDelete;				//	�ؽ�ó ���� ����

	void	Clear()
	{
		m_strImageName.clear();
		m_rcSrc.left	=	0;
		m_rcSrc.top		=	0;
		m_rcSrc.right	=	0;
		m_rcSrc.bottom	=	0;

		if( m_bDelete == true )
			SAFE_RELEASE( m_pImage );

		m_pImage		=	NULL;

		m_iSX			=	0;
		m_iSY			=	0;
		m_bDelete		=	false;
	}

	LIST_ICON()
	{
		m_pImage	=	NULL;

		Clear();
	}
};


struct LIST_ITEM
{
	LIST_ICON					m_stBGImage;			//	��� �̹���
	std::vector<LIST_ICON>		m_vIconImage;			//	���ʿ� �׷��� ������
	
	LIST_ICON					m_imgTail;		// Tail Icon
	LIST_ICON					m_imgHeader;	// Header Icon
	LIST_ICON					m_imgChannel;	// channel icon
	bool						m_bFirstLine;
	bool						m_bLastLine;

	std::string					m_strSender;			//	sender
	std::string					m_strText;				//	���ڿ�
	D3DXCOLOR					m_stTextColor;			//	���ڿ� �÷�
	SPFONT_EFFECT				m_fontEffect;

	LIST_RETURNVALUE			m_stReturnValue;		//	������ ��

	RECT						m_rcDrawPos;			//	��ü ����

	void	Clear()
	{
		m_stBGImage.Clear();
		m_imgTail.Clear();
		m_imgHeader.Clear();
		m_imgChannel.Clear();
		m_bFirstLine = true;
		m_bLastLine = true;
		m_fontEffect = SPFONT_EDGE;

		std::vector<LIST_ICON>::iterator	Iter	=	m_vIconImage.begin();

		while ( Iter != m_vIconImage.end() )
		{
			(*Iter).Clear();
			++Iter;
		}

		m_vIconImage.clear();

		m_strText.clear();
		m_strSender.clear();

		m_stTextColor	=	D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );

		m_rcDrawPos.left	=	0;
		m_rcDrawPos.top		=	0;
		m_rcDrawPos.right	=	0;
		m_rcDrawPos.bottom	=	0;
	}

	LIST_ITEM()
	{
		Clear();
	}
};

//////////////////////////////////////////////////////////////////////////

class SPWindow;
class SPWindowList :	public SPWindow {
public:
	SPWindowList(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent);
	~SPWindowList();

	virtual void Init();
	virtual void Clean();
	virtual void Process(float fTime);
	virtual void Render(float fTime);
	virtual void Refresh();

	void	SetImageRect	( const char* pszImage, RECT rcImageSrc );
	bool	InsertItem		( const char* pszListItem , D3DXCOLOR color );
	bool	InsertItem		( LIST_ITEM* pListItem );
	bool	CopyListIcon	( LIST_ICON& stDestListIcon , LIST_ICON& stSrcListIcon );
	void	PushBackItem	( LIST_ITEM& stListItem );
	void	ClearListItem	();
	LIST_RETURNVALUE*	GetReturnValue( int iXPos , int iYPos );


	int		ScrollList		( int iSubSpim = SUB_SPIM_SCROLL_LATEST , LPARAM lParam = 0 );

	void	SetMargin		( int iLeft , int iTop , int iRight , int iBottom );
	bool	GetLatest		();
	bool	IsAddString		();
	void	SetWheelUse		( bool bUse );
	void	SetNextLine		( bool bUse );

	int		GetBeginLine	();
	int		GetEndLine		();


protected:
	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	// {{ Message Map	
	virtual int OnCursorEnter		( WPARAM, LPARAM );
	virtual int OnCursorOut			( WPARAM, LPARAM );
	virtual int OnLButtonDown		( WPARAM, LPARAM );
	virtual int OnLButtonUP			( WPARAM, LPARAM );	
	virtual int OnAddItem			( WPARAM, LPARAM );
	virtual int OnScroll			( WPARAM, LPARAM );
	virtual int OnPurge				( WPARAM, LPARAM );
	virtual int OnWheelUp			( WPARAM, LPARAM );
	virtual int OnWheelDown			( WPARAM, LPARAM );
	virtual int OnGetCalcLumpString	( WPARAM, LPARAM );
	// }}

protected:

	int								m_iBeginLine;
	int								m_iPrintLineCount;

	RECT							m_rcImageSrc;
	RECT							m_rcMargin;

	std::string						m_strStatic;
	bool							m_bLatest;
	bool							m_bAddString;
	bool							m_bWheelUse;
	bool							m_bNextLine;

	//////////////////////////////////////////////////////////////////////////

	std::vector<LIST_ITEM>			m_vListItem;
	std::string						m_strLogString;

};


