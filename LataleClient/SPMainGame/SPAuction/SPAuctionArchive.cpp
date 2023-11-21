// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionArchive.cpp
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/

#include "SPCommon.h"
#include "SPUtil.h"
#include "PacketID.h"

#include "SPLDTFile.h"
#include "SPLDTManager.h"
#include "SPResourceDef.h"
#include "SPResourceManager.h"

#include "SPWindowDEF.h"
#include "SPMouseCursor.h"
#include "SPInterfaceManager.h"

#include "SPItemAttr.h"
#include "SPItemStatus.h"
#include "SPItem.h"
#include "SPItemCluster.h"

#include "SPAuctionDef.h"
#include "SPAuctionAttr.h"
#include "SPAuctionArchive.h"
#include "SPAuctionManager.h"

#include "_Error_log.h"


//////////////////////////////////////////////////////////////////////////
// Generic Sort Algorithm
// ǰ��
struct _AuctionSortByQual_A : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetItemQuality() < rv->GetItemQuality())
			return true;
		return false;
	}
} AuctionSortByQual_A;
struct _AuctionSortByQual_D : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetItemQuality() > rv->GetItemQuality())
			return true;
		return false;
	}
} AuctionSortByQual_D;

// ����
struct _AuctionSortByLevel_A : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetItemLevel() < rv->GetItemLevel())
			return true;
		return false;
	}
} AuctionSortByLevel_A;
struct _AuctionSortByLevel_D : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetItemLevel() > rv->GetItemLevel())
			return true;
		return false;
	}
} AuctionSortByLevel_D;

// ������
struct _AuctionSortByDur_A : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetItemDuration() < rv->GetItemDuration() )
			return true;
		return false;
	}
} AuctionSortByDur_A;
struct _AuctionSortByDur_D : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetItemDuration() > rv->GetItemDuration())
			return true;
		return false;
	}
} AuctionSortByDur_D;

// ���� �ð�
struct _AuctionSortByFinish_A : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetFinishTime() < rv->GetFinishTime())
			return true;
		return false;
	}
} AuctionSortByFinish_A;
struct _AuctionSortByFinish_D : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetFinishTime() > rv->GetFinishTime())
			return true;
		return false;
	}
} AuctionSortByFinish_D;

// ���� ����
struct _AuctionSortByPrice_A : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetCurBidPrice() < rv->GetCurBidPrice())
			return true;
		return false;
	}
} AuctionSortByPrice_A;
struct _AuctionSortByPrice_D : binary_function<SPAuctionAttr*, SPAuctionAttr*, bool> {
	bool operator() (SPAuctionAttr* lv, SPAuctionAttr* rv) const
	{
		if(lv->GetCurBidPrice() > rv->GetCurBidPrice())
			return true;
		return false;
	}
} AuctionSortByPrice_D;



//////////////////////////////////////////////////////////////////////////
// SPAuctionArchive
SPAuctionArchive::SPAuctionArchive()
: m_bNeedReset(true)
{
	Init() ;
}

SPAuctionArchive::~SPAuctionArchive()
{
	Clear() ;
}


void SPAuctionArchive::Init()
{
	//m_eSortKey = AUCTION_SORT_QUALITY ;
	m_vpAuctionList.clear() ;
	m_bIsLast = false ;
	m_iOnePage = -1 ;
	m_iTotalItemCount = 0 ;
	m_iArchiveType = AUCTION_ARCH_NULL ;
	SetDefaultSort(false) ;
}

void SPAuctionArchive::Clear()
{
	std::vector<SPAuctionAttr*>::iterator mIter ;
	mIter	=	m_vpAuctionList.begin() ;
	while ( mIter != m_vpAuctionList.end() )
	{
		SAFE_DELETE( (*mIter) );
		m_vpAuctionList.erase(mIter) ;
	}
	m_vpAuctionList.clear() ;
	m_iOnePage = -1 ;
	m_iArchiveType = AUCTION_ARCH_NULL ;
	m_iTotalItemCount = 0 ;
	m_iHaveSize = 0 ;
	m_bIsLast = false ;
}


