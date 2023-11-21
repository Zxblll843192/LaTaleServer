
//
#pragma once 


#define  _JOY_PAD				254

/**
 * �����е尡 �������� ��� <br> 
*/
enum JOYSTICK_MODE {
	JOYSTICK_MODE_NULL				= 0,
	JOYSTICK_MODE_ANALOG			= 1,			/**< �Ƴ��α� <br> */
	JOYSTICK_MODE_DIGITAL			= 2,			/**< ������ <br> */
};


/**
 * ��ư ��� ���� ���� <br>
*/
enum PAD_BUTTONTYPE {
	PAD_BUTTONTYPE_NORMAL,							/**< �Ϲ� ��ư <br> */
	PAD_BUTTONTYPE_FUNC1,							/**< ����Ű 1 <br> */
	PAD_BUTTONTYPE_FUNC2,							/**< ����Ű 2 <br> */
	PAD_BUTTONTYPE_MAX,
};


/**
 * �� ��ư ��ȣ <br> 
*/
enum PAD_BUTTON_NO {	
	PAD_BUTTON_NO_0							= 0,
	PAD_BUTTON_NO_1							= 1,
	PAD_BUTTON_NO_2							= 2,
	PAD_BUTTON_NO_3							= 3,
	PAD_BUTTON_NO_4							= 4,
	PAD_BUTTON_NO_5							= 5,
	PAD_BUTTON_NO_6							= 6,
	PAD_BUTTON_NO_7							= 7,
	PAD_BUTTON_NO_8							= 8,
	PAD_BUTTON_NO_9							= 9,
	PAD_BUTTON_NO_10						= 10,
	PAD_BUTTON_NO_11						= 11,	
	PAD_BUTTON_NO_MAX,
};


/**
 * ��ư�� �뵵 <br> 
*/
enum PAD_BUTTON_USE {
	PAD_BUTTON_USE_NULL,
	PAD_BUTTON_USE_KEY,								/**< �Ϲ� <br> */
	PAD_BUTTON_USE_FUNC,							/**< ���� <br> */
};


/**
 * ����� Ű������ ���� <br> 
*/
enum PAD_BUTTON_KEY_TYPE {
	PAD_BUTTON_KEY_TYPE_QUICK,						/**< ������ �� <br> */
	//PAD_BUTTON_KEY_TYPE_EMOTICON,					/**< �̸�Ƽ�� �� <br> */
	PAD_BUTTON_KEY_TYPE_INTERFACE,					/**< �������̽� �� <br> */
	PAD_BUTTON_KEY_TYPE_MOUSE,						/**< ���콺 �� <br> */
	PAD_BUTTON_KEY_TYPE_MAX,
};


/**
 * �����Ǵ� Ű ����Ʈ <br> 
*/
enum BUTTON_KEY {
	BUTTON_KEY_QUICK_START,
	BUTTON_KEY_QUICK_0			= BUTTON_KEY_QUICK_START,		//Ctrl
	BUTTON_KEY_QUICK_1,											//A
	BUTTON_KEY_QUICK_2,											//S
	BUTTON_KEY_QUICK_3,											//D
	BUTTON_KEY_QUICK_4,											//F
	BUTTON_KEY_QUICK_5,											//Alt
	BUTTON_KEY_QUICK_6,											//Shift Use With Looting 
	BUTTON_KEY_QUICK_7,											//Z
	BUTTON_KEY_QUICK_8,											//X
	BUTTON_KEY_QUICK_9,											//C
	BUTTON_KEY_QUICK_10,										//V
	BUTTON_KEY_QUICK_11,										//Space Use With Looting 
	BUTTON_KEY_QUICK_S1,										//1
	BUTTON_KEY_QUICK_S2,										//2
	BUTTON_KEY_QUICK_S3,										//3
	BUTTON_KEY_QUICK_S4,										//4
	BUTTON_KEY_QUICK_S5,										//5
	BUTTON_KEY_QUICK_S6,										//6
	BUTTON_KEY_QUICK_S7,										//7
	BUTTON_KEY_QUICK_S8,										//8
	BUTTON_KEY_QUICK_S9,										//9
	BUTTON_KEY_QUICK_S10,										//0
	BUTTON_KEY_QUICK_S11,										//-
	BUTTON_KEY_QUICK_S12,										//=
	BUTTON_KEY_QUICK_F1,										//F1
	BUTTON_KEY_QUICK_F2,										//F2

