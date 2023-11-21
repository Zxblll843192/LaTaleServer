// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPClientCommandBinder
// Comment : 
// Creation : metalgeni 2003-06-16 ���� 4:50:38
//***************************************************************************

#pragma warning(disable:4786)

#include <string>
#include "Packet.h"
#include "PacketID.h"

#include "SPCommon.h"
#include "PacketHandler.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPNetworkDEF.h"
#include "SPNetworkManager.h"

#include "SPJoyPadManager.h"

#include "SPMainGameDEF.H"
#include "SPSubGameManager.h"
#include "SPMainGameManager.h"
#include "SPMouseCursor.h"
#include "SPWindowDEF.h"
#include "SPInterfaceManager.h"

#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPGOBModel.h"
#include "SPGOBModelUnit.h"
#include "SPAvatarModelUnit.h"
#include "SPGOBCluster.h"

#include "SPGameObject.h"
#include "SPGOBStatus.h"
#include "SPGOBCoordPhysics.h"
#include "SPGOBModelUnit.h"			
#include "SPPlayerEquipInfo.h"
#include "SPGOBStatus.h"			
#include "SPPlayerInvenArchive.h"	
#include "SPPlayerStatusModel.h"	
#include "SPPlayerEquipInfo.h"
#include "SPITEMAttr.h"
#include "SPItemCluster.h"			//[2005/6/16] - jinhee
#include "SPItemStatus.h"
#include "SPPlayer.h"
#include "SPGOBManager.h"
#include "SPGuildArchive.h"
#include "SPIndun.h"
#include "SPIndunManager.h"

#include "SPLDTFile.h"
#include "SPLDTManager.h"
#include "SPResourceDef.h"
#include "SPResourceManager.h"
#include "SPUtil.h"
#include "SPLocalizeManager.h"

#include "SPEvent.h"
#include "SPEventManager.h"
#include "./SPMainGame/SPCharacter/SPPlayer/RTREffect/SPTumbleCloud.h"

#include "SPCommandDef.h"
#include "SPClientCommandBinder.h"



SPClientCommandBinder::SPClientCommandBinder()
{
	m_bInterfaceHide	=	true;
}

SPClientCommandBinder::~SPClientCommandBinder()
{
}

