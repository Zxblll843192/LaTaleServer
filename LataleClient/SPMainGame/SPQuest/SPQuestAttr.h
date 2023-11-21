#pragma once


///**
// * ���� �񱳽� ���Ǵ� �� ������ <br>
//*/
//enum STAT_OPERATOR {
//	STAT_OPERATOR_NULL = 0,			/**< ������ <br> */
//	STAT_OPERATOR_SMALL = 1,		/**< ���� <br> */
//	STAT_OPERATOR_LARGE = 2,		/**< ŭ <br> */
//	STAT_OPERATOR_LESS = 3,			/**< ���� <br> */
//	STAT_OPERATOR_MORE = 4,			/**< �̻� <br> */
//	STAT_OPERATOR_EQUAL = 5,		/**< ���� <br> */
//	STAT_OPERATOR_WRONG = 6,		/**< �ٸ� <br> */
//};

/**
 * Quest�� UI�� ���������� �����ϴ� �÷��� <br>
*/
enum QUEST_UI_SHOW {
	QUEST_UI_SHOW_NULL = 0,				/**< ���� <br> */
	QUEST_UI_SHOW_DISABLE = 1,			/**< ��Ȱ��ȭ <br> */
	QUEST_UI_SHOW_ABLE = 2,				/**< ���� <br> ������ �⺻�� <br> */
	QUEST_UI_SHOW_COMPLETE = 3,			/**< ��� �̼��� ������ ��� <br> �Ϸ� <br> */
	QUEST_UI_SHOW_REWORD = 4,			/**< ���� ���� ���<br> �Ϸ� ����Ʈ�� ��� ��� �̰��� <br> NPC�� ����Ʈ ����Ʈ���� �̻����� ���� ������ ���� <br> */
};


/**
 * ����Ʈ NPC <br> 
*/
enum QUEST_NPC {
	QUEST_NPC_REWORD	= 0,		/**< ������ �ִ� NPC <br> */
	QUEST_NPC_GIVE		= 1,		/**< ����Ʈ�� �ִ� NPC <br> */
	QUEST_NPC_MAX		= 2,		/**< ����Ʈ NPC �ִ� <br> */
};


/**
 * ����Ʈ ���� ��ũ <br>
*/
enum REWARD_RANK {
	REWARD_RANK_0		= 0,		/**< ����ũ 1��� <br> */
	REWARD_RANK_1		= 1,		/**< ����ũ 2��� <br> */
	REWARD_RANK_2		= 2,		/**< ����ũ 3��� <br> */
	REWARD_RANK_NULL	= 3,		/**< ���� ���� <br> */
};


/**
 * ����Ʈ ������ ��Ʈ�� <br>
 * �����ƽ�(Elias)�ƿ���ġ(Aoichi)���(����-RonJing)����(Elfa) <br> 
*/
enum CITY_NAME {
	CITY_NAME_NULL		= 0,		/**< ������ <br> */
	CITY_NAME_BELOS		= 1,		/**< ���ν� <br> */
	CITY_NAME_ELIAS		= 2,		/**< �����ƽ� <br> */
	CITY_NAME_AOICHI	= 3,		/**< ������ġ <br> */
	CITY_NAME_RONJING	= 4,		/**< ��� <br> */
	CITY_NAME_ELFA		= 5,		/**< ���� <br> */
	CITY_NAME_COUNT		= 6,		// ���� ���� ���� AJJIYA [6/23/2006]
};

class SPRewardAttr;

/**
 * ����Ʈ ���� �䱸 ���� <br>
*/
struct SPRequire {
	int m_iRequireStat;				/**< ���濡 �ʿ��� ���� ���� <br> */
	int m_iRequireStatValue;		/**< ���濡 �ʿ��� ������ �� <br> */
	int m_iValue1;					/**< �񱳰� 1 <br> */
	int m_iValue2;					/**< �񱳰� 2 <br> */	

	bool m_bOK;						/**< üũ�� �����ߴ��� <br> */
	
	SPRequire() {
		Clear();
	}

	~SPRequire() {
		Clear();
	}

	void Clear(){
		m_iRequireStat = 0;
		m_iRequireStatValue = 0;
		m_iValue1 = 0;
		m_iValue2 = 0;
		m_bOK = true;
	}

	void operator=(const SPRequire Src) {
		m_iRequireStat = Src.m_iRequireStat;
		m_iRequireStatValue = Src.m_iRequireStatValue;
		m_iValue1 = Src.m_iValue1;
		m_iValue2 = Src.m_iValue2;
		m_bOK = Src.m_bOK;
	}

