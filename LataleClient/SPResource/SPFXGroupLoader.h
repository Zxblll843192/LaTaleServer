// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-5-9    13:17 
//***************************************************************************

#pragma once

#include <string>

struct SPFXGroup;

namespace {

#define DECLARE_WORDCASE_MAP( _CASE_MAP_FUNCTION_ ) \
	bool _CASE_MAP_FUNCTION_ (std::string strParam);

#define WORDCASE_MAP( _CLASS_ , _CASE_MAP_FUNCTION_ ) \
	bool _CLASS_::_CASE_MAP_FUNCTION_ (std::string strParam) 

#define EXCUTE_WORDCASE_MAP(_CASE_, _CASE_MAP_FUNCTION_) \
	if ( true == isCase( _CASE_ ,  str.c_str() ) )  { \
	if(_CASE_MAP_FUNCTION_(str)) \
	continue; \
		else \
		return false; \
	}
}

class SPFXGroupLoader
{
private:

	// {{ WORD CASE MAP
	DECLARE_WORDCASE_MAP( OnComment					);	//	�ڸ�Ʈ ó��
	DECLARE_WORDCASE_MAP( OnGroupId					);	//	FX�׷� ���̵� �б�
	DECLARE_WORDCASE_MAP( OnModelId					);	//	FX�� ���̵� �б�
	// }}

	SPFXGroup*							m_pSPFXGroup;					//	�Ŵ����� �߰��� �׷쵥����

	bool	LoadFileASCII( std::string strFileName = "" );	//	ASCII �������.
	bool	LoadFileBinary( std::string strFileName = "" );	//	BINARY �������.

public:
	SPFXGroupLoader(void);
	virtual ~SPFXGroupLoader(void);

	//	�ش� ���� �����͸� �о��� FX�׷쿡�� �߰��� �� �����ش�.
	SPFXGroup*	LoadFile( std::string strFileName = "" );

};
