// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPWindowAuctionSearch.cpp
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
#include "SPWindowRowUNIT.h"
#include "SPWindowAuctionListUnit.h"
#include "SPComboBoxDEF.h"
#include "SPComboBoxItemBase.h"
#include "SPComboBoxItemTexture.h"
#include "SPWindowComboBox.h"
#include "SPWindowPageSelect.h"

#include "SPLDTFile.h"
#include "SPLDTManager.h"
#include "SPResourceManager.h"

#include "SPGameObjectDEF.h"
#include "SPGameObject.h"

#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPGOBManager.h"
#include "SPGOBStatus.h"
#include "SPGOBModel.h"
#include "SPGOBModelUnit.h"
#include "SPMonsterModelUnit.h"
#include "SPAvatarModelUnit.h"
#include "SPGOBCluster.h"
#include "SPGameObject.h"
#include "SPGOBCoordPhysics.h"
#include "SPPlayer.h"

#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"

#include "SPAuctionDef.h"
#include "SPAuctionAttr.h"
#include "SPAuctionArchive.h"
#include "SPAuctionManager.h"

#include "SPCheckManager.h"
#include "SPWindowAuction.h"
#include "SPWindowAuctionMsg.h"
#include "SPTimer.h"
#include "GlobalDefines_Share.h"
#include "_Error_log.h"


