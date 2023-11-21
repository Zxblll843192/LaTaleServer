// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowRSList.h
//	created:	2007/9/21   Time:15:36
//	purpose:	
//
//  1. RS �迭�� �Լ��� URL�� �����Ҽ� �ֵ��� RETURNVALUR ���� ����ϰ� �ִ�.
//		RSList������ GetReturnValue() �� ���ؼ� ���� ���ֵ��� ���� �Ǿ� �ִ�.
//	2. �Ǵٸ� Ư¡�� CursorEnter�� ��Ʈ �÷��� �ٲ�ų� ��� ImgaeBar�� �������� ���� �����ϴ�
//		FontColor�� SetSelectFontcolor() ȣ�� ���� �־����� �Լ�
//		�Ǵ� InsertItem( RSLIST_ITEM* pListItem )�� ���� ������ ���� �����ؼ� ������ �ȴ�.
//	3. Select ImageBar Setting�� SetSelectBar() �� ȣ���ϸ� �ڵ����� ���õȴ�.
//		
//*********************************************************************/


#pragma once

#include "SPWindowListDEF.h"

struct RSLIST_ITEM
{
	bool						m_bUseFontColor ;		//	CursorOver ��Ʈȿ�� ��뿩��
	std::string					m_strText;				//	���ڿ�
	D3DXCOLOR					m_TextColor;			//	������ �÷�
	D3DXCOLOR					m_DefTextColor;			//	Default �÷�
	D3DXCOLOR					m_RvsTextColor;			//	Mouse Over �÷�
	LIST_RETURNVALUE			m_stReturnValue;		//	������ ��
	RECT						m_rcDrawPos;			//	��ü ����

	void	Clear()
	{
		m_bUseFontColor = false ;
		m_strText.clear();
		m_TextColor		= D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );
		m_DefTextColor	= D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );
		m_RvsTextColor	= D3DXCOLOR( 0 , 0 , 0 , 1.0f );

		m_rcDrawPos.left	=	0;
		m_rcDrawPos.top		=	0;
		m_rcDrawPos.right	=	0;
		m_rcDrawPos.bottom	=	0;
	}

	RSLIST_ITEM()
	{
		Clear();
	}
	RSLIST_ITEM& operator = (const RSLIST_ITEM& Src)
	{
		m_bUseFontColor = Src.m_bUseFontColor ;
		m_strText		= Src.m_strText ;
		m_TextColor		= Src.m_TextColor;
		m_RvsTextColor	= Src.m_RvsTextColor;
		m_stReturnValue = Src.m_stReturnValue ;

		m_rcDrawPos.left	=	Src.m_rcDrawPos.left;
		m_rcDrawPos.top		=	Src.m_rcDrawPos.top;
		m_rcDrawPos.right	=	Src.m_rcDrawPos.right;
		m_rcDrawPos.bottom	=	Src.m_rcDrawPos.bottom;
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////////

class SPWindow;
class SPWindowRSList :	public SPWindow {
public:
	SPWindowRSList(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent);
	~SPWindowRSList();

	virtual void Init();
	virtual void Clean();
	virtual void Process(float fTime);
	virtual void Render(float fTime);
	virtual void Show(bool bWithChild = true);
	virtual void Refresh();

	void	SetSelectFontcolor(bool bSet)			{	m_bUseFontColor = bSet ;	}
	void	SetSelectBar	(const char* pszImage, RECT rcImageSrc, int iRelPosX, int iRelPosY) ;
	bool	InsertItem		( const char* pszListItem , D3DXCOLOR color, D3DXCOLOR Rvscolor );
	bool	InsertItem		( RSLIST_ITEM* pListItem );
	void	PushBackItem	( RSLIST_ITEM& stListItem );
	void	ClearListItem	();

	LIST_RETURNVALUE*	GetReturnValue( int iXPos , int iYPos );
	RSLIST_ITEM* GetMouseOverItem() ;

	int		ScrollList		( int iSubSpim = SUB_SPIM_SCROLL_LATEST );

	void	SetMargin		( int iLeft , int iTop , int iRight , int iBottom );
	bool	GetLatest		();
	bool	IsAddString		();
	void	SetWheelUse		( bool bUse );
	void	SetNextLine		( bool bUse );
	int		GetTotalLine	()				{	return m_iTotalLineCount ;		}


protected:

	SPIMESSAGE_OBJ_MAP_DECLARE()
		// {{ Message Map	
	virtual int OnCursorEnter	( WPARAM, LPARAM );
	virtual int OnCursorMove	( WPARAM, LPARAM );
	virtual int OnCursorOut		( WPARAM, LPARAM );
	virtual int OnLButtonDown	( WPARAM, LPARAM );
	virtual int OnLButtonUP		( WPARAM, LPARAM );	
	virtual int OnAddItem		( WPARAM wParam , LPARAM lParam);
	virtual int OnScroll		( WPARAM wParam , LPARAM lParam );
	virtual int OnPurge			( WPARAM wParam , LPARAM lParam );
	virtual int OnWheelUp		( WPARAM wParam , LPARAM lParam );
	virtual int OnWheelDown		( WPARAM wParam , LPARAM lParam );
	// }}

protected:

	int					m_iBeginLine;
	int					m_iPrintLineCount;
	int					m_iTotalLineCount;
	RSLIST_ITEM*		m_pEnterItem ;

	bool				m_bUseFontColor ;	// SelectFontColor ��뿩��
	bool				m_bUseSelectBar ;	// SelectBar ��뿩��
	SPTexture*			m_pBarTexture ;
	RECT				m_rcSelectBarSrc;	// Bar�� �ҽ���ǥ
	int					m_rcRelPosX;		// Bar�� ��� �����ǥ
	int					m_rcRelPosY;		// Bar�� ��� �����ǥ
	RECT				m_rcMargin;			// ����Ʈ ���� ����

	bool				m_bLatest;
	bool				m_bAddString;
	bool				m_bWheelUse;
	bool				m_bNextLine;
	bool				m_bFontShadow ;

	//////////////////////////////////////////////////////////////////////////

	std::vector<RSLIST_ITEM>		m_vListItem;

};
