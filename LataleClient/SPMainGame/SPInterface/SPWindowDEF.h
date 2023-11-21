// Copyright (C) metalgeni
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : metalgeni 2004-08-08 ���� 10:26:19
//***************************************************************************


#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Window Class ID List
typedef enum WND_ID {
	WNDID_INVALID					= 0x0000,

	// Control Window
	WNDID_CTRL_NULL					= 0x0100,
	WNDID_CTRL_GAUGE				= 0x0101,
	WNDID_CTRL_EDIT					= 0x0102,	
	WNDID_CTRL_STATIC				= 0x0103,

	WNDID_CTRL_BUTTON				= 0x0104,
	WNDID_CTRL_BUTTON_CHECK			= 0x0105,
	
	WNDID_CTRL_LISTBOX				= 0x0106,
	WNDID_CTRL_COMBOBOX				= 0x0107,
	WNDID_CTRL_TAB					= 0x0108,
	WNDID_CTRL_TREEBOX				= 0x0109,
	WNDID_CTRL_CUSTOM				= 0x0110,
	WNDID_CTRL_GRID					= 0x0111,
	WNDID_CTRL_NOTICE				= 0x0112,

	WNDID_CTRL_SLIDER_VERTICAL		= 0x0113,
	WNDID_CTRL_SLIDER_HORIZON		= 0x0114,

	WNDID_CTRL_TYPEWRITER			= 0x0115,
	WNDID_CTRL_DIGITBOARD			= 0x0116,

	WNDID_CTRL_MULTILINE_EDIT		= 0x0117,

	WNDID_CTRL_RS_STATIC			= 0x0118,
	WNDID_CTRL_RS_LIST				= 0x0119,
	WNDID_CTRL_ROW_UNIT				= 0x011A,

	WNDID_CTRL_FORCE				= 0x01FF,


	// Common Window
	WNDID_COMMON_CANDVERTICAL		= 0x0201,

	WNDID_CTRL_PAGESELECT			= 0x0210,		//[2007/1/25] - ���� ������ ����Ʈ

	// Parent Window
	WNDID_NULL						= 0x0300,
	WNDID_ROOT						= 0x0301,
	WNDID_MINIMAP					= 0x0302,
	WNDID_CENTER					= 0x0303,
	WNDID_CENTERSTATUS				= 0x0304,
	WNDID_CENTERCHAT				= 0x0305,
	WNDID_CENTERCHATEDIT			= 0x0306,
	WNDID_MENUBAR					= 0x0307,
	WNDID_TOOLTIP					= 0x0308,
	WNDID_LOGIN 					= 0x0309,
	WNDID_LOGIN_SOFTKEY				= 0x0310,
	WNDID_MENU						= 0x030A,
	WNDID_ITEM						= 0x0311,
	WNDID_EQUIP						= 0x0312,
	WNDID_SKILL						= 0x0313,
	WNDID_STATUS					= 0x0314,
	WNDID_QUEST						= 0x0315,
	WNDID_TEAM						= 0x0316,
	WNDID_LOOTING					= 0x0317,
	WNDID_LOBBY_SERVER				= 0x0318,
	WNDID_EXIT						= 0x0319,
	WNDID_MESSAGE					= 0x031A,	//[2005/5/3] - jinhee Event Message
	WNDID_NPCTALK					= 0x031B,	//[2005/5/11] - jinhee Npc Talk Window
	WNDID_SHOPTALK					= 0x0321,	//[2005/5/16] - Npc Shop Message
	WNDID_SHOPTRADE					= 0x0322,	//[2005/5/17] - Npc Shop Trade List Window
	//WNDID_ITEMSELL					= 0x0323,	//[2005/5/19] - Trade Sell Item Window
	//WNDID_ELY						= 0x0324,	//[2005/5/19] - Trade Ely(��) ǥ�� 
	WNDID_QUICK_SLOT				= 0x0325,	//	AJJIYA [7/6/2005]
	WNDID_STORAGE					= 0x0326,	//[2005/7/14] - jinhee //â��������
	WNDID_PC_INFO					= 0x0327,	//[2005/7/14] - jinhee //PC����â
	WNDID_PC_TRADE					= 0x0328,	//[2005/7/14] - jinhee //PC�ŷ�
	WNDID_FRIEND					= 0x0329,	// AJJIYA [8/30/2005]
	WNDID_NPC_QUEST					= 0x0330,	//[2005/9/22] - jinhee //Npc Quest ������
	WNDID_OPTION					= 0x0331,	// metalgeni [11/4/2005]
	WNDID_HELP						= 0x0332,	// AJJIYA [1/13/2006 AJJIYA]
	WNDID_GIFT						= 0x0333,	//[2006/3/20] Gift
	WNDID_CASHSHOP					= 0x0334,
	WNDID_MAILLIST					= 0x0335,	//[2006/4/6]	Mail List
	WNDID_MAILMSG					= 0x0336,	//[2006/4/6]	Mail Msg
	WNDID_ENCHANT					= 0x0337,
	WNDID_USERSHOP_SELL				= 0x0338,	//[2006/5/10]	User Shop Seller
	WNDID_USERSHOP_BUY				= 0x0339,	//[2006/5/10]	User Shop Buyer
	WNDID_PROLOGUE					= 0x033A,
	WNDID_WORLDMAP					= 0x033B,
	//WNDID_SHORTCUT					= 0x033C,
	WNDID_ITEM_UPGRADE				= 0x033D,
	WNDID_QUESTVIEW					= 0x033E,
	WNDID_QUESTNOTIFY				= 0x033F,
	WNDID_WAYPOINT					= 0x0340,	//[2006/8/30]	Way Point
	WNDID_PET						= 0x0341,	//[2006/10/18]	Pet Equip
	WNDID_ITEM_TIMEADD				= 0x0342,	//[2006/11/14]	Item Time Add
	WNDID_PET_LEVELUP				= 0x0343,	// Pet Level Up [11/22/2006 AJJIYA]
	WNDID_PETSHOP					= 0x0344,	//[2006/11/27]	Pet Shop
	WNDID_PC_TRADE_RESULT			= 0x0345,	//[2007/3/12] - PC�ŷ� ���
	WNDID_MICROPHONE				= 0x0346,	//[2007/3/15] - ��ġ��
	WNDID_GUILD_CREATE				= 0x0347,	//[2007/4/06] - ��� ����
	WNDID_GUILD_DESTROY				= 0x0348,	//[2007/4/06] - ��� ����
	WNDID_GUILD_INFO				= 0x0349,	//[2007/4/06] - ��� ����
	WNDID_CROPS						= 0x034A,	//[2007/5/30] - �۹� ����
	WNDID_BEAUTYSHOP				= 0x034B,	//[2007/5/30] - BEAUTY_SHOP
	WNDID_STORYVIEW					= 0x034C,	//[2007/5/30] - STORY_VIEW
	WNDID_GUILD_LEVELUP				= 0x034D,	//[2007/4/06] - ��� ������
	WNDID_GUILD_EMBLEM				= 0x034E,	//[2007/4/06] - ��� ���� ����
	WNDID_LOGINIDC					= 0x0350,	// Loing IDC Select [5/9/2007 AJJIYA]
	WNDID_LOTTERY					= 0x0351,	// Lottery [5/30/2007 AJJIYA]
	WNDID_JOYSTICK					= 0x0352,	//[2007/6/7]	JoyPad Setting 
	WNDID_SYSTEM_MESSAGE			= 0x0353,	// AJJIYA [7/9/2007 AJJIYA]
	WNDID_NPC_PORTAL				= 0x0354,	//[2007/8/2]	Npc�� ���� ��Ż ����Ʈ
	WNDID_CHAT_MACRO				= 0x0355,	// Chat Macro [8/7/2007 AJJIYA]
	WNDID_NPC_EVENT					= 0x0356,	//[2007/8/7]	Npc Item ExChange Event
	WNDID_NEED_LIST					= 0x0357,	//[2007/8/27]	Need Item List
	WNDID_ITEM_MIX					= 0x0358,	// Item Mix [9/3/2007 AJJIYA]
	WNDID_BUY_CONFIRM				= 0x0359,	//[2007/8/27]	Buying Confirm
	WNDID_TEXTBOOK					= 0x035A,	//[2007/9/12]	Text Book
	WNDID_PCTALK					= 0x035B,	//[2007/9/13]	CUTIN PC TALK
	WNDID_RSCLIENT					= 0x035C,	//[2007/9/28]	RS Client for SNDA
	WNDID_GAMBLE					= 0x035D,	// Gamble [10/29/2007 AJJIYA]
	WNDID_PVPRESERVE				= 0x035E,	//[2007/11/6]	PVP���� ������
	WNDID_PVPENTERWAIT				= 0x0360,	//[2007/11/7]	PVP��� ������
	WNDID_PVP_LOADWAIT				= 0x0361,	//[2007/11/14]	PVP �ε���� ������
	WNDID_PVP_TIMMER				= 0x0362,	//[2007/11/14]	PVP Ÿ�̸� ������
	WNDID_PVP_RANKING				= 0x0363,	//[2007/11/14]	PVP ��ŷ ������
	WNDID_PVP_RESULT				= 0x0364,	//[2007/11/14]	PVP ��� ������
	WNDID_GUIDE_BOOK				= 0x0365,	// GUIDE BOOK [11/19/2007 AJJIYA]
	WNDID_CHATTING_ROOM				= 0x0366,	// Chatting Room [2/25/2008 AJJIYA]
	WNDID_AUCTION					= 0x0367,	// Auction [2/25/2008 Duragon]
	WNDID_AUCTION_MSG				= 0x0368,	// Auction [2/25/2008 Duragon]
	WNDID_TALKING_ROOM				= 0x036D,	// Talking Room [3/6/2008 AJJIYA]
	WNDID_CASH_TRADE_SELECT			= 0x036E,	// [2008/3/27] Field Cash Trade Start
	WNDID_CASH_TRADE				= 0x036F,	// [2008/3/27] Field Cash Trade 
	WNDID_CASH_GIFT					= 0x0370,	// [2008/3/27] Field Cash Gift 
	WNDID_CASH_TRADE_RESULT			= 0x0371,	// [2008/3/27] Field Cash Trade Result
	WNDID_CASH_HOTLIST				= 0x0372,	// [2008/3/27] Field Cash Trade HotList
	WNDID_CHATTING_PASSWORD			= 0x0373,	// Chatting Room Password [4/4/2008 AJJIYA]
	WNDID_CASH_TRADE_WAIT			= 0x0374,	// [2008/4/8]	Field Cash Trade Wait
	WNDID_NPC_EVENTLIST				= 0x0375,	// [2008/6/10] Npc Event List
	WNDID_BUGLE_SELECT				= 0x0376,	// bugle select setting
	WNDID_BUGLE_MENU				= 0x0377,	// bugle shortcut menu window
	WNDID_VISUAL_BUGLE				= 0x0378,	// visual bugle preview & display
	WNDID_EFFECTITEM_UPGRADE		= 0x0379,
	WNDID_PUSH_PROP					= 0x0380,	// ������Ʒ
	WNDID_CASHER					= 0x0381,	// ���򴰿�
	WNDID_PHANTOM_EDITOR			= 0x0382,	// ���򴰿�
	WNDID_GREENERGUIDE				= 0x0383,
	WNDID_PETCHAT_EDITOR			= 0x0384,
	WNDID_FORCE						= 0x03FF,
	WNDID_MESSAGEBOX				= 0x0400,   // [xialin 2008/07/23]add
	WNDID_BEEXACT   				= 0x0401,   // [xialin 2008/07/30]add
	WNDID_CREATEMSG   				= 0x0402,
	WNDID_DESTORYMSG   				= 0x0403,

	WNDID_FRIEND_FIND				= 0x0404,   // [liuyang 2008/08/28]add			
	WNDID_FIND_MESSAGE				= 0x0405,	// [liuyang, 2008.8.31]add
	WNDID_AUTOSET					= 0X0406,   // [xialin 2008/11/19]add

	WNDID_PETSHOP_SELL				= 0x0407,
	WNDID_FRIEND_FOLLOW				= 0x0409,	// [liuyang, 2008.10.10]add
	WNDID_FRIEND_SNATCH				= 0x0410,	// [liuyang, 2008.10.10]add

	WNDID_MESSAGELIST				= 0x0420,

	WNDID_LOVE						= 0x0429,	// Love [9/25/2008 AJJIYA]
	WNDID_LOVEMSG_INPUT				= 0x042A,	// Love Msg Input [10/13/2008 AJJIYA]
	WNDID_OPTIONRST					= 0x042B,	// [2008/10/17] - jinhee Item Option re deal
	WNDID_PC_SUMMON					= 0x042C,	// [2008/10/27] - Duragon ĳ���� ��ȯ
	WNDID_LOVEMSG_VIEW				= 0x042D,	// Love Msg View [11/3/2008 AJJIYA]

} WND_ID;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Window Type List
enum WND_TYPE {
	WND_TYPE_NULL				= 0,
	WND_TYPE_BTN_NORMAL			= 1,
	WND_TYPE_BTN_CHECK			= 2,
	
