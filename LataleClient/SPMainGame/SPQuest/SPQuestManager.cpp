
#include "SPCommon.h"
#include "SPQuestAttr.h"
#include "SPQuestArchive.h"
#include "SPRewardAttr.h"
#include "SPRewardArchive.h"
#include "SPQuestManager.h"

#include "SPLDTFile.h"
#include "SPLDTManager.h"
#include "SPResourceDef.h"
#include "SPResourceManager.h"

#include "SPEventDEF.h"
#include "SPEventNpcHandler.h"
#include "SPEventManager.h"

#include "SPGameObjectDEF.h"
#include "SPGameObject.h"
#include "SPGOBManager.h"

//
#include "SPRenderModelDEF.h"
#include "SPRenderModel.h"
#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPGOBModel.h"
#include "SPGOBModelUnit.h"
#include "SPAvatarModelUnit.h"
#include "SPGOBCluster.h"
#include "SPGameObject.h"
//#include "SPGOBStatus.h"
//#include "SPGOBCoordPhysics.h"
//#include "SPGOBModelUnit.h"			
//#include "SPPlayerEquipInfo.h"
#include "SPGOBStatus.h"			
//#include "SPPlayerInvenArchive.h"	
//#include "SPPlayerStatusModel.h"	
//#include "SPPlayerEquipInfo.h"
//#include "SPItemAttr.h"
//#include "SPItemStatus.h"
//#include "SPItemCluster.h"
//#include "SPSkill.h"
//#include "SPSkillArchive.h"
//#include "SPMotionStatus.h"
//#include "SPSkillManager.h"
#include "SPPlayer.h"
#include "SPGOBManager.h"
//#include "SPCoolTimeManager.h"
#include "SPCommandConvert.h"
//#include "SPComboManager.h"

#include "SPCheckManager.h"

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPWindow.h"
#include "SPInterfaceManager.h"

#include "SPItemAttr.h"
#include "SPItemCluster.h"

#include <WinSock2.h>
#include "PacketID.h"
#include "Packet.h"
#include "PacketHandler.h"
#include "SPNetworkManager.h"


#include "SPDebug.h"

SPQuestManager* SPQuestManager::ms_pkInstance = NULL;


//------------------------------------------------------------------------------------
SPQuestManager* SPQuestManager::GetInstance()
{
	if( ms_pkInstance == NULL )
		ms_pkInstance = new SPQuestManager;

	return ms_pkInstance;
}

//------------------------------------------------------------------------------------
void SPQuestManager::Release()
{
	if( ms_pkInstance )
	{
		delete ms_pkInstance;
		ms_pkInstance = NULL;
	}
}

//------------------------------------------------------------------------------------
SPQuestManager::SPQuestManager()
{
	m_pRewardArchive = new SPRewardArchive;
	m_pNpcArchive = new SPQuestArchive;
	m_pPlayerArchive = new SPQuestArchive;
	m_pPlayerReword = new SPQuestArchive;

	m_pLDTQuestData = NULL;

	g_pResourceManager->GetLDTFromFileName(RES_FNAME_LDT_QUEST, &m_pLDTQuestData);

	m_bSendPacket = false;
	m_bSort = false;
}

//------------------------------------------------------------------------------------
SPQuestManager::~SPQuestManager()
{
	SAFE_RELEASE(m_pLDTQuestData);
	
	SAFE_DELETE(m_pNpcArchive);
	SAFE_DELETE(m_pPlayerArchive);
	SAFE_DELETE(m_pPlayerReword);
	SAFE_DELETE(m_pRewardArchive);
}

//------------------------------------------------------------------------------------
bool SPQuestManager::Init()
{
	m_bSendPacket = false;
	return true;
}


//------------------------------------------------------------------------------------
void SPQuestManager::PurgeAll()
{
	m_pNpcArchive->DeleteAllQuest();
	m_pPlayerArchive->DeleteAllQuest();
	m_pPlayerReword->DeleteAllQuest();

	if( g_pInterfaceManager != NULL )
		g_pInterfaceManager->SPChildWndSendMessage( WIID_QUEST , SPIM_PURGE , NULL , NULL );	// AJJIYA [6/23/2006]

#ifdef _DEBUG
	std::string msg = "------ Quest Sort flag�� false�� �����˴ϴ�.";
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING ,  (WPARAM)msg.c_str());
#endif
	
	m_bSort = false;
	m_bSendPacket = false;
}


//------------------------------------------------------------------------------------
SPQuestArchive* SPQuestManager::GetNpcArchive()
{	
	return m_pNpcArchive;
}


//------------------------------------------------------------------------------------
SPQuestArchive* SPQuestManager::GetPlayerArchive()
{
	return m_pPlayerArchive;
}


//------------------------------------------------------------------------------------
SPQuestArchive*	SPQuestManager::GetRewordArchive()
{
	return m_pPlayerReword;
}

