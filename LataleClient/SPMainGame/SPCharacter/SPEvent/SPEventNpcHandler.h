#pragma once 


class SPLDTManager;
class SPLDTFile;

const int NPC_RENDER_X = 544;			/**< Npc Full Render Dest Pos X <br> */
const int NPC_RENDER_Y = 114;			/**< Npc Full Render Dest Pos Y <br> */
const int MAX_QUEST_LIST = 30;


const float NPC_FADE_START		= 0.27f; /**< Npc CutIn Image Fade Start Value <br> */


enum EVENT_CLICK {
	EVENT_CLICK_NULL,
	EVENT_CLICK_NPCTALK,
	EVENT_CLICK_PCTALK,
	EVENT_CLICK_MAX,
};


/**
 *
*/
struct SPNpc {
	int m_iNpcID;						/**< Npc ���� �ε��� <br> */	
	int m_iCutImage;					/**< Npc Cut In Image <br> */
	std::string	m_strNpcName;			/**< Npc Name <br> */
	std::string m_strMessage;			/**< Npc First Message <br> */	
	
	EventType m_NpcEventType[MAX_NPC_EVENT_TYPE];

	SPNpc() {
		Clear();		
	}

	~SPNpc() {
		Clear();
	}

	void Clear() {
		m_iNpcID		= 0;
		m_iCutImage		= 0;
		m_strNpcName.clear();
		m_strMessage	= "";
		m_strMessage.clear();
		
		for(int i = 0; i < MAX_NPC_EVENT_TYPE ; i++ ){
			//m_iNpcEventType[i] = NPC_EVENT_TYPE_NULL;
			m_NpcEventType[i].SetEventType(NPC_EVENT_TYPE_NULL, 0, "");
		}
	}

	//void SetNpc(int iNpcID, int iCutImage, int iTalk, int iTalkID, 
	//	int iTrade, int iTradeID, int iQuest, int iQuestID, int iStorage, int iStorageID, std::string strMessage)
	void SetNpc(int iNpcID, int iCutImage, 
		int iType1, int iTypeID1, std::string strMenu1,
		int iType2, int iTypeID2, std::string strMenu2,
		int iType3, int iTypeID3, std::string strMenu3,
		int iType4, int iTypeID4, std::string strMenu4,
		std::string strName,
		std::string strMessage)
	{
		Clear();	
		int iCounter = 0;
		
		m_iNpcID		= iNpcID;
		m_iCutImage		= iCutImage;
		m_strNpcName	= strName;
		m_strMessage	= strMessage;
		
		if(iType1 > 0) {
			m_NpcEventType[iCounter].SetEventType((NPC_EVENT_TYPE)iType1, iTypeID1, strMenu1);
			iCounter++;
		}

		if(iType2 > 0) {
			m_NpcEventType[iCounter].SetEventType((NPC_EVENT_TYPE)iType2, iTypeID2, strMenu2);
			iCounter++;
		}

		if(iType3 > 0) {
			m_NpcEventType[iCounter].SetEventType((NPC_EVENT_TYPE)iType3, iTypeID3, strMenu3);
			iCounter++;
		}

		if(iType4 > 0) {
			m_NpcEventType[iCounter].SetEventType((NPC_EVENT_TYPE)iType4, iTypeID4, strMenu4);
			iCounter++;
		}
	}
	
	/**
	 * �������
	 @param
	 @return
	*/
	void SetNpcEventType(int iItem, NPC_EVENT_TYPE iType) {
	}

	/**
	 *
	 @param
	 @return
	*/
	EventType* GetEventType(int iItem = 0) {
		if(iItem > 3 || iItem < 0)
			return NULL;
		
		return &m_NpcEventType[iItem];
	}
	
	/**
	 * ���� Item�� �ش��ϴ� NPC_EVENT_TYPE�� �������� �����´� <br>
	 @param int iItem
	 @return NPC_EVENT_TYPE
	*/
	NPC_EVENT_TYPE GetNpcEventType(int iItem = 0) {
		if(iItem > 3 || iItem < 0)
			return NPC_EVENT_TYPE_NULL;
		
		//return m_iNpcEventType[iItem];
		return m_NpcEventType[iItem].m_iEventType;
	}

	/**
	 * 
	 @param 
	 @return
	*/
	std::string GetNpcEventMenu(int iItem = 0) {
		if(iItem > 3 || iItem < 0)
			return "";

		//return m_iNpcEventType[iItem];
		return m_NpcEventType[iItem].m_strMemu;
	}
	
	/**
	 *
	 @param
	 @return
	*/
	int GetNpcEventTypeID(int iItem = 0) {
		if(iItem > 3 || iItem < 0)
			return 0;

		return m_NpcEventType[iItem].m_iTypeID;
	}
};


