// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPAvatarModelUnitDef
// Comment     : 
// Creation    : metalgeni 2004-11-02 ���� 10:26:19
//***************************************************************************

#pragma once

#include <map>
#include <vector>
using namespace std;

enum PART_LAYER;
enum EQUIP_CLASS {
	EQCLASS_INVAILD	= -1,
	EQCLASS_NULL	= 0,
	EQCLASS_0001	=	1,   //�׽�Ʈ��
	
	EQCLASS_FIRST	=   101		,
	
	EQCLASS_0101	=	101		,	//��� ���� �尩	�尩
	EQCLASS_0102	=	102		,	//��� �ִ� �尩	
	EQCLASS_0103	=	103		,	//����	
	EQCLASS_0201	=	201		,	//�Ҹ� ���� ���� ���� ���� (����)	����
	EQCLASS_0202	=	202		,	//�Ҹ� �ְ� ���� ���� ���� (����)	
	EQCLASS_0203	=	203		,	//�Ҹ� ���� ���� �ִ� ���� (����)	
	EQCLASS_0204	=	204		,	//�Ҹ� �ְ� ���� �ִ� ���� (����)	
	EQCLASS_0205	=	205		,	//�Ҹ� ���� ���� ���� ���� (����)	
	EQCLASS_0206	=	206		,	//�Ҹ� �ְ� ���� ���� ���� (����)	
	EQCLASS_0207	=	207		,	//�Ҹ� ���� ���� �ִ� ���� (����)	
	EQCLASS_0208	=	208		,	//�Ҹ� �ְ� ���� �ִ� ���� (����)	
	EQCLASS_0209	=	209		,	//�Ҹ� ���� ���� ���� ���� (����)	
	EQCLASS_0210	=	210		,	//�Ҹ� �ְ� ���� ���� ���� (����)	
	EQCLASS_0211	=	211		,	//�Ҹ� ���� ���� �ִ� ���� (����)	
	EQCLASS_0212	=	212		,	//�Ҹ� �ְ� ���� �ִ� ���� (����)	
	EQCLASS_0301	=	301		,	//���� ���� (����)	����
	EQCLASS_0302	=	302		,	//���� ���� (����)	
	EQCLASS_0303	=	303		,	//���� ���� (����)	
	EQCLASS_0304	=	304		,	//ġ�� ���� (����)	
	EQCLASS_0401	=	401		,	//����	����
	EQCLASS_0501	=	501		,	//���� ���� �Ҹ� ���� ���� ���� ���� �ѹ��� (���� ������)	�ѹ���
	EQCLASS_0502	=	502		,	//���� �Ҹ� ���� ���� ���� ���� �ѹ��� (����)	
	EQCLASS_0503	=	503		,	//���� �Ҹ� �ְ� ���� ���� ���� �ѹ��� (����)	
	EQCLASS_0504	=	504		,	//���� �Ҹ� ���� ���� �ְ� ���� �ѹ��� (����)	
	EQCLASS_0505	=	505		,	//���� �Ҹ� �ְ� ���� �ְ� ���� �ѹ��� (����)	
	EQCLASS_0506	=	506		,	//���� �Ҹ� ���� ���� ���� ���� �ѹ��� (����)	
	EQCLASS_0507	=	507		,	//���� �Ҹ� �ְ� ���� ���� ���� �ѹ��� (����)	
	EQCLASS_0508	=	508		,	//���� �Ҹ� ���� ���� �ְ� ���� �ѹ��� (����)	
	EQCLASS_0509	=	509		,	//���� �Ҹ� �ְ� ���� �ְ� ���� �ѹ��� (����)	
	EQCLASS_0510	=	510		,	//���� �Ҹ� ���� ���� ���� ���� �ѹ��� (����)	
	EQCLASS_0511	=	511		,	//���� �Ҹ� �ְ� ���� ���� ���� �ѹ��� (����)	
	EQCLASS_0512	=	512		,	//���� �Ҹ� ���� ���� �ְ� ���� �ѹ��� (����)	
	EQCLASS_0513	=	513		,	//���� �Ҹ� �ְ� ���� �ְ� ���� �ѹ��� (����)	
	EQCLASS_0514	=	514		,	//���� �Ҹ� ���� ���� ���� ġ�� �ѹ��� (����)	
	EQCLASS_0515	=	515		,	//���� �Ҹ� �ְ� ���� ���� ġ�� �ѹ��� (����)	
	EQCLASS_0516	=	516		,	//���� �Ҹ� ���� ���� �ְ� ġ�� �ѹ��� (����)	
	EQCLASS_0517	=	517		,	//���� �Ҹ� �ְ� ���� �ְ� ġ�� �ѹ��� (����)	
	EQCLASS_0601	=	601		,	//��Ÿŷ	��Ÿŷ
	EQCLASS_0701	=	701		,	//�� ���� �Ź�	�Ź�
	EQCLASS_0702	=	702		,	//�� �ִ� �Ź�	
	EQCLASS_0703	=	703		,	//����	
	EQCLASS_0801	=	801		,	//��Ŭ	���� �������
	EQCLASS_0802	=	802		,	//�ܰ�	
	EQCLASS_0803	=	803		,	//��	
	EQCLASS_0804	=	804		,	//��հ�	
	EQCLASS_0805	=	805		,	//��	
	EQCLASS_0806	=	806		,	//�̵�	
	EQCLASS_0807	=	807		,	//�б�	
	EQCLASS_0808	=	808		,	//â	
	EQCLASS_0809	=	809		,	//Ȱ	
	EQCLASS_0810	=	810		,	//����	
	EQCLASS_0811	=	811		,	//����
	EQCLASS_0812	=	812		,	//������
	//  [8/10/2007 metalgeni] ���� ī�װ� �߰�
	EQCLASS_0813	=	813		,	//��Ÿ(�Ǳ�)
	EQCLASS_0814	=	814		,	//�ֱ���

