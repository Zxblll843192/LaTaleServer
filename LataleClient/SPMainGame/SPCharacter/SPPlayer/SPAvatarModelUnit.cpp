#include <algorithm>
#include <functional>
#include <string>
#include <vector>

// Modify by kkandori (11.9. 2004)
#ifdef _LATALE_CLIENT
	#include "SPCommon.h"
	#include "SPGOBClusterDEF.h"
	#include "SPAvatarModelUnitDef.h"
	#include "SPGOBAnimation.h"
	#include "SPGOBModel.h"
	//#include "SPDebug.h"

#else 
	#include "SPToolCommon.h"
	#include "SPGameObjectDef.h"
	#include "SPGameMessageDEF.H"
	#include "SPRenderModelDef.h"	
	#include "SPGOBClusterDEF.h"
	#include "SPAvatarModelUnitDef.h"

	#include "SPGameObjectToolCustom.h"
	#include "SPGOBAnimation.h"
	#include "SPGOBModel.h"
#endif
// Modify End

#include "SPGOBCluster.h"

#include "SPRenderModelDEF.h"

#include "SPGameObjectDef.h"


#ifdef _LATALE_CLIENT
	#include "SPGameObject.h"
#endif

#include "SPAvatarModelUnitDef.h"
#include "SPGOBModelUnit.h"
#include "SPAvatarModelUnit.h"

#include "SPUtil.h"

using namespace std;
struct _IsEqualInfoSeqPartFromPartLayer : binary_function<SPGOBInfoSequencePart, PART_LAYER, bool> {
	bool operator() (const SPGOBInfoSequencePart& GOBPart, PART_LAYER PartLayer) const
	{		
		return (GOBPart.PartLayer == PartLayer);
	}
} IsEqualInfoSeqPartFromPartLayer;

SPAvatarModelUnit::SPAvatarModelUnit(SPGameObject* pParent)
: SPGOBModelUnit(pParent, GOB_MODEL_AVATAR)
, m_fRenderPosX(0.0f)
, m_fRenderPosY(0.0f)
, m_fBeforeRenderPosX(0.0f)
, m_fBeforeRenderPosY(0.0f)
, m_bMustQuery(false)
, m_bAnimationLoop(true)
{
	m_pGOBModel = new SPGOBModel();
	m_pGOBForceModel = new SPGOBModel();
	m_strImagePath = new TCHAR[256];
	m_strImagePath[0] = '\0';
	Init();
}

SPAvatarModelUnit::~SPAvatarModelUnit()
{
	SAFE_DELETE(m_pGOBModel);
	SAFE_DELETE(m_pGOBForceModel);
	SAFE_DELETE_ARRAY(m_strImagePath);	
}

void SPAvatarModelUnit::Init()
{	
	m_uiLastAniInx	= 
	m_uiAniInx		= 0;

	m_fAccumulateAction				=
	m_fAccumulateRenderTime			= 
	m_fAccumulateEffectFaceRender	= 
	m_fNextEffectFaceRender			= 0.0f;

	m_iSeqFace = 0;
	m_iCurAniFrame = 0;
	m_iBeforeFaceIndex = 0;
	m_bBeforeFaceFlip = false;
	m_iTransparency = 0;
	m_fTransparencyValue = 1.0f;
	m_fTransparencyAccmulateTime = 0.0f;
	m_bAllLayerProcess = false;
	m_bPartLayerChange = false;
	m_colorPhantom = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}

void SPAvatarModelUnit::FrameInit()	
{ 
	m_iCurAniFrame = 0; 
	m_bMustQuery = true;
	m_pGOBModel->fDelayTime = 0.0f;
}


