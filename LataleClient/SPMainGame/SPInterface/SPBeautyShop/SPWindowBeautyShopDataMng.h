
#pragma once 

#include <string>
#include <vector>

/**
	BeautyShopData Manager Class
	///< HairStyle, HairColor, 
	///< ���� ����� Interface�� �����Ѵ�.
*/

enum BS_ITEM_STYLE
{
	BS_HAIR = 0,
	BS_HAIR_C,
	BS_EYE,
	BS_EYE_C,
	BS_SKIN,
	BS_ITEM_MAX,
};

enum{
	TYPE_BASIC = 0,
	TYPE_SPECIAL,
	TYPE_EXPERT,
	COLOR_SPECIAL = 50,
};

enum BS_VALID_CHECK {
	CHECK_OK = 0,
	ERROR_CANT_ITEMINFO = -1 ,
	ERROR_HASNT_COUPON	= -2 ,
	ERROR_SAME_CHANGE	= -3 ,
	WARNING_EXPERT_CHANGE  = -4,
	ERROR_COLOR_CHANGE	= -5 ,
	ERROR_ITEM_LIMIT	= -6 ,
} ;

struct BS_CODE_PARSE
{
	int iCode ;			// ������ ID
	int iLayerID ;			// ���̾� ����
	int iGender;			// ����
	int iSpecialID ;		// ����� �ڵ�
	int iSerialID ;			// �ϷĹ�ȣ
	int iColor;				// �÷���
	int iCodeNC;			// �÷��� ������ �ڵ尪

	BS_CODE_PARSE(){
		Clear();
	}
	void Clear(){
		iCode = 0 ;
		iLayerID = 0 ;
		iGender = 0 ;
		iSpecialID = 0 ;
		iSerialID = 0 ;
		iColor = 0 ;
		iCodeNC = 0 ;
	}
};

struct BS_IN_ITEM {
	int itemLayer;
	int itemID ;
	int itemCode ;
	int needItemID1 ;
	int needItemID2 ;
	int positionID ;		///< Sequence No
	std::string strCatego ;
	std::string strDetail ;

	BS_IN_ITEM() {
		Clear() ;
	}
	void insert(int nlay, int iid, int icode, int nid01, int nid02, int pos, char* strC, char* strD) {
		itemLayer = nlay ;
		itemID = iid ;
		itemCode = icode ;
		needItemID1 = nid01 ;
		needItemID2 = nid02 ;
		positionID = pos ;
		strCatego = strC ;
		strDetail = strD ;
	}
	void Clear()	{
		itemLayer = 0 ;
		itemID = 0;
		itemCode = 0;
		needItemID1 = 0;
		needItemID2 = 0;
		positionID = 0;
		strCatego.clear() ;
		strDetail.clear() ;
	}
};


struct BS_INDEX_MNG
{
	int		m_iCurCategoIndex ;
	int		m_iCurDetailIndex ;
	int		m_iPreCategoIndex ;
	int		m_iPreDetailIndex ;
	BS_INDEX_MNG()
	{
		Clear() ;
	}
	void Clear()
	{
		m_iCurCategoIndex = 0;
		m_iCurDetailIndex = 0;
		m_iPreCategoIndex = 0;
		m_iPreDetailIndex = 0;
	}
	void InitCategory(int _catIndex)
	{
		m_iPreCategoIndex = _catIndex;
		m_iCurCategoIndex = _catIndex ;
	}
	void InitDetail(int _detailIndex)
	{
		m_iPreDetailIndex = _detailIndex;
		m_iCurDetailIndex = _detailIndex ;
		if(m_iPreDetailIndex < 0)	 m_iPreDetailIndex = 0 ;
	}
	void PreChange(int _catIndex, int _detailIndex)
	{
		m_iPreCategoIndex = _catIndex ;
		m_iPreDetailIndex = _detailIndex ;
	}
	void SetCategory(int _catIndex)
	{
		m_iPreCategoIndex = m_iCurCategoIndex;
		m_iCurCategoIndex = _catIndex ;
	}
	void SetDetail(int _detailIndex)
	{
		m_iPreDetailIndex = m_iCurDetailIndex;
		m_iCurDetailIndex = _detailIndex ;
	}
};



class BeautyShopUnit;
class BeautyShopItemGroup ;
class BeautyShopItemGroupList;

class BeautyShopManager
{
public:
	BeautyShopManager() ;
	~BeautyShopManager() ;

	void Create() ;		///< ����
	void Init() ;		///< �ʱ�ȭ
	void Clean() ;		//< �޸� ����

	void LoadBeautyShopLDT() ;									///< BeautyShop.LDT���� �б�
	void AddBeautyItem(BS_IN_ITEM in_item) ;					///< LDT Data -> List�� �߰�
	int Parsing_CharCode(int iCharCode, BS_CODE_PARSE* _p) ;	///< ������ ���� �и�

	void SetTestCharSet(int _gender) ;						///< ������� �⺻ ĳ���� ������ ���� �ʱ�ȭ
	int SetDefaultCharSet(int _ItemCode, int _gender, bool bChanged = true) ;	///< ĳ������ ���ô�� Data Setting
	void SetDefaultIndexSet(int _itemLayer);									///< ���� ������ Default Index Setting

	bool OnChangeCategoryLeft(unsigned int);	///< ī�װ� Left
	bool OnChangeCategoryRight(unsigned int);	///< ī�װ� Right
	bool OnChangeDetailLeft(unsigned int);		///< ���γ��� Left
	bool OnChangeDetailRight(unsigned int);		///< ���γ��� Right

	const char* GetCategoryString(bool isCurrend, int _layer, int _gender = 0, int _catego = 0) ;
	const char* GetDetailString(bool isCurrend, int _layer, int _gender = 0, int _catego = 0, int _detail = 0) ;

	bool GetCategoryEnable(int _layer);
	int GetCategoryValue(int _layer)		{ return m_iLayerIndex[_layer].m_iCurCategoIndex ; }
	int GetDetailValue(int _layer)			{ return m_iLayerIndex[_layer].m_iCurDetailIndex ; }
	BeautyShopUnit* GetSelectItem(int _layer);

	// Group count & Item Count
	int GetLayerCount(int _gender, int _layer, int _categ = -1) ;
	int GetHairStyleCount(int _gender, int _categ = -1);
	int GetHairColorCount(int _gender, int _categ = -1);
	int GetEyeStyleCount(int _gender, int _categ = -1);
	int GetEyecolorCount(int _gender, int _categ = -1);
	int GetSkinCount(int _gender, int _categ = -1);

	// Item Valid Check
	int CommitItemValidCheck(int _layer, bool bChecked, CONTAINER_SLOT& _sendSlot1, CONTAINER_SLOT& _sendSlot2);
	int GetExpectItemCode(int _layer);
	bool VerifyBeautyShopLDT() ;

private:
	int		m_iCurGender ;								///< ���� ����
	bool	m_bEnabled[BS_ITEM_MAX];					///< Ȱ��ȭ ����
	bool	m_bLoadFail[BS_ITEM_MAX] ;					///< �⺻ �ε� �Ұ� ����
	BS_INDEX_MNG m_iLayerIndex[BS_ITEM_MAX] ;			///< ��������, ���缱�� Index
	BeautyShopItemGroupList* m_pBSGroup[BS_ITEM_MAX] ;	///< ������ �׷� ����Ʈ
};