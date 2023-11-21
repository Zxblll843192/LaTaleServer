// SPLDTFile.cpp

#include <io.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <hash_map>
#include <assert.h>
#include <iostream>
#include <fstream>

#ifdef _LATALE_CLIENT
	#include "SPCommon.h"
#elif _LATALE_SERVER
	#include <stdio.h>
	#include <tchar.h>
	#include <WTypes.h>	
	#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
	#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[] (p);	(p)=NULL; } }
#elif _LATALE_GMTOOL
	#include <WTypes.h>	
	#include "GlobalDefines.h"
	#include "SPResourceBaseDEF.h"
	#include "SPResourceBase.h"
#endif

#include "SPUtil.h"
#include "SPResourceDEF.h"

#include "SPStream.h"

#include "SPLDTManager.h"
#include "SPLDTFile.h"

SPLDTFile::SPLDTFile()
: m_iRefCount(0)
, m_bIsLoad(false)
{
	Clean();
}

SPLDTFile::~SPLDTFile()
{
	Clean();
}

int	SPLDTFile::GetRefCount()
{
	return m_iRefCount;
}

void SPLDTFile::Release()
{
	assert(m_iRefCount > 0);

	if(--m_iRefCount <= 0) {
		if(SPLDTManager::GetInstance()) {
			SPLDTManager::GetInstance()->UnloadLDTFile( m_strFileName.c_str() )	;
		} else {
			assert(0 && "ERROR : SPLDTManager not created");
		}
	}
}

void SPLDTFile::IncreaseRef()
{
	++m_iRefCount;
}



void SPLDTFile::Clean()
{
	unsigned long i;

	for (i=0; i<m_LDTLinearDB.size() ; i++)	{
		switch(m_LDTLinearDB[i].nFldTyp) {
		case fldString:	
		case fldAlias:
			SAFE_DELETE_ARRAY( m_LDTLinearDB[i].uData.pValue );
			break;
		case fldNum64:
			SAFE_DELETE(m_LDTLinearDB[i].uData.pValue64);
			break;
		}
	}
	m_bIsLoad = false ;
	m_LDTLinearDB.clear();
	m_LDTprimaryidx.clear();
	m_Label.clear();
	m_hmLabel.clear();

	m_lDB_ID = (-1);
	m_nFieldCount = 0;
	m_nDataCount = 0;
	m_strFileName.clear();
}


bool SPLDTFile::LoadLDTFile( LPCSTR pszLDTFile)
{
	if (pszLDTFile == NULL) return false;	
	SPStream* pStream;	

#ifdef _LATALE_SERVER
	pStream = new SPFileStream(GetAddResPath( pszLDTFile, SPLDTManager::GetInstance()->GetResourceDir().c_str()));
#elif _LATALE_GMTOOL
	if(g_bUsePackFile)
	{
		SPResourceBase::GetInstance()->GetStreamData(pszLDTFile, &pStream);
	}
	else
	{
		// GMTOOL�� Pack�� ����մϴ�.
		pStream = NULL;
	}
#else
	if(g_bUsePackFile) {
		SPResourceBase::GetInstance()->GetStreamData(pszLDTFile, &pStream);
	} else {
		pStream = new SPFileStream(GetAddResPath( pszLDTFile, RES_WORK_RESOURCE_PATH));	
	}
#endif

	bool bRet = false;
	if(pStream) {
		bRet = LoadLDTFile(pStream);	
		m_strFileName = pszLDTFile;
		pStream->Release();
	} else {		
		//assert(0 && "LDT not found");
	}
	return bRet;
}


