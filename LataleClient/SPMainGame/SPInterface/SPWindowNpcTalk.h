#pragma once


#define WIID_NPCTALK_NPCNAME		(WIID_NPCTALK	+	20 )	/**< NPC �̸� ��� ���� <br> */
#define WIID_NPCTALK_LINE			(WIID_NPCTALK	+	30 )	/**< NPC �̸� ��輱 <br> */
#define WIID_NPCTALK_CLOSE			(WIID_NPCTALK	+	40 )	/**< ��ȭâ ���� ��ư <br> */
#define WIID_NPCTALK_MESSAGE		(WIID_NPCTALK	+	50 )	/**< �޽��� ���� �� <br> */
#define WIID_NPCTALK_SKIN			(WIID_NPCTALK	+	100 )


enum TALK_STATE {
	TALK_STATE_NULL		= 0,				/**< ���� �ƹ��� ���°� �ƴ� <br> �Ǵ� SavePont�� ������ ��� �޽��� <br>*/
	TALK_STATE_MENU		= 1,				/**< �޴��� �����ְ� ���� <br> */
	TALK_STATE_START	= 2,				/**< Npc ��ȭ ���� <br> */
	TALK_STATE_TALK		= 3,				/**< Npc ��ȭ �� <br> */
	TALK_STATE_END		= 4,				/**< Npc ��ȭ �� <br> */
};

const int MAX_NEXT_FRAME		= 2;		/**< ���� ǥ�ÿ� ���Ǵ� ���ϸ��̼� ������ <br> */

class SPLDTFile;
class SPWindow;
class SPWindowButton;
class SPWindowTypeWriter;

#include "SPEventDEF.h"
struct SPNpcTalk;
struct SPSavePoint;
enum NPC_EVENT_TYPE;

enum TALK_FADE {
	TALK_FADE_IN,
	TALK_FADE_STOP,
	TALK_FADE_OUT,	
};

enum BOX_VIBRATE {
	BOX_VIBRATE_NULL,
	BOX_VIBRATE_LEFT,
	BOX_VIBRATE_RIGHT,
};



