// SPNetworkManager_sc_Event.cpp

#include "SPCommon.h"
//
#include "SPGameObjectDEF.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPGOBManager.h"
#include "SPSubGameManager.h"
#include "SPMainGameManager.h"

//
#include "SPGameObject.h"
#include "SPGOBStatus.h"
#include "SPGOBClusterDef.h"
#include "SPGOBCluster.h"
#include "SPGobModelUnit.h"
#include "SPAvatarModelUnitDef.h"
#include "SPAvatarModelUnit.h"
#include "SPPlayerInvenArchive.h"
#include "SPPlayerStatus.h"
#include "SPPlayer.h"

#include "SPItemAttr.h"
#include "SPItemCluster.h"

#include "SPSkill.h"

#include "SPEventDEF.h"
#include "SPCoreMissionAttr.h"
#include "SPCoreMissionArchive.h"
#include "SPCoreEventManager.h"
#include "SPQuestManager.h"
#include "SPClassChangeManager.h"
#include "SPEventManager.h"

#include "SPCheckManager.h"

#include "SPLDTFile.h"
#include "SPLDTManager.h"
#include "SPResourceDef.h"
#include "SPResourceManager.h"

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPWindow.h"
#include "SPInterfaceManager.h"

#include "SPCheckManager.h"

#include <WinSock2.h>
#include "LT_Error.h"
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;


//  Ŭ����..
DEFINE_SC_PACKET_PROC(EVENT_SC_RAISE)
{
	RESULTCODE			resultCode;
	GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

	packet->ExtractUINT8(&resultCode);
	if(resultCode != LT_NO_ERROR) {
		packet->ExtractUINT32(&ErrorID);			// If Error then Show GlobalString message at Chatting Window
		if( g_pResourceManager->GetGlobalString(ErrorID))
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		return;
	}

	WPARAM wParam = NULL;
	LPARAM lParam = (LPARAM)packet;	
	
	//g_pSubGameManager->SPPerformMessage(SPGM_EVENT_SC_ENTER, wParam, lParam);
	g_pGOBManager->SPPerformMessage(SPGM_EVENT_SC_ENTER, wParam, lParam);
}


DEFINE_SC_PACKET_PROC(EVENTMISSION_SC_LIST)
{
	GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
	int				arrFlagSave[MAX_EVENT_MISSION_DATA] = {0, };	// CP_EVENT_MISSION.ldt::_Save ����ŷ��	

	packet->ExtractUINT64(&ObjectGUID);	
	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return;
		}
	}
	else {
		return;
	}

	packet->ExtractStruct(arrFlagSave, sizeof(int)*MAX_EVENT_MISSION_DATA);
	g_pEventManager->GetCoreEventManager()->SetPlayerMissionData(arrFlagSave);
}


DEFINE_SC_PACKET_PROC(EVENTMISSION_SC_RAISE)
{
	GU_ID				ObjectGUID;		// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	iErrorID;		// �������̵�,  0 �ΰ�츸 ���� �����ͼ۽�
	UINT32				iMissionID;		// CP_EVENT_MISSION.ldt::_Item_ID
	UINT8				iMissionType;	// CP_EVENT_MISSION.ldt::_MissionType
	UINT32				iMissionFlag;	// ������ �̺�Ʈ�̼��÷��װ�(0�̸� �������)
	UINT8			iNumOfItem;			// ���� �����ۼ�
	CONTAINER_ITEM   stItem;			// ���� ������

	packet->ExtractUINT64(&ObjectGUID);

	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return;
		}
	}
	else {
		return;
	}

	packet->ExtractUINT32(&iErrorID);
	if(iErrorID) // ����
	{
		g_pCheckManager->SetDBBlock(false);
		
		// iErrorID�� GLOBAL_STRING.LDT�� ���뿡�������Դϴ�.
		std::string strMsg = g_pResourceManager->GetGlobalString(iErrorID);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
		return;
	}
	else {
		packet->ExtractUINT32((UINT32*)&iMissionID);
		//g_pEventManager->GetCoreEventManager()->SetPlayerMission(iMissionID);

		packet->ExtractUINT8((UINT8*)&iMissionType);
		if(iMissionType != CORE_MISSION_TYPE_QUEST) {
			g_pCheckManager->SetDBBlock(false);
		}

		packet->ExtractUINT32((UINT32*)&iMissionFlag);
		if(iMissionFlag){
			//[2007/10/8] - ��Ŷ�� 1���̽� �����ʹ� 0���̽� ����
			iMissionFlag -= 1;
			g_pEventManager->GetCoreEventManager()->SetPlayerMission(iMissionFlag);
		}

		SPItemAttr* pItemAttr = NULL;
		char szMsg[256];
		packet->ExtractUINT8((UINT8*)&iNumOfItem);	
		for(int i = 0; i < iNumOfItem; i++) {
			ZeroMemory(&stItem, sizeof(CONTAINER_ITEM));
			packet->ExtractStruct(&stItem, sizeof(CONTAINER_ITEM));
			stItem.SlotInfo.SlotIndex = stItem.SlotInfo.SlotIndex - 1;
			g_pGOBManager->GetLocalPlayer()->GetInvenArchive()->ItemSetting(stItem, false);

			pItemAttr = NULL;
			ZeroMemory(szMsg, 256);

			if( g_pItemCluster->GetItemInfo(stItem.Item.iItemID, pItemAttr) ) {				
				D3DXCOLOR color;
				if(pItemAttr->m_bNameColor) {
					color = pItemAttr->GetNameColor();
				}
				else {
					color = g_pCheckManager->GetItemColor(stItem.Item.iRare);
				}

				sprintf(szMsg, g_pResourceManager->GetGlobalString(5017006), pItemAttr->m_strName.c_str());

				//if(g_pClientOption->GetOptionStruct()->bItem) {
				g_pInterfaceManager->SPChildWndSendMessage( WIID_SYSTEM_MESSAGE , SPIM_SYSTEM_MESSAGE_ADD , (WPARAM)szMsg , (LPARAM)&color );
				//}

				g_pEventManager->GetQuestManager()->CheckMissionItem(stItem.Item.iItemID);
			}
		}
	}	
}


