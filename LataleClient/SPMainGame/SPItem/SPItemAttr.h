// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPItemAttr
// Comment     : 
// Creation    : metalgeni 2004-11-05 ���� 10:26:19
//***************************************************************************

#pragma once

#include <string>

using namespace std;

enum ITEM_RARE_LIMIT
{
	ITEM_RARE_NORMAL	= 1,	//���
	ITEM_RARE_MAGIC		= 2,	//����
	ITEM_RARE_RARE		= 3,	//����
	ITEM_RARE_ADD1 		= 4,	//�߰�1
	ITEM_RARE_ADD2		= 5,	//�߰�2
};								

enum ITEM_TYPE
{
	ITEM_TYPE_NULL		= 0,
	ITEM_TYPE_FIGURE	= 1,	// ���
	ITEM_TYPE_CONSUME	= 2,	// �Һ�
	ITEM_TYPE_ETC		= 3,	// ��Ÿ
	ITEM_TYPE_EVENT		= 4,			
	ITEM_TYPE_PET		= 5,
	ITEM_TYPE_HOUSING	= 6,	
};

enum ITEMSTATUS_ID {	
	IS_NULL   = -2,
	IS_PARENT = -1,

	IS_EQUIP			= 0,	
	IS_CONSUMABLE		= 1, //IS_USE_INSTANT,
	IS_ETC				= 2,
	IS_EVENT			= 3,
	IS_PET				= 4,
	IS_HOUSING			= 5,

	IS_EQUIP_BATTLE		= 6, // ������ ������ �ǹ��߾��µ� �������� ��ġ���� ������ ����..
	IS_EQUIP_FASHION	= 7,
	//IS_QUEST,
};

/**
 * ������ �����ð� Ÿ�� <br>
*/
enum ITEM_DURATION {
	ITEM_DURATION_NULL			= 0,	//�Ϲ�
	ITEM_DURATION_AMOUNT		= 1,	//���� �ð���
	ITEM_DURATION_QUANTITY		= 2,	//���� �ð���
};



enum ITEM_SUBTYPE
{
	ITEM_SUBTYPE_NULL = 0,
	//(���)
	ITEM_SUBTYPE_EQUIP_EQUIP	=	1,	//���
	ITEM_SUBTYPE_EQUIP_FASHION	=	2,	//�м�
	ITEM_SUBTYPE_EQUIP_EFFECT	=	3,
	//(�Һ�)
	ITEM_SUBTYPE_WASTE_NORMAL	=	1, 	//�Ϲ�
	ITEM_SUBTYPE_WASTE_ENCHANT	=	2,	//��æƮ
	ITEM_SUBTYPE_WASTE_DEFAULT	=	3,	//����Ʈ
	ITEM_SUBTYPE_WASTE_MSGBOARD	=	4,	//[xialin 2008/09/11]add
	ITEM_SUBTYPE_WASTE_SEARCH	=	5,  //���˵���
	ITEM_SUBTYPE_WASTE_FOLLOW	=	6,	//�������
	ITEM_SUBTYPE_WASTE_SNATCH	=	7,	//ץ�˵���

	//(��)
	ITEM_SUBTYPE_PET_EQUIP		=	1,	//�����
	ITEM_SUBTYPE_PET_WASTE		= 	2,	//��Һ�
	//(�̺�Ʈ)
	ITEM_SUBTYPE_EVENT_QUEST	=	1,	//�̺�Ʈ����Ʈ
	ITEM_SUBTYPE_EVENT_GAMBLE	=	2,	//�̺�Ʈ�׺�
};


enum ITEM_EQUIPPOS
{
	ITEM_EQUIPPOS_NULL = 0,		//	null
	//(�ǱԾ�, �м� ����)
	ITEM_EQUIPPOS_HAIRDRESS 		= 1,		//	�Ӹ����
	ITEM_EQUIPPOS_GOGGLE			= 2,		//	�Ȱ�
	ITEM_EQUIPPOS_EARING			= 3,		//	�Ͱ���
	ITEM_EQUIPPOS_SHIRTS			= 4,		//	����
	ITEM_EQUIPPOS_PANTS				= 5,		//	����
	ITEM_EQUIPPOS_CLOAK				= 6,		//	����
	ITEM_EQUIPPOS_GLOVE				= 7,		//	�尩
	ITEM_EQUIPPOS_SHOES				= 8,		//	�Ź�
	ITEM_EQUIPPOS_STOCKING			= 9	,		//	��Ÿŷ
	ITEM_EQUIPPOS_MAKEUP			= 10,		//	�����
	ITEM_EQUIPPOS_STONE				= 11,		//	���ɼ�
	ITEM_EQUIPPOS_RING				= 12,		//	����
	ITEM_EQUIPPOS_ONEHAND_WEAPON	= 13,		//	�Ѽչ���
	ITEM_EQUIPPOS_TWOHAND_WEAPON	= 13,		//	��չ���
	ITEM_EQUIPPOS_SHIELD			= 14,		//	����
	ITEM_EQUIPPOS_ONEPIECE			= 4	,		//	�ѹ���	
	ITEM_EQUIPPOS_DEFAULT_SHORTS	= 1	,		//	�ӿʻ���
	ITEM_EQUIPPOS_DEFAULT_PANTS		= 2	,		//	�ӿ�����
	ITEM_EQUIPPOS_HAIR				= 3	,		//	�Ӹ�ī��
	ITEM_EQUIPPOS_EXPRESSION 		= 4	,		//	��ǥ��
	ITEM_EQUIPPOS_SKIN				= 5	,		//	�Ǻλ�	

