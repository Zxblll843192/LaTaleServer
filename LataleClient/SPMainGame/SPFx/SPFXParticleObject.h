// ***************************************************************
//  SPFXParticleObject   version:  1.0   ��  date: 10/12/2006
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2006 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

class SPFXParticleObject
{
public:
	SPFXParticleObject(void);
	virtual ~SPFXParticleObject(void);

	virtual void	SetNull					();
	virtual	void	Create					();
	virtual void	Destory					();
	virtual	void	Process					( float fTime );
	virtual	void	Render					();

	void			RenderOnlyLine			();

	FXUNIT_STATE	GetState				();

	void			SetCarmeraPos			( float* pfCarmeraPosX , float* pfCarmeraPosY );
	void			SetParentPos			( float fParentPosX , float fParentPosY );

	void			SetParentAlpha			( float* pfParentAlpha );
	void			SetParentGravity		( float* pfParentGravity );
	void			SetDirection			( float fDirection );
	void			SetPathFollow			( BOOL bPathFollow );
	void			SetMagnetPos			( int* piMagnetPosX , int* piMagnetPosY );

	void			SetParentRed			( float* pfParentRed );
	void			SetParentGreen			( float* pfParentGreen );
	void			SetParentBlue			( float* pfParentBlue );
	void			SetParentMagnet			( float* pfParentMagnet );

	void			SetParentNextGravity	( float* pfParentNextGravity );

	void			SetParentDirection		( bool bParentDirection );

	void			SetDefaultPos			( float fDefaultPosX , float fDefaultPosY );
	void			SetObjectValue			( SPFX_PARTICLE_OBJECT_DATA_TYPE eObjectDataType , STD_MAP_PARTICLE_VALUE*	pmParticleObjectValue );

	void			SetTexture				( SPTexture* pTexture );
	void			SetRandomStart			( bool bRandom );
	void			AddImageFrameData		( SPFXFrameData* pFrameDaa );

protected:

	void			CalValueData			( float fTime );

	void			GetCalPosByTime			( float& fOutPosX , float& fOutPosY , float fTime , float* pfGravity );
	void			CalNowDirection			( float fTime );

	void			GetCurImageFrameData	();

	FXUNIT_STATE	m_FUState;
	float			m_fAccumulateProcess;

	float*			m_pfCarmeraPosX;				//	ī�޶� X ��ġ
	float*			m_pfCarmeraPosY;				//	ī�޶� Y ��ġ

	float			m_fParentPosX;					//	�θ� X ��ġ
	float			m_fParentPosY;					//	�θ� Y ��ġ

	float			m_fPosX;						//	���� ���� X ��ġ
	float			m_fPosY;						//	���� ���� Y ��ġ

	float			m_fDefaultPosX;					//	������ X ��ġ
	float			m_fDefaultPosY;					//	������ Y ��ġ

	float*			m_pfParentAlpha;				//	���� �θ��� ���İ�
	float*			m_pfParentGravity;				//	���� �θ��� �߷°�
	float			m_fDirection;					//	������ ���� ����
	BOOL			m_bPathFollow;					//	������⿡ ���� ȸ���� ����
	float			m_fPathFollowAngle;				//	������⿡ ���� ȸ���� ����
	float*			m_pfParentNextGravity;			//	���� ���� �ð��� ���� �߷°�
	int*			m_piMagnetPosX;					//	�ڼ� ������ ��ġ X
	int*			m_piMagnetPosY;					//	�ڼ� ������ ��ġ Y

	float*			m_pfParentRed;					//	���� �θ��� ����
	float*			m_pfParentGreen;				//	���� �θ��� ���
	float*			m_pfParentBlue;					//	���� �θ��� �Ķ�
	float*			m_pfParentMagnet;				//	���� �θ��� �ڼ� ������

	bool			m_bParentDirection;				//	���� �θ� �ٶ󺸴� ����

	float			m_fCalOut[ PARTICLE_OBJECT_DATA_COUNT ];	//	��ȭ�� ��갪

	//////////////////////////////////////////////////////////////////////////

	float			m_fStartTimeOut[ PARTICLE_OBJECT_DATA_COUNT ];	//	ó�� �ð�
	float			m_fEndTimeOut[ PARTICLE_OBJECT_DATA_COUNT ];	//	�� �ð�

	float			m_fStartValueOut[ PARTICLE_OBJECT_DATA_COUNT ];	//	ó�� ��
	float			m_fEndValueOut[ PARTICLE_OBJECT_DATA_COUNT ];	//	�� ��

	//////////////////////////////////////////////////////////////////////////

	STD_MAP_PARTICLE_VALUE*		m_pmParticleObjectValue[ PARTICLE_OBJECT_DATA_COUNT ];	//	��ȭ��

//	std::vector<D3DXVECTOR2>	m_vLine1;
//	std::vector<D3DXVECTOR2>	m_vLine2;

	//////////////////////////////////////////////////////////////////////////

	SPTexture*		m_pTexture;						//	�θ𿡼� �Ѱ� �޴´� �����̳� ������ ����!
	bool			m_bRandomStart;

	int				m_iCurFrameNumber;
	int				m_iStartFrameNumber;
	int				m_iEndFrameNumber;

	float			m_fAccumulateImageFrame;
	float			m_fCurFrameDelayTime;

	SPFXFrameData*	m_pCurFrameData;

	std::vector<SPFXFrameData*> m_vpImageFrameData;	//	������ ���� �̹��� ������ ������
};
