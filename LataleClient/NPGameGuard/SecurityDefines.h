#pragma once

#ifdef _LATALE_SERVER
	// XTrap
	#include "XTrap/XTrap4Server.h"
	// nProtect
	#include "nProtect/ggsrv25.h"
	// CrackProof
	#include "CrackProof/HtGECASrv.h"
#elif _LATALE_CLIENT
	// XTrap
	#include "./XTrapLib/XTrap4Client.h"
	// nProtect
	#include "NPGameLib.h"
	// CrackProof
	#include "./CrackProof/HtGECACln.h"
#endif

#define SECURITY_CNT_DATA							3			// �������˻�� �����͸� �ε��Ҽ��ִ� �ִ��. �� �����ϸ�(Ŭ���̾�Ʈ ��ġ�� 3���̻��̸�) ������ ������ؾ���.
#define SECURITY_MAX_PATH							1024
#define SECURITY_REGULAR_COUNT						3			// KeepAlive��Ŷ(10�ʰ���)�� �˻��ֱ�(1��)���� ��ȸ�̻��̸� ���������� ���� �Ǵܰ�
#define SECURITY_UPDATE_ACTIVEUSERCOUNT				100			// ���ȸ���� ������Ʈ�ϱ����� 3���� ���� �� �ֽź��ȸ���� �����Ͽ� ������ ������ ��.(�������� 1/3����)
#define SECURITY_UPDATE_CHECKTIME					30			// ���ȸ���� ������Ʈ�ϱ����� 3���� ���� �� ��赥���͸� �����ϴ� �ð�. �д���
#define SECURITY_UPDATE_ACTIVEUSERPERCENT			50			// ���ȸ���� ������Ʈ�ϱ����� 3���� ���� �� ���� �������� �� �ֽź��ȸ���� �����Ͽ� ������ ������ %.
#define SECURITY_TIME_TIMEOUT						300			// 300��. Ŭ���̾�Ʈ ������ ��ٸ��� �ִ밪. �ʴ��� -- �׽�Ʈ��� �˻��ֱⰡ 1���� ���� 100���� �ؾ� 5���Ŀ� ��������Ǿ���. �˻��ֱⰡ 20���̸� 300�����ؾ� 5���� ��������.
#define SECURITY_TIME_CHECK							10*1000		// 10��. �ʱ������ ���� �˻��ֱ�. �ʱ������ �Ϸ�Ǹ� ����⺰ �˻��ֱ�� �����ؾ��մϴ�.
#define SECURITY_TIME_CHECK_XTRAP					20*1000		// 20��. XTrap �˻��ֱ�
#define SECURITY_TIME_CHECK_NPROTECT				5*60*1000	// 5��. nProtect �˻��ֱ�
#define SECURITY_TIME_UPDATE						5*60*1000	// 5��
#define SECURITY_TIME_RELOAD						9*60*1000	// 9��
#define SECURITY_TIME_SWAP							1*60*1000	// 1��. ���ε徲���� ȣ���� 1���� �޸𸮽��ҽõ�. ���ε�ð� ��10��.
#define SECURITY_SHAKE_CNT							2			// 10���ֱ�� 2ȸ������ �ۼ��ſϷḦ �˻��մϴ�. ���� ����⺰ �˻��ֱ�� �����ؾ��մϴ�.
#define SECURITY_CPF_DATA_SIZE						512
#define SECURITY_CPF_FULL_SIZE						SECURITY_CPF_DATA_SIZE + sizeof(HtGECAData) - 1

enum SECURITY_MODE { SECURITY_MODE_NONE = 0, SECURITY_MODE_XTRAP, SECURITY_MODE_NPROTECT, SECURITY_MODE_CRACKPROOF, SECURITY_MODE_MAX };
enum SECURITY_RELOAD { SECURITY_RELOAD_NONE = 0, SECURITY_RELOAD_DOING, SECURITY_RELOAD_NEW, SECURITY_RELOAD_FAILED, SECURITY_RELOAD_MAX };

typedef struct _tagSECURITY_PACKDATA
{
	unsigned char	arrBufPackData[XTRAP_CS4_COMSIZE_PACKDATA];
	GG_AUTH_DATA	stAuthData;
	BYTE			arrCPFData[SECURITY_CPF_FULL_SIZE];

} SECURITY_PACKDATA, *PSECURITY_PACKDATA;
