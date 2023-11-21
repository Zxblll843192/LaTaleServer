#pragma once 

#include "SPQuestAttr.h"


enum CORE_MISSION_TYPE {
	CORE_MISSION_TYPE_NULL,							/**< �̼� ���� <br> */
	CORE_MISSION_TYPE_QUEST,						/**< �̼� ����Ʈ <br> */
	CORE_MISSION_TYPE_ITEM,							/**< �̼� ������ <br> */
	CORE_MISSION_TYPE_EFFECT,						/**< �̼� ȿ�� <br> */
};


class SPCoreMissionAttr {
public:
	SPCoreMissionAttr();
	~SPCoreMissionAttr();	

	bool	CheckRequire();
	void	SetSavePos(int iIndex);

private:
	void	Clear();

public:
	int								m_iID;				/**< �ش� ID <br> */
	CORE_MISSION_TYPE				m_iType;			/**< �̼� Ÿ�� <br> */
	int 							m_iSavePos;			/**< �����ϴ� ��� � ��ġ���� <br> */
	//int							m_iQuest;
	//SPQuestItem					m_iItem[];
	//int							m_iEffect[];
	SPRequire						m_Require[MAX_CORE_EVENT_REQUIRE];	/**< �̼� ���� �����̾� <br> */
};


