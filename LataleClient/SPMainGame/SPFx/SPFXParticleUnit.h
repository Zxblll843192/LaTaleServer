// ***************************************************************
//  SPFXParticleUnit   version:  1.0   ��  date: 09/29/2006
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2006 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#pragma once

class SPFXUnit;
class SPFXParticleObject;

class SPFXParticleUnit : public SPFXUnit
{
protected:
	int										m_iCurFrameNum;
	int										m_iMaxFrameCount;

	float									m_fAccumulateCreateTime;
	float									m_fCreateTime;				// �߻� �ð�
	int										m_iCreateCount;				// �߻� ����
	SPFX_PARTICLE_AREA_TYPE					m_eAreaType;				// ���� Ÿ��
	BOOL									m_bPathFollow;				// �н��� ���� ȸ�� ���� ����
	int										m_iMagnetPosX;				// �ڼ� ������ ��ġ X
	int										m_iMagnetPosY;				// �ڼ� ������ ��ġ Y

	float									m_fCalOut[ PARTICLE_DATA_COUNT ];
	float									m_fCalOutNextGravity;

	float									m_fStartTimeOut[ PARTICLE_DATA_COUNT ];		//	ó�� �ð�
	float									m_fEndTimeOut[ PARTICLE_DATA_COUNT ];		//	�� �ð�

	float									m_fStartValueOut[ PARTICLE_DATA_COUNT ];	//	ó�� ��
	float									m_fEndValueOut[ PARTICLE_DATA_COUNT ];		//	�� ��

	float									m_fStartTimeOutNextGravity;					//	ó�� ���� �߷� �ð�
	float									m_fEndTimeOutNextGravity;					//	�� ���� �߷� �ð�

	float									m_fStartValueOutNextGravity;				//	ó�� ���� �߷� ��
	float									m_fEndValueOutNextGravity;					//	�� ���� �߷� ��

	STD_VECTOR_SPFXPARTICLEOBJECT			m_vpParticleObject;


	void			CalFrameData			();
	void			CalValueData			( float fTime );

	void			RandomCreatePos			( float& fOutPosX , float& fOutPosY );
	void			RandomCreatePosEllipse	( float& fOutPosX , float& fOutPosY , float fRandomAngle );
	void			RandomCreatePosArea		( float& fOutPosX , float& fOutPosY , float fRandomAngle );

	void			SettingObject			( SPFXParticleObject& stObject );
	void			CreateObject			();
	void			ProcessObject			( float fTime );
	void			RenderObject			();

	float			GetRandomAngle			();


public:
	SPFXParticleUnit						(void);
	virtual ~SPFXParticleUnit				(void);

	virtual void	SetNull					();
	virtual	void	Init					();
	virtual	bool	Process					( float fTime );
	virtual	bool	Render					( float fTime );

	void			RenderOnlyLine			();
};

//////////////////////////////////////////////////////////////////////////
/*
class SPFXParticleUnit21 : public SPFXUnit
{
public:
	SPFXParticleUnit21					(void);
	virtual ~SPFXParticleUnit21			(void);

	virtual void	SetNull				();
	virtual	void	Init				();
	virtual	bool	Process				( float fTime );
	virtual	bool	Render				( float fTime );

protected:

	void			InitParticleInstance( SPFXParticleInstance& ParticleInstance );

	//////////////////////////////////////////////////////////////////////////

	UINT								m_iMaxRenderParticle;	// �ִ� �׸��� �ִ� ��
	UINT								m_iMaxParticle;			// � ���� �ﱸ �����ų� 0�̸� �׻� m_iMaxRenderParticle�� ��´�.
	UINT								m_iCurNOParticle;
	std::vector<SPFXParticleInstance>	m_vParticleInstance;
	SPFX_PARTICLE_MOVE					m_ParticleMove;


};
*/