LRESULT SPAvatarModelUnit::SPSendMessage(MODEL_VALUE_TYPE mvMsg, WPARAM wParam, LPARAM lParam)
{
	switch(mvMsg) {
	case MV_FRAMEINIT:				
		FrameInit();						
		return 0;

	case MV_GET_ACCUMUL_ACTION:			
		LRESULT	res;		
		DataConvert<float, LRESULT>(GetAccumulateAction(), res);		// Data Convert!!!
		return res;

	case MV_SET_ACCUMUL_ACTION:	
		float fAccTime;
		DataConvert<WPARAM,float>(wParam, fAccTime);		// Data Convert!!!
		SetAccumulateAction	(fAccTime);
		return 0;

	case MV_SET_ANIMATION_INDEX:	
		SetAnimationIndex(wParam);		
		return 0;
		
	case MV_SET_ANI_LOOP:
		SetAnimationLoop((bool)wParam);
		return 0;

	case MV_GET_CURR_FRAME:
		return (LRESULT)m_iCurAniFrame;

	case MV_GET_ANIMATION_INDEX:
		return (LRESULT) m_uiAniInx;

	case MV_GET_ANI_ACCUMUL_TIME:
		{
			float fTime = GetAniAccumulateTime();
			*((float*)wParam) = fTime;
		}
		return 0;

	case MV_SET_RENDERPOSX:			
		{			
			DataConvert<WPARAM,float>(wParam, m_fRenderPosX);			
			return 0;
		}
	case MV_SET_RENDERPOSY:			
		{			
			DataConvert<WPARAM,float>(wParam, m_fRenderPosY);			
			return 0;
		}

	case MV_SET_EQUIPLAYERPOOL:	
		{					
			return SetPartLayerInfo( (SPEquipLayerPool*)wParam, (PART_LAYER)lParam );
		}
		
	case MV_SET_PARTCHANGE:
		{
			m_pGOBModel->bPCEnable = ((BOOL)wParam ? true : false);
		}
		return 0;

	case MV_SET_TRANSPARENCY:
		{
			if( wParam )
				m_iTransparency++;
			else
				m_iTransparency--;

			if( m_iTransparency < 0 )
				m_iTransparency = 0;
		}
		return 0;

	case MV_SET_ALLLAYER_PROCESS:
		{
			if( wParam )
				m_bAllLayerProcess = true;
			else
				m_bAllLayerProcess = false;
		}
		return 0;

	case MV_COPY_PART_LAYER:
		{
			SPAvatarModelUnit* pkDstModelUnit = reinterpret_cast<SPAvatarModelUnit*>(wParam);
			if( pkDstModelUnit == NULL )
				return 0;
			
			for( int i = 0; i < PL_LAST; i++ )
			{
				pkDstModelUnit->m_pGOBModel->PartModel[i].PartLayer = m_pGOBModel->PartModel[i].PartLayer;
				pkDstModelUnit->m_pGOBModel->PartModel[i].EquipClass = m_pGOBModel->PartModel[i].EquipClass;
				pkDstModelUnit->m_pGOBModel->PartModel[i].iItemID = m_pGOBModel->PartModel[i].iItemID;
				pkDstModelUnit->m_pGOBModel->PartModel[i].iColor = m_pGOBModel->PartModel[i].iColor;
				pkDstModelUnit->m_pGOBModel->PartModel[i].pPartImage = m_pGOBModel->PartModel[i].pPartImage;
				if( pkDstModelUnit->m_pGOBModel->PartModel[i].pPartImage )
					pkDstModelUnit->m_pGOBModel->PartModel[i].pPartImage->IncreaseRef();

#if defined(_USED_TEXTURE_TABLE)
				pkDstModelUnit->m_pGOBModel->PartModel[i].pTableInfo = m_pGOBModel->PartModel[i].pTableInfo;
#endif
			}
			
		}
		return 0;
	}
	return SPGOBModelUnit::SPSendMessage(mvMsg, wParam, lParam);
}

void SPAvatarModelUnit::Process(float fTime)
{
	ProcessImageLayer(m_fRenderPosX, m_fRenderPosY, fTime );

	if( m_iTransparency )
	{
		if( m_fTransparencyValue > 0.5f )
		{
			m_fTransparencyAccmulateTime += fTime;
			m_fTransparencyValue = 1.0f - m_fTransparencyAccmulateTime;
			if( m_fTransparencyValue < 0.5f )
			{
				m_fTransparencyValue = 0.5f;
				m_fTransparencyAccmulateTime = 0.0f;
			}
		}
	}
	else
	{
		if( m_fTransparencyValue < 1.0f )
		{
			m_fTransparencyAccmulateTime += fTime;
			m_fTransparencyValue = 0.5f + m_fTransparencyAccmulateTime;
			if( m_fTransparencyValue > 1.0f )
			{
				m_fTransparencyValue = 1.0f;
				m_fTransparencyAccmulateTime = 0.0f;
			}
		}
	}

	m_fBeforeRenderPosX = m_fRenderPosX;
	m_fBeforeRenderPosY = m_fRenderPosY;
}

void SPAvatarModelUnit::ProcessImageLayer(const float fRenderPosX, const float fRenderPosY, float fTime )
{
	bool bAnimateFace = false;

	m_fAccumulateEffectFaceRender += fTime;
	m_fAccumulateRenderTime += fTime;

#ifndef _CHARTOOL
	//if(m_fAccumulateEffectFaceRender > ACCUMULATE_TIME_LIMIT)
	//	m_fAccumulateEffectFaceRender = ACCUMULATE_TIME_LIMIT;
	if(m_fAccumulateEffectFaceRender > 6.0f)
		m_fAccumulateEffectFaceRender = 6.0f;


	//if(m_fAccumulateRenderTime > ACCUMULATE_TIME_LIMIT)
	//	m_fAccumulateRenderTime = ACCUMULATE_TIME_LIMIT;

#elif _CHARTOOL
	if(fTime==0)
	{		
		m_fAccumulateRenderTime = 0 ; 
	}
#endif

	bool bChangeSuq = false;
	if(m_bMustQuery || m_fAccumulateRenderTime >= m_pGOBModel->fDelayTime) {

		if(m_uiLastAniInx != m_uiAniInx) {
			//m_fNextEffectFaceRender = 0.f;
		}

		bAnimateFace = true;
		if( m_fAccumulateRenderTime >= m_pGOBModel->fDelayTime )
		{
			m_fAccumulateRenderTime -= m_pGOBModel->fDelayTime;
			m_fAccumulateAction -= m_pGOBModel->fDelayTime;
		}

		//m_fAccumulateRenderTime = 0.0f;
		//m_fAccumulateAction = 0.0f;

		// Ŭ���̾�Ʈ���� ���� ����Ʈ �ִϸ��̼����� �ݵ�� ����ȴ�.�ƴ� ASSERT
		bool bWeaponVisible = (GetParent()->SPGOBPerformMessage( SPGM_GETWEAPONVISIBLE ) == 1);
		if( g_pGOBCluster )
			g_pGOBCluster->QueryAnimationSequence(&m_pGOBModel, m_uiAniInx, m_iCurAniFrame, m_bAnimationLoop, bWeaponVisible);

		m_uiLastAniInx = m_uiAniInx;
		m_bMustQuery = false;
		bChangeSuq = true;
	}

	SetRect(&m_rcRenderRgn, 0, 0, 0, 0);
	
	bool bOnlyFacing = true;
#ifdef _CHARTOOL
	FACING Dir = GetParent()->GetDirection();
	bOnlyFacing = false;
#else
	FACING Dir = (FACING)GetParent()->SPGOBPerformMessage( SPGM_GETFACING );
	if( m_bAllLayerProcess )
		bOnlyFacing = false;
	else
	{
		if( m_bPartLayerChange || bChangeSuq || m_iBeforeFacing != Dir ||
			m_fRenderPosX != m_fBeforeRenderPosX || m_fRenderPosY != m_fBeforeRenderPosY )
		{
			bOnlyFacing = false;
			m_bPartLayerChange = false;
		}
	}
#endif

#if defined(_USED_TEXTURE_TABLE)
	SetLayerPosbyTable(m_pGOBModel, (int)fRenderPosX, (int)fRenderPosY, Dir, bAnimateFace, true, bOnlyFacing);
#else
	SetLayerPos(m_pGOBModel, (int)fRenderPosX, (int)fRenderPosY, Dir, bAnimateFace, true, bOnlyFacing);
#endif

	m_iBeforeFacing = Dir;
	m_fBeforeRenderPosX = m_fRenderPosX;
	m_fBeforeRenderPosY = m_fRenderPosY;
}

