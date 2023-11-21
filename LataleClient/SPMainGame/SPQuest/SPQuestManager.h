#ifndef __SPQUEST_MANAGER_H__
#define __SPQUEST_MANAGER_H__


/**
 *  ����Ʈ ���ϰ� ���� <br> 
*/
enum QUEST_RETURN {
	QUEST_RETURN_A_INVAILD			= -102,			/**< ��Ÿ ���� <br> */
	QUEST_RETURN_A_FULL				= -101,			/**< ����Ʈ ����Ʈ Ǯ <br> */
	QUEST_RETURN_A_INVEN			= -100,			/**< �κ��丮 ���� ���� <br> */
	
	QUEST_RETURN_F_SLOT				= -4,			/**< �������� �ʹ� �л�Ǿ� ���� <br> */
	QUEST_RETURN_F_INVAILD			= -3,			/**< ��Ÿ ���� <br> */
	QUEST_RETURN_F_NOTCOMPLETE		= -2,			/**< �Ϸ����� ���� <br> */
	QUEST_RETURN_F_NPC				= -1,			/**< ������� NPC Error <br> */
	QUEST_RETURN_F_INVEN			= 0,			/**< �κ��丮 ���� ���� <br> */
	QUEST_RETURN_OK					= 1,			/**< OK <br> */
};

class SPLDTManager;
class SPLDTFile;

class SPRewardArchive;
class SPQuestAttr;
class SPQuestArchive;

class SPQuestManager
{
public:
	static SPQuestManager* GetInstance();
	static void Release();

	bool Init();

	/**
	 * �����ϴ� Quest��ī�̺곻 QuestAttr���� ��� ����� <br> 
	 @param NONE
	 @return NONE
	*/
	void PurgeAll();
	
	/**
	 * NPC�� ����Ʈ ����Ʈ�� �����´� <br>
	 @param NONE
	 @return SPQuestArchive*
	*/
	SPQuestArchive* GetNpcArchive();
	
	/**
	 * PC�� ����Ʈ ����Ʈ�� �����´� <br>
	 @param NONE
	 @return SPQuestArchive*
	*/
	SPQuestArchive* GetPlayerArchive();
	
	/**
	 * PC�� ���� ����Ʈ ����Ʈ�� �����´� <br>
	 @param NONE
	 @return SPQuestArchive*
	*/
	SPQuestArchive*	GetRewordArchive();	

	/**
	 * ���� ������ ���� ����Ʈ�� �����´� <br>
	 * GetRewordArchive�ʹ� �ٸ��� <br>
	 @param 
	 @return
	*/
	SPRewardArchive* GetRewardInfo();

	/**
	* �ش� ID�� ����Ʈ �⺻ ������ LDT���� �о� ����Ʈ ������ �����Ѵ� <br>
	@param int iItemID
	@param SPQuestAttr* pQuestAttr
	@return bool
	*/
	bool LoadLDTFile(int iItemID, SPQuestAttr* pQuestAttr);

	/**
	* NPC�� ���� Quest�� ������ŭ QuestList�� ����� LDT�����͸� �ε��Ѵ� <br>
	@param NONE
	@return bool
	*/
	bool LoadNpcQuest();

	/**
	* NPC ����Ʈ ��ī�̺꿡 ����Ʈ ���� �߰� <br>
	@param NONE
	@return bool
	*/
	bool LoadQuest(int iQuestID, QUEST_ACCEPTTYPE iType = QUEST_ACCEPTTYPE_NPC , int iTypeID = 0 , bool bRequireCheck = false );

	/**
	* NPC�� ���� ����Ʈ�� �����. UI�ʵ� ���� <br>
	@param NONE
	@return void
	*/
	void DeleteNpcQuest();

	/**
	* NPC�� ���� iQuestID ����Ʈ �ϳ��� �����. UI�ʵ� ���� <br>
	@param int iQuestID
	@return void
	*/
	void DeleteNpcQuest( int iQuestID );
	
