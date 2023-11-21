// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowAuctionMsg.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/


#pragma once


#define WIID_AUCTION_DIALOG					(WIID_AUCTION_MSG + 1)		// ��� ������ ���̾�α�
#define WIID_AUCTION_DIALOG_ACCEPT_MONEY	(WIID_AUCTION_MSG + 11)		// �����ݾ� (+2)
#define WIID_AUCTION_DIALOG_FEE_MONEY		(WIID_AUCTION_MSG + 13)		// ������ (+3)
#define WIID_AUCTION_DIALOG_GIVEN_MONEY		(WIID_AUCTION_MSG + 16)		// �����ݾ� (+2)
#define WIID_AUCTION_DIALOG_TEXT			(WIID_AUCTION_MSG + 18)		// ������ �޽���
#define WIID_AUCTION_DIALOG_OK				(WIID_AUCTION_MSG + 21)		// Ȯ��
#define WIID_AUCTION_DIALOG_CANCEL			(WIID_AUCTION_MSG + 22)		// ���

#define WIID_AUCTION_MESSAGE				(WIID_AUCTION_MSG + 51)		// ��� �޽��� â
#define WIID_AUCTION_MESSAGE_TEXT			(WIID_AUCTION_MSG + 53)		// ��� �޽���
#define WIID_AUCTION_MESSAGE_OK				(WIID_AUCTION_MSG + 54)		// Ȯ��
#define WIID_AUCTION_MESSAGE_CANCEL			(WIID_AUCTION_MSG + 55)		// ���
#define WIID_AUCTION_MESSAGE_BIDSPOT		(WIID_AUCTION_MSG + 56)		// ��ñ���(������==�ﱸ��)

#define WIID_AUCTION_WAIT					(WIID_AUCTION_MSG + 71)		// Wait �޽��� â (+2)
#define WIID_AUCTION_WAIT_IMG1				(WIID_AUCTION_MSG + 73)		// Wait Image
#define WIID_AUCTION_WAIT_IMG2				(WIID_AUCTION_MSG + 74)		// Wait Image
#define WIID_AUCTION_WAIT_TEXT				(WIID_AUCTION_MSG + 75)		// Wait �޽���


enum AUCTION_MSG_TYPE	{
	AUCTION_MSG_NULL = 0,
	AUCTION_MSG_NOTICE,			// �Ϲ� �޽���
	AUCTION_MSG_REFRESH,		// ���� ������
	AUCTION_MSG_BID,			// ���� ������ ǥ��
	AUCTION_MSG_SPOT,			// �ﱸ ������ ǥ��
	AUCTION_MSG_BIDSPOT,		// ������ = �ﱸ �ΰ��
	AUCTION_MSG_CANCEL,			// ��� ���
	AUCTION_MSG_SERVER_DOWN,	// Server Down
} ;




//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class SPWindow;
class SPAuctionAttr ;
struct AUCTION_TYPE_INFO;
class SPWindowAuctionMsg : public SPWindow
{
public:
	SPWindowAuctionMsg(WND_ID WndClassID , INSTANCE_ID InstanceID );
	SPWindowAuctionMsg( INSTANCE_ID InstanceID , int iX , int iY , int iCX , int iCY , SPWindow* pParent = NULL );
	virtual ~SPWindowAuctionMsg();

	virtual void	Init();
	virtual void	Clean();

	virtual void	Process( float fTime );
	//virtual void	Render( float fTime );

	//virtual void	Show( bool bWithChild = true );
	virtual void	Hide(bool bSendServer = true);

	void ShowModalWindow(SPWindow* pWindow) ;
	void HideMsgWindow() ;
	void SetAuctionWindow(SPWindow* pWindow) ;

private:
	void InitAuctionFeeDialog();					// ������ Dialog
	void InitAuctionMessage();						// Message Dialog
	void InitAuctionWait() ;						// Wait Dialog


private:
	SPWindow*	m_pWindowFeeDialog;
	SPWindow*	m_pWindowMessage;
	SPWindow*	m_pWindowWait;
	SPWindow*	m_pWindowAuction;

	bool		m_bShowFeeDialog ;		// ������
	bool		m_bShowMessage ;		// �˸� â
	bool		m_bShowWait ;			// ������ ���â
	int			m_iWaitImgIndex ;		// Wait Image Animation Index
	float		m_fWaitImgTime ;		// Wait Image Animation Time
	AUCTION_MSG_TYPE	m_iMessageType ;		// �޽���â Ÿ��
	SPAuctionAttr*		m_pBidItemAttr ;		// �����ϴ� ������ �Ӽ�

protected:

	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()
	virtual int OnAuctionServerClose(WPARAM wParam, LPARAM lParam) ;		// Server Down
	virtual int OnAuctionWaitShow(WPARAM wParam, LPARAM lParam) ;			// Show Wait Dialog
	virtual int OnAuctionWaitClose(WPARAM wParam, LPARAM lParam) ;			// Hide Wait Dialog
	
	virtual int OnAuctionNotice(WPARAM wParam, LPARAM lParam) ;			// MSG_TYPE, MSG
	virtual int OnAuctionMessage(WPARAM wParam, LPARAM lParam) ;		// MSG_TYPE, MSG
	virtual int OnAuctionBidMessage(WPARAM wParam, LPARAM lParam) ;		// MSG_TYPE, SPAuctionAttr*
	virtual int OnAuctionFeeMessage(WPARAM wParam, LPARAM lParam) ;		// MSG_TYPE, SPAuctionAttr*

	// Dialog & Message
	int OnFeeDialogOK(WPARAM wParam, LPARAM lParam) ;			// ������ ok
	int OnFeeDialogCancel(WPARAM wParam, LPARAM lParam);		// ������ Cancel
	int OnMessageOK(WPARAM wParam, LPARAM lParam) ;				// Message ok
	int OnMessageBidSpot(WPARAM wParam, LPARAM lParam);			// Message BidSpot
	int OnMessageCancel(WPARAM wParam, LPARAM lParam);			// Message Cancel

	// }}


};