/**
*
*/
struct SPNpcTalk {
	int						m_iID;							/**< Index <br> */
	std::string				m_strBGM;						/**< BGM <br> */
	bool					m_bCompel;						/**< �������� �ƴ��� <br> */
	TALK_TYPE				m_iTalkType;					/**< ��ȭ�� �Ϲ����� �̺�Ʈ(���ù�)���� <br> */	
	std::string				m_strName;						/**< Npc Name <br> */
	std::string				m_strMessage;					/**< Message <br> */
	NPC_TALK_WINDOW			m_iBoxPos;						/**< ��ȭ �����찡 PC ������ NPC ������ <br> */
	NPC_TALK_WINDOW_MODE	m_iBoxType;						/**< ��ȭ ���� <br> */
	int						m_iCutInImage;					/**< NPC �̹��� <br> */
	NPC_TALK_EFFECT			m_iCutInEffect;					/**< NPC �̹��� ��� ȿ�� <br> */
	int						m_iAttachImage;					/**< ÷�� �̹��� <br> */
	NPC_TALK_EFFECT			m_iAttachEffect;				/**< ÷�� �̹��� ��� ȿ�� <br> */
	EventType				m_NpcEventType[MAX_NPC_EVENT_TYPE]; /**< <br> */
	int						m_iMissionID;					/**< �̼� ID <br> */
	int						m_iClassChangeID;				/**< ���� ID <br> */
	int						m_iStoryID;						/**< ���丮 ID <br> */

	
	bool					m_bMenu;						/**< ��ȭ�� ���������� <br> m_NpcEventType[MAX_NPC_EVENT_TYPE] ������ �ִ� ��� <br> */
	bool					m_bShowAttach;

	SPNpcTalk() {
		Clear();
	}
	
	~SPNpcTalk() {
		Clear();
	}
	
	void Clear() {
		m_iID					= 0;
		m_strBGM.clear();
		m_bCompel				= false;
		m_iTalkType				= TALK_TYPE_NULL;
		m_strName.clear();
		m_strMessage.clear();
		m_iBoxPos				= NPC_TALK_WINDOW_NULL;
		m_iBoxType				= NPC_TALK_WINDOW_MODE_NULL;
		m_iCutInImage			= 0;
		m_iCutInEffect			= NPC_TALK_EFFECT_NULL;	
		m_iAttachImage			= 0;
		m_iAttachEffect			= NPC_TALK_EFFECT_NULL;

		for(int i = 0 ; i < MAX_NPC_EVENT_TYPE ; i++) {
			m_NpcEventType[i].SetEventType(NPC_EVENT_TYPE_NULL, 0, "");
		}

		m_iMissionID			= 0;
		m_iClassChangeID		= 0;
		m_iStoryID				= 0;

		m_bMenu					= false;
		m_bShowAttach			= true;		
	}
};

////
//struct SPNpcTalk {
//	std::string m_strMessage[MAX_NPC_MESSAGE];	/**< ��ȭ <br> */
//
//	int m_iCutInImage[MAX_NPC_MESSAGE];			/**< ��ȭ �̹��� <br> */
//
//	std::string m_strEndMessage;				/**< ��ȭ �� <br> */
//	int m_iCutInEnd;							/**< ��ȭ �� �̹��� <br> */
//
//	std::string m_strQuestion[MAX_NPC_MESSAGE]; /**< ���� ��ũ ���ڿ� <br> */
//	int m_iQuestion[MAX_NPC_MESSAGE];			/**< ���� ��ũ  <br> */
//
//	int m_iTalkSize;							/**< ��ȭ ������ <br> */
//
//	SPNpcTalk() {
//		Clear();
//	}
//
//	~SPNpcTalk() {
//		Clear();
//	}
//
//	void Clear() {
//		for(int i = 0 ; i < MAX_NPC_MESSAGE ; i++) {			
//			m_strMessage[i].clear();
//			m_strMessage[i] = "";
//			m_iCutInImage[i] = 0;
//			
//			m_strQuestion[i].clear();
//			m_strQuestion[i] = "";
//			m_iQuestion[i] = 0;
//		}		
//		
//		m_strEndMessage.clear();
//		m_strEndMessage	= "";
//		m_iCutInEnd		= 0;
//
//		m_iTalkSize		= 0;
//	}
//	
//	void SetNpcTalk(std::string strMessage1, std::string strMessage2, std::string strMessage3, std::string strMessage4,
//				int iImage1, int iImage2, int iImage3, int iImage4, 
//				std::string strEndMessage, int iEndImage,
//				std::string strQuestion1, std::string strQuestion2, std::string strQuestion3, std::string strQuestion4,
//				int iQuestion1, int iQuestion2, int iQuestion3, int iQuestion4)
//	{
//		m_iTalkSize = 0;
//		
//		m_strMessage[m_iTalkSize]	= strMessage1;
//		if(m_strMessage[m_iTalkSize] != "")
//			m_iTalkSize++;
//		
//		m_strMessage[m_iTalkSize]	= strMessage2;
//		if(m_strMessage[m_iTalkSize] != "")
//			m_iTalkSize++;
//
//		m_strMessage[m_iTalkSize]	= strMessage3;
//		if(m_strMessage[m_iTalkSize] != "")
//			m_iTalkSize++;
//
//		m_strMessage[m_iTalkSize]	= strMessage4;
//		if(m_strMessage[m_iTalkSize] != "")
//			m_iTalkSize++;
//
//		m_iCutInImage[0]	= iImage1;
//		m_iCutInImage[1]	= iImage2;
//		m_iCutInImage[2]	= iImage3;
//		m_iCutInImage[3]	= iImage4;
//		
//		m_strEndMessage	= strEndMessage;
//		m_iCutInEnd		= iEndImage;
//		
//		m_strQuestion[0] = strQuestion1;
//		m_strQuestion[1] = strQuestion2;
//		m_strQuestion[2] = strQuestion3;
//		m_strQuestion[3] = strQuestion4;
//
//		m_iQuestion[0]	= iQuestion1;
//		m_iQuestion[1]	= iQuestion2;
//		m_iQuestion[2]	= iQuestion3;
//		m_iQuestion[3]	= iQuestion4;
//	}
//};


