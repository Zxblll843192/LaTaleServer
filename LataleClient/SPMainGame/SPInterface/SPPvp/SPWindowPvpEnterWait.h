#pragma once

#define WIID_PVPENTERWAIT_ANI						(WIID_PVPENTERWAIT + 10)
#define WIID_PVPENTERWAIT_HELP						(WIID_PVPENTERWAIT + 20)
#define WIID_PVPENTERWAIT_CANCEL					(WIID_PVPENTERWAIT + 100)

////
//enum PVPENTERWAIT_BASE {
//	PVPENTERWAIT_BASE_TOP_LEFT,
//	PVPENTERWAIT_BASE_TOP,
//	PVPENTERWAIT_BASE_TOP_RIGHT,
//	PVPENTERWAIT_BASE_CENTER_LEFT,
//	PVPENTERWAIT_BASE_CENTER,
//	PVPENTERWAIT_BASE_CENTER_RIGHT,
//	PVPENTERWAIT_BASE_BOTTOM_LEFT,
//	PVPENTERWAIT_BASE_BOTTOM,
//	PVPENTERWAIT_BASE_BOTTOM_RIGHT,
//	PVPENTERWAIT_BASE_MAX,
//};


const int MAX_WAIT_ANI_FRAME			= 6;
//const int PVP_ENTERWAIT_SOUND_EFFECT	= 883;


/**
* @class SPWindowPvpReserve
* @brief PVP���� 
* @author Jinhee
* @version 00.00.01
* @date 2005.5.
* @bug ����
* @warning 
*/
class SPWindowPvpEnterWait : public SPWindow {
public:	
	SPWindowPvpEnterWait(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowPvpEnterWait();

	virtual void Init();
	virtual void Clean();

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);

	virtual void Process(float fTime);
	virtual void Render(float fTime);

protected:
	/**
	* ���� ��Ʈ�� ���� <br> 
	@param 
	@return  
	*/
	void InitSubControl();
	/**
	* Show�� Sound <br> 
	@param int iSoundID		 ��Ī ���� ����Ʈ ID
	@return  
	*/
	//void WaitEffectSound(int iSoundID);	// >> SPzone ���� ��Ī ����� ����

protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()		
	int OnPvpRegist			(WPARAM wParam, LPARAM lParam);			/**< ��û��� ���·� ��ȯ <br> */
	int OnPvpRegistCancel	(WPARAM wParam, LPARAM lParam);			/**< ��û Cancel ���� <br> ���� ���� <br> */
	int OnCancel			(WPARAM wParam, LPARAM lParam);			/**< ��û Cancel ��ư <br> */
	//}}

private:
	SPTexture*		m_pTextureBase;									/**< ������ ������ ���ҽ� <br> */
	//RECT			m_rtSrcBase[PVPENTERWAIT_BASE_MAX];				/**< ������ ���� �ҽ� ���� <br> */
	//RECT			m_rtDestBase[PVPENTERWAIT_BASE_MAX];			/**< ������ ���� ��� <br> */
	SPWindow*		m_pWindowMsg;
	
	int				m_iAniFrame;									/**< ��� �÷��� <br> */
	float			m_fAniRender;									/**< ������ �ð� ��� <br> */
	float			m_fAniDelay;									/**< ������ ���� �ð� <br> */
	RECT			m_rtAniSrc[MAX_WAIT_ANI_FRAME];
	RECT			m_rtAniDest;	
};