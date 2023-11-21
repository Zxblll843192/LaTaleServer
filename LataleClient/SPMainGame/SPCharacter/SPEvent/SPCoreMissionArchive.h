#pragma once 

class SPCoreMissionAttr;

class SPCoreMissionArchive {
public:
	SPCoreMissionArchive();
	~SPCoreMissionArchive();
	
	bool LoadCoreMissionLDT();

	/**
	 * �־��� ID�� MissionAttr�� �����´� <br>
	 @param 
	 @return  
	*/
	SPCoreMissionAttr*	GetCoreMissionAttr(int iItemID);
	
	/**
	 * �־��� SavePosition�� ���ϴ� MissionAttr�� ã�Ƴ��� <br>
	 @param 
	 @return  
	*/
	SPCoreMissionAttr*	FindMissionAttr(int iSavePos);

private:
	/**
	 * ��� MissionAttr�� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void DeleteAllCoreMission();
	
	/**
	 *
	 @param 
	 @return  
	*/
	void Clear();

private:
	std::map<int, SPCoreMissionAttr*>		m_mCoreMission;
};



