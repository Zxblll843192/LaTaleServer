
#pragma once


//enum SPID_EVENT {
//	SPID_EVENT_NULL			= 0,	
//};

/**
 * Event Model Class Type 
*/
enum SPID_EVENT {
	ID_EVENT_CL_NULL			= 0,		/**< Render Image 1�� ���°�� ��� ���� <br> */
	ID_EVENT_CL_ANI				= 1000,		/**< Animation�� ��� <br> */
};


/**
 * ���� ������ ���� ��Ȳ <br>
*/
enum CUT_IN_STATE {	
	CUT_IN_STATE_NULL				= 0,	/**< CutIn �� �ƴ� <br> */
	
	CUT_IN_STATE_SCROLL				= 1,	/**< CutIn Mode Scroll �� <br> */
	CUT_IN_STATE_SCROLL_END			= 2,	/**< CutIn Mode Scroll �� <br> */
	
	CUT_IN_STATE_TALK				= 3,	/**< CutIn Mode Talk <br> */
	CUT_IN_STATE_TRADE				= 4,	/**< CutIn Mode Trade <br> */
	CUT_IN_STATE_QUEST				= 5,	/**< CutIn Mode Quest <br> */
	CUT_IN_STATE_STORAGE			= 6,	/**< CutIn Mode Storage <br> */
	CUT_IN_STATE_GIFT				= 7,	/**< CutIn Mode Gift <br> */
	CUT_IN_STATE_SAVEPOINT			= 8,	/**< CutIn Mode SavePoint <br> */
	CUT_IN_STATE_MAIL				= 9,	/**< CutIn State Mail <br> */
	CUT_IN_STATE_BEAUTY				= 10,	/**< CutIn State Beauty <br> */
	CUT_IN_STATE_GUILD_CREATE		= 11,	/**< CutIn State Guild Create<br> */
	CUT_IN_STATE_GUILD_DISSOLVE		= 12,	/**< CutIn State Guild Dissolve <br> */
	CUT_IN_STATE_GUILD_CROPS		= 13,	/**< CutIn State Guild Crops <br> */
	CUT_IN_STATE_NPC_PORTAL			= 14,	/**< CutIn State Npc Portal <br> */
	CUT_IN_STATE_NPC_CHANGE			= 15,	/**< CutIn State Npc Item Change <br> */
	CUT_IN_STATE_GUILD_LEVEL_UP		= 16,	/**< CutIn State Guild Level Up <br> */
	CUT_IN_STATE_GUILD_EMBLEM		= 17,	/**< CutIn State Guild Emblem Change <br> */
	CUT_IN_STATE_PVP_RESERVE		= 18,	/**< CutIn State Pvp Reserve <br> */
	CUT_IN_STATE_NPC_AUCTION		= 19,	/**< CutIn State Auction <br> */
	CUT_IN_STATE_NPC_REOPTION		= 20,	/**< CutIn State Item Re Option <br> */  
	CUT_IN_STATE_PARTY_PVP_RESERVE	= 21,	/**< CutIn State Party Pvp Reserve <br> */  
	CUT_IN_STATE_RANKING			= 22,	/**< CutIn State Ranking board in game <br> */  	
	CUT_IN_STATE_LOVE				= 23,	/**< CutIn State Love <br> */ 
	CUT_IN_STATE_RELEASE,
};


/**
* ��ȭ�� �Ϲ����� �̺�Ʈ(���ù�)���� <br> 
*/
enum TALK_TYPE {
	TALK_TYPE_NULL,
	TALK_TYPE_NORMAL,							/**< �Ϲ� ��ȭ <br> */
	TALK_TYPE_SELECT,							/**< ���� ��ȭ <br> */
	TALK_TYPE_MAX,
};


/**
* ��ȭ �����찡 NPC������ PC������ <br>
*/
enum NPC_TALK_WINDOW {
	NPC_TALK_WINDOW_NULL,
	NPC_TALK_WINDOW_NPC,						/**< ��ȭâ NPC <br> */
	NPC_TALK_WINDOW_PC,							/**< ��ȭâ PC <br> */
	NPC_TALK_WINDOW_MAX,
};


