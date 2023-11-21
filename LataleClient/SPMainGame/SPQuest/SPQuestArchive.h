#ifndef __SPQUEST_ARCHIVE_H__
#define __SPQUEST_ARCHIVE_H__

class SPQuestAttr;

class SPQuestArchive
{
public:
	SPQuestArchive();
	~SPQuestArchive();
	
	/**
	 * ��� QuestList�� ���� �����͸� ���� <br>  
	 @param NONE
	 @return NONE
	*/
	void DeleteAllQuest();

	/**
	 * ��� QuestList�� ���� �����͸� �ʱ�ȭ <br>
	 @param  NONE
	 @return NONE
	*/
	void ClearAllQuest();

	/**
	 * �־��� ������ ��ŭ�� ����ִ� QuestList ���� <br> 
	 @param  int iSize = 0
	 @return NONE
	*/
	void InitQuestList(int iSize = 0);
	
	/**
	 * �־��� QuestAttr�� ����Ʈ �������� �߰��Ѵ� <br> 
	 @param SPQuestAttr* pQuestAttr
	 @return int �߰��ѵ� ����Ʈ�� ������
	*/
	int AddQuest(SPQuestAttr* pQuestAttr);

	/**
	 * �־��� ID�� ����Ʈ�� �����Ѵ� <br>
	 @param int iQuestID
	 @return int
	*/
	int DeleteQuest(int iQuestID);
	
	/**
	 * �־��� �ε����� Quest ������ �����´� <br> 
	 @param int iIndex
	 @return SPQuestAttr*
	*/
	SPQuestAttr* GetQuestAttr(int iIndex);

	/**
	 * �־��� QuestID�� Quest ������ �����´� <br>
	 @param int iQuestID
	 @return SPQuestAttr*
	*/
	SPQuestAttr* GetQuest(int iQuestID);

	/**
	 * ���� ����Ʈ�� ����� �����´� <br> 
	 @param 
	 @return
	*/
	int GetSize();

	/**
	* ���� ����Ʈ�� ����� �����´� <br> 
	@param 
	@return
	*/
	int GetShowSize();
	
	/**
	 * ���� �������� PC ����Ʈ�� ��� ó�� ������ <br>
	 * ��������� ������ �̼������� �����Ѵ� <br>
	 @param MISSION* pMission
	 @return int
	*/
	int SetMissionInfo(MISSION* pMission);

	/**
	* ���� ����Ʈ�� ��� ����Ʈ�� �䱸������ ���� ������ ���¸� �����ϵ��� �Ѵ� <br> 
	* ���� ������ �� ����Ʈ ������ m_iUIShow�� �����ȴ� <br>
	@param  NONE
	@return NONE
	*/
	void CheckRequireStat();
	
	/**
	 * ������ ȹ��� ����Ʈ ����Ʈ���� �ش� �������� �ʿ���ϴ� �̼��� ã�� ���� <br>
	 @param int iItemID
	 @return int (������Ʈ �� �̼��� ��)
	*/
	int	CheckMissionItem(int iItemID);

	/**
	 * ����, �׼�, ���̺�Ʈ�� ��� ����Ʈ ����Ʈ���� �ش��� ���� �ʿ�� �ϴ� �̼��� ã�� ���� <br>
	 @param MISSION* pMission
	 @return int (������Ʈ �� �̼��� ��)
	*/
	int CheckMission(MISSION* pMission);

	/**
	 * ����Ʈ �� �׼ǹ̼��� �ִ°�� �־��� Action�� �˻��Ͽ� <br>
	 * ������ ��Ȳ�̶�� �̼� TypeID (�˻��� ����Ʈ)�� �����Ѵ� <br>
	 @param int iAction
	 @return int QuestAttr.m_Missin[i].m_iMissionTypeID
	*/
	int CheckAction(int iAction);

	/**
	 * ����Ʈ �� �׼� ���̺�Ʈ�� �ִ� ��� �־��� MapEvent�� �˻��Ͽ� <br>
	 * ������ ��Ȳ�̶�� ���� ���θ� �����Ѵ� <br>
	 * ���� ���� �ʿ��� ��Ȳ�� ���� ���̺�Ʈ �޽����� ������ ������ <br> 
	 @param int iEventID
	 @return bool
	*/
	bool CheckMapEvent(int iEventID);


	/**
	 * �־��� ����Ʈ ������ ��� �̼��� �Ϸ��� �������� Ȯ���Ѵ� <br>  
	 @param SPQuestAttr* pQuestAttr
	 @param bool bMsg = true		true�� ��� ä��â�� ����Ʈ �Ϸ� �޽��� ���
	 @return bool
	*/
	bool CheckMissionAllClear(SPQuestAttr* pQuestAttr, bool bMsg = true);

	/**
	 * ����Ʈ ����Ʈ�� RewordNpcID�� ������������ �����Ѵ� <br>
	 * ������ Player ���� ����Ʈ �ʸ� �����Ѵ� <br>
	 @param NONE
	 @return bool
	*/
	bool SetSort();
	

protected:
	std::vector<SPQuestAttr*> m_vpQuest;			/**< ��ī�̺갡 ���ϴ� ����Ʈ�� ����Ʈ <br> */
};

#endif