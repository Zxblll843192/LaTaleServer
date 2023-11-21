// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-5-9    13:51 
//***************************************************************************

#pragma once

#include <string>

class SPFXModel;
class SPFXModelBaseLoader;
class SPStream;

struct SPFXStreamDefaultData;

class SPFXModelParticleLoader : public SPFXModelBaseLoader
{
private:

	// {{ WORD CASE MAP
	DECLARE_WORDCASE_MAP ( OnAreaType				);		//	��ƼŬ ���� Ÿ��
	DECLARE_WORDCASE_MAP ( OnPathRotation			);		//	�н��� ���� ȸ���� �ڵ����� �ϴ� ����
	DECLARE_WORDCASE_MAP ( OnFrameDataType			);		//	������ ������ Ÿ�Կ� ���� ���� �غ�
	DECLARE_WORDCASE_MAP ( OnValueDataType			);		//	�� ������ Ÿ�Կ� ���� ���� �غ�
	DECLARE_WORDCASE_MAP ( OnObjectValueDataType	);		//	������Ʈ �������� Ÿ�Կ� ���� ���� �غ�
	DECLARE_WORDCASE_MAP ( OnBlockBegin				);		//	�� ����
	DECLARE_WORDCASE_MAP ( OnTime					);		//	�����Ӵ� ���ӽð�
	DECLARE_WORDCASE_MAP ( OnScaleX					);		//	�����Ӵ� X ũ�� ��
	DECLARE_WORDCASE_MAP ( OnScaleY					);		//	�����Ӵ� Y ũ�� ��
	DECLARE_WORDCASE_MAP ( OnRadianDegree			);		//	�����Ӵ� ȸ�� ����
	DECLARE_WORDCASE_MAP ( OnLRSwap					);		//	�����Ӵ� �¿� �ø� ��
	DECLARE_WORDCASE_MAP ( OnColor					);		//	�����Ӵ� �÷� ��
	DECLARE_WORDCASE_MAP ( OnSrcRect				);		//	�����Ӵ� �̹��� �簢��
	DECLARE_WORDCASE_MAP ( OnAdjustRect				);		//	�����Ӵ� �����Ҷ� �����ϴ� �簢��
	DECLARE_WORDCASE_MAP ( OnAreaRect				);		//	�����Ӵ� ����
	DECLARE_WORDCASE_MAP ( OnCreateTime				);		//	�����Ӵ� �����Ǵ� �ð�
	DECLARE_WORDCASE_MAP ( OnCreateCount			);		//	�����Ӵ� �����Ǵ� ����
	DECLARE_WORDCASE_MAP ( OnMagnetPos				);		//	�ڼ� ��ġ
	DECLARE_WORDCASE_MAP ( OnFirstKeyTime			);		//	MAP�� ù��° Ű Time
	DECLARE_WORDCASE_MAP ( OnSecondKeyValue			);		//	MAP�� �ι�° �� Value
	DECLARE_WORDCASE_MAP ( OnBlockEnd				);		//	�� ��
	//

	// }}

	int								m_iDeep;				//	���� üũ�ϱ� ���� ��
	SPFXParticleFrameData			m_ParticleFrameData;	//	������ ����Ŭ ������
	SPFXFrameData					m_FrameData;			//	������ �̹��� ������
	SPFX_PARTICLE_FRAME_DATA_TYPE	m_eFrameDataType;		//	������ ������ Ÿ��
	SPFX_PARTICLE_DATA_TYPE			m_eValueDataType;		//	�� ������ Ÿ��
	SPFX_PARTICLE_OBJECT_DATA_TYPE	m_eObjectValueDataType;	//	������Ʈ �� ������ Ÿ��
	float							m_fFirstKeyTime;		//	�ӽ÷� ���� �ϴ� Ű ��
	float							m_fSecondKeyValue;		//	�ӽ÷� ���� �ϴ� Ű ��
	STD_MAP_PARTICLE_VALUE			m_mValueData;			//	�ӽ÷� ���� �ϴ� ������
	

public:
	SPFXModelParticleLoader(void);
	virtual ~SPFXModelParticleLoader(void);

	virtual	bool	LoadASCII	( SPFXModel* pModel , SPStream* pFile );
	virtual	bool	LoadBinary	( SPFXModel* pModel , SPStream* pFile , SPFXStreamDefaultData& DefaultData , float fVersion );
};

//////////////////////////////////////////////////////////////////////////
//	FXM �� 2.1 �϶� ��ƼŬ
//////////////////////////////////////////////////////////////////////////
//
//class SPFXModelParticleLoader21 : public SPFXModelBaseLoader
//{
//private:
//
//	// {{ WORD CASE MAP
//	DECLARE_WORDCASE_MAP ( OnDelay					);		//	Dealy�� �б�
//	DECLARE_WORDCASE_MAP ( OnMaxRenderParticle		);		//	�ִ� �����Ǵ� ��ƼŬ��
//	DECLARE_WORDCASE_MAP ( OnMaxParticle			);		//	�ִ� ��ƼŬ��
//	DECLARE_WORDCASE_MAP ( OnRadianDegree			);		//	ȸ�� ��
//	DECLARE_WORDCASE_MAP ( OnScale					);		//	ũ�� ��
//	DECLARE_WORDCASE_MAP ( OnParticleMove			);		//	��ƼŬ �̵����� �ɼ�
//	DECLARE_WORDCASE_MAP ( OnColor					);		//	�÷� �б�
//	DECLARE_WORDCASE_MAP ( OnSrcRect				);		//	�̹����� �簢��
//	DECLARE_WORDCASE_MAP ( OnAdjustRect				);		//	�̹����� �����Ҷ� �����Ǵ� �簢��
//	// }}
//
//	SPID_FX			m_eSPID_FX;								//	FX�� ID
//
//public:
//	SPFXModelParticleLoader21(void);
//	virtual ~SPFXModelParticleLoader21(void);
//
//	virtual	bool	LoadASCII	( SPFXModel** ppModel , SPStream* pFile , SPID_FX eSPID_FX );
//	virtual	bool	LoadBinary	( SPFXModel** ppModel , SPStream* pFile	, SPID_FX eSPID_FX , SPFXStreamDefaultData& DefaultData , float fVersion );
//};