	/**
	 * Player�� ���� Quest�� �����Ѵ� <br>
	 @param QUEST* pQuest
	 @param bool bMsg = true			�޽��� ��� ����
	 @return int �����ѵ� ����Ʈ�� ������
	*/
	int SetPlayerQuest(QUEST* pQuest, bool bMsg = true);

	/**
	 * Player�� ���� ���� ���� ����Ʈ �� �̼� ������ �����Ѵ� <br>
	 * ���ο��� ��ī�̺�� �ѱ��... <br>
	 @param MISSION* pMission
	 @return int �̼��� ������ ����Ʈ �ε��� (���� �ε���)
	*/
	int SetPlayerMissionInfo(MISSION* pMission);
	
	/**
	 * �Ϸ� ����Ʈ ��Ͽ��� ���� ������� Ƚ���� ���´� <br>
	 * �Ǵ� ���� �Ϸ� ����Ʈ ��Ͽ� �ִ��� Ȯ���Ѵ� <br>
	 @param  int iQuestID
	 @return int
	*/
	int GetRewordCount(int iQuestID);

	/**
	 * ���� �����Ͽ� �ִ� ����Ʈ ���� Ȯ���Ѵ� <br> 
	 @param int iQuestID
	 @return bool
	*/
	bool IsDoingQuest(int iQuestID);

	/**
	 * 
	 @param 
	 @return
	*/
	bool IsRewordQuest(int iQuestID);
	
	/**
	 * �÷��̾� ������ �̼��� ������Ʈ �Ѵ� <br>
	 * ������ ���� ���ۿ� ���� �̷������ <br>
	 @param MISSION* pMission
	 @return bool
	*/
	bool UpdateMission(MISSION* pMission);
	
	/**
	 * �÷��̾� ������ �̼��� ������ ���ø� ������Ʈ �Ѵ� <br> 
	 * �κ� ��ī�̺꿡 ���� �̷������ <br>
	 @param int iItemID
	 @return int
	*/
	int CheckMissionItem(int iItemID);

	/**
	 * �÷��̾� ������ �̼��� ���̺�Ʈ�� ������ ������ ������ <br>
	 * ������ ������Ʈ ��û�� �ϰ� �Ѵ� <br>
	 @param int iEventID
	 @return bool
	*/
	bool CheckMissionEvent(int iEventID);

	/**
	 * �÷��̾� ������ �̼��� �׼ǿ� ������ ������ ������ <br>
	 * ������ ������Ʈ ��û�� �ϰ� �Ѵ� <br>
	 @param int iAction
	 @return int
	*/
	int CheckMissionAction(int iAction);

	/**
	 * �ش� ����Ʈ�� �����Ҽ� �ִ� ��Ȳ���� �˻��Ѵ� <br>
	 @param int iQuestID
	 @return QUEST_RETURN
	*/
	QUEST_RETURN IsAcceptQuest(int iQuestID);
	
	/**
	 * �ش� ����Ʈ ���� ��û <br>  
	 @param int iQuestID
	 @return ACCEPT_RETURN 
	*/
	QUEST_RETURN SetAcceptQuest(int iQuestID);

	/**
	 * �ش� ����Ʈ ���� ��û <br>
	 @param int iQuestID
	 @return int (���� ������ �������� 1ó��)
	*/
	int SetGiveUpQuest(int iQuestID);
	
	/**
	 * ����Ʈ ���� ��û�� ���� ���� <br> 
	 @param int iQuestID
	 @return NONE
	*/
	bool OnGiveUpQuest(int iQuestID);

	/**
	 * �ش� ����Ʈ�� ��������� �ִ� ��Ȳ���� �˻��Ѵ� <br> 
	 @param int iQuestID
	 @return QUEST_RETURN
	*/
	QUEST_RETURN IsFinishQuest(int iQuestID);

	/**
	 * ����Ʈ �Ϸ� ��û <br> 
	 @param int iQuestID
	 @param int iReward			�������϶� ������ ������ �����ε���(0, 1, 2)
	 @return int 
	*/
	QUEST_RETURN SetFinishQuest(int iQuestID, int iReward = 0);	

