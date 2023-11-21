// ***************************************************************
//  SPTreeBoxItemBase.h   version:  1.0   date:2006/01/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2006 AJJIYA - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#pragma once

class SPTreeBoxItemBase
{
public:
	SPTreeBoxItemBase				();
	virtual	~SPTreeBoxItemBase		();

	virtual	void	Init			();
	virtual	void	Clear			();

	virtual	void	Process			( float fTime );
	virtual	void	Render			( float fTime );

	virtual	int		GetNextPosX		();
	virtual	int		GetNextPosY		();

	virtual	bool	IsCursorIn		( int iX, int iY );

	virtual	void	SetPos			( int iX , int iY );
	virtual	RECT	GetPosRect		();

	virtual	void	SetSize			( int iX , int iY );
	virtual	POINT	GetSize			();

	virtual	void	SetStatus		( TREEBOX_DATA_STATUS_LABEL eStatus );
	virtual	void	AddStatus		( DWORD dwStatus );
	virtual	void	DelStatus		( DWORD dwStatus );
	virtual	bool	GetStatus		( DWORD dwStatus );
	virtual	DWORD	GetStatus		();

	void			SetText			( const char* pString );
	const char*		GetText			();

	void			SetTextColor	( TREEBOX_DATA_STRING_LABEL eLabel , D3DXCOLOR cColor );
	void			SetTextColor	( int iLabel , D3DXCOLOR cColor );
	void			SetBold			( bool bBold );

	void			SetTextMargin	( int iX , int iY );
	POINT			GetTextMargin	();

	void			SetAlign		( DWORD dwAlign );
	DWORD			GetAlign		();

	void			SetFontEnumerate( FONT_ENUMERATE eFontEnumerate );
	FONT_ENUMERATE	GetFontEnumerate();

	void			SetReturnValue	( int iValue );
	int				GetReturnValue	();

	void			SetTextPeriod	( bool bPeriod );
	bool			GetTextPeriod	();

protected:
private:

	DWORD			m_dwStatus;							//	�� ����
	POINT			m_ptSize;							//	ũ��
	RECT			m_rcPos;							//	�����Ǵ� ��ġ
	std::string		m_strText;							//	����
	D3DXCOLOR		m_cTextColor[ DATA_STRING_COUNT ];	//	���� ����
	bool			m_bBold;							//	���� �ι� ��� ( ���ϰ� )
	POINT			m_ptMargin;							//	���� ������
	DWORD			m_dwAlign;							//	���� ���İ�
	FONT_ENUMERATE  m_eFontEnumerate;					//	���� ũ�� �� ����

	int				m_iReturnValue;						//	�����س� �� ����
	bool			m_bTextPeriod;						//	�ؽ�Ʈ ..���� ǥ�ÿ���
};