	ITEM_EQUIPPOS_PET_HEAD			= 1	,		//	�Ӹ�		��
	ITEM_EQUIPPOS_PET_BODY			= 2	,		//	��			��

	ITEM_EQUIPPOS_ONEHAND_WEAPON2	= 15,		//	�Ѽչ���
	ITEM_EQUIPPOS_TWOHAND_WEAPON2	= 15,		//	��չ���
	ITEM_EQUIPPOS_SHIELD2			= 16,		//	����
};										



enum ITEM_EQUIP_KIND {
	ITEM_EQUIP_KIND_NULL			= 0,	//null
	ITEM_EQUIP_KIND_KNUCKLE			= 1,	//��Ŭ
	ITEM_EQUIP_KIND_DAGGER			= 2,	//�ܰ�
	ITEM_EQUIP_KIND_SWORD			= 3,	//��
	ITEM_EQUIP_KIND_TWOHANDSWORD	= 4,	//��հ�
	ITEM_EQUIP_KIND_SABER			= 5,	//��
	ITEM_EQUIP_KIND_IDORYU			= 6,	//�̵�
	ITEM_EQUIP_KIND_CLUB			= 7,	//�б�
	ITEM_EQUIP_KIND_SPEAR			= 8,	//â
	ITEM_EQUIP_KIND_BOW				= 9,	//Ȱ
	ITEM_EQUIP_KIND_CROSSBOW		= 10,	//����
};


enum ITEM_EQUIP_EFFECT
{
	ITEM_EQUIP_EFFECT_NULL = 0,		//	null	

