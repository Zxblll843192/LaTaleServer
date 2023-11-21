// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPPlayerEquipInfo
// Comment     : 
// Creation    : metalgeni 2004-11-20 ���� 10:26:19
//***************************************************************************

#pragma once

class SPItemStatus;
class SPGameObject;
enum EQUIP_CLASS;


class SPPlayerEquipInfo {
public:
	SPPlayerEquipInfo(SPGameObject* pParent);
	virtual ~SPPlayerEquipInfo();
	virtual void	Init();

	// ����� ����Ʈü������ ����. NULL�϶� �ƹ�Ÿ���̾��������� ����Ʈ�� ����.	
	bool			SetDefaultChange(EQUIP_ID EquipID, SPItemStatus* pItemStatus = NULL);
	bool			Restore(SPEquipLayerPool EquipLayerPool, EQUIP_ID EquipID);
	bool			Unload(EQUIP_ID EquipID);	
	bool			SetCustume(SPItemStatus* pItemStatus);

	SPItemStatus* GetItemStatus(EQUIP_ID eID);

protected:
	SPGameObject*			m_pParent;	

	SPItemStatus*			m_pEquipItem[EQ_END];
	SPItemStatus*			m_pItemStatusEquipDefaultBlouse		;
	SPItemStatus*			m_pItemStatusEquipDefaultPants		;
	SPItemStatus*			m_pItemStatusEquipDefaultHair		;
	SPItemStatus*			m_pItemStatusEquipDefaultExpression	;
	SPItemStatus*			m_pItemStatusEquipDefaultSkin		;

};














