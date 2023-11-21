// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowAuctionSale.cpp
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/


#include "SPCommon.h"
#include "SPUtil.h"

#include "SPWindowDEF.h"
#include "SPWindowListDEF.h"
#include "SPWindow.h"
#include "SPWindowStatic.h"
#include "SPWindowButton.h"
#include "SPWindowEdit.h"
#include "SPWindowAuctionSaleUnit.h"
#include "SPWindowPageSelect.h"

#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"
#include "SPResourceManager.h"

#include "SPGameObjectDEF.h"
#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPGameObject.h"
#include "SPGOBCluster.h"
#include "SPMOBCluster.h"
#include "SPGOBModelUnit.h"
#include "SPGOBStatus.h"
#include "SPMonsterModelUnit.h"
#include "SPGOBManager.h"
#include "SPPlayer.h"
#include "SPPlayerInvenArchive.h"

#include "SPItem.h"
#include "SPItemAttr.h"
#include "SPItemStatus.h"
#include "SPItemCluster.h"

#include "SPAuctionDef.h"
#include "SPAuctionAttr.h"
#include "SPAuctionArchive.h"
#include "SPAuctionManager.h"

#include "SPCheckManager.h"
#include "SPTimer.h"

#include "GlobalDefines_Share.h"
#include "SPWindowAuction.h"
#include "SPWindowAuctionMsg.h"
#include "_Error_log.h"