void SPWindowAuction::InitAuctionSearch()
{
	int i ;
	SPWindowStatic*	pWindowStaticFrame;
	SPWindowStatic*	pWindowStaticBG;
	SPWindowStatic*	pWindowStatic;
	SPWindowButton*	pWindowButton;
	SPWindowEdit*	pWindowEdit ;
	SPWindowComboBox* pComboBox ;
	SPComboBoxItemTexture* pkComboItem;
	SPWindowPageSelect* pkPageSelect;

	pWindowStaticFrame	=	new SPWindowStatic( WIID_AUCTION_SEARCH_FRAME , 12 , 84 , 778 , 410 , this );
	m_pWindowSearch = (SPWindow*)pWindowStaticFrame ;

	pWindowStaticBG	=	new SPWindowStatic( WIID_AUCTION_SEARCH_SEL_BG , 4 , 4 , 144 , 50 , m_pWindowSearch );
	pWindowStaticBG->SetWindowType(WND_TYPE_NINEBASE) ;
	pWindowStaticBG->SetImageNine( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 251, 1, 12, 1) ;

	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_SEL_ICON , 23 , 14 , 32 , 32 , m_pWindowSearch );
	//pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_SEL_ICON , 19 , 14 , 32 , 32 , m_pWindowSearch );
	pWindowStatic	=	NULL;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_SEL_TEXT , 59 , 25 , 71 , 12 , m_pWindowSearch );
	pWindowStatic->SetFont(FONT_12_BOLD) ;
	pWindowStatic->SetFontColor( RGBA(143, 99, 99, 255) );
	pWindowStatic->SetFormat(DT_TOP | DT_CENTER);
	//pWindowStatic->SetWindowText("Selected") ;
	pWindowStatic	=	NULL;

	// �β������ & ���� ����
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_SEL_LINE , 148 , 50 , 628 , 5 , m_pWindowSearch );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 50 , 32 );
	pWindowStatic->SetSrcSize(4, 5) ;
	pWindowStatic	=	NULL;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_SEL_LINE+1 , 0 , 54 , 776, 1 , m_pWindowSearch );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 22, 23);
	pWindowStatic->SetSrcSize(6, 1) ;
	pWindowStatic	=	NULL;

	// MAIN MENU
	int iButtonStartX = 726 - m_iSearchMenuMax*64 ;
	for( i = 0 ; i < m_iSearchMenuMax ; i++ )
	{
		pWindowButton	=	new	SPWindowButton( WIID_AUCTION_SEARCH_MENU_BUTTON+i , iButtonStartX+i*64 , 0 , 64 , 52 , m_pWindowSearch );
		pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 146 );
		pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 199 );
		pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 252 );
		pWindowButton->SetImageCheck	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 252 );
		pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 1 , 305 );

		//��������¿��� x18 y4 (size 30 30)
		pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_MENU_ICON+i , 18 , 4 , 30 , 30 , pWindowButton );
		pWindowStatic->SetImage( m_strMenuIconPath.c_str() , m_stMenu[i].rcIconSrc.left , m_stMenu[i].rcIconSrc.top ) ;
		pWindowStatic	=	NULL;

		//�ؽ�Ʈ��¿��� x0  y36 (size 64 12 ) 
		// �⺻,���콺����(bold 143 99 99)
		// Ŭ��,üũ (bold 255 255 255)
		pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_MENU_TEXT+i , 0 , 36 , 64 , 12 , pWindowButton );
		pWindowStatic->SetFont(FONT_12_BOLD) ;
		pWindowStatic->SetFontColor( RGBA(143, 99, 99, 255) );
		pWindowStatic->SetFormat(DT_TOP | DT_CENTER);
		pWindowStatic->SetWindowText(m_stMenu[i].strCategory.c_str()) ;
		pWindowStatic	=	NULL;
	}

	// �˻� �޴� �˾�â
	InitAuctionPopMenu() ;		

	// Sub BG
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_LIST_LINE , 0 , 54 , 776 , 1 , m_pWindowSearch );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 22 , 23 );
	pWindowStatic->SetSrcSize(1, 4);
	pWindowStaticFrame	=	new SPWindowStatic( WIID_AUCTION_SEARCH_LIST_BG , 0 , 55 , 776 , 325 , m_pWindowSearch );
	pWindowStaticFrame->SetImage( "DATA/INTERFACE/CONCEPT/UI_WinBG_000.PNG" , 502 , 472 );
	pWindowStaticFrame->SetSrcSize(4, 4);

	// List Title (Quality)
	pWindowButton = new SPWindowButton( WIID_AUCTION_SEARCH_LIST_QUALITY	, 4 , 4 , 205 , 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 66 , 294);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 66 , 314);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 66 , 334);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_QUALITY, 190 , 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSearchSort[AUCTION_SORT_QUALITY] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;
	pWindowButton = new SPWindowButton( WIID_AUCTION_SEARCH_LIST_LEVEL	, 213 , 4 , 42, 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 268, 85);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 268, 105);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 268, 125);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_ITEM_LV, 27 , 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSearchSort[AUCTION_SORT_ITEM_LV] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;
	pWindowButton = new SPWindowButton( WIID_AUCTION_SEARCH_LIST_DURATION	, 259 , 4 , 60 , 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 311, 85);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 311, 105);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 311, 125);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_ITEM_OPTPOINT, 45 , 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSearchSort[AUCTION_SORT_ITEM_OPTPOINT] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;
	pWindowButton = new SPWindowButton( WIID_AUCTION_SEARCH_LIST_FINISHTIME	, 323 , 4, 67, 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 372, 85);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 372, 105);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 372, 125);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_DURATION, 52, 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSearchSort[AUCTION_SORT_DURATION] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SEARCH_LIST_SELLER , 394 , 4, 112, 19, pWindowStaticFrame );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 108 , 266);
	pWindowStatic = NULL ;
	pWindowButton = new SPWindowButton( WIID_AUCTION_SEARCH_LIST_PRICE	, 510 , 4 , 262 , 19 , pWindowStaticFrame );
	pWindowButton->SetImage		( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 108 , 146);
	pWindowButton->SetImageHit	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 108 , 166);
	pWindowButton->SetImagePush	( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 108 , 186);
	pWindowStatic =	new SPWindowStatic( WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_PRICE, 247 , 5, 10, 9, pWindowButton );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 450, 1);
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 461, 1);
	m_pSearchSort[AUCTION_SORT_PRICE] = (SPWindow*)pWindowStatic ;
	pWindowButton = NULL ;
	pWindowStatic = NULL ;

	//////////////////////////////////////////////////////////////////////////
	// Search List
	for( i = 0; i < AUCTION_SEARCH_LIST; i++)
	{
		m_pWindowSearchList[i] = new SPWindowAuctionListUNIT( WIID_AUCTION_SEARCH_LIST + (i * AUCTION_MAX_LIST_ITEM), 0, 28 + i*43, 776, 43, pWindowStaticFrame) ;
		m_pWindowSearchList[i]->SetToolTipStr("Search List") ;
	}

	// Page Number
	pkPageSelect = new SPWindowPageSelect(WIID_AUCTION_SEARCH_PAGE, 0, 301, 776, 14, pWindowStaticFrame);

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
	// Bottom Menu
	// �ϴ��� �ƺ�� ������ ��� Ÿ�Ժ��� �޶����� �Ѵ�.

	// ������ �˻��� ���� �˻� �ɼ�
	pWindowStaticFrame = NULL ;
	pWindowStaticFrame = new SPWindowStatic( WIID_AUCTION_SEARCH_BT_ITEM, 0, 381, 628, 29, m_pWindowSearch ) ;

	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_LEVEL_TITLE , 0 , 388-381 , 41 , 13 , pWindowStaticFrame );		// ����
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 470 , 191 );
	pWindowStatic	=	NULL;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_LEVEL_DASH , 75 , 391-381 , 10 , 6 , pWindowStaticFrame );		// -
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 21 , 25 );
	pWindowStatic	=	NULL;

	// �ڽ��� ������ ������ ��� Edit�� ��Ȱ��ȭ�ϱ����� Edit�ȿ� �̹��� ����
	pWindowEdit		= new SPWindowEdit(WIID_AUCTION_SEARCH_BT_LEVEL_MIN, 41, 4, 32, 18, pWindowStaticFrame) ;
	pWindowEdit->SetWindowType(WND_TYPE_LEFTBASE);
	pWindowEdit->SetMargin( 4, 3);
	pWindowEdit->SetImageNormalHead		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG",  97 , 1, 101, 19);
	pWindowEdit->SetImageNormalBody		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 102 , 1, 106, 19);
	pWindowEdit->SetImageNormalTail		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 107 , 1, 111, 19);
	pWindowEdit->SetImageFocusHead		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG",  97 , 1, 101, 19);
	pWindowEdit->SetImageFocusBody		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 102 , 1, 106, 19);
	pWindowEdit->SetImageFocusTail		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 107 , 1, 111, 19);
	pWindowEdit->SetFontColor(RGBA(0, 0, 0, 255));
	pWindowEdit->SetEnableTabStop(true);
	pWindowEdit->SetLimitText(3);
	pWindowEdit->SetNumber(true) ;
	pWindowEdit->Hide() ;
	pWindowEdit		= new SPWindowEdit(WIID_AUCTION_SEARCH_BT_LEVEL_MAX, 87, 4, 32, 18, pWindowStaticFrame) ;
	pWindowEdit->SetWindowType(WND_TYPE_LEFTBASE);
	pWindowEdit->SetMargin( 4, 3);
	pWindowEdit->SetImageNormalHead		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG",  97 , 1, 101, 19);
	pWindowEdit->SetImageNormalBody		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 102 , 1, 106, 19);
	pWindowEdit->SetImageNormalTail		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 107 , 1, 111, 19);
	pWindowEdit->SetImageFocusHead		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG",  97 , 1, 101, 19);
	pWindowEdit->SetImageFocusBody		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 102 , 1, 106, 19);
	pWindowEdit->SetImageFocusTail		("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 107 , 1, 111, 19);
	pWindowEdit->SetFontColor(RGBA(0, 0, 0, 255));
	pWindowEdit->SetEnableTabStop(true);
	pWindowEdit->SetLimitText(3);
	pWindowEdit->SetNumber(true) ;
	pWindowEdit->Hide() ;

	// ǰ��
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_QUAL_TITLE , 119 , 388-381 , 41 , 13 , pWindowStaticFrame );	// ǰ��
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 470 , 205 );
	pWindowStatic	=	NULL;

	pComboBox = new SPWindowComboBox(WIID_AUCTION_SEARCH_BT_QUAL_COMBO, 160, 385-381, 103, 19, pWindowStaticFrame);
	pComboBox->SetDropDownOffset(85, 6);
	pComboBox->SetDropDownSize(8, 7);
	pComboBox->SetDropDownTexture( COMBOBOX_DATA_TEXTURE_ENABLE	, "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 472 , 7 );	// ��ư
	pComboBox->SetDropDownTexture( COMBOBOX_DATA_TEXTURE_HIT	, "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 481 , 7 );
	pComboBox->SetDropDownTexture( COMBOBOX_DATA_TEXTURE_PUSH	, "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 490 , 7 );
	pComboBox->SetDropDownTexture( COMBOBOX_DATA_TEXTURE_DISABLE, "DATA/INTERFACE/CONCEPT/UI_Button_002.PNG" , 499 , 7 );
	pComboBox->SetScroll(FALSE);
	pComboBox->SetDropDownStatus(COMBOBOX_DATA_TEXTURE_ENABLE);

	pComboBox->SetListBoxItemMargin(1, 1, 1, 1);
	pComboBox->SetShowEditBoxText(TRUE);
	pComboBox->SetEditBoxOffset(0, 0);
	pComboBox->SetEditBoxSize( 103, 17 );
	pComboBox->SetEditBoxTextColor(D3DXCOLOR(0.1921f, 0.2980f, 0.3803f, 1.0f));
	pComboBox->SetEditBoxTexture( COMBOBOX_DATA_TEXTURE_ENABLE	, "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 344, 1, 361, 18 );	// ���
	pComboBox->SetEditBoxTexture( COMBOBOX_DATA_TEXTURE_HIT		, "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 362, 1, 379, 18 );
	pComboBox->SetEditBoxTexture( COMBOBOX_DATA_TEXTURE_PUSH	, "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 380, 1, 397, 18 );

	pComboBox->SetListBoxOffset(0, 17);
	pComboBox->SetListBoxTexture( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 398 , 1 , 415 , 18 );		// �˾� ���
	pComboBox->SetRenderItemCountMax(7);

	pkComboItem = new SPComboBoxItemTexture;
	pkComboItem->SetSize(101, 14);
	pkComboItem->SetText(g_pResourceManager->GetGlobalString(52000043));		// ��ü
	pkComboItem->SetTextColor( RGBA(0, 0, 0, 255));
	pkComboItem->SetTexture(COMBOBOX_DATA_TEXTURE_HIT, "DATA/INTERFACE/CONCEPT/CASHSHOP02.PNG", 499 , 92 , 500 , 93 );
	pComboBox->AddItem(pkComboItem);

	pkComboItem = new SPComboBoxItemTexture;
	pkComboItem->SetSize(101, 14);
	pkComboItem->SetText(g_pResourceManager->GetGlobalString(52000037));		// ���ϱ�
	pkComboItem->SetTextColor(RGBA(0, 0, 0, 255));
	pkComboItem->SetTexture(COMBOBOX_DATA_TEXTURE_HIT, "DATA/INTERFACE/CONCEPT/CASHSHOP02.PNG", 499 , 92 , 500 , 93 );
	pComboBox->AddItem(pkComboItem);

	pkComboItem = new SPComboBoxItemTexture;
	pkComboItem->SetSize(101, 14);
	pkComboItem->SetText(g_pResourceManager->GetGlobalString(52000038));		// �ϱ�
	pkComboItem->SetTextColor(RGBA(44, 143, 53, 255));
	pkComboItem->SetTexture(COMBOBOX_DATA_TEXTURE_HIT, "DATA/INTERFACE/CONCEPT/CASHSHOP02.PNG", 499 , 92 , 500 , 93 );
	pComboBox->AddItem(pkComboItem);

	pkComboItem = new SPComboBoxItemTexture;
	pkComboItem->SetSize(101, 14);
	pkComboItem->SetText(g_pResourceManager->GetGlobalString(52000039));		// �߱�
	pkComboItem->SetTextColor(RGBA(26, 155, 209, 255));
	pkComboItem->SetTexture(COMBOBOX_DATA_TEXTURE_HIT, "DATA/INTERFACE/CONCEPT/CASHSHOP02.PNG", 499 , 92 , 500 , 93 );
	pComboBox->AddItem(pkComboItem);

	pkComboItem = new SPComboBoxItemTexture;
	pkComboItem->SetSize(101, 14);
	pkComboItem->SetText(g_pResourceManager->GetGlobalString(52000040));		// ���
	pkComboItem->SetTextColor(RGBA(222, 146, 27, 255));
	pkComboItem->SetTexture(COMBOBOX_DATA_TEXTURE_HIT, "DATA/INTERFACE/CONCEPT/CASHSHOP02.PNG", 499 , 92 , 500 , 93 );
	pComboBox->AddItem(pkComboItem);

	pkComboItem = new SPComboBoxItemTexture;
	pkComboItem->SetSize(101, 14);
	pkComboItem->SetText(g_pResourceManager->GetGlobalString(52000041));		// �ֻ��
	pkComboItem->SetTextColor(RGBA(255, 0, 0, 255));
	pkComboItem->SetTexture(COMBOBOX_DATA_TEXTURE_HIT, "DATA/INTERFACE/CONCEPT/CASHSHOP02.PNG", 499 , 92 , 500 , 93 );
	pComboBox->AddItem(pkComboItem);

	pkComboItem = new SPComboBoxItemTexture;
	pkComboItem->SetSize(101, 14);
	pkComboItem->SetText(g_pResourceManager->GetGlobalString(52000042));		// �����
	pkComboItem->SetTextColor(RGBA(0, 0, 255, 255));
	pkComboItem->SetTexture(COMBOBOX_DATA_TEXTURE_HIT, "DATA/INTERFACE/CONCEPT/CASHSHOP02.PNG", 499 , 92 , 500 , 93 );
	pComboBox->AddItem(pkComboItem);

	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_USEABLE_TITLE , 263 , 388-381 , 121 , 13 , pWindowStaticFrame );	// ��밡�� ����
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 390 , 233 );
	pWindowStatic	=	NULL;
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_SEARCH_BT_USEABLE_BTN , 384 , 388-381 , 13 , 13 , pWindowStaticFrame );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 441 , 455 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 441 , 468 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 441 , 481 );
	pWindowButton->SetImageCheck	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 441 , 481 );
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_NAME_TITLE , 397 , 388-381 , 55 , 13 , pWindowStaticFrame );	// �̸�
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 456 , 219 );
	pWindowStatic	=	NULL;
	pWindowStaticBG = new SPWindowStatic( WIID_AUCTION_SEARCH_BT_NAME_BG	, 452 , 385-381 , 172 , 18 , pWindowStaticFrame );	//  �̸� ���
	pWindowStaticBG->SetWindowType(WND_TYPE_LEFTBASE);
	pWindowStaticBG->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG",  97 , 1, 101, 19);
	pWindowStaticBG->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 102 , 1, 106, 19);
	pWindowStaticBG->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 107 , 1, 111, 19);
	m_pWindowSearchEdit		= new SPWindowEdit(WIID_AUCTION_SEARCH_BT_NAME_EDIT, 4, 4, 161, 12, pWindowStaticBG) ;
	m_pWindowSearchEdit->SetFontColor(RGBA(0, 0, 0, 255));
	m_pWindowSearchEdit->SetEnableTabStop(true);
	m_pWindowSearchEdit->SetLimitText(26);		// �������� ���� �� �̸��� �ѱ� 13����

	// �Ӵ� �˻��� ���� �˻� �ɼ�
	pWindowStaticFrame = NULL ;
	pWindowStaticFrame =	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_MONEY , 0 , 381 , 628 , 29 , m_pWindowSearch );		// �ϴ� ���
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_MONEY_DASH , 493 , 10 , 10 , 6 , pWindowStaticFrame );		// -
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 21 , 25 );
	pWindowStatic	=	NULL;

	pWindowStaticBG = new SPWindowStatic( WIID_AUCTION_SEARCH_BT_MONEY_MIN+1 , 398 , 4 , 93 , 18 , pWindowStaticFrame );	// Edit ���
	pWindowStaticBG->SetWindowType(WND_TYPE_LEFTBASE);
	pWindowStaticBG->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG",  97 , 1, 101, 19);
	pWindowStaticBG->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 102 , 1, 106, 19);
	pWindowStaticBG->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 107 , 1, 111, 19);
	pWindowEdit		= new SPWindowEdit(WIID_AUCTION_SEARCH_BT_MONEY_MIN, 5, 5, 83, 12, pWindowStaticBG) ;
	pWindowEdit->SetFormat(DT_TOP | DT_RIGHT);
	pWindowEdit->SetFontColor(RGBA(0, 0, 0, 255));
	pWindowEdit->SetEnableTabStop(true);
	pWindowEdit->SetLimitText(9);			// 9��
	pWindowEdit->SetNumber(true) ;
	pWindowEdit->Hide() ;
	pWindowStaticBG = new SPWindowStatic( WIID_AUCTION_SEARCH_BT_MONEY_MAX+1 , 505 , 4 , 93 , 18 , pWindowStaticFrame );	// Edit ���
	pWindowStaticBG->SetWindowType(WND_TYPE_LEFTBASE);
	pWindowStaticBG->SetImageNormalHead("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG",  97 , 1, 101, 19);
	pWindowStaticBG->SetImageNormalBody("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 102 , 1, 106, 19);
	pWindowStaticBG->SetImageNormalTail("DATA/INTERFACE/CONCEPT/UI_Object_002.PNG", 107 , 1, 111, 19);
	pWindowEdit		= new SPWindowEdit(WIID_AUCTION_SEARCH_BT_MONEY_MAX, 5, 5, 83, 12, pWindowStaticBG) ;
	pWindowEdit->SetFormat(DT_TOP | DT_RIGHT);
	pWindowEdit->SetFontColor(RGBA(0, 0, 0, 255));
	pWindowEdit->SetEnableTabStop(true);
	pWindowEdit->SetLimitText(9);			// 9��
	pWindowEdit->SetNumber(true) ;
	pWindowEdit->Hide() ;
	pWindowStatic	=	new SPWindowStatic( WIID_AUCTION_SEARCH_BT_MONEY_ICON , 602 , 8 , 17 , 11 , pWindowStaticFrame );
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 157 , 22 );	// Ely
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 193 , 22 );	// Cash
	pWindowStatic->SetImage( "DATA/INTERFACE/CONCEPT/UI_Object_002.PNG" , 211 , 22 );	// Point

	// �˻� �� ��ҹ�ư
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_SEARCH_BT_SEARCH , 628 , 386 , 68 , 18 , m_pWindowSearch );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 139 , 289 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 139 , 307 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 139 , 325 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 139 , 343 );
	m_pSearchButton = (SPWindow*)pWindowButton ;
	pWindowButton	=	new	SPWindowButton( WIID_AUCTION_SEARCH_BT_CLOSE , 700 , 386 , 68 , 18 , m_pWindowSearch );
	pWindowButton->SetImage			( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 289 );
	pWindowButton->SetImageHit		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 307 );
	pWindowButton->SetImagePush		( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 325 );
	pWindowButton->SetImageDisable	( "DATA/INTERFACE/CONCEPT/UI_Button_000.PNG" , 208 , 343 );

}