	WND_TYPE_TOPBASE			= 3,	// ���Ʒ� �׵θ�
	WND_TYPE_LEFTBASE			= 4,	// �¿� �׵θ�
	WND_TYPE_RIGHTBASE			= 5,	
	WND_TYPE_NINEBASE			= 6,	// 9���� �׵θ�
	
	WND_TYPE_RIGHTBASE_FULLSRC	= 7,	// SPWindowGauge 

	WND_TYPE_RECT               = 8,    //[xialin 2008/07/08]add

};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Window Status List
typedef enum WND_STATE {

	WND_STATE_NULL					= 0x0000,
	WND_STATE_NORMAL				= (0x0001 << 0),
	WND_STATE_DISABLE				= (0x0001 << 1),
	WND_STATE_HITTEST				= (0x0001 << 2),
	WND_STATE_CLICK					= (0x0001 << 3),

	WND_STATE_FOCUS					= (0x0001 << 11),
	WND_STATE_ACTIVE				= (0x0001 << 12),
	WND_STATE_MODAL					= (0x0001 << 13),

} WND_STATE;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Interface Message List
typedef enum SPIM {
	SPIM_NULL						=	0,
	SPIM_USER						=	1000,
								
	// MOUSE					
	SPIM_MOUSE_FIRST				=	SPIM_USER+100,
								
	SPIM_CURSOR_ENTER				=	SPIM_USER+100,
	SPIM_CURSOR_OUT					=	SPIM_USER+101,
	SPIM_CURSOR_MOVE				=	SPIM_USER+102,
								
	SPIM_LBUTTON_DOWN				=	SPIM_USER+103,
	SPIM_LBUTTON_UP					=	SPIM_USER+104,
//	SPIM_LBUTTON_UP					=	SPIM_USER+105, //CLICK�� UP���� ���� 2005/1/24 
	SPIM_LBUTTON_DBLCLICK			=	SPIM_USER+106,
								
	SPIM_RBUTTON_DOWN				=	SPIM_USER+107,
	SPIM_RBUTTON_UP					=	SPIM_USER+108,
	SPIM_RBUTTON_CLICK				=	SPIM_USER+109,
	SPIM_RBUTTON_DBLCLICK			=	SPIM_USER+110,
								
	SPIM_WHEEL_UP					=	SPIM_USER+111,
	SPIM_WHEEL_DOWN					=	SPIM_USER+112,
								
	SPIM_MOUSE_LAST					=	SPIM_USER+200,
								
	// KEYBOARD									 
	SPIM_KEY_FIRST					=	SPIM_USER+201,
								
	SPIM_KEY_PRESS					=	SPIM_USER+201,
	SPIM_KEY_DOWN					=	SPIM_USER+202,
	SPIM_KEY_UP						=	SPIM_USER+203,
	SPIM_KEY_TAB					=	SPIM_USER+204,	// TAB, Enter�� ���� �����Ѵ�.
	SPIM_KEY_RETURN					=	SPIM_USER+205,
	SPIM_KEY_ESCAPE					=	SPIM_USER+206,
								
	SPIM_KEY_LAST					=	SPIM_USER+399,
								
	// WINDOW COMMON
	SPIM_CLOSE						=	SPIM_USER+400,		
	SPIM_KILLFOCUS					=	SPIM_USER+401,		
	SPIM_SETFOCUS					=	SPIM_USER+402,		
	SPIM_ACTIVATE					=	SPIM_USER+403,		
	SPIM_DEACTIVATE					=	SPIM_USER+404,
	SPIM_ADD_ITEM					=	SPIM_USER+405,
	SPIM_INSERT_ITEM				=	SPIM_USER+406,
	SPIM_DELETE_ITEM				=	SPIM_USER+407,
	SPIM_SET_WINDOWTEXT				=	SPIM_USER+408,
	SPIM_GET_WINDOWTEXT				=	SPIM_USER+409,
	SPIM_REFRESH					=	SPIM_USER+410,
	SPIM_POS_UPDATE					=	SPIM_USER+411,
	SPIM_SET_COLOR					=	SPIM_USER+412,
	
	// CTRL
	SPIM_SET_IMAGEINDEX				=	SPIM_USER+500, 
	SPIM_SET_IMAGECLEAR				=	SPIM_USER+501, 
	SPIM_SET_MAXVALUE				=	SPIM_USER+502, 
	SPIM_SET_CURVALUE				=	SPIM_USER+503, 
	SPIM_SET_GAUGETYPE				=	SPIM_USER+504,
	SPIM_SCROLL						=	SPIM_USER+505, // SPWindowList ����.
	SPIM_PURGE						=	SPIM_USER+506, // SPWindowList ����.
	SPIM_BTN_SELECT					=	SPIM_USER+507, // SPWindowButton ����.
	SPIM_BTN_ENABLE					=	SPIM_USER+508, // SPWindowButton ����.
	SPIM_SET_SLIDERTYPE				=	SPIM_USER+509,
	SPIM_SLIDER_PAGEUP				=	SPIM_USER+510,
	SPIM_SLIDER_PAGEDOWN			=	SPIM_USER+511,
	SPIM_SLIDER_PAGESIZE			=	SPIM_USER+512,
	SPIM_SLIDER_UP					=	SPIM_USER+513,
	SPIM_SLIDER_DOWN				=	SPIM_USER+514,
	SPIM_SLIDER_CURPAGE				=	SPIM_USER+515,
	SPIM_SET_MINVALUE				=	SPIM_USER+516,
	SPIM_COMBOBOX_CHANGE_VALUE		=	SPIM_USER+517,	// SPWindowComboBox [11/17/2005]
	SPIM_COMBOBOX_DROPDOWN_CLICK	=	SPIM_USER+518,	// SPWindowComboBox [11/17/2005]
	SPIM_COMBOBOX_LISTBOX_SHOW		=	SPIM_USER+519,	// SPWindowComboBox [11/17/2005]
	SPIM_SET_CARET_POS				=	SPIM_USER+520,	// SPWindowComboBox [11/17/2005]

	SPIM_TYPE_CLEAR					=	SPIM_USER+522,	// SPWindowTypeWriter [5/30/2006]
	SPIM_TYPE_START					=	SPIM_USER+523,	// SPWindowTypeWriter [5/30/2006]
	SPIM_TYPE_END					=	SPIM_USER+524,	// SPWindowTypeWriter [5/30/2006]
	SPIM_TYPE_SKIP					=	SPIM_USER+525,	// SPWindowTypeWriter [5/30/2006]
	SPIM_TYPE_SPEED					=	SPIM_USER+526,	// SPWindowTypeWriter [5/30/2006]
	SPIM_TYPE_SOUND					=	SPIM_USER+527,	// SPWindowTypeWriter [5/30/2006]
	SPIM_SET_MARGIN					=	SPIM_USER+528,
	SPIM_LIST_RESIZE				=	SPIM_USER+551,
	SPIM_LIST_ADDITEM				=	SPIM_USER+552,
	SPIM_LIST_CLEAR					=	SPIM_USER+553,
	SPIM_GET_ENTER_ENABLE			= 	SPIM_USER+554,	// SPWindowEditMultiLine [8/29/2007]
	SPIM_GET_CALC_LUMP_STRING		= 	SPIM_USER+555,	// SPWindowList [3/5/2008 ]

	// NOTICE
	SPIM_NOTICE_YES					=	SPIM_USER+900,
	SPIM_NOTICE_NO					=	SPIM_USER+901,
	SPIM_NOTICE_OK					=	SPIM_USER+902,
	SPIM_NOTICE_CANCEL				=	SPIM_USER+903,

	// PageSelect
	SPIM_PAGE						=	SPIM_USER+950,


	// WRAP Window List							
	// TOOLTIP									 
	SPIM_TOOLTIP_MOVE				=	SPIM_USER+1101,
	SPIM_TOOLTIP_OUT				=	SPIM_USER+1102,
	SPIM_TOOLTIP_ENTER				=	SPIM_USER+1103,

	// MOVE 
	SPIM_MOVE_BEGIN					=	SPIM_USER+1151,
	SPIM_MOVE_END					=	SPIM_USER+1152,
	SPIM_MOVE						=	SPIM_USER+1153,

	// WINDOWCHAT
	SPIM_WNDCHAT_MESSAGE_STRING		=	SPIM_USER+1201,
	SPIM_WNDCHAT_CLEAR				=	SPIM_USER+1202,
	SPIM_WNDCHAT_TOGGLE				=	SPIM_USER+1203,
	SPIM_WNDCHAT_INSERT_MSGEDIT		=	SPIM_USER+1204,
	SPIM_WNDCHAT_GET_MSG			=	SPIM_USER+1205,
	SPIM_WNDCHAT_SET_WHISPER		=	SPIM_USER+1206,
	SPIM_WNDCHAT_GET_NOTICE			=	SPIM_USER+1207,
	SPIM_WNDCHAT_SEND_MESSAGE		=	SPIM_USER+1208,
	SPIM_WNDCHAT_GET_COMMAND		=	SPIM_USER+1209,	
	SPIM_WNDCHAT_GET_BUGLE			=	SPIM_USER+1210,
	SPIM_WNDCHAT_GET_VISUALBUGLE	=	SPIM_USER+1211,		// visual bugle

	// StatPallet
	SPIM_REFRESH_PLAYER_STAT		=	SPIM_USER+1301,
	SPIM_STAT_BUTTON_ENABLE			=	SPIM_USER+1302,	//[8/2/2005] ���� �ȷ������ ��ư���� Ȱ�� ��Ȱ��ȭ�� ����
	SPIM_TEAM_ICON_UPDATE			=	SPIM_USER+1303,

	// MiniMap
	SPIM_SET_STAGE					=	SPIM_USER + 1311,			//MiniMap Set Current Stage Info
	SPIM_REFRESH_MINIMAP_GOB		=	SPIM_USER + 1312,			//�̴ϸʿ��� ����� GOB�� �����Ѵ�.
	SPIM_REFRESH_ICON_TEAM			=	SPIM_USER + 1313,			//�������� �̴ϸ� �������� �����Ѵ�.

	// Message Window
	SPIM_SET_MESSAGE_SHOW			=	SPIM_USER + 1321,			//Event Message Show/Hide
	SPIM_SET_MESSAGE_TEXT			=	SPIM_USER + 1322,			//Event Message Set Message Text	

	// Message Window Shop Talk	
	SPIM_SET_SHOPTALK_UPDATE		= 	SPIM_USER + 1330,			//Event Message Shop Talk
	SPIM_SET_SHOPTALK_MSG			=	SPIM_USER + 1331,			//Event Message Update

	// Looting
	SPIM_LOOTING_ITEM_SET			=	SPIM_USER + 1340,
	SPIM_LOOTING_ITEM_DELETE		=	SPIM_USER + 1341,
	SPIM_LOOTING_ITEM_REDRAW		=	SPIM_USER + 1342,

	// Npc Talk
	SPIM_SET_NPCDATA				=	SPIM_USER + 1350,			//NpcTalkWindow Setting Npc Data		
	// Save Point Data
	SPIM_SET_SAVEPOINT				=	SPIM_USER + 1351,			//NpcTalkWindow Setting Save Point Data
	// Npc Talk Data
	SPIM_SET_NPCTALK				=	SPIM_USER + 1352,			//NpcTalkWindow Setting NpcTalk Data
	// Npc (PC) Talk Set Skin Focus Lose
	SPIM_SET_NPCTALK_FOCUSLOSE		=	SPIM_USER + 1355,			//Npc (PC) Talk Set Skin Focus Lose
	// Npc Talk Item Select
	SPIM_SET_NPCTALK_ITEMSELECT		=	SPIM_USER + 1356,			//PcTalkWindow Set Select Item
	// Npc Talk Box Mode 
	SPIM_SET_NPCTALK_BOXTYPE		=	SPIM_USER + 1357,			//NpcTalkWindow Setting Box Type
	// Npc Talk Click 
	SPIM_SET_CUTIN_CLICK			=	SPIM_USER + 1358,			//NpcTalkClick
	// Npc Talk Render...
	SPIM_SET_HIDE_START				=	SPIM_USER + 1359,			//NpcTalkWindow Hide Starting

	// Npc Shop Show
	SPIM_SET_NPCSHOP_SHOW			=	SPIM_USER + 1360,			//NpcShop(Quest)Window Show 

	// Npc Cut �� Show�� ������ ���� �޽���
	SPIM_SET_CUTIN_WINDOW			=	SPIM_USER + 1370,			//InterfaceManager Use

	// Item �Ǹ� �� ����â�� �Ǹ� ������ �ʱ�ȭ �Ѵ� 
	SPIM_SET_ITEMSELL_RESET			=	SPIM_USER + 1380,			//SPWindowItemSell Use
	SPIM_SET_ITEMSELL_REGIST		=	SPIM_USER + 1381,			//SPWindowItemSell �Ǹ� ������ �ٷ� ���

	// Npc Cut In �� Item, Status, Equip ������ �� �����ִ� ��� HIDE ��ư�� ����ų� �����ְų� 
	SPIM_SET_EXIT_SHOW				=	SPIM_USER + 1400,			//SPWindowItem Exit Button Hide
	SPIM_EXIT_CHANNEL_ENABLE		=	SPIM_USER + 1401,
	
	SPIM_SET_CASH_ENABLE			=	SPIM_USER + 1405,			//[2006/11/2] SPWindowMenu�� Cash Buton Ȱ���Ǵ� ��Ȱ��

	SPIM_CHANNEL_SET				=	SPIM_USER + 1410,

	SPIM_DRAGNDROP_END				=	SPIM_USER + 1420,			//	�巡�� �� ��� �޼���

	SPIM_GET_QUICK_SLOT				=	SPIM_USER + 1430,			//	������ ����Ʈ �޾ƿ���	AJJIYA [7/14/2005]
	SPIM_QUICK_SLOT_UPDATE			=	SPIM_USER + 1431,			//	������ ������Ʈ AJJIYA  [7/21/2005]
	SPIM_GET_QUICK_SLOT_UNIT		=	SPIM_USER + 1432,			// [xialin 2008/11/06]

	SPIM_SET_PLAYER_INFO			=	SPIM_USER + 1440,

	SPIM_GET_SKILL_LVUP				=	SPIM_USER + 1450,			//	��ų ������ �޾ƿ��� AJJIYA  [7/19/2005]
	SPIM_SKILL_UPDATE				=	SPIM_USER + 1451,			//	��ų ȹ��� ������Ʈ AJJIYA	 [7/20/2005]
	SPIM_GET_SKILL_LEARN			=	SPIM_USER + 1452,			//	��ų ����( Ŭ���ؼ� ) [9/18/2007 AJJIYA]
	SPIM_GET_SKILL_UIUNIT			=	SPIM_USER + 1453,			// [xialin 2008/11/07]add

	//PC_TRADE
	SPIM_TRADE_PUSHMONEY			=	SPIM_USER + 1460,			//[2005/7/27] - jinhee
	SPIM_TRADE_PUSHITEM				=	SPIM_USER + 1461,			//[2005/7/27] - jinhee
	SPIM_TRADE_POPITEM				=	SPIM_USER + 1462,			//[2005/7/27] - jinhee
	SPIM_TRADE_ACCEPT				=	SPIM_USER + 1463,			//[2005/7/27] - jinhee
	SPIM_TRADE_CANCEL				=	SPIM_USER + 1464,			//[2005/7/27] - jinhee
	SPIM_TRADE_REQUEST				=	SPIM_USER + 1465,			// AJJIYA [11/21/2005]
	SPIM_TRADE_WAIT					=	SPIM_USER + 1466,			//[2007/3/22]
	
	//PC TRADE�� �ö� �������� ����� 
	SPIM_TRADE_ITEM_CLEAR			=	SPIM_USER + 1470,			//[2005/7/26] - jinhee
	SPIM_TRADE_ITEM_CANCEL			=	SPIM_USER + 1471,			//[2006/12/26] ��Ż�� ���� Ʈ���̵� ĵ����

	// Storage
	SPIM_STORAGE_REFRESH			=	SPIM_USER + 1480,	//[2005/7/21] â�� �� ����...	
	SPIM_STORAGE_INITSLOT			=	SPIM_USER + 1481,	//[2005/10/18] â�� ���� ���� �ʱ�ȭ...
	SPIM_STORAGE_SETSLOT			=	SPIM_USER + 1482,	//[8/11/2005] â�� ���� ����

	//Gift
	SPIM_GIFT_LIST_UPDATE			=	SPIM_USER + 1485,	//[2006/3/21] Gift List����	

	SPIM_PC_INFO_EQUIP_CLEAR		=	SPIM_USER + 1490,
	SPIM_PC_INFO_SET_EQUIP			=	SPIM_USER + 1491,	//[2005/8/25] Ÿ ������� �������۵��� �����ϱ�����...

	SPIM_PC_INFO_SET_STATUS			=	SPIM_USER + 1500,

	SPIM_GET_EMOTICON				=	SPIM_USER + 1510,			// �̸�Ƽ�� �޾ƿ��� AJJIYA [8/30/2005]
	SPIM_UPDATE_EMOTICON			=	SPIM_USER + 1511,			// �̸�Ƽ�� ������Ʈ AJJIYA [8/30/2005]

	SPIM_GET_FRIEND					=	SPIM_USER + 1520,			// ģ������Ʈ �ޱ� AJJIYA [9/2/2005]
	SPIM_ADD_FRIEND					=	SPIM_USER + 1521,			// �߰��� ģ�� ���� �ޱ� AJJIYA [9/2/2005]
	SPIM_ADD_RECV_FRIEND			=	SPIM_USER + 1522,			// ģ�� ����â ���� �ޱ� [4/25/2007 AJJIYA]
	SPIM_ACCEPT_FRIEND				=	SPIM_USER + 1523,			// ���� ģ�� ���� �ޱ� [4/23/2007 AJJIYA]
	SPIM_DEL_FRIEND					=	SPIM_USER + 1524,			// ������ ģ�� ���� �ޱ� AJJIYA [9/2/2005]
	SPIM_REFRESH_STATUS_FRIEND		=	SPIM_USER + 1525,			// ģ���� �ֽ� ���� ���� ���� HOSHIM [2005/9/6]
	SPIM_USER_ADD_FRIEND			=	SPIM_USER + 1526,			// ����â���� ģ�� �߰� AJJIYA [11/18/2005]
	SPIM_USER_DEL_FRIEND			=	SPIM_USER + 1527,			// ����â���� ģ�� ���� AJJIYA [11/18/2005]
	SPIM_USER_CHECK_FRIEND			=	SPIM_USER + 1528,			// ģ�� �� ���� ����Ʈ ģ�� üũ [2/9/2006 AJJIYA]
	SPIM_FRIEND_NAME				=	SPIM_USER + 1529,			// [liuyang, 2008.9.1]
					

	// Quest
	SPIM_QUEST_ADD					=	SPIM_USER + 1530,			// ����Ʈ �׸� �߰� AJJIYA [6/23/2006]
	SPIM_QUEST_DEL					=	SPIM_USER + 1531,			// ����Ʈ �׸� ���� AJJIYA [6/23/2006]
	SPIM_QUEST_NOTIFY				=	SPIM_USER + 1532,			// ����Ʈ �˸�â AJJIYA [6/27/2006]
	SPIM_QUEST_DETAIL				=	SPIM_USER + 1533,			// ����Ʈ ������ AJJIYA [6/27/2006]
	SPIM_QUEST_REFRESH				=	SPIM_USER + 1534,			// ����Ʈ â ������ ������Ʈ AJJIYA [10/6/2005]
	SPIM_QUEST_GET_REWARD			=	SPIM_USER + 1535,			// ����Ʈ ������ ������ �������� AJJIYA [6/28/2006]

	SPIM_RECEIVE_OPTION				=	SPIM_USER + 1540,	// Receive Server Side Option - metalgeni [11/9/2005]
	
	SPIM_FRIEND_WHERE				=   SPIM_USER + 1541,   //[liuyang, 2008.9.3]add
	SPIM_LEAVING_TIMES				=	SPIM_USER + 1542,	//[liuyang, 2008.9.5]add
	SPIM_ITEM_LEVEL					=	SPIM_USER + 1543,	//[liuyang, 2008.9.10]add
	SPIM_FOLLOW_FAIL				=	SPIM_USER + 1544,	//[liuyang, 2008.9.10]add
	SPIM_SNATCH_FAIL				=	SPIM_USER + 1545,
	// Team
	SPIM_TEAM_JOIN					=	SPIM_USER + 1550,
	SPIM_TEAM_SECEDE				=	SPIM_USER + 1551,
	SPIM_TEAM_UPDATE				=	SPIM_USER + 1552,
	SPIM_TEAM_UPDATE_STATUS			=	SPIM_USER + 1553,
	SPIM_TEAM_UPDATE_LOOTING_RULE	=	SPIM_USER + 1554,

	// Help
	SPIM_HELP_SHOW					=	SPIM_USER + 1560,			// ����â�� �������� [1/24/2006 AJJIYA]

	// Title
	SPIM_TITLE_GET_LIST				=	SPIM_USER + 1570,			// Ÿ��Ʋ ����Ʈ�� ������ AJJIYA [4/3/2006]
	SPIM_TITLE_CHANGE				=	SPIM_USER + 1571,			// Ÿ��Ʋ�� ���� �ɶ� AJJIYA [4/3/2006]
	SPIM_TITLE_ADD					=	SPIM_USER + 1572,			// Ÿ��Ʋ�� �߰� �ɶ� AJJIYA [4/3/2006]

	// CashShop
	SPIM_CASHSHOP_CLEAR_DRAG		=	SPIM_USER + 1600,
	SPIM_CASHSHOP_REFRESH_ITEMINVEN	=	SPIM_USER + 1601,
	SPIM_CASHSHOP_INFO				=	SPIM_USER + 1610,
	SPIM_CASHSHOP_UPDATE			=	SPIM_USER + 1611,
	SPIM_CASHSHOP_BUY				=	SPIM_USER + 1612,
	SPIM_CASHSHOP_GIFT				=	SPIM_USER + 1613,
	SPIM_CASHSHOP_SELL				=	SPIM_USER + 1614,
	SPIM_CASHSHOP_COUPON			=	SPIM_USER + 1615,
	SPIM_CASHSHOP_CARTLIST			=	SPIM_USER + 1616,
	SPIM_CASHSHOP_CARTADD			=	SPIM_USER + 1617,
	SPIM_CASHSHOP_CARTDEL			=	SPIM_USER + 1618,
	SPIM_CASHSHOP_HIDE_POPUP_MENU	=	SPIM_USER + 1620,
	SPIM_CASHSHOP_SET_URLTOKEN		=	SPIM_USER + 1621,	//[2007/03/22]Gamepot Cashshop ������ URL Token ����
	SPIM_CASHSHOP_NEED_ITEM_UPDATE	=	SPIM_USER + 1622,
	SPIM_CASHSHOP_ENTER				=	SPIM_USER + 1623,	// ĳ�ü� ���� [10/30/2007 AJJIYA]
	SPIM_CASHSHOP_WEB_PAGE			=	SPIM_USER + 1624, 
	SPIM_CASHSHOP_CART_CHECK		=	SPIM_USER + 1625,	//[2008/4/28] - �ܺο��� �� ����Ʈ �߰� �� üũ ����	
	SPIM_CASHSHOP_MSG_ADDPARCEL     =   SPIM_USER + 1626,   //[xialin 2008/07/23]add
	SPIM_CASHSHOP_MSG_ADDCONSUME    =   SPIM_USER + 1627,
	SPIM_CASHSHOP_MSG_ADDETC        =   SPIM_USER + 1628,
	SPIM_CASHSHOP_MSG_ADDEVENT      =   SPIM_USER + 1629,
	SPIM_CASHSHOP_MSG_ADDPET        =   SPIM_USER + 1630,
    SPIM_CASHSHOP_MSG_ADDWH         =   SPIM_USER + 1631,
	SPIM_CASHSHOP_EXACT				=	SPIM_USER + 1632,
	SPIM_CASHSHOP_PARCEL			=	SPIM_USER + 1633,
	SPIM_CASHSHOP_GETPLAYER			=	SPIM_USER + 1634,
	SPIM_CASHSHOP_SWAPTERMGR		=	SPIM_USER + 1635,
	SPIM_CASHSHOP_CASHSORT			=   SPIM_USER + 1636,

	// WorldMap
	SPIM_WORLDMAP_WORLD				=	SPIM_USER + 1700,
	SPIM_WORLDMAP_STAGE				=	SPIM_USER + 1701,

	//Mail List
	SPIM_MAIL_LIST_UPDATE			=	SPIM_USER + 1800,	//[2006/4/13] Mail List����
	SPIM_MAIL_LIST_SENDCLEAR		=	SPIM_USER + 1801,	//[2006/4/14] Mail Send�� Send�������̽� �ʱ�ȭ
	SPIM_MAIL_LIST_SENDITEM_RESET	=	SPIM_USER + 1802,	//[2006/4/19] �κ��丮���� ���Ͽ� ������ ���� �÷����� �������� ����
	SPIM_MAIL_LIST_CHECK_UPDATE		=	SPIM_USER + 1803,	//[2006/4/24] ���ο� ������ ���� ��� ���� ǥ�� üũ

	//Mail Msg
	SPIM_MAIL_MSG_UPDATE			=	SPIM_USER + 1810,	//[2006/4/17] Mail Msg�� ���õ� ���� �ζ����� �˷��ְ� ������Ʈ��û�� �Ѵ� 

	//Mail To ShotCut
	SPIM_SHOTCUT_MAILVOLUME			=	SPIM_USER + 1820,	//[2006/4/20] 
	SPIM_SHOTCUT_MAILNEW			=	SPIM_USER + 1821,	//[2006/4/20] 

	//ItemEnchant
	SPIM_ITEM_ENCHANT_CANCEL		=	SPIM_USER + 1901,
	SPIM_ITEM_ENCHANT_RESULT		=	SPIM_USER + 1902,
	SPIM_ITEM_ENCHANT_KEYUP			=	SPIM_USER + 1903,

	// Error
	SPIM_ERROR_SET_MSG				=	SPIM_USER + 2000,

	// Prologue
	SPIM_PROLOGUE_SET_STEP			=	SPIM_USER + 2100,
	SPIM_ACTOR_SCENE_COMPLETE		=	SPIM_USER + 2101,

	// ITEM_UPGRADE
	SPIM_ITEM_UPGRADE_CANCEL		=	SPIM_USER + 2200,
	SPIM_ITEM_UPGRADE_RESULT		=	SPIM_USER + 2201,
	SPIM_ITEM_UPGRADE_KEYUP			=	SPIM_USER + 2202,

	// UserShop Seller
	SPIM_USERSHOP_SELL_OPEN			=	SPIM_USER + 2300,		//������ ���� ����
	SPIM_USERSHOP_SELL_CLOSE		=	SPIM_USER + 2301,		//������ ���� ����
	SPIM_USERSHOP_SELL_BUY			=	SPIM_USER + 2302,		//������ ������ �Ǹ�
	SPIM_USERSHOP_SELL_SETCLOSE		=	SPIM_USER + 2303,		//Esc�� �������̽��� ���� ���λ��� ���� �����

	// PetShop Seller
	SPIM_PETSHOP_SELL_OPEN			=	SPIM_USER + 2310,		//������ ���� ����
	SPIM_PETSHOP_SELL_CLOSE			=	SPIM_USER + 2311,		//������ ���� ����
	SPIM_PETSHOP_SELL_BUY			=	SPIM_USER + 2312,		//������ ������ �Ǹ�
	SPIM_PETSHOP_SELL_SETCLOSE		=	SPIM_USER + 2313,		//Esc�� �������̽��� ���� ���λ��� ���� �����

	// UserShop Buyer
	SPIM_USERSHOP_BUY_IN			=	SPIM_USER + 2350,		//���� ���� ������ ����
	SPIM_USERSHOP_BUY_OUT			=	SPIM_USER + 2351,		//���� ���� ������ ������
	SPIM_USERSHOP_BUY_BUY			=	SPIM_USER + 2352,		//�� �Ǵ� ������ �������� ������ ������

	// petshop buyer
	SPIM_PETSHOP_BUY_IN				=	SPIM_USER + 2360,
	SPIM_PETSHOP_BUY_OUT			=	SPIM_USER + 2361,
	SPIM_PETSHOP_BUY_BUY			=	SPIM_USER + 2362,
	SPIM_PETSHOP_BUY_UPDATE			=	SPIM_USER + 2363,
	
	// WayPoint
	SPIM_WAYPOINT_UPDATE			=	SPIM_USER + 2400,		//��������Ʈ ���� ������Ʈ
	SPIM_WAYPOINT_MOVERESULT		=	SPIM_USER + 2401,		//��������Ʈ �̵� ���

	// Beautyshop
	SPIM_BEAUTYSHOP_FIGURECHANGE	=	SPIM_USER + 2500,		// ��Ƽ�� ���� ���

	// Item Time ADD
	SPIM_ITEM_TIMEADD_RESULT		=	SPIM_USER + 2600,		//������ �Ⱓ ���� ���
	// Pet
	SPIM_PET_STAT_UPDATE			=	SPIM_USER + 2700,		//�� ���� ������Ʈ
	SPIM_PET_SHOP_OPEN				=	SPIM_USER + 2701,		//�� ���� ����
	SPIM_PET_FEED_UPDATE			=	SPIM_USER + 2702,		//�ܺο��� �� �ڵ����̱� ������ ������ ������Ʈ �ɶ�
	SPIM_NEWPET_STAT_UPDATE			=	SPIM_USER + 2703,
	SPIM_NEWPET_SHOP_OPEN			=	SPIM_USER + 2704,

	// Menu
	SPIM_MENU_POPUP					=	SPIM_USER + 2800,		//���θ޴� �˾��޴��� Show���¸� ����

	// MicroPhone
	SPIM_MICROPHONE_MODE			=	SPIM_USER + 2900,		//��ġ�� ��� ���� 
	SPIM_MICROPHONE_RESULT			=	SPIM_USER + 2901, 

	SPIM_GUILD_INFO_ENABLE			=	SPIM_USER + 3001,		// Guild Information Enable
	SPIM_GUILD_MEMBER_LIST			=	SPIM_USER + 3002,		// Receive Member List
	SPIM_GUILD_MEMBER_JOIN			=	SPIM_USER + 3003,		// Receive Member Join
	SPIM_GUILD_MEMBER_SECEDE		=	SPIM_USER + 3004,		// Receive Member Secede
	SPIM_GUILD_MEMBER_INFOCHANGE	=	SPIM_USER + 3005,		// Receive Member Info Change
	SPIM_GUILD_REFRESH_COMMON		= 	SPIM_USER + 3006,		// Common Refresh
	SPIM_GUILD_RANK_CHANGE			=	SPIM_USER + 3007,		// ��� ������ư, �˾�ȣ��
	SPIM_GUILD_CREATE_RESULT		= 	SPIM_USER + 3008,		// ��� ���� ���
	SPIM_GUILD_CROP_SET				= 	SPIM_USER + 3009,		// �۹� Setting
	SPIM_GUILD_CROP_UPDATE			= 	SPIM_USER + 3010,		// �۹� ������Ʈ
	SPIM_GUILD_LEVELUP_RESULT		= 	SPIM_USER + 3011,		// ��� ������ ���
	SPIM_GUILD_EM_CHANGE_RESULT		= 	SPIM_USER + 3012,		// ���� ���� ���
	SPIM_GUILD_EM_CONFIRM_YES		= 	SPIM_USER + 3013,		// ���� ���� ���
	SPIM_GUILD_EM_CONFIRM_NO		= 	SPIM_USER + 3014,		// ���� ���� ���

	SPIM_STORY_SET_FACTOR			=	SPIM_USER + 3100,
	SPIM_STORY_FORCE_EXIT			=	SPIM_USER + 3101,		// StoryView Force Exit

	// LoginIDC
	SPIM_LOGIN_IDC_SHOW				=	SPIM_USER + 3200,		// Login IDC Button Click [5/10/2007 AJJIYA]

	// Lottery
	SPIM_LOTTERY_START				=	SPIM_USER + 3300,		// Lottery [6/1/2007 AJJIYA]
	SPIM_LOTTERY_UPDATE				=	SPIM_USER + 3301,		// Lottery [6/1/2007 AJJIYA]
	SPIM_LOTTERY_CHIOCE				=	SPIM_USER + 3302,		// Lottery [6/1/2007 AJJIYA]
	SPIM_LOTTERY_REFRESH_ITEMINVEN	=	SPIM_USER + 3303,       //[xialin 2008/10/13]add
	SPIM_LOTTERY_CLEAR_DRAG         =	SPIM_USER + 3304,       //[xialin 2008/10/13]add
	SPIM_LOTTERY_STATUS				=	SPIM_USER + 3305,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_UPDATE_ITEM		=	SPIM_USER + 3306,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_BUY				=	SPIM_USER + 3307,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_UNBUY				=	SPIM_USER + 3308,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_ACCEPT				=	SPIM_USER + 3309,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_ACCEPTSECOND		=	SPIM_USER + 3310,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_INITIAL			=	SPIM_USER + 3311,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_REFRESH			=	SPIM_USER + 3312,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_BROADCAST			=	SPIM_USER + 3313,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_SETNAME			=	SPIM_USER + 3314,		//[xialin 2008/10/13]add
	SPIM_LOTTERY_LOAD_TIP			=	SPIM_USER + 3315,		//[xialin 2008/11/06]add
	SPIM_LOTTERY_SAVE_TIP			=	SPIM_USER + 3316,		//[xialin 2008/11/06]add

	// SystemMessage
	SPIM_SYSTEM_MESSAGE_ADD			=	SPIM_USER + 3400,		// SystemMessage [7/9/2007 AJJIYA]

	// ChatMacro
	SPIM_CHATMACRO_GET_DATA			=	SPIM_USER + 3500,		//  [8/21/2007 AJJIYA]

	// ItemMix
	SPIM_ITEM_MIX_SHOW				=	SPIM_USER + 3600,		// ItemMix Window Show [9/3/2007 AJJIYA]
	SPIM_ITEM_MIX_RESULT			=	SPIM_USER + 3601,		// ItemMix Result [9/12/2007 AJJIYA]
	SPIM_ITEM_MIX_CANCEL			=	SPIM_USER + 3602,		// ItemMix Cancel [9/12/2007 AJJIYA]
	SPIM_ITEM_MIX_SKILL_INIT		=	SPIM_USER + 3603,		// ItemMix Skill Init [10/1/2007 AJJIYA]

	//	Gamble
	SPIM_GAMBLE_USE					=	SPIM_USER + 3700,		// Gamble Item use [10/29/2007 AJJIYA]
	SPIM_GAMBLE_RESULT				=	SPIM_USER + 3701,		// Gamble Result [10/29/2007 AJJIYA]

	// RS Client
	SPIM_SDRS_RECV_MAINMENU			=	SPIM_USER + 3801,		// RS Packet [11/12/2007 Duragon]
	SPIM_SDRS_RECV_SUBMENU			=	SPIM_USER + 3802,		// RS Packet [11/12/2007 Duragon]
	SPIM_SDRS_RECV_TOPTOPIC			=	SPIM_USER + 3803,		// RS Packet [11/12/2007 Duragon]
	SPIM_SDRS_RECV_ANSWER			=	SPIM_USER + 3804,		// RS Packet [11/12/2007 Duragon]
	SPIM_SDRS_RECV_UNSATREASON		=	SPIM_USER + 3805,		// RS Packet [11/12/2007 Duragon]

	//	Guide Book
	SPIM_GUIDE_BOOK_VIEW			=	SPIM_USER + 3900,		// Guide Book [11/20/2007 AJJIYA]

	//	PVP
	SPIM_PVP_ENTERWAIT_REGIST		=	SPIM_USER + 4001,		// PVP EnterWait Ok [11/20/2007 Duragon]
	SPIM_PVP_ENTERWAIT_CANCEL		=	SPIM_USER + 4002,		// PVP EnterWait Cancel [11/20/2007 Duragon]
	SPIM_PVP_LOADWAIT_UPDATE		=	SPIM_USER + 4003,		// PVP Load Update [11/20/2007 Duragon]
	SPIM_PVP_SET_TIMELIMIT			=	SPIM_USER + 4004,		// PVP Time Limit [11/20/2007 Duragon]
	SPIM_PVP_SET_KILLLIMIT			=	SPIM_USER + 4005,		// PVP Kill Limit [11/20/2007 Duragon]
	SPIM_PVP_SET_RANKING			=	SPIM_USER + 4005,		// PVP Kill Limit [11/20/2007 Duragon]
	SPIM_PVP_SET_RESULT				=	SPIM_USER + 4005,		// PVP Kill Limit [11/20/2007 Duragon]

	//	TalkingRoom
	SPIM_TALKING_ROOM_NEXTLINE		=	SPIM_USER + 4100,		// SetNextLine( ) [3/11/2008 AJJIYA]
	SPIM_TALKING_ROOM_MESSAGE		=	SPIM_USER + 4101,		// [3/11/2008 AJJIYA]

	SPIM_BEEXACT_MESSAGE			=	SPIM_USER + 4120,		// [xialin 2008/07/30] add
	SPIM_BEEXACT_GIFT				=	SPIM_USER + 4121,

	// Auction
	SPIM_AUCTION_SERVER_CLOSE		=	SPIM_USER + 4201,		// [3/13/2008 Duragon]
	SPIM_AUCTION_BID_BUY			=	SPIM_USER + 4202,		// [3/13/2008 Duragon]
	SPIM_AUCTION_SPOT_BUY			=	SPIM_USER + 4203,		// [3/13/2008 Duragon]
	SPIM_AUCTION_CANCEL				=	SPIM_USER + 4204,		// [3/13/2008 Duragon]
	SPIM_AUCTION_SEARCH_LIST		=	SPIM_USER + 4211,		// [3/20/2008 Duragon]
	SPIM_AUCTION_BUY_LIST			=	SPIM_USER + 4212,		// [3/20/2008 Duragon]
	SPIM_AUCTION_BUY_UPDATE			=	SPIM_USER + 4213,		// [3/20/2008 Duragon]
	SPIM_AUCTION_SALE_LIST			=	SPIM_USER + 4214,		// [3/20/2008 Duragon]
	SPIM_AUCTION_SALE_UPDATE		=	SPIM_USER + 4215,		// [3/20/2008 Duragon]
	SPIM_AUCTION_MONEY_UPDATE		=	SPIM_USER + 4216,		// [3/20/2008 Duragon]
	SPIM_AUCTION_SET_SEARCHNAME		=	SPIM_USER + 4217,		// [3/20/2008 Duragon]
	SPIM_AUCTION_ERROR_NOTICE		=	SPIM_USER + 4218,		// MSG OK
	SPIM_AUCTION_MSG_NOTICE			=	SPIM_USER + 4219,		// MSG OK/CANCEL
	SPIM_AUCTION_BID_MSG			=	SPIM_USER + 4220,		// BID_MSG
	SPIM_AUCTION_FEE_MSG			=	SPIM_USER + 4221,		// FEE_MSG
	SPIM_AUCTION_WAIT_SHOW			=	SPIM_USER + 4222,		// WAIT_SHOW
	SPIM_AUCTION_WAIT_CLOSE			=	SPIM_USER + 4223,		// WAIT_CLOSE
	SPIM_AUCTION_SEND_BID			=	SPIM_USER + 4224,		// Send Bid
	SPIM_AUCTION_SEND_SPOT			=	SPIM_USER + 4225,		// Send Spot
	SPIM_AUCTION_SEND_CANCEL		=	SPIM_USER + 4226,		// Send Cancel
	SPIM_AUCTION_SEND_NEXT			=	SPIM_USER + 4227,		// Send GetNext

	//	ChattingPassword
	SPIM_CHATTINGPASSWORD_SET		=	SPIM_USER + 4300,		//  [4/4/2008 AJJIYA]
	SPIM_CHATTINGPASSWORD_OK		=	SPIM_USER + 4301,		//  [4/4/2008 AJJIYA]
	SPIM_CHATTINGPASSWORD_CANCEL	=	SPIM_USER + 4302,		//  [4/4/2008 AJJIYA]

	// ChattingRoom
	SPIM_CHATTINGROOM_CREATE		=	SPIM_USER + 4401,		//  [4/10/2008 AJJIYA]
	SPIM_CHATTINGROOM_ROOM_CHECK	=	SPIM_USER + 4402,		//  [4/21/2008 AJJIYA]
	SPIM_CHATTINGROOM_JOIN			=	SPIM_USER + 4403,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_JOIN_CLEAR	=	SPIM_USER + 4404,		//  [5/19/2008 AJJIYA]
	SPIM_CHATTINGROOM_MODIFY		=	SPIM_USER + 4405,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_OUT			=	SPIM_USER + 4406,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_FORCEOUT		=	SPIM_USER + 4407,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_CHANGEMASTER	=	SPIM_USER + 4408,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_MESSAGE		=	SPIM_USER + 4409,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_MEMBERLIST	=	SPIM_USER + 4410,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_ADVERT		=	SPIM_USER + 4411,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_ROOMLIST		=	SPIM_USER + 4412,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_USERLIST		=	SPIM_USER + 4413,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_INVITE_REQ	=	SPIM_USER + 4414,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_INVITE_ANS	=	SPIM_USER + 4415,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_OTHERPC_INFO	=	SPIM_USER + 4416,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_GET_MYSTYLE	=	SPIM_USER + 4417,		//  [4/14/2008 AJJIYA]
	SPIM_CHATTINGROOM_OPTION		=	SPIM_USER + 4418,		//  [4/14/2008 AJJIYA]
	
	// Inventory			//[2008/4/17] - ID ���Ҵ�
	SPIM_ITEM_UNLOCK				=	SPIM_USER + 4500,	// ClearAllUserShopItem Func Call [9/5/2007 AJJIYA]
	SPIM_ITEM_SETTING				=	SPIM_USER + 4501,
	SPIM_ITEM_CLEAR					=	SPIM_USER + 4502,
	SPIM_ITEM_ALLCLEAR				=	SPIM_USER + 4503,
	SPIM_ITEM_SETSTACK				=	SPIM_USER + 4504,	//[2005/5/20] ����ī��Ʈ �缳��	
	SPIM_ITEM_SELECT				=	SPIM_USER + 4505,	//[2006/10/27] �������� �Ⱦ��� ���
	SPIM_ITEM_DISABLE				=	SPIM_USER + 4506,	//[2006/10/27] ��Ȱ�� 
	SPIM_ITEM_SET_PAGE				=	SPIM_USER + 4507,	//[2005/7/6] �κ��丮 ������ ������ ����
	SPIM_ITEM_SET_MAXPAGE			=	SPIM_USER + 4508,
	SPIM_ITEM_SETDEFAULT			=	SPIM_USER + 4509,	//[2005/11/27] �κ��丮 ���� �ʱ�ȭ �Ѵ� (ä���̵���)	
	SPIM_ITEM_LINE					=	SPIM_USER + 4510,	//[2006/12/21] - jinssaga   �κ��丮���� Grid�� ��� ���μ��� �����ؾ� �ϴ� ��� 
	SPIM_ITEM_HOT_STATUS			=	SPIM_USER + 4511,	//[2008/4/17] - HOT Item List Show Status �� �����Ѵ� 
	SPIM_ITEM_ID_INFO				=	SPIM_USER + 4512,	//[2008/5/16] - �κ��丮 Shift Click �� Item ID�� �������̽� �޴����� �Ѱ���
	SPIM_ITEM_SUBMENU				=	SPIM_USER + 4513,	//[2008/5/26] - �κ��丮 �������� ���� ��ư���� HIDE / SHOW

	// Equipment
	SPIM_EQUIP_SETTING				=	SPIM_USER + 4551,
	SPIM_EQUIP_CLEAR				=	SPIM_USER + 4552,
	SPIM_EQUIP_ALLCLEAR				=	SPIM_USER + 4553,
	SPIM_EQUIP_SELECT				=	SPIM_USER + 4554,	//[2005/7/8] ��� ������ ������ ǥ��
	SPIM_EQUIP_DISABLE				= 	SPIM_USER + 4555, 
	SPIM_EQUIP_SETDEFAULT			= 	SPIM_USER + 4556,	//[2005/11/27] ��� ���� �ʱ�ȭ �Ѵ� (ä���̵���)

	SPIM_EQUIP_CHANGE_WEAPON		=	SPIM_USER + 4561,	
	SPIM_WEAPON_CLEAR1				=	SPIM_USER + 4562,
	SPIM_WEAPON_CLEAR2				=	SPIM_USER + 4563,
	SPIM_WEAPON_SETTING1			=	SPIM_USER + 4564,
	SPIM_WEAPON_SETTING2			=	SPIM_USER + 4565,
	SPIM_WEAPON_ACTIVE_SLOT			=	SPIM_USER + 4566,
	SPIM_WEAPON_SELECT1 			=	SPIM_USER + 4567,	//[2005/7/8] ����1 ������ ������ ǥ��
	SPIM_WEAPON_SELECT2	    		=	SPIM_USER + 4568,	//[2005/7/8] ����2 ������ ������ ǥ��
	SPIM_WEAPON_DISABLE1			=	SPIM_USER + 4569,	//[2006/10/27] ����1 ������ ��Ȱ�� 
	SPIM_WEAPON_DISABLE2			=	SPIM_USER + 4570,	//[2006/10/27] ����2 ������ ��Ȱ�� 	

	SPIM_MSGBOARD_CREATE_OPEN		=	SPIM_USER + 4580,
	SPIM_MSGBOARD_CREATE			=	SPIM_USER + 4581,

	SPIM_MSGBOARD_DESTORY			=	SPIM_USER + 4591,

	SPIM_GREENERGUIDE_EVENT			=	SPIM_USER + 4600,
	SPIM_GREENERGUIDE_FETCHAWARD	=	SPIM_USER + 4601,

	//	Love
	SPIM_LOVE_INFO					=	SPIM_USER + 4610,		//  [11/3/2008 AJJIYA]
	SPIM_LOVE_REQUEST_RECV			=	SPIM_USER + 4611,		//  [11/3/2008 AJJIYA]
	SPIM_LOVE_RESPONSE				=	SPIM_USER + 4612,		//  [11/3/2008 AJJIYA]
	SPIM_LOVE_UPDATEMEMBER			=	SPIM_USER + 4613,		//  [11/3/2008 AJJIYA]
	SPIM_LOVE_CHAR_INFO				=	SPIM_USER + 4614,		//  [11/3/2008 AJJIYA]
	SPIM_LOVE_REFRESH_BUTTON		=	SPIM_USER + 4615,		//  [11/12/2008 AJJIYA]
	
} SPIM;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Interface Notice List
#define CPOS_BEGIN	0
#define CPOS_CUR	1
#define CPOS_END	2




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Interface Message Function Macro

