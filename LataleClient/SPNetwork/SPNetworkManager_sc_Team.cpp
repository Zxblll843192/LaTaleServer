
#include "SPCommon.h"
//
#include "SPGameObjectDEF.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPGOBManager.h"

//
#include "SPGameObject.h"
#include "SPGOBStatus.h"
#include "SPGOBClusterDef.h"
#include "SPGOBCluster.h"
#include "SPGobModelUnit.h"
#include "SPAvatarModelUnitDef.h"
#include "SPAvatarModelUnit.h"
#include "SPPlayer.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;


// ���ʴ� ���. �����ΰ��� ��û�ڿ��Ը� �۽�, �����ΰ��� ����ڿ��Ը� �۽�
// TEAM_SC_REQUEST,	// ��û�ڿ� ����ڿ��� �۽�
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// char				szCharName[LEN_NAME+1];		// �̸�
// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
DEFINE_SC_PACKET_PROC(TEAM_SC_REQUEST)
{
	GU_ID ObjectGUID;
	packet->ExtractUINT64(&ObjectGUID);

	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_INVITE, wParam, lParam);
}

// ���������� ���
// TEAM_SC_JOIN,		// ���и� ����ڿ��� �۽�, �����̸� ��� �������� �۽�
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// char				szActCharName[LEN_NAME+1];	// ��û���̸�
// GU_ID			RcvCharGUID;				// �����
// char				szRcvCharName[LEN_NAME+1];	// ������̸�
// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
// UINT8			byLootingRule;				// ���÷�(0:���ʴ��,1:����,2:����)
// int				iCnt;						// ������
// TEAM_MEMBER		stTeam_Member;				// ��������
// ...											// ��������ŭ
DEFINE_SC_PACKET_PROC(TEAM_SC_JOIN)
{
	GU_ID ObjectGUID;
	packet->ExtractUINT64(&ObjectGUID);

	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_JOIN, wParam, lParam);

}

// ��Ż�� ���.
// TEAM_SC_SECEDE,		// ��� �������� �۽�, *** ���� : ������ 2���� ��쿡 ��Ŷ�� ������ ��Ƽ�����ؾ��մϴ�.
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// GU_ID			ActCharGUID;				// Ż����
DEFINE_SC_PACKET_PROC(TEAM_SC_SECEDE)
{
	GU_ID ObjectGUID;

	packet->ExtractUINT64(&ObjectGUID);
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_SECEDE, wParam, lParam);

	// TODO : ����ó��
}

// ������
// TEAM_SC_EXPEL,		// ��� �������� �۽�, *** ���� : ������ 2���� ��쿡 ��Ŷ�� ������ ��Ƽ�����ؾ��մϴ�.
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// GU_ID			RcvCharGUID;				// ������
DEFINE_SC_PACKET_PROC(TEAM_SC_EXPEL)
{
	GU_ID ObjectGUID;

	packet->ExtractUINT64(&ObjectGUID);
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_EXPEL, wParam, lParam);
}

// �������� ���. ������ Ż���������� ���˴ϴ�.
// TEAM_SC_CHANGECAPTAIN,	// ��� �������� �۽�
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// GU_ID			RcvCharGUID;				// ������
DEFINE_SC_PACKET_PROC(TEAM_SC_CHANGECAPTAIN)
{
	GU_ID ObjectGUID;

	packet->ExtractUINT64(&ObjectGUID);
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_CHANGE_MASTER, wParam, lParam);
}

// ���÷꺯�� ���
// TEAM_SC_CHANGELOOTINGRULE,	// ��� �������� �۽�
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// UINT8			byLottingRule;				// �����÷�
DEFINE_SC_PACKET_PROC(TEAM_SC_CHANGELOOTINGRULE)
{
	GU_ID ObjectGUID;

	packet->ExtractUINT64(&ObjectGUID);
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_CHANGE_LOOTING, wParam, lParam);
}

// ������������ ���(�������� �����⸸ ��) : ������� ���������� �ʿ�
// TEAM_SC_UPDATEMEMBER,	// ��� �������� �۽�. *** ���� : ��ε�ĳ���ÿ��� ���� ������ �����մϴ�. �������� ������ ��ε�ĳ���������� �� ��Ȯ�մϴ�.
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// TEAM_MEMBER		stTeam_Member;				// ��������
DEFINE_SC_PACKET_PROC(TEAM_SC_UPDATEMEMBER)
{
	GU_ID ObjectGUID;

	packet->ExtractUINT64(&ObjectGUID);
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_UPDATE_MEMBER, wParam, lParam);
}

// �������۽�(ä���̵��� �������� ������ �۽Ž� ���)
//TEAM_SC_INFO,
// GU_ID					ObjectGUID;						// ���ӿ�����Ʈ���̵�
// UINT8					byLootingRule;					// ���÷�(0:���ʴ��,1:����,2:����)
// int						iCnt;							// ������
// TEAM_MEMBER				stTeam_Member;					// ��������
// ...														// ��������ŭ
DEFINE_SC_PACKET_PROC(TEAM_SC_INFO)
{
	GU_ID					ObjectGUID;

	packet->ExtractUINT64(&ObjectGUID);
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	

	g_pGOBManager->SPPerformMessage(SPGM_TEAM_CHANNEL_MOVE, wParam, lParam);

/*	GU_ID					ObjectGUID;
	UINT8					byLootingRule;					// ���÷�(0:���ʴ��,1:����,2:����)
	int						iCnt;							// ������
	TEAM_MEMBER				stTeam_Member;					// ��������

	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT8(&byLootingRule);
	packet->ExtractUINT32((UINT32*)&iCnt);
	for(int i=0; i<iCnt; i++)
	{
		packet->ExtractStruct(&stTeam_Member, sizeof(TEAM_MEMBER));
	}

	*/
}
