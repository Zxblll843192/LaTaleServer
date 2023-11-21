#pragma once

class SPGameObject;
class SPGOBModelUnit;
class SPEventStatusModel;
class SPQuestAttr;

#include "SPEventDEF.h"


const unsigned int EVENT_ID_NULL = 0;			/**< �̺�Ʈ ID NULL ���� <br> */


enum EVENT_QUEST_SHOW {
	EVENT_QUEST_SHOW_NULL = 0,					/**< ������ Quest ���� FX�� ���� <br> */
	EVENT_QUEST_SHOW_COMPLETE = 1,				/**< �� �Ϸᰡ ������ ��� <br> */
	EVENT_QUEST_SHOW_ABLE = 2,					/**< ���� ������ �ִ� ��� <br> */
	EVENT_QUEST_SHOW_MAX						/**< <br> */
};


/**
* @class SPEvent
* @brief �̺�Ʈ ����
* @author Jinhee
* @version 00.00.01
* @date 2005.5.1
* @bug ����
* @warning 
*/
class SPEvent : public SPGameObject 
{

public:
	SPEvent();
	SPEvent(INSTANCE_ID instanceID, CLASS_ID ClassID);
	virtual ~SPEvent();

	virtual void Process(float fTime);
	virtual	void Render(float fTime);
	virtual void Init();	
	virtual void Destroy();
	virtual void RenderFX( float fTime , SP_FXM_RENDER_LAYER eRenderLayer );

	virtual int  PerformMouseMove		( int iX, int iY);
	virtual int  PerformMouseLDown		( int iX, int iY);
	virtual int  PerformMouseLUp		( int iX, int iY);
	virtual int  PerformMouseRDown		( int iX, int iY);
	virtual int  PerformMouseRUp		( int iX, int iY);
	virtual bool IsCursorIn				( int iX, int iY);
	virtual bool IsCursorIn				( RECT & rc );

	void ProcessImage(float fTime);

	FACING	GetDirection();
	
	BG_ID	GetStandLayer();				
	
	void	SetPos(float fX, float fY);

	/**
	 * Event X �� ��ġ�� ���´� <br> 
	 @param NONE
	 @return float Event Pos X
	*/
	float	GetPosX();
	
	/**
	* Event Y �� ��ġ�� ���´� <br> 
	@param NONE
	@return float Event Pos Y
	*/
	float	GetPosY();

	/**
	* Event TYPE �� ���´� <br> 
	@param NONE
	@return EVENT_TYPE
	@warning EVENT_TYPE ���� ������ ������ int �� ��ȯ�ؼ� �������� �ִ�
	*/
	EVENT_TYPE GetEventType();

	/**
	 * Event Name �� ����´� <br> 
	 @param NONE
	 @return string eventName
	*/
	std::string GetEventName();
	
	/**
	 * MAPEVENT_INFO struct �� �������ش� <br>
	 @param MAPEVENT_INFO* pEventInfo = NULL	��Ŷ���� �Ѿ�� MAPEVENT_INFO
	 @return	bool
	*/
	//bool	SetEventInfo(MAPEVENT_INFO* pEventInfo = NULL);
	bool	SetEventInfo(EVENT_INFO* pEventInfo = NULL);
	bool	UpdateModelNpc(UINT32 ObjectImageID) ;		// NPC �̹����� ����
	
	/**
	 * member MAPEVENT_INFO �� ���� �����͸� �ʱ�ȭ �Ѵ� <br>
	 * ��Ÿ �����鵵 �ʱ�ȭ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void	SetNull();

	/**
	 * Window�� ������� �ϴ��� <br> 
	 @param NONE
	 @return bool	(true: show, false: hide)
	*/
	bool	IsMessageShow()		{ return m_bShowWindow; }

	/**
	 * Event Message �� ������ ���´��� <br>
	 @param NONE
	 @return bool	(true: send, false: not)
	*/
	bool	IsSendPacket()		{ return m_bSendPacket; }

	/**
	* Player�� ���Ͽ� ���� �̺�Ʈ�� �����־�� �� <br>
	* Quest Fx�� ǥ���Ѵ� <br>
	@param 
	@return
	*/
	EVENT_QUEST_SHOW CheckEventQuestShow();

	/**
	 * ���� Event�� ��ϵǾ� �ִ� Quest���� FX�� �����Ѵ� <br>
	 @param NONE
	 @return NONE
	*/
	void	ClearEventFX();

protected:
	SPGMESSAGE_OBJ_MAP_DECLARE()
	
	////
	virtual int OnGetPosX	( LPARAM lParam );
	virtual int OnGetPosY	( LPARAM lParam );
	virtual int OnGetFacing(LPARAM lParam);
	virtual int OnGetGOBName( LPARAM lParam );
	virtual int OnGetStandlayer(LPARAM lParam);

	virtual int OnGetFXArchive	( LPARAM lParam );		// AJJIYA [12/16/2006 AJJIYA]	

