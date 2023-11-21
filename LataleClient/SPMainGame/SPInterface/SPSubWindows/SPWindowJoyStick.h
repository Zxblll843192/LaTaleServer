#pragma once 



enum JOYSTICK_SET_MODE {
	JOYSTICK_SET_MODE_BASE,						/**< �⺻���� ������ <br> */
	JOYSTICK_SET_MODE_BUTTON,					/**< ��ư���� ������ <br> */
	JOYSTICK_SET_MODE_MAX,
};


enum JOYSTICK_BASE_HELP {
	JOYSTICK_BASE_HELP_0,
	JOYSTICK_BASE_HELP_1,
	JOYSTICK_BASE_HELP_2,
	JOYSTICK_BASE_HELP_3,
	JOYSTICK_BASE_HELP_MAX,
};


#define WIID_JOYSTICK_TITLE						(WIID_JOYSTICK	+	1)
#define WIID_JOYSTICK_LINE1						(WIID_JOYSTICK	+	2)


#define WIID_JOYSTICK_BASE						(WIID_JOYSTICK	+	100)	/**< �⺻���� ���� <br> */
#define WIID_JOYSTICK_BASE_TEXT					(WIID_JOYSTICK	+	101)	/**< �⺻���� �ؽ�Ʈ �̹��� <br> */

#define WIID_JOYSTICK_BASE_BTN_TEST_LEFT		(WIID_JOYSTICK	+	105)	/**< ��ư ��ȣȮ�� SKIN <br> */
#define WIID_JOYSTICK_BASE_BTN_TEST_CENTER		(WIID_JOYSTICK	+	106)
#define WIID_JOYSTICK_BASE_BTN_TEST_RIGHT		(WIID_JOYSTICK	+	107)
#define WIID_JOYSTICK_BASE_BTN_TEST_TEXT		(WIID_JOYSTICK	+	108)	/**< ��ư ��ȣȮ�� �ؽ�Ʈ <br> */

#define WIID_JOYSTICK_BASE_PAD_IMAGE			(WIID_JOYSTICK	+	110)	/**< �е� �̹��� <br> */
#define WIID_JOYSTICK_BASE_PAD_MODE_CHACK		(WIID_JOYSTICK	+	111)	/**< �Ƴ��α� üũ ��ư <br> */

#define WIID_JOYSTICK_BASE_FUNCKEY_TEXT_SKIN	(WIID_JOYSTICK	+	120)	/**< ���չ�ư ���� �ؽ�Ʈ <br> */
#define WIID_JOYSTICK_BASE_FUNCKEY_TEXT			(WIID_JOYSTICK	+	121)
#define WIID_JOYSTICK_BASE_FUNCKEY				(WIID_JOYSTICK	+	122)	/**< ���� A <br> */
//#define WIID_JOYSTICK_BASE_FUNCKEY_2			(WIID_JOYSTICK	+	123)	/**< ���� B <br> */

#define WIID_JOYSTICK_BASE_MOUSEKEY_TEXT_SKIN	(WIID_JOYSTICK	+	130)	/**< ���콺 ���� �ؽ�Ʈ <br> */
#define WIID_JOYSTICK_BASE_MOUSEKEY_TEXT		(WIID_JOYSTICK	+	131)	
#define WIID_JOYSTICK_BASE_MOUSEKEY				(WIID_JOYSTICK	+	132)	/**< ���콺 A <br> */
//#define WIID_JOYSTICK_BASE_MOUSEKEY_2			(WIID_JOYSTICK	+	133)	/**< ���콺 B <br> */

#define WIID_JOYSTICK_BASE_HELP_SKIN_LEFT		(WIID_JOYSTICK	+	150)	/**< ���� ���� ���� <br> */
#define WIID_JOYSTICK_BASE_HELP_SKIN_CENTER		(WIID_JOYSTICK	+	151)	/**< ���� ���� ���� <br> */
#define WIID_JOYSTICK_BASE_HELP_SKIN_RIGHT		(WIID_JOYSTICK	+	152)	/**< ���� ���� ������ <br> */
#define WIID_JOYSTICK_BASE_HELP					(WIID_JOYSTICK	+	160)	/**< ���� <br> */

