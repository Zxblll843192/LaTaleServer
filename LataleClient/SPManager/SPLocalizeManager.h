#pragma once

enum COUNTRY_TYPE
{
	CT_NULL = -1,
	CT_KOREA = 0,		// SITE_ACTOZ
	CT_JAPAN,			// SITE_GAMEPOT
	CT_CHINA,			// SITE_SANDA
	CT_BUDDYBUDDY,		// SITE_BUDDYBUDDY	
	CT_OGP,				// [4/28/2008 metalgeni]
};

//enum SITE_TYPE		// GlobalDefines_share.h�� �ߺ��Ǿ� "_"�� ����. �۾��Ϸ�� ������ �˸��ʿ���.
//{
//	SITE_LOCAL_ = 0,
//	SITE_ACTOZ_,
//	SITE_GAMEPOT_,
//	SITE_SANDA_,
//	SITE_BUDDYBUDDY_,
//	MAX_SITE_,
//};


enum LOCALIZE_VALUE
{
	LV_PROLOGUE,
	LV_CASHSHOP,
	LV_BEAUTYSHOP,
	LV_PET,
	LV_PHANTOM,
	LV_WAYPOINT,
	LV_COUPON,
	LV_GIFT,
	LV_GUILD,
	LV_LOTTERY,
	LV_INDUN,
	LV_JOYPAD,
	LV_CHATMACRO,
	LV_ITEMMIX,
	LV_GUIDEBOOK,
	LV_PVP,
	LV_CHATTINGROOM,
	LV_REPORTSHOT,
	LV_ITEMENCHANT,
	LV_ITEMUPGRADE,
	LV_EXTENDEDTERMITEM,
	LV_PETDISABLE,
	LV_LOVE,
	LV_LOVE_COLOR,

};


enum SITE_TYPE ;


/**
 * ���ӳ� ����Ʈ �ŷ� �� ĳ�þ����� ��� ���Ž� <br> 
*/
enum CASH_TRADE {
	CASH_TRADE_NULL,				/**< ĳ�� �ŷ� �Ұ� <br> */
	CASH_TRADE_ALL,					/**< ĳ�ù� ����Ʈ �ŷ� ���� <br> */
	CASH_TRADE_CASH,				/**< ĳ�� �ŷ� �� ����  <br> */
	CASH_TRADE_POINT,				/**< ����Ʈ �ŷ��� ����  <br> */	
};


class SPLocalizeManager
{
public:
	static SPLocalizeManager* GetInstance();
	static void Release();

	bool Init();
	bool IsEnableValue(LOCALIZE_VALUE eValue);
	COUNTRY_TYPE GetCountryType();
	SITE_TYPE	GetSiteType() ;
	int GetMileageRatio();
	int GetMileageGlowUnit();
	int GetCashierGlowUnit();

	const char* GetHomePage();
	const char* GetNewAccount();
	const char* GetBillingPage();
	const char* GetHomeFindUserID();
	const char* GetHomeFindPasswd();
	const char* GetRegistryCompany();

	CASH_TRADE	GetCashTradeType();	
	CASH_TRADE	GetCashTradeDisplay();

	int GetAuctionNextBidRate();
	int GetAuctionTimeShort();
	int GetAuctionTimeMiddle();
	int GetAuctionTimeLong();
	int GetAuctionFeeRate();

	/**
	 * ġƮ�� �Լ� <br> 
	 @param 
	 @return  
	*/
	void		SetCashTradeType(int iType);

	int			GetCashTradeUnit();
	int			GetPointTradeUnit();
	int			GetCashFee();
	int			GetPointFee();

	bool OnlyWebLogin();			// Buddy, AtGames
private:
	SPLocalizeManager();
	~SPLocalizeManager();

	bool LoadLDTFile();

private:
	static SPLocalizeManager* m_pkInstance;

	COUNTRY_TYPE m_eCountry;	// ����
	SITE_TYPE	m_ePublisher;	// ����Ʈ
	bool m_bPrologue;
	bool m_bCashShop;
	bool m_bBeautyShop;
	bool m_bPet;
	bool m_bWayPoint;
	bool m_bCashShopCoupon;
	bool m_bCashShopGift;
	bool m_bGuild ;
	bool m_bIndun ;
	bool m_bJoyPad ;
	bool m_bLottery;
	bool m_bChatMacro;
	bool m_bItemMix;
	bool m_bGuideBook;
	bool m_bPVP;
	bool m_bChattingRoom;
	bool m_bItemEnchant;
	bool m_bItemUpgrade;
	int m_iMileageRatio;
	int m_iMileageGlowUnit;
	int m_iCashierGlowUnit;
	bool m_bReportShot;
	int iAuctionNextBidRate ;		// ��ȸ������ ��������
	int	m_iAuctionShortTime ;		// ��� �ð�(�ܱ�)
	int	m_iAuctionMiddleTime ;		// ��� �ð�(�߱�)
	int	m_iAuctionLongTime ;		// ��� �ð�(�����)
	int m_iAuctioinFeeRate ;		// ��� ������ ����

	bool m_bExtendedTermItem;		// �����۱Ⱓ���� Disable
	bool m_bPetDisable;				// �ֿϵ��� Disable
	bool m_bPhantom;
	bool m_bLove;

	std::string m_strHomePage;
	std::string m_strNewAccount;
	std::string m_strBillingPage;
	std::string m_strFindUserID;
	std::string m_strFindPasswd;
	std::string m_strRegistryCompany;

	CASH_TRADE		m_iCashTrade;		/**< ������ ĳ�� �ŷ� ���� �÷��� <br> */
	CASH_TRADE		m_iCashDisplay;		/**< ���ӻ� ĳ�ð��� ���� ǥ�� �÷��� <br> */
	int				m_iCashTradeUnit;	/**< ĳ�� �ŷ��� �⺻ ���� ���ϴ����� ���� <br> */
	int				m_iPointTradeUnit;	/**< ����Ʈ �ŷ��� �⺻ ���� ���� ������ ���� <br> */
	int				m_iCashFee;			/**< ĳ�� �ŷ��� ������ ���ϴ� �� <br> */
	int				m_iPointFee;		/**< ����Ʈ �ŷ��� ������ ���ϴ� ��<br> */
};






