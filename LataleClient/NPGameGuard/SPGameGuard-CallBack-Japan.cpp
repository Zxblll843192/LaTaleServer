		switch (dwMsg)
		{
		case NPGAMEMON_COMM_ERROR:
		case NPGAMEMON_COMM_CLOSE:
			bAppExit = TRUE;	// �I���R�[�h
			return FALSE;
		case NPGAMEMON_INIT_ERROR:
			wsprintf( msg , "GameGuard�������G���[ : %lu", dwArg);
			bAppExit = TRUE;	// �I���R�[�h
			lpszMsg = msg;
			break;
		case NPGAMEMON_SPEEDHACK:
			wsprintf( msg , "�X�s�[�h�n�b�N�����m����܂����B");
			bAppExit = TRUE;	// �I���R�[�h
			lpszMsg = msg;
			break;
		case NPGAMEMON_GAMEHACK_KILLED:
			wsprintf( msg , "�s���c�[����������܂����B\r\n%s", SPGameGuard::GetInstance()->GetInfo() );
			bAppExit = TRUE;	// �I���R�[�h
			lpszMsg = msg;
			break;
		case NPGAMEMON_GAMEHACK_DETECT:
			wsprintf( msg , "�s���c�[����������܂����B\r\n%s", SPGameGuard::GetInstance()->GetInfo() );
			bAppExit = TRUE;	// �I���R�[�h
			lpszMsg = msg;
			break;
		case NPGAMEMON_GAMEHACK_DOUBT:
			wsprintf( msg , "�Q�[����GameGuard���ϑ�����܂����B");
			bAppExit = TRUE;	// �I���R�[�h
			lpszMsg = msg;
			break;
		default:
			// �K�؂ȏI�����b�Z�[�W�o��
			lpszMsg = "GameGuard�̎��s���G���[���������܂����B�Q�[���t�H���_������GameGuard�t�H���_�ɂ��� *.erl �t�@�C����Y�t����game2@inca.co.kr�Ƀ��[���𑗂��Ă�������悤���肢���܂��B";
			bAppExit = TRUE;
			break;
		}
