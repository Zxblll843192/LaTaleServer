// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : LataleServerTest�� ���� �Ƚ�Ŵ..... AJJIYA
// Creation    : AJJIYA 2005-11-15    14:38 
//***************************************************************************

#include <Windows.h>

#ifdef _USED_GAME_GUARD
	#define _USING_NPROTECT		1

	#pragma comment( lib , "./NPGameGuard/NPGameLib" )
	
	#pragma comment( lib , "./XTrapLib/XTrap4Client_mt" )
	#pragma comment( lib , "./XTrapLib/XTrap4Client_ClientPart_mt" )
	#pragma comment( lib , "./XTrapLib/XTrap4Client_ServerPart_mt" )
	#pragma comment( lib , "./XTrapLib/XTrap_Unipher_mt" )
	#pragma comment( lib , "./XTrapLib/XTrap4Launcher_mt" )

	#pragma comment( lib , "./CrackProof/HtGEPD" )
	#pragma comment( lib , "./CrackProof/HtGECACln" )
#endif

#include "SPCommon.h"

#include "PacketID.h"
#include "SPNetworkDEF.h"
#include "SPNetworkManager.h"

#include "Packet.h"
#include "PacketHandler.h"

#include "./NPGameGuard/SDCltDynCode.h"		// SNDC Update [5/15/2007 AJJIYA]

#include "./XTrapLib/XTrap4Client.h"
#include "./XTrapLib/XTrap4Launcher.h"

#include "./CrackProof/Service.h"
#include "./CrackProof/HtGEPD.h"

#include "SPGameGuard.h"

static void WINAPI CPFCallBackFunc()
{
	LPCSTR	lpszMsg;
	BOOL	bAppExit = TRUE;

	//	���� �����Ͽ��� ������ �ʴ� ���α׷��� �߰ߵǾ����ϴ�.
	lpszMsg	=	"LaTale will be shot off for (using) unacceptable program.\r\nPlease check programs (running) on your PC\r\n";

	if (lpszMsg)
	{
		MessageBox( g_hWnd , lpszMsg , "CrackProof", MB_OK ); // �Ǵ� ���� UI ���
	}

	// ���� ����ÿ��� false�� ����
	if ( bAppExit == TRUE )
		SendMessage( g_hWnd , WM_CLOSE , bAppExit , 1 );

	::ExitProcess(0);
}

SPGameGuard::SPGameGuard()
{
	m_pNPGameLib	=	NULL;

#ifdef _USED_GAME_GUARD
	switch( g_eCountryLocale )
	{
	case CL_KOREA:
		m_pNPGameLib	=	new	CNPGameLib( "LaTale" );
		break;
	case CL_JAPAN:
		m_pNPGameLib	=	new	CNPGameLib( "LaTaleJP" );
		HtGEPDSetCallback( CPFCallBackFunc );
	    break;
	case CL_CHINA:
		SGDP::SDDynCodeCheckUpdate( "http://autopatch.chd.sdo.com/latale/latale/LaTale-MainServer" , SDUPDATE_SYNC );
		break;
	case CL_USA:
		if( g_bGameGuardPatch == true )
			XTrap_L_Patch( X_TRAP_ARG , NULL , 60 );

		XTrap_C_Start( X_TRAP_ARG , NULL );
		break;
	}
#endif
}

SPGameGuard::~SPGameGuard()
{
#ifdef _USED_GAME_GUARD
	delete m_pNPGameLib;

	if( Service::DriverIsRun( CPF_DRIVE_NAME ) == TRUE )
		Service::DriverUnload( CPF_DRIVE_NAME );
#endif
}

//////////////////////////////////////////////////////////////////////////
//
//	�̱��� �������̽�
//

SPGameGuard* SPGameGuard::m_pGameGuardInstance	=	NULL;

SPGameGuard* SPGameGuard::GetInstance()
{
	if( m_pGameGuardInstance	==	NULL )
		m_pGameGuardInstance	=	new	SPGameGuard;

	return	m_pGameGuardInstance;
}

void SPGameGuard::DelInstance()
{
	delete m_pGameGuardInstance;
}

