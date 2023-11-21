// packetID.h

#pragma once

#ifdef _LATALE_CLIENT
	#include "BaseTypes.h"
#endif
#include "SPGameObjectDEF.h"
//#include "../LataleGameLogic/ItemStruct.h"
#include <time.h>
#include "SQLTypes.h"

#define __NEW_STAT 1
#define PACKET_ID_VERSTION	0.7
// history
/*

	0.7
		- 2006/6/2	: int,unsigned int ����
	0.6
		- 8�� 8�� �系 �׽�Ʈ ����
	0.5
		- WORLD_ID ���� : CHAR_CS_CREATE,CHAR_CS_CHECK_CHARNAME,CHAR_CS_DELETE
	0.4 
		- CHARACTER_INFO ����. ��� �ҽ� CHARACTER_INFO2 ����ϰ� ����
		- NAV_SC_INSIGHT �۽Ž�, MOB�� ��� MONSTER_INFO �۽��ϰ� ����
		- CharName : 12 ==> 16 ���� ����

	0.3
		.... �߷�
*/


// LEN_ID / LEN_PW ��ſ� g_LEN_ID / g_LEN_PW (GlobalDefines_Share.h) �� ����� ��.   2006/11/29
//
// ID/PW/CHARNAME Length Definition 
//{
		#define	MIN_LEN_NAME			2
		#define MIN_LEN_GUILDNAME		2			// for CHINA

		#define LEN_NAME				16			// charName,Name

		#define	MAX_LEN_ID				24
		#define	MAX_LEN_PW				24
		#define	MAX_LEN_NAME			24

		// 2007.02.27	dhpark	DB������ ��������� ���� ����. ����� ���������� ����ϱ� ���ؼ� ������.
		// 2007-5-3		hoshim	LEN_ID/PW�� ���� ���Ӽ� ���� �������� ���� �ڵ�󿡵� ���Ǳ� ����.
		#define	MAX_LEN_ID_DB			20
		#define	MAX_LEN_PW_DB			20
		#define	MAX_LEN_NAME_DB			20
		#define LEN_BILLING_KEY			40 

	#if MAX_LEN_ID_DB >= MAX_LEN_ID
		#error "MAX_LEN_ID_DB DEFINITION [FAILED]: MAX_LEN_ID_DB >= MAX_LEN_ID !!!"
	#endif

	// MIN_LEN_NAME <= LEN_NAME <MAX_LEN_NAME
	#if LEN_NAME >= MAX_LEN_NAME
		#error "LEN_NAME DEFINITION [FAILED]: MAX_LEN_NAME > LEN_NAME !!!"
	#endif

//}

#define MAGIC_CHAR					'*'

#define LEN_IP						16			// ip address
#define LEN_SERVERNAME				20			// server name

#define MAX_CHATMSG_LEN				150		// ä�� �޼��� ���ڿ� ���Ѱ�
#define LEN_CASHITEM_NORMAL_MSG		60		// Cash Item - '����/ä�� ��ġ��'�� ���ڿ� ���Ѱ�
//#define LEN_CASHITEM_EVENT_MSG		150		// Cash Item - '�̺�Ʈ �޼���'�� ���ڿ� ���Ѱ�

#define MAX_CHAR_NUM				3			// ������ �������� ĳ���� ��
#define MAX_CHAR_DEL				30			// ������ ĳ�� �ִ����Ƚ��
#define MAX_WORLDS					10			// �ִ� ���� ��
#define MAX_CHANNELS				20			// ���峻 �ִ� ä�� ��(1 ~ 20)
#define MAX_INDUNS					30			// ���峻 �ִ� �δ����� ��(51 ~ 80)
#define MAX_PVPS					19			// ���峻 �ִ� PVP���� ��(81 ~ 99)
#define MAX_LOBBYS					1			// ���峻 �ִ� �κ񼭹� ��
#define MAX_WORLDSERVERS			MAX_CHANNELS + MAX_INDUNS + MAX_PVPS + MAX_LOBBYS
#define MAX_GAMESERVERS				MAX_CHANNELS + MAX_INDUNS + MAX_PVPS

// ��ȹ�����ؼ� ������ �̸� �ִ�ũ�� �䱸��.(�ӽ�)
// DB �� �����Ǿ� �ֱ� ������ ���� ���� ���� �Ұ� !!!!!
#define MAX_ITEM_NAME		30  

#define MAX_CHATROOM_TITLE_LEN		40
#define MAX_CHATROOM_ADVERT_LEN		50
#define MAX_CHATROOM_PASSWORD_LEN	4

#define MAX_FRIEND_LIST				99
#define MAX_BLOCK_LIST				99

// MailBox
#define	MAILBOX_MAX_ENTRY			40			// (����) �������� �ִ� ���� ����
#define	MAILBOX_MAX_SUBJECT_LEN		50			// ���� ���� �ִ� ũ��
#define	MAILBOX_MAX_MEMO_LEN		100			// ���� ���� �ִ� ũ��
#define MAILBOX_SEND_FEE			50			// ���� ���� ������

#define KEEP_ALIVE_TIMEOUT			10000		// 10��

#define PACKET_MAGIC_NUMBER			0	

#define DECLARE_VAR(TYPE,VAR,LEN)	TYPE VAR[LEN+1]; memset(VAR,0,sizeof(VAR))
//#define ZEROVAR(VAR,SIZE)			memset(VAR,0,SIZE)
//#define ZERO_TCHAR(X,LEN)			memset(X,0,sizeof(TCHAR)*LEN)

#define DECLARE_TCHAR(VAR,LEN)		TCHAR VAR[LEN+1]; memset(VAR,0,sizeof(VAR))

#define BETWEEN(X,Y,Z)				Y = max(X,Y); Y = min(Y,Z)

#if 0
typedef unsigned short	WORLD_ID;
typedef WORLD_ID		REALM_ID;

typedef unsigned short	SERVER_ID;
typedef unsigned short	SERVER_PORT;

typedef unsigned char	RESULTCODE;

typedef unsigned long	USERID;
typedef unsigned long	PASSPORT;
typedef unsigned long	CHARID;

typedef unsigned long	ACTIONID;

typedef unsigned long	GLOBAL_STRING_ID;

#else

typedef UINT16		WORLD_ID;
typedef WORLD_ID	REALM_ID;

typedef UINT16		SERVER_ID;
typedef UINT16		SERVER_PORT;

typedef UINT8		RESULTCODE;


typedef UINT32		USERID;
typedef UINT32		PASSPORT;
typedef UINT32		CHARID;
typedef UINT32		ENTIRYID;


typedef UINT8		ACTIONID;

typedef UINT32		GLOBAL_STRING_ID;


#endif


//enum {GENDER_NONE,GENDER_MALE,GENDER_FEMALE,GENDER_BOTH};
enum GENDER
{
	GENDER_INVALID	= -1,
	GENDER_NULL		= 0,
	MALE			= 0x01,
	FEMALE			= 0x02,
	GENDER_BOTH		= MALE | FEMALE,
};

//#ifdef __CHANGE_CLASS
enum CLASS_TYPE {
	CLASS_NULL	= 0,
	CLASS_A		= 1,		// ������
	CLASS_B 	= 2,		// �����
	CLASS_C		= 3,		// ������
	CLASS_D		= 4,		// ������
	CLASS_E		= 5,		// ������
	CLASS_F 	= 6,		// ������
	CLASS_G		= 7,		// �����
	CLASS_H		= 8,		// ��ũ
	CLASS_I		= 9,		// ���÷�
	CLASS_J 	= 10,		// ��Ƽ��Ʈ
	CLASS_K		= 11,		// Ʈ��������
	CLASS_L		= 12,		// �ǳ�
	CLASS_M		= 13,		// �����Ͼ�(Base)
	CLASS_N		= 14,		// �����Ͼ�Ȯ��
	CLASS_MAX 
};
//#else
//enum CLASS_TYPE {
//	CLASS_NULL	= 0,
//	CLASS_A		= 1,		// ������
//	CLASS_B		= 2,		// �����
//	CLASS_C		= 3,		// ������
//	CLASS_D		= 4,		// ������
//	CLASS_MAX 
//};
//#endif

const int CLASS_CHANGE_BASE = (CLASS_D+1);
enum VERSION_OPTION{KEEPALIVE=1,VERBOSE};

enum SAVEPOINT_TYPE // shift count
{
	SAVEPOINT_TYPE_TOWN,	// ����.	
	SAVEPOINT_TYPE_SPOT,	// ��Ÿ����Ʈ.
	SAVEPOINT_TYPE_MAX,
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Packet ID (UINT32)
//////////////////////////////////////////////////////////////////////////////
/*
enum PACKETID
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Subject1
	//
	
		SUBJECT1_BASE = 100,
		//---------------------------------------------------------------------------
		//	Server <-> Client
		//---------------------------------------------------------------------------

		//---------------------------------------------------------------------------
		//	Server <-> Server
		//---------------------------------------------------------------------------
}

*/

// 2006.08.07 dhpark ��Ŷ���� ���� �����մϴ�.
#define PACKETID		UINT32
#define PI_CS_BASE		0				// 0				~	999,999,999		0���� 10�� -1 ����
#define PI_SS_BASE		1000000000		// 1,000,000,000	~	1,999,999,999	10����� 20�� - 1 ����
#define PI_SYSTEM_BASE	0				// 0
#define PI_TOOL_BASE	100000000		// 1��
#define PI_LOGIC_BASE	200000000		// 2��
#define PI_SITE_BASE	300000000		// 3��

#define PI_CS_SYSTEM	PI_CS_BASE + PI_SYSTEM_BASE
#define PI_CS_TOOL		PI_CS_BASE + PI_TOOL_BASE
#define PI_CS_LOGIC		PI_CS_BASE + PI_LOGIC_BASE
#define PI_SS_SYSTEM	PI_SS_BASE + PI_SYSTEM_BASE
#define PI_SS_TOOL		PI_SS_BASE + PI_TOOL_BASE
#define PI_SS_LOGIC		PI_SS_BASE + PI_LOGIC_BASE
#define PI_SS_SITE		PI_SS_BASE + PI_SITE_BASE

// ������ Subject�� ������ �⺻ 100 ���� ��õ...
// ��)	PI_CS_SUBJECT3 = PI_CS_TOOL + 700,
//		PI_SS_SUBJECT3 = PI_SS_TOOL + 700,

/*
enum PACKETID_CS_SYSTEM
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Subject1
	//
	
		PI_CS_SUBJECT1 = PI_CS_SYSTEM + 100,

}

enum PACKETID_CS_TOOL
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Subject2
	//
	
		PI_CS_SUBJECT2 = PI_CS_TOOL + 100,

}

enum PACKETID_CS_LOGIC
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Subject3
	//
	
		PI_CS_SUBJECT3 = PI_CS_LOGIC + 100,

}


"PacketID4GM.h"
enum PACKETID_SS_SYSTEM
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Subject1
	//
	
		PI_SS_SUBJECT1 = PI_SS_SYSTEM + 100,

}

enum PACKETID_SS_TOOL
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Subject2
	//
	
		PI_SS_SUBJECT2 = PI_SS_TOOL + 100,

}

enum PACKETID_SS_LOGIC
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Subject3
	//
	
		PI_SS_SUBJECT3 = PI_SS_LOGIC + 100,

}

*/


enum PACKETID_CS_SYSTEM
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Echo (HeartBeat)
	//
		PI_CS_ECHO = PI_CS_SYSTEM + 0,
		
		ECHO_XX_PACKET = PI_CS_ECHO,
		KEEP_ALIVE_PACKET = PI_CS_ECHO, // ���ŵ� ��Ŷ�� �������� �״�� �������Ѵ�.

	//////////////////////////////////////////////////////////////////////////////
	//
	// Protocol : Start & Version Check
	//
		PI_CS_PROTOCOL = PI_CS_SYSTEM + 100,
		
		// Step 1 : OnAccept���� ���ʷ� ������ Ŭ���̾�Ʈ���� �����ϴ� ��Ŷ
		PROTOCOL_SC_START_REQ = PI_CS_PROTOCOL,				// nProtect (���� ���� ����)
		// UINT8	uiStartDataLen;				// sizeof(GG_AUTH_DATA)		: �������� Ű�� �����Ͽ� Ŭ���̾�Ʈ�� ����
		// TCHAR	szStartData[];				// GG_AUTU_DATA
		// UINT8	uiCipherMode;

		// Step 2 : Ŭ���̾�Ʈ�� ����
		PROTOCOL_CS_START_RES,				// Ŭ���̾�Ʈ������ ���� ���忡 �ѱ���, ������� ����.  �����󿡼� �� ���� Ȯ���Ͽ� ���� ���� ���¸� �����Ѵ�. 
		// UINT8	uiStartDataLen;
		// TCHAR	szStartData[];

		// Step 3 : �� �������� Ŭ���̾�Ʈ�� ��Ŷ�� ������ ������ �� �ִ�.
		PROTOCOL_SC_START,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��

		//PROTOCOL_CS_VERSION_CHECK,
		//// UINT16 major;
		//// UINT16 minor;
		//// UINT32 option;		// VERSION_OPTION ����
		//		//option :

		//		//	1st bit : Keep-alive packet sending ON/OFF
		//		//	2nd bit : Verbose ON/OFF
		//		//	3rd bit : reserved
		//		//	...		: reserved

		//PROTOCOL_SC_VERSION_CHECK,
		//// RESULTCODE resultCode;			// LT_ERROR_VERSION_LOWER or LT_NO_ERROR or LT_ERROR_VERSION_UNSURPORTED_OPTION

		// �Ϲ����� ��Ŷ ���� ���� �߻�
		SYSTEM_SC_ERROR,
		// GLOBAL_STRING_ID	itemID;	
		// UINT16	uiPacketLen;			// �����߻� ������ ��Ŷ ����
		// UINT16	uiPacketKey;
		// UINT32	uiPacketID;

		PROTOCOL_SC_START_DYNCODE_1,			// for SNDC (Step 1)
		// UINT32	iDynCodeLen;
		// BYTE		szDynCode[];

		PROTOCOL_SC_START_DYNCODE_2,			// for SNDC (Step 2)
		// UINT32	iDynCodeLen;
		// BYTE		szDynCode[];


		PROTOCOL_SC_CHECK_CLIENT_VALIDATION_REQ,
		// UINT32	uiValue1
		// UINT32	uiValue2
		// UINT32	uiValue3
		// UINT32	uiValue4

		PROTOCOL_CS_CHECK_CLIENT_VALIDATION_RES,
		// UINT32	uiValue1
		// UINT32	uiValue2
		// UINT32	uiValue3
		// UINT32	uiValue4

		// DNS Server ���� site������ '���� ����' ��� �̿�� LS���� �翬�� ���� ����
		PROTOCOL_SC_LOGINSERVERINFO,
		// UINT16	uiServerID;
		// TCHAR	szIP[LEN_IP];
		// UINT16	usPort;


	//////////////////////////////////////////////////////////////////////////////
	//
	// World Environment (DATETIME/Weather,...) (GameServer)
	//
		PI_CS_WORLDENV = PI_CS_SYSTEM + 200,

		// ���� Ÿ�� ����
		WORLDENV_SC_DATETIME = PI_CS_WORLDENV,
		// UINT8	year;
		// UINT8	month;
		// UINT8	day;
		// UINT8	hour;
		// UINT8	minute;
		// UINT8	second;

		WORLDENV_SC_WEATHER ,
		// UINT8	weatherType;		// Sunny,rainy,windy,cloudy,...

	//////////////////////////////////////////////////////////////////////////////
	//
	// �ߺ��α��ΰ˻�
	//
		PI_CS_USER = PI_CS_SYSTEM + 300,

		// ���Ӽ����� ������ �α����Ѵٰ� �˸��ϴ�.(�α���, �κ�, ����)
		USER_CS_IN = PI_CS_USER,
		// UINT32			uiUserID;
		// PASSPORT			uiPassport;
		// TCHAR			szIP[LEN_IP+1];

		// Ŭ���̾�Ʈ�� �ߺ��˻� ����� �۽��մϴ�.
		USER_SC_IN,
		// GLOBAL_STRING_ID	uiErrorID;
		// PASSPORT			uiPassport;

		// ���Ӽ����� ������ �̵��Ѵٰ� �˸��ϴ�.(�α���->�κ�, �κ�->����, ����->����, ����->�α���, �κ�->�α���)
		USER_CS_MOVE,
		// UINT16			wDstServerID;

		// Ŭ���̾�Ʈ�� �̵� ����� �۽��մϴ�.
		USER_SC_MOVE,
		// GLOBAL_STRING_ID	uiErrorID;

	//////////////////////////////////////////////////////////////////////////////
	//
	// Cheat 
	//
		PI_CS_CHEAT = PI_CS_SYSTEM + 400,

		// ���� ��ġ�� �־��� ������ ����(������) for cheating
		//   ������ NAV_SC_MOVE�� ��ε�ĳ����
		CHEAT_CS_SETPOSITION = PI_CS_CHEAT,
		// TCHAR			charName[LEN_NAME];
		// LT_POSITION		pos;

		// GM�� cheat mode ���� ����
		CHEAT_CS_COMMAND ,
		// UINT8			len;
		// TCHAR			szCheatCommand[];			//<CheatCommand><whitespace><ParamList>


	//////////////////////////////////////////////////////////////////////////////
	//
	// Notification
	//
		NOTI_SC_BASE = PI_CS_SYSTEM + 500,

		// �˸��� ����(ģ��,...)
		NOTI_SC_ONLINE_STATUS_FRIEND = NOTI_SC_BASE,
		// UINT8		uiNotiType;				// 1(NotiType_Friend_OnlineStatus)
		// UINT8		uiStatus;				// 1(CH_IN),2(CH_OUT) [,3(CH_MOVE),4(ETC)]
		// UINT16		uiServerID;				// ���� ��ġ�� ����
		// UINT32		uiActorCharID;
		// UINT8		len;
		// TCHAR		szActorCharName[];


		// ��ϵ� ģ���� online���� ���� ������ �˸�. (ON,OFF)
		NOTI_MG_FRIEND_STATUS,
		// UINT8		uiNotiType,				// 1(NotiType_Friend_OnlineStatus)
		// UINT8		uiStatus,				// 1(CH_IN),2(CH_OUT) [,3(CH_MOVE),4(ETC)]
		// UINT32		uiCharID;				// Notification�� ������ ���
		// UINT32		uiNotiActorCharID;		// �ش� Notification�� ���
		// UINT16		uiServerID;				// Actor�� ��ġ�� ����
		// UINT8		len;
		// TCHAR		szActorCharName[];

		// CHANNEL_CS_IN ���¿��� ģ������� �����.
		// Ȥ�� �ش� ĳ������ ģ�� ����� �����ϸ� ���� ����� ��� �����ϰ� ���� �����
		NOTI_GM_FRIEND_REGISTER_LIST,
		// UINT32		uiCharID;
		// UINT8		nCount;
		// UINT32		uiFriendCharID[];

		// CHANNEL_CS_OUT ���¿��� uiCharID�� ģ������� ��� ������.
		NOTI_GM_FRIEND_UNREGISTER_LIST,
		// UIINT32		uiCharID;

		// ģ�� ��Ͽ� �߰��� ���� ������ϻ� �߰�
		NOTI_GM_FRIEND_ADD,
		// UINT32		uiCharID;
		// UINT32		uiFriendCharID;

		// ģ�� ��Ͽ��� �����Ͽ� ������ϻ󿡼� ����
		NOTI_GM_FRIEND_DELETE,
		// UINT32		uiCharID;
		// UINT32		uiFriendCharID;

	//////////////////////////////////////////////////////////////////////////////
	//
	// SubLogic
	//
		SUBLOGIC_CS_BASE = PI_CS_SYSTEM + 600,

		SUBLOGIC_SC_COMMAND = SUBLOGIC_CS_BASE,
		// UINT8		uiLen;
		// TCHAR		szCommand[];

	//////////////////////////////////////////////////////////////////////////////
	//
	// Fatigue Degree System
	//

		FDS_CS_BASE = PI_CS_SYSTEM + 700,

		FDS_SC_NOTICE = FDS_CS_BASE,
		// UINT32		uiOnlineMinutes;				// ���ӽð�
		// UINT32		uiOfflineMinutes;				// �����ӽð�
		// UINT16		usRate_Ely;				
		// UINT16		usRate_Exp;						// ���� ����� ����ġ ���� factor
		// UINT16		usRate_ItemDrop;				// ���� ����� ������ ����� ���� factor

		// ������ �ڽ��� ���ӻ��¸� Ȯ���ϴ� �뵵�� ���. FDS_SC_NOTICE ���ö��̵�
		FDS_CS_QUERYSTATE,
		// UINT32		uiReservedParam1;
		// UINT32		uiReservedParam2;


	//////////////////////////////////////////////////////////////////////////////
	//
	// Security System : Ŭ���̾�Ʈ ������ �˻�
	//

		SECURITY_CS_BASE = PI_CS_SYSTEM + 800,

		// �������� Query()�� ���ؼ� ������ ������ ������ �۽�
		SECURITY_SC_CHECK = SECURITY_CS_BASE,
		// SECURITY_PACKDATA	stPackData;				// ������ ������ ������

		// Ŭ���̾�Ʈ���� �������� �̿��ؼ� ������ ������ ����
		SECURITY_CS_CHECK,
		// SECURITY_PACKDATA	stPackData;				// ������ ������ ������

		// ������ �˻� ��� �뺸. �޼���â�� ���ؼ� Ŭ���̾�Ʈ ������� �����մϴ�.
		SECURITY_SC_INFO,
		// GLOBAL_STRING_ID		ErrorID;				// �������̵�

};

enum PACKETID_CS_TOOL
{
	//////////////////////////////////////////////////////////////////////////
	//
	//	GMLOGIN
	//
		PI_CS_GMLOGIN = PI_CS_TOOL + 0,

		// �������� �α���
		TOOL_CS_LOGIN = PI_CS_GMLOGIN,
		// char 			szID[MAX_LEN_ID_DB+1];
		// char 			szPW[MAX_LEN_PW_DB+1];
		// int				iVersion;		// GM���� ����ϴ� ������ȣ
		// UINT16			major;			// ����&Ŭ���̾�Ʈ�� ����ϴ� ������ ������
		// UINT16			minor;			// ����&Ŭ���̾�Ʈ�� ����ϴ� ������ ���̳�
		// UINT32			option;			// VERSION_OPTION ����

		// �α��ο� ���� ����
		TOOL_SC_LOGIN,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// UINT8 byPermit;					// ����
		// char	szName[LEN_NAME+1];			// �̸�

		TOOL_CS_LOGIN2,
		// UINT8			lenID;
		// TCHAR			ID[];
		// TCHAR			cMagicChar[1];	// must be MAGIC_CHAR
		// UINT8			lenPW;
		// TCHAR			PW[];
		// int				iVersion;		// GM���� ����ϴ� ������ȣ
		// UINT16			major;			// ����&Ŭ���̾�Ʈ�� ����ϴ� ������ ������
		// UINT16			minor;			// ����&Ŭ���̾�Ʈ�� ����ϴ� ������ ���̳�
		// UINT32			option;			// VERSION_OPTION ����

	//////////////////////////////////////////////////////////////////////////
	//
	//	GMNOTICE
	//
		PI_CS_GMNOTICE = PI_CS_TOOL + 100,

		// ������ ���������� �������� �۽�
		TOOL_CS_NOTICE = PI_CS_GMNOTICE,
		// UINT16 worldID;					// 0(all)
		// UINT16 serverID;					// 0(all)
		// UINT8 displayTime;				// 0(forever), sec
		// UINT8 optionFlags;				// reserved. display ȿ�� �뵵(į����,Į��,...)
		// UINT16 uiLen;
		// TCHAR szMsg[];

	//////////////////////////////////////////////////////////////////////////
	//
	//	GMWORLDLIST
	//
		PI_CS_GMWORLDLIST = PI_CS_TOOL + 200,

		// ���帮��Ʈ�� �����ɴϴ�.
		TOOL_CS_WORLDLIST = PI_CS_GMWORLDLIST,

		// ���帮��Ʈ�� �����ɴϴ�.
		TOOL_SC_WORLDLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_WORLD			stGM_World;
		// ...

	//////////////////////////////////////////////////////////////////////////
	//
	//	USERTAB
	//
		PI_CS_USERTAB = PI_CS_TOOL + 300,
	
		// -- ����� ��Ŷ
		// MServer�� �¶��������� �����մϴ�.(���������� ����� �ȵǾ� �����ִ� ��쿡 ���� ó��)
		TOOL_CS_OFFLINE = PI_CS_USERTAB,
		// UINT32 uiUserID;

		// -- ����� ��Ŷ
		// �¶������� ���� ���
		TOOL_SC_OFFLINE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

		// ���Ӽ������� ������ �߹��մϴ�.
		TOOL_CS_KICKOUT,
		// UINT32 uiUserID;

		// �����߹� ���
		TOOL_SC_KICKOUT,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// ������ ����� �����մϴ�.
		TOOL_CS_UPDATE_USER_BLOCK,
		// UINT32			uiUserID;		// �������̵�(������ ���Ű)
		// UINT8			byBlock;		// ��Ͽ���

		// ������ ����� �����մϴ�.
		TOOL_SC_UPDATE_USER_BLOCK,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// â��Ӵϸ� �����մϴ�.
		TOOL_CS_UPDATE_STORAGE_MONEY,
		// int				iWID;			// ������̵�
		// UINT32			uiUserID;		// �������̵�(������ ���Ű)
		// INT64			iStorageMoney;	// â��

		// â��Ӵϸ� �����մϴ�.
		TOOL_SC_UPDATE_STORAGE_MONEY,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

		// ������ �˻��մϴ�.
		TOOL_CS_FINDUSER,
		// UINT32 uiUserID;

		// �����˻� ���
		TOOL_SC_FINDUSER,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// UINT16 usServerID;				// �������̵�(�÷������� ������ġ)
		// UINT8 byStatus;					// ��������(IN, MOVE(�̵�����), OUT(�̵������ؼ�����))
		// UINT8 byValid;					// ���Ӽ����� ������ ���翩��(0:X, 1:����)
		// char szCharName[LEN_NAME+1];		// ä�μ������� �÷������϶� ���õ� ĳ���͸�
	
		// ĳ���ͻ���Ƚ���� �����մϴ�.
		TOOL_CS_UPDATE_CHARDELCOUNT,
		// int				iWID;			// ������̵�
		// UINT32			uiUserID;		// �������̵�(������ ���Ű)
		// UINT8			byCharDelCount;	// ĳ���ͻ���Ƚ��

		// ĳ���ͻ���Ƚ���� �����մϴ�.
		TOOL_SC_UPDATE_CHARDELCOUNT,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	PCTAB
	//
		PI_CS_PCTAB = PI_CS_TOOL + 400,
	
		// AccountName���� PC����Ʈ�� �����ɴϴ�.
		TOOL_CS_PCLISTBYACCOUNT = PI_CS_PCTAB,
		// int				iWID;			// ������̵�
		// char				szAccountName[MAX_LEN_ID_DB+1];

		// AccountName���� PC����Ʈ�� �����ɴϴ�.
		TOOL_SC_PCLISTBYACCOUNT,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// UINT32			uiUserID;		// �������̵�(������ ���Ű)
		// UINT8			byBlock;		// ���
		// INT64			iStorageMoney;	// â��
		// char				szAccountName[MAX_LEN_ID_DB+1];
		// int				iCnt;
		// GM_PC			stGM_PC;
		// ...
		// UINT8			byCharDelCount;	// ĳ���ͻ���Ƚ��
	
		// CharName���� PC����Ʈ�� �����ɴϴ�.
		TOOL_CS_PCLISTBYCHAR,
		// int				iWID;			// ������̵�
		// char				szCharName[LEN_NAME+1];

		// CharName���� PC����Ʈ�� �����ɴϴ�.
		TOOL_SC_PCLISTBYCHAR,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// UINT32			uiUserID;		// �������̵�(������ ���Ű)
		// UINT8			byBlock;		// ���
		// INT64			iStorageMoney;	// â��
		// char				szAccountName[MAX_LEN_ID_DB+1];
		// int				iCnt;
		// GM_PC			stGM_PC;
		// ...
		// UINT8			byCharDelCount;	// ĳ���ͻ���Ƚ��
	
		// PC�� ������ �����մϴ�.
		TOOL_CS_UPDATE_PC_PERMISSION,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ
		// UINT8			byPermission;	// ����

		// PC�� ������ �����մϴ�.
		TOOL_SC_UPDATE_PC_PERMISSION,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// PC�� �̸��� �����մϴ�.
		TOOL_CS_UPDATE_PC_CHARNAME,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ
		// char				szOldCharName[LEN_NAME+1];
		// char				szNewCharName[LEN_NAME+1];

		// PC�� �̸��� �����մϴ�.
		TOOL_SC_UPDATE_PC_CHARNAME,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// PC�� �������� �����մϴ�.
		TOOL_CS_UPDATE_PC,
		// int				iWID;			// ������̵�
		// GM_PC			stGM_PC;		// PC����

		// PC�� �������� �����մϴ�.
		TOOL_SC_UPDATE_PC,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// PC�� ���� �Ǵ� �����մϴ�.
		TOOL_CS_UPDATE_PC_DEL,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ
		// UINT8			byDel;			// ��������

		// PC�� ���� �Ǵ� �����մϴ�.
		TOOL_SC_UPDATE_PC_DEL,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// PC�� Ÿ��Ʋ���̵� �����մϴ�.
		TOOL_CS_UPDATE_PC_TITLEID,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ
		// int				iTitleID;		// Ÿ��Ʋ���̵�

		// PC�� Ÿ��Ʋ���̵� �����մϴ�.
		TOOL_SC_UPDATE_PC_TITLEID,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	ITEMTAB
	//
		PI_CS_ITEMTAB = PI_CS_TOOL + 500,

		// �����̳� Ÿ�Ժ� �����۸���Ʈ/Ȯ�彽���� �����ɴϴ�.
		TOOL_CS_ITEMLIST = PI_CS_ITEMTAB,
		// int				iWID;			// ������̵�
		// UINT32			uiUserID;		// �������̵�(������ ���Ű)
		// int				iCharID;		// PC�� DBŰ
		// UINT8			byContainerType;// �����̳�Ÿ��

		// �����̳� Ÿ�Ժ� �����۸���Ʈ/Ȯ�彽���� �����ɴϴ�.
		TOOL_SC_ITEMLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// UINT8			byContainerType;// �����̳�Ÿ��
		// UINT8			byExpandSlot;	// Ȯ�彽�Լ�
		// int				iCnt;
		// GM_ITEM			stGM_Item;
		// ...
	
		// Ȯ�彽���� �����մϴ�.
		TOOL_CS_UPDATE_EXPANDSLOT,
		// int				iWID;			// ������̵�
		// UINT32			uiUserID;		// �������̵�(������ ���Ű)
		// int				iCharID;		// PC�� DBŰ
		// UINT8			byContainerType;// �����̳�Ÿ��
		// UINT8			byExpandSlot;	// Ȯ�彽�Լ�

		// Ȯ�彽���� �����մϴ�.
		TOOL_SC_UPDATE_EXPANDSLOT,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// �������� �������� �����մϴ�.
		TOOL_CS_UPDATE_ITEM,
		// int				iWID;			// ������̵�
		// GM_ITEM			stGM_ITEM;		// ITEM����

		// �������� �������� �����մϴ�.
		TOOL_SC_UPDATE_ITEM,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// �������� �����մϴ�.
		TOOL_CS_CREATE_ITEM,
		// int				iWID;			// ������̵�
		// GM_ITEM			stGM_ITEM;		// ITEM����

		// �������� �����մϴ�.
		TOOL_SC_CREATE_ITEM,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// INT64			iItemNo;		// ������DBŰ
	
		// �������� �����մϴ�.
		TOOL_CS_DELETE_ITEM,
		// int				iWID;			// ������̵�
		// INT64			iItemNo;		// ������DBŰ

		// �������� �����մϴ�.
		TOOL_SC_DELETE_ITEM,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	SKILLTAB
	//
		PI_CS_SKILLTAB = PI_CS_TOOL + 600,
	
		// ��ų����Ʈ�� �����ɴϴ�.
		TOOL_CS_SKILLLIST = PI_CS_SKILLTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		// ��ų����Ʈ�� �����ɴϴ�.
		TOOL_SC_SKILLLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_SKILL			stGM_Skill;
		// ...
	
		// ��ų������ �����մϴ�.
		TOOL_CS_UPDATE_SKILL,
		// int				iWID;			// ������̵�
		// GM_SKILL			stGM_Skill;

		// ��ų������ �����մϴ�.
		TOOL_SC_UPDATE_SKILL,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// ��ų�� �����մϴ�.
		TOOL_CS_CREATE_SKILL,
		// int				iWID;			// ������̵�
		// GM_SKILL			stGM_Skill;

		// ��ų�� �����մϴ�.
		TOOL_SC_CREATE_SKILL,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// ��ų�� �����մϴ�.
		TOOL_CS_DELETE_SKILL,
		// int				iWID;			// ������̵�
		// GM_SKILL			stGM_Skill;

		// ��ų�� �����մϴ�.
		TOOL_SC_DELETE_SKILL,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	QUESTTAB
	//
		PI_CS_QUESTTAB = PI_CS_TOOL + 700,

		// ����Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_CS_QUESTLIST = PI_CS_QUESTTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		// ����Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_SC_QUESTLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_QUEST			stGM_Quest;
		// ...
	
		// ����Ʈ������ �����մϴ�.
		TOOL_CS_UPDATE_QUEST,
		// int				iWID;			// ������̵�
		// GM_QUEST			stGM_Quest;

		// ����Ʈ������ �����մϴ�.
		TOOL_SC_UPDATE_QUEST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// ����Ʈ�� �����մϴ�.
		TOOL_CS_CREATE_QUEST,
		// int				iWID;			// ������̵�
		// GM_QUEST			stGM_Quest;

