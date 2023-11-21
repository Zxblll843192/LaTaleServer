
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
#include "SPEventDEF.h"
#include "SPEventManager.h"

#include "SPSubGameManager.h"
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
#include "SPGuildLDT.h"
#include "SPCropArchive.h"
#include "SPGuildArchive.h"

#include "SPAbuseFilter.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;


DEFINE_SC_PACKET_PROC(GUILD_SC_PCGUILD)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	PCGUILD				stPCGuild;							// ĳ���� �������
	GUILD_BROADCAST		stGuildBroad ;
		
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractStruct(&stPCGuild, sizeof(PCGUILD));

	// Ŭ���̾�Ʈ ó��
	g_pGOBManager->GetGuildArchive()->SetGuildBasicInfo(&stPCGuild) ;
	memcpy(&stGuildBroad, &stPCGuild, sizeof(GUILD_BROADCAST)) ;
	g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)&stGuildBroad);
}

DEFINE_SC_PACKET_PROC(GUILD_SC_GUILD_COMMON)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	GUILD_COMMON		stGuildCommon;						// �Ϲ� �������
		
	packet->ExtractUINT64(&ObjectGUID);	
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		packet->ExtractStruct(&stGuildCommon, sizeof(GUILD_COMMON));

		// Ŭ���̾�Ʈ ó��
		g_pGOBManager->GetGuildArchive()->SetGuildCommonInfo(&stGuildCommon) ;
	}

}

DEFINE_SC_PACKET_PROC(GUILD_SC_MEMBERLIST)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	//INT32				iMemberCnt;							// ��� �����
	//GUILD_MEMBER		stGuildMember;						// ��� �������
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		// Ŭ���̾�Ʈ ó��
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_MEMBER_LIST, 0, (LPARAM)packet) ;
		// g_pGOBManager->GetGuildArchive()->ReceiveGuildUserList(packet) ;
	}
}

DEFINE_SC_PACKET_PROC(GUILD_SC_CREATE)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	PCGUILD				stPCGuild;							// ĳ���� �������
	GUILD_BROADCAST		stGuildBroad ;
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		packet->ExtractStruct(&stPCGuild, sizeof(PCGUILD));
		// Ŭ���̾�Ʈ ó��
		// ����� ������ Emblem�� ���� ������Ʈ
		memcpy(&stGuildBroad, &stPCGuild, sizeof(GUILD_BROADCAST)) ;
		SPPlayer* pPlayer = (SPPlayer*)g_pGOBManager->Find(ObjectGUID);
		if( pPlayer == NULL )	{
			return ;
		}
		//��������
		if ( g_pCIGWLoaderDx9 )
		{
			g_pCIGWLoaderDx9->OnCommunityEventA(ceCreateGuild, stPCGuild.szGName );
		}
		pPlayer->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)&stGuildBroad);
		if( ObjectGUID == g_pGOBManager->GetLocalPlayer()->GetGUID() )
		{
			// Local Message
			g_pGOBManager->GetGuildArchive()->SetGuildBasicInfo(&stPCGuild) ;
			g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_CREATE, SPIM_GUILD_CREATE_RESULT, ErrorID, 0);
		}
	}
	else
	{
		// Error Message
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_CREATE, SPIM_GUILD_CREATE_RESULT, ErrorID, 0);
	}
}

DEFINE_SC_PACKET_PROC(GUILD_SC_DESTROY)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		SPPlayer* pPlayer = (SPPlayer*)g_pGOBManager->Find(ObjectGUID);
		if( pPlayer == NULL )	{
			return ;
		}
		pPlayer->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)0);

		if( ObjectGUID == g_pGOBManager->GetLocalPlayer()->GetGUID() )
		{
			g_pGOBManager->GetGuildArchive()->RemoveGuildInfo() ;
			if( g_pResourceManager->GetGlobalString(27000003) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000003) );
			else
			{
				TCHAR szError[64] ;
				wsprintf(szError, "[Guild]Destroy Success[%d]") ;
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szError );
			}
		}
	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		else
		{
			TCHAR szError[64] ;
			wsprintf(szError, "[Guild]Destroy Fail[%d]", ErrorID) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szError );
		}
	}
}

DEFINE_SC_PACKET_PROC(GUILD_SC_UPDATE_SLOGAN)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		g_pGOBManager->GetGuildArchive()->ChangeSlogun(1, NULL) ;
	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		else
		{
			TCHAR szError[64] ;
			wsprintf(szError, "[Guild]Update Slogun Fail[%d]", ErrorID) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szError );
		}
	}
}

