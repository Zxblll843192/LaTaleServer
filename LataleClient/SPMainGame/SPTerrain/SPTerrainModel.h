// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-24 ���� 10:26:19
//***************************************************************************

#pragma once


class SPTerrainModel : public SPRenderModel {

public:

	SPTerrainModel();
	virtual ~SPTerrainModel();

	virtual void Init();
	virtual void SetNull();
	virtual void Destroy();
	virtual bool SetImage(SPTexture** ppImage, int iAlpha) = 0;

	virtual LRESULT GetMemberValue(MODEL_VALUE_TYPE mvMsg, LPARAM lParam = 0); 

protected:	
	std::string m_strFile;	//���ϸ� ���� jinhee - 04.10.15	



	
};


