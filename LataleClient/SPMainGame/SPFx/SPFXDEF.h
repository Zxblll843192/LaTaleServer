// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPNetworkDEF
// Comment     : 
// Creation    : metalgeni 2004-08-25 ���� 10:26:19
//***************************************************************************


#pragma once

enum SPID_FX_GROUP
{
	IDFXGR_NULL				= 0			,
	IDFXGR_LEVEL_UP			= 506		,
	IDFXGR_ASSULTED_SPEEDY	= 507		,
	IDFXGR_ASSULTED_MIGHTY	= 508		,
	IDFXGR_CRITICAL			= 1002		,
	IDFXGR_DAMAGE			= 5000		,
	IDFXGR_DAMAGE_MISS		= 5003		,
	IDFXGR_DAMAGE_IMMUNE	= 5004		,

	IDFXGR_PET_SHOP			= 1010		,
};

#ifndef _LATALE_SERVER

class SPFXUnit;
class SPFXParticleObject;

typedef	std::vector<SPFXUnit*>						STD_VECTOR_SPFXUNIT;
typedef std::vector<SPFXParticleObject*>			STD_VECTOR_SPFXPARTICLEOBJECT;


enum SPID_FX_MODEL
{
	IDFXM_NULL				= 0			,
	IDFXM_FRAMEANIMATION				,
	IDFXM_PARTICLE						,
};

enum SP_FX_UNIT
{
	FXUNIT_NULL				=	0		,
	FXUNIT_FRAMEANIMATION				,
	FXUNIT_DAMAGE						,
	FXUNIT_CRITICAL						,
	FXUNIT_PARTICLE						,

	FXUNIT_COUNT						,
};

enum SP_FXM_RENDER_LAYER
{
	FXM_RENDER_LAYER_OBJECT_FRONT	=	0	,
	FXM_RENDER_LAYER_OBJECT_BACK			,
	FXM_RENDER_LAYER_UI_FRONT				,
	FXM_RENDER_LAYER_UI_BACK				,

	FXM_RENDER_LAYER_COUNT					,
	FXM_RENDER_LAYER_ALL					,
};

//////////////////////////////////////////////////////////////////////////
//
//	FX Model Version 2.1 �϶� ��� �ϴ� Ŭ����
//

enum SPFX_PARTICLE_MOVE
{
	PARTICLE_NULL			=	0		,
	PARTICLE_CHARGE						,
	PARTICLE_SPREAD						,
	PARTICLE_SPREAD_BACK				,
	PARTICLE_DROP						,
	PARTICLE_DROP_BACK					,
};

struct SPFXParticleInstance
{
	D3DXVECTOR2 vec2Pos;
	D3DXVECTOR2 vec2Velocity;
	D3DXVECTOR2 vec2Accel;
};

//////////////////////////////////////////////////////////////////////////

enum SPFX_FOLLOW
{
	FX_FOLLOW_NULL			=	0x0000	,
	FX_FOLLOW_PARENT		=	0x0001	,
	FX_FOLLOW_FACINGPARENT	=	0x0002	,
	FX_FOLLOW_BOTH			=	0x0003	,
	FX_FOLLOW_LOOP			=	0x1000	,
	FX_FOLLOW_SCREENRENDER	=	0x2000	,
};

enum SPFX_PARTICLE_FRAME_DATA_TYPE
{
	PARTICLE_FRAME_DATA_NULL			=	0	,
	PARTICLE_FRAME_DATA_COMMON					,				//	��ƼŬ ���� ������ ������			
	PARTICLE_FRAME_DATA_IMAGE					,				//	��ƼŬ �̹��� ������ ������
};

enum SPFX_PARTICLE_AREA_TYPE
{
	SPFX_PARTICLE_AREA_NULL				=	0	,
	SPFX_PARTICLE_AREA_ELLIPSE					,				//	��
	SPFX_PARTICLE_AREA_AREA						,				//	�簢��
};

enum SPFX_PARTICLE_DATA_TYPE
{
	PARTICLE_DATA_NULL					=	0	,
	PARTICLE_DATA_ALPHA							,				//	Ȱ�� ����	- �ð����� ��ü ��ƼŬ�� ����ȴ�.
	PARTICLE_DATA_DIRECTION						,				//	���� ����	- ������ �ѹ��� ��ƼŬ�� �����ȴ�. 
	PARTICLE_DATA_GRAVITY						,				//	�߷�		- �ش� �ð����� ���� ��ƼŬ�� ����ȴ�.
	PARTICLE_DATA_RANGE							,				//	���� ����	- �����ɶ��� ���������� �����Ѵ�.
	PARTICLE_DATA_MAGNET_POINT					,				//	�ڼ� ������ - �ð����� ��ü ��ƼŬ�� ����ȴ�.
	PARTICLE_DATA_RED							,				//	COLOR ����	- �ð����� ��ü ��ƼŬ�� ����ȴ�.
	PARTICLE_DATA_GREEN							,				//	COLOR ���	- �ð����� ��ü ��ƼŬ�� ����ȴ�.
	PARTICLE_DATA_BLUE							,				//	COLOR �Ķ�	- �ð����� ��ü ��ƼŬ�� ����ȴ�.
	PARTICLE_DATA_COUNT							,
};