void SPWindowAuction::InitAuctionSale()
{
	//int i ;
	SPWindowStatic*	pWindowStaticFrame;
	SPWindowStatic*	pWindowStaticItem;
	SPWindowStatic*	pWindowStaticBG;
	SPWindowStatic*	pWindowStaticBG2;
	SPWindowStatic*	pWindowStatic;
	SPWindowButton*	pWindowButton;
	SPWindowEdit*	pWindowEdit ;
	SPWindowPageSelect* pkPageSelect;

	pWindowStaticFrame	=	new SPWindowStatic( WIID_AUCTION_SALE_FRAME , 12 , 84 , 778 , 410 , this );
	m_pWindowSale = (SPWindow*)pWindowStaticFrame ;

	//////////////////////////////////////////////////////////////////////////
	// ��ǰ ��Ϻ�
	//////////////////////////////////////////////////////////////////////////
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_TITLE , 49 , 9 , 99 , 20 , m_pWindowSale );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 127 , 1 );
	pWindowStatic = NULL ;

	pWindowStaticFrame	=	new SPWindowStatic( WIID_AUCTION_REGI_FRAME , 6 , 29 , 187 , 318 , m_pWindowSale );
	pWindowStaticFrame->SetWindowType(WND_TYPE_NINEBASE) ;
	pWindowStaticFrame->SetImageNine( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 34, 32, 4, 1) ;

	// �Ǹ� ���� ����
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_SALE_TITLE , 1 , 19 , 59 , 13 , pWindowStaticFrame );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 452 , 247 );
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_SALE_TEXT , 74 , 17 , 92 , 16 , pWindowStaticFrame );
	pWindowStatic->SetWindowType(WND_TYPE_LEFTBASE) ;
	pWindowStatic->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 34 , 47, 38, 63);
	pWindowStatic->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 39 , 47, 43, 63);
	pWindowStatic->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 44 , 47, 48, 63);
	pWindowStatic->SetFont(FONT_12_BOLD) ;
	pWindowStatic->SetFontColor(RGBA(143, 99, 99, 255)) ;
	pWindowStatic->SetFormat(DT_VCENTER | DT_CENTER) ;
	pWindowStatic = NULL ;
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_REGI_SALE_LEFT , 60 , 19 , 13 , 13 , pWindowStaticFrame );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 484 , 439 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 484 , 453 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 484 , 467 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 484 , 481 );
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_REGI_SALE_RIGHT , 168 , 19 , 13 , 13 , pWindowStaticFrame );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 498 , 439 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 498 , 453 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 498 , 467 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 498 , 481 );

	// ������ ��� ���
	pWindowStaticBG	=	new SPWindowStatic( WIID_AUCTION_REGI_ITEM_BG , 77 , 49 , 32 , 32 , pWindowStaticFrame );
	pWindowStaticBG->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 1 , 34 );

	// �ƾ���
	pWindowStaticItem	=	new SPWindowStatic( WIID_AUCTION_REGI_ITEM , 0 , 0 , 32 , 32 , pWindowStaticBG );
	pWindowStatic	=	new	SPWindowStatic( WIID_AUCTION_REGI_ITEM_COUNT10 , -2 , 20 , 9 , 10 , pWindowStaticItem );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 0, 0);	// 0
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 9, 0);	// 1
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 18, 0);	// 2
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 27, 0);	// 3
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 36, 0);	// 4
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 45, 0);	// 5
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 54, 0);	// 6
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 63, 0);	// 7
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 72, 0);	// 8
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 81, 0);	// 9
	pWindowStatic	=	new	SPWindowStatic( WIID_AUCTION_REGI_ITEM_COUNT01 , 5 , 20 , 9, 10, pWindowStaticItem );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 0, 0);	// 0
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 9, 0);	// 1
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 18, 0);	// 2
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 27, 0);	// 3
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 36, 0);	// 4
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 45, 0);	// 5
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 54, 0);	// 6
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 63, 0);	// 7
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 72, 0);	// 8
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_num.PNG" , 81, 0);	// 9

	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_ITEM_HELP , 7-77 , 85-49 , 173 , 27 , pWindowStaticItem );
	pWindowStatic->SetWindowType(WND_TYPE_LEFTBASE) ;
	pWindowStatic->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 67 , 23, 71, 50);
	pWindowStatic->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 72 , 23, 76, 50);
	pWindowStatic->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 77 , 23, 81, 50);
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_ITEM_HELP_MSG , 1 , 7 , 169 , 13 , pWindowStatic );
	pWindowStatic->SetFont(FONT_12_NORMAL) ;
	pWindowStatic->SetFontColor(RGBA(143, 99, 99, 255)) ;
	pWindowStatic->SetFormat(DT_TOP | DT_CENTER) ;
	pWindowStatic->SetWindowText("Drag Item Here!!!") ;
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_ITEM_ARROW , 88-77 , 79-49 , 10 , 10 , pWindowStaticItem );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI103.PNG" , 354 , 261 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI103.PNG" , 365 , 261 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI103.PNG" , 376 , 261 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI103.PNG" , 387 , 261 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI103.PNG" , 398 , 261 );
	pWindowStatic = NULL ;
	pWindowStaticItem = NULL ;

	
	// �Ǹ������� Point/Cash/Ely�� ��� ���
	pWindowStaticItem	=	new SPWindowStatic( WIID_AUCTION_REGI_MONEY , 0 , 0 , 32 , 32 , pWindowStaticBG );
	pWindowStaticItem->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 204 , 63 );	// Ely
	pWindowStaticItem->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 171 , 63 );	// Cash
	pWindowStaticItem->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 237 , 63 );	// Point

	pWindowStaticBG	=	new SPWindowStatic( WIID_AUCTION_REGI_MONEY_BG , 18-80 , 85-52 , 130 , 17 , pWindowStaticItem );
	pWindowStaticBG->SetWindowType(WND_TYPE_LEFTBASE) ;
	pWindowStaticBG->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 82 , 23, 86, 40);
	pWindowStaticBG->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 87 , 23, 91, 40);
	pWindowStaticBG->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 92 , 23, 96, 40);
	pWindowEdit		= new SPWindowEdit(WIID_AUCTION_REGI_MONEY_EDIT, 42, 4, 83, 12, pWindowStaticBG) ;
	pWindowEdit->SetFontColor(RGBA(143, 99, 99, 255));
	pWindowEdit->SetEnableTabStop(true);
	pWindowEdit->SetFormat(DT_RIGHT) ;
	pWindowEdit->SetNumber(true) ;
	pWindowEdit->SetLimitText(7) ;			// 9�鸸
	pWindowEdit->Hide() ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_MONEY_ICON , 152-80 , 89-52 , 17 , 11 , pWindowStaticItem );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 157 , 22 );	// Ely
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 193 , 22 );	// Cash
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 211 , 22 );	// Point
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_MONEY_HELP , 1-80 , 106-52 , 185 , 13 , pWindowStaticItem );
	pWindowStatic->SetFont(FONT_12_NORMAL) ;
	pWindowStatic->SetFontColor(RGBA(143, 99, 99, 255)) ;
	pWindowStatic->SetFormat(DT_TOP | DT_CENTER) ;
	pWindowStatic->SetWindowText("Input amount of Money!!!") ;
	pWindowStatic = NULL ;
	pWindowStaticItem = NULL ;

	// ��� ���� �� �ﱸ�� �Է�
	pWindowStaticBG	=	new SPWindowStatic( WIID_AUCTION_REGI_PRICE_FRAME , 7 , 128 , 173 , 150 , pWindowStaticFrame );
	pWindowStaticBG->SetWindowType(WND_TYPE_NINEBASE) ;
	pWindowStaticBG->SetImageNine( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 290, 1, 8, 1) ;

	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_PRICE_ST_TEXT , 2 , 16 , 169 , 13 , pWindowStaticBG );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 1 , 95 );
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_PRICE_ST_BG , 11 , 32 , 130 , 17 , pWindowStaticBG );
	pWindowStatic->SetWindowType(WND_TYPE_LEFTBASE) ;
	pWindowStatic->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 112 , 23, 116, 40);
	pWindowStatic->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 117 , 23, 121, 40);
	pWindowStatic->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 122 , 23, 126, 40);
	pWindowEdit		= new SPWindowEdit(WIID_AUCTION_REGI_PRICE_ST_EDIT, 42, 4, 83, 12, pWindowStatic) ;
	pWindowEdit->SetFontColor(RGBA(0, 0, 0, 255));
	pWindowEdit->SetEnableTabStop(true);
	pWindowEdit->SetFormat(DT_RIGHT) ;
	pWindowEdit->SetNumber(true) ;
	pWindowEdit->SetLimitText(9) ;			// 9��
	pWindowEdit->Hide() ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_PRICE_ST_ICON , 145 , 36 , 17 , 11 , pWindowStaticBG );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 157 , 22 );	// Ely
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 193 , 22 );	// Cash
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 211 , 22 );	// Point
	pWindowStatic = NULL ;

	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_SPOT_ST_TEXT , 2 , 56 , 169 , 13 , pWindowStaticBG );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 1 , 109 );
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_SPOT_ST_BG , 11 , 72 , 130 , 17 , pWindowStaticBG );
	pWindowStatic->SetWindowType(WND_TYPE_LEFTBASE) ;
	pWindowStatic->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 112 , 23, 116, 40);
	pWindowStatic->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 117 , 23, 121, 40);
	pWindowStatic->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 122 , 23, 126, 40);
	pWindowEdit		= new SPWindowEdit(WIID_AUCTION_REGI_SPOT_ST_EDIT, 42, 4, 83, 12, pWindowStatic) ;
	pWindowEdit->SetFontColor(RGBA(0, 0, 0, 255));
	pWindowEdit->SetEnableTabStop(true);
	pWindowEdit->SetFormat(DT_RIGHT) ;
	pWindowEdit->SetNumber(true) ;
	pWindowEdit->SetLimitText(9) ;			// 9��
	pWindowEdit->Hide() ;
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_SPOT_ST_ICON , 145 , 78 , 17 , 11 , pWindowStaticBG );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 157 , 22 );	// Ely
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 193 , 22 );	// Cash
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 211 , 22 );	// Point
	pWindowStatic = NULL ;

	// ��� �Ⱓ
	pWindowStaticBG2	=	new SPWindowStatic( WIID_AUCTION_REGI_DURATION_BG , 3 , 100 , 167 , 47 , pWindowStaticBG );
	pWindowStaticBG2->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 56 , 5 );
	pWindowStaticBG2->SetSrcSize(4, 4) ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_DURATION_TITLE , 8 , 10 , 75 , 15 , pWindowStaticBG2 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 65 , 51 );
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_DURATION_TEXT , 18 , 27 , 41 , 13 , pWindowStaticBG2 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 470 , 107 );
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_DURATION_TEXT+1 , 69 , 27 , 41 , 13 , pWindowStaticBG2 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 470 , 121 );
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_DURATION_TEXT+2 , 120 , 27 , 41 , 13 , pWindowStaticBG2 );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 470 , 135 );
	pWindowStatic = NULL ;
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_REGI_DURATION_BTN + PERIOD_SHORT, 8 , 28 , 10 , 10 , pWindowStaticBG2 );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 440 , 444 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 451 , 444 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 462 , 444 );
	pWindowButton->SetImageCheck	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 462 , 444 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 473 , 444 );
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_REGI_DURATION_BTN + PERIOD_LONG , 59 , 28 , 10 , 10 , pWindowStaticBG2 );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 440 , 444 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 451 , 444 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 462 , 444 );
	pWindowButton->SetImageCheck	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 462 , 444 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 473 , 444 );
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_REGI_DURATION_BTN + PERIOD_EXTREME , 110 , 28 , 10 , 10 , pWindowStaticBG2 );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 440 , 444 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 451 , 444 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 462 , 444 );
	pWindowButton->SetImageCheck	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 462 , 444 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 473 , 444 );

	// ������
	pWindowStaticBG	=	new SPWindowStatic( WIID_AUCTION_REGI_DEPOSIT_BG , 7 , 284 , 173 , 27 , pWindowStaticFrame );
	pWindowStaticBG->SetWindowType(WND_TYPE_NINEBASE) ;
	pWindowStaticBG->SetImageNine( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 142, 23, 4, 1) ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_DEPOSIT_TITLE , 2 , 7 , 68 , 13 , pWindowStaticBG );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 443 , 149 );
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_DEPOSIT_TEXT , 70 , 8 , 72 , 12 , pWindowStaticBG );
	pWindowStatic->SetFont(FONT_12_NORMAL) ;
	pWindowStatic->SetFontColor(RGBA(174, 89, 89, 255)) ;
	pWindowStatic->SetFormat(DT_RIGHT) ;
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_REGI_DEPOSIT_ICON , 146 , 7 , 17 , 11 , pWindowStaticBG );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 157 , 22 );	// Ely
	pWindowStatic = NULL ;

	// ��� & ��� �ʱ�ȭ
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_REGI_OK_BUTTON , 6 , 351 , 92 , 25 , m_pWindowSale );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 358 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 384 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 410 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 436 );
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_REGI_CANCEL_BUTTON , 101 , 351 , 92 , 25 , m_pWindowSale );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 94 , 358 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 94 , 384 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 94 , 410 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 94 , 436 );


	//////////////////////////////////////////////////////////////////////////
	// ��� ��ǰ ����Ʈ
	//////////////////////////////////////////////////////////////////////////
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SALE_LIST_LINE1 , 200 , 11 , 576 , 1 , m_pWindowSale );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 22 , 23 );
	pWindowStatic->SetSrcSize(6, 1) ;
	pWindowStatic = NULL ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SALE_LIST_LINE2 , 199 , 12 , 1 , 368 , m_pWindowSale );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 34 , 24 );
	pWindowStatic->SetSrcSize(1, 6) ;
	pWindowStatic = NULL ;

	// ��� ��� Frame
	pWindowStaticFrame	=	new SPWindowStatic( WIID_AUCTION_SALE_LIST_BG , 200 , 12 , 576 , 368 , m_pWindowSale );
	pWindowStaticFrame->SetImage( "DATA/INTERFACE/CONCEPT/UI_WinBG_000.PNG" , 502 , 472 );
	pWindowStaticFrame->SetSrcSize(4, 4) ;

	// List Title (Quality)
	pWindowButton = new SPWindowButton( WIID_AUCTION_SALE_LIST_QUALITY	, 4 , 4 , 205 , 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 66 , 294);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 66 , 314);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 66 , 334);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SALE_SORT_ARROW + AUCTION_SORT_QUALITY, 190 , 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSaleSort[AUCTION_SORT_QUALITY] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;

	m_pSaleSort[AUCTION_SORT_ITEM_LV] = NULL ;
	m_pSaleSort[AUCTION_SORT_ITEM_OPTPOINT] = NULL ;

	pWindowButton = new SPWindowButton( WIID_AUCTION_SALE_LIST_FINISHTIME	, 213 , 4, 67, 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 372, 85);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 372, 105);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 372, 125);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SALE_SORT_ARROW + AUCTION_SORT_DURATION, 52, 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSaleSort[AUCTION_SORT_DURATION] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SALE_LIST_SELLER , 284 , 4, 112, 19, pWindowStaticFrame );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 221 , 266);
	pWindowStatic = NULL ;
	pWindowButton = new SPWindowButton( WIID_AUCTION_SALE_LIST_PRICE	, 400 , 4 , 172, 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 108 , 206);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 108 , 226);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 108 , 246);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SALE_SORT_ARROW + AUCTION_SORT_PRICE, 157, 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSaleSort[AUCTION_SORT_PRICE] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;

	//////////////////////////////////////////////////////////////////////////
	// Sale List
	for( int i = 0; i < AUCTION_BUY_LIST; i++)
	{
		m_pWindowSaleList[i] = new SPWindowAuctionSaleUNIT( WIID_AUCTION_SALE_LIST + (i * AUCTION_MAX_LIST_ITEM), 0, 28 + i*43, 576, 43, pWindowStaticFrame) ;
		m_pWindowSaleList[i]->SetToolTipStr("Sale List") ;
	}

	//////////////////////////////////////////////////////////////////////////
	// Page Number
	pkPageSelect = new SPWindowPageSelect(WIID_AUCTION_SALE_PAGE, 0, 344, 576, 14, pWindowStaticFrame);

	pkPageSelect->SetPageButtonSize(PAGE_SELECT_BUNDLE_PREV, 14, 14);
	pkPageSelect->SetPageButtonImage		(PAGE_SELECT_BUNDLE_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 454, 455);
	pkPageSelect->SetPageButtonImageHit		(PAGE_SELECT_BUNDLE_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 454, 469);
	pkPageSelect->SetPageButtonImagePush	(PAGE_SELECT_BUNDLE_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 454, 483);
	pkPageSelect->SetPageButtonImageDisable	(PAGE_SELECT_BUNDLE_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 454, 497);

	pkPageSelect->SetPageButtonSize(PAGE_SELECT_PREV, 14, 14);
	pkPageSelect->SetPageButtonImage		(PAGE_SELECT_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 484, 383);
	pkPageSelect->SetPageButtonImageHit		(PAGE_SELECT_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 484, 397);
	pkPageSelect->SetPageButtonImagePush	(PAGE_SELECT_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 484, 411);
	pkPageSelect->SetPageButtonImageDisable	(PAGE_SELECT_PREV, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 484, 425);

	pkPageSelect->SetPageButtonSize(PAGE_SELECT_NEXT, 14, 14);
	pkPageSelect->SetPageButtonImage		(PAGE_SELECT_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 498, 383);
	pkPageSelect->SetPageButtonImageHit		(PAGE_SELECT_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 498, 397);
	pkPageSelect->SetPageButtonImagePush	(PAGE_SELECT_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 498, 411);
	pkPageSelect->SetPageButtonImageDisable	(PAGE_SELECT_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 498, 425);

	pkPageSelect->SetPageButtonSize(PAGE_SELECT_BUNDLE_NEXT, 14, 14);
	pkPageSelect->SetPageButtonImage		(PAGE_SELECT_BUNDLE_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 469, 455);
	pkPageSelect->SetPageButtonImageHit		(PAGE_SELECT_BUNDLE_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 469, 469);
	pkPageSelect->SetPageButtonImagePush	(PAGE_SELECT_BUNDLE_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 469, 483);
	pkPageSelect->SetPageButtonImageDisable	(PAGE_SELECT_BUNDLE_NEXT, "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG", 469, 497);

	pkPageSelect->SetNumberColor(RGBA(69, 94, 112, 255));
	pkPageSelect->SetControlInterval(12);
	pkPageSelect->SetNumberSize(21, 12);

	pkPageSelect->SetMaxPageInfo(1) ;		// ���� ������ ������ ����

	//////////////////////////////////////////////////////////////////////////
	// �ϴ� �޴�
	// [������]
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_SALE_BT_CLOSE , 700 , 386 , 68 , 18 , m_pWindowSale );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 289 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 307 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 325 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 343 );

	// ToolTip Message
	pWindowStaticBG	=	new SPWindowStatic( WIID_AUCTION_SALE_TIP_BG , 15 , 140 , 240 , 50 ,m_pWindowSale );
	pWindowStaticBG->SetWindowType(WND_TYPE_LEFTBASE);
	pWindowStaticBG->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 449 , 43, 469, 93);
	pWindowStaticBG->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 470 , 43, 490, 93);
	pWindowStaticBG->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 491 , 43, 511, 93);
	m_pWindowSaleTip = pWindowStaticBG ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SALE_TIP_MSG , 6 , 10 , 228 , 26 , m_pWindowSaleTip );
	pWindowStatic->SetFont(FONT_12_NORMAL) ;
	pWindowStatic->SetFontColor(RGBA(99, 43, 49, 255)) ;
	//pWindowStatic->SetFormat(DT_LEFT | DT_VCENTER);
	pWindowStatic->SetFormat(DT_LEFT | DT_TOP);
	pWindowStatic->SetMultiLine(true, 2) ;
	pWindowStatic	=	NULL;
	m_pWindowSaleTip->SetShowEnable(false) ;


}


