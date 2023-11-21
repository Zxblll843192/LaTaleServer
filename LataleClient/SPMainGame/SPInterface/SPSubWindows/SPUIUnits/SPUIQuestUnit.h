// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-9-23    11:56 
//***************************************************************************

#pragma once

#define QUEST_COUNT_MAX		999
#define QUEST_LENGTH_MAX	3

enum QUEST_NPC;

class SPUIUnit;
class SPQuestArchive;

class SPUIQuestUnit : public SPUIUnit
{
public:
	SPUIQuestUnit								(void);
	virtual ~SPUIQuestUnit						(void);

	//	�⺻ �������̽�
	virtual	void			Init				();
	virtual	void			Clear				();
	virtual	void			Process				( float fTime );
	virtual	void			Render				();
	virtual	BOOL			Use					();

	//	����Ʈ ���̵� �������̽�
	void					SetQuestID			( int iQuestID );
	int						GetQuestID			();

	//	����Ʈ Ÿ�� �������̽�
	void					SetQuestType		( QUEST_NPC eQuestType );
	QUEST_NPC				GetQuestType		();

	//	����Ʈ ��ī�̺� �������̽�
	void					SetQuestArchive		( SPQuestArchive* pQuestArchive );
	SPQuestArchive*			GetQuestArchive		();

	//	�ڱ� �ڽ� ���� �������̽�
	virtual SPUIUnit*		ClonePtr			();
	virtual BOOL			Copy				( SPUIUnit** ppDestUIUnit );

	//	���̵�� ���ҽ� �� �ε�
	virtual	BOOL			ReResourceLoad		();

	//	����Ʈ �Ϸ� �ؽ�ó �������̽�
	void					SetCompleteTexture	( SPTexture* pTexture );
	BOOL					SetCompleteTexture	( const char* pstrTexture );
	SPTexture*				GetCompleteTexture	();
	
	//	����Ʈ �Ϸ� �ؽ�ó ���� �������̽�
	void					SetCompleteRectSrc	( RECT rtSrc );
	void					SetCompleteRectSrc	( int ixLeft , int iyTop , int ixRight , int iyBottom );
	RECT					GetCompleteRectSrc	();

	//	����Ʈ �Ϸ� �������̽�
	void					SetComplete			( BOOL bComplete );
	BOOL					GetComplete			();

	//	����Ʈ Ƚ�� üũ �������̽�
	void					SetCount			( int iCount );
	int						GetCount			();

protected:

	//	����Ʈ Ƚ�� ���μ��� �������̽�
	void					ProcessCount		();

	//	����Ʈ Ƚ�� ���� �������̽�
	void					RenderCount			();

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	int						m_iQuestID;
	QUEST_NPC				m_eQuestType;
	SPQuestArchive*			m_pQuestArchive;

	SPTexture*				m_pCompleteTexture;
	RECT					m_rtCompleteSrc;
	BOOL					m_bComplete;

	int						m_iCount;

	int						m_iCountLength;

	RECT					m_rtCountSrc[ QUEST_LENGTH_MAX ];
	POINT					m_ptCountPos[ QUEST_LENGTH_MAX ];

};