void SPAvatarModelUnit::SetLayerPos(SPGOBModel* pGOBModel, int iPosX, int iPosY,
	FACING eFacing, bool bAnimateFace, bool bMainProcess, bool bOnlyFacing)
{
	std::vector<SPGOBInfoSequencePart>::iterator Iter, Iter2;
	RECT* pRect;
	int iIndex = 0;

	//SPGOBAniSeqPart�� ���ҽ� �ε����� �����Ͽ�, SPGOBModelPart�� ���ҽ���Ʈ�� �����Ѵ�.
	int PartLayer = PL_FIRST;
	if( bOnlyFacing )
		PartLayer = PL_FACE;

	for(; PartLayer < PL_LAST; ++PartLayer) {
		if(pGOBModel->PartModel[PartLayer].isNull()){
			if( bOnlyFacing )
				return;

			continue;
		}

		Iter = std::find_if(pGOBModel->vGOBInfoSequencePart.begin(), pGOBModel->vGOBInfoSequencePart.end(), 
			std::bind2nd(IsEqualInfoSeqPartFromPartLayer, (PART_LAYER)PartLayer));
		if( Iter == pGOBModel->vGOBInfoSequencePart.end()) {
			//assert(0 && "�ִϸ��̼� �������� ���ϴ� ��Ʈ ���̾ ã���� �����ϴ�.");
			continue;
		}

		pRect = &(pGOBModel->PartModel[PartLayer].SrcRect);

		bool bFacingSet = false;
		switch(PartLayer) {
			// �������� ���̾� ��Ʈ ��
		default:			
			GetResIndexRect((PART_LAYER)PartLayer, (*Iter).iResourceIndex, *pRect);
			break;	

			// ���������� ���̾� ��Ʈ ��
		case PL_WEAPON_OUT:
			{
				iIndex = (*Iter).iResourceIndex;
				EQUIP_CLASS eClassType = pGOBModel->PartModel[PartLayer].EquipClass;
				if( eClassType == EQCLASS_0802 || eClassType == EQCLASS_0803 ||
					eClassType == EQCLASS_0804 || eClassType == EQCLASS_0807 ||
					eClassType == EQCLASS_0812 )
				{
					if( iIndex == 2 )
						iIndex = 1;
				}
				else if( eClassType == EQCLASS_0808 )
				{
					if( iIndex == 2 || iIndex == 3 )
						iIndex = 1;
				}
				GetResIndexRect((PART_LAYER)PartLayer, iIndex, *pRect);
			}
			break;
			
		case PL_COAT:
			{
				iIndex = (*Iter).iResourceIndex;
				if( iIndex == 3 || iIndex == 4 || iIndex == 5 )
					iIndex = 2;

				GetResIndexRect((PART_LAYER)PartLayer, iIndex, *pRect);
			}
			break;

		case PL_HAIR_FRONT:
			{
				if( pGOBModel->PartModel[PL_HEAD].isNull() )
					continue;

				Iter2 = std::find_if(pGOBModel->vGOBInfoSequencePart.begin(), pGOBModel->vGOBInfoSequencePart.end(), 
					std::bind2nd(IsEqualInfoSeqPartFromPartLayer, PL_HEAD));
				if( Iter2 == pGOBModel->vGOBInfoSequencePart.end() )
					continue;

				iIndex = (*Iter2).iResourceIndex;
				if( iIndex > 2 )
					iIndex += 5;

#if defined(_CHARTOOL)
				if( (*Iter).iResourceIndex > 12 )
					iIndex += 12;
#else
				if( pGOBModel->bPCEnable )
					iIndex += 12;
#endif
				GetResIndexRect((PART_LAYER)PartLayer, iIndex, *pRect);
	
				//iIndex = (*Iter).iResourceIndex;

				//iIndex = (*Iter).iResourceIndex;
				//if( (*Iter).iResourceIndex == 3 || (*Iter).iResourceIndex == 4 )
				//	iIndex = 2;
				//else if( (*Iter).iResourceIndex == 6 || (*Iter).iResourceIndex == 7 )
				//	iIndex = 5;

				//// PL_HAIR_FRONT�� PartChange �ϰ��� �ε����� �ٲٿ��־�� �Ѵ�.
				//if(pGOBModel->bPCEnable)
				//	GetResIndexRect((PART_LAYER)PartLayer, iIndex + 12, *pRect);
				//else
				//	GetResIndexRect((PART_LAYER)PartLayer, iIndex, *pRect);
			}
			break;

		case PL_HAIR_REAR:
			{
				iIndex = (*Iter).iResourceIndex;
				if( (*Iter).iResourceIndex == 2 || (*Iter).iResourceIndex == 3 )
					iIndex = 1;
				else if( (*Iter).iResourceIndex == 5 || (*Iter).iResourceIndex == 6 )
					iIndex = 4;
				else if( (*Iter).iResourceIndex == 8 || (*Iter).iResourceIndex == 9 )
					iIndex = 7;
				else if( (*Iter).iResourceIndex == 14 )
					iIndex = 13;

				GetResIndexRect((PART_LAYER)PartLayer, iIndex, *pRect);
			}
			break;

		case PL_FACE:
			// ��ǥ��
			// �޾ƿ� �ִϸ��̼ǵ���Ÿ�� �̿��Ͽ� ���� �� �ٽ� �޴´�.
			// �ϵ��ڵ��Ҽ� �ۿ� ����..��

			if( bMainProcess )
			{
				// 1���̳� 4���� ���ڰŸ��� �ε�����..
				// �׷��� m_fAccumulateEffectFaceRender�� üũ�ؼ� ���� �ִϸ��̼ǰ� ��� ���� �ٲ۴�.
				if((*Iter).iResourceIndex == 1 || (*Iter).iResourceIndex == 4)
				{
					bool bChangeRect = false;
					if( m_fAccumulateEffectFaceRender > m_fNextEffectFaceRender )
						bChangeRect = true;
					if( bAnimateFace )
					{
						if( (m_iBeforeFaceIndex != (*Iter).iResourceIndex) ||
							(m_bBeforeFaceFlip != (*Iter).bFlip) )
						{
							bChangeRect = true;
							m_iBeforeFaceIndex = (*Iter).iResourceIndex;
							m_iSeqFace = 0;
							m_bBeforeFaceFlip = (*Iter).bFlip;
						}
					}

					if( bChangeRect )
					{
						// �ϵ��ڵ��Ҽ� �ۿ� ����..��
						switch((*Iter).iResourceIndex)
						{
						case 1: // ��� - 1~3������ �ִϸ��̼�
							GetResIndexRect((PART_LAYER)PartLayer, (*Iter).iResourceIndex+m_iSeqFace, *pRect);
							bFacingSet = true;
							break;
						case 4: // ���� - 4~6������ �ִϸ��̼�
							GetResIndexRect((PART_LAYER)PartLayer, (*Iter).iResourceIndex+m_iSeqFace, *pRect);
							bFacingSet = true;
							break;
						}

						if( m_fAccumulateEffectFaceRender > m_fNextEffectFaceRender )
						{
							if(m_iSeqFace == 0) {
								m_fNextEffectFaceRender = 0.1f + (float)(rand()%6) ;
							} else {
								m_fNextEffectFaceRender = 0.1f;
							}

							m_iSeqFace++;		
							if(m_iSeqFace > 2) {
								m_iSeqFace = 0;
							}

							m_fAccumulateEffectFaceRender = 0.0f;
							//m_fAccumulateEffectFaceRender -= m_fNextEffectFaceRender;
						}
					}
					// â������ 80019
				} else {
					// 1���̳� 4���ܿ��� �ִϸ��̼� ������ Ÿ���� �̿��ؼ� �ٲ��ش�
					GetResIndexRect((PART_LAYER)PartLayer, (*Iter).iResourceIndex, *pRect);
					m_iBeforeFaceIndex = (*Iter).iResourceIndex;
					m_iSeqFace = 0;
					bFacingSet = true;
				}
			}
			else
			{	
				GetResIndexRect((PART_LAYER)PartLayer, 1, *pRect);
				bFacingSet = true;
			}
			break;		
		}

		if( (*Iter).bFlip )
		{
			bool bChange = true;
			if( PartLayer == PL_FACE )
				bChange = bFacingSet;

			if( bChange )
			{
				int iTemp;
				iTemp = pRect->left;
				pRect->left = pRect->right;
				pRect->right = iTemp;
			}
		}

		pRect = &(pGOBModel->PartModel[PartLayer].TarRect);

		if(eFacing == FACING_LEFT) {
			pRect->left		= (LONG)(iPosX + ((*Iter).iRX));
			pRect->right	= (LONG)(pRect->left + g_ciCharResIndex[(*Iter).PartLayer][RI_SX]);
			pGOBModel->PartModel[PartLayer].iRotationDegree = (*Iter).iRotationDegree;
		} else {
			pRect->left		= (LONG)(iPosX - ((*Iter).iRX));
			pRect->right	= (LONG)(pRect->left - g_ciCharResIndex[(*Iter).PartLayer][RI_SX]);
			pGOBModel->PartModel[PartLayer].iRotationDegree = -((*Iter).iRotationDegree);
		}
		pRect->top	= iPosY + (*Iter).iRY;
		pRect->bottom = pRect->top	+ g_ciCharResIndex[(*Iter).PartLayer][RI_SY];

		if( PartLayer == PL_HAIR_FRONT && bMainProcess )
			m_rcRenderRgn = *pRect;

		if( bOnlyFacing )
			break;
	}
}

