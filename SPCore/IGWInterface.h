#pragma once
#pragma pack(push,1)

const static BYTE IGW_DICTIONARY[256] =
{
    0xF0, 0x1F, 0x0B, 0x64, 0xCD, 0x34, 0x4D, 0x10, 0x8C, 0xA5, 0xA3, 0xD9, 0x8D, 0xDC, 0xCF, 0xD1,
        0x4A, 0x76, 0x95, 0x07, 0x13, 0x3D, 0x4B, 0xDD, 0xBF, 0x5F, 0x44, 0x7D, 0xFB, 0xD5, 0x8B, 0x04,
        0x5A, 0x6F, 0xF1, 0x85, 0x42, 0x99, 0x4E, 0xE6, 0xA4, 0x8C, 0xE6, 0x83, 0xBB, 0x11, 0xF1, 0xE3,
        0xA0, 0xE2, 0x8D, 0x03, 0xAE, 0xE1, 0x49, 0x1A, 0xA1, 0x34, 0xDC, 0xDD, 0x84, 0x8B, 0xBA, 0x8A,
        0x65, 0xB8, 0x68, 0x0B, 0xD3, 0x0C, 0x44, 0xD8, 0x85, 0xA3, 0xA3, 0x2C, 0xD7, 0xDE, 0xA5, 0x44,
        0x39, 0x43, 0x42, 0x70, 0x84, 0x4D, 0x44, 0xE8, 0xB0, 0x86, 0x61, 0x33, 0x19, 0x92, 0x55, 0xAF,
        0x06, 0x16, 0x61, 0xF1, 0x53, 0x7C, 0x44, 0x72, 0x9D, 0x74, 0xAD, 0x08, 0xEC, 0xAE, 0x1E, 0x23,
        0x5E, 0xAD, 0x93, 0xD2, 0x4E, 0x76, 0x44, 0x49, 0x8F, 0x71, 0x38, 0x8B, 0xD5, 0x4B, 0xA7, 0x79,
        0x0E, 0xC6, 0x08, 0xD0, 0xC7, 0x16, 0x40, 0x7B, 0x8D, 0x1A, 0x68, 0x38, 0x9F, 0xC5, 0x17, 0x67,
        0xF6, 0x80, 0x5E, 0x9F, 0xD3, 0x45, 0x4F, 0x8B, 0xBD, 0x56, 0x4E, 0xE0, 0x1B, 0xC5, 0x2D, 0xD0,
        0x6F, 0x83, 0x35, 0xB8, 0xE1, 0x88, 0x46, 0x59, 0xA7, 0xDE, 0x9C, 0x17, 0xEE, 0x31, 0x8C, 0x6F,
        0x48, 0xF3, 0x6F, 0xCA, 0x88, 0x87, 0x46, 0x5D, 0xB1, 0xA7, 0x4E, 0x14, 0xC7, 0x0F, 0x79, 0x8A,
        0xAB, 0xB2, 0xB7, 0xCB, 0xF5, 0xB5, 0x4A, 0x62, 0xA7, 0xEF, 0xA0, 0xBF, 0x8B, 0x6D, 0xAB, 0x8C,
        0xB2, 0xA6, 0x77, 0xFD, 0x4E, 0xC9, 0x4F, 0xE4, 0xBD, 0xAE, 0x28, 0x1B, 0xD9, 0xAA, 0x8E, 0xC2,
        0x9D, 0x42, 0x28, 0xF6, 0x2E, 0x0A, 0x4C, 0x5C, 0x8D, 0x86, 0xDD, 0x4A, 0xD1, 0xD6, 0x7C, 0x74,
        0xE4, 0x0B, 0xBF, 0x2E, 0xAA, 0x03, 0x49, 0x6E, 0xA6, 0xB1, 0x89, 0xEF, 0xB3, 0x15, 0x95, 0x79
};

// ��ǰ IGW �ӿڰ汾
#define IGW_VERSION                 0x010

// IGW ����ֵ
#define IGW_OK                      0
#define IGW_FALSE                   1

// IGW ��������붨��
// ͼ�νӿ�
#define igwGraphicGDI               0x0000
#define igwGraphicDDraw             0x0001
#define igwGraphicD3D8              0x0002
#define igwGraphicD3D9              0x0003
#define igwGraphicD3D10             0x0004
#define igwGraphicOpenGL            0x0005
// �û��ӿ�
#define igwUserInterface            0x0100
// �û���Ⱥ�ӿ�
#define igwUserCommunityInterface   0x0101

