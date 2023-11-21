
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#ifndef __ERROR_LOG__
#define __ERROR_LOG__

#ifndef NO_
#define NO_		0
#define YES_	1
#endif


#define ErrorFLogs	ErrorFLog::GetInstance()
extern bool g_bFileLog ;

class ErrorFLog
{
public:
	static ErrorFLog* GetInstance() ;
	static void Release() ;

	~ErrorFLog() ;
	void SetFileLog(bool isFile) ;
	void Error_Log(const TCHAR* msg,...) ;
	void Sys_Log(const TCHAR* msg,...) ;
	//void Error_Log(const TCHAR* msg) ;

protected:
	ErrorFLog();

	const char*  GetWorkPath();
	const char*  SetWorkPath(char* pBuff );
	const char*  GetLogFileName();
	const char*  SetLogFileName(char* pBuff);
	const char*  GetSysFileName();
	const char*  SetSysFileName(char* pBuff);
	const char*  GetLogPath();
	const char*  SetLogPath(char* pBuff);

private:
	static ErrorFLog*	m_pInstance;
	bool m_bIsFileLog ;				//���Ϸα� ������ ����
	bool m_bSysLogSet ;
	char m_strWorkPath[256] ;		//���� ���� ���.
	char m_strLogPath[256] ;		//�α� ���� ���.
	char m_strLogFileName[256] ;	//�α� ���� ��.
	char m_strSysFileName[256] ;	//�α� ���� ��.


};

#endif			// __ERROR_LOG__