//------------------------------------------------------------------------------------
SPRewardArchive* SPQuestManager::GetRewardInfo()
{
	return m_pRewardArchive;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::LoadNpcQuest()
{	
	SPNpcQuestList* pNpcQuestList = g_pEventManager->GetEventHandler()->GetNpcQuestData();
	int iSize = 0;
	
	if(pNpcQuestList == NULL)		return false;

	DeleteNpcQuest();
	
	//m_pNpcArchive->InitQuestList(pNpcQuestList->m_iQuestCount);

	for(int i = 0; i < pNpcQuestList->m_iQuestCount; i++) {
		//m_pNpcArchive->LoadQuestFromNpc(i);
		//LoadLDTFile(pNpcQuestList->m_iQuestID[i], m_pNpcArchive->GetQuestAttr(i));		
		LoadQuest(pNpcQuestList->m_iQuestID[i]);
	}

	//[2006/7/6] NPC����Ʈ ����Ʈ�� �����鼭 PC�� ���󰡴� ����� ����ENPC�� �ش�ENPC�� ���� �濁E����Ʈ�� �߰�
	int iPlayerQuestSize = m_pPlayerArchive->GetSize();
	for(int i = 0 ; i < iPlayerQuestSize; i++) {
		SPQuestAttr* pPlayerAttr = m_pPlayerArchive->GetQuestAttr(i);
		if(m_pNpcArchive->GetQuest(pPlayerAttr->m_iQuestID))			//����ENPC ����Ʈ�� �����ϴ� ����Ʈ�� �濁E�Ѿ�̣��
			continue;

		if(pPlayerAttr && pPlayerAttr->m_iUiShow == QUEST_UI_SHOW_COMPLETE && g_pEventManager->GetCurEvent() &&
			pPlayerAttr->m_iRewordNpcID == g_pEventManager->GetCurEvent()->eventTypeID) 
		{
			SPQuestAttr* pNewNpcQuestAttr = new SPQuestAttr;
			pNewNpcQuestAttr->Copy(pPlayerAttr);
			m_pNpcArchive->AddQuest(pNewNpcQuestAttr);
			if( g_pInterfaceManager != NULL )
				g_pInterfaceManager->SPChildWndSendMessage( WIID_NPC_QUEST , SPIM_QUEST_ADD , NULL , pNewNpcQuestAttr->m_iQuestID );	// AJJIYA [6/26/2006]
		}
	}

	m_pNpcArchive->GetSize();

	return true;
}

//------------------------------------------------------------------------------------
bool SPQuestManager::LoadQuest( int iQuestID, QUEST_ACCEPTTYPE iType /* = QUEST_ACCEPTTYPE_NPC  */, int iTypeID /* = 0  */, bool bRequireCheck /* = false  */ )
{
	// ������ ����Ʈ�� �ִ°��� Ȯ���Ѵ�. [9/21/2007 AJJIYA]
	if( m_pNpcArchive != NULL )
	{
		SPQuestAttr* pSameQuestAttr	=	m_pNpcArchive->GetQuest( iQuestID );
		
		if( pSameQuestAttr != NULL )
		{
			if( iType == QUEST_ACCEPTTYPE_SHARE || iType == QUEST_ACCEPTTYPE_ITEM )
				return false;
		}
	}

	int iSize = 0;
	SPQuestAttr* pQuestAttr = new SPQuestAttr;		
	if(LoadLDTFile(iQuestID, pQuestAttr) == false) {
		SAFE_DELETE(pQuestAttr);
		//continue;
		return false;
	}

	pQuestAttr->IsRequire();									//���� �˻�E

	if((iType & pQuestAttr->m_eAcceptType) == iType) {
		pQuestAttr->m_iCurrentAccept	= iType;
		pQuestAttr->m_iActCharID		= iTypeID;
	}
	else {
		SAFE_DELETE(pQuestAttr);
		return false;
	}

	//[2005/10/13] ����E�������̴��� ���� �Ϸ��� �濁E?üũ
	if(GetRewordCount(pQuestAttr->m_iQuestID) > 0) {
		pQuestAttr->m_iUiShow = QUEST_UI_SHOW_REWORD;
	}

	if(pQuestAttr->m_iUiShow == QUEST_UI_SHOW_REWORD) {			//����E�Ϸ�E��Ͽ� �ִ°����� ������ �濁E		
		//�ݺ� ������ ��������E�ʾҴٸ�ENPC ����Ʈ ����Ʈ�� �����ش�	
		for(int j = 0; j < QUEST_MAX_REQUIRE; j++) {
			if(pQuestAttr->m_Require[j].m_iRequireStat == REQUIRE_TYPE_QUEST) {					
				//if(pQuestAttr->m_Require[j].m_iValue1 == 2) {
				if(pQuestAttr->m_Require[j].m_iRequireStatValue == 2) {
					int iRewordCount = GetRewordCount(pQuestAttr->m_iQuestID);
					if(iRewordCount < pQuestAttr->m_Require[j].m_iValue2) {
						pQuestAttr->m_iUiShow = QUEST_UI_SHOW_ABLE;
					}
				}
			}
		}


		//pQuestAttr->IsRequire();

		//
		if(pQuestAttr->m_iUiShow == QUEST_UI_SHOW_ABLE) {		//�Ϸ�Ǵ� �������ѹ��̻�E������� ����Ʈ�� �����鼭 �ٽ� �Ҽ�E�ִ� �濁E
			pQuestAttr->IsRequire();							//�ٽ� �ʿ����� üũ
		}

		//else {
		//	if(IsRewordQuest(pQuestAttr-m_iQuestID)) {
		//		pQuestAttr->m_iUiShow = QUEST_UI_SHOW_REWORD;
		//	}
		//}
	}

	if(pQuestAttr->m_iUiShow > QUEST_UI_SHOW_NULL) {			//����E���̴� �͵���
		if(IsDoingQuest(pQuestAttr->m_iQuestID)) {				//����E�������ΰ��� �����
			pQuestAttr->m_iUiShow = QUEST_UI_SHOW_NULL;

			if(GetPlayerArchive()->GetQuest(pQuestAttr->m_iQuestID)) {
				if(GetPlayerArchive()->GetQuest(pQuestAttr->m_iQuestID)->m_iUiShow == QUEST_UI_SHOW_COMPLETE) {
					if(g_pEventManager->GetCurEvent() && pQuestAttr->m_iRewordNpcID == g_pEventManager->GetCurEvent()->eventTypeID)
						pQuestAttr->m_iUiShow = QUEST_UI_SHOW_COMPLETE;
				}
			}
		}
	}


	//[2005/10/13] �������� ����E�������ΰ濁E��?������ ǥ���� ����E
	//if(pQuestAttr->m_iUiShow > QUEST_UI_SHOW_NULL) {
	//	if(IsDoingQuest(pQuestAttr->m_iQuestID)) {				//����E������������ Ȯ���Ѵ� 
	//		pQuestAttr->m_iUiShow = QUEST_UI_SHOW_NULL;
	//	}
	//	//else if(GetRewordCount(pQuestAttr->m_iQuestID) > 0) {	//����E�Ϸ�E��Ͽ� �ִ� �濁E			
	//	if(GetRewordCount(pQuestAttr->m_iQuestID) > 0) {	//����E�Ϸ�E��Ͽ� �ִ� �濁E
	//		pQuestAttr->m_iUiShow = QUEST_UI_SHOW_REWORD;
	//	}
	//}

	//if(pQuestAttr->m_iUiShow == QUEST_UI_SHOW_REWORD) {			//����E�Ϸ�E��Ͽ� �ִ°����� ������ �濁E		
	//	//�ݺ� ������ ��������E�ʾҴٸ�ENPC ����Ʈ ����Ʈ�� �����ش�	
	//	for(int j = 0; j < QUEST_MAX_REQUIRE; j++) {
	//		if(pQuestAttr->m_Require[j].m_iRequireStat == REQUIRE_TYPE_QUEST) {					
	//			if(pQuestAttr->m_Require[j].m_iValue1 == 2) {
	//				int iRewordCount = GetRewordCount(pQuestAttr->m_iQuestID);
	//				if(iRewordCount < pQuestAttr->m_Require[j].m_iValue2) {
	//					pQuestAttr->m_iUiShow = QUEST_UI_SHOW_ABLE;
	//				}
	//			}
	//		}
	//	}
	//}

	if( bRequireCheck == true )
	{
		if( pQuestAttr->m_iUiShow == QUEST_UI_SHOW_NULL || pQuestAttr->m_iUiShow == QUEST_UI_SHOW_DISABLE )
		{
			SAFE_DELETE( pQuestAttr );
			return false;
		}
	}

	if(pQuestAttr->m_iUiShow == QUEST_UI_SHOW_ABLE || pQuestAttr->m_iUiShow == QUEST_UI_SHOW_DISABLE || pQuestAttr->m_iUiShow == QUEST_UI_SHOW_COMPLETE){
		iSize = m_pNpcArchive->AddQuest(pQuestAttr);
		if( g_pInterfaceManager != NULL )
			g_pInterfaceManager->SPChildWndSendMessage( WIID_NPC_QUEST , SPIM_QUEST_ADD , NULL , pQuestAttr->m_iQuestID );	// AJJIYA [6/26/2006]
	}
	else {
		SAFE_DELETE(pQuestAttr);
	}
	
	
	return true;
}

//------------------------------------------------------------------------------------
void SPQuestManager::DeleteNpcQuest()
{
	if( m_pNpcArchive != NULL )
		m_pNpcArchive->DeleteAllQuest();

	if( g_pInterfaceManager != NULL )
		g_pInterfaceManager->SPChildWndSendMessage( WIID_NPC_QUEST , SPIM_PURGE , NULL , NULL );
}

//------------------------------------------------------------------------------------
void SPQuestManager::DeleteNpcQuest( int iQuestID )
{
	if( g_pInterfaceManager != NULL )
		g_pInterfaceManager->SPChildWndSendMessage( WIID_NPC_QUEST , SPIM_QUEST_DEL , NULL , iQuestID );	// AJJIYA [6/23/2006]

	if( m_pNpcArchive != NULL )
		m_pNpcArchive->DeleteQuest( iQuestID );
}
//------------------------------------------------------------------------------------
int SPQuestManager::SetPlayerQuest(QUEST* pQuest, bool bMsg /*= true*/)
{	
	SPQuestAttr* pQuestAttr = new SPQuestAttr;
	
	if(LoadLDTFile(pQuest->uiQuestID, pQuestAttr) == false) {
		SAFE_DELETE(pQuestAttr);
		return -1;
	}

	//[2006/6/16] ����κ� ������	
	for(int i = 0; i < QUEST_MAX_RANK; i++) {		
		for(int j = 0; j < QUEST_MAX_REWARD; j++) {
			int iRewardID = pQuestAttr->m_RewordRank[i].m_Info[j].m_iID;
			if(iRewardID) {
				pQuestAttr->m_RewordRank[i].m_Info[j].m_pRewardInfo = m_pRewardArchive->GetReward(iRewardID);
			}			
		}		
	}	

	int iSize = 0;
	
	if(pQuest->uiStatus == QUEST_STATUS_FINISH) {					//������� ����Ʈ
		//[2005/10/13] ����E�� ����E����Ʈ�� �����ϴ� ����Ʈ�� �濁E
		if(IsRewordQuest(pQuest->uiQuestID) != NULL) {
			SAFE_DELETE(pQuestAttr);
			DXUTOutputDebugString("�ش�E����E����Ʈ�� �� ����E����Ʈ�� �����մϴ� : [%d]\n", pQuest->uiQuestID);
			return -1;
		}
		
		pQuestAttr->m_iUiShow = QUEST_UI_SHOW_REWORD;
		pQuestAttr->m_iRewordCount = pQuest->iFinishCnt;
		
		//���� �̼��� �Ϸ�E���·� �������־��� �Ѵ� 		
		for(int i = 0; i < QUEST_MAX_MISSION; i++) {
			pQuestAttr->m_Mission[i].m_bClear = true;
			pQuestAttr->m_Mission[i].m_iCurCount = pQuestAttr->m_Mission[i].m_iMissionCount;
		}

		iSize = m_pPlayerReword->AddQuest(pQuestAttr);
	}
	else if(pQuest->uiStatus == QUEST_STATUS_ACTIVE) {				//�������� ����Ʈ
		//[2005/10/13] ����E�� ��?E����Ʈ�� �����ϴ� ����Ʈ�� �濁E
		if(IsDoingQuest(pQuest->uiQuestID) != NULL) {
			SAFE_DELETE(pQuestAttr);
			DXUTOutputDebugString("�ش�E��?E����Ʈ�� �� ��?E����Ʈ�� �����մϴ� : [%d]\n", pQuest->uiQuestID);
			return -1;
		}
		
		//����E��?E����Ʈ ���� 15�� �̻��� �濁E����
		if(m_pPlayerArchive->GetSize() >= QUEST_MAX_ACTIVE) {
			SAFE_DELETE(pQuestAttr);
			return -1;
		}

		if(bMsg){														//����Ʈ�� ���� ���� �濁E
			if(g_pResourceManager->GetGlobalString(6001005) != NULL) {	//����Ʈ ������ �޽���E
				std::string strMsg = g_pResourceManager->GetGlobalString(6001005);
				char szMsg[512];
				wsprintf(szMsg, strMsg.c_str(), pQuestAttr->m_strQuestName.c_str());
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMsg);
			}

			//Npc ��E?����E������Ʈ
			SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_SHOPTALK);
			if(pQuestAttr->m_strMsgAccept != "") {
				pWindow->SPSendMessage(SPIM_SET_SHOPTALK_MSG, (WPARAM)pQuestAttr->m_strMsgAccept.c_str(), 0);
			}

			if(pQuestAttr->m_iImageAccept != 0) {
				g_pEventManager->GetEventHandler()->SetNpcTalkImage(pQuestAttr->m_iImageAccept);
			}
		}
		
		pQuestAttr->m_iRewordCount = pQuest->iFinishCnt;		
		
		//������ ����Ʈ�� �濁E����Ʈ�� �̼� �������� ��Ȳ�� �Բ� Ȯ�����ش� (�������� �޴� ���� ����!)
		pQuestAttr->SetCheckMissionItem(bMsg);		
		
		iSize = m_pPlayerArchive->AddQuest(pQuestAttr);

		if( g_pInterfaceManager != NULL )
			g_pInterfaceManager->SPChildWndSendMessage( WIID_QUEST , SPIM_QUEST_ADD , NULL , pQuestAttr->m_iQuestID );	// AJJIYA [6/23/2006]
		
		//����E���� ����Ʈ ��Ͽ� �ش�E����Ʈ�� �ִٸ�E������ 
		m_pPlayerReword->DeleteQuest(pQuest->uiQuestID);
	}
	else {
		//return false;
	}
	
	return iSize;
}


