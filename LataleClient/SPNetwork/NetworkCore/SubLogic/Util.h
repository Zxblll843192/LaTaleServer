// Util.h

#pragma once

extern char* FormattingDateTime(time_t tms,char* buf);

// ���� ����/�ð� ���
extern char* GetCurDateTimeStr(char* buf,char* szFormat);
extern char* GetCurDateStr(char* buf,char* szFormat);

extern TCHAR* GetCurDateTimeStrEx(TCHAR* pszStr,TCHAR* pszFormat);
extern TCHAR* GetCurDateStrEx(TCHAR* pszStr,TCHAR* pszFormat);


extern TCHAR* GetCurrentDir(TCHAR* pszFullPath);

// *.ini ���ϸ� ����
extern void MakeConfigureFullPathName(TCHAR* pszFullPathName);

// FullPath + PartialPath �� FullPath ���
extern TCHAR* MakeFullPath(TCHAR* pFullPath, TCHAR* pPartialPath);
// ���� ������ �м��Ͽ� �������� ���ϸ��� �����Ѵ�.
extern bool MakeSequentialFileName(TCHAR* pszNewFileName,TCHAR* pszOldFileName);
extern bool IsExist(TCHAR* pszFile);

extern void WriteStringToFile(char* msg);

extern void myReportEvent(LPCTSTR *szMsg);

//extern bool GetIPAddress(char* szHostname,char* ipaddress);
//extern void GetLocalIPAddress(char* ipaddress);
extern bool GetPeerInfo(SOCKET socket,TCHAR* pszIPAddress,u_short& usPort);

extern void GetIPs(TCHAR* pszLocalIP,TCHAR* pszPublicIP);


extern void GetOSVersionInfo(OSVERSIONINFO& verInfo);

extern bool GetComputerName(TCHAR* pszComputerName);


#define IS_WHITESPACE(X)	(X==' ' || X=='\t' || X=='\n' || X== '\r' )?true:false
#define IS_SPACE(X)			(X==' ')?true:false


extern TCHAR* RTrim(TCHAR* pszStr);
extern TCHAR* LTrim(TCHAR* pszStr);

extern TCHAR* Trim(TCHAR* pszStr);

// pszStr���� ������ �ʴ� ���ڰ� �ִ��� Ȯ��. TEXT(" ~!@#$%^&*()+-=|\\{}[]:;\"\'`<>.,?/")
extern bool CheckMaskString(TCHAR* pszStr);

// �ش� ����̺��� ��밡�� �뷮 ���
extern BOOL GetDiscFreeSpace(LPCTSTR lpszDrive, DWORDLONG* pnFree);

extern void SetThreadName(DWORD dwThreadID, LPCSTR szThreadName);

// (int)�� ���� �Ͻ������� ȣ��Ǵ� ftol2() �Լ��� ������带 ������.
#if 1 //def _USING_MY_FTOL
inline int my_ftol(float f) 
{ 
	int rvalue; 

	_asm { 
		fld		f 
		fistp   rvalue 
	} 

	return rvalue; 
} 
#endif

typedef struct tagTHREADNAME_INFO
{
	DWORD dwType;     // must be 0x1000
	LPCSTR szName;    // pointer to name (in user address space)
	DWORD dwThreadID; // thread ID (-1 = caller thread)
	DWORD dwFlags;    // reserved for future use, must be zero
} THREADNAME_INFO;
