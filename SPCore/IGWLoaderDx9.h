#pragma once

#include <d3d9.h>
#include "winbase.h"
#include "IGWInterface.h"

/* ����GameWidget.dll�еĵ������� */
typedef DECLSPEC_IMPORT bool (WINAPI* PFNInitializeGraphic)(IDirect3DDevice9* Dev9, D3DPRESENT_PARAMETERS* Params, bool HookGameWnd);
typedef DECLSPEC_IMPORT bool (WINAPI* PFNRender)();
//typedef DECLSPEC_IMPORT bool (WINAPI* PFNUpdate)();
typedef DECLSPEC_IMPORT bool (WINAPI* PFNFinalizeGraphic)();
typedef DECLSPEC_IMPORT void (WINAPI* PFNOnDeviceReset)(D3DPRESENT_PARAMETERS* Params);
typedef DECLSPEC_IMPORT void (WINAPI* PFNOnDeviceLost)();
typedef DECLSPEC_IMPORT HRESULT (WINAPI* PFNOnWindowProc)( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
typedef DECLSPEC_IMPORT HRESULT (WINAPI* PFNOnWindowProcEx)( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult);
typedef DECLSPEC_IMPORT HRESULT (WINAPI* PFNRenderEx)(WPARAM wParam, LPARAM lParam);


#pragma pack(push,1)
struct IGWExportDx9
{
	PFNInitializeGraphic		FInitializeGraphic;
	PFNRender					FRender;	
	PFNRenderEx					FRenderEx;
	PFNFinalizeGraphic			FFinalizeGraphic;
	PFNOnDeviceReset			FOnDeviceReset;
	PFNOnDeviceLost				FOnDeviceLost;
	PFNOnWindowProc				FOnIGWWndProc;
	PFNOnWindowProcEx			FOnIGWWndProcEx;
};
#pragma pack(pop)

typedef DECLSPEC_IMPORT bool (WINAPI* PFNGetIGWExportDx9Data)( IGWExportDx9* IGWExportDx9Data );

//��Ⱥ�¼����ͳ������ο�IGWInterface.h�е�IGWUserCommunityInterfaceA����
enum IGW_CommunityEventType {
    ceSetGuildTitle, ceCreateGuild, ceJoinGuild,
    ceQuitGuild, ceAddFriend, ceRemoveFriend, ceMarried, ceDivorced,
    ceJoinMaster, ceLeaveMaster
};


class CIGWLoaderDx9
{
private:
	static HINSTANCE			hInstIGWDll;
	IGWExportDx9*				G_IGWExportDx9;		// D3D9ͼ�νӿں�����
	LPIGWUserInterfaceA			FTUserA ;			// �û��ӿڱ�1
	LPIGWUserInterfaceW			FTUserW ;			// �û��ӿڱ�2
	LPIGWConfigureInterface		FIGWConfigure;		// ���ýӿ�

	LPIGWCustomizeInterfaceA	FIGWCustomizeInterfaceA;		// ���ƵĽӿ�1
	LPIGWCustomizeInterfaceW	FIGWCustomizeInterfaceW;		// ���ƵĽӿ�2
	LPIGWGameAudioSetting		FIGWGameAudioSetting;           // ��Ϸ�������ýӿ�

    LPIGWUserCommunityInterfaceA m_pCommunityInterfaceA;    //��Ⱥ�ӿ�
    LPIGWUserCommunityInterfaceW m_pCommunityInterfaceW;

    LPIGWLocationInterfaceA     m_pLocationInterfaceA;      //λ����Ϣ�ӿ�
    LPIGWLocationInterfaceW     m_pLocationInterfaceW;

	// ���ڿ����Ƿ���ʾ��Ĭ��������ʾ��
	bool				FVisible;

	PFNigwInit			igwInit;
	PFNigwInitExA		igwInitExA;
	PFNigwInitExW		igwInitExW;
	PFNigwSupportW		igwSupportW;
	PFNigwSupportA		igwSupportA;
	PFNigwSupportExA	igwSupportExA;
	PFNigwSupportExW	igwSupportExW;
	PFNigwTerminal		igwTerminal;	// FreeLibraryǰ�����ͷ�Dll�з������Դ
	// ����������ʹ������ӿ�
	bool				bUseIGWSupportEx;
	// ���������Դ
	void CleanupIGWLoader();
	// ��ʼ������ʱ��Ҫ׼������Ϣ
	bool InitCreate();
	// �õ����нӿ���Ϣ���
	bool GetAllIGWInteface();
public:
	CIGWLoaderDx9( const LPGameBasicInfoExA GameInfo );
	CIGWLoaderDx9( const LPGameBasicInfoExW GameInfo );

	~CIGWLoaderDx9(void);

// 
// D3D9ͼ�νӿ�
// 
public:
	// ��ʼ��IGWͼ�β���
	BOOL InitializeGraphic(IDirect3DDevice9* Dev9, D3DPRESENT_PARAMETERS* Params, bool HookGameWnd);

	// ��Ⱦ�����ڲ��Ѿ�����BeginScene��EndScene��ȷ����EndScene֮�������
	BOOL Render();

	// ȷ����BeginScene��EndScene֮�����RenderEx��������ʱδ����Ϊ��չ����
	HRESULT RenderEx(WPARAM wParam, LPARAM lParam);

	// �˳�IGWʱ����
	BOOL FinalizeGraphic();

	// �豸����
	VOID OnDeviceReset(D3DPRESENT_PARAMETERS* Params);

	// �豸��ʧ
	VOID OnDeviceLost();

	// ��Ϣ�������
	HRESULT OnWindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	// ��Ϣ���������չ��
	HRESULT OnWindowProcEx( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lResult);

//
// �û��ӿ�
//
public:
	// ��ʼ����Ϸ��Ϣ
	VOID	InitGameInfoA ( const LPGameBasicInfoA GameInfo ) ;
	VOID	InitGameInfoW ( const LPGameBasicInfoW GameInfo ) ;
	
	// ��¼������Ϸ��¼�ɹ������( LoginType: ��¼���� )
	VOID	LoginA ( const PUserBasicInfoA UserInfo, int LoginType);
	VOID	LoginW ( const PUserBasicInfoW UserInfo, int LoginType);

	// �ǳ�������Ϸ�ǳ������
	VOID	LogoutA () ;
	VOID	LogoutW () ;

	//������ҽ�ɫ��Ϣ����¼�ɹ�����ҽ�ɫ��Ϣ����ʱ����
	VOID	ChangeUserInfoA ( const PUserDetailInfoA UserInfo );
	VOID	ChangeUserInfoW ( const PUserDetailInfoW UserInfo );

	// ����λ����Ϣ
	VOID	ChangeLocationA ( const PUserLocationA pLocation ) ;
	VOID	ChangeLocationW ( const PUserLocationW pLocation ) ;

    //������Ⱥ��Ϣ
    void SetCommunityInfoA(const PUserCharacterInfoA pCharacter);
    void SetCommunityInfoW(const PUserCharacterInfoW pCharacter);

    //��Ⱥ��ص�ͨ�ûص�
    void OnCommunityEventA(int EventType, LPCSTR Target);
    void OnCommunityEventW(int EventType, LPCWSTR Target);
    //��ɫ�����ص�
    void OnLevelUp(int NewLevel);
    //��ɫ���л��е�ְλ�ı�ص�
    void OnGuildTitleChangedA(LPCSTR OldTitle, LPCSTR NewTitle, DWORD Change);
    void OnGuildTitleChangedW(LPCWSTR OldTitle, LPCWSTR NewTitle, DWORD Change);

    //���ý��볡��(����)�ص�
    void SetEnterLocationCallback(const PFNChangeLocationA CBFuncA, const PFNChangeLocationW CBFuncW);

	void Terminal(); // ���IGW�õ�����Դ

	// ����IGW���
	bool GetSelfCursor();
	void SetSelfCursor(const bool value);
	int GetScreenStatus();
	void SetScreenStatus(const int value);
	bool GetScreenEnabled();
	void SetScreenEnabled(const bool value);
	bool GetTaskBarPosition(PPOINT p);
	bool SetTaskBarPosition(const POINT p);
	bool GetFocus();
	void SetFocus(const bool value);

	// ���ƵĽӿ����
	int GetWinPropertyA(LPCSTR WinName, PIGWWinProperty WinProperty);
	int SetWinPropertyA(LPCSTR WinName, PIGWWinProperty WinProperty);
	int GetWinPropertyW(LPCWSTR WinName, PIGWWinProperty WinProperty);
	int SetWinPropertyW(LPCWSTR WinName, PIGWWinProperty WinProperty);
	// �򿪹ر�Widget�ӿ�
	int OpenWidgetA(LPCSTR WidgetNameSpace);
	int CloseWidgetA(LPCSTR WidgetNameSpace);
	int OpenWidgetW(LPCWSTR WidgetNameSpace);
	int CloseWidgetW(LPCWSTR WidgetNameSpace);

	
	// ��Ϸʵ����ؽӿ�
		// ʵ����Ϸ���ֺ���Ч�������
	bool SetAudioSetting(	PFNGetAudioSoundVolume		AGetAudioSoundVolume,	
							PFNSetAudioSoundVolume		ASetAudioSoundVolume,
							PFNGetAudioEffectVolume		AGetAudioEffectVolume,
							PFNSetAudioEffectVolume		ASetAudioEffectVolume	);
	// ֪ͨIGW��ؽӿ�
		// ֪ͨIGW��Ϸ�е����ֻ�����Ч��С�ı䣬������SetAudioSet���óɹ������Ч
	bool NodifyAudioChanged();

	// ���ڿ����Ƿ���ʾIGW����ʹRender()��RenderEx()ʧЧ
	void SetVisible(const bool Value);
	bool GetVisible();
};

extern CIGWLoaderDx9*	g_pCIGWLoaderDx9;