#define WIID_JOYSTICK_BASE_NEXT					(WIID_JOYSTICK	+	190)	/**< ���� ��ư <br> */
#define WIID_JOYSTICK_BASE_INIT					(WIID_JOYSTICK	+	191)	/**< �ʱ�ȭ ��ư <br> */
#define WIID_JOYSTICK_BASE_OK					(WIID_JOYSTICK	+	192)	/**< Ȯ�� ��ư <br> */
#define WIID_JOYSTICK_BASE_CANCEL				(WIID_JOYSTICK	+	193)	/**< ��� ��ư <br> */


#define WIID_JOYSTICK_BUTTON					(WIID_JOYSTICK	+	200)	/**< ��ư���� ���� <br> */
#define WIID_JOYSTICK_BUTTON_TEXT				(WIID_JOYSTICK	+	201)	/**< ��ư���� �ؽ�Ʈ �̹��� <br> */

#define WIID_JOYSTICK_BUTTON_BTN_TEST_LEFT		(WIID_JOYSTICK	+	205)	/**< ��ư ��ȣȮ�� SKIN <br> */
#define WIID_JOYSTICK_BUTTON_BTN_TEST_CENTER	(WIID_JOYSTICK	+	206)
#define WIID_JOYSTICK_BUTTON_BTN_TEST_RIGHT		(WIID_JOYSTICK	+	207)
#define WIID_JOYSTICK_BUTTON_BTN_TEST_TEXT		(WIID_JOYSTICK	+	208)	/**< ��ư ��ȣȮ�� �ؽ�Ʈ <br> */

#define WIID_JOYSTICK_BUTTON_HELP1_SKIN_LEFT	(WIID_JOYSTICK	+	210)	/**< �е� ��ư ��ȣȮ�� �� ���� ���� ���� <br> */
#define WIID_JOYSTICK_BUTTON_HELP1_SKIN_CENTER	(WIID_JOYSTICK	+	211)	/**< �е� ��ư ��ȣȮ�� �� ���� ���� ���� <br> */
#define WIID_JOYSTICK_BUTTON_HELP1_SKIN_RIGHT	(WIID_JOYSTICK	+	212)	/**< �е� ��ư ��ȣȮ�� �� ���� ���� ������ <br> */
#define WIID_JOYSTICK_BUTTON_HELP1				(WIID_JOYSTICK	+	213)	/**< ���� 1 <br> */

#define WIID_JOYSTICK_BUTTON_HELP2_SKIN_LEFT	(WIID_JOYSTICK	+	215)	/**< ����Ű ���� �ϴ��� ���� ���� ���� <br> */
#define WIID_JOYSTICK_BUTTON_HELP2_SKIN_CENTER	(WIID_JOYSTICK	+	216)	/**< ����Ű ���� �ϴ��� ���� ���� ���� <br> */
#define WIID_JOYSTICK_BUTTON_HELP2_SKIN_RIGHT	(WIID_JOYSTICK	+	217)	/**< ����Ű ���� �ϴ��� ���� ���� ������ <br> */
#define WIID_JOYSTICK_BUTTON_HELP2				(WIID_JOYSTICK	+	218)	/**< ���� 2 <br> */

#define WIID_JOYSTICK_BUTTON_KEY_LEFT			(WIID_JOYSTICK	+	220)	/**< Ű �Է�â SKIN <br> */
#define WIID_JOYSTICK_BUTTON_KEY_CENTER			(WIID_JOYSTICK	+	221)
#define WIID_JOYSTICK_BUTTON_KEY_RIGHT			(WIID_JOYSTICK	+	222)

#define WIID_JOYSTICK_BUTTON_PREV				(WIID_JOYSTICK	+	225)	/**< ���� ��ư <br> */
#define WIID_JOYSTICK_BUTTON_INIT				(WIID_JOYSTICK	+	226)	/**< �ʱ�ȭ ��ư <br> */
#define WIID_JOYSTICK_BUTTON_OK					(WIID_JOYSTICK	+	227)	/**< Ȯ�� ��ư <br> */
#define WIID_JOYSTICK_BUTTON_CANCEL				(WIID_JOYSTICK	+	228)	/**< ��� ��ư <br> */