void SPAuctionArchive::ClearList()
{
	std::vector<SPAuctionAttr*>::iterator mIter ;
	mIter	=	m_vpAuctionList.begin() ;
	while ( mIter != m_vpAuctionList.end() )
	{
		SAFE_DELETE( (*mIter) );
		m_vpAuctionList.erase(mIter) ;
	}
	m_vpAuctionList.clear() ;

	m_iTotalItemCount = 0 ;
	m_iStartIndex = 0 ;
	m_iHaveSize = 0 ;
	m_bIsLast = false ;
}


//////////////////////////////////////////////////////////////////////////
// List Function
/**
	@param AUCTION_ARCH_DATA	: Auction List Data
	@param int iOnePage			: OnePage ���� ũ�� (Default:7)
	@param int iTotalCount		: ��ü ������ ũ�� (for Part)
	@param int iStart			: ���� ��ġ (for Part)
	@param int iEnd				: �� ��ġ (for Part)
*/
bool SPAuctionArchive::SetAuctionList(AUCTION_ARCH_DATA eType, int iOnePage/*=7*/, int iTotalCount/*= 0*/, int iStart/*=0*/, int iSize/*=0*/)
{
	Clear() ;
	m_iOnePage = iOnePage ;
	m_iArchiveType = eType ;
	m_bNeedReset = false ;

	// for PART List
	m_iTotalItemCount = iTotalCount ;
	m_iStartIndex = iStart ;

	if( iTotalCount == (iStart + iSize) )
		m_bIsLast = true ;

	return false ;
}

/**
	@param SPAuctionAttr* pAuctionItem	: Item Data
	@param int iIndex					: InsertPosition (-1:END)
*/
bool SPAuctionArchive::AddAuctionList(SPAuctionAttr* pAuctionItem, bool bCount/*=false*/)
{
	// [20080616]�߰��ÿ��� ������ �߰��ؼ� �ʿ��� ������ ã���� �ֵ��� �ϰ�
	// BuyList, SaleList�� �ޱ����� ����Ʈ�� �ʱ�ȭ�ؼ� �ٽ� �޴´�.
	//if( m_bNeedReset )
	//	return false ;

	m_vpAuctionList.push_back(pAuctionItem) ;
	if( bCount )		++m_iTotalItemCount ;

	m_iHaveSize = (int)m_vpAuctionList.size() ;
	if( m_iArchiveType == AUCTION_ARCH_ALL)
		m_iTotalItemCount = m_iHaveSize ;
	return true ;
}

/**
	�ش������� Index�� �����͸� �����Ѵ�.
	������ Aution_Header ������ ����ȴ�.
	@param int iPage		: Page Number
	@param int iIndex		: List Index
	@param SPAuctionAttr* pAuctionItem	: Data
*/
bool SPAuctionArchive::ChangeAuctionList(int iPage, int iIndex, SPAuctionAttr* pAuctionItem)
{
	int iListIndex = iPage * m_iOnePage + iIndex ;
	int iSize = (int)m_vpAuctionList.size() ;

	if( m_iArchiveType == AUCTION_ARCH_ALL)
	{
		iListIndex = iPage * m_iOnePage + iIndex ;
		iSize = (int)m_vpAuctionList.size() ;
	}
	else
	{
		iListIndex = iPage * m_iOnePage + iIndex - m_iStartIndex ;		// �Ϻ��ΰ�� ���� Index ���
		iSize = (int)m_vpAuctionList.size() ;
	}

	if( iListIndex < iSize ) {
		return m_vpAuctionList[iListIndex]->SetChangeHeader(pAuctionItem->GetHeader()) ;
	}

	return false ;
}


/**
	�ش� AuctionID�� ã�Ƽ� ������Ʈ �Ѵ�.
	@param INT64 iAuctionID
	@param void* pAuctionHeader (AUCTION_HEADER*)
 */
