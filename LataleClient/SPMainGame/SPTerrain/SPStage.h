
// Copyright (C) jinhee
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : jinhee 2005-1-7 ���� 2:56:36
//***************************************************************************


#pragma once

#ifdef _LATALE_SERVER
	#include "GlobalDefines.h"
#endif

class SPTerrainAttribute;


////
//struct SPBGInfo {
//	int iBGID;						/**< BG Index <br> */
//	std::string strBGFile;			/**< BG File <br> */
//
//	SPBGInfo() {
//		SetNull();
//	}
//
//	~SPBGInfo() {
//	}
//
//	void SetNull() {
//		iBGID = -1;
//		strBGFile = "";
//	}
//
//	void operator=(const SPBGInfo Src) {
//		iBGID = Src.iBGID;
//		strBGFile = Src.strBGFile;
//	}
//};


//
struct SPMapInfo {					//jinee - [2004/12/30] //Test��
	int iMapID;						/**< Map Index <br> */
	int iBGIndex;					/**< ���Ǵ� BG Index <br> */

	//int iLeftMap;					/**< ���ʿ� ������ �� <br> */
	//int iRightMap;					/**< �����ʿ� ������ �� <br> */

	float fMapLeft;					/**< �׷���� �� ���� ��ġ X <br> */
	float fMapTop;					/**< �׷���� �� ���� ��ġ Y <br> */
	float fMapRight;			
	float fMapBottom;
	float fMapWidth;				/**< �� ���� <br> */
	float fMapHeight;				/**< �� ���� <br> */

	std::string strMapName;			/**< �� �̸� <br> */
	std::string strFormFile;		/**< Form File <br> */
	std::string strAttributeFile;	/**< Attribute File <br> */
	std::string strMiniMapFile;		/**< Mini Map File <br> */

	SPMapInfo() {
		SetNull();
	}

	~SPMapInfo()
	{
	}

	void SetNull() 
	{
		iMapID = -1;
		iBGIndex = -1;
		//iLeftMap = -1;
		//iRightMap = -1;
		
		fMapLeft = -1.0f;
		fMapTop = -1.0f;
		fMapRight = -1.0f;
		fMapBottom = -1.0f;
		fMapWidth = 0.0f;
		fMapHeight = 0.0f;

		strMapName = "";
		strFormFile = "";
		strAttributeFile = "";
		strMiniMapFile = "";
	}	
	
	/**
	 * �Ѱ��� ���� �׷�󿡼� �����ϴ� ������ �����Ѵ� <br> 
	 @param float fMapX
	 @param float fMapY
	 @param float fWidth
	 @param float fHeight
	 @return NULL
	*/
	void SetMapRect(float fMapX, float fMapY, float fWidth, float fHeight)
	{
		fMapLeft = fMapX;
		fMapTop = fMapY;	
		fMapWidth = fWidth;
		fMapHeight = fHeight;

		fMapRight = fMapLeft + fWidth;
		fMapBottom = fMapTop + fHeight;
	}

	void operator=(const SPMapInfo Src)
	{
		iMapID				= Src.iMapID;
		iBGIndex			= Src.iBGIndex;
		//iLeftMap			= Src.iLeftMap;
		//iRightMap			= Src.iRightMap;

		fMapLeft			= Src.fMapLeft;
		fMapTop				= Src.fMapTop;
		fMapRight			= Src.fMapRight;
		fMapBottom			= Src.fMapBottom;
		fMapWidth			= Src.fMapWidth;
		fMapHeight			= Src.fMapHeight;

		strMapName			= Src.strMapName;
		strFormFile			= Src.strFormFile;
		strAttributeFile	= Src.strAttributeFile;
		strMiniMapFile		= Src.strMiniMapFile;
	}
};


/**
 * �� ���� ��� <br>
*/
enum MAP_LINK {
	MAP_LINK_NULL = 0,						/**< NO LINK <br> */
	MAP_LINK_HORIZONTAL = 1,				/**< horizontal(width) <br> */
	MAP_LINK_VERTICAL = 2					/**< vertical(height) <br> */
};