//------------------------------------------------------------------------------------
int SPQuestManager::SetPlayerMissionInfo(MISSION* pMission)
{
	return m_pPlayerArchive->SetMissionInfo(pMission);
}


//------------------------------------------------------------------------------------
int SPQuestManager::GetRewordCount(int iQuestID)
{
	SPQuestAttr* pQuestAttr = m_pPlayerReword->GetQuest(iQuestID);
	
	if(pQuestAttr) {
		return pQuestAttr->m_iRewordCount;
	}

	if(pQuestAttr == NULL) {
		pQuestAttr = m_pPlayerArchive->GetQuest(iQuestID);

		if(pQuestAttr) {
			return pQuestAttr->m_iRewordCount;
		}
	}

	return 0;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::IsDoingQuest(int iQuestID)
{
	SPQuestAttr* pQuestAttr = m_pPlayerArchive->GetQuest(iQuestID);
	
	if(pQuestAttr) {
		return true;
	}

	return false;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::IsRewordQuest(int iQuestID)
{
	SPQuestAttr* pQuestAttr = m_pPlayerReword->GetQuest(iQuestID);

	if(pQuestAttr) {
		return true;
	}

	return false;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::UpdateMission(MISSION* pMission)
{
	switch(pMission->uiMissionType) {
		case MISSION_TYPE_MONSTER:
		case MISSION_TYPE_ACTION:			
		case MISSION_TYPE_EVENT:
			if(pMission->uiMissionType == MISSION_TYPE_ACTION) {
				pMission->uiValueID = pMission->uiValueID + 1;
			}
			m_pPlayerArchive->CheckMission(pMission);
			return true;
		default:
			break;
	}

	return false;
}


//------------------------------------------------------------------------------------
int SPQuestManager::CheckMissionItem(int iItemID)
{
	int iResult = m_pPlayerArchive->CheckMissionItem(iItemID);
	return iResult;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::CheckMissionEvent(int iEventID)
{
	bool bResult = false;

	bResult = m_pPlayerArchive->CheckMapEvent(iEventID);

	return bResult;
}


//------------------------------------------------------------------------------------
int SPQuestManager::CheckMissionAction(int iAction)
{
	int iResult = 0;
	if(iAction == 0)
		return iResult;

	iResult = m_pPlayerArchive->CheckAction(iAction);

	if(iResult > 0)
		SendMissionAction(iResult);

	return iResult;
}


//------------------------------------------------------------------------------------
QUEST_RETURN SPQuestManager::IsAcceptQuest(int iQuestID)
{
	SPQuestAttr* pQuest = m_pNpcArchive->GetQuest(iQuestID);
	if(pQuest == NULL) {
		return QUEST_RETURN_A_INVAILD;
	}

	//CUT_IN ��Ȳ�� QUEST���°� �ƴѰ濁E����
	if(pQuest->m_iCurrentAccept == QUEST_ACCEPTTYPE_NPC) {
		if(g_pEventManager->GetCutInState() != CUT_IN_STATE_QUEST)
			return QUEST_RETURN_A_INVAILD;
	}

	// ����E����Ʈ ����Ʈ�� MAX �� ���ų� ū �濁E����
	if(m_pPlayerArchive->GetSize() >= QUEST_MAX_ACTIVE)
		return QUEST_RETURN_A_FULL;	

	return QUEST_RETURN_OK;
}


//------------------------------------------------------------------------------------
QUEST_RETURN SPQuestManager::SetAcceptQuest(int iQuestID)
{	
	QUEST_RETURN iReturn = IsAcceptQuest(iQuestID);
	
	if(iReturn == QUEST_RETURN_OK) {
		// ����Ʈ ����E��Ŷ�� ����
		int i = 0;
		int iCheckCount = 0;
		
		// ����Ʈ ������ �Բ� ����;� �� �������� ������ ������ �ִ���EȮ��
		SPQuestAttr* pQuest = m_pNpcArchive->GetQuest(iQuestID);
		for(i = 0; i < QUEST_MAX_ACQUISITION_ITEM; i++) {
			if(pQuest->m_AcquisitionItem[i].m_iItemID > 0) {
				iCheckCount++;
				if(false == g_pCheckManager->CheckEnableSlot(pQuest->m_AcquisitionItem[i].m_iItemID, pQuest->m_AcquisitionItem[i].m_iStack)) {
					iReturn = QUEST_RETURN_A_INVEN;
					SetReturnMsg(iReturn);			
					return iReturn;
				}
			}
		}		

		int iTypeID = 0;
		if(pQuest->m_iCurrentAccept == QUEST_ACCEPTTYPE_NPC) {
			iTypeID = g_pEventManager->GetEventHandler()->GetNpcID();
		}
		else if(pQuest->m_iCurrentAccept == QUEST_ACCEPTTYPE_SHARE) {
			iTypeID = pQuest->m_iActCharID;
		}
		else if(pQuest->m_eAcceptType & QUEST_ACCEPTTYPE_ITEM) {
			//[9/20/2007 AJJIYA]�� �Ҳ�����
			iTypeID = 0;
		}

		SendAcceptQuest(pQuest->m_iCurrentAccept, iTypeID, iQuestID);
	}
	else {
		SetReturnMsg(iReturn);
	}

	////CutIn ����...
	//g_pEventManager->SetCutInState(CUT_IN_STATE_NULL);

    return iReturn;
}


//------------------------------------------------------------------------------------
int SPQuestManager::SetGiveUpQuest(int iQuestID)
{
	SendGiveUpQuest(iQuestID);	
	return 1;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::OnGiveUpQuest(int iQuestID)
{		
	SPQuestAttr* pGiveUpQuestAttr = m_pPlayerArchive->GetQuest(iQuestID);	//������ ����Ʈ

	if(pGiveUpQuestAttr == NULL) {
		return false;
	}

	if(g_pResourceManager->GetGlobalString(6001003) != NULL) {
		std::string strMsg = g_pResourceManager->GetGlobalString(6001003);
		char szMsg[512];
		wsprintf(szMsg, strMsg.c_str(), pGiveUpQuestAttr->m_strQuestName.c_str());
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMsg);
	}	
	
	//����E��?����Ʈ�� ����E�ѹ��̶� �ݺ��� ����Ʈ�� �濁E
	if(pGiveUpQuestAttr->m_iRewordCount > 0) {
		//�Ϸ�E����Ʈ ����� ���������� �̵�	
		SPQuestAttr* pQuestAttr = new SPQuestAttr;
		//pQuestAttr = pGiveUpQuestAttr;
		pQuestAttr->Copy(pGiveUpQuestAttr);

		//���� �̼��� �Ϸ�E���·� �������־��� �Ѵ� 		
		for(int i = 0; i < QUEST_MAX_MISSION; i++) {
			pQuestAttr->m_Mission[i].m_bClear = true;
			pQuestAttr->m_Mission[i].m_iCurCount = pQuestAttr->m_Mission[i].m_iMissionCount;
		}
		pQuestAttr->m_iUiShow = QUEST_UI_SHOW_REWORD;

		m_pPlayerReword->AddQuest(pQuestAttr);
	}	
	
	if( g_pInterfaceManager != NULL )
		g_pInterfaceManager->SPChildWndSendMessage( WIID_QUEST , SPIM_QUEST_DEL , NULL , iQuestID );	// AJJIYA [6/23/2006]

	//����E��?E����Ʈ���� ����
	m_pPlayerArchive->DeleteQuest(iQuestID);

	g_pGOBManager->CheckEventQuestFx();

	////CutIn ����...
	//g_pEventManager->SetCutInState(CUT_IN_STATE_NULL);
	return true;
}


//------------------------------------------------------------------------------------
QUEST_RETURN SPQuestManager::IsFinishQuest(int iQuestID)
{
	// CUT_IN ��Ȳ�� QUEST���°� �ƴѰ濁E����
	if(g_pEventManager->GetCutInState() != CUT_IN_STATE_QUEST)
		return QUEST_RETURN_F_INVAILD;

	// �÷��̾�̡ ������E�ִ� ����Ʈ�� �ƴ� �濁E����
	SPQuestAttr* pQuest = m_pPlayerArchive->GetQuest(iQuestID);
	if(pQuest == NULL) {
		return QUEST_RETURN_F_INVAILD;
	}

	// �ش�E����Ʈ�� ���ø�Ʈ ���°� �ƴ϶�E����
	if(pQuest->m_iUiShow != QUEST_UI_SHOW_COMPLETE) {
		return QUEST_RETURN_F_NOTCOMPLETE;
	}

	// ����E���� NPC�� �ƴ϶�E����
	int iNpcID = g_pEventManager->GetEventHandler()->GetNpcID();
	if(pQuest->m_iRewordNpcID != iNpcID) {
		return QUEST_RETURN_F_NPC;
	}	
	
	return QUEST_RETURN_OK;
}


//------------------------------------------------------------------------------------
QUEST_RETURN SPQuestManager::SetFinishQuest(int iQuestID, int iReward /*= 0*/)
{
	QUEST_RETURN iReturn = IsFinishQuest(iQuestID);
	
	if(iReturn == QUEST_RETURN_OK) {
		SPQuestAttr* pQuest = m_pPlayerArchive->GetQuest(iQuestID);
		int i = 0;
		// ����Ʈ ����� �����Ǿ��� �� �������� ���û�Ȳ�� üũ 
		for(i = 0; i < QUEST_MAX_MISSION; i++) {
			if(pQuest->m_Mission[i].m_iMissionType == MISSION_TYPE_ITEM) {
				if(g_pCheckManager->CheckBiggerSlot(pQuest->m_Mission[i].m_iMissionTypeID, pQuest->m_Mission[i].m_iMissionCount) == false) {
					if(g_pCheckManager->CheckBiggerSlot5(pQuest->m_Mission[i].m_iMissionTypeID, pQuest->m_Mission[i].m_iMissionCount) == false) {
						iReturn = QUEST_RETURN_F_SLOT;
						SetReturnMsg(iReturn);
						return iReturn;
					}
				}
			}
		}

		//[2006/6/19]	Rank ���� Ȯ��
		REWARD_RANK iRank = pQuest->IsRewardRequire();
		
		if(iRank == REWARD_RANK_NULL) {			//����E�䱸���� ����
			return iReturn;
		}
				
		
		//[2006/7/14] ������� �������� ����� ������ ���� ���� Ȯ�� ����
		SPRewardAttr* pRewardAttr = NULL;		
		int iRequireSlot[FIGURE_EQUIP] = {0, 0, 0, 0, 0, 0};		//Inventroy�� size 6
		
		//����EŸ�Կ� ����Eüũ�ؾ��� ����E������ �������ش� 
		int iRid = 0;												//����EID �⾁E�E
		if(pQuest->m_RewordRank[iRank].m_iType == REWARD_TYPE_RANDOM) {
			iRid = pQuest->m_RewordRank[iRank].m_Info[2].m_iID;
			pRewardAttr = pQuest->m_RewordRank[iRank].m_Info[2].m_pRewardInfo;
		}
		else {
			iRid = pQuest->m_RewordRank[iRank].m_Info[iReward].m_iID;
			pRewardAttr = pQuest->m_RewordRank[iRank].m_Info[iReward].m_pRewardInfo;
		}

		//����E�����Ͱ� �ִ���EȮ���Ѵ� 
		if(pRewardAttr == NULL) {
			pRewardAttr = m_pRewardArchive->GetReward(iRid);
			if(pRewardAttr == NULL) {
				iReturn = QUEST_RETURN_A_INVAILD;
				////[2006/12/21] - jinssaga  ũ�������� �̺�Ʈ ���� ���  
				//SetReturnMsg(iReturn);
				if(g_pResourceManager->GetGlobalString(14000001) != NULL) {
					std::string strMsg = g_pResourceManager->GetGlobalString(14000001);
					if(strMsg != "") {
						g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
					}
				}
				
				return iReturn;
			}			
		}

		//�� �����̳ʺ��� �ʿ��� ���Լ��� �⾁E
		for(i = 0; i < QUESTREWARD_MAX_ITEM; i++) {
			CONTAINER_TYPE iContainer = CONTAINER_TYPE_INVALID;
			SPItemAttr* pItem = NULL;
			g_pItemCluster->GetItemInfo(pRewardAttr->m_Item[i].m_iItemID, pItem);
			if(pItem == NULL)
				continue;
			iContainer = (CONTAINER_TYPE)(pItem->m_eType - 1);
			iRequireSlot[iContainer]++;
		}

		//�����̳� ���� ����ִ� ���Լ��� �軁EѴ?
		for(i = 0; i < FIGURE_EQUIP; i++) {
			for(i = 0; i < FIGURE_EQUIP; i++) {
				if(iRequireSlot[i] == 0) 
					continue;

				if(false == g_pCheckManager->CheckRequireSlot(i, iRequireSlot[i])) {
					iReturn = QUEST_RETURN_F_INVEN;
					SetReturnMsg(iReturn);
					return iReturn;
				}
			}
		}

		//������ ������ �軁EѴ?
		for(i = 0; i < QUESTREWARD_MAX_ITEM; i++) {
			if(pRewardAttr->m_Item[i].m_iItemID > 0) {
				if(false == g_pCheckManager->CheckEnableSlot(pRewardAttr->m_Item[i].m_iItemID, pRewardAttr->m_Item[i].m_iStack)) {
					iReturn = QUEST_RETURN_F_INVEN;
					SetReturnMsg(iReturn);
					return iReturn;
				}
			}
		}
		
		
		
		
		//[2006/6/15] - ����E�ٲ��� ?E·?�������־��� �Ѵ�
		//for(i = 0; i < QUEST_MAX_REWARD_ITEM; i++) {
		//	CONTAINER_TYPE iContainer = CONTAINER_TYPE_INVALID;
		//	SPItemAttr* pItem;
		//	g_pItemCluster->GetItemInfo(pQuest->m_RewordItem[i].m_iItemID, pItem);
		//	if(pItem == NULL)
		//		continue;

		//	iContainer = (CONTAINER_TYPE)(pItem->m_eType - 1);
		//	iRequireSlot[iContainer]++;
		//}

		//for(i = 0; i < FIGURE_EQUIP; i++) {
		//	if(iRequireSlot[i] == 0) 
		//		continue;

		//	if(false == g_pCheckManager->CheckRequireSlot(i, iRequireSlot[i])) {
		//		iReturn = QUEST_RETURN_F_INVEN;
		//		SetReturnMsg(iReturn);
		//		return iReturn;
		//	}
		//}

		//// ����Ʈ ����� �Բ� ����;� �� �������� ������ ������ �ִ���EȮ��
		//for(i = 0; i < QUEST_MAX_REWARD_ITEM; i++) {
		//	if(pQuest->m_RewordItem[i].m_iItemID > 0) {
		//		if(false == g_pCheckManager->CheckEnableSlot(pQuest->m_RewordItem[i].m_iItemID, pQuest->m_RewordItem[i].m_iStack)) {
		//			iReturn = QUEST_RETURN_F_INVEN;
		//			SetReturnMsg(iReturn);
		//			return iReturn;
		//		}
		//	}
		//}				
		
		int iNpcID = g_pEventManager->GetEventHandler()->GetNpcID();		
		// ����E��û �޽����� ��E?
		SendFinishQuest(iNpcID, iQuestID, iRank, iReward);
	}
	else {
		SetReturnMsg(iReturn);
	}

	////[2005/10/4] ������ �濁E���信 ����Eϰ?CutIn ����...
	//g_pEventManager->SetCutInState(CUT_IN_STATE_NULL);

	return iReturn;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::OnFinishQuest(QUEST* pQuest)
{	
	SPQuestAttr* pRewordQuest = m_pPlayerArchive->GetQuest(pQuest->uiQuestID);
	if(pRewordQuest == NULL)
		return false;

	if(g_pResourceManager->GetGlobalString(6001006) != NULL) {				//����Ʈ ����� �޽���E
		std::string strMsg = g_pResourceManager->GetGlobalString(6001006);
		char szMsg[512];
		wsprintf(szMsg, strMsg.c_str(), pRewordQuest->m_strQuestName.c_str());
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMsg);
	}	

	pRewordQuest->m_iRewordCount = pQuest->iFinishCnt;
	pRewordQuest->m_iUiShow = QUEST_UI_SHOW_REWORD;
	//���� �̼� ���� ������Ʈ 
	for(int i = 0; i < QUEST_MAX_MISSION; i++) {
		pRewordQuest->m_Mission[i].m_bClear = true;
		pRewordQuest->m_Mission[i].m_iCurCount = pRewordQuest->m_Mission[i].m_iMissionCount;
	}
	
	//�ڽ��� ����Ʈ�� �Ϸ�E����Ʈ�� ���������� �̵��ѵ�
	SPQuestAttr* pQuestAttr = new SPQuestAttr;
	//(SPQuestAttr&)(pQuestAttr) = (SPQuestAttr&)(pRewordQuest);
	//*pQuestAttr = *pRewordQuest;
	pQuestAttr->Copy(pRewordQuest);

	m_pPlayerReword->AddQuest(pQuestAttr);	

	// ����Ʈ ����Ʈ���� ����E�E��E?����E�����ؾ� �Ѵ�. [7/3/2006]
	if( g_pInterfaceManager != NULL )
		g_pInterfaceManager->SPChildWndSendMessage( WIID_QUEST , SPIM_QUEST_DEL , NULL , pQuest->uiQuestID );	// AJJIYA [6/23/2006]

	//��?E����Ʈ ��Ͽ��� �����Ѵ�
	m_pPlayerArchive->DeleteQuest(pQuest->uiQuestID);

	////CutIn ����...
	//g_pEventManager->SetCutInState(CUT_IN_STATE_NULL);

	g_pCheckManager->SetDBBlock(false);

	//Effect ��?E
	//for(int i = 0; i < QUEST_MAX_REWARD_EFFECTID; i++) {
	//	g_pCheckManager->SetLocalEffect(pQuestAttr->m_iRewordEffect[i]);
	//}

	//[2006/8/1] Quest �Ϸ�EFXǥ?ESound���
	if(g_pGOBManager->GetLocalPlayer()) {
		g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_SET_FX_GROUP, (LPARAM)509);
		g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_SET_PLAY_SOUND, (LPARAM)65);
	}

	//Npc ��E?����E������Ʈ
	SPWindow* pWindow = g_pInterfaceManager->FindWindow(WIID_SHOPTALK);
	if(pQuestAttr->m_strMsgReword != "") {
		pWindow->SPSendMessage(SPIM_SET_SHOPTALK_MSG, (WPARAM)pQuestAttr->m_strMsgReword.c_str(), 0);
	}

	if(pQuestAttr->m_iImageReword != 0) {
		g_pEventManager->GetEventHandler()->SetNpcTalkImage(pQuestAttr->m_iImageReword);
	}	

	return true;
}


//------------------------------------------------------------------------------------
bool SPQuestManager::IsListSort()
{		
	return m_bSort;	
}


//------------------------------------------------------------------------------------
void SPQuestManager::SetListSort(bool bSort /*= true*/)
{
#ifdef _DEBUG
	std::string msg = "------ Quest ����Ʈ�� ������ �޾ҽ��ϴ� !!";
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING ,  (WPARAM)msg.c_str());
#endif
	
	m_pPlayerArchive->SetSort();
	m_bSort = true;
}


//------------------------------------------------------------------------------------
void SPQuestManager::ResetSendBlock()
{
	m_bSendPacket = false;
}

//------------------------------------------------------------------------------------
void SPQuestManager::SendQuestSharePacket( int iQuestID )
{
	CPacket Packet;
	Packet.Add((UINT32)QUEST_CS_SHARE);
	Packet.Add((UINT32)iQuestID);

	g_pNetworkManager->GetPacketHandler()->PostMsg( &Packet );
}

//------------------------------------------------------------------------------------
void SPQuestManager::RecvQuestSharePacket( int iQuestID , INT32 iActCharID )
{
	if( LoadQuest( iQuestID , QUEST_ACCEPTTYPE_SHARE , iActCharID , true ) == true )
		g_pInterfaceManager->ShowWindow( WIID_NPC_QUEST , true );
}

//------------------------------------------------------------------------------------
bool SPQuestManager::AddItemQuest( int iQuestID , int iItemID )
{
	if( m_pPlayerArchive == NULL || g_pInterfaceManager == NULL || g_pResourceManager == NULL || m_pLDTQuestData == NULL || iQuestID <= 0 )
		return false;

	const char*		pszGlobalString	=	NULL;
	D3DXCOLOR		color(1.0f, 0.0f, 0.0f, 1.0f);

	// ���� ���� ���������� üũ [10/2/2007 AJJIYA]
	if( IsDoingQuest( iQuestID ) == true )
	{
		pszGlobalString	=	g_pResourceManager->GetGlobalString( 6003001 );
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)pszGlobalString , (LPARAM)&color);;
		return false;
	}

	// ����Ʈ ������ 15�� �̻����� üũ [10/2/2007 AJJIYA]
	if( m_pPlayerArchive->GetSize() >= QUEST_MAX_ACTIVE )
	{
		pszGlobalString	=	g_pResourceManager->GetGlobalString( 6003002 );
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)pszGlobalString , (LPARAM)&color);;
		return false;
	}

	LDT_Field ldtFieldName;

	// ����Ʈ ���̵� QUEST.LDT�� �����ϴ��� üũ [10/2/2007 AJJIYA]
	if( m_pLDTQuestData->GetField( iQuestID , 0 ,	ldtFieldName )  == false )
	{
		pszGlobalString	=	g_pResourceManager->GetGlobalString( 6003003 );
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)pszGlobalString , (LPARAM)&color);;
		return false;
	}	

	// ����Ʈ�� �߰� �Ҽ� �ִ��� ���� üũ [10/2/2007 AJJIYA]
	if( LoadQuest( iQuestID , QUEST_ACCEPTTYPE_ITEM , iItemID , true ) == false )
	{
		pszGlobalString	=	g_pResourceManager->GetGlobalString( 6003004 );
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)pszGlobalString , (LPARAM)&color);;
		return false;
	}

	g_pInterfaceManager->ShowWindow( WIID_NPC_QUEST , true );
	return true;
}

