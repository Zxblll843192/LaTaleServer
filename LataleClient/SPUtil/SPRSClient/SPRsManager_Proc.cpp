// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPRsManager.cpp
//	created:	2007/10/1   Time:11:59
//	purpose:	
//*********************************************************************/

//#ifdef _INCLUDE_RSCLIENT_


#include "tinyxml.h"

#include "RSSDKdefine.h"
#include "SPRsManager.h"

#include "RSXMLTags.h"
#include "_Error_log.h"

//#include <stdio.h>

#ifdef _LATALE_CLIENT
	#include "SPCommon.h"
	#include "SPUtil.h"

	#include "SPMainGameDEF.H"
	#include "SPGameObjectDEF.h"

	#include "SPSubGameManager.h"
	#include "SPGameObject.h"
	#include "SPManager.h"
	#include "SPMouseCursor.h"
	#include "SPIMEPool.h"

	#include "SPResourceDef.h"
	#include "SPWindowDEF.h"
	#include "SPInterfaceManager.h"
	#include "SPResourceManager.h"
#endif




//---------------------------------------------------------------------
//���ɹ�			//Send OK
DEFINE_RS_PROC( RETN_JUDGEANSWER_OK		)
{
	ErrorFLogs->Error_Log("Judge Answer OKKKKK") ;
	g_pkRsManager->SendQHotTop10() ;
	return ;
}

//��ϵͳ����		// System Error
DEFINE_RS_PROC( RETN_JUDGEANSWER_SYSERR	)
{
	ErrorFLogs->Error_Log("#### Result ERROR RETN_JUDGEANSWER_SYSERR") ;
	return ;
}

//��ϵͳ�ܾ�		// System Refused request
DEFINE_RS_PROC( RETN_JUDGEANSWER_SYSREFUSE)
{		
	ErrorFLogs->Error_Log("#### Result ERROR RETN_JUDGEANSWER_SYSREFUSE") ;
	return ;
}

//����������		// Parameter error
DEFINE_RS_PROC( RETN_JUDGEANSWER_PARAMERR	)
{		
	ErrorFLogs->Error_Log("#### Result ERROR RETN_JUDGEANSWER_PARAMERR") ;
	return ;
}

//��ϵͳæ			// System busy
DEFINE_RS_PROC( RETN_JUDGEANSWER_BUSY		)
{		
	ErrorFLogs->Error_Log("#### Result ERROR RETN_JUDGEANSWER_BUSY") ;
	return ;
}

//����ƥ������		// no match answer or question check failed
DEFINE_RS_PROC( RETN_JUDGEANSWER_NOMATCH	)
{		
	ErrorFLogs->Error_Log("#### Result ERROR RETN_JUDGEANSWER_NOMATCH") ;
	return ;
}

//---------------------------------------------------------------------
//�������ݣ����ش�										// Return right content
DEFINE_RS_PROC( RETN_SENDQNEW_OK			)
{		
	ErrorFLogs->Error_Log("Receive RETN_SENDQNEW_OK") ;
	
	TiXmlDocument doc ;
	doc.Parse(packet);
	if ( doc.Error() )
	{
		ErrorFLogs->Error_Log("Tiny XML Parse Error.......") ;
		return ;
	}

	RS_ANSWER* pAnswer = new RS_ANSWER ;
	TiXmlNode* nodeRET = NULL ;
	TiXmlNode* nodeHOT = NULL ;
	TiXmlNode* node = NULL ;
	TiXmlElement* elem;
	TiXmlElement* Childelem;
	int count = 0 ;
	std::string strText ;
	char szQuestID[256] ;
	char szAnsId[256] ;
	char szQuestion[256] ;

	nodeRET = doc.FirstChild(XMLTAG_RETURN) ;					//<Return>
	elem = nodeRET->FirstChildElement(XMLTAG_OTHERANS) ;		//<Return>-<OtherAns>

	for( ; elem; elem = elem->NextSiblingElement(XMLTAG_OTHERANS))	// Next <OtherAns>
	{
		Childelem = elem->FirstChildElement();				//<Return>-<OtherAns>-<QuestID>
		strText = Childelem->GetText() ;
		::strcpy(szQuestID, Childelem->GetText());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<OtherAns>-<Question>
		strText = Childelem->GetText() ;
		::strcpy(pAnswer->szOtherAns[count], strText.c_str());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<OtherAns>-<Ansid>
		strText = Childelem->GetText() ;
		::strcpy(szAnsId, Childelem->GetText());

		ErrorFLogs->Error_Log("Load OtherAns[QID:%s] : %s [AID:%s]", szQuestID, pAnswer->szOtherAns[count], szAnsId) ;
		count++;
	}
	pAnswer->iOtherCount = count ;

	//<MasterAns> ����Ʈ ���.
	elem = nodeRET->FirstChildElement(XMLTAG_MASTERANS) ;		//<Return>-<MasterAns>
	Childelem = elem->FirstChildElement();				//<Return>-<MasterAns>-<QuestID>
	strText = Childelem->GetText() ;
	::strcpy(szQuestID, Childelem->GetText());

	Childelem = Childelem->NextSiblingElement();		//<Return>-<MasterAns>-<AnsDes>
	strText = Childelem->GetText() ;
	::strcpy(pAnswer->szMasterAns, strText.c_str());

	Childelem = Childelem->NextSiblingElement();		//<Return>-<MasterAns>-<UserLogIdx>
	strText = Childelem->GetText() ;
	::strcpy(pAnswer->szLogIdx, Childelem->GetText());

	Childelem = Childelem->NextSiblingElement();		//<Return>-<MasterAns>-<Question>
	strText = Childelem->GetText() ;
	::strcpy(szQuestion, Childelem->GetText());

	ErrorFLogs->Error_Log("Load MasterAns[AID:%s] : %s [LogIdx:%s][Ques:%s]", szAnsId, pAnswer->szMasterAns, pAnswer->szLogIdx, szQuestion) ;
	g_pInterfaceManager->SPChildWndSendMessage(WIID_RSCLIENT, SPIM_SDRS_RECV_ANSWER, 0, (LPARAM)pAnswer) ;

	SAFE_DELETE( pAnswer ) ;
	return ;
}