	/*
	BUTTON_KEY_EMOTICON_START,
	BUTTON_KEY_EMOTICON_0		= BUTTON_KEY_EMOTICON_START,	//F1
	BUTTON_KEY_EMOTICON_1,										//F2
	BUTTON_KEY_EMOTICON_2,										//F3
	BUTTON_KEY_EMOTICON_3,										//F4
	BUTTON_KEY_EMOTICON_4,										//F5
	BUTTON_KEY_EMOTICON_5,										//F6
	BUTTON_KEY_EMOTICON_6,										//F7
	BUTTON_KEY_EMOTICON_7,										//F8
	BUTTON_KEY_EMOTICON_8,										//F9
	BUTTON_KEY_EMOTICON_9,										//F10
	BUTTON_KEY_EMOTICON_10,										//F11
	BUTTON_KEY_EMOTICON_11,										//F12
	*/

	BUTTON_KEY_INTERFACE_START,
	BUTTON_KEY_INTERFACE_I		= BUTTON_KEY_INTERFACE_START,	//I Inven
	BUTTON_KEY_INTERFACE_E,										//E Equip
	BUTTON_KEY_INTERFACE_T,										//T State
	BUTTON_KEY_INTERFACE_K,										//K Skill
	BUTTON_KEY_INTERFACE_B,										//B Friend
	BUTTON_KEY_INTERFACE_Q,										//Q Quest
	BUTTON_KEY_INTERFACE_O,										//O Option
	BUTTON_KEY_INTERFACE_P,										//P Team
	BUTTON_KEY_INTERFACE_H,										//H Help
	BUTTON_KEY_INTERFACE_W,										//W World Map
	BUTTON_KEY_INTERFACE_M,										//M	Map Stage
	BUTTON_KEY_INTERFACE_N,										//N Enchant
	BUTTON_KEY_INTERFACE_U,										//U Upgrad
	BUTTON_KEY_INTERFACE_Y,										//Y Way Point
	BUTTON_KEY_INTERFACE_L,										//L Pet
	BUTTON_KEY_INTERFACE_G,										//G Guild
	BUTTON_KEY_INTERFACE_TAB,									//Tab
	//BUTTON_KEY_INTERFACE_SHIFT,
	BUTTON_KEY_INTERFACE_ENTER,									//Enter
	//BUTTON_KEY_INTERFACE_SPACE,
	BUTTON_KEY_INTERFACE_ESC,									//Esc

	BUTTON_KEY_MOUSE_START,
	BUTTON_KEY_MOUSE_L			= BUTTON_KEY_MOUSE_START,
	BUTTON_KEY_MOUSE_R,	
	BUTTON_KEY_MOUSE_MAX,
	BUTTON_KEY_MAX				= BUTTON_KEY_MOUSE_MAX,
};

