// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-7-15    18:31 
//***************************************************************************

#pragma once

#define ITEM_COUNT_MAX	999
#define ITEM_LENGTH_MAX	3

class SPUIUnit;

class SPUIItemUnit : public SPUIUnit
{
public:
	SPUIItemUnit								(void);
	virtual ~SPUIItemUnit						(void);

	//	�⺻ �������̽�
	virtual	void			Init				();
	virtual	void			Clear				();
	virtual	void			Process				( float fTime );
	virtual	void			Render				();
	virtual	BOOL			Use					();

	//	������ ���̵� �������̽�
	void					SetItemID			( int iItemID );
	int						GetItemID			();

	//	������ Ÿ�� �������̽�
	void					SetItemType			( CONTAINER_TYPE eType );
	CONTAINER_TYPE			GetItemType			();

	//	�ڱ� �ڽ� ���� �������̽�
	virtual SPUIUnit*		ClonePtr			();
	virtual BOOL			Copy				( SPUIUnit** ppDestUIUnit );

	//	���̵�� ���ҽ� �� �ε�
	virtual	BOOL			ReResourceLoad		();

	//	������ ��׶��� �ؽ�ó �������̽�
	void					SetBGTexture		( SPTexture* pTexture );
	BOOL					SetBGTexture		( const char* pstrTexture );
	SPTexture*				GetBGTexture		();
	
	//	������ ��׶��� �ؽ�ó ���� �������̽�
	void					SetBGRectSrc		( RECT rtSrc );
	void					SetBGRectSrc		( int ixLeft , int iyTop , int ixRight , int iyBottom );
	RECT					GetBGRectSrc		();

	//	������ ���� üũ �������̽�
	void					CheckCount			();
	void					SetCount			( int iCount );
	int						GetCount			();

	//	������ ������ �ؽ�ó �������̽�
	void					SetIconTexture		( SPTexture* pTexture );
	BOOL					SetIconTexture		( const char* pstrTexture );
	SPTexture*				GetIconTexture		();

	//	������ ���� ���μ��� �������̽�
	void					ProcessCount		();

	//	������ �Ⱓ ǥ�� ����
	void					SetDuration			( BOOL bDuration );
	BOOL					GetDuration			();

protected:

	//	������ ���� ���� �������̽�
	void					RenderCount			();

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	int						m_iItemID;
	CONTAINER_TYPE			m_eItemType;

	SPTexture*				m_pBGTexture;
	RECT					m_rtBGSrc;

	int						m_iCount;

	int						m_iCountLength;

	RECT					m_rtCountSrc[ ITEM_LENGTH_MAX ];
	POINT					m_ptCountPos[ ITEM_LENGTH_MAX ];

	SPTexture*				m_pIconTexture;
	RECT					m_rtIconSrc;

	BOOL					m_bDuration;

};