/**
* NPC ��ȭ ���� <br>
*/
enum NPC_TALK_WINDOW_MODE {
	NPC_TALK_WINDOW_MODE_NULL,
	NPC_TALK_WINDOW_MODE_NORMAL,				/**< Npc �Ϲ� ��ȭ <br> */
	NPC_TALK_WINDOW_MODE_OUTBURST,				/**< Npc �ݳ�(?) ��ȭ <br> */
	NPC_TALK_WINDOW_MODE_MAX,
};


/**
 * NPC ��ȭ�� ȿ�� <br> 
*/
enum NPC_TALK_EFFECT {
	NPC_TALK_EFFECT_NULL,						/**< ȿ�� ���� <br> */
	NPC_TALK_EFFECT_SCROLL,						/**< ȿ�� ��ũ�� <br> */
	NPC_TALK_EFFECT_MAX,
};


/**
 * ���� Npc Talk �����찡 � ���� ���� �ִ��� <br> 
 * ��������� �ʰ� ���� <br> 
*/
enum NPC_TALK_USE {
	NPC_TALK_USE_NULL,							/**< <br> */
	NPC_TALK_USE_START,							/**< <br> */
	NPC_TALK_USE_TALK,							/**< <br> */
	NPC_TALK_USE_SAVEPOINT,						/**< <br> */
	NPC_TALK_USE_MAX,
};


////
///**
//* ���� NPC �� EVENT ���� ���� <br> 
//*/
//enum NPC_EVENT_TYPE {
//	NPC_EVENT_TYPE_NULL				= 0,/**< �ƹ��͵� �ƴ� <br> */
//	NPC_EVENT_TYPE_TALK				= 1,/**< ��ȭ <br> */
//	NPC_EVENT_TYPE_TRADE			= 2,/**< ���� <br> */
//	NPC_EVENT_TYPE_STORAGE			= 3,/**< â�� <br> */
//	NPC_EVENT_TYPE_QUEST			= 4,/**< Quest <br> */	
//};


const int MAX_NPC_EVENT_TYPE		= 4;/**< NPC�� ���Ҽ� �ִ� �ִ� EVENT_TYPE�� ���� <br> */
const int MAX_NPC_MESSAGE			= 4;/**< NPC�� ���Ҽ� �ִ� �ִ� Message�� ���� <br> */


typedef struct _EVENT_TYPE {
	NPC_EVENT_TYPE m_iEventType;	
	int m_iTypeID;
	std::string m_strMemu;

	_EVENT_TYPE() {
		m_iEventType = NPC_EVENT_TYPE_NULL;
		m_iTypeID = 0;
		m_strMemu = "";
		m_strMemu.clear();
	}

	void SetEventType(NPC_EVENT_TYPE iType, int iTypeID, std::string strMenu) {		
		m_iEventType = iType;
		m_iTypeID = iTypeID;
		m_strMemu = strMenu;
	}
} EventType ;

/**
 * Event Type
*/
//enum EVENT_TYPE {
//	EVENT_TYPE_NULL		= 0,			/**< �ȳ��� �뵵 <br> */
//	EVENT_TYPE_NPC		= 1,			/**< NPC <br> */
//	EVENT_TYPE_SAVE		= 2,			/**< Save Point <br> */
//	EVENT_TYPE_PORTAL	= 3,			/**< Potal <br> */
//};


/**
 * Condition Type
*/
enum CONDITION_TYPE {
	CONDITION_TYPE_NULL			= 0,
	CONDITION_TYPE_TYPE			= 1,
	CONDITION_TYPE_GENDER		= 2,
};


/**
 * Event Condition Check Stuct <br> 
 * ���� ���� üũ�� �ļ� üũ�� �ϴ� ���<br>
 * �ش������� ������ ��� �ִ� ����ü�� <br>
*/
struct SPEventCondition {
	CONDITION_TYPE iCondition;			/**< ���� Ÿ�� <br> */
	int iCheckValue1;					/**< ���� �� 1 <br> */
	int iCheckValue2;					/**< ���� �� 2 <br> ��ȹ�� ������ ���Ƿ� �߰��� <br>*/

	SPEventCondition() {
		iCondition = CONDITION_TYPE_NULL;
		iCheckValue1 = -1;
		iCheckValue2 = -1;
	}

	//void SetCondition(CONDITION_TYPE iCon, int iVal) {
	//	iCondition = iCon;
	//	iCheckVelue1 = iVal;
	//}