// IGW���ýӿ� (���ڶ�̬����IGW��һЩ����
#define igwConfigureInterface       0x0200

// Ϊ��Ϸ���ƵĽӿ� 
#define igwCustomizeInterface		0x0400
// λ����Ϣ�ӿ�
#define igwLocationInterface        0x0401

// ��Ϸ���ܽӿ�
#define igwGameSetting      		0x0500
#define igwGameAudioSetting 		0x0501

#define igwDirectDraw  0x0001
#define igwDirectDraw2 0x0002
#define igwDirectDraw3 0x0003
#define igwDirectDraw4 0x0004
#define igwDirectDraw7 0x0005

// ����Ϊͼ�νӿڶ���



// ����Ϊ�û��ӿڶ���

// ��Ϸ����
#define GAMETYPE_UNKNOWN            0
#define GAMETYPE_GDI                1
#define GAMETYPE_DDRAW              2
#define GAMETYPE_D3D8               3
#define GAMETYPE_D3D9               4
#define GAMETYPE_D3D10              5
#define GAMETYPE_OPENGL             6

// ��¼����
#define LOGINTYPE_PTACCOUNT         0    // ʢ��ͨ��֤ + ����//�ʺ絺
#define LOGINTYPE_PTNUMID           1    // ����ID + ����
#define LOGINTYPE_PTACCOUNTWITHEKEY 2    // ʢ��ͨ��֤ + ���� + �ܱ�//�ʺ絺
#define LOGINTYPE_PTNUMIDWITHEKEY   3    // ����ID + ���� + �ܱ�
#define LOGINTYPE_SSOACCESSKEY      4    // SSO AccessKey


// IGW��Ļ״̬����
#define igwScreenNone    0      // Screenû�б�����
#define igwScreenNormal  1      // ������ʾ״̬
#define igwScreenMini    2      // ��С��״̬

// ���¼�¼���е� LPCSTR/LPCWSTR ָ����ַ��������û���ر�˵�����䳤��
// �������Ϊ128�ַ�(����0��β���ڣ�ע�����ַ��������ֽ�)�����������ض�

// ��Ϸ������Ϣ
typedef struct _GameBasicInfoA {
    DWORD   cbSize;       // sizeof(GameBasicInfoA) 
    int     GameID;       // ʢ��ͳһ��ϷID
    LPCSTR  GameName;     // ��Ϸ����
    LPCSTR  GameVer;      // ��Ϸ�汾
    int     GameType;     // ��Ϸ����
    int     MaxUser;      // ��Ϸͬʱ֧���û���Ŀ��ͨ��Ϊ1
    // 2008.4.9
    LPCSTR  SPID;         // SPID
} GameBasicInfoA, *PGameBasicInfoA, *LPGameBasicInfoA;

typedef struct _GameBasicInfoW {
    DWORD   cbSize;       // sizeof(GameBasicInfoW) 
    int     GameID;       // ʢ��ͳһ��ϷID
    LPCWSTR GameName;     // ��Ϸ����
    LPCWSTR GameVer;      // ��Ϸ�汾
    int     GameType;     // ��Ϸ����
    int     MaxUser;      // ��Ϸͬʱ֧���û���Ŀ��ͨ��Ϊ1
    // 2008.4.9
    LPCWSTR SPID;         // SPID
} GameBasicInfoW, *PGameBasicInfoW, *LPGameBasicInfoW;

// ��Ϸ������Ϣ(Ex��, igwInitExʹ��)
typedef struct _GameBasicInfoExA {
	DWORD		cbSize;			// = SizeOf(TGameBasicInfoA)
	int			GameID;			// ʢ��ͳһ��ϷID
	LPCSTR		GameName;		// ��Ϸ����
	LPCSTR		GameVer;		// ��Ϸ�汾
	int			GameType;		// ��Ϸ����
	int			MaxUser;		// ��Ϸͬʱ֧���û���Ŀ��ͨ��Ϊ1
	LPCSTR		GameArea;		// ��Ϸ����������		(������Ҫ��)
	LPCSTR		GameServer;		// ��Ϸ���ڷ���������	(������Ҫ��)
	int			GameAreaID;		// ��Ϸ��ID				(ע�⣺������ʱ��-1)
	int			GameServerID;	// ��Ϸ��������ID		(ע�⣺������ʱ��-1)
} GameBasicInfoExA, *PGameBasicInfoExA, *LPGameBasicInfoExA;

