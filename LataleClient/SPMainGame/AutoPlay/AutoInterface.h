#pragma once

#include "SPCommandConvert.h"
#include "SPGOBManager.h"
#include "SPGOBCoordPhysics.h"
#include "SPGameObject.h"
#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPPlayerInvenArchive.h"
#include "SPPlayer.h"
#include "SPPlayerActionManager.h"

#include "SPSoundManager.h"
#include "SPSkill.h"
#include "SPSkillArchive.h"
#include "SPMotionStatus.h"
#include "SPSkillManager.h"


enum  AUTO_STATUS
{
	AUTO_MOVE		= 0,	//��ΧѲ��
	AUTO_MOVETO,			//�ƶ���Ŀ��
	AUTO_MOVE_RECORD,		//����������ƶ�
};


struct   ACTION_LIST
{
	float		fPosX;
	float		fPosY;
	FACING		eFacing;
	UINT64      uiAction;

	ACTION_LIST()
	{
		fPosX		= 0.0f;
		fPosY		= 0.0f;
		eFacing		= FACING_LEFT;
		uiAction	= ACTION_STOP;
	}
};


class CAutoInterface
{
public:
	CAutoInterface(void);
	~CAutoInterface(void);

	static CAutoInterface &  GetInstance()
	{
		static  CAutoInterface  _inst;
		return  _inst;
	}
	
	bool		Initial();
	void		Destroy();
	void		Process( float fTime );
	void		Render( float fTime );

	void		Start(int iOper);	//1,¼�� 2,�һ�
	void		Stop(int iOper);
	bool		isStart() { return m_bAutoPlay; }
	bool		isRecord() { return m_bAutoRecord; }

	void        InitQuickSlot();

	void		RecordAction(UINT64 uiAction);

	bool		CheckAttackRgn(int iSkillID);
	bool		FindMonster();
	bool		FindActionIndex();
	void		Move(float fTime);

	//=====================================================
	float       GetPlayerPosX();
	float       GetPlayerPosY();
	int			GetDirection();
	float       GetMapWidth();
	float       GetMapHeight();
	UINT		GetPlayerStatus(STATUS_TYPE type);

	bool		GetMoveEnable();
	bool		CheckBlock(int iDir = 0);  //0:�������ҷ������ 1:��, 2:��

	void		SetAction( UINT64 uiAction );
	UINT64		GetAction();
	void		SetSkillAction( int iSkillID );

	bool		UseSkillAttack();
	void		UseSkill2();
	bool		UseHPItem(int iIndex = 0);
	bool		UseSPItem(int iIndex = 0);
	bool		UseReturnItem();


	//��Ϣ
	bool		WndProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	bool						m_bAutoPlay;
	bool						m_bAutoRecord;
	AUTO_STATUS					m_eAutoStatus;
	AUTO_STATUS					m_eLastStatus;			//���Ķ���״̬

	SPPlayer *					m_pLocalPlayer;
	SPPlayerActionManager*		m_pPlayerActionManager;
	SPSkillUsed	*				m_pkSkillUsed;

	//
	int							m_iCurSkillIndex;
	std::vector<UINT>			m_vSkillID;				//���ʹ�õļ���
	std::vector<UINT>			m_vSkillID2;			//���ʹ�õĸ�������
	std::vector<UINT>			m_vHPItemID;			//���ʹ�õĺ�
	std::vector<UINT>			m_vSPItemID;			//���ʹ�õ���
	std::vector<UINT>			m_vReturnTtemID;		//���ʹ�õĻس���Ʒ

	//
	int							m_iMonsterDst;			//Ѱ�־���
	POINT						m_iPlayerDstPos;		//����ƶ�Ŀ��
	FACING						m_eFacing;				//Ŀ�귽��
	bool						m_bLastAttack;			//������Ƿ�Ϊ����
	GOB_STATE_TYPE				m_eLastGobStateType;

	int							m_iCurActionIndex;		//��ǰ�������
	vector<ACTION_LIST>			m_vActionList;			//��Ҷ����б�
	
};