	void SetCondition(CONDITION_TYPE iCon, int iVal1, int iVal2 = 0) {
		iCondition = iCon;
		iCheckValue1 = iVal1;
		iCheckValue2 = iVal2;
	}
};


//enum ITEM_TYPE;
//#include "SPItemAttr.h"
//#include "SPItemStatus.h"

enum EVENT_INVEN_TYPE {
	EVENT_INVEN_TYPE_NULL = 0,			/**< �κ� NULL <br> */
	EVENT_INVEN_TYPE_EQUIP = 1,			/**< ��� �κ� <br> */
	EVENT_INVEN_TYPE_USE = 2,				/**< ��� �κ� <br> */
	EVENT_INVEN_TYPE_ETC = 3,				/**< ��Ÿ �κ� <br> */
	EVENT_INVEN_TYPE_EVENT = 4,			/**< �̺�Ʈ �κ� <br> */
	EVENT_INVEN_TYPE_PET = 5,				/**< �� �κ� <br> */
	EVENT_INVEN_TYPE_HOUSING = 6,			/**< �Ͽ�¡ �κ� <br> */
};

/**
 * Item Condition Check Struct <br>
 * ������ ������ üũ�� ���� ������ ������ ����ü�� <br> 
*/
struct SPEventItem {
	//ITEM_TYPE iConditionItem;			/**< ���� ������ <br> */
	EVENT_INVEN_TYPE iConditionInven;
	int iCheckValue1;					/**< ���� �� 1 <br> */

	SPEventItem() {
		//iConditionItem = ITEM_TYPE_NULL;
		iConditionInven = EVENT_INVEN_TYPE_NULL;
		iCheckValue1 = -1;
	}

	void SetEventItem( EVENT_INVEN_TYPE iItem, int iVal) {
		iConditionInven = iItem;
		iCheckValue1 = iVal;
	}
};



struct SPEventFrameData {
	FLOAT		fFrameTime;			// �� �������� Delay.
	FLOAT		fFrameDegree;		// �� �������� ȸ����.
	FLOAT		fFrameScale;		// �� �������� Scale.
	RECT		RectSrc;			// �� �������� �ؽ��ļҽ�.
	RECT		RectAdjust;			// �� �������� ����Ÿ���� ��ġ������ top, left�� ��.
	D3DXCOLOR	FrameColor;			// �� �������� �÷�.
	bool		bLRSwap;			// �¿��� ������

	SPEventFrameData() 
		: fFrameTime(0.0f)
		, fFrameDegree(0.0f)
		, fFrameScale(0.0f)
		, FrameColor(1.0f, 1.0f, 1.0f, 1.0f)
		, bLRSwap(false)
	{
		ZeroMemory(&RectSrc,		sizeof(RECT));
		ZeroMemory(&RectAdjust,		sizeof(RECT));
	}

	void SetNull()
	{
		fFrameTime		=	(0.0f);
		fFrameDegree	=	(0.0f);
		fFrameScale		=	(0.0f);
		FrameColor		=	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		bLRSwap			=	false;
		ZeroMemory(&RectSrc,		sizeof(RECT));
		ZeroMemory(&RectAdjust,		sizeof(RECT));
	}

	void operator=(const SPEventFrameData Src)
	{
		fFrameTime		= Src.fFrameTime;		
		fFrameDegree	= Src.fFrameDegree;	
		fFrameScale		= Src.fFrameScale;	
		RectSrc			= Src.RectSrc;		
		RectAdjust		= Src.RectAdjust;		
		FrameColor		= Src.FrameColor;
		bLRSwap			= Src.bLRSwap;
	}
};


/**
* Npc�� ������ �Ǹ��� ������ ����
*/
typedef struct _SPSellItem {
	int m_iItemID;									/**< Item ID <br> */
	int m_iRear;									/**< Rear <br> */
	int m_iStack;									/**< �ǸŵǴ� ���� <br> */
	int m_iSellFactor;								/**< NPC�� �������� �ȶ� ���ݿ� ������ �ִ� ���� <br> */

	_SPSellItem(){
		Clear();
	}

	~_SPSellItem(){
		Clear();
	}

	void Clear(){
		m_iItemID		= 0;
		m_iRear			= 0;
		m_iStack		= 0;
		m_iSellFactor	= 0;
	}

	void SetSellItem(int iItemID, int iRear, int iStack, int iSellFactor) {
		Clear();
		m_iItemID		= iItemID;
		m_iRear			= iRear;
		m_iStack		= iStack;
		m_iSellFactor	= iSellFactor;
	}
} SPSellItem;