typedef struct _GameBasicInfoExW {
	DWORD		cbSize;			// = SizeOf(TGameBasicInfoA)
	int			GameID;			// ʢ��ͳһ��ϷID
	LPCWSTR		GameName;		// ��Ϸ����
	LPCWSTR		GameVer;		// ��Ϸ�汾
	int			GameType;		// ��Ϸ����
	int			MaxUser;		// ��Ϸͬʱ֧���û���Ŀ��ͨ��Ϊ1
	LPCWSTR		GameArea;		// ��Ϸ����������		(������Ҫ��)
	LPCWSTR		GameServer;		// ��Ϸ���ڷ���������	(������Ҫ��)
	int			GameAreaID;		// ��Ϸ��ID				(ע�⣺������ʱ��-1)
	int			GameServerID;	// ��Ϸ��������ID		(ע�⣺������ʱ��-1)
} GameBasicInfoExW, *PGameBasicInfoExW, *LPGameBasicInfoExW;


// �û�������Ϣ����¼�ã�
typedef struct _UserBasicInfoA {
    DWORD   cbSize;                    // sizeof(UserBasicInfoA)
    LPCSTR  PTAccount;                 // �û��˺�
    LARGE_INTEGER PTNumID;             // �û�����ID
    BYTE    Password[64];              // �û�����
    LPCSTR  EKey;                      // �ܱ�
    BYTE    SSOAccessKey[128];         // SSO AccessKey
} UserBasicInfoA, *PUserBasicInfoA, *LPUserBasicInfoA;

typedef struct _UserBasicInfoW {
    DWORD   cbSize;                    // sizeof(UserBasicInfoW)
    LPCWSTR PTAccount;                 // �û��˺�
    LARGE_INTEGER PTNumID;             // �û�����ID
    BYTE    Password[64];              // �û�����
    LPCWSTR EKey;                      // �ܱ�
    BYTE    SSOAccessKey[128];         // SSO AccessKey
} UserBasicInfoW, *PUserBasicInfoW, *LPUserBasicInfoW;

// �û���ϸ��Ϣ
typedef struct _UserDetailInfoA {
    DWORD   cbSize;                    // sizeof(UserDetailInfoA)
    LPCSTR  NickName;                  // �ǳ�
    int     Gender;                    // �Ա�(0: Ů; 1: ��)
    LPCSTR  GameArea;                  // ��Ϸ������
    LPCSTR  GameServer;                // ��Ϸ���ڷ�����
    int     GameAreaID;                // ʢ��ͳһ��Ϸ����ID��Ĭ��-1��      // 2008.3.5 ������Ϸ��������ID��Ϣ
    int     GameServerID;              // ʢ��ͳһ��Ϸ������ID��Ĭ��-1��
    // more
} UserDetailInfoA, *PUserDetailInfoA, *LPUserDetailInfoA;

typedef struct _UserDetailInfoW {
    DWORD   cbSize;                    // sizeof(UserDetailInfo)
    LPCWSTR NickName;                  // �ǳ�
    int     Gender;                    // �Ա�(0: Ů; 1: ��)
    LPCWSTR GameArea;                  // ��Ϸ������
    LPCWSTR GameServer;                // ��Ϸ���ڷ�����
    int     GameAreaID;                // ʢ��ͳһ��Ϸ����ID��Ĭ��-1��      // 2008.3.5 ������Ϸ��������ID��Ϣ
    int     GameServerID;              // ʢ��ͳһ��Ϸ������ID��Ĭ��-1��
    // more
} UserDetailInfoW, *PUserDetailInfoW, *LPUserDetailInfoW;

// �û�λ����Ϣ(�� Path + Room ��ɣ��������Ϊ��λ�ļ��� Path + File)
// ע��Path/Room������Ϸ�Զ�����ڲ����ݣ���Ϸ�Լ���⼴��
//     PathTitle/RoomTitle����ʾ���û����ı���
typedef struct _UserLocationA {
    LPCSTR  Path;                      // ·��Ψһ��ʶ(����ж༶����"/"���ָ���)
    LPCSTR  PathTitle;                 // ·������(����ж༶����"/"���ָ���)
    LPCSTR  Room;                      // ����Ψһ��ʶ
    LPCSTR  RoomTitle;                 // �������
} UserLocationA, *PUserLocationA, *LPUserLocationA;

