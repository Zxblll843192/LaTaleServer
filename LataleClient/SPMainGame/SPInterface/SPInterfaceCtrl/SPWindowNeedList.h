// Copyright (C) duragon
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : duragon 2007-08-24 ���� 10:26:19
//***************************************************************************


#pragma once

//////////////////////////////////////////////////////////////////////////
#define DEFAULT_MARGIN			8			// Default Margin 8

//////////////////////////////////////////////////////////////////////////
//
struct LIST_NEEDITEM
{
	int					m_ItemID ;				// ItemID (if Item)
	int					m_ItemCount ;			// Item Count
	int					m_iRelSX ;				// �̹��� ������ǥ(�����ǥ)
	SPTexture*			m_pImage ;				// ������ �ؽ�ó
	RECT				m_rtSrc ;				// �ؽ��� �ҽ� ��ǥ
	RECT				m_rtDstImage ;			// �̹��� �����ǥ

	std::string			m_strText ;				// ���ڿ� �׸�
	D3DXCOLOR			m_colText ;				// ���ڻ�
	int					m_iStrLength ;			// ���� ����
	RECT				m_rtDstText ;			// �ؽ�Ʈ �����
	
	LIST_NEEDITEM()
	{
		Clear();
	}
	~LIST_NEEDITEM()
	{
		SAFE_RELEASE(m_pImage) ;
		Clear();
	}

	void	Clear()
	{
		m_ItemID	= 0 ;
		m_ItemCount = 0 ;
		m_iRelSX	= 0 ;
		m_pImage	= NULL ;
		SetRect(&m_rtSrc, 0, 0, 0, 0);
		SetRect(&m_rtDstImage, 0, 0, 0, 0);
		
		m_strText.clear() ;
		m_colText = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) ;
		m_iStrLength = 0 ;
		SetRect(&m_rtDstText, 0, 0, 0, 0) ;
	}

	bool SetImage(const char* szImage, int iSrcX, int iSrcY, int iSrcEX, int iSrcEY)
	{
		std::string strResource = szImage;

		if( strResource.empty() == true )
			return false;

		if( g_pVideo->GetTextureMgr()->LoadTexture(strResource.c_str(), &m_pImage) == false )
			return false;

		SetRect(&m_rtSrc, iSrcX, iSrcY, iSrcEX, iSrcEY) ;
		return true ;
	}
	bool SetImage(const char* szImage, RECT rtSrc)
	{
		std::string strResource = szImage;

		if( strResource.empty() == true )
			return false;

		if( g_pVideo->GetTextureMgr()->LoadTexture(strResource.c_str(), &m_pImage) == false )
			return false;

		SetRect(&m_rtSrc, rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom) ;
		return true ;
	}
	bool SetImage(SPTexture* pImage, RECT rtSrc)
	{
		if( pImage == NULL )
			return false;

		m_pImage = pImage ;

		SetRect(&m_rtSrc, rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom) ;
		return true ;
	}

	bool SetText(const char* strText)
	{
		if( strText == NULL )
			return false ;
		m_strText = strText ;
		return true ;
	}

	D3DXCOLOR SetTextColor(float fR, float fG, float fB, float fA)
	{
		m_colText = D3DXCOLOR(fR, fG, fG, fA) ;
		return m_colText ;
	}
	D3DXCOLOR SetTextColor(D3DXCOLOR dColor)
	{
		m_colText = dColor ;
		return m_colText ;
	}
};


//////////////////////////////////////////////////////////////////////////
//
class SPWindow;
class SPWindowNeedList :	public SPWindow {
public:
	SPWindowNeedList(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent);
	~SPWindowNeedList();

	virtual void Init();
	virtual void Clean();
	virtual void Process(float fTime);
	virtual void Render(float fTime);

	virtual void	RefreshRelationCoord();

	void ClearListItem() ;

	bool InsertItem( const char* pszImage, RECT rcImageSrc, const char* pszItemText , D3DXCOLOR color = D3DXCOLOR(0, 0, 0, 1.0f) ) ;
	bool InsertItem( int iItemID, int iItemCount) ;		// Default ItemAttr->m_eRareLimit Color (default Black)
	
	bool SetBGImage(const char* pszImage, RECT rcImageSrc ) ;
	void SetMargin( int iWidthMargin, int iHeightMargin ) ;

protected:
	D3DXCOLOR GetItemColor(int iLareLimit) ;
	bool PushBackItem( LIST_NEEDITEM* pListItem ) ;
	void ReposeStartPos() ;
	void ReposOwnImage() ;
	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	// {{ Message Map	
	virtual int OnPurge			( WPARAM wParam , LPARAM lParam );
	// }}

protected:
	RECT		m_rcBGSrc;
	SPTexture*	m_pTextureBG ;
	SPTexture*	m_pTextureNum ;		// Item Count Texture
	RECT		m_rcNumSrc;

	bool	m_bDrawLine ;			// Guide Line Render
	int		m_iImageSX ;			// �̹����� ���� ��ġ
	int		m_iImageMAXWidth ;		// �̹��� ���� Width (Height�� ����)
	int		m_iTextSX ;				// Text�� ���� ��ġ
	int		m_iTextMAXWidth ;		// Text ������ Width
	int		m_iWidthMargin ;		// Image�� Text�� Margin
	int		m_iHeightMargin ;

	//////////////////////////////////////////////////////////////////////////
	std::vector<LIST_NEEDITEM*>		m_vpNeedItem;

};