#include "SPQuestAttr.h"

const int MAX_NPC_PORTAL_REQUIRE = 2;							/**< Npc�� �̿��� ��Ż ������ ���Ǵ� ����üũ ���� <br> */

/**
 * Npc �� �̿��� ��Ż�� ����ϴ� ��Ż ������ ���� <br>
*/
typedef struct _SPNPCPortalInfo {
	int					m_iItemID;								/**< Item Id <br> */
	std::string			m_strName;								/**< Name <br> */
	int					m_iDestID;								/**< ������ ID <br> */
	int					m_iStage;								/**< �������� Stage <br> */
	int					m_iMapGroup;							/**< �������� mapGroup <br> */
	int					m_iMapIndex;							/**< �������� MapIndex <br> */
	SPRequire			m_Require[MAX_NPC_PORTAL_REQUIRE];		/**< ü�� ���� <br> */
	int					m_iRequireItem;							/**< üũ Item <br> */
	UINT64				m_iRequireEly;							/**< üũ Ely <br> */
	int					m_iFxID;								/**< FX ID <br> */
	float				m_fDelay;								/**< Fx ������ <br> */
	std::string			m_strErrMsg;							/**< Error <br> */

	_SPNPCPortalInfo() {
		Clear();
	}

	~_SPNPCPortalInfo() {
		Clear();
	}

	void Clear() {
		m_iItemID				= 0;
		m_strName.clear();
		m_iDestID				= 0;
		m_iStage				= 0;	
		m_iMapGroup				= 0;
		m_iMapIndex				= 0;
		m_iRequireItem			= 0;
		m_iRequireEly			= 0;
		m_iFxID					= 0;
		m_fDelay				= 0.0f;
		m_strErrMsg.clear();

		for(int i = 0; i < MAX_NPC_PORTAL_REQUIRE; i++) {
			m_Require[i].Clear();
		}
	}

} SPNpcPortalInfo;


const int MAX_NPC_EVENT_INFO_REQUIRE = 2;
const int MAX_NPC_EVENT_REQUIRE_ITEM = 4;

typedef struct _SPNpcEventInfo {
	int					m_iID;							/**< Key ID <br> */
	
	SPQuestItem			m_RewordItem;					/**< �������� ���� �������� ���� <br> */	
	std::string			m_strTitleName;					/**< ������ �̸� <br> */	
	int					m_iIcon;						/**< ������ ID �� ���� ��� ����� ������ <br> */
	int					m_iIconIndex;					/**< ������ ID �� ���� ��� ����� ������<br> */
	UINT64				m_iEly;							/**< ���� ���� <br> */	
	
	std::string			m_strDesc;						/**< ���� <br> */
	
	SPRequire			m_Require[MAX_NPC_EVENT_INFO_REQUIRE];			/**< ���� ���� <br> */
	SPQuestItem			m_RequireItem[MAX_NPC_EVENT_REQUIRE_ITEM];		/**< �ʿ� ������ <br> */

	UINT64				m_iRequireEly;									/**< �ʿ� ���� <br> */
	int					m_iRequirePvpPoint;								/**< �ʿ� PVP ����Ʈ <br> */

	std::string			m_strErr;						/**< ���������̳� �ʿ� ������ �Ǵ� ���� ������ �޽��� <br> */

	_SPNpcEventInfo() {
		Clear();
	}

	~_SPNpcEventInfo() {
		Clear();
	}

	void Clear() {
		m_iID					= 0;
		
		m_RewordItem.Clear();
		m_strTitleName.clear();
		m_iIcon					= 0;
		m_iIconIndex			= 0;
		m_iEly					= 0;

		m_strDesc.clear();
		
		int i = 0;
		for(i = 0; i < MAX_NPC_EVENT_INFO_REQUIRE; i++) {
			m_Require[i].Clear();
		}

		for(i = 0; i < MAX_NPC_EVENT_REQUIRE_ITEM; i++) {
			m_RequireItem[i].Clear();
		}
		
		m_iRequireEly			= 0;
		m_iRequirePvpPoint		= 0;
		m_strErr.clear();
	}

} SPNpcEventInfo;

