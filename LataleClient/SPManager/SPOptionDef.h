// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPOptionDEF.h
// Comment : 
// Creation : metalgeni 2005-04-7 ���� 1:30:38
//***************************************************************************


#pragma once

#define CUR_CLIENT_OPTION_VER  0x00000012

//typedef unsigned short SERVER_SIDE_OPTION;
typedef INT32 SERVER_SIDE_OPTION;

#define LOGIN_ID_LEN 32

enum SPServerSideOption {
	SSO_NULL				= 0,	
	SSO_DEFAULT				= 0xFFFFFFFF,	// ��� �ɼ� ��� ���� �ǹ�
	SSO_REQ_TRADE			= 1 << 0,		// �ŷ� ��û ���
	SSO_REQ_TEAM			= 1 << 1,		// �� �ʴ� ���
	SSO_REQ_ALERT			= 1 << 2,		// �¶��� ���� ���� ���	
	SSO_REQ_WANTTEAM		= 1 << 3,		// ��Ƽ���� ����
	SSO_REQ_WHISPER			= 1 << 4,		// �ӼӸ� ���
	SSO_REQ_CHATTEAM		= 1 << 5,		// ��Ƽä�� ����
	SSO_REQ_CHATFRIEND		= 1 << 6,		// ģ��ä�� ����
	SSO_REQ_CHATGUILD		= 1 << 7,		// ���ä�� ����
	SSO_REQ_FRIEND			= 1 << 8,		// ģ�� �ʴ� ���
	SSO_REQ_CHATROOM_UNUSED = 1 << 9,		// ������ �˻� ���
	SSO_REQ_CHATROOM_INVITE_DENIAL = 1 << 10,	// ��ȭ ��û ���
	SSO_REQ_CHATROOM_STYLE_SECRET = 1 << 11,	// ��Ÿ�� ����

	//- 
	SSO_REQ_PVP						= 1 << 13,	
	SSO_REQ_LEVEL					= 1 << 14,	
	SSO_REQ_COMBAT					= 1 << 15,	
	SSO_REQ_LOVE					= 1 << 16,		//	LOVE ��û ���
	SSO_REQ_LOVE_INFO				= 1 << 17,		//	LOVE �������� ���
};

/*
enum SCREEN_SHOT {
	SCREEN_SHOT_PNG			= 0,			// ��ũ���� ���� PNG
	SCREEN_SHOT_BMP			= 1,			// ��ũ���� ���� BMP
	SCREEN_SHOT_JPG			= 2,			// ��ũ���� ���� JPG
	SCREEN_SHOT_MAX			= 3,
};
*/

enum SCREEN_SHOT {
	SCREEN_SHOT_JPG			= 0,			// ��ũ���� ���� JPG
	SCREEN_SHOT_PNG			= 1,			// ��ũ���� ���� PNG
	SCREEN_SHOT_BMP			= 2,			// ��ũ���� ���� BMP	
	SCREEN_SHOT_MAX			= 3,
};


enum EFFECT_STEP {
	EFFECT_STEP_0		= 0,			// ����Ʈ ��
	EFFECT_SEEP_1		= 1,
	EFFECT_STEP_2		= 2,			// ����Ʈ ��
	EFFECT_STEP_3		= 3,
	EFFECT_STEP_4		= 4,			// ����Ʈ ��
	EFFECT_SETP_MAX		= 5,			// ����Ʈ �ƽ�
};


struct SPOptionStruct {	
	//System
	bool bExp;							/**< ���� ����ġ <br> */
	bool bItem;							/**< ���� ������ <br> Ely ���� <br> */
	bool bUseItem;						/**< ��� ������ <br> */
	bool bHelp;							/**< ä��â ���� <br> */

	bool bEnableBGM;					/**< BGM <br> */
	bool bEnableSE;						/**< ȿ���� <br> */	

	int	iVolumeBGM;						/**< BGM Volume <br> */
	int	iVolumeSE;						/**< ȿ���� Volume <br> */
	int	iGammaRamp;						/**< ȭ���� Volume <br> */
	int	iEffect;						/**< Effect Volume <br> */	

	//Community
	//bool bChatParty;					/**< ��Ƽä�� <br> */
	//bool bChatFriend;					/**< ģ��ä�� <br> */
	//bool bChatGuild;					/**< ���ä�� <br> */

