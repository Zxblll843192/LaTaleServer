
#include <vector>
#include <string>

#include "SPCommon.h"
#include "SPUtil.h"

#include "SPMainGameDEF.H"
#include "SPGameObjectDEF.h"

#include "SPResourceDef.h"
#include "SPResourceManager.h"

#include "SPSubGameManager.h"
#include "SPGameObject.h"
#include "SPManager.h"
#include "SPMouseCursor.h"
#include "SPIMEPool.h"
#include "SPWindowDEF.h"
#include "SPInterfaceManager.h"

#include "SPWindow.h"
#include "SPWindowButton.h"
#include "SPWindowStatic.h"
#include "SPWindowEdit.h"

#include "Packet.h"
#include "SPNetworkManager.h"

#include "SPItemAttr.h"
#include "SPItemStatus.h"
#include "SPItem.h"
#include "SPItemCluster.h"			//[2005/6/16] - jinhee

#include "SPEventDEF.h"
#include "SPEventNpcHandler.h"
#include "SPEventManager.h"

#include "SPMainGameDEF.H"
#include "SPSubGameManager.h"
#include "SPMainGameManager.h"
#include "SPMouseCursor.h"
#include "SPWindowDEF.h"
#include "SPInterfaceManager.h"
#include "SPGOBClusterDef.h"
#include "SPAvatarModelUnitDef.h"
#include "SPGOBModel.h"
#include "SPGOBModelUnit.h"
#include "SPMonsterModelUnit.h"
#include "SPAvatarModelUnit.h"
#include "SPGOBCluster.h"
#include "SPGameObject.h"
#include "SPGOBStatus.h"
#include "SPGOBCoordPhysics.h"
#include "SPGOBModelUnit.h"			
#include "SPPlayerEquipInfo.h"
#include "SPGOBStatus.h"			
#include "SPPlayerInvenArchive.h"	
#include "SPPlayerStatusModel.h"	
#include "SPPlayerEquipInfo.h"
#include "SPItemAttr.h"
#include "SPItemStatus.h"
#include "SPPlayer.h"
#include "SPGOBManager.h"

#include "SPMainGameManager.h"

#include "SPCheckManager.h"
#include "SPLocalizeManager.h"

#include "SPWindowNpcTrade.h"

#include "SPUtil.h"

#include "SPDebug.h"

SPWindowNpcTrade::SPWindowNpcTrade(INSTANCE_ID InstanceID, int iX, int iY, int iCX, int iCY, SPWindow* pParent /*= NULL*/)
: SPWindow(WNDID_SHOPTRADE, InstanceID, iX, iY, iCX, iCY, pParent)
{
	Init();
}


SPWindowNpcTrade::~SPWindowNpcTrade()
{
	Clean();
}

void SPWindowNpcTrade::Init()
{
	m_pNpcShop = NULL;
	m_iSelectItemIndex = -1;
	m_iViewItemIndex = -1;
	m_iBuyCount = 1;
	m_iPage = 1;
	m_iMaxPage = 1;
	ZeroMemory(m_szPage, 64);
	ZeroMemory(m_szBuyCount, 64);

	m_bSend = false;

	//Load Texture Image
	std::string strTextureFile = "";
	strTextureFile = "DATA/INTERFACE/CONCEPT/UI100.PNG";
	g_pVideo->GetTextureMgr()->LoadTexture(strTextureFile.c_str(), &m_pDisable);

	SetRect(&m_rtSrcDisable, 434 , 37 , 436 , 39);
	SetRect(&m_rtMarkSrc[0], 479, 152, 511, 184);		//ICON_MARK_LOCK
	SetRect(&m_rtMarkSrc[1], 479, 185, 511, 217);		//ICON_MARK_FASHION
	SetRect(&m_rtMarkSrc[2], 479, 339, 511, 371);		//ICON_MARK_EVENT
	SetRect(&m_rtMarkSrc[3], 479, 372, 511, 404);		//ICON_MARK_FANCY

	CreateSubControl();	

	m_PickUpItem.Clear();

	//Hide();
}