	//(Pc Status. ȿ�� �� ���� ������ �������� ����)	
	ITEM_EQUIP_EFFECT_CLASS					=	1 ,				//ĳ���� ����
	ITEM_EQUIP_EFFECT_GENDER				=	2 ,				//����
	ITEM_EQUIP_EFFECT_LV					=	3 ,				//���� ����
	ITEM_EQUIP_EFFECT_MONEY					=	4 ,				//���� ��
	ITEM_EQUIP_EFFECT_EXP					=	5 ,				//���� ����ġ
	ITEM_EQUIP_EFFECT_HP					=	6 ,				//���� HP
	ITEM_EQUIP_EFFECT_SP					=	7 ,				//���� SP
	ITEM_EQUIP_EFFECT_CURR_FAME				=	8 ,				//�� ������
	ITEM_EQUIP_EFFECT_BASE_FAME				=	9 ,				//�⺻ ��
	ITEM_EQUIP_EFFECT_ADD_FAME				=	10,				//�� + 
	ITEM_EQUIP_EFFECT_RATIO_FAME			=	11,				//�� %
	ITEM_EQUIP_EFFECT_CURR_ATK				=	12,				//���� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_ATK				=	13,				//�⺻ ���ݷ�
	ITEM_EQUIP_EFFECT_ADD_ATK				=	14,				//���ݷ� +
	ITEM_EQUIP_EFFECT_RATIO_ATK				=	15,				//���ݷ� %
	ITEM_EQUIP_EFFECT_CURR_LUK				=	16,				//���� ���
	ITEM_EQUIP_EFFECT_BASE_LUK				=	17,				//�⺻ ���
	ITEM_EQUIP_EFFECT_ADD_LUK				=	18,				//��� +
	ITEM_EQUIP_EFFECT_RATIO_LUK				=	19,				//��� %
	ITEM_EQUIP_EFFECT_CURR_ELE				=	20,				//���� ������
	ITEM_EQUIP_EFFECT_BASE_ELE				=	21,				//�⺻ ������
	ITEM_EQUIP_EFFECT_ADD_ELE				=	22,				//������ +
	ITEM_EQUIP_EFFECT_RATIO_ELE				=	23,				//������ %
	ITEM_EQUIP_EFFECT_CURR_DEF				=	24,				//���� ����
	ITEM_EQUIP_EFFECT_BASE_DEF				=	25,				//�⺻ ����
	ITEM_EQUIP_EFFECT_ADD_DEF				=	26,				//���� +
	ITEM_EQUIP_EFFECT_RATIO_DEF				=	27,				//���� %
	ITEM_EQUIP_EFFECT_CURR_MHP				=	28,				//���� �ִ� Hp
	ITEM_EQUIP_EFFECT_BASE_MHP				=	29,				//�⺻ �ִ� HP
	ITEM_EQUIP_EFFECT_ADD_MHP				=	30,				//�ִ� HP +
	ITEM_EQUIP_EFFECT_RATIO_MHP				=	31,				//�ִ� HP %
	ITEM_EQUIP_EFFECT_CURR_MSP				=	32,				//���� �ִ� SP
	ITEM_EQUIP_EFFECT_BASE_MSP				=	33,				//�⺻ �ִ� SP
	ITEM_EQUIP_EFFECT_ADD_MSP				=	34,				//�ִ� SP +
	ITEM_EQUIP_EFFECT_RATIO_MSP				=	35,				//�ִ� SP %
	ITEM_EQUIP_EFFECT_CURR_WATER			=	36,				//���� ���Ӽ�
	ITEM_EQUIP_EFFECT_BASE_WATER			=	37,				//�⺻ ���Ӽ�
	ITEM_EQUIP_EFFECT_ADD_WATER				=	38,				//���Ӽ� +
	ITEM_EQUIP_EFFECT_RATIO_WATER			=	39,				//���Ӽ� %
	ITEM_EQUIP_EFFECT_CURR_WIND				=	40,				//���� ǳ�Ӽ�
	ITEM_EQUIP_EFFECT_ADD_WIND				=	41,				//�⺻ ǳ�Ӽ�
	ITEM_EQUIP_EFFECT_BASE_WIND				=	42,				//ǳ�Ӽ� +
	ITEM_EQUIP_EFFECT_RATIO_WIND			=	43,				//ǳ�Ӽ� %
	ITEM_EQUIP_EFFECT_CURR_FIRE				=	44,				//���� ȭ�Ӽ�
	ITEM_EQUIP_EFFECT_BASE_FIRE				=	45,				//�⺻ ȭ�Ӽ�
	ITEM_EQUIP_EFFECT_ADD_FIRE				=	46,				//ȭ�Ӽ� +
	ITEM_EQUIP_EFFECT_RATIO_FIRE			=	47,				//ȭ�Ӽ� %
	ITEM_EQUIP_EFFECT_CURR_EARTH			=	48,				//���� ���Ӽ�
	ITEM_EQUIP_EFFECT_BASE_EARTH			=	49,				//�⺻ ���Ӽ�
	ITEM_EQUIP_EFFECT_ADD_EARTH				=	50,				//���Ӽ� +
	ITEM_EQUIP_EFFECT_RATIO_EARTH			=	51,				//���Ӽ� %
	ITEM_EQUIP_EFFECT_CURR_RECV_HP			=	52,				//���� ȸ�� HP
	ITEM_EQUIP_EFFECT_BASE_RECV_HP			=	53,				//�⺻ ȸ�� HP
	ITEM_EQUIP_EFFECT_ADD_RECV_HP			=	54,				//ȸ�� HP +
	ITEM_EQUIP_EFFECT_RATIO_RECV_HP			=	55,				//ȸ�� HP %
	ITEM_EQUIP_EFFECT_CURR_RECV_SP			=	56,				//���� ȸ�� SP
	ITEM_EQUIP_EFFECT_BASE_RECV_SP			=	57,				//�⺻ ȸ�� SP
	ITEM_EQUIP_EFFECT_ADD_RECV_SP			=	58,				//ȸ�� SP +
	ITEM_EQUIP_EFFECT_RATIO_RECV_SP			=	59,				//ȸ�� SP %
	ITEM_EQUIP_EFFECT_CURR_HEAVY			=	60,				//���� ���� ���� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_HEAVY			=	61,				//�⺻ ���� ���� ���ݷ�
	ITEM_EQUIP_EFFECT_ADD_HEAVY				=	62,				//���� ���� ���ݷ� +
	ITEM_EQUIP_EFFECT_RATIO_HEAVY			=	63,				//���� ���� ���ݷ� %
	ITEM_EQUIP_EFFECT_CURR_NORMAL			=	64,				//���� ���� �Ϲ� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_NORMAL			=	65,				//�⺻ ���� �Ϲ� ���ݷ�
	ITEM_EQUIP_EFFECT_ADD_NORMAL			=	66,				//���� �Ϲ� ���ݷ� +
	ITEM_EQUIP_EFFECT_RATIO_NORMAL			=	67,				//���� �Ϲ� ���ݷ� %
	ITEM_EQUIP_EFFECT_CURR_MP_WATER			=	68,				//���� ���Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_MP_WATER			=	69,				//�⺻ ���Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_CURR_MP_WIND			=	70,				//���� ǳ�Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_ADD_MP_WIND			=	71,				//�⺻ ǳ�Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_CURR_MP_FIRE			=	72,				//���� ȭ�Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_MP_FIRE			=	73,				//�⺻ ȭ�Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_CURR_MP_EARTH			=	74,				//���� ���Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_MP_EARTH			=	75,				//�⺻ ���Ӽ� ���ݷ�
	ITEM_EQUIP_EFFECT_ADD_MP_ELEMENTAL		=	76,				//���� ���ݷ� +(�� �Ӽ� ����)
	ITEM_EQUIP_EFFECT_RATIO_MP_ELEMENTAL	=	77,				//���� ���ݷ� %(�� �Ӽ� ����)
	ITEM_EQUIP_EFFECT_CURR_AP_HEAVY			=	78,				//���� ���� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_AP_HEAVY			=	79,				//�⺻ ���� ���ݷ�
	ITEM_EQUIP_EFFECT_CURR_AP_NORMAL		=	80,				//���� �Ϲ� ���ݷ�
	ITEM_EQUIP_EFFECT_BASE_AP_NORMAL		=	81,				//�⺻ �Ϲ� ���ݷ�
	ITEM_EQUIP_EFFECT_ADD_AP_ATK			=	82,				//���� ���ݷ� +(Heavy, Normal ����)
	ITEM_EQUIP_EFFECT_RATIO_AP_ATK			=	83,				//���� ���ݷ� %(Heavy, Normal ����)
																			