/**
	�޴� ������ �ִ� AUCTION_ITEM.LDT Load
*/
void SPWindowAuction::LoadMenuLDT()
{
	int i ;
	for( i = 0 ; i < AUCTION_MAX_MENU; i++)
		m_stMenu[i].Init() ;

	std::string strLDTFile;
	strLDTFile = "DATA/LDT/AUCTION_ITEM.LDT";
	m_strMenuIconPath = "DATA/INTERFACE/CONCEPT/UI_Icon_000.PNG" ;

	SPLDTFile* pkLDTFile = NULL;
	if( !g_pResourceManager->GetLDTFromFileName(strLDTFile.c_str(), &pkLDTFile) )
	{
		ErrorFLogs->Error_Log("Can't Find AUCTION_ITEM.LDT[%s]", strLDTFile.c_str()) ;
		return;
	}

	int iDataNum, iFieldNum;
	long lItemID;
	int iCategoryIndex = 0 ;

	LDT_Field Field;
	AUCTION_MENU_DETAIL*	pMenuDetail = NULL ;

	iDataNum = pkLDTFile->GetItemCount();
	iFieldNum = pkLDTFile->GetFieldCount();
	for( i = 0; i < iDataNum; i++ )
	{
		lItemID = pkLDTFile->GetPrimaryKey(i);

		Field.Init() ;					// Category
		pkLDTFile->GetField(lItemID, 0, Field);
		iCategoryIndex = Field.uData.lValue - 1 ;

		if( iCategoryIndex < 0 )	{
			return;
		}
		m_iSearchMenuMax = (m_iSearchMenuMax < iCategoryIndex) ? iCategoryIndex : m_iSearchMenuMax ;

		// Add Category Info
		if( m_stMenu[iCategoryIndex].iCategory_ID <= 0 )
		{
			// Category ID
			Field.Init() ;					// Category
			pkLDTFile->GetField(lItemID, 1, Field);
			m_stMenu[iCategoryIndex].iCategory_ID = Field.uData.lValue ;
			Field.Init() ;					// Icon SX
			pkLDTFile->GetField(lItemID, 3, Field);
			m_stMenu[iCategoryIndex].rcIconSrc.left = Field.uData.lValue ;
			Field.Init() ;					// Icon SY
			pkLDTFile->GetField(lItemID, 4, Field);
			m_stMenu[iCategoryIndex].rcIconSrc.top = Field.uData.lValue ;
			Field.Init() ;					// Icon EX
			pkLDTFile->GetField(lItemID, 5, Field);
			m_stMenu[iCategoryIndex].rcIconSrc.right = Field.uData.lValue ;
			Field.Init() ;					// Icon EY
			pkLDTFile->GetField(lItemID, 6, Field);
			m_stMenu[iCategoryIndex].rcIconSrc.bottom = Field.uData.lValue ;
			Field.Init() ;					// �з� ��Ʈ��
			pkLDTFile->GetField(lItemID, 7, Field);
			m_stMenu[iCategoryIndex].strCategory	=	Field.uData.pValue;
		}

		// Add Detail Info
		pMenuDetail = new AUCTION_MENU_DETAIL ;
		Field.Init() ;					// Detail ID
		pkLDTFile->GetField(lItemID, 2, Field);
		pMenuDetail->iDetail_ID = Field.uData.lValue ;
		Field.Init() ;					// Detail ��Ʈ��
		pkLDTFile->GetField(lItemID, 12, Field);
		pMenuDetail->strDetail = Field.uData.pValue;

		Field.Init() ;					// SX
		pkLDTFile->GetField(lItemID, 8, Field);
		pMenuDetail->rcIconSrc.left = Field.uData.lValue ;
		Field.Init() ;					// SY
		pkLDTFile->GetField(lItemID, 9, Field);
		pMenuDetail->rcIconSrc.top = Field.uData.lValue ;
		Field.Init() ;					// EX
		pkLDTFile->GetField(lItemID, 10, Field);
		pMenuDetail->rcIconSrc.right = Field.uData.lValue ;
		Field.Init() ;					// EY
		pkLDTFile->GetField(lItemID, 11, Field);
		pMenuDetail->rcIconSrc.bottom = Field.uData.lValue ;

		Field.Init() ;					// SX
		pkLDTFile->GetField(lItemID, 13, Field);
		pMenuDetail->rcBigIconSrc.left = Field.uData.lValue ;
		Field.Init() ;					// SY
		pkLDTFile->GetField(lItemID, 14, Field);
		pMenuDetail->rcBigIconSrc.top = Field.uData.lValue ;
		Field.Init() ;					// EX
		pkLDTFile->GetField(lItemID, 15, Field);
		pMenuDetail->rcBigIconSrc.right = Field.uData.lValue ;
		Field.Init() ;					// EY
		pkLDTFile->GetField(lItemID, 16, Field);
		pMenuDetail->rcBigIconSrc.bottom = Field.uData.lValue ;

		// ���� �޴� �߰�
		m_stMenu[iCategoryIndex].vpDetail.push_back(pMenuDetail) ;
		pMenuDetail = NULL ;
	}
	++m_iSearchMenuMax ;		// Index�� Size�� �ٲ���� �Ѵ�.

	// ���� ū SubMenu Size�� �����Ѵ�.
	for( i = 0 ; i < m_iSearchMenuMax; i++)
	{
		int iPopSize = (int)m_stMenu[i].vpDetail.size() ;
		m_iSearchPopMax = ( m_iSearchPopMax < iPopSize ) ? iPopSize : m_iSearchPopMax ;
	}

	SAFE_RELEASE(pkLDTFile) ;
}