typedef struct _UserLocationW {
    LPCWSTR Path;                      // ·��Ψһ��ʶ(����ж༶����"/"���ָ���)
    LPCWSTR PathTitle;                 // ·������(����ж༶����"/"���ָ���)
    LPCWSTR Room;                      // ����Ψһ��ʶ
    LPCWSTR RoomTitle;                 // �������
} UserLocationW, *PUserLocationW, *LPUserLocationW;

// �û���Ⱥ��Ϣ
typedef struct _UserCharacterInfoA{
    LPCSTR      ChracterName;        // ��ɫ����
    DWORD       Gender;              // �Ա�(0: Ů; 1: ��)
    LPCSTR      Occupation;          // ��ɫְҵ
    int         Level;               // ��ɫ�ȼ�
    LPCSTR      GuildName;           // �����л�
    LPCSTR      GuildTitle;          // ���л��е�ͷ��
}UserCharacterInfoA, *PUserCharacterInfoA;

typedef struct _UserCharacterInfoW{
    LPCWSTR     ChracterName;        // ��ɫ����
    DWORD       Gender;              // �Ա�(0: Ů; 1: ��)
    LPCWSTR     Occupation;          // ��ɫְҵ
    int         Level;               // ��ɫ�ȼ�
    LPCWSTR     GuildName;           // �����л�
    LPCWSTR     GuildTitle;          // ���л��е�ͷ��
}UserCharacterInfoW, *PUserCharacterInfoW;


// GameWidget.dll�е����Ľӿڵ����Ͷ���
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwInit)(DWORD dwVersion);
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwInitExA)(DWORD dwVersion,  const LPGameBasicInfoExA GameInfo );
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwInitExW)(DWORD dwVersion,  const LPGameBasicInfoExW GameInfo );
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwSupportA)(int nCode, void* FuncGroup);
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwSupportW)(int nCode, void* FuncGroup);
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwSupportExA)(int nCode, void* FuncGroup, int FuncGroupSize);
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwSupportExW)(int nCode, void* FuncGroup, int FuncGroupSize);
typedef DECLSPEC_IMPORT int (WINAPI* PFNigwTerminal)();


// ��ʼ����Ϸ������Ϣ
typedef DECLSPEC_IMPORT void (WINAPI* PFNInitGameInfoA)(const LPGameBasicInfoA GameInfo);
typedef DECLSPEC_IMPORT void (WINAPI* PFNInitGameInfoW)(const LPGameBasicInfoW GameInfo);
// ��¼������Ϸ��¼�ɹ������
// LoginType: ��¼���ͣ���ο�����LOGINTYPE�ĳ�������
typedef DECLSPEC_IMPORT void (WINAPI* PFNLoginA)(const PUserBasicInfoA UserInfo, int LoginType);
typedef DECLSPEC_IMPORT void (WINAPI* PFNLoginW)(const PUserBasicInfoW UserInfo, int LoginType);
// �ǳ�������Ϸ�ǳ������
typedef DECLSPEC_IMPORT void (WINAPI* PFNLogoutA)(void);
typedef DECLSPEC_IMPORT void (WINAPI* PFNLogoutW)(void);
//������ҽ�ɫ��Ϣ����¼�ɹ�����ҽ�ɫ��Ϣ����ʱ����
typedef DECLSPEC_IMPORT void (WINAPI* PFNChangeUserInfoA)(const PUserDetailInfoA UserInfo);
typedef DECLSPEC_IMPORT void (WINAPI* PFNChangeUserInfoW)(const PUserDetailInfoW UserInfo);
// ����λ����Ϣ
typedef void (WINAPI* PFNChangeLocationA)(const PUserLocationA Location);
typedef void (WINAPI* PFNChangeLocationW)(const PUserLocationW Location);


// ��ɫ�����¼�
typedef void (WINAPI* pfnLevelUpEventA)(int Level);
typedef void (WINAPI* pfnLevelUpEventW)(int Level);
// ��ɫͷ�θı��¼�
typedef void (WINAPI* pfnGuildTitleChangeEventA) (
    LPCSTR OldTitle,    //ԭͷ��
    LPCSTR NewTitle,    //��ͷ��
    DWORD Change        //0:���ԣ�1:��ְ��2:��ְ
    ); 
