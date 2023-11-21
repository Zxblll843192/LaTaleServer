	// GlobalDefines_Share.h

/*

	Client / Server ���� ���� Define �� ���� ���� �뵵
	(Packet �� ������ ��� Share_Defines ����)

*/

#pragma once


#define ITEMSKILL_SELL_PERCENT	20 // 2007.09.10 dhpark 15 -> 20 �꽺ų�� ���ؼ� �������ǸŸ� ������ �ǸŰ� �����Դϴ�. ��ȹ����å���濡 ���ؼ� ������. ���������

// ID/PW/NAME Length definition
//{
	//extern int g_LEN_ID/* = LEN_ID*/;
	//extern int g_LEN_PW/* = LEN_PW*/;

	//extern int g_MIN_LEN_ID/* = MIN_LEN_ID*/;
	//extern int g_MIN_LEN_PW/* = MIN_LEN_PW*/;

	//extern bool SetLength_Init(TCHAR* pszIniFile);

	//extern bool SetLength_ID(int iIDLen);
	//extern bool SetLength_PW(int iPWLen);
	//extern bool SetLength_MinID(int iMinIDLen);
	//extern bool SetLength_MinPW(int iMinPWLen);
	//extern bool CheckLength_IDPW();

//}


enum SITE_TYPE {
	SITE_LOCAL,
	SITE_ACTOZ,
	SITE_GAMEPOT,
	SITE_SANDA,
	SITE_BUDDYBUDDY, 
	SITE_ATGAMES, 
	SITE_OGP,		//  [4/28/2008] append by metalgeni 
	MAX_SITES};


// 1(6,without challenge),2(not used),3(8,with challenge)
enum {EKEYTYPE_NONE,EKEYTYPE_WITHOUT_CHALLENGE_6,EKEYTYPE_WITHOUT_CHALLENGE_8,EKEYTYPE_WITH_CHALLENGE_8,MAX_EKEYTYPE};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ҽ� ���� üũ �뵵 (��ũ��ũ ��Ŷ �ۼ��ſ뵵�δ� ������� ����)
//{
	#define MAX_RESOURCE_FILE_COUNT		50

	#pragma pack(push,8)

	typedef struct _RES_VERSION_INFO
	{
		int iVersion;
		TCHAR szFile[MAX_PATH];

	}RES_VERSION_INFO;

	#pragma pack(pop)

//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ���� �ؼ� ������� ����ϴ�. �Ѱ� ���Ѿȿ��� ����ü �����ϼ���.
#pragma pack(push,1)

//------------------------------------------------------------------------------
// ���
//#define _GUILD_FUNC_								0
#define GUILD_MAX_NAME								16					// ���� �ִ����(DB�� 20���� ���� ������)
#define GUILD_MAX_SLOGAN							100					// ��彽�ΰ� �ִ����
#define GUILD_MAX_MEMBERLIST_PERPACKET				100					// ��Ŷ�� ����� ��(�������ü�� ũ�Ⱑ Ŀ���� �����ʿ���)
#define GUILD_MIN_MEMBERCNT							1					// ��带 �����ϴ� �ּ��ο�(�渶�� ��������)
#define GUILD_MAX_MEMBERCNT							200					// �ý������� �ִ������
// �������
#define GUILD_MAX_REQUIRE_CREATE					5					// ����(��ũ��)�� ���ǰ˻��
#define GUILD_MAX_CONSUMPTION_ITEM_CREATE			1					// �������� �Ҹ�Ǵ� ������ �ִ��
#define GUILD_MAX_REQUIRE_LOAN						5					// ���� �뿩�� ���ǰ˻��
// ũ������
#define CROP_MAX_REQUIRE_CREATE						3					// ������ ���ǰ˻��
#define CROP_MAX_CONSUMPTION_ITEM_CREATE			1					// ������ �Ҹ�Ǵ� ������ �ִ��
#define CROP_MAX_EVENTID_CREATE						2					// ������ �����ؾ��ϴ� �̺�Ʈ �ִ��
// ���������
#define DIVISION_MAX_EVENTID						10					// ����δ���Ż�̺�Ʈ �ִ��
// �������
#define NOURISH_MAX_CONSUMPTION_ITEM				1					// �Ҹ�Ǵ� ������ �ִ��
// �������Ʈ�ִ밪
#define GUILD_MAX_POINT								2000000000			// �������Ʈ �ִ밪(����/��� ����)
// ��巩ũ�ִ밪
#define GUILD_MAX_RANK								10					// ����ִ뷩ũ(2007.08.14 dhpark ��ũ����˻縦 ������ �����ϱ� ���ؼ� ���Ƿ� ����)
// ��巩ũ�� �ִ� ���ȼ�
#define GUILD_MAX_STATUS							4					// ��巩ũ�� �ִ� ���ȼ�
// ��帶ũ�� �⺻��
#define GUILD_DEFAULT_MARK1							0					// ��帶ũ1�� �⺻��(�ɺ�)
#define GUILD_DEFAULT_MARK2							0					// ��帶ũ2�� �⺻��(���)
#define GUILD_DEFAULT_MARK3							0					// ��帶ũ3�� �⺻��(ȿ��). �⺻ȿ���� ����Ʈ�� ���°����� �Ѵٰ� ��.
// ��帶ũ����
#define GUILDMARK_MAX_REQUIRE						3					// ��帶ũ����� �������� �ִ��


// ��å
enum { GUILD_GRADE_NONE, GUILD_GRADE_MASTER, GUILD_GRADE_NO2, GUILD_GRADE_NO3, GUILD_GRADE_NO4, GUILD_GRADE_NO5, GUILD_GRADE_NO6,  };
// ����(0:�۹�����, 1:��������, 2:���ΰǺ���, 3:����, 4:���Ա���, 5~9:����, 10:�����ִ��)
enum { GUILD_AUTHORITY_CROP, GUILD_AUTHORITY_GRADE, GUILD_AUTHORITY_SLOGAN, GUILD_AUTHORITY_EXPEL, GUILD_AUTHORITY_REQUEST, GUILD_AUTHORITY_RESERVE1, GUILD_AUTHORITY_RESERVE2, GUILD_AUTHORITY_RESERVE3, GUILD_AUTHORITY_RESERVE4, GUILD_AUTHORITY_RESERVE5, GUILD_MAX_AUTHORITY };
// ����޼���Ÿ��(0:����, 1:Ż��, 2:����, 3:��������, 4:�α���, 5:�α׾ƿ�, 6:����)
enum { GUILD_MSG_MEMBER_JOIN, GUILD_MSG_MEMBER_SECEDE, GUILD_MSG_MEMBER_EXPEL, GUILD_MSG_MEMBER_GRADE, GUILD_MSG_MEMBER_LOGIN, GUILD_MSG_MEMBER_LOGOUT, GUILD_MSG_MEMBER_CHANGEMASTER, };
// ���޼���Ÿ��(0:���ΰǺ���, 1:��ũ����, 2:����ɱ�, 3:����̱�, 4:������Ϸ�, )
enum { GUILD_MSG_GUILD_SLOGAN, GUILD_MSG_GUILD_RANK, GUILD_MSG_GUILD_PLANT, GUILD_MSG_GUILD_GRUB, GUILD_MSG_GUILD_GROWTHCROP, };
// ���Ÿ��(0:�۹��ƴ�, 1:���, 2:������)
enum { BOOSTER_TYPE_NONE, BOOSTER_TYPE_MANURE, BOOSTER_TYPE_HASTEN, };
// ���Ÿ��/����
enum { GUILD_TYPE_NONE, GUILD_TYPE_NEUTRALITY, GUILD_TYPE_ANGEL, GUILD_TYPE_DEVIL, GUILD_TYPE_NA, GUILD_TYPE_ND, GUILD_TYPE_AD, GUILD_TYPE_NAD, };
// ��帶ũŸ��(1:������, 2:���, 3:ȿ��)
enum { GMARK_TYPE_ICON = 1, GMARK_TYPE_BACKGROUND, GMARK_TYPE_EFFECT, };


typedef struct _GUILD_BROADCAST
{
	INT32	iGNum;
	char	szGName[GUILD_MAX_NAME+1];
#if defined(__ADD_GUILD_MARK) || defined(_LATALE_CLIENT)
	UINT8	arrGMark[3];						// �ɺ�, ���, ȿ��
#else
	UINT8	arrGMark[2];						// �ɺ�, ���
#endif
	UINT8	byGType;							// �������(1:�Ϲ�, 2:õ��, 3:�Ǹ�)
	UINT8	byGRank;							// ��巩ũ(����ִ��ο����� ������ ��ħ)

} GUILD_BROADCAST, *PGUILD_BROADCAST;