/**
 * Npc ������� ������ 
*/
struct SPNpcShop {
	int m_iNpcID;									/**< ��� Npc Index <br> */
	int m_iShopID;									/**< ��� NPC�� ���ϴ� Type ID <br> ��Ȯ�� Shop�� ID <br> */
	int m_iBuyFactor;								/**< Npc�� �������� �����Ҷ� ���ݿ� ������ �ִ� ���� <br> */
	
	SPSellItem m_NpcSellItem[MAX_NPC_TRADE_ITEM];	/**< Npc�� �Ǹ��ϴ� Item�� List <br> */
	
	int m_iCutInImage;								/**< NPC�� �Ǹ��Ҷ� ���� �̹��� �ε��� <br> */	
	std::string m_strCutInMessage;					/**< NPC�� �Ǹ��Ҷ� ���� �޽��� �ε��� <br> */

	int m_iItemSize;								/**< NPC�� �Ǹ��ϴ� �������� ���� ������ <br> */
	int m_iPageCount;								/**< NPC�� �Ǹ��ϴ� ������ ����Ʈ�� ������ �� <br> */

	SPNpcShop(){
		Clear();
	}

	~SPNpcShop(){
		Clear();
	}

	void Clear() {
		m_iNpcID = 0;
		m_iShopID = 0;
		m_iBuyFactor = 0;
		m_iCutInImage = 0;
		m_strCutInMessage = "";
		m_strCutInMessage.clear();
		m_iItemSize = 0;
		m_iPageCount = 0;

		for(int i = 0; i < MAX_NPC_TRADE_ITEM; i++) {
			m_NpcSellItem[i].Clear();
		}
	}
	
	void SetNpcShop(int iNpcID, int iShopID, int iBuyFactor, int iCutInImage, std::string strCutInMessage) {
		Clear();
		
		m_iNpcID		= iNpcID;
		m_iShopID		= iShopID;
		m_iBuyFactor	= iBuyFactor;
		m_iCutInImage	= iCutInImage;
		m_strCutInMessage = strCutInMessage;
	}

	void SetNpcShopSellItem(int iItemIndex, int iItemID, int iRear, int iStack, int iSellFactor) {
		m_NpcSellItem[iItemIndex].SetSellItem(iItemID, iRear, iStack, iSellFactor);
	}

	void SetSellItemSize(int iSize) {
		assert(iSize > 0 && "NPC�� �Ǹ��ϴ� �������� �����ϴ�. \n");
		assert(iSize < (MAX_NPC_TRADE_ITEM + 1) && "NPC�� �Ǹ��ϴ� ������ ������ �ʰ��Ͽ����ϴ�\n");
		m_iItemSize = iSize;
		
		m_iPageCount = 0;
		m_iPageCount = m_iItemSize / 10;
		if( /*m_iPageCount > 0 &&*/ (m_iItemSize % 10 > 0)) {
			m_iPageCount++;
		}
	}
};


/**
 *
*/
struct SPNpcStorage {
	int m_iNpcID;								/**< ��� Npc Index <br> */
	int m_iCutInImage;							/**< Npc Cut In Image <br> */
	std::string m_strCutInMessage;				/**< Npc Cut In Message <br> */

	SPNpcStorage(){
		Clear();
	}

	~SPNpcStorage(){
		Clear();
	}

	void Clear() {
		m_iNpcID = 0;		
		m_iCutInImage = 0;
		m_strCutInMessage = "";
		m_strCutInMessage.clear();
	}

