#pragma once

#include <vector>
#include <string>

using namespace std;

enum	ITEMSTATUS_ID;
class	SPTexture;

//#define ITEM_SEARCH_HEADER()	std::vector< SPItemStatus* >::iterator iter = m_vpItem.begin(); \
//								iter = std::find_if( m_vpItem.begin(), m_vpItem.end(), std::bind2nd( IsEqualItem, nItemUID ) );\
//								if(iter==m_vpItem.end())\
//								{return 0;}



//////////////////////////////////////////////////////////////////////////
// Item �� ���� ��� ������ ������ �ִ� Ŭ���� 
class SPItemStatus;
enum ICON_MARK;
enum CASHITEM_CATEGORY;
enum ITEM_DURATION;
struct SPItemAttr;
struct SPCashItemAttr;
struct SPItemEnchant;
struct SPItemUpgrade;
struct SPItemTimeAdd;
struct SPItemSet;
struct SPItemMix;
struct SPPhantomLevelUp;
struct SPCashItemMiss;
struct SPCashItemSultlist;
struct SPCashEffectItem;

struct SPItemOption
{
	std::string			m_strName;			//	�̸�  [12/5/2005] ���� �̸������� �ɼ� ǥ��.
	std::string			m_strDesc;			//	����
	int					m_iEffect;			//	ȿ��
	int					m_iEffectType;		//	ȿ�� ����
	int					m_iOptionMin;		//	�ɼ� �ּ� ��
	int					m_iOptionMax;		//	�ɼ� �ִ� ��
	int					m_iEnchantMin;		//	��æƮ �ּ� ��
	int					m_iEnchantMax;		//	��æƮ �ִ� ��
	int					m_iAppType;
	int					m_iOptionGroup;
	int					m_iOptionLevel;

	SPItemOption			();
	void	SetNull			();
	virtual ~SPItemOption	();
};

enum SPITEM_UPGRADE_STATE
{
	SPIU_STATE_NULL				=	0	,
	SPIU_STATE_ITEM_UPGRADE				,
	SPIU_STATE_PET_LEVELUP				,
	SPIU_STATE_ITEM_MIX					,
};


class SPItemCluster {
public:	
	SPItemCluster();
	~SPItemCluster();

	bool		Init();
	bool		LoadLDTItem(const char* szFileName, bool bLoadPvp = false);	
	bool		LoadLDTOption();
	bool		LoadLDTCashItem();
	bool		LoadLDTEnchant();
	bool		LoadLDTUpgrade();	
	bool		LoadLDTItemSet();
	bool		LoadLDTMix();
	bool		LoadLDTCashMiss();
	bool		LoadLDTSultList();
	bool		LoadLDTCashEffect();
	
	/**
	 * 
	 @param 
	 @return
	*/
	bool		LoadLDTTimeAdd();
	bool		LoadLDTPhantomUp();//��Ӱ����
	//void		InsertItem(int nItemUID, ITEMSTATUS_ID eClass, int nXSrcPos, int nYSrcPos, string itemName, string itemDesc, int nStackCnt=1);
	//void		InsertItem( int , int, int, int, int, string , int nType, int nSubType, int nPosID1, int nSubPosID11=0, int nPosID2=0, int nSubPosID21=0, int nStackCnt=0);	


	int			GetItemInfo(int nItemUID, string& itemName, string& itemDesc);

	//int		GetEquipID(int nItemUID);			// equip
	//int		GetStackCount(int nItemUID);		// comsume
	//int		GetPosID(int nItemUID, int &nPosID1, int &nSubPosID1, int &nPosID2, int &nSubPosID2);
	//int 		GetPosID(int nItemUID, int &nPosID1 );

	//int			GetType( int nItemUID, int &nType);
	//int			GetSubType( int nItemUID, int &nSubType);

	SPTexture*	GetItemTexture(int iItemID, POINT& ptSrcPos);
	SPTexture*	GetItemTextureFromTextureInx(int iIconImage, int iIconIndex, POINT& ptSrcPos);
	const char*	GetItemTextureStr(int iItemID, POINT& ptSrcPos);
	const char* GetItemTextureStrFromTextureInx(int iIconImage, int iIconIndex,POINT& ptSrcPos);

	SPTexture*	GetNumTexture();

	ICON_MARK	GetItemIconMark(int iItemID);			//[2006/2/10] ������ ��ũ ������ ������

	bool		IsItemNameColor(int iItemID);			//[2006/2/13] ������ �̸��� Ư���� �÷��� ����ϴ���
	D3DXCOLOR	GetItemNameColor(int iItemID);			//[2006/2/13] ������ �̸��� Ư���� �÷��� ����ϴ� ��� �ش� ���� �����´� 

	bool		GetItemInfo(int iItemID, SPItemAttr*& pItemAttr);

	SPCashItemAttr* GetCaseListItem(int iIndex);

	SPItemOption*	GetItemOption( UINT32 uiItemOptionID );