#define WIID_JOYSTICK_BUTTON_NORMAL				(WIID_JOYSTICK	+	230)	/**< �� ����Ű, ����1, ����2 <br> */

#define WIID_JOYSTICK_BUTTON_KEY				(WIID_JOYSTICK	+	250)	/**< Ű �Է��� �޴� ��ư <br> 12�� */

#define WIID_JOYSTICK_BUTTON_INFO_TEXT_IMAGE	(WIID_JOYSTICK	+	300)	/**< ����Ű ���� �ؽ�Ʈ <br> */
#define WIID_JOYSTICK_BUTTON_KEYBOARD_IMAGE		(WIID_JOYSTICK	+	301)	/**< Ű���� �̹��� <br> */
#define WIID_JOYSTICK_BUTTON_KEYBOARD_KEY		(WIID_JOYSTICK	+	310)	/**< Ű���� ������ Ű <br> */

const int MAX_FUNC_BUTTON				= 2;
const int MAX_MOUSE_BUTTON				= 2;

#include "SPJoyPadManager.h"
class SPWindow;
class SPWindowButton;

class SPWindowJoyStick : public SPWindow 
{
public:
	SPWindowJoyStick(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);
	virtual ~SPWindowJoyStick();

	virtual void Init();
	virtual void Clean();

	virtual void Process(float fTime);
	virtual void Render(float fTime);



protected:
	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);		

	/**
	* ���� ��Ʈ�� ���� <br>
	@param 
	@return
	*/
	void InitSubControl();
	
	/**
	 * 12���� Ű �Է� ��ư ���ÿ� <br> 
	 @param 
	 @return  
	*/
	inline void SetKeyButton(SPWindowButton* pButton);

	/**
	 * JOYSTICK_SET_MODE ���� �������̽� ����
	 @param 
	 @return  
	*/
	void UpdateSubControl();

	/**
	 * ��ư������ ������ Ű ������ ������Ʈ ���ش� <br> 
	 @param 
	 @return  
	*/
	void UpdateKeyList();

	/**
	* �е� �Է½�ȣ�� üũ�Ѵ� <br>
	@param 
	@return  
	*/
	void PadCheckProcess(float fTime);
	
	/**
	 * ����Ű�� ���콺 Ű�� �����Ѵ� <br> 
	 @param PAD_BUTTON_NO iButton	���õ� ��ư
	 @return  bool
	*/
	bool SetSpecialKey(PAD_BUTTON_NO iButton);	

	/**
	 * Ű���� �Է��� üũ �Ѵ� <br> 
	 @param 
	 @return  
	*/
	void KeyCheckProcess(float fTime);

protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnNext				(WPARAM wParam, LPARAM lparam);
	int OnReset				(WPARAM wParam, LPARAM lparam);
	int OnOk				(WPARAM wParam, LPARAM lparam);
	int OnCancel			(WPARAM wParam, LPARAM lparam);
	int OnPrev				(WPARAM wParam, LPARAM lparam);
	int OnPadMode			(WPARAM wParam, LPARAM lparam);							/**< �Ƴ��α� üũ �ڽ� <br> */
	int OnSelectFunc		(unsigned int iID, WPARAM wParam, LPARAM lparam);		/**< ����Ű 1, 2 <br> */
	int OnSelectMouse		(unsigned int iID, WPARAM wParam, LPARAM lparam);		/**< Mouse L, R <br> */
	int OnSelectKeyType		(unsigned int iID, WPARAM wParam, LPARAM lparam);		/**< ����Ű �Է�, ����Ű �Է� 1, ����Ű �Է� 2 <br> */
	int OnSelectKey			(unsigned int iID, WPARAM wParam, LPARAM lparam);		/**< 12���� Ű <br> */

