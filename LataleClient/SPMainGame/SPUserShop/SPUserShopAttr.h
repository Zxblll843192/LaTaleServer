#pragma once

#include "SPQuestAttr.h"

const int MAX_USER_SHOP_REQUIRE = 4;					/**< �ִ� �䱸���� <br> */
const int MAX_USER_SHOP_FRAME = 4;						/**< �ִ� �ִϸ��̼� ���� <br> */

enum USER_SHOP_LEVEL {
	USER_SHOP_LEVEL_NULL	= 0,
	USER_SHOP_LEVEL_1		= 1,
	USER_SHOP_LEVEL_2		= 2,
	USER_SHOP_LEVEL_3		= 3,
	USER_SHOP_LEVEL_4		= 4,
	USER_SHOP_LEVEL_5		= 5,
	USER_SHOP_LEVEL_MAX		= 6,
};

struct SPSignBoard {
	std::string		m_strSource;						/**< �ҽ� ���� <br> */
	RECT			m_rtSrc;							/**< �ҽ� ���� <br> */
	POINT			m_ptDest;							/**< ��� ���� <br> */
	POINT			m_ptNameDest;						/**< ���� ���� �̸� ���� <br> */
	POINT			m_ptTitleDest;						/**< ���� �� ���� <br> */
	float			m_fDelay;							/**< ������ <br> */
	
	SPTexture*		m_pTexture;							/**< �ҽ� �ؽ��� <br> */	
	int				m_iWidth;							/**< �̹��� ���� <br> */
	int				m_iHeight;							/**< �̹��� ���� <br> */

	SPSignBoard() {
		m_pTexture = NULL; 
		Clear();
	}

	~SPSignBoard() {
		SAFE_RELEASE(m_pTexture);
		Clear();
	}

	void Clear() {
		m_strSource = "";
		m_strSource.clear();
		SetRect(&m_rtSrc, 0, 0, 0, 0);
		m_ptDest.x = 0;
		m_ptDest.y = 0;
		m_ptNameDest.x = 0;
		m_ptNameDest.y = 0;
		m_ptTitleDest.x = 0;
		m_ptTitleDest.y = 0;
		m_fDelay = 0.0f;

		m_iWidth = 0;
		m_iHeight = 0;
	}

	void SetSrcFile(std::string strSrcFile) {
		m_strSource = "";
		m_strSource.clear();
		m_strSource = strSrcFile;
		
		std::string strTextureFile = "";
		strTextureFile.clear();
		strTextureFile = "DATA/INTERFACE/CONCEPT/" + m_strSource;
		//g_pVideo->GetTextureMgr()->LoadTexture(strTextureFile.c_str(), &m_pTexture);
		g_pVideo->GetTextureMgr()->GetTexture(strTextureFile.c_str(), &m_pTexture,TEX_INTERFACE);
		
	}

	void SetSrcRect(int iLeft, int iTop, int iRight, int iBottom) {
		SetRect(&m_rtSrc, iLeft, iTop, iRight, iBottom);
		m_iWidth = iRight - iLeft ;
		m_iHeight = iBottom - iTop;
	}

	void SetDest(int iX, int iY) {
		m_ptDest.x = iX;
		m_ptDest.y = iY; 
	}

	void SetNameDeat(int iX, int iY) {
		m_ptNameDest.x = iX;
		m_ptNameDest.y = iY;
	}

	void SetTitleDest(int iX, int iY) {
		m_ptTitleDest.x = iX;
		m_ptTitleDest.y = iY;
	}
};



class SPUserShopAttr {
public:
	SPUserShopAttr();
	~SPUserShopAttr();

	void SetOverLapRect(int iLeft, int iTop, int iRight, int iBottom);
	void SetNameColor(int iRed, int iGreen, int iBlue, int iAlpha = 255);
	void SetTitleColor(int iRed, int iGreen, int iBlue, int iAlpha = 255);
	

protected:
	void Init();
	void Clear();

public:
	int				m_iID;								/**< LDT ID <br> */
	int				m_iType;							/**< ���λ��� ���� <br> */
	RECT			m_rtOverLapRect;					/**< �ߺ� üũ ���� <br> */
	SPRequire		m_Require[MAX_USER_SHOP_REQUIRE];	/**< ���λ��� ���� üũ�� �䱸���� <br> */
	int				m_iPage;							/**< ������ ���λ��� ������ <br> ������ * 4 <br> */	
	
	int				m_iNameWidth;						/**< ���� ���� �̸� <br> */
	int				m_iNameHeight;						/**< ���� ���� �̸� <br> */	
	D3DXCOLOR		m_NameColor;						/**< ���� ���� �̸� <br> */	
	bool			m_bNameBold;						/**< ���� ���� �̸� <br> */	

	int				m_iTitleWidth;						/**< ���� �̸� <br> */
	int				m_iTitleHeight;						/**< ���� �̸� <br> */
	D3DXCOLOR		m_TitleColor;						/**< ���� �̸� <br> */
	bool			m_bTitleBold;						/**< ���� �̸� <br> */

	SPSignBoard		m_SignBoard[MAX_USER_SHOP_FRAME];	/**< ���ϸ��̼�? ������ ���� <br> */		
	int				m_iMaxFrame;						/**< ���ϸ��̼� �ִ� ������ ���� <br> */

	int				m_iMotion;							//!< shop motion	
};