/**  
 * NPC �� ���� ��ȭ ���ڿ� ���� �̹����� �޽��� <br> 
 * NPC_GUILD �� ������ ���� <br>
 * ����� CUT_IN_STATE_NPC_REOPTION �� ��Ȳ������ ��� <br>
*/  
struct SPCutInTalk {
	int					m_iID;						/**< ID <br> */  
	int					m_iImageID;					/**< CutIn Image <br> */  
	std::string			m_strMsg;					/**< CutIn Shop Message <br> */ 

	SPCutInTalk() {
		Clear();
	}

	~SPCutInTalk() {
		Clear();
	}

	void Clear() {
		m_iID				= 0;
		m_iImageID			= 0;
		m_strMsg.clear();
	}	
};


const int MAX_CORE_REQUIRE				= 10;		/**< �� �������� üũ�� �ִ� Event Require�� ���� <br> */
const int MAX_CORE_EVENT_REQINVEN		= 2;		/**< �ִ� �κ� üũ�� ���� <br> */
const int MAX_CORE_EVENT_REQUIRE		= 8;		/**< �ִ� Requrie üũ�� ���� <br> */


/**
 * ���� �̺�Ʈ ���� ���� üũ ID ����Ʈ <br> 
 * ID�� �����Ͽ� SPCoreRequireAttr ������ �о�� �� <br> 
*/
struct SPCoreEventInfo {
	int				m_iID;							/**< �ش� Info�� Ű <br> */
	int				m_iRequireID[MAX_CORE_REQUIRE];	/**< RequireAttr �� ����Ű�� ID <br> */

	SPCoreEventInfo() {
		Clear();
	}

	~SPCoreEventInfo() {
		Clear();
	}

	void Clear() {
		m_iID				= 0;
		for(int i = 0; i < MAX_CORE_REQUIRE; i++) {
			m_iRequireID[i]		= 0;
		}		
	}
};


/**
 * �κ� üũ�� ���� <br>
*/
struct SPReqInvenSize {
	CONTAINER_TYPE	m_iContainerType;				/**< üũ�� �κ��丮 Ÿ�� <br> */
	int				m_iSize;						/**< üũ�� ����־���� ���� <br> */

	SPReqInvenSize() {
		Clear();
	}

	~SPReqInvenSize() {
		Clear();
	}

	void Clear() {
		m_iContainerType	= CONTAINER_TYPE_INVALID;
		m_iSize				= 0;
	}

	void SetReqInven(CONTAINER_TYPE iType, int iSize) {
		m_iContainerType	= iType;
		m_iSize				= iSize;
	}
};


typedef struct _SPCoreRequireAttr {
	int				m_iID;										/**< �ش� ID <br> */						
	SPReqInvenSize	m_InvenReq[MAX_CORE_EVENT_REQINVEN];		/**< �κ� üũ�� ���� <br> */
	int				m_iReqQuestSize;							/**< ����Ʈ üũ�� ���� <br> */
	REQUIRE_INFO	m_Require[MAX_CORE_EVENT_REQUIRE];			/**< �Ϲ� Requireüũ�� <br> */

	NPC_EVENT_TYPE	m_iEventType;								/**< ����Ǵ� �̺�Ʈ Ÿ�� <br> */
    int				m_iEventID;									/**< ����Ǵ� �̺�Ʈ ID <br> */
	
	int				m_iRank;

	_SPCoreRequireAttr() {
		Clear();
	}

	~_SPCoreRequireAttr() {
		Clear();
	}

	void Clear() {
		m_iID				= 0;
		int i = 0;
		for(i = 0; i < MAX_CORE_EVENT_REQINVEN; i++) {
			m_InvenReq[i].Clear();
		}
		
		m_iReqQuestSize		= 0;
		
		for(i = 0; i < MAX_CORE_EVENT_REQUIRE; i++) {
			m_Require[i].Clear();
		}		

		m_iEventType		= NPC_EVENT_TYPE_NULL;
		m_iEventID			= 0;
		m_iRank				= 0;
	}


} SPCoreRequireAttr;

