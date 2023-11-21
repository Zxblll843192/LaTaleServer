
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

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPWindow.h"
#include "SPInterfaceManager.h"

#include "SPResourceDef.h"
#include "SPResourceManager.h"

//
#include "SPEventDEF.h"
#include "SPQuestAttr.h"
#include "SPQuestArchive.h"
#include "SPQuestManager.h"
#include "SPEvent.h"
#include "SPEventManager.h"

#include "SPCheckManager.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;


DEFINE_SC_PACKET_PROC(MISSION_SC_LIST)
{
	GU_ID			ObjectGUID	= 0;	// ���ӿ�����Ʈ���̵�
	int				iCnt = 0;			// �̼� ����
	MISSION			stMission = {0,};	// �̼� ����

	packet->ExtractUINT64(&ObjectGUID);	
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return ;
		}
	}
	
	packet->ExtractUINT32((UINT32*)&iCnt);
	for(int i=0; i<iCnt; i++)
	{
		packet->ExtractStruct(&stMission, sizeof(MISSION));
		// �̼� �Ŵ����� �߰��ؾ��մϴ�.
		
		//[2005/9/27] ������ ����Ʈ�� ���� ��Ȳ�� ����
		g_pEventManager->GetQuestManager()->SetPlayerMissionInfo(&stMission);
	}
}


DEFINE_SC_PACKET_PROC(MISSION_SC_UPDATE)
{
	GU_ID			ObjectGUID	= 0;	// ���ӿ�����Ʈ���̵�
	MISSION			stMission = {0,};	// �̼� ����

	packet->ExtractUINT64(&ObjectGUID);
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return ;
		}
	}
	
	packet->ExtractStruct(&stMission, sizeof(MISSION));
	
	//[2005/9/29] ������ ����Ʈ�� �̼� ������Ʈ
	g_pEventManager->GetQuestManager()->UpdateMission(&stMission);

}


DEFINE_SC_PACKET_PROC(MISSION_SC_ACTION)
{
	GU_ID			ObjectGUID	= 0;	// ���ӿ�����Ʈ���̵�
	UINT32			uiActionID	= 0;

	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&uiActionID);
}


DEFINE_SC_PACKET_PROC(QUEST_SC_LIST)
{
	GU_ID			ObjectGUID	= 0;	// ���ӿ�����Ʈ���̵�
	int				iCnt = 0;			// ����Ʈ ����
	QUEST			stQuest = {0,};		// ����Ʈ ����

	packet->ExtractUINT64(&ObjectGUID);	
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return ;
		}
	}

	////[2005/10/6] ����Ʈ�� �ѹ��̶� �޾Ƽ� ��Ʈ�� ��Ȳ�̶��...
	//if(g_pEventManager->GetQuestManager()->IsListSort()) {
	//	return;
	//}

	packet->ExtractUINT32((UINT32*)&iCnt);
	for(int i=0; i<iCnt; i++)
	{
		packet->ExtractStruct(&stQuest, sizeof(QUEST));
		// ����Ʈ �Ŵ����� �߰��ؾ��մϴ�.
		
		//[2005/9/27] ����Ʈ�� �÷��̾��ʿ� �����ϵ��� ��
		g_pEventManager->GetQuestManager()->SetPlayerQuest(&stQuest, false);
	}	

	//[2005/10/6] ����Ʈ�� ó�� ���� ��� ����Ʈ�� ��Ʈ�ϵ��� �Ѵ� 
	if(g_pEventManager->GetQuestManager()->IsListSort() == false) {
		g_pEventManager->GetQuestManager()->SetListSort();
	}
}