	EQCLASS_0901	=	901		,	//���Ӹ��� ���� �ոӸ� ���	�Ӹ����
	EQCLASS_0902	=	902		,	//���Ӹ��� ���� �ʴ� �ոӸ� ���	
	EQCLASS_0903	=	903		,	//�޸Ӹ� ���	
	EQCLASS_0904	=	904		,	//���Ӹ��� ���� ��,�� �Ӹ� ���	
	EQCLASS_0905	=	905		,	//���Ӹ��� ���� �ʴ� ��,�� �Ӹ� ���	
	EQCLASS_0906	=	906		,	//�Ӹ� ��ü�� ���� ���	
	EQCLASS_1001	=	1001	,	//�Ȱ�	�Ȱ�
	EQCLASS_1101	=	1101	,	//�Ͱ���	�Ͱ���
	EQCLASS_1201	=	1201	,	//�� ���	�� ���
	EQCLASS_1301	=	1301	,	//�Ӹ�ī�� (����)	�Ӹ�ī��
	EQCLASS_1302	=	1302	,	//�Ӹ�ī�� (����)	
	EQCLASS_1401	=	1401	,	//�� ǥ�� (����)	�� ǥ��
	EQCLASS_1402	=	1402	,	//�� ǥ�� (����)	
	EQCLASS_1501	=	1501	,	//�Ǻλ�	�Ǻλ�
	EQCLASS_1601	=	1601	,	//��� ȿ��	���ȿ��
	EQCLASS_1701	=	1701	,	//�Ҹ���, ��ɼ� ������	������
	EQCLASS_1801	=	1801	,	//���� �Ű��� ������	
	EQCLASS_1901	=	1901	,	//�̺�Ʈ �߿� ������	
	EQCLASS_2001	=	2001	,	//�Ͽ�¡ ������	

	EQCLASS_LAST	=   2002	
};

enum EQUIP_ID {
	EQ_INVAILD	= -1,
	EQ_NULL		= 0,