bool SPAuctionArchive::UpdateAuctionArchive(INT64 iAuctionID, void* pAuctionHeader)
{
	SPAuctionAttr* pAttr = NULL ;
	if( ( pAttr = FindAuctionItem(iAuctionID) ) == NULL )
		return false ;

	return pAttr->SetChangeHeader((AUCTION_HEADER*)pAuctionHeader) ;
}




/**
	�ش� AuctionID �� �����͸� ����
	@param int iAuctionID
*/
bool SPAuctionArchive::DeleteAuctionItem(INT64 iAuctionID, bool bCount/*=false*/)
{
	//if( m_bNeedReset )
	//	return false ;

	SPAuctionAttr* pAttr ;
	std::vector<SPAuctionAttr*>::iterator mIter ;
	mIter	=	m_vpAuctionList.begin() ;
	while ( mIter != m_vpAuctionList.end() )
	{
		pAttr = (*mIter) ;
		if( pAttr->GetAuctionID() == iAuctionID )	{
			SAFE_DELETE( (*mIter) );
			m_vpAuctionList.erase(mIter) ;
			if( bCount )	--m_iTotalItemCount ;

			m_iHaveSize = (int)m_vpAuctionList.size() ;
			if( m_iArchiveType == AUCTION_ARCH_ALL)
				m_iTotalItemCount = m_iHaveSize ;
			return true ;
		}
		++mIter ;
	}

	return false ;
}


/**
	�ش������� Index�� �����͸� �����´�.
	@param int iPage		: Page Number (1 Base)
	@param int iIndex		: List Index (0 Base)
	@return SPAuctionAttr* pAuctionItem	: return Data
*/
SPAuctionAttr* SPAuctionArchive::GetAuctionItem(int iPage, int iIndex)
{
	if( m_bNeedReset )
		return NULL ;

	int iListIndex ;
	int iSize ;
	if( m_iArchiveType == AUCTION_ARCH_ALL)
	{
		iListIndex = iPage * m_iOnePage + iIndex ;
		iSize = (int)m_vpAuctionList.size() ;
	}
	else
	{
		iListIndex = iPage * m_iOnePage + iIndex - m_iStartIndex ;		// �Ϻ��ΰ�� ���� Index ���
		iSize = (int)m_vpAuctionList.size() ;
	}

	if( iListIndex < iSize )
		return m_vpAuctionList[iListIndex] ;
	return NULL ;
}


/**
	�ش������� Index�� �����͸� �����´�.
	@param int iPage		: Page Number (1 Base)
	@param int iIndex		: List Index (0 Base)
	@return SPAuctionAttr* pAuctionItem	: return Data
*/
SPAuctionAttr* SPAuctionArchive::FindAuctionItem(INT64 iAuctionID)
{
	//if( m_bNeedReset )	
	//	return NULL ;

	SPAuctionAttr* pAttr ;
	std::vector<SPAuctionAttr*>::iterator mIter ;
	mIter	=	m_vpAuctionList.begin() ;
	while ( mIter != m_vpAuctionList.end() )
	{
		pAttr = (*mIter) ;
		if( pAttr->GetAuctionID() == iAuctionID )	{
			return pAttr ;
		}
		++mIter ;
	}
	return NULL ;
}