typedef struct _GUILD_COMMON
{
	char	szGSlogan[GUILD_MAX_SLOGAN+1];		// ��彽�ΰ�
	UINT32	uiCropID;							// ������̵�
	UINT32	uiRemainTime;						// ����ð��� ���Ͽ� ���� ����Ϸ���� �����ð�(�ʴ���)
	UINT32	uiNourishTime;						// ����ð��� ���Ͽ� ���� ��Ḧ ���� �ð�(�ʴ���)
	UINT32	uiHastenSumTime;					// ������ �����ð�

} GUILD_COMMON, *PGUILD_COMMON;

typedef struct _GUILD_SERVER
{
	INT32				iOriginRemainTime;					// DB�� ����� ����Ϸ���� �����ð�(�ʴ���)
	INT32				iOriginNourishTime;					// DB�� ����� ��Ḧ ���� �ð�(�ʴ���)
	time_t				tmMemLoadTime;						// ���Ӽ������� ó�� �ε�� �ð�. �ð� ����� �����.
	TIMESTAMP_STRUCT	stDBLoadTime;						// �ε�� DB�� GETDATE()�� ������.
	TIMESTAMP_STRUCT	stNourishStartTime;					// ��Ḧ �Ա� ������ �ð�
	INT32				iEventID;							// �����δ���Ż�̺�Ʈ���̵�
	UINT8				byIndunFinish;						// �δ����ɿ���(0:������, 1:���ɿϷ�)

} GUILD_SERVER, *PGUILD_SERVER;

typedef struct _GUILD : public GUILD_BROADCAST, public GUILD_COMMON
{

} GUILD, *PGUILD;

typedef struct _DBGUILD : public GUILD_BROADCAST, public GUILD_COMMON, public GUILD_SERVER
{

} DBGUILD, *PDBGUILD;

typedef struct _PCGUILD : public GUILD_BROADCAST, public GUILD_COMMON
{
	UINT8	byGrade;
#if defined(__ADD_GUILD_RANKUP) || defined(_LATALE_CLIENT)
	INT32	iPoint;				// �������Ʈ
#endif

} PCGUILD, *PPCGUILD;

typedef struct _DBPCGUILD : public GUILD_BROADCAST, public GUILD_COMMON, public GUILD_SERVER
{
	UINT8	byGrade;
#if defined(__ADD_GUILD_RANKUP) || defined(_LATALE_CLIENT)
	INT32	iPoint;				// �������Ʈ
#endif

} DBPCGUILD, *PDBPCGUILD;

typedef struct _GUILD_MEMBER
{
	INT32	iCharID;			// ĳ������ DBŰ
	INT32	iUserID;			// Account�� DBŰ(���������� ã�����Ѱ�)
	char	szName[LEN_NAME+1];	// ĳ����
	UINT8	byClass;			// ����
	UINT16	wLevel;				// ����
	UINT16	wServerID;			// �������̵�(ä������ǥ�ø� ���ؼ�)
	UINT8	byGrade;			// ��峻 ��å(1:�渶, 2:�α渶, 3~6:ȸ��)
#if defined(__ADD_GUILD_RANKUP) || defined(_LATALE_CLIENT)
	INT32	iPoint;				// �������Ʈ
#endif

} GUILD_MEMBER, *PGUILD_MEMBER;


// ���
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// �δ�

#define INDUN_MAX_PERSERVER						50					// �δ������� �δ��� �ִ��
#define INDUN_MAX_REQUIRE_IN					5					// �δ��������ǰ˻� �ִ��
#define INDUN_DESTROYTIME_WIHTOUTPC				60*10				// PC�� �δ��� �ƹ��� ������ �ı��Ǵ� �ð��� �ִ밪(�ʴ���)
#define INDUN_MIN_DESTROYTIME_WIHTOUTPC			1					// PC�� �δ��� �ƹ��� ������ �ı��Ǵ� �ð��� �ּҰ�(�ʴ���)
#define INDUNMISSION_MAX_REQUIRE				2					// �δ��̼����Ǽ�
#define INDUNMISSION_MAX_MISSION				2					// �δ��̼Ǽ�
#define INDUNMISSION_MAX_REWARD					3					// �δ��̼Ǻ����
#define INDUNIN_MAX_PERPACKET					100					// MgmtServer�� ���ӽ� ����������� ���ؼ� ������ ��Ŷ�� �δ����������� �ִ��
#define INDUN_CHANNEL_MAX						20					// 50 ���� ũ�� �δ� ����
#define INDUN_PVP_CHANNEL_MAX					80					// 80 ���� ũ�� PVP�δ�

// �δ�Ÿ��
enum { INDUN_TYPE_GUILD = 1, INDUN_TYPE_TEAM, INDUN_TYPE_SOLO, INDUN_TYPE_EVENT, INDUN_TYPE_GUILDINDUN, INDUN_TYPE_CHATROOM };
// �δ�����
enum { INDUNIN_STATUS_RESERVE = 0, INDUNIN_STATUS_CREATE, };
// �δ��̼�Ÿ��
enum { INDUNMISSION_TYPE_NONE = 0, INDUNMISSION_TYPE_MOBCNT, INDUNMISSION_TYPE_MAPEVENT, };
// �δ��̼Ǻ���Ÿ��
enum { INDUNMISSION_REWARD_TYPE_NONE = 0, INDUNMISSION_REWARD_TYPE_MAPEVENT, INDUNMISSION_REWARD_TYPE_EFFECT, };

typedef struct _INDUNIN
{
	UINT32	uiID;				// �δ� �ν��Ͻ� ���̵�
	UINT32	uiLDTID;			// �δ� LDT ���̵�
	UINT8	byType;				// �δ�Ÿ��(1:����δ�, 2:�ַ��δ�, 3:���δ�, 4:�̺�Ʈ�δ�)
	INT32	iGuildNum;			// ��� DBŰ
	UINT32	uiTeamID;			// �� ���̵�
	INT32	iCharID;			// ĳ���� DBŰ
	UINT16	wServerID;			// �������̵�(��δ��������� ������ ���ؼ�)

} INDUNIN, *PINDUNIN;

typedef struct _tagINDUNMISSION
{
	UINT8	byType;	// 0:NONE, 1:��ī��Ʈ, 2:���̺�Ʈ
	UINT32	uiID;
	INT32	iFinishCnt;	// �̼ǿϷ�ī��Ʈ
	INT32	iCurCnt;	// ����ī��Ʈ(LDT�ε�/�δ��̼ǰ������� �Բ� ���)

} INDUNMISSION, *PINDUNMISSION;

// �δ�
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// PVP

#define PVP_MAX_PERSERVER						500					// PVP������ PVP�� �ִ��
#define PVP_MAX_REQUIRE_IN						5					// PVP�������ǰ˻� �ִ��
#define PVP_DESTROYTIME_WIHTOUTPC				60*3				// PC�� PVP�� �ƹ��� ������ �ı��Ǵ� �ð�(�ʴ���)
#define PVPIN_MAX_PERPACKET						200					// MgmtServer�� ���ӽ� PVP��������� ���ؼ� ������ ��Ŷ�� PVP���������� �ִ��
#define PVP_MAX_ROOMUSER						8					// ���� �Ѱ��� PVP ����� ��
#define PVP_MAX_STARTPOS						8					// ������ġ�� �ִ��
#define PVPDIVISION_MAX_PVPINDUN				20					// PVP�δ��� �����ϰ� �����ϱ� ���� �������� �ִ��
#define PVP_TIME_ALARM							30					// �߰������� Ŭ���̾�Ʈ�� �����ִ� �ð�����(�ʴ���)
#define PVP_TIME_PLAY							60*5				// �÷��̽ð�(�ʴ���)
#define PVP_MAX_RANK							8					// ������ ��(8����� ����. PVP_POINT.LDT�� ��������)
#define	PVP_REVIVAL_DELAY						5					// ���� ��Ȱ���ð�(�ʴ���)
#define PVP_MAX_POINT							2000000000			// PVP����Ʈ�� �ִ밪
#define PVP_MAX_GLORY							999999999999999		// PVP���� �ִ밪

// PVPŸ��
enum { PVP_TYPE_NONE = 0, PVP_TYPE_FDEATH = 1, PVP_TYPE_FTIME, PVP_TYPE_PDEATH, PVP_TYPE_PTIME, PVP_TYPE_GDEATH, PVP_TYPE_GTIME, PVP_TYPE_MAX, };
// PVP�Ը�(�ߺ����������ϵ��� 2�ǹ���� ����)
enum { PVP_SCALE_NONE = 0, PVP_SCALE_2 = 1, PVP_SCALE_4 = 2, PVP_SCALE_6 = 4, PVP_SCALE_8 = 8, PVP_SCALE_MAX, };
// PVP�Ը�Ÿ��(LDT���� �ԷµǴ� ��)
enum { PVP_SCALETYPE_NONE = 0, PVP_SCALETYPE_2, PVP_SCALETYPE_4, PVP_SCALETYPE_6, PVP_SCALETYPE_8, PVP_SCALETYPE_MAX, };
// ��ġ�ּ��ο�
enum { PVP_MIN_MEMBERCNT_FTIME_2 = 2, PVP_MIN_MEMBERCNT_FTIME_4 = 4, PVP_MIN_MEMBERCNT_FTIME_6 = 6, PVP_MIN_MEMBERCNT_FTIME_8 = 8, };
// PVPIN����
enum { PVPIN_STATUS_RESERVE = 0, PVPIN_STATUS_CREATE, };
// PVPLOADSTATUS
enum { PVPLOADSTATUS_STATUS_NOTLOAD = 0, PVPLOADSTATUS_STATUS_LOAD, PVPLOADSTATUS_STATUS_DISCONNECT, };
// PVPSTATUS(PVP�δ��� ����)
enum { PVP_STATUS_NONE = 0, PVP_STATUS_PLAY, PVP_STATUS_FINISH, };