/**
 * �׷� Ÿ�� <br> 
*/
// 2006.05.19 dhpark �׷�Ÿ���� �ߺ����������ϰ� �����մϴ�.
const int GROUP_TYPE_FIELD		= 1<<0;	// 1
const int GROUP_TYPE_MINIMAP	= 1<<1;	// 2
const int GROUP_TYPE_EVENT		= 1<<2;	// 4
const int GROUP_TYPE_MARKET		= 1<<3;	// 8
const int GROUP_TYPE_EXP		= 1<<4;	// 16
const int GROUP_TYPE_PVP		= 1<<5;	// 32
const int GROUP_TYPE_CASH		= 1<<7; // 128
const int GROUP_TYPE_INDUN		= 1<<8; // 256

//enum GROUP_TYPE {
//	GROUP_TYPE_HOUSE			= 0,		/**< �ǹ� ���� <br> */
//	//GROUP_TYPE_VILLAGE = 10,				/**< �Ϲ� ���� <br> */
//	//GROUP_TYPE_ELIAS = 100,				/**< BELOS ���� <br> */
//	//GROUP_TYPE_DUNGUEN = 200,				/**< ���� <br> */
//	GROUP_TYPE_PVP_ENABLE		= 1000,		/**< PVP ���� �������� <br> */
//	GROUP_TYPE_EVENT			= 2000,
//};

const int MAX_MAP = 255;


/**
* @class SPMapGroup
* @brief �ʱ�(���������� �� �׷��� �ϳ��� ������ �ν��Ѵ�)
* @author Jinhee
* @version 00.00.01
* @date 2005.1.13
* @bug ����
* @warning ����
*/
class SPMapGroup {
public:
	SPMapGroup() {
		SetNull();
	}

	~SPMapGroup() {
		DeleteAllMapInfo();
	}
	
	/**
	 * MapGroup�� MapInfoList�� MapInfo�� �߰��Ѵ�. <br>
	 @param SPMapInfo* pMapInfo = NULL
	 @return bool
	*/
	bool AddMapInfo(SPMapInfo* pMapInfo = NULL) {		// ���ͻ��
		m_vpMapInfo.push_back(pMapInfo);		
		return true;
	}
	
	//
	//bool AddMapInfo(SPMapInfo pMapInfo) {				// �迭���
	//	//m_vpMapInfo.push_back(pMapInfo);		
	//	m_pMapInfo[m_iMapCount] = pMapInfo;
	//	return true;
	//}
	
	/**
	 * Group��ǥ ��ġ���� �� ID �� ���´� <br>
	 @param float fPointX = 0.0f	����� X��ǥ
	 @param float fPointY = 0.0f	����� Y��ǥ
	 @return int	ã�Ƴ� ���� ID
	*/
	int FindMapID(float fPointX = 0.0f, float fPointY = 0.0f);	
	
	/**
	 * �׷쳻 ù��° ���� ����Ʈ�� �� ID�� ���´� <br> 
	 @param NONE
	 @return int
	*/
	int GetFirstMapID();
	
	/**
	 * �׷쳻 ���� ������ ���´� <br>
	 @param NONE
	 @return int
	*/
	int GetGroupSize();

	/**
	 * Group�� MapList���� ��ǥ�� �ش��ϴ� MapInfo �������� �ε����� ���´� <br>
	 @param float fPointX = 0.0f	����� X��ǥ
	 @param float fPointY = 0.0f	����� Y��ǥ
	 @return int	ã�Ƴ� ���� ID 
	*/
	int FindMap(float fPointX = 0.0f, float fPointY = 0.0f);

	SPMapInfo* FindMapInfo(float fPosX = 0.0f, float fPosY = 0.0f);

	/**
	 * MapGroup�� ��ǥ�� �ش���� ��ǥ�� ��ȯ�Ѵ� <br> 
	 @param float fPointX	����� X��ǥ
	 @param float fPointY	����� Y��ǥ
	 @param int iMapID = -1	�̹� ���� ���� ����س��� ��� ���
	 @return float ������� ��ġ�������� ������ X��ǥ
	*/
	float GetMapPosX(float fPointX, float fPointY, int iMapID = -1);
	
	/**
	 * MapGroup�� ��ǥ�� �ش���� ��ǥ�� ��ȯ�Ѵ� <br> 
	 @param float fPointX	����� X��ǥ
	 @param float fPointY	����� Y��ǥ
	 @param int iMapID = -1	�̹� ���� ���� ����س��� ��� ���
	 @return float ������� ��ġ�������� ������ Y��ǥ
	*/
	float GetMapPosY(float fPointX, float fPointY, int iMapID = -1);