BOOL SPGameGuard::Init()
{
	if( m_pNPGameLib == NULL )
		return TRUE;

#ifdef _USED_GAME_GUARD
	DWORD	dwResult	=	m_pNPGameLib->Init();

	if( dwResult != NPGAMEMON_SUCCESS )
	{
		TCHAR	msg[256];
		LPCSTR	lpszMsg;

		DWORD	dwLocale	=	PRIMARYLANGID( ::GetUserDefaultLangID() );

		if( dwLocale == LANG_JAPANESE )
		{
#include "SPGameGuard-Init-Japan.cpp"
		}
		else
		{
			// ��6. �ֿ信���ڵ塯�� �����Ͽ� ��Ȳ�� �´� �޽����� ������ݴϴ�.
			switch (dwResult)
			{
			case NPGAMEMON_ERROR_EXIST:
				lpszMsg = "���Ӱ��尡 ���� �� �Դϴ�. ��� �ĳ� ����� �Ŀ� �ٽ� �����غ��ñ� �ٶ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_GAME_EXIST:
				lpszMsg = "������ �ߺ� ����Ǿ��ų� ���Ӱ��尡 �̹� ���� �� �Դϴ�. ���� ���� �� �ٽ� �����غ��ñ� �ٶ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_INIT:
				lpszMsg = "���Ӱ��� �ʱ�ȭ �����Դϴ�. ����� �� �ٽ� �����غ��ų� �浹�� �� �ִ� �ٸ� ���α׷����� ������ �� ������ ���ñ� �ٶ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_AUTH_GAMEGUARD:
			case NPGAMEMON_ERROR_NFOUND_GG:
			case NPGAMEMON_ERROR_AUTH_INI:
			case NPGAMEMON_ERROR_NFOUND_INI:
				lpszMsg = "���Ӱ��� ������ ���ų� �����Ǿ����ϴ�. ���Ӱ��� �¾� ������ ��ġ�غ��ñ� �ٶ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_CRYPTOAPI:
				lpszMsg = "�������� �Ϻ� �ý��� ������ �ջ�Ǿ����ϴ�. ���ͳ� �ͽ��÷η�(IE)�� �ٽ� ��ġ�غ��ñ� �ٶ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_EXECUTE:
				lpszMsg = "���Ӱ��� ���࿡ �����߽��ϴ�. ���Ӱ��� �¾� ������ �ٽ� ��ġ�غ��ñ� �ٶ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_ILLEGAL_PRG:
				lpszMsg = "�ҹ� ���α׷��� �߰ߵǾ����ϴ�. ���ʿ��� ���α׷��� ������ �� �ٽ� �����غ��ñ� �ٶ��ϴ�.";
				break;
			case NPGMUP_ERROR_ABORT:
				lpszMsg = "���Ӱ��� ������Ʈ�� ����ϼ̽��ϴ�. ������ ��� ���� ���� ��� ���ͳ� �� ���� ��ȭ�� ������ ������ ���ñ� �ٶ��ϴ�.";
				break;
			case NPGMUP_ERROR_CONNECT:
			case HOOK_TIMEOUT:
				lpszMsg = "���̷����� �����̿���� ���� ��ŷ�� �����Ͽ����ϴ�. �ֽŹ���� ������ �� ��ǻ�� ��ü�˻縦 �غ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_GAMEGUARD:
				lpszMsg = "���Ӱ��� �ʱ�ȭ ���� �Ǵ� �������� ���Ӱ��� �����Դϴ�. ���Ӱ��� �¾������� �ٽ� ��ġ�ϰ� ������ �����غ��ϴ�.";
				break;
			case NPGMUP_ERROR_PARAM:
				lpszMsg = "ini ������ ���ų� �����Ǿ����ϴ�. ���Ӱ��� �¾� ������ ��ġ�ϸ� �ذ��� �� �ֽ��ϴ�.";
				break;
			case NPGMUP_ERROR_INIT:
				lpszMsg = "npgmup.des �ʱ�ȭ �����Դϴ�. ���Ӱ��������� ������ �ٽ� ���ӽ����� �غ��ϴ�.";
				break;
			//case ???:
			//	lpszMsg = "�������� ���� Windows XP x64 ������ ������ ����Դϴ�. �ֽ����� �������� ��ġ�� ���ӽ����� �غ��ϴ�.";
			//	break;
			case NPGMUP_ERROR_DOWNCFG:
				lpszMsg = "���Ӱ��� ������Ʈ ���� ���ӿ� �����Ͽ����ϴ�. ��� �� ��õ� �غ��ų�, ���� ��ȭ���� �ִٸ� ������ ������ ���ñ� �ٶ��ϴ�.";
				break;
			case NPGMUP_ERROR_AUTH:
				lpszMsg = "���Ӱ��� ������Ʈ�� �Ϸ����� �� �߽��ϴ�. ���̷��� ����� �Ͻ� �߽� ��Ų �� ��õ� �غ��ðų�, PC ���� ���α׷��� ����Ͻø� ������ ������ ���ñ� �ٶ��ϴ�.";
				break;
			case NPGAMEMON_ERROR_NPSCAN:
				lpszMsg = "���̷��� �� ��ŷ�� �˻� ��� �ε��� ���� �߽��ϴ�. �޸� �����̰ų� ���̷����� ���� ������ �� �ֽ��ϴ�.";
				break;
			default:
				// ������ ���� �޽��� ���
				lpszMsg = "���Ӱ��� ���� �� ������ �߻��Ͽ����ϴ�. ���� ���� ���� GameGuard ������ �ִ� *.erl ���ϵ��� Game1@inca.co.kr�� ÷���Ͽ� ���� �����ֽñ� �ٶ��ϴ�.";
				break;
			}
			wsprintf( msg, "���Ӱ��� ���� : %lu" , dwResult );
		}

		MessageBox( NULL , lpszMsg , msg , MB_OK );

		return FALSE;
	}

#endif

	return TRUE;
}

