// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-6-28    14:41 
//***************************************************************************

#pragma once


class SPUIUnit
{
public:
	enum STATUS_UI_UNIT
	{
		STATUS_UI_UNIT_NONE			=	0x0000	,
		STATUS_UI_UNIT_RENDER		=	0x0100	,
		STATUS_UI_UNIT_DRAGNDROP	=	0x0200	,
		STATUS_UI_UNIT_COOLTIME		=	0x0400	,
		STATUS_UI_UNIT_NO_DRAGNDROP	=	0x0800	,
		STATUS_UI_UNIT_NO_TOOLTIP	=	0x1000	,
		STATUS_UI_UNIT_MASK			=	0xFF00	,
		STATUS_UI_UNIT_ENABLE		=	0x0001	,
		STATUS_UI_UNIT_DISABLE		=	0x0002	,
	};

	SPUIUnit								(void);
	virtual ~SPUIUnit						(void);

	//	�⺻ �������̽�
	virtual	void		Init				();
	virtual	void		Clear				();
	virtual	void		Process				( float fTime );
	virtual	void		Render				();
	virtual	BOOL		Use					();
	virtual	BOOL		MouseOver			( int iX , int iY );

	//	InstanceID �������̽�
	void				SetInstanceID		( INSTANCE_ID iID );
	INSTANCE_ID			GetInstanceID		();

	//	Status �������̽�
	void				SetStatus			( DWORD dwStatus );
	void				AddStatus			( DWORD dwStatus );
	void				DelStatus			( DWORD dwStatus );
	BOOL				GetStatus			( DWORD dwStatus );
	DWORD				GetStatus			();

	//	���ҽ� ���� �������̽�
	BOOL				SetResource			( int iResID , int iResIndex );

	//	�ؽ��� ���� ���� �������̽�
	void				SetRectSrc			( RECT rtSrc );
	void				SetRectSrc			( int ixLeft , int iyTop , int ixRight , int iyBottom );
	RECT				GetRectSrc			();

	//	�ؽ��� ���� ��ġ �������̽�
	void				SetPos				( POINT ptPos );
	void				SetPos				( LONG lX , LONG lY );
	POINT				GetPos				();

	//	�ؽ��� ������ �������̽�
	void				SetSize				( POINT ptSize );
	void				SetSize				( LONG lX , LONG lY );
	POINT				GetSize				();

	//	���� �ؽ��� �������̽�
	void				SetTexture			( SPTexture* pTexture );
	BOOL				SetTexture			( const char* pstrTexture );
	SPTexture*			GetTexture			();

	//	��Ȱ��ȭ �ؽ��� ���� ���� �������̽�
	void				SetDisableRectSrc	( RECT rtSrc );
	void				SetDisableRectSrc	( int ixLeft , int iyTop , int ixRight , int iyBottom );
	RECT				GetDisableRectSrc	();

	//	��Ȱ��ȭ �ؽ��� �������̽�
	void				SetDisableTexture	( SPTexture* pTexture );
	BOOL				SetDisableTexture	( const char* pstrTexture );
	SPTexture*			GetDisableTexture	();

	//	��Ȱ��ȭ �÷� �������̽�
	void				SetDisableColor		( D3DXCOLOR cColor );
	D3DXCOLOR			GetDisableColor		();

	//	�ڱ� �ڽ� ���� �������̽�
	virtual SPUIUnit*	ClonePtr			();
	virtual BOOL		Copy				( SPUIUnit** ppDestUIUnit );

	//	���̵�� ���ҽ� �� �ε�
	virtual	BOOL		ReResourceLoad		();

	//	CoolTime ID �������̽�
	void				SetCoolTimeID		( int iID );
	int					GetCoolTimeID		();

	//	CoolTime �ؽ�ó �������̽�
	void				SetCoolTimeTexture	( SPTexture* pTexture );
	BOOL				SetCoolTimeTexture	( const char* pstrTexture );
	SPTexture*			GetCoolTimeTexture	();

	//	CoolTime �ؽ�ó ���� ���� �������̽�
	void				SetCoolTimeRectSrc	( RECT rtSrc );
	void				SetCoolTimeRectSrc	( int ixLeft , int iyTop , int ixRight , int iyBottom );
	RECT				GetCoolTimeRectSrc	();

protected:

	//	��Ÿ �������̽�
	BOOL				IsRender			();
	BOOL				IsTexture			();
	BOOL				IsDisableTexture	();
	BOOL				IsCoolTimeTexture	();
	BOOL				IsRectIn			( int iX , int iY );

	//	���μ��� �������̽�
	virtual void		DisablePorcess		();
	virtual	void		CoolTimeProcess		( float fTime );

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	INSTANCE_ID			m_iInstanceID;			//	���� �ν��Ͻ� ���̵�( SPWindow�� ���� )
	DWORD				m_dwStatus;				//	���� Unit�� ����
	
	SPTexture*			m_pTexture;				//	���� �ؽ���
	POINT				m_ptPos;				//	�ؽ��� ���� ��ġ
	POINT				m_ptSize;				//	�ؽ��� ũ��
	RECT				m_rtSrc;				//	�ؽ��� ����

	SPTexture*			m_pDisableTexture;		//	��Ȱ��ȭ�� ����� �ؽ���
	RECT				m_rtDisableSrc;			//	��Ȱ��ȭ�� �ؽ��� ����
	RECT				m_rtDisableTarget;		//	��Ȱ��ȭ�� ���� ����
	D3DXCOLOR			m_cDisableRGBA;			//	��Ȱ��ȭ�� ����ϴ� �÷���

	D3DXCOLOR			m_cRGBA;				//	�巡�� �����϶� �����ϰ� ��������~

	int					m_iCoolTimeID;			//	��Ÿ�� ���̵�
	SPTexture*			m_pCoolTimeTexture;		//	��Ÿ�� �ؽ�ó
	RECT				m_rtCoolTimeSrc;		//	��Ÿ�� �ؽ�ó ����
	RECT				m_rtCoolTimeTarget;		//	��Ÿ�� �ؽ�ó Ÿ�� ����

};
