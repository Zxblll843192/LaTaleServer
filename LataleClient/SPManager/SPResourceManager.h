// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPResourceManager
// Comment     : LDT Data Storage, ItemCluster
// Creation    : metalgeni 2004-08-23 ���� 2:56:36
//***************************************************************************

#pragma once 

// .NET2003 ���� �ؽø� ��붧����.. 
#ifdef _DEFINE_DEPRECATED_HASH_CLASSES
#undef _DEFINE_DEPRECATED_HASH_CLASSES
#define _DEFINE_DEPRECATED_HASH_CLASSES 0	
#endif

#include <hash_map>

class SPItemCluster;
class SPLDTFile;
class SPLDTManager;
class SPResourceBase;

class SPResourceManager : public SPManager {
public:
	SPResourceManager();
	virtual ~SPResourceManager();
	virtual bool	Init();
	virtual void	Clean();

	bool	InitItemCluster();
	bool	GetLDTFromFileName	(const char* szFileName, SPLDTFile** ppLDTFile);	
	bool	GetLDTFromInx		(int iDbName, SPLDTFile** ppLDTFile);

	const char* GetGlobalFileName(int iItemID);
	const char* GetGlobalString(int iItemID);

	/**
	 * LDT���� Chat Color�� �����´� <br> 
	 @param  int iItemID
	 @return const D3DXCOLOR
	*/
	const D3DXCOLOR GetGlobalColor(int iItemID);

protected:

	bool	UnloadLDT			(const char* szFileName);

protected:

	SPItemCluster*		m_pItemCluster;
	SPLDTManager*		m_pLDTManager;

	SPLDTFile*			m_pLDTDataTable;
	SPLDTFile*			m_pLDTGlobalRes;
	SPLDTFile*			m_pLDTGlobalString;

	SPLDTFile*			m_pLDTGlobalColor;		/**< Chat Color�� <br> */
	TCHAR				m_szError[256] ;

	//SPResourceBase*		m_pResourceBase;

};


extern SPResourceManager* g_pResourceManager;



