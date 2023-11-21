
// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-17 ���� 2:56:36
//***************************************************************************


#pragma once

class SPManager;
class SPTerrainManager;	
class SPGOBManager;		
class SPFXManager;		
class SPInputManager;		
class SPInterfaceManager;	
class SPCameraManager;	
class SPNetworkManager;
class SPResourceManager;
class SPEventManager;		//[2005/4/20] - jinhee
class SPCheckManager;		//[2005/9/27] - jinhee
class SPLogoThread;


struct ReportStuff {
	GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
	SYSTEMTIME		stServerTime;				// �����ð�
	WORLD_ID		wWorldID;					// ������̵�
	SERVER_ID		wServerID;					// �������̵�
	TCHAR			szAccountID[MAX_LEN_ID];	// �������̵�
	TCHAR			szClientIP[LEN_IP];			// Ŭ���̾�Ʈ������
	TCHAR			szName[LEN_NAME+1];			// ĳ���͸�
	UINT			uiStageID;					// �����������̵�
	UINT			uiMapGroupID;				// �ʱ׷���̵�
	UINT			uiPosX;						// X��ǥ
	UINT			uiPosY;						// Y��ǥ
};




DWORD WINAPI InitializeThread(LPVOID lParam);

class SPMainGameManager {
public:
	SPMainGameManager();
	virtual ~SPMainGameManager();
	
	void					Init();	
	void					InitAllocate();
	void					PostInit();
	void					Render();
	bool					Process();
	
	/**
	 * ���� �޽��� �� <br>  
	 @param float fTime
	 @return NONE
	*/
	void					ProcessNotice(float fTime);
	
	bool					WndProc(UINT message, WPARAM wParam, LPARAM lParam);
	void					RenderText();

	/**
	 * ���� �޽��� �� <br>  
	 @param NONE 
	 @return NONE
	*/
	void					RenderNotice();

	bool					ChangeSubGame(SUBGAME_ID SubGameID, bool bPurgeAll = true);	//bPurgeAll�� �ӽ÷� �߰�
	SUBGAME_ID				GetSubGameID		()	{ return m_pMgrSubGame->GetSubGameID(); }
	SPSubGameManager*		GetSubGameManager	()	{ return m_pMgrSubGame;		}

	SPTerrainManager*		GetTerrainManager	()	{ return m_pMgrTerrain;		}
	SPGOBManager*			GetGOBManager		()	{ return m_pMgrGob;			}
	SPFXManager*			GetFXManager		()	{ return m_pMgrFX;			}
	SPInputManager*			GetInputManager		()	{ return m_pMgrInput;		}
	SPInterfaceManager*		GetInterfaceManager	()	{ return m_pMgrInterface;	}
	SPCameraManager*		GetCameraManager	()	{ return m_pMgrCamera;		}
	SPResourceManager*		GetResourceManager	()	{ return m_pMgrResource;	}
	SPNetworkManager*		GetNetworkManager	()	{ return m_pMgrNetwork;		}
	SPEventManager*			GetEventManager		()	{ return m_pMgrEvent;		}
	void					SetExit()				{ m_bExit = true; }	

	bool					GetRenderDebugInfo()	{ return m_bRenderDebugInfo; }

	void					BeginInitialize();
	bool					GetInitializeComplete()	{ return m_bInitialize; }
	bool					IsProcessReady();
	friend DWORD WINAPI InitializeThread(LPVOID lParam);

	void					OnSetNotice(std::string strMsg, float fDisplayTime = 0, int iOption = 0);

	void					InitLogoDisplay() ;
	void					ProcessLogoDisplay() ;
	void					DestroyLogoDisplay() ;

	void					WebEnableCallBack(bool bEnable);

	bool					SnapShot();	
	bool					ReportShot(ReportStuff* pReportStuff);	


protected:	

	float						m_fOffsetX;
	float						m_fOffsetY;

	bool						m_bActive;

	GAME_STATE					m_iGameState;

	SPCameraManager*			m_pMgrCamera;
	SPTerrainManager*			m_pMgrTerrain;
	SPGOBManager*				m_pMgrGob;
	SPFXManager*				m_pMgrFX;
	SPInputManager*				m_pMgrInput;
	SPInterfaceManager*			m_pMgrInterface;
	SPResourceManager*			m_pMgrResource;
	SPNetworkManager*			m_pMgrNetwork;
	SPEventManager*				m_pMgrEvent;	//[2005/4/20] - jinhee
	SPCheckManager*				m_pMgrCheck;	//[2005/9/27] - jinhee
	SPLogoThread*				m_pLogoDisplay ;

	std::vector<SPManager*>		m_vpManager;

	SPSubGameManager*			m_pMgrSubGame;	

	FLOAT						m_fLastTime;
	FLOAT						m_fElapsedTime;
	FLOAT						m_fFPS;	
	FLOAT						m_fUpdateTime ;
	bool						m_bRenderDebugInfo;

	bool						m_bPlayBGM;
	bool						m_bExit;
	
	bool						m_bInitialize;
	bool						m_bOnceInitialize;
	HANDLE						m_hInitThreadHandle;

	std::string					m_strNotice;			/**< �� ����� �����޽��� <br> */
	std::string					m_strOrgNotice;			/**< �����κ��� ���� �������� ���� �޽��� <br> */
	RECT						m_rtNotice;				/**< ���� ��� ���� <br> */
	FLOAT						m_fAccumulateNotice;	/**< Ÿ�� ���� <br> */
	FLOAT						m_fDelayNotice;			/**< �ʺ��� �����ϱ� ���� �뵵 <br> */	
	FLOAT						m_fEndNotice;			/**< ��ü ����� �ð� �ʴ��� <br> 0�ΰ�� ���������� <br> */	
	
	int							m_iRemainTime;			/**< displayTime �� �ʿ��� ��� <br> */
	char						m_szRemain[32];			/**< ���� �ð� ǥ���� <br> */
	bool						m_bShowAll;				/**< ���������� �����ٰ����� <br> true�� ��� ���� <br> */

	int							m_iReportIndicate;
	
	int							m_iNoticeOption;
};


extern SPMainGameManager*	g_pMainGameManager;
#define g_pSubGameManager	g_pMainGameManager->GetSubGameManager()