		// ����Ʈ�� �����մϴ�.
		TOOL_SC_CREATE_QUEST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// ����Ʈ�� �����մϴ�.
		TOOL_CS_DELETE_QUEST,
		// int				iWID;			// ������̵�
		// GM_QUEST			stGM_Quest;

		// ����Ʈ�� �����մϴ�.
		TOOL_SC_DELETE_QUEST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	MISSIONTAB
	//
		PI_CS_MISSIONTAB = PI_CS_TOOL + 800,
	
		// �̼Ǹ���Ʈ�� �����ɴϴ�.
		TOOL_CS_MISSIONLIST = PI_CS_MISSIONTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		// �̼Ǹ���Ʈ�� �����ɴϴ�.
		TOOL_SC_MISSIONLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_MISSION		stGM_Mission;
		// ...
	
		// �̼������� �����մϴ�.
		TOOL_CS_UPDATE_MISSION,
		// int				iWID;			// ������̵�
		// GM_MISSION		stGM_Mission;

		// �̼������� �����մϴ�.
		TOOL_SC_UPDATE_MISSION,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// �̼��� �����մϴ�.
		TOOL_CS_CREATE_MISSION,
		// int				iWID;			// ������̵�
		// GM_MISSION		stGM_Mission;

		// �̼��� �����մϴ�.
		TOOL_SC_CREATE_MISSION,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
	
		// �̼��� �����մϴ�.
		TOOL_CS_DELETE_MISSION,
		// int				iWID;			// ������̵�
		// GM_MISSION		stGM_Mission;

		// �̼��� �����մϴ�.
		TOOL_SC_DELETE_MISSION,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	MAILTAB
	//
		PI_CS_MAILTAB = PI_CS_TOOL + 900,
	
		// ���ϸ���Ʈ�� �����ɴϴ�.
		TOOL_CS_MAILLIST = PI_CS_MAILTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		// ���ϸ���Ʈ�� �����ɴϴ�.
		TOOL_SC_MAILLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_MAIL			stGM_Mail;
		// ...
	
		// ������ �����մϴ�.
		TOOL_CS_DELETE_MAIL,
		// int				iWID;			// ������̵�
		// GM_MAIL			stGM_Mail;

		// ������ �����մϴ�.
		TOOL_SC_DELETE_MAIL,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

		// ������ ������Ʈ �մϴ�.
		TOOL_CS_UPDATE_MAIL,
		// int				iWID;			// ������̵�
		// GM_MAIL			stGM_Mail;

		// ������ ������Ʈ �մϴ�.
		TOOL_SC_UPDATE_MAIL,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_MAIL			stGM_Mail;
		

	//////////////////////////////////////////////////////////////////////////
	//
	//	GIFT
	//
		PI_CS_GIFTTAB = PI_CS_TOOL + 1000,
	
		// ���ϸ���Ʈ�� �����ɴϴ�.
		TOOL_CS_GIFTLIST = PI_CS_GIFTTAB,
		// int				iWID;			// ������̵�
		// char				szAccountName[LEN_ID+1];

		// ���ϸ���Ʈ�� �����ɴϴ�.
		TOOL_SC_GIFTLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_GIFT			stGM_Gift;
		// ...

	//////////////////////////////////////////////////////////////////////////
	//
	//	EFFECTTAB
	//
		PI_CS_EFFECTTAB = PI_CS_TOOL + 1100,
	
		// ����Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_CS_EFFECTLIST = PI_CS_EFFECTTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		// ����Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_SC_EFFECTLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_EFFECT		stGM_Effect;
		// ...
	
		// ����Ʈ�� �����մϴ�.
		TOOL_CS_DELETE_EFFECT,
		// int				iWID;			// ������̵�
		// GM_EFFECT		stGM_Effect;

		// ����Ʈ�� �����մϴ�.
		TOOL_SC_DELETE_EFFECT,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	TITLETAB
	//
		PI_CS_TITLETAB = PI_CS_TOOL + 1200,
	
		// Ÿ��Ʋ����Ʈ�� �����ɴϴ�.
		TOOL_CS_TITLELIST = PI_CS_TITLETAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		// Ÿ��Ʋ����Ʈ�� �����ɴϴ�.
		TOOL_SC_TITLELIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_TITLE			stGM_Title;
		// ...
		
		// Ÿ��Ʋ�� �����մϴ�.
		TOOL_CS_CREATE_TITLE,
		// int				iWID;			// ������̵�
		// GM_TITLE			stGM_Title;

		// Ÿ��Ʋ�� �����մϴ�.
		TOOL_SC_CREATE_TITLE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

		// Ÿ��Ʋ�� �����մϴ�.
		TOOL_CS_DELETE_TITLE,
		// int				iWID;			// ������̵�
		// GM_TITLE			stGM_Title;

		// Ÿ��Ʋ�� �����մϴ�.
		TOOL_SC_DELETE_TITLE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	WAYPOINTTAB
	//
		PI_CS_WAYPOINTTAB = PI_CS_TOOL + 1300,
	
		// ��������Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_CS_WAYPOINTLIST = PI_CS_WAYPOINTTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		// ��������Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_SC_WAYPOINTLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GM_WAYPOINT		stGM_WayPoint;

		//��������Ʈ ���� ���� ��û�մϴ�
		TOOL_CS_WAYPOINTSAVE,
		// int				iWID;			// ������̵�
		// GM_EVENT			stGM_WayPoint

		//��������Ʈ ���� ���� ��û�մϴ�
		TOOL_SC_WAYPOINTSAVE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GM_WAYPOINT		stGM_WayPoint;

	//////////////////////////////////////////////////////////////////////////
	//
	//	ACCOUNTTAB
	//
		PI_CS_ACCOUNTTAB = PI_CS_TOOL + 1400,
	
		// GM��������Ʈ�� �����ɴϴ�.
		TOOL_CS_ACCOUNTLIST = PI_CS_ACCOUNTTAB,

		// GM��������Ʈ�� �����ɴϴ�.
		TOOL_SC_ACCOUNTLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iCnt;
		// GM_ACCOUNT		stGM_Account;
		// ...
		
		// GM������ �����մϴ�.
		TOOL_CS_CREATE_ACCOUNT,
		// GM_ACCOUNT		stGM_Account;

		// GM������ �����մϴ�.
		TOOL_SC_CREATE_ACCOUNT,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iGMNum;			// GM������ȣ
		
		// GM������ �����մϴ�.
		TOOL_CS_UPDATE_ACCOUNT,
		// GM_ACCOUNT		stGM_Account;

		// GM������ �����մϴ�.
		TOOL_SC_UPDATE_ACCOUNT,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	GMCASHSHOP
	//
		PI_CS_GMCASHSHOP = PI_CS_TOOL + 1500,

		// ������ ���������� �������� �۽�
		TOOL_CS_CASHSHOP = PI_CS_GMCASHSHOP,
		// UINT16 worldID;					// 0(all)
		// UINT16 serverID;					// 0(all)
		// UINT8 optionFlags;				// 0: ĳ���� �ݱ� 1: ���� ���� 2: ĳ���� ���� 

		TOOL_SC_CASHSHOP	,
		// UINT16 worldID;					// 0(all)
		// UINT16 serverID;					// 0(all)
		// UINT8 optionFlags;				// 0: ĳ���� �ݱ� 1: ���� ���� 2: ĳ���� ���� 
		// UINT8 uiResult;					// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	GUILDTAB
	//
		PI_CS_GUILDTAB = PI_CS_TOOL + 1600,
	
		// ��������� �����ɴϴ�.
		TOOL_CS_GUILD = PI_CS_GUILDTAB,
		// UINT32				iWID;			// ������̵�
		// TCHAR				szCharName[MAX_LEN_NAME_DB+1];	// ĳ���͸�

		// ��������� �����ɴϴ�.
		TOOL_SC_GUILD,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�
		// GM_GUILD				stGM_Guild;		// �������

		// ��带 �����մϴ�.(������� �����մϴ�.)
		TOOL_CS_DELETE_GUILD,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ

		// ��带 �����մϴ�.(������� �����մϴ�.)
		TOOL_SC_DELETE_GUILD,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ��������� ������ �����մϴ�.
		TOOL_CS_UPDATE_GUILD_GNAME,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ
		// TCHAR				szGName[GUILD_MAX_NAME+1];	// ����

		// ��������� ������ �����մϴ�.
		TOOL_SC_UPDATE_GUILD_GNAME,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ��������� ��彽�ΰ��� �����մϴ�.
		TOOL_CS_UPDATE_GUILD_GSLOGAN,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ
		// TCHAR				szGSlogan[GUILD_MAX_SLOGAN+1];	// ��彽�ΰ�

		// ��������� ��彽�ΰ��� �����մϴ�.
		TOOL_SC_UPDATE_GUILD_GSLOGAN,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ��������� ������̵� �����մϴ�.
		TOOL_CS_UPDATE_GUILD_CROPID,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ
		// UINT32				iCropID;		// ������̵�

		// ��������� ������̵� �����մϴ�.
		TOOL_SC_UPDATE_GUILD_CROPID,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ��������� ������Ϸ���� �����ð��� �����մϴ�.
		TOOL_CS_UPDATE_GUILD_REMAINTIME,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ
		// UINT32				iRemainTime;	// ������Ϸ���� �����ð�

		// ��������� ������Ϸ���� �����ð��� �����մϴ�.
		TOOL_SC_UPDATE_GUILD_REMAINTIME,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ��������� ������ ���ð��� �����մϴ�.
		TOOL_CS_UPDATE_GUILD_NOURISHTIME,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ
		// UINT32				iNourishTime;	// ������ ���ð�

		// ��������� ������ ���ð��� �����մϴ�.
		TOOL_SC_UPDATE_GUILD_NOURISHTIME,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

		// ��������� ��������� ���۽ð��� �����մϴ�.
		TOOL_CS_UPDATE_GUILD_NOURISHSTARTTIME,
		// UINT32				iWID;				// ������̵�
		// UINT32				iGNum;				// ����� DBŰ
		// TIMESTAMP_STRUCT		stNourishStartTime;	// ��������� ���۽ð�

		// ��������� ��������� ���۽ð��� �����մϴ�.
		TOOL_SC_UPDATE_GUILD_NOURISHSTARTTIME,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

		// ��������� ������ �������ð��� �����մϴ�.
		TOOL_CS_UPDATE_GUILD_HASTENSUMTIME,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ
		// UINT32				iHastenSumTime;	// ������ �������ð�

		// ��������� ������ �������ð��� �����մϴ�.
		TOOL_SC_UPDATE_GUILD_HASTENSUMTIME,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ��������� �δ������ ���̺�Ʈ���̵� �����մϴ�.
		TOOL_CS_UPDATE_GUILD_INDUNEVENTID,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ
		// UINT32				iIndunEventID;	// �δ������ ���̺�Ʈ���̵�

		// ��������� �δ������ ���̺�Ʈ���̵� �����մϴ�.
		TOOL_SC_UPDATE_GUILD_INDUNEVENTID,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�


		// ���������Ʈ�� �����ɴϴ�.
		TOOL_CS_GUILDMEMBERLIST,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ

		// ���������Ʈ�� �����ɴϴ�.
		TOOL_SC_GUILDMEMBERLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// UINT32				iCnt;
		// GM_GUILDMEMBER		stGM_GuildMember;
		// ...

		// ������� �����մϴ�.
		TOOL_CS_DELETE_GUILDMEMBER,
		// UINT32				iWID;			// ������̵�
		// UINT32				iCharID;		// PC�� DBŰ

		// ������� �����մϴ�.
		TOOL_SC_DELETE_GUILDMEMBER,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ����������� ������ �����մϴ�.
		TOOL_CS_UPDATE_GUILDMEMBER_GRADE,
		// UINT32				iWID;			// ������̵�
		// UINT32				iCharID;		// PC�� DBŰ
		// UINT8				byGrade;		// ����

		// ����������� ������ �����մϴ�.
		TOOL_SC_UPDATE_GUILDMEMBER_GRADE,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// ���Ÿ���� �����մϴ�
		TOOL_CS_UPDATE_GUILD_GTYPE,
		// UINT32				iWID;			// ������̵�
		// UINT32				iGNum;			// ����� DBŰ

		// ���Ÿ���� �����մϴ�
		TOOL_SC_UPDATE_GUILD_GTYPE,
		// GLOBAL_STRING_ID		uiErrorID;		// �����ڵ�

		// Guild End-Mark
		PI_CS_GUILDTAB_END,


	//////////////////////////////////////////////////////////////////////////
	//
	//	LDT2DB TAB
	//
		TOOL_CS_LDT2DB_BASE = PI_CS_TOOL + 1700,

		TOOL_CS_LDT2DB_SELECT = TOOL_CS_LDT2DB_BASE,
		// UINT32				uiTableType;				// 1(MapInfo),2(GiftInfo),3(ItemInfo)
		TOOL_SC_LDT2DB_SELECT,
		// GLOBAL_STRING_ID		uiErrorID;					// �����ڵ�
		// UINT32				uiTableType;			
		// UINT32				uiLen;
		// TCHAR				szData[];

		// MapInfo (DELETE)
		TOOL_CS_LDT2DB_DELETE,
		// UINT32				uiTableType;			
		TOOL_SC_LDT2DB_DELETE,
		// GLOBAL_STRING_ID		uiErrorID;		
		// UINT32				uiTableType;			

		// MapInfo (UPDATE)
		TOOL_CS_LDT2DB_UPDATE,
		// UINT32				uiTableType;			
		// UINT32				uiLen;
		// TCHAR				szData[];
		TOOL_SC_LDT2DB_UPDATE,
		// GLOBAL_STRING_ID		uiErrorID;		
		// UINT32				uiTableType;			

		// LDT2DB End-Mark
		TOOL_CS_LDT2DB_END,

	//////////////////////////////////////////////////////////////////////////
	//
	//	ABILITYTAB
	//
		PI_CS_ABILITYTAB = PI_CS_TOOL + 1800,

		//���������� �����ɴϴ�
		TOOL_CS_MIXINFO = PI_CS_ABILITYTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		//���������� �����ɴϴ�
		TOOL_SC_MIXINFO,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iProfessionLv_1;//���շ���
		// int				iProfessionExp_1;//���հ���ġ

		//���������� �����մϴ�
		TOOL_CS_MIXINFO_UPDATE,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ	
		// int				iCurMixLv;		// ����� ���շ���
		// int				iCurMixExp;		// ����� ���հ���ġ

		//���������� �����մϴ�
		TOOL_SC_MIXINFO_UPDATE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

		//PVP ������ �����ɴϴ�
		TOOL_CS_PVPINFO,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		//PVP ������ �����ɴϴ�
		TOOL_SC_PVPINFO,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// int				iPVPLv;			// PVP����
		// int				iPVPGlory;		// PVP����ġ
		// int				iPVPPoint;		// PVP����Ʈ

		//PVP ������ �����մϴ�
		TOOL_CS_PVPINFO_UPDATE,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ
		// int				iPVPLv;			// PVP����
		// int				iPVPGlory;		// PVP����ġ
		// int				iPVPPoint;		// PVP����Ʈ

		//PVP ������ �����մϴ�
		TOOL_SC_PVPINFO_UPDATE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�

	//////////////////////////////////////////////////////////////////////////
	//
	//	EVENTTAB
	//
		PI_CS_EVENTTAB = PI_CS_TOOL + 1900,

		//�����̺�Ʈ ����Ʈ�� �����ɴϴ�
		TOOL_CS_EVENTLIST = PI_CS_EVENTTAB,
		// int				iWID;			// ������̵�
		// int				iCharID;		// PC�� DBŰ

		//�����̺�Ʈ ����Ʈ�� �����ɴϴ�
		TOOL_SC_EVENTLIST,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GM_EVENT		stGM_Event;

		//�����̺�Ʈ üũ ���θ� �����մϴ�
		TOOL_CS_EVENTCHECK,
		// int				iWID;			// ������̵�
		// GM_EVENT		stGM_Event;

		//�����̺�Ʈ üũ ���θ� �����մϴ�
		TOOL_SC_EVENTCHECK,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GM_EVENT		stGM_Event;

	//////////////////////////////////////////////////////////////////////////
	//
	//	GLOBALEVENTTAB
	//
		PI_CS_GLOBALEVENTTAB = PI_CS_TOOL + 2000,

		// ����� �����̺�Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_CS_GLOBALEVENT_RESERVELIST = PI_CS_GLOBALEVENTTAB,

		// ����� �����̺�Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_SC_GLOBALEVENT_RESERVELIST,
		// INT32			iCnt;
		// GLOBALEVENT		stGlobalEvent;
		// ...

		// ����� �����̺�Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_CS_GLOBALEVENT_APPLYLIST,

		// ����� �����̺�Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_SC_GLOBALEVENT_APPLYLIST,
		// INT32			iCnt;
		// GLOBALEVENT		stGlobalEvent;
		// ...

		// ���Ӽ����� ���� ����� �����̺�Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_CS_GLOBALEVENT_REALLIST,

		// ���Ӽ����� ���� ����� �����̺�Ʈ����Ʈ�� �����ɴϴ�.
		TOOL_SC_GLOBALEVENT_REALLIST,
		// UINT16			wWorldID;
		// UINT16			wServerID;
		// INT32			iCnt;
		// GLOBALEVENT		stGlobalEvent;
		// ...

		// �������� �����̺�Ʈ�� �����մϴ�.
		TOOL_CS_GLOBALEVENT_RESERVE,
		// GLOBALEVENT		stGlobalEvent;

		// �������� �����̺�Ʈ�� �����մϴ�.
		TOOL_SC_GLOBALEVENT_RESERVE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GLOBALEVENT		stGlobalEvent;

		// ����� �����̺�Ʈ�� �����մϴ�.
		TOOL_CS_GLOBALEVENT_DELETE_RESERVE,
		// GLOBALEVENT		stGlobalEvent;

		// ����� �����̺�Ʈ�� �����մϴ�.
		TOOL_SC_GLOBALEVENT_DELETE_RESERVE,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GLOBALEVENT		stGlobalEvent;

		// ����� �����̺�Ʈ�� �����մϴ�.
		TOOL_CS_GLOBALEVENT_DELETE_APPLY,
		// GLOBALEVENT		stGlobalEvent;

		// ����� �����̺�Ʈ�� �����մϴ�.
		TOOL_SC_GLOBALEVENT_DELETE_APPLY,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GLOBALEVENT		stGlobalEvent;

		// ���Ӽ����� ���� ����� �����̺�Ʈ�� �����մϴ�.
		TOOL_CS_GLOBALEVENT_DELETE_REAL,
		// GLOBALEVENT		stGlobalEvent;

		// ���Ӽ����� ���� ����� �����̺�Ʈ�� �����մϴ�.
		TOOL_SC_GLOBALEVENT_DELETE_REAL,
		// GLOBAL_STRING_ID	uiErrorID;		// �����ڵ�
		// GLOBALEVENT		stGlobalEvent;

};

enum PACKETID_CS_LOGIC
{
	//////////////////////////////////////////////////////////////////////////////
	//
	// Auth
	//
		PI_CS_AUTH = PI_CS_LOGIC + 0,

		AUTH_CS_LOGIN = PI_CS_AUTH,
		// NOT SUPPORTED !!! (Don't use it)

		AUTH_SC_LOGIN ,
		// RESULTCODE		resultCode;
		// USERID			uid;
		// PASSPORT			passport;
		// UINT16			uiServerID;
		// TCHAR			ID[MAX_LEN_ID];			// included NULL

		// for FDS (Shanda)
			// UINT32		uiAdditionalParam1;
			// UINT32		uiAdditionalParam2;

		AUTH_CS_LOGOUT ,
		//                        RID			uid;
		// PASSPORT			passport;

		AUTH_SC_LOGOUT ,
		// RESULTCODE		resultCode;

		AUTH_CS_LOGIN_WITH_VERSION ,
		// NOT SUPPORTED !!! (Don't use it)


		// keylogin + Version Check
		AUTH_CS_KEYLOGIN,
		// UINT8			lenKeyID;
		// TCHAR			KEYID[];				// include NULL
		// UINT8			lenStartTime;
		// TCHAR			StartTTime[];			// include NULL
		// UINT16			major;					// Build #
		// UINT16			minor;
		// UINT32			option;					// VERSION_OPTION ����

		// UINT8			uiCount;
			// UINT32			uiVersion_1;		// uiCount ������ŭ �ݺ�
			// UINT8			uiFileNameLen_1;
			// TCHAR			szFileName_1[];


		AUTH_CS_LOGIN_WITH_VERSION2 ,
		// NOT SUPPORTED !!! (Don't use it)


		// �α�(����Ȯ��) : SITE_SANDA,SITE_BUDDYBUDDY
		AUTH_CS_LOGIN_EX,
		// UINT32			option;					// VERSION_OPTION ����
		// UINT16			major;					// Build #
		// UINT16			minor;
		// UINT8			lenParam1;
		// TCHAR			szParam1[];
		// UINT8			lenParam2;	
		// TCHAR			szParam2[];

		/*
				SITE_ACTOZ
					param1 : ID
					param2 : PW
				SITE_GAMEPOT
					param1 : ID
					param2 : PW
				SITE_SANDA
					param1 : ID
					param2 : PW
				SITE_BUDDYBUDDY
					param1 : ID
					param2 : AUTHCODE[144]
		 */

		// UINT8			uiCount;
			// UINT32			uiVersion_1;		// uiCount ������ŭ �ݺ�
			// UINT8			uiFileNameLen_1;
			// TCHAR			szFileName_1[];

		 AUTH_SC_EKEY,
		 // UINT8			mode;					// 1(EKEY_REQUEST),2(EKEY_ERROR),3(EKEY_SN_REQUEST)
		 // int				errorValue;

		 //if mode == EKEY_REQUEST
			// UINT8		EKeyType;				// 1(6,old ekey with challenge),2(8,old ekey without challenge),3(8,new ekey with challenge)
			// UINT8		lenChallenge;			// include NULL
			// TCHAR		szChallenge[];			

		 AUTH_CS_EKEY,
		 // UINT8			lenChallenge;
		 // TCHAR			szChallenge[];			// include NULL
		 // UINT8			lenEKey;	
		 // TCHAR			szEKey[];				// include NULL

		 // Ekey machine's SN : ������ 6�ڸ�
		 AUTH_CS_EKEY_SN,
		 // TCHAR			szEKeySN[7];				// include NULL

		 // AUTH_CS_LOGIN_EX�� ���� ��� 
		 AUTH_SC_LOGIN_EX ,
		 // GLOBAL_STRING_ID	itemID;	

		 // if itemID == 0
			// USERID				uid;
			// PASSPORT				passport;
			// UINT16				uiServerID;
			// UINT8				lenID;
			// TCHAR				szID[];

	//////////////////////////////////////////////////////////////////////////////
	//
	// World/Channel Selection (WorldServer)
	//
		PI_CS_WORLD = PI_CS_LOGIC + 100,

		// ���� ��� ��û
		WORLD_CS_GETLIST = PI_CS_WORLD,
		// USERID		userID;

		WORLD_SC_GETLIST ,
		//UINT8			numOfWorlds;
		//WORLD_INFO	worldInfos[];

		// ���� ���ð���� ������ ����, �ش� ���峻�� ä�� ���� ����(WORLD_SC_CHANNELSTATUS)�ϰ� ��
		WORLD_CS_SELECT ,
		//WORLD_ID		worldID;

		WORLD_SC_SELECT ,
		// RESULTCODE		resultCode;			

		// ���õ� ������ ä�� ���� ���� ��û
		WORLD_CS_CHANNELSTATUS ,
		//WORLD_ID			worldID;

		// �α�/�κ�â���� ��û�� ���
		WORLD_SC_CHANNELSTATUS ,
		// UINT8			numOfChannels;
		// CHANNEL_INFO		chInfo[];

		// zone���� ä�� ������ ���� ������, ä�� ��� ��û�� ���
		WORLD_SC_CHANNELSTATUS2 ,
		// UINT8			numOfChannels;
		// CHANNEL_INFO		chInfo[];
		// SERVER_ID		curChannelID;

		// ä�� ���� ����� ������ ����
		CHANNEL_CS_SELECT ,
		// WORLD_ID			worldID;
		// SERVER_ID		channelID;
		// USERID			uid;
		// PASSPORT			passport;

		CHANNEL_SC_SELECT ,
		// RESULTCODE		resultCode;
		// TCHAR			ip[LEN_IP];
		// UINT16			port;

		// Ư�� ������ ����
		WORLD_CS_ENTER ,
		// USERID			uid;
		// PASSPORT			passport;
		// WORLD_ID			worldID;
		// TCHAR			charName[LEN_NAME];
		// TCHAR			szID[LEN_ID];
		// UINT32			uiIndunID; // �δ������� ���� �δ��ν��Ͻ����̵�, ���Ӽ����� ���� �δ�LDT���̵�

		WORLD_SC_ENTER ,
		// RESULTCODE		resultCode;

		// ���ӿ��� ������
		WORLD_CS_LEAVE ,
		// USERID			uid;
		// PASSPORT			passport;

		WORLD_SC_LEAVE ,
		// RESULTCODE		resultCode;
		
		GAME_CS_START ,
		
		// ���� ����!!!
		GAME_SC_START ,				
		// RESULTCODE		resultCode;
		
		// �� �������� ä�� ���� �۾��� ����. ���� ������ �� �������� SaveDB ����
		GAME_CS_CHANGE_CHANNEL ,
		// WORLD_ID			worldID;
		// SERVER_ID		channelID;

		// saveDB ��� ����. Ŭ���̾�Ʈ�� disconnect�ϰ� ������ ä�η� connection
		GAME_SC_CHANGE_CHANNEL ,
		// GLOBAL_STRING_ID	itemID;				// itemID = 0 or 4000006 or LT_ERROR_SYSTEMERROR(= 6)
		// if(itemID == 0)
			// TCHAR			ip[LEN_IP];
			// UINT16			port;
			// USERID			userID;
			// PASSPORT			passport2;		// DestServer���� ���� ������ passport


		// Channel in and out
		//
		// ä�λ���(���� �÷��� ����)���� ����/���� 
		//{
			// GS���� ���� : LBS --> GS
			CHANNEL_CS_IN,
			// UINT32	uiUserID;
			// UINT32	uiReservedParam;
			CHANNEL_SC_IN,
			// GLOBAL_STRING_ID	itemID;			

			// GS������ ���� : GS --> LS [,kickout,disconnect,serverdown]
			CHANNEL_CS_OUT,
			// UINT32	uiUserID;
			// UINT32	uiReservedParam;
			CHANNEL_SC_OUT,
			// GLOBAL_STRING_ID	itemID;		

		//}

	//////////////////////////////////////////////////////////////////////////////
	//
	// Character Management (WorldServer)
	//
		PI_CS_CHAR = PI_CS_LOGIC + 200,

		// ĳ���� �����۾��� ����ϵ� ĳ���͸� ����
		CHAR_CS_DELETE_CHARNAME = PI_CS_CHAR,
		// TCHAR			charName[LEN_NAME];

		CHAR_SC_DELETE_CHARNAME ,
		// RESULTCODE		resultCode;

		// ĳ���� ����������, ĳ���� �̸� �ߺ� �˻�
		CHAR_CS_CHECK_CHARNAME ,
		// WORLD_ID			worldID;
		// TCHAR			szID[LEN_ID];
		// TCHAR			szNewCharName[LEN_NAME];

		CHAR_SC_CHECK_CHARNAME ,
		// RESULTCODE		resultCode;					// LT_NO_ERROR(��밡��), LT_ERROR_FAILED(ĳ���͸� �ߺ�)

		// ���� �ش� ������ ĳ���� ����� ��û�Ѵ�.
		CHAR_CS_GETLIST ,
		// USERID			userID;
		// WORLD_ID			worldID;
		// TCHAR			szID[LEN_ID];

		CHAR_SC_GETLIST ,
		// RESULTCODE		resultCode;
		// UINT8			numOfChars;

		// for(numOfChars)
			// CHARACTER_INFO2	charInfo[];
			// UINT16			numOfItems
			// CONTAINER_ITEM	itemInfo[];
			// UINT8			byNewbi;		// ĳ���� ������ ���� ���� ����

		// �ش� ���峻�� ���ο� ĳ���͸� �ϳ� �����Ѵ�.
		CHAR_CS_CREATE ,
		// WORLD_ID			worldID;
		// CHARACTER_INFO	charInfo;
		// CHAR_FIGURE		charFigure;

		CHAR_SC_CREATE ,
		// RESULTCODE		resultCode;
		// CHARID			charID;

		// �ش� ĳ���͸� �����Ѵ�.
		CHAR_CS_DELETE ,
		// WORLD_ID			worldID;
		// USERID			userID;
		// CHARID			charID;
		// TCHAR			szCharName[LEN_NAME+1];

		CHAR_SC_DELETE ,
		// GLOBAL_STRING_ID	iErrorMsg;		// �����ڵ�

		// Ư�� ĳ���͸� �����ϰ� ���� ����.
		CHAR_CS_SELECT ,
		// USERID			userID;
		// CHARID			charID;
		// SERVER_ID		channelID;		// ������ ä��ID

		CHAR_SC_SELECT ,	// ���� ����
		// RESULTCODE			resultCode;
		// CHARACTER_INFO		charInfo;
		// LT_POSITION			posInfo;
		// STATUS_INFO			statusInfo;
		// MAP_INFO				mapInfo;
		// ITEMMIX_INFO			ItemMixInfo;
		// PVP_STAT				PvPInfo;
		// CHARACTER_CASH_INFO charCashInfo; //mijin 20080306 ĳ���߰�

		// Ư�� ĳ������ ���� ���
		CHAR_CS_CHARINFO,
		// CHARID			charID;				// for PC/NPC/MOB

		CHAR_SC_CHARINFO ,
		// RESULTCODE		resultCode;
		// GU_ID			globalID;
		// CHARACTER_INFO2	charInfo2;

		// Ư�� ĳ���� ��ġ���� ���
		CHAR_CS_POSINFO ,
		// CHARID			charID;				// for PC/NPC/MOB

		CHAR_SC_POSINFO ,
		// RESULTCODE		resultCode;
		// MAP_INFO			mapInfo;
		// LT_POSITION		posInfo;

		// Ư�� ĳ���� ���� ���� ���
		CHAR_CS_STATUSINFO ,       // ��� �ȵǰ� ���� ����������
		// CHARID			charID;				

		CHAR_SC_STATUSINFO ,		// ��� �ȵǰ� ���� ����������
		// GU_ID		globalID;
		// STATUS_INFO	statusInfo;

		CHAR_CS_ACTION ,
		// ACTIONID			actionID;

		CHAR_SC_ACTION ,
		// CHARID			charID;
		// ACTIONID			actionID:

		CHAR_CS_SET_QUICK_SLOT ,
		// UINT8			iNumOfQuickSlot;
		// QUICK_SLOT*iNumOfLevelUpChange;

		CHAR_SC_QUICK_SLOT	,
		// GU_ID			globalID
		// UINT8			iNumOfQuickSlot;
		// QUICK_SLOT*iNumOfLevelUpChange;
	
		// Ư�� ĳ���� �̵����� Status ���� ���
		CHAR_CS_MOVING_STATUS_INFO ,

		CHAR_SC_MOVING_STATUS_INFO ,
		// GU_ID			globalID
		// MOVING_STAUS		MovingStatusInfo;

		// ĳ������ �𷺼� ���� ��û.
		CHAR_CS_FACING				,
		// UINT8			facing

		// ĳ������ �𷺼� ���� ����.
		CHAR_SC_FACING				,
		// GU_ID			globalID
		// FACING			facing

		// ĳ������ �����̳� ����.
		CHAR_SC_CONTAINER_INFOS		,
		// GU_ID			globalID		//
		// INT8				iNumOfInfo		// ����� ������Ʈ ����
		// CONTAINER_TYPE	ContainerType	// �����̳� Ÿ��.		(����� ������Ʈ)
		// INT8				TotalSlot		// �Ѱ��� (=  �⺻ + OptionSlotTot )
		// INT8				OptionSlotTot	// �ɼ� ������ �Ѱ���.(����� ������Ʈ)

		// ĳ������ �����̳� ����.
		CHAR_CS_CONTAINER_INFOS		,

		CHAR_SC_EFFECT_STATUS_INFO ,
		// GU_ID				globalID		
		// EFFECT_STATUS_INFO	StatusInfo;

		// �ǻ�Ƴ��� ��û
		CHAR_CS_REVIVAL,
		// SAVEPOINT_TYPE			iSavePointType; 
		// ITEM_NO					iTrashItemNo;
		// TRASH_ITEM				TrashItem;

		// ������ ���� ���õ� �����
		CHAR_SC_ITEMMIX_INFO,
		// GU_ID				globalID;
		// ITEMMIX_INFO			stItemMixInfo;

		// ĳ���� Ŭ��������
		CHAR_CS_CHANGE_CLASS ,
		// int				iChangeClassID ;	// CLASS_CHANGE.ldt::_Item_ID
		// TRASH_ITEM		stTrashItem;		// �Ҹ������

		// ĳ���� Ŭ�������� ���
		CHAR_SC_CHANGE_CLASS ,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;		// �������̵�,  0 �ΰ�츸 ���� �����ͼ۽�
		// UINT8			NewClassType;
		// __int64			iCurrEly;		// �� 
		// short			iSkillFreePoint;// SKILL_SC_INIT�� ������ �̺�Ʈ ó�����
		// UINT8			iNumOfLevelUpChange;
		// STATUS_CHANGE    tStatPack[];	// �ٲ� �ɷ�ġ 	
		// STATUS_INFO		statInfo ;
		// UINT8			iNumOfItem;		// ���������� �ؼ� �����Ǵ� ������
		// CONTAINER_ITEM	aryContainerItem[];
		// TRASH_ITEM		stTrashItem;