//------------------------------------------------------------------------------------
bool SPQuestManager::LoadLDTFile(int iItemID, SPQuestAttr* pQuestAttr)
{
	//if(m_pLDTQuestData == NULL)
	//	g_pResourceManager->GetLDTFromFileName(RES_FNAME_LDT_QUEST, &m_pLDTQuestData);
	
	if( m_pLDTQuestData == NULL )
	{
		assert(m_pLDTQuestData != NULL && "m_pLDTQuestData is NULL..");
		return false;
	}

	int recordCount = m_pLDTQuestData->GetItemCount();
	int i = 0;	
	
	// Quest �ʼ�E����
	LDT_Field ldtFieldName;
	//LDT_Field ldtFieldIcon;		
	//LDT_Field ldtFieldIconIndex;
	LDT_Field ldtFieldVisible;

	std::string strName = "";
	//int iIcon = 0;
	//int iIconIndex = 0;
	int iVisible = 0;

	//if(g_pEventManager->GetEventArchive()->GetQuestAttr(iItemID) == NULL) {
	//	return false;
	//}

	if(m_pLDTQuestData->GetFieldFromLable(iItemID, "_Name",	ldtFieldName) == false) {
		return false;
	}	
	if( ldtFieldName.uData.pValue )
		strName = ldtFieldName.uData.pValue;

	//m_pLDTQuestData->GetFieldFromLable(iItemID, "_Icon",	ldtFieldIcon);
	//iIcon = ldtFieldIcon.uData.lValue;

	//m_pLDTQuestData->GetFieldFromLable(iItemID, "_IconIndex",	ldtFieldIconIndex);
	//iIconIndex = ldtFieldIconIndex.uData.lValue;	

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Visible", ldtFieldVisible);
	iVisible = ldtFieldVisible.uData.lValue;

	//if(pQuestAttr->SetQuestAttr(iItemID, strName, iIcon, iIconIndex, iVisible) == false)
	if(pQuestAttr->SetQuestAttr(iItemID, strName, iVisible) == false)
		return false;

	
	// ����Ʈ Require Stat 
	LDT_Field ldtFieldRequireType;
	LDT_Field ldtFieldRequireID;
	LDT_Field ldtFieldRequireValue1;
	LDT_Field ldtFieldRequireValue2;
	int iRequireType = 0;
	int iRequireID = 0;
	int iRequireValue1 = 0;
	int iRequireValue2 = 0;
	
	char szFieldRequireType[64];
	char szFieldRequireID[64];
	char szFieldRequireValue1[64];
	char szFieldRequireValue2[64];
	for(i = 0; i < QUEST_MAX_REQUIRE; i++) {
		ZeroMemory(szFieldRequireType, 64);
		ZeroMemory(szFieldRequireID, 64);
		ZeroMemory(szFieldRequireValue1, 64);
		ZeroMemory(szFieldRequireValue2, 64);
		wsprintf(szFieldRequireType,	"_Require%d_Type",		i+1);
		wsprintf(szFieldRequireID,		"_Require%d_ID",		i+1);
		wsprintf(szFieldRequireValue1,	"_Require%d_Value1",	i+1);
		wsprintf(szFieldRequireValue2,	"_Require%d_Value2",	i+1);
		
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireType,	ldtFieldRequireType);
		iRequireType = ldtFieldRequireType.uData.lValue;
		//if(iRequireType == 0)
		//	break;

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireID,	ldtFieldRequireID);
		iRequireID = ldtFieldRequireID.uData.lValue;

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireValue1, ldtFieldRequireValue1);
		iRequireValue1 = ldtFieldRequireValue1.uData.lValue;

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireValue2, ldtFieldRequireValue2);
		iRequireValue2 = ldtFieldRequireValue2.uData.lValue;

		////[2006/6/21] ������ ��āEüũ�� ����E��?�ٲ��鼭 ����Ǿ�?E�����ε�E..
		//if(iRequireType == REQUIRE_TYPE_ITEM ||iRequireType == REQUIRE_TYPE_SKILL || iRequireType == REQUIRE_TYPE_QUEST) {
		//	int iTemp = iRequireID;
		//	iRequireID = iRequireValue1;
		//	iRequireValue1 = iTemp;
		//}
		
		if(pQuestAttr->SetQuestRequireStat(i, iRequireType, iRequireID, iRequireValue1, iRequireValue2) ==  false)
			break;
	}

	//Reword Require
	for(i = 0; i < QUEST_MAX_RANK; i++) {
		for(int j = 0; j < QUEST_MAX_RANK_REQUIRE; j++) {
			ZeroMemory(szFieldRequireType, 64);
			ZeroMemory(szFieldRequireID, 64);
			ZeroMemory(szFieldRequireValue1, 64);
			ZeroMemory(szFieldRequireValue2, 64); //_Rank1_Require1_Type
			wsprintf(szFieldRequireType,	"_Rank%d_Require%d_Type",		i+1, j+1);
			wsprintf(szFieldRequireID,		"_Rank%d_Require%d_ID",			i+1, j+1);
			wsprintf(szFieldRequireValue1,	"_Rank%d_Require%d_Value1",		i+1, j+1);
			wsprintf(szFieldRequireValue2,	"_Rank%d_Require%d_Value2",		i+1, j+1);

			m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireType,	ldtFieldRequireType);
			iRequireType = ldtFieldRequireType.uData.lValue;
			//if(iRequireType == 0)
			//	break;

			m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireID,	ldtFieldRequireID);
			iRequireID = ldtFieldRequireID.uData.lValue;

			m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireValue1, ldtFieldRequireValue1);
			iRequireValue1 = ldtFieldRequireValue1.uData.lValue;

			m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRequireValue2, ldtFieldRequireValue2);
			iRequireValue2 = ldtFieldRequireValue2.uData.lValue;			

			if(pQuestAttr->SetQuestRewordStat(i, j, iRequireType, iRequireID, iRequireValue1, iRequireValue2) ==  false)
				break;
		}
	}


	// Acquisition Effect
	LDT_Field ldtFieldAcquistionEffect;
	int iAcquistionEffect = 0;

	char szFieldAcquistionEffect[64];	
	for(i = 0; i < QUEST_MAX_ACQUISITION_EFFECTID; i++) {
		ZeroMemory(szFieldAcquistionEffect, 64);
		wsprintf(szFieldAcquistionEffect,	"_Acquisition_EffectID%d",	i+1);
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldAcquistionEffect, ldtFieldAcquistionEffect);
		iAcquistionEffect = ldtFieldAcquistionEffect.uData.lValue;
		//if(iAcquistionEffect == 0)
		//	break;

		if(pQuestAttr->SetAcquisitionEffect(i, iAcquistionEffect) == false)
			break;
	}

	// Acquistion Item
	LDT_Field ldtFieldAcquistionItemID;
	LDT_Field ldtFieldAcquistionStack;
	LDT_Field ldtFieldAcquistionRear;
	int iAcquistionItemID = 0;
	int iAcquistionItemStack = 0;
	int iAcquistionItemRear = 0;

	char szFieldAcquistionItemID[64];
	char szFieldAcquistionStack[64];
	char szFieldAcquistionRear[64];
	for(i = 0; i < QUEST_MAX_ACQUISITION_ITEM; i++) {
		ZeroMemory(szFieldAcquistionItemID, 64);
		ZeroMemory(szFieldAcquistionStack, 64);
		ZeroMemory(szFieldAcquistionRear, 64);
		wsprintf(szFieldAcquistionItemID,	"_Acquisition_ItemID%d",	i+1);
		wsprintf(szFieldAcquistionStack,	"_Acquisition_StackCount%d",	i+1);
		wsprintf(szFieldAcquistionRear,	"_Acquisition_Rare%d",		i+1);
		
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldAcquistionItemID,	ldtFieldAcquistionItemID);
		iAcquistionItemID = ldtFieldAcquistionItemID.uData.lValue;
		//if(iAcquistionItemID == 0)
		//	break;

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldAcquistionStack,		ldtFieldAcquistionStack);
		iAcquistionItemStack = ldtFieldAcquistionStack.uData.lValue;
		
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldAcquistionRear,		ldtFieldAcquistionRear);
		iAcquistionItemRear = ldtFieldAcquistionRear.uData.lValue;

		if(pQuestAttr->SetAcquisitionItem(i, iAcquistionItemID, iAcquistionItemStack, iAcquistionItemRear) ==  false)
			break;
	}

	// Mission
	LDT_Field ldtFieldMissionType;
	LDT_Field ldtFieldMissionID;
	LDT_Field ldtFieldMissionCount;
	LDT_Field ldtFieldMissionOnOff;
	int iMissionType = 0;
	int iMissionID = 0;
	int iMissionCount = 0;
	bool bMissionOnOff = 0;
	
	char szFieldMissionType[64];
	char szFieldMissionID[64];
	char szFieldMissionCount[64];
	char szFidleMissionOnOff[64];
	for(i = 0 ; i < QUEST_MAX_MISSION; i++) {
		ZeroMemory(szFieldMissionType, 64);
		ZeroMemory(szFieldMissionID, 64);
		ZeroMemory(szFieldMissionCount, 64);
		ZeroMemory(szFidleMissionOnOff, 64);
		wsprintf(szFieldMissionType,	"_Mission_Type%d",	i+1);
		wsprintf(szFieldMissionID,		"_Mission_ID%d",	i+1);
		wsprintf(szFieldMissionCount,	"_Mission_Count%d",	i+1);
		wsprintf(szFidleMissionOnOff,	"_Mission_OnOff%d",	i+1);

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldMissionType,		ldtFieldMissionType);
		iMissionType = ldtFieldMissionType.uData.lValue;
		//if(iMissionType == 0)
		//	break;
		
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldMissionID,		ldtFieldMissionID);
		iMissionID = ldtFieldMissionID.uData.lValue;
		
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldMissionCount,	ldtFieldMissionCount);
		iMissionCount = ldtFieldMissionCount.uData.lValue;

		//[2007/1/9] - jinssaga   
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFidleMissionOnOff,	ldtFieldMissionOnOff);
		bMissionOnOff = (ldtFieldMissionOnOff.uData.lValue == 0)? false : true;		

		if(pQuestAttr->SetMission(i, (MISSION_TYPE)iMissionType, iMissionID, iMissionCount, bMissionOnOff) == false)
			break;
	}

	// ConsumeItem
	LDT_Field ldtFieldConsumeItemID;
	LDT_Field ldtFieldConsumeItemStack;
	int iConsumeItemID = 0;
	int iConsumeItemStack = 0;
	
	char szFieldConsumeItemID[64];
	char szFieldConsumeItemStack[64];
	for(i = 0; i < QUEST_MAX_CONSUMPTION_ITEM; i++) {
		ZeroMemory(szFieldConsumeItemID, 64);
		ZeroMemory(szFieldConsumeItemStack, 64);
		wsprintf(szFieldConsumeItemID,		"_Consumption_ItemID%d",	i+1);
		wsprintf(szFieldConsumeItemStack,	"_Consumption_ItemCount%d",	i+1);
		
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldConsumeItemID,	ldtFieldConsumeItemID);
		iConsumeItemID = ldtFieldConsumeItemID.uData.lValue;
		//if(iConsumeItemID == 0)
		//	break;

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldConsumeItemStack, ldtFieldConsumeItemStack);
		iConsumeItemStack = ldtFieldConsumeItemStack.uData.lValue;

		if(pQuestAttr->SetCunsumeItem(i, iConsumeItemID, iConsumeItemStack) == false)
			break;
	}

	// Reword Effect
	//LDT_Field ldtFieldRewordEffect;
	//int iRewordEffect = 0;
	
	//char szFieldRewordEffect[64];
	////
	//for(i = 0; i < QUEST_MAX_REWARD_EFFECTID; i++) {
	//	ZeroMemory(szFieldRewordEffect, 64);
	//	wsprintf(szFieldRewordEffect,		"_Reward_EffectID%d",	i+1);
	//	
	//	m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRewordEffect,	ldtFieldRewordEffect);
	//	iRewordEffect = ldtFieldRewordEffect.uData.lValue;
	//	//if(iRewordEffect == 0)
	//	//	break;

	//	if(pQuestAttr->SetRewordEffect(i, iRewordEffect) == false)
	//		break;
	//}

	//// Reword Item
	//LDT_Field ldtFieldRewordItemID;
	//LDT_Field ldtFieldRewordStack;
	//LDT_Field ldtFieldRewordRear;
	//int iRewordItemID = 0;
	//int iRewordItemStack = 0;
	//int iRewordItemRear = 0;

	//char szFieldRewordItemID[64];
	//char szFieldRewordStack[64];
	//char szFieldRewordRear[64];
	//for(i = 0; i < QUEST_MAX_REWARD_ITEM; i++) {
	//	ZeroMemory(szFieldRewordItemID, 64);
	//	ZeroMemory(szFieldRewordStack, 64);
	//	ZeroMemory(szFieldRewordRear, 64);
	//	wsprintf(szFieldRewordItemID,	"_Reward_ItemID%d",	i+1);
	//	wsprintf(szFieldRewordStack,	"_Reward_StackCount%d",	i+1);
	//	wsprintf(szFieldRewordRear,		"_Reward_Rare%d",	i+1);

	//	m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRewordItemID,	ldtFieldRewordItemID);
	//	iRewordItemID = ldtFieldRewordItemID.uData.lValue;
	//	//if(iRewordItemID == 0)
	//	//	break;

	//	m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRewordStack,	ldtFieldRewordStack);
	//	iRewordItemStack = ldtFieldRewordStack.uData.lValue;

	//	m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRewordRear,	ldtFieldRewordRear);
	//	iRewordItemRear = ldtFieldRewordRear.uData.lValue;

	//	if(pQuestAttr->SetRewordItem(i, iRewordItemID, iRewordItemStack, iRewordItemRear) == false)
	//		break;
	//}	

	// Reword Rank Info
	LDT_Field ldtFieldRankType;
	LDT_Field ldtFieldRankID;
	LDT_Field ldtFieldRankProbability;
	char szFieldRankType[64];
	char szFieldRankID[64];
	char szFieldRankProbability[64];
	for(i = 0; i < QUEST_MAX_RANK; i++) {
		ZeroMemory(szFieldRankType, 64);
		wsprintf(szFieldRankType,			"_Rank%d_Type",	i+1);
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRankType,	ldtFieldRankType);
		REWARD_TYPE iType = (REWARD_TYPE)(ldtFieldRankType.uData.lValue);
		pQuestAttr->m_RewordRank[i].SetRankType(iType);
		
		for(int j = 0; j < QUEST_MAX_REWARD; j++) {
			ZeroMemory(szFieldRankID, 64);
			ZeroMemory(szFieldRankProbability, 64);
			wsprintf(szFieldRankID,				"_Rank%d_ID%d",				i+1, j+1);
			wsprintf(szFieldRankProbability,	"_Rank%d_Probability%d",	i+1, j+1);
			
			m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRankID,			ldtFieldRankID);
			m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldRankProbability,	ldtFieldRankProbability);
			
			int iID = ldtFieldRankID.uData.lValue;
			int iProbability = ldtFieldRankProbability.uData.lValue;
			pQuestAttr->m_RewordRank[i].m_Info[j].SetRewordInfo(iID, iProbability);
		}			
	}

	// Quest Info
	LDT_Field ldtFieldRewordNpcID;
	//LDT_Field ldtFieldPlaceInfo;
	//LDT_Field ldtFieldNpcInfo;
	LDT_Field ldtFieldTalk1;
	LDT_Field ldtFieldTalk2;
	LDT_Field ldtFieldPurpose;
	
	int iRewordNpcID = 0;
	//std::string strPlaceInfo = "";
	//std::string strNpcInfo = "";
	std::string strTalk1 = "";
	std::string strTalk2 = "";
	std::string strPurpose = "";

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Complete_NPCID",	ldtFieldRewordNpcID);
	iRewordNpcID = ldtFieldRewordNpcID.uData.lValue;

	//m_pLDTQuestData->GetFieldFromLable(iItemID, "_Place_Info",	ldtFieldPlaceInfo);
	//strPlaceInfo = ldtFieldPlaceInfo.uData.pValue;

	//m_pLDTQuestData->GetFieldFromLable(iItemID, "_NPC_Info",	ldtFieldNpcInfo);
	//strNpcInfo = ldtFieldNpcInfo.uData.pValue;

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Talk1",	ldtFieldTalk1);	
	if(ldtFieldTalk1.uData.pValue)
		strTalk1 = ldtFieldTalk1.uData.pValue;

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Talk2",	ldtFieldTalk2);

	if( ldtFieldTalk2.uData.pValue )
		strTalk2 = ldtFieldTalk2.uData.pValue;

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Purpose",	ldtFieldPurpose);
	if(ldtFieldPurpose.uData.pValue)
		strPurpose = ldtFieldPurpose.uData.pValue;

	if(pQuestAttr->SetQuestAttrInfo(strTalk1, strTalk2, strPurpose, iRewordNpcID) == false)
		return false;

	
	// NPC Info
	LDT_Field ldtFieldNpcIcon;
	LDT_Field ldtFieldNpcIconIndex;
	LDT_Field ldtFieldNpcPlace;
	LDT_Field ldtFieldNpcName;	
	int iNpcIcon = 0;
	int iNpcIconIndex = 0;
	std::string strNpcPlace = "";
	std::string strNpcName = "";

	char szFieldNpcIcon[64];
	char szFieldNpcIconIndex[64];
	char szFieldNpcPlace[64];
	char szFieldNpcName[64];
	for(i = 0; i < QUEST_NPC_MAX; i++) {
		ZeroMemory(szFieldNpcIcon, 64);
		ZeroMemory(szFieldNpcIconIndex, 64);
		ZeroMemory(szFieldNpcPlace, 64);
		ZeroMemory(szFieldNpcName, 64);
		wsprintf(szFieldNpcIcon,		"_Icon%d",			i+1);
		wsprintf(szFieldNpcIconIndex,	"_IconIndex%d",		i+1);
		wsprintf(szFieldNpcPlace,		"_Place_Info%d",	i+1);
		wsprintf(szFieldNpcName,		"_NPC_Info%d",		i+1);

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldNpcIcon,	ldtFieldNpcIcon);
		iNpcIcon = ldtFieldNpcIcon.uData.lValue;
		
		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldNpcIconIndex,	ldtFieldNpcIconIndex);
		iNpcIconIndex = ldtFieldNpcIconIndex.uData.lValue;

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldNpcPlace,	ldtFieldNpcPlace);
		if(ldtFieldNpcPlace.uData.pValue)
			strNpcPlace = ldtFieldNpcPlace.uData.pValue;

		m_pLDTQuestData->GetFieldFromLable(iItemID, szFieldNpcName,	ldtFieldNpcName);
		if(ldtFieldNpcName.uData.pValue)
			strNpcName = ldtFieldNpcName.uData.pValue;

		if(pQuestAttr->SetNpc(i, iNpcIcon, iNpcIconIndex, strNpcPlace, strNpcName) == false)
			return false;
	}
	
	//Npc Message
	LDT_Field ldtFieldMsgAccept;
	LDT_Field ldtFieldImageAccept;
	LDT_Field ldtFieldMsgReword;
	LDT_Field ldtFieldImageReword;	
	int iImageAccept = 0;
	int iImageReword = 0;
	std::string strMsgAccept = "";
	std::string strMsgReword = "";	

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Accept_Message",	ldtFieldMsgAccept);
	if(ldtFieldMsgAccept.uData.pValue)
		strMsgAccept = ldtFieldMsgAccept.uData.pValue;

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Complete_Message",	ldtFieldMsgReword);
	if(ldtFieldMsgReword.uData.pValue)
		strMsgReword = ldtFieldMsgReword.uData.pValue;

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Accept_Image",	ldtFieldImageAccept);
	iImageAccept = ldtFieldImageAccept.uData.lValue;

	m_pLDTQuestData->GetFieldFromLable(iItemID, "_Complete_Image",	ldtFieldImageReword);
	iImageReword = ldtFieldImageReword.uData.lValue;

	if(pQuestAttr->SetNpcMessage(strMsgAccept, iImageAccept, strMsgReword, iImageReword) == false)
		return false;

	//[2006/6/23]	City Name
	LDT_Field ldtFieldCityName;
	m_pLDTQuestData->GetFieldFromLable(iItemID, "_City_Name",	ldtFieldCityName);
	pQuestAttr->m_iCityName = (CITY_NAME)ldtFieldCityName.uData.lValue;

	// AcceptType [9/20/2007 AJJIYA]
	LDT_Field ldtFieldAcceptType;
	m_pLDTQuestData->GetField( iItemID, 121,	ldtFieldAcceptType );		//	_Quest_Type
	pQuestAttr->m_eAcceptType	=	(QUEST_ACCEPTTYPE)ldtFieldAcceptType.uData.lValue;
	
	return true;
}


