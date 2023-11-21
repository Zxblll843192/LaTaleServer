
// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-11-29 ���� 2:56:36
//***************************************************************************


#pragma once

enum LOAD_STATE {

	LS_NULL				= 0,

	LS_STAGE_LOAD		= 1,		//jinhee - [2004/12/30] //Stage���� �ε�

	LS_BGI_LOADER		= 2,
	LS_TERRAIN_PALLET	= 3,
	LS_TERRAIN_FORM		= 4,
	LS_TERRAIN_ATTR		= 5,	

	LS_RENDER			= 6,		//[2005/9/9] //�߰��� �����ϴ� Ÿ��...

	LS_CASH_CHECK		= 7,

	LS_THREAD_WAIT		= 10,

	LS_END			   = 99,
};

struct SPBGInfo;
struct SPMapInfo;
class SPStage;

class SPLDTManager;
class SPLDTFile;

const int MAX_IMAGE_LIST = 3;				/**< ImageInfo�� ���ԵǴ� ������ ���� <br> */

struct SPLoadImageInfo {
	std::string m_strImage;					/**< �̹��� ���ҽ� <br> */
	RECT m_rtSrc[MAX_IMAGE_LIST];			/**< �̹��� �ҽ� ��ǥ ����Ʈ <br> */
	RECT m_rtDest[MAX_IMAGE_LIST];			/**< �̹��� ��� ��ǥ ����Ʈ <br> */
	int	m_iShowCount;						/**< ����ϴ� ��ǥ�� ���� <br> */

	SPLoadImageInfo() {
		Clear();
	}

	~SPLoadImageInfo() {
		Clear();
	}

	void Clear() {
		m_strImage = "";
		m_strImage.clear();
		m_iShowCount = 0;

		for(int i = 0; i < MAX_IMAGE_LIST ; i++) {
			SetRect(&m_rtSrc[i], -1, -1, -1, -1);
			SetRect(&m_rtDest[i], -1, -1, -1, -1);
		}
	}

	void SetInfoRect(int iIndex, RECT rtSrc, RECT rtDest) {
		SetRect(&m_rtSrc[iIndex], rtSrc.left, rtSrc.top, rtSrc.right, rtSrc.bottom);
		int iWidth = rtSrc.right - rtSrc.left;
		int iHeight = rtSrc.bottom - rtSrc.top;
		
		SetRect(&m_rtDest[iIndex], rtDest.left, rtDest.top, rtDest.left + iWidth, rtDest.top + iHeight);
		m_iShowCount = iIndex + 1;
	}
};


struct SPLoadInfo {
	std::string m_strBGImage;				/**< ������ ����� �̹��� ���ҽ� <br> */
	SPLoadImageInfo m_LoadImage[MAX_IMAGE_LIST];	/**< �ΰ������� ����� �̹��� ���� ����Ʈ <br> */
	int m_iImageCount;						/**< ����ϴ� �̹����� ���� <br> */

	SPLoadInfo() {
		Clear();
	}

	~SPLoadInfo() {
		Clear();
	}

	void Clear() {
		m_strBGImage = "";
		m_strBGImage.clear();
		m_iImageCount = 0;

		for(int i = 0; i < MAX_IMAGE_LIST; i++) {
			m_LoadImage[i].Clear();
		}
	}

	void SetBGFile(std::string strFile) {
		Clear();
		m_strBGImage = RES_PAHT_LOADING + strFile;
	}

	void SetImageFile(int iImageIndex, std::string strFile) {
		m_LoadImage[iImageIndex].m_strImage = RES_PAHT_LOADING + strFile;
		m_iImageCount = iImageIndex + 1;
	}

	void SetImageRect(int iImageIndex, int iInfoIndex, RECT rtSrc, RECT rtDest) {
		m_LoadImage[iImageIndex].SetInfoRect(iInfoIndex, rtSrc, rtDest);
	}
};


class SPLoading : public SPSubGameManager {
public:
	SPLoading();
	virtual ~SPLoading();

	virtual void			Render(float fTime);
	virtual void			Process(float fTime);
	virtual bool			Init();	
	
	virtual void			RenderText();

	virtual int				SPPerformMessage	(UINT msg, WPARAM wparam = 0, LPARAM lParam = 0);

	//void SetStageID(int iStage)			{ m_iStageID = iStage; }
	//void SetMapGroupID(int iGroupID)	{ m_iMapGroupID = iGroupID; }
	