		// PVP �ǻ�Ƴ��� ��û
		CHAR_CS_PVP_REVIVAL,

		//	 ��ҵ�GM״̬
		CHAR_SC_GM_STATUS,
		//	INT  byIsGM;			0Ϊ��GM ������0ΪGM

	//////////////////////////////////////////////////////////////////////////////
	//
	// Status (LevelUp,Exp,hp,sp,...) 
	//
	PI_CS_STAT = PI_CS_LOGIC + 300,

		// ����� status ���� ����
		STAT_SC_CHANGE = PI_CS_STAT,
		// GU_ID			globalID; 
		// UINT8			numOfStatus;
		// STATUS_CHANGE	statusChanges[];

		STAT_SC_CHANGE_EX ,
		// GU_ID			globalID;
		// UINT8			numOfStatus;
		// STATUS_CHANGE_EX	statusChanges[];

		STAT_SC_LEVEL_UP ,
#ifdef __CHANGE_CLASS
		//GU_ID		globalID			
		//UINT16	iLevel;
		//__int64   BaseExp	
		//__int64   NextExp
		//UINT8		iNumOfLevelUpChange;
		//STATUS_CHANGE tStatPack[]
#else
		//GU_ID   globalID			
		//__int64 BaseExp	
		//__int64 NextExp
		//UINT8 iNumOfLevelUpChange;
		//STATUS_CHANGE tStatPack[]
#endif

	//////////////////////////////////////////////////////////////////////////////
	//
	// Game Options : ���� �������� �α�� DBLoad �ǰ�, �α׾ƿ��� DBSave��
	//
		PI_CS_GAME_OPTION = PI_CS_LOGIC + 400,

		// PC�� ���� �ɼ� ��û. *** ���� ������� �ʽ��ϴ�. CHARACTER_INFO2 ����ü�� ���ԵǾ ���Ӽ��� ���Խÿ� �λ���Ʈ/�ƿ�����Ʈ�� Ŭ���̾�Ʈ�� �۽��մϴ�.
		GAME_CS_GETOPTION = PI_CS_GAME_OPTION,
		GAME_SC_GETOPTION ,
		// GLOBAL_STRING_ID	ErrorID;
		// UINT16			uiGameOption;		// �ͼӸ�,ģ���߰�,�ŷ���û,����û,���¾˸�			

		// PC�� ���� �ɼ� ����
		GAME_CS_SETOPTION ,
		// INT32			iGameOptions;
		GAME_SC_SETOPTION ,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;
		// INT32			iGameOptions;

	//////////////////////////////////////////////////////////////////////////////
	//
	// Action Command (MOVE/STOP/ATTACK/SKILL,...)
	//
		PI_CS_ACTION_COMMAND = PI_CS_LOGIC + 500,

		ACTION_CS_COMMAND = PI_CS_ACTION_COMMAND,
		// unsigned __int64	commandBuf;
		// unsigned int		sequenceIndex;

		ACTION_SC_COMMAND ,
		// RESULTCODE		resultCode;
		// GU_ID			globalID;			// classID(CLASS_ID_AVATAR(PC) | CLASS_ID_MONSTER(MOB)) + instanceID
		// unsigned __int64	commandBuf;
		// unsigned int		seqIndex
		// LT_POSITION		pos;

		ACTION_SC_KNOCKBACK,
		// RESULTCODE		resultCode;
		// GU_ID			globalID;
		// LT_KNOCKBACK		knockBackInfo;

	//////////////////////////////////////////////////////////////////////////////
	//
	// Battle (GameServer)
	//
		PI_CS_BATTLE = PI_CS_LOGIC + 600,

		BATTLE_SC_ATTACKED = PI_CS_BATTLE,
		// RESULTCODE		resultCode;
		// GU_ID			globalID;	// �ǰ���
		// int				iDamage;		// damage value
		// int				iMode		// 0:�Ϲ� 1:ũ�� 2: �̽� 3: Immune
		// int				iType		// EFFECT.LDT::_StatusEffectType
		// GU_ID			AttackerGlobalID;	// ������
		// uint8			iHitCount			// Combo HitCount

		BATTLE_SC_HEALING,
		// RESULTCODE		resultCode;
		// GU_ID			globalID;
		// int				iHeal;		// damage value
		// int				iMode		// 0:�Ϲ� 1:ũ�� 2: �̽� 3: Immune
		// int				iType		// EFFECT.LDT::_StatusEffectType

	//////////////////////////////////////////////////////////////////////////////
	//
	// Navigation	(GameServer)
	//
		PI_CS_NAV = PI_CS_LOGIC + 700,

		// Ư�� ĳ���Ͱ� �þ߿� ���Դ�.
		NAV_SC_INSIGHT = PI_CS_NAV,

		//�⺻����
		//packet << pChar->GetGUID();
		//packet.PushBack(&charInfo2,sizeof(CHARACTER_INFO2));

		//Action
		//packet << pChar->GetCurAction();
		//packet << uiSeqIndex;
		//packet.PushBack(&posInfo,sizeof(LT_POSITION));

		//Item
		//packet.PushBack((UINT16)iNumOfFigureItem);
		//sizeof(FIGURE_ITEM) * iNumOfFigureItem;

		//Effect
		//packet.PushBack((UINT16)iNumOfEffect);
		//sizeof(EFFECT_DATA) * iNumOfEffect;

		// ���λ����������� �����϶��� �������� �����ϴ�.
		// char				szFMName[FM_MAX_NAME+1]; // ������

		// �������
		// packet.PushBack(&stGuildBroadCast, sizeof(GUILD_BROADCAST));

		// PC �ΰ��
		//UINT8		iGloryLv;

		// ��ȭ�� ������Ʈ �� ���.. 2008.04.14 Hoony
		// GU_ID					ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// BG_ID					Layer;
		// UINT						iPosX;						//
		// UINT						iPosY;						//
		// CHATROOM_OBJECT_INFO		stChatRoomObject_Info		//

		// Ư�� ĳ���Ͱ� �þ߿��� �����.
		NAV_SC_OUTOFSIGHT ,
		// GU_ID			globalID;			// classID + instanceID


		//	��������ͻ��˷��ͽ�����Ұ�������guid
		NAV_SC_INSIGHT_GUID,
		//  UINT8 uCount;
		//  UINT32 insight_ID[];

		//	�ͻ��˸��ݷ������˷��͵Ľ�����Ұ������guid������ȡ������Ϣ
		NAV_CS_INSIGHT_GUID,
		//	UINT8 uCount;
		//	UINT32 insight_ID[];

	//////////////////////////////////////////////////////////////////////////////
	//
	// Event : NPC, SavePoint, Portal	(GameServer)
	//
		PI_CS_EVENT = PI_CS_LOGIC + 800,

		EVENT_CS_RAISE = PI_CS_EVENT,
		//UINT8		eventType;					// NPC(1),SavePoint(2),Portal(3)
		//UINT32	uiEventID;					// NPCID,SavePointID,PortalID
		
		EVENT_SC_RAISE ,
		// RESULTCODE		resultCode;
		// UINT8			EventType;			// NPC(1),SavePoint(2),Portal(3)
		// UINT32			uiEventID;
		// MAP_INFO			mapInfo;			// for Portal		 (���� ä�γ��� ���ѵ�)
		// float			posX;				// for Portal	
		// float			posY;				// for Portal	

		// EVENT_SC_RAISE -> Client -> Client:;LoadStage() �Ϸ���, ������ ���۵�.
		NAV_CS_ENTERSTAGE ,

	//////////////////////////////////////////////////////////////////////////
	//
	// Item 
	//
		PI_CS_ITEM = PI_CS_LOGIC + 900,

		// �����̳� ������ ���� ������ ������ ���� ����
		ITEM_SC_CONTAINER_INFO  = PI_CS_ITEM,	
		// GU_ID				globalID;
		// CONTAINER_ITEM		containerItem;

		// �����̳� ������ ���� ������ ������ ���� ����
		ITEM_SC_CONTAINER_INFOS  ,
		// GU_ID				globalID;
		// UINT16				nItems;
		// CONTAINER_ITEM		containerItem;

		// ������ �ݱ� �̵� ��û
		ITEM_CS_LOOTING ,
		// GU_ID				iLootingBagID;
		// LOOTING_ITEM			stLooting_Item;

		// ������ �ݱ� ����. (�ش� �� �κ��� ������ Ŭ���� ���ش�.)
		ITEM_SC_LOOTING , // ��ε� ĳ���õ� �ؾ���.			
		// GU_ID				globalID;
		// GLOBAL_STRING_ID		ErrorID;		// �������̵�
		// GU_ID				ActCharGUID;	// �������� ������ PC�� GUID
		// LOOTING_ITEM			stLooting_Item;	// Ŭ���̾�Ʈ ������ ���Ǽ��� ���Ͽ� ������������ �ѹ� �� �־��ݴϴ�. <-- �޼�����
		// UINT8				byRare;			// �޼����� ����ǥ�ø� ���ؼ� ����� �߰��մϴ�.
		// LOOTING_ITEM			stLooting_Item;

		// �����̳ʳ������� ������ ��ġ �̵� ��û.
		ITEM_CS_CHANGE_SLOT ,	
		// CHANGE_SLOT			changeSlot;

		// �����̳ʳ������� ������ ��ġ �̵� ��û.
		ITEM_SC_CHANGE_SLOT ,	
		// GU_ID				globalID;
		// CHANGE_SLOT			changeSlot;

		// ������ ������ ��û.
		ITEM_CS_TRASH ,
		//TRASH_ITEM			trashItem;

		// ������ �ı� ���� ( �ش� �κ��� ������ Ŭ���� ����)
		ITEM_SC_TRASH ,			
		// GU_ID				globalID;
		// UINT8				iNumOfTrashItem;
		// TRASH_ITEM			trashItem*iNumOfTrashItem;

		// ������ ������ ���� �޼���. 
		ITEM_SC_ALARM , // ��� ����
		//// GU_ID				globalID;
		//// EXCEPTION_CODE		exceptionCode;

		// ������ ���
		ITEM_CS_USING ,
		// GU_ID				Ÿ�� ��ƼƼ ���̵�
		// CONTAINER_SLOT		��ġ����
	
		// ��� ����. Ŭ��Ʈ���� �ش� ������ ����.
		ITEM_SC_USING ,
		// GU_ID				globalID	; // Ÿ�� ��ƼƼ ���̵�
		// GLOBAL_STRING_ID		iError		; // 0 : ����
		// TRASH_ITEM			UsingItem	; // ��� �� ������ ��ġ ����

		// �ܺο� ������ �ϴ� �����۵��� ��ε� ĳ���� ����
		ITEM_SC_FIGURE_INFOS  ,	// ��������
		ITEM_SC_FIGURE_ON,				// ���� 
		ITEM_SC_FIGURE_OFF,				// ���� ����(���� �ʿ�)
		
		ITEM_CS_TOGGLE_USE_WEAPON_SET,  // ���� swap ��û.
		ITEM_SC_TOGGLE_USE_WEAPON_SET,	// ���� swap ����.
		//GU_ID				globalID	;
		//RESULT_CODE iError 
		//UINT8 uiActiveSet);

		ITEM_SC_LOOTING_LIST,           // ���� ������ ������ ����. 
		// GU_ID					// Looting bag GlobalID
		// GU_ID					// Looting bag Owner
		// POSITION					// Looting bag Position
		// iNumOfItem(UINT8)				// Items In Bag
		//    iSlot	 (UINT8)					 
		//    ITEM	 			
		
		ITEM_CS_CONTAINER_INFOS ,
		// GU_ID				globalID;
		// UINT16				nItems;
		// CONTAINER_ITEM		containerItem;

		// ���º����.
		ITEM_CS_FIGURE_INFOS_FOR_SINGLE,
		// GU_ID			iGlobalID				// Target������ GU_ID 
		// INT8				iNumOfCONTAINER_TYPE	// ������� �����̳ʹ�ȣ�� ����.						//
		// CONTAINER_TYPE	iContainerType[] 		// �����̳� Ÿ��.
			
		// �ٸ� ������ ������ ��������
		ITEM_SC_FIGURE_INFOS_FOR_SINGLE,
		// GU_ID			iGUID					// ������ GU_ID
		// GU_ID			iTargetGUID				// Ÿ�������� GU_ID
		// UINT16			iNumOfContainerItem		// �����̳� ������ ����		
		// CONTAINER_ITEM	iContainerItems[]		// Ÿ�������� �����̳� ������.

		// �ű� ���ο� �ν��Ͻ� �������� ����� ����.
		ITEM_CS_DIVIDE,
		// CHANGE_SLOT		changeSlot				// �ش� �������� ��ġ �� ��������/

		ITEM_SC_DIVIDE,
		// GU_ID			iGUID					// ������ GU_ID
		// GLOBAL_STRING_ID	iResultError			// 0: ���� 0���� ũ�� ����.
		// TRASH_ITEM		TrashITem				// �ҽ��� ī���� �谨 ����.
		// CONTAINER_ITEM	NewItem					// ���� ������ �ν��Ͻ� �����̳� ������.

		ITEM_CS_ENCHANT,
		// int				iEnchantID;				// ITEM_ENCHANT.LDT::PrimaryKey
		//----------------------------------------------------------
		// CONTAINER_TYPE	iMainContainerType;			// ����
		// UINT8			iMainContainerSlot;			// ����
		// ITEMNO			iMainItemNo;				// ����

		// CONTAINER_TYPE	iMaterialContainerType;		// ��� ������ ��ġ  
		// UINT8			iMaterialContainerSlot;		// ��� ������ ��ġ
		// ITEMNO			iMaterialItemNo;			// ��� ������ ��ȣ
		// UINT8			iMaterialItemCount;			// ��� ������ �䱸����.  -- ������
		//-------------------------------------------------------------

		ITEM_SC_ENCHANT,
		// GU_ID			iGUID;					// ������ GU_ID
		// UINT8			iEnchanted;				// 0: ��þƮ ���� �ǻ� 1: ��þƮ
		// GLOBAL_STRING_ID	iResultError;			// iEnchanted�� 1 �ΰ�� 0: ���� 0���� ũ�� ��.  iEnchanted�� 0�� ��� �̰��� ������ 0���� ū������ �;���.
													// ������ �������ſ��� ���� (ITEM_SC_CONTAINER_INFOS/ITEM_SC_TRASH) ���� ��Ŷ���� ����.
		// int				iEnchantID;	


		ITEM_CS_UPGRADE,
		// int				iUpgradeID;				// ITEM_ENCHANT.LDT::PrimaryKey
		//----------------------------------------------------------
		// CONTAINER_TYPE	iMainContainerType;			// ����
		// UINT8			iMainContainerSlot;			// ����
		// ITEMNO			iMainItemNo;				// ����
		//----------------------------------------------------------------
		// unsigned INT8	iNumOfMaterial; // �ִ� 4
		// MATERIAL_DATA	MaterialData[iNumOfMaterial]; // iNumOfMaterial ��ŭ �ٿ��ּ���	
		//-------------------------------------------------------------
		// ITEMNO			iResultItemID;				// ��� ������			-- ������
		// 

		ITEM_SC_UPGRADE,
		// GU_ID			iGUID;					/// ������ GU_ID
		// UIN8				iUpgraded;				/// 0: ���׷��̵� ���� �ǻ� 1: ���׷��̵�
		// GLOBAL_STRING_ID	iResultError;			/// iUpgraded�� 1 �ΰ�� 0: ���� 0���� ũ�� ��.  iUpgraded�� 0�� ��� �̰��� ������ 0���� ū������ �;���./ 0: ���� 0���� ũ�� ����.  // ������ �������ſ��� ���� (ITEM_SC_CONTAINER_INFOS/ITEM_SC_TRASH) ���� ��Ŷ���� ����.
		// int				iUpgradeID;						// ������ �������ſ��� ���� (ITEM_SC_CONTAINER_INFOS/ITEM_SC_TRASH) ���� ��Ŷ���� ����.

		ITEM_CS_DESTROY_BY_TIME ,
		// ITEMNO			iItemNo;				
		// CONTAINER_SLOT	ContainerInfo;

		ITEM_SC_DESTROY_BY_TIME ,
		//GU_ID					iGUID;	
		//TRASH_ITEM			trashItem;

		ITEM_CS_BASIC_FIGURE_CHANGE,
		// int					iBeautyShopID;		// BEAUTY_SHOP.LDT::ItemID #
		// UINT8				iBasicFigureSlot;	//FIGURE_BASIC_TYPE �� �ϳ� 
		// CONTAINER_SLOT		UsingItemPos1;  // ����������������ġ
		// ITEMNO				iUsingItemNo1;  // ��������������Ű
		// CONTAINER_SLOT		UsingItemPos2;  // ����������������ġ
		// ITEMNO				iUsingItemNo2;  // ��������������Ű

		ITEM_SC_BASIC_FIGURE_CHANGE,  // �ֺ��ε鿡�Դ� ITEM_SC_FIGURE_ON 
		//GU_ID					iGUID;
		//GLOBAL_STRING_ID		iResultError;	
		//int					iBeautyShopID;	// ����
		//TRASH_ITEM			UsingItemPos1;	// ����������������ġ
		//ITEMNO				iUsingItemNo1;	// ��������������Ű
		//TRASH_ITEM			UsingItemPos2;	// ����������������ġ
		//ITEMNO				iUsingItemNo2;	// ��������������Ű
		//CONTAINER_ITEM		NewCharItem;	// ������ ����

		ITEM_SC_EXPIRE,
		//GU_ID					iGUID;	
		//CONTAINER_SLOT		stItemPos;

		ITEM_CS_ADDTIME,
		// int				iItemAddTimeID;				// ITEM_ADD_TIME.LDT::PrimaryKey
		//----------------------------------------------------------
		// CONTAINER_TYPE	iMainContainerType;			// ����
		// UINT8			iMainContainerSlot;			// ����
		// ITEMNO			iMainItemNo;				// ����

		// CONTAINER_TYPE	iMaterialContainerType;		// ��� ������ ��ġ  
		// UINT8			iMaterialContainerSlot;		// ��� ������ ��ġ
		// ITEMNO			iMaterialItemNo;			// ��� ������ ��ȣ
		// UINT8			iMaterialItemCount;			// ��� ������ �䱸����.  -- ������
		//-------------------------------------------------------------

		ITEM_SC_ADDTIME,
		// GU_ID			iGUID;					// ������ GU_ID
		// int				iItemAddTimeID;	
		// GLOBAL_STRING_ID	iResultError;			// 0: ���� 0���� ũ�� ��. ������ �������ſ��� ���� (ITEM_SC_TRASH) ���� ��Ŷ���� ����.
		// ITEM_LIFETIME	stItemLifeTime;			// �����ÿ��� ��ȿ�� ����� ������Ÿ������

		ITEM_SC_ITEMEXP,
		//GU_ID					iGUID;	
		//ITEM_EXP				stItemExp;

		ITEM_CS_ADDSP,
		// CONTAINER_SLOT		stMainItemPos;
		// ITEMNO				iMainItemNo;
		// CONTAINER_SLOT		stMaterialItemPos;
		// ITEMNO				iMaterialItemNo;

		ITEM_SC_ADDSP,
		//GU_ID					iGUID;	
		//GLOBAL_STRING_ID		ErrorID;
		//ITEM_SP				stItemSP;

		ITEM_CS_CHAT,
		// CONTAINER_SLOT		UsingItemPos;		// ����� ������ ��ġ����
		// ITEMNO				iUsingItemNo;		// ����� ������ Ű��ȣ
		// BROADCAST_SCOPE		scope;				// ��ε�ĳ���� ����
		// UINT8				len;				// �޼��� ����
		// TCHAR				szMsg[];	

		// ��� ����. Ŭ��Ʈ���� �ش� ������ ����. // ����ä���� CHAT_CS_MSG �� ����
		ITEM_SC_CHAT,
		// GU_ID				globalID	; // ����� ���̵�
		// GLOBAL_STRING_ID		iError		; // 0 : ����
		// TRASH_ITEM			UsingItem	; // ��� �� ������ ��ġ ����
		
		// ����
		ITEM_CS_MIX,
		// int				iMixID;				// ITEM_CREATE_RECIPE.LDT::PrimaryKey
		//----------------------------------------------------------------
		// UINT8			iNumOfMaterial; // �ִ� 5
		// MATERIAL_DATA	MaterialData[iNumOfMaterial]; // iNumOfMaterial ��ŭ �ٿ��ּ���	

		// ���հ��
		ITEM_SC_MIX,
		// GU_ID			iGUID;					/// ������ GU_ID
		// GLOBAL_STRING_ID	iResultError;			/// 0: ���� 0���� ũ�� ����. 
		// UIN8				iMixed;					/// 0: Ȯ������ 1: Ȯ������
		// int				iMixID;
		// ITEMMIX_INFO		stItemMixInfo;			// ĳ������ ��������
		// UINT8			iNumOfMeterial;
		// TRASH_ITEM		stMeterial[];
		// CONTAINER_ITEM	stResult;				// ���������

		//	ʹ�õ������ [2008-07-17]
		MONEY_CS_CHAT,
		//	CONTAINER_SLOT		UsingItemPos;		// ����� ������ ��ġ����
		//	ITEMNO				iUsingItemNo;		// ����� ������ Ű��ȣ
		//	BROADCAST_SCOPE		scope;				//	�㲥�ķ�Χ
		//	ITEMID				iItemID;			//	��Ӧ����Ʒ��ID
		//  UINT8				len;				//  ��Ϣ����
		//  TCHAR				szMsg[];			//	��Ϣ������

		//	�Ƿ�ɹ�	[2008-07-17]
		MONEY_SC_CHAT,	
		// GU_ID				globalID	; ��ҵ�GUID
		// GLOBAL_STRING_ID		iError		; ��Ӧ����Ϣ��ID
		// TRASH_ITEM			UsingItem	; // ��� �� ������ ��ġ ����
		
		ITEM_CS_EFFECTUPGRADE,
		// int				iUpgradeID;					// 
		// CONTAINER_TYPE	iMainContainerType;			// 
		// UINT8			iMainContainerSlot;			// 
		// ITEMNO			iMainItemNo;				// 
		// MATERIAL_DATA	MaterialData;				//
		// ITEMNO			iResultItemID;				//

		ITEM_SC_EFFECTUPGRADE,
		// GU_ID			iGUID;					//
		// UIN8				iUpgraded;				//
		// GLOBAL_STRING_ID	iResultError;			//
		// int				iUpgradeID;				//

		///add by chenhao 08.8.29
		ITEM_CS_WHERE,
		// GU_ID				Ÿ�� ��ƼƼ ���̵�
		// CONTAINER_SLOT		��ġ����
		// INT32	SvrSeq
		// UINT32	Seq
		// TCHAR	szTargetCharName[LEN_NAME+1];

		ITEM_SC_WHERE,
		// GLOBAL_STRING_ID		iError;					// ����ID
		// INT32			SvrSeq
		// UINT32			Seq
		// UINT8			bFlag;						// ����Ƿ����ߣ�1Ϊ���ߣ�0Ϊ������
		// TCHAR			szCharName[LEN_NAME+1];
		// TCHAR			szTargetCharName[LEN_NAME+1];
		// UINT16			ServerID;
		// UINT				uiStageID;					// �����������̵�
		// UINT				uiMapGroupID;				// �ʱ׷���̵�
		// UINT				uiPosX;						// X��ǥ
		// UINT				uiPosY;						// Y��ǥ

		ITEM_SC_WHERE_COMMAMD_INFOS,
		// int nWhereItemCount;
		// WHERE_ITEMINFO stInfo[11];
		///add by chenhao 08.9.2

		ITEM_CS_MSGBOARD,
		// GU_ID
		// CONTAINER_SLOT
		// INT				iPosX;
		// INT				iPosY;
		// UINT				uiType;						//  ��Ϣ������
		// UINT8			len;						//  ��Ϣ����
		// TCHAR			szMsg[];					//	��Ϣ������

		ITEM_SC_MSGBOARD,
		// GLOBAL_STRING_ID		iError;					// ����ID

		ITEM_CS_DEL_MSGBOARD,
		// GU_ID										//����id
		// CONTAINER_SLOT
		// GU_ID										//��Ϣ��id

		ITEM_SC_DEL_MSGBOARD,
		// GLOBAL_STRING_ID		iError;					// ����ID
		
		ITEM_CS_TRACK,									//���棬ץ�˵���
		// GU_ID
		// CONTAINER_SLOT
		// TCHAR			szTargetCharName[LEN_NAME+1];

		ITEM_SC_TRACK,
		// GU_ID
		// GLOBAL_STRING_ID		iError;					// ����ID


	//////////////////////////////////////////////////////////////////////////
	//
	//	NPC
	// 
		PI_CS_NPC = PI_CS_LOGIC + 1000,

		// NPC���� �ȱ�. PC -> NPC
		NPC_SHOP_CS_SELL = PI_CS_NPC, 
		// int				iNpcID 
		// int				iShopID
		// CONTAINTER_ITEM tContainerItem;

		// NPC���� ���.	NPC -> PC
		NPC_SHOP_CS_BUY,  
		// int			iNpcID;			 // �������Լ� ����ΰ�
		// int			iShopID;		 // Shop ID 
		// UINT8		iSlotIndex;      // ���ĭ�� �ִ� �������� ����ΰ�.
		// ITEM			tItem;			 // ITEMID / COUNT  � �������� � ����ΰ�.
	
		// 2005.11.03 dhpark NPC���� ��� ���. �������� ������ �߰��մϴ�.
		NPC_SHOP_SC_BUY,  
		// GU_ID			ObjectGUID;	// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;	// �������̵�(0�̸� ��������)

		// ���� ����
		CUTIN_CS_OPEN,
		// int				iNpcID;		// NPC

		// ���� ����
		CUTIN_SC_OPEN,
		// GU_ID			ObjectGUID;	// ���ӿ�����Ʈ���̵�

		// ���� �ݱ�
		CUTIN_CS_CLOSE,
		// int				iNpcID;		// NPC

		// ���� �ݱ�
		CUTIN_SC_CLOSE,
		// GU_ID			ObjectGUID;	// ���ӿ�����Ʈ���̵�

		// Npc PORTAL
		NPC_CS_PORTAL,
		// int            iNpcID;			// ���ǽ�
		// int			  iPortalGroupID;	// ��Ż �׷��� Key ID NPCPORTAL.LDT::_ItemID
		// int			  iPotalIndex;		// ��ġ����
		// int			  iPortalInfoID;    // PORTAL_DETAIL.LDT::_ItemID
		// CONTAINER_SLOT stUsingItemPos;	// �Ҹ������
		// ITEMNO		  iUsingItemNo;		// �Ҹ������ No
		// int			  iUsingEly;		// �Ҹ�

		NPC_SC_PORTAL,
		// GU_ID			iPCGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID iErrorID;		// ���� 0 
		// UINT64			iCurrEly;       // ���� ��Ż�� EVENT_SC_RAISE
		// TRASH_ITEM		stUsingItem;

		// NPC ���� �ý��� ��û
		NPC_CS_REWARD,
		// int            iNpcID;			// ���ǽ�
		// int			  iRewardGroupID;		  
		// UINT8		  iRewardIndex;		// ���� �� ��� �����ϰ����ǹ̾���
		// UINT8		  iNumOfUsingItem;
		// TRASH_ITEM	  stReqItem;		// �Ҹ������
		// ITEMNO	      iReqItemNo;		// �Ҹ������ No
		// int			  iUsingEly;		// �Ҹ�
		// int			  iUsingPVPPoint;	// �Ҹ�	PVP Point mijin 20071129

		// NPC ���� �ý��� ���
		NPC_SC_REWARD,
		// GU_ID			iPCGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID iErrorID;		// ���� 0 
		// UINT64			iCurrEly;       //
		// UINT8			iNumOfReqItem;
		// TRASH_ITEM		stReqItem;
		// UINT8			iNumOfRewardItem;
		// CONTAINER_ITEM	stItem;
		// int				iCurrPVPPoint;	// Current PVP Point mijin 20071129

	//////////////////////////////////////////////////////////////////////////
	//
	//	STORAGE
	// 
		PI_CS_STORAGE = PI_CS_LOGIC + 1100,

		// â�� ���ӸӴ� �����ϱ�
		STORAGE_CS_INMONEY = PI_CS_STORAGE,
		// UINT64			uiMoney;		// �����Ϸ��� �ݾ�

		// â�� ���ӸӴ� �����ϱ�
		STORAGE_SC_INMONEY,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// UINT64			uiMoney;		// ������ �ƹ�Ÿ�� ������ �ִ� �ݾ�
		// UINT64			uiStorageMoney;	// ������ â�� ����� �ݾ�

		// â���� ���ӸӴ� ��������
		STORAGE_CS_OUTMONEY,
		// UINT64			uiMoney;		// ���������ϴ� �ݾ�

		// â���� ���ӸӴ� ��������
		STORAGE_SC_OUTMONEY,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// UINT64			uiMoney;		// ������ �ƹ�Ÿ�� ������ �ִ� �ݾ�
		// UINT64			uiStorageMoney;	// ������ â�� ����� �ݾ�

	//////////////////////////////////////////////////////////////////////////////
	//
	// Chatting : �ִ� MAX_CHATMSG_LEN ������ �޼����� ����
	//
		PI_CS_CHAT = PI_CS_LOGIC + 1200,

		// ä�ø޼���
		CHAT_CS_MSG	= PI_CS_CHAT,
		// BROADCAST_SCOPE	scope;					// ��ε�ĳ���� ����
		// UINT32			destination;			// ���(partyID,channelID,worldID). if ������ ���۽�, HIWORD(worldID),LOWORD(serverID)
		// UINT8			len;					// �޼��� ����
		// TCHAR			szMsg[];				// �޼���
		// UINT8			nReceiverName;				// SCOPE_WHISPER�϶��� ����
		// TCHAR			szReceiverName[LEN_NAME];	// SCOPE_WHISPER�϶��� ����, ���� ĳ��������

		//	GLOBAL_STRING_ID ��: �ӼӸ� ���� ������ ������ system Message�� �ݼ� : 000���� ã�� �� �����ϴ�.
		CHAT_SC_MSG ,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// BROADCAST_SCOPE	scope;				// ��ε�ĳ���� ����
		// UINT8			uiFontColor;		// ��Ʈ��	: 0(default),1(Red),2(Orange),3(Yellow),4(white) : CHAT_COLOR.LDT::ItemID
		// UINT8			uiOptions;			// reserved for FontSize,FontType
		// UINT8			len;
		// TCHAR			szMsg[];		
		// GU_ID			guidSender;			// �۽��� ����
		// UINT8			nSenderName;
		// TCHAR			szSender[];			

		// ������ ����(SCOPE_WHISPER only)
		//{
			// GU_ID			guidReceiver;
			// UINT8			nReceiverName;			
			// TCHAR			szReceiver[];
		//}

		// (SCOPE_WORLD ONLY)
		// UINT16			ChannelID;			// ä�� ID	(Cash-Item�� ���� ���� ��ġ��� ä�� ���� ǥ�ÿ�)

		// (SCOPE_TEAM ONLY)
		// INT32			iSenderCharID;		// ��ä���� ���� ĳ����DBŰ(��ǳ���� �����ֱ� ���ؼ� �߰�)

		CHAT_SC_MSG_MONEY,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// BROADCAST_SCOPE	scope;				// ��ε�ĳ���� ����
		// UINT8			uiFontColor;		// ��Ʈ��	: 0(default),1(Red),2(Orange),3(Yellow),4(white) : CHAT_COLOR.LDT::ItemID
		// UINT8			uiOptions;			// reserved for FontSize,FontType
		// ITEMID			useitemID
		// UINT8			len;
		// TCHAR			szMsg[];		
		// GU_ID			guidSender;			// �۽��� ����
		// UINT8			nSenderName;
		// TCHAR			szSender[];
		// UINT16			ChannelID;			// ä�� ID	(Cash-Item�� ���� ���� ��ġ��� ä�� ���� ǥ�ÿ�)

		CHAT_SC_MSG_PCINFO,		
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// BROADCAST_SCOPE	scope;				// ��ε�ĳ���� ����
		// UINT8			uiFontColor;		// ��Ʈ��	: 0(default),1(Red),2(Orange),3(Yellow),4(white) : CHAT_COLOR.LDT::ItemID
		// UINT8			uiOptions;			// reserved for FontSize,FontType
		// ITEMID			useitemID			// ���ʹ�õ���Ʒ
		// CHARACTER_INFO2  info;				//	��ҵ�AVATA��Ϣ
		// UINT				uItemCount;			//	�����г�����Ʒ������
		// FIGURE_ITEM      tFigureItemList[MAX_FIGURE_SIZE + MAX_EQUIP_SIZE + MAX_FASHION_SIZE] ; //��ҵ�Avatar��Ϣ
		// UINT8			len;
		// TCHAR			szMsg[];

	//////////////////////////////////////////////////////////////////////////////
	// Notice
	//
		PI_CS_NOTICE = PI_CS_LOGIC + 1300,

		// ���� �޼��� ���. �����ٿ�,��ü ����....
		MSG_CS_NOTICE = PI_CS_NOTICE,
		// UINT8			displayTime;		// 0(forever), sec
		// UINT8			optionFlags;		// reserved. display ȿ�� �뵵(į����,Į��,...)
		// UINT16			len;
		// TCHAR			szMsg[];

		MSG_SC_NOTICE ,
		// RESULTCODE		resultCode;
		// UINT8			displayTime;		// 0(forever), sec
		// UINT8			optionFlags;		// reserved. display ȿ�� �뵵(į����,Į��,...)
		// UINT16			len;
		// TCHAR			szMsg[];

	//////////////////////////////////////////////////////////////////////////
	//
	// Trade
	//
		PI_CS_TRADE = PI_CS_LOGIC + 1400,

		// �ŷ���û
		TRADE_CS_REQUEST = PI_CS_TRADE,
		// GU_ID			DstCharGUID;				// �ŷ������

		// �ŷ���û ���
		TRADE_SC_REQUEST,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			SrcCharGUID;				// �ŷ���û��
		// char				szSrcCharName[LEN_NAME+1];	// �ŷ���û���̸�
		// GU_ID			DstCharGUID;				// �ŷ������
		// char				szDstCharName[LEN_NAME+1];	// �ŷ�������̸�
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

		// �ŷ�������� ��������
		TRADE_CS_RESPONSE,
		// UINT8			bAccept;					// ����/����

		TRADE_SC_RESPONSE,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			SrcCharGUID;				// �ŷ���û��
		// char				szSrcCharName[LEN_NAME+1];	// �ŷ���û���̸�
		// GU_ID			DstCharGUID;				// �ŷ������
		// char				szDstCharName[LEN_NAME+1];	// �ŷ�������̸�
		// UINT8			byAccept;					// ����/����
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

		// ���� �ŷ�â�� �ø���.
		TRADE_CS_PUSHMONEY,
		// UINT64	uiMoney;							// �ø� ���ӸӴ�
		// int		iCash;								// 20080312 mijin �ø� ĳ��
		// int		iMile;								// 20080312 mijin �ø� ���ϸ���
		// int		iCashComm;							// 20080312 mijin ĳ�� ������
		// int		iMileComm;							// 20080312 mijin ���ϸ��� ������


		// ���� �ø� PC�� �����ݾװ� ���Ͽ� �����̸� �� �ƹ�Ÿ���� ��� �۽��Ѵ�.
		TRADE_SC_PUSHMONEY,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			ActCharGUID;				// ���� �ø� �ƹ�Ÿ�� Ű
		// UINT64			uiMoney;					// �ø� ��
		// int				iCash;						// 20080312 mijin �ø� ĳ��
		// int				iMile;						// 20080312 mijin �ø� ���ϸ���
		// int				iCashComm;					// 20080312 mijin ĳ�� ������
		// int				iMileComm;					// 20080312 mijin ���ϸ��� ������


		// �������� �ŷ�â�� �ø���.
		TRADE_CS_PUSHITEM,
		// TRADE_ITEM		stTradeItem;				// �������� �ø� ������ �����̳�,����,Ʈ���̵彽�� ������ ����ִ� ����ü

		// �ŷ�������, �������� �ŷ������Ѱ���, �ش� ������ �������� �̹� �ִ��� ����� �˻����� �����̸� ������ ���и� �����α�
		TRADE_SC_PUSHITEM,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			ActCharGUID;				// �������� �ø� �ƹ�ŸŰ
		// TRADE_ITEM		stTradeItem;				// �������� �ø� ������ �����̳�,����,Ʈ���̵彽�� ������ ����ִ� ����ü
		// ITEM				stItem;						// �����ۿ� ���� �������� �����༭ ���콺�� �����ۿ� ��ġ��Ű�� ������ �����ټ��ֵ�����

		// �������� �ŷ�â���� ������. Accept���¸� ������. 
		TRADE_CS_POPITEM,
		// SLOT_INDEX		TradeSlotIndex;				// �ŷ������� �ε���

		// ������ �˻����� �����̸� ������ ���и� �����α�
		TRADE_SC_POPITEM,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			ActCharGUID;				// �������� ���� �ƹ�ŸŰ
		// SLOT_INDEX		TradeSlotIndex;				// �ŷ������� �ε���

		// ������ �̹� accept�� ���¸� �ŷ��Ϸ�, �ƴϸ� accept����
		TRADE_CS_ACCEPT,

		// ������ ���¸� �˻��Ͽ� accept���·� �����ϰų� �ŷ��ϷḦ �մϴ�.
		TRADE_SC_ACCEPT,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			ActCharGUID;				// accept�� ���� �ƹ�ŸŰ
		// UINT8			byFinish;					// �ŷ��ϷῩ��
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
		// GU_ID			ErrCharGUID;				// ���������� �ƹ�ŸŰ

		// �ŷ��� ����մϴ�.
		TRADE_CS_CANCEL,

		// �ŷ���Ҹ� ��PC���� �۽��մϴ�. �ŷ������ڿ��� �ŷ�������Ʈ ����
		TRADE_SC_CANCEL,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			ActCharGUID;				// �ŷ��� ����� �ƹ�ŸŰ

		// ������ �̹� WAIT�� ���¸� �ŷ����Ϸ����, �ƴϸ� WAIT����
		TRADE_CS_WAIT,

		// ������ ���¸� �˻��Ͽ� WAIT���·� �����ϰų� �ŷ����Ϸ���� ��ȯ�մϴ�.
		TRADE_SC_WAIT,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GU_ID			ActCharGUID;				// WAIT�� ���� �ƹ�ŸŰ
		// UINT8			byAllWait;					// �ŷ����ϷῩ��

	//////////////////////////////////////////////////////////////////////////
	//
	// Mission 
	//
		PI_CS_MISSION = PI_CS_LOGIC + 1500,

		// �̼� ����Ʈ
		MISSION_SC_LIST = PI_CS_MISSION,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// int				iCnt;			// �̼� ����
		// MISSION			stMission;		// �̼� ����
		// MISSION			stMission;		// �̼� ����
		// MISSION			stMission;		// �̼� ����
		// ...								// �̼� ������ŭ

		// �̼� ����
		MISSION_SC_UPDATE,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// MISSION			stMission;		// �̼� ����

		// �׼����̼� ����
		MISSION_CS_ACTION,
		// UINT32			uiActionID;		// �׼Ǿ��̵�

		// �׼����̼� �������
		MISSION_SC_ACTION,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// UINT32			uiActionID;		// �׼Ǿ��̵�

	//////////////////////////////////////////////////////////////////////////
	//
	// Quest 
	//
		PI_CS_QUEST = PI_CS_LOGIC + 1600,

		// ����Ʈ ����Ʈ
		QUEST_SC_LIST =  PI_CS_QUEST,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// int				iCnt;			// ����Ʈ ����
		// QUEST			stQuest;		// ����Ʈ ����
		// QUEST			stQuest;		// ����Ʈ ����
		// QUEST			stQuest;		// ����Ʈ ����
		// ...								// ����Ʈ ������ŭ
			
		// ����Ʈ ����. 2007.09.19 dhpark ����Ʈ�������������� ���� ��Ŷ��������.
		QUEST_CS_ACCEPT,
		// UINT8			byAcceptType;	// ����Ʈ ���� Ÿ��(1:NPC, 2:����, 4:������, 8:�̺�Ʈ)
		// INT32			iValue;			// Ÿ�Կ� ���� �˻����̵�(NPC���̵�, ������ ĳ����DBŰ, ���)
		// UINT32			uiQuestID;		// ����Ʈ���̵�

		// ����Ʈ ����. 2007.10.01 dhpark Ŭ���̾�Ʈ�� ������� ������ ���Ͽ� ����Ÿ�Լ۽�
		QUEST_SC_ACCEPT,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�
		// QUEST			stQuest;		// ����Ʈ ����
		// UINT8			byAcceptType;	// ����Ʈ ���� Ÿ��(1:NPC, 2:����, 4:������, 8:�̺�Ʈ)

		// ����Ʈ ����
		QUEST_CS_CANCEL,
		// UINT32			uiQuestID;		// ����Ʈ���̵�
			
		// ����Ʈ ����
		QUEST_SC_CANCEL,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// UINT32			uiQuestID;		// ����Ʈ���̵�

		// ����Ʈ �Ϸ�
		QUEST_CS_FINISH,
		// int				iNpcID;			// NPC���̵�
		// UINT32			uiQuestID;		// ����Ʈ���̵�
		// UINT8			byRank;			// 0, 1, 2
		// UINT8			byReward;		// �������϶� ������ ������ �����ε���(0, 1, 2)
			
		// ����Ʈ ����
		QUEST_SC_FINISH,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�
		// QUEST			stQuest;		// ����Ʈ ����

		// ����Ʈ ����
		QUEST_CS_SHARE,
		// UINT32			uiQuestID;		// ����Ʈ���̵�
			
		// ����Ʈ ����(������ ĳ���Ϳ�)
		QUEST_SC_SHARE,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�
		// char				szRcvCharName[LEN_NAME+1];	// �����޴� ĳ���͸�
			
		// ����Ʈ ����(�����޴� ĳ���Ϳ�)
		QUEST_SC_SHARE_RECV,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// UINT32			uiQuestID;		// ����Ʈ���̵�
		// INT32			iActCharID;		// ������ ĳ����DBŰ(QUEST_CS_ACCEPT�� ������ ����ؾ��մϴ�.)

	//////////////////////////////////////////////////////////////////////////
	//
	//	Ŀ�´�Ƽ : ģ�� ���, ���� ���, ...
	//
		PI_CS_COMMUNITY = PI_CS_LOGIC + 1700,

		// ģ�� ���
		FRIEND_CS_GETLIST = PI_CS_COMMUNITY,
		FRIEND_SC_GETLIST,
		// UINT8			nCount;
		// FRIEND_INFO		friendInfo[];
		// UINT8			uiRefreshPeriodSec;		// 0(disable)

		// ģ�� �߰� ��û
		FRIEND_CS_ADD,
		// UINT8			len;
		// TCHAR			szCharName[];

		// ģ�� �߰� ��û ���
		FRIEND_SC_ADD, 
		// GLOBAL_STRING_ID	itemID;					// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// UINT8			len;
		// TCHAR			szAccepter[];

		// ģ�� ����
		FRIEND_CS_DELETE,
		// UINT8			len;
		// TCHAR			szCharName[];
		FRIEND_SC_DELETE,
		// GLOBAL_STRING_ID	itemID;					// GLOBAL_STRING.LDT ���� �޼����� itemID ��

		// �ش� ĳ������ ����(ON/OFF LINE,Level) ���� ��û
		FRIEND_CS_REFRESH_STATUS,
		// UINT8			nCount;
		// TCHAR			charNames[][LEN_NAME];
		FRIEND_SC_REFRESH_STATUS,
		// UINT8			uiRefreshPeriodSec;		// 1<= uiNextRequestSec<=255.  // 0(disable)
		// UINT8			nCount;
		// FRIEND_INFO		friendInfo[];

		// ���� ���
		BLOCK_CS_GETLIST,
		BLOCK_SC_GETLIST,
		// UINT8			nCount;
		// TCHAR			szCharName[][LEN_NAME];

		//���� ��Ͽ� �߰�
		BLOCK_CS_ADD,
		// UINT8			len;
		// TCHAR			szCharName[];
		BLOCK_SC_ADD,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// UINT8			len;
		// TCHAR			szCharName[];

		// ���� ��Ͽ��� ����
		BLOCK_CS_DELETE,
		// UINT8			len;
		// TCHAR			szCharName[];
		BLOCK_SC_DELETE,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��

		// ���(szTargetName)�� ���� ��ϻ� ���� ��ϵǾ��°�?
		BLOCK_CS_ISBLOCKED,
		// UINT8			len;
		// TCHAR			szTargetName[];
		BLOCK_SC_ISBLOCKED,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// GU_ID			guid;				// ��û�� ������� GU_ID
		// bool				bWedding;			// ��ȥ������ ������ �ؿ� ������ ���� ������
		// UINT8			iWeddingLv;			// ��ȥ����
		// int				iWeddingDay;		// �����ϼ� �Ǵ� ��ȥ�ϼ�
		// TCHAR			szWeddingPartName[LEN_NAME+1]; //��ȥ�����̸�

		// �����ڿ��� ģ���߰� ��û�� ��������
		FRIEND_SC_ADD_RECV,
		// GLOBAL_STRING_ID iErrorMsg;
		// USERID			iRequesterUserID;
		// CHARID			iRequesterCharID;
		// UINT8			iLen;
		// TCHAR			szRequesterName[];
	
		// 
		FRIEND_CS_ACCEPT,
		// UINT8			iFlag;				// 0: ��� 1: �ź� 2: ����
		// USERID			iRequesterUserID;
		// CHARID			iRequesterCharID;
		// UINT8			iLen;
		// TCHAR			szRequesterName[];

		FRIEND_SC_ACCEPT,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// FRIEND_INFO		friendInfo;			// 

		// �ش� ĳ������ ����(ON/OFF LINE,Level) ���� ��û
		FRIEND_CS_REFRESH_STATUS2,
		// UINT8			nCount;
		// UINT32			uiFriendCharIDs[];

	//////////////////////////////////////////////////////////////////////////
	//
	//	SKILL
	//
		PI_CS_SKILL = PI_CS_LOGIC + 1800,

		// ������ ������ ��ų ����.
		SKILL_SC_INFOS = PI_CS_SKILL, 
		// GU_ID			iInstanceID
		// unsigned short	iNumOfSkill
		// sizeof(CHAR_SKILL)*iNumOfSkill

		// ��ų����Ʈ�� ȯ���ϰ� �ʱ�ȭ.
		SKILL_SC_INIT, 
		// GU_ID			iInstanceID
		// short			iSkillFreePoint;	

		// ��ų ���.
		SKILL_CS_USING, 
		// int iSkillID // ��ų ���̵�.
		// UINT8 facing

		// ��ų ��� ���.
		SKILL_SC_USING,
		// RESULTCODE		resultCode;
		// GU_ID			iInstanceID;
		// UINT32			iSkillID;
		// LT_POSITION		pos;

		// �����۽�ų ���.
		ITEMSKILL_CS_USING, 
		// CONTAINER_SLOT	stItemPos;	// ����������
		// int				iSkillID;	// ��ų ���̵�.
		// UINT8			facing;

		// �����۽�ų ��� ���.
		ITEMSKILL_SC_USING,
		// GU_ID			iInstanceID;
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�(0�̸� ��������)
		// ITEM_SP			stItemSP;		// ���������� / ���ſ� SP����
		// int				iSkillID;
		// LT_POSITION		stPCPos;

		// ��ų�� ��������Ʈ�� ����Ͽ� �������� �Ѵ�.
		SKILL_CS_LVUP,
		// int iSkillID // ��ų ���̵�.

		SKILL_SC_LVUP,
		// RESULTCODE		resultCode;
		// GU_ID			iInstanceID;
		// short			iSkillFreePoint;
		// if(0 == resultCode)
			// CHAR_SKILL		SkillData;

		// ��۽�ų����, ����� EFFECT_SC_DEL�� �����ϴ�.
		SKILL_CS_OFFTOGGLE, 
		// int iSkillID // ��ų ���̵�.

		// �����۽�ų�� �̿��� �������Ǹ�. ����� STAT_SC_CHANGE_EX, ITEM_SC_TRASH ��Ŷ���� Ŭ���̾�Ʈ�� �۽��մϴ�.(���� �����ۻ����Ǹ� ������ ����)
		ITEMSKILL_CS_SELL, 
		// CONTAINER_SLOT	stSkillItemPos;	// �����Ǹ�Ư����ų�� ������ �ִ� �����Ѿ���������
		// int				iSkillID;		// �����Ǹ� �Ӽ��� ������ �ִ� ��ų��ȣ
		// CONTAINER_ITEM	stSellItem;		// �Ǹ��� ����������

		SKILL_CS_LEARN,
		// int iSkillID;
		// int			iUseEly;
		// TRASH_ITEM	stUseItem;


		SKILL_SC_LEARN,
		// GLOBAL_STRING_ID	iErrorMsg;
		// GU_ID			iInstanceID;
		// CHAR_SKILL       stSkillInfo;
		// __int64			iCurEly;
		// TRASH_ITEM		stUseItem;
	
		SKILL_SC_INIT_ITEMMIX,
		// GU_ID			iInstanceID
		// ITEMMIX_INFO     stItemMixInfo;	

		SKILL_SC_INIT_SELECTIVE,
		// GU_ID			iInstanceID
		// UINT32			iMaskingFlag;

	//////////////////////////////////////////////////////////////////////////
	//
	//	EFFECT
	//
		PI_CS_EFFECT = PI_CS_LOGIC + 1900,

		// ���� Char���ɸ� ����Ʈ����.
		EFFECT_SC_INFOS = PI_CS_EFFECT,
		// GU_ID			iInstanceID; // pc
		// GU_ID			iInstanceID; // Caster
		// UINT16			iNumOfEffect;
		// sizeof(EFFECT_DATA)*iNumOfEffect;

		// ���� Char�� �ɸ� ����Ʈ ������ �����.
		EFFECT_SC_DEL,  
		// GU_ID			iInstanceID; // pc
		// GU_ID			iInstanceID; // Caster
		// UINT16			iNumOfEffect;
		// sizeof(int)*iNumOfEffect;	// iEffectInstanceID;

	//////////////////////////////////////////////////////////////////////////
	//
	// Team
	//
		PI_CS_TEAM = PI_CS_LOGIC + 2000,

		// ���ʴ�
		TEAM_CS_REQUEST = PI_CS_TEAM,
		// char				szRcvCharName[LEN_NAME+1];	// ������̸�

		// ���ʴ� ���. �����ΰ��� ��û�ڿ��Ը� �۽�, �����ΰ��� ����ڿ��Ը� �۽�
		TEAM_SC_REQUEST,	// ��û�ڿ� ����ڿ��� �۽�
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// char				szCharName[LEN_NAME+1];		// �̸�
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

		// ����������
		TEAM_CS_JOIN,
		// char				szActCharName[LEN_NAME+1];	// ��û���̸�

		// ���������� ���
		TEAM_SC_JOIN,		// ���и� ����ڿ��� �۽�, �����̸� ��� �������� �۽�
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// char				szActCharName[LEN_NAME+1];	// ��û���̸�
		// GU_ID			RcvCharGUID;				// �����
		// char				szRcvCharName[LEN_NAME+1];	// ������̸�
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
		// UINT8			byLootingRule;				// ���÷�(0:���ʴ��,1:����,2:����)
		// int				iCnt;						// ������
		// TEAM_MEMBER		stTeam_Member;				// ��������
		// ...											// ��������ŭ

		// ��Ż��
		TEAM_CS_SECEDE,

		// ��Ż�� ���.(������ȭ)
		TEAM_SC_SECEDE,		// ��� �������� �۽�, *** ���� : ������ 2���� ��쿡 ��Ŷ�� ������ ��Ƽ�����ؾ��մϴ�.
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// INT32			iActCharID;					// Ż����ĳ����DBŰ

		// ����(������ȭ)
		TEAM_CS_EXPEL,
		// INT32			iRcvCharID;					// �����ĳ����DBŰ

		// ������(������ȭ)
		TEAM_SC_EXPEL,		// ��� �������� �۽�, *** ���� : ������ 2���� ��쿡 ��Ŷ�� ������ ��Ƽ�����ؾ��մϴ�.
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// INT32			iRcvCharID;					// ������ĳ����DBŰ

		// ��������(������ȭ)
		TEAM_CS_CHANGECAPTAIN,
		// INT32			iRcvCharID;					// �����ĳ����DBŰ

		// �������� ���(������ȭ)
		TEAM_SC_CHANGECAPTAIN,	// ��� �������� �۽�
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// INT32			iRcvCharID;					// ������ĳ����DBŰ

		// ���÷꺯��
		TEAM_CS_CHANGELOOTINGRULE,
		// UINT8			byLootingRule;				// �����÷�

		// ���÷꺯�� ���
		TEAM_SC_CHANGELOOTINGRULE,	// ��� �������� �۽�
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// UINT8			byLootingRule;				// �����÷�

		// ������������ ���(�������� �����⸸ ��) : ������� ���������� �ʿ�
		// 2006.04.13 dhpark ������� ��ġǥ�ø� ���ؼ� ��ġ������ �߰��ǰ� Ŭ���̾�Ʈ�� ��û�Ҽ��ֵ��� �����մϴ�.
		TEAM_SC_UPDATEMEMBER,	// ��� �������� �۽�. *** ���� : ��ε�ĳ���ÿ��� ���� ������ �����մϴ�. �������� ������ ��ε�ĳ���������� �� ��Ȯ�մϴ�.
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// TEAM_MEMBER		stTeam_Member;				// ��������

		// ������������ ��û. ������� ���� �ִ� ������ �����ֱ⸶�� �ٸ������� ������ ��û�մϴ�.
		TEAM_CS_UPDATEMEMBER,
		// GU_ID			RcvCharGUID;				// ������ ���ŵ� ����

		// �������۽�(ä���̵��� �������� ������ �۽Ž� ���)
		TEAM_SC_INFO,
		// GU_ID					ObjectGUID;						// ���ӿ�����Ʈ���̵�
		// UINT8					byLootingRule;					// ���÷�(0:���ʴ��,1:����,2:����)
		// int						iCnt;							// ������
		// TEAM_MEMBER				stTeam_Member;					// ��������
		// ...														// ��������ŭ

	//////////////////////////////////////////////////////////////////////////
	//
	//	Event Box 
	//
		PI_CS_GIFT = PI_CS_LOGIC + 2100,

		// gift �����Կ� �����ϴ� gift����Ʈ�� ��û.
		GIFT_CS_LIST = PI_CS_GIFT,

		// gift �����Կ� �����ϴ� gift��û ���.
		GIFT_SC_LIST,
		// GU_ID				CharGUID;		// ��ü��
		// GLOBAL_STRING_ID		iError ;		// 0: ����
		// int					iNumOfGiftID;	// �޾ƾ� �� gift ����
		// __int64				iGiftNO;		// gift key ID					
		// int					iGiftID;		// GIFT.LDT ����	
		
		// gift �����Կ��� 1���� gift �ޱ� ��û.
		GIFT_CS_GET,
		// __int64				iGiftNO;

		// gift �����Կ��� 1���� gift �ޱ� ��û ���
		GIFT_SC_GET,
		// GU_ID				CharGUID;		// ��ü��
		// GLOBAL_STRING_ID		iError ;		// 0: ����
		// __int64				iGiftNO;
		// __int64				iCurrMoney;		// ������
		// UINT8				iItemCount;		// ������ ���� ����
		// CONTAINER_ITEM		tContainerItem;	// ���� ������ ����

	//////////////////////////////////////////////////////////////////////////
	//
	//	MailBox
	//
		PI_CS_MAILBOX = PI_CS_LOGIC + 2200,

		// ���� ��� ��û
		MAILBOX_CS_GETLIST	= PI_CS_MAILBOX,
		// TCHAR					szCharName[LEN_NAME+1];					// null included
		// UINT32					uiMailBoxID;
		MAILBOX_SC_GETLIST,
		// GLOBAL_STRING_ID			iError;
		// UINT8					nMailCount;				// ���� ���� ����
			// nMailCount �ݺ�
			//{
				// MAIL_HEADER_ATTACHMENT	mailHeaderInfo[];		// ������� ����
				// UINT8			uiSubjectLen;
				// TCHAR			szSubect[];
				// CONTAINER_ITEM	containerItem;				
			//}
		
		// ���� ���� (Ŭ���̾�Ʈ������ ������ �ѹ��� �ϳ����� �����ϰ� ����. (���� - ��� ���� - ���� ����)
		MAILBOX_CS_SEND,
		// MAIL_HEADER_ATTACHMENT	mailHeaderInfo[];		// ������� ����
		// UINT8					uiSubjectLen;			// ����
		// TCHAR					szSubect[];
		// UINT8					uiMemoLen;				// ����
		// TCHAR					szMemo[];
		// TCHAR					szReceiver[LEN_NAME+1];	// ������
		// UINT32					uiMailBoxID;
		// CONTAINER_SLOT			UsingItemPos;		// ����� ������ ��ġ����
		// ITEMNO					iUsingItemNo;		// ����� ������ Ű��ȣ

		MAILBOX_SC_SEND,
		// GLOBAL_STRING_ID			iError;

		// if iError == 0
			// UINT8				flagTrashItem;			// 0(NONE),1(Item�� �κ����� ������ ��)
			// TRASH_ITEM			AttachItem;				// ÷�ξ�����
			// UINT64				uiRemainEly;			// ���� ������ �ܿ� Ely��
			// TRASH_ITEM			UsingItem;				// ��ǥ������
		// else
			// TCHAR				szReceiver[LEN_NAME+1];	// if iError != 0(������)

		// ���� ����
		MAILBOX_CS_DELETE,
		// UINT64					uiMailID;
		// UINT32					uiMailBoxID;
		MAILBOX_SC_DELETE,
		// GLOBAL_STRING_ID			iError;
		// UINT64					uiMailID;

		// ���� (����) ����
		MAILBOX_CS_GETBODY,
		// UINT64					uiMailID;
		// UINT32					uiMailBoxID;
		MAILBOX_SC_GETBODY,
		// GLOBAL_STRING_ID			iError;
		// UINT64					uiMailID;
		// UINT8					uiLen;
		// TCHAR					szMemo[];

		// ÷�ε� ���� ó�� 
		// ÷�ε� Ely,Item�� ���� �κ��� �ܰ� �߰��Ѵ�.(Attachment ������ �Ұ�,Memo�� ����. -->  ���� Ŭ���̾�Ʈ�� ������� ���� ��û�� ���� ���� ������)
		MAILBOX_CS_MOVEATTACHMENT,
		// UINT64					uiMailID;
		// CONTAINER_ITEM			containerItem;				
		// UINT32					uiMailBoxID;
		MAILBOX_SC_MOVEATTACHMENT,						// Item �̵� ����(InsertITem), Ely��ȭ���� ������ ��Ŷ���� ó����
		// GLOBAL_STRING_ID			iError;
		// UINT64					uiMailID;
		// UINT64					uiRemainEly;
		// UINT8					uiItemCount;		// ������ ���� ����
		// CONTAINER_ITEM			containerItem;		// ���� ������ ����
		// UINT8					uiMailDeleted;		// Memo ������ ���� ��� �ڵ� ������

		// New Mail arrived
		MAILBOX_SC_NEWMAIL,
		// GLOBAL_STRING_ID			iError;
		// UINT8					nMailCount;			// ���� ������ ���� ���� (����� �׻� 1)
		// MAIL_HEADER_ATTACHMENT	mailHeaderInfo[];	// ������� ����
		// UINT8					uiLen;
		// TCHAR					szSubject[];
		// CONTAINER_ITEM			containerItem;		// �߰� ������ ����

	//////////////////////////////////////////////////////////////////////////
	//
	//	Cash Shop 
	//
		PI_CS_CASHSHOP = PI_CS_LOGIC + 2300,

		// ĳ���� ����
		CASHSHOP_CS_IN = PI_CS_CASHSHOP,
		// int					iMajor;  // �߰� : GLOBAL_SYS : 21�� ��. 
		// int					iMinor;  // �߰� : Ŭ���̾�Ʈ���� ���� ���� ���̳� ����. ä�� �̵��ÿ��� �����Ǿ����� ��������... 
		// int					iHotVer; // �߰�

		CASHSHOP_SC_IN,
 		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;
		// int					iMinor;  // �߰� 
		// int					iHotVer; // �߰�

			// for GamePot
				// UINT8		uiTokenLen;
				// if uiTokenLen > 0
					// TCHAR	szToken[];

			// other
				// UINT64		uiDID;
				// int    nCount;             //[xialin 2008/07/30] add�Դ���¼
				// ITEMID nItems[nCount];


		// ĳ���� ��Ż
		CASHSHOP_CS_OUT,
		// int nCount;		//[xialin 2008/07/30] add�Դ���¼
		// ITEMID nItems[nCount];

		CASHSHOP_SC_OUT,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;

		// ĳ������/�κ�������������û.
		CASHSHOP_CS_INFO,

		// ĳ������/�κ������� ���� ��û ���
		CASHSHOP_SC_INFO,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;
		// int					iCurrOz;
		// int					iCurrMileage;
		// UINT16				nItems;
		// CONTAINER_ITEM		containerItem;

		// ĳ������ ���� ��û.
		CASHSHOP_CS_CASH,
		
		// ĳ������ ���� ��û ���.
		CASHSHOP_SC_CASH,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;
		// int					iCurrOz;
		// int					iCurrMileage;

		// CASHSHOP ���� ����.
		CASHSHOP_CS_BUY,
//new
		// int					iPackageID;				//CASH_SHOP.LDT::ItemID
		//-------------------------------------------   // ��ȿ�� �˻縦 ����
		// int					iShopPrice;				//CASH_SHOP.LDT::_CashPrice
		// int					iSalePrice;				//CASH_SHOP.LDT::_SalePrice
		// int					iMaxOz;					//CASH_SHOP.LDT::_MaxOz
		// int					iMaxMileage;			//CASH_SHOP.LDT::_MaxMileage
		//--------------------------------------------  // ��ȿ�� �˻縦 ����
		// int					iBuyOz;					// �������ڰ�.
		// int					iBuyMileage;			// ���ϸ��� ���ڰ�.

		// CASHSHOP ���� ���԰��.
		CASHSHOP_SC_BUY,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;
		// int					iPackageID;				//CASH_SHOP.LDT::ItemID 
		// int					iCurrOz;				// ���� ����
		// int					iCurrMileage;			// ���� ���ϸ���.
		// UINT16				nItems;					// �ű� ���� ������ ����
		// CONTAINER_ITEM		containerItem;			// �ű� ���� ������ ����.

		// CASHSHOP �� �ȱ�. // stack �� �ִ� �� �ȼ� ����. �⺻ 1��¥���� ���ȱⰡ ��. 
		CASHSHOP_CS_SELL,
		// CONTAINER_ITEM		tContainerItem;         // ��� ��ġ�� �ִ� ���� // ������ ���� �����̸� // MaxStack �� 1�ΰ͸� ����

		// CASHSHOP �� �ȱ� ���.
		CASHSHOP_SC_SELL,
		// GLOBAL_STRING_ID		iError ;		// 0: ����
		// GU_ID				globalID;
		// int					iCurrMileage;	// ���ϸ����� ȯ�� �ǹǷ� ���� ��ȭ �Ǿ�� ��.
		// TRASH_ITEM			tTrashItem;		// �����Ǿ�� �� ������ ����
		// UINT8				iSkipUpdate;	// �ܰ�������Ʈ �������� 0: ������Ʈ 1: ������Ʈ����


		// ���� ���
		CASHSHOP_CS_COUPON,
		//UINT8	len;
		//TCHAR szCouponCode[];

		CASHSHOP_SC_COUPON,
		// GLOBAL_STRING_ID		iError ;		// 0: ����
			//iError == 9002003
				// int iMilage;					// iMilage ���ϸ����� ȹ���ϼ̽��ϴ�.		
				// int iRemainMilage;			// �� ���ϸ��� �ܰ�
			//iError == 9002004
				// UINT32	uiGiftID;			// uiGiftID�� ȹ���ϼ̽��ϴ�. Gift �� Ȯ���ϼ���....
			//iError == 9002010
				// int iOz;						// iOz�� ȹ���ϼ̽��ϴ�.		
				// int iRemainOz;				// �� �ܰ�

		// CASHSHOP ���� ����.
		CASHSHOP_CS_BUY_PRESENT,
//new
		// TCHAR				TargetCharName[LEN_NAME];
		// int					iPackageID;				//CASH_SHOP.LDT::ItemID
		//-------------------------------------------   // ��ȿ�� �˻縦 ����
		// int					iShopPrice;				//CASH_SHOP.LDT::_CashPrice
		// int					iSalePrice;				//CASH_SHOP.LDT::_SalePrice
		// int					iMaxOz;					//CASH_SHOP.LDT::_MaxOz
		// int					iMaxMileage;			//CASH_SHOP.LDT::_MaxMileage
		//--------------------------------------------  // ��ȿ�� �˻縦 ����
		// int					iBuyOz;					// �������ڰ�.
		// int					iBuyMileage;			// ���ϸ��� ���ڰ�.
		// TCHAR				Comment[MAX_MAIl_BODY_LEN] // ���� ����.					

		// CASHSHOP ���� ���԰��.
		CASHSHOP_SC_BUY_PRESENT,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;
		// TCHAR				TargetCharName[LEN_NAME];
		// int					iPackageID;				//CASH_SHOP.LDT::ItemID 
		// int					iCurrOz;				// ���� ����
		// int					iCurrMileage;			// ���� ���ϸ���.

		// �򸮽�Ʈ �۽�(CASHSHOP_CS_INFO�� ���ؼ� �ڵ����� Ŭ���̾�Ʈ�� �۽�)
		CASHSHOP_SC_WISH_LIST,
		// int					iCnt;			// �򰳼�
		// int					iPackageID;		// ��Ű�����̵�
		// ...									// �򰳼���ŭ

		// ���߰�
		CASHSHOP_CS_WISH_ADD,
		// int					iPackageID;		// ��Ű�����̵�

		// ���߰�
		CASHSHOP_SC_WISH_ADD,
		// GLOBAL_STRING_ID		iErrorMsg;
		// int					iPackageID;		// ��Ű�����̵�(�����϶���)

		// �����
		CASHSHOP_CS_WISH_DEL,
		// int					iPackageID;		// ��Ű�����̵�

		// �����
		CASHSHOP_SC_WISH_DEL,
		// GLOBAL_STRING_ID		iErrorMsg;
		// int					iPackageID;		// ��Ű�����̵�(�����϶���)

		// �߰�
		CASHSHOP_SC_MINOR_INIT,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;

		// �߰�
		CASHSHOP_SC_MINOR_INFO,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;
		// UINT16				nShopInfo;
		// CASHSHOP_INFO		ShopInfos[];		

		CASHSHOP_SC_OUT_READY,
		// GLOBAL_STRING_ID		iErrorMsg;
		// GU_ID				globalID;



		//20080407 mijin �ε��� ĳ����,��õ��ǰ ���� üũ
		CASHSHOP_CS_VERSION,
		// int					iMajor;  				//ĳ���� Major����
		// int					iMinor;  				//ĳ���� Minor����
		// int					iHotVer;				//��õ��ǰ ����

		//20080407 mijin ĳ����,��õ��ǰ ������ Ʋ���� �����͸� ������
		CASHSHOP_SC_VERSION,
		// GLOBAL_STRING_ID			iErrorMsg;
		// GU_ID				globalID;
		// int					iMinor;  				//ĳ���� Minor����
		// int					iHotVer;				//��õ��ǰ ����



		//20080407 mijin �ʵ忡�� ��ǰ ���� üũ
		CASHSHOP_CS_PRICE,
		// int					iHotVer;				//��õ��ǰ ����
		// int					iPackageID;				//CASH_SHOP.LDT::ItemID
		// int					iShopPrice;				//CASH_SHOP.LDT::_CashPrice
		// int					iSalePrice;				//CASH_SHOP.LDT::_SalePrice
		// int					iMaxOz;					//CASH_SHOP.LDT::_MaxOz
		// int					iMaxMileage;				//CASH_SHOP.LDT::_MaxMileage

		//20080407 mijin �ʵ忡�� ��ǰ ���� üũ ���
		CASHSHOP_SC_PRICE,
		// GLOBAL_STRING_ID			iErrorMsg;
		// GU_ID				globalID;
		// int					iHotVer;				//��õ��ǰ ����
		// int					iPackageID;				//CASH_SHOP.LDT::ItemID 
		// int					iShopPrice;				//CASH_SHOP.LDT::_CashPrice
		// int					iSalePrice;				//CASH_SHOP.LDT::_SalePrice
		// int					iMaxOz;					//CASH_SHOP.LDT::_MaxOz
		// int					iMaxMileage;				//CASH_SHOP.LDT::_MaxMileage



		//��õ��ǰ ������ Ʋ����� �����͸� ������
		CASHSHOP_SC_HOT_INFO,
		// GLOBAL_STRING_ID			iErrorMsg;
		// GU_ID					globalID;
		// UINT16					nHotInfo;
		// CASHSHOP_HOT_INFO		HotInfos[];


		// �������� ���� ��õ��ǰ ������¸� ��� pc�鿡�� ����
		CASHSHOP_SC_HOT_STATUS,
		// UINT8					iHotCashShopMode;

		CASHSHOP_CS_EFFECT,
		//int					iSeqID;						//�ͻ���SeqID
		//int					iID;						//CASH_EFFECT.LDT::nID
		//UINT8					iOptLen;					//������Ϣ����
		//TCHAR					szOpt[];					//������Ϣ

		CASHSHOP_SC_EFFECT,
		//int					iSeqID;						//�ͻ���SeqID
		//GLOBAL_STRING_ID		iErrorMsg;

		//	jmulro ���ٹ���2008��8��26  ---start
		CASHSHOP_CS_GET_QUICK_BUY_INFO,	
		CASHSHOP_SC_GET_QUICK_BUY_INFO,
		//	GLOBAL_STRING_ID			iErrorMsg;
		//	UINT uInfoCount;
		//	t_Quick_Buy_Info info[];
		CASHSHOP_CS_QUICK_BUY_BUY_ITEM,
		//	int					nPackageID;
		//-------------------------------------------   // ��ȿ�� �˻縦 ����
		// int					iShopPrice;				//CASH_SHOP.LDT::_CashPrice
		// int					iSalePrice;				//CASH_SHOP.LDT::_SalePrice
		// int					iMaxOz;					//CASH_SHOP.LDT::_MaxOz
		// int					iMaxMileage;			//CASH_SHOP.LDT::_MaxMileage
		//--------------------------------------------  // ��ȿ�� �˻縦 ����
		// int					iBuyOz;					// �������ڰ�.
		// int					iBuyMileage;			// ���ϸ��� ���ڰ�.		
		//	jmulro ���ٹ���2008��8��26 ---end

		CASHSHOP_CS_ASK_BUY,
		// UINT8				nPackageID;					// iPackageID������
		// int					iPackageID[];				// CASH_SHOP.LDT::ItemID
		// UINT8				len;						// szMsg����
		// TCHAR				szMsg[];					// ��Ϣ
		// UINT8				nReceiverName;				// szReceiverName�ĳ���
		// TCHAR				szReceiverName[LEN_NAME];	// �������������

		CASHSHOP_SC_ASK_BUY,
		// GLOBAL_STRING_ID		iErrorMsg;
		// UINT8				nPackageID;					// iPackageID������
		// int					iPackageID[];				// CASH_SHOP.LDT::ItemID
		// UINT8				nSenderName;				// szSender�ĳ���
		// TCHAR				szSender[];					// ����������

		CASHSHOP_SC_ASK_BUY_RECV,
		// UINT8				nPackageID;					// iPackageID������
		// int					iPackageID;					// CASH_SHOP.LDT::ItemID
		// UINT8				iLen;						// szReceiverName�ĳ���
		// TCHAR				szRequesterName[LEN_NAME];	// �������������
		// UINT8				len;						// szMsg����
		// TCHAR				szMsg[];					// ��Ϣ

	//////////////////////////////////////////////////////////////////////////
	//
	//	Title
	//
		PI_CS_TITLE = PI_CS_LOGIC + 2400,

		// Ÿ��Ʋ ����Ʈ. Ÿ��Ʋ�� ���� ������ ��Ŷ�� ��������ŭ�� ������ �۽��մϴ�. 
		TITLE_SC_LIST = PI_CS_TITLE,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// int				iCnt;			// Ÿ��Ʋ ����
		// UINT32			uiTitleID;		// Ÿ��Ʋ ���̵�
		// ...								// Ÿ��Ʋ ������ŭ

		// Ÿ��Ʋ �߰�
		TITLE_SC_INSERT,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// UINT32			uiTitleID;		// ������ Ÿ��Ʋ���̵�

		// Ÿ��Ʋ ����
		TITLE_CS_CHANGE,
		// UINT32			uiTitleID;		// ������ Ÿ��Ʋ���̵�

		// Ÿ��Ʋ ����
		TITLE_SC_CHANGE,	// �ֺ��� ��ε�ĳ��Ʈ�ؾ���
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// UINT32			uiTitleID;		// ������ Ÿ��Ʋ���̵�

	//////////////////////////////////////////////////////////////////////////
	//
	//	FreeMarket
	//
		PI_CS_FREEMARKET = PI_CS_LOGIC + 2500,

		// ���λ��� ����
		FREEMARKET_CS_OPEN = PI_CS_FREEMARKET,
		// UINT8			byType;			// ����Ÿ��(�̰��� �ش��ϴ� ���ǰ˻�/������������ �˻��մϴ�.)
		// char				szFMName[FM_MAX_NAME+1]; // ������
		// int				iCnt;			// �Ǹž����� ����
		// FM_SELLITEM		stFM_SellItem;	// �Ǹž����� ����
		// ...								// �Ǹž����� ������ŭ

		// ���λ��� ����
		FREEMARKET_SC_OPEN,		// �ֺ��� ��ε�ĳ��Ʈ�ؾ���
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�(��������)
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�(��������)
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�(0�̸� ��������)
		// UINT8			byType;			// ����Ÿ��
		// char				szFMName[FM_MAX_NAME+1]; // ������

		// ���λ��� �ݱ�
		FREEMARKET_CS_CLOSE,

		// ���λ��� �ݱ�
		FREEMARKET_SC_CLOSE,	// �ֺ��� ��ε�ĳ��Ʈ�ؾ���
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�(��������)
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�(��������)
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�(0�̸� ��������)

		// ���λ����� ����
		FREEMARKET_CS_IN,
		// GU_ID			FMGUID;			// ���������� ���ӿ�����Ʈ���̵�

		// ���λ����� ����
		FREEMARKET_SC_IN,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�(0�̸� ��������)
		// int				iCnt;			// �Ǹž����� ����
		// FM_VIEWITEM		stFM_ViewItem;	// �Ǹž����� ����
		// ...								// �Ǹž����� ������ŭ

		// ���λ������� ������
		FREEMARKET_CS_OUT,
		// GU_ID			FMGUID;			// ���������� ���ӿ�����Ʈ���̵�

		// ���λ������� ������
		FREEMARKET_SC_OUT,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�

		// ���λ������� ���� ���
		FREEMARKET_CS_BUY,
		// GU_ID			FMGUID;			// ���������� ���ӿ�����Ʈ���̵�
		// FM_ITEM			stFM_Item;		// ������ ������ ����

		// ���λ������� ���� ���
		FREEMARKET_SC_BUY,	// �����϶��� ����ڿ��Ը� ������ �����϶��� �մԵ� ��ο��� ������ �Ǹž����۸���� �����ϰ� �մϴ�.
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�(��������մ�)
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�(��������մ�)
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�(0�̸� ��������)
		// FM_ITEM			stFM_Item;		// �Ǹŵ� ������ ����

	//////////////////////////////////////////////////////////////////////////
	//
	// Festival ( ���ӳ����� ����Ǵ� ���� �̺�Ʈ)
	//
		PI_CS_FESTIVAL = PI_CS_LOGIC + 2600,

	//////////////////////////////////////////////////////////////////////////
	//
	//	WayPoint
	//
		PI_CS_WAYPOINT = PI_CS_LOGIC + 2700,

		// ��������Ʈ ����Ʈ
		WAYPOINT_SC_LIST = PI_CS_WAYPOINT,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// int				arrWayPoint[];	// ��������Ʈ������

		// �� ��������Ʈ �߰�
		WAYPOINT_CS_FIND,
		// int				iWayPointID;		// ��������Ʈ���̵�

		// �� ��������Ʈ �߰�
		WAYPOINT_SC_FIND,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�
		// int				iWayPointID;	// ��������Ʈ���̵�

		// ������ ��������Ʈ�� �̵�
		WAYPOINT_CS_MOVE,
		// int				iWayPointID;		// ��������Ʈ���̵�
		// UINT8			byRank;				// 0, 1

		// ������ ��������Ʈ�� �̵�
		WAYPOINT_SC_MOVE,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;		// �������̵�
		// int				iWayPointID;	// ��������Ʈ���̵�

	//////////////////////////////////////////////////////////////////////////
	//
	//	Guild
	//
		PI_CS_GUILD = PI_CS_LOGIC + 2800,

		// PC�α��ν� ������ �����ִ� PC�� �Ҽӵ� �������
		GUILD_SC_PCGUILD = PI_CS_GUILD,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// PCGUILD			stPCGuild;							// ĳ���� �������

		// �Ϲ� �������
		GUILD_CS_GUILD_COMMON,
			
		// �Ϲ� �������
		GUILD_SC_GUILD_COMMON,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// GUILD_COMMON		stGuildCommon;						// �Ϲ� �������

		// ��� ��� ����Ʈ
		GUILD_CS_MEMBERLIST,
			
		// ��� ��� ����Ʈ
		GUILD_SC_MEMBERLIST,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// INT32			iMemberCnt;							// ��� �����
		// GUILD_MEMBER		stGuildMember;						// ��� �������
		// ...
	
		// ��� ����
		GUILD_CS_CREATE,
		// char				szGName[GUILD_MAX_NAME+1];			// ����
		// UINT8			byGType;							// ���Ÿ��(1:�Ϲ�, 2:õ��, 3:�Ǹ�)
		// UINT8			arrGMark[3];						// ��帶ũ
		// UINT8			byGRank;							// ��巩ũ(Ÿ�԰� ��ũ�� ��� LDTŰ�� ����մϴ�.)
			
		// ��� ����(������ ��ε�ĳ��Ʈ�Ǿ����)
		GUILD_SC_CREATE,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// PCGUILD			stPCGuild;							// ĳ���� �������

		// ��� �ı�
		GUILD_CS_DESTROY,
			
		// ��� �ı�(������ ��ε�ĳ��Ʈ�Ǿ����(�ֺ�������� ��尡 ������ٴ°��� �˾ƾ���). ������ �̹� �渶�� ���� ��Ȳ�̹Ƿ� ������� ����)
		GUILD_SC_DESTROY,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�

		// ��� ���ΰ� ����
		GUILD_CS_UPDATE_SLOGAN,
		// char				szGSlogan[GUILD_MAX_SLOGAN+1];		// ��彽�ΰ�

		// ��� ���ΰ� ����
		GUILD_SC_UPDATE_SLOGAN,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�

		// ����ʴ�
		GUILD_CS_REQUEST,
		// char				szRcvCharName[LEN_NAME+1];			// ������̸�

		// ����ʴ� ���. �����ΰ��� ��û�ڿ��Ը� �۽�, �����ΰ��� ����ڿ��Ը� �۽�. szCharName(�����ΰ��� ����ڸ�, �����ΰ��� ��û�ڸ�)
		GUILD_SC_REQUEST,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// char				szGName[GUILD_MAX_NAME+1];			// ����
		// char				szCharName[LEN_NAME+1];				// ������ ���� ��û�ڸ�, ������ ���� ����ڸ�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)

		// �����������
		GUILD_CS_JOIN,
		// char				szActCharName[LEN_NAME+1];			// ��û���̸�

		// �����������
		GUILD_SC_JOIN,		// ���и� ����ڿ��� �۽�, �����̸� �ֺ��� ��ε�ĳ����
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
		// PCGUILD			stPCGuild;							// ĳ���� �������

		// ���Ż��
		GUILD_CS_SECEDE,