void SPWindowNpcTrade::CreateSubControl()
{
	//��Ʈ��
	SPWindow* pStatic = NULL;
	SPWindow* pCenter = NULL;
	SPWindow* pMiddle = NULL;
	SPWindowButton* pButton;	

	pStatic = new SPWindowStatic(WIID_NPCTRADE_TOP, 0, 0, 319, 4, this);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 1,	16);
	pStatic->Show();
	pStatic = NULL;

	pCenter = new SPWindowStatic(WIID_NPCTRADE_CENTER, 0, 4, 319, 469, this);
	pCenter->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 1,	22);
	pCenter->SetSrcSize(319, 2);
	pCenter->Show();

	pStatic = new SPWindowStatic(WIID_NPCTRADE_BOTTOM, 0, 473, 319, 4, this);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 1,	26);
	pStatic->Show();
	pStatic = NULL;

	pStatic = new SPWindowStatic(WIID_NPCTRADE_TITLE, 10, 7 - 4, 57, 15, pCenter);
	pStatic->SetImage		("DATA/INTERFACE/CONCEPT/UI103.PNG", 59,	360); //�Ϲ�
	pStatic->Show();
	pStatic = NULL;

	pButton = new SPWindowButton(WIID_NPCTRADE_EXIT, 298, 9 - 4, 12, 12, pCenter);
	pButton->SetImage		("DATA/INTERFACE/CONCEPT/UI103.PNG", 301,	321); //�Ϲ�
	pButton->SetImageHit	("DATA/INTERFACE/CONCEPT/UI103.PNG", 314,	321); //on	
	pButton->SetImagePush	("DATA/INTERFACE/CONCEPT/UI103.PNG", 327,	321); //push
	pButton->SetImageDisable("DATA/INTERFACE/CONCEPT/UI103.PNG", 340,	321); //disable
	pButton = NULL;

	pMiddle = new SPWindowStatic(WIID_NPCTRADE_MIDDLE, 2, 27 - 4, 315, 419, pCenter);
	pMiddle->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 493,	477);
	pMiddle->SetSrcSize(6, 6);
	pMiddle->Show();

	SPWindowStatic* pStaticWnd = NULL;
	pStaticWnd = new SPWindowStatic(WIID_NPCTRADE_LIST_IMG_BASE, 10 - 2, 34 - 27, 220, 15, pMiddle);
	pStaticWnd->SetWindowType(WND_TYPE_LEFTBASE);
	pStaticWnd->SetImageNormalHead	("DATA/INTERFACE/CONCEPT/UI103.PNG", 347, 245, 349, 260);
	pStaticWnd->SetImageNormalBody	("DATA/INTERFACE/CONCEPT/UI103.PNG", 351, 245, 353, 260);
	pStaticWnd->SetImageNormalTail	("DATA/INTERFACE/CONCEPT/UI103.PNG", 355, 245, 357, 260);
	pStaticWnd->Show();
	pStaticWnd = NULL;

	pStatic = new SPWindowStatic(WIID_NPCTRADE_LIST_IMG, 75 - 2, 36 - 27, 90, 11, pMiddle);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 355,	223);
	pStatic->Show();
	pStatic = NULL;

	pStaticWnd = new SPWindowStatic(WIID_NPCTRADE_PRICE_IMG_BASE, 232 - 2, 34 - 27, 77, 15, pMiddle);
	pStaticWnd->SetWindowType(WND_TYPE_LEFTBASE);
	pStaticWnd->SetImageNormalHead	("DATA/INTERFACE/CONCEPT/UI103.PNG", 347, 245, 349, 260);
	pStaticWnd->SetImageNormalBody	("DATA/INTERFACE/CONCEPT/UI103.PNG", 351, 245, 353, 260);
	pStaticWnd->SetImageNormalTail	("DATA/INTERFACE/CONCEPT/UI103.PNG", 355, 245, 357, 260);
	pStaticWnd->Show();
	pStaticWnd = NULL;

	pStatic = new SPWindowStatic(WIID_NPCTRADE_PRICE_IMG, 260 - 2, 36 - 27, 21, 11, pMiddle);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 424,	211);
	pStatic->Show();
	pStatic = NULL;

	
	//�ߴ�	
	//int	iSkinY[TRADE_PAGE] = {58-27, 94-27, 103-27, 166-27, 202-27, 238-27, 274-27, 310-27, 346-27, 382-27};	//���, �����۸�, ������ ����
	int iSkinY = 58 - 27;
	int iCashY[TRADE_PAGE] = {59-42, 94-77, 129-112, 164-147, 199-182, 234-217};	//����
	for(int i = 0 ; i < TRADE_PAGE ; i++) {
		iSkinY = (58 - 27) + (36 * i);
		
		SPWindow* pSkin = NULL;

		//�ٴ� ��Ų
		pSkin = new SPWindowStatic(WIID_NPCTRADE_ITEM_SKIN + i, 2, iSkinY, 307, 32, pMiddle);		
		pSkin->Show();		

		//��ư ó��
		pButton = new SPWindowButton(WIID_NPCTRADE_ITEM_BUTTON + i, 0, 0, 319-4, 32, pSkin);		
		pButton->Show();
		m_pButton[i] = pButton;
		pButton = NULL;

		m_pSkin[i] = new SPWindowStatic(WIID_NPCTRADE_ITEM_SEL + i, 0, 0, 307, 32, pSkin);
		m_pSkin[i]->SetWindowType(WND_TYPE_LEFTBASE);
		m_pSkin[i]->SetImageNormalHead	("DATA/INTERFACE/CONCEPT/UI103.PNG", 258, 407, 260, 439);
		m_pSkin[i]->SetImageNormalBody	("DATA/INTERFACE/CONCEPT/UI103.PNG", 262, 407, 264, 439);
		m_pSkin[i]->SetImageNormalTail	("DATA/INTERFACE/CONCEPT/UI103.PNG", 266, 407, 268, 439);
		m_pSkin[i]->Show();		

		pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_GRID + i, 10, 0, 32, 32, pSkin);
		pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 203, 408);
		pStatic->Show();
		pStatic = NULL;

		//������ ������
		//pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_ICON + i, 6, iSkinY[i], 32, 32, pSkin);
		pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_ICON + i, 10, 0, 32, 32, pSkin);		
		pStatic->Show();
		m_pIcon[i] = pStatic;
		m_pIcon[i]->GetWindowRect(m_rtStack[i]);
		pStatic = NULL;
		
		m_iStack[i] = 0;
		m_bAble[i] = true;
		m_iMark[i] = ICON_MARK_NULL;
	
		//�̸�
		//pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_NAME + i, 40, iSkinY[i], 115, 16, pSkin);
		pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_NAME + i, 50, 10, 178, 12, pSkin);
		pStatic->SetFormat(DT_LEFT | DT_VCENTER);
		pStatic->SetTextPeriod(true);
		//pStatic->SetWindowText("�����۸�");
		pStatic->Show();
		m_pName[i] = pStatic;
		pStatic = NULL;
		
		//��
		//pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_CASH + i, 63, iCashY[i], 92, 16, pSkin);
		pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_CASH + i, 230, 10, 56, 12, pSkin);
		pStatic->SetFormat(DT_RIGHT | DT_VCENTER);
		pStatic->SetWindowText("123456");
		pStatic->Show();
		//pStatic->SetFontColor(RGBA(255, 255, 255, 255));
		pStatic->SetFontColor(RGBA(0, 0, 0, 255));
		m_pCash[i] = pStatic;
		pStatic = NULL;	

		//Ely Image
		pStatic = new SPWindowStatic(WIID_NPCTRADE_ITEM_ELY_IMG + i, 290, 14, 17, 5, pSkin);
		pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 494, 506);
		pStatic->Show();
		pStatic = NULL;
	}
	

	//�ϴ�
	//������ ����
	pButton = new SPWindowButton(WIID_NPCTRADE_PAGEDOWN, 126 - 2 , 424 - 27, 7, 11, pMiddle);
	pButton->SetImage		("DATA/INTERFACE/CONCEPT/UI103.PNG", 238,	378); //�Ϲ�
	pButton->SetImageHit	("DATA/INTERFACE/CONCEPT/UI103.PNG", 246,	378); //on	
	pButton->SetImagePush	("DATA/INTERFACE/CONCEPT/UI103.PNG", 254,	378); //push
	pButton->SetImageDisable("DATA/INTERFACE/CONCEPT/UI103.PNG", 262,	378); //disable
	m_pPageDown = pButton;
	pButton->Show();
	pButton = NULL;

	//������ ǥ��
	pStatic = new SPWindowStatic(WIID_NPCTRADE_PAGE,	136 - 2, 422 - 27, 48, 14, pMiddle);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 226,	345);
	pStatic->SetFontColor(RGBA(255, 255, 255, 255));
	pStatic->SetFormat(DT_CENTER | DT_VCENTER);
	pStatic->SetWindowText(" / ");
	m_pPageInfo = pStatic;
	pStatic->Show();
	pStatic = NULL;

	//������ ����
	pButton = new SPWindowButton(WIID_NPCTRADE_PAGEUP, 188 - 2 , 424 - 27, 7, 11, pMiddle);
	pButton->SetImage		("DATA/INTERFACE/CONCEPT/UI103.PNG", 269,	378); //�Ϲ�
	pButton->SetImageHit	("DATA/INTERFACE/CONCEPT/UI103.PNG", 277,	378); //on	
	pButton->SetImagePush	("DATA/INTERFACE/CONCEPT/UI103.PNG", 285,	378); //push
	pButton->SetImageDisable("DATA/INTERFACE/CONCEPT/UI103.PNG", 293,	378); //disable
	m_pPageUp = pButton;
	pButton->Show();
	pButton = NULL;

	pStatic = new SPWindowStatic(WIID_USER_ELY_TEXT_IMG, 10 - 2, 456 - 27, 34, 11, pMiddle);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 301,	378);
	pStatic->Show();
	pStatic = NULL;

	pStatic = new SPWindowStatic(WIID_USER_ELY, 50 - 2, 454 - 27, 121, 14, pMiddle);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 104, 345);
	pStatic->SetFontColor(RGBA(143, 99, 99, 255));
	pStatic->SetFormat(DT_RIGHT | DT_VCENTER);
	pStatic->Show();
	m_pUserEly = pStatic;
	pStatic = NULL;

	pStatic = new SPWindowStatic(WIID_USER_ELY_IMG, 175 - 2, 460 - 27, 17, 5, pMiddle);
	pStatic->SetImage("DATA/INTERFACE/CONCEPT/UI103.PNG", 494, 506);
	pStatic->Show();
	pStatic = NULL;

	//���� ��ư
	pButton = new SPWindowButton(WIID_NPCTRADE_BUY, 241 - 2, 452 - 27, 68, 17, pMiddle);
	pButton->SetImage		("DATA/INTERFACE/CONCEPT/UI103.PNG", 70,	215); //�Ϲ�
	pButton->SetImageHit	("DATA/INTERFACE/CONCEPT/UI103.PNG", 70,	233); //on	
	pButton->SetImagePush	("DATA/INTERFACE/CONCEPT/UI103.PNG", 70,	251); //push
	pButton->SetImageDisable("DATA/INTERFACE/CONCEPT/UI103.PNG", 70,	269); //disable
	m_pBuy = pButton;
	pButton->Show();
	pButton = NULL;
}


