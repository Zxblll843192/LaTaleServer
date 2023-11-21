
#include <string>
#include <vector>

#ifndef EMPTY_NODE
#define EMPTY_NODE	-1
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif




/**
	BeautyShop Item
	///< ItemUNIT�� �ش� ��
*/
class BeautyShopUnit
{
public:
	BeautyShopUnit() {}
	BeautyShopUnit(int _itemID, int _itemCode, int _layer, int _groupID, int _itemSeq, const char* _strItemName, int _needItemCode1, int _needItemCode2) \
		:m_iItemID(_itemID), m_iItemCode(_itemCode), m_iItemLayer(_layer), m_iGroupID(_groupID), m_iItemSeq(_itemSeq), m_iNeedItemCode1(_needItemCode1), m_iNeedItemCode2(_needItemCode2), m_strItemName(_strItemName){}
	virtual ~BeautyShopUnit()  {}
	
	void SetItemData(int _itemID, int _itemCode, int _layer, int _groupID, int _itemSeq, char* _strItemName, int _needItemCode1, int _needItemCode2 = 0)
	{
		m_iItemID = _itemID ;
		m_iItemCode = _itemCode ;
		m_iItemLayer = _layer ;
		m_iGroupID = m_iGroupID;
		m_iItemSeq = _itemSeq ;
		m_iNeedItemCode1 = _needItemCode1 ;
		m_iNeedItemCode2 = _needItemCode2 ;
		m_strItemName = _strItemName ;
	}
	
	void operator=(const BeautyShopUnit& Src) {
		m_iItemID = Src.m_iItemID;
		m_iItemCode = Src.m_iItemCode;
		m_iItemLayer = Src.m_iItemLayer ;
		m_iGroupID = Src.m_iGroupID;
		m_iItemSeq = Src.m_iItemSeq;
		m_strItemName = Src.m_strItemName.c_str();
		m_iNeedItemCode1 = Src.m_iNeedItemCode1;
		m_iNeedItemCode2 = Src.m_iNeedItemCode2;
	}
	bool operator==(const BeautyShopUnit& Src) {
		return ( m_iItemCode == Src.m_iItemCode ) ? true : false ;
	}

public:
	int m_iItemID ;				///< Item ID
	int m_iItemCode ;			///< Item Code
	int m_iItemLayer;			///< Hair, Color, Eye
	int m_iGroupID ;			///< Normal, Special, Expert
	int m_iItemSeq ;			///< Item Sequence Number
	int m_iNeedItemCode1 ;	///< Require Code
	int m_iNeedItemCode2 ;	///< Require Code
	std::string	m_strItemName ;	///< Name
};



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
BeautyShop Item Group
///< �Ϲ�, �����, ������... � �ش��
*/
class BeautyShopItemGroup
{
public:
	BeautyShopItemGroup(int _groupCode, int _groupIndex, const char* _strGroupName);
	virtual ~BeautyShopItemGroup();

	void Clean();


	///< Item �߰�
	bool AddItemNode(int _itemID, int _itemCode, int _layer, int _groupID, int _itemSeq, const char* _strItemName, int _needItemCode1, int _needItemCode2=0) ;


	///< ItemID�� �ش� �������� ã�´�.
	BeautyShopUnit* FindItemByID(int _itemID);
	///< ItemCode�� �ش� �������� ã�´�.
	BeautyShopUnit* FindItemByCode(int _itemCode);
	///< ItemCode�� �ش� �������� ã�´�.
	int FindItemIndexByCode(int _itemCode);


	///< Item�� Index�� ItemNode�� �����͸� ���´�.
	const char*	GetGroupName();
	int		GetGroupCount();
	int		GetGroupCode();
	int		GetGroupIndex();

	BeautyShopUnit*	GetItemNode(int _index);
	const char*		GetItemName(int _index);

public:
	int				m_iGroupCode ;
	int				m_iGroupIndex ;
	std::string		m_strGroupName ;
	std::vector<BeautyShopUnit*>	m_vpItemNode;
};



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
BeautyShop Item GroupList 
///< ��Ÿ��, ��� �÷� �� �ش��
*/
class BeautyShopItemGroupList
{
public:
	BeautyShopItemGroupList();
	virtual ~BeautyShopItemGroupList();

	virtual void Init()	;
	void Clean();


	/**
	������ �߰� : �׷��� ���°�� �׷��� �߰��ؼ� �ֵ��� �Ѵ�.
	@param int _gender: ����
	@param int _groupID : �׷� ID
	@param int _groupName : �׷� �̸�
	@param BeautyShopUnit* _pItem : �߰��� ������ Ŭ����
	*/
	bool AddItem(int _gender, int _layer, int _groupID, const char* _groupName, int _itemID, int _itemCode, int _itemSeq, const char* _itemName, int _needItemCode1, int _needItemCode2=0);


