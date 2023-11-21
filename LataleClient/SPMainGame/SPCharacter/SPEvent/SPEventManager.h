#pragma once 

class SPEvent;

class SPEventArchive;

class SPEventNpcHandler;

class SPQuestManager;

class SPGiftManager;

class SPMailManager;	

class SPUserShopArchive;

class SPWayPointManager;

class SPCoreEventManager;

class SPClassChangeManager;

////
//enum CHECK_STATUS_RESULT {
//	CHECK_STATUS_RESULT_FAIL = 0,
//	CHECK_STATUS_RESULT_V1 = 1,
//	CHECK_STATUS_RESULT_V2 = 2,
//	CHECK_STATUS_RESULT_OK = 3,
//	CHECK_STATUS_RESULT_MAX = 4,
//};

enum CUT_IN_STATE;

//const int MAX_HIDE_TOP = 113;
//const int MAX_HIDE_BOTTOM = 514;

/**
* @class SPEventManager
* @brief �̺�Ʈ���� �ൿ�� ���� ����(����)�Ѵ� 
* @author Jinhee
* @version 00.00.01
* @date 2005.5.1
* @bug ����
* @warning 
*/
class SPEventManager : public SPManager {
public:
	SPEventManager();
	virtual ~SPEventManager();

	virtual void Process	(float fTime);
	virtual	void Render		(float fTime);
	//virtual void RenderTextDebug();
	//virtual void RenderText();

	virtual bool Init();
	virtual void Clean();
	
	virtual int SPPerformMessage	(UINT msg, WPARAM wparam = 0, LPARAM lParam= 0);	
	
	
	/**
	 *
	 @param
	 @return
	*/
	void	SetCutIn(bool bCutIn = false);
	
	/**
	 *
	 @param
	 @return
	*/
	bool	IsCutIn();	

	/**
	 * ���� �������ͽ� ���¸� �����Ѵ� <br>
	 @param CUT_IN_STATE iCutInState = CUT_IN_STATE_NULL	������ ���� �������ͽ� 
	 @param , int iEventID = 0								���� �߻��� �̺�Ʈ�� ID
	 @return NULL
	*/
	void	SetCutInState(CUT_IN_STATE iCutInState = CUT_IN_STATE_NULL, MAPEVENT_INFO* pEvent = NULL);
	
	/**
	 * 
	 @param 
	 @return
	*/
	CUT_IN_STATE GetCutInState();

	/**
	 *
	 @param
	 @return
	*/
	SPEventNpcHandler* GetEventHandler();
	
	/**
	 * QuestManager�� �����´� <br> 
	 @param NONE
	 @return SPQuestManager*
	*/
	SPQuestManager* GetQuestManager();

	/**
	 * Event, Npc, QuestList, QuestAttr�� ������ ��� ���ϰ� ���� <br> 
	 @param 
	 @return
	*/
	SPEventArchive*	GetEventArchive();

	/**
	 * GiftManager�� �����´� <br>
	 @param 
	 @return
	*/
	SPGiftManager* GetGiftManager();

	/**
	 * MailManager�� �����´� <br>  
	 @param 
	 @return
	*/
	SPMailManager* GetMailManager();

	/**
	 * 
	 @param 
	 @return
	*/
	SPUserShopArchive* GetUserShopArchive();

	/**
	 * WayPoint Manager�� �����´� <br>  
	 @param 
	 @return
	*/
	SPWayPointManager* GetWayPointManager();

	/**
	 * core Event Manager�� �����´� <br>
	 @param 
	 @return  
	*/
	SPCoreEventManager* GetCoreEventManager();

	/**
	 * Class Change Manager�� �����´� <br>
	 @param 
	 @return  
	*/
	SPClassChangeManager* GetClassChangeManager();

	/**
	 * ������ �����Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void OnCutInStart();

	/**
	 * ������ �����Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void OnCutInEnd();

	/**
	 * �̺�Ʈ ��Ŷ�� ���� �÷��װ� ������ ��� �ε��� ȣ���� �ʱ�ȭ ���ش� <br> 
	 @param bool bSend = false
	 @return bool 
	*/
	bool SetEventPacketSendFlag(bool bSend = false)	{
		m_bSendPacket = bSend;
		return m_bSendPacket;
	}
	
	void SetEventBlock(bool bBlock) { m_bEventBlock = bBlock; }
	
	//true�� ��� �̺�Ʈ���� ���Ѵ� <br>
	bool IsEventBlock() { return m_bEventBlock; }

	/**
	 * 
	 @param 
	 @return
	*/
	EVENT_TYPE GetCutInEvnetType() {
		if(m_pEvent) {
			return (EVENT_TYPE)m_pEvent->eventType;
		}

		return EVENT_NULL;
	}

	/**
	 * ���� �������� �̺�Ʈ ������ �����´� <br> 
	 @param 
	 @return
	*/
	MAPEVENT_INFO* GetCurEvent() {
		if(m_pEvent)
			return m_pEvent;

		return NULL;
	}

	void SetCoreRequireAttr(SPCoreRequireAttr* pAttr);
	SPCoreRequireAttr* GetCoreRequireAttr();
	CUT_IN_STATE GetNextCutInStateByCoreEvent();

protected:
	//SPIMESSAGE_MAP_DECLARE()

	/**
	 * ���θ��� ���� ������ ��û <br>
	 @param int iNpcID = 0
	 @return NONE
	*/
	void SendCutInStart(UINT32 iNpcID = 0);
	
	/**
	 * ���θ�忡�� ������ ������ ��û <br>
	 @param int iNpcID = 0
	 @return NONE
	*/
	void SendCutInEnd(UINT32 iNpcID = 0);


protected:
	SPEventArchive*			m_pEventArchive;		/**< Map Event Data Pool <br> */
	SPEventNpcHandler*		m_pNpcHandler;			/**< NPC Handler <br> */
	bool					m_bCutInRender;			/**< CutIn Render Flag <br> */

	SPQuestManager*			m_pQuestManager;		/**< Quest Manager <br> */
	
	MAPEVENT_INFO*			m_pEvent;				/**< ���� �������� �̺�Ʈ�� ����Ѵ� <br> */

	bool					m_bSendPacket;			/**< �ߺ� ������ ���� ���ؼ�... <br> ��Ŷ�� ������ true <br> */

	bool					m_bEventBlock;			/**< �����, �Ǵ� �ε��� Event �� <br> */

	SPGiftManager*			m_pGiftManager;			/**< ���� �޴��� <br> */
	SPMailManager*			m_pMailManager;			/**< Mail Box Manager <br> */
	SPUserShopArchive*		m_pUserShopArchive;		/**< User Shop Data Pool <br> */
	SPWayPointManager*		m_pWayPointManager;		/**< WayPoint Manager <br> */
	SPCoreEventManager*		m_pCoreEventManager;	/**< Core Event Manager<br> ���� �̺�Ʈ <br> */
	SPClassChangeManager*	m_pClassChangeManager;	/**< Class Change�� Level Up �̺�Ʈ�� ���� <br> */

	SPCoreRequireAttr*		m_pCoreRequire;			/**< <br> */
};


extern SPEventManager*	g_pEventManager;