DEFINE_SC_PACKET_PROC(GUILD_SC_REQUEST)
{
	//GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	//char				szGName[GUILD_MAX_NAME+1];			// ����
	//char				szCharName[LEN_NAME+1];				// ������ ���� ��û�ڸ�, ������ ���� ����ڸ�
	//GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)

	// �ʴ�� NoticeBox ������ Player���� ó��
	g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_GUILD_INVITE, (LPARAM)packet);
}

DEFINE_SC_PACKET_PROC(GUILD_SC_JOIN)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
	PCGUILD				stPCGuild;							// ĳ���� �������
	GUILD_BROADCAST		stGuildBroad ;
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	
	if(0 == ErrorID) // �����̸�
	{
		packet->ExtractStruct(&stPCGuild, sizeof(PCGUILD));
		memcpy(&stGuildBroad, &stPCGuild, sizeof(GUILD_BROADCAST)) ;
		SPPlayer* pPlayer = (SPPlayer*)g_pGOBManager->Find(ObjectGUID);
		if( pPlayer == NULL )	{
			return ;
		}
		//�������
		if ( g_pCIGWLoaderDx9 )
		{
			g_pCIGWLoaderDx9->OnCommunityEventA(ceJoinGuild, stPCGuild.szGName );
		}
		pPlayer->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)&stGuildBroad);
		if( ObjectGUID == g_pGOBManager->GetLocalPlayer()->GetGUID() )
		{
			g_pGOBManager->GetGuildArchive()->SetGuildBasicInfo(&stPCGuild) ;
		}
	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		else
		{
			TCHAR szError[64] ;
			wsprintf(szError, "[Guild] Join Fail[%d]", ErrorID) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szError );
		}
	}
	g_pGOBManager->GetGuildArchive()->ClearInviteName() ;
}

DEFINE_SC_PACKET_PROC(GUILD_SC_SECEDE)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);

	if(0 == ErrorID) // �����̸�
	{
		SPPlayer* pPlayer = (SPPlayer*)g_pGOBManager->Find(ObjectGUID);
		if( pPlayer == NULL )	{
			return ;
		}
		//�˳�����
		if ( g_pCIGWLoaderDx9 )
		{
			g_pCIGWLoaderDx9->OnCommunityEventA(ceQuitGuild, g_pGOBManager->GetGuildArchive()->GetGuildName() );
		}
		pPlayer->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)0);
		
		if( ObjectGUID == g_pGOBManager->GetLocalPlayer()->GetGUID() )
			g_pGOBManager->GetGuildArchive()->RemoveGuildInfo() ;

		g_pSubGameManager->SPPerformMessage(SPGM_INDUN_FORCE_EXIT, 0, 0);		// ���� ������
	}
	else
	{
		// Guild Secede Fail
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		else
		{
			TCHAR szError[64] ;
			wsprintf(szError, "[Guild] [%s]Secede Error[%d]", ErrorID) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szError );
		}
	}
}

DEFINE_SC_PACKET_PROC(GUILD_SC_EXPEL)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 != ErrorID)	// ���и�
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		else
		{
			TCHAR szError[64] ;
			wsprintf(szError, "[Guild] [%s]Expel Error[%d]", ErrorID) ;
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szError );
		}
	}
}

DEFINE_SC_PACKET_PROC(GUILD_SC_EXPEL_ME)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	packet->ExtractUINT64(&ObjectGUID);

	SPPlayer* pPlayer = (SPPlayer*)g_pGOBManager->Find(ObjectGUID);
	if( pPlayer == NULL )	{
		return ;
	}
	//�����忪��,�˳�����
	if ( g_pCIGWLoaderDx9 )
	{
		g_pCIGWLoaderDx9->OnCommunityEventA( ceQuitGuild, g_pGOBManager->GetGuildArchive()->GetGuildName() );
	}
	pPlayer->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)0);

	// Ŭ���̾�Ʈ ó��
	if( ObjectGUID == g_pGOBManager->GetLocalPlayer()->GetGUID() )
		g_pGOBManager->GetGuildArchive()->RemoveGuildInfo() ;

	g_pSubGameManager->SPPerformMessage(SPGM_INDUN_FORCE_EXIT, 0, 0);		// ���� ������
}

DEFINE_SC_PACKET_PROC(GUILD_SC_CHANGEGRADE)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 != ErrorID)	// ���и� ��û�ѻ���� �޴´�.
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
}