	void SetNpcStorage(int iNpcID, int iCutInImage, std::string strCutInMessage) {
		Clear();

		m_iNpcID		= iNpcID;
		m_iCutInImage	= iCutInImage;
		m_strCutInMessage = strCutInMessage;
	}
};


/**
 *
*/
struct SPNpcGift {
	int m_iNpcID;						/**< ��� Npc Index <br> */
	int m_iImage;						/**< Npc Cut In Image <br> */
	std::string m_strMessage;			/**< Npc Cut In Message <br> */

	SPNpcGift(){
	}

	~SPNpcGift(){
	}

	void Clear() {
		m_iNpcID = 0;		
		m_iImage = 0;
		m_strMessage = "";
		m_strMessage.clear();
	}

	void SetNpcGift(int iNpcID, int iImage, std::string strMessage){
		Clear();
		m_iNpcID = iNpcID;
		m_iImage = iImage;
		m_strMessage = strMessage;
	}
};


/**
 *
*/
struct SPNpcGuild {
	int m_iNpcID;
	int m_iImage;
	std::string m_strMessage;

	SPNpcGuild() {
		Clear();
	}

	~SPNpcGuild() {
	}

	void Clear() {
		m_iNpcID = 0;		
		m_iImage = 0;
		m_strMessage = "";
		m_strMessage.clear();
	}

	void SetNpcGuild(int iNpcID, int iImage, std::string strMessage) {
		Clear();
		m_iNpcID = iNpcID;
		m_iImage = iImage;
		m_strMessage = strMessage;
	}
};


/**
 *
*/
struct SPSavePointMsg {
	std::string				m_strBGM;
	std::string				m_strNpcName;
	std::string				m_strMessage;
	NPC_TALK_WINDOW_MODE	m_iBoxType;
	int						m_iCutInImage;
	NPC_TALK_EFFECT			m_iCutInEffect;

	SPSavePointMsg() {
		Clear();
	}

	~SPSavePointMsg() {
		Clear();
	}

	void Clear() {
		m_strBGM.clear();
		m_strNpcName.clear();
		m_strMessage.clear();
		m_iBoxType		= NPC_TALK_WINDOW_MODE_NORMAL;
		m_iCutInImage	= 0;
		m_iCutInEffect	= NPC_TALK_EFFECT_NULL;
	}

	//void SetSavePointMsg(string strMsg, int iCutInImage) {
	//	Clear();
	//	m_strMessage = strMsg;
	//	m_iCutInImge = iCutInImage;
	//}
};


enum SAVE_POINT {
	SAVE_POINT_0			= 0,
	SAVE_POINT_1			= 1,
	SAVE_POINT_2			= 2,
	SAVE_POINT_3			= 3,
	SAVE_POINT_SELECT		= 4,
	SAVE_POINT_YES			= 5,
	SAVE_POINT_NO			= 6,
	SAVE_POINT_MAX			= 7,
};

/**
*
*/
struct SPSavePoint {	
	int					m_iEventID;
	EVENT_TYPE			m_iEventType;			//�̰��� �������� EVENT_SAVEPOINT ��...
	int					m_iStoryID;
	
	SPSavePointMsg		m_MsgInfo[SAVE_POINT_MAX];
	int					m_iMsgSize;

	SPSavePoint() {
		Clear();
	}

	~SPSavePoint() {
		Clear();
	}

	void Clear() {
		m_iEventID			= 0;
		m_iEventType		= EVENT_SAVEPOINT;
		m_iStoryID			= 0;
		
		for(int i = 0; i < SAVE_POINT_MAX; i++) {
			m_MsgInfo[i].Clear();
		}
		m_iMsgSize			= 0;
	}
	
	////
	//std::string			m_strBGM;
	//SPSavePointMsg		m_MsgInfo[4];
	//int					m_iMsgSize;
	//std::string			m_strEventMessage;
	//int					m_iEventCutInImage;
	//std::string			m_strYesMessage;
	//int					m_iYesCutInImage;
	//std::string			m_strNoMessage;
	//int					m_iNoCutInImage;	
	//

	//int					m_iStoryID;

	//EVENT_TYPE			m_iEventType;			//�̰��� �������� EVENT_SAVEPOINT ��...
	//int					m_iEventID;

	//SPSavePoint() {
	//	Clear();
	//}

	//~SPSavePoint() {
	//	Clear();
	//}

	//void Clear() {
	//	m_strBGM = "";
	//	m_strBGM.clear();	
	//	
	//	m_iMsgSize = 0;

	//	m_strEventMessage = "";
	//	m_strEventMessage.clear();
	//	m_iEventCutInImage = 0;
	//	m_strYesMessage = "";
	//	m_strYesMessage.clear();
	//	m_iYesCutInImage = 0;
	//	m_strNoMessage = "";
	//	m_strNoMessage.clear();
	//	m_iNoCutInImage = 0;
	//	m_iStoryID = 0;
	//	
	//	for(int i = 0; i < 4 ; i++) {
	//		m_MsgInfo[i].Clear();
	//	}