void SPClientCommandBinder::ServerCommandExecute(const char* pszCommand)
{
	//TODO: Command History
	// m_vCommandHistory

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// ������ ���ǵ� ������.
	char szTmp[CHEAT_STRING_MAX];
	strncpy(szTmp, pszCommand, CHEAT_STRING_MAX);

	CPacket packet;
	packet.AddUINT32(CHEAT_CS_COMMAND);	

	int iLen = (int)strlen(szTmp);
	if(iLen > CHEAT_STRING_MAX) {
		iLen = CHEAT_STRING_MAX;
		*(szTmp + CHEAT_STRING_MAX) = 0;
	}
	packet.AddUINT8( iLen );
	packet.AddData( pszCommand, iLen);
	(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
	

	
	sscanf(pszCommand, "%s ", szTmp );

	string strCommand = szTmp;
	string strArgument;
	strArgument = pszCommand + strCommand.size();

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// ������ ���ÿ� Ŭ���̾�Ʈ�� �����ϴ� Ŀ�ǵ� ��
	//EXECUTE_CLIENT_COMMAND_MAP(	"Warp",			OnWarp				)
}

void SPClientCommandBinder::ClientCommandExecute(const char* pszCommand)
{
	//TODO: Command History
	// m_vCommandHistory

	char szTmp[256];	
	sscanf(pszCommand, "%s ", szTmp );

	string strCommand = szTmp;
	string strArgument;
	strArgument = pszCommand + strCommand.size();


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ŭ���̾�Ʈ�� Ŀ�ǵ� ��
	EXECUTE_CLIENT_COMMAND_MAP(	"cls",				OnClean				)
	EXECUTE_CLIENT_COMMAND_MAP(	"CLS",				OnClean				)
	EXECUTE_CLIENT_COMMAND_MAP(	"stat",				OnStat				)
	EXECUTE_CLIENT_COMMAND_MAP(	"stat_ex",			OnStatEx			)
	EXECUTE_CLIENT_COMMAND_MAP(	"fxg",				OnFXFroup			)
	EXECUTE_CLIENT_COMMAND_MAP(	"fxgclear",			OnFXFroupClear		)
	EXECUTE_CLIENT_COMMAND_MAP(	"bgm",				OnSetBGM			)
	EXECUTE_CLIENT_COMMAND_MAP(	"se",				OnSetEffect			)
	EXECUTE_CLIENT_COMMAND_MAP(	"bgmvol",			OnSetBGMVolume		)
	EXECUTE_CLIENT_COMMAND_MAP(	"sevol",			OnSetEffectVolume	)	
	EXECUTE_CLIENT_COMMAND_MAP(	"TakeShot",			OnTakeShot			)	
	EXECUTE_CLIENT_COMMAND_MAP(	"contrast",			OnContrast			)	
	EXECUTE_CLIENT_COMMAND_MAP(	"SoundStatus",		OnSoundStat			)	
	EXECUTE_CLIENT_COMMAND_MAP(	"tooltipidshow",	OnToolTipID			)	
	EXECUTE_CLIENT_COMMAND_MAP(	"interfacehide",	OnInterfaceHide		)	
	EXECUTE_CLIENT_COMMAND_MAP( "errorbreak",		OnErrorBreak	)

	// ����׿�
#ifdef _DEBUG
	EXECUTE_CLIENT_COMMAND_MAP(	"LDTTest",			OnLDTTest			)
	EXECUTE_CLIENT_COMMAND_MAP(	"LDTTest2",			OnLDTTest2			)

	EXECUTE_CLIENT_COMMAND_MAP(	"Connect",			OnConnect			)
	EXECUTE_CLIENT_COMMAND_MAP(	"Disconnect",		OnDisconnect		)
	EXECUTE_CLIENT_COMMAND_MAP(	"SendMsg",			OnSendMsg			)
	EXECUTE_CLIENT_COMMAND_MAP(	"BSON",				OnBeautyShopOn		)
	EXECUTE_CLIENT_COMMAND_MAP( "LDTTEST",			OnLDTSaveTest		)
	EXECUTE_CLIENT_COMMAND_MAP( "GUILD",			OnGuildInfo		)
	EXECUTE_CLIENT_COMMAND_MAP( "guild",			OnGuildInfo		)
	EXECUTE_CLIENT_COMMAND_MAP( "guildlv",			OnGuildLevelup	)
	EXECUTE_CLIENT_COMMAND_MAP( "guildem",			OnGuildEmblem	)
	EXECUTE_CLIENT_COMMAND_MAP( "gsend",			OnGuildSend		)
	EXECUTE_CLIENT_COMMAND_MAP( "crop",				OnCropInfo		)
	EXECUTE_CLIENT_COMMAND_MAP( "csend",			OnCropSend		)
	EXECUTE_CLIENT_COMMAND_MAP( "fdsset",			OnFDSSend		)
	EXECUTE_CLIENT_COMMAND_MAP( "savetex",			OnSaveTexture	)
	EXECUTE_CLIENT_COMMAND_MAP( "PadMode",			OnJoyPadMode	)
	EXECUTE_CLIENT_COMMAND_MAP( "PadSet",			OnJoyPadKey		)
	EXECUTE_CLIENT_COMMAND_MAP( "indun",			OnIndunEnter	)
	EXECUTE_CLIENT_COMMAND_MAP( "gpoint",			OnSetGuildPoint	)
	EXECUTE_CLIENT_COMMAND_MAP( "induninfo",		OnGetIndunInfo	)
	EXECUTE_CLIENT_COMMAND_MAP( "error",			OnErrorBreak	)
	EXECUTE_CLIENT_COMMAND_MAP( "textbook",			OnTextBook		)
	EXECUTE_CLIENT_COMMAND_MAP( "hold",				OnTriggerPlayer	)
	EXECUTE_CLIENT_COMMAND_MAP( "rsshow",			OnRSShow	)
	EXECUTE_CLIENT_COMMAND_MAP( "PVPR",				OnPVPReserve	)
	EXECUTE_CLIENT_COMMAND_MAP( "pvpload",			OnPVPLoadWait	)
	EXECUTE_CLIENT_COMMAND_MAP( "pvprank",			OnPVPRank	)
	EXECUTE_CLIENT_COMMAND_MAP( "pvpresult",		OnPVPResult	)
	EXECUTE_CLIENT_COMMAND_MAP( "pvptime",			OnPVPTimmer	)
	EXECUTE_CLIENT_COMMAND_MAP( "auction",			OnAuctionShow	)
	EXECUTE_CLIENT_COMMAND_MAP( "CashMode",			OnCashTradeMode	)
	EXECUTE_CLIENT_COMMAND_MAP( "CashSelect",		OnCashTradeSelect	)
	EXECUTE_CLIENT_COMMAND_MAP( "lovecutinend",		OnLoveCutInEnd)
	EXECUTE_CLIENT_COMMAND_MAP( "ReloadTumble",		OnTumbleReload	)

#endif
#ifdef _PHANTOM_EDITOR_ENABLE
	EXECUTE_CLIENT_COMMAND_MAP( "phantom",			OnPhantom )	
#endif

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// command map function list
void SPClientCommandBinder::OnLDTTest				(const char* pszCommand, const char* pszArg)
{
	SPLDTFile* pLDTFile;
	g_pResourceManager->GetLDTFromFileName(RES_FNAME_LDT_DESC, &pLDTFile);	

	if(pLDTFile == NULL) return;

	int recordCount = pLDTFile->GetItemCount();
	int fieldCount = pLDTFile->GetFieldCount();
	LDT_Field ldtField1;
	LDT_Field ldtField2;
	LDT_Field ldtField3;
	LDT_Field ldtField4;

	int		iItemID;
	char	szTemp[128];
	for( int record = 0; record < recordCount; record++ )
	{
		iItemID = pLDTFile->GetPrimaryKey( record );

		//_STRING			���ڿ�			txt
		//_DESC				����			txt
		//_NUMBERTest		�ѹ��׽�Ʈ		num
		//_YNTEST			���Ұ��׽�Ʈ	yn

		pLDTFile->GetFieldFromLable( iItemID, "_STRING",		ldtField1);
		pLDTFile->GetFieldFromLable( iItemID, "_DESC",			ldtField2); 
		pLDTFile->GetFieldFromLable( iItemID, "_NUMBERTest",	ldtField3); 
		pLDTFile->GetFieldFromLable( iItemID, "_YNTEST",		ldtField4);

		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)ldtField1.uData.pValue );
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)ldtField2.uData.pValue );

		ltoa(ldtField3.uData.lValue, szTemp, 10);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

		ltoa(ldtField4.uData.lValue, szTemp, 10);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	}
	SAFE_RELEASE(pLDTFile);
}


