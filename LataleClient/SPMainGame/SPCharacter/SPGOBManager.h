// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPGOBManager
// Comment     : 
// Creation    : metalgeni 2004-08-23 ���� 2:56:36
//***************************************************************************


#pragma once 

class SPGameObject;
class SPPlayer;
class SPMonster;
class SPLootingBag;
class SPGOBCluster;
class SPMOBCluster;
class SPBattleCluster;
class SPEvent;					//[2005/4/25] - jinhee
class SPGuildArchive;
//class SPMouseCursor;			//[2005/5/6] - jinhee
class SPChatBoard;				//  [4/10/2008 AJJIYA]
enum SP_FXM_RENDER_LAYER;

typedef int ( *PNameOutPut )( const char* playName );

class SPGOBManager : public SPManager {
public:

	SPGOBManager();
	virtual ~SPGOBManager();

	virtual void	Process(float fTime);
	void			ProcessJoyPad(float fTime);			//[2007/5/28]-jinhee
	virtual	void	Render(float fTime);
	void			RenderLayer2(float fTime);
	void			RenderLayer3(float fTime);			//jinhee - [2005/1/24]
	void			RenderFX( float fTime , SP_FXM_RENDER_LAYER eRenderLayer );

	virtual bool	Init();
	virtual void	Clean();	
	virtual bool	PurgeAll();			// Purge Instant Data for Subgame Change
	virtual int		SPPerformMessage	(UINT msg, WPARAM wparam = 0, LPARAM lParam = 0);

	SPGameObject*	Find( INSTANCE_ID InstanceID, CLASS_ID ClassID = CLASS_ID_NULL);
	SPGameObject*	Find( GU_ID guid );
	SPPlayer*		FindPlayerByName( const char* pCharName  ) ;

	SPPlayer*		AddPlayer(float fX, float fY);	
	SPPlayer*		AddPlayer(CPacket* pPacket, bool bLocalPlayer = false);
	SPMonster*		AddMonster(CPacket* pPacket, CLASS_ID ClassID);
	SPMonster*		AddMonster(float fX, float fY, CLASS_ID ClassID);
	SPLootingBag*	AddLootingBag(CPacket* pPacket, CLASS_ID ClassID, INSTANCE_ID InstanceID);
	SPEvent*		AddEvent(CPacket* pPacket, CLASS_ID ClassID, INSTANCE_ID InstanceID);	//[2005/4/25] - jinhee
	bool			AddGameObject(SPGameObject* pkGameObject, int iObjectType);
	bool			AddChatBoard( CPacket* pPacket , CLASS_ID eClassID, INSTANCE_ID eInstanceID );	//  [4/10/2008 AJJIYA]
	bool			AddMsgBoard( CPacket* pPacket , CLASS_ID eClassID, INSTANCE_ID eInstanceID );	// {xialin 2008/09/10]add
	bool			AddShopPet( CPacket* pPacket , CLASS_ID eClassID, INSTANCE_ID eInstanceID );

	bool			DelObject( INSTANCE_ID InstanceID, CLASS_ID ClassID);

	bool			ResetObject();		//Local Player�̿��� ��� ������Ʈ�� ����

	SPPlayer*		GetLocalPlayer()	
	{ 	
		return m_pLocalPlayer;
	}

	SPGuildArchive* GetGuildArchive() ;	

	SPGOBCluster*	GetGOBCluster()		{ return m_pGOBCluster; }
	bool			SetLocalPlayer(SPPlayer* pPlayer);

	SPGameObject* GetLootingBag(float fPosX, float fPosY, SPGameObject* pkExceptObject = NULL, bool bUsedDistance = true);

	int GetLootingBagSize();
	SPGameObject* GetLootingBag(int iIndex);

	int GetAllMonster(std::vector< SPGameObject* >& vMOBList);
	int GetAllPlayer(std::vector< SPGameObject* >& vPlayerList);
	
	/**
	 * ��� �÷��̾� �ϰ��� ��Ƽ���� ǥ�� ���� <br>
	 @param bool bShowByPvp = false				true�� ��� ��� ǥ�� ���� false �ΰ�� Option�� ���� ����
	 @return  
	*/
	void SetAllPlayerWantTeam(bool bShowByPvp = false);

	/**
	* EventList�� Object���� Quest���� FX�� �����ش� <br>
	@param NONE
	@return NONE
	*/
	void ClearEventQuestFx();

	/**
	 * EventList�� Object���� Quest���� Fx�� �ٽ� �����ϰ� �Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void CheckEventQuestFx();
	
	/**
	 * ExecutePotalEvent <br>
	 * OnEventMessage() �� �̺�Ʈ�� ��Ż�ΰ�� �����Ѵ� <br>
	 @param int iStage
	 @param int iGroup
	 @param float fPosX = 0.0f
	 @param float fPosY = 0.0f
	 @return bool 
	*/
	bool ExecutePotalEvent(int iStage, int iGroup, float fPosX = 0.0f, float fPosY = 0.0f);	

	/**
	* ���� ������ ������ �ߺ��Ǵ� ������ �ִ��� Ȯ���Ѵ� <br>
	* ������ ��ȭ���� �ִ����� Ȯ���Ѵ� <br> 
	@param int iShopType = 0 �����Ϸ��� ���λ��� ����
	@return bool (true�� ��� �ߺ� ����)
	*/
	bool CheckUserShopOverlap(int iShopType = 0);