	SPStage*				GetStage(int iCurStage = 0);	//test // �Ȼ���ҵ�.

protected:

	void		ProcessImage(float fTime);

	/**
	 * Loading �� �ʿ��� Data�� LDT���� �о� LoadInfo�� �����Ѵ� <br>
	 @param  int iItemID ���⼭�� �Ȼ���Ѵ� (���������� id ����)
	 @return SPLoadInfo*
	*/
	SPLoadInfo* LoadLoadingDataLDT(int iItemID = 0);

	/**
	 * LoadInfo�� ������ ���� �ʿ��� ���ҽ��� �д´� <br>
	 @param NONE
	 @return int
	*/
	int			LoadLoadingImage();

	SPGMESSAGE_MAP_DECLARE()
	int			OnLoadSetStage				(WPARAM wparam, LPARAM lparam);
	int			OnLoadSetGroup				(WPARAM wparam, LPARAM lparam);
	int			OnSocketFailed				(WPARAM wparam, LPARAM lparam);
	//int		OnGOBEnter					(WPARAM wparam, LPARAM lparam);
	//SPGMESSAGE_COMMAND( SPGM_GOB_ENTER_EX			, OnGOBEnterEx	)

	void InitLoadingThread();
	friend DWORD WINAPI LoadingThread(LPVOID lParam);

protected:
	SPTexture*				m_pImageBack;
	SPTexture*				m_pImageGauge;
	SPTexture*				m_pImageWrap;

	LOAD_STATE				m_LoadState;
	LOAD_STATE				m_LoadStateNext;	//[2005/9/9] /**< �߰��� ������ ���� ���� �ε��� ���¸� �����Ѵ� <br> */
	float					m_fLoadProtage;
	float					m_fProtage;			//[2005/9/9] /**< Render Protage <br> */

	float					m_fLastRenderDelay;	//[2005/9/13]/**< �� LoadStatus �� ������ �ð��� ��� <br> */
	float					m_fAccumulateRender;//[2005/9/9] /**< ������ �ð� ��� <br> */
	float					m_fCurDelay;		//[2005/9/9] /**< ������ ���� �ð� <br> */
	
	RECT					m_RectGauge;
	RECT					m_RectBack;
	RECT					m_RectLog;

	int						m_iStageID;		//[2005/4/13] /**< Stage ID <br> */
	int						m_iMapGroupID;	//[2005/4/13] /**< Map Group ID <br> */
	
	RECT		m_rtSrc1;		//[2005/3/21] /**< �̹��� 1 �� <br> */
	RECT		m_rtSrc2;		//[2005/3/21] /**< �̹��� 2 �� <br> */
	RECT		m_rtSrc3;		//[2005/3/21] /**< �̹��� 3 �� ���� �ٴ� <br> */
	RECT		m_rtSrc4;		//[2005/3/21] /**< �̹��� 4 �� �ٴ� <br> */
	RECT		m_rtSrc5;		//[2005/3/21] /**< �̹��� 5 �� �ٴ� <br> */
	RECT		m_rtSrc6;		//[2005/3/21] /**< �̹��� 6 �� �ٴ� <br> */

	RECT		m_rtDest1;		//[2005/3/21] /**< �̹��� 1 �� <br> */
	RECT		m_rtDest2;		//[2005/3/21] /**< �̹��� 2 �� <br> */
	RECT		m_rtDest3;		//[2005/3/21] /**< �̹��� 3 �� ���� �ٴ� <br> */
	RECT		m_rtDest4;		//[2005/3/21] /**< �̹��� 4 �� �ٴ� <br> */
	RECT		m_rtDest5;		//[2005/3/21] /**< �̹��� 5 �� �ٴ� <br> */
	RECT		m_rtDest6;		//[2005/3/21] /**< �̹��� 6 �� �ٴ� <br> */

	SPLDTFile*	m_pLDTLoadData;	//[2005/9/14] /**< Load Image Data LDT <br> */
	SPLoadInfo*	m_pLoadInfo;	//[2005/9/14] /**< �ε� �� �ʿ��� �̹��� ������ ����.. <br> */
	SPTexture*	m_pImageLoad[MAX_IMAGE_LIST]; /**< �ε��� �ʿ��� ���� �̹��� <br> */

	HANDLE m_hThreadHandle;
	volatile bool m_bSendKeepAlive;
	volatile bool m_bThreadExit;
};