//��ϵͳ����												// System Error
DEFINE_RS_PROC( RETN_SENDQNEW_SYSERR		)
{		
	ErrorFLogs->Error_Log("#### Result ERROR RETN_SENDQNEW_SYSERR") ;
	return ;
}

//��ϵͳ�ܾ�												// System Refused request
DEFINE_RS_PROC( RETN_SENDQNEW_SYSREFUSE	)
{
	ErrorFLogs->Error_Log("#### Result ERROR RETN_SENDQNEW_SYSREFUSE") ;
	return ;
}

//����������												// Parameter error
DEFINE_RS_PROC( RETN_SENDQNEW_PARAMERR	)
{		
	ErrorFLogs->Error_Log("#### Result ERROR RETN_SENDQNEW_PARAMERR") ;
	return ;
}

//��ϵͳæ�����ݣ����磺����"ϵͳæ����1���Ӻ����ԡ�."		// System busy
DEFINE_RS_PROC( RETN_SENDQNEW_BUSY		)
{	
	ErrorFLogs->Error_Log("#### Result ERROR RETN_SENDQNEW_BUSY") ;
	return ;
}

//�������ݣ���ƥ��𰸻�������Ⱦ�����						// no match answer or question check failed
DEFINE_RS_PROC( RETN_SENDQNEW_NOMATCH		)
{		
	ErrorFLogs->Error_Log("#### Result ERROR RETN_SENDQNEW_NOMATCH") ;
	return ;
}

//---------------------------------------------------------------------
//�������ݣ����ش�										// Return right content
DEFINE_RS_PROC( RETSZ_HotQTopNV2_OK			)
{		
	ErrorFLogs->Error_Log("Receive RETSZ_HotQTopNV2_OK") ;
	if( g_pkRsManager )
	{
		if( GetHopQNV2Type() == TYPE_QNV2_MAIN )
			HotQTopNV2_MainMenu(packet);		// Receive Main Menu
		else if( GetHopQNV2Type() == TYPE_QNV2_SUB )
			HotQTopNV2_SubMenu(packet);			// Receive Sub Menu
		else if( GetHopQNV2Type() == TYPE_QNV2_CONTEXT )
			HotQTopNV2_Contents(packet) ;		// Receive Sub Menu contents
	}
	return ;
}

//��ϵͳ����												// System Error
DEFINE_RS_PROC( RETSZ_HotQTopNV2_NOMATCH		)
{
	ErrorFLogs->Error_Log("HotQTopNV2_NOMATCH !!!") ;
	return ;
}



