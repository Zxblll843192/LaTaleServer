// ***************************************************************
//  SPUIChatMacro   version:  1.0   ��  date: 08/09/2007
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#pragma once

class SPUIUnit;

enum CHAT_MACRO_TYPE
{
	CHAT_MACRO_TYPE_NULL	=	0	,
	CHAT_MACRO_TYPE_NORMAL			,
	CHAT_MACRO_TYPE_SPECIAL			,
	CHAT_MACRO_TYPE_COUNT			,
};

struct CHAT_MACRO
{
	int					m_iIndex;
	std::string			m_strName;
	std::string			m_strContents;
};

struct CHAT_MACRO_LDT
{
	CHAT_MACRO_TYPE		m_eType;
	int					m_iSubType;
	int					m_iCount;
	int					m_iIconFile;
	int					m_iIconIndex;
	int					m_iRequireItem;
	std::string			m_strAppName;
	std::string			m_strKeyName;
};

struct CHAT_MACRO_POS
{
	CHAT_MACRO_TYPE		m_eType;
	int					m_iIndex;
};

class SPUIChatMacro : public SPUIUnit
{
public:
	SPUIChatMacro								(void);
	virtual ~SPUIChatMacro						(void);

	//	�⺻ �������̽�
	virtual	void			Init				();
	virtual	void			Clear				();
	virtual	void			Process				( float fTime );
	virtual	void			Render				();
	virtual	BOOL			Use					();

	//	�ڱ� �ڽ� ���� �������̽�
	virtual SPUIUnit*		ClonePtr			();
	virtual BOOL			Copy				( SPUIUnit** ppDestUIUnit );

	//	���ҽ� �� �ε�
	virtual	BOOL			ReResourceLoad		();

	//	ä�� ��ũ�� ������
	void					SetChatMacro		( CHAT_MACRO* pChatMacro );
	CHAT_MACRO*				GetChatMacro		();

	//	ä�� ��ũ�� LDT ������
	void					SetChatMacroLDT		( CHAT_MACRO_LDT* pChatMacroLDT );
	CHAT_MACRO_LDT*			GetChatMacroLDT		();

	//	���� ���� ��ġ �������̽�
	void					SetTextRect			( RECT rtSrc );
	void					SetTextRect			( int ixLeft , int iyTop , int ixRight , int iyBottom );
	RECT					GetTextRect			();

	//	���� ���� �������̽�
	void					SetTextColor		( D3DXCOLOR cColor );
	D3DXCOLOR				GetTextColor		();

	//	���� ���� �������̽�
	void					SetTextAlign		( DWORD dwAlign );
	DWORD					GetTextAlign		();

	//	���� ��Ʈ �׸��� �������̽�
	void					SetFontShadow		( BOOL bShow );
	BOOL					GetFontShadow		();

	//	���� Period �������̽�
	void					SetPeriod			( BOOL bPeriod );
	BOOL					GetPeriod			();

	//	���� ���� �������̽�
	void					SetText				( const char* pszText );
	const char*				GetText				();

	//	���� ��Ʈ �������̽�
	void					SetFont				( FONT_ENUMERATE eFont );
	FONT_ENUMERATE			GetFont				();

protected:

	//	��Ÿ �������̽�
	BOOL					IsText				();

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	CHAT_MACRO*				m_pChatMacro;			//	ä�� ��ũ�� ������
	CHAT_MACRO_LDT*			m_pChatMacroLDT;		//	ä�� ��ũ�� LDT ������

	RECT					m_rtTextDest;			//	���� ���� ��ġ
	D3DXCOLOR				m_cTextRGBA;			//	���� ����
	DWORD					m_dwTextAlign;			//	���� ����
	BOOL					m_bTextFontShadow;		//	���� ��Ʈ �׸���
	BOOL					m_bTextPeriod;			//	���� Period
	std::string				m_strText;				//	����

	FONT_ENUMERATE			m_eTextFont;			//	���� ��Ʈ Ÿ��
	SPFont*					m_pTextFont;			//	���� ��Ʈ ������


};