void SPWindowAuction::ShowAuctionSale()
{
	m_pWindowBuy->Hide();
	m_pWindowSearch->Hide();
	HidePopMenu() ;

	m_pWindowSale->Show();

	SetAuctionSaleType(true) ;		// �Ǹ� ������ ���������� �ʱ�ȭ �Ѵ�.
	SetSaleItemInfo() ;				// DragItem �ʱ�ȭ

	OnReceiveAuctionSaleList(0, 0) ;			
}


/**
	Archive�κ��� �������� �ش��ϴ� �����͸� �����ͼ� ����Ʈ�� ����Ѵ�.
	@param int iPage
*/
void SPWindowAuction::ShowSaleList(int iPage)
{
	SPAuctionArchive* pArchive ;
	std::vector<SPAuctionAttr*> vShowList ;
	pArchive = g_pkAuctionManager->GetAuctionSaleArchive() ;

	if( pArchive == NULL )	{
		ErrorFLogs->Error_Log("SPWindowAuction::ShowSaleList Archive is NULL") ;
		return ;
	}

	vShowList.clear() ;
	int iSize = pArchive->GetAuctionListPage(vShowList, iPage) ;
	if( iSize == 0 )	{
		ErrorFLogs->Error_Log("SPWindowAuction::OnReceiveAuctionSaleList has No data!!!") ;
	}
	ErrorFLogs->Error_Log("SPWindowAuction::OnReceiveAuctionSaleList Show[%d], Page[%d]", iSize, iPage) ;
	for( int i = 0; i < AUCTION_SALE_LIST; i++ )
	{
		if( i < iSize )
		{
			m_pWindowSaleList[i]->SetAuctionItem(vShowList[i]) ;
			m_pWindowSaleList[i]->SetShowEnable(true) ;
		}
		else
		{
			m_pWindowSaleList[i]->ClearAuctionInfo() ;
			m_pWindowSaleList[i]->SetShowEnable(false) ;
		}
	}
}




/**
	���� �ð����� Arrow Icon�� �����Ѵ�.
*/
void SPWindowAuction::SetSaleArrowIcon(int iIndex)
{
	SPWindowStatic* pWindowStatic	=	(SPWindowStatic*)Find( WIID_AUCTION_REGI_ITEM_ARROW, true);
	if( pWindowStatic )
		pWindowStatic->SPSendMessage(SPIM_SET_IMAGEINDEX, iIndex) ;
}




/**
	�Ǹ� Ÿ�Ժ� ȭ�� �������� �����Ѵ�.
	���۰�, �ﱸ��, �Ⱓ �ʱ�ȭ
	@param bool bInit	: �ʱ�ȭ ���� ���� (������ ������ �ڵ� �ʱ�ȭ)
*/
void SPWindowAuction::SetAuctionSaleType(bool bDefault/*= false*/)
{
	SPWindowStatic* pStatic = NULL ;
	SPWindowEdit*	pEdit = NULL ;
	bool			bShowItem = false ;

	if( m_pSaleTypeInfo == NULL || bDefault == true )
	{
		m_iSaleType = AUCTION_TYPE_ITEM_BY_ELY ;
		m_iSaleIndex = 1 ;
		AUCTION_TYPE_INFO* pAuctionTypeInfo = g_pkAuctionManager->GetAuctionTypeInfo(m_iSaleType) ;
		if( pAuctionTypeInfo == NULL )
			return ;
		m_pSaleTypeInfo = pAuctionTypeInfo ;
	}

	if( m_pSaleTypeInfo == NULL )
	{
		ErrorFLogs->Error_Log("Can't Find AuctionInfo in SetAuctionSaleType!!") ;
		return ;
	}

	InitBidMoney() ;						// ���� �� �ﱸ�� �ʱ�ȭ
	m_iSaleDuration = PERIOD_SHORT ;		// ��űⰣ �ʱ�ȭ
	SetSaleDuration(m_iSaleDuration) ;
	UpdateEnrolFee(true) ;					// ������ �ʱ�ȭ

	if( m_pSaleTypeInfo->iSaleType == AUCTION_TYPE_ITEM_BY_ELY)	{
		m_pSaleTimer->Start(1, 0.1f) ;				// Arrow Icon Start
		bShowItem = true ;
	}
	else	{
		SetSaleItemInfo() ;		// �ٸ������� ���� Drag Item ���� �ʱ�ȭ
		bShowItem = false ;
	}

	// ������ �Է��� ���
	pStatic = (SPWindowStatic*)Find(WIID_AUCTION_REGI_ITEM, true) ;
	if( pStatic )	{
		pStatic->SPSendMessage(SPIM_SET_IMAGECLEAR) ;		// ������ ���� clear
		bShowItem ? pStatic->Show() : pStatic->Hide() ;		// ���̱� ����
	}

	// Money�Է��� ���
	pStatic = (SPWindowStatic*)Find(WIID_AUCTION_REGI_MONEY, true) ;
	if( pStatic )	bShowItem ? pStatic->Hide() : pStatic->Show() ;

	// ������ ����
	SetAuctionSaleTypeIcon(m_pSaleTypeInfo->iSaleType) ;
	InitTabStop() ;
}