	/**
	 * ��Ŷ���� �� MAPEVENT_INFO�� SetEventInfo�� SetEventInfo()�� �ѱ� <br>
	 @param LPARAM lParam
	 @return int
	*/
	virtual int OnSetEventInfo(LPARAM lParam);

protected:		
	/**
	 * Event ������ ������ �׷��ش� <br> 
	 * _DEBUG ��� <br>
	 @param NONE
	 @return NONE
	*/	
	void RenderEventLine();

	/**
	 * Player Postion ������ �̿��Ͽ� �̺�Ʈ ������ ��ġ�ߴ��� üũ�Ѵ� <br>
	 @param NONE
	 @return unsgined int EventID
	*/
	unsigned int CheckPlayerEvent();
	
	/**
	 *
	 @param 
	 @return  
	*/
	bool LoadEventCore(int iItemID);
	

	/**
	 * Client�󿡼� Event Data�ε�... <br>
	 @param int iItemID
	 @return bool
	*/
	bool LoadEventLDT(int iItemID);

	/**
	 * NpcLdt���� �ʿ��� ���� Npc�� ���ϰ� �ִ� questlist�� ����� ������ �Ѵ� <br> 
	 @param 
	 @return
	*/
	int LoadNpcLDT(int iItemID);

	/**
	 * NpcQuest List�� ���� ����Ʈ ����Ʈ�� �߰��ϰ� <br>
	 * EVENT_QUEST_SHOW�÷��� ���� �۾��� �Ѵ� <br>
	 @param 
	 @return
	*/
	int LoadNpcQuestList(int iItemID);

	/**
	 * NpcQuest List�� ����Ʈ�� �߰��Ѵ� <br>
	 @param 
	 @return
	*/
	bool AddQuestList(int iQuestID);	

	/**
	* Event Message �� ������ ������ <br>
	@param NONE
	@return bool
	*/
	bool	SendEventPacket();

	/**
	 * Local Player�� Status ������ üũ�Ѵ� <br>
	 * �� �Լ��� ���� ��� �ְ� �ܺο��� üũ �Ҽ� �ֵ��� �ؾ� �ҵ��ϴ� <br>
	 @param NONE
	 @return bool
	*/
	bool CheckRequire();

	/**
	 * ���� �̺�Ʈ Require������ üũ�Ѵ� <br>
	 @param 
	 @return  
	*/
	bool CheckCoreRequire();

	/**
	 * ���� �̺�Ʈ Requireüũ�� �κ��丮�� �� ������ üũ���ش� <br>
	 @param 
	 @return  
	*/
	bool IsEnableInven(SPCoreRequireAttr* pCoreReq);
	
	/**
	 * ���� �̺�Ʈ Requireüũ�� �÷��̾��� ���� ������ ����Ʈ ������� üũ���ش� <br>
	 @param 
	 @return  
	*/
	bool IsEnableQuestSize(SPCoreRequireAttr* pCoreReq);

	/**
	 * ...<br> 
	 @param 
	 @return
	*/
	void ChangeAnimation();

	/**
	 * ��� QuestList�� �����Ѵ� <br>
	 @param 
	 @return
	*/
	void DeleteAllQuest();

	/**
		Dynimic Event �� ��� DynimicFx�� �����ؾ� �� ���� �ִ�.
	*/
	void SetDynimicFX() ;

private:
	// Action
	UINT64 m_uiCurAction;
	UINT64 m_uiLastAction;

	float m_fPlayerX;						/**< Local Player Pos X <br> */
	float m_fPlayerY;						/**< Local Player Pos Y <br> */

	float m_fCamX;							/**< Camera Pos X <br> */
	float m_fCamY;							/**< Camera Pos Y <br> */

	float m_fMouseX;						/**< Mouse Pos X <br> */
	float m_fMouseY;						/**< Mouse Pos Y <br> */
	int	m_iLClick;							/**< Mouse Left Button Click <br> */
	
	SPFXArchive*			m_pkFXArchive;	// AJJIYA [11/28/2005]

	MAPEVENT_INFO	m_MapEvent;				/**< Map Event Struct <br> */
	RECT			m_rtEvent;				/**< Event Area Rect <br> */
	bool			m_bShowWindow;			/**< Window Show Flag <br> */
	bool			m_bSendPacket;			/**< Event Send Packet <br> */
	bool			m_bRunCoreEvent;		/**< Core Event Running Flag <br> */

	FACING			m_eFacing;
	float			m_fAnimationTime;
	
	SPGOBModelUnit*	m_pkModelUnit;			/**< Render Model <br> */
	SPEventStatusModel*	m_pkStatusModel;
	
	int		m_iQuestListID;
	std::vector<SPQuestAttr*> m_vpQuest;	/**< Event�� Npc�̰� Quest�� ���� ��� ���ϰ� �ִ� QuestList <br> */
	EVENT_QUEST_SHOW m_iEventQuestShow;		/**< Evnet�� Npc�̰� Quest�� ���� ��� FX ǥ�ÿ� <br> */
	
	std::vector<SPCoreRequireAttr*> m_vpCoreRequire;
};