bool SPLDTFile::LoadLDTFile( SPStream* pLDTStream)
{
	LDT_Header	Header;
	LDT_Field	tmpCell;
	long		tmpLong;

	short       tmpShort; // VB���� CInt�� �Ѿ�´�. 
	//unsigned short     tmpShort;	// by metalgeni..

	float		tmpFloat;
	long i,j;

	if(pLDTStream == NULL || pLDTStream->Valid() == false) 
		return false;

	Clean();

	pLDTStream->Seek(0, SEEK_SET);
	pLDTStream->Read( &Header, sizeof(Header));	
	m_lDB_ID = Header.nDB_ID;
	m_nFieldCount= Header.nFields;
	m_nDataCount = Header.nData ;

	// ������
	string strFileName;
	m_Label.resize( Header.nFields );
	for( j = 0; j < Header.nFields; j++ ) {
		m_Label[j] = Header.FieldNAM[j];

		//string strFileName = GetUpperString2(m_Label[j].String);
		string strFileName;
		GetUpperString3(strFileName, m_Label[j].String);
		
		m_hmLabel.insert( hash_map<string, long>::value_type(strFileName, j) );
		strFileName.clear();
	}

	int cnt = 0;

	m_LDTLinearDB.resize( Header.nData * Header.nFields + Header.nData );

	for (i=0; i< Header.nData ; i++) {
		pLDTStream->Read(&tmpLong, sizeof(tmpLong));		

		tmpCell.nSize        = sizeof(tmpLong);
		tmpCell.uData.lValue = tmpLong;
		tmpCell.nFldTyp      = fldPrimaryKey;

		m_LDTLinearDB[cnt++] = tmpCell;


		// �ӽ÷� ���´� ������ �ʹ� ����...
		// Check Duplicate.. [12/13/2007 metalgeni]
		//if(tmpLong) {
		//	stdext::hash_map<long, long>::iterator IterTemp = m_LDTprimaryidx.find(tmpLong);
		//	if(IterTemp != m_LDTprimaryidx.end()) {				
		//		assert(0 && "Find Dupplicate PrimaryKey.");
		//		return false;
		//	}
		//}

		m_LDTprimaryidx.insert(stdext::hash_map<long, long>::value_type(tmpLong, i*(Header.nFields+1) ));

		for (j=0; j< Header.nFields ; ++j) {
			tmpCell.pName = m_Label[j].String;
			tmpCell.nFldTyp = Header.FieldTYP[j];

			switch ( tmpCell.nFldTyp ) {
			case  fldNA :
				pLDTStream->Read( &tmpLong, sizeof(tmpLong));				
				tmpCell.nSize=0;
				tmpCell.uData.pValue=NULL;
				break;

			case fldString :
				{				
					pLDTStream->Read(&tmpShort, sizeof(tmpShort));

					assert(tmpShort >= 0 && tmpShort < 8192);	// check the string size

					// 4096->8192   2003.9.17 by metalgeni
					char strRead[8192] = {0, };
					pLDTStream->Read(strRead, tmpShort);
					strRead[tmpShort] = 0;

					short sLeng = strlen(strRead);
					tmpCell.nSize = sLeng;
					tmpCell.uData.pValue = new char[sLeng + 1];
					strcpy(tmpCell.uData.pValue, strRead);
					tmpCell.uData.pValue[sLeng] = 0;
				}
				break;

			case fldTF :
				pLDTStream->Read(&tmpLong, sizeof(tmpLong));
				tmpCell.nSize=sizeof(tmpLong);
				tmpCell.uData.lValue= tmpLong;
				break;

			case fldNum :
				pLDTStream->Read(&tmpLong, sizeof(tmpLong));
				tmpCell.nSize=sizeof(tmpLong);
				tmpCell.uData.lValue= tmpLong;
				break;

			case fldPer :
				pLDTStream->Read(&tmpFloat, sizeof(tmpFloat));
				tmpCell.nSize=sizeof(tmpLong);
				tmpCell.uData.fValue= tmpFloat;
				break;

			case fldFID :
				pLDTStream->Read(&tmpLong, sizeof(tmpLong));
				tmpCell.nSize=sizeof(tmpLong);
				tmpCell.uData.lValue= tmpLong;
				break;

			case fldAlias :
				pLDTStream->Read(&tmpShort, sizeof(tmpShort));

				assert(tmpShort >= 0 && tmpShort < 4096);	// check the string size
				tmpCell.nSize = tmpShort;
				tmpCell.uData.pValue = new char[tmpShort + 1];

				pLDTStream->Read( tmpCell.uData.pValue, tmpShort);
				tmpCell.uData.pValue[tmpShort] = '\0';
				break;

			case fldNum64:
				{					
					assert(0 && "LDT���� INT64 �������� �׷��� �Ⱦ�...");
					double tempVar64;					 
					pLDTStream->Read(&tempVar64, sizeof(tempVar64));
					tmpCell.nSize = sizeof(tempVar64);
					tmpCell.uData.pValue64 = new __int64;
					*(tmpCell.uData.pValue64) = tempVar64;
				}
				break;
				

			default :
				assert(0 && "invalid field type !");	 
			}
			m_LDTLinearDB[cnt++] = tmpCell;
		}
	}	
	m_bIsLoad = true ;			///< ���� �ε�
	return true;
}


long SPLDTFile::GetIDXprimary(long lPrimaryKey)
{	
	stdext::hash_map<long, long>::iterator location = m_LDTprimaryidx.find(lPrimaryKey);

	return (location != m_LDTprimaryidx.end()) ? location->second : (-1);
}

