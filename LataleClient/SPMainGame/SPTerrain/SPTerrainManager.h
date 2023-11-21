// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPTerrainManager
// Comment     : 
// Creation    : metalgeni 2004-08-23 ���� 2:56:36
//***************************************************************************


#pragma once 

extern BG_ID;
class SPManager;
class SPBGILoader;
class SPTerrainCluster;

//04.10.15 Moved SPTerrainDEF.h - jinhee
//struct SPRotateScrollImage {
//}

struct SPMapInfo;
class SPMapGroup;
class SPStage;

class SPTerrainManager : public SPManager {

public:

	SPTerrainManager();
	virtual ~SPTerrainManager();

	virtual void Process(float fTime);
	virtual	void Render(float fTime);
	virtual bool PurgeAll();	// Purge Instant Data for Subgame Change

	// after render module because Z-order.
	void		 RenderLayer2(float fTime);
	void		 RenderLayer3(float fTime);

	/**
	 * ���� ����� �����Ѵ� <br> 
	 @param float fTime
	 @return NONE
	*/
	void		 RenderForeGround(float fTime); 

	virtual bool Init();
	virtual void Clean();	

	void		 SetLength(float, float);

	float		 GetSX() { return m_fLenX;	}
	float		 GetSY() { return m_fLenY;	}
	bool		 isRenderAttr() { return m_bViewAttr; }

	

	SPTerrainCluster* GetTerrainCluster() { return m_pTerrainCluster; }

	virtual int		SPPerformMessage(UINT msg, WPARAM wparam = 0, LPARAM lParam = 0);
	
	/**
	 * BG �ε� <br>
	 @param SPStage* pStage = NULL
	 @return int
	*/
	int LoadBG(SPStage* pStage = NULL);			//jinhee - [2005/1/11]
	
	/**
	 * Cluster�� Form �ε� ȣ��<br>
	 @param SPStage* pStage = NULL
	 @return int
	*/
	int LoadForm(SPStage* pStage = NULL);		//jinhee - [2005/1/11]
	
	/**
	 * Cluster�� Attribute �ε� ȣ�� <br> 
	 @param SPStage* pStage = NULL
	 @return int
	*/
	int LoadAttribute(SPStage* pStage = NULL);	//jinhee - [2005/1/11]	


protected:
	/**
	 * m_vpBackRotatePicList �� ���� <br>
	 @param NONE
	 @return bool
	*/
	bool DeleteAllStageBG();					//jinhee - [2005/1/11]

	SPTMESSAGE_MAP_DECLARE()
	int OnPurgeAll		(WPARAM wparam, LPARAM lparam);
	int OnInit			(WPARAM wparam, LPARAM lparam);
	int OnLoadPallet	(WPARAM wparam, LPARAM lparam);
	

protected:
	
	//jinhee - [2005/1/10]
	std::vector<std::vector<SPRotateScrollImage*> > m_vpBackRotatePicList;	/**< ��� ����Ʈ <br> */

	SPTerrainCluster*					m_pTerrainCluster;
	bool								m_bViewAttr;

	float m_fLenX; 
	float m_fLenY;

	SPBGILoader* m_pBGILoader;
};

extern SPTerrainManager* g_pTerrainManager;