typedef void (WINAPI* pfnGuildTitleChangeEventW) (LPCWSTR OldTitle, LPCWSTR NewTitle, DWORD Change); 
// ��ý�ɫ�ƺţ�ͷ�Σ��¼�
typedef void (WINAPI* pfnSetGuildTitleEventA) (LPCSTR Title); 
typedef void (WINAPI* pfnSetGuildTitleEventW) (LPCWSTR Title); 
// ����/����/�˳��л��¼�
typedef void (WINAPI* pfnGuildRelationChangeEventA) (LPCSTR GuildName); 
typedef void (WINAPI* pfnGuildRelationChangeEventW) (LPCWSTR GuildName); 
// �ı���Ŀ��Ĺ�ϵ���¼�������
//   ����/ɾ�������¼�
//   ��ʦ/��ͽ
//   ���/����¼�
typedef void (WINAPI* pfnChangeRelationshipEventA)(LPCSTR Target); 
typedef void (WINAPI* pfnChangeRelationshipEventW)(LPCWSTR Target); 
// ����û�������Ϣ
typedef void (WINAPI* pfnSetCharacterInfoA)(const PUserCharacterInfoA CharacterInfo);
typedef void (WINAPI* pfnSetCharacterInfoW)(const PUserCharacterInfoW CharacterInfo);

//-------------------------------------------------------------------------------------------
// ��2�ֵ�¼��ʽ

typedef struct LOGINRESULT {
    DWORD dwSize;                      // sizeof(LoginResult)��Ϊ�Ժ������ṩ����           
    char token[1024];
    char sdid[20];
    char idcard[20];

    LOGINRESULT()
    {
        dwSize = sizeof(LOGINRESULT);
        memset(token, 0, 1024);
        memset(sdid, 0, 20);
        memset(idcard, 0, 20);
    }
} LoginResult, *PLoginResult;

// ��¼�ص�����
// ErrorCode:     ��¼���ش������
// LoginResult:   ��¼���ؽ����ֻ�� ErrorCode = LOGIN_OK ʱ����Ч
// UserData:      �ڵ���ShowLoginDialogʱ������û�����
// Reserved:      �������ݲ�ʹ�ã�Ŀǰ����Ϊ0(������ShowLoginDialog�д����Reserved����)
// ����ֵ:        ΪTrue���رնԻ���ΪFalse���ر�
typedef BOOL (CALLBACK* LOGINCALLBACKPROC)(int ErrorCode, const PLoginResult LoginResult, int UserData, int Reserved);

// ��ʾ��¼�Ի���
// Callback:      �ص�����
// UserData:      �û����ݣ���Callback�д���
// Reserved:      �������ݲ�ʹ�ã�����Ϊ0
// ����ֵ:        Ϊ0��ʾ�ɹ�
typedef DECLSPEC_IMPORT int (WINAPI* PFNShowLoginDialog)(const LOGINCALLBACKPROC Callback, int UserData, int Reserved);
// ��ʾ��ֵ�Ի���
// Reserved1:     �������ݲ�ʹ�ã�����Ϊ0
// Reserved2:     �������ݲ�ʹ�ã�����Ϊ0
// ����ֵ:        Ϊ0��ʾ�ɹ�
typedef DECLSPEC_IMPORT int (WINAPI* PFNShowPaymentDialog)(int Reserved1, int Reserved2);
// ��ʾ֧���Ի���
// gameUserId:    �����Ϸ�ʺ�
// spSiteCode:    Shop Server��Ψһ����. ��BillingGate Systemͳһ����ı���
// orderId:       �������룬��ʶΨһ��һ����������
// payInfo:       ������Ϣ(������߷��ã�����ֻ֧��ʢ����(3)��������)����ʽ��3|amount
// goodsNum:      ��Ч��������
// goodsInfo:     ������ϸ��Ϣ,�����ֶε���ʽ��ʾitemid,itemnum,itemattr#...... itemid,itemnum,itemattr��
// signedString:  ǩ�����򣺰����ַ����ķ�ʽ��uidType + userId + gameUserID + spSiteCode + payInfo + goodsNum + goodsInfo + �������� ��ӣ�Ȼ��ʹ��MD5�㷨����Щ��Ϣ���м��ܵ�ֵ����������:BillingGate Systemͳһ����ĸ�spSiteCode��Ӧ�ı���
// sendItemUrl:   ֪ͨ�����ߵĻص�webservice��Url
// reserveInt:    ��չ�ֶΣ��ɲ���д
// reserveString: ��չ�ֶΣ��ɲ���д
// ����ֵ:        Ϊ0��ʾ�ɹ�
typedef DECLSPEC_IMPORT int (WINAPI* PFNShowBillingDialog)(const BSTR gameUserId,
                                                           const BSTR spSiteCode, const BSTR orderId, const BSTR payInfo, int goodsNum,
                                                           const BSTR goodsInfo, const BSTR signedString, const BSTR sendItemUrl,
                                                           int reserveInt, const BSTR reserveString);
