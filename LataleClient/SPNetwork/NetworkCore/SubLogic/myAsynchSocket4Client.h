// myAsynchSocket4Client.h

// Copyright (C) hoshim
//***************************************************************************
// System Name : CmyAsynchSocket4Client
// Comment     : Asynchronous Socket for Client connector
//
// Creation    : hoshim 2005-04-29 ���� 11:00:00
//***************************************************************************

#pragma once

#include <queue>
using namespace std;

#ifdef SC_THREAD_SAFE
	#include "LockObject.h"
#endif

typedef 	int (*CALLBACK_RECV_FN)(BYTE* pszBuf,int nReceived,LPVOID pThis);

// Ŭ���̾�Ʈ ���� ����ü (��������, ����� ����)
typedef struct 
{
	BYTE	szBuf[MAX_PACKET_SIZE];
	SOCKET	Socket;
	DWORD	dwSent;				// ������� ���۵� ������
	DWORD	dwRecv;
	DWORD	dwTotalToSend;		// ���۵� �� ������
	WSABUF	wsaBuf;
	DWORD	dwRemained;			// �б� ��忡�� �ܿ���

} SOCKINFO, *PSOCKINFO;

typedef struct 
{
	WSABUF	wsaBuf;
	CHAR	Buffer[MAX_PACKET_SIZE];
	DWORD	dwTotalToSend;		//������ �ѷ�
	DWORD	dwSent;				//������� ������ ��
}SEND_BUFFER,*PSEND_BUFFER;

class CmyAsynchSocket4Client
{
public:
	CmyAsynchSocket4Client(void);
	virtual ~CmyAsynchSocket4Client(void);

private:
	SOCKET m_Socket;
	WSADATA m_wsadata;
	sockaddr_in m_addr_in;

	WSAEVENT m_wsaEvent;
	SOCKINFO m_SockInfo;

	CALLBACK_RECV_FN m_pfnOnReceive;
	
	bool m_bConnected;

	TCHAR m_szDestIP[20];
	USHORT m_usDestPort;

	DWORD m_dwConnectRetry_Period;
	DWORD m_dwConnectRetry_LastTime;

public:

	bool Init();
	void Exit();

	bool Process(DWORD dwCheckTimeout);

	void SetCallbackFunc(CALLBACK_RECV_FN pfnCallback){m_pfnOnReceive = pfnCallback;}

	bool Connect(char* ipaddr,unsigned short port);
	void Close(void);

	bool CheckEvent(const DWORD& dwTimeoout = WSA_INFINITE);	// check event once

	bool IsConnected(){return m_bConnected;	}

	bool InitSockInfo(SOCKET s);
	void ResetBufferLength();

	virtual int OnConnect(DWORD Event);
	virtual int OnReceive(DWORD Event);
	virtual int OnWritable(DWORD Event);
	virtual int OnClose(DWORD Event);

	int OnReceivedPacketEx(BYTE* pszBuf,int nReceived);

	int SendData(DWORD Event,char* pszData, int nLen);
	int RecvData();

	bool SendBuffer(const TCHAR* pszBuffer,const DWORD& dwLen);

	SOCKET GetSocketHandle(){return m_Socket;};

// Send Queue ����

public:
	bool SendBufferEx(const TCHAR* pszBuffer,const DWORD& dwLen);
	void AddToSendQueue(SEND_BUFFER* pSendQueueEntry);		// Send Queue�� �߰�
	bool SendFromQueue();									// Loop���� ���� �׿��ִ� �۽� ��Ŷ ����

private:

#ifdef SC_THREAD_SAFE
	CLockObject			m_LockObject;
#endif

	bool	m_bWritable;
	typedef queue<SEND_BUFFER*>	queueForSendQueueEntry;
	queueForSendQueueEntry m_SendQueue;
};