DEFINE_SC_PACKET_PROC(CHAR_SC_CHANGE_CLASS)
{
	GU_ID				ObjectGUID;				// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	iErrorID;				// �������̵�,  0 �ΰ�츸 ���� �����ͼ۽�
	UINT8				NewClassType;			// ����� Ŭ���� Ÿ��
	UINT64				iCurrEly;		// �� 
	UINT16				iSkillFreePoint;		// SKILL_SC_INIT�� ������ �̺�Ʈ ó�����
	UINT8				iNumOfLevelUpChange;	// tStatPack �� ����
	STATUS_CHANGE		tStatPack;				// �ٲ� �ɷ�ġ 	
	STATUS_INFO			statInfo ;
	UINT8				iNumOfItem;				// ���������� �ؼ� �����Ǵ� ������
	CONTAINER_ITEM		aryContainerItem;		// �߰� ������
	TRASH_ITEM			stTrashItem;			// �ı� ������

	packet->ExtractUINT64(&ObjectGUID);

	if(g_pGOBManager->GetLocalPlayer()) {
		if(g_pGOBManager->GetLocalPlayer()->GetGUID() != ObjectGUID) {
			return;
		}
	}
	else {
		return;
	}

	g_pCheckManager->SetDBBlock(false);

	packet->ExtractUINT32(&iErrorID);
	if(iErrorID) // ����
	{
		// iErrorID�� GLOBAL_STRING.LDT�� ���뿡�������Դϴ�.
		std::string strMsg = g_pResourceManager->GetGlobalString(iErrorID);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
		return;
	}
	else {
		packet->ExtractUINT8(&NewClassType);
		SPPlayerStatus* pStatus = (SPPlayerStatus*)g_pGOBManager->GetLocalPlayer()->GetStatus();
		if(pStatus) {
			pStatus->SetStatusValue(STATUS_CLASS_TYPE, NewClassType);
		}
		
		packet->ExtractUINT64(&iCurrEly);		
		g_pGOBManager->GetLocalPlayer()->GetStatus()->SetStatusValueEX(STATUS_EX_ELY, iCurrEly);
		
		packet->ExtractUINT16(&iSkillFreePoint);		
		g_pGOBManager->GetLocalPlayer()->SetSkillInitData( SSC_SKILL , iSkillFreePoint , true );
		
		packet->ExtractUINT8(&iNumOfLevelUpChange);
		bool bRet = false;
		int i = 0;
		for(i = 0; i < iNumOfLevelUpChange; i++) {
			packet->ExtractStruct(&tStatPack, sizeof(STATUS_CHANGE) );
			bRet &= pStatus->SetStatusValue((STATUS_TYPE)tStatPack.eType, tStatPack.uiValue);
		}

		packet->ExtractStruct(&statInfo, sizeof(STATUS_INFO));
		g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_SET_SC_STATUSINFO, (WPARAM)&statInfo);

		packet->ExtractUINT8(&iNumOfItem);
		char szMsg[256];
		SPItemAttr* pItemAttr = NULL;
		for(i = 0; i < iNumOfItem; i++) {
			ZeroMemory(&aryContainerItem, sizeof(CONTAINER_ITEM));
			packet->ExtractStruct(&aryContainerItem, sizeof(CONTAINER_ITEM));
			aryContainerItem.SlotInfo.SlotIndex = aryContainerItem.SlotInfo.SlotIndex - 1;
			g_pGOBManager->GetLocalPlayer()->GetInvenArchive()->ItemSetting(aryContainerItem, false);

			pItemAttr = NULL;
			ZeroMemory(szMsg, 256);

			if( g_pItemCluster->GetItemInfo(aryContainerItem.Item.iItemID, pItemAttr) ) {				
				D3DXCOLOR color;
				if(pItemAttr->m_bNameColor) {
					color = pItemAttr->GetNameColor();
				}
				else {
					color = g_pCheckManager->GetItemColor(aryContainerItem.Item.iRare);
				}

				sprintf(szMsg, g_pResourceManager->GetGlobalString(5017006), pItemAttr->m_strName.c_str());

				//if(g_pClientOption->GetOptionStruct()->bItem) {
				g_pInterfaceManager->SPChildWndSendMessage( WIID_SYSTEM_MESSAGE , SPIM_SYSTEM_MESSAGE_ADD , (WPARAM)szMsg , (LPARAM)&color );
				//}

				g_pEventManager->GetQuestManager()->CheckMissionItem(aryContainerItem.Item.iItemID);
			}
		}

		packet->ExtractStruct(&stTrashItem, sizeof(TRASH_ITEM));
		stTrashItem.iContainerSlot.SlotIndex = stTrashItem.iContainerSlot.SlotIndex - 1;
		g_pGOBManager->GetLocalPlayer()->GetInvenArchive()->TrashItem(stTrashItem);

		g_pEventManager->GetClassChangeManager()->OnClassChangeEffect(NewClassType);
	}
}