// ��ȡ����������Ϣ
typedef DECLSPEC_IMPORT void (WINAPI* PFNGetErrorDesc)(int ErrorCode, BSTR& Desc);


//-------------------------------------------------------------------------------------------
// IGW���ýӿ����
typedef DECLSPEC_IMPORT void (WINAPI* PFNSetSelfCursor)(const bool value);
typedef DECLSPEC_IMPORT bool (WINAPI* PFNGetSelfCursor)();

// ע��IGW��Ļ���������IGW������ʾ�Ŀ���Ԫ��
// ��ȡIGW��ǰ��Ļ״̬��ֵΪ���涨���igwScreenNone��igwScreenNormal��igwScreenMini
typedef DECLSPEC_IMPORT int (WINAPI* PFNGetScreenStatus)();
// ������Ļ״̬����valueֵΪigwScreenNormal��igwScreenMini
typedef DECLSPEC_IMPORT void (WINAPI* PFNSetScreenStatus)(const int value);
// ��ȡ��ǰ��Ļ����״̬,falseΪ�����ã�trueΪ����
typedef DECLSPEC_IMPORT bool (WINAPI* PFNGetScreenEnabled)();
// ���õ�ǰ��Ļ����״̬,falseΪ�����ã�trueΪ����
typedef DECLSPEC_IMPORT void (WINAPI* PFNSetScreenEnabled)(const bool value);
// ��ȡ��ǰTaskBar��λ�� p����ΪNULL
typedef DECLSPEC_IMPORT bool (WINAPI* PFNGetTaskBarPosition)(PPOINT p);
// ���õ�ǰTaskBar��λ��
typedef DECLSPEC_IMPORT bool (WINAPI* PFNSetTaskBarPosition)(const POINT p);
typedef DECLSPEC_IMPORT bool (WINAPI* PFNGetFocus)();
typedef DECLSPEC_IMPORT void (WINAPI* PFNSetFocus)(const bool value);



// IGW UserInterface
typedef struct _IGWUserInterfaceA {
    PFNInitGameInfoA   InitGameInfo;     // ��ʼ����Ϸ������Ϣ
    PFNLoginA          Login;            // ��¼
    PFNLogoutA         Logout;           // �ǳ�
    PFNChangeUserInfoA ChangeUserInfo;   // ��ʼ����ҽ�ɫ��ϸ��Ϣ
    PFNChangeLocationA ChangeLocation;   // λ����Ϣ�ı�
    // 2008.4.9 ���ӵ�2�ֵ�¼��ʽ
    PFNShowLoginDialog   ShowLoginDialog;     // ��¼
    PFNShowPaymentDialog ShowPaymentDialog; // ��ֵ
    PFNShowBillingDialog ShowBillingDialog; // ֧��
    PFNGetErrorDesc      GetErrorDesc;        // ��ȡ����������Ϣ
} IGWUserInterfaceA, *PIGWUserInterfaceA, *LPIGWUserInterfaceA;

typedef struct _IGWUserInterfaceW {
    PFNInitGameInfoW   InitGameInfo;     // ��ʼ����Ϸ������Ϣ
    PFNLoginW          Login;            // ��¼
    PFNLogoutW         Logout;           // �ǳ�
    PFNChangeUserInfoW ChangeUserInfo;   // ��ʼ����ҽ�ɫ��ϸ��Ϣ
    PFNChangeLocationW ChangeLocation;   // λ����Ϣ�ı�
    // 2008.4.9 ���ӵ�2�ֵ�¼��ʽ
    PFNShowLoginDialog   ShowLoginDialog;   // ��¼
    PFNShowPaymentDialog ShowPaymentDialog; // ��ֵ
    PFNShowBillingDialog ShowBillingDialog; // ֧��
    PFNGetErrorDesc      GetErrorDesc;      // ��ȡ����������Ϣ
} IGWUserInterfaceW, *PIGWUserInterfaceW, *LPIGWUserInterfaceW;


