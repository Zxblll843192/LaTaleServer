#pragma once


#define WIID_CASH_TRADE_WAIT_LEFT						(WIID_CASH_TRADE_WAIT	+	10 )
#define WIID_CASH_TRADE_WAIT_CENTER						(WIID_CASH_TRADE_WAIT	+	20 )
#define WIID_CASH_TRADE_WAIT_RIGHT						(WIID_CASH_TRADE_WAIT	+	30 )

#define WIID_CASH_TRADE_WAIT_CANCEL						(WIID_CASH_TRADE_WAIT	+	41 )

#define WIID_CASH_TRADE_WAIT_ITEMIMG					(WIID_CASH_TRADE_WAIT	+	50 )
#define WIID_CASH_TRADE_WAIT_CUSTOMERIMG				(WIID_CASH_TRADE_WAIT	+	60 )
#define WIID_CASH_TRADE_WAIT_HELP						(WIID_CASH_TRADE_WAIT	+	70 )


const int WAITING_FRAME = 14;					/**< �� ��� ���� ���� <br> */
const int WAITING_SRC = 10;						/**< �� ������ ������ �̹��� ���� <br> */

/**
 * �� ������ ���� ���ϸ��̼� ������ <br> 
*/
enum WAIT_ANI_STATUS {
	WAIT_ANI_STATUS_READY,						/**< ����� <br> */
	WAIT_ANI_STATUS_PLAY,						/**< ���ϸ��̼� �� <br> */
	WAIT_ANI_STATUS_END,						/**< 10���� �̹����� ��� �÷��� <br> */
};


/**
 * �� ��� ���� ���� ��ŭ ���� <br> 
 * �� ���� �� ��� �ִϸ��̼� ������ ��� <br>
*/
struct SPWaitAniInfo {
	int				m_iSrcIndex;				/**< ���� �����ִ� �̹��� �ε��� <br> */
	WAIT_ANI_STATUS m_iAniStatus;				/**< ���� ���ϸ��̼� ���� <br> */

	SPWaitAniInfo() {
		Clear();
	}
	~SPWaitAniInfo() {
		Clear();
	}

	void Clear() {
		m_iSrcIndex			= 0;
		m_iAniStatus		= WAIT_ANI_STATUS_READY;
	}
};


class SPWindowCashTradeWait : public SPWindow {

public:	
	SPWindowCashTradeWait(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowCashTradeWait();
  
	virtual void Init();
	virtual void Clean();

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);


	virtual void Process(float fTime);
	virtual void Render(float fTime);

protected:
	void InitSubControl();

	/**
	 * 14���� ���� ���� ���ϸ��̼� ���� �ʱ�ȭ <br> 
	 @param 
	 @return  
	*/
	void InitAnimationInfo();
	
	/**
	 * ���ϸ��̼� �ʱ�ȭ <br>
	 @param 
	 @return  
	*/
	void ResetAnimation();

	/**
	 * ��� ���ϸ��̼� ���μ��� <br>
	 @param 
	 @return  
	*/
	void ProcessAnimation(float fTime);

	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	int OnCancel					(WPARAM wParam, LPARAM lParam);
	// }}

private:
	RECT				m_rtAniSrc[WAITING_SRC];
	RECT				m_rtAniDesc[WAITING_FRAME];
	
	SPWaitAniInfo		m_AniInfo[WAITING_FRAME];	
	
	float				m_fDeley;
	float				m_fAccumulate;

	SPTexture*			m_pAnimation;
};