	void SetRequire(int iStat, int iStatValue, int iValue1, int iValue2) {
		Clear();
		m_iRequireStat = iStat;
		m_iRequireStatValue = iStatValue;
		m_iValue1 = iValue1;
		m_iValue2 = iValue2;
	}
};


/**
 * ����Ʈ�� ���Ǵ� ������ ���� <br> 
*/
struct SPQuestItem {
	int m_iItemID;					/**< ������ ID <br> */
	int m_iStack;					/**< ���� <br> */
	int m_iRear;					/**< ��� <br> */

	SPQuestItem(){
		Clear();
	}
	
	~SPQuestItem(){
		Clear();
	}

	void Clear() {
		m_iItemID = 0;
		m_iStack = 0;
		m_iRear = 0;
	}

	void operator=(const SPQuestItem Src) {
		m_iItemID = Src.m_iItemID;
		m_iStack = Src.m_iStack;
		m_iRear = Src.m_iRear;
	}

	void SetQuestItem(int iItemID, int iStack, int iRear) {
		Clear();
		m_iItemID = iItemID;
		m_iStack = iStack;
		m_iRear = iRear;
	}
};


/**
 * ����Ʈ ���� �ӹ� <br>
*/
struct SPMission {
	MISSION_TYPE m_iMissionType;			/**< �ӹ� ���� <br> */
	int m_iMissionTypeID;					/**< �ӹ��� ���� ID <br> �ӹ� ������ �������̸� ������ ID �� �� <br> */
	int m_iMissionCount;					/**< �������Ѿ� �� Ƚ�� <br> */
	bool m_bShow;							/**< �̼� ��������� �����ٰ����� <br> */

	bool m_bClear;							/**< �÷��̾ ��� <br> �ӹ��� Ŭ���� �Ǿ� �ִ��� <br> */
	int m_iCurCount;						/**< ���� �÷��̾ ������Ų Ƚ�� <br> */
	
	SPMission(){
		Clear();
	}
	
	~SPMission(){
		Clear();
	}
	
	void Clear() {
		m_iMissionType = MISSION_TYPE_NULL;
		m_iMissionTypeID = 0;
		m_iMissionCount = 0;
		m_bShow = true;
		m_bClear = false;
		m_iCurCount = 0;
	}

	void operator=(const SPMission Src) {
		m_iMissionType = Src.m_iMissionType;
		m_iMissionTypeID = Src.m_iMissionTypeID;
		m_iMissionCount = Src.m_iMissionCount;
		m_bShow = Src.m_bShow;
		m_bClear = Src.m_bClear;
		m_iCurCount = Src.m_iCurCount;
	}

	void SetMission(MISSION_TYPE iMission, int iTypeID, int iCount, bool bShow) {
		Clear();
		m_iMissionType = iMission;
		m_iMissionTypeID = iTypeID;
		m_bShow = bShow;
		if(m_iMissionType == MISSION_TYPE_ACTION) {
			m_iMissionTypeID++;
		}		
		m_iMissionCount = iCount;
	}
};


/**
 * ����Ʈ �Ϸ�(����)�� �Ҹ�Ǵ� ������ <br>
*/
struct SPConsumeItem {
	int m_iItemID;							/**< ������ ID <br> */
	int m_iStack;							/**< ���� <br> */

	SPConsumeItem(){
		Clear();
	}

	~SPConsumeItem(){
		Clear();
	}

	void Clear() {
		m_iItemID = 0;
		m_iStack = 0;		
	}

	void operator=(const SPConsumeItem Src) {
		m_iItemID = Src.m_iItemID;
		m_iStack = Src.m_iStack;
	}

	void SetConsumeItem(int iItemID, int iStack) {
		Clear();
		m_iItemID = iItemID;
		m_iStack = iStack;
	}
};


/**
 * Quest�� ���Ǵ� NPC(����Ʈ�� �� NPC, ������ �ִ� NPC)�� ������ ���� <br> 
*/
struct SPQuestNpc{
	int m_iIcon;							/**< ������ <br> */
	int m_iIconIndex;						/**< ������ �ε��� <br> */
	std::string m_strPlace;					/**< NPC ��� ���ڿ� <br> */
	std::string m_strName;					/**< NPC �̸� ���ڿ� <br> */

	SPQuestNpc(){
	}

	~SPQuestNpc(){
	}

	void Clear() {
		m_iIcon = 0;
		m_iIconIndex = 0;
		m_strPlace = "";
		m_strPlace.clear();
		m_strName = "";
		m_strName.clear();
	}