////
//static std::string g_strKeyList[BUTTON_KEY_MAX + 1] = {
//	"Ctrl",					//BUTTON_KEY_QUICK_0			
//	"A",					//BUTTON_KEY_QUICK_1,
//	"S",					//BUTTON_KEY_QUICK_2,
//	"D",					//BUTTON_KEY_QUICK_3,
//	"F",					//BUTTON_KEY_QUICK_4,
//	"Alt",					//BUTTON_KEY_QUICK_5,
//	"Shift",				//BUTTON_KEY_QUICK_6,		//Use With Looting
//	"Z",					//BUTTON_KEY_QUICK_7,
//	"X",					//BUTTON_KEY_QUICK_8,
//	"C",					//BUTTON_KEY_QUICK_9,
//	"V",					//BUTTON_KEY_QUICK_10,
//	"Space",				//BUTTON_KEY_QUICK_11,		//Use With Looting
//	"1",					//BUTTON_KEY_QUICK_S1
//	"2",					//BUTTON_KEY_QUICK_S2
//	"3",					//BUTTON_KEY_QUICK_S3
//	"4",					//BUTTON_KEY_QUICK_S4
//	"5",					//BUTTON_KEY_QUICK_S5,
//	"6",					//BUTTON_KEY_QUICK_S6,
//	"7",					//BUTTON_KEY_QUICK_S7,
//	"8",					//BUTTON_KEY_QUICK_S8,
//	"9",					//BUTTON_KEY_QUICK_S9,
//	"10",					//BUTTON_KEY_QUICK_S10,
//	"-",					//BUTTON_KEY_QUICK_S11,
//	"=",					//BUTTON_KEY_QUICK_S12,
//	"F1",					//BUTTON_KEY_QUICK_F1,
//	"F2",					//BUTTON_KEY_QUICK_F2,
//	
//	/*
//	"F1",					//BUTTON_KEY_EMOTICON_0		
//	"F2",					//BUTTON_KEY_EMOTICON_1,
//	"F3",					//BUTTON_KEY_EMOTICON_2,
//	"F4",					//BUTTON_KEY_EMOTICON_3,
//	"F5",					//BUTTON_KEY_EMOTICON_4,
//	"F6",					//BUTTON_KEY_EMOTICON_5,
//	"F7",					//BUTTON_KEY_EMOTICON_6,
//	"F8",					//BUTTON_KEY_EMOTICON_7,
//	"F9",					//BUTTON_KEY_EMOTICON_8,
//	"F10",					//BUTTON_KEY_EMOTICON_9,
//	"F11",					//BUTTON_KEY_EMOTICON_10,
//	"F12",					//BUTTON_KEY_EMOTICON_11,	
//	*/
//
//	"I",					//BUTTON_KEY_INTERFACE_I		
//	"E",					//BUTTON_KEY_INTERFACE_E,		
//	"T",					//BUTTON_KEY_INTERFACE_T,		
//	"K",					//BUTTON_KEY_INTERFACE_K,		
//	"B",					//BUTTON_KEY_INTERFACE_B,		
//	"Q",					//BUTTON_KEY_INTERFACE_Q,		
//	"O",					//BUTTON_KEY_INTERFACE_O,		
//	"P",					//BUTTON_KEY_INTERFACE_P,		
//	"H",					//BUTTON_KEY_INTERFACE_H,		
//	"W",					//BUTTON_KEY_INTERFACE_W,		
//	"M",					//BUTTON_KEY_INTERFACE_M,		
//	"N",					//BUTTON_KEY_INTERFACE_N,		
//	"U",					//BUTTON_KEY_INTERFACE_U,		
//	"Y",					//BUTTON_KEY_INTERFACE_Y,		
//	"L",					//BUTTON_KEY_INTERFACE_L,		
//	"G",					//BUTTON_KEY_INTERFACE_G,		
//	"Tab",					//BUTTON_KEY_INTERFACE_TAB,
//	//"Shift",				//BUTTON_KEY_INTERFACE_SHIFT,
//	"Enter",				//BUTTON_KEY_INTERFACE_ENTER,
//	//"Space",				//BUTTON_KEY_INTERFACE_SPACE,
//	"Esc",					//BUTTON_KEY_INTERFACE_ESC,	
//	
//	"MouseL",				//BUTTON_KEY_MOUSE_L		
//	"MouseR",				//BUTTON_KEY_MOUSE_R,	
//	"NULL",					//BUTTON_KEY_MAX			
//};							/**< �����Ǵ� Ű �̸� <br> */


/**
 * ����Ű ���п� <br>
*/
enum BUTTON_FUNC {
	BUTTON_FUNC_0,					/**< ����Ű 1 <br> */
	BUTTON_FUNC_1,					/**< ����Ű 2 <br> */
	BUTTON_FUNC_MAX,
};


/**
 * ���콺 ���п� <br>
*/
enum BUTTON_MOUSE {
	BUTTON_MOUSE_L,					/**< ���콺 L ��ư <br> */
	BUTTON_MOUSE_R,					/**< ���콺 R ��ư <br> */
	BUTTON_MOUSE_MAX,
};


/**
 * ���� �������̽����� �����ϰ��� ������ Ű <br>
*/
enum JOYSTICK_SELECT {
	JOYSTICK_SELECT_NULL,
	JOYSTICK_SELECT_FUNC1,								//����1
	JOYSTICK_SELECT_FUNC2,								//����2
	JOYSTICK_SELECT_MOUSEL,								//���콺 L
	JOYSTICK_SELECT_MOUSER,								//���콺 R