#if defined(_USED_TEXTURE_TABLE)
void SPAvatarModelUnit::SetLayerPosbyTable(SPGOBModel* pGOBModel, int iPosX, int iPosY,
	FACING eFacing, bool bAnimateFace, bool bMainProcess, bool bOnlyFacing)
{
	SPGOBInfoSequencePart* pSeqPart1, *pSeqPart2;
	RECT* pRect;
	TEXTURE_TABLE_INFO* pTableInfo;
	FRAME_INFO* pFrameInfo;
	int iIndex = 0;

	//SPGOBAniSeqPart�� ���ҽ� �ε����� �����Ͽ�, SPGOBModelPart�� ���ҽ���Ʈ�� �����Ѵ�.
	int PartLayer = PL_FIRST;
	if( bOnlyFacing )
		PartLayer = PL_FACE;

	for(; PartLayer < PL_LAST; ++PartLayer) {
		if(pGOBModel->PartModel[PartLayer].isNull()) {
			if( bOnlyFacing )
				return;

			continue;
		}

		if( pGOBModel->PartModel[PartLayer].pTableInfo == NULL )
			continue;

		pGOBModel->PartModel[PartLayer].iRenderType = 0;
		pTableInfo = pGOBModel->PartModel[PartLayer].pTableInfo;
		pSeqPart1 = GetSequencePart(pGOBModel, (PART_LAYER)PartLayer);
			
		if( pSeqPart1 == NULL)
			continue;

		pRect = &(pGOBModel->PartModel[PartLayer].SrcRect);

		pFrameInfo = NULL;
		bool bFacingSet = false;
		switch(PartLayer) {
			// �������� ���̾� ��Ʈ ��
		default:			
			pFrameInfo = GetResIndexRectbyTable(pTableInfo, pSeqPart1->iResourceIndex, *pRect);
			break;		

			// ���������� ���̾� ��Ʈ ��
		case PL_WEAPON_OUT:
			{
				iIndex = pSeqPart1->iResourceIndex;
				EQUIP_CLASS eClassType = pGOBModel->PartModel[PartLayer].EquipClass;
				if( eClassType == EQCLASS_0802 || eClassType == EQCLASS_0803 ||
					eClassType == EQCLASS_0804 || eClassType == EQCLASS_0807 ||
					eClassType == EQCLASS_0812 )
				{
					if( iIndex == 2 )
						iIndex = 1;
				}
				else if( eClassType == EQCLASS_0808 )
				{
					if( iIndex == 2 || iIndex == 3 )
						iIndex = 1;
				}

				pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex, *pRect);
			}
			break;

		case PL_COAT:
			{
				iIndex = pSeqPart1->iResourceIndex;
				if( iIndex == 3 || iIndex == 4 || iIndex == 5 )
					iIndex = 2;

				pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex, *pRect);
			}
			break;

		case PL_HAIR_FRONT:
			{
				if( pGOBModel->PartModel[PL_HEAD].isNull() )
					continue;

				pSeqPart2 = GetSequencePart(pGOBModel, (PART_LAYER)PL_HEAD);
				if( pSeqPart2 == NULL )
					continue;

				iIndex = pSeqPart2->iResourceIndex;
				if( iIndex > 2 )
					iIndex += 5;

				if( pGOBModel->bPCEnable )
					iIndex += 12;
				
				pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex, *pRect);

				//iIndex = (*Iter).iResourceIndex;
				//if( (*Iter).iResourceIndex == 3 || (*Iter).iResourceIndex == 4 )
				//	iIndex = 2;
				//else if( (*Iter).iResourceIndex == 6 || (*Iter).iResourceIndex == 7 )
				//	iIndex = 5;

				//// PL_HAIR_FRONT�� PartChange �ϰ��� �ε����� �ٲٿ��־�� �Ѵ�.
				//if(pGOBModel->bPCEnable)
				//	pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex + 12, *pRect);
				//else
				//	pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex, *pRect);
			}
			break;

		case PL_HAIR_REAR:
			{
				iIndex = pSeqPart1->iResourceIndex;
				if( iIndex == 2 || iIndex == 3 )
					iIndex = 1;
				else if( iIndex == 5 || iIndex == 6 )
					iIndex = 4;
				else if( iIndex == 8 || iIndex == 9 )
					iIndex = 7;
				else if( iIndex == 14 )
					iIndex = 13;

				pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex, *pRect);
			}
			break;

		case PL_FACE:
			// ��ǥ��
			// �޾ƿ� �ִϸ��̼ǵ���Ÿ�� �̿��Ͽ� ���� �� �ٽ� �޴´�.
			// �ϵ��ڵ��Ҽ� �ۿ� ����..��

			// 1���̳� 4���� ���ڰŸ��� �ε�����..
			// �׷��� m_fAccumulateEffectFaceRender�� üũ�ؼ� ���� �ִϸ��̼ǰ� ��� ���� �ٲ۴�.

			if( bMainProcess )
			{
				// 1���̳� 4���� ���ڰŸ��� �ε�����..
				// �׷��� m_fAccumulateEffectFaceRender�� üũ�ؼ� ���� �ִϸ��̼ǰ� ��� ���� �ٲ۴�.
				iIndex = pSeqPart1->iResourceIndex;
				if( iIndex == 1 || iIndex == 4 )
				{
					bool bChangeRect = false;
					if( m_fAccumulateEffectFaceRender > m_fNextEffectFaceRender )
						bChangeRect = true;
					if( bAnimateFace )
					{
						if( (m_iBeforeFaceIndex != iIndex) ||
							(m_bBeforeFaceFlip != pSeqPart1->bFlip) )
						{
							bChangeRect = true;
							m_iBeforeFaceIndex = iIndex;
							m_iSeqFace = 0;
							m_bBeforeFaceFlip = pSeqPart1->bFlip;
						}
					}

					if( bChangeRect )
					{
						// �ϵ��ڵ��Ҽ� �ۿ� ����..��
						switch(iIndex)
						{
						case 1: // ��� - 1~3������ �ִϸ��̼�
							pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex+m_iSeqFace, *pRect);
							bFacingSet = true;
							break;
						case 4: // ���� - 4~6������ �ִϸ��̼�
							pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex+m_iSeqFace, *pRect);
							bFacingSet = true;
							break;
						}

						if( m_fAccumulateEffectFaceRender > m_fNextEffectFaceRender )
						{
							if(m_iSeqFace == 0) {
								m_fNextEffectFaceRender = 0.1f + (float)(rand()%6) ;
							} else {
								m_fNextEffectFaceRender = 0.1f;
							}

							m_iSeqFace++;		
							if(m_iSeqFace > 2) {
								m_iSeqFace = 0;
							}

							m_fAccumulateEffectFaceRender = 0.0f;
							//m_fAccumulateEffectFaceRender -= m_fNextEffectFaceRender;
						}
					}
					// â������ 80019
				} else {

					//////////////////////////////////////////////////////////////////////////
					//WILL ���̾� 2007�� 10����ġ ��������
					//		�׼������� ���� �׽�Ʈ�ؾ���.
					//
					//	PL_HAND_OUT (4,1) -> (4,2)
					//  PL_FACE (8,5) -> (8,10)
					//
					
					// �� �� Ÿ�Ժ����� �ε���
					// 01~10, 12~18

					// �������� ���� �� - ���� X�� �׷����ٴ��� �ϴ�..
					// 2007/10 ���� - 11,19~40
					// 2007/10��ġ���� - 11, 19~80

					// 1���̳� 4���ܿ��� �ִϸ��̼� ������ Ÿ���� �̿��ؼ� �ٲ��ش�					
					//if( iIndex == 11 || (iIndex >= 19 && iIndex <= 40) )
					if( iIndex == 11 || (iIndex >= 19) )
					{
						pTableInfo = pGOBModel->PartModel[PartLayer].pTableInfoReserve;
						pGOBModel->PartModel[PartLayer].iRenderType = 1;
					}
					
					pFrameInfo = GetResIndexRectbyTable(pTableInfo, iIndex, *pRect);
					m_iBeforeFaceIndex = iIndex;
					m_iSeqFace = 0;
					bFacingSet = true;
				}
			}
			else
			{	
				pFrameInfo = GetResIndexRectbyTable(pTableInfo, 1, *pRect);
				bFacingSet = true;
			}
			break;		
		}

		if( PartLayer == PL_FACE )
		{
			if( pFrameInfo )
				pGOBModel->PartModel[PartLayer].pFrameInfo = pFrameInfo;
			else
				pFrameInfo = pGOBModel->PartModel[PartLayer].pFrameInfo;
		}
		else
			pGOBModel->PartModel[PartLayer].pFrameInfo = pFrameInfo;
		
		if( pFrameInfo == NULL )
			continue;
		
		bool bChange = false;
		if( pSeqPart1->bFlip )
		{
			bChange = true;
			//if( PartLayer == PL_FACE )
			//	bChange = bFacingSet;

			if( bChange )
			{
				if( pRect->left < pRect->right )
				{
					int iTemp;
					iTemp = pRect->left;
					pRect->left = pRect->right;
					pRect->right = iTemp;
				}
			}
		}

		pRect = &(pGOBModel->PartModel[PartLayer].TarRect);
		int iSrcWidth, iSrcHeight;
		iSrcWidth = pFrameInfo->rcResourceRgn.right - pFrameInfo->rcResourceRgn.left;
		iSrcHeight = pFrameInfo->rcResourceRgn.bottom - pFrameInfo->rcResourceRgn.top;

		if(eFacing == FACING_LEFT) {
			if( bChange )			// flip
			{
				pRect->left	= (LONG)(iPosX + pSeqPart1->iRX +
					(g_ciCharResIndex[pSeqPart1->PartLayer][RI_SX] - (pFrameInfo->iOffsetX + iSrcWidth)));
			}
			else
				pRect->left	= (LONG)(iPosX + pSeqPart1->iRX + pFrameInfo->iOffsetX);

			pRect->right = (LONG)(pRect->left + iSrcWidth);
			pGOBModel->PartModel[PartLayer].iRotationDegree = pSeqPart1->iRotationDegree;

		} else {
			if( bChange )			// flip
			{
				pRect->left	= (LONG)(iPosX - pSeqPart1->iRX -
					(g_ciCharResIndex[pSeqPart1->PartLayer][RI_SX] - (pFrameInfo->iOffsetX + iSrcWidth)));
			}
			else
				pRect->left	= (LONG)(iPosX - pSeqPart1->iRX - pFrameInfo->iOffsetX);

			pRect->right = (LONG)(pRect->left - iSrcWidth);
			pGOBModel->PartModel[PartLayer].iRotationDegree = -(pSeqPart1->iRotationDegree);
		}
		pRect->top	= iPosY + pSeqPart1->iRY + pFrameInfo->iOffsetY;
		pRect->bottom = pRect->top	+ iSrcHeight;

		/*
		if( bChange )
		{
			if( eFacing == FACING_LEFT )
			{
				pRect->left -= (int)pFrameInfo->fCenterOffsetX;
				pRect->right -= (int)pFrameInfo->fCenterOffsetX;
			}
			else
			{
				pRect->left += (int)pFrameInfo->fCenterOffsetX;
				pRect->right += (int)pFrameInfo->fCenterOffsetX;
			}

			//pRect->top += (int)(pFrameInfo->fCenterOffsetY + (float)iSrcHeight / 2.0f);
			//pRect->bottom += (int)(pFrameInfo->fCenterOffsetY + (float)iSrcHeight / 2.0f);
		}
		*/

		if( PartLayer == PL_HAIR_FRONT && bMainProcess )
			m_rcRenderRgn = *pRect;

		if( bOnlyFacing )
			break;
	}
}
#endif