/**
	ī�װ� TEXT ����
	ī�װ� BIG Icon ����
	���� ����
	���� Icon ����
	AUCTION_TYPE_ITEM_BY_ELY,	// �Ǹ� : ������,	���ż��� : Ely		--> CLEAR, Ely
	AUCTION_TYPE_ELY_BY_CASH,	// �Ǹ� : Ely,		���ż��� : Cash		--> ELY, Cash
	AUCTION_TYPE_CASH_BY_ELY,	// �Ǹ� : Cash,		���ż��� : Ely		-->	
	AUCTION_TYPE_ELY_BY_MILEAGE,// �Ǹ� : Ely,		���ż��� : Mileage	-->
	AUCTION_TYPE_MILEAGE_BY_ELY,// �Ǹ� : Mileage,	���ż��� : Ely		-->
*/
void SPWindowAuction::SetAuctionSaleTypeIcon(AUCTION_TYPE eType)
{
	int iMoneyIconIndex = 0 ;
	int iSaleIconIndex = 0 ;
	int iElyDigitSize = 0 ;
	int iCashDigitSize = 0 ;
	int iMiliDigitSize = 0 ;
	bool bShowTip = false ;
	SPWindowStatic* pStaticItem = NULL ;
	SPWindowStatic* pStaticText = NULL ;
	SPWindowStatic* pStaticHelp = NULL ;
	SPWindowEdit* pEditSale = NULL ;		// �Ǹűݾ�
	SPWindowEdit* pEditStart = NULL ;		// ���۰�
	SPWindowEdit* pEditSpot = NULL ;		// �ﱸ��
	TCHAR szRegMesg[256] ;

	pStaticText = (SPWindowStatic*)Find(WIID_AUCTION_REGI_SALE_TEXT, true) ;		// ī�װ� Text
	pStaticHelp = (eType == AUCTION_TYPE_ITEM_BY_ELY) ? 
							(SPWindowStatic*)Find(WIID_AUCTION_REGI_ITEM_HELP_MSG, true) :	// ������ ����
							(SPWindowStatic*)Find(WIID_AUCTION_REGI_MONEY_HELP, true) ;		// �Ӵ� ����
	pEditSale	= (SPWindowEdit*)Find(WIID_AUCTION_REGI_MONEY_EDIT, true) ;
	pEditStart	= (SPWindowEdit*)Find(WIID_AUCTION_REGI_PRICE_ST_EDIT, true) ;
	pEditSpot	= (SPWindowEdit*)Find(WIID_AUCTION_REGI_SPOT_ST_EDIT, true) ;
	iElyDigitSize = g_pCheckManager->CheckDigitSize((INT64)AUCTION_ELY_MAX) ;
	iCashDigitSize = g_pCheckManager->CheckDigitSize((INT64)AUCTION_CASH_MAX) ;
	iMiliDigitSize = g_pCheckManager->CheckDigitSize((INT64)AUCTION_MILE_MAX) ;

	std::string strMsg = g_pResourceManager->GetGlobalString(52000060) ;

	if( g_pkAuctionManager->GetAuctionFeeRate() > 0 )
		_stprintf( szRegMesg, g_pResourceManager->GetGlobalString(52000060), g_pkAuctionManager->GetAuctionFeeRate()) ;
	else
		_stprintf( szRegMesg, g_pResourceManager->GetGlobalString(52000055)) ;

	// pStaticItem->SPSendMessage(SPIM_SET_IMAGECLEAR);
	if( eType == AUCTION_TYPE_ITEM_BY_ELY )	{
		if( pStaticText )	pStaticText->SetWindowText(g_pResourceManager->GetGlobalString(52000049)) ;	// [������]ī�װ�
		if( pStaticHelp )	pStaticHelp->SetWindowText(g_pResourceManager->GetGlobalString(52000054)) ;
		pEditStart->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		pEditSpot->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		iSaleIconIndex = -1 ;	// ITEM�� -1
		iMoneyIconIndex = 0 ;	// Ely
	}
	else if( eType == AUCTION_TYPE_ELY_BY_CASH )	{
		if( pStaticText )	pStaticText->SetWindowText(g_pResourceManager->GetGlobalString(52000052)) ;	// [ELY]ī�װ�
		if( pStaticHelp )	pStaticHelp->SetWindowText(g_pResourceManager->GetGlobalString(52000055)) ;
		pEditSale->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		pEditStart->SetLimitText(iCashDigitSize) ;		// 9�鸸���� �Է�
		pEditSpot->SetLimitText(iCashDigitSize) ;		// 9�鸸���� �Է�
		iSaleIconIndex = 0 ;	// Ely
		iMoneyIconIndex = 1 ;	// Cash
		bShowTip = true ;
	}
	else if( eType == AUCTION_TYPE_CASH_BY_ELY )	{
		if( pStaticText )	pStaticText->SetWindowText(g_pResourceManager->GetGlobalString(52000050)) ;	// [CASH]ī�װ�
		if( pStaticHelp )	pStaticHelp->SetWindowText(szRegMesg) ;
		pEditSale->SetLimitText(iCashDigitSize) ;		// 9�鸸���� �Է�
		pEditStart->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		pEditSpot->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		iSaleIconIndex = 1 ;	// Cash
		iMoneyIconIndex = 0 ;	// Ely
	}
	else if( eType == AUCTION_TYPE_ELY_BY_MILEAGE )	{
		if( pStaticText )	pStaticText->SetWindowText(g_pResourceManager->GetGlobalString(52000052)) ;	// [ELY]ī�װ�
		if( pStaticHelp )	pStaticHelp->SetWindowText(g_pResourceManager->GetGlobalString(52000055)) ;
		pEditSale->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		pEditStart->SetLimitText(iMiliDigitSize) ;		// 9�鸸���� �Է�
		pEditSpot->SetLimitText(iMiliDigitSize) ;		// 9�鸸���� �Է�
		iSaleIconIndex = 0 ;	// Ely
		iMoneyIconIndex = 2 ;	// Point
		bShowTip = true ;
	}
	else if( eType == AUCTION_TYPE_MILEAGE_BY_ELY )	{
		if( pStaticText )	pStaticText->SetWindowText(g_pResourceManager->GetGlobalString(52000051)) ;	// [Point]ī�װ�
		if( pStaticHelp )	pStaticHelp->SetWindowText(szRegMesg) ;
		pEditSale->SetLimitText(iMiliDigitSize) ;		// 9�鸸���� �Է�
		pEditStart->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		pEditSpot->SetLimitText(iElyDigitSize) ;		// 9����� �Է�
		iSaleIconIndex = 2 ;	// Point 
		iMoneyIconIndex = 0 ;	// Ely
	}
	else	{
		ErrorFLogs->Error_Log("SetAuctionSaleTypeIcon ERROR [%d]", eType) ;
		return ;
	}

	if( iSaleIconIndex >= 0 )	{
		pStaticItem = (SPWindowStatic*)Find(WIID_AUCTION_REGI_MONEY, true) ;		// �Ӵ��ΰ�� ū ������ ����
		if( pStaticItem )	{
			pStaticItem->SPSendMessage(SPIM_SET_IMAGEINDEX, iSaleIconIndex) ;
			pStaticItem->Show() ;
		}
		pStaticItem = (SPWindowStatic*)Find(WIID_AUCTION_REGI_MONEY_ICON, true) ;	// �Ǹ� ������ ���� ������
		if( pStaticItem )	pStaticItem->SPSendMessage(SPIM_SET_IMAGEINDEX, iSaleIconIndex) ;
		SetSaleItemCount(0) ;
	}
	pStaticItem = NULL ;
	pStaticItem = (SPWindowStatic*)Find(WIID_AUCTION_REGI_PRICE_ST_ICON, true) ;	// ��� ���۰�
	if( pStaticItem)	
		pStaticItem->SPSendMessage(SPIM_SET_IMAGEINDEX, iMoneyIconIndex) ;
	pStaticItem = NULL ;
	pStaticItem = (SPWindowStatic*)Find(WIID_AUCTION_REGI_SPOT_ST_ICON, true) ;		// ��� �ﱸ��
	if( pStaticItem)	
		pStaticItem->SPSendMessage(SPIM_SET_IMAGEINDEX, iMoneyIconIndex) ;
	pStaticItem = NULL ;

	// Show Tooltip
	if( bShowTip )	{
		m_pWindowSaleTip->SetShowEnable(true) ;
		_stprintf( szRegMesg, g_pResourceManager->GetGlobalString(52000059), g_pkAuctionManager->GetAuctionFeeRate() ) ;
		pStaticHelp = (SPWindowStatic*)Find(WIID_AUCTION_SALE_TIP_MSG, true) ;
		if( pStaticHelp )	
			pStaticHelp->SetWindowText(szRegMesg) ;	// Tip Message
		m_pWindowSaleTip->Show() ;
		m_pSaleTipTimer->Start(1, 3.0f) ;
	}

}