/**
	�������� �����͸� �����´�.
	@param std::vector<SPAuctionAttr*>& pAuctionItem	: return Data
	@param int iPage		: Page Number(1 Base)
	@return int				: Item count 	
*/
int SPAuctionArchive::GetAuctionListPage(std::vector<SPAuctionAttr*>& vAuctionList, int iPage)
{
	int iSize ;
	int iStart, iNext, iEnd ;
	int iGetStart, iGetCount ;
	SPAuctionAttr* pAttr ;

	if( m_iArchiveType == AUCTION_ARCH_ALL)
	{
		iStart = iPage * m_iOnePage ;
		if( iStart < 0 )	iStart = 0 ;
		iSize = (int)m_vpAuctionList.size() ;
		iNext = iStart + m_iOnePage ;
		iEnd = (iNext < iSize ) ? iNext : iSize ;

		iGetStart = iStart ;
		iGetCount = iEnd - iStart ;

		for( int i = iGetStart; i < iGetStart+iGetCount; i++ )
		{
			pAttr = m_vpAuctionList[i] ;
			vAuctionList.push_back(pAttr) ;
		}
		return iGetCount ;
	}
	else
	{
		iStart = iPage * m_iOnePage ;			// Abs Index
		if( iStart < 0 )	iStart = 0 ;
		iSize = (int)m_vpAuctionList.size() + m_iStartIndex ;
		iNext = iStart + m_iOnePage ;
		iEnd = (iNext < iSize ) ? iNext : iSize ;

		if( m_iStartIndex > iStart )
			return 0 ;

		iGetStart = iStart - m_iStartIndex ;
		iGetCount = iEnd - iStart ;


		for( int i = iGetStart; i < iGetStart+iGetCount; i++ )
		{
			pAttr = m_vpAuctionList[i] ;
			vAuctionList.push_back(pAttr) ;
		}
		return iGetCount ;
	}
	return 0 ;
}


/**
	����Ʈ�� ������ ������ �����´�.
	��ǰ����� �Ϻθ� �޴� ��찡 �����Ƿ� TotalCount�� ������ �װ����� ����Ѵ�.
*/
int SPAuctionArchive::GetTotalPageCount()
{
	int iSize = ( m_iTotalItemCount ) ? m_iTotalItemCount : (int)m_vpAuctionList.size() ;
	if( iSize == 0 || m_iOnePage == 0 )
		return 0 ;
	int iExtra = ( (iSize % m_iOnePage) == 0 ) ? 0 : 1 ;

	return (iSize / m_iOnePage) + iExtra  ;
}


int SPAuctionArchive::GetListCount()
{
	return (int)m_vpAuctionList.size() ;
}


/**
	�ش� �������� ������ Archive�� �ִ��� Ȯ��	
	@param int iPage : 0 Base Page
*/
bool SPAuctionArchive::HasPageInfo(int iPage)
{
	int iSize ;
	int iStartPage ;
	int iEndPage ;
	int iExtra = 0 ;

	iSize = (int)m_vpAuctionList.size() ;				// ����Ʈ ũ��
	iExtra = ( (iSize % m_iOnePage) == 0 ) ? 0 : 1 ;	// ������ ����������
	if( m_iArchiveType == AUCTION_ARCH_ALL)
	{
		iEndPage = iSize / m_iOnePage + iExtra ;
		return ( iEndPage > iPage ) ? true : false ;
	}
	else
	{
		// �Ϻθ� ������ �ִ� ���
		iStartPage = (m_iStartIndex+1) / m_iOnePage ;
		if( iStartPage > iPage )	
			return false ;

		iEndPage = iStartPage + (iSize / m_iOnePage) -1;	// ������ �������� ����
		if( m_bIsLast && iExtra )		++iEndPage ;	// �� �������̰� ������ ������ ������ ���� ������ �߰�
		if( iEndPage < iPage )
			return false ;
		return true ;
	}
	return false ;
}


/**
	AUCTION_ARCH_PART Ÿ���߿���
	Part�� ������ ��ȿ�� ������ ���� ���θ� �Ǵ��Ѵ�.
	SearchArchive���� ��ñ��Ű� �߻��Ǿ����� ����Ʈ�� ������Ʈ�� ���ؼ� ���ȴ�.
 */
bool SPAuctionArchive::IsPartLastPage(int iPage)
{
	int iStartPage ;
	int iEndPage ;
	int iExtra = 0 ;

	if( m_iArchiveType == AUCTION_ARCH_ALL )	// Part����Ʈ�� �ƴϸ� false
		return false ;
	if( m_bIsLast )			// ��ü����Ʈ�� ���̸� false 
		return false ;

	iStartPage = (m_iStartIndex+1) / m_iOnePage ;
	iEndPage = iStartPage + (m_iHaveSize / m_iOnePage) -1 ;		// ������ �������� ����
	iExtra = ( (m_iHaveSize % m_iOnePage) == 0 ) ? 0 : 1 ;	// ������ ����������

	// ������ ������ �̰� ������ �����Ͱ� ������ Part�� ������ ������ �̴�.
	// �� ��� ���� �����͸� ��û�ؾ� �Ѵ�.
	if( iPage == iEndPage && iExtra == 0 )	
		return true ;

	return false ;
}