	/**
	 * ����Ʈ �Ϸ� ��û�� ���� ���� <br>  
	 * ���� ����Ʈ �Ϸ� ó���� �Ѵ� <br>
	 @param 
	 @return
	*/
	bool OnFinishQuest(QUEST* pQuest);

	/**
	 * �÷��̾� ����Ʈ�� �ʱ�ȭ �Ǹ鼭 �ѹ� �ҵ� �Ǿ�����? <br> 
	 @param NONE
	 @return bool (true�� ��� ��Ʈ �Ǿ�����)
	*/
	bool IsListSort();
	
	/**
	 * ��Ʈ ��Ȳ�� ���� <br>
	 * ���ο��� ��Ʈ <br>
	 @param bool bSort = true
	 @return NONE
	*/
	void SetListSort(bool bSort = true);

	/**
	 * Accept, Give Up, Finish ��Ŷ�� ������ �ش� ��Ŷ������ �ٽ� ���������� Block <br> 
	 @param 
	 @return
	*/
	void ResetSendBlock();

	/**
	* ���� ����Ʈ ��Ŷ�� ������  <br> 
	@param int iQuestID
	@return
	*/
	void SendQuestSharePacket( int iQuestID );

	/**
	* ���� ����Ʈ ��Ŷ�� �޴´�  <br> 
	@param int iQuestID
	@param INT32 iActCharID
	@return
	*/
	void RecvQuestSharePacket( int iQuestID , INT32 iActCharID );

	/**
	* ������ ���� ����Ʈ�� �߰��Ѵ�.	<br> 
	@param int iQuestID
	@param int iItemID
	@return bool
	*/
	bool AddItemQuest( int iQuestID , int iItemID );

protected:
	SPQuestManager();
	virtual ~SPQuestManager();	

	/**
	 * ����Ʈ ������û ��Ŷ�� ���� <br> 
	 @param int iType				���� ����
	 @param int iTypeID				Ÿ�Կ� ���� ��
	 @param int iQuestID			���� �������� ����Ʈ�Ƶ�
	 @return NONE
	*/
	void SendAcceptQuest(int iType, int iTypeID, int iQuestID);

	/**
	 * ����Ʈ �����û ��Ŷ�� ���� <br>
	 @param int iQuestID
	 @return void
	*/
	void SendGiveUpQuest(int iQuestID);

	/**
	 * ����Ʈ �Ϸ� ��û ��Ŷ�� ���� <br> 
	 @param int iNpcID
	 @param int iQuestID
	 @param int iRank				�Ϸ�� ����Ʈ Ŭ���� ��ũ ����
	 @param int iReward				�������϶� ������ ������ �����ε���(0, 1, 2)
	 @return NULL
	*/
	void SendFinishQuest(int iNpcID, int iQuestID, int iRank, int iReward);

	/**
	 * �׼� ���� ��Ŷ�� ���� <br> 
	 @param 
	 @return
	*/
	void SendMissionAction(int iActionID);

	/**
	 * ä��â�� �޽��� ���� <br> 
	 @param 
	 @return
	*/
	void SetReturnMsg(QUEST_RETURN iReturn);

protected:
	static SPQuestManager* ms_pkInstance;
	
	SPRewardArchive* m_pRewardArchive;
	SPQuestArchive* m_pNpcArchive;				/**< NPC�� ����Ʈ ��ī�̺� <br> */
	SPQuestArchive* m_pPlayerArchive;			/**< PC�� ����Ʈ ��ī�̺� <br> */
	SPQuestArchive*	m_pPlayerReword;			/**< PC�� �Ϸ� ����Ʈ ��ī�̺� <br> */
	
	SPLDTFile*		m_pLDTQuestData;			/**< NPC Data LDT <br> */
	bool			m_bSort;					/**< Player Quest List Sort <br> */
	
	bool			m_bSendPacket;				/**< Accept, Give Up, Finish Send�� Ȱ���� ���� ��Ŷ ������ block <br> */	
};

#endif