	ITEM_EQUIP_EFFECT_EFFECTID				= 1000	,	//// EffectID	(Effect)

//////////////////////////////////////////////////////////////////////////


			
//////////////////////////////////////////////////////////////////////////



};

enum ICON_MARK {
	ICON_MARK_NULL			= 0,
	ICON_MARK_LOCK			= 1,
	ICON_MARK_FASHION		= 2,
	ICON_MARK_EVENT			= 3,
	ICON_MARK_FANCY			= 4,
	ICON_MARK_MAX			= 5
};

enum CASHITEM_CATEGORY
{
	CI_NULL = 0,
	CI_FASSION = 1,
	CI_PET,
	CI_ETC,
	CI_HOUSING,
	CI_PVP,
	CI_PACKAGE,
	CI_POINT,

	CI_EVENT = 10,
	CI_SEARCH,     //[xialin 2008/07/17] add
};

enum CASHITEM_CATEGORY_SUB1
{
	CIS1_NULL = 0,
	CIS1_DRESS = 1,
	CIS1_HELMET,
	CIS1_SHOES,
	CIS1_GLOVE,
	CIS1_ACCESSARIES,
	CIS1_ETC,
	CIS1_PET,
	CIS1_PET_ETC,
	CIS1_FUNCTIONAL,
	CIS1_BEAUTY,
	CIS1_COMMUNITY,
	CIS1_HOUSING,
	CIS1_PVP,
	CIS1_PACKAGE_FASSION,
	CIS1_PACKAGE_PET,
	CIS1_PACKAGE_HOUSING,
	CIS1_PACKAGE_PVP,
	CIS1_PACKAGE_ETC,

	CIS1_EVENT_NEW,
	CIS1_EVENT_HOT,
	CIS1_EVENT_EVENT,
	CIS1_POINT_FASSION,
	CIS1_POINT_PET,
	CIS1_POINT_FUNCTIONAL,
};

enum CASHITEM_CATEGORY_SUB2
{
	CIS2_NULL = 0,
	CIS2_ONEPEACE = 1,
	CIS2_BLOUSE,
	CIS2_PANTS,
	CIS2_COAT,
	CIS2_HELMET,
	CIS2_HEADBAND,
	CIS2_HAIRPIN,
	CIS2_SHOES,
	CIS2_LEGBAND,
	CIS2_GLOVE,
	CIS2_ARMBAND,
	CIS2_GLASS,
	CIS2_EARING,
	CIS2_MAKEUP,
	CIS2_STOCKINGS,
	CIS2_EMOTICON,
	CIS2_EXPRESS,
	CIS2_EVENT,
	CIS2_CHATTING,
};

enum EQUIP_ID;

struct SPEffectValue {
	ITEM_EQUIP_EFFECT	Effect;
	int					iValue;
};

struct SPItemRequire {
	int					m_iType;
	int					m_iID;
	int					m_iValue1;
	int					m_iValue2;
	SPItemRequire& operator = (const SPItemRequire& indunInfo)
	{
		m_iType		= indunInfo.m_iType		;
		m_iID		= indunInfo.m_iID		;
		m_iValue1	= indunInfo.m_iValue1	;
		m_iValue2	= indunInfo.m_iValue2	;
		return *this;
	}
};


const int ITEM_SET_A_MAX				 = 11;			/**< 11������ �� <br> */
const int ITEM_SET_FUUL_OPTION			 = 4;			/**< Ǯ���ΰ�� �ɼ� �ִ�ġ <br> */

#define MAX_ITEM_OPTION 4
#define MAX_ITEM_EFFECT 4
#define MAX_ITEM_SKILL	4