void SPWindowNpcTrade::Clean()
{
	SAFE_RELEASE(m_pDisable);
	m_pDisable = NULL;

	SPWindow::Clean();
}


void SPWindowNpcTrade::Show(bool bWithChild)
{
	//����� ���� ���� ���� �Ǹ� ������ ����Ʈ�� ������Ʈ �Ѵ�
	m_iMaxPage = 1;
	m_iPage = 1;
	
	SPWindow::Show(bWithChild);
}


void SPWindowNpcTrade::Process(float fTime)
{	
	if(m_bShow && m_pUserEly) {
		//g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValueEX()
		if( g_pGOBManager->GetLocalPlayer() ) {
			//itoa(g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValueEX(STATUS_EX_ELY), m_szEly, 10);
			m_pUserEly->SetWindowText(ConvertMoneyToString(g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValueEX(STATUS_EX_ELY)));
		}
		else
			return;

		//m_pMessage->SetWindowText(m_szEly);		
	}
	SPWindow::Process(fTime);
}


void SPWindowNpcTrade::Render(float fTime)
{	
	if(IsShow() == false) return;	// by metalgeni ���ϵ� �����쵵 �����ϸ� �ȵ˴ϴ�..	

	SPWindow::Render(fTime);

	for(int i = 0; i < TRADE_PAGE; i++) {
		if(m_pDisable) {
			RECT rtRect;
			m_pIcon[i]->GetWindowRect(rtRect);
			
			if(m_bAble[i] == false) {				//������ ���� ��¦ ��Ȱ��ȭ				
				m_pDisable->RenderTexture(&rtRect, &m_rtSrcDisable);
			}

			if(m_iMark[i] > ICON_MARK_NULL) {				
				m_pDisable->RenderTexture(&rtRect, &m_rtMarkSrc[ (m_iMark[i] - 1) ]);
			}
		}

		//Stack Count Local ǥ��
		if(m_iStack[i] > 9) {
			RECT rtTenNumTarget, rtNumTarget, rtTenNumSrc, rtNumSrc;
			int iTenStack = m_iStack[i] / 10;
			int iOneStack = m_iStack[i] % 10;

			SetRect(&rtTenNumTarget, m_rtStack[i].left, m_rtStack[i].bottom - 10, m_rtStack[i].left + 9, m_rtStack[i].bottom);
			SetRect(&rtNumTarget, rtTenNumTarget.right - 2, m_rtStack[i].bottom - 10, rtTenNumTarget.right + 9 - 2, m_rtStack[i].bottom);

			rtTenNumSrc.left = iTenStack * 9;
			rtTenNumSrc.right = rtTenNumSrc.left + 9;
			rtTenNumSrc.top = 0;
			rtTenNumSrc.bottom = 10;

			rtNumSrc.left = iOneStack * 9;
			rtNumSrc.right = rtNumSrc.left + 9;
			rtNumSrc.top = 0;
			rtNumSrc.bottom = 10;

			g_pItemCluster->GetNumTexture()->RenderTexture( &rtTenNumTarget , &rtTenNumSrc);
			g_pItemCluster->GetNumTexture()->RenderTexture( &rtNumTarget , &rtNumSrc);
		}
		else if(m_iStack[i] > 1) {
			int iOneStack = m_iStack[i] % 10;
			RECT rtNumTarget, rtNumSrc;
			SetRect(&rtNumTarget, m_rtStack[i].left, m_rtStack[i].bottom - 10, m_rtStack[i].left + 9, m_rtStack[i].bottom);

			rtNumSrc.left = iOneStack * 9;
			rtNumSrc.right = rtNumSrc.left + 9;
			rtNumSrc.top = 0;
			rtNumSrc.bottom = 10;

			g_pItemCluster->GetNumTexture()->RenderTexture( &rtNumTarget , &rtNumSrc);
		}
	}

#ifdef _DEBUG
	RECT rtRect = {0, 0, 0, 0};
	for(int i = 0; i < TRADE_PAGE; i++) {
		m_pName[i]->GetWindowRect(rtRect);
		g_pVideo->GetSysLine()->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_pVideo->GetSysLine()->DrawRect(rtRect);
		g_pVideo->GetSysLine()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
#endif
}


void SPWindowNpcTrade::RenderText()
{
	SPWindow::RenderText();
}


//////////////////////////////////////////////////////////////////////////
void SPWindowNpcTrade::ResetItemListControl()
{
	ZeroMemory(m_szPage, 64);
	wsprintf(m_szPage, "%d/%d", m_iPage, m_iMaxPage);
	m_pPageInfo->SetWindowText(m_szPage);

	if(m_iPage == 1) {
		m_pPageDown->SetEnable(false);
	}
	else {
		m_pPageDown->SetEnable(true);
	}

	if(m_iPage == m_iMaxPage){
		m_pPageUp->SetEnable(false);
	}
	else{
		m_pPageUp->SetEnable(true);
	}

	for(int i = 0 ; i < TRADE_PAGE ; i++ ) {
		m_pIcon[i]->Hide();
		m_pIcon[i]->SPSendMessage(SPIM_SET_IMAGECLEAR);
		m_pIcon[i]->Show();
		
		m_pName[i]->SetWindowText("");			
		m_pCash[i]->SetWindowText("");
		//m_bDisable[i] = false;
		m_bAble[i] = true;
		m_iMark[i] = ICON_MARK_NULL;
		m_iStack[i] = 0;
	}

	ResetItemButton();
}


void SPWindowNpcTrade::UpdateItemList()
{
	ResetItemListControl();

	
	m_iBuyCount = 1;			//�ӽ�
	m_iSelectItemIndex = -1;
	m_iViewItemIndex = -1;
	//UpdateBuyCount();

	//control select
	for(int i = 0 ; i < TRADE_PAGE ; i++ ){	
		m_pSkin[i]->Hide();
	}

	int iStartIndex = m_iPage -1 ;
	iStartIndex = iStartIndex * TRADE_PAGE;
	int iEndIndex = iStartIndex + TRADE_PAGE;

	
	DXUTOutputDebugString("Page[%d] iStartIndex[%d] iEndIndex[%d]\n", m_iPage, iStartIndex, iEndIndex);

	SPItemAttr* pkItemAttr = NULL;
	int iCounter = 0;
	//char szName[32];
	for(int index = iStartIndex, iCounter = 0; index < iEndIndex ; index++, iCounter++) {
		//if( g_pItemCluster->GetItemInfo(ItemInfo.Item.iItemID, pkItemAttr) ) {

		if(m_pNpcShop->m_NpcSellItem[index].m_iItemID > 0 ){
			if( g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[index].m_iItemID, pkItemAttr) ) {

				//m_pName[iCounter]->SetFontColor(GetItemColor(m_pNpcShop->m_NpcSellItem[index].m_iRear));
				//m_pName[iCounter]->SetFontColor(g_pCheckManager->GetItemColor(m_pNpcShop->m_NpcSellItem[index].m_iRear));				
				if(g_pItemCluster->IsItemNameColor(m_pNpcShop->m_NpcSellItem[index].m_iItemID)){
					m_pName[iCounter]->SetFontColor(g_pItemCluster->GetItemNameColor(m_pNpcShop->m_NpcSellItem[index].m_iItemID));
				}
				else {
					m_pName[iCounter]->SetFontColor(g_pCheckManager->GetItemColor(m_pNpcShop->m_NpcSellItem[index].m_iRear));
				}				
				
				///[12/8/2006 jinssaga]
				//if(pkItemAttr->m_strName.length() > 24) {					
				//	ZeroMemory(szName, 32);
				//	string strSub =  pkItemAttr->m_strName.substr(0, 24);
				//	wsprintf(szName, "%s", strSub.c_str());
				//	m_pName[iCounter]->SetWindowText(szName);
				//}
				//else {
				//	m_pName[iCounter]->SetWindowText(pkItemAttr->m_strName.c_str());
				//}
				
				m_pName[iCounter]->SetWindowText(pkItemAttr->m_strName.c_str());

				int iSellFactor = m_pNpcShop->m_NpcSellItem[index].m_iSellFactor;
				int iTotalBuyPrice = GET_BUY_PRICE(pkItemAttr->m_iGamePrice, 1, iSellFactor, 100);
				iTotalBuyPrice = iTotalBuyPrice *m_pNpcShop->m_NpcSellItem[index].m_iStack;
				m_pCash[iCounter]->SetWindowText(ConvertMoneyToString(iTotalBuyPrice));

				POINT ptSrcPos;
				SPTexture* pkTexture = g_pItemCluster->GetItemTexture(m_pNpcShop->m_NpcSellItem[index].m_iItemID, ptSrcPos);
				//m_pIcon[iCounter]->SPSendMessage(SPIM_SET_IMAGECLEAR);
				m_pIcon[iCounter]->Hide();
				m_pIcon[iCounter]->SetImage(pkTexture, ptSrcPos.x, ptSrcPos.y);
				m_pIcon[iCounter]->Show();
				
				//[2005/10/10] �� �����ۺ��� �� �����÷��̾ ����Ҽ� �ִ����� ���� üũ
				m_bAble[iCounter] = g_pCheckManager->CheckItemStatus(m_pNpcShop->m_NpcSellItem[index].m_iItemID);
				m_iMark[iCounter] = g_pItemCluster->GetItemIconMark(m_pNpcShop->m_NpcSellItem[index].m_iItemID);
				m_iStack[iCounter] = m_pNpcShop->m_NpcSellItem[index].m_iStack;
			}			
		}
		else {
			//m_pIcon[iCounter]->SPSendMessage(SPIM_SET_IMAGECLEAR);
			//m_pName[iCounter]->SetWindowText("");			
			//m_pCash[iCounter]->SetWindowText("");
		}
	}
}