/**
	�� �̵��� ���ؼ� ���â�� ���̴� ���
 */
void SPWindowAuction::ShowAuctionSearch()
{
	SPWindowButton* pButton = NULL ;

	m_pWindowBuy->Hide();
	m_pWindowSale->Hide();

	m_pWindowSearch->Show();
	m_pWindowSearchPopup->Hide();

	// �ϴ� �޴��� ����
	ShowSearchList(m_iSearchCurPage) ;
	SetSearchBottomMenu(m_iSelectedCategory, m_iSelectedDetail, false) ;
}


/**
	���â�� ó�� �������� �ʱ�ȭ�� Search�� ������ �Ѵ�.
*/
void SPWindowAuction::InitShowAuctionSearch()
{
	SPWindow* pWindow ;
	SPWindowPageSelect* pkPageSelect ;

	SetShowSearchGuide(true) ;		// Search Guide �����ֱ�
	m_pWindowBuy->Hide();
	m_pWindowSale->Hide();

	m_pWindowSearch->Show();
	m_pWindowSearchPopup->Hide();

	// Menu Select
	m_iSelectedTab = AUCTION_SEARCH_TAB ;
	pWindow = Find(WIID_AUCTION_MAIN_TAB+m_iSelectedTab	, true); 
	if(pWindow) pWindow->SPSendMessage(SPIM_BTN_SELECT, TRUE	);

	// List Clear
	for( int i = 0; i < AUCTION_SEARCH_LIST; i++ )
	{
		m_pWindowSearchList[i]->SetShowEnable(false) ;
	}

	// Page Clear
	pkPageSelect = (SPWindowPageSelect*)Find(WIID_AUCTION_SEARCH_PAGE, true);
	if( pkPageSelect )	{
		//ErrorFLogs->Error_Log("Init Auction Search Page") ;
		pkPageSelect->SetMaxPageInfo(1) ;
	}

	// Sort Key Clear
	// Search Key Clear
	m_pSearchKey->Clear() ;
	m_pSuccessKey->Clear() ;
	m_bSearchUsable		= false;		// ��밡�� ���� üũ

	SetSearchBottomMenu(m_iSelectedCategory, m_iSelectedDetail) ;		// �ϴ� �޴��� ����
}


/**
	���� ���õ� �޴��� ���� ��ܿ� ���̵��� �Ѵ�.
	@param bool bClear : true�̸� �ʱ�ȭ
*/
void SPWindowAuction::SetSelectedTitle(bool bClear/*=false*/)
{
	SPWindowStatic* pStaticIcon = (SPWindowStatic*)Find(WIID_AUCTION_SEARCH_SEL_ICON, true) ;
	SPWindowStatic* pStaticText = (SPWindowStatic*)Find(WIID_AUCTION_SEARCH_SEL_TEXT, true) ;

	if( bClear )
	{
		pStaticIcon->SPSendMessage(SPIM_SET_IMAGECLEAR);
		pStaticText->SetWindowText("") ;
	}
	else
	{
		if( pStaticIcon )	{
			pStaticIcon->SPSendMessage(SPIM_SET_IMAGECLEAR);
			pStaticIcon->SetImage(m_strMenuIconPath.c_str(), 
				m_stMenu[m_iSelectedCategory].vpDetail[m_iSelectedDetail]->rcBigIconSrc.left , 
				m_stMenu[m_iSelectedCategory].vpDetail[m_iSelectedDetail]->rcBigIconSrc.top) ;
		}

		if( pStaticText )	{
			pStaticText->SetWindowText(m_stMenu[m_iSelectedCategory].vpDetail[m_iSelectedDetail]->strDetail.c_str()) ;
		}
	}
}


/**
	Category���� SortButton �����Ѵ�.
	WIID_AUCTION_SEARCH_LIST_QUALITY		0N | ON
	WIID_AUCTION_SEARCH_LIST_LEVEL			ON | OFF
	WIID_AUCTION_SEARCH_LIST_DURATION		ON | OFF
	WIID_AUCTION_SEARCH_LIST_FINISHTIME		ON | ON
	WIID_AUCTION_SEARCH_LIST_PRICE			ON | ON
 */
void SPWindowAuction::SetSearchSortButton(int iCategory)
{
	SPWindow* pWindow = NULL ;
	if( CHECK_AUCTION_ITEM_CATEGORY(iCategory) )	{
		pWindow = Find(WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_ITEM_LV, true) ;
		if( pWindow )	pWindow->SetShowEnable(true) ;
		pWindow = Find(WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_ITEM_OPTPOINT, true) ;
		if( pWindow )	pWindow->SetShowEnable(true) ;
	}
	else	{
		pWindow = Find(WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_ITEM_LV, true) ;
		if( pWindow )	pWindow->SetShowEnable(false) ;
		pWindow = Find(WIID_AUCTION_SEARCH_SORT_ARROW + AUCTION_SORT_ITEM_OPTPOINT, true) ;
		if( pWindow )	pWindow->SetShowEnable(false) ;
	}
}


