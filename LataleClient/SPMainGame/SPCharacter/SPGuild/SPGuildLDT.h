// Copyright (C) DURAGON
//***************************************************************************
// System Name : GUILD CROPS
// Comment     : 
// Creation    : DURAGON 2007-4-04    11:18 
//***************************************************************************

#pragma once

#define CROP_LEVEL_MAX			4
#define CROP_REQUIRE_MAX		3
#define EMBLEM_REQUIRE_MAX		3
#define GUILD_GRADE_MAX			7			// 1 ~ 6
#define GUILD_STATUS_COUNT		4

enum EMBLEM_LAYER
{
	LAYER_GUILD_SYM		= 0,
	LAYER_GUILD_BG		= 1,
	LAYER_GUILD_FX		= 2,
	LAYER_GUILD_MAX		= 3,
} ;
//////////////////////////////////////////////////////////////////////////
//
//	Guild.LDT
//
typedef struct _GUILD_REQUIRE
{
	int iRequireType ;
	int iRequireID ;
	int iRequireValue1 ;
	int iRequireValue2 ;
	_GUILD_REQUIRE() {
		Clear() ;
	}
	~_GUILD_REQUIRE() {
		Clear() ;
	}
	void Clear() {
		iRequireType	= 0 ;
		iRequireID		= 0 ;
		iRequireValue1	= 0 ;
		iRequireValue2	= 0 ;
	}
} GUILD_REQUIRE, *PGUILD_REQUIRE;

typedef struct _GUILD_LDT
{
	int				iItemID ;
	int				iPersonality ;			// ����
	int 			iGLevel ;				// ��� ����
	GUILD_REQUIRE	stCreateRequire[5] ;	// ���� ����
	long			lCreateMoney ;			// ���� �ݾ�
	int				iCreateItemID ;			// ���� �Һ������
	int				iCreateItemCount ;		// ���� �Һ� ������ ����
	int				iGuildMaxNum ;			// ��� �ο�
	int				lLoanZoneTime ;			// ��� �뿩�ð�
	int				iDungeonNo ;			// ��� �δ���ȣ
	DWORD			m_dwStatusType[ GUILD_STATUS_COUNT ];		// ��� ������ �ɷ�ġ
	int				m_iStatusValue[ GUILD_STATUS_COUNT ];		// ��� ������ �ɷ°�
	int				iPointLimit ;			// ������ ����Ʈ ����
	int				m_iLVName ;				// ��� ������Ī (GlobalString)

	void Clear()
	{
		int i ;
		iItemID			= 0 ;
		iPersonality	= 0 ;			// ����
		iGLevel			= 0 ;			// ��� ����
		for( i = 0; i < 5; i++ ) {
			stCreateRequire[i].iRequireType = 0 ;
			stCreateRequire[i].iRequireID = 0 ;
			stCreateRequire[i].iRequireValue1 = 0 ;
			stCreateRequire[i].iRequireValue2 = 0 ;
		}
		lCreateMoney	= 0 ;			// ���� �ݾ�
		iCreateItemID	= 0 ;			// ���� �Һ������
		iCreateItemCount = 0 ;			// ���� �Һ� ������ ����
		iGuildMaxNum	= 0 ;			// ��� �ο�
		lLoanZoneTime	= 0 ;			// ��� �뿩�ð�
		iDungeonNo		= 0 ;			// �δ�

		for( i = 0; i < GUILD_STATUS_COUNT; i++ ) {
			m_dwStatusType[i] = 0 ;
			m_iStatusValue[i] = 0 ;
		}
		iPointLimit		= 0 ;			// ������ ����Ʈ ����
		m_iLVName		= 0 ;
	}

} GUILD_ATTR, *PGUILD_ATTR;



