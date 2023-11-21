// Copyright (C) metalgeni
//*****************************************************************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-19 ���� 10:26:19
//
// modified history :
//
//					metalgeni 2004/10/12 ---------------------------------------------------------------------
//					removed SPGOBPartPool
//					removed SPGOBPart
//
//					appended
//					SPGOBInfoSequencePart	- �ִϸ޼� ��Ʈ ������ ����
//					SPGOBPartModel			- ����������ȣ, �����ȣ, �ؽ��ĵ� �����ۿ� ���� ��Ʈ����
//
//
//					metalgeni 2004/11/5 ---------------------------------------------------------------------
//					SPGOBClusterDEF�� �ִ� �ִϸ��̼ǰ� ���� �ΰ��� ���κи�.
//					SPGOBClusterDEF�� �״�� �����Ѵ�.
//					SPGOBAnimation	- �ִϸ��̼ǿ� ���õ� ���
//					SPGOBModel		- Part������ �������� ���õ� ���
//										��⸸ �и��Ǿ����� ������ ����Ȱ� �ƴ�.
//										�� SPGOBModel�� struct���� class�� ����.
//
//					
//*****************************************************************************************************************************

#pragma once

// ���������� �о�´� (�����Ҷ� ���� �ٲ��)
struct SPGOBInfoSequencePart {
	PART_LAYER	PartLayer;	
	int			iResourceIndex;
	int			iRotationDegree;
	int			iRX;
	int			iRY;
	bool		bVisable;
	bool		bFlip;
#ifdef _CHARTOOL	
	bool			bSelect;
#endif
	SPGOBInfoSequencePart();
	void SetNull();	
	bool operator==(const SPGOBInfoSequencePart CompObj);	

	// added by kkandori (11.15.2004)
	SPGOBInfoSequencePart& operator=(const SPGOBInfoSequencePart &src);
};

struct SPGOBModelPart {
	PART_LAYER	PartLayer;
	EQUIP_CLASS	EquipClass;
	int			iItemID;
	int			iColor;

	int			iRotationDegree;
	RECT		SrcRect;
	RECT		TarRect;

#if defined(_USED_TEXTURE_TABLE)
	TEXTURE_TABLE_INFO* pTableInfo;
	TEXTURE_TABLE_INFO* pTableInfoReserve;
	FRAME_INFO* pFrameInfo;
#endif

	int			iRenderType;
	SPTexture*	pPartImage;	
	SPTexture*	pPartImageReserve;
	bool		ReloadTexture(TCHAR	*strImagePath=NULL);	
	void		Render();

	SPGOBModelPart();
	~SPGOBModelPart();
	void SetNull();
	bool isNull();	

	// added by kkandori (11.15.2004)
	SPGOBModelPart& operator=(const SPGOBModelPart &src);
};

struct SPGOBModel {
	std::vector<SPGOBInfoSequencePart>		vGOBInfoSequencePart;	// �����ؿ��� �ִϸ��̼� ������ ����
	float						fDelayTime;

	unsigned int 				uiAniIndex;
	int							iAniSequence;	// 0 BASE
	int							iMaxSequence;	// size()
	SPGOBModelPart				PartModel[PL_LAST];

	// ���� PC�� �Ӹ��� ���̱� ������ ����𵨿��� ���̴��� �� �˸� �ȴ�.
	bool						bPCEnable;		

	SPGOBModel();
	void SetNull();
	void Destroy();

	// added by kkandori (11.15.2004)
	SPGOBModel& operator=(const SPGOBModel &src);
};





