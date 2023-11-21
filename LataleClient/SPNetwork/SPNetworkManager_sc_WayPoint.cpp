
#include "SPCommon.h"
//
#include "SPGameObjectDEF.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPGOBManager.h"

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPWindow.h"
#include "SPInterfaceManager.h"
#include "SPResourceDef.h"
#include "SPResourceManager.h"

//
#include "SPGameObject.h"
#include "SPGOBStatus.h"
#include "SPGOBClusterDef.h"
#include "SPGOBCluster.h"
#include "SPGobModelUnit.h"
#include "SPAvatarModelUnitDef.h"
#include "SPAvatarModelUnit.h"
#include "SPPlayer.h"

#include "SPEventDEF.h"
#include "SPWayPointManager.h"
#include "SPEventManager.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;


DEFINE_SC_PACKET_PROC(WAYPOINT_SC_LIST)
{
	GU_ID				ObjectGUID;								// ���ӿ�����Ʈ���̵�
	int					arrWayPoint[WAYPOINT_SIZE_DATA] = {0,};	// ��������Ʈ������

	packet->ExtractUINT64(&ObjectGUID);	

	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return;
		}
	}
	else {
		return;
	}
	
	packet->ExtractStruct(arrWayPoint, sizeof(int)*WAYPOINT_SIZE_DATA);
	g_pEventManager->GetWayPointManager()->SetSaveData(arrWayPoint);
}

DEFINE_SC_PACKET_PROC(WAYPOINT_SC_FIND)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
	int					iWayPointID;				// ��������Ʈ���̵�

	packet->ExtractUINT64(&ObjectGUID);

	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return;
		}
	}
	else {
		return;
	}

	packet->ExtractUINT32(&ErrorID);
	if(ErrorID) // ����
	{
		// ErrorID�� GLOBAL_STRING.LDT�� ���뿡�������Դϴ�.
		std::string strMsg = g_pResourceManager->GetGlobalString(ErrorID);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
		return;
	}

	packet->ExtractUINT32((UINT32*)&iWayPointID);
	g_pEventManager->GetWayPointManager()->OnUpdateNewWayPoint(iWayPointID);

}

DEFINE_SC_PACKET_PROC(WAYPOINT_SC_MOVE)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	//GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
	//int					iWayPointID;				// ��������Ʈ���̵�

	packet->ExtractUINT64(&ObjectGUID);
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return;
		}
	}
	else {
		return;
	}

	//packet->ExtractUINT32(&ErrorID);
	//if(ErrorID) // ����
	//{
	//	// ErrorID�� GLOBAL_STRING.LDT�� ���뿡�������Դϴ�.
	//	std::string strMsg = g_pResourceManager->GetGlobalString(ErrorID);
	//	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );	
	//	
	//	return;
	//}	
	//packet->ExtractUINT32((UINT32*)&iWayPointID);
	
	g_pEventManager->GetWayPointManager()->OnMove(packet);
}
