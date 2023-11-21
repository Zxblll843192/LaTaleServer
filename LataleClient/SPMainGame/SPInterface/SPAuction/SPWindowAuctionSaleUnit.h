// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowAuctionSaleUnit.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/


#pragma once

#include "PacketID.h"

class SPItem ;
class SPAuctionAttr ;
class SPWindowAuctionSaleUNIT : public SPWindow
{
public:
	SPWindowAuctionSaleUNIT( INSTANCE_ID InstanceID , int iX , int iY , int iCX , int iCY , SPWindow* pParent = NULL );
	virtual	~SPWindowAuctionSaleUNIT();

	virtual	void	Init();
	virtual	void	Clean();
	virtual void	Show(bool bWithChild = true);
	virtual void	Hide(bool bSendServer = true);

	virtual	void	Process( float fTime );
	virtual	void	Render( float fTime );
	virtual void	RefreshRelationCoord();

	void			SetAuctionItem( SPAuctionAttr* pAuctionAttr ) ;
	void			ClearAuctionInfo() ;						// Auction ���� �ʱ�ȭ
	void			SetItemField( SPItem* pItem) ;				// Item
	void			SetItemField( int iType, INT64 iMoney ) ;	// Oz, Point, Ely
	

	int				GetAuctionType()				{	return m_iAuctionType ;		}
	INT64			GetAuctionID()					{	return m_iAuctionID;		}
	SPAuctionAttr*	GetAuctionAttr()				{	return m_pAuctionAttr;		}

	void			SetFinishTime() ;							// �����ð�
	void			SetBidder( const char* szBidder) ;			// ������
	void			SetPrice( INT64 iBidPrice, INT64 iSpotPrice, USERID iBidUser ) ;		// ��� ������ ����
	
	void			SetSelectBG( char* pTextureFile, RECT* prcSrc ) ;		// ���� �ڽ� ��������
	void			SetWndState( WND_STATE eWndState );
	void			SetRelatedPos(int iX, int iY) ;
	void			SetSelectAble(bool bSelectAble)		{	 m_bSelectAble = bSelectAble;	}		// ��� ��� ����

private:
	void			ReposOwnImage();
	DWORD			GetRareLevelColor(int iRLevel) ;
	void			SetItemCount(int iCount) ;


protected:
	// {{ Message Map	
	SPIMESSAGE_OBJ_MAP_DECLARE()

	int				OnCursorEnter		( WPARAM wParam, LPARAM lParam );
	int				OnCursorOut			( WPARAM wParam, LPARAM lParam );
	int				OnCursorMove		( WPARAM wParam, LPARAM lParam );
	int				OnCursorEnter		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int				OnCursorOut			( unsigned int iID, WPARAM wParam , LPARAM lParam );
	int				OnCursorMove		( unsigned int iID, WPARAM wParam , LPARAM lParam );
	virtual int		OnToolTipEnter(unsigned int iID, WPARAM wParam, LPARAM lParam);
	virtual int		OnToolTipOut(unsigned int iID, WPARAM wParam, LPARAM lParam);
	virtual int		OnToolTipMove(unsigned int iID, WPARAM wParam, LPARAM lParam);

	int				OnSaleCancel		( WPARAM wParam, LPARAM lParam );
	// }}


protected:
	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//
	int					m_iAuctionType ;		// ��� Ÿ��
	INT64				m_iAuctionID ;			// ��� ID
	SPAuctionAttr*		m_pAuctionAttr ;
	SPItem*				m_pItemInfo ;

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
	INSTANCE_ID			m_iItemIcon;	// Item Icon for Tooltip
	INSTANCE_ID			m_iCancelButton;	// ���� ��� ��ư

	bool				m_bShowToolTip;
	bool				m_bSelectAble ;
	bool				m_bUsable ;				// ��� ���ɿ���
};