struct CROP_INFO
{
	UINT32			iItemID ;
	UINT32			iGrowTime[CROP_LEVEL_MAX] ;
	UINT32			iHastenTime ;
	UINT32			iConsumeItem ;
	GUILD_REQUIRE	stRequire[CROP_REQUIRE_MAX] ;
	CROP_INFO() {
		Clear() ;
	}
	~CROP_INFO() {
		Clear() ;
	}
	void Clear() {
		iItemID = 0 ;
		iGrowTime[0] = 0 ;
		iGrowTime[1] = 0 ;
		iGrowTime[2] = 0 ;
		iGrowTime[3] = 0 ;
		iHastenTime  = 0 ;
		iConsumeItem = 0 ;
		stRequire[0].Clear() ;
		stRequire[1].Clear() ;
		stRequire[2].Clear() ;
	}
	CROP_INFO& operator=(const CROP_INFO &src)
	{
		iItemID = src.iItemID ;
		iGrowTime[0] = src.iGrowTime[0] ;
		iGrowTime[1] = src.iGrowTime[1] ;
		iGrowTime[2] = src.iGrowTime[2] ;
		iGrowTime[3] = src.iGrowTime[3] ;
		iHastenTime  = src.iHastenTime  ;
		iConsumeItem = src.iConsumeItem ;
		stRequire[0] = src.stRequire[0] ;
		stRequire[1] = src.stRequire[1] ;
		stRequire[2] = src.stRequire[2] ;
		return *this ;
	}
} ;
typedef struct CROP_INFO *PCROP_INFO;

//////////////////////////////////////////////////////////////////////////
// For Event > Crop Image Information
// Key is EVENT_ID
struct DISPLAY_CROP_UNIT
{
	UINT32 iImageID ;
	UINT32 iCutInImageID ;
	UINT32 iDlgImageID ;
	std::string strTalk ;
	DISPLAY_CROP_UNIT() {
		Clear() ;
	}
	~DISPLAY_CROP_UNIT() {
		Clear() ;
	}
	void Clear() {
		iImageID		= 0 ;
		iCutInImageID	= 0 ;
		iDlgImageID		= 0 ;
		strTalk.clear() ;
	}
} ;

struct DISPLAY_CROP
{
	UINT32 lItemID ;
	UINT32 iImageID[CROP_LEVEL_MAX] ;
	UINT32 iCutInImageID[CROP_LEVEL_MAX] ;
	UINT32 iDlgImageID[CROP_LEVEL_MAX] ;
	std::string strTalk[CROP_LEVEL_MAX] ;
	DISPLAY_CROP() {
		Clear() ;
	}
	~DISPLAY_CROP() {
		Clear() ;
	}
	void Clear() {
		lItemID = 0 ;
		for( int i = 0; i < CROP_LEVEL_MAX; i++)
		{
			iImageID[i]			= 0 ;
			iCutInImageID[i]	= 0 ;
			iDlgImageID[i]		= 0 ;
			strTalk[i].clear() ;
		}
	}
};


struct EMBLEM_INFO
{
	UINT32			iCIItemID ;
	UINT32			iCIType ;
	UINT32			iConsumeEly ;
	UINT32			iConsumeItem ;
	UINT32			iConsumeItemCount ;
	UINT32			iMinLevel ;
	UINT32			iMaxLevel ;
	UINT32			iResIconID ;
	UINT32			iResIconIndex ;			// Src ���� ���� Index
	UINT32			iResFxID ;
	UINT32			iSortIndex ;
	GUILD_REQUIRE	stRequire[EMBLEM_REQUIRE_MAX] ;
	EMBLEM_INFO() {
		Clear() ;
	}
	~EMBLEM_INFO() {
		Clear() ;
	}
	void Clear() {
		iCIItemID		= 0;
		iCIType 		= 0;
		iConsumeEly 	= 0;
		iConsumeItem 	= 0;
		iConsumeItemCount = 0;
		iMinLevel 		= 0;
		iMaxLevel 		= 0;
		iResIconID 		= 0;
		iResIconIndex 	= 0;			// Src ���� ���� Index
		iResFxID		= 0;
		iSortIndex		= 0;
		stRequire[0].Clear() ;
		stRequire[1].Clear() ;
		stRequire[2].Clear() ;
	}
	EMBLEM_INFO& operator=(const EMBLEM_INFO &src)
	{
		iCIType 		= src.iCIType ;
		iConsumeEly 	= src.iConsumeEly ;
		iConsumeItem 	= src.iConsumeItem ;
		iConsumeItemCount= src.iConsumeItemCount;
		iMinLevel 		= src.iMinLevel;
		iMaxLevel 		= src.iMaxLevel;
		iResIconID 		= src.iResIconID;
		iResIconIndex 	= src.iResIconIndex;
		iResFxID		= src.iResFxID;
		iSortIndex		= src.iSortIndex;
		stRequire[0] = src.stRequire[0] ;
		stRequire[1] = src.stRequire[1] ;
		stRequire[2] = src.stRequire[2] ;
		return *this ;
	}
} ;
typedef struct EMBLEM_INFO *PEMBLEM_INFO;