	void GetMapPos(float fPosX, float fPosY,
		float& fMapOffsetX, float& fMapOffsetY);

	/**
	 * MapIndex�� ������� ��ǥ�� �̿��Ͽ� �ʱ׷��� ��ǥ�� ��ȯ�Ѵ� <br> 
	 @param int iMapID �� �ʱ׷�󿡼��� �� �ε���
	 @param float fPointX �� �ʻ󿡼��� X��ǥ
	 @return float	�� �׷�󿡼��� X��ǥ
	*/
	float GetGroupPosX(int iMapID, float fPointX);
	
	/**
	* MapIndex�� ������� ��ǥ�� �̿��Ͽ� �ʱ׷��� ��ǥ�� ��ȯ�Ѵ� <br> 
	@param int iMapID �� �ʱ׷�󿡼��� �� �ε���
	@param float fPointY �� �ʻ󿡼��� Y��ǥ
	@return float	�� �׷�󿡼��� Y��ǥ
	*/
	float GetGroupPosY(int iMapID, float fPointY);
	
	/**
	 * �׷�Ÿ���� �����´� <br> 
	 @param NONE
	 @return int GROUP_TYPE
	*/
	int GetType() {return m_iType;}	
	// 2006.05.19 dhpark ���� �ʱ׷�Ÿ���� ����ϱ� ���� �Լ�
	bool IsMapGroupType(int iMapGroupType) { return (m_iType & iMapGroupType) ? true : false; }

protected:
	/**
	 * MapGroup�� Mamber�� �ʱ�ȭ �Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void SetNull() {
		m_iGroupID = -1;
		m_iMapLink = MAP_LINK_NULL;
		m_iMapCount = 0;
		m_lGroupWidth = 0;
		m_lGroupHeight = 0;
		m_iSoundEffectType = 0;
		m_iMiniMapIconID = 0;
		m_iMiniMapResID = 0;
		m_strGroupName = "";
		m_strBGFile = "";
		m_strBGMFile = "";
		m_iBGID = -1;
		m_iType = 0;
		m_fVelocityX = 1.0f;
		m_fJumpSpeed = 1.0f;
		m_fHangingVelocity = 1.0f;
		m_fUpDownVelocity = 1.0f;
		m_fGravity = 1.0f;
		m_fMaxDropSpeed = 1.0f;
	}
	
	/**
	 * MapGroup�� MapList�� �ʱ�ȭ�Ѵ� <br>
	 @param NONE
	 @return bool
	*/
	bool DeleteAllMapInfo() {
		//������ ���
		std::vector<SPMapInfo*>::iterator iter;
		for(iter = m_vpMapInfo.begin(); iter != m_vpMapInfo.end(); ++iter) {
			SAFE_DELETE(*iter);
		}
		m_vpMapInfo.clear();

		return true;
	}

public:
	int m_iGroupID;							/**< �ʱ׷� ID <br> */
	int m_iMapCount;						/**< �����ϴ� ���� ���� <br> */
	int m_iBGID;							/**< ����ϴ� ��� ID <br> */
	int m_iType;							/**< �׷� Ÿ�� <br> */
	
	MAP_LINK m_iMapLink;					/**< �� ���� ���� <br> */
	long m_lGroupWidth;						/**< �׷� ���¿��� �� Width <br> */
	long m_lGroupHeight;					/**< �׷� ���¿��� �� Height <br> */
	
	// �߰� ����
	int m_iSoundEffectType;					/**< ���� ����Ʈ Type <br> */	
	int m_iMiniMapResID;					/**< �̴ϸ� ������ ���ҽ� �ε��� <br> */
	int m_iMiniMapIconID;					/**< �̴ϸ� ������ ���ҽ� �� �ε��� <br> */	

	std::string m_strGroupName;				/**< �� �׷� �� <br> */
	std::string m_strBGFile;				/**< ����ϴ� BG File <br> */

	std::string m_strBGMFile;				/**< �� �׷쿡 ����� BGM File <br> */