	void operator=(const SPQuestNpc Src) {
		Clear();
		m_iIcon = Src.m_iIcon;
		m_iIconIndex = Src.m_iIconIndex;
		m_strPlace = Src.m_strPlace;
		m_strName = Src.m_strName;
	}

	void SetQuestNpc(int iIcon, int iIconIndex, std::string strPlace, std::string strName)
	{
		m_iIcon = iIcon;
		m_iIconIndex = iIconIndex;
		m_strPlace = strPlace;
		m_strName = strName;
	}

};


/**
 * �Ϸ�� �ش� ��ũ���� ���ð����� ���� ���� <br> 
 * ���� ������ ��� Probability �� ���� ���� <br>
 * ID�� ���ؼ� ���� ���� ���� <br>
*/
struct SPRewordInfo {
	int m_iID;						/**< ��ũ ID <br> */
	int m_iProbability;				/**< ��ũ Ȯ��? <br> */
	SPRewardAttr* m_pRewardInfo;

	SPRewordInfo() {
	}

	~SPRewordInfo() {
	}

	void Clear() {
		m_iID = 0;
		m_iProbability = 0;
		m_pRewardInfo = NULL;
	}

	void operator=(const SPRewordInfo Src) {
		Clear();
		m_iID = Src.m_iID;
		m_iProbability = Src.m_iProbability;
		m_pRewardInfo = Src.m_pRewardInfo;
	}

	void SetRewordInfo(int iID, int iProbability) {
		m_iID = iID;
		m_iProbability = iProbability;
	}
};


/**
 * ��ũ�� ���� ���� ���¿� ���� ������ ���� ���� �������� ��ũ ������ ���� <br>
*/
struct SPRewordRank {
	REWARD_TYPE	m_iType;					/**< ��ũ Ÿ�� <br> */
	SPRewordInfo m_Info[QUEST_MAX_REWARD];	/**< �Ϸ�� �ش� ��ũ���� ���ð����� ���� ���� <br> */	

	SPRewordRank(){
		Clear();
	}
	
	~SPRewordRank(){
		Clear();
	}

	void Clear() {
		m_iType = REWARD_TYPE_FIX;		
		for(int i = 0; i < QUEST_MAX_REWARD; i++) {
			m_Info[i].Clear();
		}
	}

	void operator=(const SPRewordRank Src) {
		Clear();
		m_iType = Src.m_iType;		
		
		for(int i = 0; i < QUEST_MAX_REWARD; i++) {
			m_Info[i] = Src.m_Info[i];
		}
	}

	void SetRankType(REWARD_TYPE iType) {
		m_iType = iType;
	}
};


/**
* @class SPQuestAttr
* @brief ����Ʈ �ε� ����
* @author Jinhee
* @version 00.00.01
* @date 2005.09.21
* @bug ����
* @warning 
*/
class SPQuestAttr {
public:
	SPQuestAttr();
	~SPQuestAttr();

	void Clear();

	void operator=(const SPQuestAttr Src);
	void Copy(SPQuestAttr* pSrc);

	bool SetQuestAttr(int iQuestID, std::string strName, int iVisible);	

	bool SetQuestAttrInfo(std::string strTalk1, std::string strTalk2,
		std::string strPurPose, int iRewordNpcID);

	bool SetQuestRequireStat(int iIndex, int iStat, int iStatValue, int iValue1, int iValue2);

	bool SetAcquisitionEffect(int iIndex, int iEffect);

	bool SetAcquisitionItem(int iIndex, int iItemID, int iStack, int iRear);

	bool SetMission(int iIndex, MISSION_TYPE iMission, int iTypeID, int iCount, bool bShow);

	bool SetCunsumeItem(int iIndex, int iItemID, int iStack);

	//bool SetRewordEffect(int iIndex, int iEffect);

	//bool SetRewordItem(int iIndex, int iItemID, int iStack, int iRear);

	bool SetQuestRewordStat(int i, int j, int iStat, int iStatValue, int iValue1, int iValue2);

	bool SetNpc(int iIndex, int iIcon, int iIconIndex, std::string strPlace, std::string strName);

	bool SetNpcMessage(std::string strAccept, int iAccept, 
		std::string strReword, int iReword);

	/**
	 * �⺻���� ������ �䱸 ������ üũ�Ѵ� <br>
	 * ���� üũ�� UiShow ���¸� �����Ѵ� <br>
	 @param NONE
	 @return QUEST_UI_SHOW
	*/
	QUEST_UI_SHOW IsRequire();

	/**
	* ����� �䱸������ Ȯ���� Rank ������ ��ȯ�Ѵ� <br> 
	@param 
	@return
	*/
	REWARD_RANK IsRewardRequire();