#define SPIMESSAGE_OBJ_FUNC SPIMessageMapFunc
#define SPIMESSAGE_OBJ_MAP_DECLARE() \
protected :\
	virtual int SPIMESSAGE_OBJ_FUNC( SPIM Spim, UINT iID, WPARAM wParam, LPARAM lParam );	

#define SPIMESSAGE_OBJ_MAP_BEGIN( __classwindow ) \
	int __classwindow::SPIMESSAGE_OBJ_FUNC( SPIM Spim, UINT iID, WPARAM wParam, LPARAM lParam ) {

#define SPIMESSAGE_OBJ_MAP_END( __baseclass ) \
	return __baseclass::SPIMESSAGE_OBJ_FUNC( Spim, iID, wParam, lParam );\
	}

#define SPIMESSAGE_OBJ_MAP_END_BASE() \
	return -1;\
}

#define SPIMESSAGE_COMMAND( message, msg_func )		\
	if ( Spim == message && iID <= 0 )	{ return msg_func( wParam, lParam ); }
#define SPIMESSAGE_CONTROL( message, id, msg_func )	\
	if ( Spim == message && iID == id )	{ return msg_func( wParam, lParam ); }
#define SPIMESSAGE_CONTROL_RANGE( message, id1, id2, msg_func ) \
	if ( Spim == message && ( iID >= id1 && iID <= id2 ) ) { return msg_func( iID, wParam, lParam ); }