long SPLDTFile::GetPrimaryKey(long lIndex)
{ 
	return m_LDTLinearDB[lIndex * (GetFieldCount()+1) ].uData.lValue; 
}

bool SPLDTFile::GetField(long lItemID, long lFieldNum, LDT_Field& rLDTField)
{
	long lIndex = GetIDXprimary(lItemID);
	if (lIndex == (-1) || lFieldNum < 0 || lFieldNum >= GetFieldCount()) {
		rLDTField.Init();
		return false;
	}

	rLDTField = m_LDTLinearDB[lIndex + lFieldNum + 1];
	return true;
}

bool SPLDTFile::CheckLDTField(LDT_Field& stField)
{
	if( stField.nFldTyp == fldNum )
	{
		if( stField.uData.lValue == 0 )
			return false;
	}
	else if( stField.nFldTyp == fldString )
	{
		if( (int)strlen(stField.uData.pValue) == 0 )
			return false;
	}
	return true ;
}


bool SPLDTFile::GetFieldFromLable(long lItemID, const char* cFieldLabel, LDT_Field& rLDTField)
{
	long lIndex = GetIDXprimary(lItemID);
	if (lIndex == (-1)) {
		rLDTField.Init();
		return false;
	}
	long i = GetFieldNum( cFieldLabel );
	if (i >= 0) {
		rLDTField = m_LDTLinearDB[lIndex + i +1];
		return true;
	}

#ifdef _LATALE_SERVER
	_tprintf("ERROR : LDT=[%s] Field=[%s] : Invalid Field\n",m_strFileName.c_str(),cFieldLabel);
#endif
	assert(0 && "LDT ����Ÿ ����! Ȯ�� �Ͻÿ�!!!");				// �߸��� �ּҸ� ȣ���� �� �Ͽ�.

	rLDTField.Init();
	return false;
}

long SPLDTFile::GetFieldNum( const char* pszFieldLabel)
{
	//string strFileName = GetUpperString2(pszFieldLabel);

	string strFileName;
	GetUpperString3(strFileName, pszFieldLabel);

	hash_map<string, long>::iterator Iter = m_hmLabel.find(strFileName);
	if(Iter != m_hmLabel.end() && (strFileName == (*Iter).first)) { 
		return (*Iter).second;
	}

	return -1;
}





//////////////////////////////////////////////////////////////////////////
//
//	LDT Save
//
//////////////////////////////////////////////////////////////////////////
/**
	���� �ε��Ǿ� �ִ� SPLDTFile Class�� LDT File�� �����Ѵ�.
	SPStream �������̽��� �̿��ؼ� ������ �ϵ��� �Ѵ�.
	// ���� ��� �Ǵ� LDTArchive�� ���ؼ� ��밡�� ( CopyLDTFile(); �Ǵ� SaveLDTFile(); )
	@param LPCSTR pszLDTFile : ���� ���ϸ�
	@return bool : ���� ����
*/
bool SPLDTFile::SaveLDTFile( LPCSTR pszLDTFile)
{
	if (pszLDTFile == NULL) return false;	
	SPStream* pStream;	

	pStream = new SPFileStream(GetAddResPath( pszLDTFile, RES_WORK_RESOURCE_PATH), SPStream::OPEN_WRITE);	

	bool bRet = false;
	if(pStream) {
		bRet = SaveLDTFile(pStream);	
		pStream->Release();
	} else {		
		//assert(0 && "LDT not found");
	}
	return bRet;
}