////
//void SPWindowNpcTrade::UpdateBuyCount()
//{	
//	ZeroMemory(m_szBuyCount, 64);
//	//wsprintf(m_szBuyCount, "%d��", m_iBuyCount);
//	wsprintf(m_szBuyCount, "%d", m_iBuyCount);
//	//m_pBuyCountInfo->SetWindowText(m_szBuyCount);	
//	m_pBuyCountInfo->SetWindowFormatText(m_szBuyCount);
//
//	if(m_iSelectItemIndex < 0) {
//		m_pDownCount->SetEnable(false);
//		m_pCount->SetEnable(false);
//		m_pBuy->SetEnable(false);
//		return;
//	}
//	
//	SPItemAttr* pItemAttr = NULL;
//	int iMaxBuyCount = 1;					//������ ���� ����(�� ������ �������� ����� �ߺ��� �Ǵ���)
//	
//	if( g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr) ) {	
//		iMaxBuyCount = pItemAttr->m_iStackLimit;
//	}
//	else {
//		ResetSelectItem();
//		return;
//	}
//
//	if(pItemAttr == NULL) {				//
//		ResetSelectItem();
//		return;	
//	}
//
//	if(m_iBuyCount == 1) {
//		m_pDownCount->SetEnable(false);
//	}
//	else {
//		m_pDownCount->SetEnable(true);
//	}
//
//	if(m_iBuyCount == iMaxBuyCount || m_iBuyCount == MAX_BUY_COUNT){
//		m_pCount->SetEnable(false);
//	}
//	else{
//		m_pCount->SetEnable(true);
//	}
//
//	m_pBuy->SetEnable(true);
//
//	//m_iBuyCount �� ���� ���� ���� ������ ����Ҽ� �ֵ��� �Ѵ� 
//	//int iTotalBuyPrice = m_iBuyCount * pItemAttr->m_iGamePrice;
//	int iSellFactor = m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iSellFactor;
//	int iTotalBuyPrice = GET_BUY_PRICE(pItemAttr->m_iGamePrice, m_iBuyCount, iSellFactor, 100);	
//	m_pCash[m_iViewItemIndex]->SetWindowText(ConvertMoneyToString(iTotalBuyPrice));
//}	


void SPWindowNpcTrade::ResetItemButton()
{
	for(int i = 0 ; i < TRADE_PAGE ; i++ ){
		//SPWindow* pkWindow = Find(WIID_NPCTRADE_ITEM_BUTTON + i, true);
		//if( pkWindow == NULL )
		//	continue;
		//pkWindow->SPSendMessage(SPIM_BTN_SELECT, FALSE);
		m_pSkin[i]->Hide();
	}

	m_iSelectItemIndex = -1;			//���õ� ������ �ε��� �ʱ�ȭ
	m_iViewItemIndex = -1;

	m_bSend = false;
}


void SPWindowNpcTrade::ResetSelectItem()
{
	//������Ʈ�� ����ȭ // �Լ�ȭ ���� ���� ó���ÿ��� ����Ҽ� �ֵ���
	//m_pButton[m_iViewItemIndex]->SPSendMessage(SPIM_BTN_SELECT, FALSE);
	if(m_iViewItemIndex >= 0 && m_iViewItemIndex < TRADE_PAGE)
		m_pSkin[m_iViewItemIndex]->Hide();
	
	SPItemAttr* pItemAttr = NULL;
	if( g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr) ) {		
		int iSellFactor = m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iSellFactor;
		int iTotalBuyPrice = GET_BUY_PRICE(pItemAttr->m_iGamePrice, 1, iSellFactor, 100);
		iTotalBuyPrice = iTotalBuyPrice *m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iStack;
		m_pCash[m_iViewItemIndex]->SetWindowText(ConvertMoneyToString(iTotalBuyPrice));
	}

	m_iSelectItemIndex = -1;
	m_iViewItemIndex = -1;
	m_iBuyCount = 1;
	//UpdateBuyCount();
}