	JOYSTICK_SELECT_KEY_0,								//�Ϲ� Ű
	JOYSTICK_SELECT_KEY_1,
	JOYSTICK_SELECT_KEY_2,
	JOYSTICK_SELECT_KEY_3,
	JOYSTICK_SELECT_KEY_4,
	JOYSTICK_SELECT_KEY_5,
	JOYSTICK_SELECT_KEY_6,
	JOYSTICK_SELECT_KEY_7,
	JOYSTICK_SELECT_KEY_8,
	JOYSTICK_SELECT_KEY_9,
	JOYSTICK_SELECT_KEY_10,
	JOYSTICK_SELECT_KEY_11,

	JOYSTICK_SELECT_FUNC1_0,							//���� Ű 1
	JOYSTICK_SELECT_FUNC1_1,
	JOYSTICK_SELECT_FUNC1_2,
	JOYSTICK_SELECT_FUNC1_3,
	JOYSTICK_SELECT_FUNC1_4,
	JOYSTICK_SELECT_FUNC1_5,
	JOYSTICK_SELECT_FUNC1_6,
	JOYSTICK_SELECT_FUNC1_7,
	JOYSTICK_SELECT_FUNC1_8,
	JOYSTICK_SELECT_FUNC1_9,
	JOYSTICK_SELECT_FUNC1_10,
	JOYSTICK_SELECT_FUNC1_11,

	JOYSTICK_SELECT_FUNC2_0,							//���� Ű 2
	JOYSTICK_SELECT_FUNC2_1,
	JOYSTICK_SELECT_FUNC2_2,
	JOYSTICK_SELECT_FUNC2_3,
	JOYSTICK_SELECT_FUNC2_4,
	JOYSTICK_SELECT_FUNC2_5,
	JOYSTICK_SELECT_FUNC2_6,
	JOYSTICK_SELECT_FUNC2_7,
	JOYSTICK_SELECT_FUNC2_8,
	JOYSTICK_SELECT_FUNC2_9,
	JOYSTICK_SELECT_FUNC2_10,
	JOYSTICK_SELECT_FUNC2_11,
};


static char*	PAD_SETTING_FILE		= "PADSETTING.DAT";			/**< ������ ������ ���� <br> */

/**
 * 1 - �⺻
 * 2 - ���չ�ư ����
 * 3 - Push ���� üũ �߰�
*/
static int		PAD_SETTING_VER			= 3;						/**< ���� ���� <br> */


/**
 * ��ư ���� <br>
*/
struct SPJoyPadButtonInfo {
	PAD_BUTTON_NO		m_iButtonMajor;				/**< �� �Է� Ű <br> */
	PAD_BUTTON_USE		m_iUse;						/**< ��� �뵵 <br> */
	PAD_BUTTON_NO		m_iButtonMinor;				/**< �� �Է� Ű <br> */
	
	BUTTON_KEY			m_iKey;						/**< ���� Ű <br> */
	int					m_iInputState;				/**< �Է� ��Ȳ <br> */
	bool				m_bPush;					/**< ��ư�� ��� ������ �ִ��� �Ǻ��� ��� <br> �ܺο��� ���� <br> */

	//
	SPJoyPadButtonInfo() {
		Clear();
	}

	~SPJoyPadButtonInfo() {

	}

	void Clear() {
		m_iButtonMajor	= PAD_BUTTON_NO_MAX;
		m_iUse			= PAD_BUTTON_USE_NULL;		
		m_iButtonMinor	= PAD_BUTTON_NO_MAX;
		m_iKey			= BUTTON_KEY_MAX;
		m_iInputState	= INPUT_UNPRESS;
		m_bPush			= false;
	}

	void SetInfo(PAD_BUTTON_NO iMajor, PAD_BUTTON_USE iUse, BUTTON_KEY iAction, PAD_BUTTON_NO iMinor = PAD_BUTTON_NO_MAX) {
		m_iButtonMajor	= iMajor;
		m_iUse			= iUse;		
		m_iButtonMinor	= iMinor;
		m_iKey			= iAction;
		m_iInputState	= INPUT_UNPRESS;
		m_bPush			= false;
	}