void SPAvatarModelUnit::ReCalcLayerPos(int iPosXChange, int iPosYChange)
{
	if (!m_pGOBModel)
		return;

	int PartLayer = PL_FIRST;
	RECT *pRect;
	for (; PartLayer < PL_LAST; ++PartLayer)
	{
		if (m_pGOBModel->PartModel[PartLayer].isNull())
			continue;

		if (m_pGOBModel->PartModel[PartLayer].pTableInfo == NULL)
			continue;

		pRect = &(m_pGOBModel->PartModel[PartLayer].TarRect);
		pRect->left += iPosXChange;
		pRect->right += iPosXChange;
		pRect->top += iPosYChange;
		pRect->bottom += iPosYChange;
	}
}


void SPAvatarModelUnit::Render(float fTime)
{	
	//D3DXCOLOR AlphaColor(1.0f, 1.0f, 1.0f, m_fTransparencyValue);
	D3DXCOLOR AlphaColor = m_colorPhantom;

	//  [9/3/2007 metalgeni] cap_rear �ǵڷ� ���� ����
	std::vector<SPGOBInfoSequencePart>::iterator Iter;
	Iter = std::find_if(m_pGOBModel->vGOBInfoSequencePart.begin(), m_pGOBModel->vGOBInfoSequencePart.end(), 
		std::bind2nd(IsEqualInfoSeqPartFromPartLayer, PL_CAP_REAR));
	if( Iter != m_pGOBModel->vGOBInfoSequencePart.end()) {

		PART_LAYER iLayer = (*Iter).PartLayer;

		if(!(m_pGOBModel->PartModel[(*Iter).PartLayer].isNull())) {

			if((*Iter).bVisable && m_pGOBModel->PartModel[(*Iter).PartLayer].pPartImage )
			{
				m_pGOBModel->PartModel[(*Iter).PartLayer].pPartImage->SetColor(AlphaColor);
				m_pGOBModel->PartModel[(*Iter).PartLayer].Render();
				m_pGOBModel->PartModel[(*Iter).PartLayer].pPartImage->SetColor();
			}

#ifdef _LATALE_CLIENT
			;
#else		
			if((*Iter).bSelect)
				g_pVideo->GetSysLine()->DrawRect( m_pGOBModel->PartModel[(*Iter).PartLayer].TarRect );			
#endif			
			g_pVideo->Flush();
		}
	}


	std::vector<SPGOBInfoSequencePart>::reverse_iterator rIter = m_pGOBModel->vGOBInfoSequencePart.rbegin();
	for(;rIter != m_pGOBModel->vGOBInfoSequencePart.rend();++rIter) {
		PART_LAYER iLayer = (*rIter).PartLayer;
		if(PL_CAP_REAR == iLayer)
			continue;
		
		if(!(m_pGOBModel->PartModel[(*rIter).PartLayer].isNull())) {

			if((*rIter).bVisable && m_pGOBModel->PartModel[(*rIter).PartLayer].pPartImage )
			{
				m_pGOBModel->PartModel[(*rIter).PartLayer].pPartImage->SetColor(AlphaColor);
				m_pGOBModel->PartModel[(*rIter).PartLayer].Render();
				m_pGOBModel->PartModel[(*rIter).PartLayer].pPartImage->SetColor();
			}

#ifdef _LATALE_CLIENT
			;
#else		
			if((*rIter).bSelect)
				g_pVideo->GetSysLine()->DrawRect( m_pGOBModel->PartModel[(*rIter).PartLayer].TarRect );			
#endif			
			g_pVideo->Flush();
		}		
	}
}