typedef struct _PVPIN
{
	UINT32	uiID;				// PVP �ν��Ͻ� ���̵�
	UINT32	uiLDTID;			// PVP LDT ���̵�
	UINT8	byType;				// PVPŸ��(1:����ų��, 2:�����ð���, 3:��ų��, 4:���ð���, 5:���ų��, 6:���ð���)
	UINT32	uiScale;			// ���ο�����(1:2�ο�, 2:4�ο�, 4:6�ο�, 8:8�ο�)
	UINT16	wServerID;			// �������̵�(�PVP�������� ������ ���ؼ�)

} PVPIN, *PPVPIN;

typedef struct _PVPWAIT
{
	INT32			iCharID;				// ĳ������ DBŰ
	INT32			iUserID;				// Account�� DBŰ(���������� ã�����Ѱ�)
	UINT16			wWorldID;				// ������̵�(��������PVP���� ������ �����)
	UINT16			wServerID;				// �������̵�
	INSTANCE_ID		PCIID;					// InstanceID
	char			szCharName[LEN_NAME+1];	// ĳ����
	UINT16			wLv;					// ����

} PVPWAIT, *PPVPWAIT;

typedef struct _PVPREGIST
{
	PVPWAIT			stPVPWait;				// ���������
	UINT8			byType;					// PVPŸ��(1:����ų��, 2:�����ð���, 3:��ų��, 4:���ð���, 5:���ų��, 6:���ð���)
	UINT32			uiScale;				// ���ο�����(1:2�ο�, 2:4�ο�, 4:6�ο�, 8:8�ο�)

} PVPREGIST, *PPVPREGIST;

typedef struct _PVPLOADSTATUS
{
	UINT32			uiTeamID;				// �����̵�(�����ΰ�� �����̵�, ������� ��� ���DBŰ, 0�� ���� ������)
	char			szCharName[LEN_NAME+1];	// ĳ����
	UINT8			byStatus;				// (0:�ε���, 1:�ε�Ϸ�)

} PVPLOADSTATUS, *PPVPLOADSTATUS;

typedef struct _PVPSTATUS
{
	INT32			iCharID;				// ĳ���� DBŰ
	UINT32			uiTeamID;				// �����̵�(�����ΰ�� �����̵�, ������� ��� ���DBŰ, 0�� ���� ������)
	char			szCharName[LEN_NAME+1];	// ĳ����
	UINT8			byStatus;				// (0:�ε���, 1:�ε�Ϸ�)
	INT32			iPosIndex;				// ��ġ����
	INT32			iDamage;				// ������
	INT32			iKillCnt;				// ���μ�
	INT32			iDeathCnt;				// ������

} PVPSTATUS, *PPVPSTATUS;

typedef struct _PVPRANK
{
	INT32			iCharID;				// ĳ���� DBŰ
	INT32			iRank;					// ����
	char			szCharName[LEN_NAME+1];	// ĳ����
	INT32			iKillCnt;				// ���μ�
	INT32			iDeathCnt;				// ������
	INT32			iScore;					// ������ �����ϱ����� ��(�������� * ((���μ�*2)-������)) 2007.11.25 dhpark ������ ����
	INT32			iPVPPoint;				// �̹���⿡�� ȹ���� PVP����Ʈ

} PVPRANK, *PPVPRANK;