	/**
	 * ���� �������� ����Ʈ�� �̼��� ��� <br>
	 * ����Ʈ�� Add�ɶ� Item���� �̼ǿ� ���Ǵ� �������� ������ �����ϵ��� �Ѵ� <br> 
	 @param bool bMsg = true		�޽��� ��¿���
	 @return bool
	*/
	bool SetCheckMissionItem(bool bMsg = true);
	
	/**
	 * Quest�� UIShow Status�� ���� <br> 
	 @param QUEST_UI_SHOW iUiShow = QUEST_UI_SHOW_NULL
	 @return void
	*/
	void SetQuestUIShow(QUEST_UI_SHOW iUiShow = QUEST_UI_SHOW_NULL);
	
	/**
	 * Quest�� UIShow Status�� Ȯ�� <br> 
	 @param NONE
	 @return QUEST_UI_SHOW
	*/
	QUEST_UI_SHOW GetQuestUIShow();		
	

public:
	int m_iQuestID;												/**< Quest ID <br> */
	std::string m_strQuestName;									/**< Quest Name <br> */
	SPQuestNpc m_QuestNpc[QUEST_NPC_MAX];						/**< ����Ʈ�� ������ NPC ���� <br> */
	
	std::string m_strTalk1;										/**< ��ȭ 1 <br> */
	std::string m_strTalk2;										/**< ��ȭ 2 <br> */
	std::string m_strPurPose;									/**< ���� <br> */

	int m_iRewordNpcID;											/**< ������ �ִ� NPC ID <br> */

	int m_iVisible;												/**< ������ �����ְų� ����� �ɼ� <br> */	
	
	SPRequire m_Require[QUEST_MAX_REQUIRE];						/**< ���濡 �ʿ��� ���� ���� <br> */	

	int m_iAcquisitionEffect[QUEST_MAX_ACQUISITION_EFFECTID];	/**< ����Ʈ ����� �ߵ�ȿ�� <br> */
	SPQuestItem m_AcquisitionItem[QUEST_MAX_ACQUISITION_ITEM];	/**< ����Ʈ ����� �԰� ���� ������ <br> */
	
	SPMission m_Mission[QUEST_MAX_MISSION];						/**< �̼� <br> */	
	
	SPConsumeItem m_ConsumeItem[QUEST_MAX_CONSUMPTION_ITEM];	/**< ����Ʈ �Ϸ�(����)�� �Һ�Ǵ� ������ <br> */

	//int m_iRewordEffect[QUEST_MAX_REWARD_EFFECTID];				/**< ����Ʈ �Ϸ�(����)�� �޴� ȿ�� <br> */	
	//SPQuestItem m_RewordItem[QUEST_MAX_REWARD_ITEM];			/**< ����Ʈ �Ϸ�� �������� �ް� �Ǵ� ������ <br> */

	SPRequire	m_RewordRequire[QUEST_MAX_RANK][QUEST_MAX_RANK_REQUIRE];  /**< ����Ʈ ����� ���� ���� Ȯ�ο� <br> */
	SPRewordRank m_RewordRank[QUEST_MAX_RANK];					/**< ���� ������ ���� ���� ���� <br> */	

	//�÷��̾ ���
	QUEST_UI_SHOW m_iUiShow;									/**< ����Ʈ�� UI ǥ�� ���� <br> */	
	int		m_iRewordCount;										/**< ����Ʈ�� ���� Ƚ�� (Ŭ���� �ݺ�Ƚ��) <br> */	
	REWARD_RANK	 m_iRank;										/**< ����Ʈ �����(�Ǵ� �����찡 ���� ����) ������ ��ũ <br> */

	//����Ʈ �����̳� ����� Npc Message ó���� 
	std::string m_strMsgAccept;									/**< ����Ʈ ������ Npc �޽��� <br> */
	int			m_iImageAccept;									/**< ����Ʈ ������ Npc Image <br> */
	std::string m_strMsgReword;									/**< ����Ʈ ������ Npc �޽��� <br> */
	int			m_iImageReword;									/**< ����Ʈ ������ Npc Image <br> */	

	CITY_NAME	m_iCityName;									/**< ����Ʈ ���� ����? <br> */

	QUEST_ACCEPTTYPE	m_eAcceptType;							/**< �������ɼ� üũ <br> */
	INT32				m_iActCharID;							/**< ������ ����ϴ� ������ ĳ����ID( DBKey ) <br> */

	QUEST_ACCEPTTYPE	m_iCurrentAccept;						/**< ���� ��� �����Ǿ������� Ÿ���� ��� <br> */
};