//////////////////////////////////////////////////////////////////////////
// BOOSTER
typedef struct _BOOSTER
{
	long	lItemID ;				// ������ ID
	int		iType ;					// ���, ������
	UINT32	iConsumeItemID ;		// �Һ� ������ ID
	UINT32	iCalcTime ;				// ����ð�
} BOOSTER_INFO, *PBOOSTER_INFO ;

//////////////////////////////////////////////////////////////////////////
//	Use Map
//	STD_MAP_CROP_INFO is ItemID & CROP_INFO
//	STD_MAP_DISPLAY_CROP is EventID & DISPLAY_CROP
typedef std::map< int , PGUILD_ATTR >			STD_MAP_GUILD_LDT ;
typedef std::map< UINT32 , PCROP_INFO >			STD_MAP_CROP_INFO ;
typedef std::map< UINT32 , UINT32 >				STD_MAP_DISPLAY_CROP_ID ;
typedef std::map< UINT32 , DISPLAY_CROP >		STD_MAP_DISPLAY_CROP ;
typedef std::map< UINT32 , PBOOSTER_INFO >		STD_MAP_BOOSTER_INFO ;

typedef std::map< int , PEMBLEM_INFO >			STD_MAP_EMBLEM_SYMBOL ;
typedef std::map< int , PEMBLEM_INFO >			STD_MAP_EMBLEM_BG ;
typedef std::map< int , PEMBLEM_INFO >			STD_MAP_EMBLEM_FX ;
typedef std::map< int , PEMBLEM_INFO >			STD_MAP_EMBLEM_SORT_SYMBOL ;
typedef std::map< int , PEMBLEM_INFO >			STD_MAP_EMBLEM_SORT_BG ;
typedef std::map< int , PEMBLEM_INFO >			STD_MAP_EMBLEM_SORT_FX ;


class SPGuildArchive ;
class SPGuildLDT
{

public:
	static SPGuildLDT* GetInstance();
	static void Release();

	void		Init() ;
	bool		IsEnable()										{	return m_bEnable;	}
	int			GetGuildAuthority(int iGrade) ;
	void		SetGuildArchive(SPGuildArchive* pArchive)		{	m_pGuildArchive = pArchive;		}
	SPGuildArchive*	GetGuildArchive()							{	return m_pGuildArchive;			}
	int			GetLimitGuildLevel()							{	return m_iMaxGuildLevel;		}

	PGUILD_ATTR	FindGuildAttribute(int iKey) ;
	UINT32		FindGuildCreateItem(int iKey) ;

	bool	GetCropImageByEvent(UINT32 iEventID, int iCLevel, DISPLAY_CROP_UNIT& dpCrop ) ;
	bool	GetCropImageByCrop(UINT32 iCropID, int iCLevel, DISPLAY_CROP_UNIT& dpCrop ) ;
	bool	FindCropIDbyConsumeID(UINT32 iConsumeItemID, UINT32& iItemID) ;
	bool	FindCropInfobyConsumeID(UINT32 iConsumeItemID, CROP_INFO* &pCrop) ;
	bool	FindCropInfobyCropID(UINT32 iCropID, CROP_INFO& pCrop) ;
	bool	FindBoosterIDbyItem(UINT32 iConsumeItemID, UINT32& iItemID) ;
	bool	FindBoosterInfobyItem(UINT32 iConsumeItemID, BOOSTER_INFO* &pBooster) ;