//---------------------------------------------------------------------
// Receive Main Menu
void SPRsManager::HotQTopNV2_MainMenu(char* packet)
{		
	ErrorFLogs->Error_Log("Receive HotQTopNV2_MainMenu OK") ;

	TiXmlDocument doc ;
	doc.Parse(packet);
	if ( doc.Error() )
	{
		ErrorFLogs->Error_Log("Tiny XML Parse Error.......") ;
		return ;
	}

	m_pMainMenu->Init() ;

	TiXmlNode* nodeRET = NULL ;
	TiXmlNode* nodeHOT = NULL ;
	TiXmlNode* node = NULL ;
	TiXmlElement* elem;
	TiXmlElement* Childelem;
	char szSNF[256] ;
	std::string strText ;
	int count = 0 ;

	// First MainMenu is HOTTOP10
	if( g_pResourceManager->GetGlobalString(5008001))
		::strcpy(m_pMainMenu->szText[0], g_pResourceManager->GetGlobalString(5008001));
	else
		::strcpy(m_pMainMenu->szText[0], "HotTop10");

	nodeRET = doc.FirstChild(XMLTAG_RETURN) ;					//<Return>
	elem = nodeRET->FirstChildElement(XMLTAG_HOTQUESNODE) ;		//<Return>-<HQN>

	for( ; elem; elem = elem->NextSiblingElement(XMLTAG_HOTQUESNODE))	// Next <HQN>
	{
		Childelem = elem->FirstChildElement();				//<Return>-<HQN>-<SNF>
		strText = Childelem->GetText() ;
		::strcpy(szSNF, strText.c_str());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<HQN>-<AC>
		strText = Childelem->GetText() ;
		::strcpy(m_pMainMenu->szAC[count+1], strText.c_str());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<HQN>-<NN>
		strText = Childelem->GetText() ;
		::strcpy(m_pMainMenu->szText[count+1], strText.c_str());

		ErrorFLogs->Error_Log("Load MainMenu[%d][SNF:%s, AC:%s] : %s", count, szSNF, m_pMainMenu->szAC[count+1], m_pMainMenu->szText[count+1]) ;
		count++;
	}
	m_pMainMenu->iCount = count + 1 ;
	m_bHasMainMenu = true ;
	SetMainMenuToWindow() ;
	return ;
}


//---------------------------------------------------------------------
// Receive Sub Menu
void SPRsManager::HotQTopNV2_SubMenu(char* packet)
{		
	ErrorFLogs->Error_Log("Receive HotQTopNV2_SubMenu") ;

	TiXmlDocument doc ;
	doc.Parse(packet);
	if ( doc.Error() )
	{
		ErrorFLogs->Error_Log("Tiny XML Parse Error.......") ;
		return ;
	}

	int iSelectMain = m_iSelectMain ;		// Selected main Menu
	TiXmlNode* nodeRET = NULL ;
	TiXmlNode* nodeHOT = NULL ;
	TiXmlNode* node = NULL ;
	TiXmlElement* elem;
	TiXmlElement* Childelem;
	char szSNF[256] ;
	std::string strText ;
	int count = 0 ;

	nodeRET = doc.FirstChild(XMLTAG_RETURN) ;					//<Return>
	elem = nodeRET->FirstChildElement(XMLTAG_HOTQUESNODE) ;		//<Return>-<HQN>

	for( ; elem; elem = elem->NextSiblingElement(XMLTAG_HOTQUESNODE))	// Next <HQN>
	{
		Childelem = elem->FirstChildElement();				//<Return>-<HQN>-<SNF>
		strText = Childelem->GetText() ;
		::strcpy(szSNF, strText.c_str());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<HQN>-<AC>
		strText = Childelem->GetText() ;
		::strcpy(m_pSubMenu[iSelectMain].szAC[count], strText.c_str());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<HQN>-<NN>
		strText = Childelem->GetText() ;
		::strcpy(m_pSubMenu[iSelectMain].szText[count], strText.c_str());

		ErrorFLogs->Error_Log("Load SubMenu[%d][SNF:%s, AC:%s] : %s", count, szSNF, m_pSubMenu[iSelectMain].szAC[count], m_pSubMenu[iSelectMain].szText[count]) ;
		count++;
	}
	m_pSubMenu[iSelectMain].iCount = count ;
	m_bHasSubMenu[iSelectMain] = true ;
	SetSubMenuToWindow() ;
	return ;
}