bool SPWindowNpcTrade::IsQuickItemSell()
{
	bool bSend = false;						//�ߺ� ��Ŷ���ѿ�... ���� �־�� ��ȿ�� ������..

	if(g_pGOBManager->GetLocalPlayer() == NULL)
		return false;

	//����� ����
	if(g_pGOBManager->GetLocalPlayer()->GetCoordPhysics()->GetCurState() == GOB_STATE_DEAD) {
		return false;
	}

	//�Ⱦ� ���°� �ƴѰ�� �Ѿ��
	SPPlayerInvenArchive* pInvenArchive = NULL;
	pInvenArchive = g_pGOBManager->GetLocalPlayer()->GetInvenArchive();	

	if(pInvenArchive->m_bPickup == false) {
		DXUTOutputDebugString("No PickUp Item\n");
		return false;
	}	

	m_PickUpItem = pInvenArchive->GetPickupItem();
	
	//����ǿ��� ���� ���
	if(m_PickUpItem.GetContainerType() >= INVENTORY_HOUSING) {
		//DXUTOutputDebugString("ItemSell Equip, Costume... Inven.. \n")	;
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);		
		return false;
	}

	//�ش���ġ�� �������� ���� ���
	if(pInvenArchive->IsItemExist(m_PickUpItem.m_iSlotIndex, m_PickUpItem.m_iContainer) == false) {
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);		
		return false;
	}
	
	SPItem* pSellSelectItem = g_pGOBManager->GetLocalPlayer()->GetInvenArchive()->GetInventoryItem(m_PickUpItem.m_iContainer, m_PickUpItem.m_iSlotIndex);
	if(pSellSelectItem == NULL) {
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);		
		return false;
	}

	SPItemStatus* pItemStatus = pSellSelectItem->GetItemStatus();
	if(pItemStatus == NULL || pItemStatus->GetItemID() == 0) {
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);		
		return false;
	}
	
	if(m_pNpcShop == NULL) {
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);
		return false;
	}

	SPItemAttr* pItemAttr = pItemStatus->GetItemAttr();
	
	//[2007/1/22] - jinssaga   
	if(pItemAttr->m_bCashCheck) {
		std::string strMsg = "";
		if(SPLocalizeManager::GetInstance()->GetMileageRatio() == 0) {			//����Ʈ�� ������� �ʴ� ���
			if(g_pResourceManager->GetGlobalString(4003009))
				strMsg = g_pResourceManager->GetGlobalString(4003009);
		}
		else {
			if(g_pResourceManager->GetGlobalString(4003008))					//����Ʈ�� ���
				strMsg = g_pResourceManager->GetGlobalString(4003008);
		}		
		
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);
		
		g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
		return false;
	}
	
	//�Ǹ� �Ұ����� �Ӽ��� �������� ��� ����	
	if(pItemAttr == NULL || pItemAttr->m_bSell == false) {
		if(g_pGOBManager->GetLocalPlayer())
			g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);
		return false ;
	}

	CONTAINER_ITEM item;
	if(m_PickUpItem.m_iContainer < INVENTORY_EQUIP || m_PickUpItem.m_iContainer > INVENTORY_HOUSING)
		return false;
	if(m_PickUpItem.m_iSlotIndex < 0 || m_PickUpItem.m_iSlotIndex >= pInvenArchive->GetInventorySize(m_PickUpItem.m_iContainer))
		return false;

	item.SlotInfo.ContainerType = m_PickUpItem.m_iContainer;
	item.SlotInfo.SlotIndex = m_PickUpItem.m_iSlotIndex + 1;
	item.Item.iItemID = pItemStatus->GetItemID();
	item.Item.iStackCount = pItemStatus->SPSendMessage(MV_ITEM_GETSTACK_CNT);
	item.Item.iBackPrice = pItemStatus->SPSendMessage(MV_ITEM_GET_BACKPRICE);
	item.Item.iItemNo = *(ITEMNO*)pItemStatus->SPSendMessage(MV_ITEM_GET_ITEMNO);

	if(g_pCheckManager->IsDBBlock()) {
		
		DXUTOutputDebugString("\tSPWindowItemSell::OnSell DB Working Block\n");
		return false;
	}

	//��Ŷ �����
	CPacket Packet(NPC_SHOP_CS_SELL);
	Packet.Add((UINT32)m_pNpcShop->m_iNpcID);
	Packet.Add((UINT32)m_pNpcShop->m_iShopID);
	Packet.AddData(&item, sizeof(CONTAINER_ITEM));

	if(!bSend) {		
		g_pNetworkManager->SPPerformMessage(NPC_SHOP_CS_SELL, 0, (LPARAM)&Packet);
		bSend = true;
		//Cash Sound
		g_pInterfaceManager->RegisterSoundUnit("DATA/SOUND/SYSTEM_CASH.WAV");
	}
	
	return true;
}


//////////////////////////////////////////////////////////////////////////
SPIMESSAGE_OBJ_MAP_BEGIN	( SPWindowNpcTrade )

SPIMESSAGE_COMMAND( SPIM_SET_NPCSHOP_SHOW,		OnUpdateShopData )

SPIMESSAGE_CONTROL( SPIM_LBUTTON_UP,	WIID_NPCTRADE_EXIT		, OnClose)
SPIMESSAGE_CONTROL( SPIM_LBUTTON_UP,	WIID_NPCTRADE_PAGEDOWN	, OnPageDown)
SPIMESSAGE_CONTROL( SPIM_LBUTTON_UP,	WIID_NPCTRADE_PAGEUP	, OnPageUp)

//SPIMESSAGE_CONTROL( SPIM_LBUTTON_UP,	WIID_NPCTRADE_COUNT		, OnCount)		//��Ȳ�� ���� LBUTTON_DOWN���� �ٲ��� ������..
//SPIMESSAGE_CONTROL( SPIM_LBUTTON_UP,	WIID_NPCTRADE_DOWNCOUNT	, OnCountDown)
//SPIMESSAGE_CONTROL( SPIM_REFRESH,		WIID_NPCTRADE_COUNTER	, OnUpdateCount)
//SPIMESSAGE_CONTROL( SPIM_SETFOCUS,	WIID_NPCTRADE_COUNTER	, OnInputFocus)
//SPIMESSAGE_COMMAND( SPIM_WHEEL_UP,								OnCount)
//SPIMESSAGE_COMMAND( SPIM_WHEEL_DOWN,							OnCountDown)
//SPIMESSAGE_CONTROL( SPIM_WHEEL_UP,	WIID_NPCTRADE_COUNTER,	OnCount)
//SPIMESSAGE_CONTROL( SPIM_WHEEL_DOWN,	WIID_NPCTRADE_COUNTER,	OnCountDown)

