
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
#include "GlobalDefines_Share.h"
#include "SPGuildArchive.h"
#include "SPSubGameManager.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;



DEFINE_SC_PACKET_PROC(INDUN_SC_IN)
{
	WPARAM wParam = 0;
	LPARAM lParam = (LPARAM)packet;

	if(g_pSubGameManager)
		g_pSubGameManager->SPPerformMessage(SPGM_INDUN_IN, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(INDUN_SC_OUT)
{
	WPARAM wParam = 0;
	LPARAM lParam = (LPARAM)packet;

	if(g_pSubGameManager)
		g_pSubGameManager->SPPerformMessage(SPGM_INDUN_OUT, wParam, lParam);
	
}

// �δ� �ʱ�ȭ ��û ���. �����ϰ� �ִ� �δ��� ������ uiIndunLDTID�� 0�Դϴ�.
//INDUN_SC_INIT,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
// UINT32			uiIndunLDTID;						// �δ� LDT ���̵�
// GLOBAL_STRING_ID	ErrorID;							// �������̵�
DEFINE_SC_PACKET_PROC(INDUN_SC_INIT)
{
	WPARAM wParam = 0;
	LPARAM lParam = (LPARAM)packet;

	if(g_pSubGameManager)
		g_pSubGameManager->SPPerformMessage(SPGM_INDUN_RESET, wParam, lParam);
}
