			// �u6.��v�G���[�R�[�h�v���Q�l���ď󋵂ɍ������b�Z�[�W���o�͂��܂��B
			switch (dwResult)
			{
			case NPGAMEMON_ERROR_EXIST:
				lpszMsg = "GameGuard�����s���ł��B���΂炭��܂��͍ċN���̌�A�Ď��s���Ă��������B";
				break;
			case NPGAMEMON_ERROR_GAME_EXIST:
				lpszMsg = "�Q�[�����d�����s���ꂽ�Ƃ�����GameGuard�����s���ł��B�Q�[���I���̌�Ď��s���Ă��������B";
				break;
			case NPGAMEMON_ERROR_INIT:
				lpszMsg = "GameGuard�������G���[�ł��B�ċN���̌�A�ēx���s���Ă݂�Ƃ��Փ˂̉\�������鑼�̃v���O�������I��������A���s���Ă��������B";
				break;
			case NPGAMEMON_ERROR_AUTH_GAMEGUARD:
			case NPGAMEMON_ERROR_NFOUND_GG:
			case NPGAMEMON_ERROR_AUTH_INI:
			case NPGAMEMON_ERROR_NFOUND_INI:
				lpszMsg = "GameGuard�t�@�C�����Ȃ����ϑ�����܂����BGameGuard�Z�b�g�A�b�v�t�@�C�����C���X�g�[�����Ă��������B";
				break;
			case NPGAMEMON_ERROR_CRYPTOAPI:
				lpszMsg = "�E�B���h�E�̈ꕔ�V�X�e���t�@�C������������܂����B�C���^�[�l�b�g�G�N�X�v���[��(IE)���ăC���X�g�[�����Ă��������B";
				break;
			case NPGAMEMON_ERROR_EXECUTE:
				lpszMsg = "GameGuard���s�Ɏ��s���܂����BGameGuard�Z�b�g�A�b�v�t�@�C�����ăC���X�g�[�����Ă��������B";
				break;
			case NPGAMEMON_ERROR_ILLEGAL_PRG:
				lpszMsg = "�s�@�v���O������������܂����B�s�v�ȃv���O�������I��������A�Ď��s���Ă��������B";
				break;
			case NPGMUP_ERROR_ABORT:
				lpszMsg = "GameGuard�A�b�v�f�[�g���L�����Z�����܂����B�����Đڑ��ł��Ȃ��ꍇ�A�C���^�[�l�b�g�y�ьl�t�@�C�A�E�H�[���ݒ�𒲐����Ă��������B";
				break;
			case NPGMUP_ERROR_CONNECT:
			case HOOK_TIMEOUT:
				lpszMsg = "�E�B���X��Spyware�ɂ����Hooking�Ɏ��s���܂����B�ŐV���N�`�����^�E�����[�h���ăR���s���[�^�[�S�̌��������Ă��������B";
				break;
			case NPGAMEMON_ERROR_GAMEGUARD:
				lpszMsg = "GameGuard�������G���[���͋��o�[�W������GameGuard�t�@�C���ł��B GameGuard�Z�b�g�A�b�v�t�@�C�����ăC���X�g�[�����ăQ�[�������s���Ă��������B";
				break;
			case NPGMUP_ERROR_PARAM:
				lpszMsg = "ini�t�@�C�����Ȃ��Ƃ��ϑ�����܂����BGameGuard�Z�b�g�A�b�v�t�@�C�����ăC���X�g�[�����Ă��������B";
				break;
			case NPGMUP_ERROR_INIT:
				lpszMsg = "npgmup.des�������G���[�ł��BGameGuard�t�H���_���폜������Q�[�����ċN�����Ă��������B";
				break;
			//case ???:
			//	lpszMsg = "���؂���Ȃ�Windows XP x64�o�[�W���������s�����ꍇ�ł��B�ŐV�o�[�W�����ŃC���X�g�[��������Q�[�����s�����Ă��������B";
			//	break;
			case NPGMUP_ERROR_DOWNCFG:
				lpszMsg = "GameGuard�̃A�b�v�f�[�g�T�[�o�ڑ��Ɏ��s���܂����B���΂炭��Ď��s���邩�A�l�t�@�C�A�E�H�[��������ΐݒ�𒲐����Ă��������B";
				break;
			case NPGMUP_ERROR_AUTH:
				lpszMsg = "GameGuard�̃A�b�v�f�[�g����������܂���ł����B�E�B���X���N�`�����ꎞ���~��������A�Ď��s���邩�APC�Ǘ��v���O�������g���ΐݒ�𒲐����Ă��������B";
				break;
			case NPGAMEMON_ERROR_NPSCAN:
				lpszMsg = "�E�B���X�y�ѕs���c�[���������W���[�����[�f�B���O�Ɏ��s���܂����B�������[�s���܂��̓E�B���X�ɂ�銴���̉\��������܂��B";
				break;
			default:
				// �K�؂ȏI�����b�Z�[�W�o��
				lpszMsg = "GameGuard�̎��s���G���[���������܂����B�Q�[���t�H���_������GameGuard�t�H���_�ɂ��� *.erl �t�@�C����Y�t����game2@inca.co.kr�Ƀ��[���𑗂��Ă�������悤���肢���܂��B";
				break;
			}
			wsprintf( msg, "GameGuard�G���[ : %lu" , dwResult );