struct SPItemAttr {
	// m_iCategory, m_iNum, m_iColorID �� ������ Item ID�� �����
	int							m_iCategory			;		//ī�װ�
	int							m_iNum				;		//?
	int							m_iColorID			;		//�÷�
	
	string						m_strName			;
	string						m_strDescription	;
	int							m_iIcon				;
	int							m_iIconIndex		;
	int							m_iGamePrice		;
	int							m_iCashPrice		;
	ITEM_RARE_LIMIT				m_eRareLimit		;
	ITEM_TYPE					m_eType				;
	ITEM_SUBTYPE				m_eSubType			;
	ITEM_EQUIPPOS				m_ePosID1			;
	ITEM_EQUIPPOS				m_eSubPosID11		;
	ITEM_EQUIPPOS				m_eSubPosID12		;
	ITEM_EQUIPPOS				m_ePosID2			;
	ITEM_EQUIPPOS				m_eSubPosID21		;
	ITEM_EQUIPPOS				m_eSubPosID22		;
	ITEM_EQUIP_KIND				m_eKind				;

	SPEffectValue				m_StatusType	[MAX_ITEM_OPTION];
	SPEffectValue				m_StatusTypePvp [MAX_ITEM_OPTION];	//PVP�� ���Ǵ� �����۽���
	SPItemRequire				m_RequireType	[MAX_ITEM_OPTION];
	//ITEM_EQUIP_EFFECT			m_eStatusType1		;
	//int							m_iStatusValue1		;
	//ITEM_EQUIP_EFFECT			m_eStatusType2      ;   
	//int							m_iStatusValue2     ;   
	//ITEM_EQUIP_EFFECT			m_eStatusType3      ;   
	//int							m_iStatusValue3     ;   
	//ITEM_EQUIP_EFFECT			m_eStatusType4      ;   
	//int							m_iStatusValue4     ;   
	//ITEM_EQUIP_EFFECT			m_eRequireType1		;
	//int							m_iRequireValue1    ;   
	//ITEM_EQUIP_EFFECT			m_eRequireType2     ;   
	//int							m_iRequireValue2    ;   
	//ITEM_EQUIP_EFFECT			m_eRequireType3     ;   
	//int							m_iRequireValue3    ;   
	//ITEM_EQUIP_EFFECT			m_eRequireType4     ;   
	//int							m_iRequireValue4    ;   

	int							m_iCoolTime1		;
	int							m_iCoolTime2		;
	int							m_iCoolTimeApplyID1	;
	int							m_iCoolTimeApplyID2	;
	int							m_iItemCoolTimeID	;
	bool						m_bCashCheck		;
	int							m_iDurationTime		;
	int							m_iStackLimit		;
	int							m_iItemLv			;
	bool						m_bLogging			;
	bool						m_bSerialized		;
	bool						m_bTrade			;
	bool						m_bDestroy			;
	bool						m_bStorage			;
	bool						m_bSell				;
	int							m_iItemPointMin		;
	int							m_iItemPointMax		;
	int							m_iOptionID1		;
	int							m_iOptionID2		;
	int							m_iOptionID3		;
	int							m_iOptionID4		;
	int							m_iMotionTypeID1	;
	int							m_iMotionTypeID2	;
	int							m_iEffectID[ MAX_ITEM_EFFECT ];	// ȿ�� ID  AJJIYA [7/21/2006]
	int							m_iOptionType		;
	int							m_iOptionClass		;
	
	ICON_MARK 					m_eIconMark			;	// �����ܿ� �߰� ǥ��

	bool						m_bNameColor		;	// �켱���� �̸� �÷�
	byte						m_cRed				;
	byte						m_cGreen			;
	byte						m_cBlue				;

	ITEM_DURATION				m_eDuration			;	// �ð� ������ ���� Ÿ��
	int							m_iLifeTime			;	// �������������� �ð�

	int							m_iMacroType;

	unsigned int				m_iPetClassID;
	INT64						m_iPetMaxExp;
	int							m_iSkillID[MAX_ITEM_SKILL];
	int							m_iSkillLevel[MAX_ITEM_SKILL];
	int							m_iConsumeSP[MAX_ITEM_SKILL];

	int							m_iSetID;						/**< �������� Set ID <br> */
	int							m_iQuestID;						// �������� ����Ʈ ID �̺�Ʈ�϶��� ��� [10/2/2007 AJJIYA]
	bool						m_bPvp;							/**< Pvp������ ��� ���� ���� �ʵ� <br> */
	int							m_iCashPoint;					//ĳ������Ʈ

	int							m_iItemLevel;					/**< ������ ���� <br> */
	int							m_iAuctionCategory;				/**< ��� ���� <br> */
	int							m_iAuctionQuality;				/**< ��� ǰ�� <br> */
	int							m_iShopID;						/**< ĳ�ü� ID <br> */

	int							m_iCash;						/**< ĳ�� �ŷ� �� <br> */
	int							m_iPoint;						/**< ����Ʈ �ŷ� �� <br> */