SPIMESSAGE_CONTROL( SPIM_LBUTTON_UP,	WIID_NPCTRADE_BUY		, OnBuyItem)	//���� ����

SPIMESSAGE_CONTROL_RANGE( SPIM_LBUTTON_UP, WIID_NPCTRADE_ITEM_BUTTON,		WIID_NPCTRADE_ITEM_BUTTON + TRADE_PAGE,	OnLBuyItemClick)
SPIMESSAGE_CONTROL_RANGE( SPIM_RBUTTON_UP, WIID_NPCTRADE_ITEM_BUTTON,		WIID_NPCTRADE_ITEM_BUTTON + TRADE_PAGE,	OnRBuyItemClick)
SPIMESSAGE_CONTROL_RANGE( SPIM_TOOLTIP_ENTER,	WIID_NPCTRADE_ITEM_BUTTON,		WIID_NPCTRADE_ITEM_BUTTON + TRADE_PAGE,	OnToolTipEnter)
SPIMESSAGE_CONTROL_RANGE( SPIM_TOOLTIP_OUT,		WIID_NPCTRADE_ITEM_BUTTON,		WIID_NPCTRADE_ITEM_BUTTON + TRADE_PAGE,	OnToolTipOut)
SPIMESSAGE_CONTROL_RANGE( SPIM_TOOLTIP_MOVE,	WIID_NPCTRADE_ITEM_BUTTON,		WIID_NPCTRADE_ITEM_BUTTON + TRADE_PAGE,	OnToolTipMove)

SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_TOP		, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_CENTER	, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_BOTTOM	, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_TITLE		, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_MIDDLE	, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_LIST_IMG_BASE , OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_LIST_IMG	, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_PRICE_IMG_BASE, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_PRICE_IMG		, OnLButtonUp)		//�����۾����� ��Ŀ��
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_PAGEUP	, OnLButtonUp)
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_PAGE		, OnLButtonUp)
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_NPCTRADE_PAGEDOWN	, OnLButtonUp)
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_USER_ELY_TEXT_IMG	, OnLButtonUp)
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_USER_ELY			, OnLButtonUp)
SPIMESSAGE_CONTROL(SPIM_LBUTTON_UP,	WIID_USER_ELY_IMG		, OnLButtonUp)

SPIMESSAGE_OBJ_MAP_END	( SPWindow	)



int SPWindowNpcTrade::OnUpdateShopData( WPARAM wParam, LPARAM lParam )
{
	//���������͸� �����´�
	m_pNpcShop = g_pEventManager->GetEventHandler()->GetNpcShopData();
	
	m_iPage = 1;
	m_iMaxPage = m_pNpcShop->m_iPageCount;
	
	//m_iBuyCount = 1;			//�ӽ�
	
	//��Ʈ�� ���� ������Ʈ�� �Ѵ� 	
	UpdateItemList();

	return 1;
}


int SPWindowNpcTrade::OnClose( WPARAM wParam, LPARAM lParam )
{
	g_pEventManager->SetCutInState(CUT_IN_STATE_RELEASE);

	
	DXUTOutputDebugString("SPWindowNpcTrade::OnClose::CUT_IN_STATE_NULL\n");

	//g_pInterfaceManager->GetItemSellWindow()->SPSendMessage(SPIM_SET_ITEMSELL_RESET);
	
	return 1;
}


int SPWindowNpcTrade::OnPageDown( WPARAM wParam, LPARAM lParam )
{
	if(g_pGOBManager->GetLocalPlayer())
		g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);
	
	if( m_iPage > 1  && m_iPage <= m_iMaxPage ) {
		m_iPage--;

		UpdateItemList();
	}

	return 1;
}


int SPWindowNpcTrade::OnPageUp( WPARAM wParam, LPARAM lParam )
{
	if(g_pGOBManager->GetLocalPlayer())
		g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);
	
	if( m_iPage > 0 && m_iPage < m_iMaxPage ) {
		m_iPage++;
		
		UpdateItemList();
	}
	
	return 1;
}


int SPWindowNpcTrade::OnCount( WPARAM wParam, LPARAM lParam )
{
	//���� ���õ� �������� ��ȿ���� ���� üũ 
	if(m_iSelectItemIndex < 0 || m_iSelectItemIndex > m_pNpcShop->m_iItemSize)
		return 1;
	
	SPItemAttr* pItemAttr = NULL;
	if( g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr) ) {
		if(0 < m_iBuyCount && m_iBuyCount < pItemAttr->m_iStackLimit) {
			m_iBuyCount++;

			//UpdateBuyCount();
		}
	}

	return 1;
}


int SPWindowNpcTrade::OnCountDown( WPARAM wParam, LPARAM lParam )
{
	//���� ���õ� �������� ��ȿ���� ���� üũ 	
	if(m_iSelectItemIndex < 0 || m_iSelectItemIndex > m_pNpcShop->m_iItemSize)
		return 1;
	
	SPItemAttr* pItemAttr = NULL;
	if( g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr) ) {
		//if(1 < m_iBuyCount && m_iBuyCount <= MAX_BUY_COUNT ) {
		if(1 < m_iBuyCount && m_iBuyCount <= pItemAttr->m_iStackLimit ) {
			m_iBuyCount--;

			//UpdateBuyCount();
		}
	}

	return 1;
}


int SPWindowNpcTrade::OnUpdateCount(WPARAM wParam, LPARAM lParam)
{
	//���� ���õ� �������� ��ȿ���� ���� üũ 	
	if(m_iSelectItemIndex < 0 || m_iSelectItemIndex > m_pNpcShop->m_iItemSize) {
		m_iBuyCount = 1;
		//m_pBuyCountInfo->KillFocus();
		return 1;
	}
	
	//int iTradeCount = atoi(m_pBuyCountInfo->GetWindowText());
	int iTradeCount = 0;

	SPItemAttr* pItemAttr = NULL;
	if( g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr) ) {		
		if(iTradeCount > 0 && iTradeCount <= pItemAttr->m_iStackLimit) {
			//ī���� ������Ʈ
			m_iBuyCount = iTradeCount;
			
		}
		else {			
			if(iTradeCount < 1) {
				m_iBuyCount = 0;
			}
			else if(iTradeCount > pItemAttr->m_iStackLimit) {
				m_iBuyCount = pItemAttr->m_iStackLimit;
			}		
		}
		//UpdateBuyCount();
	}
	
	return 1;
}


int SPWindowNpcTrade::OnInputFocus(WPARAM wParam, LPARAM lParam)
{
	//���� ���õ� �������� ��ȿ���� ���� üũ 	
	if(m_iSelectItemIndex < 0 || m_iSelectItemIndex > m_pNpcShop->m_iItemSize) {
		//m_pBuyCountInfo->KillFocus();
		return 1;
	}

	//������������ ���ų� ������ 1������ ���
	SPItemAttr* pItemAttr;
	g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr);
	if( pItemAttr ) {
		if(pItemAttr->m_iStackLimit < 2) {
			//m_pBuyCountInfo->KillFocus();					//������ 1�̻��� �����۸� ��Ŀ���� �ش�
			return 1;
		}
	}
	
	return 1;
}


