// ***************************************************************
//  MiniDumper.cpp   version:  1.0   date:2006/01/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2006 AJJIYA - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "StdAfx.h"

#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <DbgHelp.h>
#include "SPStream.h"

#include "LataleVersionDef.h"

#include "SPCommon.h"

#include "MiniDumper.h"

// based on dbghelp.h
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(
	HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType,
	CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
	CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
	CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam
	);

MiniDumper::DumpLevel MiniDumper::s_DumpLevel                = MiniDumper::DUMP_LEVEL_0;
bool                  MiniDumper::s_bAddTimeStamp            = true;
TCHAR                 MiniDumper::s_szAppName[_MAX_PATH]     = {0,};
TCHAR                 MiniDumper::s_szFaultReason[2048]      = {0,};

#define chDIMOF(Array) (sizeof(Array) / sizeof(Array[0]))

//////////////////////////////////////////////////////////////////////////////
/// \brief ������
/// \param DL ���� ����
/// \param bAddTimeStamp ���� ���� �̸����ٰ� ���� ������ ������ ��¥��
/// ����ִ°��� ����.
//////////////////////////////////////////////////////////////////////////////
MiniDumper::MiniDumper(DumpLevel DL, bool bAddTimeStamp)
{
	assert(s_szAppName[0] == 0);
	assert(DL >= 0);
	assert(DL <= DUMP_LEVEL_3);

	s_DumpLevel     = DL;
	s_bAddTimeStamp = bAddTimeStamp;

	// ��� ��θ� �˾Ƴ���.
	TCHAR szFilename[_MAX_PATH];
	::GetModuleFileName(NULL, szFilename, _MAX_PATH);

	// Ȯ���ڸ� ������ ��� ��θ� �غ��صΰ�...
	TCHAR* dot = strrchr(szFilename, '.');
	::lstrcpyn(s_szAppName, szFilename, (int)(dot - szFilename + 1));

	// ���� ó�� �ڵ鷯�� �����Ѵ�.
	::SetUnhandledExceptionFilter(TopLevelFilter);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief �Ҹ���
//////////////////////////////////////////////////////////////////////////////
MiniDumper::~MiniDumper()
{
}

//////////////////////////////////////////////////////////////////////////////
/// \brief ���ܿ� ���� ������ �޾Ƽ�, �̴� ���� ������ �����Ѵ�. 
/// 
/// SetUnhandledExceptionFilter() API�� ���ؼ� �����ǰ�, ���μ��� ���ο��� 
/// Unhandled Exception�� �߻��� ���, ȣ��ǰ� �ȴ�. �� ����Ű� �پ��ִ� 
/// ���, Unhandled Exception Filter�� ȣ����� �ʴ´�. �� ���� �� �Լ� 
/// ���θ� ������� ���� ���ٴ� ���̴�. �� �Լ� ���θ� ������ϱ� ���ؼ��� 
/// �޽��� �ڽ� �Ǵ� ������ �̿��ؾ��Ѵ�.
/// 
/// \param pExceptionInfo ���� ����
/// \return LONG �� �Լ��� �����ϰ� �� ����, ���� �ൿ��. �ڼ��� ���� SEH
/// ������ �����ϵ���.
//////////////////////////////////////////////////////////////////////////////
LONG WINAPI MiniDumper::TopLevelFilter(struct _EXCEPTION_POINTERS* pExPtr)
{
	LONG    retval                   = EXCEPTION_CONTINUE_SEARCH;
	HMODULE hDLL                     = NULL;
	TCHAR   szDbgHelpPath[_MAX_PATH] = {0,};
	TCHAR   szDumpPath[MAX_PATH * 2] = {0,};
	TCHAR   szFilePath[MAX_PATH * 2] = {0,};
	TCHAR	szBuf[_MAX_PATH * 5]	 = {0,};

	if( g_eCountryLocale == CL_JAPAN )
		return retval;

	// ���� ���� ������ �ִ� ���丮���� DBGHELP.DLL�� �ε��� ����.
	// Windows 2000 �� System32 ���丮�� �ִ� DBGHELP.DLL ������ ������ 
	// ������ ���� �� �ֱ� �����̴�. (�ּ� 5.1.2600.0 �̻��̾�� �Ѵ�.)
	if (::GetModuleFileName(NULL, szDbgHelpPath, _MAX_PATH))
	{
		LPTSTR pSlash = ::strrchr(szDbgHelpPath, '\\');
		if (pSlash)
		{
			::lstrcpy(pSlash + 1, "DBGHELP.DLL");
			hDLL = ::LoadLibrary(szDbgHelpPath);
		}
	}

	// ���� ���丮�� ���ٸ�, �ƹ� �����̳� �ε��Ѵ�.
	if (hDLL == NULL) hDLL = ::LoadLibrary("DBGHELP.DLL");

	// ���� �ð��� ���´�.
	SYSTEMTIME t;
	::GetLocalTime(&t);

	// �ð� ���ڿ��� �غ��Ѵ�.
	TCHAR szTail[_MAX_PATH] = {0,};
	TCHAR szErrorUnique[_MAX_PATH] = {0,};
	_snprintf(szTail, chDIMOF(szTail)-1, " %04d-%02d-%02d %02d-%02d-%02d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	_snprintf(szErrorUnique, chDIMOF(szErrorUnique)-1, "LaTaleClient/%d.%d/%04d-%02d-%02d/%02d-%02d-%02d", VER_MAJOR , VER_MINOR , t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond );

	//	�ð� üũ
	if (s_bAddTimeStamp)
	{
		// ���� ���� �̸� += �ð� ���ڿ�
		::lstrcat(szDumpPath, s_szAppName);
		::lstrcat(szDumpPath, szTail);
	}

	::lstrcpy( szFilePath , szDumpPath );
	::lstrcat( szFilePath , ".ERR");

	SPFileStream*	pLogFile	=	new	SPFileStream( szFilePath , SPFileStream::OPEN_CREATE | SPFileStream::OPEN_WRITE );

	if( g_eCountryLocale == CL_JAPAN )
	{
#include "MiniDumper-Japan.cpp"
	}
	else if( g_eCountryLocale == CL_CHINA )
	{
		if (hDLL == NULL)
			return retval;

		MINIDUMPWRITEDUMP pfnMiniDumpWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDLL, "MiniDumpWriteDump");

		if (pfnMiniDumpWriteDump == NULL)
			return retval;

		::lstrcat(szDumpPath, ".DMP");

		HANDLE hFile = ::CreateFile( szDumpPath, GENERIC_WRITE , FILE_SHARE_WRITE , NULL , CREATE_ALWAYS , FILE_ATTRIBUTE_NORMAL , NULL );

		if (hFile == INVALID_HANDLE_VALUE)
			return retval;

		MINIDUMP_EXCEPTION_INFORMATION ExceptionParam;

		ExceptionParam.ThreadId = ::GetCurrentThreadId();
		ExceptionParam.ExceptionPointers = pExPtr;
		ExceptionParam.ClientPointers = FALSE;

		BOOL bResult = FALSE;

		switch (s_DumpLevel)
		{
		case DUMP_LEVEL_0: // MiniDumpNormal
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpNormal, &ExceptionParam, NULL, NULL);
			break;
		case DUMP_LEVEL_1: // MiniDumpWithDataSegs 
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpWithDataSegs, &ExceptionParam, NULL, NULL);
			break;
		case DUMP_LEVEL_2: // MiniDumpWithFullMemory 
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, (MINIDUMP_TYPE)( MiniDumpNormal | MiniDumpWithIndirectlyReferencedMemory ) , &ExceptionParam, NULL, NULL);
			break;
		case DUMP_LEVEL_3: // MiniDumpWithFullMemory 
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpWithFullMemory, &ExceptionParam, NULL, NULL);
			break;
		default:
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpNormal, &ExceptionParam, NULL, NULL);
			break;
		}

		_snprintf( szBuf , chDIMOF( szBuf ) - 1 , "LaTaleClient Version : %d.%d\r\n\r\nLaTaleClient Error : [%s]\r\n\r\n" , VER_MAJOR , VER_MINOR , GetFaultReason(pExPtr) );

		pLogFile->Write( szBuf , (unsigned int)strlen( szBuf ) );
		pLogFile->Release();

		if( bResult == FALSE )
		{
			bResult = pfnMiniDumpWriteDump( ::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, &ExceptionParam, NULL, NULL);
		}
	}
	else
	{
		// DBGHELP.DLL�� ã�� �� ���ٸ� �� �̻� ������ �� ����.
		if (hDLL == NULL)
		{
			strcpy( szBuf , "LaTaleClient�� ������������ ���� �Ǿ����ϴ�. DBGHELP.DLL ������ ��� ������ �����Ҽ� �����ϴ�." );

			pLogFile->Write( szBuf , (unsigned int)strlen( szBuf ) );
			pLogFile->Release();

			::MessageBox( NULL , szBuf , "LaTaleClient" , MB_ICONWARNING );

			return retval;
		}

		// DLL ���ο��� MiniDumpWriteDump API�� ã�´�.
		MINIDUMPWRITEDUMP pfnMiniDumpWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDLL, "MiniDumpWriteDump");

		// �̴ϴ��� �Լ��� ã�� �� ���ٸ� �� �̻� ������ �� ����.
		if (pfnMiniDumpWriteDump == NULL)
		{
			strcpy( szBuf , "LaTaleClient�� ������������ ���� �Ǿ����ϴ�. DBGHELP.DLL�� ������ ���Ƽ� ������ �����Ҽ� �����ϴ�." );

			pLogFile->Write( szBuf , (unsigned int)strlen( szBuf ) );
			pLogFile->Release();

			::MessageBox( NULL , szBuf , "LaTaleClient" , MB_ICONWARNING );

			return retval;
		}

		// ���� ���� �̸� += Ȯ����
		::lstrcat(szDumpPath, ".DMP");

		// ������ �����Ѵ�.
		HANDLE hFile = ::CreateFile(
			szDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, 
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		// ������ ������ �� ���ٸ� �� �̻� ������ �� ����.
		if (hFile == INVALID_HANDLE_VALUE)
		{
	//		sprintf( szBuf , "Failed to create dump file '%s'", szDumpPath );
			sprintf( szBuf , "LaTaleClient�� ������������ ���� �Ǿ����ϴ�. %s ������ ������ �� �����ϴ�." , szDumpPath );

			pLogFile->Write( szBuf , (unsigned int)strlen( szBuf ) );
			pLogFile->Release();

			::MessageBox( NULL , szBuf , "LaTaleClient" , MB_ICONWARNING );

			return retval;
		}

		MINIDUMP_EXCEPTION_INFORMATION ExceptionParam;

		ExceptionParam.ThreadId = ::GetCurrentThreadId();
		ExceptionParam.ExceptionPointers = pExPtr;
		ExceptionParam.ClientPointers = FALSE;

		// �ɼǿ� ���� ���� ������ �����Ѵ�. 
		BOOL bResult = FALSE;
		switch (s_DumpLevel)
		{
		case DUMP_LEVEL_0: // MiniDumpNormal
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpNormal, &ExceptionParam, NULL, NULL);
			break;
		case DUMP_LEVEL_1: // MiniDumpWithDataSegs 
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpWithDataSegs, &ExceptionParam, NULL, NULL);
			break;
		case DUMP_LEVEL_2: // MiniDumpWithFullMemory 
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, (MINIDUMP_TYPE)( MiniDumpNormal | MiniDumpWithIndirectlyReferencedMemory ) , &ExceptionParam, NULL, NULL);
			break;
		case DUMP_LEVEL_3: // MiniDumpWithFullMemory 
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpWithFullMemory, &ExceptionParam, NULL, NULL);
			break;
		default:
			bResult = pfnMiniDumpWriteDump(
				::GetCurrentProcess(), ::GetCurrentProcessId(), 
				hFile, MiniDumpNormal, &ExceptionParam, NULL, NULL);
			break;
		}

		if( bResult == FALSE )
		{
			bResult = pfnMiniDumpWriteDump( ::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, &ExceptionParam, NULL, NULL);
		}

		UINT	uiType	=	MB_ICONWARNING;
		BOOL	bIsLaTaleErrorExits	=	FALSE;		// LaTaleError.EXE �� �ִ��� Ȯ���Ѵ�.
		TCHAR   szLaTaleErrorFullPath[_MAX_PATH] = {0,};
		TCHAR   szLaTaleErrorPath[_MAX_PATH] = {0,};
		TCHAR   szLaTaleErrorName[_MAX_PATH] = {0,};
		TCHAR   szLaTaleErrorCmdLine[_MAX_PATH] = {0,};

		// ���� ���� ���� ����� �α� ���Ͽ��� ����Ѵ�.
		if (bResult)
		{
	//		TCHAR szMessage[8192] = {0,};
	//		lstrcat(szMessage, "Saved dump file to '");
	//		lstrcat(szMessage, szDumpPath);
	//		lstrcat(szMessage, "'.\nFault Reason : ");
	//		lstrcat(szMessage, GetFaultReason(pExPtr));

			retval = EXCEPTION_EXECUTE_HANDLER;

			// LaTaleError.EXE �� �ִ��� Ȯ���Ѵ�.
			if (::GetModuleFileName(NULL, szLaTaleErrorFullPath, _MAX_PATH))
			{
				::lstrcpy( szLaTaleErrorName , "LaTaleError.EXE" );

				TCHAR* pszSlash = ::strrchr( szLaTaleErrorFullPath , '\\' );

				if (pszSlash)
				{
					::lstrcpyn( szLaTaleErrorPath , szLaTaleErrorFullPath , (int)( pszSlash - szLaTaleErrorFullPath + 1 ) );
					::lstrcpy( pszSlash + 1, szLaTaleErrorName );

					if( ( _taccess( szLaTaleErrorFullPath , 0 ) ) != -1 )
						bIsLaTaleErrorExits	=	TRUE;
				}
			}

			_snprintf( szBuf , chDIMOF( szBuf ) - 1 , "LaTaleClient Version : %d.%d\r\n\r\nLaTaleClient�� Error : [%s] ������ ������������ ���� �Ǿ����ϴ�.\r\n\r\nhttp://www.LaTale.com Ȩ�������� ���Ϲ��� �޴���\r\n\r\n %s \r\n %s \r\n\r\n" , VER_MAJOR , VER_MINOR , GetFaultReason(pExPtr) , szDumpPath , szFilePath );

			if( bIsLaTaleErrorExits == TRUE )
			{
				::lstrcat( szBuf , "�� �ΰ��� ���� ���ϰ� �߰������� ���� PC�� Direct X�� ������,\r\n\r\n" );
				::lstrcat( szBuf , "���� LaTaleError�� ����Ͽ� ���� ������ ÷���ؼ� �����ðڽ��ϱ� ? \r\n" );
				uiType	|=	MB_YESNO;

				TCHAR* pszFileSlash = ::strrchr( szFilePath , '\\' );
				TCHAR* pszDumpSlash = ::strrchr( szDumpPath , '\\' );

				if( pszFileSlash )
				{
					::lstrcpy( szFilePath , pszFileSlash + 1 );
				}

				if( pszDumpSlash )
				{
					::lstrcpy( szDumpPath , pszDumpSlash + 1 );
				}

				::lstrcat( szLaTaleErrorCmdLine , UNIQUE_LATALE_ERROR );
				::lstrcat( szLaTaleErrorCmdLine , szErrorUnique );
				::lstrcat( szLaTaleErrorCmdLine , " " );
				::lstrcat( szLaTaleErrorCmdLine , CMD_INFO );
				::lstrcat( szLaTaleErrorCmdLine , szFilePath );
				::lstrcat( szLaTaleErrorCmdLine , " " );
				::lstrcat( szLaTaleErrorCmdLine , CMD_DMP );
				::lstrcat( szLaTaleErrorCmdLine , szDumpPath );
				::lstrcat( szLaTaleErrorCmdLine , CMD_END );
			}
			else
			{
				::lstrcat( szBuf , "�� �ΰ��� ���� ���ϰ� �߰������� ���� PC�� Direct X�� ������ �ʿ��Ͽ���,\r\n" );
				::lstrcat( szBuf , "���� > ����  ���� dxdiag �� �Է��Ͻð� Ȯ�� ��ư�� �����ø�,\r\n" );
				::lstrcat( szBuf , "Direct X ���ܵ����� ����ǿ��� ��� ���� ���� �� Ŭ���Ͻþ� ������ �Ͻ� ��\r\n\r\n" );
				::lstrcat( szBuf , "( ���� -> ���� -> dxdiag �Է� -> ��� ���� ����  )\r\n\r\n" );
				::lstrcat( szBuf , "�ش� ������ ÷���Ͽ� ���������� [DMP���� ���� dxdiag���� ÷��]�� �ۼ��� ��\r\n" );
				::lstrcat( szBuf , "�߼��Ͽ� �ֽñ⸦ ��Ź�帳�ϴ�.\r\n\r\n" );
				::lstrcat( szBuf , "�̸��Ͽ� ÷������ �뷮�� 2�ް��� �����̿��� �뷮Ȯ���� �����ֽð�\r\n" );
				::lstrcat( szBuf , "���� ÷�� ��ư�� �� ���� �ֽþ� �ϴ��� ÷�� ���� ��Ͽ�\r\n" );
				::lstrcat( szBuf , "������ ÷�ΰ� �Ǿ������� Ȯ���� ���ֽʽÿ�." );
			}
		}
		else
		{
	//		sprintf( szBuf , "Failed to save dump file to '%s' (error %d)", szDumpPath, ::GetLastError() );
			sprintf( szBuf , "LaTaleClient�� ������������ ���� �Ǿ����ϴ�. %s ���� ������ �����Ҽ� �����ϴ�.\n Error Code : [ %d ]" , szDumpPath , ::GetLastError() );

			//filelog(NULL, "Failed to save dump file to '%s' (error %d,%s)", 
			//	szDumpPath, ::GetLastError(), GetLastErrorString().c_str());

			assert(false);
		}

		pLogFile->Write( szBuf , (unsigned int)strlen( szBuf ) );
		pLogFile->Release();

		::CloseHandle(hFile);
		int	iResult = ::MessageBox( NULL , szBuf , "LaTaleClient" , uiType );

		//	::MessageBox( NULL , szLaTaleErrorCmdLine , "LaTaleClient" , MB_ICONWARNING );

		if( bIsLaTaleErrorExits == TRUE && iResult == IDYES )
		{
			SHELLEXECUTEINFO	si;

			memset( &si, 0, sizeof(SHELLEXECUTEINFO) );

			si.cbSize		= sizeof(si);
			si.lpVerb		= _T("Open");
			si.nShow		|= SW_SHOWNA;
			si.lpDirectory	= (LPCSTR)szLaTaleErrorPath;
			si.lpFile		= (LPCSTR)szLaTaleErrorName;
			si.lpParameters	= (LPCSTR)szLaTaleErrorCmdLine;

			if( ShellExecuteEx( &si ) == FALSE )
			{   
				int res = GetLastError();

				if( res == ERROR_FILE_NOT_FOUND )
					::MessageBox( NULL , "���α׷��� ã�� �� �����ϴ�." , "LaTaleClient" , MB_ICONWARNING );
				if( res == ERROR_PATH_NOT_FOUND )
					::MessageBox( NULL , "���α׷� ��ΰ� �ùٸ��� �ʽ��ϴ�." , "LaTaleClient" , MB_ICONWARNING );
				if( res == ERROR_ACCESS_DENIED )
					::MessageBox( NULL , "���α׷� �׼����� �źεǾ����ϴ�." , "LaTaleClient" , MB_ICONWARNING );
			}
		}
	}

	return retval;
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 
/// 
/// \param pExPtrs 
/// \return LPCTSTR
//////////////////////////////////////////////////////////////////////////////
LPCTSTR MiniDumper::GetFaultReason(struct _EXCEPTION_POINTERS* pExPtrs)
{
	if (::IsBadReadPtr(pExPtrs, sizeof(EXCEPTION_POINTERS))) 
		return "BAD EXCEPTION POINTERS";

	// ������ ���� �ڵ��� �׳� ��ȯ�� �� �ִ�.
	switch (pExPtrs->ExceptionRecord->ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:         return "EXCEPTION_ACCESS_VIOLATION";
	case EXCEPTION_DATATYPE_MISALIGNMENT:    return "EXCEPTION_DATATYPE_MISALIGNMENT";
	case EXCEPTION_BREAKPOINT:               return "EXCEPTION_BREAKPOINT";
	case EXCEPTION_SINGLE_STEP:              return "EXCEPTION_SINGLE_STEP";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:    return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
	case EXCEPTION_FLT_DENORMAL_OPERAND:     return "EXCEPTION_FLT_DENORMAL_OPERAND";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:       return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
	case EXCEPTION_FLT_INEXACT_RESULT:       return "EXCEPTION_FLT_INEXACT_RESULT";
	case EXCEPTION_FLT_INVALID_OPERATION:    return "EXCEPTION_FLT_INVALID_OPERATION";
	case EXCEPTION_FLT_OVERFLOW:             return "EXCEPTION_FLT_OVERFLOW";
	case EXCEPTION_FLT_STACK_CHECK:          return "EXCEPTION_FLT_STACK_CHECK";
	case EXCEPTION_FLT_UNDERFLOW:            return "EXCEPTION_FLT_UNDERFLOW";
	case EXCEPTION_INT_DIVIDE_BY_ZERO:       return "EXCEPTION_INT_DIVIDE_BY_ZERO";
	case EXCEPTION_INT_OVERFLOW:             return "EXCEPTION_INT_OVERFLOW";
	case EXCEPTION_PRIV_INSTRUCTION:         return "EXCEPTION_PRIV_INSTRUCTION";
	case EXCEPTION_IN_PAGE_ERROR:            return "EXCEPTION_IN_PAGE_ERROR";
	case EXCEPTION_ILLEGAL_INSTRUCTION:      return "EXCEPTION_ILLEGAL_INSTRUCTION";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
	case EXCEPTION_STACK_OVERFLOW:           return "EXCEPTION_STACK_OVERFLOW";
	case EXCEPTION_INVALID_DISPOSITION:      return "EXCEPTION_INVALID_DISPOSITION";
	case EXCEPTION_GUARD_PAGE:               return "EXCEPTION_GUARD_PAGE";
	case EXCEPTION_INVALID_HANDLE:           return "EXCEPTION_INVALID_HANDLE";
	case 0xE06D7363:                         return "Microsoft C++ Exception";
	default:
		break;
	}

	// ���� �� �� ������ �������...
	lstrcpy(s_szFaultReason, "Unknown"); 
	::FormatMessage(
		FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,
		::GetModuleHandle("NTDLL.DLL"),
		pExPtrs->ExceptionRecord->ExceptionCode, 
		0,
		s_szFaultReason,
		0,
		NULL);

	return s_szFaultReason;
}