/**
	Ÿ�Կ� ���� �������� �Դ��� ���θ� Ȯ���� �ش�.
	@return ������:SPItem* , ������ NULLL
*/
SPItem* SPWindowAuction::GetDragItem()
{
	SPPlayerInvenArchive* pInven = NULL;
	if(g_pGOBManager->GetLocalPlayer())
		pInven = g_pGOBManager->GetLocalPlayer()->GetInvenArchive();
	else 
		return NULL;

	//�Ⱦ� ���°� �ƴѰ�� �Ѿ��
	if(pInven->m_bPickup == false) {
		return NULL;
	}	

	SPSelectItem SelectItem = pInven->GetPickupItem();
	SPItem* pItem = pInven->GetInventoryItem(SelectItem.m_iContainer, SelectItem.m_iSlotIndex);	

	return pItem ;
}




/**
	��� �Ⱓ ����
	#define WIID_AUCTION_REGI_DURATION_SHORT	(WIID_AUCTION + 636)
	#define WIID_AUCTION_REGI_DURATION_MIDDLE	(WIID_AUCTION + 637)
	#define WIID_AUCTION_REGI_DURATION_LONG		(WIID_AUCTION + 638)
	WIID_AUCTION_REGI_DURATION_BTN
	PERIOD_SHORT,		// �ܱ�		(12)
	PERIOD_LONG,		// ���		(24)
	PERIOD_EXTREME,		// �����	(48)
*/
void SPWindowAuction::SetSaleDuration(int iDuration/*= 0*/)
{
	if( m_iSaleDuration )
		m_iSaleDuration = (AUCTION_DURATION)iDuration ;

	SPWindowButton* pButton ;
	pButton = (SPWindowButton*)Find(WIID_AUCTION_REGI_DURATION_BTN+PERIOD_SHORT, true) ;
	if( pButton )	pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)FALSE);
	pButton = (SPWindowButton*)Find(WIID_AUCTION_REGI_DURATION_BTN+PERIOD_LONG, true) ;
	if( pButton )	pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)FALSE);
	pButton = (SPWindowButton*)Find(WIID_AUCTION_REGI_DURATION_BTN+PERIOD_EXTREME, true) ;
	if( pButton )	pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)FALSE);

	pButton = (SPWindowButton*)Find(WIID_AUCTION_REGI_DURATION_BTN+m_iSaleDuration, true) ;
	if( pButton )	pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)TRUE);
}



/**
	Set Drag Item Info
	@param SPItem* pkItem	: If NULL then Clear Item Info
*/
bool SPWindowAuction::SetSaleItemInfo( SPItem* pkItem/*= NULL*/)
{
	POINT		pItemIcon ;
	SPTexture*	pTexture = NULL ;
	SPWindowStatic* pStaticItem = NULL ;
	SPWindowStatic* pStaticHelp = NULL ;
	SPWindow* pStartMoney = NULL ;
	D3DXCOLOR cItemColor ;

	pStaticItem = (SPWindowStatic*)Find(WIID_AUCTION_REGI_ITEM, true) ;
	pStaticHelp = (SPWindowStatic*)Find(WIID_AUCTION_REGI_ITEM_HELP_MSG, true) ;
	pStartMoney = Find(WIID_AUCTION_REGI_PRICE_ST_EDIT, true) ;

	if( pkItem == NULL )		// Clear Item Info
	{
		if( pStaticItem )	pStaticItem->SPSendMessage(SPIM_SET_IMAGECLEAR) ;
		if( pStaticHelp )	{
			pStaticHelp->SetWindowText(g_pResourceManager->GetGlobalString(52000054)) ;		// ������ ��ϸ޽���
			pStaticHelp->SetFontColor( RGBA(0, 0, 0, 255) ) ;
		}
		// ���۰� �� ������ �ʱ�ȭ �߰�
		SetSaleItemCount(0) ;
		m_pSaleItem = NULL ;
		UpdateEnrolFee(true) ;
		if( pStartMoney )
			pStartMoney->SetWindowText("0") ;
		SetAcutionItemAllUnlock() ;
	}
	else
	{
		m_pSaleItem = pkItem ;

		// ������ �⺻ �ǸŰ� ����
		int iStartMoney = 0 ;
		int iGamePrice = m_pSaleItem->GetItemAttr()->m_iGamePrice ;
		int iSysStartMoney = g_pkAuctionManager->GetSysStartMoneyID() ;
		int iStackCount = m_pSaleItem->GetItemStatus()->GetStackCount() ;

		iStartMoney = (int)( GET_AUCTION_STARTMONEY(iGamePrice , iSysStartMoney, iStackCount ) );
		if( iStartMoney > 0 && iStartMoney < AUCTION_ELY_MAX )	{
			char szBuf[16] = {0} ;
			sprintf(szBuf, "%d", iStartMoney) ;
			if( pStartMoney )
				pStartMoney->SetWindowText(szBuf) ;
		}
		else	{		// �ǸŰ� ����� �߸��� -> �޽��� ���
			if( g_pResourceManager->GetGlobalString(52000110) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000110) );
			SetAcutionItemAllUnlock() ;
			m_pSaleItem = NULL ;
			return false ;
		}

		// �ǸŰ��� ������ �������� ��쿡�� ������ ���� ����
		// ������ ���� ����
		SetSaleItemCount(iStackCount) ;
		pTexture = g_pItemCluster->GetItemTexture(pkItem->GetItemStatus()->GetItemID(), pItemIcon) ;
		if( pTexture != NULL && pStaticItem )	{
			pStaticItem->SPSendMessage(SPIM_SET_IMAGECLEAR) ;
			pStaticItem->SetImage( pTexture, pItemIcon.x, pItemIcon.y ) ;
		}
		// ������ �� ����
		if( pStaticHelp )	{
			if( pkItem->GetItemAttr()->m_bNameColor == true )
				cItemColor	=	pkItem->GetItemAttr()->GetNameColor();
			else
				cItemColor	=	g_pCheckManager->GetItemColor( pkItem->GetItemStatus()->GetRareLevel() );
			pStaticHelp->SetFontColor( cItemColor ) ;
			pStaticHelp->SetWindowText(pkItem->GetItemStatus()->GetItemAttr()->m_strName.c_str() ) ;
		}
		UpdateEnrolFee() ;
	}
	return true ;
}


/**
	Item�� StackCount�� ����Ѵ�.
*/
void SPWindowAuction::SetSaleItemCount(int iCount)
{
	SPWindow* pWindow10 = NULL ;
	SPWindow* pWindow01 = NULL ;
	int iTen = iCount / 10 ;
	int iOne = iCount % 10 ;
	pWindow10 = Find( WIID_AUCTION_REGI_ITEM_COUNT10, true ) ;
	pWindow01 = Find( WIID_AUCTION_REGI_ITEM_COUNT01, true ) ;

	if( iCount > 1 )	
	{
		if( iTen > 0 )	{
			pWindow10->SPSendMessage(SPIM_SET_IMAGEINDEX, iTen) ;	
			pWindow01->SPSendMessage(SPIM_SET_IMAGEINDEX, iOne) ;	
			pWindow10->SetShowEnable(true) ;
			pWindow01->SetShowEnable(true) ;
		}
		else	{	// 10������ ������ 1������ ������
			pWindow10->SPSendMessage(SPIM_SET_IMAGEINDEX, iOne) ;	
			pWindow10->SetShowEnable(true) ;
			pWindow01->SetShowEnable(false) ;
		}
	}
	else	
	{
		pWindow10->SetShowEnable(false) ;
		pWindow01->SetShowEnable(false) ;
	}
}




/**
	Drag �� ���� �κ������� ������ ���
*/
void SPWindowAuction::SetAcutionItemAllUnlock()
{
	if( g_pGOBManager == NULL || g_pGOBManager->GetLocalPlayer() == NULL )
		return;

	SPPlayerInvenArchive* pkInven = g_pGOBManager->GetLocalPlayer()->GetInvenArchive();
	if( pkInven )
		pkInven->ClearAllBlockItem();
}

