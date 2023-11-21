// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-6-28    15:24 
//***************************************************************************

#pragma once

enum SKILL_INVENTORY_TYPE;
enum EFFECT_STATUS_KIND_TYPE;

#define GS_SKILL						1200000
#define GS_SKILL_LEVEL					( GS_SKILL + 1000 )
#define GS_SKILL_GET_LEVEL				( GS_SKILL + 2000 )
#define GS_SKILL_MAX_LEVEL				( GS_SKILL + 2001 )
#define GS_SKILL_TYPE					( GS_SKILL + 3000 )
#define GS_SKILL_REQUIRE_STAT			( GS_SKILL + 4000 )
#define GS_SKILL_CONSUMPTION_STAT		( GS_SKILL + 5000 )
#define GS_SKILL_REQUIREITEM_KIND		( GS_SKILL + 6000 )
#define GS_SKILL_COOLTIME				( GS_SKILL + 7000 )
#define GS_SKILL_INVENTORY_TYPE			( GS_SKILL + 8000 )
#define GS_SKILL_LEVEL_UP_POINT			( GS_SKILL + 9000 )
#define GS_SKILL_UPREQUIRE_STAT			( GS_SKILL + 10000 )

class SPUIUnit;
class SPSkill;
class SPSkillActivity;

class SPUISkillUnit : public SPUIUnit
{
public:
	SPUISkillUnit								(void);
	virtual ~SPUISkillUnit						(void);

	//	�⺻ �������̽�
	virtual	void			Init				();
	virtual	void			Clear				();
	virtual	void			Process				( float fTime );
	virtual	void			Render				();
	virtual	BOOL			Use					();

	//	��ų ���̵� �������̽�
	void					SetSkillID			( int iSkillID );
	int						GetSkillID			();

	//	��ų �κ��丮 Ÿ�� �������̽�
	void					SetType				( SKILL_INVENTORY_TYPE eType );
	SKILL_INVENTORY_TYPE	GetType				();

	//	������ ���̵� �������̽�
	void					SetItemID			( int iItemID );
	int						GetItemID			();

	//	CONTAINER_SLOT �������̽� - ������ ��ų�� ��� CONTAINER_SLOT�� �����ؾ� �Ѵ�.
	void					SetContainerSlot	( CONTAINER_SLOT stContainerSlot );
	CONTAINER_SLOT			GetContainerSlot	();

	//	������ ���� �ε� �������̽�
	void					ReItemInfoLoad		();

	//	�ڱ� �ڽ� ���� �������̽�
	virtual SPUIUnit*		ClonePtr			();
	virtual BOOL			Copy				( SPUIUnit** ppDestUIUnit );

	//	���̵�� ���ҽ� �� �ε�
	virtual	BOOL			ReResourceLoad		();

	//	�޺� �ؽ�ó �������̽�
	void					SetComboTexture		( SPTexture* pTexture );
	BOOL					SetComboTexture		( const char* pstrTexture );
	SPTexture*				GetComboTexture		();

	//	�޺� �ؽ�ó ���� �������̽�
	void					SetComboRectSrc		( RECT rtSrc );
	void					SetComboRectSrc		( int ixLeft , int iyTop , int ixRight , int iyBottom );
	RECT					GetComboRectSrc		();

	//	�޺� ���� �������̽�
	void					SetCombo			( BOOL bCombo );
	BOOL					GetCombo			();

	//	�޺� ǥ�� �ð� �������̽�
	void					SetComboLimitTime	( float fLimitTime );
	float					GetComboLimitTime	();

	//	��� �ؽ�ó �������̽�
	void					SetToggleTexture	( SPTexture* pTexture );
	BOOL					SetToggleTexture	( const char* pstrTexture );
	SPTexture*				GetToggleTexture	();

	//	��Ŭ ��ų �������̽�
	void					SetToggle			( BOOL bToggle );
	BOOL					GetToggle			();

protected:

	//	�޺� ǥ�� ���μ���
	void					ProcessCombo		( float fTime );

	//	Toggle ǥ�� ���μ���
	void					ProcessToggle		( float fTime );

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	int						m_iSkillID;
	SKILL_INVENTORY_TYPE	m_eType;
	int						m_iItemID;
	CONTAINER_SLOT			m_stContainerSlot;

	SPTexture*				m_pComboTexture;
	RECT					m_rtComboSrc;

	BOOL					m_bCombo;
	D3DXCOLOR				m_stComboColor;

	float					m_fComboLimitTime;
	float					m_fComboAccmulateTime;

	BOOL					m_bToggle;
	int						m_iCurToggleFrame;
	int						m_iMaxToggleFrame;
	float					m_fToggleLimitTime;
	float					m_fToggleAccmulateTime;
	SPTexture*				m_pToggleTexture;
	RECT					m_rtToggleSrc;
	POINT					m_ptToogleRenderOffset;
	POINT					m_ptToggleSize;

};