// PVP
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ��ȭ��
#ifndef MAX_BUF_LEN
#define MAX_BUF_LEN		4096
#endif
#define MIN_LEN_ROOOMTITLE	4
#define MAX_ROOM_NUMBER 999
// ��ȭ�� Ÿ�� �з�
// enum { CHATROOM_TYPE_GENERAL = 0, CHATROOM_TYPE_MARKET, CHATROOM_TYPE_OFFERJOB, CHATROOM_TYPE_MEETING, MAX_CHATROOM_TYPE, };
#define MAX_CHATROOM_TYPE 4
// ��ȭ�� ���� �з�
// enum { CHATROOM_SEX_ALL = 0, CHATROOM_SEX_MAN, CHATROOM_SEX_WOMAN, MAX_CHATROOM_SEX, };
#define MAX_CHATROOM_SEX 3
// ��ȭ�� ���ɴ� �з�
//enum { CHATROOM_AGE_ALL = 0, CHATROOM_AGE_ELEMENTARY, CHATROOM_AGE_MIDDLE, CHATROOM_AGE_HIGH, MAX_CHATROOM_AGE, };
#define MAX_CHATROOM_AGE 4
// ��ȭ�� ī�װ� �з�
enum { /*CHATROOM_CATEGORY_NONE = 0, */CHATROOM_CATEGORY_1 = 0, CHATROOM_CATEGORY_2, CHATROOM_CATEGORY_3, CHATROOM_CATEGORY_4, MAX_CHATROOM_CATEGORY, };
// Indun LDT �� ����� ��ȭ�� Ÿ��
enum { CHATROOM_CATEGORY_NORMAL = 1000, CHATROOM_CATEGORY_MARKET, CHATROOM_CATEGORY_TAKE, CHATROOM_CATEGORY_MEET, };
// CHATROOM_SC_BROADCAST_UNITED_MESSAGE ���� ���� Flag �� ������
enum { CHATROOM_UNITED_MSG_JOIN = 0, CHATROOM_UNITED_MSG_OUT, CHATROOM_UNITED_MSG_FORCEOUT, CHATROOM_UNITED_MSG_CHANGEMASTER, MAX_CHATROOM_UNITED_MSG, };
// ��ȭ�� ������Ʈ �̹��� ������
#define CHATROOM_LEFT_SIZE		-128
#define CHATROOM_TOP_SIZE		-227
#define CHATROOM_RIGHT_SIZE		128
#define CHATROOM_BOTTOM_SIZE	0

typedef struct _CHATROOM_INFO
{
	TCHAR			szTitle[MAX_CHATROOM_TITLE_LEN+1];			// ��ȭ�� ����
	UINT8			iCategory;									// ��ȭ�� Ÿ��(0:�Ϲ�, 1:����, 2:����, 3:����)
	UINT8			iSex;										// ����
	UINT8			iAge;										// ���� ��
	UINT8			iLimitNum;									// �ִ� �ο� ��
	TCHAR			szPassword[MAX_CHATROOM_PASSWORD_LEN+1];	// ��й�ȣ

	UINT32			uiID;										// ��ȭ�� �ν��Ͻ� ���̵� (Unique Key)
	UINT32			uiRoomNo;									// ��ȭ�� ��ȣ
	UINT32			iMasterCharID;								// ���� ĳ���� DBŰ
	TCHAR			szMasterName[LEN_NAME+1];					// ��ȭ�� ������ ĳ���� �̸�.
	UINT8			iCurrentNum;								// ���� �ο� ��
} CHATROOM_INFO, *PCHATROOM_INFO;

typedef struct _ROOM_MEMBER 
{
	//UINT8		uiMaster;
	CLASS_TYPE	eClassType;
	UINT32		uiCharID;
	TCHAR		szCharName[LEN_NAME+1];
}ROOM_MEMBER, *PROOM_MEMBER;

typedef struct _BAN_MEMBER 
{
	UINT8		uiCount;
	UINT32		uiCharID;
	//TCHAR		szCharName[LEN_NAME + 1];
}BAN_MEMBER, *PBAN_MEMBER;

typedef struct _CHATROOM_OBJECT
{
	UINT32		uiIndunID;
	UINT8		iCategory;
	SERVER_ID	ServerID;
	SERVER_ID	IndunServerID;
	GU_ID		uiObjectID;
} CHATROOM_OBJECT, *PCHATROOM_OBJECT;