	//	m_iEventType = EVENT_SAVEPOINT;
	//	m_iEventID = 0;
	//}

	//void SetSavePoint(int iEventID, string strBGM, string strMessage, int iImage, 
	//	string strMessageYes, int iImageYes, string strMessageNo, int iImageNo, int iStoryID)
	//{
	//	Clear();

	//	m_iEventID = iEventID;
	//	m_strBGM = strBGM;		
	//	m_strEventMessage = strMessage;
	//	m_iEventCutInImage = iImage;
	//	m_strYesMessage = strMessageYes;
	//	m_iYesCutInImage = iImageYes;
	//	m_strNoMessage = strMessageNo;
	//	m_iNoCutInImage = iImageNo;
	//	m_iStoryID = iStoryID ;
	//}
};


/**
 * 
 @param 
 @return
*/
struct SPNpcQuestList {
	int m_iNpcID;							/**< ���� ���θ���� NPC ID <br> */
	int m_iCutInImage;						/**< ����Ʈ ���¿����� NPC Image <br> */
	std::string m_strMessage;				/**< ��� <br> */
	std::string m_strTitle;					/**< NPC Quest �����쿡 ����� Title String <br> */
	int m_iQuestID[MAX_QUEST_LIST];
	int m_iQuestCount;

	SPNpcQuestList() {
		Clear();
	}

	~SPNpcQuestList() {
		Clear();
	}

	void Clear() {
		m_iNpcID = 0;
		m_iCutInImage = 0;
		m_strMessage = "";
		m_strMessage.clear();
		m_strTitle = "";
		m_strTitle.clear();

		for(int i = 0; i < MAX_QUEST_LIST; i++) {
			m_iQuestID[i] = 0;
		}
		m_iQuestCount = 0;
	}

	void SetNpcQuest(int iNpcID, int iCutInImage, 
					std::string strMsg, std::string strTitle) 
	{
		Clear();
		m_iNpcID = iNpcID;
		m_iCutInImage = iCutInImage;
		m_strMessage = strMsg;
		m_strTitle = strTitle;
	}
};


/**
 * 
*/
struct SPNpcPortal {	
	int					m_iItemID;						/**< Item ID <br> */
	int					m_iCutInImage;					/**< CutIn Image <br> */
	std::string			m_strMessage;					/**< CutIn Message <br> */
	int					m_iNpcID;						/**< NPC ID <br> */
	std::vector<SPNpcPortalInfo*>	m_vpNpcPortal;		/**< ��Ż ����Ʈ <br> */

	SPNpcPortal() {
		Clear();
	}

	~SPNpcPortal() {
		Clear();
	}

	void Clear();

	void SetNpcPortal(int iItemID, int iCutInImage, std::string strMsg, int iNpcID);

	bool AddPortalInfo(SPNpcPortalInfo* pInfo = NULL);

	int GetSize();

	SPNpcPortalInfo* GetInfo(int iIndex);

	std::vector<SPNpcPortalInfo*>* GetNpcPortalList();
};


/**
 * NPC Event ���� Ÿ�� <br> 
*/
enum NPC_EVENT_REWARD_TYPE {
	NPC_EVENT_REWARD_TYPE_NULL			= 0,
	NPC_EVENT_REWARD_TYPE_SELECT		= 1,			/**< ����Ÿ�� ���� <br> */
	NPC_EVENT_REWARD_TYPE_RENDOM		= 2,			/**< ����Ÿ�� ���� <br> */
	NPC_EVENT_REWARD_TYPE_FIX			= 3,			/**< ����Ÿ�� ���� <br> */
	NPC_EVENT_REWARD_TYPE_MAX			= 4,
};


const int MAX_NPC_EVENT_LIST			= 50;			/**< Npc Event List �� �ִ� ���� <br> */
const int MAX_NPC_EVENT_REQUIRE			= 2;			/**< Npc �̺�Ʈ ���� ���� <br> */
const int MAX_NPC_EVENT_ITEM			= 2;			/**< Npc �̺�Ʈ ���� ������ <br> */


/**
 *
*/
struct SPNpcEvent {
	int								m_iItemID;			/**< Item ID <br> */
	std::string						m_strName;			/**< Event Name <br> */
	//int								m_iCutImage;		/**< CutIN Image <br> */
	//std::string						m_strMessage;		/**< cutIn Message <br> */
	int								m_iNpcID;			/**< Npc ID <br> */
	NPC_EVENT_REWARD_TYPE			m_iRewordType;		/**< ���� Ÿ�� <br> */