/**
	Archive�κ��� �������� �ش��ϴ� �����͸� �����ͼ� ����Ʈ�� ����Ѵ�.
	@param int iPage
*/
void SPWindowAuction::ShowSearchList(int iPage)
{
	SPAuctionArchive* pArchive ;
	std::vector<SPAuctionAttr*> vShowList ;
	pArchive = g_pkAuctionManager->GetAuctionSearchArchive() ;

	if( pArchive == NULL )	{
		ErrorFLogs->Error_Log("SPWindowAuction::ShowSearchList Archive is NULL") ;
		return ;
	}

	vShowList.clear() ;
	int iSize = pArchive->GetAuctionListPage(vShowList, iPage) ;
	for( int i = 0; i < AUCTION_SEARCH_LIST; i++ )
	{
		if( i < iSize )
		{
			m_pWindowSearchList[i]->SetAuctionItem(vShowList[i]) ;
			m_pWindowSearchList[i]->SetShowEnable(true) ;
		}
		else
		{
			m_pWindowSearchList[i]->ClearAuctionInfo() ;
			m_pWindowSearchList[i]->SetShowEnable(false) ;
		}
	}
}



/**
	������ SearchKey�� ���´�.
*/
bool SPWindowAuction::UpdateSearchKey()
{
	int	iSearchCategory ;		// �˻� ī�װ�Key
	int	iSearchLevelMin = 0 ;	// �˻� ����
	int	iSearchLevelMax = 0 ;	// �˻� ����
	int	iSearchMoneyMin = 0 ;	// �˻� �ݾ�
	int	iSearchMoneyMax = 0 ;	// �˻� �ݾ�
	int iItemLvMax = 999 ;
	SPWindow* pWindow = NULL ;

	if( m_iSelectedCategory < 0 || m_iSelectedDetail < 0 )	{
		ErrorFLogs->Error_Log("First, you should choice Category!!!") ;
		return false ;
	}

	iSearchCategory = m_stMenu[m_iSelectedCategory].vpDetail[m_iSelectedDetail]->iDetail_ID ;

	pWindow = Find( WIID_AUCTION_SEARCH_BT_LEVEL_MIN, true) ;		// Min
	if( pWindow )	iSearchLevelMin = atoi(pWindow->GetWindowText()) ;
	if( iSearchLevelMin < 1 )		iSearchLevelMin = 1 ;
	pWindow = Find( WIID_AUCTION_SEARCH_BT_LEVEL_MAX, true) ;		// Max Level
	if( pWindow )	iSearchLevelMax = atoi(pWindow->GetWindowText()) ;
	if( iSearchLevelMax < 1 )		iSearchLevelMax = 999 ;
	if( m_bSearchUsable )
	{
		SPPlayer* pPlayer = NULL ;
		pPlayer = g_pGOBManager->GetLocalPlayer() ;
		if( pPlayer == NULL )	{
			ErrorFLogs->Error_Log("Can't Find Player Info[SPWindowAuction::OnSearchItem]") ;
			return false ;
		}
		iItemLvMax = pPlayer->GetStatus()->GetLevel() ;
		iSearchLevelMax = iItemLvMax ;
	}
	iSearchLevelMax = (iSearchLevelMax > iItemLvMax ) ? iItemLvMax : iSearchLevelMax ;

	pWindow = Find( WIID_AUCTION_SEARCH_BT_MONEY_MIN, true) ;		// �ݾ� Min
	if( pWindow )	iSearchMoneyMin = atoi(pWindow->GetWindowText()) ;
	pWindow = Find( WIID_AUCTION_SEARCH_BT_MONEY_MAX, true) ;		// �ݾ� Max
	if( pWindow )	iSearchMoneyMax = atoi(pWindow->GetWindowText()) ;

	// SearchKey Clear & Copy
	m_pSearchKey->Clear() ;
	pWindow = Find( WIID_AUCTION_SEARCH_BT_NAME_EDIT, true) ;
	if( pWindow )	
		strcpy(m_pSearchKey->szName,  pWindow->GetWindowText() ) ;
	m_pSearchKey->iCategoryID = iSearchCategory ;
	m_pSearchKey->iMinLevel = iSearchLevelMin ;
	m_pSearchKey->iMaxLevel = iSearchLevelMax ;
	m_pSearchKey->iQuality = m_iSearchQuality ;
	m_pSearchKey->iMoneyMin = iSearchMoneyMin ;
	m_pSearchKey->iMoneyMax = iSearchMoneyMax ;
	return true ;
}



/**
	���� [����][�ﱸ]�� ������ �������� Ȯ���Ѵ�.
	- ����, �ﱸ ���ݺ��� ���� ���� �ݾ��� ������� Error
	@param SPAuctionAttr* pItemAttr : ��� ��ǰ����
	@param bool isBid : true(Bid), false(Spot)
 */
bool SPWindowAuction::CheckAuctionBidable(SPAuctionAttr* pItemAttr, bool isBid)
{
	INT64 iAuctionMoney = 0 ;
	INT64 iAuctionSale = 0 ;

	if( pItemAttr == NULL )
		return false ;

	if( isBid )
		iAuctionMoney = min(pItemAttr->GetNextBidPrice(), pItemAttr->GetSpotPrice()) ;		// ���� ���� �ݾ�
	else
		iAuctionMoney = pItemAttr->GetSpotPrice() ;

	// ���� ���� ������ ����/�ﱸ�� �������� ���� �ľ�
	if( pItemAttr->GetType() == AUCTION_TYPE_ELY_BY_CASH ) {		// CASH ��
		if( iAuctionMoney > (INT64)g_pkAuctionManager->GetPlayerCash() )	{
			if( g_pResourceManager->GetGlobalString(52000002) )		// Cash����
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000002) );
			return false ;
		}
	}
	else if( pItemAttr->GetType() == AUCTION_TYPE_ELY_BY_MILEAGE )	{	// MILIGE ��
		if( iAuctionMoney > (INT64)g_pkAuctionManager->GetPlayerMilige() )	{
			if( g_pResourceManager->GetGlobalString(52000053) )		// Point����  
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000053) );
			return false ;
		}
	}
	else	{		// ELY ��
		if( iAuctionMoney > g_pkAuctionManager->GetPlayerEly() )	{
			if( g_pResourceManager->GetGlobalString(52000001) )		// Ely����  
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000001) );
			return false ;
		}
	}

	// ��ǰ�� ���������� ���� ������ �ݾ���, �������Ѻ��� ū ��� ���� �Ұ�
	iAuctionSale = (INT64)pItemAttr->GetSellPoint() ;
	if( pItemAttr->GetType() == AUCTION_TYPE_ELY_BY_CASH || pItemAttr->GetType() == AUCTION_TYPE_ELY_BY_MILEAGE ) {		// Ely���� üũ
		if( (INT64)(g_pkAuctionManager->GetPlayerEly() + iAuctionSale) > MAX_MONEY )	{
			if( g_pResourceManager->GetGlobalString(52000090) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000090) );
			return false ;
		}
	}
	else if( pItemAttr->GetType() == AUCTION_TYPE_MILEAGE_BY_ELY )	{	// MILIGE ���� üũ
		if( (INT64)(g_pkAuctionManager->GetPlayerMilige() + iAuctionSale) > MAX_MILE )	{
			if( g_pResourceManager->GetGlobalString(52000091) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000091) );
			return false ;
		}
	}
	else if( pItemAttr->GetType() == AUCTION_TYPE_CASH_BY_ELY )	{	// CASH ���� üũ 
		if( (INT64)(g_pkAuctionManager->GetPlayerCash() + iAuctionSale) > MAX_CASH )	{
			if( g_pResourceManager->GetGlobalString(52000092) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000092) );
			return false ;
		}
	}

	// ��� �ð��� �����Ǿ����� ����/�ﱸ�� �� �� ����.
	if( pItemAttr->GetFinishTime() < 1 )	{
		if( g_pResourceManager->GetGlobalString(52000108) )		// ��Žð� ����
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000108) );
		return false ;
	}
	return true ;
}



/**
	���� ���õ� �޴��� ���� [�ϴ� ���ΰ˻�]�� �ٲ��� �Ѵ�.
	�ϴ� �޴������� ���ؼ� [�ƺ������]�� ������ �����ȴ�.
	@param int iCategory : ���� ī�װ�
	@param int iDetail	: ���� ����
	@param bool bInit	: �ʱ�ȭ ����
 */
