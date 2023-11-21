#pragma once 


#include <bitset>

class SPCoreEventManager {
public:	
	SPCoreEventManager();
	~SPCoreEventManager();

	void RestPlayerMission();
	void SetPlayerMissionData(int iMissionInfo[MAX_EVENT_MISSION_DATA]);
	void SetPlayerMission(int iIndex);
	bool IsCompleteMission(int iIndex);

	SPCoreMissionArchive*	GetMissionArchive();

	bool SendCoreEventRaise(int iMissionID);

private:
	void Clear();
	

private:
	//std::map<int, >		m_mCoreEventReqInfo;
	SPCoreMissionArchive*	m_pMissionArchive;
	std::bitset<MAX_EVENT_MISSION_BIT>	m_bPlayerMission;		/**< ������ �̼� ������ ��� <br> */
};