	SPRequire						m_Require[MAX_NPC_EVENT_REQUIRE];			/**< ���� <br> */
	SPQuestItem						m_RequireItem[MAX_NPC_EVENT_ITEM];			/**< �ʿ� ������ <br> */
	UINT64							m_iRequireEly;		/**< �ʿ� ���� <br> */
	int								m_iRequirePvpPoint;	/**< �ʿ� PVP ����Ʈ <br> */
	std::string						m_strErr;			/**< ���� �޽��� <br> */

	std::vector<SPNpcEventInfo*>	m_vpNpcEventInfo;		/**< ���� ����Ʈ <br> */

	SPNpcEvent() {
		Clear();
	}

	~SPNpcEvent() {
		Clear();
	}

	void Clear();

	//void SetNpcEvent(int iItemID, *int iCutImage, std::string strMsg, int iNpcID, NPC_EVENT_REWARD_TYPE iType);
	void SetNpcEvent(int iItemID,  std::string strName, int iNpcID, NPC_EVENT_REWARD_TYPE iType);

	bool AddEventInfo(SPNpcEventInfo* pInfo = NULL);

	int GetSize();

	SPNpcEventInfo* GetEventInfo(int iIndex);
};


/**
*
*/
struct SPNpcEventList {
	int								m_iItemID;			/**< <br> */
	int								m_iCutImage;		/**< <br> */
	std::string						m_strMessage;		/**< CutIn Message <br> */	
	std::vector<SPNpcEvent*>		m_vpNpcEvent;		/**< <br> */
	int								m_iSelect;			/**< <br> */

	SPNpcEventList() {
		Clear();
	}

	~SPNpcEventList() {
		Clear();
	}

	void Clear();	

	bool AddNpcEvent(SPNpcEvent* pNpcEvent = NULL);

	int GetSize();

	bool SetSelect(int iIndex);
	
	void SetSelectReset();

	SPNpcEvent* GetNpcEvent(int iIndex = -1);
	
	SPNpcEvent* GetSelectNpcEvent();
};


enum NPC_FADE {
	NPC_FADE_IN,
	NPC_FADE_OUT,
};

/**
* @class SPEventNpcHandler
* @brief NPC�� ������ �ൿ�� �Ѵ�  ex) NPC ���ҽ� ó��(?), NPC Talk, NPC Shop etc..
* @author Jinhee
* @version 00.00.01
* @date 2005.5.9
* @bug ����
* @warning 
*/
class SPEventNpcHandler {
public:
	SPEventNpcHandler();
	~SPEventNpcHandler();

	void	Init();
	void	Clear();

	void	Process(float fTime);
	void	Render(float fTime);

	void	CutInProcess(float fTime);
	void	CutInRender(float fTime);
	 
	void	CutInKeyProcess(float fTime);		// CutIn �� Key �Է� ó���� �Ѵ�

	/**
	 * NpcRender Postion�� �ʱ�ȭ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void	ResetRect(NPC_FADE iFade = NPC_FADE_IN);
	
	/**
	 * ���� Cut In ���¸� �����Ѵ� <br> 
	 @param bool bCutIn = false
	 @return NONE
	*/
	void	SetCutIn(bool bCutIn = false);

	/**
	 * ���� Cut In ���¸� �����´� <br>
	 @param NONE
	 @return bool
	*/
	bool	IsCutIn();
	
	/**
	 * ���� CUT_IN Process State �� �����Ѵ� <br> 
	 @param CUT_IN_STATE iState = CUT_IN_STATE_NULL
	 @return NONE
	*/
	void	SetCutInState(CUT_IN_STATE iState = CUT_IN_STATE_NULL);
	
	/**
	 * ���� CUT_IN Process State �� �����´� <br> 
	 @param NONE
	 @return CUT_IN_STATE
	*/
	CUT_IN_STATE GetCutInState();

	/**
	 *
	 @param 
	 @return  
	*/
	int PerformMouseLUp		( int iX, int iY);

	void	SetEventClick(EVENT_CLICK iClick)		{m_iClick = iClick;}
	EVENT_CLICK	GetEventClick()	{ return m_iClick; }

	void	SetNPCTalk();
	void	SetNpcTalkWindowMode(NPC_TALK_WINDOW_MODE iType = NPC_TALK_WINDOW_MODE_NORMAL);	
	inline	NPC_TALK_WINDOW_MODE	GetNpcTalkWindowMode() { return m_iNpcTalkWindowMode; }

	/**
	 * 
	 @param 
	 @return
	*/
	int		GetNpcID();

	/**
	 * event���� NPCŬ���� �ش� NPC�� �������� �ε��ϵ��� �Ѵ� <br>
	 @param int iItemID = 0			itemID�� EVENT�������� EventTypeID �̸� NPC�� ���� ��ȣ�̴�
	 @return bool
	*/
	bool	LoadNpc(int iItemID = 0);
	