	EQ_FIRST	= 1,

	EQ_HAIR_DRESS	= 1,		// �Ӹ���� ( ���� )
	EQ_GOGGLE		= 2,		// �Ȱ�
	EQ_EARRING		= 3,		// �Ͱ���
	EQ_BLOUSE		= 4,		// ����
	EQ_PANTS		= 5,		// ����
	EQ_CLOAK		= 6,		// ����
	EQ_GLOVES		= 7,		// �尩
	EQ_SHOES		= 8,		// �Ź�
	EQ_STOCKINGS	= 9,		// ��Ÿŷ
	EQ_MAKEUP		= 10,		// ȭ�� (�����)

	EQ_STONE		= 11,		// ���ɼ�
	EQ_RING			= 12,		// ����

	EQ_WEAPON1		= 13,		// ����1
	EQ_BUCKLER1		= 14,		// ����1
	EQ_WEAPON2		= 15,		// ����2
	EQ_BUCKLER2		= 16,		// ����2	

	EQ_HAIR			= 17,		// �Ӹ�
	EQ_EXPRESSION	= 18,		// ǥ��
	EQ_SKIN			= 19,		// �Ǻλ���

	EQ_ONE_PIECE	= 20,		// �ѹ���

	EQ_END,

	//0	null
	//(�ǱԾ�, �м� ����)
	//1	�Ӹ����
	//2	�Ȱ�
	//3	�Ͱ���
	//4	����
	//5	����
	//6	����
	//7	�尩
	//8	�Ź�
	//9	��Ÿŷ
	//10	�����
	//11	���ɼ�
	//12	����
	//13	�Ѽչ���
	//13	��չ���
	//14	����
	//4	�ѹ���
	//(�Һ��� ����Ʈ ����)
	//1	�ӿʻ���
	//2	�ӿ�����
	//3	�Ӹ�ī��
	//4	��ǥ��
	//5	�Ǻλ�
	//(�� ��� ����)
	//1	�Ӹ�
	//2	��


};


#ifndef _LATALE_SERVER

// ������ ����� ��Ʈ��ȯ
enum CHANGE_TYPE {
	CTYPE_INVAILD	= -1,
	CTYPE_O,		// ���̾���					(O)
	CTYPE_X,		// ���̾������				(X)
	CTYPE_PC,		// �ٸ��ִϸ��̼���Ʈ�� ��ȯ	(Part Change)
	CTYPE_NC,		// ������� ����				(No Change)
	CTYPE_DC		// �ʱⰪ���� ����				(Default Change)
};

//[xialin 2008/07/29] add
enum LOBBY_AVATAT {
	LOBBY_NULL = 0,
	LOBBY_CASH,
	LOBBY_INFO,
};

struct SPEquipLayerPool {
	PART_LAYER	PartLayer;
	EQUIP_CLASS	EquipClass;
	int			iItemID;
	int			iItemColor;
	SPEquipLayerPool();
};


// �ѹ� �����ؼ� ����Ÿ�� �� Ŭ����
struct SPEquipLayerSet {
	PART_LAYER	PartLayer;
	CHANGE_TYPE	ChangeType;
};

struct SPEquipPart {
	EQUIP_ID	EquipID;
	int			iNOEquipLayer;
	std::vector<PART_LAYER>	vPartLayer;
	std::map<EQUIP_CLASS, std::vector<SPEquipLayerSet> >	mvLayerEquipSet;

	SPEquipPart()
	: EquipID(EQ_NULL)
	, iNOEquipLayer(0)
	{}
};

struct SPEquipRestore {
	PART_LAYER PartLayer;
	std::vector<EQUIP_ID> vRestoreEquipID;
};


extern SPEquipPart g_aEquipPart[EQ_END];
void InitEquipPart();


extern SPEquipRestore g_aEquipRestore[PL_LAST];
void InitEquipRestore();



bool IsDefaultEquip(EQUIP_ID EquipID);


#endif



