#define SPIMESSAGE_CHECK( message, msg_func )		\
	if ( Spim == message )		{ msg_func( iID, lParam ); }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Interface Manager Message Function Macro

#define SPIMESSAGE_FUNC SPInterfaceManagerMessageMapFunc
#define SPIMESSAGE_MAP_DECLARE() \
protected :\
	virtual int SPIMESSAGE_FUNC( SPIM spim, WPARAM wParam, LPARAM lparam);	

#define SPIMESSAGE_MAP_BEGIN( __class ) \
	int __class::SPIMESSAGE_FUNC( SPIM spim, WPARAM wParam, LPARAM lparam) {

#define SPIMESSAGE_MAP_END_BASE() \
	return -1;\
	}

#define SPIMESSAGE_COMMAND_EX( message, msg_func )		\
	if ( spim == message  )	{ return msg_func( wParam, lparam ); }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Window Instance ID List

//  10���� ���ϴ� ���ϵ��������̸� �� ��Ʈ�����쿡�� ������

#define WIID_NULL							0
#define WIID_INVALID						0
#define WIID_TOOLTIP						0x0001

#define WIID_ROOT							0x00000010
#define WIID_SUBGAMELOGIN					0x10000030
#define WIID_SUBGAMEZONE					0x20000020
#define WIID_SUBGAMELOBBY					0x30000020
#define WIID_SUBGAMEPROLOGUE				0x40000010

