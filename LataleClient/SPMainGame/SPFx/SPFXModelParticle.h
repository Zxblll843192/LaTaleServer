// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-24 ���� 10:26:19
//***************************************************************************

#pragma once

class SPFXModel;

class SPFXModelParticle : public SPFXModel
{
public:
	SPFXModelParticle					();
	virtual ~SPFXModelParticle			();

	virtual void		SetNull			();
	virtual void		Init			();
	virtual void		Destroy			();
	virtual bool		SetImage		( SPTexture** ppImage );
	virtual LRESULT		GetMemberValue	( MODEL_VALUE_TYPE mvMsg , LPARAM lParam = 0 );

protected:

	SPTexture*							m_pFrameImage;										//	�ؽ�ó

	int									m_iFrameCount;										//	������ ������ ����
	std::vector<SPFXParticleFrameData*>	m_vpFrameData;										//	������ ���� ������ ������

	SPFX_PARTICLE_AREA_TYPE				m_eAreaType;										//	���� ����

	SPFX_PARTICLE_DATA_TYPE				m_eDataType;										//	��ƼŬ ������ ����
	STD_MAP_PARTICLE_VALUE				m_mValueData[ PARTICLE_DATA_COUNT ];				//	��ƼŬ ������ ��

	SPFX_PARTICLE_OBJECT_DATA_TYPE		m_eObjectDataType;									//	��ƼŬ ��ü ������ ����
	STD_MAP_PARTICLE_VALUE				m_mObjectValueData[ PARTICLE_OBJECT_DATA_COUNT ];	//	��ƼŬ ��ü ������ ��

	int									m_iImageFrameCount;									//	�̹��� ������ ������ ����
	std::vector<SPFXFrameData*>			m_vpImageFrameData;									//	������ ���� �̹��� ������ ������

	BOOL								m_bPathFollow;										//	�н��� ���� ȸ�� �ڵ� ��� ����

};

//////////////////////////////////////////////////////////////////////////
//
//	FX Model Version 2.1 �϶� ��� �ϴ� Ŭ����
//

//class SPFXModelParticle21 : public SPFXModel {
//public:
//	SPFXModelParticle21();
//	SPFXModelParticle21(SPID_FX ID, float fDelay);
//	virtual ~SPFXModelParticle21();
//
//	virtual void SetNull();
//	virtual void Init();
//	virtual void Destroy();
//	virtual bool SetImage(SPTexture** ppImage);	
//	virtual LRESULT GetMemberValue(MODEL_VALUE_TYPE mvMsg, LPARAM lParam = 0);
//
//protected:
//	SPTexture*				m_pFrameImage;	
//	float					m_fRotation;			// �� �������� ȸ����.	
//	float					m_fScale;				// ������
//
//	RECT					m_RectSrc;				// �� �������� �ؽ��ļҽ�.	
//	RECT					m_RectSize;				// �� �������� ����Ÿ���� �����ϴ� ����������
//
//	UINT					m_iMaxRenderParticle;	// �ִ� �׸��� �ִ� ��
//	UINT					m_iMaxParticle;			// � ���� �ﱸ �����ų� 0�̸� �׻� m_iMaxRenderParticle�� ��´�.
//
//	D3DXCOLOR				m_RGBA;					// �÷�
//
//
//	SPFX_PARTICLE_MOVE		m_ParticleMove;			// � ��ƼŬ ������
//
//
//	// VECTOR4�� ���ڷ� ����Ѵ�..
//	// x : VelocityX
//	// y : VelocityY
//	// z : AccelX
//	// w : AccelY
//	D3DXVECTOR4				m_vec4ParticleFactor;	
//
//};