//------------------------------------------------------------------------------------
void SPQuestManager::SendAcceptQuest(int iType, int iTypeID, int iQuestID)
{
	// int				iNpcID;			// NPC���̵�E
	// UINT32			uiQuestID;		// ����Ʈ���̵�E

	if(g_pCheckManager->IsDBBlock()) {
		DXUTOutputDebugString("\tSPQuestManager::SendAcceptQuest DB Working Block\n");
		return;
	}

	if(m_bSendPacket) {
		DXUTOutputDebugString("\tSPQuestManager::SendAcceptQuest Packet Send Block\n");
		return;
	}
	
	//
	CPacket Packet;
	Packet.Add((UINT32)QUEST_CS_ACCEPT);
	Packet.Add((UINT8)iType);
	Packet.Add((UINT32)iTypeID);
	Packet.Add((UINT32)iQuestID);

	g_pCheckManager->SetDBBlock(true);
	
	m_bSendPacket = true;

	//�̺κ� ���ϰ� ���� ������E����...
	g_pNetworkManager->SPPerformMessage(QUEST_CS_ACCEPT, 0, (LPARAM)&Packet);	
}


//------------------------------------------------------------------------------------
void SPQuestManager::SendGiveUpQuest(int iQuestID)
{
	// UINT32			uiQuestID;		// ����Ʈ���̵�E

	if(g_pCheckManager->IsDBBlock()) {
		DXUTOutputDebugString("\tSPQuestManager::SendGiveUpQuest DB Working Block\n");
		return;
	}

	if(m_bSendPacket) {		
		DXUTOutputDebugString("\tSPQuestManager::SendGiveUpQuest Packet Send Block\n");
		return;
	}
	
	//
	CPacket Packet;
	Packet.Add((UINT32)QUEST_CS_CANCEL);
	Packet.Add((UINT32)iQuestID);
	
	m_bSendPacket = true;

	g_pNetworkManager->SPPerformMessage(QUEST_CS_CANCEL, 0, (LPARAM)&Packet);
}