	int							m_iNewPet;						//!< 1 for new pet, 0 fo old pet

	bool						m_bWedding;						/**< ��ȥ ���������� <br> true�� ��� ��ȥ ������ <br> */  

	SPItemAttr();	
	void	SetNull();
	virtual ~SPItemAttr();
	
	/**
	 * �켱���� ������ �̸� �÷��� �����´� <br> 
	 @param NONE
	 @return D3DXCOLOR
	*/
	D3DXCOLOR GetNameColor();
	
	/**
	 * 
	 @param 
	 @return
	*/
	ITEM_DURATION GetDurationType();	
	
	bool GetConvertFigureItem(FIGURE_ITEM* pFigureItem);

	void SetCash(int iCash);
	void SetPoint(int iPoint);
};

struct SPCashItemInfo
{
	int iID;
	int iRare;
	int iCount;
	int iPriceRate;

	SPCashItemInfo()
	{
		iID = 0;
		iRare = 0;
		iCount = 0;
		iPriceRate = 0;
	}
};

#define CASHITEMINFO_COUNT		8
#define CASHITEM_REQUIRE_NUM	3

struct SPCashItemAttr
{
	CASHITEM_CATEGORY eCategory;
	CASHITEM_CATEGORY_SUB1 eCategorySub1;
	CASHITEM_CATEGORY_SUB2 eCategorySub2;

	bool bView;
	int iCashID;
	int iPositionIndex;
	int iEventPage;
	int iIcon;
	int iIconIndex;
	int iPrice;
	int iSalePrice;
	int iEventIcon;
	int iMaxOZ;
	int iMaxMile;
	int iGender;
	int iMotionID;
	int iClassID;
	bool bBuyDisable;
	bool bGiftDisable;

	SPCashItemInfo ItemInfo[ CASHITEMINFO_COUNT ];
	SPItemRequire ItemRequire[CASHITEM_REQUIRE_NUM];
	
	string strName;
	string strDescription;
	string strHotDesc;

	SPCashItemAttr()
	{
		eCategory = CI_NULL;
		eCategorySub1 = CIS1_NULL;
		eCategorySub2 = CIS2_NULL;
		iCashID = 0;
		iPositionIndex = 0;
		iEventPage = 0;
		iIcon = 0;
		iIconIndex = 0;
		iPrice = 0;
		iSalePrice = 0;
		iEventIcon = 0;
		iMaxOZ = 0;
		iMaxMile = 0;
		iGender = 0;
		iMotionID = 0;
		iClassID = 0;
		bView = true;
		bBuyDisable = false;
		bGiftDisable = false;

		strName.clear();
		strDescription.clear();
		strHotDesc.clear();
	}

	void ClearHotDesc() {
		strHotDesc.clear();
	}

	void SetHotDesc(string strDesc) {
		strHotDesc.clear();
		strHotDesc = strDesc;
	}

	void UpdateCashPrize();
};

struct SPItemEnchant
{
	int iEnchantKey;
	int iItemOptionType;
	int iItemOptionClass;
	int iItemOptionGroup;
	int iItemOptionLevel;
	bool bItemOptionCheck;

	int iMaterialID;
	int iMaterialNum;

	int iOPMin;
	int iOPMax;
	int iProbabilityModifier;
	int iProbabilityMin;
	int iProbabilityMax;

	int iResult;
	int iWhenFailed;
	string strDescription;
	string strErrorMsg;

	SPItemRequire RequireType[4];
};

struct SPItemEnchantResult
{
	void* pItem;					// SPItem
	SPItemEnchant* pItemEnchant;
};


struct SPItemTimeAdd
{
	int m_iItemID;								//���� Key (��� Item ID)
	string m_strDesc;							//����
	int m_iResult;								//������ �ð� �߰� ���� �ÿ� �߰��Ǵ� �ð� ���� ����. ������ �ð���(hour)
	
	int m_iMaterialID;							//��� ������ ID
	int m_iMaterialNum;							//��� ����
	SPItemRequire m_Require[MAX_ITEM_OPTION];	//Require
	string m_strErr;							//���� �޽���

	SPItemTimeAdd() {
		Clear();
	}

	~SPItemTimeAdd() {
	}

	void Clear() {		
		m_iItemID			= 0;
		m_iResult			= 0;
		m_iMaterialID		= 0;
		m_iMaterialNum		= 0;

		for(int i = 0; i < MAX_ITEM_OPTION; i++) {
			m_Require[i].m_iID = 0;
			m_Require[i].m_iType = 0;
			m_Require[i].m_iValue1 = 0;
			m_Require[i].m_iValue2 = 0;
		}

		m_strDesc.clear();
		m_strErr.clear();
	}
};
//��Ӱ����
struct SPPhantomLevelUp
{
	
};
//////////////////////////////////////////////////////////////////////////
//
//	ITEM UPGRADE
//	AJJIYA [5/19/2006]
//