void SPWindowAuction::SetAuctionItemLock( SPItem* pkItem , int iIndex )
{
	if( g_pGOBManager == NULL || g_pGOBManager->GetLocalPlayer() == NULL )
		return;

	if( pkItem == NULL )
		return;

	SPPlayerInvenArchive* pkInven = g_pGOBManager->GetLocalPlayer()->GetInvenArchive();
	if( pkInven )
		pkInven->SetBlockItem(iIndex, pkItem->GetContainerType(), pkItem->GetSlotIndex());
}



/**
	��� ���۰� �� �ﱸ�� �ʱ�ȭ
*/
void SPWindowAuction::InitBidMoney()
{
	SPWindowEdit* pEdit ;

	m_iSaleMoney = 0 ;
	m_iSaleStartMoney = 0 ;
	m_iSaleSpotMoney = 0 ;

	pEdit = (SPWindowEdit*)Find(WIID_AUCTION_REGI_MONEY_EDIT, true) ;		// �Ӵ��Է�
	if( pEdit )		pEdit->SetWindowText("0") ;
	pEdit = (SPWindowEdit*)Find(WIID_AUCTION_REGI_PRICE_ST_EDIT, true) ;	// ���۰�
	if( pEdit )		pEdit->SetWindowText("0") ;
	pEdit = (SPWindowEdit*)Find(WIID_AUCTION_REGI_SPOT_ST_EDIT, true) ;		// �ﱸ��
	if( pEdit )		pEdit->SetWindowText("0") ;
}


/**
	��� ��� ������ ������Ʈ
	@param bool bInit : �ʱ�ȭ ����
*/
void SPWindowAuction::UpdateEnrolFee(bool bInit /*=false*/)
{

	SPWindowEdit* pEdit = NULL ;
	SPWindowStatic* pStatic = NULL ;

	m_iEnrolFee = 0 ;
	if( !bInit )
	{
		pEdit = (SPWindowEdit*)Find(WIID_AUCTION_REGI_MONEY_EDIT, true) ;		// �Ǹ� �ݾ�
		if( pEdit )		{
			m_iSaleMoney = atoi(pEdit->GetWindowText()) ;
		}
		pEdit = (SPWindowEdit*)Find(WIID_AUCTION_REGI_PRICE_ST_EDIT, true) ;	// ���۰�
		if( pEdit )		{
			m_iSaleStartMoney = _atoi64(pEdit->GetWindowText()) ;
		}
		pEdit = (SPWindowEdit*)Find(WIID_AUCTION_REGI_SPOT_ST_EDIT, true) ;		// �ﱸ��
		if( pEdit )		{
			m_iSaleSpotMoney = _atoi64(pEdit->GetWindowText()) ;
		}

		// ��ǰ Ÿ�Ժ� ������ ���
		if( m_iSaleType == AUCTION_TYPE_ITEM_BY_ELY )
		{
			if( m_pSaleItem != NULL )	{
				int iItemLv = m_pSaleItem->GetItemAttr()->m_iItemLevel ;
				int iItemPrice = m_pSaleItem->GetItemAttr()->m_iGamePrice ;
				int iItemCount = m_pSaleItem->GetItemStatusValue(MV_ITEM_GETSTACK_CNT);	
				m_iEnrolFee = g_pkAuctionManager->ComputeEnrolFee(m_iSaleType, m_iSaleStartMoney, m_iSaleDuration, 0, iItemLv, iItemPrice, iItemCount) ;
			}
		}
		else
		{
			if( m_iSaleMoney != 0 )	{
				m_iEnrolFee = g_pkAuctionManager->ComputeEnrolFee(m_iSaleType, m_iSaleStartMoney, m_iSaleDuration, m_iSaleMoney) ;
			}
		}
	}

	pStatic = (SPWindowStatic*)Find(WIID_AUCTION_REGI_DEPOSIT_TEXT, true) ;		// ������
	if( pStatic )		{
		//ErrorFLogs->Error_Log("Update EnrolFee [%d]", m_iEnrolFee) ;
		pStatic->SetWindowText( ConvertMoneyToString(m_iEnrolFee) ) ;
	}
}



/**
	������ ��Ͻ� �ʿ��� üũ�� �Ѵ�.
 */
bool SPWindowAuction::CheckCreateItem(AUCTION_TYPE_INFO* pAuctionTypeInfo)
{
	// ��Ÿ�Ժ� üũ ============================================================= ��
	// �������� ������ [52000021]
	if( m_iSaleType == AUCTION_TYPE_ITEM_BY_ELY && m_pSaleItem == NULL )	{
		if( g_pResourceManager->GetGlobalString(52000021) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000021) );
		return false ;
	}
	else if( m_iSaleType == AUCTION_TYPE_CASH_BY_ELY )	{
		// �Ǹ� �ݾ��� ���� �ݾ׺��� ������ [52000001, 52000002, 52000053]
		if( g_pkAuctionManager->GetPlayerCash() < m_iSaleMoney )	{
			if( g_pResourceManager->GetGlobalString(52000002) )		// Cash����
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000002) );
			return false ;
		}
		// ����, �ﱸ���� �ʹ� ū��� [52000071, 52000072]
		if( m_iSaleStartMoney > AUCTION_CASH_MAX ) {
			if( g_pResourceManager->GetGlobalString(52000071) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000071) );
			return false ;
		}
		if( m_iSaleSpotMoney > AUCTION_CASH_MAX ) {
			if( g_pResourceManager->GetGlobalString(52000072) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000072) );
			return false ;
		}
		// ��� �ִ� �ݾ� �ʰ��� [52000070]
		if( m_iSaleMoney > AUCTION_CASH_MAX )	{
			if( g_pResourceManager->GetGlobalString(52000070) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000070) );
			return false ;
		}
	}
	else if( m_iSaleType == AUCTION_TYPE_MILEAGE_BY_ELY )	{
		// �Ǹ� �ݾ��� ���� �ݾ׺��� ������ [52000001, 52000002, 52000053]
		if( g_pkAuctionManager->GetPlayerMilige() < m_iSaleMoney )	{
			if( g_pResourceManager->GetGlobalString(52000053) )		// Point����
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000053) );
			return false ;
		}
		// ����, �ﱸ���� �ʹ� ū��� [52000071, 52000072]
		if( m_iSaleStartMoney > AUCTION_MILE_MAX ) {
			if( g_pResourceManager->GetGlobalString(52000071) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000071) );
			return false ;
		}
		if( m_iSaleSpotMoney > AUCTION_MILE_MAX ) {
			if( g_pResourceManager->GetGlobalString(52000072) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000072) );
			return false ;
		}
		// ��� �ִ� �ݾ� �ʰ��� [52000070]
		if( m_iSaleMoney > AUCTION_MILE_MAX )	{
			if( g_pResourceManager->GetGlobalString(52000070) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000070) );
			return false ;
		}
	}
	else if( m_iSaleType == AUCTION_TYPE_ELY_BY_CASH || m_iSaleType == AUCTION_TYPE_ELY_BY_MILEAGE )	{
		// �Ǹ� �ݾ��� ���� �ݾ׺��� ������ [52000001, 52000002, 52000053]
		if( g_pkAuctionManager->GetPlayerEly() < (INT64)m_iSaleMoney )	{
			if( g_pResourceManager->GetGlobalString(52000001) )		// Ely ����
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000001) );
			return false ;
		}
		// ����, �ﱸ���� �ʹ� ū��� [52000071, 52000072]
		if( m_iSaleStartMoney > AUCTION_ELY_MAX ) {
			if( g_pResourceManager->GetGlobalString(52000071) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000071) );
			return false ;
		}
		if( m_iSaleSpotMoney > AUCTION_ELY_MAX ) {
			if( g_pResourceManager->GetGlobalString(52000072) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000072) );
			return false ;
		}
		// ��� �ִ� �ݾ� �ʰ��� [52000070]
		if( m_iSaleMoney > AUCTION_ELY_MAX )	{
			if( g_pResourceManager->GetGlobalString(52000070) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000070) );
			return false ;
		}
	}
	// ��Ÿ�Ժ� üũ ============================================================= ��

	// ĳ�� �ּҵ�� �ݾ� [52000017]
	// ����Ʈ �ּҵ�� �ݾ� [52000018]
	// Ely �ּҵ�� �ݾ� [52000019]
	if( m_iSaleType != AUCTION_TYPE_ITEM_BY_ELY && m_iSaleMoney < AUCTION_UPPOINT_MIN )	{
		if( m_iSaleType == AUCTION_TYPE_CASH_BY_ELY )	{
			if( g_pResourceManager->GetGlobalString(52000017) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000017) );
			return false ;
		}
		else if( m_iSaleType == AUCTION_TYPE_MILEAGE_BY_ELY )	{
			if( g_pResourceManager->GetGlobalString(52000018) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000018) );
			return false ;
		}
		else	{
			if( g_pResourceManager->GetGlobalString(52000019) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000019) );
			return false ;
		}
	}

	// ���۰��� ������ [52000081~52000083]
	if( m_iSaleStartMoney < AUCTION_PRICE_MIN )	
	{
		if( m_iSaleType == AUCTION_TYPE_ELY_BY_CASH )	{
			if( g_pResourceManager->GetGlobalString(52000081) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000081) );
			return false ;
		}
		else if( m_iSaleType == AUCTION_TYPE_ELY_BY_MILEAGE )	{
			if( g_pResourceManager->GetGlobalString(52000082) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000082) );
			return false ;
		}
		else	{
			if( g_pResourceManager->GetGlobalString(52000083) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000083) );
			return false ;
		}
	}

	// ���۰� > �ﱸ�� �ΰ�� [52000013]
	if( m_iSaleSpotMoney > 0 && m_iSaleStartMoney > m_iSaleSpotMoney )	{
		if( g_pResourceManager->GetGlobalString(52000013) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000013) );
		return false ;
	}

	// ��� �������� ���� ��� [52000014]
	if( pAuctionTypeInfo->bRegistCharge )	{
		if( m_iSaleType == AUCTION_TYPE_ELY_BY_CASH || AUCTION_TYPE_ELY_BY_MILEAGE )	{
			// ��ϱݾ� + ������ üũ
			if( g_pkAuctionManager->GetPlayerEly() < m_iEnrolFee+m_iSaleMoney )	{
				if( g_pResourceManager->GetGlobalString(52000014) )
					g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000014) );
				return false ;
			}
		}
		else	{
			// �����ݸ� üũ
			if( g_pkAuctionManager->GetPlayerEly() < m_iEnrolFee )	{
				if( g_pResourceManager->GetGlobalString(52000014) )
					g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000014) );
				return false ;
			}
		}
	}

	// ��Ͽ� �ʿ��� �������� ���°�� [52000015]
	if( pAuctionTypeInfo->iConsumeItem > 0 )	{
		if( false == g_pCheckManager->CheckCondition( REQUIRE_TYPE_ITEM , 1 , pAuctionTypeInfo->iConsumeItem , 1 ) )	{
			if( g_pResourceManager->GetGlobalString(52000015) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000015) );
			return false ;
		}
	}
	return true ;
}