DEFINE_SC_PACKET_PROC(GUILD_SC_CHANGEGRADE_ME)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	UINT8				byGrade;							// ���� ��å
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT8(&byGrade);

	// Ŭ���̾�Ʈ ó��
	// ���� ó���� GUILD_SC_MSG_MEMBER ���� ����
	// ReceiveChangeGuildUser -> SetGuildAuthority -> UpdateGuildUserList -> UpdateRankControl
	g_pGOBManager->GetGuildArchive()->UpdateMyGrade((int)byGrade) ;
}

DEFINE_SC_PACKET_PROC(GUILD_SC_MSG_MEMBER)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	UINT8				byMemberMsgType;					// ����޼���Ÿ��(0:����, 1:Ż��, 2:����, 3:��������, 4:�α���, 5:�α׾ƿ�)
	GUILD_MEMBER		stGuildMember;						// �������
	char szMsg[256];
	TCHAR szPlayerName[MAX_LEN_NAME] ;

	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT8(&byMemberMsgType);
	packet->ExtractStruct(&stGuildMember, sizeof(GUILD_MEMBER));

	memset(szPlayerName, 0, MAX_LEN_NAME) ;
	g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_GETGOBNAME, (LPARAM)szPlayerName);

	// Ŭ���̾�Ʈ ó��
	int iMsgType = (int)byMemberMsgType ;
	switch( iMsgType )
	{
	case 0:		// ����
		//g_pGOBManager->GetGuildArchive()->ReceiveGuildUserJoin(&stGuildMember) ;
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_MEMBER_JOIN, 0, (LPARAM)&stGuildMember) ;
		if( g_pResourceManager->GetGlobalString(27000021) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000021), stGuildMember.szName);
		break ;
	case 1:		// Ż��
		//g_pGOBManager->GetGuildArchive()->ReceiveGuildUserSecede(&stGuildMember) ;
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_MEMBER_SECEDE, 0, (LPARAM)&stGuildMember) ;
		if( g_pResourceManager->GetGlobalString(27000022) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000022), stGuildMember.szName);
		break ;
	case 2:		// ����
		//g_pGOBManager->GetGuildArchive()->ReceiveGuildUserSecede(&stGuildMember) ;
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_MEMBER_SECEDE, 0, (LPARAM)&stGuildMember) ;
		if( g_pResourceManager->GetGlobalString(27000023) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000023), stGuildMember.szName);
		break ;
	case 3:		// ��������
		//g_pGOBManager->GetGuildArchive()->ReceiveChangeGuildUser(&stGuildMember) ;
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_MEMBER_INFOCHANGE, 0, (LPARAM)&stGuildMember) ;
		if( g_pResourceManager->GetGlobalString(27000025) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000025), stGuildMember.szName);
		break ;
	case 4:		// �α���
		if( g_pResourceManager->GetGlobalString(27000026) && strcmp(stGuildMember.szName, szPlayerName) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000026), stGuildMember.szName);
		else
			return ;
		break ;
	case 5:		// �α׾ƿ�
		if( g_pResourceManager->GetGlobalString(27000027) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000027), stGuildMember.szName);
		break ;
	case 6:		// ����������
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_MEMBER_INFOCHANGE, 0, (LPARAM)&stGuildMember) ;
		if( g_pResourceManager->GetGlobalString(27000073) )
			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000073), stGuildMember.szName);
		break ;
	default:
		wsprintf(szMsg, "[Guild] MEMBER Information Change[%d]", iMsgType);
		break ;
	}
	g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMsg );
}

DEFINE_SC_PACKET_PROC(GUILD_SC_MSG_GUILD)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	UINT8				byGuildMsgType;						// ���޼���Ÿ��(0:���ΰǺ���, 1:��ũ����)
	GUILD_COMMON		stGuildCommon;						// �Ϲ����� �������
	char szMsg[256];

	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT8(&byGuildMsgType);
	packet->ExtractStruct(&stGuildCommon, sizeof(GUILD_COMMON));

	// Ŭ���̾�Ʈ ó��
	int iMsgType = (int)byGuildMsgType ;
	switch( iMsgType )
	{
	case 0:		// ���ΰ� ����
		g_pGOBManager->GetGuildArchive()->SetGuildCommonInfo(&stGuildCommon) ;
		if( g_pResourceManager->GetGlobalString(27000024) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000024) );
		break ;
	case 1:		// ���� ����
		g_pGOBManager->GetGuildArchive()->SetGuildCommonInfo(&stGuildCommon) ;
		if( g_pResourceManager->GetGlobalString(27000059) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000059) );
		break ;
	case 2:		// ���� ����
		break ;
	case 3:		// ���� �ı�
		if( g_pResourceManager->GetGlobalString(27000077) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000077) );
		break ;
	case 4:		// ���� ����Ϸ�
		if( g_pResourceManager->GetGlobalString(27000014) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000014) );
		break ;
	default:
		wsprintf(szMsg, "[Guild] Guild Information Change[%d]", iMsgType);
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szMsg );
		break ;
	}
}

