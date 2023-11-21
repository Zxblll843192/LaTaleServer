
#include <vector>

//
//	2005. 4. 25.	AJJIYA
//	ĳ���� ���� ȣȯ�� ���� ���ȭ�� ����
//	Start
#ifdef _LATALE_CLIENT
#include "SPCommon.h"
#include "SPGameObject.h"
#include "SPManager.h"
#else 
#include "SPToolCommon.h"
#include "SPGameMessageDEF.H"
#endif
//	End

#include "SPUtil.h"
#include "SPResourceDef.h"

#include "SPGameObjectDEF.h"

#include "SPRenderModelDEF.h"
#include "SPRenderModel.h"

#include "SPFXDEF.h"
#include "SPRenderModel.h"
#include "SPFXModel.h"

#include "SPFXModelParticle.h"

//////////////////////////////////////////////////////////////////////////

SPFXModelParticle::SPFXModelParticle()
{
	Init();	
}

SPFXModelParticle::~SPFXModelParticle()
{
	Destroy();
}

void SPFXModelParticle::SetNull()
{
	SPFXModel::SetNull();

	m_eAreaType			=	SPFX_PARTICLE_AREA_NULL;

	m_iFrameCount		=	0;
	m_iImageFrameCount	=	0;

	m_bPathFollow		=	false;
}

void SPFXModelParticle::Init()
{	
	SPFXModel::Init();
	m_ClassID = FX_MODEL_CLASS_PARTICLE;
}

void SPFXModelParticle::Destroy()
{
	SPFXModel::Destroy();
	SAFE_RELEASE( m_pFrameImage );

	std::vector<SPFXParticleFrameData*>::iterator ParticleIter = m_vpFrameData.begin();	
	for(;ParticleIter != m_vpFrameData.end(); ++ParticleIter) {
		SAFE_DELETE(*ParticleIter);
	}
	m_vpFrameData.clear();

	std::vector<SPFXFrameData*>::iterator Iter = m_vpImageFrameData.begin();	
	for(;Iter != m_vpImageFrameData.end(); ++Iter) {
		SAFE_DELETE(*Iter);
	}
	m_vpImageFrameData.clear();

	SetNull();
}

bool SPFXModelParticle::SetImage(SPTexture** ppImage)
{
	m_pFrameImage = *ppImage;
	return true;
}

LRESULT SPFXModelParticle::GetMemberValue(MODEL_VALUE_TYPE mvMsg, LPARAM lParam)
{
	switch(mvMsg) {
	case MV_GETINITIMAGE:
	case MV_GETIMAGE:
		return (LRESULT)&m_pFrameImage;

	case MV_GET_MAXFRAME:
		return m_iFrameCount;

	case MV_PUSHBACK_FRAMEDATA:
		{			
			if(lParam) {			
				SPFXParticleFrameData* pFrameData = new SPFXParticleFrameData();
				(*pFrameData) = *((SPFXParticleFrameData*)lParam);				
				m_vpFrameData.push_back(pFrameData);
				m_iFrameCount = (int)m_vpFrameData.size();
				return TRUE;
			}
			return FALSE;
		}

	case MV_GET_FRAMEDATA:
		{
			int	iPage	=	(int)lParam;
			if(iPage >= 0 && iPage < (int)m_vpFrameData.size()) {
				return (LRESULT)(m_vpFrameData[ iPage ]);
			}
			return NULL;
		}

	case MV_SET_PARTICLE_AREA_TYPE:
		m_eAreaType = (SPFX_PARTICLE_AREA_TYPE)lParam;
		break;
	case MV_GET_PARTICLE_AREA_TYPE:
		return (LRESULT)m_eAreaType;

	case MV_SET_PARTICLE_ITEM_TYPE:
		m_eDataType = (SPFX_PARTICLE_DATA_TYPE)lParam;
		break;
	case MV_SET_PARTICLE_ITEM_DATA:
		{
			STD_MAP_PARTICLE_VALUE*	pmValueData	=	(STD_MAP_PARTICLE_VALUE*)lParam;
			m_mValueData[ m_eDataType ]	=	 *pmValueData;
		}
		break;
	case MV_GET_PARTICLE_ITEM_DATA:
		{
			SPFX_PARTICLE_DATA_TYPE	eDataType	=	(SPFX_PARTICLE_DATA_TYPE)lParam;
			return (LRESULT)&m_mValueData[ eDataType ];
		}
	case MV_SET_PARTICLE_OBJECT_ITEM_TYPE:
		m_eObjectDataType = (SPFX_PARTICLE_OBJECT_DATA_TYPE)lParam;
		break;
	case MV_SET_PARTICLE_OBJECT_ITEM_DATA:
		{
			STD_MAP_PARTICLE_VALUE*	pmObjectValueData	=	(STD_MAP_PARTICLE_VALUE*)lParam;
			m_mObjectValueData[ m_eObjectDataType ]	=	 *pmObjectValueData;
		}
		break;
	case MV_GET_PARTICLE_OBJECT_ITEM_DATA:
		{
			SPFX_PARTICLE_OBJECT_DATA_TYPE	eObjectDataType	=	(SPFX_PARTICLE_OBJECT_DATA_TYPE)lParam;
			return (LRESULT)&m_mObjectValueData[ eObjectDataType ];
		}
	case MV_GET_PARTICLE_IMAGE_FRAMEDATA_COUNT:
		return m_iImageFrameCount;

	case MV_SET_PARTICLE_PUSHBACK_IMAGE_FRAMEDATA:
		{			
			if(lParam) {			
				SPFXFrameData* pFrameData = new SPFXFrameData();
				(*pFrameData) = *((SPFXFrameData*)lParam);				
				m_vpImageFrameData.push_back(pFrameData);
				m_iImageFrameCount = (int)m_vpImageFrameData.size();
				return TRUE;
			}
			return FALSE;
		}

	case MV_GET_PARTICLE_IMAGE_FRAMEDATA:
		{
			int	iPage	=	(int)lParam;
			if(iPage >= 0 && iPage < (int)m_vpImageFrameData.size()) {
				return (LRESULT)(m_vpImageFrameData[iPage]);
			}
			return NULL;
		}
	case MV_SET_PARTICLE_PATH_FOLLOW:
		{
			m_bPathFollow		=	(BOOL)lParam;
		}
		break;
	case MV_GET_PARTICLE_PATH_FOLLOW:
		{
			return	(LRESULT)m_bPathFollow;
		}

	}
	return SPFXModel::GetMemberValue(mvMsg, lParam);
}

