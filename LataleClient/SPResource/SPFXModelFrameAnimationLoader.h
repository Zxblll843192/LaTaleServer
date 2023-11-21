// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-5-9    13:55 
//***************************************************************************

#pragma once

#include <string>

class SPFXModel;
class SPFXModelBaseLoader;
class SPStream;

enum SPID_FX;

struct SPFXStreamDefaultData;

class SPFXModelFrameAnimationLoader : public SPFXModelBaseLoader
{
private:

	// {{ WORD CASE MAP
	DECLARE_WORDCASE_MAP ( OnBlockBegin				);		//	�� ����
	DECLARE_WORDCASE_MAP ( OnTime					);		//	�����Ӵ� ���ӽð�
	DECLARE_WORDCASE_MAP ( OnScale					);		//	�����Ӵ� ũ�� �� 2.0 ���Ϲ��������� ���!!!
	DECLARE_WORDCASE_MAP ( OnScaleX					);		//	�����Ӵ� X ũ�� ��
	DECLARE_WORDCASE_MAP ( OnScaleY					);		//	�����Ӵ� Y ũ�� ��
	DECLARE_WORDCASE_MAP ( OnRadianDegree			);		//	�����Ӵ� ȸ�� ����
	DECLARE_WORDCASE_MAP ( OnLRSwap					);		//	�����Ӵ� �¿� �ø� ��
	DECLARE_WORDCASE_MAP ( OnColor					);		//	�����Ӵ� �÷� ��
	DECLARE_WORDCASE_MAP ( OnSrcRect				);		//	�����Ӵ� �̹��� �簢��
	DECLARE_WORDCASE_MAP ( OnAdjustRect				);		//	�����Ӵ� �����Ҷ� �����ϴ� �簢��
	DECLARE_WORDCASE_MAP ( OnBlockEnd				);		//	�� ��
	//

	int				m_iDeep;								//	���� üũ�ϱ� ���� ��
	SPFXFrameData	m_FrameData;							//	������ ������

public:
	SPFXModelFrameAnimationLoader			(void);
	virtual ~SPFXModelFrameAnimationLoader	(void);

	virtual	bool	LoadASCII	( SPFXModel* pModel , SPStream* pFile );
	virtual	bool	LoadBinary	( SPFXModel* pModel , SPStream* pFile , SPFXStreamDefaultData& DefaultData , float fVersion );
};