	bool CopyInfo(SPJoyPadButtonInfo* pSrc) {
		if(pSrc) {
			m_iButtonMajor	= pSrc->m_iButtonMajor;
			m_iUse			= pSrc->m_iUse;
			m_iButtonMinor	= pSrc->m_iButtonMinor;
			m_iKey			= pSrc->m_iKey;
			m_iInputState	= INPUT_UNPRESS;
			m_bPush			= false;

			return true;
		}
		return false;
	}	
};


/**
 * ��ư ������ ������ �����е� ���� ���� <br>
 * Manager�� Interface�� ���� �Ѱ��� ���� ���� <br>
*/
class SPPadSettingInfo {
public:
	JOYSTICK_MODE			m_iJoyStickMode;

	/**
	* ��ư �� Ű ���� ���¹� ��ȣ ������Ʈ �� ���� 36�� <br> �ӽ� ����� <br>
	*/
	std::vector<SPJoyPadButtonInfo*>	m_vpButtonSetting[PAD_BUTTONTYPE_MAX];

	PAD_BUTTON_NO			m_iFunc[BUTTON_FUNC_MAX];			/**< ����Ű�� ������ Ű�� ��� <br> �ӽ� ����� <br> */
	PAD_BUTTON_NO			m_iMouse[BUTTON_MOUSE_MAX];			/**< ���콺�� ������ Ű�� ��� <br> �ӽ� ����� <br>*/	


public:		
	SPPadSettingInfo() {
		int i = 0;
		SPJoyPadButtonInfo* pButtonInfo = NULL;

		for(i = 0; i < PAD_BUTTONTYPE_MAX; i++) {
			for(int j = 0; j < PAD_BUTTON_NO_MAX; j++) {
				pButtonInfo = new SPJoyPadButtonInfo;
				m_vpButtonSetting[i].push_back(pButtonInfo);
			}
		}		
		Clear();
	};

	~SPPadSettingInfo() {
		std::vector<SPJoyPadButtonInfo*>::iterator iter;

		for(int i = 0; i < PAD_BUTTONTYPE_MAX; i++) {
			iter = m_vpButtonSetting[i].begin();
			for(; iter != m_vpButtonSetting[i].end(); ++iter) {
				delete (*iter);
			}
			m_vpButtonSetting[i].clear();
		}
	}
	
	void Clear() {
		m_iJoyStickMode = JOYSTICK_MODE_DIGITAL;
		for(int i = 0; i < BUTTON_FUNC_MAX; i++) {
			m_iFunc[i] = PAD_BUTTON_NO_MAX;			
		}

		for(int i = 0; i < BUTTON_MOUSE_MAX; i++) {
			m_iMouse[i] = PAD_BUTTON_NO_MAX;			
		}

	}

	/**
	 * ��� ��ư ������ �ʱ�ȭ <br>
	 @param 
	 @return  
	*/
	void ClearAllButtonInfo() {
		std::vector<SPJoyPadButtonInfo*>::iterator iter;
		for(int i = 0; i < PAD_BUTTONTYPE_MAX; i++) {
			iter = m_vpButtonSetting[i].begin();
			for(; iter != m_vpButtonSetting[i].end(); ++iter) {
				(*iter)->Clear();
			}		
		}
	}
	
	/**
	 * �־��� SPPadSettingInfo�� �ڽ��� ���� <br>
	 @param  SPPadSettingInfo* pSrcInfo
	 @return  bool
	*/
	bool CopySettingInfo(SPPadSettingInfo* pSrcInfo) {
		if(pSrcInfo == NULL) 
			return false;
		
		m_iJoyStickMode = pSrcInfo->m_iJoyStickMode;
		for(int i = 0; i < BUTTON_FUNC_MAX; i++) {
			m_iFunc[i] = pSrcInfo->m_iFunc[i];
		}

		for(int i = 0; i < BUTTON_MOUSE_MAX; i++) {
			m_iMouse[i] = pSrcInfo->m_iMouse[i];
		}

		bool bRet = false;
		std::vector<SPJoyPadButtonInfo*>::iterator iter;
		std::vector<SPJoyPadButtonInfo*>::iterator iterSrc;
		for(int i = 0; i < PAD_BUTTONTYPE_MAX; i++) {
			iter = m_vpButtonSetting[i].begin();
			iterSrc = pSrcInfo->m_vpButtonSetting[i].begin();
			for(; iter != m_vpButtonSetting[i].end(); ++iter, ++iterSrc) {
				bRet &= (*iter)->CopyInfo((*iterSrc));
			}
		}
		return bRet;
	}
	