enum ITEM_UPGRADE_WHENFAILS
{
	ITEM_UPGRADE_WHENFAILS_NULL			=	0x0000			,	//	������
	ITEM_UPGRADE_WHENFAILS_ORIGINAL		=	0x0001			,	//	���� �ı�
	ITEM_UPGRADE_WHENFAILS_MATERIAL		=	0x0002			,	//	��� �ı�
	ITEM_UPGRADE_WHENFAILS_BOTH			=	0x000F			,	//	��� �ı�
};

enum ITEM_UPGRADE_RARE
{
	ITEM_UPGRADE_RARE_CHEAP				=	1				,	//	LDT �� 1
	ITEM_UPGRADE_RARE_NORMAL								,	//	LDT �� 2
	ITEM_UPGRADE_RARE_ABNOMAL								,	//	LDT �� 3
	ITEM_UPGRADE_RARE_RARE									,	//	LDT �� 4
	ITEM_UPGRADE_RARE_LEGEND								,	//	LDT �� 5
};

enum ITEM_UPGRADE_TYPE
{
	ITEM_UPGRADE_TYPE_NULL				=	0				,
	ITEM_UPGRADE_TYPE_WEAPON								,	//	���
	ITEM_UPGRADE_TYPE_PET									,	//	��
};

struct SPItemUpgradeMaterial
{
	int									m_iID;				//	��� ������ ���̵�
	int									m_iCount;			//	��� ������ ����
	ITEM_UPGRADE_RARE					m_eRare;			//	��� ������ ���
};

#define ITEM_UPGRADE_KEY_SECTION		100					//	������ ���̵�� ����� �и��ϴ� ��
#define MAX_ITEM_UPGRADE_MATERIAL		4
#define MAX_ITEM_UPGRADE_REQUIRE		4

struct SPItemUpgrade
{
	int									m_iLDTItemID;			//	ITEM_UPGRADE.LDT�� ItemID = No.
	std::string							m_strDesc;				//	����
	int									m_iResult;				//	������ ���׷��̵� �Ǵ� ������ ID
	ITEM_UPGRADE_WHENFAILS				m_eWhenFails;			//	���� �������� �ؾ� �ϴ� �۾�
	int									m_iItemID_Original;		//	���� ������ ID
	ITEM_UPGRADE_RARE					m_eRare_Original;		//	���� �������� ���
	int									m_iProbabilityModifier;	//	Ȯ�� ����
	int									m_iProbabilityMin;		//	Ȯ�� �ּ� ��
	int									m_iProbabilityMax;		//	Ȯ�� �ִ� ��
	ITEM_UPGRADE_TYPE					m_eType;				//	������ Ÿ��

	SPItemUpgradeMaterial				m_stMaterial	[ MAX_ITEM_UPGRADE_MATERIAL ];	//	��� ( ���̵� , ���� , ��� )
	SPItemRequire						m_stRequireType	[ MAX_ITEM_UPGRADE_REQUIRE ];	//	�ʿ� ����
};


enum ITEM_SET_OPTION_TYPE {
	ITEM_SET_OPTION_TYPE_NULL,
	ITEM_SET_OPTION_TYPE_STAT,				/**< ȿ���� Stat���� �ٴ� ��� <br> SPEffectValue �� ��� <br> */
	ITEM_SET_OPTION_TYPE_EFFECT,			/**< ȿ���� Effect�� �ٴ� ��� <br> int m_iEffectID �� ��� <br> */
	ITEM_SET_OPTION_TYPE_MAX,
};


/**
* Item Set  �� ���� ȿ�� <br>    
*/
struct SPSetEffect {
	ITEM_SET_OPTION_TYPE	m_iType;			/**< ITEM_SET_OPTION_TYPE ���� <br> */
	SPEffectValue			m_stEffect;			/**< m_iType�� ITEM_SET_OPTION_TYPE_STAT �� ��� <br> */
	int						m_iEffectID;		/**< m_iType�� ITEM_SET_OPTION_TYPE_EFFECT �� ��� <br> */

	SPSetEffect() {
		Clear();
	}

	~SPSetEffect() {
		Clear();
	}

	void Clear() {
		m_iType			= ITEM_SET_OPTION_TYPE_NULL;
		ZeroMemory(&m_stEffect, sizeof(SPEffectValue));
		m_iEffectID		= 0;
	}

	void SetEffect(ITEM_SET_OPTION_TYPE iType, int iStat, int iValue = 0) {		
		if(iType == ITEM_SET_OPTION_TYPE_STAT) {
			m_iType = iType;
			m_stEffect.Effect = (ITEM_EQUIP_EFFECT)iStat;
			m_stEffect.iValue = iValue;
			m_iEffectID = 0;
		}
		else if(iType == ITEM_SET_OPTION_TYPE_EFFECT) {
			m_iType = iType;
			ZeroMemory(&m_stEffect, sizeof(SPEffectValue));
			m_iEffectID = iStat;
		}
	}

