// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPAuctionArchive.h
//	created:	2008/2/26   Time:10:59
//	purpose:	
//*********************************************************************/

#pragma once 

enum AUCTION_ARCH_DATA ;
class SPAuctionAttr ;
class SPAuctionArchive 
{
public:
	SPAuctionArchive();
	~SPAuctionArchive();

	void Init();
	void Clear();
	void ClearList();

	bool SetAuctionList(AUCTION_ARCH_DATA eType, int iOnePage = 7, int iTotalCount = 0, int iStart = 0, int iEnd = 0) ;
	bool AddAuctionList(SPAuctionAttr* pAuctionItem, bool bCount = false) ;			// �߰�
	bool ChangeAuctionList(int iPage, int iIndex, SPAuctionAttr* pAuctionItem) ;	// ����
	bool UpdateAuctionArchive(INT64 iAuctionID, void* pAuctionHeader = NULL) ;		// ����
	bool DeleteAuctionItem(INT64 iAuctionID, bool bCount = false) ;					// ����
	

	SPAuctionAttr* GetAuctionItem(int iPage, int iIndex) ;
	SPAuctionAttr* FindAuctionItem(INT64 iAuctionID) ;
	int GetAuctionListPage(std::vector<SPAuctionAttr*>& vAuctionList, int iPage) ;		// ������ ������ �����´�

	int GetListCount() ;				// Archive�� Size�� �����´�
	int GetTotalPageCount() ;			// ����Ʈ�� ������ ������ �����´�.
	bool HasPageInfo(int iPage) ;		// �ش� �������� ������ Archive�� �ִ��� Ȯ��
	bool IsPartLastPage(int iPage) ;	// PART�� ������ ��ȿ �������� ������Ʈ �Ǿ�� �ϴ��� ���� üũ

	void SetDefaultSort(bool bReal=true) ;			// Archive�� �⺻ Sort�� ����
	bool SetSort(AUCTION_SORT_KEY eSortKey, bool bReal= true) ;		// SortKey�� Archive�� Sort
	void GetLatestSortKey(AUCTION_SORT_KEY& eSortKey, int& iAscend) ;
	int  GetSortAscendKey(AUCTION_SORT_KEY eSortKey) ;

	bool GetNeedReset()						{	return m_bNeedReset ;	}		// ����, �������½� ������
	void SetNeedReset(bool bReset)			{	m_bNeedReset = bReset ;	}		// ����, �������½� ������
private:



private:
	bool		m_bNeedReset ;				// ������ �޾ƾ� �ϴ� ���
	AUCTION_ARCH_DATA	m_iArchiveType ;	// ��ü�� �����ϴ� ���� �Ϻθ� �����ϴ� ���
	int			m_iTotalItemCount ;
	int			m_iStartIndex ;		// PART Ÿ���ΰ�� ���
	int			m_iHaveSize ;		// PART Ÿ���ΰ�� ���
	int			m_iOnePage ;		// OnePage Size
	bool		m_bIsLast ;			// PART�� ������ ������ ���� ó��
	AUCTION_SORT_KEY m_eSortKey ;	// SortKey
	int			m_iSortAscend[AUCTION_SORT_MAX] ;		// 0:Descend, 1:Ascend
	std::vector<SPAuctionAttr*>		m_vpAuctionList;
};