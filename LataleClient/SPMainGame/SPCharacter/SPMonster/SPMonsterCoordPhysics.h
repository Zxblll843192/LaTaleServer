// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPMonsterCoordPhysics
// Comment     : Ŭ���̾�Ʈ/���� ��� ���̴� ����̹Ƿ� Ưȭ�� ��� �߰��� ����.
//
// Creation    : metalgeni 2004-08-24 ���� 10:26:19
//***************************************************************************

#pragma once

class SPMonsterCoordPhysics : public SPGOBCoordPhysics
{
public:
#ifdef _LATALE_CLIENT
	SPMonsterCoordPhysics(SPGameObject* pkParent = NULL);
#else
	SPMonsterCoordPhysics(CCharacter* pkParent = NULL);
#endif
	virtual ~SPMonsterCoordPhysics();
	
	virtual void Init();
	virtual void Process(float fElapsedTime);

	virtual bool IsActionChange(UINT64& uiAction);

protected:
	virtual void CalVelocity(UINT64 uiAction);

	virtual void OnStateAttackSpeedY();
	virtual void OnStateAttackMighty();
	virtual void OnStateSkill();
};

#include "SPMonsterCoordPhysics.inl"