// ��û�ڿ��� ������ ���������� ���. �����ΰ��� ��û�ڿ��Ը� �۽�, �����ΰ��� ��û���ֺ��� ��ε�ĳ����(�����渶�� ���Ż�� �ֺ�����鿡�� �˸��� ����)
//GUILD_SC_CHANGEMASTER,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�(��û��)
// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
DEFINE_SC_PACKET_PROC(GUILD_SC_CHANGEMASTER)
{
	GU_ID				ObjectGUID;						// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;						// �������̵�

	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		SPPlayer* pPlayer = (SPPlayer*)g_pGOBManager->Find(ObjectGUID);
		if( pPlayer == NULL )	{
			return ;
		}
		//���峤������,�Լ��˳�����
		if ( g_pCIGWLoaderDx9 )
		{
			g_pCIGWLoaderDx9->OnCommunityEventA( ceQuitGuild, g_pGOBManager->GetGuildArchive()->GetGuildName() );
		}
		pPlayer->SPGOBPerformMessage(SPGM_SET_GUILD_INFO, (LPARAM)0);

		if( ObjectGUID == g_pGOBManager->GetLocalPlayer()->GetGUID() )
			g_pGOBManager->GetGuildArchive()->RemoveGuildInfo() ;
	}
	else			// ���и�
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
}

// ����ڿ��� ������ ���������� ���. �渶�������� ������ �ʿ��ϰԵǸ� ���⼭ ó���ؾ��մϴ�. ����� �������â���� �渶���޾׼��� �����־ �ʿ����.
//GUILD_SC_CHANGEMASTER_ME,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�(��������)
DEFINE_SC_PACKET_PROC(GUILD_SC_CHANGEMASTER_ME)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�

	packet->ExtractUINT64(&ObjectGUID);
	if( ObjectGUID == g_pGOBManager->GetLocalPlayer()->GetGUID() )
	{
		// ���� �޴� ����� â�� �ٽ� ���� Refresh
		g_pGOBManager->GetGuildArchive()->UpdateMyGrade(GUILD_GRADE_01) ;
	}
}

// ����ɱ� ���. �ֺ��� ��ε�ĳ��Ʈ�մϴ�.(��, ���濡���� ������ �׼��̰� ������ ��ü�� ��ε�ĳ��Ʈ�������� �����Ѵٰ� ��ӵ�.)
//GUILD_SC_PLANT,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
// UINT32			uiCropID;							// ������̵�
DEFINE_SC_PACKET_PROC(GUILD_SC_PLANT)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	UINT32				uiCropID;							// ������̵�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		packet->ExtractUINT32(&uiCropID);
		g_pGOBManager->GetGuildArchive()->SetCropInformation(CROP_SET_INITIALIZE, uiCropID) ;	// Set
		// Show Chat Message
		if( g_pResourceManager->GetGlobalString(27000013) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(27000013) );

	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
}

// ����̱� ���. �ֺ��� ��ε�ĳ��Ʈ�մϴ�.(��, ���濡���� ������ �׼��̰� ������ ��ü�� ��ε�ĳ��Ʈ�������� �����Ѵٰ� ��ӵ�.)
//GUILD_SC_GRUB,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
DEFINE_SC_PACKET_PROC(GUILD_SC_GRUB)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		g_pGOBManager->GetGuildArchive()->SetCropInformation(CROP_SET_CLEAR) ;		// Clear
		
		g_pEventManager->SetCutInState(CUT_IN_STATE_RELEASE);
	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
}