	/**
	 * NPC.LDT���� ItemID�� �ش��ϴ� NPC������ �о� SPNpc �� �����Ѵ� <br>
	 @param int iItemID = 0			itemID�� EVENT�������� EventTypeID �̸� NPC�� ���� ��ȣ�̴�
	 @return SPNpc*
	*/
	SPNpc*	LoadNpcDataLDT(int iItemID = 0);	

	/**
	 * NPCTALK.LDT���� �ش� Talk ���� Data�� �ε��Ѵ� <br> 
	 @param int iItemID = 0			itemID�� NPC.LDT�� ������ TALK Data�� index
	 @return SPNpc*
	*/
	SPNpcTalk* LoadNpcTalkDataLDT(int iItemID = 0);

	/**
	 * ���� Ȱ��ȭ �Ǿ� �ִ� NPC�� Data�� �����´� <br> 
	 * NULL �� ��� ���� �ؾ� ��!!
	 @param ���� ������� ����
	 @return SPNpc* m_pNpc
	*/
	SPNpc*	GetNpcData(int iItemID = 0);
	
	/**
	 * ���� Ȱ��ȭ �Ǿ� �ִ� NpcTalk Data�� �����´� <br> 
	 * NULL �� ��� �����ؾ� ��!!
	 @param ���� ������� ����
	 @return SPNpcTalk*	m_pNpcTalk;
	*/
	SPNpcTalk* GetNpcTalkData(int iItemID = 0);	
	
	/**	 
	 * �ش� index�� �̹����� GrobalResource���� �ε� �� ������ npcImage�� ����Ѵ� <br> 
	 @param int iIndex = 0
	 @return bool
	*/
	bool	SetNpcTalkImage(int iIndex = 0);

	/**
	 *
	 @param 
	 @return  
	*/
	bool	SetNpcBGM(std::string strBGM);

	/**
	 * Npc Shop Data�� �ε��Ѵ� <br>
	 @param int iItemID = 0		���� ID
	 @return SPNpcShop*
	*/
	SPNpcShop* LoadNpcShopDataLDT(int iItemID = 0);	

	/**
	 * Npc ���� Data �� ���´� <br>
	 @param int iItemID = 0		���� ID
	 @return SPNpcShop*
	*/
	SPNpcShop* GetNpcShopData(int iItemID = 0);

	/**
	 * â�� Data�� �ε� �Ѵ� <br>
	 @param int iItemID = 0 â�� ID
	 @return SPNpcStorage*
	*/
	SPNpcStorage* LoadNpcStorageDataLDT(int iItemID = 0);

	/**
	 * â�� Data�� �����´� <br>
	 @param int iItemID = 0 â�� ID
	 @return SPNpcStorage*
	*/
	SPNpcStorage* GetNpcStorageData(int iItemID = 0);

	/**
	 * SavePoint Data�� �ε��ϴ� <br>
	 @param int iItemID = 0 SavePoint ID
	 @return SPSavePoint*
	*/
	SPSavePoint* LoadSavePointData(int iItemID = 0);

	/**
	 * SavePoint Data�� �����´� <br>
	 @param int iItemID = 0 SavePoint ID
	 @return SPSavePoint*
	*/
	SPSavePoint* GetSavePointData(int iItemID = 0);

	/**
	 * QuestList Data�� �ε��Ѵ� <br>
	 @param int iItemID = 0
	 @return SPNpcQuestList*
	*/
	SPNpcQuestList* LoadNpcQuestDataLDT(int iItemID = 0);

	/**
	 * QuestList Data�� �����´� <br>
	 @param int iItemID = 0
	 @return SPNpcQuestList*
	*/
	SPNpcQuestList* GetNpcQuestData(int iItemID = 0);

	/**
	 * NpcGift Data�� �ε��Ѵ� <br>
	 @param 
	 @return
	*/
	SPNpcGift*	LoadNpcGiftDataLDT(int iItemID = 0);

	/**  
	 * CutIn �� ���� ���� Ŀ�� �̹��� ������ �ε��Ѵ� <br> 
	 * ���� ������ �ɼ� ��й� �� ��������� <br>
	 * �ٸ� ��ɿ� CutIN ���� ���� �̹��� ������ ��� �����ϴ� <br>
	 @param  
	 @return 
	*/  
	SPCutInTalk* LoadCutInTalkDataLDT(int iItemID = 0);

	/**  
	 *  
	 @param  
	 @return 
	*/  
	SPCutInTalk* GetCutInTalk(int iItemID = 0);

	/**
	 * NpcGift Data�� �����´� <br>
	 @param 
	 @return
	*/
	SPNpcGift*	GetNpcGift(int iItemID = 0);

	/**
	 * <br>
	 @param
	 @return
	*/
	SPNpcGuild*	LoadNpcGuildDataLDT(int iItemID = 0);
	
	/**
	 *
	 @param 
	 @return  
	*/
	SPNpcGuild*	GetNpcGuild(int iItemID = 0);
	