DEFINE_SC_PACKET_PROC(QUEST_SC_ACCEPT)
{
	GU_ID				ObjectGUID = 0;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID = 0;							// �������̵�
	QUEST				stQuest = {0,};							// ����Ʈ ����

	packet->ExtractUINT64(&ObjectGUID);
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return ;
		}
	}

	g_pEventManager->GetQuestManager()->ResetSendBlock();
	
	packet->ExtractUINT32(&ErrorID);
	if(ErrorID) // ����
	{
		// ������ ó��
		// �����¸� �����ؾ��մϴ�.
		g_pCheckManager->SetDBBlock(false);
		
		// ErrorID�� GLOBAL_STRING.LDT�� ���뿡�������Դϴ�. 4000002
		std::string strMsg = g_pResourceManager->GetGlobalString(ErrorID);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );		
		
		return;
	}

	packet->ExtractStruct(&stQuest, sizeof(QUEST));
	//[2005/9/29] ����Ʈ�� �÷��̾��ʿ� �����ϵ��� ��
	g_pEventManager->GetQuestManager()->SetPlayerQuest(&stQuest);
	
	////
	//packet->ExtractUINT32((UINT32*)&iItemCnt);
	//if(QUEST_MAX_ACQUISITION_ITEM < iItemCnt)
	//{
	//	// *** �̰� *** �����α�
	//	return;
	//}
	//for(int i=0; i<iItemCnt; i++)
	//{
	//	packet->ExtractStruct(&arrItem[i], sizeof(CONTAINER_ITEM));		
	//}
/* 2005.10.04 dhpark ��Ŷ���� �����ϰ� ITEM_SC_CONTAINER_INFO�� �۽��մϴ�.
	//[2005/9/29] ������ ó���� ������ ó�� ��ƾ���� ����...
	// SPGM_ITEM_SC_CONTAINER_INFOS �� ���� ó����...
	// ���ʿ� ���� ������ �����Ұ�!
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	
	g_pGOBManager->SPPerformMessage(SPGM_ITEM_SC_CONTAINER_INFOS, wParam, lParam);	
*/
	g_pCheckManager->SetDBBlock(false);				//[2005/11/4] - ���������� ���⼭ ���� ���� ���ش�...

	////CutIn ����...
	//g_pEventManager->SetCutInState(CUT_IN_STATE_NULL);

	UINT8			byAcceptType;	// ����Ʈ ���� Ÿ��(1:NPC, 2:����, 4:������, 8:�̺�Ʈ)
	packet->ExtractUINT8( &byAcceptType );

	if( byAcceptType & QUEST_ACCEPTTYPE_NPC == QUEST_ACCEPTTYPE_NPC )
	{
		g_pEventManager->GetQuestManager()->LoadNpcQuest();
	}
	else
	{
		g_pEventManager->GetQuestManager()->DeleteNpcQuest( stQuest.uiQuestID );
	}

	//SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_NPC_QUEST);
	//pWindow->Show();
	//pWindow = g_pInterfaceManager->FindWindow(WIID_QUEST);
	//pWindow->Show();
}


DEFINE_SC_PACKET_PROC(QUEST_SC_CANCEL)
{
	GU_ID			ObjectGUID	= 0;	// ���ӿ�����Ʈ���̵�
	UINT32			uiQuestID = 0;		// ����Ʈ���̵�

	packet->ExtractUINT64(&ObjectGUID);
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return ;
		}
	}

	g_pEventManager->GetQuestManager()->ResetSendBlock();
	
	packet->ExtractUINT32(&uiQuestID);	
	
	//[2005/9/29]	������ ����Ʈ�� �����ϰ� ��
	g_pEventManager->GetQuestManager()->OnGiveUpQuest(uiQuestID);

	////CutIn ����...
	//g_pEventManager->SetCutInState(CUT_IN_STATE_NULL);
	
	//SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_QUEST);
	//pWindow->Show();
	//pWindow = g_pInterfaceManager->FindWindow(WIID_NPC_QUEST);
	//pWindow->Show();
}


DEFINE_SC_PACKET_PROC(QUEST_SC_FINISH)
{
	GU_ID				ObjectGUID = 0;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID = 0;							// �������̵�
	QUEST				stQuest = {0,};							// ����Ʈ ����

	packet->ExtractUINT64(&ObjectGUID);
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return ;
		}
	}

	g_pEventManager->GetQuestManager()->ResetSendBlock();
	
	packet->ExtractUINT32(&ErrorID);
	if(ErrorID) // ����
	{
		// ������ ó��
		// �����¸� �����ؾ��մϴ�.
		g_pCheckManager->SetDBBlock(false);
		
		// ErrorID�� GLOBAL_STRING.LDT�� ���뿡�������Դϴ�. 4000002
		std::string strMsg = g_pResourceManager->GetGlobalString(ErrorID);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );		
		
		return;
	}

	packet->ExtractStruct(&stQuest, sizeof(QUEST));
	g_pEventManager->GetQuestManager()->OnFinishQuest(&stQuest);

	////
	//packet->ExtractUINT32((UINT32*)&iItemCnt);
	//if(QUEST_MAX_REWARD_ITEM < iItemCnt)
	//{
	//	// *** �̰� *** �����α�
	//	return;
	//}
	//for(int i=0; i<iItemCnt; i++)
	//{
	//	packet->ExtractStruct(&arrItem[i], sizeof(CONTAINER_ITEM));
	//}