/**
	���� �ֱٿ� ������Ʈ�� SortKey�� ��ȯ�Ѵ�.
*/
void SPAuctionArchive::GetLatestSortKey(AUCTION_SORT_KEY& eSortKey, int& iAscend)
{
	eSortKey = m_eSortKey ;
	iAscend = m_iSortAscend[eSortKey] ;
}


int SPAuctionArchive::GetSortAscendKey(AUCTION_SORT_KEY eSortKey)
{
	return m_iSortAscend[eSortKey] ;
}

/**
	iSortKey�� ���ؼ� Archive�� sort�Ѵ�.
	@param AUCTION_SORT_KEY eSortKey
	@param int iAscend	: 0:��������, 1:��������
*/
bool SPAuctionArchive::SetSort(AUCTION_SORT_KEY eSortKey, bool bReal /*= true*/)
{
	bool bRet = false ;

	if( bReal == false ) {
		m_eSortKey = eSortKey ;
		m_iSortAscend[eSortKey] = m_iSortAscend[eSortKey] ? 0 : 1 ;		// Toogle
		return true ;
	}

	if( m_bNeedReset || m_iArchiveType != AUCTION_ARCH_ALL )
		return false ;

	// ���� Sort
	int iAscend = m_iSortAscend[eSortKey] ? 0 : 1 ;		// Toogle
	switch(eSortKey)	{
		case AUCTION_SORT_QUALITY:		// ǰ��
			iAscend ? sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByQual_A) 
				: sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByQual_D) ;
			bRet = true ;
			break ;
		case AUCTION_SORT_ITEM_LV:			// ����
			iAscend ? sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByLevel_A) 
				: sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByLevel_D) ;
			bRet = true ;
			break ;
		case AUCTION_SORT_ITEM_OPTPOINT:	// ������
			iAscend ? sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByDur_A) 
				: sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByDur_D) ;
			bRet = true ;
			break ;
		case AUCTION_SORT_DURATION:	// �����ð�
			iAscend ? sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByFinish_A) 
				: sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByFinish_D) ;
			bRet = true ;
			break ;
		case AUCTION_SORT_PRICE:			// ������(ely,cash,mile)
			iAscend ? sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByPrice_A) 
				: sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByPrice_D) ;
			bRet = true ;
			break ;

		default:
			bRet = false ;
			break ;
	}

	// Sort������ ���� Sort ����
	if( bRet )	{
		m_eSortKey = eSortKey ;
		m_iSortAscend[eSortKey] = iAscend ;
	}
	return bRet ;
}


/**
	�⺻ Sort������ Price�� ������ ��� Sort�� Descend
	�����ð��� Default�� �������� �ʰ� Ascend�� ����
	Descend: 0, Ascend: 1
 */
void SPAuctionArchive::SetDefaultSort(bool bReal/*=true*/)
{
	m_iSortAscend[AUCTION_SORT_NULL] = 0 ;
	m_iSortAscend[AUCTION_SORT_DURATION] = 1 ;

	m_iSortAscend[AUCTION_SORT_ITEM_OPTPOINT] = 0 ;
	//if( bReal ) sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByDur_D) ;

	m_iSortAscend[AUCTION_SORT_PRICE] = 1 ;
	//if( bReal ) sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByPrice_A) ;

	m_iSortAscend[AUCTION_SORT_ITEM_LV] = 0 ;
	if( bReal ) sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByLevel_D) ;

	m_eSortKey = AUCTION_SORT_QUALITY ;
	m_iSortAscend[AUCTION_SORT_QUALITY] = 0 ;
	if( bReal ) sort(m_vpAuctionList.begin(), m_vpAuctionList.end(), AuctionSortByQual_D) ;
}