private:
	SPTexture*				m_pTextureBase;							/**< ������ ������ ���ҽ� <br> */
	RECT					m_rtBaseSrc[WINDOW_BASE_MAX];
	RECT					m_rtBaseDest[WINDOW_BASE_MAX];

	JOYSTICK_SET_MODE		m_iSetMode;								/**< ���� ��� <br> */
	SPWindow*				m_pSetMode[JOYSTICK_SET_MODE_MAX];		/**< �� ��� �� ���� ������ <br> */

	SPTexture*				m_pTextureButton;						/**< ��ư ǥ���� ���ҽ� <br> */
	RECT					m_rtButtonSkinSrcNormal;				/**< �е��ư ��ȣ �� ��Ų �ҽ� �Ϲ� <br> */
	RECT					m_rtButtonSkinSrcPush;					/**< �е��ư ��ȣ �� ��Ų �ҽ� �Է� <br> */
	RECT					m_rtButtonSkinDest[PAD_BUTTON_NO_MAX];	/**< �е��ư ��ȣ �� ��Ų ��� <br> */
	RECT					m_rtButtonSrc[PAD_BUTTON_NO_MAX + 1];	/**< �е��ư ��ȣ �ҽ� <br> */
	RECT					m_rtButtonDest[PAD_BUTTON_NO_MAX];		/**< �е��ư ��ȣ ��� <br> */
	bool					m_bButtonPush[PAD_BUTTON_NO_MAX];		/**< �е��ư ��ȣ �Է� ���� <br> */

	RECT					m_rtFuncSkinDest[BUTTON_FUNC_MAX];		/**< ����Ű ��Ų ��� <br> */
	RECT					m_rtFuncDest[BUTTON_FUNC_MAX];			/**< ����Ű �е��ư ��� <br> */

	RECT					m_rtMouseSkinDest[BUTTON_MOUSE_MAX];	/**< ���콺 ��� <br> */
	RECT					m_rtMouseDest[BUTTON_MOUSE_MAX];		/**< ���콺 �е��ư ��� <br> */

	SPWindowButton*			m_pModeCheck;							/**< �Ƴ��α�, ������ üũ ��ư <br> */
	SPWindowButton*			m_pFunc[BUTTON_FUNC_MAX];				/**< ���չ�ư ���� üũ ��ư <br> */
	SPWindowButton*			m_pMouse[BUTTON_MOUSE_MAX];				/**< ���콺��ư ���� üũ ��ư <br> */
	//JOYSTICK_SELECT			m_iSelect;								/**< ���� ��� <br> */
	SPWindow*				m_pBaseHelp[JOYSTICK_BASE_HELP_MAX];	/**< <br> */
	
	SPWindowButton*			m_pButtonMode[PAD_BUTTONTYPE_MAX];		/**< ����Ű, ����1,2 ���� �� ��ư <br> */
	PAD_BUTTONTYPE			m_iButtonSetType;
	SPWindowButton*			m_pButtonKey[PAD_BUTTON_NO_MAX];		/**< Ű�Է��� �ް�, ����ϰ�, ������ ��ư <br> */
	PAD_BUTTON_NO			m_iButtonSetNo;

	RECT					m_rtButtonSetSkinDest[PAD_BUTTON_NO_MAX];/**< ����Ű, ����1,2 �� �� ��ư ��ġ ��Ų ��� <br> */
	RECT					m_rtButtonSetDest[PAD_BUTTON_NO_MAX];	/**< ����Ű, ����1,2 �� �� ��ư ��� <br> */
	
	SPPadSettingInfo*		m_pCopyInfo;							/**< ����Ʈ�� �е� ���� ���� <br> */	
	SPJoyPadManager*		m_pManager;								/**< SPJoyPadManager* <br> */	
	
	SPWindowButton*			m_pButtonNext;							/**< ���� ��ư <br> */
	SPWindowButton*			m_pButtonOk;							/**< Ȯ�� ��ư <br> */
	SPWindowButton*			m_pButtonReset;							/**< �ʱ�ȭ ��ư <br> */
	std::vector<SPWindow*>	m_vpKeyButton;							/**< ����Ű ������ ���Ǵ� Ű�� <br> */
};