		// ���Ż�� ���.
		GUILD_SC_SECEDE,	// ������ ��ε�ĳ���õǾ����. 
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)

		// ��尭��
		GUILD_CS_EXPEL,
		// INT32			iRcvCharID;							// ���������� DBNum

		// ��尭����
		GUILD_SC_EXPEL,		// ��û�ڿ��� ������ ��û�� ���� ���
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)

		// ��尭����
		GUILD_SC_EXPEL_ME,	// �������� �������� �۽�(���������� ��尡 ��������ϹǷ�).
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�

		// ��å����
		GUILD_CS_CHANGEGRADE,
		// INT32			iRcvCharID;							// ��å���������� DBNum
		// UINT8			byGrade;							// ���� ��å

		// ��å����
		GUILD_SC_CHANGEGRADE, // ��û�ڿ��� ������ ��û�� ���� ���
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)

		// ��å����
		GUILD_SC_CHANGEGRADE_ME, // ����ڿ��� ������ �뺸��Ŷ. ��å�� �������� ������ �ƴϹǷ� ��ε�ĳ�������� ����
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// UINT8			byGrade;							// ���� ��å

		// ����������� �޼���
		GUILD_SC_MSG_MEMBER,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// UINT8			byMemberMsgType;					// ����޼���Ÿ��(0:����, 1:Ż��, 2:����, 3:��������, 4:�α���, 5:�α׾ƿ�)
		// GUILD_MEMBER		stGuildMember;						// �������

		// ����������� �޼���
		GUILD_SC_MSG_GUILD,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// UINT8			byGuildMsgType;						// ���޼���Ÿ��(0:���ΰǺ���, 1:��ũ����)
		// GUILD_COMMON		stGuildCommon;						// �Ϲ����� �������

		// ����������
		GUILD_CS_CHANGEMASTER,
		// INT32			iRcvCharID;							// �����ĳ����DBŰ

		// ��û�ڿ��� ������ ���������� ���. �����ΰ��� ��û�ڿ��Ը� �۽�, �����ΰ��� ��û���ֺ��� ��ε�ĳ����(�����渶�� ���Ż�� �ֺ�����鿡�� �˸��� ����)
		GUILD_SC_CHANGEMASTER,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)

		// ����ڿ��� ������ ���������� ���. �渶�������� ������ �ʿ��ϰԵǸ� ���⼭ ó���ؾ��մϴ�. ����� �������â���� �渶���޾׼��� �����־ �ʿ����.
		GUILD_SC_CHANGEMASTER_ME,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�

		// ����ɱ�
		GUILD_CS_PLANT,
		// UINT32			uiCropID;							// ������̵�
		// TRASH_ITEM		stConsumeItem;						// �Ҹ�Ǵ¾�����

		// ����ɱ� ���. �ֺ��� ��ε�ĳ��Ʈ�մϴ�.(��, ���濡���� ������ �׼��̰� ������ ��ü�� ��ε�ĳ��Ʈ�������� �����Ѵٰ� ��ӵ�.)
		GUILD_SC_PLANT,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
		// UINT32			uiCropID;							// ������̵�

		// ����̱�
		GUILD_CS_GRUB,

		// ����̱� ���. �ֺ��� ��ε�ĳ��Ʈ�մϴ�.(��, ���濡���� ������ �׼��̰� ������ ��ü�� ��ε�ĳ��Ʈ�������� �����Ѵٰ� ��ӵ�.)
		GUILD_SC_GRUB,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)

		// ���/������ �ֱ�
		GUILD_CS_NOURISH,
		// UINT32			uiBoosterID;						// ���/���������̵�
		// TRASH_ITEM		stConsumeItem;						// �Ҹ�Ǵ¾�����

		// ���/������ �ֱ� ���. �ֺ��� ��ε�ĳ��Ʈ�մϴ�.(��, ���濡���� ������ �׼��̰� ������ ��ü�� ��ε�ĳ��Ʈ�������� �����Ѵٰ� ��ӵ�.)
		GUILD_SC_NOURISH,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
		// UINT32			uiRemainTime;						// ����ð��� ���Ͽ� ���� ����Ϸ���� �����ð�(�ʴ���)
		// UINT32			uiNourishTime;						// ����ð��� ���Ͽ� ���� ��Ḧ ���� �ð�(�ʴ���)
		// UINT32			uiHastenSumTime;					// ������ �����ð�

		// ������Ϸ�. ���泻�� ��� PC���� ��ε�ĳ��Ʈ�մϴ�.
		GUILD_SC_GROWTHCROP,

		// ��ũ��
		GUILD_CS_RANKUP,
		// UINT8			byNewGRank;							// New��巩ũ
		// TRASH_ITEM		stConsumeItem;						// �Ҹ�Ǵ¾�����

		// ��ũ��. �����ֺ��� ��ε�ĳ�������� �ʽ��ϴ�.(2007.08.13 dhpark ����������� ����)
		GUILD_SC_RANKUP,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
		// INT32			iGNum;								// ���DBNum
		// UINT8			byNewGRank;							// New��巩ũ

		// ��帶ũ����
		GUILD_CS_CHANGEMARK,
		// UINT32			uiGMarkID;							// ��帶ũLDT���̵�
		// TRASH_ITEM		stConsumeItem;						// �Ҹ�Ǵ¾�����

		// ��帶ũ����. �����ֺ��� ��ε�ĳ�������� �ʽ��ϴ�.(2007.08.13 dhpark ����������� ����)
		GUILD_SC_CHANGEMARK,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�(0�̸� ��������)
		// INT32			iGNum;								// ���DBNum
		// UINT8			arrGMark[3];						// ��帶ũ

	//////////////////////////////////////////////////////////////////////////
	//
	//	Indun
	//
		PI_CS_INDUN = PI_CS_LOGIC + 2900,

		// �δ� ���� ��û
		INDUN_CS_IN = PI_CS_INDUN,
		// UINT32			uiIndunLDTID;						// �����Ϸ����ϴ� �δ��� LDTID
			
		// �δ� ���� ��û ���
		INDUN_SC_IN,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// UINT32			uiIndunID;							// �δ� �ν���Ʈ ���̵�
		// UINT16			wServerID;							// �δ� �������̵�

		// �δ� ���� ��û ���. OnPortalEvent()������ �б��Ͽ� ó���˴ϴ�.(�δ������̸鼭 ��ǥ���� �δ����ʱ׷�Ÿ���� �ƴѰ�쿡 ä���̵����� �����°����� �Ǵ�)
		INDUN_SC_OUT,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
			
		// �δ� �ʱ�ȭ ��û
		INDUN_CS_INIT,
			
		// �δ� �ʱ�ȭ ��û ���. �����ϰ� �ִ� �δ��� ������ uiIndunLDTID�� 0�Դϴ�.
		INDUN_SC_INIT,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// UINT32			uiIndunLDTID;						// �δ� LDT ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�

	//////////////////////////////////////////////////////////////////////////
	//
	//	Lottery
	//
		PI_CS_LOTTERY = PI_CS_LOGIC + 3000,

		//�̱� �� ����� ����.
		LOTTERY_SC_START = PI_CS_LOTTERY, 

		// �̱� ������Ʈ �̱� ���Խó� ������Ʈ��ư ������
		LOTTERY_CS_UPDATE ,
		// UINT32			iVer;

		// �̱� ������Ʈ ���
		LOTTERY_SC_UPDATE,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// UINT32			iVer;								// ErrorID�� 0 ��츸 ����
		// UINT16			iLotteryCount;						// ErrorID�� 0 ��츸 ����
		// UINT8			iNumOfLotteryBoard;					// ErrorID�� 0 ��츸 ����
		// UINT32			iLotteryBoard[iNumOfLotteryBoard];					// ErrorID�� 0 ��츸 ����
		// UINT8			iNumOfRewardInfo;
		// LOTTERY_REWARD	RewardInfo[iNumOfRewardInfo];

		// �̱�
		LOTTERY_CS_CHOICE,
		// UINT32			iVer;								// �ǹ���
		// UINT16			iIndex;								// bit�ǹ迭 ÷��
		// CONTAINER_SLOT	UsingItemPos;				// ����� ������ ��ġ����
		// ITEMNO			iUsingItemNo;				// ����� ������ Ű��ȣ
		// int				iUsingEly;					// ����� ���� �Ӵ�	

		// 

		// �̱� ���
		LOTTERY_SC_CHOICE,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// UINT16			iRewardID;							// ErrorID�� 0��츸 ����
		// CONTAINER_ITEM   tItem;								// ErrorID�� 0��츸 ���� 
		// UINT64			iPCCurrEly;							// ErrorID�� 0��츸 ����
		// TRASH_ITEM		TrashItem;							// ErrorID�� 0��츸 ����
		// UINT16			iLotteryCount;						// ErrorID�� 0, 13001004 ��츸 ����.
		// UINT8			iNumOfLotteryBoard;					// ErrorID�� 0, 13001004 ��츸 ����.
		// UINT32			iLotteryBoard[iNumOfLotteryBoard];	// ErrorID�� 0, 13001004 ��츸 ����. iLotteryCount�� �����Ҽ� �̴� �迭 ������ŭ��

	//////////////////////////////////////////////////////////////////////////
	//
	//	Event Mission
	//
		PI_CS_EVENTMISSION = PI_CS_LOGIC + 3100,

		// ��������Ʈ ����Ʈ
		EVENTMISSION_SC_LIST = PI_CS_EVENTMISSION, // �����
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// int				arrMissionFlag[MAX_EVENT_MISSION_DATA];	// CP_EVENT_MISSION.ldt::_Save ����ŷ�� 

		// �̺�Ʈ �߻�
		EVENTMISSION_CS_RAISE ,
		// int				iMissionID ;	// CP_EVENT_MISSION.ldt::_Item_ID

		// �̺�Ʈ �߻� ���. 
		// iMissionType �� ����Ʈ �̰� iErrorMsg = 0 �̸� �� ���� ���� �����ּ���. 
		EVENTMISSION_SC_RAISE,
		// GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;		// �������̵�,  0 �ΰ�츸 ���� �����ͼ۽�
		// int				iMissionID;		// CP_EVENT_MISSION.ldt::_Item_ID
		// UINT8			iMissionType;	// CP_EVENT_MISSION.ldt::_MissionType
		// int				iMissionFlag;	// ������ �̺�Ʈ�̼��÷��װ�(0�̸� �������)
		// UINT8			iNumOfItem;		// ���� �����ۼ�
		// CONTAINER_ITEM   stItem[];		// ���� ������


	//////////////////////////////////////////////////////////////////////////
	//
	//	GAMBLE
	//
		PI_CS_GAMBLE = PI_CS_LOGIC + 3200,

		// �̱�
		GAMBLE_CS_REQ	= PI_CS_GAMBLE,
		// int				iGambleID;					// GAMBLE.LDT::_ITEM_ID
		// UINT8			iBettingCount;				// 
		// UINT8			iNumOfUseItem;				// �Ҹ��� ������
		// TRASH_ITEM		TrashItem[];				// ����� ������ ��ġ����
		// UINT8			iNumOfAutoSell;				// �ڵ������� �ȱ�
		// int				iAutoSellRewardID[];

		// �̱� ���
		GAMBLE_SC_REQ,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// int				iGambleID;							// ErrorID�� 0��츸 ����
		// UINT8			iBettingCount;
		// int				iGambleRewardID[];					// ErrorID�� 0��츸 ����
		// UINT8			iAutoSell[];						// �ڵ��Ǹ�
		// UINT8			iNumOfItem;							// ErrorID�� 0��츸 ����
		// CONTAINER_ITEM   tItem;								// ErrorID�� 0��츸 ���� 
		// UINT64			iPCCurrEly;							// ErrorID�� 0��츸 ����
		// UINT8			iNumOfTrashItem;					// ErrorID�� 0��츸 ����
		// TRASH_ITEM		TrashItem;							// ErrorID�� 0��츸 ����


	//////////////////////////////////////////////////////////////////////////
	//
	//	PVP
	//
		PI_CS_PVP = PI_CS_LOGIC + 3400,

		// PVP ���
		PVP_CS_REGIST = PI_CS_PVP,
		// UINT8			byPVPType;							// (1:FDEATH, 2:FTIME, 3:PDEATH, 4:PTIME, 5:GDEATH, 6:GTIME)
		// UINT32			uiPVPScale;							// ���ο�����. (1:2�ο�, 2:4�ο�, 4:6�ο�, 8:8�ο�)
			
		// PVP ��� ���
		PVP_SC_REGIST,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�

		// PVP ��� ���
		PVP_CS_CANCEL,
			
		// PVP ��� ��� ���
		PVP_SC_CANCEL,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
			
		// PVP ���� ���(�������� ��Ī�� �Ǹ� ������)
		PVP_SC_IN,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// UINT32			uiIndunID;							// PVP�� �ν���Ʈ ���̵�
		// UINT16			wServerID;							// �δ� �������̵�
			
		// ����� ����ڵ��� �ε����¸� �˷���(1�� �ε��Ϸ�ø��� ��� ����ڿ��� �۽�)
		PVP_SC_LOADSTATUS,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// INT32			iMemberCnt;							// ����ڼ�
		// PVPLOADSTATUS	stPVPLoadStatus;					// ������� PVP�ε����
		// ...
			
		// ����� ����ڵ鿡�� PVP�� ���۵Ǿ��ٰ� �˷���
		PVP_SC_START,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// UINT32			uiLDTID;							// PVP LDT ���̵�
			
		// PVP �����û(PVP�δ����� ����� ��Ż�� ��� ������ ������ �����)
		PVP_CS_OUT,
			
		// PVP �����û ���. OnPortalEvent()������ �б��Ͽ� ó���˴ϴ�.(�δ������̸鼭 ��ǥ���� �δ����ʱ׷�Ÿ���� �ƴѰ�쿡 ä���̵����� �����°����� �Ǵ�)
		// Ŭ���̾�Ʈ�� PVP������ ������ PVP_CS_OUT�� ������ ���������� ��ġ���常�ϰ� �����⵵ ��.
		PVP_SC_OUT,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
			
		// PVP������ �۽��մϴ�.
		PVP_SC_RANK,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// INT32			iMemberCnt;							// ����ڼ�
		// PVPRANK			stPVPRank;							// ������� PVP��������
		// ...
			
		// PVP���Ḧ �۽��մϴ�.
		PVP_SC_FINISH,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// INT32			iMemberCnt;							// ����ڼ�
		// PVPRANK			stPVPRank;							// ������� PVP��������
		// ...


	//////////////////////////////////////////////////////////////////////////
	//
	//	SERVERINFO : Ŭ���̾�Ʈ�� ��û�� ���� ���������� �۽��մϴ�.
	//
		PI_CS_SERVERINFO = PI_CS_LOGIC + 3500,

		// �����ð�/���� ��û
		SERVERTIME_CS_INFO = PI_CS_SERVERINFO,

		// �����ð�/���� �۽�
		SERVERTIME_SC_INFO,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// tm				stServerTime;				// �����ð�
		// WORLD_ID			wWorldID;					// ������̵�
		// SERVER_ID		wServerID;					// �������̵�
		// char				szAccountID[MAX_LEN_ID+1];	// �������̵�
		// char				szClientIP[LEN_IP+1];		// Ŭ���̾�Ʈ������
		// TCHAR			szName[LEN_NAME+1];			// ĳ���͸�
		// UINT				uiStageID;					// �����������̵�
		// UINT				uiMapGroupID;				// �ʱ׷���̵�
		// UINT				uiPosX;						// X��ǥ
		// UINT				uiPosY;						// Y��ǥ


	//////////////////////////////////////////////////////////////////////////
	//
	//	Chat Room												// 2008/03/07 by Hoony0109
	//
		PI_CS_CHATROOM = PI_CS_LOGIC + 3600,

		// ��ȭ�� ���� ��û
		CHATROOM_CS_CREATE = PI_CS_CHATROOM, // (ĳ���� �Ҹ�� ������Ų�� ������Ʈ�� ���� ��� Ȯ�强 ���.)
		// CHATROOM_INFO	stChatRoomInfo;						// �����Ϸ����ϴ� ��ȭ���� ����
		// UINT8			iAdvert;							// ���� ���� (0 , 1)
		// if(iAdvert == 1)
			// TRASH_ITEM		stConsumeItem;						// ����� ������
			// UINT8			iChatRoomAdvertLen;					// ���� �޼��� ����
			// TCHAR			szAdvert[iChatRoomAdvertLen];		// ���� �޼��� (�ִ�: MAX_CHATROOM_ADVERT_LEN)

		// ��ȭ�� ���� ���.	+ INDUN_SC_IN ���� (���� ���� + ITEM_SC_TRASH ����)
		CHATROOM_SC_CREATE,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// UINT32			uiMyCharID;
		// UINT8			iAdvert;							// ���� ���� (0, 1)
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// if(ErrorID == 0)
			// CHATROOM_INFO	stCRInfo;							// �����Ϸ����ϴ� ��ȭ���� ����

		// ��ȭ�� ������Ʈ ����.
		// CHATROOM_SC_MAKE_OBJECT, => NAV_SC_INSIGHT �� ����
			// GU_ID					ObjectGUID;					// ���ӿ�����Ʈ���̵�
			// BG_ID					Layer;
			// UINT						iPosX;						//
			// UINT						iPosY;						//
			// CHATROOM_OBJECT_INFO		stChatRoomObject_Info		//

		// ��ȭ�� ������Ʈ �ı�.
		// CHATROOM_SC_DESTROY_OBJECT, => NAV_SC_OUTOFSIGHT �� ����.
			// GU_ID						ObjectGUID;					// ���ӿ�����Ʈ���̵�

		// ��ȭ�� ���� �� �� ���� Ȯ��.
		CHATROOM_CS_ROOMINFO_CHECK,
		// UINT32			uiRoomNo;

		// ��û�� ������ ���.
		CHATROOM_SC_ROOMINFO_CHECK,
		// GU_ID			globalID;							// ����� ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// if(0 == _ErrorID)
			// CHATROOM_INFO	stChatRoomInfo;						// �����Ϸ����ϴ� ��ȭ���� ����

		// ��ȭ�� ���� ��û. (�̹� ActPC �� 2�� ����� ������ üũ.) (�δ�, ��ȭ�濡�� �� �̵��ϴ� ��� ó��.)
		CHATROOM_CS_JOIN,
		// CHATROOM_INFO	stChatRoomInfo;						// �����Ϸ����ϴ� ��ȭ���� ����

		// ��ȭ�� ���� ���.	+ INDUN_SC_IN ����
		CHATROOM_SC_JOIN,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// UINT32			uiMyCharID;
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// if(ErrorID == 0)
			// CHATROOM_INFO	stCRInfo;							// �����Ϸ����ϴ� ��ȭ���� ����

		// ��ȭ�� ����� ��û.
		CHATROOM_CS_MODIFY,
		// UINT8			iPassWord;							// 0: �н����� �̺���, 1: �н����� ���� ���Խ�.
		// CHATROOM_INFO	stCRInfo;							// �����Ϸ����ϴ� ��ȭ���� ����

		// ��ȭ�� ����� ���. (������ ��� ���� ����. - �н����常 ����ô� ����.)
		CHATROOM_SC_MODIFY,
		// GU_ID				globalID;						// ����� ���̵�
		// GLOBAL_STRING_ID		iError;							// 0 : ����
		// CHATROOM_INFO		stCRInfo;						// �����Ϸ����ϴ� ��ȭ���� ����

		// ��ȭ�� ���� ��û.
		CHATROOM_CS_OUT,
		// UINT32			uiID;								// ��ȭ�� �ν��Ͻ� ���̵� (Unique Key)
		// UINT32			uiRoomNo;							// �����Ϸ��� �ϴ� ��ȭ���� ��ȣ.
		// UINT8			iBanOut;							// 0: �Ϲ����� 1: ��������

		// ��ȭ�� ���� ���.	+ INDUN_SC_OUT ����
		CHATROOM_SC_OUT,	
		// GU_ID			globalID;							// ����� ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�

		// ������ ���� ���� ��û. (�ִ� 2���� ���� Ƚ�� �� ���ȣ ����.) �������� ������ ��ϰ� ������ ��� �� Ƚ�� ����.
		CHATROOM_CS_FORCEOUT,
		// UINT32			uiID;								// ��ȭ�� �ν��Ͻ� ���̵� (Unique Key)
		// UINT32			uiRoomNo;							// �����Ű���� �ϴ� ��ȭ���� ��ȣ.
		// UINT32			uiCharID;							// ���� ���� ���.

		// ������ ���� ���� ��û ����. (������ CHATROOM_SC_BROADCAST_UNITED_MESSAGE �޼��� �۽�.)
		CHATROOM_SC_FORCEOUT,
		// GU_ID				globalID;						// ����� ���̵�
		// GLOBAL_STRING_ID		iError;							// 0 : ����
		// if(0 == iError)
			// UINT8				iFlag;						// 0: ������ ���� ��û�� ����. 1:���� ���� �����.

		// ���� �絵 ��û.
		CHATROOM_CS_CHANGEMASTER,
		// UINT32			uiTargetCharID;
		// UINT32			uiRoomID;
		// UINT32			uiRoomNo;

		// ���� �絵 ��û ���.
		CHATROOM_SC_CHANGEMASTER,
		// GU_ID			globalID;							// ����� ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�

		CHATROOM_SC_BROADCAST_UNITED_MESSAGE, // (0:Join, 1:Out, 2:Forceout, 3:ChangeMaster)
		// UINT8			iFlag;
		// ROOM_MEMBER		stRoomMember;

		// ��ȭ�� ������ ��� ����.
		CHATROOM_SC_MEMBERLIST,
		// UINT32			uiSize;
		// ROOM_MEMBER		stRoomMember[uiSize];

		// ��ȭ�� ���� ��û. (�� ������ ���� ���� ���� ...) -> SCOPE_CHATROOM_ADVERT �߰��ϴ� �������...
		CHATROOM_CS_ADVERT,
		// UINT32			uiRoomID;
		// UINT32			uiRoomNo;
		// TRASH_ITEM		stConsumeItem;								// ����� ������
		// UINT16			iAdvertSize;
		// TCHAR			szAdvertMessage[iAdvertSize]				// iAdvertSize <= MAX_CHATROOM_ADVERT_LEN

		// ��ȭ�� ���� ���. (������ �Ҹ� => ITEM_SC_TRASH)
		CHATROOM_SC_ADVERT,
		// GU_ID			globalID;							// ����� ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�

		// ��ȭ�� ��� ��û. (��û�� �ʱ�ȭ)
		CHATROOM_CS_ROOMLIST,
		// UINT8			iRoomType;

		// ��ȭ�� ��� ���. (�������� ��Ŷ���� ������ ����.)
		CHATROOM_SC_ROOMLIST,
		// GU_ID			globalID;						// ����� ���̵�
		// GLOBAL_STRING_ID ErrorID;
		// if(ErrorID == 0)
			// UINT8			iResetFlag;						// 1 = ����Ʈ �ʱ�ȭ, 0 = ����Ʈ ������, 2 = ����Ʈ ������, 3 = ����Ʈ �������� ������(���� �� ������ 1���� ��Ŷ�� �� ������� �ǹ���)
			// UINT8			iRoomType;
			// UINT32			uiCount;
			// CHATROOM_INFO	stChatRoomInfo[uiCount];

		// ��ȭ ��� ��� ��û.
		CHATROOM_CS_USERLIST,
		// UINT8			iSex;
		// UINT16			iMinLevel;
		// UINT16			iMaxLevel;
		// PCSTATUS_STYLE	stStyle;

		// ��ȭ ��� ��� ���.
		CHATROOM_SC_USERLIST,
		// GU_ID				globalID;						// ����� ���̵�
		// GLOBAL_STRING_ID		ErrorID;
		// if(ErrorID == 0)
			// UINT32				uiCount;
			// CHARACTER_BASICINFO	stCharInfo[uiCount];

		// �ʴ��� ���� Flow (A-S-B)
		// CHATROOM_CS_INVITE_REQ (A -> S) - CHATROOM_SC_INVITE_REQ (S -> B) - CHATROOM_CS_INVITE_ANS (B -> S) - CHATROOM_SC_INVITE_ANS (S -> A)
		// �ʴ� ��ü�� ������ ���
		// CHATROOM_CS_INVITE_REQ (A -> S) - CHATROOM_SC_INVITE_REQ (S -> A)
		// �ʴ� �� �ʴ��ڿ� ���� ������ ���
		// CHATROOM_CS_INVITE_REQ (A -> S) - CHATROOM_SC_INVITE_REQ (S -> B) - CHATROOM_CS_INVITE_ANS (B -> S) - CHATROOM_SC_INVITE_ANS (S -> B)

		// ��ȭ ��� �ʴ� ��û (��û��). // 1:1 ��ȭ �ʴ� ���� (Client A -> Sv)
		CHATROOM_CS_INVITE_REQ,
		// TCHAR			szRcvCharName[LEN_NAME+1];				// ������̸�
		// UINT8			uiInviteInRoom;							// �ʴ��� ����.(�̹� ������ �濡�� �ʴ��ϴ� ������(1), 1:1��ȭ �ʴ�����(0))
		// CHATROOM_INFO	stChatRoomInfo;

		// ��ȭ ��� �ʴ� (��û ���). // 1:1 ��ȭ �ʴ� ���� (Sv -> Client B)
		CHATROOM_SC_INVITE_REQ,
		// GU_ID				globalID;						// ����� ���̵�
		// TCHAR				szTargetName[LEN_NAME+1];
		// GLOBAL_STRING_ID		ErrorID;
		// if(0 == ErrorID)
			// TCHAR				szActorName[LEN_NAME+1];
			// UINT8				uiInviteInRoom;
			// CHATROOM_INFO		stChatRoomInfo;

		// ��ȭ ��� �ʴ� ���� (��û ���). // 1:1 ��ȭ �ʴ� ���� (Client B -> Sv)
		CHATROOM_CS_INVITE_ANS,
		// UINT8				iAllowed;						// 0: �ʴ� �ź�, 1: �ʴ� ����.
		// TCHAR				szActorName[LEN_NAME+1];
		// UINT8				uiInviteInRoom;
		// CHATROOM_INFO		stChatRoomInfo;

		// ��ȭ ��� �ʴ� ��� (��û��). // 1:1 ��ȭ �ʴ� ���� (Sv -> Client A)
		CHATROOM_SC_INVITE_ANS,
		// GU_ID				globalID;						// ����� ���̵�
		// TCHAR				szTargetName[LEN_NAME+1];
		// GLOBAL_STRING_ID		ErrorID;

		// ��ȭ��� Ư�� PC ���� ��û.
		CHATROOM_CS_OTHERPC_INFO,
		// TCHAR			szCharName[LEN_NAME+1];

		// ��ȭ��� �� Ư�� PC ���� ���.
		CHATROOM_SC_OTHERPC_INFO,
		// GU_ID			globalID;							// ����� ���̵�
		// GLOBAL_STRING_ID	ErrorID;							// �������̵�
		// UINT8			iFlag;								// 0: ����, 1: �ڽ��� ��Ÿ�� �����, 2: ����� ��Ÿ�� �����
		// if(0 == ErrorID)
			// CHARACTER_INFO2	stCharInfo2;
			// UINT16			iTotalSize;
			// FIGURE_ITEM		stFigureItemList[iTotalSize];
			// PCSTATUS_STYLE	stStyle;

		// ��Ÿ�� ���� ���� ��û. (���� Tabel�� ����)
		CHATROOM_CS_SET_MYSTYLE,
		// PCSTATUS_STYLE	stStyle;

		// ��Ÿ�� ���� ���.
		CHATROOM_SC_GET_MYSTYLE,
		// GU_ID			ObjectGUID;							// ���ӿ�����Ʈ���̵�
		// PCSTATUS_STYLE	stStyle;

	//////////////////////////////////////////////////////////////////////////
	//
	//	Auction												// 2008/03/07 by Hoony0109
	//
		PI_CS_AUCTION = PI_CS_LOGIC + 3700,		

		// ��������( ���������� ������� �߰� �Ȱ��)
		AUCTION_SC_OPEN,
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�

					
		// ���� ���
		AUCTION_CS_CREATE,
		// UINT8	iType;				//�ŷ�Ÿ��(AUCTION_TYPE)
		// UINT8	iDuration;			//�ⰣŸ��(AUCTION_DURATION )
		// __int64	iStartingPrice;		//���۰�
		// __int64	iBuyOutPrice;		//�ﱸ��
		// __int64	iEnrolPrice;		//��ϼ�����
		// TRASH_ITEM stUseItem;		//�ʿ��������ġ�� ����(1)
		// ITEM_NO	iUseItemNo;			//�ʿ������Ű
		//-------------------------------------------------
		//	iType == AUCTION_TYPE_ITEM_BY_ELY
		//		CONTAINER_SLOT		stUpItemPos;
		//		ITEM_NO				iUpItemNo;
		//	else
		//		AUCTION_GOODS_POINT stUpPoint;

		// ���ǵ�� ���
		// �ǸŸ���Ʈ �ѹ��� ���� �������� ����
		AUCTION_SC_CREATE,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�
		// iErrorID == 0
			// AUCTION_HEADER	stAuctionHeader;					// �⺻����
			// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)
			// __int64			iCurrEly;							// ���糲���� (��ϼ����� or �ø� ���� ���ϰ� ���� �������ִµ�)
			// TRASH_ITEM		stUseItem;							// �ʿ������
			//-------------------------------------------------
			//	stAuctionHeader.iType == AUCTION_TYPE_ITEM_BY_ELY
			//		TRASH_ITEM			stUpItem;					// �ø�Z�����ۻ�������
			//	else
			//		CHARACTER_CASH_INFO stCash;						// ����ĳ������
		// iErrorID != 0
			// CHARACTER_CASH_INFO stCash;	


		// ��� ��û
		AUCTION_CS_CANCEL,
		//__int64	iAuctionID;									// ���Ű
		// int		iCategory;									// Item.ldt::AuctionCategory or 8000 �̻�
	
		// ��� ��û ���(�����)
   		AUCTION_SC_CANCEL,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�
		// iErrorID == 0
			// __int64			iAuctionID;							// ���Ű
			// CHARACTER_CASH_INFO stCash;							// 
		// iErrorID != 0
			// CHARACTER_CASH_INFO stCash;							// 


		// ��������
		//		- ������ �Ǹ���/�����ڿ��� 
		//		- ��ҽ� �����ڿ���
		AUCTION_SC_FINISH,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�
		// iErrorID == 0
			// __int64			iAuctionID;							// ���Ű
			// CHARACTER_CASH_INFO stCash;							// 
		// iErrorID != 0
			// CHARACTER_CASH_INFO stCash;							// 

		// �����Ϸ�
		//		- ������ �Ǹ���/�����ڿ���
		//		- �ﱸ�� �Ǹ��ڿ���
		AUCTION_SC_FINISH_SELL,
		// GU_ID			iObjectID;
		// __int64			iAuctionID;							// ���Ű
		// USERID			iBuyerID;							// ������
		// CHARACTER_CASH_INFO stCash;							// 

		// �����ϱ��û
		AUCTION_CS_BID,
		// __int64			iAuctionID;							// ���Ű
		// int				iCategory;							// Item.ldt::AuctionCategory or 8000 �̻�
		// __int64			iBidPrice;							// ������

		// �������� : �Ǹ��� �����ڿ��� ����
		// �ǸŸ���Ʈ/��������Ʈ�� �ѹ��� ���� �������� ����
		AUCTION_SC_BID,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�
		// iErrorID == 0
			// AUCTION_HEADER	stAuctionHeader;					// �⺻����
			// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)
			// __int64			iCurrEly;							// ���糲���� (��ϼ����� or �ø� ���� ���ϰ� ���� �������ִµ�)
			// CHARACTER_CASH_INFO stCash;							// ����ĳ������							
		// iErrorID != 0
			// CHARACTER_CASH_INFO stCash;							// 


		// �ﱸ��û
		AUCTION_CS_BUYOUT,
		// __int64			iAuctionID;							// ���Ű
		// int				iCategory;							// Item.ldt::AuctionCategory or 8000 �̻�
		// __int64			iBidPrice;							// �ﱸ��
		// UINT8			iRefresh;							// 1: ���� 0: ���ž���
		// int				iStartNumber;						// ���°�ͺ��� �� �ް� ������
		// int				iCategory;							// 
		// UINT8			iSortKey;							// AUCTION_SORT_ITEMKEY(������ �������� ��������̸� ��ȹ���� ���Ѱ�)
		// UINT8			IsAsc;								// 1: �������� 0: ��������
		// iCategory < 8000
			// TCHAR			szItemName[MAX_ITEM_NAME];		// �����۸�
			// short			iItemLvMin;							// �����۷����̻�: �⺻ 1
			// short			iItemLvMax;							// �����۷�������: �⺻ 999 (�˻����� ������ üũ�� ���η�������)
			// UINT8			iItemQuility;						// ������ǰ��
		// iCategory >= 8000
			// int				iMinPoint;							// ��ü�˻��ϰ�� iMinPoint iMaxPoint 0
			// int				iMaxPoint;

		// �ﱸ��û���
		AUCTION_SC_BUYOUT,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�
		// iErrorID == 0
			// __int64			iAuctionID;							// ���Ű
			// __int64			iCurrMoney;							// ���Ű
			// CHARACTER_CASH_INFO stCash;							// 
		// iErrorID != 0
			// CHARACTER_CASH_INFO stCash;							// 



		//-----------------------------------------------------------------
		// ���ǰ˻�(
		AUCTION_CS_SEARCH,
		// int				iCategory;							// 
		// UINT8			iSortKey;							// AUCTION_SORT_ITEMKEY(������ �������� ��������̸� ��ȹ���� ���Ѱ�)
		// UINT8			IsAsc;								// 1: �������� 0: ��������
		// iCategory < 8000
			// TCHAR			szItemName[MAX_ITEM_NAME];		// �����۸� : ��ü(NULL)
			// short			iItemLvMin;							// �����۷����̻�: �⺻ 1
			// short			iItemLvMax;							// �����۷�������: �⺻ 999 (�˻����� ������ üũ�� ���η�������)
			// UINT8			iItemQuility;						// ������ǰ�� : ��üǰ��(0)
		// iCategory >= 8000
			// int				iMinPoint;							// ��ü�˻��ϰ�� iMinPoint iMaxPoint 0
			// int				iMaxPoint;


		// ���ǰ˻����̹� �̷���� ���¿��� ��Ʈ�� �ؼ� ���������
		// Item Auction/ �ƺ������ ����
		AUCTION_CS_SORTING, // ������ ù�������� ����
		// int				iCategory;							// 
		// UINT8			iSortKey;							// AUCTION_SORT_ITEMKEY(������ �������� ��������̸� ��ȹ���� ���Ѱ�)
		// UINT8			IsAsc;								// 1: �������� 0: ��������
		// iCategory < 8000
			// TCHAR			szItemName[MAX_ITEM_NAME];		// �����۸�
			// short			iItemLvMin;							// �����۷����̻�: �⺻ 1
			// short			iItemLvMax;							// �����۷�������: �⺻ 999 (�˻����� ������ üũ�� ���η�������)
			// UINT8			iItemQuility;						// ������ǰ��								// 1: �������� 0: ��������
		// iCategory >= 8000
			// int				iMinPoint;							// ��ü�˻��ϰ�� iMinPoint iMaxPoint 0
			// int				iMaxPoint;

		// �˻�����Ʈ�� �̷�������¿��� ������ �� �޾Ƴ��� ������
		AUCTION_CS_GETNEXT,
		// int				iStartNumber;						// ���°�ͺ��� �� �ް� ������
		// int				iCategory;							// 
		// UINT8			iSortKey;							// AUCTION_SORT_ITEMKEY(������ �������� ��������̸� ��ȹ���� ���Ѱ�)
		// UINT8			IsAsc;								// 1: �������� 0: ��������
		// iCategory < 8000
			// TCHAR			szItemName[MAX_ITEM_NAME];		// �����۸�
			// short			iItemLvMin;							// �����۷����̻�: �⺻ 1
			// short			iItemLvMax;							// �����۷�������: �⺻ 999 (�˻����� ������ üũ�� ���η�������)
			// UINT8			iItemQuility;						// ������ǰ��		
		// iCategory >= 8000
			// int				iMinPoint;							// ��ü�˻��ϰ�� iMinPoint iMaxPoint 0
			// int				iMaxPoint;

		// ���ǰ˻�/��Ʈ/���޾ƿ��� ���
		AUCTION_SC_SEARCH_INFO,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID iErrorMsg ;							// iErrorMsg != 0 �� ���� ������ ���� ����
		// int				iNumOfTotalCount;					// �Ѱ���
		// int				iStartNumber;						// ��������ó������ �Ѱ����� ���°���� �ش��ϴ���
		// UINT8			iNumOfAuction;						// ���۵ɿ�����������
			// AUCTION_HEADER	stAuctionHeader;					// �⺻����
			// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)


		//--------------------------------------------------------------------

		// �ڱ��������� ������ 
		//		- ������������ ���� �������� �������� ����̰ų� 
		//		- AUCTION_SC_OPEN ���� ó�� �������� �������� �߻�.
		AUCTION_CS_INFO_4BIDDER,			

		AUCTION_SC_INFO_4BIDDER,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�

		AUCTION_SC_BIDLIST,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// UINT8			iNumOfAuction;						// ���۵ɿ�����������
			// AUCTION_HEADER	stAuctionHeader;					// �⺻����
			// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)

		//	��ȸ������ ���������ڿ��� ������������
		AUCTION_SC_BIDDEL,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�
		// __int64			iAuctionID;							// ���Ű

		// �ڱ� ������� ������
		//		- ������������ ���� �������� ���������߻� ����̰ų�
		//		- AUCTION_SC_OPEN ���� ó�� �������� �������� �߻�.
		AUCTION_CS_INFO_4SELLER,

		// �ڱ� �������
		AUCTION_SC_INFO_4SELLER,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	iErrorID;							// �������̵�
	
		AUCTION_SC_SELLLIST,
		// GU_ID			iObjectGUID;						// ���ӿ�����Ʈ���̵�
		// UINT8			iNumOfAuction;						// ���۵ɿ�����������
			// AUCTION_HEADER	stAuctionHeader;					// �⺻����
			// AUCTION_GOODS_XX stAuctionGoods;						// �ø� ���� ����( AUCTION_GOODS_ITEM or AUCTION_GOODS_POINT)

		//--------------------------------------------------------------------
		// Greener Guide
		
		GREENERGUIDE_SC_EVENT,
		// UINT32	iStartLevel

		GREENERGUIDE_CS_FETCHAWARD,
		// UINT32	iFetchLevel

		GREENERGUIDE_SC_FETECHAWARD,
		// UINT32	iFetchLevel
		// GLOBAL_STRING_ID	bResult
		// UINT32	iNotifyCode	(0: �����������ｫȫ�����͵��������䣬��ȥ�������ʵ�Ա����ȡ��
		//						(1: ���İ�����������δ��ȡ���ｫ�����������䣬��ȥ�������ʵ�Ա����ȡ��
		//						(2: �ɹ���ȡ


	//////////////////////////////////////////////////////////////////////////
	//
	//	COOLTIME
	//
		PI_CS_COOLTIME = PI_CS_LOGIC + 3800,

		COOLTIME_SC_INFOS = PI_CS_COOLTIME,
		// GU_ID			iInstanceID
		// unsigned short	iNumOfCoolTime
		// COOLTIME_DATA	stCoolTime[]


	//////////////////////////////////////////////////////////////////////////
	//
	//	LOTTERY
	//

		//	�ٱ����Э���
		//	��ҹ���ٱ���   2008��9��12 ��ʤ��
		PI_GAMBLE_LOGIC		= PI_CS_LOGIC + 3900,

		GAMBLE_SC_INITIAL	= PI_GAMBLE_LOGIC,
		//  UINT64 gambleVersion;
		//	UNSIGNED SHORT      usServerPoit;		//	�Ƿ��Ƿ������ڵ㹺��

		GAMBLE_CS_GET_STATUS,	
		//	
		GAMBLE_SC_GET_STATUS,
		//	GLOBAL_STRING_ID	ErrID;
		//	unsigned short		usFinished;    // �Ƿ������
		//	UINT64				GambleVersion;
		//	UNSIGNED SHORT      usServerPoit;		//	�Ƿ��Ƿ������ڵ㹺��
		//	UINT				count;
		//  t_Gamble_Status		status[];
		
		GAMBLE_SC_UPDATE,					//	���°ٱ����Ӧ��״̬��Ϣ
		//	UINT64 gambleVersion;			//	�ٱ���İ汾��
		//	t_Gamble_Status status;			//	�ٱ����״̬	
		//	char	szName[LEN_NAME+1];		//	�������
			
		GAMBLE_CS_BUY,
		//	UINT64  gambleVersion;		//	�汾��
		//	UINT32	uIndex;				//	λ��
		//	CONTAINER_SLOT ContainerSlot;	//	��Ʒλ��,ContainerSlot.ContainerTypeΪCONTAINER_TYPE_INVALID��ʾ�õ����
		//	ITEMNO	ItemNO;				//	��Ʒ�ı��

		GAMBLE_SC_BUY,
		//	GLOBAL_STRING_ID	iErrorID;			//	0Ϊû�д���1Ϊ�汾�����ͻ�����Ҫ���°ٱ���,2Ϊ�ٱ�����ʱ�޷�ʹ��
													//	3Ϊ����㣬4Ϊ��Ʒ����5Ϊ����İٱ���λ�ò��ԣ�6Ϊ�Ѿ������˹���
													//	7Ϊ��������ϴι����״̬����δ����ϴι���
		//	CHARID				charID;				//	��ҵ�ID��
		//	UINT64				gambleVersion;		//	�汾��
		//	t_Gamble_Getted_Item	itemID;				//	û�г��������£����򵽵���Ʒ
		//	UNSIGNED SHORT      usServerPoit;		//	�Ƿ��Ƿ������ڵ㹺��
		//	UINT8				uCount;				//	�ڶ�����Ʒ������
		//	t_Gamble_Getted_Item	itemID[];			//	�ڶ��ε���Ʒ	

		GAMBLE_SC_UN_BUY,				//	���ȡ������ĳ���ٱ���
		//	GLOBAL_STRING_ID	iErrorID;			//	errorID == 0 ��ʾû�з�������ֻ�������ȡ�˹���
		//	UINT64				gambleVersion;		//	�汾��
		//	UINT				uIndex;				//	�ٱ����ĳ��λ��

		GAMBLE_CS_ACCEPT_ITEM,
		//	UINT64  gambleVersion;		//	�汾��
		//	UINT8	accept;				//	�Ƿ���ܵ�һ�ε���Ʒ	0Ϊ���ܣ�1Ϊ������
		//	t_Gamble_Getted_Item  itemID;				//	��һ����Ʒ��ID
		//	CONTAINER_SLOT ContainerSlot;	//	��Ʒλ��,ContainerSlot.ContainerTypeΪCONTAINER_TYPE_INVALID��ʾ�õ����
		//	ITEMNO	ItemNO;				//	��Ʒ�ı��
		//	UNSIGNED SHORT      usServerPoit;		//	�Ƿ��Ƿ������ڵ㹺��


		GAMBLE_SC_ACCEPT_ITEM,
		//	GLOBAL_STRING_ID	iErrorID;	//	������Ϣ
		//	UINT8				accept;		//	�Ƿ���ܵ�һ�ε���Ʒ	1Ϊ��һ�Σ�2Ϊ�ڶ�����Ʒ
		//	t_Gamble_Getted_Item	itemID;		//	��Ʒ����Ϣ

		GAMBLE_CS_ACCEPT_SECOND_ITEM,		//	���ܵڶ��ε���Ʒ
		//	ITEMID  itemIDGetted;			//	�ڶ��ν��ܵ���Ʒ

		GAMBLE_SC_ACCEPT_SECOND_ITEM,
		//	GLOBAL_STRING_ID		iErrorID;	//	������Ϣ
		//	t_Gamble_Getted_Item	itemID;		//	��Ʒ����Ϣ

		GAMBLE_CS_ENTER_GAMBLE,				//	����ٱ��乺��״̬
		GAMBLE_SC_ENTER_GAMBLE,				//	���������ؽ��빺��״̬�Ƿ�ɹ�
		//	GLOBAL_STRING_ID	iErrorID;
		GAMBLE_CS_LEAVER_GAMBLE,			//	�ͻ����뿪����״̬	
		GAMBLE_SC_LEAVER_GAMBLE,			//	�뿪�ٱ���
		//	GLOBAL_STRING_ID	iErrorID;
		GAMBLE_SC_BROADCAST_GETTED_ITEM,	//	�㲥ĳ����һ�õ���Ʒ
		//	char   szName[LEN_NAME + 1];	//	�����Ʒ����ҵ�����
		//	t_Gamble_Getted_Item itemID;					//	��õ���Ʒ��ID

		GAMBLE_CS_GET_NAME,				//	��ȡ�ٱ����л�ý�Ʒ����ҵ�����
		//	UINT64  gambleVersion;		//	�汾��
		//	UINT32	uIndex;				//	λ��
		GAMBLE_SC_GET_NAME,
		//	UINT32	uIndex;					//	λ��
		//	char    szName[LEN_NAME + 1];	//	����


	//////////////////////////////////////////////////////////////////////////
	//
	//	NEW PET	
	//
		//	�³���Э���  2008��11��5
		PI_PET_LOGIC	= PI_CS_LOGIC + 4000,

		PET_SC_GET_INFO = PI_PET_LOGIC,
		//	UINT8 slotIndex;			//	�����ڳ���װ�����е�λ��
		//	ITEMNO itemNo;				//	�����Ψһ���
		//	t_PetAttr_Info Info;		//	����Ļ�������
		//	int	   nSkillCount;			//	���＼������
		//	t_Pet_Skill_To_Client petSkill[nSkillCount];	//	���＼��
		
		PET_CS_OPEN_PET_SHOP,
		//	UINT8	slotIndex;				//	��̯������װ������λ��
		//	ITEMNO	itemNo;					//	��̯�������Ʒ���
		//	char	szShopName[LEN_NAME];	//	�̵������
		//	UINT8	uShopStyle;				//	�̵��װ�Σ���ȷ��??????
		//	UINT8	uItemCount;				//	��Ʒ������
		//	FM_SELLITEM items[];			//	��Ʒ��λ��

		PET_SC_OPEN_PET_SHOP,
		//	GLOBAL_STRING_ID	iErrorID;		//	��̯�Ƿ�ɹ�

		PET_CS_GET_PET_SHOP_INFO,
		//	GU_ID shopGuid;					//	�̵��Ψһ��־��
		PET_SC_GET_PET_SHOP_INFO,
		//	GLOBAL_STRING_ID	iErrorID;	
		//	char szShopName[LEN_NAME];		//	�̵�����
		//	UINT32 itemCount;				//	��Ʒ������
		//	FM_VIEWITEM items[];			//	��Ʒ����Ϣ

		PET_CS_ENTER_PET_SHOP,		//	��ҽ�������̵�  ��Ϊ�˹㲥������Ϣ��������̵�����
		//	GU_ID shopguid;
		PET_SC_ENTER_PET_SHOP,
		//	GLOBAL_STRING_ID	iErrorID;		
		PET_CS_LEAVE_PET_SHOP,
		//	GU_ID shopguid;
		PET_SC_LEAVE_PET_SHOP,
		//	GLOBAL_STRING_ID	iErrorID;		
		PET_SC_UPDATE_PET_SHOP_ITEM,
		//	GU_ID shopguid;					// �̳ǵ�ID
		//	UINT8 uSlotIndex;				// ��λ�õ���Ʒ������	

		PET_CS_BUY_ITEM,					//	����Ʒ
		//	GU_ID	shopID;					//	�̵���
		//	UINT8	shopSlotIndex;			//	�����λ��
		//	FM_VIEWITEM viewItem;			//	������Ʒ����Ϣ������������

		PET_SC_BUY_ITEM,					
		//	GLOBAL_STRING_ID	iErrorID;	//	�Ƿ���ɹ�	

		PET_CS_CLOSE_PET_SHOP,
		//	USERID  uID;		
		//	CHARID  charID;		
		//	ITEMNO  itemNo;			//	�������Ʒ���

		PET_SC_CLOSE_PET_SHOP,
		//	GLOBAL_STRING_ID	iErrorID;
		//	ITEMNO  itemNo;			//	�������Ʒ���

		PET_CS_LEARN_SKILL,		//	ѧϰ����
		//	CONTAINER_SLOT itemSlot;	//	���＼�����ڲֿ��е�λ��
		//	ITEMNO itemNo;
		//	int nSkillID;
		//	int nBaseLevel;				//	���ܵȼ�

		PET_SC_LEARN_SKILL,
		//	GLOBAL_STRING_ID			//	iErrorID;		
		//	ITEMNO	itemNo;				//	�ĸ�����ѧ��
		//	int		nSkillID;			//	ѧϰ�ļ���
		//	int		nBaseLevel;			//	ѧϰ���ܵĵȼ�
		
		PET_CS_DISCARD_SKILL,
		//	ITEMNO	itemNo;
		//	int		nSkillID;			//	ȥ�����ܵ�ID
		//	int		nBaseLevel;			//	ȥ�����ܵĵȼ�

		PET_SC_DISCARD_SKILL,
		//	GLOBAL_STRING_ID	iErrorID;	//	�Ƿ�ɹ�
		//	ITEMNO itemNo;		//	����ı��
		//	int nSkillID;		//	���������ļ��ܵ�ID
		//	int		nBaseLevel;			//	ȥ�����ܵĵȼ�

		PET_SC_PET_ATTR_CHANGE,			//	��������Ըı䣬��Ҫ�㲥�����������
		//	CHARID  charID;				//	��ҵ�ID
		//	UINT8 slotIndex;			//	�����ڳ���װ�����е�λ��
		//	ITEMNO itemNo;				//	�����Ψһ���
		//	t_PetAttr_Info Info;		//	����Ļ�������

		PET_SC_PET_TAKE_OFF,			//	ж�س���ʱ�㲥
		//	CHARID	charID;
		//	UINT8	slotIndex;
		//	ITEMNO	itemNo;

		PET_CS_ADD_SSP,				//	����������ֽ����ĵ���
		//	CONTAINER_SLOT slot;	//	�ֽ���ߵ�λ��
		//	ITEMNO	itemNo;			//	����ı��
		PET_SC_ADD_SSP,				//	
		//	GLOBAL_STRING_ID	iErrorID;	//	�Ƿ�ɹ�

		PET_CS_CHANGE_NAME,			//	�������޸�����
		//	CONTAINER_SLOT slot;	//	�ֽ���ߵ�λ��
		//	ITEMNO itemNo;			//	����ı��
		//	char   szPetName[LEN_NAME];	//	�����������
		PET_SC_CHANGE_NAME,
		//	GLOBAL_STRING_ID	iErrorID;

        PET_CS_SHOUT,
		//	ITEMNO itemNo;		//	��Ӧ�ĳ���
		//	char   szContent[50];	//	��������

		PET_SC_SHOUT,
		//	GLOBAL_STRING_ID	iErrorID;
		//	GU_ID  guid;			//	��������ڰ�̯����ô���̳ǵ�GUID�����ڰ�̯����ô������ҵ�GUID
		//	char   szContent[50];	//	��������

		PET_SC_PET_SHOP_CLOSED,		//	�����̵걻�رյ�֪ͨ
		//	ITEMNO itemNo;


	//////////////////////////////////////////////////////////////////////////
	//
	//	WEDDING
	//

		PI_CS_WEDDING = PI_CS_LOGIC + 4200,

		WEDDING_SC_INFO = PI_CS_WEDDING,
		// GU_ID				ObjectGUID;						// ���ӿ�����Ʈ���̵�
		// WEDDING_INFO			WeddingInfo;					// ��������
		
		// ��û
		WEDDING_CS_REQUEST,
		// UINT8				iWeddingType;					// 1:����, 2:��������, 3:��ȥ
		// char					szRcvCharName[LEN_NAME+1];		// ��û������̸�
		// int					iEly;							// �Һ�Ǿ��ϴ� ����
		// CONTAINER_SLOT		tItemSlot;					// �Һ�Ǿ��ϴ� ������

		// ��û
		WEDDING_SC_REQUEST,
		// GU_ID				ObjectGUID;						// ���ӿ�����Ʈ���̵�
		// UINT8				iWeddingType;					// 1:����, 2:��������, 3:��ȥ
		// GLOBAL_STRING_ID		ErrorID;						// �������̵�(0�̸� ��������)
		// char					szRcvCharName[LEN_NAME+1];		// ��û������̸�


		// �����ڿ��� ��û ��û�� ��������
		WEDDING_SC_REQUEST_RECV,
		// GU_ID				ObjectGUID;						// ���ӿ�����Ʈ���̵�
		// UINT8				iWeddingType;					// 1:����, 2:��������, 3:��ȥ
		// char					szCharName[LEN_NAME+1];			// �̸� 

		// ��û ����
		WEDDING_CS_RESPONSE,
		// UINT8				iWeddingType;					// 1:����, 2:��������, 3:��ȥ
		// char					szActCharName[LEN_NAME+1];		// ��û���̸�
		// UINT8				byAccept;						// 0:����, 1:����


		// ��û ����
		WEDDING_SC_RESPONSE,
		// GU_ID				ObjectGUID;						// ���ӿ�����Ʈ���̵�
		// UINT8				iWeddingType;					// 1:����, 2:��������, 3:��ȥ
		// char					szCharName[LEN_NAME+1];
		// GLOBAL_STRING_ID		ErrorID;						// �������̵�(0�̸� ��������)

		// errorID�� �����϶��� accept,weddingInfo�� ������
		// UINT8				byAccept;						// 0:����, 1:����
		// weddingInfo�� accept�� �����ϰ�츸 ������
		// WEDDING_INFO			WeddingInfo;					// ��������
		// TRASH_ITEM			TrashItem;						// ����� ������


		// ��ȥ ��ġ��
		WEDDING_CS_CHAT,
		//UINT8					iMsgLen;							// �޼��� ����
		//TCHAR					szMsg[LEN_CASHITEM_NORMAL_MSG+1] = {0,};	

		//������ġ�⿡ Ÿ���߰��� ����
		//CHAT_SC_MSG ,
		// GLOBAL_STRING_ID	itemID;				// GLOBAL_STRING.LDT ���� �޼����� itemID ��
		// BROADCAST_SCOPE	scope;				// ��ε�ĳ���� ����
		// UINT8			uiFontColor;		// ��Ʈ��	: 0(default),1(Red),2(Orange),3(Yellow),4(white) : CHAT_COLOR.LDT::ItemID
		// UINT8			uiOptions;			// reserved for FontSize,FontType
		// UINT8			len;
		// TCHAR			szMsg[];		
		// GU_ID			guidSender;			// �۽��� ����
		// UINT8			nSenderName;
		// TCHAR			szSender[];
		// UINT16			ChannelID;			// ä�� ID	


		// ��ȥ�� ���
		WEDDING_SC_WEDDING_CANCEL,
		// GU_ID				ObjectGUID;						// ���ӿ�����Ʈ���̵�


		// ��ȥ�� ����/�� �˸�
		WEDDING_SC_MOTION_STARTEND,
		// GU_ID				globalID; 						// ����� ���̵�
		// UINT8				iStartEnd; 						// 0:Start(��ġ��â���ͽ���) 1:Start(��ġ��â���̽���) 2:End


		//�̴ϸ�, ����ʿ��� ����� ��ġ ���̱�
		WEDDING_CS_UPDATEMEMBER,


		//�α׿���, ä���� �ٸ��� �Ⱥ�����
		WEDDING_SC_UPDATEMEMBER,
		// GU_ID			globalID;							// ����� ���̵�
		// GU_ID			PartnerID;							// ����� GUID, ���������ϰ�� 0����
		// UINT8			iServerID;							// �������̵�, ���������ϰ�� 0���� 
		// int				usStageID;							// stageID, ���������ϰ�쳪 �ٸ�ä���϶� -1����
		// int				usMapGroupID;						// MapGroupID, ���������ϰ�쳪 �ٸ�ä���϶� -1����


		//�̺�
		WEDDING_CS_PARTING,
		// int			iEly;									// �Ҹ�Ǵ¿���


		WEDDING_SC_PARTING,
		// GU_ID				globalID;						// ����� ���̵�
		// GLOBAL_STRING_ID		iError;							// 0 : ����

		//WEDDING_CS_CHAR_INFO,
		//// char					szCharName[LEN_NAME+1];		// ���������ϱ����� ĳ�����̸�


		//WEDDING_SC_CHAR_INFO,
		//// GU_ID				globalID;					// ����� ���̵�
		//// GLOBAL_STRING_ID		iError;						// ��ȥ ������ ���»���� ������ ǥ��
		//// int					iLv;
		//// int					iDay;
		//// char					szCharName[LEN_NAME+1];		// ������ ĳ�����̸�

		// ��ȥ ��� ��ų
		WEDDING_SC_SKILL_USING,
		// RESULTCODE		resultCode;
		// GU_ID			iInstanceID;
		// UINT32			iSkillID;
		// LT_POSITION		pos;

		WEDDING_SC_SUMMON_REQUEST,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�

		// ��ȯ �����ڿ��� �����϶��� ������
		WEDDING_SC_SUMMON_REQUEST_ERR,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)



		// ���μ�ȯ��û����
		WEDDING_CS_SUMMON_RESPONSE,
		// UINT8			byAccept;					// 0:����, 1:����

		// ���μ�ȯ��û���� ���
		// �����϶��� ����ڿ��Ը� ������
		WEDDING_SC_SUMMON_RESPONSE,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

		// ���μ�ȯ��û����
		// ��û�ڿ��� ������ �ƴҶ� ������
		WEDDING_SC_SUMMON_RESPONSE_RECV,
		// GU_ID			ObjectGUID;					// ���ӿ�����Ʈ���̵�
		// GLOBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
		// UINT8			byAccept;

};