	/**
	 * �Ϲ� Ű ������ �Ѵ� <br>
	 @param PAD_BUTTON_NO iMajor	���� ��ư�̸� ����Ʈ���� ��ġ�̱⵵ �ϴ� 
	 @param PAD_BUTTON_USE iUse		��� Ÿ��
	 @param BUTTON_KEY iKey			���� Ű
	 @return  bool
	*/
	bool SetNormalInfo(PAD_BUTTON_NO iMajor, PAD_BUTTON_USE iUse, BUTTON_KEY iKey){		
		if(iMajor < 0 || iMajor >= static_cast<int>(m_vpButtonSetting[PAD_BUTTONTYPE_NORMAL].size()))
			return false;
		SPJoyPadButtonInfo* pInfo = m_vpButtonSetting[PAD_BUTTONTYPE_NORMAL].at(iMajor);

		if(pInfo) {
			pInfo->m_iButtonMajor	= iMajor;
			pInfo->m_iUse			= iUse;
			pInfo->m_iKey			= iKey;
			pInfo->m_iInputState	= INPUT_UNPRESS;			
			return true;
		}

		return false;
	}
	
	/**
	 * ����Ű 1 �� ���� Ű ������ �Ѵ� <br>
	 * ����Ű �� ������ ������ Ű�� ����Ѵ� <br>
	 @param PAD_BUTTON_NO iMinor	���� ��ư �̸� ����Ʈ���� ��ġ�̱⵵ �ϴ� 
	 @param BUTTON_KEY iKey			���� Ű
	 @return  bool
	*/
	bool SetFunc1KeyInfo(PAD_BUTTON_NO iMinor, BUTTON_KEY iKey) {
		if(iMinor < 0 || iMinor >= static_cast<int>(m_vpButtonSetting[PAD_BUTTONTYPE_FUNC1].size()))
			return false;

		SPJoyPadButtonInfo* pInfo = m_vpButtonSetting[PAD_BUTTONTYPE_FUNC1].at(iMinor);
		if(pInfo) {
			if(iMinor == m_iFunc[BUTTON_FUNC_0] || iMinor == m_iFunc[BUTTON_FUNC_1] || 
				iMinor == m_iMouse[BUTTON_MOUSE_L] || iMinor == m_iMouse[BUTTON_MOUSE_R])
			{
				return false;
			}

			pInfo->m_iButtonMajor	= m_iFunc[BUTTON_FUNC_0];
			pInfo->m_iButtonMinor	= iMinor;
			pInfo->m_iKey			= iKey;
			pInfo->m_iInputState	= INPUT_UNPRESS;
		}

		return true;
	}
	
	/**
	* ����Ű 2 �� ���� Ű ������ �Ѵ� <br>
	* ����Ű �� ������ ������ Ű�� ����Ѵ� <br>
	@param PAD_BUTTON_NO iMinor	���� ��ư �̸� ����Ʈ���� ��ġ�̱⵵ �ϴ� 
	@param BUTTON_KEY iKey			���� Ű
	@return  bool
	*/
	bool SetFunc2KeyInfo(PAD_BUTTON_NO iMinor, BUTTON_KEY iKey) {
		if(iMinor < 0 || iMinor >= static_cast<int>(m_vpButtonSetting[PAD_BUTTONTYPE_FUNC2].size()))
			return false;

		SPJoyPadButtonInfo* pInfo = m_vpButtonSetting[PAD_BUTTONTYPE_FUNC2].at(iMinor);
		if(pInfo) {
			if(iMinor == m_iFunc[BUTTON_FUNC_0] || iMinor == m_iFunc[BUTTON_FUNC_1] || 
				iMinor == m_iMouse[BUTTON_MOUSE_L] || iMinor == m_iMouse[BUTTON_MOUSE_R])
			{
				return false;
			}

			pInfo->m_iButtonMajor	= m_iFunc[BUTTON_FUNC_1];
			pInfo->m_iButtonMinor	= iMinor;
			pInfo->m_iKey			= iKey;
			pInfo->m_iInputState	= INPUT_UNPRESS;
		}

		return true;
	}
	