// IGW Configure
typedef struct _IGWConfigureInterface{
    PFNGetSelfCursor		GetSelfCursor;      // �õ���ǰIGW�����ָ�����״̬ trueΪ�Ի� falseΪ������
    PFNSetSelfCursor		SetSelfCursor;      // ����IGW������״̬������ͬ��
    PFNGetScreenStatus		GetScreenStatus;    // ��ȡIGW��Ļ״̬��ֵΪ���涨���igwScreenNone��igwScreenNormal��igwScreenMini
    PFNSetScreenStatus		SetScreenStatus;    // ������Ļ״̬����valueֵΪigwScreenNormal��igwScreenMini
    PFNGetScreenEnabled		GetScreenEnabled;   // ��ȡ��Ļ����״̬
    PFNSetScreenEnabled		SetScreenEnabled;   // ������Ļ����״̬
    PFNGetTaskBarPosition	GetTaskBarPosition; // ��ȡ�����������λ��
    PFNSetTaskBarPosition	SetTaskBarPosition; // ���������������λ��
    PFNGetFocus				GetFocus;			// ��ȡ��ǰIGW�Ƿ��ڽ���״̬trueΪ����״̬��falseû�н���״̬
    PFNSetFocus				SetFocus;			// ����IGW��ǰ�����н���trueΪ�н��㣬false���޽���
} IGWConfigureInterface, *PIGWConfigureInterface, *LPIGWConfigureInterface;


// 08-05-15 ��Ⱥ���罻����Ľӿ�
typedef struct _IGWUserCommunityInterfaceA{
    pfnSetCharacterInfoA           SetCharacterInfo;     //���ý�ɫ��Ϣ
    pfnLevelUpEventA               OnLevelUp;            // ����
    pfnGuildTitleChangeEventA      OnGuildTitleChanged;  // �л�ͷ�θı�
    pfnSetGuildTitleEventA         OnSetGuildTitle;      // ����л�ͷ��
    pfnChangeRelationshipEventA    OnAddFriend;          // ���Ӻ���
    pfnChangeRelationshipEventA    OnRemoveFriend;       // ɾ������
    pfnGuildRelationChangeEventA   OnCreateGuild;        // �����л�
    pfnGuildRelationChangeEventA   OnJoinGuild;          // �����л�
    pfnGuildRelationChangeEventA   OnQuitGuild;          // �˳��л�
    pfnChangeRelationshipEventA    OnMarried;            // ���
    pfnChangeRelationshipEventA    OnDivorced;           // ���
    pfnChangeRelationshipEventA    OnJoinMaster;         // ��ʦ
    pfnChangeRelationshipEventA    OnLeaveMaster;        // ����ʦͽ��ϵ
}IGWUserCommunityInterfaceA, *PIGWUserCommunityInterfaceA, *LPIGWUserCommunityInterfaceA;

typedef struct _IGWUserCommunityInterfaceW{
    pfnSetCharacterInfoW           SetCharacterInfo;     //���ý�ɫ��Ϣ
    pfnLevelUpEventW               OnLevelUp;            // ����
    pfnGuildTitleChangeEventW      OnGuildTitleChanged;  // �л�ͷ�θı�
    pfnSetGuildTitleEventW         OnSetGuildTitle;      // ����л�ͷ��
    pfnChangeRelationshipEventW    OnAddFriend;          // ���Ӻ���
    pfnChangeRelationshipEventW    OnRemoveFriend;       // ɾ������
    pfnGuildRelationChangeEventW   OnCreateGuild;        // �����л�
    pfnGuildRelationChangeEventW   OnJoinGuild;          // �����л�
    pfnGuildRelationChangeEventW   OnQuitGuild;          // �˳��л�
    pfnChangeRelationshipEventW    OnMarried;            // ���
    pfnChangeRelationshipEventW    OnDivorced;           // ���
    pfnChangeRelationshipEventW    OnJoinMaster;         // ��ʦ
    pfnChangeRelationshipEventW    OnLeaveMaster;        // ����ʦͽ��ϵ
}IGWUserCommunityInterfaceW, *PIGWUserCommunityInterfaceW, *LPIGWUserCommunityInterfaceW;

// λ����Ϣ�ӿ�
typedef struct _IGWLocationInterfaceA{
    PFNChangeLocationA Enter;       // ����λ�ã����䣩
}IGWLocationInterfaceA, *PIGWLocationInterfaceA, *LPIGWLocationInterfaceA;