	float	m_fVelocityX;					/**< X�� �̵� <br> */
	float	m_fJumpSpeed;					/**< ���� <br> */
	float	m_fHangingVelocity;				/**< �Ŵ޸��� �̵� <br> */
	float	m_fUpDownVelocity;				/**< ���������� <br> */
	float	m_fGravity;						/**< �߷� <br> */
	float	m_fMaxDropSpeed;				/**< �ִ� ���� �� <br> */
	
	std::vector<SPMapInfo*> m_vpMapInfo;	/**< �����ϴ� �� List ���� <br> */	
	//SPMapInfo m_pMapInfo[MAX_MAP];		/**< �����ϴ� �� List �迭 <br> */
};


/**
* @class SPStage
* @brief �ϳ��� ��������
* @author Jinhee
* @version 00.00.01
* @date 2005.1.7
* @bug ����
* @warning ����
*/
class SPStage {
public:
	SPStage();
	~SPStage();
	
	/**
	 * List �� ���� �ɹ� �����͸� �ʱ�ȭ�Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void Init();
	
	/**
	 * List �ʹ� �����͸� �ʱ�ȭ�Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void ResetStage();

	/**
	 * �ش� �������� ���� �׷� ���� �����´� <br>
	 @param NONE
	 @return int GroupCount
	*/
	int GetGroupCount() { return m_iGroupCount; }
	
	/**
	 * Palette File �� List �� �߰��Ѵ� <br>
	 @param std::string strPalette = ""
	 @return bool
	*/
	bool AddPaletteFile(std::string strPalette = "");	

	/**
	 * MapGroup�� �߰��Ѵ� <br>
	 @param SPMapGroup* pMapGroup = NULL
	 @return bool
	*/
	bool AddMapGroup(SPMapGroup* pMapGroup = NULL);

	/**
	 * MapGroup�� �����Ѵ� <br>
	 @param NONE
	 @return bool
	*/
	bool ResetMapGroup();

	/**
	 * ���� �� �׷� �ε����� �����Ѵ� <br>
	 @param int iGroupIndex = -1
	 @return NULL
	*/
	void SetCurMapGroupIndex(int iGroupIndex = -1);

	/**
	 * ���� ���õ� �� �׷� �ε����� ��ȯ�Ѵ� <br>
	 @param NONE
	 @return int
	*/
	int GetCurMapGroupIndex();

	/**
	 * �ش��ε����� �� �׷��� �����ɴϴ� <br>
	 @param int iGroupIndex = -1
	 @return SPMapGroup*
	*/
	SPMapGroup* GetMapGroup(int iGroupIndex = -1);

	/**
	 * ���� ��ǥ�� �� ��Ʈ����Ʈ�� �����´� <br> 
	 * �켱 ���ٸ� �ϵ��� �Ǿ����� �׳� ���ο��� ����Ҽ� ���� ������ �ϴ�...<br>
	 @param float fPointX	�׷����ǥ
	 @param float fPointY	�׷����ǥ
	 @param int iGroupID = -1
	 @param int iMapID = -1
	 @return SPTerrainAttribute*
	*/
	SPTerrainAttribute* GetCurTerrainAttribute(float fPointX, float fPointY,
		float& fMapOffsetX, float& fMapOffsetY, int iGroupID = -1, int iMapID = -1);


//protected:
public:
	int m_iStageID;							/**< �������� �ε��� <br> */
	std::string m_strStageName;				/**< �������� �� <br> */
	
	int m_iGroupCount;						/**< �׷� �� <br> */	

	int m_iSyncRegionWidth;					/**< ����ȭ ���� Width <br> */
	int m_iSyncRegionHeight;				/**< ����ȭ ���� Height <br> */	

	long m_dwMapWidth;						/**< �׷� ���� <br> */
	long m_dwMapHeight;						/**< �׷� ���� <br> */

	std::vector<std::string> m_vpPalette;	/**< �ķ�ƮFile ����Ʈ <br> */

	std::vector<SPMapGroup*> m_vpMapGroup;	/**< MapGroup ����Ʈ <br> */
	
	std::vector<SPTerrainAttribute*> m_vpTerrainAttribute;

protected:
	int m_iCurMapGroupIndex;				/**< ���� ���õ� �׷��� �ε��� <br> */
};