	/**
	 * �־��� ID�� Npc Portal Data�� �ε��� ����� ���´� <br>
	 @param 
	 @return  
	*/
	SPNpcPortal* LoadNpcPortalDataLDT(int iItemID = 0);
	
	/**
	 * ��� �Ǿ� �ִ� Npc Portal Data�� �����´� <br> 
	 @param 
	 @return  
	*/
	SPNpcPortal* GetNpcPortal();

	SPNpcEventList* LoadNpcEventListDataLDT(int iItemID = 0);
	SPNpcEvent*	LoadNpcEventDataLDT(SPLDTFile* pLDTNpcEvent, SPLDTFile* pLDTNpcEventInfo, int iItemID = 0);
	
	SPNpcEventList* GetNpcEventList();
	void		SetNpcEventSelect();
	SPNpcEvent* GetNpcEvent();

protected:
	float				m_fAccumulateRender;	/**< ������ �ð� ��� <br> */
	float				m_fCurDelay;			/**< ������ ���� �ð� <br> */

	bool				m_bCutIn;				/**< ���� CutIn ���������� <br> <br> */	
	CUT_IN_STATE		m_iCutInState;			/**< ���� CutIn�� ���� State <br> */

	NPC_TALK_WINDOW_MODE	m_iNpcTalkWindowMode;			/**< <br> */
	
	int					m_iNpcID;				/**< Evnet ���� �Ѿ�� NPC �ڵ� �� (ItemID �� ���� <br> */
	SPNpc*				m_pNpc;					/**< SPNpc Data <br> */	
	SPNpcTalk*			m_pNpcTalk;				/**< SPNpcTalk Data <br> */	
	SPNpcShop*			m_pNpcShop;				/**< SPNpcShop Data <br> */
	SPNpcStorage*		m_pNpcStorage;			/**< SPNpcStorage Data <br> */
	SPSavePoint*		m_pSavePoint;			/**< SavePoint Data <br> */
	SPNpcQuestList*		m_pNpcQuestList;		/**< SPNpcQuest Data <br> */
	SPNpcGift*			m_pNpcGift;				/**< SPNpcGift Data <br> */
	SPNpcGuild*			m_pNpcGuild;			/**< SPNpcGuild Data <br> */
	SPNpcPortal*		m_pNpcPortal;			/**< SPNpcPortal Data <br> */
	SPNpcEventList*		m_pNpcEventList;		/**< SPNpcEventList Data <br> */
	//SPNpcEvent*			m_pNpcEvent;			/**< SPNpcEvent Data <br> */
	SPCutInTalk*		m_pCutInTalk;			/**< SPCutInTalk Data <br> */  
	
	SPTexture*			m_pNpcTexture;			/**< Cut In Npc Texture <br> */
	int					m_iNpcMoveUnit;			/**< Npc Image Move Factor <br> */
	int					m_iNpcMoveCount;		/**< m_iNpcMoveUnit Move Factor <br> */
	int					m_iNpcX;				/**< Cut In Npc Render Dest Start X <br> */
	int					m_iNpcY;				/**< Cut In Npc Render Dest Start Y <br> */	
	
	float				m_fNpcAlpha;			/**< Npc Image Alpha <br> */

	float				m_fNpcFadeAlpha;		/**< Npc Image Fade Alpha <br> */
	float				m_fNpcFadeUnit;			/**< m_fNpcFadeAlpha Factor <br> */
	
	
	SPLDTFile*			m_pLDTNpcData;			/**< NPC Data LDT <br> */
	SPLDTFile*			m_pLDTNpcTalk;			/**< NPC Talk LDT <br> */
	SPLDTFile*			m_pLDTNpcShop;			/**< NPC Shop LDT <br> */
	SPLDTFile*			m_pLDTNpcShopDetail;	/**< Npc Shop Detail LDT <br> */
	SPLDTFile*			m_pLDTNpcStorage;		/**< NPC Storage LDT <br> */
	SPLDTFile*			m_pLDTSavePoint;		/**< SavePoint LDT <br> */
	SPLDTFile*			m_pLDTNpcQuest;			/**< NPC Quest LDT <br> */
	SPLDTFile*			m_pLDTNpcGift;			/**< Npc Gift LDT <br> */
	SPLDTFile*			m_pLDTNpcGuild;			/**< NPc Guild LDT <br> */

	//int					m_iKeyLeft;				/**< Left Key <br> */
	//int					m_iKeyRight;			/**< Right Key <br> */
	int					m_iKey1;				/**< Key 1 <br> */
	int					m_iKey2;				/**< Key 2 <br> */
	int					m_iKey3;				/**< Key 3 <br> */
	int					m_iKey4;				/**< Key 4 <br> */
	//int					m_iKeyEsc;
	int					m_iSpace;				/**< <br> */
	
	EVENT_CLICK			m_iClick;				/**< <br> */
};




