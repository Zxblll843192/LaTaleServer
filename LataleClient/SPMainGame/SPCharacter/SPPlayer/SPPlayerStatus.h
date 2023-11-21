// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPPlayerStatus
// Comment     : 
// Creation    : metalgeni 2004-08-24 ���� 10:26:19
//***************************************************************************

#pragma once


class SPGameObject;
class SPGOBStatus;
class SPPlayer;

class SPPlayerStatus : public SPGOBStatus {
public:
	SPPlayerStatus(SPGameObject* pParent);
	virtual ~SPPlayerStatus();
	virtual void	Init();	
	virtual bool	SetCharInfo(CHARACTER_INFO2* pCharInfo);
	virtual bool	SetStatusInfo(STATUS_INFO* StatusInfo);
	virtual CHAR_EXP* GetCHAR_EXP();

	virtual UINT	GetStatusValue(STATUS_TYPE StatusType);
	virtual bool	SetStatusValue(STATUS_TYPE StatusType, UINT uiValue);

	virtual UINT64	GetStatusValueEX(STATUS_EX_TYPE	 StatusType);
	virtual bool	SetStatusValueEX(STATUS_EX_TYPE	 StatusType, UINT64 uiValue);

	void			SetTitleID( UINT32 uiTitleID );
	UINT32			GetTitleID();

	int				GetGameOption();
	bool			IsTrade();
	bool			IsTeam();
	bool			IsAlert();
	bool			IsWantTeamHide();	
	
	bool			SetWantParty(bool bPvp = false);

	void			SetItemMix( ITEMMIX_INFO& stItemMixInfo , bool bShowChatMessage );
	ITEMMIX_INFO*	GetItemMix();

	void			SetLovePoint( int iLovePoint , bool bShowMsg );

protected:
	SPGMESSAGE_OBJ_MAP_DECLARE()

	virtual int OnSetStatusInfo ( LPARAM lParam );
	virtual int OnSetCharInfo	( LPARAM lParam );
	virtual int OnStatLevelUp	( LPARAM lParam );
	virtual int OnStorageInMoney	( LPARAM lParam );		//[8/3/2005]
	virtual int OnStorageOutMoney	( LPARAM lParam );		//[8/3/2005]
	virtual int OnSetEffectStatusInfo(LPARAM lParam);
	virtual int OnSetOptions (LPARAM lParam);
	virtual int OnSetCashInfo(LPARAM lParam);


	void		UpdateOption();	//  [4/24/2008 AJJIYA]

protected:

	friend				SPPlayer;

	UINT32				m_uiTitleID;	
	UINT32				m_uiFameBase;
	UINT32				m_uiFame;
	CHAR_EXP			m_CharExp;

	UINT8				m_cCharType;
	GENDER				m_Gender;
	UINT64				m_uiMoney;
	UINT64				m_uiStorageMoney;			//[2005/7/20]
	int					m_iSkillPoint;
	int					m_uiArmor ;			// ����
	int					m_uiRegistEarth ;	// ���׷�
	int					m_uiRegistWind ;	// ���׷�
	int					m_uiRegistWater ;	// ���׷�
	int					m_uiRegistFire ;	// ���׷�
	int					m_uiRequireLv ;		// ���ѷ�������
	int					m_uiProvEnchant ;	// ��þƮ ����Ȯ������.
	INT32				m_iGameOptions;		// Server Side Game Option

	ITEMMIX_INFO		m_stItemMix;
	PVP_STATUS			m_stPvpStat;		//[2007/11/27] Pvp Status Info

	int					m_iCash;			//[2008/3/12] �÷��̾� ���� ĳ��
	int					m_iPoint;			//[2008/3/12] �÷��̾� ���� ����Ʈ

	//-----------------------------------------------
	//{
	int					m_iLovePoint;		// ���� ����Ʈ ���簪 [10/2/2008 AJJIYA]
	int					m_iLovePointMax;	// ���� ����Ʈ �ִ밪 [10/2/2008 AJJIYA]
	int					m_iLoveDay;			// ���� ���� �� �� [10/2/2008 AJJIYA]
	int					m_iLoveState;		// ���� ���� ( 0 : None , 1 : �������� , 2 : �������� �Ϸ� ���� , 4 : ��ȥ���� ) [10/2/2008 AJJIYA]
	int					m_iLoveLevel;		// ���� ���� [10/27/2008 AJJIYA]

	int					m_iExpandCharSlot;		// ĳ���� Ȯ�� ���� [10/20/2008 DURAGON]
	int					m_iSummonMobCount;		// ���� ��ȯ ��ü��[10/20/2008 DURAGON]
	
	int					m_iRankingLevel;
	int					m_iRankingPvp;
	UINT				m_iRankingLove;
	int					m_iRankingGuild;
	//-----------------------------------------------
	//}
};