enum SPFX_PARTICLE_OBJECT_DATA_TYPE
{
	PARTICLE_OBJECT_DATA_NULL			=	0	,
	PARTICLE_OBJECT_DATA_VELOCITY				,				//	�̵� �ӵ�
	PARTICLE_OBJECT_DATA_X_SCALE				,				//	���� ũ��
	PARTICLE_OBJECT_DATA_Y_SCALE				,				//	���� ũ��
	PARTICLE_OBJECT_DATA_DIRECTION_MOVE			,				//	��� Y �̵�
	PARTICLE_OBJECT_DATA_LIFETIME				,				//	����
	PARTICLE_OBJECT_DATA_ROTATION_VELOCITY		,				//	ȸ�� �ӵ�
	PARTICLE_OBJECT_DATA_ROTATION				,				//	����
	PARTICLE_OBJECT_DATA_ALPHA					,				//	�����
	PARTICLE_OBJECT_DATA_MAGNET_POINT			,				//	�ڼ� ������
	PARTICLE_OBJECT_DATA_RED					,				//	COLOR ����
	PARTICLE_OBJECT_DATA_GREEN					,				//	COLOR ���
	PARTICLE_OBJECT_DATA_BLUE					,				//	COLOR �Ķ�
	PARTICLE_OBJECT_DATA_COUNT					,
};

struct SPFXGroup
{
	SPID_FX_GROUP			FXGroupID;
	std::vector<UINT>		vFXID;
};

typedef std::map< float , float >																STD_MAP_PARTICLE_VALUE;
typedef std::pair< STD_MAP_PARTICLE_VALUE::iterator , STD_MAP_PARTICLE_VALUE::iterator >		STD_PAIR_PARTICLE_VALUE;

#ifndef GetRandom
#define GetRandom(X)						( (float)(X) * rand() / ( RAND_MAX ) )
#endif

// ���� ���Ϲ��� [2/14/2006 AJJIYA]
struct SPFXFrameData
{
	FLOAT		fFrameTime;			// �� �������� Delay.
	FLOAT		fFrameDegree;		// �� �������� ȸ����.
	FLOAT		fFrameScaleX;		// �� �������� Scale X.
	FLOAT		fFrameScaleY;		// �� �������� Scale Y.
	RECT		RectSrc;			// �� �������� �ؽ��ļҽ�.
	RECT		RectAdjust;			// �� �������� ����Ÿ���� ��ġ������ top, left�� ��.	��ƼŬ���� ������ ȸ�� ���� ����Ʈ�� ��� Left , Top , ���������� ������ Bottom �� �� ������ üũ.
	D3DXCOLOR	FrameColor;			// �� �������� �÷�.
	bool		bLRSwap;			// �¿��� ������

	SPFXFrameData() 
		: fFrameTime(0.0f)
		, fFrameDegree(0.0f)
		, fFrameScaleX(0.0f)
		, fFrameScaleY(0.0f)
		, FrameColor(1.0f, 1.0f, 1.0f, 1.0f)
		, bLRSwap(false)
	{
		ZeroMemory(&RectSrc,		sizeof(RECT));
		ZeroMemory(&RectAdjust,		sizeof(RECT));
	}

	void SetNull()
	{
		fFrameTime		=	(0.0f);
		fFrameDegree	=	(0.0f);
		fFrameScaleX	=	(0.0f);
		fFrameScaleY	=	(0.0f);
		FrameColor		=	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		bLRSwap			=	false;
		ZeroMemory(&RectSrc,		sizeof(RECT));
		ZeroMemory(&RectAdjust,		sizeof(RECT));
	}

	void operator=(const SPFXFrameData Src)
	{
		fFrameTime		= Src.fFrameTime;
		fFrameDegree	= Src.fFrameDegree;
		fFrameScaleX	= Src.fFrameScaleX;
		fFrameScaleY	= Src.fFrameScaleY;
		RectSrc			= Src.RectSrc;
		RectAdjust		= Src.RectAdjust;
		FrameColor		= Src.FrameColor;
		bLRSwap			= Src.bLRSwap;
	}
};