typedef struct _CHATROOM_OBJECT_INFO
{
	UINT32			uiID;										// ��ȭ�� �ν��Ͻ� ���̵� (Unique Key)
	UINT32			uiRoomNo;									// ��ȭ�� ��ȣ
	UINT8			iPassword;									// ����/����� (�н����� ��뿩��)
	UINT8			iCategory;									// ��ȭ�� Ÿ��(0:�Ϲ�, 2:����, 3:����, 4:����)
	TCHAR			szTitle[MAX_CHATROOM_TITLE_LEN+1];			// ��ȭ�� ����
	UINT8			iNowPCNum;									// ���� �ο���
	UINT8			iLimitNum;									// �ִ� �ο� ��
} CHATROOM_OBJECT_INFO, *PCHATROOM_OBJECT_INFO;

typedef struct _CHARACTER_BASICINFO				// ��ȭ�� ������ ���� ĳ���� �⺻ ����
{
	UINT16			wWorldID;
	UINT16			wServerID;
	UINT32			uiCharID;					// ĳ���� ID
	TCHAR			szName[LEN_NAME+1];
	UINT16			uiLevel;					// ����
	UINT8			uiClassType;				// Class Type
	UINT8			uiSex;						// 1: ��, 2: ��
	INT32			iGameOptions;				// ���ӿɼǵ�
	PCSTATUS_STYLE	stStyle;
} CHARACTER_BASICINFO, *PCHARACTER_BASICINFO;

#define CHATROOM_MAX_PERPACKET	40
#define CHATROOM_MIN_MEMBER_IN_ROOM		2
#define CHATROOM_MAX_MEMBER_IN_ROOM		50
#define CHATROOM_MAX_USER_TYPESEARCH	50

// ��ȭ��
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// GlobalEvent

#define GLOBALEVENT_MAX_RATE		1000*100		// ��ȹ���� ������ 100��� �ý������� ������ 1000��� �����մϴ�. 2008.03.19 dhpark ��ȹ������ڿ� ����
#define GLOBALEVENT_MIN_DATEDIFF	5*60*1000		// ���۽ð��� ����ð��� ���� �ּ� 5��
#define GLOBALEVENT_MAX_DATEDIFF	24*60*60*1000	// ���۽ð��� ����ð��� ���� �ִ� 24�ð�
#define GLOBALEVENT_MAX_COMMANDERID	20				// ����ھ��̵����
#define MAX_GLOBALEVENT_PERPACKET	40				// ��Ŷ�� �ִ� �̺�Ʈ��

// �̺�Ʈ������Ÿ�� �з�
enum { GLOBALEVENT_COMMANDTYPE_SYSTEM = 0, GLOBALEVENT_COMMANDTYPE_GM, };

typedef struct _tagGLOBALEVENT
{
	UINT32 uiID;
	UINT32 uiLDTID;				// byCommanderType�� 0�ΰ�� LDTID
	UINT16 wWorldID;
	UINT16 wServerID;
	UINT8 byCommanderType;		// 0:�ý���, 1:����
	char szCommander[GLOBALEVENT_MAX_COMMANDERID+1];
	SYSTEMTIME stStartTime;
	SYSTEMTIME stEndTime;
	UINT32 uiExpRate;
	UINT32 uiItemDropRate;
	UINT32 uiElyRate;
	UINT32 uiItemRareRate;
	UINT32 uiPortalID;			// ��ŻŸ�� MapEventID
	UINT32 uiMaxUseCnt;			// ��Ż���ȸ��
	UINT32 uiNPCID;				// NPC�� MapEventID

} GLOBALEVENT, *PGLOBALEVENT;

// GlobalEvent
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Auction
#define AUCTION_FEE_MIN			1			// ELY������/cash.mile ��Ͻ� ������ �ּҰ�
#define	SET_AUCTION_FEE(up, ratio, fee) {fee = up*ratio/100; if(ratio && !fee) fee = AUCTION_FEE_MIN;}

// ely,cash,mile ��Ͻ�
#define	AUCTION_UPPOINT_MIN		10			
//#define	AUCTION_UPPOINT_MAX		999999999	// 999,999,999 

// ������/���۰�/�ﱸ��
#define AUCTION_PRICE_MIN		10			
//#define AUCTION_PRICE_MAX		999999999999 // 999,999,999,999 

#define	AUCTION_ELY_MAX			999999999	//999,999,999
#define AUCTION_MILE_MAX		9999999		//9,999,999
#define AUCTION_CASH_MAX		9999999		//9,999,999


// ��ī�װ� ���̵�
enum AUCTION_CATEGORY
{
	AUCTION_CATEGORY_NULL, 
	AUCTION_CATEGORY_ITEM, 
	AUCTION_CATEGORY_ELY = 8, 
	AUCTION_CATEGORY_CASH, 
	AUCTION_CATEGORY_MILEAGE, 
	MAX_AUCTION_CATEGORY 
};

