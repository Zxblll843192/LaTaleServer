#pragma once

enum WAY_POINT_TYPE {
	WAY_POINT_TYPE_NULL			= 0,		// NULL
	WAY_POINT_TYPE_STONE		= 1,		// ��ž
	WAY_POINT_TYPE_TOMB			= 2,		// ��
};

enum WAY_POINT_RANK {
	WAY_POINT_RANK_0			= 0,		// Way Point Require Rank 0
	WAY_POINT_RANK_1			= 1,		// Way Point Require Rank 1
	WAY_POINT_RANK_NULL			= 3,		// Way Point Require Rank NULL
};

const int MAX_WAY_POINT_RANK	= 2;		// ��������Ʈ ��ũ 
const int MAX_WAY_POINT_REQUIRE	= 2;		// ����ũ�� �����̾��� ����
const int MAX_WAY_POINT_EFFECT	= 2;		// �ִ� ���� ����Ʈ ����, Ŭ���̾�Ʈ���� ������ 

#include "SPQuestAttr.h"


class SPWayPointAttr {
public:
	SPWayPointAttr();
	~SPWayPointAttr();
	
	/**
	 * ��� ���� ������ �ʱ�ȭ <br> 
	 @param 
	 @return
	*/
	void Clear();
	
	/**
	 * ��������Ʈ ���������� �ʱ�ȭ <br> 
	 @param 
	 @return
	*/
	void Reset();

	/**
	 * ���� �Ǿ� �ִ��� Ȯ���Ѵ� <br> 
	 @param 
	 @return bool	ture�� ��� ����Ǿ� ����
	*/
	bool IsSave();

	/**
	 * ���̺�Ʈ ID�� �����ϸ鼭 ���̺�Ʈ �����͸� �����Ѵ� <br>
	 @param 
	 @return
	*/
	bool SetMapEventID(int iID);

	/**
	 * ��Ż�� ���� üũ <br>
	 @param 
	 @return
	*/
	WAY_POINT_RANK	CheckRequire();
	

protected:
	

public:
	int				m_iID;								/**< ��������Ʈ ID <br> MapEvent ID�� ���� <br> */
	int				m_iGroup;							/**< ��������Ʈ�� ���� Group ID <br> */
	std::string		m_strName;							/**< ��������Ʈ �̸� <br> */
	std::string		m_strDesc;							/**< ��������Ʈ ���� <br> */
	WAY_POINT_TYPE	m_iType;							/**< ��������Ʈ Ÿ�� <br> */
	int				m_iMapEventID;						/**< ��������Ʈ ID�� ���� <br> */
	MAPEVENT_INFO*	m_pMapEvent;						/**< �ش� ID�� MapEvent ���� <br> �ε��� ���õ� <br> */
	SPRequire		m_Require[MAX_WAY_POINT_RANK][MAX_WAY_POINT_REQUIRE];	/**< ��������Ʈ üũ�� �䱸���� <br> */
	int				m_iUseItemID[MAX_WAY_POINT_RANK];						/**< ���� ������ ID <br> */
	int				m_iUseItemCount[MAX_WAY_POINT_RANK];					/**< ���� ������ ���� <br> */
	int				m_iEffect[MAX_WAY_POINT_EFFECT];						/**< ����� ���Ǵ� ����Ʈ <br> */
	std::string		m_strErr;							/**< Require Rank NULL �̰ų� Item üũ�� ���������� ��� �޽��� <br> */
	int				m_iStoryID;							/**< ��������Ʈ �� ������ ���丮 ID <br> */
	bool			m_bOpen;							/**< ��������Ʈ�� ������ �Ǿ� �ִ����� �÷��� <br> */

	bool			m_bSave;							/**< ��������Ʈ�� ���忩�� <br> */
	WAY_POINT_RANK	m_iRank;							/**< ��������Ʈ üũ�� ���⿡ ���� ������ ��ũ <br> */
};