typedef struct _IGWLocationInterfaceW{
    PFNChangeLocationW Enter;       // ����λ�ã����䣩
}IGWLocationInterfaceW, *PIGWLocationInterfaceW, *LPIGWLocationInterfaceW;


// ���Ƶ���չ�ӿ����Ͷ���
#define igwWindowsNone		0      // ����û�б�����
#define igwWindowsShow		1      // ������ʾ״̬
#define igwWindowsHide		2      // ��������
// ��������
#define igwWindowsType_None		0	// δ֪����
#define igwWindowsType_ToolBar	1	// ������
#define igwWindowsType_Widget	2  // Widget����

// �������Խṹ����
typedef struct _IGWWinProperty{
    int Type;          // ��������(ֻ���ڱ�ʶ�������ͣ�������Ч)
    int Status;        // ����״̬
    // ������λ�á������Ϣ
    int Left;
    int Top;
    int Width;
    int Height;	
} IGWWinProperty, *PIGWWinProperty, *LPIGWWinProperty;


typedef DECLSPEC_IMPORT int (WINAPI* PFNGetWinPropertyA)(LPCSTR WinName, PIGWWinProperty WinProperty);
typedef DECLSPEC_IMPORT int (WINAPI* PFNSetWinPropertyA)(LPCSTR WinName, PIGWWinProperty WinProperty);
typedef DECLSPEC_IMPORT int (WINAPI* PFNGetWinPropertyW)(LPCWSTR WinName, PIGWWinProperty WinProperty);
typedef DECLSPEC_IMPORT int (WINAPI* PFNSetWinPropertyW)(LPCWSTR WinName, PIGWWinProperty WinProperty);

typedef DECLSPEC_IMPORT int (WINAPI* PFNOpenWidgetA)(LPCSTR WidgetNameSpace);
typedef DECLSPEC_IMPORT int (WINAPI* PFNOpenWidgetW)(LPCWSTR WidgetNameSpace);
typedef DECLSPEC_IMPORT int (WINAPI* PFNCloseWidgetA)(LPCSTR WidgetNameSpace);
typedef DECLSPEC_IMPORT int (WINAPI* PFNCloseWidgetW)(LPCWSTR WidgetNameSpace);


typedef struct _IGWCustomizeInterfaceA{
    PFNGetWinPropertyA		GetWinProperty;
    PFNSetWinPropertyA		SetWinProperty;
    PFNOpenWidgetA			OpenWidget;
    PFNCloseWidgetA			CloseWidget;
} IGWCustomizeInterfaceA, *PIGWCustomizeInterfaceA, *LPIGWCustomizeInterfaceA;

typedef struct _IGWCustomizeInterfaceW{
    PFNGetWinPropertyW		GetWinProperty;
    PFNSetWinPropertyW		SetWinProperty;
    PFNOpenWidgetW			OpenWidget;
    PFNCloseWidgetW			CloseWidget;
} IGWCustomizeInterfaceW, *PIGWCustomizeInterfaceW, *LPIGWCustomizeInterfaceW;


// ע������ֵ����Ч��Χ��0-100
typedef DECLSPEC_IMPORT void (WINAPI* PFNNodifyAudioVolumeChanged)();
typedef DECLSPEC_IMPORT void (WINAPI* PFNSetAudioSoundVolume)(DWORD NewVolume);
typedef DECLSPEC_IMPORT DWORD (WINAPI* PFNGetAudioSoundVolume)();
typedef DECLSPEC_IMPORT void (WINAPI* PFNSetAudioSoundVolume)(DWORD NewVolume);
typedef DECLSPEC_IMPORT DWORD (WINAPI* PFNGetAudioEffectVolume)();
typedef DECLSPEC_IMPORT void (WINAPI* PFNSetAudioEffectVolume)(DWORD NewVolume);

typedef struct _IGWGameAudioSetting{
    PFNNodifyAudioVolumeChanged NodifyAudioVolumeChanged;
    PFNGetAudioSoundVolume		GetAudioSoundVolume;
    PFNSetAudioSoundVolume		SetAudioSoundVolume;
    PFNGetAudioEffectVolume		GetAudioEffectVolume;
    PFNSetAudioEffectVolume		SetAudioEffectVolume;
} IGWGameAudioSetting, *PIGWGameAudioSetting, *LPIGWGameAudioSetting;


#pragma pack(pop)