void SPClientCommandBinder::OnLDTTest2				(const char* pszCommand, const char* pszArg)
{
	SPLDTFile* pLDTFile;
	g_pResourceManager->GetLDTFromFileName("DATA/LDT/METALGENI_TEST.LDT", &pLDTFile);	

	if(pLDTFile == NULL) return;

	int recordCount = pLDTFile->GetItemCount();
	int fieldCount = pLDTFile->GetFieldCount();
	LDT_Field ldtField1;
	LDT_Field ldtField2;

	int		iItemID;
	char	szTemp[128];
	for( int record = 0; record < recordCount; record++ )
	{
		iItemID = pLDTFile->GetPrimaryKey( record );

		pLDTFile->GetFieldFromLable( iItemID, "test",		ldtField1);
		pLDTFile->GetFieldFromLable( iItemID, "test2",		ldtField2); 

		_i64toa( *(ldtField1.uData.pValue64), szTemp, 10);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

		_i64toa( *(ldtField2.uData.pValue64), szTemp, 10);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	}
	SAFE_RELEASE(pLDTFile);
}



void SPClientCommandBinder::OnClean				(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_CLEAR );
}


void SPClientCommandBinder::OnStat				(const char* pszCommand, const char* pszArg)
{
	if(g_pGOBManager->GetLocalPlayer() == NULL) return;	
	
	UINT uiValue;
	char szTemp[256];

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_LV		);		
	sprintf(szTemp, "STATUS_LV		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_LUK_BASE	);		
	sprintf(szTemp, "STATUS_LUK_BASE= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_ATK_BASE	); 		
	sprintf(szTemp, "STATUS_ATK_BASE= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_DEF_BASE	); 		
	sprintf(szTemp, "STATUS_DEF_BASE= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_ELE_BASE	); 		
	sprintf(szTemp, "STATUS_ELE_BASE= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );	

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_MHP_BASE	); 		
	sprintf(szTemp, "STATUS_MHP_BASE= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );	

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_MSP_BASE	); 		
	sprintf(szTemp, "STATUS_MSP_BASE= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	
	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_LUK		); 		
	sprintf(szTemp, "STATUS_LUK		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_ATK  		); 		
	sprintf(szTemp, "STATUS_ATK  	= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_DEF	 	); 		
	sprintf(szTemp, "STATUS_DEF	 	= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_ELE  		); 		
	sprintf(szTemp, "STATUS_ELE  	= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_MHP  		); 		
	sprintf(szTemp, "STATUS_MHP  	= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_MSP		); 		
	sprintf(szTemp, "STATUS_MSP		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_HP  		); 		
	sprintf(szTemp, "STATUS_HP  	= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_SP		); 		
	sprintf(szTemp, "STATUS_SP		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_EARTH		); 		
	sprintf(szTemp, "STATUS_EARTH	= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_WIND		); 		
	sprintf(szTemp, "STATUS_WIND	= %d", uiValue);	
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_WATER		); 		
	sprintf(szTemp, "STATUS_WATER		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_FIRE		); 		
	sprintf(szTemp, "STATUS_FIRE		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_NORMAL_ATK); 		
	sprintf(szTemp, "STATUS_NORMAL_ATK	= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValue(STATUS_HEAVY_ATK	); 		
	sprintf(szTemp, "STATUS_HEAVY_ATK	= %d", uiValue);																		
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

}


void SPClientCommandBinder::OnStatEx			(const char* pszCommand, const char* pszArg)
{
	UINT64 uiValue;
	char szTemp[256];
	
	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValueEX(STATUS_EX_EXP	);		
	sprintf(szTemp, "STATUS_EX_EXP		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	uiValue = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValueEX(STATUS_EX_ELY	);		
	sprintf(szTemp, "STATUS_EX_ELY		= %d", uiValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );	

}

void SPClientCommandBinder::OnFXFroup	(const char* pszCommand, const char* pszArg)
{
	int iVal;
	iVal = atoi(pszArg);
	g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_SET_FX_GROUP, iVal);
}

void SPClientCommandBinder::OnFXFroupClear	(const char* pszCommand, const char* pszArg)
{
	int iVal;
	iVal = atoi(pszArg);
	g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_SET_FX_GROUP_CLEAR, iVal);
}

void SPClientCommandBinder::OnSetBGM	(const char* pszCommand, const char* pszArg)
{
	int iVal;	
	iVal = atoi(pszArg);
	if(iVal == 0) {		
		SPSoundBase::GetInstance()->EnableBGM(false);
	} else {		
		SPSoundBase::GetInstance()->EnableBGM(true);
	}	
}

void SPClientCommandBinder::OnSetEffect	(const char* pszCommand, const char* pszArg)
{
	int iVal;	
	iVal = atoi(pszArg);
	if(iVal == 0) {		
		SPSoundBase::GetInstance()->EnableEffect(false);
	} else {		
		SPSoundBase::GetInstance()->EnableEffect(true);
	}	
}

void SPClientCommandBinder::OnSetBGMVolume(const char* pszCommand, const char* pszArg)
{
	float fVal;	
	fVal = atof(pszArg);
	SPSoundBase::GetInstance()->UpdateBGMVolume( fVal );
}

void SPClientCommandBinder::OnSetEffectVolume(const char* pszCommand, const char* pszArg)
{
	float fVal;	
	fVal = atof(pszArg);
	SPSoundBase::GetInstance()->UpdateEffectVolume( fVal );
}

void SPClientCommandBinder::OnTakeShot(const char* pszCommand, const char* pszArg)
{
	char szTemp[128];
	if(g_pVideo->SurfaceCapturePNG() == true) {
		sprintf(szTemp, "screen capture success.");
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
	} else {
		sprintf(szTemp, "screen capture fail.");
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
	}
}


void SPClientCommandBinder::OnContrast(const char* pszCommand, const char* pszArg)
{
	int iVal;	
	iVal = atoi(pszArg);

	g_pVideo->SetContrast( iVal);
}



void SPClientCommandBinder::OnSoundStat			(const char* pszCommand, const char* pszArg)
{
	int uiValue;
	float fValue;
	char szTemp[256];

	uiValue = SPSoundBase::GetInstance()->GetSoundOption();

	sprintf(szTemp, "ENABLE_BGM = %d", (uiValue & ENABLE_BGM	) ? 1 : 0 	);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	sprintf(szTemp, "ENABLE_EFFECT = %d", (uiValue & ENABLE_EFFECT	) ? 1 : 0	);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	sprintf(szTemp, "ENABLE_SYSTEM = %d", (uiValue & ENABLE_SYSTEM	) ? 1 : 0	);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

	sprintf(szTemp, "ENABLE_OPTION = %d", (uiValue & ENABLE_OPTION	) ? 1 : 0	);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
	

	fValue = SPSoundBase::GetInstance()->GetBGMVolume();
	sprintf(szTemp, "BGM_VOL = %f", fValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );	

	fValue = SPSoundBase::GetInstance()->GetEffectVolume();
	sprintf(szTemp, "EFFECT_VOL = %f", fValue);
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );

}

void SPClientCommandBinder::OnToolTipID(const char* pszCommand, const char* pszArg)
{
	int iVal	=	atoi( pszArg );

	g_pInterfaceManager->SPChildWndSendMessage( WIID_TOOLTIP , SPIM_REFRESH , (WPARAM)iVal , (LPARAM)iVal );
}

void SPClientCommandBinder::OnInterfaceHide(const char* pszCommand, const char* pszArg)
{
	m_bInterfaceHide	=	!m_bInterfaceHide;
	
	g_pInterfaceManager->SetShowDefaultWindow( m_bInterfaceHide );
}

void SPClientCommandBinder::OnErrorBreak(const char* pszCommand, const char* pszArg)
{	
	SPLDTFile* pLdtFile = NULL ;
	pLdtFile->GetFileName() ;
	pLdtFile->SaveToTXT("ForTest.txt") ;
}


//////////////////////////////////////////////////////////////////////////
//
//	Only Debug
//
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG

//extern void Connect(char*);
//extern void Disconnect();
//extern void SendMsg(char*);

void SPClientCommandBinder::OnConnect(const char* pszCommand, const char* pszArg)
{
	//::Connect((char*)pszArg);
}

void SPClientCommandBinder::OnDisconnect(const char* pszCommand, const char* pszArg)
{
	//::Disconnect();
}

void SPClientCommandBinder::OnSendMsg(const char* pszCommand, const char* pszArg)
{
	//::SendMsg((char*)pszArg);
}

// duragon [2006/10/09]
// Beautyshop Window Test
void SPClientCommandBinder::OnBeautyShopOn(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_BEAUTYSHOP, SP_NONE, SP_TOGGLE_ON, true) ;
}

// ����� LDTManager or LDTFile���� �� �� �ִ�.
void SPClientCommandBinder::OnLDTSaveTest(const char* pszCommand, const char* pszArg)
{
	SPLDTFile* pLdtFile = NULL ;
	SPLDTManager::GetInstance()->LoadLDTFileFromFile("DATA/LDT/BEAUTY_SHOP.LDT", &pLdtFile) ;

	pLdtFile->SaveToTXT("BEAUTY_SHOP_BEFORE.TXT") ;		// RESOURCE Folder �� ����
	
	///< ������ �߰�
	std::string strAddData = "255:4:50104:3:4:0:3:4:2:3:4:5:1:4:�߰�:1:9:�߰���:3:4:3:3:4:150100103:3:4:190160501:3:4:0:3:4:5:" ;
	pLdtFile->PushBack(strAddData) ;

	pLdtFile->SaveToTXT("BEAUTY_SHOP_AFTER.TXT") ;		// RESOURCE Folder �� ����
}

// duragon [2006/10/09]
// `guild 0 ==> Guild Create Window
// `guild 1 ==> Guild Info Window
void SPClientCommandBinder::OnGuildInfo(const char* pszCommand, const char* pszArg)
{
	int iVal	=	atoi( pszArg );
	if( iVal == 0 )
		g_pInterfaceManager->ShowWindow(WIID_GUILD_CREATE, SP_NONE, SP_TOGGLE_ON, true) ;
	else if(iVal == 1 )
		g_pInterfaceManager->ShowWindow(WIID_GUILD_INFO, SP_NONE, SP_TOGGLE_ON, true) ;
	else if(iVal == 2 )
		g_pInterfaceManager->ShowWindow(WIID_GUILD_DESTROY, SP_NONE, SP_TOGGLE_ON, true) ;
}

// For Guild Level up
//SPIM_LIST_ADDITEM				=	SPIM_USER+552,
//SPIM_LIST_CLEAR				=	SPIM_USER+553,
void SPClientCommandBinder::OnGuildLevelup(const char* pszCommand, const char* pszArg)
{
	int iVal	=	atoi( pszArg );
	switch(iVal)
	{
	case 1:
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_LEVELUP, SPIM_LIST_ADDITEM, 0, 0, false) ;
		break ;
	case 2:
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_LEVELUP, SPIM_LIST_CLEAR, 0, 0, false) ;
		break ;
	default:
		g_pInterfaceManager->ShowWindow(WIID_GUILD_LEVELUP, SP_NONE, SP_TOGGLE_ON, true) ;
		break ;
	}
}

// For Guild Level up
//SPIM_LIST_ADDITEM				=	SPIM_USER+552,
//SPIM_LIST_CLEAR				=	SPIM_USER+553,
void SPClientCommandBinder::OnGuildEmblem(const char* pszCommand, const char* pszArg)
{
	int iVal	=	atoi( pszArg );
	switch(iVal)
	{
	case 1:
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_EMBLEM, SPIM_LIST_ADDITEM, 0, 0, false) ;
		break ;
	case 2:
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_EMBLEM, SPIM_LIST_CLEAR, 0, 0, false) ;
		break ;
	default:
		g_pInterfaceManager->ShowWindow(WIID_GUILD_EMBLEM, SP_NONE, SP_TOGGLE_ON, true) ;
		break ;
	}
}

// duragon [2007/06/09]
void SPClientCommandBinder::OnCropInfo(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_CROPS, SP_NONE, SP_TOGGLE_ON, true) ;
}

void SPClientCommandBinder::OnCropSend(const char* pszCommand, const char* pszArg)
{
	int iCmd ;
	int iNOArg = 0 ;
	int iParam = 0 ;
	std::vector<std::string> vstrArg;
	CPacket packet;

	UINT32  lData ;

	if( (iNOArg = GetSeperateString(pszArg, vstrArg, ',')) < 1)
		return ;
	iCmd = atoi(vstrArg[0].c_str()) ;
	switch(iCmd)
	{
	case 1:		// ����ɱ�
		packet.AddUINT32( GUILD_CS_PLANT );	
		lData = atol(vstrArg[1].c_str()) ;
		packet.AddUINT32( lData );
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 2:		// ����ֱ�
		packet.AddUINT32( GUILD_CS_NOURISH );	
		lData = atol(vstrArg[1].c_str()) ;
		packet.AddUINT32( lData );
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 3:		// ����̱�
		packet.AddUINT32( GUILD_CS_GRUB );	
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 4:
		//g_pGOBManager->GetGuildArchive()->CropLevelUp() ;
		break ;
	case 5:
		iParam = atoi(vstrArg[1].c_str()) ;
		if( iParam == 0 )		return ;
		//g_pGOBManager->GetGuildArchive()->UpdateCropNPC(iParam) ;
		break ;
	}
}



void SPClientCommandBinder::OnGuildSend(const char* pszCommand, const char* pszArg)
{
	int iCmd ;
	int iNOArg = 0 ;
	std::vector<std::string> vstrArg;
	CPacket packet;
	char szTemp[256];

	long  lData ;
	UINT8 byData ;
	UINT8 arrGMark[2] ;

	if( (iNOArg = GetSeperateString(pszArg, vstrArg, ',')) < 1)
		return ;
	iCmd = atoi(vstrArg[0].c_str()) ;
	switch(iCmd)
	{
	case 1:
		packet.AddUINT32( GUILD_CS_GUILD_COMMON );	
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 2:
		packet.AddUINT32( GUILD_CS_MEMBERLIST );	
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 3:
		if( iNOArg != 6 ) {
			sprintf(szTemp, "GUILD_CS_CREATE Usage: `gsend 3,����,byGType,arrGMark[0],arrGMark[1],byGRank");
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
			break ;
		}
		packet.AddUINT32( GUILD_CS_CREATE );
		packet.AddData( vstrArg[1].c_str(), GUILD_MAX_NAME+1);
		byData = (UINT8)atoi(vstrArg[2].c_str()) ;
		packet.AddUINT8( byData ) ;
		arrGMark[0] = (UINT8)atoi(vstrArg[3].c_str()) ;
		arrGMark[1] = (UINT8)atoi(vstrArg[4].c_str()) ;
		packet.AddData( arrGMark, sizeof(BYTE)*2);
		byData = (UINT8)atoi(vstrArg[5].c_str()) ;
		packet.AddUINT8( byData ) ;
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 4:
		packet.AddUINT32( GUILD_CS_DESTROY );	
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 5:
		if( iNOArg != 2 ) {
			sprintf(szTemp, "GUILD_CS_UPDATE_SLOGAN Usage: `gsend 5,���ΰ� ");
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
			break ;
		}
		packet.AddUINT32( GUILD_CS_UPDATE_SLOGAN );	
		packet.AddData( vstrArg[1].c_str(), GUILD_MAX_SLOGAN+1);
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 6:
		if( iNOArg != 2 ) {
			sprintf(szTemp, "GUILD_CS_REQUEST Usage: `gsend 6,������̸� ");
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
			break ;
		}
		packet.AddUINT32( GUILD_CS_REQUEST );	
		packet.AddData( vstrArg[1].c_str(), LEN_NAME+1);
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 7:
		if( iNOArg != 2 ) {
			sprintf(szTemp, "GUILD_CS_REQUEST Usage: `gsend 7,��û���̸� ");
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
			break ;
		}
		packet.AddUINT32( GUILD_CS_JOIN );	
		packet.AddData( vstrArg[1].c_str(), LEN_NAME+1);
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 8:
		packet.AddUINT32( GUILD_CS_SECEDE );	
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 9:
		if( iNOArg != 2 ) {
			sprintf(szTemp, "GUILD_CS_EXPEL Usage: `gsend 9,DBNum");
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
			break ;
		}
		packet.AddUINT32( GUILD_CS_EXPEL );	
		lData = atol(vstrArg[1].c_str()) ;
		packet.AddUINT32( lData );	
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	case 0:
		if( iNOArg != 3 ) {
			sprintf(szTemp, "GUILD_CS_CHANGEGRADE Usage: `gsend 6,DBNum,byGrade");
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
			break ;
		}
		packet.AddUINT32( GUILD_CS_CHANGEGRADE );	
		lData = atol(vstrArg[1].c_str()) ;
		packet.AddUINT32( lData );
		byData = (UINT8)atoi(vstrArg[2].c_str()) ;
		packet.AddUINT8( byData );
		(((SPNetworkManager*)g_pNetworkManager)->GetPacketHandler())->PostMsg(&packet);
		break ;
	default:
		sprintf(szTemp, "1:�Ϲݱ������ 2:�������Ʈ 3:������ 4:����ı� 5:���ΰǼ��� ");
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
		sprintf(szTemp, "6:����ʴ�  7:��������   8:Ż��   9:����   0:��å���� ");
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szTemp );
		break ;
	}

}



/**
	��� ����ġ ���� (������ Ȯ�ο�)
*/
void SPClientCommandBinder::OnSetGuildPoint(const char* pszCommand, const char* pszArg)
{	
	int iVal	=	atoi( pszArg );
	if( iVal > -1 )
		g_pGOBManager->GetGuildArchive()->SetGuildTotalPoint(iVal) ;
}


/**
	�δ� ����� ġƮ
*/
void SPClientCommandBinder::OnIndunEnter(const char* pszCommand, const char* pszArg)
{	
	int iVal	=	atoi( pszArg );
	if( iVal > 0 )
		g_pSubGameManager->SPPerformMessage(SPGM_INDUN_IN_REQUEST, iVal);
}


/**
�δ� ����� ġƮ
*/
void SPClientCommandBinder::OnGetIndunInfo(const char* pszCommand, const char* pszArg)
{
	g_pkIndunManager->DisplayIndunInfo() ;
}

void SPClientCommandBinder::OnFDSSend(const char* pszCommand, const char* pszArg)
{	
	// Need Localize compare by SNDA, but didn't
	g_pNetworkManager->FDS_QueryState() ;
}

void SPClientCommandBinder::OnSaveTexture(const char* pszCommand, const char* pszArg)
{	
	static int iFileCount = 0;
	char strFileName[256];
	char szErrorMsg[256];
	std::string strLoadFile ;

	if( pszArg == NULL )
	{
		sprintf(szErrorMsg, "savetex DATA/LOGO/NowLoading1.PNG", pszArg);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szErrorMsg );
		return ;
	}
	strLoadFile = pszArg ;
	Trim(strLoadFile) ;

	CreateDirectory("GMark", NULL);

	for(;iFileCount < 9999;)  {
		sprintf(strFileName,	"GMark\\SPSCF%04d.BMP", iFileCount++);
		FILE *hFile = fopen(strFileName, "rb");
		if(hFile == NULL) break;
		fclose(hFile);
	}

	SPTexture* pTexture = NULL ;
	if( !g_pVideo->GetTextureMgr()->LoadTexture( strLoadFile.c_str(), &pTexture) )	{
		sprintf(szErrorMsg, "[%s] LoadTexture Fail ->savetex DATA/LOGO/NowLoading1.PNG ", strLoadFile.c_str());
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szErrorMsg );
		return ;
	}

	if( D3DXSaveTextureToFile(strFileName, D3DXIFF_BMP, pTexture->GetD3DTexture(), NULL) != S_OK ) {
		sprintf(szErrorMsg, "[%s] Texture to file Fail ", strLoadFile.c_str());
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szErrorMsg );
		return ;
	}

	sprintf(szErrorMsg, "[%s] Texture to file Save Ok ", strLoadFile.c_str());
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szErrorMsg );

	return ;
}


void SPClientCommandBinder::OnJoyPadMode(const char* pszCommand, const char* pszArg)
{
	int iVal;	
	iVal = atoi(pszArg);
	if(iVal == 0) {		
		g_pInputManager->GetJoyPadManager()->SetJoyStickMode(JOYSTICK_MODE_NULL);
	}
	else if(iVal == 1) {		
		g_pInputManager->GetJoyPadManager()->SetJoyStickMode(JOYSTICK_MODE_ANALOG);
	}
	else if(iVal ==  2) {
		g_pInputManager->GetJoyPadManager()->SetJoyStickMode(JOYSTICK_MODE_DIGITAL);
	}
	else {

	}
}


void SPClientCommandBinder::OnJoyPadKey(const char* pszCommand, const char* pszArg)
{	
	g_pInterfaceManager->ShowWindow(WIID_JOYSTICK, SP_NONE, SP_TOGGLE_ON, true) ;
}



void SPClientCommandBinder::OnTextBook(const char* pszCommand, const char* pszArg)
{	
	int iVal;	
	iVal = atoi(pszArg);
	if(iVal == 0) {		
		g_pSubGameManager->SPPerformMessage(SPGM_SET_BOOK_VIEW, 1, 100000);
		//g_pInterfaceManager->SetTextBookView(true) ;
	}
	else if(iVal == 1) {		
		g_pSubGameManager->SPPerformMessage(SPGM_SET_BOOK_VIEW, 0, 0);
		//g_pInterfaceManager->SetTextBookView(false) ;
	}
}

/**
	SPWindowRS Show Test
 */
void SPClientCommandBinder::OnRSShow(const char* pszCommand, const char* pszArg)
{	
	g_pInterfaceManager->ShowWindow(WIID_RSCLIENT, SP_NONE, SP_TOGGLE_ON, true) ;
}

/**
	ĳ������ ������ ���� �׽�Ʈ�� ���ؼ� ����Ѵ�.
	PVP���� ���� ��, ����� ���ö� ĳ���Ͱ� �������� �ʵ��� �ϱ� ���ؼ� ���
 */
void SPClientCommandBinder::OnTriggerPlayer(const char* pszCommand, const char* pszArg)
{
	int iVal;	
	SPPlayer* pPlayer  = NULL ;

	iVal = atoi(pszArg);
	pPlayer = g_pGOBManager->GetLocalPlayer() ;
	if( pPlayer )
	{
		if(iVal == 0) {		
			pPlayer->TriggerEnable(false) ;
		}
		else if(iVal == 1) {		
			pPlayer->TriggerEnable(true) ;
		}
	}
}


void SPClientCommandBinder::OnPVPReserve(const char* pszCommand, const char* pszArg)		// Pvp Reserve Window Test
{
	g_pInterfaceManager->ShowWindow(WIID_PVPRESERVE, SP_NONE, SP_TOGGLE_ON, true);
}



void SPClientCommandBinder::OnPVPLoadWait(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_PVP_LOADWAIT, SP_NONE, SP_TOGGLE_ON, true);
}