void SPWindowAuction::SetSearchBottomMenu(int iCategory, int iDetail, bool bInit/*=true*/)
{
	SPWindow* pWindowItem	= NULL ;
	SPWindow* pWindowMoney	= NULL ;
	SPWindow* pMoneyIcon	= NULL ;
	SPWindow* pWindow ;
	SPWindowButton* pButton ;
	int iCategoryID = 0 ;
	if( iCategory > 0 && iDetail >= 0 )
		iCategoryID = m_stMenu[iCategory].vpDetail[iDetail]->iDetail_ID ;

	pWindowItem		= Find(WIID_AUCTION_SEARCH_BT_ITEM, true) ;
	pWindowMoney	= Find(WIID_AUCTION_SEARCH_BT_MONEY, true) ;
	pMoneyIcon		= Find(WIID_AUCTION_SEARCH_BT_MONEY_ICON, true) ;

	if( iCategoryID < 8000 )	{			// Item
		pWindowMoney->SetShowEnable(false) ;
		pWindowItem->SetShowEnable(true) ;
	}
	else if( iCategoryID == 8000 )	{		// Ely
		pWindowItem->SetShowEnable(false) ;
		pWindowMoney->SetShowEnable(true) ;
		pMoneyIcon->SPSendMessage(SPIM_SET_IMAGEINDEX, 0) ;
	}
	else if( iCategoryID == 9000 )	{		// Cash
		pWindowItem->SetShowEnable(false) ;
		pWindowMoney->SetShowEnable(true) ;
		pMoneyIcon->SPSendMessage(SPIM_SET_IMAGEINDEX, 1) ;
	}
	else if( iCategoryID == 10000 )	{		// Point
		pWindowItem->SetShowEnable(false) ;
		pWindowMoney->SetShowEnable(true) ;
		pMoneyIcon->SPSendMessage(SPIM_SET_IMAGEINDEX, 2) ;
	}

	// �ٲ�� �ʱ�ȭ �ȴ�.
	if( bInit )	{
		pWindow = Find(WIID_AUCTION_SEARCH_BT_LEVEL_MIN, true);		// Min Level
		if( pWindow )		{
			pWindow->SetWindowText("") ;
			pWindow->SetEnable(true) ;
		}
		pWindow = Find(WIID_AUCTION_SEARCH_BT_LEVEL_MAX, true);		// Max Level
		if( pWindow )		{
			pWindow->SetWindowText("") ;
			pWindow->SetEnable(true) ;
		}
		pWindow = Find(WIID_AUCTION_SEARCH_BT_NAME_EDIT, true);		// Search Name
		if( pWindow )		pWindow->SetWindowText("") ;
		pWindow = Find(WIID_AUCTION_SEARCH_BT_MONEY_MIN, true);		// Money Min
		if( pWindow )		pWindow->SetWindowText("") ;
		pWindow = Find(WIID_AUCTION_SEARCH_BT_MONEY_MAX, true);		// Money Max
		if( pWindow )		pWindow->SetWindowText("") ;
		m_bSearchUsable = false ;
		pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_BT_USEABLE_BTN, true) ;	// ��밡�ɾ�����
		if( pButton )		pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)FALSE);

		SPWindowComboBox* pComboBox = (SPWindowComboBox*)Find(WIID_AUCTION_SEARCH_BT_QUAL_COMBO, true);
		if( pComboBox)	{
			pComboBox->SetSelectNumber( 0 );
			pComboBox->AcceptSelectValueApply();
		}
		OnChangeSearchCombo(0, 0) ;
	}
	InitTabStop() ;

}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
/**
	���� ī�װ����ý�
*/
int SPWindowAuction::OnCategorySelect(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	int iSelCategory ;
	if( iID < WIID_AUCTION_SEARCH_MENU_TEXT )
		if( iID < WIID_AUCTION_SEARCH_MENU_ICON)
			iSelCategory = iID - WIID_AUCTION_SEARCH_MENU_BUTTON ;
		else
			iSelCategory = iID - WIID_AUCTION_SEARCH_MENU_ICON ;
	else
		iSelCategory = iID - WIID_AUCTION_SEARCH_MENU_TEXT ;

	SPWindowButton* pButton ;
	SPWindowStatic* pStatic ;
	pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_MENU_BUTTON+m_iPreShowPopup, true) ;	// �������� Check ����
	if( pButton )		pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)FALSE);
	pStatic = (SPWindowStatic*)Find(WIID_AUCTION_SEARCH_MENU_TEXT+m_iPreShowPopup, true) ;
	if( pStatic )		pStatic->SetFontColor( RGBA(143, 99, 99, 255) );


	pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_MENU_BUTTON+iSelCategory, true) ;		// ���缱�� check
	if( pButton )		pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)TRUE);
	pStatic = (SPWindowStatic*)Find(WIID_AUCTION_SEARCH_MENU_TEXT+iSelCategory, true) ;
	if( pStatic )		pStatic->SetFontColor( RGBA(255, 255, 255, 255) );

	SetPopMenu(iSelCategory) ;

	return 0 ;
}

/**
	�˾� �޴����� ���� ���ý�
*/
int SPWindowAuction::OnDetailSelect(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	SPWindowRowUNIT* pWindowRowUnit;
	HidePopMenu() ;

	int iIndex = iID - WIID_AUCTION_POPUP_LIST ;

	// ���� ������ �ǵ�����.
	if( m_iSelectedCategory == m_iPreShowPopup && m_iSelectedDetail >= 0 )	{
		pWindowRowUnit = m_vpPopMenu[m_iSelectedDetail] ;
		pWindowRowUnit->SetWndState(WND_STATE_NORMAL) ;
	}
	m_iSelectedCategory = m_iPreShowPopup ;		// ���õ� ī�װ� ����

	// m_vpPopMenu
	int iSelectIndex = 0 ;
	SPWindowRowUNIT* pRow ;
	std::vector<SPWindowRowUNIT*>::iterator Iter = m_vpPopMenu.begin() ;
	for( ; Iter != m_vpPopMenu.end(); ++Iter)
	{
		pRow = (*Iter) ;
		if( (*Iter)->GetInstanceID() == iID )
		{
			m_iSelectedDetail = iSelectIndex ;
			//ErrorFLogs->Error_Log("Detail Select [%d]", m_iSelectedDetail) ;
			SetSelectedTitle() ;
			SetSearchBottomMenu(m_iSelectedCategory, m_iSelectedDetail) ;
			return 1 ;
		}
		++iSelectIndex;
	}
	
	return 0 ;
}


int SPWindowAuction::OnCategoryIconCursorON(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	SPWindowButton* pButton = NULL ;
	int iIndex = iID - WIID_AUCTION_SEARCH_MENU_ICON ;
	pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_MENU_BUTTON+iIndex, true) ;
	if(pButton)
		pButton->SPSendMessage(SPIM_CURSOR_ENTER) ;
	return 0 ;
}
int SPWindowAuction::OnCategoryIconCursorOUT(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	SPWindowButton* pButton = NULL ;
	int iIndex = iID - WIID_AUCTION_SEARCH_MENU_ICON ;
	pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_MENU_BUTTON+iIndex, true) ;
	if(pButton)
		pButton->SPSendMessage(SPIM_CURSOR_OUT) ;
	return 0 ;
}


int SPWindowAuction::OnCategoryTextCursorON(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	SPWindowButton* pButton = NULL ;
	int iIndex = iID - WIID_AUCTION_SEARCH_MENU_TEXT ;
	pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_MENU_BUTTON+iIndex, true) ;
	if(pButton)
		pButton->SPSendMessage(SPIM_CURSOR_ENTER) ;
	return 0 ;
}
int SPWindowAuction::OnCategoryTextCursorOUT(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	SPWindowButton* pButton = NULL ;
	int iIndex = iID - WIID_AUCTION_SEARCH_MENU_TEXT ;
	pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_MENU_BUTTON+iIndex, true) ;
	if(pButton)
		pButton->SPSendMessage(SPIM_CURSOR_OUT) ;

	return 0 ;
}


