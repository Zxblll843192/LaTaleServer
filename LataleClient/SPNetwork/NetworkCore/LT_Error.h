// LT_Error.h

#pragma  once

// typedef UINT8	RESULTCODE

enum
{
	LT_NO_ERROR							= 0,	// ����
	LT_ERROR_FAILED						= 1,	// ����

	LT_ERROR_DUPLICATED					= 2,	// �ߺ� �α�								(���� ���� : sp_authUser)
	LT_ERROR_PWMISMATCH					= 3,	// ��ȣ ����ġ								(���� ���� : sp_authUser)
	LT_ERROR_UNAVAILABLEID				= 4,	// ���� ID									(���� ���� : sp_authUser)
	LT_ERROR_DISABLEDID					= 5,	// ��� ������ ����							(���� ���� : sp_authUser)

	LT_ERROR_SYSTEMERROR				= 6,	// �ý��� ����
	LT_ERROR_DBERROR					= 7,	// DB ���� ����								(���� ���� : sp_RegisterCharName,AddChar,setPC)
	LT_ERROR_PERMISSION					= 8,	// �۹̼� �Ұ�(�����۹̼� �ʿ�)				(���� ���� : sp_DeleteChar)
	LT_ERROR_ALREADYJOINED				= 9,	// �̹� �濡 ������ ����

	LT_ERROR_NEW						= 10,	// new �Ҵ� ����
	LT_ERROR_INVALID_FILENAME			= 11,	// �� ���ϸ� ����

	LT_ERROR_UNKNOWN					= 12,	// �˼� ���� ����


	LT_ERROR_INVALID_ACTION				= 13,	// ���� ���¿��� ������ �ʴ� action �õ�
	LT_ERROR_INVALID_TARGET				= 14,	// �߸��� Ÿ��

	LT_ERROR_USERFULL					= 15,	// ���� full

	LT_ERROR_CHARNAME_RESERVED			= 16,	// �����			(ĳ���� ������ ����)	(���� ���� : sp_CheckCharName)
	LT_ERROR_CHARNAME_USED				= 17,	// �̹� �����		(ĳ���� ������ ����)	(���� ���� : sp_CheckCharName,AddChar,setPC)

	LT_ERROR_LEN_CHARNAME				= 18,	// ĳ���� �̸� ���� ���� (CharName:2~16)

	// 2007-5-3 by hoshim : ID/PW ���� ���õ� ���Ӽ� ���� ����
	//LT_ERROR_LEN_ID						= 19,	// ID ���� ���� (ID:2~12)
	//LT_ERROR_LEN_PW						= 20,	// PW ���� ���� (PW:6~12)

	LT_ERROR_INVALID_ITEM_ID			= 21,	// invalid item ID

	LT_ERROR_WEARABLE_MISMATCH_GENDER	= 22,	// �ش� ������ ������ �� ���� ������
	LT_ERROR_WEARABLE_NOT_ENOUGH_LEVEL	= 23,	// ���� �����

	LT_ERROR_DISTANCE					= 24,	// �Ÿ� ���� ����.    LoogtingBag(50),NPC �ŷ���(500)

	LT_ERROR_NOT_FOUND					= 25,	// Not Found
	LT_ERROR_INVALID_PARAM				= 26,
	LT_ERROR_ALREADY_EXIST				= 27,	// find ��� �̹� ����
	LT_ERROR_EXCEED_LIMIT				= 28,	// �� �̻� ��� �Ұ�(Friend/Block ����� ����)

	LT_ERROR_BLOCKED					= 29,	// GMTool�� �ʿ信 ���� �ش� ������ �α� ���� 	(���� ���� : sp_authUser)
	LT_ERROR_REQUIREAGREEMENT			= 30,	// ����������� ������ �����ϰ��ӿ� �������� ���� ������

	LT_ERROR_TIMEOUT					= 31,	// Timeout !!!

	// insert here!!!
	LT_ERROR_EXCEED_CHAR_COUNT			= 40,	// ���� ���� ĳ���� �� �ʰ�

	LT_ERROR_INVALID_CHARACTER			= 50,	// mask�� ����( ~!@#$%^&*()+-=|\\{}[]:;\"\'`<>.,?/)�� ����

	LT_ERROR_INVALID_ID_PW				= 51,	// ID/��ȣ ���� (MW ���� �÷���)
	LT_ERROR_INVALID_EKEY_ID_PW			= 52,	// �߸��� E-key Code�� ��ȣ
	
	// 2007.05.13 dhpark �δ������ ����
	LT_ERROR_INVALID_INDUNID			= 61,	// �δ��������� �ش� �δ��� ��ã�� ���
	LT_ERROR_INVALID_DEAD				= 62,	// �������·� �δ������� �����ϴ� ���
	LT_ERROR_INVALID_SERVERTYPE			= 63,	// �δ������� ä�μ����� �ƴ� ���

	LT_ERROR_OSP_CANNOT_CONNECT			= 100,		// OSP ���� �̿���
	LT_ERROR_OSP_PACKET_FORMAT			= 101,		// OSP ���� ��Ŷ ���� ����
	LT_ERROR_OSP_FAILED					= 102,		// OSP ���� ���� ����
	LT_ERROR_OSP_TIMEOUT				= 103,		// OSP ���� timeout

	LT_ERROR_EKEY_USERLOCKED			= 104,		// user_locked (5ȸ �̻� EKey ������ 5�а� Lock��)
	
	LT_ERROR_VERSION_LOWER				= 200,		// Protocol Version üũ : ���� Ŭ���̾�Ʈ ������ ����
	LT_ERROR_VERSION_UNSURPORTED_OPTION = 201,		// Protocol Version üũ : ������ Option value

	LT_ERROR_RESOURCE_VERSION_LOWER		= 202,		// ���ҽ� ���� üũ : NEED Patch

	LT_ERROR_SERVICE_NOT_READY			= 254,		// ���� ������(�ӽ�/���� ���˽� ���)

	MAX_LT_ERROR						= 255,
};




//-----------------------------------------------------------------------------
// Error Code Definitions
//-----------------------------------------------------------------------------

// SUCCEEDED(hr) or FAILED(hr)
// int iErrCode = HRESULT_CODE(hr);
#ifndef HRESULT_CODE
	#define HRESULT_CODE(hr)				((hr) & 0xFFFF)
	#define HRESULT_FACILITY(hr)			(((hr) >> 16) & 0x1fff)
	#define HRESULT_SEVERITY(hr)			(((hr) >> 31) & 0x1)
#endif


#ifndef MAKE_HRESULT
	#define MAKE_HRESULT(sev,fac,code) \
	((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )
#endif

#define FACILITY_LT							0x900              // LT Error Facility Code

#define MAKE_LT_HRESULT(code)				MAKE_HRESULT(1,FACILITY_LT,code)
#define MAKE_LT_STATUS(code)				MAKE_HRESULT(0,FACILITY_LT,code)


#define LT_ERR_INVALIDFORMAT				MAKE_LT_HRESULT(1)
#define LT_ERR_INVALIDPARAMS				MAKE_LT_HRESULT(2)
#define LT_ERR_OUTOFMEMORY					MAKE_LT_HRESULT(3)
#define LT_ERR_ACCESSDENIED					MAKE_LT_HRESULT(4)
#define LT_ERR_FILENOTOPEN					MAKE_LT_HRESULT(5)

