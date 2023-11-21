// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-5-9    13:39 
//***************************************************************************

#pragma once

#include <string>

class SPFXModel;
class SPTexture;
class SPStream;

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

//	FX ���� ���̳ʸ� �������

#define FXM_VERSION		3.2f

struct SPFXStreamHeader {
	enum { BINARY_CHECK = 415 };

	char			szDescription[255];
	int				iBinary;
	float			fVersion;
	unsigned long	ulExpansion;

	SPFXStreamHeader()
	{
		memset( szDescription , 0 , sizeof( szDescription ) );
		iBinary		=	0;
		fVersion	=	0.0f;
		ulExpansion	=	0;
	}
};

//	Ver 1.0 - > 1.1	�������
//		Loop , ScreenRender �׸��� iFollowParent�� ���� ����
//	Ver 1.1 - > 2.0	�������
//		bool			bLightMap;	-> TEXTURE_EFFECT	eTextureEffect; ���� ����
//	Ver 2.0 - > 2.1	�������
//		SPFXFrameDataŬ������	fFrameScale	-> fFrameScaleX , fFrameScaleY �߰�.
//	Ver 2.1 - > 3.0 �������
//		��ƼŬ ���� ������ ( 2.1�� �ε带 �ϳ� 3.0���� ������ ��ȯ�� ���� ���� )
//	Ver 3.0 - > 3.1 �������
//		SPFXStreamDefaultData Ŭ������ Model ID , Type �߰� , fDelayTime �� ����
//	Ver 3.1 - > 3.2 �������
//		SPFXStreamDefaultData Ŭ������ FXM Render Layer �߰�

//	FX Model �⺻ ������

struct SPFXStreamDefaultData {	// AJJIYA Ver.Now!!! [10/6/2008 AJJIYA]
	TEXTURE_EFFECT	eTextureEffect;
	int				iFollowParent;
	float			fLifeTime;
	char			szPath[255];
	UINT			uiFXModelID;
	SPID_FX_MODEL	eFXModelType;
	int				iFXMRenderLayer;

	SPFXStreamDefaultData()
	{
		memset( szPath , 0 , sizeof( szPath ) );
		eTextureEffect	=	TEXTURE_EFFECT_NULL;
		iFollowParent	=	0;
		fLifeTime		=	0.0;
		uiFXModelID		=	0;
		eFXModelType	=	IDFXM_NULL;
		iFXMRenderLayer	=	0;
	}
};

struct SPFXStreamDefaultData31 {	// AJJIYA Ver3.1 [12/1/2005]
	TEXTURE_EFFECT	eTextureEffect;
	int				iFollowParent;
	float			fLifeTime;
	char			szPath[255];
	UINT			uiFXModelID;
	SPID_FX_MODEL	eFXModelType;

	SPFXStreamDefaultData31()
	{
		memset( szPath , 0 , sizeof( szPath ) );
		eTextureEffect	=	TEXTURE_EFFECT_NULL;
		iFollowParent	=	0;
		fLifeTime		=	0.0;
		uiFXModelID		=	0;
		eFXModelType	=	IDFXM_NULL;
	}
};

struct SPFXStreamDefaultData30 {	// AJJIYA Ver3.0 [12/1/2005]
	TEXTURE_EFFECT	eTextureEffect;
	int				iFollowParent;
	float			fLifeTime;
	float			fDelayTime;
	char			szPath[255];

	SPFXStreamDefaultData30()
	{
		memset( szPath , 0 , sizeof( szPath ) );
		eTextureEffect	=	TEXTURE_EFFECT_NULL;
		iFollowParent	=	0;
		fLifeTime		=	0.0;
		fDelayTime		=	0.0;
	}
};

struct SPFXStreamDefaultData11 {	// AJJIYA Ver1.1 [12/1/2005]
	bool			bLightMap;
	int				iFollowParent;
	float			fLifeTime;
	float			fDelayTime;
	char			szPath[255];

	SPFXStreamDefaultData11()
	{
		memset( szPath , 0 , sizeof( szPath ) );
		bLightMap		=	false;
		iFollowParent	=	0;
		fLifeTime		=	0.0;
		fDelayTime		=	0.0;
	}
};

class SPFXModelBaseLoader
{
protected:

	// {{ WORD CASE MAP
	DECLARE_WORDCASE_MAP ( OnComment				);		//	�ڸ�Ʈ ó��
	DECLARE_WORDCASE_MAP ( OnPath					);		//	�ؽ�ó ���� ���
	DECLARE_WORDCASE_MAP ( OnLifeTime				);		//	���� �ð� �б�
	DECLARE_WORDCASE_MAP ( OnFollowParent			);		//	�θ� ���� �ٴҶ��� �ɼ�
	DECLARE_WORDCASE_MAP ( OnLightMap				);		//	���̸� ��� ����
	DECLARE_WORDCASE_MAP ( OnModelType				);		//	�� Ÿ��
	DECLARE_WORDCASE_MAP ( OnRenderLayer			);		//	���� ���̾�
	// }}

	SPFXModel*		m_pModel;								//	�������� �޾ƿ� �� ������
	std::string		m_strImgPath;							//	ĳ���������� ����� �̹��� ���
	std::string		m_strImgName;							//	ĳ���������� ����� �̹��� ���ϸ�

	//	��θ� �־� �ؽ�ó�� �޾ƿ´�.
	bool			GetTexture( const char* pszPath , SPTexture** ppTexture );

public:
	SPFXModelBaseLoader(void);
	virtual ~SPFXModelBaseLoader(void);

	//	���� �ڽĵ��� �˾Ƽ� �ε��Ѵ�.
	virtual	bool	LoadASCII	( SPFXModel* pModel , SPStream* pFile ) = 0;
	virtual	bool	LoadBinary	( SPFXModel* pModel , SPStream* pFile , SPFXStreamDefaultData& DefaultData , float fVersion );

	const char*	GetImgPath()	{	return m_strImgPath.c_str();	}
	const char* GetImgName()	{	return m_strImgName.c_str();	}
};

extern	bool		IsASCIIFile	( const char* pszFileName );
extern	bool		StrToChar	( char* pszOut , std::string *strLine );
extern	int			StrToInt	( std::string *strLine );
extern	bool		StrToBool	( std::string *strLine );
extern	float		StrToFloat	( std::string *strLine );
extern	POINT		StrToPoint	( std::string *strLine );
extern	RECT		StrToRect	( std::string *strLine );
extern	D3DXCOLOR	StrToColor	( std::string *strLine );