void SPGameGuard::AfterCreateWindow()
{
	switch( g_eCountryLocale )
	{
		case CL_USA:
#ifdef _USED_GAME_GUARD
			XTrap_C_KeepAlive();
#endif
			break;
	}
}

void SPGameGuard::SetHwnd( HWND hWnd )
{
	if( m_pNPGameLib == NULL )
		return;

#ifdef _USED_GAME_GUARD
	m_pNPGameLib->SetHwnd( hWnd );
#endif
}

void SPGameGuard::SetUserID( const char* szUserID )
{
	if( m_pNPGameLib == NULL )
		return;

#ifdef _USED_GAME_GUARD
	m_pNPGameLib->Send( szUserID );
#endif
}

//void SPGameGuard::SetAuth( GG_AUTH_DATA& stAuthData )
//{
//	if( m_pNPGameLib == NULL )
//		return;
//
//#ifdef _USED_GAME_GUARD
//	m_pNPGameLib->Auth2( &stAuthData );
//#endif
//}

// 2008.05.26 dhpark ������ ����
void SPGameGuard::Auth(SECURITY_PACKDATA* pPackData)
{
#ifdef _USED_GAME_GUARD
	BOOL bResult = 0;
	DWORD dwError = 0;
	SECURITY_PACKDATA stOutPackData = {0,};

	switch(g_eCountryLocale)
	{
	case CL_KOREA:
		if(m_pNPGameLib == NULL)
			return;
		dwError = m_pNPGameLib->Auth2(&pPackData->stAuthData);
		// *** �̰� : dwErroró��. ����� �������� �����Ͽ� ��������ó����.
		// NPGameMonCallback()�Լ����� ��� �۽�
		break;
	case CL_JAPAN:
		memcpy(&stOutPackData, pPackData, sizeof(SECURITY_PACKDATA));
		bResult = HtGECAAuthorize((PHtGECAData)stOutPackData.arrCPFData, (PHtGECAData)pPackData->arrCPFData);
		// *** �̰� : bResultó��. ����� �������� �����Ͽ� ��������ó����.
		// �ٷ� �۽�
		{
			CPacket packet(SECURITY_CS_CHECK);
			packet.AddData(&stOutPackData, sizeof(SECURITY_PACKDATA));
			if(g_pNetworkManager != NULL)
				g_pNetworkManager->GetPacketHandler()->PostMsg(&packet);
		}
		break;
	case CL_USA:
		memcpy(&stOutPackData, pPackData, sizeof(SECURITY_PACKDATA));
		dwError = XTrap_CS_Step2((LPCVOID)pPackData->arrBufPackData, (LPVOID)stOutPackData.arrBufPackData, XTRAP_PROTECT_PE | XTRAP_PROTECT_TEXT | XTRAP_PROTECT_EXCEPT_VIRUS);
		// *** �̰� : dwErroró��. ����� �������� �����Ͽ� ��������ó����.
		// �ٷ� �۽�
		{
			CPacket packet(SECURITY_CS_CHECK);
			packet.AddData(&stOutPackData, sizeof(SECURITY_PACKDATA));
			if(g_pNetworkManager != NULL)
				g_pNetworkManager->GetPacketHandler()->PostMsg(&packet);
		}
		break;
	default:
		break;
	}
#endif
}