/**
	�ǸŵǴ� �������� �����ϴ� ��
	Drag�� ���ؼ� ��� ���� (Default)
	Shift+Click�� ���ؼ� ��� ���� (Must set parameter)
 */
bool SPWindowAuction::CheckSaleItem(bool bDrag/*=true*/ , SPItem* pClickItem/*=NULL*/ )
{
	SPItem* pSaleItem = NULL ;
	AUCTION_TYPE_INFO* pAuctionTypeInfo = g_pkAuctionManager->GetAuctionTypeInfo(m_iSaleType) ;
	if( pAuctionTypeInfo == NULL )
		return false ;
	SetSaleItemInfo() ;					// ���� ���� Clear

	if( bDrag )	{
		pSaleItem = GetDragItem() ;		// Drag�� �������� �ִ��� Ȯ���Ѵ�.
	}
	else	{
		pSaleItem = pClickItem ;
	}

	// �������� �ִ���
	if(pSaleItem == NULL || pSaleItem->GetItemStatus() == NULL || pSaleItem->GetItemStatus()->GetItemID() == 0) {
		return false;
	}

	//����ǿ��� ���� ���
	if( pSaleItem->GetContainerType() >= INVENTORY_HOUSING ) {
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);		
		return false;
	}

	if( m_iSaleType != AUCTION_TYPE_ITEM_BY_ELY )
		return false ;

	// ������ ��ȿ�� üũ
	if( pSaleItem->GetItemStatus()->IsTimeAvailable() == false )
	{
		// ��� ������ �Ⱓ ���� [52000022] => ��� �Ұ� ���������� ǥ�� ó��
		if( g_pResourceManager->GetGlobalString(52000022) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000022) );
		return false;
	}

	// ��϶� �Һ�Ǵ� �������� ����� �� ����.
	// ��� �Ұ� ������ [52000022]
	if( m_iSaleType == AUCTION_TYPE_ITEM_BY_ELY && (pSaleItem->GetItemStatus()->GetItemID() == pAuctionTypeInfo->iConsumeItem) )	{
		if( g_pResourceManager->GetGlobalString(52000022) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000022) );
		return 0 ;
	}

	// ��� ó��
	if( pSaleItem->GetItemStatus()->GetItemAttr()->m_bTrade )	{
		if( SetSaleItemInfo( pSaleItem ) == false )
			return false ;
		SetAuctionItemLock( pSaleItem , 0 );
		return true ;
	}
	else		{
		// ��� �Ұ� ������ [52000022]
		if( g_pResourceManager->GetGlobalString(52000022) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000022) );
		return false ;
	}
	return true ;
}




//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
/**
	�Ǹ����� ���� (������/ĳ��/����Ʈ/����) : �ִ� 4����
*/
int SPWindowAuction::OnSaleRegistryLeft(WPARAM wParam, LPARAM lParam)
{
	AUCTION_TYPE eChangeType ;
	int iLeft = m_iSaleIndex - 1 ;
	if( iLeft > 0 )
	{
		m_iSaleIndex = iLeft ;
		eChangeType = (AUCTION_TYPE)g_pkAuctionManager->GetAuctionTypeID(m_iSaleIndex) ;
		if( eChangeType == AUCTION_TYPE_NULL )
			return 0 ;

		AUCTION_TYPE_INFO* pAuctionTypeInfo = NULL ;
		pAuctionTypeInfo = g_pkAuctionManager->GetAuctionTypeInfo(eChangeType) ;
		if( pAuctionTypeInfo == NULL )	{
			ErrorFLogs->Error_Log("LEFT::Can't Find AuctionTypeInfo [%d]", iLeft) ;
			return 0 ;
		}
		m_iSaleType = eChangeType ;
		m_pSaleTypeInfo = pAuctionTypeInfo ;
		SetAuctionSaleType() ; 
	}
	return 0 ;
}
/**
	�Ǹ����� ���� (������/ĳ��/����Ʈ/����) : �ִ� 4����
*/
int SPWindowAuction::OnSaleRegistryRight(WPARAM wParam, LPARAM lParam)
{
	AUCTION_TYPE eChangeType ;
	int iRight = m_iSaleIndex + 1 ;
	if( iRight <= g_pkAuctionManager->GetAuctionTypeCount() )
	{
		m_iSaleIndex = iRight ;
		eChangeType = (AUCTION_TYPE)g_pkAuctionManager->GetAuctionTypeID(m_iSaleIndex) ;
		if( eChangeType == AUCTION_TYPE_NULL )
			return 0 ;

		AUCTION_TYPE_INFO* pAuctionTypeInfo = NULL ;
		pAuctionTypeInfo = g_pkAuctionManager->GetAuctionTypeInfo(eChangeType) ;
		if( pAuctionTypeInfo == NULL )	{
			ErrorFLogs->Error_Log("RIGHT::Can't Find AuctionTypeInfo [%d]", iRight) ;
			return 0 ;
		}
		m_iSaleType = eChangeType ;
		m_pSaleTypeInfo = pAuctionTypeInfo ;
		SetAuctionSaleType() ; 
	}
	return 0 ;
}


/**
	����ϱ� ������ Drag-On
*/
int	SPWindowAuction::OnSaleItemButtonUp	( WPARAM wParam, LPARAM lParam )
{
	SPItem* pDragItem = NULL ;

	// Drag�� ���� ó���� ��� �̰����� �Ѵ�.
	CheckSaleItem() ;

	return 1 ;
}



/**
	Sale Item Tooltip
*/
int SPWindowAuction::OnSaleItemToolTipEnter(WPARAM wParam, LPARAM lParam)
{
	if( m_pSaleItem != NULL )
	{
		SPItemStatus* pItemStatus = m_pSaleItem->GetItemStatus();

		SPWindow* pWindow = g_pInterfaceManager->GetToolTipWindow();
		pWindow->SPSendMessage( SPIM_TOOLTIP_ENTER, (WPARAM)pItemStatus, lParam);
		pWindow->Show();
	}

	return 1;
}

int SPWindowAuction::OnSaleItemToolTipOut(WPARAM wParam, LPARAM lParam)
{
	if( m_pSaleItem != NULL )
	{
		SPWindow* pWindow = g_pInterfaceManager->GetToolTipWindow();
		pWindow->SPSendMessage( SPIM_TOOLTIP_OUT, NULL, lParam);
		pWindow->Show();
	}
	return 1;
}

int SPWindowAuction::OnSaleItemToolTipMove(WPARAM wParam, LPARAM lParam)
{
	if( m_pSaleItem != NULL )
	{
		SPItemStatus* pItemStatus = m_pSaleItem->GetItemStatus();

		SPWindow* pWindow = g_pInterfaceManager->GetToolTipWindow();
		if( !pWindow->IsShow() )	{
			pWindow->SPSendMessage(SPIM_TOOLTIP_MOVE, (WPARAM)pItemStatus, lParam);
			pWindow->Show();
		}
	}
	return 1;
}