	int		GetEmblemCount(int iLayer) ;
	bool	FindEmblemInfo(int iLayer, int iIndex, EMBLEM_INFO* &emblemInfo) ;
	bool	FindEmblemSymbol(int iIndex, EMBLEM_INFO* &emblemInfo) ;
	bool	FindEmblemBG(int iIndex, EMBLEM_INFO* &emblemInfo) ;
	bool	FindEmblemFX(int iIndex, EMBLEM_INFO* &emblemInfo) ;
	bool	FindSortEmblemInfo(int iLayer, int iIndex, EMBLEM_INFO* &emblemInfo) ;
	bool	FindSortSymbol(int iViewIndex, EMBLEM_INFO* &emblemInfo);
	bool	FindSortBG(int iViewIndex, EMBLEM_INFO* &emblemInfo);
	bool	FindSortFX(int iViewIndex, EMBLEM_INFO* &emblemInfo);

	const char* GetSymbolFilename() ;
	const char* GetEmblemBGFilename() ;
	UINT32		GetEmblemFxID(int iFxIndex) ;

private:
	void	LoadGuildLDT() ;		// ��� Guild.LDT
	void	DeleteGuildLDT() ;
	void	LoadAuthorityLDT() ;	// ���� Authority.LDT
	void	DeleteAuthorityLDT() ;

	void	LoadCropLDT() ;			// �۹� Crop.LDT
	void	CheckCropLDT() ;
	void	DeleteCropLDT() ;
	void	LoadBoosterLDT() ;		// ��� Booster.LDT
	void	CheckBoosterLDT() ;
	void	DeleteBoosterLDT() ;

	void	LoadEmblemLDT() ;		// ��� Booster.LDT
	void	CheckEmblemLDT() ;
	void	DeleteEmblemLDT() ;

protected:
	SPGuildLDT();
	virtual ~SPGuildLDT();

protected:
	static SPGuildLDT*		m_pkInstance;

	bool					m_bEnable ;
	SPGuildArchive*			m_pGuildArchive ;
	STD_MAP_GUILD_LDT		m_mpGuildAttr ;							// Guild Attribute
	int						m_iGuildAuthority[GUILD_GRADE_MAX] ;	// Guild Authority
	int						m_iMaxGuildLevel ;						// Guild Max Level -> Read LDT

	STD_MAP_CROP_INFO		m_mpCropInfo ;			// CropLDT Information (Key:ConsumeItem)
	STD_MAP_DISPLAY_CROP	m_mDisplayCrop ;		// Crop Event Display Image Information (Key:EventID)
	STD_MAP_DISPLAY_CROP_ID	m_mDisplayCropID ;		// CropID & EventID (Key:CropID)
	STD_MAP_BOOSTER_INFO	m_mpBoosterInfo ;		// Booster Item Information (Key:consumeItem)

	STD_MAP_EMBLEM_SYMBOL	m_mpEmblemSym ;			// Guild Emblem Symbol
	STD_MAP_EMBLEM_BG		m_mpEmblemBG ;			// Guild Emblem BG
	STD_MAP_EMBLEM_FX		m_mpEmblemFX ;			// Guild Emblem FX
	STD_MAP_EMBLEM_SORT_SYMBOL	m_mpSortSym ;			// Guild Emblem Symbol
	STD_MAP_EMBLEM_SORT_BG		m_mpSortBG ;			// Guild Emblem BG
	STD_MAP_EMBLEM_SORT_FX		m_mpSortFX ;			// Guild Emblem FX

};

extern SPGuildLDT* g_pkGuildManager;