	//[xialin 2008/09/11]add
	bool CheckMsgBoardOverlap(int iMsgType, int iPosX, int iPosY);

	/**
	 * ������ ������ �ߺ��Ǵ� ������ �����ϴ��� Ȯ���Ѵ� <br> 
	 @param RECT rtLocal üũ �� Local Rect (���� �÷��̾��� ���λ��� ũ�⺰�� ���̳�)
	 @return  bool (true�� ��� �ߺ� ����)
	*/
	bool IsUserShopRect(RECT rtLocal);


	//[xialin 2008/09/11]add
	bool IsTerrainBack( RECT rcLocal );

	//[xialin 2008/09/11]add
	bool IsMsgBoardRect( RECT rcBound , bool bScreenPos );

	//[xialin 2008/09/11]add
	bool IsEventRect( RECT rcBound , bool bScreenPos );

	/**
		GuildCrop�� LevelUp�� Npc�� Image�� �������ִ� �Լ�
	*/
	bool UpdateEventNPC(INSTANCE_ID InstanceID, CLASS_ID ClassID, UINT32 ObjectImageID) ;

	bool IsChatBoardRect( RECT rcBound , bool bScreenPos );	// �ʵ��� ä�ú��� ���� �˻� [5/23/2008 AJJIYA]
	bool IsPetShopRect(RECT rtLocal);

	virtual int	WndProc(UINT message, WPARAM wParam, LPARAM lParam);
	int PerformMouseMove		( int iX, int iY);
	int PerformMouseLDown		( int iX, int iY);
	int PerformMouseLUp			( int iX, int iY);
	int PerformMouseRDown		( int iX, int iY);
	int PerformMouseRUp			( int iX, int iY);
	int PerformMouseLDBLClick	( int iX, int iY);
	int PerformMouseRDBLClick	( int iX, int iY);	

protected:
	bool SendPlayerBlockExist(std::string strCharName = "");
	void GetPlayerInfo();

	SPGMESSAGE_MAP_DECLARE()
	int OnInit				(WPARAM wparam, LPARAM lparam);
	int OnPurgeAll			(WPARAM wparam, LPARAM lparam);
	int OnAddGameobj		(WPARAM wparam, LPARAM lparam);
	int OnDelGameobj		(WPARAM wparam, LPARAM lparam);
	int OnSetLocalPlayer	(WPARAM wparam, LPARAM lparam);
	int	OnGOBAddObjID		(WPARAM wparam, LPARAM lparam);

	int OnAddLocalPlayer	(WPARAM wparam, LPARAM lparam);	

	int OnAddEnterPlayer	(WPARAM wparam, LPARAM lparam);
	int OnAddEnterPlayerEx	(WPARAM wparam, LPARAM lparam);
	int OnAddLeavePlayer	(WPARAM wparam, LPARAM lparam);
	int OnGOBMove			(WPARAM wparam, LPARAM lparam);	

	int	OnPlayerEquipDefaultChange	(WPARAM wparam, LPARAM lparam);
	int	OnPlayerEquipChange			(WPARAM wparam, LPARAM lparam);
	
	int OnEventMessage		(WPARAM wparam, LPARAM lparam);			//Server �ʿ��� Event ���� �޽����� �� ��� ó��
	int OnSendEnterStageMessage		(WPARAM wparam, LPARAM lparam); //Server������ Ŭ���̾�Ʈ �ε� �Ϸ� �޽��� ����

	int OnPlayerBlockExist (WPARAM wParam, LPARAM lParam);	//[2005/9/2] ���� �ٸ� ���������� ����� �Ǿ������� ���� �Ǵ�...
	int OnRefreshNameColor(WPARAM wParam, LPARAM lParam);
	
private:

	std::vector<SPGameObject*> m_vpGameObjPlayer	;	
	std::vector<SPGameObject*> m_vpGameObjMonster	;	
	std::vector<SPGameObject*> m_vpGameObjEvent		;	//[2005/4/25] - jinhee
	std::vector<SPGameObject*> m_vpGameObjLootingBag;
	std::vector<SPGameObject*> m_vpGameObjChatBoard;	//  [4/10/2008 AJJIYA]
	std::vector<SPGameObject*> m_vpGameObjMessageBoard;	//  [xialin 2008/09/10]add
	std::vector<SPGameObject*> m_vpGameObjShopPet;

	std::vector<UINT32>        m_vPlayerID; //���볡����� ID

	INSTANCE_ID			m_LastInstance;	
	SPGOBCluster*		m_pGOBCluster;
	SPMOBCluster*		m_pMOBCluster;
	SPGuildArchive*		m_pGuildArchive ;

	SPBattleCluster*	m_pBattleCluster;	

	SPPlayer*			m_pLocalPlayer;

	GU_ID				m_iSendPlayerInfo;				//[2005/9/2] - �÷��̾� �������� ��Ŷ�� ��û�ߴ���?

	int					m_iCursorX;
	int					m_iCursorY;
	bool				m_bJoyPadLPush;			/**< <br> */
	bool				m_bJoyPadRPush;			/**< <br> */
private:

	int					GmOutPutPlayName( const char* pName );
};


extern SPGOBManager* g_pGOBManager;






