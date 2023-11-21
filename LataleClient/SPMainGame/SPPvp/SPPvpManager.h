// Copyright (C) DURAGON
//********************************************************************
//	filename: 	SPPvpManager.h
//	created:	2007/11/19   Time:11:11
//	purpose:	
//*********************************************************************/

#pragma once 

#include "GlobalDefines_Share.h"

//---------------------------------------------------------------------
// PVP Match Type
enum PVP_MATCH_TYPE
{
	FREE_DEATH_MATCH = 1,		// ���� Kill ���� ������
	FREE_TIME_MATCH ,			// ���� �ð� ����	������
	PARTY_DEATH_MATCH ,
	PARTY_TIME_MATCH ,
	GUILD_DEATH_MATCH ,
	GUILD_TIME_MATCH ,
} ;

//---------------------------------------------------------------------
// PVP ���ӻ���
enum PVP_GAME_STATE
{
	PVP_STATUS_EMPTY = 0,
	PVP_STATUS_ENTERWAIT ,			// ���� ���
	PVP_STATUS_LOADWAIT ,			// �ε� ���
	PVP_STATUS_GAMEPLAY ,			// ������
	PVP_STATUS_RESULT ,				// ��� ȭ��
} ;

//---------------------------------------------------------------------
// PVP Indun info
struct PVP_INFO
{
	int iPvpMatchType ;
	int	iMapInStage ;
	int iMapInGroup ;
	int	iMapOutStage ;
	int iMapOutGroup ;
	int iPvpWinValue ;
	int iPvpWarnValue ;
	std::string strIndunName ;

	void Clear()
	{
		iPvpMatchType	= 0 ;
		iMapInStage		= 0 ;
		iMapInGroup		= 0 ;
		iMapOutStage	= 0 ;
		iMapOutGroup	= 0 ;
		iPvpWinValue	= 0 ;
		iPvpWarnValue	= 0 ;
		strIndunName.clear() ;
	}
	PVP_INFO& operator = (const PVP_INFO& stPvpInfo)
	{
		iPvpMatchType	= stPvpInfo.iPvpMatchType;
		iMapInStage		= stPvpInfo.iMapInStage	;
		iMapInGroup		= stPvpInfo.iMapInGroup	;
		iMapOutStage	= stPvpInfo.iMapOutStage;
		iMapOutGroup	= stPvpInfo.iMapOutGroup;
		iPvpWinValue	= stPvpInfo.iPvpWinValue;
		iPvpWarnValue	= stPvpInfo.iPvpWarnValue;
		strIndunName	= stPvpInfo.strIndunName.c_str() ;
		return *this;
	}
	bool IsEnable()
	{
		return iPvpMatchType ? true : false ;
	}
};

bool PVPSortByRank( PVPRANK& lv, PVPRANK& rv ) ;


struct SPPvpGloryLevelAttr;
class SPPvpGloryLevelArchive;
struct SPItemRequire;
class SPPvpManager
{
public:

	static SPPvpManager* GetInstance();
	static void Release();

	bool	Init();
	void	Clear();
	void	Process(float fTime);
	void	Render();

	//bool	EnterPvpIndun(UINT32 iInstanceID, int iIndunID=0) ;
	void	SetLoadBGFileName(const char* szFileName) ;
	const char*	GetLoadBGFileName() 	{	return m_strLoadWaitBGFileName.c_str();		}
	//---------------------------------------------------------------------
	// PVP_Indun.LDT Info
	bool	FindPvpInfo(int iIndunID, PVP_INFO& indunInfo);
	void	ClearPvpInfo() ;

	//---------------------------------------------------------------------
	// Get Value
	UINT32	GetPVPScale()			{	return m_uiPVPScale;		}		// PVP ���� ��� üũ
	int		GetPvpStatus()			{	return m_iPVPGameState;		}		// PVP Game ����

	//---------------------------------------------------------------------
	// Send Packet
	bool	SendPVPEnterWait(UINT32 uiPVPScale, int iPVPType=FREE_TIME_MATCH) ;			// PVP ���� ���
	bool	SendPVPEnterCancel() ;			// PVP ���� ��� ���
	bool	SendPVPExit() ;					// PVP ����

	//---------------------------------------------------------------------
	// Receive Packet
	void	OnPVPScEnterRegist(void* pPacket) ;				// PVP ���� ��� ���
	void	OnPVPScEnterCancel(void* pPacket) ;				// PVP ���� ��� ��� ���
	void	OnPVPScMatchOK(void* pPacket) ;					// PVP Match OK
	void	OnPVPScLoadStatus(void* pPacket) ;				// PVP �ε� ��� ���
	void	OnPVPScStart(void* pPacket) ;					// PVP ���� -> ȭ����ȯ �� ����
	void	OnPVPScRank(void* pPacket) ;					// PVP �߰� Ranking
	void	OnPVPScResult(void* pPacket) ;					// PVP ���
	void	OnPVPScExit(void* pPacket) ;					// PVP Exit ���

	//---------------------------------------------------------------------
	// Rect Util Function
	void	RectPlus(RECT& rt1, RECT& rt2, RECT& result);
	void	RectMinus(RECT& rt1, RECT& rt2, RECT& result);
	void	RectHalf(RECT& rt1, RECT& rt2, RECT& result);

	//---------------------------------------------------------------------
	// PVP Zone Check
	bool	IsPvpZone();

	//---------------------------------------------------------------------
	//
	SPPvpGloryLevelArchive* GetPvpGloryLevelArchive();
	
	/**
	 * iPvpLevel�� �ش��ϴ� SPPvpGloryLevelAttr �� �����´� <br>
	 * iPvpLevel�� 0�ΰ�� �����÷��̾� ������ �´� SPPvpGloryLevelAttr�� �����´� <br>
	 @param int iPvpLevel = 0			0�ΰ�� �����÷��̾��� Pvp������ ����Ѵ�
	 @return  SPPvpGloryLevelAttr*		������ ���ų� �߸��� ��� NULL
	*/
	SPPvpGloryLevelAttr*	GetPvpGloryLevelAttr(int iPvpLevel = 0);

	/**
	* iPvpLevel�� �ش��ϴ� SPPvpGloryLevelAttr �� �����´� <br>
	* iPvpLevel�� 0�ΰ�� �����÷��̾� ������ �´� SPPvpGloryLevelAttr�� �����´� <br>
	@param int iPvpLevel = 0			0�ΰ�� �����÷��̾��� Pvp������ ����Ѵ�
	@return  SPPvpGloryLevelAttr*		������ ���ų� �߸��� ��� NULL
	*/
	std::string				GetPvpGloryLevelString(int iPvpLevel = 0);


protected:
	SPPvpManager();
	virtual ~SPPvpManager();

	bool LoadLDTFile();
	

protected:
	static SPPvpManager*	m_pkInstance;

	UINT32		m_uiPVPScale ;				// PVP �������
	int			m_iPVPGameState ;			// PVP ���ӻ��� (0:Empty, 1:�ε����, 2:������, 3:���ȭ��)
	UINT32		m_iPvpIndunID ;				// PVP Indun Instance ID
	std::string m_strLoadWaitBGFileName ;

	std::map< int, PVP_INFO > m_mPvpData;
	PVP_INFO	m_CurPvpIndun;
	bool		m_bForceExit;

	SPPvpGloryLevelArchive*	m_pGloryLevelArchive;	/**< PVP �� ����Ʈ�� �� ������ ȯ���ϴ� ���̺� <br> */
};

extern SPPvpManager* g_pkPvpManager;