//////////////////////////////////////////////////////////////////////////////
// typedef

#pragma pack(push,1)

typedef UINT8	SLOT_INDEX;	// Slot Index (1 Base)
typedef UINT32	ITEMID;		// Item ID
typedef __int64 ITEMNO;

typedef struct _tagPCSTATUS_STYLE
{
	UINT8			uiHair;			// �Ӹ�
	UINT8			uiFashion;		// �м�
	UINT8			uiPersonality;	// ����
	UINT8			uiCondition;	// ����
} PCSTATUS_STYLE, *PPCSTATUS_STYLE;

typedef struct _tagPCSTATUS_POS
{
	int				iRevivalMap;	// ��Ȱ��ġ
	int				iTownMap;	// ��Ȱ��ġ
	UINT16			uiStageID;		// StageID
	UINT16			uiMapGroupID;	// MapGroupID
	UINT16			uiLayer;		// ���̾�
	int				iPosX;			// x��ǥ
	int				iPosY;			// y��ǥ
	UINT8			uiDir;			// PC�� �ٶ󺸴� �擇

} PCSTATUS_POS, *PPCSTATUS_POS;

//  [11/18/2004] ��� ������ by metalgeni
typedef struct _CHAR_EQUIPMENT
{
	INT16	iEquipID;			// enum EQUIP_ID		 0 = NULL, -1 = INVALID
	INT16	iEquipClass;		// enum EQUIP_CLASS		 0 = NULL, -1 = INVALID
	INT16	iiItemID;			// 0~999
	INT8	iiItemColor;		// 0~99
	UINT32  uiItemUniqueID;		
} CHAR_EQUIPMENT;


typedef struct _Gamble_Status
{
	UINT    uGambleIndex;	//	�ٱ���ı��
	int		nBuyStep;	//	����Ľ׶Σ�0δ������1Ϊ�Ѿ����򣬵���û�и�����Ʒ��2Ϊ�Ѿ��������Ѿ�������Ʒ��Ϣ
	ITEMID	itemID;		//	�Ѿ�����֮���itemID
	UINT32	uSetID;		//	��Ʒ�����ID

	_Gamble_Status()
	{
		uGambleIndex = 0;
		nBuyStep = 0;
		itemID = 0;
		uSetID = 0;
	}

}t_Gamble_Status;


typedef struct _Gamble_Getted_Item
{
	ITEMID	itemID;		//	��õĽ�Ʒ
	UINT8   usCount;	//	��Ʒ������
	UINT32	uSetID;		//	��Ʒ�����ID

	_Gamble_Getted_Item()
	{
		itemID	= 0;
		usCount = 0;
		uSetID  = 0;
	}

}t_Gamble_Getted_Item;


//[xialin 2008/07/25]add
enum CASH_EFFECT
{
	EFT_ADDPARCEL = 1,			//�Ӵ������
	EFT_ADDCONSUME = 2,			//�Ӵ�������
	EFT_ADDETC = 3,				//�Ӵ�������
	EFT_ADDEVENT = 4,			//�Ӵ�������
	EFT_ADDPET = 5,				//�Ӵ������
	EFT_ADDWH = 6,				//�Ӵ�ֿ���
	
};


enum VALUE_TYPE
{
	VALUE_BASE, // ������
	VALUE_CURR, // ������
	VALUE_MAX,
};


enum STAT
{
	STAT_LUK,	// luck
	STAT_ATK,	// attack
	STAT_DEF,	// defense
	STAT_ELE,	// element
	STAT_TOTAL,
};

enum ELEMENT
{
	WATER,
	EARTH,
	FIRE,
	WIND,
	ELEMENT_TOTAL,
};
enum ATK_TYPE
{
	ATK_NORMAL,
	ATK_HEAVY,
	ATK_JUMP,
	ATK_MAX,
};

typedef struct _MOVING_STATUS
{
	float			fMaxVelocityX;
	float			fJumpSpeed;
	float			fUpDownVelocity;
	float			fHangingVelocity;
	float			fDropSpeedNow;
	float			fDropSpeedMax;

}MOVING_STATUS;

// ũ���� �⺻ ����
typedef struct _CREATURE_INFO
{
	GU_ID	uiGlobalID;							// ClassID + InstanceID
	TCHAR	szName[LEN_NAME];
	UINT16	uiLevel;
	UINT32	uiMHP[VALUE_MAX];					// Base MaxHp, Curr MaxHP
	UINT32	uiMSP[VALUE_MAX];					// Base MaxSp, Curr MaxSP
	UINT32	uiHP;								// NowHP
	UINT32	uiSP;								// NowSP
	UINT32	uiRHP;								// Recv HP
	UINT32	uiRSP;								// Recv SP
} CREATURE_INFO,*PCREATURE_INFO;

// ���� ����(LUK,ATK,DEF,ELE,WATER,EARTH,FIRE,WIND)
typedef struct _CHAR_STS
{
	UINT16		Sts[STAT_TOTAL][VALUE_MAX]; 
	UINT16		Ele[ELEMENT_TOTAL];				// �������� ����.
	UINT16		Atk[ATK_MAX];					// �������� ����.

} CHAR_STS, *PCHAR_STS;

// ����ġ ����
typedef struct _CHAR_EXP
{
	UINT64  uiCurExp;
	UINT64  uiMinExp;
	UINT64  uiMaxExp;

} CHAR_EXP, *PCHAR_EXP;

// ���� ����
typedef struct _MONSTER_INFO
{
	CREATURE_INFO	BaseInfo;
	MOVING_STATUS   MovingStatus;
	int iType;


} MONSTER_INFO,*PMONSTER_INFO;

// NPC ����
typedef struct _NPC_INFO
{
	CREATURE_INFO	BaseInfo;

} NPC_INFO,*PNPC_INFO;

// ĳ���� �⺻ ����
typedef struct _CHARACTER_INFO2
{
	CREATURE_INFO	BaseInfo;
	USERID			uiUserID;					// ������ ���� ID
	UINT32			uiTitleID;					// Ÿ��Ʋ
	UINT64			uiMoney;					// ���ӸӴ�
	UINT8			uiClassType;				// Class Type
	UINT8			uiSex;						// 1: ��, 2: ��
	UINT8			uiWeaponSet;				// 0: 13,14  1:15,16 
	UINT64			uiStorageMoney;				// â��Ӵ�
	MOVING_STATUS	MovingStatus;
	UINT32			Fame[VALUE_MAX];			// ��ġ
	INT32			iGameOptions;				// 2007.02.21 dhpark �������� �����ؾ��� ���ӿɼǵ�

	// �̵�
} CHARACTER_INFO2, *PCHARACTER_INFO2;


// ĳ���� ĳ������ 20080306 mijin
typedef struct _CHARACTER_CASH_INFO
{
	int			iCash;						// 20080306 mijin ĳ��
	int			iMile;						// 20080306 mijin ���ϸ���
	UINT8		uiHotCashShopMode;			// 20080415 mijin ��õ��ǰ ��ŷ ���� (0: close, 1:open)
} CHARACTER_CASH_INFO, *PCHARACTER_CASH_INFO;



// ģ�� ��ϻ��� ĳ���� ����
typedef struct _FRIEND_INFO
{
	TCHAR			szCharName[LEN_NAME+1];
	UINT8			uiClassType;				// ������,...
	UINT8			uiLevel;					// �ش� ĳ������ ���� ����
	UINT16			uiServerID;					// 0(off-line), >1(on-line)
	CHARID			friendCharID;

}FRIEND_INFO,*PFRIEND_INFO;

// ���� ���� ����
typedef struct _TEAMMEMBER_INFO : public CREATURE_INFO
{

}TEAMMEMBER_INFO,*PTEAMMEMBER_INFO;


// ���� ����
typedef struct _STATUS_INFO
{
	CHAR_EXP		ExpInfo;
	CHAR_STS		StsInfo;
	short			iSkillFreePoint;
	short iAmor;					// ����
	short iResEarth;				// ���׷�
	short iResWind;				// ���׷�
	short iResWater;				// ���׷�
	short iResFire;				// ���׷�
	short iReqLv;					// ���ѷ���
	short iProbEnchat;			// ��þƮ ������.
} STATUS_INFO,*PSTATUS_INFO;

// ����Ʈ�� ���Ͽ� ����ɼ� �ִ� ���Ȱ���
typedef struct _EFFECT_STATUS_INFO
{
	UINT16	uiLevel;
	UINT32	uiMHP[VALUE_MAX];					// Base MaxHp, Curr MaxHP
	UINT32	uiMSP[VALUE_MAX];					// Base MaxSp, Curr MaxSP
	UINT32	uiHP;								// NowHP
	UINT32	uiSP;		
	UINT32  uiRHP;
	UINT32  uiRSP;
	UINT32	Fame[VALUE_MAX];
	STATUS_INFO		Status;
	MOVING_STATUS	MovingStatus;
} EFFECT_STATUS_INFO, *PEFFECT_STATUS_INFO;

// ��ġ ����
typedef struct _LT_POSITION
{
	float	fPosX;								// ���� ��ġ
	float	fPosY;			
	float	fVelocityX;							// �ȱ� �ӵ�		ACCUMULATE_PROCESS_TICK����
	float	fVelocityY;							// �������� �ӵ�	ACCUMULATE_PROCESS_TICK����
	float	fAccelX;							// ���ӵ�			ACCUMULATE_PROCESS_TICK����
	float	fAccelY;			
	int		eFacing;							// ���� (FACING)
	int		bgStandLayer;						// ���� ���ִ� �ͷ��� ���̾� (BG_ID)

	bool	bKnockBack;
	bool	bDelay;
	float	fKnockTime;
	float	fDelayTime;
	float	fKnockVelocityX;
	float	fKnockVelocityY;

}LT_POSITION,*PLT_POSITION;

typedef struct _LT_KNOCKBACK
{
	bool	bKnockBack;
	bool	bDelay;
	float	fKnockTime;
	float	fDelayTime;
	float	fKnockVelocityX;
	float	fKnockVelocityY;

}LT_KNOCKBACK,*PLT_KNOCKBACK;

typedef struct _MAP_INFO
{
	 UINT16	uiStageID;			// �������� ID
	 UINT16	uiMapGroupID;		// �ʱ׷� ID
	 UINT16	uiMapID;			// �� ID
}MAP_INFO,*PMAP_INFO;

enum EVENT_TYPE{EVENT_NULL,EVENT_NPC,EVENT_SAVEPOINT,EVENT_PORTAL,EVENT_QUEST,EVENT_MAILBOX,EVENT_BEAUTY,EVENT_CROPS,EVENT_CORE,EVENT_CHATROOMOBJECT,MAX_EVENT};

/**
* ���� NPC �� EVENT ���� ���� <br> 
*/
enum NPC_EVENT_TYPE {
	NPC_EVENT_TYPE_NULL				= 0,	/**< �ƹ��͵� �ƴ� <br> */
	NPC_EVENT_TYPE_TALK				= 1,	/**< ��ȭ <br> */
	NPC_EVENT_TYPE_TRADE			= 2,	/**< ���� <br> */
	NPC_EVENT_TYPE_STORAGE			= 3,	/**< â�� <br> */
	NPC_EVENT_TYPE_QUEST			= 4,	/**< Quest <br> */
	NPC_EVENT_TYPE_GIFT				= 5,	/**< Gift <br> */
	NPC_EVENT_TYPE_GUILD_CREATE		= 6,	/**< ��� ����<br> */
	NPC_EVENT_TYPE_GUILD_DISSOLVE	= 7,	/**< ��� ��ü <br> */
	NPC_EVENT_TYPE_GUILD_ENTER		= 8,	/**< ��� ���� <br> */
	NPC_EVENT_TYPE_PORTAL			= 9, 	/**< NPC�� ���� ��Ż <br> */
	NPC_EVENT_TYPE_CHANGE			= 10,	/**< NPC�� ���� �̺�Ʈ ������ ��ȯ <br> */
	NPC_EVENT_TYPE_GUILD_LEVELUP	= 11,	/**< ��� ���� �� <br> */
	NPC_EVENT_TYPE_GUILD_EMBLEM		= 12,	/**< ��� ���� ���� <br> */	
	NPC_EVENT_TYPE_PVP_RESERVE		= 13,	/**< PVP ���� <br> */
	NPC_EVENT_TYPE_AUCTION			= 14,	/**< ��� <br> */
	NPC_EVENT_TYPE_REOPTION				= 15,	/**< �ɼ� ��й� <br> */ 
	NPC_EVENT_TYPE_PARTY_PVP_RESERVE	= 16,	/**< ��Ƽ PVP ���� <br> */  
	NPC_EVENT_TYPE_RANKING				= 17,
	NPC_EVENT_TYPE_WEDDING_RESERVE		= 18,	/**< ��ȥ NPC�� ���� �� ���� <br> */  
	NPC_EVENT_TYPE_WEDDING_DIVORCE		= 19,	/**< ��ȥ NPC�� ���� ��ȥ <br> */  
};


// �籸���� MapEventInfo�� �� �䱸 ����
typedef struct _REQUIRE_INFO {

	UINT32	requireType;
	UINT32	requireID;
	UINT32	requireValue1;
	UINT32	requireValue2;

	_REQUIRE_INFO(int iType = 0, int iID = 0, int iValue1 = 0, int iValue2 = 0) {		
		SetRequireInfo(iType, iID, iValue1, iValue2);
	}

	void Clear() {
		requireType			= 0;
		requireID			= 0;
		requireValue1		= 0;
		requireValue2		= 0;		
	}

	void SetRequireInfo(int iType, int iID, int iValue1, int iValue2) {
		requireType			= iType;
		requireID			= iID;
		requireValue1		= iValue1;
		requireValue2		= iValue2;
	}

}REQUIRE_INFO;

typedef struct _EVENT_INFO
{
	UINT32		id; // EventID

	// position
	MAP_INFO	mapInfo	;
	float		posX;
	float		posY;

	_EVENT_INFO()
	{
		id						= 0;

		ZeroMemory(&mapInfo,sizeof(MAP_INFO));
		posX					= 0.0;
		posY					= 0.0;
	}

} EVENT_INFO, *PEVENT_INFO;


// MapEvent Info�� �籸��
typedef struct _MAPEVENT_INFO 
{
	UINT32	classID;				// AVATAR_MAPEVENT_*
	UINT32	instanceID;
	UINT32	id;

	MAP_INFO mapInfo;
	float	posX;
	float	posY;
	float	rectTop;
	float	rectLeft;
	float	rectRight;
	float	rectBottom;

	UINT8	eventType;
	UINT32	eventSubType;	
	UINT32	eventTypeID;

	UINT32	obejctImage;
	UINT8	iTerrainLayer;
	UINT8	iFacing;	

	REQUIRE_INFO	requireInfo[2];	

	// ������ �Ҹ� ����( ��Ż�̺�Ʈ�ø� �̿�:��ȹ���ǵ� ) 2007/01/19 
	ITEMID			iConsumeItemID;

	TCHAR name[LEN_NAME+1];	
	TCHAR tipMessage[512];
	TCHAR errorMessage[512];
	TCHAR tipMessageOff[512];
	TCHAR dummy[3];	

	UINT32	iInsDungeunID;
	UINT8	byDynamicCreate;
	UINT	iDynamicFX ;

	_MAPEVENT_INFO() {
		Clear();
	}

	void Clear() {
		classID					= 0;
		instanceID				= 0;
		id						= 0;

		//stageID				= 0;
		//mapGroupID			= 0;
		//mapID					= 0;
		//mapInfo.Clear();
		ZeroMemory(&mapInfo, sizeof(MAP_INFO));

		posX					= 0;
		posY					= 0;
		rectTop					= 0;
		rectLeft				= 0;
		rectRight				= 0;
		rectBottom				= 0;

		eventType				= 0;
		eventSubType			= 0;
		eventTypeID				= 0;

		obejctImage				= 0;
		iTerrainLayer			= 0;
		iFacing					= 0;

		iConsumeItemID			= 0;

		requireInfo[0].Clear();
		requireInfo[1].Clear();

		ZeroMemory(name, LEN_NAME + 1);
		ZeroMemory(tipMessage, 512);
		ZeroMemory(errorMessage, 512);
		ZeroMemory(tipMessageOff, 512);

		iInsDungeunID			= 0;
		byDynamicCreate			= 0;
		iDynamicFX				= 0;
	}

	void SetEventInfo(EVENT_INFO* srcEventInfo) {
		id = srcEventInfo->id;
		mapInfo = srcEventInfo->mapInfo;
		posX = srcEventInfo->posX;
		posY = srcEventInfo->posY;
	}

}MAPEVENT_INFO;

// 4byte ����
enum STATUS_TYPE 
{
	STATUS_NONE=0,
	STATUS_LV,
	STATUS_LUK_BASE,					// �������� ä��â�� ǥ�õǴ¹����� ���� ����!!!! [2/6/2006 AJJIYA]
	STATUS_ATK_BASE,					// �������� ä��â�� ǥ�õǴ¹����� ���� ����!!!! [2/6/2006 AJJIYA]
	STATUS_DEF_BASE,					// �������� ä��â�� ǥ�õǴ¹����� ���� ����!!!! [2/6/2006 AJJIYA]
	STATUS_ELE_BASE,					// �������� ä��â�� ǥ�õǴ¹����� ���� ����!!!! [2/6/2006 AJJIYA]
	STATUS_MHP_BASE,
	STATUS_MSP_BASE,
	STATUS_FAME_BASE,
	STATUS_LUK, 						// ������
	STATUS_ATK,  						// ������
	STATUS_DEF,	 						// ������
	STATUS_ELE,  						// ������
	STATUS_MHP,  						// ����
	STATUS_MSP,							// ������
	STATUS_HP,  						// ������
	STATUS_SP,							// ���縶��
	STATUS_FAME,
	STATUS_CLASS_TYPE,
	STATUS_PVP_LV,						// PVP Rank Level
	STATUS_PVP_POINT,					// PVP �ŷ� ����Ʈ
	STATUS_EARTH,
	STATUS_WIND,
	STATUS_WATER,
	STATUS_FIRE,
	STATUS_NORMAL_ATK, 
	STATUS_HEAVY_ATK,
	STATUS_RECOVERY_HP,
	STATUS_RECOVERY_SP,
	STATUS_SKILL_POINT,
	STATUS_GENDER,
	STATUS_AMOR,						// ����
	STATUS_RES_EARTH,					// ���׷�
	STATUS_RES_WIND,					// ���׷�
	STATUS_RES_WATER,					// ���׷�
	STATUS_RES_FIRE,					// ���׷�
	STATUS_REQ_LV,						// ���ѷ�������
	STATUS_PROB_ENCHANT,				// ��þƮ ����Ȯ������.		
	STATUS_CASH,						//20080310 mijin ĳ��(����)
	STATUS_MILE,						//20080310 mijin ���ϸ���
	STATUS_PHYCRI,						// ����ũ��
	STATUS_ELECRI,						// ����ũ��
	STATUS_PHYDODGE,					// ����ȸ��
	STATUS_ELEDODGE,					// ����ȸ��
	STATUS_PHYHITRATE,					// ��������
	STATUS_ELEHITRATE,
	STATUS_LOVE_LV,						// ���� Level
	STATUS_LOVE_POINT,					// ���� ����Ʈ ���簪 [10/2/2008 AJJIYA]
	STATUS_LOVE_POINT_MAX,				// ���� ����Ʈ �ִ밪 [10/2/2008 AJJIYA]
	STATUS_LOVE_DAY,					// ���� ���� �� �� [10/2/2008 AJJIYA]
	STATUS_LOVE_STATE,					// ���� ���� ( 0 : None , 1 : �������� , 2 : �������� �Ϸ� ���� , 4 : ��ȥ���� ) [10/2/2008 AJJIYA]
	STATUS_MOB_COUNT,					// ��ȯ�� ������
	STATUS_EXTENDED_CHARSLOT,			// Ȯ��� ĳ���� ���Լ�
	STATUS_RANKING_LEVEL,				// ��ŷ�ý��� : ������ŷ
	STATUS_RANKING_PVP,					// ��ŷ�ý��� : PVP
	STATUS_RANKING_LOVE,				// ��ŷ�ý��� : ������
	STATUS_RANKING_GUILD,				// ��ŷ�ý��� : ���
	MAX_STATUS
};

// �⺻ 8BYTE ����.
enum STATUS_EX_TYPE		
{
	STATUS_EX_NONE = 0,
	STATUS_EX_EXP,
	STATUS_EX_EXP_MAX,
	STATUS_EX_EXP_MIN,
	STATUS_EX_ELY,
	STATUS_EX_STORAGE_ELY,				//[2005/7/20]
	STATUS_EX_PVP_GLORY,				//[2007/11/27]	PVP �� ����Ʈ
	MAX_STATUS_EX,		
};

typedef struct _STATUS_CHANGE
{
	UINT16				eType;			// enum STATUS_TYPE 
	UINT32				uiValue;		// value;
} STATUS_CHANGE, *PSTATUS_CHANGE;

typedef struct _STATUS_CHANGE_EX
{
	UINT8				eType;			// enum STATUS_EX_TYPE
	UINT64				uiValue;		// value;
}STATUS_CHANGE_EX, *PSTATUS_CHANGE_EX;



// PC's mode
enum PC_MODE {PM_NONE=0,
		PM_INITIALIZING,				// �ʱ�ȭ��.
		PM_CHAR_MANAGING,				// ĳ���� ����/����/���� ��
		PM_PALYING,						// ������
		PM_EXITING,						// ���� ������
		MAX_PM};

// ���庰 ĳ���ͼ� ����
//typedef struct _WORLD_INFO
//{
//	WORLD_ID	wid;
//	TCHAR		name[LEN_NAME];
//	TCHAR		ip[LEN_IP];
//	SERVER_PORT	port;
//	int			nCharCount;
//	float		fStatusValue;			// ���峻 �ѵ�����/�ִ����Ӱ��ɼ�
//}WORLD_INFO;
//
//typedef struct _CHANNEL_INFO
//{
//	SERVER_ID	uiChannelID;
//	UINT16		uiMaxUsers;
//	UINT16		uiCurUsers;
//	//float		fStatusValue;			// ä�γ� ������/�ִ밡�ɼ�
//}CHANNEL_INFO,*PCHANNEL_INFO;

// ���庰 ĳ���ͼ� ����
typedef struct _WORLD_INFO
{
	UINT16		wid;
	TCHAR		name[LEN_NAME];
	SERVER_ID	usLobbySID;
	TCHAR		ip[LEN_IP];
	UINT16		port;
	UINT8		nCharCount;
	UINT8		status;					// ����(0),����(1),ȥ��(2)
}WORLD_INFO;

typedef struct _CHANNEL_INFO
{ 
	UINT16		channelID;
	TCHAR		name[LEN_NAME];
	UINT8		status;					// ����(0),����(1),ȥ��(2),���ӺҰ�(3)
}CHANNEL_INFO;


// ä�� �޼����� ������ ������ ����
// ä���� �߰��� LDT���� �ش�κ� �����Ǿ� �����Ƿ� ���� ���� ���� ��Ź�帳�ϴ�. [4/23/2007 AJJIYA]
enum BROADCAST_SCOPE 
{
	SCOPE_BROADCAST			=	0		,
	SCOPE_AROUNDREGION					,			// ��ó(��ε�ĳ���� ������) PC			: ä�γ�
	SCOPE_FRIENDLIST					,			// ģ�� ��ϻ��� ��� ����				: ���� ä�γ��� ����
	SCOPE_GUILD							,			// ���ä��								: ���峻 ������
	SCOPE_TEAM							,			// ��									: ���� ä�γ��� ����
	SCOPE_WHISPER						,			// Ư�� ����(�ӼӸ�)					: ���峻�� ����
	SCOPE_BUGLE							,
	
	SCOPE_CHANNEL			=	1001	,			// Ư�� ä�γ��� ��� ����				: ä�γ�
	SCOPE_WORLD				=	1002	,			// Ư�� ���峻�� ��� ����				: ���峻
	SCOPE_CHATROOM_ADVERT	=	1003	,			// ��ȭ�� ������ ���峻�� ��� ������ ������� �ϴ� ���� �޼���
	SCOPE_WEDDING			=	1004	,			// ��ȥ�� ���峻�� ����������� ����

	SCOPE_NOTICE			=	2001	,			// ��������. Ư�� ���峻�� ��� ����(GM Only)	: ���峻
	SCOPE_SYSTEMMSG			=	2002	,			// �ý��� �޼��� ���ۿ�(cheat ���,����/��� �޼���,...)
};

//////////////////////////////////////////////////////////////////////////
// Item Structure
enum CONTAINER_TYPE
{
	CONTAINER_TYPE_INVALID = -1,
	INVENTORY_EQUIP=0,
	INVENTORY_CONSUME,
	INVENTORY_ETC,
	INVENTORY_EVENT,
	INVENTORY_PET,
	INVENTORY_HOUSING,
	FIGURE_EQUIP,
	FIGURE_FASHION,
	FIGURE_BASIC,
	STORAGE,
	INVENTORY_CASH,
	FIGURE_PET,
	INVENTORY_WEAR,        //[xialin 2008/07/21] add �Դ���¼
	FIGURE_EFFECT,
	CONTAINER_MAX,
	CONTAINER_AUCTION = 88,
	CONTAINER_MAILBOX = 99,
};

// Packet�� 

/*-------------------------------------------------*/

// ĳ������ �⺻ ���� ����

/*-------------------------------------------------*/

enum FIGURE_BASIC_TYPE
{
	FIGURE_BASIC_NULL,
	FIGURE_BASIC_UNDER_SHIRT, // �ӿ� ����
	FIGURE_BASIC_UNDER_PANTS, // �ӿ� ����
	FIGURE_BASIC_HAIR,
	FIGURE_BASIC_FACE,
	FIGURE_BASIC_SKIN,
	FIGURE_BASIC_MAX,
};

/*-------------------------------------------------*/

// �м�â ���Թ�ȣ

/*-------------------------------------------------*/

enum EQUIP_SLOT_NUMBER
{
	EQUIP_SLOT_NULL,
	EQUIP_SLOT_HEAD,		// �Ӹ�
	EQUIP_SLOT_FACE1,		// �Ȱ�
	EQUIP_SLOT_EARRING,		// �Ͱ���
	EQUIP_SLOT_SHIRT,		// ����
	EQUIP_SLOT_PANTS,		// ����
	EQUIP_SLOT_MANTLE,		// ����
	EQUIP_SLOT_GLOVE,		// �尩
	EQUIP_SLOT_SHOES,		// �Ź�
	EQUIP_SLOT_LEG,			// �ٸ�
	EQUIP_SLOT_FACE2,		// �󱼿� ���¾Ǽ�����
	EQUIP_SLOT_STONE,		// ���ɼ�		
	EQUIP_SLOT_RING,		// ����	
	EQUIP_SLOT_WEAPON1,
	EQUIP_SLOT_BUCKLER1,
	EQUIP_SLOT_WEAPON2,
	EQUIP_SLOT_BUCKLER2,
	EQUIP_SLOT_MAX,
};

/*-------------------------------------------------*/

// �м�â ���Թ�ȣ

/*-------------------------------------------------*/
enum FASHION_SLOT_NUMBER
{
	FASHION_SLOT_NULL,
	FASHION_SLOT_HEAD,			// �Ӹ�
	FASHION_SLOT_FACE1,			// �󱼿� �ϴ� ������
	FASHION_SLOT_EARRING,		// �Ͱ���
	FASHION_SLOT_SHIRT,			// ����
	FASHION_SLOT_PANTS,			// ����
	FASHION_SLOT_MANTLE,		// ����
	FASHION_SLOT_GLOVE,			// �尩
	FASHION_SLOT_SHOES,			// �Ź�
	FASHION_SLOT_LEG,			// �ٸ�
	FASHION_SLOT_FACE2,			// �󱼿� �ϴ� ������
	FASHION_SLOT_STONE,			// ���ɼ�
	FASHION_SLOT_RING,			// ����
	FASHION_SLOT_MAX
};

//--------------------------------------------------
// effect slot number
enum EFFECT_SLOT_NUMBER
{
	EFFECT_SLOT_NULL,

	EFFECT_SLOT_HEAD,		// �Ӹ�
	EFFECT_SLOT_FACE1,		// �Ȱ�
	EFFECT_SLOT_EARRING,	// �Ͱ���
	EFFECT_SLOT_SHIRT,		// ����
	EFFECT_SLOT_PANTS,		// ����
	EFFECT_SLOT_MANTLE,		// ����
	EFFECT_SLOT_GLOVE,		// �尩
	EFFECT_SLOT_SHOES,		// �Ź�
	EFFECT_SLOT_LEG,		// �ٸ�
	EFFECT_SLOT_FACE2,		// �󱼿� ���¾Ǽ�����
	EFFECT_SLOT_STONE,		// ���ɼ�		
	EFFECT_SLOT_RING,		// ����	

	EFFECT_SLOT_FORCEENUMMAX
};
//--------------------------------------------------

/*-------------------------------------------------*/

// ��â ���Թ�ȣ

/*-------------------------------------------------*/
enum PET_SLOT_NUMBER
{
	PET_SLOT_NULL,
	PET_SLOT_PRIMARY,				// ������
	PET_SLOT_SECONDARY,
	PET_SLOT_TERTIARY,
	PET_SLOT_MAX
};

enum PET_PLACE
{
	PET_PLACE_NULL = -1,
	PET_PRIMARY,
	PET_SECONDARY,
	PET_TERTIARY,

	PET_PLACE_TYPE_NUMBER
};

//typedef UINT32	DUABILITY;	// ������
typedef UINT32	DURATION;	// ���ӽð� 
typedef UINT32	MOBID;

// �����̳� ���� ����
typedef struct _CONTAINER_SLOT
{
	CONTAINER_TYPE	ContainerType;
	SLOT_INDEX		SlotIndex;

} CONTAINER_SLOT, *PCONTAINER_SLOT;

typedef struct _CHAR_FIGURE
{
	ITEMID FIGURE[FIGURE_BASIC_MAX];
}CHAR_FIGURE,*PCHAR_FIGURE;

// pc Container ����
typedef struct _CONTAINER_SLOT_INFO
{
	CONTAINER_TYPE ContainerType;
	UINT8		   iContainerSlot;
	UINT8		   iOptionalSlot;
} CONTAINER_SLOT_INFO;

#define MAX_ITEM_OPT 5

typedef struct _PACK_OPT
{
	short iID;
	short iValue;
} PACK_OPT, *PPACK_OPT;