/**
* @class SPWindowNpcTalk
* @brief NPC�� ��ȭ â
* @author Jinhee
* @version 00.00.01
* @date 2005.5.
* @bug ����
* @warning 
*/
class SPWindowNpcTalk : public SPWindow {

public:	
	SPWindowNpcTalk(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowNpcTalk();

	virtual void Init();
	virtual void Clean();
	
	virtual void Show(bool bWithChild = true);
	void ShowComplete();
	
	virtual void Hide(bool bSendServer = true);
	
	
	virtual void Process(float fTime);
	virtual void Render(float fTime);
	

public:
	

protected:

	/**
	 * �Ϻ� ��Ʈ�ѵ��� ����, �ʱ�ȭ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void InitSubControl();	

	/**
	 * �ش� index�� NpcTalkData�� NpcHandler���� �ε��� �����ϵ��� �Ѵ� <br>
	 * ���ο��� SetNpcTalk�� ȣ�� <br> 
	 @param 
	 @return NONE
	*/
	void SetNpcTalkData(int iTalkIndex = 0);
	
	/**
	 * �ε��� NpcTalkData�� BoxPos�� ���� ���� NpcTalk������ ���� <br>
	 @param 
	 @return 
	*/
	void SetNpcTalk();	

	/**
	 * SavePointData���� ���� Page�� ��ȭ ������ ������ �����Ѵ� <br> 
	 @param int iTalkIndex = 1 ��ȭ �ε����� SCROOL_END ���¿��� SavePoint �� msgInfo[index] �� ������
	 @return
	*/	
	void SetSavePointTalk(int iTalkIndex = 0);

	/**
	 *
	 @param 
	 @return  
	*/
	bool LoadAttachImage(int iImageIndex = 0);


protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnSetNpcData		( WPARAM wParam, LPARAM lParam );	//ó�� SPNpc�� �̿��Ͽ� UI�� �����Ѵ� 
	int OnSetSavePoint		( WPARAM wParam, LPARAM lParam );	//Save Point �̿��Ͽ� UI�� ������ ���
	int OnSetNpcTalk		( WPARAM wParam, LPARAM lParam );	/**< �ܺο��� NPCTalk�� �ε� �ϵ��� ��û�� ��� <br> */
	int OnNpcTalkClose		( WPARAM wParam, LPARAM lParam );	/**< Close Button <br> */
	int OnSetBoxType		( WPARAM wParam, LPARAM lParam );	/**< Box Type Setting <br> */

	int OnHideStart			(WPARAM wParam, LPARAM lParam);		/**< Faid In �۾��� �����Ѵ� <br> */
	int OnTypeWriteEnd		(WPARAM wParam, LPARAM lParam);		/**< Ÿ�Զ������� ���ڰ� �� ���� ��� <br> */
	int OnTypeWriteClick	(WPARAM wParam, LPARAM lParam);		/**< ���������� �ϴ� ��� <br> */


private:
	SPWindow*	m_pParent;
	std::string m_strMessage;					/**< â�� �ٿ� Message <br> */	

	SPNpcTalk* m_pNpcTalk;						/**< Npc Talk ���� Data <br> */		
	SPSavePoint* m_pSavePoint;					/**< Save Point Talk ���� Data <br> */
	int m_iTalkIndex;							/**< ���� Save Point Talk �� �� Page <br> */

	TALK_STATE m_iTalkState;					/**< ���� �����찡 ǥ���ϴ� ��ȭ ��Ȳ <br> */
	char	m_szMsg[512];						/**< <br> */

	SPTexture*	m_pWindowSkin[NPC_TALK_WINDOW_MODE_MAX];	/**< �ٴ� ��Ų���� ���� �ؽ��� <br> */
	RECT		m_rtSkinSrc[NPC_TALK_WINDOW_MODE_MAX];		/**< �ٴ� ��Ų �ҽ� <br> */
	
	int			m_iEndHeight;					/**< Skin Faid �۾��� �ִ���� �񱳿� <br> */
	int			m_iEndWidth;					/**< Skin Faid �۾��� �ִ���� �񱳿�  <br> */
	int			m_iMoveSkinHeight;				/**< Skin Faid�� ���̿� ������ �� <br> */
	int			m_iMoveSkinWidth;				/**< Skin Faid�� ���̿� ������ �� <br> */
	
	int			m_iSkinMoveX;					/**< m_iMoveSkiWidth�� ������ �ִ� �� <br> */
	int			m_iSkinMoveY;					/**< m_iMoveSkinHeight�� ������ �ִ� �� <br> */

	int			m_iSkinMoveUnitX;				/**< m_iSkinMoveX�� ������ �ִ� �� <br> */
	int			m_iSkinMoveUnitY;				/**< m_iSkinMoveY�� ������ �ִ� �� <br> */
	
	RECT		m_rtSkinBaseDest;				/**< ������ ������ ������ ��� <br> */
	RECT		m_rtSkinDest;					/**< ��Ų ���� ������ <br> */

	TALK_FADE	m_iTalkFadeType;				/**< ��Ų ���̵� Ÿ�� <br> */
	float		m_fFadeAlpha;					/**< ��Ų ���� ���� <br> */
	float		m_fFadeAlphaUnit;				/**< m_fFadeAlpha ������ �ִ� �� <br> */

	float		m_fAccumulateRender;			/**< ������ �ð� ��� <br> */
	float		m_fCurDelay;					/**< ������ ���� �ð� <br> */

	SPWindow*	m_pNpcName;						/**< NPC �̸� <br> */
	SPWindowTypeWriter* m_pTypeWriter;			/**< ��� <br> */
	bool		m_bTypeWriteEnd;				/**< <br> */
	SPWindowButton* m_pClose;					/**< ���� ��ư <br> */

	bool		m_bShowAttach;					/**< �ΰ� �̹����� ������� �ϴ��� <br> */
	RECT		m_rtAttachSkinDest;				/**< �ΰ� �̹��� ��Ų ��� ���� <br> */
	RECT		m_rtAttachSkinSrc;				/**< �ΰ� �̹��� ��Ų �ҽ�  <br> */
	float		m_fAttachSkinAlpha;				/**< �ΰ� �̹����� ������ ����  <br> */	
	//ATTACH_FADE	m_iAttachFade;
	
	SPLDTFile*	m_pAttachImageLDTFile;
	RECT		m_rtAttachDest;
	RECT		m_rtAttachSrc;
	SPTexture*	m_pAttachImage;

	NPC_TALK_WINDOW_MODE m_iTalkWindowMode;		/**< ���� ��ȭâ ��Ų ���� <br> */
	BOX_VIBRATE	m_iVibrate;						/**< ��Ų ���� ���� <br> */
	float		m_fVibrateTotalRender;			/**< �� ������ �ð� ��� <br> */
	float		m_fVibrateTotalDelay;			/**< �� ������ ���� �ð� <br> */
	float		m_fVibrateRender;				/**< ������ �ð� ��� <br> */
	float		m_fVibrateDelay;				/**< ������ ���� �ð� <br> */

	bool		m_bFocusLose;					/**< ��Ŀ���� ���� ��� ǥ�� <br> */
	SPTexture*	m_pFocusLoseSkin;				/**< ��Ŀ���� ���� ��� �߰� ��Ų <br> */
	RECT		m_rtFocusLoseSkinSrc[NPC_TALK_WINDOW_MODE_MAX];	/**< ��Ŀ���� ���� ��� �߰� ��Ų �ҽ� <br> */

	bool		m_bShowNext;					/**< ���� Ŭ�� ǥ�� <br> */
	SPTexture*	m_pNextSkin;					/**< ���� Ŭ�� ��Ų <br> */
	RECT		m_rtNextSkinDest;				/**< ���� Ŭ�� ��� ����<br> */
	RECT		m_rtNextSkinSrc[MAX_NEXT_FRAME];/**< ���� Ŭ�� ��Ų �ҽ� <br> */
	int			m_iNextFrame;					/**< ��� �÷��� <br> */
	float		m_fNextRender;					/**< ������ �ð� ��� <br> */
	float		m_fNextDelay;					/**< ������ ���� �ð� <br> */
};