/**
	[��Ž��۰�] �Է�
	���۰��� �ԷµǸ� �������� ������Ʈ �Ǿ�� �Ѵ�.
*/
int SPWindowAuction::OnSaleMoneyKeyDown(WPARAM wParam, LPARAM lParam)
{
	UpdateEnrolFee() ;
	return 0 ;
}

/**
	[��� �Ⱓ] ����
	�Ⱓ�� ����Ǹ� �������� ������Ʈ
*/
int SPWindowAuction::OnSaleDuration(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	int iDuration = iID - WIID_AUCTION_REGI_DURATION_BTN ;
	m_iSaleDuration = (AUCTION_DURATION)iDuration ;
	SetSaleDuration(m_iSaleDuration) ;
	UpdateEnrolFee() ;

	return 0 ;
}



/**
	������ ��� �ϱ�
*/
int SPWindowAuction::OnSaleRegistItem(WPARAM wParam, LPARAM lParam)
{
	// ��� Ÿ�Կ� ���� ������üũ�� ��� ����� ����ؾ� �Ѵ�.
	if( m_iSaleType > 0 )
	{
		UpdateEnrolFee() ;		// �ۼ��� �ݾ��� ������Ʈ

		AUCTION_TYPE_INFO* pAuctionTypeInfo = g_pkAuctionManager->GetAuctionTypeInfo(m_iSaleType) ;
		if( pAuctionTypeInfo == NULL )
			return 0 ;

		if( CheckCreateItem( pAuctionTypeInfo ) == false )
			return 0 ;

		// ��϶� �Һ�Ǵ� �������� ����� �� ����.
		// ��� �Ұ� ������ [52000022]
		//if( m_iSaleType == AUCTION_TYPE_ITEM_BY_ELY && (m_pSaleItem->GetItemStatus()->GetItemID() == pAuctionTypeInfo->iConsumeItem) )	{
		//	if( g_pResourceManager->GetGlobalString(52000022) )
		//		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000022) );
		//	return 0 ;
		//}

		m_pSaleTypeInfo = pAuctionTypeInfo ;
		m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000077)) ;		// ��� �޽���
		if( m_iSaleType == AUCTION_TYPE_ITEM_BY_ELY)	{
			g_pkAuctionManager->SendAuctionSaleItem(m_pSaleItem, m_iSaleStartMoney, m_iSaleSpotMoney, m_iSaleDuration, m_iEnrolFee ) ;
		}
		else {
			g_pkAuctionManager->SendAuctionSaleMoney(m_iSaleType, m_iSaleMoney, m_iSaleStartMoney, m_iSaleSpotMoney, m_iSaleDuration, m_iEnrolFee ) ;
		}

		SetAuctionSaleType() ;		// �Ǹ� ������ ���������� �ʱ�ȭ �Ѵ�.
		SetSaleItemInfo() ;			// DragItem �ʱ�ȭ
	}

	return 0 ;
}



/**
	��� ������ ���� �ʱ�ȭ
*/
int SPWindowAuction::OnSaleClearItem(WPARAM wParam, LPARAM lParam)
{
	SetAuctionSaleType() ;		// �Ǹ� ������ ���������� �ʱ�ȭ �Ѵ�.
	SetSaleItemInfo() ;				// DragItem �ʱ�ȭ

	return 0 ;
}


/**
	����Ʈ ī������ ����
*/
int SPWindowAuction::OnSortSaleQuality(WPARAM wParam, LPARAM lParam)
{
	if( g_pkAuctionManager->GetAuctionSaleArchive()->GetListCount() > 0 )	{
		if( g_pkAuctionManager->GetAuctionSaleArchive()->SetSort(AUCTION_SORT_QUALITY) )
		{
			UpdateSortArrow(AUCTION_SALE_TAB) ;
			ShowSaleList(m_iSaleCurPage) ;		// BuyList Update
		}
	}

	return 0 ;
}

int SPWindowAuction::OnSortSaleFinish(WPARAM wParam, LPARAM lParam)
{
	if( g_pkAuctionManager->GetAuctionSaleArchive()->GetListCount() > 0 )	{
		if( g_pkAuctionManager->GetAuctionSaleArchive()->SetSort(AUCTION_SORT_DURATION) )
		{
			UpdateSortArrow(AUCTION_SALE_TAB) ;
			ShowSaleList(m_iSaleCurPage) ;
		}
	}

	return 0 ;
}

int SPWindowAuction::OnSortSalePrice(WPARAM wParam, LPARAM lParam)
{
	if( g_pkAuctionManager->GetAuctionSaleArchive()->GetListCount() > 0 )	{
		if( g_pkAuctionManager->GetAuctionSaleArchive()->SetSort(AUCTION_SORT_PRICE) )
		{
			UpdateSortArrow(AUCTION_SALE_TAB) ;
			ShowSaleList(m_iSaleCurPage) ;
		}
	}

	return 0 ;
}


/**
	����Ʈ [������] ����
*/
int SPWindowAuction::OnSaleListCancelClick(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	int iSelectRow = (iID - WIID_AUCTION_SALE_LIST) / AUCTION_MAX_LIST_ITEM ;
	int iSelectIndex = (iID - WIID_AUCTION_SALE_LIST) % AUCTION_MAX_LIST_ITEM ;
	if( iSelectRow < 0 || iSelectRow > AUCTION_SALE_LIST )
		return 0 ;

	if( iSelectIndex < AUCTION_SALE_LIST && m_pWindowSaleList[iSelectRow]->GetAuctionAttr() == NULL )	{
		ErrorFLogs->Error_Log("SPWindowAuction::OnSaleListCancelClick[%d, %d] is NoDATA", iSelectRow, iSelectIndex) ;
		return 0 ;
	}
	else	{
		// �ð��� ����Ǹ� ���� ǥ�ø� �Ѵ�.
		if( m_pWindowSaleList[iSelectIndex]->GetAuctionAttr()->GetFinishTime() < 1 )	{
			if( g_pResourceManager->GetGlobalString(52000108) )		// ��Žð� ����
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000108) );
			m_pWindowSaleList[iSelectIndex]->SetFinishTime() ;		// ����ǥ��
		}
		else	{
			SPAuctionAttr* pItemAttr = m_pWindowSaleList[iSelectRow]->GetAuctionAttr() ;
			if( pItemAttr )
				m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_BID_MSG, AUCTION_MSG_CANCEL, (LPARAM)pItemAttr) ;
		}
	}
	return 0 ;
}


/**
	������ ����
*/
int SPWindowAuction::OnSaleListPage(WPARAM wParam, LPARAM lParam)
{
	int iPage = (int)wParam ;
	int iSelectBundle = (int)lParam ;
	int iSelectPage = iPage ;

	// �ش� �������� �����͸� ������ ������ Manager���� ��������
	// ������ ��Ŷ�� ������ ������ ��û�Ѵ�.
	if( g_pkAuctionManager->GetAuctionSaleArchive()->HasPageInfo(iSelectPage) )
	{
		m_iSaleCurPage = iSelectPage ;
		ShowSaleList(m_iSaleCurPage) ;		// BuyList Update
	}
	else
	{
		ErrorFLogs->Error_Log("SaleArchive Hasn't Info [%d]Page", iSelectPage) ;
	}

	return 0 ;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
/**
	����Ʈ ������ ó��
*/
int SPWindowAuction::OnReceiveAuctionSaleList(WPARAM wParam, LPARAM lParam)
{
	SPAuctionArchive* pArchive ;
	std::vector<SPAuctionAttr*> vShowList ;

	m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, 0, 0) ;
	pArchive = g_pkAuctionManager->GetAuctionSaleArchive() ;
	
	UpdateSortArrow(AUCTION_SALE_TAB) ;

	// Page Setting
	int iMaxPage = pArchive->GetTotalPageCount() ;
	if( iMaxPage < 1 )		iMaxPage = 1 ;
	SPWindowPageSelect* pkPageSelect ;
	pkPageSelect = (SPWindowPageSelect*)Find(WIID_AUCTION_SALE_PAGE, true);
	if( pkPageSelect )	{
		//ErrorFLogs->Error_Log("Set Auction SALE Page[%d]", iMaxPage) ;
		pkPageSelect->SetMaxPageInfo(iMaxPage) ;		// ���� ������ ������ ����
		pkPageSelect->SetSelectPage((m_iSaleCurPage%10)) ;
	}

	if( IsShow() && m_iSelectedTab == AUCTION_SALE_TAB )
	{
		// List Setting
		ShowSaleList(m_iSaleCurPage) ;
		return 1 ;
	}

	return 0 ;
}