	/**
	 * �־��� ��ġ�� ��ư ������ �����´� <br>
	 @param PAD_BUTTONTYPE iType
	 @param PAD_BUTTON_NO iIndex
	 @return  SPJoyPadButtonInfo*
	*/
	SPJoyPadButtonInfo* GetButtonInfo(PAD_BUTTONTYPE iType, PAD_BUTTON_NO iIndex) {		
		if(iIndex < 0 || iIndex >= static_cast<int>(m_vpButtonSetting[iType].size()))
			return NULL;

		return m_vpButtonSetting[iType].at(iIndex);
	}
	
	/**
	 * �־��� Ű�� ���õ� ��� Ű�� �˻��� ���� Ű�� �ʱ�ȭ �Ѵ� <br>
	 * �ߺ��� �������� �뵵 <br>
	 @param BUTTON_KEY iKey
	 @return  int 
	*/
	int SetClearKey(BUTTON_KEY iKey) {
		int iCount = 0;
		std::vector<SPJoyPadButtonInfo*>::iterator iter;
		for(int i = 0; i < PAD_BUTTONTYPE_MAX; i++) {
			iter = m_vpButtonSetting[i].begin();
			for(; iter != m_vpButtonSetting[i].end(); ++iter) {
				if((*iter)->m_iKey == iKey) {
					(*iter)->m_iKey = BUTTON_KEY_MAX;
					iCount++;
				}
			}
		}

		return iCount;
	}

	/**
	 *
	 @param 
	 @return  
	*/
	bool SetFuncKey(PAD_BUTTONTYPE iType) {
		std::vector<SPJoyPadButtonInfo*>::iterator iter;
		if(iType == PAD_BUTTONTYPE_FUNC1) {
			iter = m_vpButtonSetting[iType].begin();
			for(; iter != m_vpButtonSetting[iType].end(); ++iter) {
				(*iter)->m_iButtonMajor = m_iFunc[BUTTON_FUNC_0];
			}

			return true;
		}
		else if(iType == PAD_BUTTONTYPE_FUNC2) {
			iter = m_vpButtonSetting[iType].begin();
			for(; iter != m_vpButtonSetting[iType].end(); ++iter) {
				(*iter)->m_iButtonMajor = m_iFunc[BUTTON_FUNC_1];
			}
			return true;
		}
		
		return false;
	}
};



//class SPManager;
class SPInputManager;

class SPJoyPadManager {
public:
	SPJoyPadManager();
	~SPJoyPadManager();

	void Process(float fTime);
	void Render(float fTime);		

	/**
	* ������ ��ư ������ �����Ѵ� <br>
	@param 
	@return  
	*/
	void Save();
	
	/**
	* ��ư ������ �ʱ�ȭ�Ѵ� <br>
	@param SPPadSettingInfo* �ʱ�ȭ �ϰ��� �ϴ� setting info NULL�� ���� �ɹ��� �ʱ�ȭ
	@return  
	*/
	void SetDefault(SPPadSettingInfo* pInfo = NULL);

	/**
	*
	@param 
	@return  
	*/
	void SetKeyList();
	
	/**
	 *
	 @param 
	 @return  
	*/
	const char* GetKeyName(BUTTON_KEY iKey);

	/**
	* ButtonSetting�� ���õ� ������ Button�� �����Ѵ� <br> 
	@param 
	@return  
	*/
	void UpdateButton();

	/**
	 * �����е��� �Ƴ��α�/������ ��带 ���� <br>
	 @param JOYSTICK_MODE iMode
	 @return  
	*/
	void SetJoyStickMode(JOYSTICK_MODE iMode);
	
	/**
	 * ���� �����е� ��带 Ȯ�� <br>
	 @param 
	 @return   JOYSTICK_MODE
	*/
	JOYSTICK_MODE GetJoyStickMode();

	/**
	 * �����е� ���� ������ �����´� <br>
	 @param 
	 @return  SPPadSettingInfo*
	*/
	SPPadSettingInfo* GetPadSettingInfo();

	/**
	 * �־��� Ÿ���� m_vpButton �� �����´� 
	 @param PAD_BUTTON_KEY_TYPE iType
	 @return  std::vector<SPJoyPadButtonInfo*>*
	*/
	std::vector<SPJoyPadButtonInfo*>* GetPadButton(PAD_BUTTON_KEY_TYPE iType);

