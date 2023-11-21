#pragma once

class SPWayPointAttr;
class SPWayPointArchive;

//const int CHECK_FIELD		=	0x80000000;
const int CHECK_FIELD		=	0x00000001;

class SPWayPointManager {
public:
	SPWayPointManager();
	~SPWayPointManager();

	/**
	 * ĳ���� ����� ��������Ʈ ���� �ʱ�ȭ <br> 
	 @param 
	 @return
	*/
	void ClearWayPoint();

	/**
	 * 
	 @param 
	 @return
	*/
	SPWayPointArchive* GetWayPointArchive();

	/**
	 * Global String�� ������ ��������Ʈ �׷캰 �̸��� �ε��Ѵ� <br> 
	 @param 
	 @return
	*/
	int LoadGroupName();

	/**
	 * ��������Ʈ �׷캰 �̸� ����Ʈ�� �����´� <br> 
	 @param 
	 @return
	*/
	std::vector<std::string>* GetGroupNameList();

	/**
	 * ��������Ʈ �׷� ����Ʈ ����� Ȯ���Ѵ� <br>
	 @param 
	 @return
	*/
	int GetGroupSize();

	/**
	 * WayPoint Data�� �����´� <br>
	 @param 
	 @return
	*/
	SPWayPointAttr* GetWayPoint(int iIndex);
	
	/**
	 * �ش� ID�� WayPoint Data�� �����´� <br>
	 @param 
	 @return
	*/
	SPWayPointAttr* FindWayPointByID(int iID);
	
	/**
	 * �ش� MapEventID�� WayPoint Data�� �����´� <br>
	 @param 
	 @return
	*/
	SPWayPointAttr* FindWayPointByMapEventID(int iMapEventID);

	/**
	 * Save������ ������Ʈ �Ѵ� <br>
	 @param 
	 @return
	*/
	bool SetSaveData(int iSaveInfo[WAYPOINT_SIZE_DATA]);

	/**
	 * �־��� ���̺�Ʈ�� ���� WayPoint�� ����Ǿ� �ִ��� Ȯ���Ѵ� <br>
	 @param 
	 @return bool	false �ΰ�� ���� WayPoint�̰ų� �̹� ����� WayPoint��
	*/
	bool IsNewWayPoint(int iMapEventID);

	/**
	* �־��� ���̺�Ʈ�� ���� WayPoint�� ����Ǿ� �ִ��� Ȯ���Ѵ� <br>
	* ������ ����Ǵ� WayPoint�� ��� ������ ���ο� ���̺�����Ʈ ����� �˸� <br>
	@param 
	@return bool	false �ΰ�� ���� WayPoint�̰ų� �̹� ����� WayPoint��
	*/
	bool SaveNewWayPoint(int iMapEventID);

	/**
	 * ���ο� ��������Ʈ�� ������� ������Ʈ �Ѵ� <br> 
	 @param 
	 @return
	*/
	bool OnUpdateNewWayPoint(int iWayPointID);

	/**
	 * ��������Ʈ �̵� ��û�� �Ѵ� <br>
	 @param 
	 @return
	*/
	bool SendMove(int iWayPointID, int iRank);

	/**
	 * ��������Ʈ �̵� ��û�� ���� <br> 
	 @param 
	 @return
	*/
	bool OnMove(CPacket* packet);

protected:
	

private:
	SPWayPointArchive* m_pWayPointArchive;			/**< ��������Ʈ ������ <br> */
	std::vector<std::string> m_vGroupName;			/**< ��������Ʈ �׷� ������ <br> */
};


