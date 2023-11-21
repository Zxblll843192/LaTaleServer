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

struct SPGOBAniSeqPart {
	PART_LAYER		PartLayer;	
	int				iResourceIndex;
	int				iRotationDegree;
	int				iRX;
	int				iRY;
	bool			bVisable;
	bool			bFlip;
#ifdef _CHARTOOL	
	bool			bSelect;
#endif
	SPGOBAniSeqPart();
	void SetNull();
	bool isNull();

	// added by kkandori (11.15.2004)
	SPGOBAniSeqPart& operator=(const SPGOBAniSeqPart &src);
};

struct SPGOBAniSeq {
	std::vector<SPGOBAniSeqPart>	vAniSeqPart;
	int		iSeqNum;				// 1 BASE
	float	fDelayTime;

	SPGOBAniSeq();
	void SetNull();
	bool isNull();	

	// added by kkandori (11.15.2004)
	SPGOBAniSeq& operator=(const SPGOBAniSeq &src);
};

struct SPGOBAnimation {
	std::vector<SPGOBAniSeq>		vAniSeq;
	unsigned int 					uiAniInx;	
	float							fAccumulateTime;

	SPGOBAnimation();
	void SetNull();
	bool isNull();	

	// added by kkandori (11.15.2004)
	SPGOBAnimation& operator=(const SPGOBAnimation &src);
};