// Subgame Login
#define WIID_LOGIN							0x10001000
#define WIID_SOFTKEY						0x10002000

// Subgame Lobby
#define WIID_LOBBY							0x20001000

// Subgame Prologue
#define WIID_PROLOGUE						0x40001000


// Subgame Zone
#define WIID_CHATCONSOLE					0x30001000
#define WIID_CHATHISTORY					0x30002000
#define WIID_MENUBAR						0x30003000
#define WIID_MINIMAP						0x30004000
#define WIID_STATPALLET						0x30005000
#define WIID_CHAT							0x30006000
#define WIID_ITEM							0x30007000			// ITEM���� TEAM���� ������ �ٲ�� �ȵ�!! AJJIYA [9/8/2005]
#define WIID_EQUIP							0x30008000			// ITEM���� TEAM���� ������ �ٲ�� �ȵ�!! AJJIYA [9/8/2005]
//#define WIID_SKILL							0x30009000			// ITEM���� TEAM���� ������ �ٲ�� �ȵ�!! AJJIYA [9/8/2005]
#define WIID_STATUS							0x3000A000			// ITEM���� TEAM���� ������ �ٲ�� �ȵ�!! AJJIYA [9/8/2005]
#define WIID_QUEST							0x3000B000			// ITEM���� TEAM���� ������ �ٲ�� �ȵ�!! AJJIYA [9/8/2005]
#define WIID_TEAM							0x3000C000			// ITEM���� TEAM���� ������ �ٲ�� �ȵ�!! AJJIYA [9/8/2005]
#define WIID_MENU							0x3000D000
#define WIID_MESSAGE						0x3000E000			//[2005/5/3] - jinhee
#define WIID_EXIT							0x3000F000
#define WIID_LOOTING						0x30010000
#define WIID_NPCTALK						0x30011000			//[2005/5/11] - jinhee
#define WIID_SHOPTALK						0x30012000			//[2005/5/16] - jinhee
#define WIID_NPCTRADE						0x30013000			//[2005/5/17] - jinhee
//#define WIID_ITEMSELL						0x30014000			//[2005/5/19] - jinhee
//#define WIID_ELY							0x30015000			//[2005/5/19] - jinhee
#define WIID_CHANNEL_CHANGE					0x30016000
#define WIID_QUICK_SLOT						0x30017000			// AJJIYA [7/1/2005]
#define WIID_STORAGE						0x30018000			//[2005/7/14] - jinhee //â��������
#define WIID_PC_INFO						0x30019000			//[2005/7/14] - jinhee //PC����â
#define WIID_PC_TRADE						0x3001A000			//[2005/7/14] - jinhee //PC�ŷ�
#define WIID_NOTICEBOX						0x3001B000	
#define WIID_PC_EQUIP						0x3001C000
#define WIID_PC_STATUS						0x3001D000
#define WIID_FRIEND							0x3001E000			// AJJIYA [8/30/2005]	// ģ��
#define WIID_NPC_QUEST						0x3001F000			//[2005/9/22] - jinhee //Npc ����Ʈ 
#define WIID_BUFF							0x30020000			// AJJIYA [10/10/2005]	//	���� ������
#define WIID_EMOTICON						0x30030000			// AJJIYA [10/25/2005]	//	�̸�Ƽ��
#define WIID_OPTION							0x30031000			// metalgeni [11/4/2005]
#define WIID_MINI_TEAM						0x30032000
#define WIID_HELP							0x30033000			// AJJIYA [1/13/2006 AJJIYA]
//#define WIID_SHORTCUT						0x30034000			// HELPâ ����Ű [1/24/2006 AJJIYA]
#define	WIID_GIFT							0x30035000			//[2006/3/20] Gift
#define WIID_CASHSHOP						0x30036000
#define WIID_MAILLIST						0x30037000			//[2006/4/6]	Mail List
#define WIID_MAILMSG						0x30038000			//[2006/4/6]	Mail Msg
#define WIID_WORLDMAP						0x30039000			// ����� AJJIYA [4/7/2006]
#define WIID_WORLDMAP_SHORTCUT				0x30040000			// ����� ��������� AJJIYA [4/11/2006]
#define WIID_ENCHANT						0x30041000
#define WIID_USERSHOP_SELL					0x30042000			//[2006/5/10]	User Shop Seller
#define WIID_USERSHOP_BUY					0x30043000			//[2006/5/10]	User Shop Buyer
#define WIID_ITEM_UPGRADE					0x30044000			// AJJIYA [5/19/2006]
#define WIID_QUESTVIEW						0x30045000			// AJJIYA [6/23/2006]
#define WIID_QUESTNOTIFY					0x30046000			// AJJIYA [6/29/2006]
#define WIID_WAYPOINT						0x30047000			//[2006/8/30]	Way Point
#define WIID_BEAUTYSHOP						0x30048000			// Duragon [2006/10/09]	Beautyshop
#define WIID_PET							0x30049000			//[2006/10/18] Pet Equip
#define WIID_ITEM_TIMEADD					0x3004A000			//[2006/11/14] Item Time ADd
#define WIID_PET_LEVELUP					0x3004B000			// Pet Level Up [11/22/2006 AJJIYA]
#define WIID_PETSHOP						0x3004C000			//[2006/11/27] Pet Shop
#define WIID_PC_TRADE_RESULT				0x3004D000			//[2007/3/12] PC�ŷ��� ���â
#define WIID_MICROPHONE						0x3004E000			//[2007/3/15] ��ġ�� â
#define WIID_GUILD_INFO						0x30051000			//[2007/4/06] ��� â
#define WIID_GUILD_CREATE					0x30052000			//[2007/4/06] ��� �����â
#define WIID_GUILD_DESTROY					0x30053000			//[2007/4/06] ��� �����â
#define WIID_STORY							0x30054000
#define WIID_LOGINIDC						0x30055000			// Login IDC Select [5/9/2007 AJJIYA]
#define WIID_LOTTERY						0x30056000			// Lottery ���� ���� 2000�� ���!!! [5/30/2007 AJJIYA]
#define WIID_CROPS							0x30058000			// [2007/05/30]�۹�â
#define WIID_JOYSTICK						0x30059000			//[2007/6/7]	JoyPad Setting
#define WIID_GUILD_LEVELUP					0x3005A000			//[2007/8/23]	Guild Levelup
#define WIID_GUILD_EMBLEM					0x3005B000			//[2007/8/23]	Guild Emblem
#define WIID_SYSTEM_MESSAGE					0x30060000			// SystemMessage [7/9/2007 AJJIYA]
#define WIID_NPC_PORTAL						0x30061000			//[2007/8/2]	Npc Portal
#define WIID_CHAT_MACRO						0x30062000			// Chat Macro [8/7/2007 AJJIYA]
#define WIID_NPC_EVENT						0x30063000			//[2007/8/7]	Npc Item ExChange Event
#define WIID_ITEM_MIX						0x30064000			// Item Mix [9/3/2007 AJJIYA]
#define WIID_BUY_CONFIRM					0x30065000			// Buying Confirm Window [2007.09.07]Duragon
#define WIID_TEXTBOOK						0x30066000			// TextBook Window [2007.09.12]Duragon
#define WIID_PCTALK							0x30067000			//[2007/9/13]	CUTIN PC Talk
#define WIID_RSCLIENT						0x30068000			//[2007/9/28]	RS Client for SNDA
#define WIID_GAMBLE							0x30069000			// Gamble [10/29/2007 AJJIYA]
#define WIID_PVPRESERVE						0x3006A000			//[2007/11/6]	PVP���� ������
#define WIID_PVPENTERWAIT					0x3006B000			//[2007/11/7]	PVP��� ������
#define WIID_PVP_LOADWAIT					0x3006C000			//[2007/11/14]	PVP �ε� ������
#define WIID_PVP_TIMMER						0x3006D000			//[2007/11/14]	PVP Ÿ�̸� ������
#define WIID_PVP_RANKING					0x3006E000			//[2007/11/14]	PVP ��ŷ ������
#define WIID_PVP_RESULT						0x3006F000			//[2007/11/14]	PVP ��� ������
#define WIID_SKILL							0x30070000			// 70000 ~ 80000 ���� ��� �ּ��� Ŭ���� 99���� �غ� [12/6/2007 AJJIYA]
#define WIID_GUIDE_BOOK						0x30080000			// Guide Book [11/19/2007 AJJIYA]
#define WIID_CHATTING_ROOM					0x30081000			// Chatting Room [2/25/2008 AJJIYA]
#define WIID_AUCTION						0x30082000			// Auction [2/26/2008 Duragon]
#define WIID_TALKING_ROOM					0x30083000			// Talking Room [3/6/2008 AJJIYA]
#define WIID_CASH_TRADE_SELECT				0x30084000			// [2008/3/24]	Field Cash Trade Start
#define WIID_CASH_TRADE						0x30085000			// [2008/3/24]	Field Cash Trade 
#define WIID_CASH_GIFT						0x30086000			// [2008/3/24]  Field Cash Gift 
#define WIID_CASH_TRADE_RESULT				0x30087000			// [2008/3/24]	Field Cash Trade Result
#define WIID_CASH_HOTLIST					0x30088000			// [2008/3/24]	Field Cash Trade HotList
#define WIID_CHATTING_PASSWORD				0x30089000			// Chatting Room Password [4/4/2008 AJJIYA]
#define WIID_CASH_TRADE_WAIT				0x3008A000			// [2008/4/8]	Field Cash Trade Wait 
#define WIID_AUCTION_MSG					0x3008B000			// Auction [5/28/2008 Duragon]
#define WIID_NPC_EVENTLIST					0x3008C000			// [2008/6/10] Npc Event List
#define WIID_BUGLE_SELECT					0x3008D000			// bugle select shortcut setting window
#define WIID_BUGLE_MENU						0x3008E000			// bugle select shortcut menu
#define WIID_VISUAL_BUGLE					0x3008F000			// visual bugle
#define WIID_VISUAL_BUGLE_PREVIEW			0x30090000
#define WIID_PUSH_PROP						0x30091000			// ������Ʒ
#define WIID_CASHER							0x30092000			// ������Ʒ
#define WIID_EFFECTITEM_UPGRADE				0x30093000          //[2008/9/04] ��Ч��Ʒ����
#define WIID_PHANTOM_EDITOR					0x30094000          //[2008/9/04] phantom editor 
#define WIID_GREENERGUIDE					0x30095000			// greener guild window
#define WIID_PETCHAT_EDITOR					0x30096000			// pet chat editor
#define WIID_PETSHOP_SELL					0x30097000			// pet shop sell

