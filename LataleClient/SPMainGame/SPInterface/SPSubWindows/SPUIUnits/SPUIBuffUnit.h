// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-10-10    16:08 
//***************************************************************************

#pragma once

#define TIME_COUNT_MAX		9999
#define TIME_LENGTH_MAX		4

class SPUIUnit;
class SPEffect;

class SPUIBuffUnit : public SPUIUnit
{
public:
	enum BUFF_FONT_COLOR
	{
		BUFF_FONT_WIDTH				=	9	,
		BUFF_FONT_HEIGHT			=	10	,
		BUFF_FONT_COLOR_WHITE		=	0	,
		BUFF_FONT_COLOR_YELLOW				,
		BUFF_FONT_COLOR_GREEN				,
	};

	SPUIBuffUnit								(void);
	virtual ~SPUIBuffUnit						(void);

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
//	virtual	BOOL			ReResourceLoad		();

	//	���� ��Ƽ��Ƽ ����ũ ���̵� �������̽�
	void					SetBuffID			( unsigned int uiBuffID );
	unsigned int			GetBuffID			();

	//	���� ����Ʈ ���� �������̽�
	BOOL					SetEffect			( SPEffect* pEffect );

	//	Ÿ�� üũ ���� �������̽�
	void					SetTimeCheck		( BOOL bTimeCheck );
	BOOL					GetTimeCheck		();

	//	Ÿ�� ���ҽ� ���� �����
	void					SetTimeData			( int iTime );
	int						GetTime				();

protected:

	//	Ÿ�� ���� �������̽�
	void					RenderTime			();

	//	����Ʈ ���μ��� �������̽�
	void					ProcessEffect		( float fTime );

	//	����Ʈ ���� �������̽�
	void					RunEffect			();

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	unsigned int			m_uiBuffID;

	BOOL					m_bTimeCheck;

	int						m_iTime;
	int						m_iTimeLength;
	RECT					m_rtTimeSrc[ TIME_LENGTH_MAX ];
	POINT					m_ptTimePos[ TIME_LENGTH_MAX ];

	BOOL					m_bEffect;
	float					m_fLimitTime;					//	�������� ���ؼ�
	float					m_fAccmulateTime;				//	�������� ���ؼ�

};