// ���/������ �ֱ� ���. �ֺ��� ��ε�ĳ��Ʈ�մϴ�.(��, ���濡���� ������ �׼��̰� ������ ��ü�� ��ε�ĳ��Ʈ�������� �����Ѵٰ� ��ӵ�.)
//GUILD_SC_NOURISH,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
// UINT32			uiRemainTime;						// ����ð��� ���Ͽ� ���� ����Ϸ���� �����ð�(�ʴ���)
// UINT32			uiNourishTime;						// ����ð��� ���Ͽ� ���� ��Ḧ ���� �ð�(�ʴ���)
// UINT32			uiHastenSumTime;					// ������ �����ð�
DEFINE_SC_PACKET_PROC(GUILD_SC_NOURISH)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	UINT32				uiRemainTime;						// ����ð��� ���Ͽ� ���� ����Ϸ���� �����ð�(�ʴ���)
	UINT32				uiNourishTime;						// ����ð��� ���Ͽ� ���� ��Ḧ ���� �ð�(�ʴ���)
	UINT32				uiHastenSumTime;					// ������ �����ð�
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		packet->ExtractUINT32(&uiRemainTime);
		packet->ExtractUINT32(&uiNourishTime);
		packet->ExtractUINT32(&uiHastenSumTime);
		g_pGOBManager->GetGuildArchive()->SetCropInformation(CROP_SET_NOURISH, 0, uiRemainTime, uiNourishTime, uiHastenSumTime) ;		// TimeUpdate
	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
}

// ������Ϸ�. ���泻�� ��� PC���� ��ε�ĳ��Ʈ�մϴ�.
//GUILD_SC_GROWTHCROP,
DEFINE_SC_PACKET_PROC(GUILD_SC_GROWTHCROP)
{
	// ���� ���� �Ϸ� ����ȭ
	g_pGOBManager->GetGuildArchive()->SetCropGrowthComplete() ;
}

// ��ũ��. �����ֺ��� ��ε�ĳ�������� �ʽ��ϴ�.(2007.08.13 dhpark ����������� ����)
//GUILD_SC_RANKUP,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
// INT32			iGNum;								// ���DBNum
// UINT8			byNewGRank;							// New��巩ũ
DEFINE_SC_PACKET_PROC(GUILD_SC_RANKUP)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	INT32				iGNum;								// ���DBNum
	UINT8				byNewGRank;							// New��巩ũ
	char				szMsg[256];
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		packet->ExtractUINT32((UINT32*)&iGNum);
		packet->ExtractUINT8(&byNewGRank);
		g_pGOBManager->GetGuildArchive()->UpdateGuildLevel((int)byNewGRank) ;
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_INFO, SPIM_GUILD_INFO_ENABLE, 0, 0, true);		// ��� �⺻���� Update (for Tooltip)
		if( g_pResourceManager->GetGlobalString(27000059) )	{

			wsprintf(szMsg, g_pResourceManager->GetGlobalString(27000059), byNewGRank);
			char szLineFeedBuf[MAX_STR_LENGTH+1];
			SPAbuseFilter::GetInstance()->ReplaceLineFeed( szMsg , szLineFeedBuf , MAX_STR_LENGTH );
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)szLineFeedBuf );
		}
	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
	}
}

// ��帶ũ����. �����ֺ��� ��ε�ĳ�������� �ʽ��ϴ�.(2007.08.13 dhpark ����������� ����)
//GUILD_SC_CHANGEMARK,
// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
// INT32			iGNum;								// ���DBNum
// UINT8			arrGMark[3];						// ��帶ũ
DEFINE_SC_PACKET_PROC(GUILD_SC_CHANGEMARK)
{
	GU_ID				ObjectGUID;							// ���ӿ�����Ʈ���̵�
	GLOBAL_STRING_ID	ErrorID;							// �������̵�
	INT32				iGNum;								// ���DBNum
	UINT8				arrGMark[3];						// ��帶ũ
	GUILD_BROADCAST		stGuildBroad ;
		
	packet->ExtractUINT64(&ObjectGUID);
	packet->ExtractUINT32(&ErrorID);
	if(0 == ErrorID) // �����̸�
	{
		packet->ExtractUINT32((UINT32*)&iGNum);
		packet->ExtractStruct(arrGMark, sizeof(UINT8)*3);
		g_pGOBManager->GetGuildArchive()->UpdateMyEmblem(arrGMark[0], arrGMark[1], arrGMark[2]) ;
	}
	else
	{
		if( g_pResourceManager->GetGlobalString(ErrorID) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(ErrorID) );
		g_pInterfaceManager->SPChildWndSendMessage(WIID_GUILD_EMBLEM, SPIM_GUILD_EM_CHANGE_RESULT, -1, 0);
	}
}