void SPAvatarModelUnit::ForceRender(int iPosX, int iPosY, FACING eFaing, int iWeaponItem, unsigned char iClassType /*= 0*/)
{
	unsigned int uiAniIndex = GetGOBSeqKey(iWeaponItem, GOB_SEQ_STAND, iClassType);
	int iAniFrame = 0;

	g_pGOBCluster->QueryAnimationSequence(&m_pGOBForceModel, uiAniIndex, iAniFrame, false);
	m_pGOBForceModel->bPCEnable = m_pGOBModel->bPCEnable;
	for( int i = 0; i < PL_LAST; i++ )
	{
		m_pGOBForceModel->PartModel[i].EquipClass = m_pGOBModel->PartModel[i].EquipClass;
		m_pGOBForceModel->PartModel[i].iColor = m_pGOBModel->PartModel[i].iColor;
		m_pGOBForceModel->PartModel[i].iItemID = m_pGOBModel->PartModel[i].iItemID;
		//m_pGOBForceModel->PartModel[i].iRotationDegree = m_pGOBModel->PartModel[i].iRotationDegree;
		m_pGOBForceModel->PartModel[i].PartLayer = m_pGOBModel->PartModel[i].PartLayer;
		//m_pGOBForceModel->PartModel[i].pPartImage = m_pGOBModel->PartModel[i].pPartImage;

#if defined(_USED_TEXTURE_TABLE)
		m_pGOBForceModel->PartModel[i].pTableInfo = m_pGOBModel->PartModel[i].pTableInfo;
#endif
	}

#if defined(_USED_TEXTURE_TABLE)
	SetLayerPosbyTable(m_pGOBForceModel, iPosX, iPosY, eFaing, true, false);
#else
	SetLayerPos(m_pGOBForceModel, iPosX, iPosY, eFaing, true, false);
#endif

	SPTexture* pkTexture;
	std::vector<SPGOBInfoSequencePart>::reverse_iterator Iter = m_pGOBForceModel->vGOBInfoSequencePart.rbegin();
	for(;Iter != m_pGOBForceModel->vGOBInfoSequencePart.rend();++Iter)
	{
		if(!(m_pGOBForceModel->PartModel[(*Iter).PartLayer].isNull()))
		{
			if((*Iter).bVisable)
			{
				if( pkTexture = m_pGOBModel->PartModel[(*Iter).PartLayer].pPartImage )
				{
#if defined(_USED_TEXTURE_TABLE)
					FRAME_INFO* pFrameInfo = m_pGOBForceModel->PartModel[(*Iter).PartLayer].pFrameInfo;
					if( pFrameInfo )
					{
						pkTexture->RenderTexture(&m_pGOBForceModel->PartModel[(*Iter).PartLayer].TarRect,
							&m_pGOBForceModel->PartModel[(*Iter).PartLayer].SrcRect,
							(float)pFrameInfo->iOffsetX, (float)pFrameInfo->iOffsetY,
							pFrameInfo->fCenterOffsetX, pFrameInfo->fCenterOffsetY,
							D3DXToRadian(m_pGOBForceModel->PartModel[(*Iter).PartLayer].iRotationDegree));
						//pPartImage->RenderTexture(&TarRect, &SrcRect, D3DXToRadian(iRotationDegree));
					}
#else
					pkTexture->RenderTexture(&m_pGOBForceModel->PartModel[(*Iter).PartLayer].TarRect,
						&m_pGOBForceModel->PartModel[(*Iter).PartLayer].SrcRect,
						D3DXToRadian(m_pGOBForceModel->PartModel[(*Iter).PartLayer].iRotationDegree));	
#endif
				}
			}
			
			g_pVideo->Flush();
		}		
	}
}