/* 2005.10.04 dhpark ��Ŷ���� �����ϰ� ITEM_SC_CONTAINER_INFO�� �۽��մϴ�.
	//[2005/9/29] ������ ó���� ������ ó�� ��ƾ���� ����...
	// SPGM_ITEM_SC_CONTAINER_INFOS �� ���� ó����...
	// ���ʿ� ���� ������ �����Ұ�!
	WPARAM wParam = (WPARAM)&ObjectGUID;
	LPARAM lParam = (LPARAM)packet;	
	g_pGOBManager->SPPerformMessage(SPGM_ITEM_SC_CONTAINER_INFOS, wParam, lParam);	
*/
	
	////CutIn ����...
	//g_pEventManager->SetCutInState(CUT_IN_STATE_NULL);

	g_pEventManager->GetQuestManager()->LoadNpcQuest();

	//SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_NPC_QUEST);
	//pWindow->Show();
	//pWindow = g_pInterfaceManager->FindWindow(WIID_QUEST);
	//pWindow->Show();
}

// ����Ʈ ����(������ ĳ���Ϳ�)
//QUEST_SC_SHARE,
// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	ErrorID;					// �������̵�
// char				szRcvCharName[LEN_NAME+1];	// �����޴� ĳ���͸�
DEFINE_SC_PACKET_PROC(QUEST_SC_SHARE)
{
	GU_ID				ObjectGUID	= 0;			// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID = 0;				// �������̵�
	char				szRcvCharName[LEN_NAME+1];	// �����޴� ĳ���͸�

	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	packet->ExtractData(szRcvCharName, LEN_NAME+1);	

	if( g_pGOBManager == NULL )
		return;

	SPPlayer*	pLocalPlayer	=	g_pGOBManager->GetLocalPlayer();

	if( pLocalPlayer == NULL )
		return;

	if( pLocalPlayer->GetGUID() != ObjectGUID )
		return;

	char			szBuf[ _MAX_PATH ];
	const char*		pszGlobalString	=	g_pResourceManager->GetGlobalString( ErrorID );

	if( pszGlobalString == NULL )
		return;

	if( strlen( pszGlobalString ) <= 0 )
		return;

	sprintf( szBuf , pszGlobalString , szRcvCharName );
	D3DXCOLOR color(1.0f, 0.0f, 0.0f, 1.0f);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szBuf , (LPARAM)&color );
}

// ����Ʈ ����(�����޴� ĳ���Ϳ�)
//QUEST_SC_SHARE_RECV,
// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
// UINT32			uiQuestID;		// ����Ʈ���̵�
// INT32			iActCharID;		// ������ ĳ����DBŰ(QUEST_CS_ACCEPT�� ������ ����ؾ��մϴ�.)
DEFINE_SC_PACKET_PROC(QUEST_SC_SHARE_RECV)
{
	GU_ID				ObjectGUID	= 0;			// ���ӿ�����Ʈ���̵�
	UINT32				uiQuestID = 0;				// ����Ʈ���̵�
	INT32				iActCharID = 0;				// ������ ĳ����DBŰ(QUEST_CS_ACCEPT�� ������ ����ؾ��մϴ�.)

	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&uiQuestID);
	packet->ExtractUINT32((UINT32*)&iActCharID);

	if( g_pGOBManager == NULL )
		return;

	SPPlayer*	pLocalPlayer	=	g_pGOBManager->GetLocalPlayer();

	if( pLocalPlayer == NULL )
		return;

	if( pLocalPlayer->GetGUID() != ObjectGUID )
		return;

	if( g_pEventManager != NULL )
	{
		SPQuestManager*	pQuestManager	=	g_pEventManager->GetQuestManager();

		if( pQuestManager != NULL )
		{
			pQuestManager->RecvQuestSharePacket( uiQuestID ,iActCharID );
		}
	}
}
