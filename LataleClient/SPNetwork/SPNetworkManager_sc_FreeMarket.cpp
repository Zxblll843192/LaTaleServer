
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

#include "DebugPrint.h"

extern SPNetworkManager* g_pNetworkManager;


DEFINE_SC_PACKET_PROC(FREEMARKET_SC_OPEN)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	//GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
	//char				szFMName[FM_MAX_NAME+1];	// ������

	packet->ExtractUINT64(&ObjectGUID);	

	////
	//packet->ExtractUINT32(&ErrorID);
	//if(0 == ErrorID)
	//{
	//	packet->ExtractData(szFMName, FM_MAX_NAME+1);
	//}

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;
	g_pGOBManager->SPPerformMessage(SPGM_USERSHOP_SC_OPEN, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(FREEMARKET_SC_CLOSE)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	//GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT32(&ErrorID);

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;
	g_pGOBManager->SPPerformMessage(SPGM_USERSHOP_SC_CLOSE, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(FREEMARKET_SC_IN)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	//GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
	//UINT32				uiCnt;								// �Ǹž����� ����
	//FM_VIEWITEM			arrFM_ViewItem[FM_MAX_SELLITEM];	// �Ǹž����� ����	
	
	////
	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT32(&ErrorID);
	//if(0 == ErrorID)
	//{
	//	packet->ExtractUINT32(&uiCnt);
	//	if(uiCnt <= FM_MAX_SELLITEM)
	//	{
	//		for(int i=0; i<uiCnt; i++)
	//		{
	//			packet->ExtractStruct(&arrFM_ViewItem[i], sizeof(FM_VIEWITEM));
	//		}
	//	}
	//}

	DebugPrint("\t  - FREEMARKET_SC_IN\n");

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;
	g_pGOBManager->SPPerformMessage(SPGM_USERSHOP_SC_IN, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(FREEMARKET_SC_OUT)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�

	DebugPrint("\t  - FREEMARKET_SC_OUT\n");

	packet->ExtractUINT64(&ObjectGUID);
	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = 0;
	g_pGOBManager->SPPerformMessage(SPGM_USERSHOP_SC_OUT, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(FREEMARKET_SC_BUY)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	//GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
	//FM_ITEM				stFM_Item;					// �Ǹŵ� ������ ����

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT32(&ErrorID);
	//if(0 == ErrorID)
	//{
	//	packet->ExtractStruct(&stFM_Item, sizeof(FM_ITEM));
	//}

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;
	g_pGOBManager->SPPerformMessage(SPGM_USERSHOP_SC_BUY, wParam, lParam);
}