	ITEM_SET_OPTION_TYPE GetType() {
		return m_iType;
	}
};

/**
 * Item Set <br>
*/
struct SPItemSet {
	int					m_iSetID;						/**< Set ID <br> */
	std::string			m_strName;						/**< Set Name <br> */
	int					m_iMaxPieces;					/**< Set�� �ƽ� <br> */
	int					m_iCurrentPieces;				/**< ���� �����ϰ� �ִ� ���� <br> GetSetItemEffectB() �Լ� ���� ���� <br> */
	bool				m_bFull;						/**< ���� ���� ������ �ƽ��� �������� ���� <br> */
	SPSetEffect			m_stSetEffect[ITEM_SET_A_MAX];	/**< ������ ���� ȿ�� ���� <br> */
	SPSetEffect			m_stFullSetEffect[ITEM_SET_FUUL_OPTION]; /**< Ǯ�½� ȿ�� ���� <br> */


	SPItemSet() {
		Clear();
	}

	~SPItemSet() {
		Clear();
	}

	void Clear() {
		m_iSetID		= 0;
		m_strName.clear();
		m_iMaxPieces	= 0;
		m_iCurrentPieces = 0;
		m_bFull			= false;
		
		int i = 0;
		for(i = 0; i < ITEM_SET_A_MAX; i++) {
			m_stSetEffect[i].Clear();
		}
		
		for(i = 0; i < ITEM_SET_FUUL_OPTION; i++) {
			m_stFullSetEffect[i].Clear();
		}
	}

	SPSetEffect*	GetEffect(int iIndex) {
		if(iIndex < 0 || iIndex >= ITEM_SET_A_MAX)
			return NULL;

		return &m_stSetEffect[iIndex];
	}

	SPSetEffect*	GetFullEffect(int iIndex) {
		if(iIndex < 0 || iIndex >= ITEM_SET_FUUL_OPTION)
			return NULL;

		return &m_stFullSetEffect[iIndex];
	}

	void	SetCurrentPieces(int iTotalCount) {
		m_iCurrentPieces = iTotalCount;
		m_bFull = false;
		if(m_iCurrentPieces == m_iMaxPieces)
			m_bFull = true;
	}
};

#define MAX_ITEM_MIX_MATERIAL				5
#define MAX_ITEM_MIX_REQUIRE				4
#define MAX_ITEM_MIX_RARE_PROBABILITY		5

/**
* Item Mixt <br>
*/
struct SPItemMix
{
	int									m_iItemMixID;											//	Ldt ItemID = No.
	std::string							m_strName;												//	�̸�
	int									m_iResult;												//	��� ������ ���̵�
	int									m_iResultCount;											//	��� ������ ����
	int									m_iWhenFails;											//	���� ������ �����Ǵ� ������
	int									m_iWhenFailsCount;										//	���� ������ ����
	int									m_iSkillID;												//	��ũ�� ��ų ���̵�
	int									m_iCategory;											//	ī�װ�
	SPItemRequire						m_stRequireType	[ MAX_ITEM_MIX_REQUIRE ];				//	�ʿ� ���� 4��
	SPItemUpgradeMaterial				m_stMaterial	[ MAX_ITEM_MIX_MATERIAL ];				//	��� ( ���̵� , ���� , ��� )

	int									m_iOptMin;												//	������ �ּ� �� ����
	int									m_iOptMax;												//	������ �ִ� �� ����
	int									m_iSuccess_Probability;									//	���� Ȯ�� ����
	int									m_iRare_Probability[ MAX_ITEM_MIX_RARE_PROBABILITY ];	//	�ɼ� �߻� Ȯ��
	int									m_iUpDex_Success_Min;									//	���õ� ���� �ּ� ��
	int									m_iUpDex_Success_Max;									//	���õ� ���� �ִ� ��
	int									m_iUpDex_Fail_Min;										//	���õ� ���� �ּ� ��
	int									m_iUpDex_Fail_Max;										//	���õ� ���� �ִ� ��
	int									m_iBase_Lv;												//	���̽� ����
	int									m_iSuccess_Probability_Min;								//	�ּ� ���� Ȯ��
	int									m_iSuccess_Probability_Max;								//	�ִ� ���� Ȯ��
	int									m_iSuccess_Probability_Revision;						//	���� Ȯ�� ����
};

struct SPCashItemMiss
{
	int   iItemID;
	int   iCashItemID;
	int   iCategory;
	int   iCategorySub1;
	int   iCategorySub2;
};

struct SPCashItemSultlist
{
	int   iCashItem[10];
};

struct SPCashEffectItem
{
	int     iItemID;
	int     iCashNum;
	int     iEffectID[4];
	string  strName;

	SPCashEffectItem()
	{
		iItemID = 0;
		iCashNum = 0;
		for (int i=0; i<4; i++)
			iEffectID[i] = 0;
		strName = "";
	}
};

