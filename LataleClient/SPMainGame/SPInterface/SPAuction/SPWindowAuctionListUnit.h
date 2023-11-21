// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowAuctionRegist.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/


#pragma once

#include "PacketID.h"

enum AUCTION_BID_TYPE	{
	BID_ALLENABLE = 0,	// ���� ����
	BID_ENABLE,			// ���۰��� ������ �ﱸ �Ұ�
	BID_SELF,			// ��������ǰ (�ﱸ ����)
	BID_OWN,			// �� ��� ��ǰ
	BID_OVER,			// ��ȸ���� ��ǰ
	BID_DISABLE,		// �������� ���۰��� �ִ°��(��� �Ұ�)
} ;

class SPItem ;
class SPAuctionAttr ;
class SPWindowAuctionListUNIT : public SPWindow
{
public:
	SPWindowAuctionListUNIT( INSTANCE_ID InstanceID , int iX , int iY , int iCX , int iCY , SPWindow* pParent = NULL );
	virtual	~SPWindowAuctionListUNIT();

	virtual	void	Init();
	virtual	void	Clean();
	virtual void	Show(bool bWithChild = true);
	virtual void	Hide(bool bSendServer = true);

	virtual	void	Process( float fTime );
	virtual	void	Render( float fTime );
	virtual void	RefreshRelationCoord();

	void			SetAuctionItem( SPAuctionAttr* pAuctionAttr ) ;			// SPAuctionAttr ����
	void			ClearAuctionInfo() ;						// Auction ���� �ʱ�ȭ
	void			SetItemField( SPItem* pItem) ;				// Item
	void			SetItemField( int iType, INT64 iMoney ) ;	// Oz, Point, Ely
	

	int				GetAuctionType()				{	return m_iAuctionType ;		}
	INT64			GetAuctionID()					{	return m_iAuctionID;		}
	SPAuctionAttr*	GetAuctionAttr()				{	return m_pAuctionAttr;		}

	void			SetLevel( int iLevel) ;					// ��� ���� ����
	void			SetDuration( int iDuration) ;			// ������ ����
	void			SetFinishTime() ;						// �����ð�
	void			SetSeller( const char* szSeller, USERID iSellUser) ;					// �Ǹ���
	void			SetPrice( INT64 iBidPrice, INT64 iSpotPrice, USERID iBidUser ) ;		// ��� ������ ����
	void			SetOutBid() ;				// [��ȸ����] ǥ��
	void			UpdateBidButtonEnable() ;

	void			SetSelectBG( char* pTextureFile, RECT* prcSrc ) ;		// ���� �ڽ� ��������
	void			SetWndState( WND_STATE eWndState );
	void			SetRelatedPos(int iX, int iY) ;
	void			SetSelectAble(bool bSelectAble)		{	 m_bSelectAble = bSelectAble;	}		// ��� ��� ����

private:
	void			ReposOwnImage();
	void			SetItemCount(int iCount) ;


protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()

	virtual int		OnCursorEnter( WPARAM wParam, LPARAM lParam );
	virtual int		OnCursorOut( WPARAM wParam, LPARAM lParam );
	virtual int		OnCursorMove( WPARAM wParam, LPARAM lParam );
	virtual int		OnCursorEnter( unsigned int iID, WPARAM wParam , LPARAM lParam );
	virtual int		OnCursorOut( unsigned int iID, WPARAM wParam , LPARAM lParam );
	virtual int		OnCursorMove( unsigned int iID, WPARAM wParam , LPARAM lParam );
	virtual int		OnToolTipEnter(unsigned int iID, WPARAM wParam, LPARAM lParam);
	virtual int		OnToolTipOut(unsigned int iID, WPARAM wParam, LPARAM lParam);
	virtual int		OnToolTipMove(unsigned int iID, WPARAM wParam, LPARAM lParam);

	virtual int		OnLButtonUp( unsigned int iID, WPARAM wParam , LPARAM lParam );
	// }}


protected:
	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//
	bool				m_bShowToolTip;
	bool				m_bSelectAble ;
	bool				m_bExpired ;			// ��Žð� ���� ����
	bool				m_bUsable ;				// ��� ���ɿ���
	
	int					m_iAuctionType ;		// ��� Ÿ��
	int					m_iPriceType ;			// �������� ���� (Ely, Cash, Point)
	AUCTION_BID_TYPE	m_iBidEnable ;			// ���� ���� (0:����, 1:��������, 2:���ι�ǰ, 3:��ȸ����)
	INT64				m_iAuctionID ;			// ��� ID
	SPAuctionAttr*		m_pAuctionAttr ;		// ���� �ö� ������ ����
	SPItem*				m_pItemInfo ;			// ���� �ö� ������ ����

	SPTexture*			m_pBGTexture;
	SPTexture*			m_pDisTexture;
	RECT				m_rcBGDest;				// ��� ���� �̹���
	RECT				m_rcBGSrc;
	RECT				m_rcLineDest;			// �ϴ� ���� ����
	RECT				m_rcLineSrc;
	RECT				m_rcDisDest;			// Disable
	RECT				m_rcDisSrc;

	INSTANCE_ID			m_iStartID;
	INSTANCE_ID			m_iEndID;
	INSTANCE_ID			m_iItemIcon;		// Item Icon for Tooltip
	INSTANCE_ID			m_iBidButton;		// ���� ��ư
	INSTANCE_ID			m_iSpotButton;		// ��ñ��� ��ư

};