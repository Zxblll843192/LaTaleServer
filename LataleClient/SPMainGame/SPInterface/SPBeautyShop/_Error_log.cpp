
/**
@file 
@author ��ȭ��( duragon@empal.com )
@date 2007/01/25(��)

@section example ��뿹
	ErrorFlog::GetInstance()->SetFileLog(true) ;
	ErrorFlog::GetInstance()->ErrorLog("Errorlog�����Դϴ�. %d", 1) ; 
	ErrorFlog::GetInstance()->ErrorLog("log�����Դϴ�.") ; 
*/

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include "_Error_log.h"

#define ERROR_FILE_LOG		0

ErrorFLog* ErrorFLog::m_pInstance = NULL;
bool g_bFileLog = false ;					// Argument�� ���ؼ� FileLog  /FLOG


ErrorFLog::ErrorFLog()
: m_bIsFileLog(false)
, m_bSysLogSet(false)
{

}

ErrorFLog::~ErrorFLog()
{
	//Release() ;
}


ErrorFLog* ErrorFLog::GetInstance()
{
	if(m_pInstance == NULL) {
		m_pInstance = new ErrorFLog;
	}
	return m_pInstance;
}


void ErrorFLog::Release()
{
	if(m_pInstance != NULL) {
		delete (m_pInstance);
	}
	m_pInstance = NULL;
}


//////////////////////////////////////////////////////////////////////////
/**
	Setup : Whether File log or Debug log
*/
void ErrorFLog::SetFileLog(bool isFile)
{
	char dir[256];

	m_bIsFileLog = isFile ;
	::GetCurrentDirectory(256, dir);
	SetWorkPath(dir);					//�������� ���� ����.
	strcat(dir, "\\log");				//�α� ���� ���� �� ����. 
	SetLogPath(dir);					//�α� ���� ���� ����.		

	if( m_bIsFileLog )
	{
		CreateDirectory(dir, NULL);			//�α� ���� ���� ����.

		//�ý��� �ð� ���. 
		SYSTEMTIME systime;
		GetLocalTime(&systime);

		char* date = "AM";
		if(systime.wHour - 12 >= 0) date = "PM";

		//�α� ���ϸ� ����.
		sprintf( dir, "Log_%04d%02d%02d_%s_%02d.txt", 
			systime.wYear, systime.wMonth, systime.wDay,
			date,
			systime.wHour % 12);

		//�α� ���ϸ� ����.
		SetLogFileName(dir);

		char logfullname[256];
		sprintf(logfullname, "%s\\%s", GetLogPath(), GetLogFileName());
		FILE* fp = fopen(logfullname, "at");
		fprintf(fp,  "//******************************************************\n");
		fprintf(fp,  "// Log Start : \t%s\n", dir);
		fclose(fp);
	}
}


//////////////////////////////////////////////////////////////////////////
/**
	Log 
*/
void ErrorFLog::Error_Log(const TCHAR* msg,...)
{
	char message[1024];
	char mm[1024];
	va_list va_ptr;

	va_start(va_ptr, msg);
	vsprintf(mm, msg, va_ptr); 
	va_end(va_ptr);

	// Set Current Time 
	static int StartTime = timeGetTime();
	float dTime = (timeGetTime() - StartTime)*0.001f;
	sprintf(message, "[LOG:%.3f] %s", dTime, mm);

	// File Log
	if( m_bIsFileLog )
	{
		char dir[256];
		::GetCurrentDirectory(256, dir);
		::SetCurrentDirectory(GetLogPath());

		FILE* fp = fopen(GetLogFileName(), "at");				
		if(fp == NULL) return;
		fprintf(fp, message);
		fprintf(fp, "\n"); 
		fclose(fp);

		::SetCurrentDirectory(dir);
	}

#ifdef _DEBUG
	::OutputDebugString(message);
	::OutputDebugString("\n");
#endif
}

/**
	System File Log 
*/
void ErrorFLog::Sys_Log(const TCHAR* msg,...)
{
	char message[1024];
	char mm[1024];
	va_list va_ptr;
	char dir[256];

	va_start(va_ptr, msg);
	vsprintf(mm, msg, va_ptr); 
	va_end(va_ptr);

	// Set Current Time 
	static int SysLogTime = timeGetTime();
	float dTime = (timeGetTime() - SysLogTime)*0.001f;
	sprintf(message, "[SYS:%.3f] %s", dTime, mm);

	::GetCurrentDirectory(256, dir);		// ���� ���� ���

	// File Log
	if( !m_bSysLogSet )
	{
		SetWorkPath(dir);					//�������� ���� ����.
		strcat(dir, "\\log");				//�α� ���� ���� �� ����. 
		SetLogPath(dir);					//�α� ���� ���� ����.		
		CreateDirectory(dir, NULL);			//�α� ���� ���� ����.
		::SetCurrentDirectory(GetLogPath());

		//�ý��� �ð� ���. 
		SYSTEMTIME systime;
		GetLocalTime(&systime);

		//�α� ���ϸ� ����.
		sprintf( dir, "SysLog_%04d_%02d_%02d.txt", systime.wYear, systime.wMonth, systime.wDay);

		//�α� ���ϸ� ����.
		SetSysFileName(dir);

		FILE* fp = fopen(GetSysFileName(), "at");
		fprintf(fp,  "//******************************************************\n");
		fprintf(fp,  "// SysLog Start : \t%s\n", dir);
		fclose(fp);
		m_bSysLogSet = true ;
	}

	::SetCurrentDirectory(GetLogPath());
	FILE* fp = fopen(GetSysFileName(), "at");				
	if(fp == NULL) return;
	fprintf(fp, message);
	fprintf(fp, "\n"); 
	fclose(fp);

	::SetCurrentDirectory(dir);			// ���� ���� ����

#ifdef _DEBUG
	::OutputDebugString(message);
	::OutputDebugString("\n");
#endif
}


/////////////////////////////////////////////////////////////////////////////
//
//	Local Function
//

/**
	GetLogPath
*/
const char*  ErrorFLog::GetLogPath()
{
	return m_strLogPath;
}

const char*  ErrorFLog::SetLogPath(char* pBuff)
{
	return strcpy(m_strLogPath, pBuff);
}


/**
	GetLogFileName(..)	
*/
const char*  ErrorFLog::GetLogFileName()
{
	return m_strLogFileName;
}

const char*  ErrorFLog::SetLogFileName(char* pBuff)
{
	return strcpy(m_strLogFileName, pBuff);
}


/**
	GetSysFileName(..)	
*/
const char*  ErrorFLog::GetSysFileName()
{
	return m_strSysFileName;
}

const char*  ErrorFLog::SetSysFileName(char* pBuff)
{
	return strcpy(m_strSysFileName, pBuff);
}


/**
	GetWorkPath(..)	
*/
const char*  ErrorFLog::GetWorkPath()
{
	return m_strWorkPath;
}

const char*  ErrorFLog::SetWorkPath(char* pBuff )
{
	return strcpy(m_strWorkPath, pBuff);
}