#define WIID_ERROR							0x30100000
#define WIID_CANDIVERTICAL					0x30200000			//  [9/25/2006] Candidate Window Vertical
#define WIID_MESSAGEBOX						0x30300000          // 300000 ~ 301000 [xialin 2008/07/23]add
#define WIID_BEEXACT						0x30301000          // 301000 ~ 302000 [xialin 2008/07/30]add

#define WIID_CREATEMSG						0x30302000          // 302000 ~ 303000
#define WIID_DESTORYMSG						0x30303000          // 303000 ~ 304000

#define WIID_FRIEND_FIND					0x30304000			// 304000 ~ 305000 [liuyang 2008/08/28]add 
#define WIID_FIND_MESSAGE					0x30305001			// 305001 ~ 306000 [liuyang, 2008.8.31]add
#define WIID_FIND_MESSAGE_ONE				0x30306001			// 306001 ~	307000 [liuyang, 2008.9.1]add
#define WIID_FIND_MESSAGE_TWO				0x30307001			// 307001 ~ 308000 [liuyang, 2008.9.1]add


#define WIID_AUTOSET						0x30308000			// 308000 ~ 309000 [xialin 2008/11/19]add
#define WIID_FRIEND_FOLLOW					0x30309001			// 309001 ~ 30B000 [liuyang, 2008.10.10]add
#define WIID_FRIEND_SNATCH					0x3030A001			// 30A001 ~ 30B000 [liuyang, 2008.10.10]add