	int GetSortCashItemSize(int iCategory);
	SPCashItemAttr* GetSortCashItem(int iCategory, int iIndex);
	SPCashItemAttr* GetCashItem(int iID);
	SPCashItemAttr* GetMinorCashItem(int iID);
	void SortCashItem();
	void SortCashItem(int iGender, int iPrice);
	void RandCashItem();				//[xialin 2008/07/17] add �����Ʒ����
	int  GetRandStoreCashCategory(int iCategory, int iIndex); //[xialin 2008/07/17] add
	void SetCashVersion(int iMajor, int iMinor);
	void GetCashVersion(int& iMajor, int& iMinor);
	void InitMinorCashItem();
	void UpdateMinorCashItem(CASHSHOP_INFO* pItemInfo);
	void InsertMinorCashItem(SPCashItemAttr& tItemAttr);
	void EraseMinorCashItem(int iID);	
	bool RefreshCaseList(SPCashItemAttr* pkItemAttr);
	/**
	 * �־��� CashItemAttr �� �����ϴ� �������� ���� ������ �����Ѵ� <br>
	 * ī�װ��� ��Ű���� ��쿡�� ���� ���� �ʴ´� <br> 
	 @param SPCashItemAttr* pCashItemAttr
	 @return  
	*/
	//void UpdateItemCashPrize(SPCashItemAttr* pCashItemAttr);

	/**  
	 * ItemCluster�� ��� �������� CashShopID�� �ִ� ��� <br>
	 * �ش� CashShop ������ Cash, mile�� ItemAttr�� ������Ʈ �Ѵ� <br>
	 @param  
	 @return 
	*/  
	void UpdateItemCashPrize();

	bool InsertItemEnchant(int iKey, SPItemEnchant& ItemEnchant);
	SPItemEnchant* GetExactItemEnchant(int iOptionID, int iMaterialID, int iMaterialNum);
	SPItemEnchant* GetItemEnchant(int iOptionID, int iMaterialID, int iMaterialNum);
	bool IsItemEnchant(int iOptionID);
	bool IsItemEnchant(int iOptionID, int iMaterialID);

	bool					InsertItemUpgrade( SPItemUpgrade& ItemUpgrade );//need
	bool					IsItemUpgrade( int iItemID , int iRare );
	SPItemUpgrade*			GetItemUpgrade( int iItemID , int iRare );
	__int64					GetItemUpgradeKey( int iItemID , int iRare );
	SPITEM_UPGRADE_STATE	GetItemUpgradeState();
	void					SetItemUpgradeState( SPITEM_UPGRADE_STATE eState );

	bool			InsertItemTimeAdd(SPItemTimeAdd& ItemTimeAdd);
	bool			IsItemTimeAdd(int iItemID);			/**< �ð������� ������ ���������� Ȯ�� <br> */
	SPItemTimeAdd*	GetItemTimeAdd(int iItemID);

	bool				InsertPhantomLevelUp( SPPhantomLevelUp& PhantomLevelUp );//�����Ӱ
	bool				IsPhantomLevelUp( int iItemID );//�ж��Ƿ��ǿ������Ļ�Ӱ����
	SPPhantomLevelUp*	GetPhantomLevelUp( int iItemID); //�õ������Ӱ���ߵĽṹ��
	
	bool			InsertItemSet(SPItemSet& ItemSetB);
	bool			IsItemSet(int iSetID);
	SPItemSet*		GetItemSet(int iSetID);

	SPCashEffectItem*   GetEffectByID(int iID);
	SPCashEffectItem*   GetEffectByName(const char * pszName);


	ITEM_DURATION GetItemDuration(int iItemID);

	bool												InsertItemMix			( SPItemMix& stItemMixAdd );
	bool												IsItemMix				( int iSkillID , int iItemMixID );
	std::map< int , std::map< int , SPItemMix > >*		GetItemMixSkillID		( int iSkillID );
	std::map< int , SPItemMix >*						GetItemMixCategory		( int iSkillID , int iCategory );
	SPItemMix*											GetItemMixItemMixID		( int iSkillID , int iItemMixID );

	void            SetSearchKey(string  strKey) { m_strKeyName = strKey; }

protected:

	std::vector< SPItemStatus* >	m_vpItem;

	stdext::hash_map<UINT32, SPItemAttr*>	m_hmItem;
	stdext::hash_map<UINT32, SPTexture*>	m_hmIconTexture;

	std::map< UINT32 , SPItemOption >		m_mItemOption;

	int m_iCashMajorVersion;
	int m_iCashMinorVersion;
	std::vector< SPCashItemAttr > m_vCashItem;
	std::vector< SPCashItemAttr > m_vMinorCashItem;
	std::vector< SPCashItemAttr* > m_vSortCashItem;
	std::map< int, std::vector< SPItemEnchant > > m_mItemEnchant;

	std::map< __int64 , SPItemUpgrade >		m_mItemUpgrade;
	SPITEM_UPGRADE_STATE					m_eItemUpgradeState;

	std::map<int, SPItemTimeAdd>			m_mItemTime;
	std::map<int, SPPhantomLevelUp>			m_mPhantom;//��Ӱ
	std::map<int, SPItemSet>				m_mItemSet;
	std::map< int , std::map< int , std::map< int , SPItemMix > > >		m_mmmItemMix;			//	SkillID , Category , ItemMixID

	SPTexture*			m_pItemTexture;	
	SPTexture*			m_pItemNumTexture;

	std::string                      m_strKeyName;           //[xialin 2008/07/17] �����ؼ���
	std::vector<SPCashItemMiss>      m_vecRandItem;          //[xialin 2008/07/17] �����������Ʒ��Ӧ��
	std::vector<SPCashItemSultlist>  m_vecCaseItem;          //[xialin 2008/07/17] ��װ��Ӧ��
	std::vector<SPCashItemAttr*>     m_vecCurCaseList;       //[xialin 2008/07/25] ��ǰ��װ��
	std::vector<SPCashEffectItem>    m_vecCaseEffect;        //[xialin 2008/07/28] add

};


extern SPItemCluster* g_pItemCluster;