// pEquipLayerPool�� NULL�̸� PartLayer�� �־�� �Ѵ�.
bool SPAvatarModelUnit::SetPartLayerInfo(SPEquipLayerPool* pEquipLayerPool, PART_LAYER PartLayer)
{	
	m_bPartLayerChange = true;
	if(pEquipLayerPool) {	
		(m_pGOBModel->PartModel)[pEquipLayerPool->PartLayer].PartLayer	= pEquipLayerPool->PartLayer;
		(m_pGOBModel->PartModel)[pEquipLayerPool->PartLayer].EquipClass	= pEquipLayerPool->EquipClass;
		(m_pGOBModel->PartModel)[pEquipLayerPool->PartLayer].iItemID	= pEquipLayerPool->iItemID;
		(m_pGOBModel->PartModel)[pEquipLayerPool->PartLayer].iColor		= pEquipLayerPool->iItemColor;
		
		if( pEquipLayerPool->PartLayer == PL_FACE )
			m_fAccumulateEffectFaceRender = m_fNextEffectFaceRender;

		return (m_pGOBModel->PartModel[pEquipLayerPool->PartLayer]).ReloadTexture( m_strImagePath );
	} else {
		assert(PartLayer != PL_NULL);
		(m_pGOBModel->PartModel)[PartLayer].SetNull();

		if( PartLayer == PL_FACE )
			m_fAccumulateEffectFaceRender = m_fNextEffectFaceRender;

		return (m_pGOBModel->PartModel[PartLayer]).ReloadTexture( m_strImagePath );
	}
}