#define WIID_MESSAGELIST					0x30316000			// 316000 ~ 317000 [xialin 2008/12/04]add

#define WIID_PC_SUMMON						0x31001000			// ĳ���� ��ȯ			[10/27/2008 - Duragon]
#define WIID_LOVE							0x31003000			// Love					[09/25/2008 - AJJIYA ]
#define WIID_RANKING                        0x31004000			// ��ŷ					[10/28/2008 - W.Fairy]
#define WIID_PET_SERVICE					0x31005000			// �ֿϵ��� ����		[--/--/---- - W.Fairy]
#define WIID_LOVEMSG_INPUT					0x31006000			// LoveMsgInput			[10/13/2008 - AJJIYA ]
#define WIID_OPTIONRST						0x31007000			// Item Option Re deal	[10/17/2008 - jinhee ]  
#define WIID_LOVEMSG_VIEW					0x31008000			// LoveMsgView			[11/03/2008 - AJJIYA ]


enum FONT_SIZE {
	FONT_SIZE_NULL		= 0,
	FONT_SIZE_SMALL		= 1,
	FONT_SIZE_MEDIUM	= 2,
	FONT_SIZE_LARGE		= 3,
};


//
enum  MesBox_Type{
	MES_OK = 1,
	MES_CANCEL = 2,
};

#define  MES_OKCANCEL    (MES_OK | MES_CANCEL)
