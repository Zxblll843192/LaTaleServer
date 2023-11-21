// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : ���� !: lItemID�� 0�� �ƴ϶� 1���� �����Ѵ�. 
//					�׸���, DB�� ���� �׻� 1,2,3 �� �ƴ�. ������ DB ������ Unique�� ������.
// Modified    : metalgeni 2004-08-29 ���� 2:32:54 
//***************************************************************************


#pragma once

#include <vector>
#include <hash_map>
#include <string>

// .NET2003 ���� �ؽø� ��붧����.. 
#ifdef _DEFINE_DEPRECATED_HASH_CLASSES
#undef _DEFINE_DEPRECATED_HASH_CLASSES 
#define _DEFINE_DEPRECATED_HASH_CLASSES 0	
#endif

#pragma warning(disable:4786)	// vector warning disable

using namespace std;
using namespace stdext;

class SPLDTManager;

class SPStream;

enum LDTfldTypes {
	fldNA = 0,
	fldString = 1,
	fldTF = 2,
	fldNum = 3,
	fldPer = 4,
	fldFID = 5,
	fldAlias = 6,
	fldNum64 = 7,
	fldPrimaryKey=255
};

struct LDT_STR64 {
	char	String[64];
};

struct LDT_Field {
	void Init() {
		pName=NULL;
		nSize=0;
		nFldTyp=0;
		uData.lValue=0;
	}
	char*		pName;
	long        nFldTyp;
	union
	{
		char*		pValue;
		long		lValue;
		float		fValue;
		__int64*	pValue64;		  
	} uData;
	int	nSize;
};

struct LDT_Header {
	long		nDB_ID;
	long		nFields;
	long		nData;
	LDT_STR64	FieldNAM[128];
	long		FieldTYP[128];
};

class SPLDTFile
{
public:	
	virtual ~SPLDTFile();	
	
	void		Clean();	

	// item ID�� field �ε����� ������ field ����ü�� �������ش�
	bool		GetField(long lItemID, long lFieldNum, LDT_Field& rLDTField);
	// �ش� Field�� Data�� �ִ��� ���� �ľ�
	bool		CheckLDTField(LDT_Field& stField) ;

	// item ID�� field label�� ������ field ����ü�� �������ش�
	bool		GetFieldFromLable(long lItemID, const char* cFieldLabel, LDT_Field& rLDTField);					

	long		GetItemCount() { return (long)(m_LDTprimaryidx.size()); }
	long		GetFieldCount() { return m_nFieldCount; }
	const char* GetFieldLabel( long lField ) { return m_Label[lField].String; }	
	long		GetFieldNum( const char* pszFieldLabel);

	// ���ڵ� �ε����κ��� �� ���ڵ��� primary key (lItemID)�� ��´�.
	long		GetPrimaryKey(long lIndex); 				

	// �ش� primary key (lItemID) �� ���ڵ� �ε����� �ǵ�����. //lPrimaryKey == ItemID�̴�
	long		GetIDXprimary(long lPrimaryKey);			

	long		GetDB_ID()				{ return m_lDB_ID; }
	const char* GetFileName()	{ return m_strFileName.c_str(); }
	void		Release();

	// SAVE Interface �߰� [200611:duragon]
	bool		SaveLDTFile( LPCSTR pszLDTFile);			///< LDT File�� ����
	bool		SaveToTXT(const char* pszFileName) ;		///< TXT File�� ����
	bool		PushBack(std::string& strLDTField);			///< Data Add --> type : size : data (��������!!)

protected:	
	friend SPLDTManager;	
	
	// ������ �׻� SPLDTManager������.
	SPLDTFile();
	bool		LoadLDTFile( LPCSTR pszLDTFile);		//SPLDTManager�� ȣ���ؾ���.
	bool		LoadLDTFile( SPStream* pLDTStream);		//SPLDTManager�� ȣ���ؾ���.
	
	int			GetRefCount();	
	void		IncreaseRef();

	bool		SaveLDTFile( SPStream* pLDTStream);		//[200611:duragon]SPLDTManager�� ȣ���ؾ���.
														// �ϴ��� Stream�κи� Protect��
	

private:

	vector<LDT_Field>		m_LDTLinearDB;		// DB
	hash_map<long, long>	m_LDTprimaryidx;	// Item ID to Index
	vector<LDT_STR64>		m_Label;			// ������

	hash_map<std::string, long> m_hmLabel;	

	long m_lDB_ID;
	long m_nFieldCount;
	long m_nDataCount;

	string m_strFileName;

	int m_iRefCount;
	bool m_bIsLoad ;			///< LDT������ �ε��Ǿ� �ִ��� ���� (�ּ� Header�� �־�� ��)

};