#ifdef _CHARTOOL
SPGOBAnimation*	SPAvatarModelUnit::GetAnimation(const unsigned uiAniInx)
{
    return g_pGOBCluster->GetAnimation(uiAniInx);
}
void SPAvatarModelUnit::SetAnimation(const unsigned int uiAniInx, SPGOBAnimation* pGOBAnimation)
{
	g_pGOBCluster->SetAnimation( uiAniInx, pGOBAnimation );

}
#endif


void SPAvatarModelUnit::SetAccumulateAction(float fAccumulateAction) 
{
	m_fAccumulateAction = fAccumulateAction; 

}

void SPAvatarModelUnit::SetAnimationIndex(unsigned int uiAniInx) 
{ 
	m_uiAniInx = uiAniInx; 	
#ifdef _LATALE_CLIENT	
	FrameInit();
	if(m_uiAniInx != m_uiLastAniInx) 
	{
		m_pGOBModel->fDelayTime = 0.0f;
		m_fAccumulateRenderTime = 0.0f;
	}
#endif
}

//------------------------------------------------------------------------------------
float SPAvatarModelUnit::GetAniAccumulateTime()
{
#if defined(_LATALE_CLIENT)
	float fTime = 0.0f;
	if( g_pGOBCluster )
		g_pGOBCluster->GetAnimationTime(m_uiAniInx, fTime);

	return fTime;
#endif
	return 0.0f;
}

//------------------------------------------------------------------------------------
void SPAvatarModelUnit::SetAnimationLoop(bool bLoop)
{
	m_bAnimationLoop = bLoop;
}

//------------------------------------------------------------------------------------
SPGOBInfoSequencePart* SPAvatarModelUnit::GetSequencePart(SPGOBModel* pGOBModel, PART_LAYER eLayer)
{
	std::vector<SPGOBInfoSequencePart>::iterator iter = pGOBModel->vGOBInfoSequencePart.begin();
	while( iter != pGOBModel->vGOBInfoSequencePart.end() )
	{
		if( iter->PartLayer == eLayer )
			return &(*iter);

		++iter;
	}

	return NULL;
}