/**
	�˻�����Ʈ [����] Ŭ��
*/
int SPWindowAuction::OnSearchListBidClick(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	SPAuctionAttr* pItemAttr = NULL ;
	HidePopMenu() ;
	int iSelectRow = (iID - WIID_AUCTION_SEARCH_LIST) / AUCTION_MAX_LIST_ITEM ;
	if( iSelectRow < 0 || iSelectRow > AUCTION_SEARCH_LIST )
		return 0 ;

	if( iSelectRow < AUCTION_SEARCH_LIST && m_pWindowSearchList[iSelectRow]->GetAuctionAttr() == NULL )	{
		ErrorFLogs->Error_Log("SPWindowAuction::OnSearchListBidClick[%d] is NoDATA", iSelectRow ) ;
		return 0 ;
	}
	else	{
		pItemAttr = m_pWindowSearchList[iSelectRow]->GetAuctionAttr() ;
		if( CheckAuctionBidable(pItemAttr, true) == false )		{
			m_pWindowSearchList[iSelectRow]->SetFinishTime() ;
			m_pWindowSearchList[iSelectRow]->UpdateBidButtonEnable() ;
			return 0 ;
		}

		if( pItemAttr->GetType() == AUCTION_TYPE_CASH_BY_ELY || pItemAttr->GetType() == AUCTION_TYPE_MILEAGE_BY_ELY )
			m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_FEE_MSG, AUCTION_MSG_BID, (LPARAM)pItemAttr) ;
		else
			m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_BID_MSG, AUCTION_MSG_BID, (LPARAM)pItemAttr);
	}

	return 0 ;
}


/**
	�˻� ����Ʈ [��ñ���] Ŭ��
*/
int SPWindowAuction::OnSearchListSpotClick(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	SPAuctionAttr* pItemAttr = NULL ;
	HidePopMenu() ;

	int iSelectRow = (iID - WIID_AUCTION_SEARCH_LIST) / AUCTION_MAX_LIST_ITEM ;
	if( iSelectRow < 0 || iSelectRow > AUCTION_SEARCH_LIST )
		return 0 ;

	int iSearchIndex = m_iSearchCurPage * AUCTION_SEARCH_LIST ;
	if( iSelectRow < AUCTION_SEARCH_LIST && m_pWindowSearchList[iSelectRow]->GetAuctionAttr() == NULL )	{
		ErrorFLogs->Error_Log("SPWindowAuction::OnSearchListSpotClick[%d] is NoDATA", iSelectRow ) ;
		return 0 ;
	}
	else	{
		pItemAttr = m_pWindowSearchList[iSelectRow]->GetAuctionAttr() ;
		if( CheckAuctionBidable(pItemAttr, false) == false )	{
			m_pWindowSearchList[iSelectRow]->SetFinishTime() ;
			m_pWindowSearchList[iSelectRow]->UpdateBidButtonEnable() ;
			return 0 ;
		}

		if( pItemAttr->GetType() == AUCTION_TYPE_CASH_BY_ELY || pItemAttr->GetType() == AUCTION_TYPE_MILEAGE_BY_ELY )
			m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_FEE_MSG, AUCTION_MSG_SPOT, (LPARAM)pItemAttr) ;
		else
			m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_BID_MSG, AUCTION_MSG_SPOT, (LPARAM)pItemAttr);
	}
	

	return 0 ;
}


/**
	�˻� ����Ʈ ���� Ŭ��
*/
int SPWindowAuction::OnSearchListClick(unsigned int iID, WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;

	int iSelectRow = (iID - WIID_AUCTION_SEARCH_LIST) / AUCTION_MAX_LIST_ITEM ;
	//ErrorFLogs->Error_Log("SPWindowAuction::OnSearchListClick[%d]", iSelectRow) ;

	return 0 ;
}



/**
	�������� ������ ���
*/
int SPWindowAuction::OnSearchListPage(WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;

	int iPage = (int)wParam ;
	int iSelectBundle = (int)lParam ;
	int iSelectPage = iPage ;
	//ErrorFLogs->Error_Log("Search Select Page[%d]->[%d + %d*10]", m_iSearchCurPage, iPage, iSelectBundle) ;


	// �ش� �������� �����͸� ������ ������ Manager���� ��������
	// ������ ��Ŷ�� ������ ������ ��û�Ѵ�.
	if( g_pkAuctionManager->GetAuctionSearchArchive()->HasPageInfo(iSelectPage) )
	{
		m_iSearchCurPage = iSelectPage ;
		//ErrorFLogs->Error_Log("Request Search List[%d]", m_iSearchCurPage) ;
		ShowSearchList(m_iSearchCurPage) ;		
	}
	else
	{
		// ������ ��û
		m_iSearchCurPage = iSelectPage ;
		int iRequestIndex = iSelectPage * AUCTION_SEARCH_LIST ;
		m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000079)) ;
		g_pkAuctionManager->SendAuctionSearchNext(iRequestIndex, m_pSuccessKey) ;
	}
	return 0 ;
}


/**
	������ ǰ���� �޺����� ������ ���
	��ü	: RGBA(0, 0, 0, 255)
	���ϱ�	: RGBA(0, 0, 0, 255)
	�ϱ�	: RGBA(44, 143, 53, 255)
	�߱�	: RGBA(26, 155, 209, 255)
	���	: RGBA(222, 146, 27, 255)
	�ֻ��	: RGBA(255, 0, 0, 255)
	�����	: RGBA(0, 0, 255, 255)
*/
int SPWindowAuction::OnChangeSearchCombo(WPARAM wParam, LPARAM lParam)
{
	DWORD dwColor ;
	m_iSearchQuality = (int)wParam;

	HidePopMenu() ;
	switch(m_iSearchQuality ){
		case 1:		dwColor = RGBA(0, 0, 0, 255) ;
			break ;
		case 2:		dwColor = RGBA(44, 143, 53, 255) ;
			break ;
		case 3:		dwColor = RGBA(26, 155, 209, 255) ;
			break ;
		case 4:		dwColor = RGBA(222, 146, 27, 255) ;
			break ;
		case 5:		dwColor = RGBA(255, 0, 0, 255) ;
			break ;
		case 6:		dwColor = RGBA(0, 0, 255, 255) ;
			break ;
		default:	dwColor = RGBA(0, 0, 0, 255) ;
			break ;
	}

	// �޺��� ��� Text ���� �ٲ��� �Ѵ�.
	SPWindowComboBox* pComboBox = (SPWindowComboBox*)Find(WIID_AUCTION_SEARCH_BT_QUAL_COMBO, true);
	if( pComboBox)	
		pComboBox->SetEditBoxTextColor(D3DXCOLOR(dwColor)) ;

	return 0 ;
}


/**
	[��밡���� ����] üũ �ڽ�
*/
int SPWindowAuction::OnSearchUsableCheck( WPARAM wParam, LPARAM lParam )
{
	SPWindowButton* pButton ;
	SPWindow*		pWindow;
	pButton = (SPWindowButton*)Find(WIID_AUCTION_SEARCH_BT_USEABLE_BTN, true) ;		// ��밡�� ���� ��ư
	int iMyLevel = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetLevel() ;
	char szMyLevel[4] ;
	_stprintf(szMyLevel, "%d", iMyLevel) ;	

	HidePopMenu() ;
	if( m_bSearchUsable )	{
		m_bSearchUsable = false ;
		if( pButton )		pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)m_bSearchUsable);
		pWindow = Find(WIID_AUCTION_SEARCH_BT_LEVEL_MIN, true);		// Min Level
		if( pWindow )		{
			pWindow->SetWindowText("") ;
			pWindow->SetEnable(!m_bSearchUsable) ;
		}
		pWindow = Find(WIID_AUCTION_SEARCH_BT_LEVEL_MAX, true);		// Max Level
		if( pWindow )		{
			pWindow->SetWindowText("") ;
			pWindow->SetEnable(!m_bSearchUsable) ;
		}
	}
	else	{
		m_bSearchUsable = true ;
		if( pButton )		pButton->SPSendMessage(SPIM_BTN_SELECT, (WPARAM)m_bSearchUsable);
		pWindow = Find(WIID_AUCTION_SEARCH_BT_LEVEL_MIN, true);		// Min Level
		if( pWindow )		{
			pWindow->SetWindowText("1") ;
			pWindow->SetEnable(!m_bSearchUsable) ;
		}
		pWindow = Find(WIID_AUCTION_SEARCH_BT_LEVEL_MAX, true);		// Max Level
		if( pWindow )		{
			pWindow->SetWindowText(szMyLevel) ;
			pWindow->SetEnable(!m_bSearchUsable) ;
		}
	}

	return 1;
}


