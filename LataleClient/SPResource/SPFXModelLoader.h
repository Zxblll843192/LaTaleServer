// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-5-9    14:13 
//***************************************************************************

#pragma once

#include <string>

class SPFXModel;
//class SPFXFactory;
class SPFXModelBaseLoader;
class SPStream;

enum SPID_FX_MODEL;

class SPFXModelLoader
{
private:

	// {{ WORD CASE MAP
	DECLARE_WORDCASE_MAP( OnComment					);						//	�ڸ�Ʈ ó��
	DECLARE_WORDCASE_MAP( OnFXType					);						//	FXŸ�� �б�
	DECLARE_WORDCASE_MAP( OnFXVersion				);						//	FX���� �б�
	DECLARE_WORDCASE_MAP( OnFXId					);						//	FX���̵� �б�
	// }}

	SPStream*			m_pFileHandle;										//	���� �ڵ�
	SPFXModel*			m_pModel;											//	FX�� ������

	SPFXFactory< SPFXModelBaseLoader* , SPID_FX_MODEL > m_LoaderFactory;	//	ModelLoader	Factory
	SPFXFactory< SPFXModel* , SPID_FX_MODEL >			m_FXModelFactory;	//	SPFXModel	Factory

	SPID_FX_MODEL		m_eFXModelType;										//	FX Ÿ��
	float				m_fFXModelVersion;									//	FX ����

	std::string			m_strImgPath;										//	�̹��� ���
	std::string			m_strImgName;										//	�̹��� ���ϸ�

	bool	LoadFileASCII	( std::string strFileName = "" );				//	ASCII �������.
	bool	LoadFileBinary	( std::string strFileName = "" );				//	BINARY �������.

	bool	ExeSubLoader	( int iFXModelID );							//	FX_ID�� �о� �ش�Ǵ� �δ��� ȣ���Ѵ�.

public:
	SPFXModelLoader(void);
	virtual ~SPFXModelLoader(void);

	//	�ش� ���� �����͸� �о��� FX�𵨿��� �߰��� �� �����ش�.
	SPFXModel* LoadFile( std::string strFileName = "" );
	const char* GetImgPath()	{	return m_strImgPath.c_str();	}
	const char* GetImgName()	{	return m_strImgName.c_str();	}
};