/**
	���� �ε��Ǿ� �ִ� SPLDTFile Class�� LDT File�� �����Ѵ�.
	@param SPStream* pLDTStream
*/
bool SPLDTFile::SaveLDTFile( SPStream* pLDTStream)
{
	LDT_Header	saveHeader;
	LDT_Field*	ptmpCell = NULL;
	char* tempLabel = NULL ;
	long i,j;

	if(pLDTStream == NULL || pLDTStream->Valid() == false) 
		return false;

	//////////////////////////////////////////////////////////////////////////
	// Header Save
	memset(&saveHeader, 0, sizeof(LDT_Header)) ;
	saveHeader.nDB_ID = m_lDB_ID;
	saveHeader.nFields = m_nFieldCount;
	saveHeader.nData = m_nDataCount;
	for( j = 0; j < saveHeader.nFields; j++ ) 
	{
		tempLabel = m_Label[j].String;
		memcpy(saveHeader.FieldNAM[j].String , tempLabel, sizeof(LDT_STR64));		/// string Need Copy
		ptmpCell = &m_LDTLinearDB[j+1] ;		/// PrimaryKey Skip
		saveHeader.FieldTYP[j] = ptmpCell->nFldTyp ;
	}
	pLDTStream->Seek(0, SEEK_SET);
	pLDTStream->Write( &saveHeader, sizeof(saveHeader));

	//////////////////////////////////////////////////////////////////////////
	// Data Save
	int cnt = 0;
	for (i=0; i< saveHeader.nData ; i++) 
	{
		// Primary Key
		ptmpCell = &m_LDTLinearDB[cnt++] ;
		pLDTStream->Write( &ptmpCell->uData.lValue, sizeof(long));	

		// Field Data
		for (j = 0; j < saveHeader.nFields; ++j)
		{
			ptmpCell = &m_LDTLinearDB[cnt++] ;

			switch ( ptmpCell->nFldTyp ) {
			case  fldNA :
				ptmpCell->nSize=0;
				ptmpCell->uData.pValue=NULL;
				pLDTStream->Write( ptmpCell, sizeof(long));
				break;

			case fldString :
				{
					assert(ptmpCell->nSize >= 0 && ptmpCell->nSize < 8192);
					pLDTStream->Write(&ptmpCell->nSize, sizeof(short));
					char* pValue = new char[ptmpCell->nSize + 1];
					strcpy(pValue, ptmpCell->uData.pValue);
					pValue[ptmpCell->nSize] = '\0';
					pLDTStream->Write(pValue, ptmpCell->nSize);
					delete pValue ;
				}
				break;

			case fldTF :
			case fldNum :
			case fldPer :
			case fldFID :
				pLDTStream->Write(&ptmpCell->uData.lValue, sizeof(long));
				break;

			case fldAlias :
				{
					assert(ptmpCell->nSize >= 0 && ptmpCell->nSize < 4096);	// check the string size
					pLDTStream->Write(&ptmpCell->nSize, sizeof(short));
					char* pValue = new char[ptmpCell->nSize + 1];
					strcpy(pValue, ptmpCell->uData.pValue);
					pValue[ptmpCell->nSize] = '\0';
					pLDTStream->Write(pValue, ptmpCell->nSize);
					delete pValue ;
				}
				break;

			case fldNum64:
				{					
					assert(0 && "LDT���� INT64 �������� �׷��� �Ⱦ�...");
				}
				break;

			default :
				assert(0 && "invalid field type !");	 
			}
		}
	}
	char strEnd[4] = "END";
	pLDTStream->Write(strEnd, sizeof(strEnd));
	// pLDTStream->Close() ;
	return true;
}


