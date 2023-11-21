
// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPRsManager.h
//	created:	2007/10/1   Time:11:55
//	purpose:	
//*********************************************************************/

#pragma once 

//#ifdef _INCLUDE_RSCLIENT_

#include <string>
#include "RSSDKdefine.h"

using namespace std;

#define DECLARE_RS_PROC(X)	void OnRS_##X(int iMsg, char* packet)
#define CASE_RS_PROC(X)		case X:{ g_pkRsManager->OnRS_##X(iMsg, packet);}break
#define DEFINE_RS_PROC(X)	void SPRsManager::OnRS_##X(int iMsg, char* packet)
#define ERROR_RS_PROC(X)	void SPRsManager::RETSZ_##X(int iMsg, char* packet)

//#ifndef SAFE_DELETE
//#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
//#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
//#endif

#define RS_DEF_SERVER_IP		"61.152.103.69"			// Test Server
#define RS_DEF_SERVER_PORT		"8025"					// Test Server
#define RS_DEF_GAMETYPE			39
#define RS_DEF_AREA				1
#define RS_DEF_USERID			"test"
#define RS_DEF_IDTYPE			"1"


enum HotQTopNV2_TYPE {
	TYPE_QNV2_MAIN		= 0,
	TYPE_QNV2_SUB		= 1,
	TYPE_QNV2_CONTEXT	= 2,
} ;



class SPRSPacketHandler;
class SPRsManager
{
public:
	static SPRsManager* GetInstance();
	static void Release();

	bool Init();
	void Clear();

	//---------------------------------------------------------------------
	// For Handler Param
	void SetNetParam		(const char* szRSIP, const char*szRSPort) ;		// RSSDK IP, PORT Setting
	void SetGameType		( int iGMType, int iArea );	
	//---------------------------------------------------------------------
	// For Local Param
	void SetlUserLogIdx		( const char* szlUserLogIdx );
	void SetAnsID			( const char* szAnsID );
	void SetIDType			( const char* szIDType );	
	void SetAccount			( const char* szAccount );
	void SetQuestion		( const char* szQuestion );
	
	void SetMainMenuToWindow() ;
	void SetSubMenuToWindow() ;
	//---------------------------------------------------------------------
	// RS Send Function
	int SendQMainMenu() ;
	int SendQSubMenu(const char* pAC) ;				// for MainMenu's Content lists (SubMenu)
	int SendQSubMenu(int iSelectIndex) ;
	int SendQHotTop10() ;
	int SendQSubMenuContents(const char* pAC) ;		// for SubMenu's Content lists
	int SendQSubMenuContents(int iSelectMain, int iSelectIndex) ;
	int SendQuestionText(const char* pText) ;
	int SendQuestionContext(const char* pText) ;
	int SendJudgeAnsYes() ;
	int SendGetUnsatReason() ;
	int SendJudgeUnsatReason(int iSelectIndex, const char* szReason = NULL) ;

	//---------------------------------------------------------------------
	// HotQTopNV2 Parsing
	void HotQTopNV2_MainMenu(char* packet) ;
	void HotQTopNV2_SubMenu(char* packet) ;
	void HotQTopNV2_Contents(char* packet) ;

	//---------------------------------------------------------------------
	bool HasMenu(int iSelectMain)				{	return (m_bHasMainMenu && m_bHasSubMenu[iSelectMain]) ;		}
	HotQTopNV2_TYPE GetHopQNV2Type()			{	return m_eHotQType;		}
	//---------------------------------------------------------------------
	void SetMainMenu(int iSelect)				{	m_iSelectMain = iSelect;	}
	int GetMainMenu()							{	return m_iSelectMain;		}
	const char* GetQuestionTitle()				{	return m_strSendQuest.c_str() ;	 }

protected:
	SPRsManager();
	virtual ~SPRsManager();

protected:
	static SPRsManager* m_pkInstance;

private:
	bool			m_bHasMainMenu ;
	bool			m_bHasSubMenu[5] ;
	HotQTopNV2_TYPE m_eHotQType ;
	RS_MENU*		m_pMainMenu ;
	RS_MENU*		m_pSubMenu ;
	int				m_iSelectMain ;
	// argument list
	string			m_strIDType;
	string			m_strAccount;
	string			m_strQuestion;
	string			m_strlUserLogIdx;
	string			m_strAnsID;
	string			m_strSendQuest ;		// ���� ����

	SPRSPacketHandler*  m_pkRSHandle;

public:
	DECLARE_RS_PROC( RETN_JUDGEANSWER_OK		);		//���ɹ�			//Send OK
	DECLARE_RS_PROC( RETN_JUDGEANSWER_SYSERR	);		//��ϵͳ����		// System Error
	DECLARE_RS_PROC( RETN_JUDGEANSWER_SYSREFUSE);		//��ϵͳ�ܾ�		// System Refused request
	DECLARE_RS_PROC( RETN_JUDGEANSWER_PARAMERR	);		//����������		// Parameter error
	DECLARE_RS_PROC( RETN_JUDGEANSWER_BUSY		);		//��ϵͳæ			// System busy
	DECLARE_RS_PROC( RETN_JUDGEANSWER_NOMATCH	);		//����ƥ������		// no match answer or question check failed

	DECLARE_RS_PROC( RETN_SENDQNEW_OK			);		//�������ݣ����ش�										// Return right content
	DECLARE_RS_PROC( RETN_SENDQNEW_SYSERR		);		//��ϵͳ����												// System Error
	DECLARE_RS_PROC( RETN_SENDQNEW_SYSREFUSE	);		//��ϵͳ�ܾ�												// System Refused request
	DECLARE_RS_PROC( RETN_SENDQNEW_PARAMERR		);		//����������												// Parameter error
	DECLARE_RS_PROC( RETN_SENDQNEW_BUSY			);		//��ϵͳæ�����ݣ����磺����"ϵͳæ����1���Ӻ����ԡ�."		// System busy
	DECLARE_RS_PROC( RETN_SENDQNEW_NOMATCH		);		//�������ݣ���ƥ��𰸻�������Ⱦ�����						// no match answer or question check failed

	DECLARE_RS_PROC( REASONSTAISFIED_OK			);		// UnSatisfyReason
	DECLARE_RS_PROC( REASONSTAISFIED_SYSERR		);
	DECLARE_RS_PROC( REASONSTAISFIED_SYSREFUSE	);
	DECLARE_RS_PROC( REASONSTAISFIED_PARAMERR	);
	DECLARE_RS_PROC( REASONSTAISFIED_BUSY		);

	//---------------------------------------------------------------------
	DECLARE_RS_PROC( RETSZ_HotQTopNV2_OK		);
	DECLARE_RS_PROC( RETSZ_HotQTopNV2_NOMATCH	);


#define HOTNODEQUESTION_OK					0x1C10		//�������ݣ����ش�
#define HOTNODEQUESTION_SYSERR				0x1C11		//��ϵͳ����
#define HOTNODEQUESTION_SYSREFUSE			0x1C12		//��ϵͳ�ܾ�
#define HOTNODEQUESTION_PARAMERR			0x1C13		//����������
#define HOTNODEQUESTION_TOOLONG				0x1C14		//������������ݰ�����"
#define HOTNODEQUESTION_NOMATCH				0x1C15		//����ѯ�޼�¼

};

//---------------------------------------------------------------------
// XML Parsing to 
void RsParsing(int iMsg, char* packet);
//---------------------------------------------------------------------

extern SPRsManager* g_pkRsManager;

//#endif