void SPClientCommandBinder::OnPVPRank(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_PVP_RANKING, SP_NONE, SP_TOGGLE_ON, true);
}


void SPClientCommandBinder::OnPVPResult(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_PVP_RESULT, SP_NONE, SP_TOGGLE_ON, true);
}

void SPClientCommandBinder::OnPVPTimmer(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_PVP_TIMMER, SP_NONE, SP_TOGGLE_ON, true);
}

void SPClientCommandBinder::OnAuctionShow(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_AUCTION, SP_NONE, SP_TOGGLE_ON, true);
}


void SPClientCommandBinder::OnCashTradeMode(const char* pszCommand, const char* pszArg)
{
	int iVal;	
	iVal = atoi(pszArg);	
	SPLocalizeManager::GetInstance()->SetCashTradeType(iVal);
}


void SPClientCommandBinder::OnCashTradeSelect(const char* pszCommand, const char* pszArg)
{
	g_pInterfaceManager->ShowWindow(WIID_CASH_TRADE_SELECT, SP_NONE, SP_TOGGLE_ON, true);
}

void SPClientCommandBinder::OnLoveCutInEnd(const char* pszCommand, const char* pszArg)
{
	if( g_pEventManager != NULL )
	{
		if( g_pEventManager->IsCutIn() == true )
		{
			g_pEventManager->OnCutInEnd();

			if( g_pInterfaceManager != NULL )
				g_pInterfaceManager->SetShowDefaultWindow( true );
		}
		else
		{
			g_pEventManager->SetCutIn( true );
			g_pEventManager->SetCutInState( CUT_IN_STATE_LOVE );
		}
	}
}

void SPClientCommandBinder::OnTumbleReload(const char* pszCommand, const char* pszArg)
{
	TumbleCloudLdtCfg::getInstance().ReloadLdt();
}

#endif

#ifdef _PHANTOM_EDITOR_ENABLE
#include "RTREffect/RTREffectManager.h"
void SPClientCommandBinder::OnPhantom(const char* pszCommand, const char* pszArg)
{
	static int id = 0;
	if (pszArg)
	{
		if (pszArg[1] == '0')
			g_pGOBManager->GetLocalPlayer()->getEffecgMgr()->DelItemRTREffect(id);
		else
		{
			g_pGOBManager->GetLocalPlayer()->getEffecgMgr()->DelItemRTREffect(id);
			id = ::atoi( ++pszArg );
			g_pGOBManager->GetLocalPlayer()->getEffecgMgr()->AddItemRTREffect(id);
		}
	}
}

#endif