	/**
	 * ���� Ű������ ���� ���� <br> 
	 @param 
	 @return  
	*/
	void SetButtonSetMode(bool bMode) {	m_bButtonSetMode = bMode; }
	
	/**
	 * ���� Ű���������� Ȯ�� <br> 
	 @param 
	 @return  
	*/
	bool IsButtonSetMode()	{ return m_bButtonSetMode; }		
	
	/**
	 * �־��� Ű�� �������� Ű�� ���� <br> 
	 @param 
	 @return  
	*/
	inline void SetSelectKey(JOYSTICK_SELECT iSelect)	{ m_iSelect = iSelect; }
	
	/**
	 * �������� Ű�� �ִ��� Ȯ�� <br>
	 @param 
	 @return  
	*/
	inline JOYSTICK_SELECT GetSelectKey() { return m_iSelect; }
	
	/**
	 * Ű ������ �ٸ� Ű �Է��� �������� ���� <br>
	 @param 
	 @return  
	*/
	inline void SetKeyPass(bool bPass)		{ m_bKeyPass = bPass; }
	
	/**
	 * ���� ��ư������ �ϰ� �ִ��� Ȯ�� <br>
	 @param 
	 @return  
	*/
	inline bool IsKeyPass()					{ return m_bKeyPass; }
	
	/**
	 * �е带 �̿��Ͽ� ���콺 �����͸� �̵��ϰ� �ִ��� ���� <br>
	 @param 
	 @return  
	*/
	inline void SetPadMouseMove(bool bMove)	{ m_bMouseMove = bMove; }
	
	/**
	 * �е带 �̿��Ͽ� ���콺 �����͸� �̵��ϰ� �ִ��� Ȯ�� <br>
	 @param 
	 @return  
	*/
	inline bool IsPadMouseMove()			{ return m_bMouseMove; }
	
	/**
	 * �е带 �̿��Ͽ� ���콺 �����͸� �̵��ϴ� ��� ����ġ <br>
	 @param 
	 @return  
	*/
	inline int	GetFixHeight()				{ return m_iFixHeight; }

	/**
	 * �е带 �̿��Ͽ� ���콺 �����͸� �̵��ϴ� ��� ����ġ <br>
	 @param 
	 @return  
	*/
	inline int	GetFixWidth()				{ return m_iFixWidth; }

protected:
	bool Init();
	void Clean();	
	
	/**
	 * �е� ������ �ε� <br>
	 @param 
	 @return  
	*/
	bool Load();

	/**
	 * ��ư�� ���� ���� �ʱ�ȭ <br> 
	 @param 
	 @return  
	*/
	void ClearAllSettingInfo();	
	
	
	/**
	 * ��� Ű ��ɺ� ���� Ȯ�ο� ���� ���� <br> 
	 @param 
	 @return  
	*/
	void DeleteAllButton();			
	

private:	
	/**
	 * Ű ��ɺ� ���� Ȯ�ο� ���� <br> �� �����ʹ� ���� ��ũ ������ ���� <br> 
	*/
	std::vector<SPJoyPadButtonInfo*>	m_vpButton[PAD_BUTTON_KEY_TYPE_MAX];		

	SPPadSettingInfo*		m_pPadInfo;				/**< �����е� ���� ������ ��� <br> */

	bool					m_bButtonSetMode;		/**< ���� ��ư ���� ������ <br> */
	JOYSTICK_SELECT			m_iSelect;				/**< ���� ������ ���� ������ ��ư <br> */
	bool					m_bKeyPass;				/**< ���� ��ư������ �ϰ� �ִ��� <br> */
	bool					m_bMouseMove;			/**< ���� ���콺 Move�� �е�� �ϰ� �ִ��� <br> */
	
	int						m_iFixWidth;			/**< ������ ���� <br> */
	int						m_iFixHeight;			/**< ������ ���� <br> */
	
	bool					m_bFuncCheckPush1;		/**< ����Ű 1 �����ִ��� Ȯ�� <br> */
	bool					m_bFuncCheckPush2;		/**< ����Ű 2 �����ִ��� Ȯ�� <br> */

	std::string				m_strKeyList[BUTTON_KEY_MAX + 1];
};