//////////////////////////////////////////////////////////////////////////
//
//	FX Model Version 2.1 �϶� ��� �ϴ� Ŭ����
//
/*
SPFXModelParticle21::SPFXModelParticle21(SPID_FX ID, float fDelay)
: SPFXModel(ID)
{
	Init();	
	m_fNextAnimation = fDelay;	
}

SPFXModelParticle21::~SPFXModelParticle21()
{
	Destroy();
}

void SPFXModelParticle21::SetNull()
{
	SPFXModel::SetNull();

	m_fRotation	= 0.0f;			// �� �������� ȸ����.	
	m_fScale	= 1.0f;			// ������

	ZeroMemory(&m_RectSrc,		sizeof(RECT));			// �� �������� �ؽ��ļҽ�
	ZeroMemory(&m_RectSize,		sizeof(RECT));			// �� �������� ����Ÿ��

	m_iMaxRenderParticle	= 0;		// �ִ� �׸��� �ִ� ��
	m_iMaxParticle			= 0;		// � ���� �ﱸ ������

	m_RGBA					= 0xffffffff;	// �÷�

	m_ParticleMove = PARTICLE_NULL;			// � ��ƼŬ ������
}

void SPFXModelParticle21::Init()
{	
	SPFXModel::Init();
	m_ClassID = FX_MODEL_CLASS_PARTICLE;	
}

void SPFXModelParticle21::Destroy()
{
	SPFXModel::Destroy();
	SAFE_RELEASE(m_pFrameImage);
	SetNull();
}

bool SPFXModelParticle21::SetImage(SPTexture** ppImage)
{
	m_pFrameImage = *ppImage;
	return true;
}

LRESULT SPFXModelParticle21::GetMemberValue(MODEL_VALUE_TYPE mvMsg, LPARAM lParam)
{
	switch(mvMsg) {
	case MV_GETINITIMAGE:
	case MV_GETIMAGE:
		return (LRESULT)&m_pFrameImage;

	case MV_PUSHBACK_COLOR:
		m_RGBA = *(D3DXCOLOR*)lParam;
		return TRUE;

	case MV_PUSHBACK_SCALE:
		m_fScale = *(float*)lParam;
		return TRUE;

	case MV_PUSHBACK_ADJUST:
		m_RectSize = *(RECT*)lParam;
		OffsetRect(&m_RectSize, -(m_RectSize.right/2), -(m_RectSize.bottom/2));
		return TRUE;

	case MV_PUSHBACK_SRC_RECT:
		m_RectSrc = *(RECT*)lParam;
		return TRUE;

	case MV_GET_COLOR:	
		return (LRESULT)&(m_RGBA);

	case MV_GET_RADIANDEGREE:		
		return (LRESULT)&(m_fRotation);

	case MV_GET_SRC_RECT:
		return (LRESULT)&(m_RectSrc);

	case MV_GET_ADJUST:
		return (LRESULT)&m_RectSize;

	case MV_PUSHBACK_MAXRENDERPARTICLE:
		m_iMaxRenderParticle = (int)lParam;	// �ִ� �׸��� �ִ� ��
		return TRUE;

	case MV_PUSHBACK_MAXPARTICLE:	
		m_iMaxParticle = (int)lParam;		// � ���� �ﱸ �����ų� 0�̸� �׻� m_iMaxRenderParticle�� ��´�.
		return TRUE;

	case MV_SET_RADIANDEGREE:
		m_fRotation = ( *(float*)lParam );
		return TRUE;

	case MV_SET_PARTICLE_MOVE:
		m_ParticleMove = (SPFX_PARTICLE_MOVE)lParam;
		return TRUE;		

	case MV_PUSHBACK_FACTOR:
		m_vec4ParticleFactor = *(D3DXVECTOR4*)lParam;
		return TRUE;

	case MV_GET_MAXRENDERPARTICLE:
		return m_iMaxRenderParticle;

	case MV_GET_MAXPARTICLE:
		return m_iMaxParticle;

	case MV_GET_SCALE:
		return (LRESULT)&(m_fScale);

	case MV_GET_FACTOR:
		return (LRESULT)&m_vec4ParticleFactor;

	case MV_GET_PARTICLE_MOVE:
		return m_ParticleMove;

	}
	return SPFXModel::GetMemberValue(mvMsg, lParam);
}
*/