// 2.0 ���� [2/14/2006 AJJIYA]
struct SPFXFrameData20
{
	FLOAT		fFrameTime;			// �� �������� Delay.
	FLOAT		fFrameDegree;		// �� �������� ȸ����.
	FLOAT		fFrameScale;		// �� �������� Scale.
	RECT		RectSrc;			// �� �������� �ؽ��ļҽ�.
	RECT		RectAdjust;			// �� �������� ����Ÿ���� ��ġ������ top, left�� ��.
	D3DXCOLOR	FrameColor;			// �� �������� �÷�.
	bool		bLRSwap;			// �¿��� ������

	SPFXFrameData20() 
		: fFrameTime(0.0f)
		, fFrameDegree(0.0f)
		, fFrameScale(0.0f)
		, FrameColor(1.0f, 1.0f, 1.0f, 1.0f)
		, bLRSwap(false)
	{
		ZeroMemory(&RectSrc,		sizeof(RECT));
		ZeroMemory(&RectAdjust,		sizeof(RECT));
	}

	void SetNull()
	{
		fFrameTime		=	(0.0f);
		fFrameDegree	=	(0.0f);
		fFrameScale		=	(0.0f);
		FrameColor		=	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		bLRSwap			=	false;
		ZeroMemory(&RectSrc,		sizeof(RECT));
		ZeroMemory(&RectAdjust,		sizeof(RECT));
	}

	void operator=(const SPFXFrameData20 Src)
	{
		fFrameTime		= Src.fFrameTime;		
		fFrameDegree	= Src.fFrameDegree;	
		fFrameScale		= Src.fFrameScale;	
		RectSrc			= Src.RectSrc;		
		RectAdjust		= Src.RectAdjust;		
		FrameColor		= Src.FrameColor;
		bLRSwap			= Src.bLRSwap;
	}
};

//////////////////////////////////////////////////////////////////////////
//	Particle FX Model ������

struct SPFXParticleFrameData
{
	FLOAT		fFrameTime;			// �� �������� Delay.
	FLOAT		fFrameDegree;		// �� �������� ȸ����.
	RECT		RectArea;			// �� �������� ����.
	FLOAT		fCreateTime;		// �� �������� �߻� �ð�.
	int			iCreateCount;		// �� �������� �߻� ����.
	int			iMagnetPosX;		// �� �������� �ڼ������� X
	int			iMagnetPosY;		// �� �������� �ڼ������� Y

	SPFXParticleFrameData() 
		: fFrameTime(0.0f)
		, fFrameDegree(0.0f)
		, fCreateTime(0.0f)
		, iCreateCount(0)
		, iMagnetPosX(0)
		, iMagnetPosY(0)
	{
		ZeroMemory(&RectArea,		sizeof(RECT));
	}

	void SetNull()
	{
		fFrameTime		=	(0.0f);
		fFrameDegree	=	(0.0f);
		fCreateTime		=	(0.0f);
		iCreateCount	=	0;
		iMagnetPosX		=	0;
		iMagnetPosY		=	0;
		ZeroMemory(&RectArea,		sizeof(RECT));
	}

	void operator=(const SPFXParticleFrameData Src)
	{
		fFrameTime		= Src.fFrameTime;
		fFrameDegree	= Src.fFrameDegree;
		RectArea		= Src.RectArea;
		fCreateTime		= Src.fCreateTime;
		iCreateCount	= Src.iCreateCount;
		iMagnetPosX		= Src.iMagnetPosX;
		iMagnetPosY		= Src.iMagnetPosY;
	}
};

struct SPFXStreamPartcleData {		// AJJIYA Ver.Now!!! [9/28/2006 AJJIYA]
public:
	SPFX_PARTICLE_AREA_TYPE		m_eAreaType;
	BOOL						m_bPathRotation;

	SPFXStreamPartcleData()
	{
		m_eAreaType			=	SPFX_PARTICLE_AREA_NULL;
		m_bPathRotation		=	FALSE;
	}
};

struct SPFXStreamPartcleData21 {		// AJJIYA Ver2.1 [9/28/2006 AJJIYA]
public:
	int			iMaxRenderCount;
	int			iMaxCount;
	int			iMove;
	float		fDelayTime;
	float		fRadianDegree;
	float		fScale;
	D3DXCOLOR	cRGBA;
	RECT		rtSrc;
	RECT		rtAdjust;

	SPFXStreamPartcleData21()
	{
		iMaxRenderCount	=	0;
		iMaxCount		=	0;
		iMove			=	0;
		fDelayTime		=	0.0f;
		fRadianDegree	=	0.0f;
		fScale			=	0.0f;
		cRGBA			=	D3DXCOLOR( 0.0f , 0.0f , 0.0f , 0.0f );
		SetRect( &rtSrc		, 0 , 0 , 0 , 0 );
		SetRect( &rtAdjust	, 0 , 0 , 0 , 0 );
	}
};

#endif
