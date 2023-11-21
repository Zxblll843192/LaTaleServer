// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-10 ���� 10:26:19
//***************************************************************************

#pragma once


extern BG_ID;

class SPTerrainManager;
class SPTerrainModel;
class SPTerrainUnit;
class SPTerrainAttribute;

struct SPBGInfo;
struct SPMapInfo;
class SPStage;

class SPTerrainCluster {

public:
	SPTerrainCluster();
	~SPTerrainCluster();
	bool Init(SPTerrainManager* pParent);
	void Clean();

	void SetCameraOffset(float, float);

	void RenderLayer1(float fTime);
	void RenderLayer2(float fTime);
	void RenderLayer3(float fTime);

	void RenderSecondLayer1(float fTime);
	void RenderSecondLayer2(float fTime);
	void RenderSecondLayer3(float fTime);

	void RenderAttr();

	void Process(float fTime);

	bool MoveDrop(float& fx, float& fy, BG_ID& bgLayer, const float fDropStep);
	bool InspectStandLayer(float fx, float fy, BG_ID& bgLayer);

	// ������� �ҷ��� �Ѵ�..!!
	bool LoadPallet( const char* pszFName);
	bool LoadForm( SPStage* pStage = NULL);			//jinhee - [2005/1/11]
	bool LoadAttribute( SPStage* pStage = NULL);	//jinhee - [2005/1/11]

	/**
	 * ���� �������� ���� TerrainLayerList�� ���θ� ���� <br> 
	 @param 
	 @return 
	*/
	bool DeleteAllTerrainLayerList();				//jinhee - [2005/1/11]
	
	/**
	 * ���� �������� ���� TerainAttributeList�� ���θ� ���� <br>
	 @param 
	 @return 
	*/
	bool DeleteAllAttributeLayerList();				//jinhee - [2005/1/11]

	/**
	* �������� ����� �ͷ��� ���Ϳ� ������ �ε����� -1�� ���� <br>
	@param 
	@return 
	*/
	void ResetStage() {
		m_iFirstMapID		= -1;
		m_iSecondMapID		= -1;
	}

	bool SetShareLayer();

		//[xialin 2008/09/18]add
	bool IsTerrainLayer2Back( int x, int y );

	//[xialin 2008/09/18]add
	bool IsTerrainLayer3Back( int x, int y );


private:
	std::vector<SPTerrainModel*>	m_vpTerrainLocalModel;	
	std::vector<SPTerrainModel*>	m_vpTerrainGlobalModel;	

	std::vector<std::vector<SPTerrainUnit*> >	m_vpTerrainLayer1List;	//jinee - [2005/1/10]
	std::vector<std::vector<SPTerrainUnit*> >	m_vpTerrainLayer2List;	//jinee - [2005/1/10]
	std::vector<std::vector<SPTerrainUnit*> >	m_vpTerrainLayer3List;	//jinee - [2005/1/10]

	std::vector<SPTerrainUnit*> m_vpShareTerrainLayer1;					//[2005/11/8] - �����ϴ� �ͷ���
	std::vector<SPTerrainUnit*> m_vpShareTerrainLayer2;					//[2005/11/8] 
	std::vector<SPTerrainUnit*> m_vpShareTerrainLayer3;					//[2005/11/8]


	int m_iFirstMapID;		/**< ù��° �� ID Process ���� ������ش� <br> */
	int m_iSecondMapID;		/**< �ι�° �� ID Process ���� ������ش� <br> */ 

	bool m_bShowSecondLayer;

	// Block Attribute
	SPTexture* m_pAttrImageLayer1;
	SPTexture* m_pAttrImageLayer2;

	float	m_fLenX;
	float	m_fLenY;
	int		m_iMapID;

	float	m_fCameraOffsetX;
	float	m_fCameraOffsetY;

	SPTerrainManager*	m_pParent;
	SPTerrainAttribute*	m_pTerrainAttribute;
	
	std::vector<SPTerrainAttribute*> m_vpTerrainAttributeList;			//jinhee - [2005/1/10]

	friend SPTerrainManager;

};




