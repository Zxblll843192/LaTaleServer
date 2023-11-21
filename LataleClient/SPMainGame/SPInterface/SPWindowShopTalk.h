#pragma once

#define WIID_SHOPTALK_TOP			(WIID_SHOPTALK		+	1 )
#define WIID_SHOPTALK_CENTER		(WIID_SHOPTALK		+	2 )
#define WIID_SHOPTALK_BOTTOM		(WIID_SHOPTALK		+	3 )
#define WIID_SHOPTALK_TAIL			(WIID_SHOPTALK		+	4 )

#define WIID_SHOPTALK_MESSAGE		(WIID_SHOPTALK		+	10 )	//�޽��� ����
#define WIID_SHOPTALK_INFO			(WIID_SHOPTALK		+	20 )	//Info ����
#define WIID_SHOPTALK_CLOSE			(WIID_SHOPTALK		+	30 )	//Cloase ��ư

////
//enum FRAME_IMAGE_TYPE {
//	FRAME_IMAGE_TYPE_NULL = 0,				/**< Frame Image Auto Load <br> */
//	FRAME_IMAGE_TYPE_ROOF = 1,				/**< Frame Image Roof <br> */
//	FRAME_IMAGE_TYPE_CENTER = 2,			/**< Frame Image Center <br> */
//	FRAME_IMAGE_TYPE_BOTTOM = 3,			/**< Frame Image Bottom <br> */
//};


class SPWindow;


/**
* @class SPWindowShopTalk
* @brief NPC ���� ����Ʈ�� ��� ��� �޽���â
* @author Jinhee
* @version 00.00.01
* @date 2005.5.16
* @bug ����
* @warning 
*/
class SPWindowShopTalk : public SPWindow {

public:	
	SPWindowShopTalk(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent = NULL);	
	virtual ~SPWindowShopTalk();

	virtual void Init();
	virtual void Clean();
	virtual void SetFocus();
	virtual void Process(float fTime);
	virtual void Render(float fTime);
	virtual void RenderText();

	virtual void Show(bool bWithChild = true);
	virtual void Hide(bool bSendServer = true);
	//virtual bool IsShow();
	//virtual void Hide();  // ������� ������ �� ����..

public:

protected:
	/**
	 *
	 @param
	 @return
	*/
	void	UpdateMessage();


protected:
	// {{ ShopTalk Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()

	virtual int OnShopTalkClose		( WPARAM wParam, LPARAM lParam );
	//virtual int OnShopTalkShow		( WPARAM wParam, LPARAM lParam );
	//virtual int OnShopTalkTextSet	( WPARAM wParam, LPARAM lParam );
	//virtual int OnMessageUpdate		(WPARAM wParam, LPARAM lParam);
	virtual int	OnSetMessage		(WPARAM wParam, LPARAM lParam);	


protected:
	std::string m_strMessage;					/**< â�� �ٿ� ShopTalk <br> */
	std::string m_strInfo;						/**< â �ϴܿ� ǥ�ǵ� �ൿ ���� <br> */	
	SPWindow* m_pMessage;						/**< Static Window ShopTalk <br> */	
	char		m_szMsg[512];			/**< <br> */
protected:


};
