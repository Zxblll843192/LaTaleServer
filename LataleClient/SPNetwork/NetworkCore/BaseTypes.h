// BaseTypes.h

#pragma once


#if 0
	#include <basetsd.h>
#else

	// Data Type Range : ms-help://MS.VSCC.2003/MS.MSDNQTR.2003FEB.1042/vclang/html/_langref_data_type_ranges.htm

	//		int, unsigne int,enum :  System dependent

	//		int, unsigned int ��� ����

	//typedef unsigned char				    BYTE;
	//typedef unsigned short      			WORD;	
	//typedef unsigned long       			DWORD;

	typedef signed char				INT8, *PINT8;
	typedef signed short			INT16, *PINT16;
	#if _MSC_VER > 1000
		typedef signed __int32      INT32, *PINT32;
	#else
		typedef signed long		    INT32, *PINT32;
	#endif
	typedef signed __int64			INT64, *PINT64;

	typedef unsigned char			UINT8, *PUINT8;
	typedef unsigned short			UINT16, *PUINT16;
	#if _MSC_VER > 1000
		typedef unsigned __int32    UINT32, *PUINT32;
	#else
		typedef unsigned long		UINT32, *PUINT32;
	#endif
	typedef unsigned __int64		UINT64, *PUINT64;

	typedef INT8	int8;
	typedef INT16	int16;
	typedef INT32	int32;
	typedef INT64	int64;
	typedef UINT8	uint8;
	typedef UINT16	uint16;
	typedef UINT32	uint32;
	typedef UINT64	uint64;

#endif

typedef double DISTANCE;

typedef UINT16	MAPID;		
typedef UINT32	USERID;		
typedef UINT32	CHARID;		

//typedef unsigned short	MAPID;		// UINT16
//typedef unsigned long	USERID;		// UINT32
//typedef unsigned long	CHARID;		// UINT32

typedef enum _SERVER_MODE
{
	SERVERMODE_DEBUG,
	SERVERMODE_SERVICE,
	MAX_SERVERMODE
} SERVER_MODE;

typedef enum _GAMEENTITY_STATUS
{
	GE_STATUS_NONE = 0,
	GE_STATUS_INIT = 1,
	GE_STATUS_AUTH = 2,
	GE_STATUS_CHAR_MGMT = 3,
	GE_STATUS_PLAYING = 4,
	GE_STATUS_EXITING = 5,
	MAX_GAMEENTITY_STATUS
} GAMEENTITY_STATUS,*PGAMEENTITY_STATUS;

//////////////////////////////////////////////////////////////////////////////////////////

#define MAX_PACKET_SIZE		8192
#define MAX_CLIENT_SESSION	200			// �� ���� ������ Ŭ���̾�Ʈ�� �������� ���Ӽ� ����

#define LEN_MTU				1600
#define LEN_MSS				1460		// Maximum Segment Size

//////////////////////////////////////////////////////////////////////////////////////////

#ifdef _LATALE_SERVER

typedef enum _IO_OPERATION
{
	IO_NULL,
	IO_ACCEPT,
	IO_READ,
	IO_WRITE,
	IO_DISCONNECT,
	IO_SENDQUEUEING
} IO_OPERATION;

typedef enum _PLAYSTEP
{
	PLAYSTEP_INIT,						// �ʱ�ȭ��
	PLAYSTEP_AUTH,						// �α��μ������� ������
	PLAYSTEP_USERIN,					// �ߺ��˻������
	PLAYSTEP_LOGIN,						// �ʱ�ȭ����, PC instance ��������
	PLAYSTEP_DBLOADING,					// DBJobQueue �� �ε� ��û
	PLAYSTEP_DBLOAD_COMPLETED,			// DBJobQueue �� �ε� �۾� �Ϸ�
	PLAYSTEP_PLAYING,					// ���� ��
	PLAYSTEP_MOVE,						// �ٸ��������� �̵���Ŷ�� ��������
	PLAYSTEP_DBSAVING,					// DBJobQueue �� ���� ��û
	PLAYSTEP_DBSAVE_COMPLETED,			// DBJobQueue �� ���� �Ϸ�
	PLAYSTEP_LOGOUT,					// �α׾ƿ���
	MAX_PLAYSTEP
} PLAYSTEP;

enum 
{
	PEERTYPE_USER,
	PEERTYPE_USER_GM,
	PEERTYPE_SERVER_BASE,
	PEERTYPE_SERVER_LS,
	PEERTYPE_SERVER_LBS,
	PEERTYPE_SERVER_GS,
	PEERTYPE_SERVER_MS,
	PEERTYPE_SERVER_CMS,
	PEERTYPE_SERVER_MW,
	PEERTYPE_SERVER_TS,
	PEERTYPE_SERVER_AS,
	PEERTYPE_SERVER_IDS,		// InDun Server
	PEERTYPE_SERVER_PS,			// Pvp Server
	PEERTYPE_SERVER_BS,
	MAX_PEERTYPES
};

#define SET_PLAYSTEP(X,Y)		X->SetProcessStep(Y)
#define GET_PLAYSTEP(X)			X->GetProcessStep()

#endif // LATALE_SERVER