/**
	Edit Window�� ��Ŀ���� ������ ������ ����Ű�� �ߵ��ȴ�.
*/
int SPWindowAuction::OnSearchNameSetFocus( WPARAM wParam, LPARAM lParam )
{
	g_pInterfaceManager->SetKeyInput( TRUE );
	return 1;
}
int SPWindowAuction::OnSearchNameKillFocus( WPARAM wParam, LPARAM lParam )
{
	g_pInterfaceManager->SetKeyInput( FALSE );
	return 1;
}




/**
	[������ �˻�] ��ư
*/
int SPWindowAuction::OnSearchItem(WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;

	m_pSearchTimer->Start(0, (float)AUCTION_SEARCH_TIMER) ;	// SearchTimer Set (3.0f Seconds)
	m_pSearchButton->SetEnable(false) ;					// SearchButton Disable

	
	if( UpdateSearchKey() )		{
		if( m_pSearchKey->iMinLevel > m_pSearchKey->iMaxLevel )	{
			if( g_pResourceManager->GetGlobalString(52000011) )
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000011) );		
		}
		else	{
			SetShowSearchGuide(false) ;									// Search Guide �����
			m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000079)) ;
			g_pkAuctionManager->SendAuctionSearch(m_pSearchKey) ;		// ���� Setting Search Key
		}
	}

	return 0 ;
}



/**
	�޴������� Sort
*/
int SPWindowAuction::OnSortSearchQuality(WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;
	//ErrorFLogs->Error_Log("SPWindowAuction::OnSortSearchQuality") ;

	// Send Sort
	if( m_pSuccessKey->iCategoryID > 1 && g_pkAuctionManager->GetAuctionSearchArchive()->GetListCount() > 0 )	{
		// Clear Current Data
		m_iSearchCurPage = 0 ;

		m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000079)) ;
		g_pkAuctionManager->GetAuctionSearchArchive()->SetSort(AUCTION_SORT_QUALITY, false) ;
		g_pkAuctionManager->SendAuctionSearchSort(m_pSuccessKey) ;
		UpdateSortArrow(AUCTION_SEARCH_TAB) ;
	}
	

	return 0 ;
}

int SPWindowAuction::OnSortSearchLevel(WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;
	//ErrorFLogs->Error_Log("SPWindowAuction::OnSortSearchLevel") ;

	// Send Sort (�Ӵϴ� Sort���� �ʴ´�.)
	if( m_pSuccessKey->iCategoryID > 1 && CHECK_AUCTION_ITEM_CATEGORY(m_pSuccessKey->iCategoryID)  && g_pkAuctionManager->GetAuctionSearchArchive()->GetListCount() > 0 )	{
		// Clear Current Data
		m_iSearchCurPage = 0 ;

		m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000079)) ;
		g_pkAuctionManager->GetAuctionSearchArchive()->SetSort(AUCTION_SORT_ITEM_LV, false) ;
		g_pkAuctionManager->SendAuctionSearchSort(m_pSuccessKey) ;
		UpdateSortArrow(AUCTION_SEARCH_TAB) ;
	}
	return 0 ;
}

int SPWindowAuction::OnSortSearchDuration(WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;
	//ErrorFLogs->Error_Log("SPWindowAuction::OnSortSearchDuration") ;

	// Send Sort (�Ӵϴ� Sort���� �ʴ´�.)
	if( m_pSuccessKey->iCategoryID > 1  && CHECK_AUCTION_ITEM_CATEGORY(m_pSuccessKey->iCategoryID)  && g_pkAuctionManager->GetAuctionSearchArchive()->GetListCount() > 0 )	{
		// Clear Current Data
		m_iSearchCurPage = 0 ;

		m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000079)) ;
		g_pkAuctionManager->GetAuctionSearchArchive()->SetSort(AUCTION_SORT_ITEM_OPTPOINT, false) ;
		g_pkAuctionManager->SendAuctionSearchSort(m_pSuccessKey) ;
		UpdateSortArrow(AUCTION_SEARCH_TAB) ;
	}
	return 0 ;
}

int SPWindowAuction::OnSortSearchFinish(WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;
	//ErrorFLogs->Error_Log("SPWindowAuction::OnSortSearchFinish") ;

	// Send Sort
	if( m_pSuccessKey->iCategoryID > 1  && g_pkAuctionManager->GetAuctionSearchArchive()->GetListCount() > 0 )	{
		// Clear Current Data
		m_iSearchCurPage = 0 ;

		m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000079) ) ;
		g_pkAuctionManager->GetAuctionSearchArchive()->SetSort(AUCTION_SORT_DURATION, false) ;
		g_pkAuctionManager->SendAuctionSearchSort(m_pSuccessKey) ;
		UpdateSortArrow(AUCTION_SEARCH_TAB) ;
	}
	return 0 ;
}

int SPWindowAuction::OnSortSearchPrice(WPARAM wParam, LPARAM lParam)
{
	HidePopMenu() ;
	//ErrorFLogs->Error_Log("SPWindowAuction::OnSortSearchPrice") ;

	// Send Sort
	if( m_pSuccessKey->iCategoryID > 1  && g_pkAuctionManager->GetAuctionSearchArchive()->GetListCount() > 0 )	{
		// Clear Current Data
		m_iSearchCurPage = 0 ;

		m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_SHOW, 0, (LPARAM)g_pResourceManager->GetGlobalString(52000079)) ;
		g_pkAuctionManager->GetAuctionSearchArchive()->SetSort(AUCTION_SORT_PRICE, false) ;
		g_pkAuctionManager->SendAuctionSearchSort(m_pSuccessKey) ;
		UpdateSortArrow(AUCTION_SEARCH_TAB) ;
	}
	return 0 ;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
/**
	����Ʈ ������ ó��
	Search�� ��� ����Ʈ/Page������ �ʱ�ȭ �ؾ��ϰ�
	GetNext�� ��� ����Ʈ�� �ʱ�ȭ������ Page������ �����Ѵ�.
	@param WPARAM wParam : Search���� (1�̸� Search, Sort, 0�̸� GetNext)
	@param WPARAM wParam : PageUpdate ����(1�̸� MaxPageInfo Update)
*/
int SPWindowAuction::OnReceiveAuctionSearchList(WPARAM wParam, LPARAM lParam)
{
	SPAuctionArchive* pArchive ;
	//std::vector<SPAuctionAttr*> vShowList ;
	int isSearch = (int)wParam ;
	int isPageUPdate = (int)lParam ;

	m_pAuctionMsg->SPSendMessage(SPIM_AUCTION_WAIT_CLOSE, 0, 0) ;
	pArchive = g_pkAuctionManager->GetAuctionSearchArchive() ;
	if( pArchive == NULL )	{
		ErrorFLogs->Error_Log("SPWindowAuction::OnReceiveAuctionSearchList Archive is NULL") ;
		return 0 ;
	}

	if( isSearch )	{
		m_pSuccessKey->Copy(m_pSearchKey) ;		// SearchKey Copy
		UpdateSortArrow(AUCTION_SEARCH_TAB) ;	// Sort Arrow Update
	}

	// Page Setting
	int iMaxPage = pArchive->GetTotalPageCount() ;
	if( iMaxPage < 1 )		{
		//  ����Ʈ�� ������ [52000011]�˻��Ͻ� �������� �������� �ʽ��ϴ�.
		if( g_pResourceManager->GetGlobalString(52000011) )
			g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)g_pResourceManager->GetGlobalString(52000011) );
		iMaxPage = 1 ;
	}
	SPWindowPageSelect* pkPageSelect ;
	pkPageSelect = (SPWindowPageSelect*)Find(WIID_AUCTION_SEARCH_PAGE, true);
	if( pkPageSelect )	{
		if( isSearch )	{
			m_iSearchCurPage = 0 ;
			pkPageSelect->SetMaxPageInfo(iMaxPage) ;		// ���� ������ ������ ����(�ʱ�ȭ ����)
		}
		else if( isPageUPdate )
			pkPageSelect->SetMaxPageInfo(iMaxPage, false) ;		// ���� ������ ������ ����(������Ʈ)
		pkPageSelect->SetSelectPage((m_iSearchCurPage%10)) ;
		//ErrorFLogs->Error_Log("Set Auction Search Page[%d / %d]", m_iSearchCurPage, iMaxPage) ;
	}

	if( IsShow() && m_iSelectedTab == AUCTION_SEARCH_TAB )
	{
		// List Setting
		ShowSearchList(m_iSearchCurPage) ;
		SetSearchSortButton(m_pSuccessKey->iCategoryID) ;
		return 1 ;
	}

	return 0 ;
}



