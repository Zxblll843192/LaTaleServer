#pragma once


class SPWayPointAttr;

const int	MAX_WAY_POINT		= 128;			/**< �ִ� Waypoint �� ���� <br> */

class SPWayPointArchive {
public:
	SPWayPointArchive();
	~SPWayPointArchive();
	
	/**
	 * ��� WayPoint ������ Reset�Ѵ� <br> 
	 @param 
	 @return
	*/
	void ClearAllWayPoint();
	
	/**
	 * LDT���� �⺻ WayPoint������ Load�Ѵ� <br>
	 @param 
	 @return
	*/
	bool LoadLDTData();

	/**
	 * WayPoint ����Ʈ�� �����´� <br>
	 @param 
	 @return
	*/
	std::vector<SPWayPointAttr>*	GetWayPointList();
	
	/**
	 * WayPoint Data�� �ε��� ������ ���� �����´� <br>
	 @param 
	 @return	 
	*/
	SPWayPointAttr* GetWayPoint(int iIndex);
	
	/**
	 * WayPoint Data�� �־��� ID���� ã�� �����´� <br>
	 * ������ NULL <br>
	 @param 
	 @return
	*/
	SPWayPointAttr* FindWayPointByID(int iID);
	
	/**
	 * WayPoint Data�� �־��� MapEventID���� ã�� �����´� <br>
	 * ������ NULL <br>
	 @param 
	 @return
	*/
	SPWayPointAttr* FindWayPointByMapEventID(int iMapEventID);

	/**
	 * ������ <br>
	 @param 
	 @return
	*/
	void PrintSaveInfo();

protected:	

private:
	std::vector<SPWayPointAttr>		m_vpWayPoint;		/**< ��������Ʈ ����Ʈ <br> */
};