	/**
	������ ã��
	@param int _gender : ����
	@param int _groupID : �׷� ID
	@param int _itemCode : ������ �ڵ�
	*/
	BeautyShopUnit* FindItemByCode(int _gender, int _groupID, int _itemCode);
	BeautyShopUnit* FindItemByID(int _gender, int _groupID, int _itemID);	
	BeautyShopUnit* FindItemByIndex(int _gender, int _groupID, int _itemIndex);

	///< ������ �ڵ�� �������� Index�� ����
	int FindItemIndexByCode(int _gender, int _groupID, int _itemCode);		


	BeautyShopUnit*	GetItemNode(int _gender, int _groupID, int _detail);
	const char*	GetItemNodeName(int _gender, int _groupID, int _detail);			


	///< Group ����
	const char*	GetGroupName(int _gender, int _groupID);
	int			GetGroupCount(int _gender, int _groupID);
	int			GetGroupCode(int _gender, int _groupID);			

	///< GroupList ����
	int		GetGroupListCount(int _gender);
	int		GetGroupIndex(int _gender, int _groupID);

private:
	std::vector<BeautyShopItemGroup*>	m_vpItemGroup[2];
};





////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///**
//	BeautyShop Item Group
//	///< �Ϲ�, �����, ������... � �ش��
//*/
//class BeautyShopItemGroup
//{
//public:
//	BeautyShopItemGroup(int _groupCode, int _groupIndex, const char* _strGroupName) \
//		:m_iGroupCode(_groupCode), m_iGroupIndex(_groupIndex), m_strGroupName(_strGroupName){}
//	virtual ~BeautyShopItemGroup()	{	Clean();	}
//
//	void Clean()
//	{
//		std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
//		for(;Iter != m_vpItemNode.end(); ++Iter) {
//				SAFE_DELETE(*Iter);
//			}
//		m_vpItemNode.clear();
//	}
//
//	///< Item �߰�
//	bool AddItemNode(int _itemID, int _itemCode, int _layer, int _groupID, int _itemSeq, const char* _strItemName, int _needItemCode1, int _needItemCode2=0) 
//	{
//		BeautyShopUnit* pInItem = new BeautyShopUnit(_itemID, _itemCode, _layer, _groupID, _itemSeq, _strItemName, _needItemCode1, _needItemCode2) ;
//		if( _itemSeq < (int)m_vpItemNode.size() )
//		{
//			// Sequence �� ���� ������ �־�� ��.
//			BeautyShopUnit* pItem = NULL ;
//			std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
//			for(;Iter != m_vpItemNode.end(); ++Iter) {
//				pItem = (*Iter) ;
//				if( pItem->m_iItemSeq > _itemSeq )
//				{
//					m_vpItemNode.insert(Iter, pInItem) ;
//					//DXUTOutputDebugString("AdditemNode Insert[%d]-seq[%d] : [%d, %d]", i, _itemSeq, _itemID, _itemCode ) ;
//					return true ;
//				}
//			}
//			m_vpItemNode.push_back(pInItem) ;
//		}
//		else
//			m_vpItemNode.push_back(pInItem) ;
//			
//		return true ;
//	}
//
//
//	///< ItemID�� �ش� �������� ã�´�.
//	BeautyShopUnit* FindItemByID(int _itemID)
//	{
//		BeautyShopUnit* pItem = NULL ;
//		std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
//		for(;Iter != m_vpItemNode.end(); ++Iter) {
//			pItem = (*Iter) ;
//			if( pItem->m_iItemID == _itemID )	{
//				return pItem ;
//			}
//		}
//		return NULL ;
//	}
//
//	///< ItemCode�� �ش� �������� ã�´�.
//	BeautyShopUnit* FindItemByCode(int _itemCode)
//	{
//		BeautyShopUnit* pItem = NULL ;
//		std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
//		for(;Iter != m_vpItemNode.end(); ++Iter) {
//			pItem = (*Iter) ;
//			if( pItem->m_iItemCode == _itemCode )	{
//				return pItem ;
//			}
//		}
//		return NULL ;
//	}
//
//	///< ItemCode�� �ش� �������� ã�´�.
//	int FindItemIndexByCode(int _itemCode)
//	{
//		int iIndex = 0 ;
//		std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
//		for(;Iter != m_vpItemNode.end(); ++Iter) {
//			if( (*Iter)->m_iItemCode == _itemCode )	{
//				return iIndex ;
//			}
//			iIndex++ ;
//		}
//		return 0 ;
//	}
//	
//
//	///< Item�� Index�� ItemNode�� �����͸� ���´�.
//	const char*	GetGroupName()				{	return m_strGroupName.c_str();	}
//	int		GetGroupCount()					{	return (int)m_vpItemNode.size();	}
//	int		GetGroupCode()					{	return m_iGroupCode;	}
//
//	BeautyShopUnit*	GetItemNode(int _index)	{	return (_index > EMPTY_NODE && _index < (int)m_vpItemNode.size())?m_vpItemNode.at(_index) : NULL ;	}
//	const char*		GetItemName(int _index)	{	return (_index > EMPTY_NODE && _index < (int)m_vpItemNode.size())?m_vpItemNode.at(_index)->m_strItemName.c_str() : NULL ;	}
//
//public:
//	int				m_iGroupCode ;
//	int				m_iGroupIndex ;
//	std::string		m_strGroupName ;
//	std::vector<BeautyShopUnit*>	m_vpItemNode;
//};
//
//
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///**
//	BeautyShop Item GroupList 
//	///< ��Ÿ��, ��� �÷� �� �ش��
//*/
//class BeautyShopItemGroupList
//{
//public:
//	BeautyShopItemGroupList()			{	Init();	}
//	virtual ~BeautyShopItemGroupList()	{	Clean();	}
//
//	virtual void Init()	
//	{	
//		m_vpItemGroup[0].clear();
//		m_vpItemGroup[1].clear();
//	}
//	void Clean()
//	{
//		for(int i = 0; i < 2; i++)
//		{
//			std::vector<BeautyShopItemGroup*>::iterator Iter = m_vpItemGroup[i].begin();
//			for(;Iter != m_vpItemGroup[i].end(); ++Iter) {
//				(*Iter)->Clean() ;
//				SAFE_DELETE(*Iter);
//			}
//			m_vpItemGroup[i].clear();
//		}
//	}
//
//	/**
//		������ �߰� : �׷��� ���°�� �׷��� �߰��ؼ� �ֵ��� �Ѵ�.
//		@param int _gender: ����
//		@param int _groupID : �׷� ID
//		@param int _groupName : �׷� �̸�
//		@param BeautyShopUnit* _pItem : �߰��� ������ Ŭ����
//	*/
//	bool AddItem(int _gender, int _layer, int _groupID, const char* _groupName, int _itemID, int _itemCode, int _itemSeq, const char* _itemName, int _needItemCode1, int _needItemCode2=0)
//	{
//		if( _groupID < (int)m_vpItemGroup[_gender].size() )
//		{
//			return m_vpItemGroup[_gender].at(_groupID)->AddItemNode(_itemID, _itemCode, _layer, _groupID, _itemSeq, _itemName, _needItemCode1, _needItemCode2) ;
//		}
//		else
//		{
//			BeautyShopItemGroup* pGroup = new BeautyShopItemGroup(_groupID, (int)m_vpItemGroup[_gender].size(), _groupName) ;
//			m_vpItemGroup[_gender].push_back(pGroup) ;
//			return m_vpItemGroup[_gender].at(_groupID)->AddItemNode(_itemID, _itemCode, _layer, _groupID, _itemSeq, _itemName, _needItemCode1, _needItemCode2) ;
//		}
//	}
//	
//
//	/**
//		������ ã��
//		@param int _gender : ����
//		@param int _groupID : �׷� ID
//		@param int _itemCode : ������ �ڵ�
//	*/
//	BeautyShopUnit* FindItemByCode(int _gender, int _groupID, int _itemCode)	{	return m_vpItemGroup[_gender].at(_groupID)->FindItemByCode(_itemCode) ; }
//	BeautyShopUnit* FindItemByID(int _gender, int _groupID, int _itemID)		{	return m_vpItemGroup[_gender].at(_groupID)->FindItemByID(_itemID) ; }
//	BeautyShopUnit* FindItemByIndex(int _gender, int _groupID, int _itemIndex)	{	return m_vpItemGroup[_gender].at(_groupID)->GetItemNode(_itemIndex) ; }
//	///< ������ �ڵ�� �������� Index�� ����
//	int FindItemIndexByCode(int _gender, int _groupID, int _itemCode)			{	return m_vpItemGroup[_gender].at(_groupID)->FindItemIndexByCode(_itemCode) ; }
//	BeautyShopUnit*	GetItemNode(int _gender, int _groupID, int _detail)			{	return m_vpItemGroup[_gender].at(_groupID)->GetItemNode(_detail) ;	}
//	const char*	GetItemNodeName(int _gender, int _groupID, int _detail)			{	return m_vpItemGroup[_gender].at(_groupID)->GetItemName(_detail) ;	}
//	
//	///< Group ����
//	const char*	GetGroupName(int _gender, int _groupID)			{	return m_vpItemGroup[_gender].at(_groupID)->GetGroupName();	}
//	int			GetGroupCount(int _gender, int _groupID)		{	return m_vpItemGroup[_gender].at(_groupID)->GetGroupCount();	}
//	int			GetGroupCode(int _gender, int _groupID)			{	return m_vpItemGroup[_gender].at(_groupID)->GetGroupCode();	}
//
//	///< GroupList ����
//	int		GetGroupListCount(int _gender)			{	return (int)m_vpItemGroup[_gender].size();	}
//private:
//	std::vector<BeautyShopItemGroup*>	m_vpItemGroup[2];
//};
//