#define CATEGORY_UNIT 1000			// ��ī�װ� ����
#define GET_CATEGORY(x) (x * CATEGORY_UNIT) // ��ī�װ�

// ������ ��� ī�װ� üũ
// Usage 
// short iCategory = GET_CATEGORY(AUCTION_CATEGORY_ELY);
#define CHECK_AUCTION_ITEM_CATEGORY(x) ( x < GET_CATEGORY(AUCTION_CATEGORY_ELY))

//
// ��� ��Ϻ�(������) Auction(20080404).doc
// Usage 
//		__int64 iEnrolFee = GET_AUCTION_ENROLFEE_ITEMELY(iStartPrice, ItemLv, ItemQuality, ItemDurability); 
//		iEnrolFee = GET_AUCTION_ENROLFEE(iEnrolfee, pTypeInfo->GetPeriodRate(iDuration))
//

// �����۵�Ϻ�

#define MIN_AUCTION_STARTPRICE_FACTOR 1
#define MAX_AUCTION_STARTPRICE_FACTOR 9999
#define MIN_AUCTION_GAMEPRICE_FACTOR 1
#define MAX_AUCTION_GAMEPRICE_FACTOR 9999
#define MIN_AUCTION_STANDARDPRICE_FACTOR 1
#define MAX_AUCTION_STANDARDPRICE_FACTOR 9999

//__int64 iEnrolFee = GET_AUCTION_ENROLFEE_ITEM(pAuction->iStartPrice, iStartPriceFactor, pUpItemInfo->m_iPrice,iGamePriceFactor, tUpDBItem.ItemData.iStackCount);
//__int64 iStandardPrice = GET_AUCTION_ENROLFEE_ITEM_STANDARD(pUpItemInfo->m_iItemLv, iStartPriceFactor);
//if(iEnrolFee < iStandardPrice) iEnrolFee = iStandardPrice;

#define GET_AUCTION_ENROLFEE_ITEM(StartPrice, StartPriceFactor, GamePrice, GamePriceFactor, ItemCount) ((__int64)(StartPrice * StartPriceFactor) / 1000 + (__int64)(GamePrice * GamePriceFactor) / 1000 * ItemCount)
#define GET_AUCTION_ENROLFEE_ITEM_STANDARD(ItemLv, StandardFactor) ((__int64)(ItemLv * StandardFactor) / 10)

//  ���� ��Ϻ�
//		Auction_Enrol ={(Game_Money*0.05)+(Auction_Money*2)}/2
#define	GET_AUCTION_ENROLFEE_ELY(StartPrice,  UpPoint) ((UpPoint*5/100 + (__int64)StartPrice*2) /2 + 0.5f)

//	ĳ�� ��Ͻ� ��� ��� ����
// 		Auction_Enrol ={(Cash_money*30)+( Auction_Money*0.2)}/2
#define	GET_AUCTION_ENROLFEE_CASH(StartPrice,  UpPoint) ((UpPoint*30 + (__int64)StartPrice*2/10) /2 + 0.5f)

//	���ϸ��� ��Ͻ� ��� ��� ����
//		Auction_Enrol = {(Mile_Money*25)+(Auction_Money0.2)}/2
#define	GET_AUCTION_ENROLFEE_MILE(StartPrice,  UpPoint) ((UpPoint*25 + (__int64)StartPrice*2/10) /2 + 0.5f)

//	���� ��� ��� =  Auction_Enrol +(Auction_Enrol*Auction_Time*0.01)
#define GET_AUCTION_ENROLFEE(Fee, FeeAddRate) (Fee + (Fee * FeeAddRate/100) + 0.5f)

//	��� ���۰� ���
#define GET_AUCTION_STARTMONEY(GamePrice, SysStartMoney, iItemCount) (((GamePrice * SysStartMoney / 1000) + 0.5f) * iItemCount)

// Auction
//------------------------------------------------------------------------------

#define MAX_MONEY			999999999999	// 999,999,999,999 pc �� ��������
#define MAX_CASH			2100000000		// ������ ĳ�� ������
#define MAX_MILE			2100000000		// ������ ���ϸ��� ������

#include <typeinfo.h>

#define DYNAMIC_CAST(T,X) X ? dynamic_cast<T>(X) : (T)X
#define VALID_DYNAMIC_CAST(T,X) X ? (typeid(X) == typeid(T) ? dynamic_cast<T>(X) : 0/*(T)X*/) : 0

#pragma pack(pop)