//------------------------------------------------------------------------------------
void SPQuestManager::SendFinishQuest(int iNpcID, int iQuestID, int iRank, int iReward)
{
	// int				iNpcID;			// NPC���̵�E
	// UINT32			uiQuestID;		// ����Ʈ���̵�E
	//UINT8				byRank = 0;		// 0, 1, 2
	//UINT8				byReward = 0;	// ����?E϶?������ ������ �����ε���(0, 1, 2)

	if(g_pCheckManager->IsDBBlock()) {
		
		DXUTOutputDebugString("\tSPQuestManager::SendFinishQuest DB Working Block\n");
		return;
	}

	if(m_bSendPacket) {
		DXUTOutputDebugString("\tSPQuestManager::SendFinishQuest Packet Send Block\n");
		return;
	}
	
	//
	CPacket Packet;
	Packet.Add((UINT32)QUEST_CS_FINISH);
	Packet.Add((UINT32)iNpcID);
	Packet.Add((UINT32)iQuestID);
	Packet.Add((UINT8)iRank);
	Packet.Add((UINT8)iReward);

	g_pCheckManager->SetDBBlock(true);
	
	m_bSendPacket = true;

	g_pNetworkManager->SPPerformMessage(QUEST_CS_FINISH, 0, (LPARAM)&Packet);
}