int SPWindowNpcTrade::OnLBuyItemClick( unsigned int uiID, WPARAM wParam, LPARAM lParam )	//������ ������ Ŭ�� (��Ʈ�� Ŭ��)
{
	//[2005/12/19] - �� �Ǹſ� ���� ���� �������� ��� �ִ� ��Ȳ�̶��... ó��
	if(IsQuickItemSell())
		return 1;
	
	//������ ���õǾ� �ִ� �κ��� �����Ѵ� 
	ResetSelectItem();						//[2005/10/10]
	
	int iSelect = uiID - WIID_NPCTRADE_ITEM_BUTTON;	
	assert(iSelect < TRADE_PAGE && "NPC Shop Item List Constrol�� �������̽� �ε��� ����");	
	
	//������ ���� �ִ� Counter������ �������ش� 
	ResetItemButton();	

	//��Ʈ�� Select���� ���� �Ǹ� ������ ����Ʈ�� ���Ͽ� ������� ū��� �׳� ��ȯ�Ѵ� 
	
	m_iSelectItemIndex = iSelect + ((m_iPage - 1) * TRADE_PAGE);	
	m_iViewItemIndex = iSelect;
	if(m_iSelectItemIndex >= m_pNpcShop->m_iItemSize) {
		DXUTOutputDebugString("FAIL : m_iSelectItemIndex [%d] - ItemSize[%d] \n", m_iSelectItemIndex, m_pNpcShop->m_iItemSize);
		
		m_iSelectItemIndex = -1;
		m_iViewItemIndex = -1;
		
		return 1;
	}
	DXUTOutputDebugString("OK : m_iSelectItemIndex [%d] ViewIndex[%d]- ItemSize[%d]\n", m_iSelectItemIndex, m_iViewItemIndex, m_pNpcShop->m_iItemSize);	

	//control select
	for(int i = 0 ; i < TRADE_PAGE ; i++ ){
		if(i == m_iViewItemIndex) {
			m_pSkin[i]->Show();						
		}
		else {
			m_pSkin[i]->Hide();
		}

	}	
	
	//������ ī���͸� ������Ʈ �Ѵ� 	
	m_iBuyCount = 1;
	//�̰� ���Ŀ� ��Ʈ�� ���������� �������־�� �Ѵ� (List ��ü�� �����Ǿ�� �ҵ�...)	
	
	//UpdateBuyCount();

	SPItemAttr* pItemAttr;
	g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr);
	if( pItemAttr ) {
		if(pItemAttr->m_iStackLimit > 1) {
			//m_pBuyCountInfo->SetFocus();					//������ 1�̻��� �����۸� ��Ŀ���� �ش�
		}
	}	
	
	return 1;
}


int SPWindowNpcTrade::OnRBuyItemClick( unsigned int uiID, WPARAM wParam, LPARAM lParam )
{
	//[2005/12/19] - �� �Ǹſ� ���� ���� �������� ��� �ִ� ��Ȳ�̶��... ó��
	if(IsQuickItemSell())
		return 1;

	//������ ���õǾ� �ִ� �κ��� �����Ѵ� 
	ResetSelectItem();						//[2005/10/10]

	int iSelect = uiID - WIID_NPCTRADE_ITEM_BUTTON;	
	assert(iSelect < TRADE_PAGE && "NPC Shop Item List Constrol�� �������̽� �ε��� ����");	

	//������ ���� �ִ� Counter������ �������ش� 
	ResetItemButton();	

	//��Ʈ�� Select���� ���� �Ǹ� ������ ����Ʈ�� ���Ͽ� ������� ū��� �׳� ��ȯ�Ѵ� 
	
	m_iSelectItemIndex = iSelect + ((m_iPage - 1) * TRADE_PAGE);	
	m_iViewItemIndex = iSelect;
	if(m_iSelectItemIndex >= m_pNpcShop->m_iItemSize) {
		DXUTOutputDebugString("FAIL : m_iSelectItemIndex [%d] - ItemSize[%d] \n", m_iSelectItemIndex, m_pNpcShop->m_iItemSize);

		m_iSelectItemIndex = -1;
		m_iViewItemIndex = -1;

		return 1;
	}
	DXUTOutputDebugString("OK : m_iSelectItemIndex [%d] ViewIndex[%d]- ItemSize[%d]\n", m_iSelectItemIndex, m_iViewItemIndex, m_pNpcShop->m_iItemSize);	

	//control select
	for(int i = 0 ; i < TRADE_PAGE ; i++ ){
		if(i == m_iViewItemIndex) {
			m_pSkin[i]->Show();						
		}
		else {
			m_pSkin[i]->Hide();
		}

	}

	OnBuyItem((WPARAM)0, (LPARAM)0);
	
	return 1;
}


int SPWindowNpcTrade::OnBuyItem( WPARAM wParam, LPARAM lParam )
{
	//////////////////////////////////////////////////////////////////////////���� ������ ���� ó��
	if(m_pNpcShop == NULL)		return 1;			//����ó��
	if(m_iSelectItemIndex < 0)	return 1;

	SPItemAttr* pItemAttr = NULL;
	
	if(g_pGOBManager->GetLocalPlayer() == NULL)
		return 1;

	//���� Local Player�� ���� ���Ÿ� �Ҽ� �ִ� ��Ȳ���� Ȯ���Ѵ�
	if(g_pGOBManager->GetLocalPlayer()->GetCoordPhysics()->GetCurState() == GOB_STATE_DEAD) {
		ResetSelectItem();
		return 1;
	}
	
	//���� ���� �۾�	
	if( g_pItemCluster->GetItemInfo(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, pItemAttr) ) {					
		CONTAINER_TYPE iContainerType = (CONTAINER_TYPE)(pItemAttr->m_eType - 1);
		int iItemID = m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID;
		int iStack = m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iStack;

		//�κ��丮�� Full���� ���� Ȯ���Ѵ�
		if(g_pGOBManager->GetLocalPlayer()->GetInvenArchive()->IsFullInventory(iContainerType)) {
			if(false == g_pGOBManager->GetLocalPlayer()->GetInvenArchive()->IsEnableSpace(iContainerType, iItemID, iStack))
			{	
				//���� ����ī��Ʈ�� �� ���� ���� �������� �����ϴ� ��� ���� �������� �Ѵ�		
				ResetSelectItem();

				if(g_pResourceManager->GetGlobalString(4003102)) {
					std::string strMsg = g_pResourceManager->GetGlobalString(4003102);	//�κ��丮 ������ �����Ͽ� �������� ������ �� �����ϴ�.
					g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
				}

				return 1;
			}
		}		
		
		if(false == g_pCheckManager->CheckEnableSlot(m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID, m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iStack)) {
			ResetSelectItem();
			return 1;
		}
		
		//�÷��̾��� ���� ������ �ݾ׺��� ������ ��� ó��
		int iUserEly = g_pGOBManager->GetLocalPlayer()->GetStatus()->GetStatusValueEX(STATUS_EX_ELY);
		//int iTotalBuyPrice = m_iBuyCount * pItemAttr->m_iGamePrice;
		int iSellFactor = m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iSellFactor;
		int iTotalBuyPrice = GET_BUY_PRICE(pItemAttr->m_iGamePrice, m_iBuyCount, iSellFactor, 100);
		iTotalBuyPrice = iTotalBuyPrice * m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iStack;
		
		if(iTotalBuyPrice > iUserEly) {
			ResetSelectItem();

			if(g_pResourceManager->GetGlobalString(4003101)) {
				std::string strMsg = g_pResourceManager->GetGlobalString(4003101);	//Ely�� �����Ͽ� �������� ������ �� �����ϴ�.
				g_pInterfaceManager->SPPerformMessage( SPIM_WNDCHAT_MESSAGE_STRING , (WPARAM)strMsg.c_str() );
			}

			return 1;
		}

		//iMaxBuyCount = pItemAttr->m_iStackLimit;

		if(g_pCheckManager->IsDBBlock()) {
			
			DXUTOutputDebugString("\tSPWindowNpcTrade::OnBuyItem DB Working Block\n");
			return 1;
		}

		CPacket Packet(NPC_SHOP_CS_BUY);
		Packet.Add((UINT32)m_pNpcShop->m_iNpcID);
		Packet.Add((UINT32)m_pNpcShop->m_iShopID);
		Packet.Add((UINT8)m_iSelectItemIndex);
		
		ITEM item = {0,};		
		item.iItemID = m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iItemID;
		item.iStackCount = m_pNpcShop->m_NpcSellItem[m_iSelectItemIndex].m_iStack;		
		Packet.AddData(&item, sizeof(ITEM));

		if(!m_bSend) {
			//�̺κ� ���ϰ� ���� ������ ����...
			//return g_pNetworkManager->SPPerformMessage(NPC_SHOP_CS_SELL, 0, (LPARAM)&Packet);	
			g_pNetworkManager->SPPerformMessage(NPC_SHOP_CS_BUY, 0, (LPARAM)&Packet);	

			m_bSend = true;				

			//������Ʈ�� ����ȭ
			ResetSelectItem();

			//�ȱ����� ����� �������� �����ϵ��� �Ѵ�
			//g_pInterfaceManager->GetItemSellWindow()->SPSendMessage(SPIM_SET_ITEMSELL_RESET);

			//m_pBuy->SetEnable(false);

			g_pCheckManager->SetDBBlock(true);

			//Cash Sound
			g_pInterfaceManager->RegisterSoundUnit("DATA/SOUND/SYSTEM_CASH.WAV");
		}
	}

	return 1;
}