//---------------------------------------------------------------------
// Receive Contents
void SPRsManager::HotQTopNV2_Contents(char* packet)
{		
	ErrorFLogs->Error_Log("Receive RETSZ_HotQTopNV2_OK") ;

	TiXmlDocument doc ;
	doc.Parse(packet);
	if ( doc.Error() )
	{
		ErrorFLogs->Error_Log("Tiny XML Parse Error.......") ;
		return ;
	}

	RS_CONTENTS* pCoutents = new RS_CONTENTS ;
	TiXmlNode* nodeRET = NULL ;
	TiXmlNode* nodeHOT = NULL ;
	TiXmlElement* elem;
	TiXmlElement* Childelem;
	char szIndex[256] ;
	std::string strText ;
	int count = 0 ;

	nodeRET = doc.FirstChild(XMLTAG_RETURN) ;					//<Return>
	elem = nodeRET->FirstChildElement(XMLTAG_HOTQUESTION) ;		//<Return>-<HotQuestion>

	for( ; elem; elem = elem->NextSiblingElement(XMLTAG_HOTQUESTION))	// Next <HotQuestion>
	{
		Childelem = elem->FirstChildElement();				//<Return>-<HotQuestion>-<Content>
		strText = Childelem->GetText() ;
		::strcpy(pCoutents->szText[count], strText.c_str());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<HotQuestion>-<Index>
		strText = Childelem->GetText() ;
		::strcpy(szIndex, strText.c_str());

		ErrorFLogs->Error_Log("Load HotTOP[%s] : %s", szIndex, pCoutents->szText[count]) ;
		count++;
	}
	pCoutents->iCount = count ;
	g_pInterfaceManager->SPChildWndSendMessage(WIID_RSCLIENT, SPIM_SDRS_RECV_TOPTOPIC, 0, (LPARAM)pCoutents) ;
	SAFE_DELETE( pCoutents ) ;
	return ;
}




//---------------------------------------------------------------------
// Receive Contents
DEFINE_RS_PROC( REASONSTAISFIED_OK		)
{		
	ErrorFLogs->Error_Log("Receive REASONSTAISFIED_OK") ;
	TiXmlDocument doc ;
	doc.Parse(packet);
	if ( doc.Error() )
	{
		ErrorFLogs->Error_Log("Tiny XML Parse Error.......") ;
		return ;
	}

	RS_CONTENTS* pCoutents = new RS_CONTENTS ;
	TiXmlNode* nodeRET = NULL ;
	TiXmlNode* nodeHOT = NULL ;
	TiXmlElement* elem;
	TiXmlElement* Childelem;
	char szIndex[256] ;
	std::string strText ;
	int count = 0 ;

	nodeRET = doc.FirstChild(XMLTAG_RETURN) ;					//<Return>
	elem = nodeRET->FirstChildElement(XMLTAG_UNSATISFIEDREASON) ;		//<Return>-<UnsatisfiedReason>

	for( ; elem; elem = elem->NextSiblingElement(XMLTAG_UNSATISFIEDREASON))	// Next <UnsatisfiedReason>
	{
		Childelem = elem->FirstChildElement();				//<Return>-<UnsatisfiedReason>-<Content>
		strText = Childelem->GetText() ;
		::strcpy(pCoutents->szText[count], strText.c_str());

		Childelem = Childelem->NextSiblingElement();		//<Return>-<UnsatisfiedReason>-<Index>
		strText = Childelem->GetText() ;
		::strcpy(szIndex, strText.c_str());

		ErrorFLogs->Error_Log("Load HotTOP[%s] : %s", szIndex, pCoutents->szText[count]) ;
		count++;
	}
	pCoutents->iCount = count ;
	g_pInterfaceManager->SPChildWndSendMessage(WIID_RSCLIENT, SPIM_SDRS_RECV_UNSATREASON, 0, (LPARAM)pCoutents) ;
	SAFE_DELETE( pCoutents ) ;
	return ;
}

//��ϵͳ����												// System Error
DEFINE_RS_PROC( REASONSTAISFIED_SYSERR		)
{		
	ErrorFLogs->Error_Log("#### Result ERROR REASONSTAISFIED_SYSERR") ;
	return ;
}

//��ϵͳ�ܾ�												// System Refused request
DEFINE_RS_PROC( REASONSTAISFIED_SYSREFUSE	)
{
	ErrorFLogs->Error_Log("#### Result ERROR REASONSTAISFIED_SYSREFUSE") ;
	return ;
}

//����������												// Parameter error
DEFINE_RS_PROC( REASONSTAISFIED_PARAMERR	)
{		
	ErrorFLogs->Error_Log("#### Result ERROR REASONSTAISFIED_PARAMERR") ;
	return ;
}

//��ϵͳæ�����ݣ����磺����"ϵͳæ����1���Ӻ����ԡ�."		// System busy
DEFINE_RS_PROC( REASONSTAISFIED_BUSY		)
{
	ErrorFLogs->Error_Log("#### Result ERROR REASONSTAISFIED_BUSY") ;
	return ;
}


//#endif