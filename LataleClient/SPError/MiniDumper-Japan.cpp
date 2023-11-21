	if (hDLL == NULL)
	{
		strcpy( szBuf , "LaTaleClient������ɏI������܂���ł����BDBGHELP.DLL �t�@�C�����Ȃ��̂ŏ���ۑ��ł��܂���B" );

		pLogFile->Write( szBuf , (unsigned int)strlen( szBuf ) );
		pLogFile->Release();

		::MessageBox( NULL , szBuf , "LaTaleClient" , MB_ICONWARNING );

		return retval;
	}

	// DLL ���ο��� MiniDumpWriteDump API�� ã�´�.
	MINIDUMPWRITEDUMP pfnMiniDumpWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDLL, "MiniDumpWriteDump");

	// �̴ϴ��� �Լ��� ã�� ��E���ٸ�E��E�̻�E������ ��E����.
	if (pfnMiniDumpWriteDump == NULL)
	{
		strcpy( szBuf , "LaTaleClient������ɏI������܂���ł����B DBGHELP.DLL�̃o�[�W�������Ⴂ���ߏ���ۑ��ł��܂���B." );

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

	// ������ ������ ��E���ٸ�E��E�̻�E������ ��E����.
	if (hFile == INVALID_HANDLE_VALUE)
	{
//		sprintf( szBuf , "Failed to create dump file '%s'", szDumpPath );
		sprintf( szBuf , "LaTaleClient������ɏI������܂���ł����B %s �t�@�C���𐶐��ł��܂���B" , szDumpPath );

		pLogFile->Write( szBuf , (unsigned int)strlen( szBuf ) );
		pLogFile->Release();

		::MessageBox( NULL , szBuf , "LaTaleClient" , MB_ICONWARNING );

		return retval;
	}

	MINIDUMP_EXCEPTION_INFORMATION ExceptionParam;

	ExceptionParam.ThreadId = ::GetCurrentThreadId();
	ExceptionParam.ExceptionPointers = pExPtr;
	ExceptionParam.ClientPointers = FALSE;

	// �ɼǿ� ����E���� ������ �����Ѵ�. 
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
	BOOL	bIsLaTaleErrorExits	=	FALSE;		// LaTaleError.EXE �� �ִ���EȮ���Ѵ�.
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

		// LaTaleError.EXE �� �ִ���EȮ���Ѵ�.
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

		_snprintf( szBuf , chDIMOF( szBuf ) - 1 , "LaTaleClient Version : %d.%d\r\n\r\nLaTaleClient�� Error : [%s] ���Ő���ɏI������܂���ł����B\r\n\r\nhttp://www.latale.jp�̂��₢���킹�͂�����\r\n\r\n %s \r\n %s \r\n\r\n" , VER_MAJOR , VER_MINOR , GetFaultReason(pExPtr) , szDumpPath , szFilePath );

		if( bIsLaTaleErrorExits == TRUE )
		{
			::lstrcat( szBuf , "��L�̂Q�̃t�@�C���ƒǉ��ł��q�lPC��Direct X����\r\n\r\n" );
			::lstrcat( szBuf , "LaTaleError�𗘗p���ď��t�@�C����Y�t���đ����Ă��������܂��ł��傤���H \r\n" );
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
			::lstrcat( szBuf , "��L�̂Q�̃t�@�C���ƒǉ��ł��q�lPC��Direct X��񂪕K�v�Ȃ̂�\r\n" );
			::lstrcat( szBuf , "�X�^�[�g > �t�@�C�������w�肵�Ď��s  ���� dxdiag ����͂��Ċm�F�{�^����������\r\n" );
			::lstrcat( szBuf , "Direct X �f�f���s���܂��̂őS�Ă̏���ۑ����N���b�N���ĕۑ�������A\r\n\r\n" );
			::lstrcat( szBuf , "( �X�^�[�g -> �t�@�C�������w�肵�Ď��s -> dxdiag ���� -> �S�Ă̏���ۑ�  )\r\n\r\n" );
			::lstrcat( szBuf , "���̃t�@�C����Y�t���ă��[���̌����� [DMP�G���[�֘A dxdiag�t�@�C���Y�t]�ō쐬���Ă���������\r\n" );
			::lstrcat( szBuf , "�����Ă�������悤�ɂ��肢�������܂��B\r\n\r\n" );
			::lstrcat( szBuf , "���[���ɓY�t����e�ʂ�2���K�܂łł��̂ŁA�T�C�Y�̊m�F�����Ă���\r\n" );
			::lstrcat( szBuf , "���ɂ���Y�t�{�^���������ĉ��i�̓Y�t���X�g��\r\n" );
			::lstrcat( szBuf , "�t�@�C�����Y�t����Ă��邩���m�F���Ă��������B" );
		}
	}
	else
	{
//		sprintf( szBuf , "Failed to save dump file to '%s' (error %d)", szDumpPath, ::GetLastError() );
		sprintf( szBuf , "LaTaleClient������ɏI������܂���ł����B%s ���t�@�C����ۑ����邱�Ƃ��ł��܂���ł����B\r\n Error Code : [ %d ]" , szDumpPath , ::GetLastError() );

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
				::MessageBox( NULL , "�����邱�Ƃ��ł��܂���B" , "LaTaleClient" , MB_ICONWARNING );
			if( res == ERROR_PATH_NOT_FOUND )
				::MessageBox( NULL , "�v���O�����ւ̃A�N�Z�X������������܂���B" , "LaTaleClient" , MB_ICONWARNING );
			if( res == ERROR_ACCESS_DENIED )
				::MessageBox( NULL , "�v���O�����ւ̃A�N�Z�X�����ۂ���܂����B" , "LaTaleClient" , MB_ICONWARNING );
		}
	}