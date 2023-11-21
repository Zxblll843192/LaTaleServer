// Copyright (C) DURAGON
//***************************************************************************
// System Name : GUILD CROPS
// Comment     : 
// Creation    : DURAGON 2007-4-04    11:18 
//***************************************************************************

#pragma once

enum { CROP_UPDATE_NULL, CROP_UPDATE_TIME , CROP_UPDATE_LEVEL,} ;
enum { CROP_SET_CLEAR, CROP_SET_INITIALIZE, CROP_SET_DATA, CROP_SET_NOURISH } ;

struct DISPLAY_CROP_UNIT ;
//class SPGuildLDT ;
class SPGuildCrops
{

public:
	SPGuildCrops();
	virtual ~SPGuildCrops();

	void	Init() ;
	void	DestroyCrop() ;
	bool	CropProcess(float fTime, int &iUpdate) ;

	bool	hasCorps() ;							// �۹��� �ִ��� ����
	bool	IsComplete() ;							// �۹� ���� �Ϸ�
	
	UINT32	GetCropImageID(int iCLevel) ;			// �۹� �̹��� ID (MapEvent)
	UINT32	GetCropDlgImageID(int iCLevel) ;		// �۹� �̹��� ID(GlobalRes)
	UINT32	GetCropCutinImageID(int iCLevel) ;		// �۹� Cut In Image
	const char* GetCropCutinTalk(int iCLevel) ;		// Cut In Talk
	UINT32	GetUseItemForIcon()	{	return m_iUseItemID ;	}	// �۹� �������� (��� ������)
	const char* GetCropName() ;						// �۹� �̸�
	int		GetCropLevel() ;						// �۹� ����
	

	void	SetCropClassID(INSTANCE_ID InstanceID=0, CLASS_ID ClassID=CLASS_ID_NULL) ;
	bool	GetCropClassID(INSTANCE_ID& InstanceID, CLASS_ID& ClassID) ;
	void	SetCropInformation(int iCmd, UINT32 iCropID=0, UINT32 iRemainTime=0, UINT32 iNourishTime=0, UINT32 iHastenSumTime=0) ;
	void	SetCropTimes(UINT32 iRemainTime, UINT32 iNourishTime, UINT32 iHastenSumTime) ;
	void	SetGrowthComplete() ;
	void	SetCropName(const char* pName) {	m_strCropName = pName ;		}

	UINT32	GetRemainTime()			{	return m_iRemainTime - m_iCropCountTime ;	}
	UINT32	GetNourishTime()		{	return m_iNourishTime - m_iCropCountTime ;	}
	UINT32	GetHastenSumTime()		{	return m_iHastenSumTime ;	}

	bool CheckAddBoosterTime(int iType, UINT32 iAddTime) ;
	bool CheckCropLevelup() ;					// LevelUP Check (Process, USE Nourish)

private:
	void SetCropImageInfo(UINT32 iCropID) ;
	int	 CalcCropLevel() ;						// �۹� ���� ���

private:
	INSTANCE_ID	m_InstanceID;
	CLASS_ID	m_ClassID;
	int			m_iCropLevel ;
	bool		m_bComplete ;				// �۹����� �Ϸ�
	UINT32		m_iCropID ;					// �۹� ID ( ID == 0 is Empty)
	UINT32		m_iUseItemID ;				// �������� (For Icon)
	UINT32		m_iRemainTime ;				// ���� �Ϸ���� ���� �ð�
	UINT32		m_iNourishTime ;			// ���� ��� �ð�
	UINT32		m_iHastenSumTime ;			// ������ ���� �ð�
	UINT32		m_iCropCountTime ;			// Client�� ������ �ð�
	float		m_fProcessTime ;			// Process���� ����ϴ� �ð�

	DISPLAY_CROP_UNIT	m_stDisplayCrop[4] ;
	//UINT32		m_iCropImageID[4] ;			// ������ CropImageID
	//UINT32		m_iCropDlgImageID[4];		// ������ Dlg�� ImageID

	UINT32		m_iLevelTime[4] ;			// ������ �ð�
	UINT32		m_iLimitHastenTime ;		// ������ ���ѽð�
	std::string	m_strCropName ;				// �۹� �̸�

protected:
	
};