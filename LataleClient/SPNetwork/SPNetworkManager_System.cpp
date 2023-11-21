

//***************************************************************************
// System Name : SPNetworkManager_System.cpp
// Comment     : 
//  [3/20/2008 metalgeni]
//  ReportShot �� �ý��۰��� ���� �߰��� ���� ����߰�
//***************************************************************************



#include "SPCommon.h"
//
#include "SPGameObjectDEF.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPGOBManager.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPGameObjectDEF.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPGOBManager.h"
#include "SPSubGameManager.h"
#include "SPMainGameManager.h"

// 2008.05.26 dhpark ������ ����
#include "../NPGameGuard/SPGameGuard.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;


DEFINE_CS_PACKET_PROC(SERVERTIME_CS_INFO)
{
	CPacket Packet;
	Packet.Add((UINT32)SERVERTIME_CS_INFO);

	GetPacketHandler()->PostMsg(&Packet);

	return 0;
}



// �����ð�/���� �۽�(MAX_LEN_ID, LEN_IP�� ������ �����Դϴ�.)
//SERVERTIME_SC_INFO,
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// SYSTEMTIME		stServerTime;				// �����ð�
// WORLD_ID			wWorldID;					// ������̵�
// SERVER_ID		wServerID;					// �������̵�
// TCHAR			szAccountID[MAX_LEN_ID];	// �������̵�
// TCHAR			szClientIP[LEN_IP];			// Ŭ���̾�Ʈ������
// TCHAR			szName[LEN_NAME+1];			// ĳ���͸�
// UINT				uiStageID;					// �����������̵�
// UINT				uiMapGroupID;				// �ʱ׷���̵�
// UINT				uiPosX;						// X��ǥ
// UINT				uiPosY;						// Y��ǥ
DEFINE_SC_PACKET_PROC(SERVERTIME_SC_INFO)
{
	GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
	SYSTEMTIME		stServerTime;				// �����ð�
	WORLD_ID		wWorldID;					// ������̵�
	SERVER_ID		wServerID;					// �������̵�
	TCHAR			szAccountID[MAX_LEN_ID];	// �������̵�
	TCHAR			szClientIP[LEN_IP];			// Ŭ���̾�Ʈ������
	TCHAR			szName[LEN_NAME+1];			// ĳ���͸�
	UINT			uiStageID;					// �����������̵�
	UINT			uiMapGroupID;				// �ʱ׷���̵�
	UINT			uiPosX;						// X��ǥ
	UINT			uiPosY;						// Y��ǥ

	ReportStuff rsStuffInstance;

	packet->ExtractUINT64(&rsStuffInstance.ObjectGUID); 
	packet->ExtractStruct(&rsStuffInstance.stServerTime, sizeof(SYSTEMTIME));
	packet->ExtractUINT16(&rsStuffInstance.wWorldID);
	packet->ExtractUINT16(&rsStuffInstance.wServerID);
	packet->ExtractData(rsStuffInstance.szAccountID, MAX_LEN_ID);
	packet->ExtractData(rsStuffInstance.szClientIP, LEN_IP);
	packet->ExtractData(rsStuffInstance.szName, LEN_NAME+1);
	packet->ExtractUINT32(&rsStuffInstance.uiStageID);
	packet->ExtractUINT32(&rsStuffInstance.uiMapGroupID);
	packet->ExtractUINT32(&rsStuffInstance.uiPosX);
	packet->ExtractUINT32(&rsStuffInstance.uiPosY);

	if(g_pMainGameManager)
		g_pMainGameManager->ReportShot(&rsStuffInstance);


}

// �������� Query()�� ���ؼ� ������ ������ ������ �۽�
//SECURITY_SC_CHECK = SECURITY_CS_BASE,
// SECURITY_PACKDATA	stPackData;				// ������ ������ ������
DEFINE_SC_PACKET_PROC(SECURITY_SC_CHECK)
{
	SECURITY_PACKDATA	stPackData = {0,};				// ������ ������ ������

	packet->ExtractStruct(&stPackData, sizeof(SECURITY_PACKDATA));

	// ���� Ŭ���̾�Ʈ�� ���ȸ��� ������ ���� / ������ �۽�
	// nProtect�� �ݹ��Լ��� ���ο��� ��Ŷ�۽��ϰ� XTrap�� �ٷ� �۽��մϴ�. ��� ���ο��� ��Ŷ�۽��ϵ��� ó��.
	SPGameGuard::GetInstance()->Auth(&stPackData);
}

// ������ �˻� ��� �뺸. �޼���â�� ���ؼ� Ŭ���̾�Ʈ ������� �����մϴ�.
//SECURITY_SC_INFO,
// GLOBAL_STRING_ID		ErrorID;				// �������̵�
DEFINE_SC_PACKET_PROC(SECURITY_SC_INFO)
{
	GLOBAL_STRING_ID		ErrorID = 0;				// �������̵�

	packet->ExtractUINT32(&ErrorID);

	if(0 != ErrorID)
	{
		g_pSubGameManager->SPPerformMessage(SPGM_SUG_SOCKET_FAILED, ErrorID, 0);
		g_pNetworkManager->SetExceptSocketFailed(true);
	}
}