LPCSTR SPGameGuard::GetInfo()
{
	LPCSTR	lpszMsg	=	NULL;

	if( m_pNPGameLib == NULL )
		return lpszMsg;

#ifdef _USED_GAME_GUARD
	lpszMsg	=	m_pNPGameLib->GetInfo();
#endif

	return lpszMsg;
}

//////////////////////////////////////////////////////////////////////////
//
//	���� ���� �ݹ� �Լ�
//

BOOL CALLBACK NPGameMonCallback( DWORD dwMsg , DWORD dwArg )
{
	TCHAR msg[128];
	LPCTSTR lpszMsg = NULL;
	BOOL bAppExit;

#ifdef _USED_GAME_GUARD
	// AJJIYA [1/18/2006 AJJIYA]
	// Auth2 ȣ���� ��� �޼���
	// 2008.05.26 dhpark ������ ����
	if(dwMsg == NPGAMEMON_CHECK_CSAUTH2)
	{
		GG_AUTH_DATA stAuthData = {0,};
		memcpy(&stAuthData, (PVOID)dwArg, sizeof(GG_AUTH_DATA));
		
		SECURITY_PACKDATA stOutPackData = {0,};
		memcpy(&stOutPackData.stAuthData, &stAuthData, sizeof(GG_AUTH_DATA));

		CPacket packet(SECURITY_CS_CHECK);
		packet.AddData(&stOutPackData, sizeof(SECURITY_PACKDATA));
		if(g_pNetworkManager != NULL)
			g_pNetworkManager->GetPacketHandler()->PostMsg(&packet);

		return TRUE;
	}
#endif

	if( g_eCountryLocale == CL_JAPAN )
	{
#include "SPGameGuard-CallBack-Japan.cpp"
	}
	else
	{
		switch (dwMsg)
		{
		case NPGAMEMON_COMM_ERROR:
		case NPGAMEMON_COMM_CLOSE:
			bAppExit = TRUE; // ���� �ڵ�
			return FALSE;
		case NPGAMEMON_INIT_ERROR:
			wsprintf( msg , "���Ӱ��� �ʱ�ȭ ���� : %lu", dwArg);
			bAppExit = TRUE; // ���� �ڵ�
			lpszMsg = msg;
			break;
		case NPGAMEMON_SPEEDHACK:
			wsprintf( msg , "���ǵ����� �����Ǿ����ϴ�.");
			bAppExit = TRUE; // ���� �ڵ�
			lpszMsg = msg;
			break;
		case NPGAMEMON_GAMEHACK_KILLED:
			wsprintf( msg , "�������� �߰ߵǾ����ϴ�.\r\n%s", SPGameGuard::GetInstance()->GetInfo() );
			bAppExit = TRUE; // ���� �ڵ�
			lpszMsg = msg;
			break;
		case NPGAMEMON_GAMEHACK_DETECT:
			wsprintf( msg , "�������� �߰ߵǾ����ϴ�.\r\n%s", SPGameGuard::GetInstance()->GetInfo() );
			bAppExit = TRUE; // ���� �ڵ�
			lpszMsg = msg;
			break;
		case NPGAMEMON_GAMEHACK_DOUBT:
			wsprintf( msg , "�����̳� ���Ӱ��尡 �����Ǿ����ϴ�.");
			bAppExit = TRUE; // ���� �ڵ�
			lpszMsg = msg;
			break;
		default:
			// ������ ���� �޽��� ���
			lpszMsg = "���Ӱ��� ���� �� ������ �߻��Ͽ����ϴ�. ���� ���� ���� GameGuard ������ �ִ� *.erl ���ϵ��� Game1@inca.co.kr�� ÷���Ͽ� ���� �����ֽñ� �ٶ��ϴ�.";
			bAppExit = TRUE;
			break;
		}
	}

	if (lpszMsg)
	{
		MessageBox( g_hWnd , lpszMsg , "nProtect GameGuard", MB_OK ); // �Ǵ� ���� UI ���
	}

	// ���� ����ÿ��� false�� ����
	if ( bAppExit == TRUE )
	{
		SendMessage( g_hWnd , WM_CLOSE , bAppExit , 1 );
		return false;
	}

	return TRUE;
}
