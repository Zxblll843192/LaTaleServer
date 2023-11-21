
#include "SPWindowBeautyShopDataUnit.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
	BeautyShop Item Group
	///< �Ϲ�, �����, ������... � �ش��
*/

BeautyShopItemGroup::BeautyShopItemGroup(int _groupCode, int _groupIndex, const char* _strGroupName) 
:m_iGroupCode(_groupCode), m_iGroupIndex(_groupIndex), m_strGroupName(_strGroupName)
{
}


BeautyShopItemGroup::~BeautyShopItemGroup()	
{	
	Clean();	
}


void BeautyShopItemGroup::Clean()
{
	std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
	for(;Iter != m_vpItemNode.end(); ++Iter) {
		SAFE_DELETE(*Iter);
	}
	m_vpItemNode.clear();
}


//////////////////////////////////////////////////////////////////////////
///< Item �߰�
bool BeautyShopItemGroup::AddItemNode(int _itemID, int _itemCode, int _layer, int _groupID, int _itemSeq, const char* _strItemName, int _needItemCode1, int _needItemCode2) 
{
	BeautyShopUnit* pInItem = new BeautyShopUnit(_itemID, _itemCode, _layer, _groupID, _itemSeq, _strItemName, _needItemCode1, _needItemCode2) ;
	if( _itemSeq < (int)m_vpItemNode.size() )
	{
		// Sequence �� ���� ������ �־�� ��.
		BeautyShopUnit* pItem = NULL ;
		std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
		for(;Iter != m_vpItemNode.end(); ++Iter) {
			pItem = (*Iter) ;
			if( pItem->m_iItemSeq > _itemSeq )
			{
				m_vpItemNode.insert(Iter, pInItem) ;
				//DXUTOutputDebugString("AdditemNode Insert[%d]-seq[%d] : [%d, %d]", i, _itemSeq, _itemID, _itemCode ) ;
				return true ;
			}
		}
		m_vpItemNode.push_back(pInItem) ;
	}
	else
		m_vpItemNode.push_back(pInItem) ;

	return true ;
}


//////////////////////////////////////////////////////////////////////////
///< ItemID�� �ش� �������� ã�´�.
BeautyShopUnit* BeautyShopItemGroup::FindItemByID(int _itemID)
{
	BeautyShopUnit* pItem = NULL ;
	std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
	for(;Iter != m_vpItemNode.end(); ++Iter) {
		pItem = (*Iter) ;
		if( pItem->m_iItemID == _itemID )	{
			return pItem ;
		}
	}
	return NULL ;
}


//////////////////////////////////////////////////////////////////////////
///< ItemCode�� �ش� �������� ã�´�.
BeautyShopUnit* BeautyShopItemGroup::FindItemByCode(int _itemCode)
{
	BeautyShopUnit* pItem = NULL ;
	std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
	for(;Iter != m_vpItemNode.end(); ++Iter) {
		pItem = (*Iter) ;
		if( pItem->m_iItemCode == _itemCode )	{
			return pItem ;
		}
	}
	return NULL ;
}


//////////////////////////////////////////////////////////////////////////
///< ItemCode�� �ش� �������� ã�´�.
int BeautyShopItemGroup::FindItemIndexByCode(int _itemCode)
{
	int iIndex = 0 ;
	std::vector<BeautyShopUnit*>::iterator Iter = m_vpItemNode.begin();
	for(;Iter != m_vpItemNode.end(); ++Iter) {
		if( (*Iter)->m_iItemCode == _itemCode )	{
			return iIndex ;
		}
		iIndex++ ;
	}
	return 0 ;
}


//////////////////////////////////////////////////////////////////////////
///< Item�� Index�� ItemNode�� �����͸� ���´�.
const char*	BeautyShopItemGroup::GetGroupName()				
{	
	return m_strGroupName.c_str();	
}

int		BeautyShopItemGroup::GetGroupCount()					
{	
	return (int)m_vpItemNode.size();	
}

int		BeautyShopItemGroup::GetGroupCode()					
{	
	return m_iGroupCode;	
}

int		BeautyShopItemGroup::GetGroupIndex()					
{	
	return m_iGroupIndex;	
}

//////////////////////////////////////////////////////////////////////////
//
//	Sequence�� �̿��� Indexing
//	Sequence�� ������ �̾����� �Ѵ�.
//
BeautyShopUnit*	BeautyShopItemGroup::GetItemNode(int _index)	
{	
	return (_index > EMPTY_NODE && _index < (int)m_vpItemNode.size())?m_vpItemNode.at(_index) : NULL ;	
}

const char*		BeautyShopItemGroup::GetItemName(int _index)	
{	
	return (_index > EMPTY_NODE && _index < (int)m_vpItemNode.size())?m_vpItemNode.at(_index)->m_strItemName.c_str() : NULL ;	
}
// Index Search -> Find Search ����
// SEQ�� ����ϹǷ� �״�� Index ���
//BeautyShopUnit*	BeautyShopItemGroup::GetItemNode(int _index)	
//{	
//	int iSize = (int)m_vpItemNode.size() ;
//	if( iSize < 1 )		return NULL ;
//	for( int i = 0; i < iSize; i++ )
//	{
//		int iCode = m_vpItemNode.at(i)->m_iItemCode ;
//		if(iCode % 100 == _index)
//			return m_vpItemNode.at(i) ;
//	}
//	return NULL ;	
//}
//
//const char*		BeautyShopItemGroup::GetItemName(int _index)	
//{	
//	int iSize = (int)m_vpItemNode.size() ;
//	if( iSize < 1 )		return NULL ;
//	for( int i = 0; i < iSize; i++ )
//	{
//		int iCode = m_vpItemNode.at(i)->m_iItemCode ;
//		if( iCode % 100 == _index)
//			return m_vpItemNode.at(i)->m_strItemName.c_str() ;
//	}
//	return NULL ;	
//}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
	BeautyShop Item GroupList 
	///< ��Ÿ��, ��� �÷� �� �ش��
*/

BeautyShopItemGroupList::BeautyShopItemGroupList()	
{	
	Init();	
}


BeautyShopItemGroupList::~BeautyShopItemGroupList()	
{	
	Clean();	
}


void BeautyShopItemGroupList::Init()	
{	
	m_vpItemGroup[0].clear();
	m_vpItemGroup[1].clear();
}


void BeautyShopItemGroupList::Clean()
{
	for(int i = 0; i < 2; i++)
	{
		std::vector<BeautyShopItemGroup*>::iterator Iter = m_vpItemGroup[i].begin();
		for(;Iter != m_vpItemGroup[i].end(); ++Iter) {
			(*Iter)->Clean() ;
			SAFE_DELETE(*Iter);
		}
		m_vpItemGroup[i].clear();
	}
}


/**
	������ �߰� : �׷��� ���°�� �׷��� �߰��ؼ� �ֵ��� �Ѵ�.
	@param int _gender: ����
	@param int _groupID : �׷� ID
	@param int _groupName : �׷� �̸�
	@param BeautyShopUnit* _pItem : �߰��� ������ Ŭ����
*/
bool BeautyShopItemGroupList::AddItem(int _gender, int _layer, int _groupID, const char* _groupName, int _itemID, int _itemCode, int _itemSeq, const char* _itemName, int _needItemCode1, int _needItemCode2)
{
	int _groupIdx ;

	if( _groupID < (int)m_vpItemGroup[_gender].size() )
	{
		if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
			return false ;	
		return m_vpItemGroup[_gender].at(_groupIdx)->AddItemNode(_itemID, _itemCode, _layer, _groupID, _itemSeq, _itemName, _needItemCode1, _needItemCode2) ;
	}
	else
	{
		_groupIdx = (int)m_vpItemGroup[_gender].size() ;
		BeautyShopItemGroup* pGroup = new BeautyShopItemGroup(_groupID, _groupIdx, _groupName) ;
		m_vpItemGroup[_gender].push_back(pGroup) ;
		return m_vpItemGroup[_gender].at(_groupIdx)->AddItemNode(_itemID, _itemCode, _layer, _groupID, _itemSeq, _itemName, _needItemCode1, _needItemCode2) ;
	}
}


/**
	������ ã��
	@param int _gender : ����
	@param int _groupID : �׷� ID
	@param int _itemCode : ������ �ڵ�
*/
BeautyShopUnit* BeautyShopItemGroupList::FindItemByCode(int _gender, int _groupID, int _itemCode)	
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return NULL ;
	return m_vpItemGroup[_gender].at(_groupID)->FindItemByCode(_itemCode) ; 
}

BeautyShopUnit* BeautyShopItemGroupList::FindItemByID(int _gender, int _groupID, int _itemID)		
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return NULL ;
	return m_vpItemGroup[_gender].at(_groupID)->FindItemByID(_itemID) ; 
}

BeautyShopUnit* BeautyShopItemGroupList::FindItemByIndex(int _gender, int _groupID, int _itemIndex)	
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return NULL ;
	return m_vpItemGroup[_gender].at(_groupID)->GetItemNode(_itemIndex) ; 
}

//////////////////////////////////////////////////////////////////////////
///< ������ �ڵ�� �������� Index�� ����
int BeautyShopItemGroupList::FindItemIndexByCode(int _gender, int _groupID, int _itemCode)			
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return -1 ;
	return m_vpItemGroup[_gender].at(_groupID)->FindItemIndexByCode(_itemCode) ; 
}

BeautyShopUnit*	BeautyShopItemGroupList::GetItemNode(int _gender, int _groupID, int _detail)			
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return NULL ;
	return m_vpItemGroup[_gender].at(_groupID)->GetItemNode(_detail) ;	
}

const char*	BeautyShopItemGroupList::GetItemNodeName(int _gender, int _groupID, int _detail)			
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return NULL ;
	return  m_vpItemGroup[_gender].at(_groupID)->GetItemName(_detail) ;

}

//////////////////////////////////////////////////////////////////////////
///< Group ����
const char*	BeautyShopItemGroupList::GetGroupName(int _gender, int _groupID)			
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return NULL ;
	return m_vpItemGroup[_gender].at(_groupID)->GetGroupName();	
}

int			BeautyShopItemGroupList::GetGroupCount(int _gender, int _groupID)		
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return -1 ;
	return m_vpItemGroup[_gender].at(_groupID)->GetGroupCount();	
}

int			BeautyShopItemGroupList::GetGroupCode(int _gender, int _groupID)			
{	
	//int _groupIdx ;
	//if( (_groupIdx = GetGroupIndex(_gender, _groupID)) < 0 ) 
	//	return -1 ;
	return m_vpItemGroup[_gender].at(_groupID)->GetGroupCode();	
}

//////////////////////////////////////////////////////////////////////////
///< GroupList ����
int		BeautyShopItemGroupList::GetGroupListCount(int _gender)			
{	
	return (int)m_vpItemGroup[_gender].size();	
}

int		BeautyShopItemGroupList::GetGroupIndex(int _gender, int _groupID)				
{	
	std::vector<BeautyShopItemGroup*>::iterator Iter = m_vpItemGroup[_gender].begin();
	for(;Iter != m_vpItemGroup[_gender].end(); ++Iter) {
		if( (*Iter)->GetGroupCode() == _groupID )
			return (*Iter)->GetGroupIndex() ;
	}
	return -1 ; 
}