	//bool bChatPermitFriend;				/**< ģ��ä�� ��� <br> */
	bool bChatPermitWhisper;			/**< �ӼӸ� ��� <br> */
	
	//User Benefit
	bool bIndicatePlayer;				/**< �÷��̾� �̸� ǥ�� <br> */
	bool bIndicateMonster;				/**< ���� �̸� ǥ�� <br> */
	bool bIndicateNPC;					/**< NPC �̸� ǥ�� <br> */
	bool bIndicatePet;					/**< Pet �̸� ǥ�� <br> */

	bool bSpeechPlayer;					/**< ��ǳ�� ��ü <br> */
	bool bSpeechTeam;					/**< ��ǳ�� ��Ƽ <br> */	
	bool bSpeechNPC;					/**< ��ǳ�� NPC <br> */
	bool bSpeechGuild;					/**< ��ǳ�� Guild <br> */	

	bool bHpBarSelf;					/**< ���� ������ HP Bar <br> */
	bool bHpBarParty;					/**< ��Ƽ���� HP Bar <br> */
	bool bHpBarPlayer;					/**< Ÿ ������ HP Bar <br> */	

	bool bAutoHideMouse;				/**< Ŀ�� �ڵ� ���� <br> */

	int	iScreenShot;					/**< ��ũ���� ���� <br> */

	//std::string strID;					//[2005/11/11] ���� ID
};



#define REFRESH_NULL			0
#define REFRESH_SERVERSIDE		(1 << 0)
#define REFRESH_CLIENTSIDE		(1 << 2)
#define REFRESH_ALL				(REFRESH_SERVERSIDE | REFRESH_CLIENTSIDE)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Registry Key Value
#define OPTION_VER			"OptionVer"		
#define OPTION_BIN			"Option"
#define LAST_ID				"ID"
#define LAST_LOGINSERVER	"LoginServer"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Option Archive Message 
#define SPOAM_NULL				0x00000000
#define SPOAM_BASE				0x00010000

#define SPOAM_COMMIT_TO_SERVER		(SPOAM_BASE + 10)
//#define SPOAM_REQUIRE_TO_SERVER		(SPOAM_BASE + 20)
//#define SPOAM_RECEIVE_FROM_SERVER	(SPOAM_BASE + 30)

//#define SPOAM_NAME_PLAYER		(SPOAM_BASE + 60)
//#define SPOAM_NAME_MONSTER		(SPOAM_BASE + 70)
//#define SPOAM_NAME_NPC			(SPOAM_BASE + 80)

//#define SPOAM_SPEECH_PLAYER		(SPOAM_BASE + 130)
//#define SPOAM_SPEECH_TEAM		(SPOAM_BASE + 140)
//#define SPOAM_SPEECH_NPC		(SPOAM_BASE + 150)

//#define SPOAM_COMM_TRADE		(SPOAM_BASE + 200)
//#define SPOAM_COMM_INVITE		(SPOAM_BASE + 210)
//#define SPOAM_COMM_ALERT		(SPOAM_BASE + 220)

#define SPOAM_HIDE_MOUSE		(SPOAM_BASE + 240)

#define SPOAM_BTN_BGM			(SPOAM_BASE + 260)
#define SPOAM_SLD_BGM			(SPOAM_BASE + 270)

#define SPOAM_BTN_SOUNDEFFECT	(SPOAM_BASE + 290)
#define SPOAM_SLD_SOUNDEFFECT	(SPOAM_BASE + 300)
#define SPOAM_SLD_GAMMARAMP		(SPOAM_BASE + 320)

//#define SPOAM_USER_ID			(SPOAM_BASE + 400)		//[2005/11/11]


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Option Archive Message Function Macro

#define SPOAMESSAGE_FUNC SPOptionArchiveMessageMapFunc
#define SPOAMESSAGE_MAP_DECLARE() \
	int SPOAMESSAGE_FUNC( unsigned int spoam, WPARAM wParam, LPARAM lparam);

#define SPOAMESSAGE_MAP_BEGIN( __class ) \
	int __class::SPOAMESSAGE_FUNC( unsigned int spoam, WPARAM wParam, LPARAM lparam) {

#define SPOAMESSAGE_MAP_END_BASE() \
	return -1;\
	}

#define SPOAMESSAGE_COMMAND( message, msg_func )		\
	if ( spoam == message  )	{ return msg_func( wParam, lparam ); }