typedef struct _ITEM
{
	ITEMID		iItemID;			// ������ ���̵�
	UINT8		iStackCount;		// ������ ����
	int			iLifeTime;			// ���� Ÿ���̹Ƿ� ���� ���� �ü� ����. DB �� ��������.
	UINT8		iRare;				// ���
	PACK_OPT	Opt[MAX_ITEM_OPT];	// �ɼ�
	ITEMNO		iItemNo;
	int			iBackPrice;		// 
	short		iOptPoint;
	INT64		iItemExp;			// �����۰���ġ
	INT16		iItemSP;			// ������SP
} ITEM, *PITEM;

// ������ ������ sizeof(CONTAINER_ITEM) => 56
typedef struct _CONTAINER_ITEM
{
	CONTAINER_SLOT	SlotInfo;
	ITEM			Item;		// Item Object
} CONTAINER_ITEM, *PCONTAINER_ITEM;

// ���������� �ѷ��ִ� ������ (�ַ� ��ε��ɽ�Ʈ��...)
typedef struct _FIGURE_ITEM
{
	CONTAINER_SLOT  SlotInfo;
	ITEMID			iItemID;	// Item ID --> �����ͼ� �ش� ID�� ã�Ƽ� �ѷ��ش�.

}FIGURE_ITEM, *PFIGURE_ITEM;


typedef struct _LOOTING_ITEM
{
	SLOT_INDEX iSlotIndex;
	ITEMID	   iItemID;    // ������.
} LOOTING_ITEM, *PLOOTING_ITEM;

typedef struct _TRASH_ITEM
{
	CONTAINER_SLOT	iContainerSlot;
	UINT8			iCount;
} TRASH_ITEM, *PTRASH_ITEM;

typedef struct _CHANGE_SLOT
{
	CONTAINER_SLOT	SrcSlotInfo;
	UINT8			iCount;
	CONTAINER_SLOT	DestSlotInfo;
} CHANGE_SLOT, *PCHANGE_SLOT;

// Ʈ���̵� ������â�� �������� �ø��� ����ϴ� ����ü
typedef struct _TRADE_ITEM
{
	CONTAINER_SLOT	stActSlotInfo;
	SLOT_INDEX		TradeSlotIndex;

} TRADE_ITEM, *PTRADE_ITEM;

// ������ ������Ÿ�� ����ü
typedef struct _ITEM_LIFETIME
{
	CONTAINER_SLOT	stSlotInfo;
	int				iLifeTime;

} ITEM_LIFETIME, *PITEM_LIFETIME;

// ������ ����ġ ����ü
typedef struct _ITEM_EXP
{
	CONTAINER_SLOT	stSlotInfo;
	INT64			iItemExp;

} ITEM_EXP, *PITEM_EXP;

// ������ SP ����ü
typedef struct _ITEM_SP
{
	CONTAINER_SLOT	stSlotInfo;
	INT16			sItemSP;

} ITEM_SP, *PITEM_SP;

// Upgrade���� �̿�Ǵ�

typedef struct _MATERIAL_DATA
{
	CONTAINER_TYPE	iContainerType;		// ��� ������ ��ġ  
	UINT8			iContainerSlot;		// ��� ������ ��ġ
	ITEMNO			iItemNo;			// ��� ������ ��ȣ
	UINT8			iItemCount;			// -- ������
} MATERIAL_DATA, *PMATERIAL_DATA;

typedef struct _EFFECT_DATA
{
	unsigned int iInstanceID;
	int iEffectID;
	UINT8 iEffectLv;
	int iRemainTime; // ���� :0.1��
	GU_ID iCasterID;
} EFFECT_DATA, *PEFFECT_DATA;

// mijin ��Ÿ�� ����ü
typedef struct _COOLTIME_DATA
{
	int iCoolTimeID;
	int	iMaxCoolTime;	// ó�� ����� ��Ÿ�� ( ���� : �� )
	int iApplyCoolTime; // ���� ��Ÿ�� ( ���� : �� )

} COOLTIME_DATA, *PCOOLTIME_DATA;


// QUICK SLOT
enum QUICK_LINK_FLAG
{
	QUIKC_LINK_FLAG_INVALID = 0,
	QUICK_LINK_FLAG_ITEM,
	QUICK_LINK_FLAG_ACTION,
	QUICK_LINK_FLAG_SKILL,
	QUICK_LINK_FLAG_ITEMSKILL,
	QUICK_LINK_FLAG_CHAT,
	QUICK_LINK_FLAG_PETSKILL,
};

typedef struct _LINKED_DATA
{
	UINT8	iFlag;			/* QUICK_SLOT_FLAG */
	int		iObjTypeID;		/* ItemID, SkilllID, ActionID */
	int		iSubTypeID;		/* ItemID */ // �����۽�ų����� ���

}LINKED_DATA, *PLINKED_DATA;

typedef struct _QUICK_SLOT 
{
	LINKED_DATA LinkedData;
	UINT8		iSlotIndex; /* Quick slot position */ // Valid Range : 0~MAX_QUICK_SLOT -1 
} QUICK_SLOT, *PQUICK_SLOT;

#define START_EMOTICON_SLOT	36	// 2005.08.30 dhpark �̸�Ƽ�� ���� �ε��� ����

#define MAX_QUICKSLOT_DATAPERTAB	12
#define MAX_QUICKSLOT_TAB			4
#define MAX_QUICK_SLOT				MAX_QUICKSLOT_DATAPERTAB * MAX_QUICKSLOT_TAB


//////////////////////////////////////////////////////////////////////////
//
//	Npc section
//

#define MAX_NPC_TRADE_ITEM			50
#define MAX_LOOT_ITEM				3
#define MAX_LOOT_ITEM_SET			7
#define MAX_MOB_LOOT_ITEM			(MAX_LOOT_ITEM + MAX_LOOT_ITEM_SET)





//  ��ġ�� �ָ��ؼ� �ӽ÷� ..

//////////////////////////////////////////////////////////////////////////
//
// npc�κ��� �춧 �̿�
//
//////////////////////////////////////////////////////////////////////////
//
// �Ķ���� ����
// ItemPrice : ����� �ϴ� �������� "ITEM.LDT"�� "_GamePrice".
// ItemCount : NPC ���� �� ������ ����.
// ShopSellPercent : "NPC_TRADE.LDT"�� �ش� ������ "_SellFactor". 
// PCBuyPercent : PC���� ����� ���Թ���. ����� �⺻ 100 % �� �Է¿��. 

#define GET_BUY_PRICE(ItemPrice,ItemCnt,ShopSellPercent,PCBuyPercent) \
	(ItemPrice*ShopSellPercent/100*PCBuyPercent/100*ItemCnt)

//////////////////////////////////////////////////////////////////////////
//
// NPC���� �ȶ� �̿�
//
// ItemPrice : �Ȱ����ϴ� �������� "ITEM.LDT"�� "_GamePrice".
// ItemCount : NPC ���� �� ������ ����.
// ShopBuyPercent : "NPC_TRADE.LDT"�� "_BuyFactor". 
// PCSellPercent : PC���� ����� �ǸŹ���. ����� �⺻ 100 % �� �Է¿��. 
// 					

#define GET_SELL_PRICE(ItemPrice,ItemCnt,ShopBuyPercent,PCSellPercent) \
	(ItemPrice*ItemCnt*ShopBuyPercent/100*PCSellPercent/100)


//////////////////////////////////////////////////////////////////////////
//
// ������ ĳ�� �ŷ��� ������ ���
// 20080313 mijin
//	- �ŷ������ �Ҽ��� ���ϴ� ����
//
// TradeCash : �ŷ��Ǵ� ĳ��
// CommPercent : ������ �ۼ�Ʈ(LOCALIZE.LDT �� ǥ��)
//////////////////////////////////////////////////////////////////////////					
#define GET_TRADE_CASH_COMM(TradeCash, CommPercent) (TradeCash*CommPercent/100)




// 2005.07.28 dhpark Trade�� �Ÿ����� Define
const float CHECK_INTERVAL_X = 400.0f;			/**< ��� PC�� �� �Ÿ� üũ�� <br> */
const float CHECK_INTERVAL_Y = 300.0f;			/**< ��� PC�� �� �Ÿ� üũ�� <br> */

//------------------------------------------------------------------------------
// QUEST

#define QUEST_MAX_ACTIVE				15	// �������� ����Ʈ�� �ִ� ����
#define QUEST_MAX_NAME					64	// LDT�� ������ txt�� ũ�������
#define QUEST_MAX_REQUIRE				5	/**< ���濡 �ʿ��� ���� ������ �ִ� ���� <br> */
#define QUEST_MAX_ACQUISITION_EFFECTID	5	/**< ����Ʈ ����� �Բ� �߻��ϴ� ȿ���� �ִ� ���� <br> */
#define QUEST_MAX_ACQUISITION_ITEM		2	/**< ����Ʈ ����� �Բ� �����ϴ� ������ �ִ� ���� <br> */
#define QUEST_MAX_MISSION				4	/**< �Ϸῡ �ʿ��� �̼��� ���� <br> */
#define QUEST_MAX_CONSUMPTION_ITEM		5	/**< ����Ʈ �Ϸ�(����)�� �Һ�Ǵ� ������ ������ �ִ� ���� <br> */
#define QUEST_MAX_RANK					3	// ��ũ�� ��
#define QUEST_MAX_RANK_REQUIRE			2	// ��ũ�� �����ϴ� ������ ��
#define QUEST_MAX_REWARD				3	// ��ũ���� �����Ҽ��ִ� ������ ��
#define QUEST_MAX_DIVIDE_ITEM			5	// �Ϸ�� ������ ������ �������� ���ҵɼ��ִ� �ִ�� -- �˻��Ģ:1.���Ժ� ���ü��� �����Ǿ���� ���ü��� �Ѵ°��� �ִ��� �˻�. 2.�տ��� �ټ����� ������ �������� ���ü��� ���� �����Ǿ���� ���ü��� �Ѵ��� �˻�. ������ ���� Mission failed...
#define MAX_ITEM_UPGRADE_MATERIALS		4

#define QUESTREWARD_MAX_EFFECTID		4	// ���� ����Ʈ�� ��
#define QUESTREWARD_MAX_ITEM			6	// ���� �������� ��

typedef enum _enumQUEST_ACCEPTTYPE	// ����Ÿ��
{
	QUEST_ACCEPTTYPE_NPC = 1,
	QUEST_ACCEPTTYPE_SHARE = 2,
	QUEST_ACCEPTTYPE_ITEM = 4,
	QUEST_ACCEPTTYPE_EVENT = 8,

} QUEST_ACCEPTTYPE;

typedef enum _enumREWARD_TYPE	// ����Ÿ��
{
	REWARD_TYPE_FIX = 1,
	REWARD_TYPE_RANDOM,
	REWARD_TYPE_SELECT,

} REWARD_TYPE;

typedef enum _enumQUEST_STATUS
{
	QUEST_STATUS_ACTIVE = 0,
	QUEST_STATUS_FINISH = 1,
	QUEST_STATUS_MAX	= 2,		//[2006/4/3] - jinhee

} QUEST_STATUS;

typedef enum _enumMISSION_TYPE
{
	MISSION_TYPE_NULL = 0,			//[2005/9/21] - jinhee
	MISSION_TYPE_MONSTER = 1,
	MISSION_TYPE_EVENT,
	MISSION_TYPE_ITEM,
	MISSION_TYPE_ACTION,

} MISSION_TYPE;

typedef struct _tagQUEST
{
	UINT32		uiQuestID;		// ����Ʈ���̵�
	int			iFinishCnt;		// �Ϸ��� Ƚ��
	UINT8		uiStatus;		// 0:�Ϸ�, 1:������

} QUEST, *PQUEST;

typedef struct _FESTIVAL
{
	int		iAppliedLoginEvent;
	time_t	tmLastLoginTime;
} FESTIVAL, *PFESTIVAL;

typedef struct _tagMISSION
{
	UINT8		uiMissionType;	// �̼�Ÿ��(0:NULL, 1:Monster, 2:Event, 3:Item, 4:Action)
	UINT32		uiValueID;		// �̼��� ����� ���̵�(�̼�Ÿ���� Monster�϶��� MonsterID)
	int			iFinishValue;	// �Ϸᰪ
	int			iCurValue;		// ���簪

} MISSION, *PMISSION;

#define CASHSHOP_ERROR_NOT_OPENED 9009006 //9000004 // ĳ������ �ӽ÷� ���� ���
#define CASHSHOP_ERROR_FAIL 4000020   // osp ���� �������� ���µ� ������ ������ ������ ���.
#define DEFAULT_ERROR_ID		4000002		// ���������� ������ �ʿ䰡 ���ų� ���������� �����ְ� ������ ����ϴ� �۷ι���Ʈ���� �������̵��Դϴ�. ������ ������ �� �۾��� �Ҽ����ٴ� ���������ϰ����� ����˴ϴ�.(����� ������� ���Ұ���)
#define DEFAULT_ERROR_ID_TARGET	4000003		// ���������� ������ �ʿ䰡 ���ų� ���������� �����ְ� ������ ����ϴ� �۷ι���Ʈ���� �������̵��Դϴ�. ������ ������ ������ �� �۾��� �Ҽ����ٴ� ���������ϰ����� ����˴ϴ�.(����� ������� ���Ұ���)
#define DEFAULT_ERROR_USERIN	30003		// �ߺ��α��ΰ˻�� ����.
#define DEFAULT_ERROR_FAIL_BY_BATTLE	4008001 // ��Ʋ�϶� ����.// ĳ���� ä���̵�

// Auction ������ ����
//
//��ǰ�� �������� ���� �� 	Ȯ��	52000009
//�������� �������� ���� �� 	Ȯ��	52000074
//��ȸ �������� ���ؼ� ���� ������ ���� ���� �� 	Ȯ��	52000073
//���� �� �ٸ� ������ ���ؼ� ������ ���صǴ� ������ ������ ��(��� ���, ��ȸ ����, ��� ����)	Ȯ��	52000080

#define AUCTION_ERROR_NOT_OPENED 52000075  // ��ż����� ���µ��� ���� ���
#define AUCTION_ERROR_BLOCKED	52000080	// ��Ź����� ���Ȱ��
#define AUCTION_ERROR_BIDPRICE  52000073 // �������� ���� ������
#define AUCTION_ERROR_NOT_EXIST 52000009 // ��Ź��� �ȷȰų� ��ҵǼ� ������ ���
#define AUCTION_ERROR_EXPIRED   52000108 // ��Ź����� �����Ȱ��(����/�ﱸ/���) �Ұ���
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Team

#define TEAM_MAX_MEMBER		4
#define TEAM_MIN_MEMBER		2

enum
{
	TEAM_GRADE_NONE = 0,	// ����
	TEAM_GRADE_CAPTAIN,		// ����
	TEAM_GRADE_MAX,			// MAX
};

enum
{
	TEAM_LOOT_ORDER = 0,	// ���ʴ��
	TEAM_LOOT_RANDOM,		// ����
	TEAM_LOOT_FREE,			// ����
	TEAM_LOOT_MAX,			// MAX
};

typedef struct _tagTEAM_MEMBER
{
	GU_ID	CharGUID;
	UINT8	byGrade;	// ���(0:����, 1:����)
	short	sLv;
	UINT8	byClass;
	char	szCharName[LEN_NAME+1];
	UINT32	uiMaxHP;
	UINT32	uiHP;
	UINT32	uiMaxSP;
	UINT32	uiSP;
	UINT16	usStageID;
	UINT16	usMapGroupID;
	float	fPosX;
	float	fPosY;
	UINT8	byWhere;	// 0:�Ϲ��������, 1:ĳ����
#if defined(__ADD_WORLDTEAM) || ( !defined(_CHANNEL_TEAM_VERSION_) && defined(_LATALE_CLIENT) )
	INT32	iCharID;	// ĳ���� DBŰ
	UINT16	wServerID;	// �������̵�
#endif

} TEAM_MEMBER, *PTEAM_MEMBER;

#define TEAM_DIST_X		800.0f
#define TEAM_DIST_Y		600.0f

// Team
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Title

#define TITLE_ID_NOTUSE					1	// �������� ����ϴ� Ű��
#define TITLE_MAX_NAME					64	// LDT�� ������ txt�� ũ�������
#define TITLE_MAX_STATUS				4
#define TITLE_MAX_EFFECTID				4

// Title
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// FreeMarket

#define FM_MAX_NAME			24
#define FM_MIN_NAME			2
#define FM_MIN_PRICE		1
#define FM_MAX_SELLITEM		16
#define FM_BASE_SELLITEM	4
#define FM_OTHER_DISTANCE_X	100.0f
#define FM_OTHER_DISTANCE_Y	100.0f

typedef struct _tagFM_ITEM
{
	UINT8			bySlot;
	ITEMID			uiItemID;
	UINT8			byStackCount;
	UINT64			uiPrice;

} FM_ITEM, *PFM_ITEM;

typedef struct _tagFM_SELLITEM
{
	FM_ITEM			stFM_Item;
	CONTAINER_SLOT	stInvenSlotInfo;

} FM_SELLITEM, *PFM_SELLITEM;

typedef struct _tagFM_VIEWITEM
{
	FM_ITEM			stFM_Item;
	ITEM			stItem;						// �����ۿ� ���� �������� �����༭ ���콺�� �����ۿ� ��ġ��Ű�� ������ �����ټ��ֵ�����

} FM_VIEWITEM, *PFM_VIEWITEM;

// FreeMarket
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// CashShop

#define CASHSHOP_MAX_WISH				6

// CashShop
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// WayPoint

#define WAYPOINT_SIZE_BIT					128	// ��Ʈ�� ������ �������� �� *** PacketID.h�� �̻翹��
#define WAYPOINT_SIZE_DATA					4	// ��Ʈ�� �����ϱ� ���� long�� �������� �� *** PacketID.h�� �̻翹��
#define WAYPOINT_MAX_NAME					64	// LDT�� ������ txt�� ũ�������
#define WAYPOINT_MAX_RANK					2	// ��ũ�� ��
#define WAYPOINT_MAX_RANK_REQUIRE			2	// ��ũ�� �����ϴ� ������ ��
#define WAYPOINT_MAX_DIVIDE_ITEM			5	// �Ϸ�� ������ ������ �������� ���ҵɼ��ִ� �ִ�� -- �˻��Ģ:1.���Ժ� ���ü��� �����Ǿ���� ���ü��� �Ѵ°��� �ִ��� �˻�. 2.�տ��� �ټ����� ������ �������� ���ü��� ���� �����Ǿ���� ���ü��� �Ѵ��� �˻�. ������ ���� Mission failed...
#define WAYPOINT_MAX_FIND_EFFECTID			2	// ù�߽߰� ����Ʈ ��
#define WAYPOINT_MAX_CONSUMPTION_ITEM		1	// ������������ �ִ��

#define DISTANCE_DEFAULT_X				800.0f	// �Ϲ����� �Ÿ��˻�� ����Ұ���
#define DISTANCE_DEFAULT_Y				600.0f	// �Ϲ����� �Ÿ��˻�� ����Ұ���

// WayPoint
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Event Mission

#define MAX_EVENT_MISSION_BIT			1024	// ��Ʈ�� ������ �������� �� *** PacketID.h�� �̻翹��
#define MAX_EVENT_MISSION_REQUIRES		8
#define MAX_EVENT_MISSION_EFFECT		4
#define	MAX_EVENT_MISSION_ITEM			2

const int MAX_EVENT_MISSION_DATA		= 32;// ( MAX_EVENT_MISSION_BIT / 32);	// ��Ʈ�� �����ϱ� ���� long�� �������� �� *** PacketID.h�� �̻翹��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Ŭ���� ����

#define MAX_CLASS_CHANGE_REQUIRES		8
#define	MAX_CLASS_CHANGE_ITEM			4

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ItemAddTime

#define ITEMADDTIME_MAX_REQUIRE				4			// ������ ��
#define ITEMADDTIME_MAX_ADDTIME				2100000000	// �ð����������� �������ִ� �ý����� �ִ밪 �� 66��

// ItemAddTime
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �����ֱ�

#define ITEM_MAX_ITEMSP						100			// ������ �ִ� SP

// ItemAddTime
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Gameble

#define MAX_GAMBLE_REWARD			30
#define MAX_GAMBLE_BETTING		3   
#define MAX_GAMBLE_MATERIALS		2
#define MAX_GAMBLE_REWARD_BIT		MAX_GAMBLE_REWARD	// ��Ʈ�� ������ �������� �� 
//const int MAX_GAMBLE_REWARD_DATA	= 1;//( MAX_GAMBLE_REWARD_BIT / 32);	// ��Ʈ�� �����ϱ� ���� long�� �������� �� *** PacketID.h�� �̻翹��
//------------------------------------------------------------------------------

// Auction
// ��Űŷ�Ÿ��
enum AUCTION_TYPE
{
	AUCTION_TYPE_NULL,
	AUCTION_TYPE_ITEM_BY_ELY,	// �Ǹ� : ������,	���ż��� : Ely
	AUCTION_TYPE_CASH_BY_ELY,	// �Ǹ� : Cash,		���ż��� : Ely
	AUCTION_TYPE_MILEAGE_BY_ELY,// �Ǹ� : Mileage,	���ż��� : Ely
	AUCTION_TYPE_ELY_BY_CASH,	// �Ǹ� : Ely,		���ż��� : Cash
	AUCTION_TYPE_ELY_BY_MILEAGE,// �Ǹ� : Ely,		���ż��� : Mileage
	AUCTION_TYPE_MAX,
};

//------------------------------------------------------------------------------
#define MAX_MAIl_BODY_LEN MAILBOX_MAX_MEMO_LEN 

// SYSTEM MAIL TYPE
// �ý��۸����ΰ�� Ÿ��Ʋ�� �޶����ٸ�
enum MAIL_TYPE
{
	MAIL_TYPE_NULL	,									// ����� ����
	MAIL_TYPE_AUCTION_BASE		= 50,					// ���
	MAIL_TYPE_AUCTION_SELL		= MAIL_TYPE_AUCTION_BASE +1,	// �ǸſϷ� : ����ڰ� ������
	MAIL_TYPE_AUCTION_BUY,								// ����(�ﱸ����): �����ڰ�������
	MAIL_TYPE_AUCTION_OUTBID,							// ��ȸ���� : �������ڰ��� �������� ����������
	MAIL_TYPE_AUCTION_CANCEL_BIDDER,							// ������ : ����ڰ� ��Ź����� ��ҽ�(�����/������)
	MAIL_TYPE_AUCTION_CANCEL_SELLER,
	MAIL_TYPE_AUCTION_EXPIRED,							// ���� : ����ڰ� �ø� ������ �Ⱓ�� ��������
};			   

#define AUCTION_MAIL_DELIMETER "_"						// ��Ÿ��Ͽ��� ���� ������
//////////////////////////////////////////////////////////////////////
// MailBox

// Client <-> Server
typedef struct _MAIL_HEADER
{
	UINT64				uiMailID;				// Mail index
	TIMESTAMP_STRUCT	tmSendTime;				// ���� �ð�
	TCHAR				szSender[LEN_NAME+1];	// �۽���
	UINT8				iType;					// MAIL_TYPE 
}MAIL_HEADER,*PMAIL_HEADER;

typedef struct _MAIL_ATTACHMENT
{
	UINT64	uiEly;					// ÷���� ely amount
	UINT32	uiItemID;				// ÷�ε� Item Type (tbluItem2::TypeID)
	UINT64	uiItemNo;				// ÷�ε� Item NO (tbluItem2::ItemNo)
	UINT8	uiItemCount;			// ÷�ε� Item ���� (tbluItem2::cnt)
	UINT8	uiContainerType;		// ÷�ε� Item�� �κ��丮 Ÿ��
	UINT8	uiContainerSlot;		// ÷�ε� Item�� �κ��丮���� ��ġ
	UINT8	uiReadFlag;				// IsNewMail?  ���� ���� ���ο� ���������� ǥ���� (tbluMailBox::ReadFlag)
}MAIL_ATTACHMENT,*PMAIL_ATTACHMENT;

// ���� �۽� ���� + ���� + ÷�� ����
typedef struct _MAIL_HEADER_ATTACHMENT: public MAIL_ATTACHMENT, public MAIL_HEADER
{
}MAIL_HEADER_ATTACHMENT,*PMAIL_HEADER_ATTACHMENT;


//////////////////////////////////////////////////////////////////////
// Server <-> DB : ���� ���ο� ����ü
	typedef struct _MAIL_HEADER_ATTACHMENT_SS: public MAIL_ATTACHMENT, public MAIL_HEADER
	{
		TCHAR	szSubject[MAILBOX_MAX_SUBJECT_LEN+1];				// ���� : MAIL_HEADER::iType > MAIL_TYPE_AUCTION_BASE �ΰ��� "\0"  
	}MAIL_HEADER_ATTACHMENT_SS,*PMAIL_HEADER_ATTACHMENT_SS;

	typedef struct _MAIL_INFO_SS: public MAIL_HEADER_ATTACHMENT_SS
	{
		TCHAR	szReceiver[LEN_NAME+1];
		USERID	iReceiverUserID;
		CHARID	iReceiverCharID;
		USERID	iSenderUserID;
		CHARID	iSenderCharID;

		// MAIL_HEADER::iType > MAIL_TYPE_AUCTION_BASE �ΰ�� 
		// "AUCTION-TYPE_����_������_������_ITEMID_VALUE" �� "%d_%d_%d_%d_%d_%d" ���˷� �����ϸ� �ݾװ� ������ ���� ������ ���ù����̾ ������ ���߾� ������
		// ITEMID �� �ǸſϷ�� �Ǹ��� ������ �������� ��� 
		// VALUE�� AUCTION-TYPE ���� ely / mile / cash �ϼ� ����
		TCHAR	szMemo[MAILBOX_MAX_MEMO_LEN+1];						
		CONTAINER_SLOT StampItemPos;	// �߰�
		ITEMNO		   iStampItemNo;	// �߰�
	}MAIL_INFO_SS,*PMAIL_INFO_SS;


//////////////////////////////////////////////////////////////////////

// �߰�
typedef struct _CASHSHOP_INFO
{
	int  iPackageID;
	bool bEnable;
	UINT16 iPositionIndex;
	UINT8 iEventPage;
	UINT8 iEventIcon;
	int	 iCashPrice; // 
	int	 iSalePrice;
	int  iMaxOz; // 
	int  iMaxMileage;
} CASHSHOP_INFO, *PCASHSHOP_INFO;	


// 20080411 mijin ��õ��ǰ 
typedef struct _CASHSHOP_HOT_INFO
{
	int  	iShopID;
	UINT8 	iDescLength;
	TCHAR	strDesc[50];

} CASHSHOP_HOT_INFO, *PCASHSHOP_HOT_INFO;

//	jmulro ���ٹ���2008��8��26
typedef struct _Quick_Buy_Info
{
	int  m_iPackageID;			//	�̳ǵ�ID
	int  m_nLevel;				//	��ҵĵȼ�
	int  m_nOrder;				//	�ڷŵ�λ��
}t_Quick_Buy_Info;

//////////////////////////////////////////////////////////////////////
// Lottery

#define MAX_LOTTERY_INT	  50
#define	MAX_LOTTERY_COUNT (50*32)
#define MAX_LOTTERY_RANK 10

typedef struct _LOTTERY_REWARD
{
	UINT16 iRewardID;
	UINT16 iRewardCount;

} LOTTERY_REWARD, *PLOTTERY_REWARD;

//////////////////////////////////////////////////////////////////////
// PC�� ��������
typedef struct _ITEMMIX_INFO
{
	UINT8	iLv;		//  ���շ���
	int		iCurExp;	//  ���հ���ġ ���緮
	int		iMinExp;	//  ���հ���ġ ����
	int		iMaxExp;	//  ���հ���ġ ��
	UINT8	iRareProb;  //  ���ս� ��� ����Ȯ������
	UINT8   iSuccessProb;  // ���ռ���Ȯ������
	UINT8	iOptProb;	// ���ս� �ɼ�����Ʈ ����Ȯ�� ����
}ITEMMIX_INFO;

//////////////////////////////////////////////////////////////////////
// PC�� pvp ����
typedef struct _PVP_STATUS
{
	UINT8		iLv;		//  PVP ������
	__int64		iGlory;		//  �� ���緮
	int			iPoint;		//	PVP �ŷ��� ����Ʈ
}PVP_STATUS;

//////////////////////////////////////////////////////////////////////
// ��ų����
typedef struct _CHAR_SKILL
{
	int				iSkillID;	// SKILL.LDT::ItemID
	short			iSkillLv;	// PC�� ����Ʈ�� �� �ø� ������.
	short			iSkillCurrLv;// PC�� ������ ����/��ų/���� ���� ���ؼ� �ø� �ӽ����� ������ ���� ������.
	UINT16			iSkillNo;	// ��ų ��������
} CHAR_SKILL, *PCHAR_SKILL;

enum SKILL_SAVE_TYPE
{
	SKILL_SAVE_NULL,	// �Ϲݽ�ų �ʱ�ȭ�� ����
	SKILL_SAVE_GENERAL, // �Ϲݽ�ų �ʱ�ȭ�� ���ܵ�
	SKILL_SAVE_ITEMMIX,	// ���ս�ų �ʱ�ȭ�� ����
};

//////////////////////////////////////////////////////////////////////
// ���

// OSP �ŷ�Ÿ�� 20080325 mijin
enum OSP_TRADE
{
	TRADE_TYPE_USER = 1,		// ������ ���ŷ�
	TRADE_AUCTION_REGISTER,			// ��ŵ��
	TRADE_AUCTION_CASH_BUY,			// ĳ��(���ϸ���)�� ��ñ���
	TRADE_AUCTION_ELY_BUY,			// ������(���ӸӴ�)�� ��ñ���
	TRADE_AUCTION_TENDER,			// �������
	TRADE_AUCTION_ACCEPT,			// ��ų���
	TRADE_AUCTION_CANCEL = 9,			// ������
};

// ��űⰣ Ÿ��
enum AUCTION_DURATION
{
	PERIOD_SHORT,		// �ܱ�		(6)
	PERIOD_LONG,		// ���		(12)
	PERIOD_EXTREME,		// �����	(24)
};

// �����۰�ż�ƮŰ
// ��������:0, ��������:1
enum AUCTION_SORT_KEY
{
	AUCTION_SORT_NULL,
	AUCTION_SORT_QUALITY,	// ǰ��
	AUCTION_SORT_ITEM_LV,		// ����
	AUCTION_SORT_ITEM_OPTPOINT,	// ������
	AUCTION_SORT_DURATION,	// �����ð�
	AUCTION_SORT_PRICE,			// ������(ely,cash,mile)
	AUCTION_SORT_MAX,
};

// ��ű⺻����
typedef struct _AUCTION_HEADER
{
	__int64 iAuctionID;				// ���Ű
	UINT8	iType;					// AUCTION_TYPE (���Ÿ��)
	UINT8	iDuration;				// AUCTION_DURATION (�Ǹ��ڰ� ������)
	USERID	iSellerID;				// �ǸŰ� ����Ű
	TCHAR	szSeller[LEN_NAME+1];	// �Ǹ��� ĳ����
	UINT32	iRemainTime;			// ���糲���ð�

	__int64 iBidPrice;				// ���������� Ȥ�� ��ȸ������
	__int64 iBuyOutPrice;			// �ﱸ��
	__int64 iCurrPrice;				// ���簡
	USERID  iCurrUserID;			// ���������ڰ���Ű
	TCHAR	szBidder[LEN_NAME+1];	// �ְ�������
} AUCTION_HEADER, *PAUCTION_HEADER;

// ��Űŷ�Ÿ�Ժ��߰�����Ÿ
typedef struct _AUCTION_GOODS_ITEM 
{
	ITEM stAuctionItem;
} AUCTION_GOODS_ITEM, *PAUCTION_GOODS_ITEM;

typedef struct _AUCTION_GOODS_POINT 
{
	int SellPoint; // Ely, Cash, Mileage
	int FeePoint;  // ������
} AUCTION_GOODS_POINT, *PAUCTION_GOODS_POINT;

typedef struct _PetAttr_Info
{
	UINT8	uPetStatus;
	UINT16	uStayServerID;
	char	szPetName[LEN_NAME];
	UINT16	lv;
	UINT16	hp;
	UINT16	sp;
	UINT32	exp;
	int  	ssp;
} t_PetAttr_Info;

typedef struct _Pet_Skill_To_Client
{
	int nSkillID;
	int nLevel;
}t_Pet_Skill_To_Client;


//////////////////////////////////////////////////////////////////////
// PC�� ��ȥ����

enum WEDDING_PC_STATUS
{
	WEDDING_STATUS_NONE =		0,			// 0
	WEDDING_STATUS_LOVE =		1 << 0,		// 1 ��������
	WEDDING_STATUS_PROPOSE =	1 << 1,		// 2 �����������
	WEDDING_STATUS_WEDDING =	1 << 2,		// 4 ��ȥ����
	//WEDDING_STATUS_PARTING =	1 << 3,		// 8 �̺����� �̺��� ������ WEDDING_STATUS_NONE���� �����ϱ����
};

enum WEDDING_TYPE
{
	WEDDING_TYPE_NONE =		0,			// 0
	WEDDING_TYPE_LOVE,				//����
	WEDDING_TYPE_PROPOSE,			//��������
	WEDDING_TYPE_WEDDING			//��ȥ
};

typedef struct _WEDDING_INFO
{
	UINT8				iLv;							//  Wedding Lv
	int					iLP;							//  Love Point
	int					iLPM;							//	Love Point Max
	int					iDay;							//	�����ϼ� �Ǵ� ��ȥ�ϼ�
	UINT8				iStatus;						//	�������
	int					iPartingNum;					//	�̺������ð�(�ʴ���)
	TCHAR				szPartName[LEN_NAME+1];			//	���� �̸�

}WEDDING_INFO;


#pragma pack(pop)
