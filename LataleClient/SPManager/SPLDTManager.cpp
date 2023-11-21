// SPLDTManager.cpp

#ifdef _LATALE_CLIENT
	#include "SPCoreDef.h"
	#include "SPResourceBase.h"	
#elif _LATALE_SERVER
	#include <vector>
	#include <assert.h>
	#include <WTypes.h>	

	#include "SPResourceDEF.h"
	
	#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

	using namespace std;
#elif _LATALE_GMTOOL
	#include <assert.h>
	#include <WTypes.h>	
	#include "GlobalDefines.h"
	#include "SPResourceDEF.h"
#endif

#include "SPUtil.h"

#include "SPLDTFile.h"
#include "SPLDTManager.h"


using namespace std;
using namespace stdext;

SPLDTManager* SPLDTManager::m_pInstance = NULL;


SPLDTManager::SPLDTManager()
//: m_pResManager	(NULL)
{
#ifdef _LATALE_SERVER
	m_sResourceDir = RES_WORK_RESOURCE_PATH;
#endif
}

SPLDTManager::~SPLDTManager()
{
	hash_map<string, SPLDTFile*>::iterator Iter = m_hmLDTFileList.begin();
	for(; Iter != m_hmLDTFileList.end(); ++Iter) {
		SAFE_DELETE((*Iter).second);
	}
	m_hmLDTFileList.clear();
}



SPLDTManager* SPLDTManager::GetInstance()	
{
	return m_pInstance;
}

SPLDTManager* SPLDTManager::Create()
{
	if(m_pInstance == NULL) {
		m_pInstance = new SPLDTManager;			
	} 
	return m_pInstance;
}

void SPLDTManager::Release()
{
	if(m_pInstance != NULL) {
		SAFE_DELETE(m_pInstance);
	}
	m_pInstance = NULL;
}	








#ifdef _LATALE_SERVER
void SPLDTManager::SetResourceDir(std::string sDir)
{
	m_sResourceDir = sDir;
}

std::string	SPLDTManager::GetResourceDir()
{
	return m_sResourceDir;
}
#endif

bool SPLDTManager::LoadLDTFileFromFile(const char* szFileName, SPLDTFile** ppLDTFile)
{
	//string strFileName = GetUpperString(szFileName);
	string strFileName = szFileName;
	SPLDTFile* pLDTFileCreate = NULL;
	(*ppLDTFile) = NULL;

	hash_map<string, SPLDTFile*>::iterator Iter = m_hmLDTFileList.find(strFileName);
	if(Iter != m_hmLDTFileList.end() && (strFileName == (*Iter).first) ) {
		(*ppLDTFile) = (*Iter).second;
	} else {
		pLDTFileCreate = new SPLDTFile;
		bool bRet = pLDTFileCreate->LoadLDTFile(strFileName.c_str());
		if(bRet == false) {
			SAFE_DELETE(pLDTFileCreate);
			return false;
		}
		m_hmLDTFileList.insert ( hash_map<string, SPLDTFile*>::value_type ( strFileName, pLDTFileCreate) );
		(*ppLDTFile) = pLDTFileCreate;
	}

	if( *ppLDTFile )
		(*ppLDTFile)->IncreaseRef();

	return true;
}


bool SPLDTManager::UnloadLDTFile(const char* szFileName)
{
	//string strFileName = GetUpperString(szFileName);	
	string strFileName = szFileName;	
	hash_map<string, SPLDTFile*>::iterator Iter = m_hmLDTFileList.find(strFileName);

	if(Iter != m_hmLDTFileList.end())  {
		if( strFileName == (*Iter).first) {
			SPLDTFile* pLDTFile = (*Iter).second;
			if(pLDTFile->GetRefCount() == 0) {
				SAFE_DELETE(pLDTFile);
				m_hmLDTFileList.erase(Iter);
				return true;
			} 
		}
	}

	assert(0 && "�ӽ� ��ε�üũ, UNLOAD FAILED");
	return false;
}


/**
	���ϸ��� �̿��ؼ� szSrcFileName�� szDstFileName���� �����Ѵ�. (only LDT)
	(�ε��� �ٷ� �����ϴ� ��쿡�� ����ϰ� �ȴ�.)
	@param const char* szSrcFileName : �ε��� ���ϸ�
	@param const char* szDstFileName : ������ ���ϸ�
	@return bool : ���� ����
*/
bool SPLDTManager::SaveLDTFile(const char* szSrcFileName, const char* szDstFileName)
{
	SPLDTFile* pkLDTFile = NULL;

	if( LoadLDTFileFromFile(szSrcFileName, &pkLDTFile) ) {
		return pkLDTFile->SaveLDTFile(szDstFileName) ;
	}

	return false;
}


/**
	LDT������������ �ش� SPLDTFile Class�� �����Ѵ�. (only LDT)
	@param const SPLDTTile* pkLDTFile : LTD File Class
	@param const char* szDstFileName : ������ ���ϸ�
	@return bool : ���� ����
*/
bool SPLDTManager::SaveLDTFile(SPLDTFile* pkLDTFile , const char* szDstFileName)
{
	if( pkLDTFile )	{
		return pkLDTFile->SaveLDTFile(szDstFileName) ;
	}

	return false;
}

/**
	TXT ������������ �ش� SPLDTFile Class�� �����Ѵ�. (only LDT)
	@param const SPLDTTile* pkLDTFile : LTD File Class
	@param const char* szDstFileName : ������ ���ϸ�
	@return bool : ���� ����
*/
bool SPLDTManager::SaveLDTToTxt(SPLDTFile* pkLDTFile , const char* szDstFileName)
{
	if( pkLDTFile )	{
		return pkLDTFile->SaveToTXT(szDstFileName) ;
	}

	return false;
}

/**
	TXT ������������ �ش� SPLDTFile Class�� �����Ѵ�. (only LDT)
	@param const char* szSrcFileName : �ε��� ���ϸ�
	@param const char* szDstFileName : ������ ���ϸ�(TXT)
	@return bool : ���� ����
*/
bool SPLDTManager::SaveLDTToTxt(const char* szSrcLDTName, const char* szDstTxtName)
{
	SPLDTFile* pkLDTFile = NULL;

	if( LoadLDTFileFromFile(szSrcLDTName, &pkLDTFile) )	{
		return pkLDTFile->SaveToTXT(szDstTxtName) ;
	}

	return false;
}