//------------------------------------------------------------------------------------
void SPQuestManager::SendMissionAction(int iActionID)
{
	// UINT32			uiActionID;		// �׼Ǿ��̵�E

	//
	CPacket Packet;
	Packet.Add((UINT32)MISSION_CS_ACTION);
	Packet.Add((UINT32)iActionID);

	g_pNetworkManager->SPPerformMessage(MISSION_CS_ACTION, 0, (LPARAM)&Packet);
}


//------------------------------------------------------------------------------------
void SPQuestManager::SetReturnMsg(QUEST_RETURN iReturn)
{
	std::string strMsg = "";
	strMsg.clear();
	
	switch(iReturn) {
		case QUEST_RETURN_A_INVAILD:
			//strMsg = "����E�� ����Ʈ ����E����";
			break;
		case QUEST_RETURN_A_FULL:
			//strMsg = "����Ʈ ����E����Ʈ Full";
			break;
		case QUEST_RETURN_A_INVEN:
			if(g_pResourceManager->GetGlobalString(6001001) != NULL)
				strMsg = g_pResourceManager->GetGlobalString(6001001);
			break;
		case QUEST_RETURN_F_SLOT:
			//strMsg = "����Ʈ �Ϸ�E�κ��丮 ����";
			if(g_pResourceManager->GetGlobalString(6001004) != NULL)
				strMsg = g_pResourceManager->GetGlobalString(6001004);
			break;
		case QUEST_RETURN_F_INVAILD:
			//strMsg = "����Ʈ �Ϸ�E����E�� ����";
			break;
		case QUEST_RETURN_F_NOTCOMPLETE:
			//strMsg = "����Ʈ �Ϸ�E�̼��� ��������";
			break;
		case QUEST_RETURN_F_NPC:
			//strMsg = "����Ʈ �Ϸ�E�Ϸ�ENPC�ƴ�";
			break;
		case QUEST_RETURN_F_INVEN:
			if(g_pResourceManager->GetGlobalString(6001001) != NULL)
				strMsg = g_pResourceManager->GetGlobalString(6001001);
			break;
		case QUEST_RETURN_OK:
			//strMsg = "Quest ����E�Ǵ� �Ϸ�E����E..";
			break;
		default:
			break;
	}
	
	if(strMsg != "") {
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
	}	
}


