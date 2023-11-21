#pragma once

#define WIID_PCTALK_BASE		(WIID_PCTALK	+	1 )
#define WIID_PCTALK_PCNAME		(WIID_PCTALK	+	10 )
#define WIID_PCTALK_LINE		(WIID_PCTALK	+	20 )
#define WIID_PCTALK_MESSAGE		(WIID_PCTALK	+	30 )
#define WIID_PCTALK_MESSAGE_L	(WIID_PCTALK	+	31 )
#define WIID_PCTALK_MENU		(WIID_PCTALK	+	50 )
#define WIID_PCTALK_BUTTON		(WIID_PCTALK	+	100 )


enum PC_MENU {
	PC_MENU_0,
	PC_MENU_1,
	PC_MENU_2,
	PC_MENU_3,
	PC_MENU_MAX,
};


enum TALK_FADE;
enum TALK_STATE;

class SPWindowPcTalk : public SPWindow {

public:	
	SPWindowPcTalk(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowPcTalk();

	virtual void Init();
	virtual void Clean();
	//virtual void SetFocus();

	virtual void Show(bool bWithChild = true);
	void ShowComplete();

	virtual void Hide(bool bSendServer = true);


	virtual void Process(float fTime);
	virtual void Render(float fTime);

protected:
	/**
	 * ���� ��Ʈ���� �ʱ�ȭ�Ѵ� <br> 
	 @param 
	 @return  
	*/
	void	InitSubControl();
	
	/**
	 * ���ڿ� ��� ���� ��Ʈ���� �ʱ�ȭ �Ѵ� <br> 
	 @param 
	 @return  
	*/
	void	ClearMenuText(bool bMenu);
	
	/**
	 * �޴� ���ý� ������ ������ �Ѵ� <br> 
	 @param 
	 @return  
	*/
	int		SetSelectItem(int iItem);	

	/**
	* �ش� index�� NpcTalkData�� Hander���� �ε��� �����ϵ��� �Ѵ� <br>
	* ���ο��� SetNpcTalk�� ȣ���Ѵ� <br> 
	@param 
	@return NONE
	*/
	void SetNpcTalkData(int iTalkIndex = 0);

	/**
	* �ε��� NpcTalkData�� BoxPos�� ���� ���� NpcTalk������ ���� <br>
	@param 
	@return NONE
	*/
	void SetNpcTalk();	

	/**
	* SavePoint�� ��ġ ���� �޽����� ������ <br> 
	@param NONE
	@return bool
	*/
	bool SendEventPacket();

	/**
	* ������ ������ ��� ���� �����͸� Event Hander�� �ε� �Ҽ� �ֵ��� �ϰ� <br> 
	* NPC Event Shop ���·� �����Ѵ� 
	@param int iTradeIndex = 0			�ε��� ���� ������ �ε���
	@return NONE
	*/
	void SetNpcShopData(int iTradeIndex = 0);

	/**
	* â�� ���·� �ٲ��ش� <br>
	@param NONE 
	@return NONE
	*/
	void SetNpcStorage(int iStorageIndex = 0);

	/**
	* Quest ���·� �ٲ��ش� <br>
	@param 
	@return
	*/
	void SetNpcQuest(int iQuestIndex = 0);

	/**
	* Gift ���·� �ٲ��ش� <br>
	@param 
	@return
	*/
	void SetNpcGift(int iGiftIndex = 0);

	/**
	* Guild ���� ���� ���·� �ٲ��ش� <br>
	@param
	@return
	*/
	void SetNpcGuildCreate(int iGuildIndex = 0);
	
	/**
	 *
	 @param 
	 @return  
	*/
	void SetNpcGuildDissolve(int iGuildIndex = 0);
	
	/**
	 *
	 @param 
	 @return  
	*/
	void SetNpcGuildEnter();
	
	/**
	 *
	 @param 
	 @return  
	*/
	void SetNpcGuildLevelUp(int iGuildIndex = 0);
	
	/**
	 *
	 @param 
	 @return  
	*/
	void SetNpcGuildEmblemChange(int iGuildIndex = 0);	

	/**
	* Npc Portal ���·� �ٲ��ش� <br> 
	@param 
	@return  
	*/
	void SetNpcPortal(int iPortalIndex = 0);

	/**
	* Npc Event ���·� �ٲ��ش� <br> 
	@param 
	@return  
	*/
	void SetNpcEvent(int iEventIndex = 0);

	/**
	*
	@param 
	@return  
	*/
	void SetNpcPvpReserve(int iPvpIndex = 0, bool bParty = false);

	/**
	 *
	 @param 
	 @return  
	*/
	void SetNpcAuction(int iAuctionIndex = 0);

	/**
	 * PC Evnet �����찡 ��Ŀ���� ���������� ���� <br> 
	 * �� ������ Ÿ�� �ʴ� �ڵ尡 ������ ���� <br> 
	 @param 
	 @return  
	*/
	void SetFocusLose(bool bLose = false);

	/**  
	 * NPC Item Option ��й� ���·� �ٲ��ش� <br>
	 @param  
	 @return 
	*/  
	void SetNpcItemReOption(int iReOptionIndex = 0);


	/** W.Fairy : 2008.10.07
	* ��ŷ ���·� �ٲ��ش� <br>
	@param NONE 
	@return NONE
	*/
	void SetNpcRanking(int rec_Index = 0);


protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnHideStart			(WPARAM wParam, LPARAM lParam);				/**< Faid in �۾��� ���� <br> */
	int OnSetNpcData		(WPARAM wParam, LPARAM lParam);				//ó�� SPNpc�� �̿��Ͽ� UI�� �����Ѵ� 
	int OnSetSavePoint		( WPARAM wParam, LPARAM lParam );			//Save Point �̿��Ͽ� UI�� ������ ���
	int OnSetNpcTalk		( WPARAM wParam, LPARAM lParam );			/**< �ܺο��� NPCTALK�� �ε� �ϵ��� ��û�� ��� <br> */
	int OnNpcTalkItemSelect	( WPARAM wParam, LPARAM lParam );			/**< �޴����� ��Ʈ�ѿ� ���� ���� ������ �߻��ϴ� ���� <br> */
	int OnItemSelect		(unsigned int uiID, WPARAM wParam, LPARAM lParam);	/**< OnNpcTalkItemSelect ȣ�� <br> */
	int OnClick				(WPARAM wParam, LPARAM lParam);				/**< �ش� �����찡 Ŭ���� ��� <br> */
	int OnSetFocusLose		(WPARAM wParam, LPARAM lParam);				/**< SetFocusLose ȣ�� <br> */
	// }}
	
private:
	SPWindow*	m_pParent;
	SPTexture*	m_pWindowSkin;					/**< ������ ��Ų �ؽ��� <br> */
	
	RECT		m_rtSkinSrc;					/**< ������ ��Ų �ҽ� ���� <br> */
	RECT		m_rtSkinDest;					/**< ������ ��Ų ��� ���� <br> */
	
	RECT		m_rtSkinBaseDest;				/**< ���� �������� ���� ��� <br> */

	TALK_FADE	m_iTalkFadeMode;				/**< ��Ų ���̵� Ÿ�� <br> */

	int			m_iEndHeight;
	int			m_iEndWidth;
	int			m_iMoveSkinHeight;
	int			m_iMoveSkinWidth;	

	int			m_iSkinMoveX;
	int			m_iSkinMoveY;

	int			m_iSkinMoveUnitX;
	int			m_iSkinMoveUnitY;

	float		m_fFadeAlpha;
	float		m_fFadeAlphaUnit;

	float		m_fAccumulateRender;			/**< ������ �ð� ��� <br> */
	float		m_fCurDelay;					/**< ������ ���� �ð� <br> */
	
	SPWindow*	m_pName;						/**< ���� �̸� ǥ�� <br> */
	SPWindow*	m_pMessage;						/**< ���� �޽��� <br> */
	SPWindow*	m_pLMessage;					/**< ū �޽��� <br> */
	
	SPWindow*	m_pMenu[PC_MENU_MAX];
	SPWindow*	m_pButton[PC_MENU_MAX];			/**< 4���� ���ù� ��ư <br> */
	int			m_iSelectItem;					/**< 4���� ���ù� ��ư �� ���õ� ��ȣ <br> */

	bool		m_bFocusLose;					/**< ��Ŀ���� ���� ��� ǥ�� <br> */
	SPTexture*	m_pFocusLoseSkin;				/**< ��Ŀ���� ���� ��� �߰� ��Ų <br> */
	RECT		m_rtFocusLoseSkinSrc;			/**< ��Ŀ���� ���� ��� �߰� ��Ų �ҽ� <br> */

	TALK_STATE	m_iTalkState;					/**< ���� �����찡 ǥ���ϴ� ��ȭ ��Ȳ <br> */
	SPNpcTalk*	m_pNpcTalk;						/**< NPcTalkData <br> */

	SPSavePoint* m_pSavePoint;					/**< Save Point <br> */

};