int SPWindowNpcTrade::OnToolTipMove(unsigned int uiID, WPARAM wParam, LPARAM lParam)
{
	int iCurIndex = uiID - WIID_NPCTRADE_ITEM_BUTTON;	
	iCurIndex = iCurIndex + ((m_iPage - 1) * TRADE_PAGE);	

	unsigned int uiUniqueID;
	int iEquipClass, iItemID, iItemColor;

	if(m_pNpcShop == NULL || m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID == 0)	return 1;

	//uiUniqueID = m_ContainerItem[iCurIndex].Item.iItemID;
	uiUniqueID = m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID;	
	iItemColor = (m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID) % 100;
	iEquipClass = (m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID) / 100000;
	iItemID = ((m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID) % 100000 - iItemColor) / 100;	

	SPItemStatus kItemStatus;
	kItemStatus.SetItemID(uiUniqueID);

	SPItemAttr* pItemAttr;
	g_pItemCluster->GetItemInfo(uiUniqueID, pItemAttr);
	if( pItemAttr )
	{
		kItemStatus.SPSendMessage(MV_ITEM_SETEQUIPID, pItemAttr->m_ePosID1);
		kItemStatus.SPSendMessage(MV_ITEM_SETEQUIPCLASS, iEquipClass);
		kItemStatus.SPSendMessage(MV_ITEM_SETEQUIPITEMID, iItemID);
		kItemStatus.SPSendMessage(MV_ITEM_SETCOLOR,	iItemColor);
		kItemStatus.SPSendMessage(MV_ITEM_SET_RARELEVEL, m_pNpcShop->m_NpcSellItem[iCurIndex].m_iRear);

		if(pItemAttr->m_eDuration != ITEM_DURATION_NULL) {
			kItemStatus.SetLifeTime(pItemAttr->m_iLifeTime * 3600);
		}

		SPWindow* pWindow = g_pInterfaceManager->GetToolTipWindow();
		pWindow->SPSendMessage(SPIM_TOOLTIP_MOVE, (WPARAM)&kItemStatus, lParam);
		pWindow->Show();
	}

	return 1;
}


int SPWindowNpcTrade::OnToolTipEnter(unsigned int uiID, WPARAM wParam, LPARAM lParam)
{	
	int iCurIndex = uiID - WIID_NPCTRADE_ITEM_BUTTON;	
	iCurIndex = iCurIndex + ((m_iPage - 1) * TRADE_PAGE);

	unsigned int uiUniqueID;
	int iEquipClass, iItemID, iItemColor;
	
	if(m_pNpcShop == NULL || m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID == 0)	return 1;	
	
	uiUniqueID = m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID;	
	iItemColor = (m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID) % 100;
	iEquipClass = (m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID) / 100000;
	iItemID = ((m_pNpcShop->m_NpcSellItem[iCurIndex].m_iItemID) % 100000 - iItemColor) / 100;	

	SPItemStatus kItemStatus;
	kItemStatus.SetItemID(uiUniqueID);

	SPItemAttr* pItemAttr;
	g_pItemCluster->GetItemInfo(uiUniqueID, pItemAttr);
	if( pItemAttr )
	{
		kItemStatus.SPSendMessage(MV_ITEM_SETEQUIPID, pItemAttr->m_ePosID1);
		kItemStatus.SPSendMessage(MV_ITEM_SETEQUIPCLASS, iEquipClass);
		kItemStatus.SPSendMessage(MV_ITEM_SETEQUIPITEMID, iItemID);
		kItemStatus.SPSendMessage(MV_ITEM_SETCOLOR,	iItemColor);
		kItemStatus.SPSendMessage(MV_ITEM_SET_RARELEVEL, m_pNpcShop->m_NpcSellItem[iCurIndex].m_iRear);

		if(pItemAttr->m_eDuration != ITEM_DURATION_NULL) {
			kItemStatus.SetLifeTime(pItemAttr->m_iLifeTime * 3600);
		}

		SPWindow* pWindow = g_pInterfaceManager->GetToolTipWindow();
		pWindow->SPSendMessage(SPIM_TOOLTIP_ENTER, (WPARAM)&kItemStatus, lParam);
		pWindow->Show();
	}

	return 1;
}


int SPWindowNpcTrade::OnToolTipOut(unsigned int uiID, WPARAM wParam, LPARAM lParam)
{
	SPWindow* pWindow = g_pInterfaceManager->GetToolTipWindow();
	pWindow->SPSendMessage( SPIM_TOOLTIP_OUT, NULL, lParam);
	pWindow->Show();

	return 1;
}


int SPWindowNpcTrade::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if(g_pGOBManager->GetLocalPlayer())
		g_pGOBManager->GetLocalPlayer()->SPGOBPerformMessage(SPGM_INVEN_RECOVER_ICON , 0);
	return 1;
}