/**
	SPLDTFile Class �� Txt���Ϸ��� ����
	@param @ const char* pszFileName : ���� ���ϸ� (Ȯ���� ����)
	@return bool : ��������
*/
bool SPLDTFile::SaveToTXT(const char* pszFileName) 
{
	int i, j ;
	LDT_Field*	ptmpCell = NULL;

	if( !m_bIsLoad )
	{
		assert(0 && "Can't open New File\n");
		return false;
	}

	ofstream file(GetAddResPath( pszFileName, RES_WORK_RESOURCE_PATH), std::ios::out | std::ios::app);
	if(!file){
		assert(0 && "Can't open New TXT File\n");
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	// Header
	file << "// FileName : " << pszFileName << endl << endl;
	file << "// Header.DB_ID : " << m_lDB_ID << endl;
	file << "// Header.nFields : " << m_nFieldCount << endl;
	file << "// Header.nData : " << m_nDataCount << endl;
	for( j = 0; j < m_nFieldCount; j++ ) {
		ptmpCell = &m_LDTLinearDB[j+1] ;
		file << "// Field [" << j << "] : type[" << ptmpCell->nFldTyp << "], Name[" << m_Label[j].String << "]" << endl;
	}
	file << endl ;

	//////////////////////////////////////////////////////////////////////////
	// DATA
	int cnt = 0;
	for (i=0; i< m_nDataCount ; i++) 
	{
		// Primary Key
		ptmpCell = &m_LDTLinearDB[cnt++] ;
		file << "[" << i << "] P-Key[" << ptmpCell->nFldTyp << ":" << ptmpCell->nSize << ":" << ptmpCell->uData.lValue << "]\t" ;

		// Field Data
		for (j = 0; j < m_nFieldCount; ++j)
		{
			ptmpCell = &m_LDTLinearDB[cnt++] ;

			switch ( ptmpCell->nFldTyp ) {
			case  fldNA :
				file << " [NA]\t";
				break;

			case fldString :
				file << m_Label[j].String << "[" << ptmpCell->nFldTyp << ":" << ptmpCell->nSize << ":" << ptmpCell->uData.pValue << "]\t" ;
				break;

			case fldTF :
			case fldNum :
			case fldPer :
			case fldFID :
				file << m_Label[j].String << "[" << ptmpCell->nFldTyp << ":" << ptmpCell->nSize << ":" << ptmpCell->uData.lValue << "]\t" ;
				break;

			case fldAlias :
				file << m_Label[j].String << "[" << ptmpCell->nFldTyp << ":" << ptmpCell->nSize << ":" << ptmpCell->uData.pValue << "]\t" ;
				break;

			case fldNum64:
				{					
					assert(0 && "LDT���� INT64 �������� �׷��� �Ⱦ�...");
				}
				break;

			default :
				assert(0 && "invalid field type !");	 
			}
		}
		file << endl ;
	}
	file << endl << "// END" << endl ;

	file.close() ;
	return true;
}




/**
	std::String ������ �����͸� �߰��ϴ� ��ƾ
	// Data�� ":"�� Delimiter�� ����Ѵ�.
	// type : size : data
	@param std::string& strLDTField : Field Data
	@return bool : ��������
*/
bool SPLDTFile::PushBack(std::string& strLDTField)
{
	int j ;
	int iIndex = 0 ;
	LDT_Field	tmpCell ;
	std::vector<std::string> vstrField ;

	if( !m_bIsLoad )			return false ;

	// 1) Parsing Data
	// 2) Data Count ���� (Field�� �������� �ʴ´�.)
	// 3) LinearDB Resize
	// 4) Primary Key Insert
	// 5) Data Inserting ( LinearDB )

	GetSeperateString(strLDTField, vstrField) ;
	if( (int)vstrField.size() != (m_nFieldCount+1) * 3 )		// ������ �����ʹ� 3��
	{
		assert(0 && "LDT Parameter ERROR") ;
		return false ;
	}

	iIndex = (int)m_LDTLinearDB.size() ;		// LDTLinearDB Start Point

	m_nDataCount += 1;
	m_LDTLinearDB.resize( m_nDataCount * m_nFieldCount + m_nDataCount );

	int iFieldcnt = 1 ;
	tmpCell.nFldTyp      = fldPrimaryKey;
	tmpCell.nSize        = sizeof(long);
	tmpCell.uData.lValue = atol( vstrField[iFieldcnt++].c_str() ) ;

	m_LDTLinearDB[ iIndex++ ] = tmpCell;
	m_LDTprimaryidx.insert(stdext::hash_map<long, long>::value_type(tmpCell.uData.lValue, m_nDataCount * m_nFieldCount + m_nDataCount ));

	for (j=0; j< m_nFieldCount ; ++j) 
	{
		tmpCell.Init() ;

		tmpCell.pName = m_Label[j].String;
		tmpCell.nFldTyp = atol( vstrField[iFieldcnt++].c_str() ) ;
		tmpCell.nSize	= atoi( vstrField[iFieldcnt++].c_str() ) ;

		switch ( tmpCell.nFldTyp ) {
			case  fldNA :
				tmpCell.nSize=0;
				tmpCell.uData.pValue=NULL;
				iFieldcnt++ ;
				break;

			case fldString :
				{
					assert(tmpCell.nSize >= 0 && tmpCell.nSize < 8192);
					tmpCell.uData.pValue = new char[tmpCell.nSize + 1];
					strcpy( tmpCell.uData.pValue, vstrField[iFieldcnt++].c_str() );
					tmpCell.uData.pValue[tmpCell.nSize] = '\0';
				}
				break;

			case fldTF :
			case fldNum :
			case fldPer :
			case fldFID :
				tmpCell.nSize=sizeof(long);
				tmpCell.uData.lValue= atol( vstrField[iFieldcnt++].c_str() );
				break;

			case fldAlias :
				{
					assert( tmpCell.nSize >= 0 && tmpCell.nSize < 4096);
					tmpCell.uData.pValue = new char[tmpCell.nSize + 1];
					strcpy(tmpCell.uData.pValue, vstrField[iFieldcnt++].c_str() );
					tmpCell.uData.pValue[tmpCell.nSize] = '\0';
				}
				break;

			case fldNum64:
				assert( 0 && "LDT���� INT64 �������� �׷��� �Ⱦ�...");
				break;


			default :
				assert( 0 && "invalid field type !");	 
		}
		m_LDTLinearDB[iIndex++] = tmpCell;			///< ���� �����ʹ� ���� �ڿ� �ִ´�.
	}
	return true ;
}















