// SockWnd.cpp

#include "stdafx.h"
#include <winsock2.h>

#include "SockWnd.h"
#include "DebugPrint.h"
#include "lgclientlog.h"
#include "PacketID.h"

#include "SPDebug.h"

char *get_dump_data(char *s, unsigned char *buf, int len, int offset)
{
	int     i;
	char    hex[10];
	unsigned char   *p = buf;

	strcpy(s, "");

	for(i = 0; i < len; i++) 
	{
		sprintf(hex, "%02X ", p[i]);
		strcat(s, hex);
	}

	return (s);
}
///////////////////////////////////////////////////////////////////////////////////////

CSockWnd * CSockWnd::m_pSockWnd = NULL;


CSockWnd::CSockWnd()
{
}

bool CSockWnd::Init(HWND hParentWnd, HINSTANCE hParentInst)
{
	m_pSockWnd = NULL;
	m_bConnect = FALSE;
	m_RecvQ = NULL;
	m_SendQ = NULL;
	RecvInit();
	m_iReadStreamCount = 0;

	WSAData ws;
	if(WSAStartup(MAKEWORD(2,2), &ws) != 0)	return FALSE;

	if ( LOBYTE( ws.wVersion ) != 2 || HIBYTE( ws.wVersion ) != 2 ) 
	{ 
		WSACleanup( ); 
		return false; 
	} 

	if(Create(hParentWnd, hParentInst))
	{
		return true;
	}

	return false;
}

void CSockWnd::Exit()
{
	Disconnect();
	WSACleanup( ); 
}
#if 1
void CSockWnd::SetQueue(CQueue<CPacket> *PlQueue, CQueue<CPacket> *cSendQ)
{
	m_RecvQ = PlQueue;
	m_SendQ = cSendQ;
}
#else
void CSockWnd::SetQueue(CMemoryPoolQueue<CPacket> *PlQueue, CMemoryPoolQueue<CPacket> *cSendQ)
{
	m_RecvQ = PlQueue;
	m_SendQ = cSendQ;
}
#endif

CSockWnd::~CSockWnd()
{
	m_pSockWnd = NULL;

	if(m_bConnect)
	{
		Disconnect();

		if(IsWindow(m_hWnd))
		{
			DestroyWindow(m_hWnd);
		}
	}

	Exit();
}
 
BOOL CSockWnd::Create(HWND hWnd, HINSTANCE hInst)
{
	if(m_pSockWnd)		return FALSE;

	m_hParentWnd = hWnd;

	m_hWnd = CreateWindowEx(NULL, "Message", NULL, WS_CHILD, 0, 0, 0, 0, m_hParentWnd, NULL, hInst, NULL);

	m_pSockWnd = this;
	SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG) CSockWnd::WndProc);

	return TRUE;		
}


BOOL CSockWnd::Connect(LPCTSTR szIPAddress, UINT iPort)
{
	if(!m_pSockWnd)		return FALSE;

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);

	// Socket Option
	int nZero = 100000;
/*
	if(setsockopt(m_Socket,SOL_SOCKET,SO_SNDBUF,(char*)&nZero,sizeof(nZero))!=0 )
	{
		SC_WSAERROR(setsockopt_sndbuf);
		return false;
	}
*/

	//nZero = 0;
	if(setsockopt(m_Socket,SOL_SOCKET,SO_RCVBUF,(char*)&nZero,sizeof(nZero)) != 0)
	{
		SC_WSAERROR(setsocket_rcvbuf);
		return false;
	}

	int on = 1;
	if(setsockopt(m_Socket,IPPROTO_TCP,TCP_NODELAY,(char*)&on,sizeof(on))!=0)
	{
		SC_WSAERROR(setsocket_nodelay);
		return false;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(iPort);
	addr.sin_addr.S_un.S_addr = inet_addr(szIPAddress);

	if(addr.sin_addr.S_un.S_addr == INADDR_NONE)
	{
		struct hostent *h = gethostbyname(szIPAddress);
		if(!h)	return FALSE;
		memcpy(&(addr.sin_addr.S_un.S_addr), h->h_addr, sizeof(int));
	}

	if(connect(m_Socket, (struct sockaddr *)&addr, sizeof(addr)) != 0) 
	{
		SC_WSAERROR(CSockWnd::connect);
		int iError = GetLastError();
		return FALSE;
	}

	m_bConnect = TRUE;

	//int iMode = 1;
	//ioctlsocket(m_Socket, FIONBIO, (u_long FAR*) &iMode);

	WSAAsyncSelect(m_Socket, m_hWnd, WM_SOCKET_MESSAGE, FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT);
	//PostMessage(m_hParentWnd, WM_SOCKET_CONNECT, 0, 0);

	return TRUE;
}

BOOL CSockWnd::Disconnect()
{
	if(m_bConnect)
	{
#if 0
		//LINGER linger;

		//linger.l_onoff = 0;
		//linger.l_linger = 0;

		//::setsockopt(m_Socket,SOL_SOCKET,SO_LINGER,(char*)&linger,sizeof(linger));

		::shutdown(m_Socket, SD_SEND);

		::closesocket(m_Socket);
#else
		::shutdown(m_Socket,SD_SEND);
#endif
	}

	m_bConnect = FALSE;
	m_RecvQ->reset();
	m_SendQ->reset();
	
	return TRUE;
}



//bool CSockWnd::MakePacket(UINT16 iMaxSize)
//{
//	// iOnceLen : ��Ʈ�� ����
//
//	int tLen; // �����ذ� ����.
//	int iReadLength;
//
//	iReadLength = 0;
//
//	while(iMaxSize > iReadLength)	 // iMaxSize �� �� ����������
//	{
//
//		switch( m_iPacketMode )
//		{
//		case HEADER_MODE:
//			tLen = PACKET_HEADER_SIZE - m_iPacketSize; // �ش��� �����ؾ� �� ������ ����Ʈ ����.
//
//			if(iMaxSize - iReadLength < tLen) tLen = iMaxSize - iReadLength ; // t_Len ����
//			
//			memcpy((void*)(m_cPacket.GetHead() + m_iPacketSize), m_Stream + iReadLength, tLen);
//
//			m_iPacketSize += tLen;
//			if(m_iPacketSize == PACKET_HEADER_SIZE)
//			{
//				m_iPacketSize = 0;
//
//				if(m_cPacket.GetHead()->length > PACKET_HEADER_SIZE) // Ping ����
//				{
//					m_iPacketMode = BODY_MODE;
//				}
//			}
//			break;
//		case BODY_MODE:
//			tLen = m_cPacket.GetHead()->length - PACKET_HEADER_SIZE - m_iPacketSize; // �ٵ� �����ؾ� �� ������ ����Ʈ ����.
//
//			if(iMaxSize-iReadLength < tLen) tLen = iMaxSize - iReadLength ; // t_Len ����
//
//			if(m_cPacket.GetHead()->length <= MAX_PACKET_SIZE)
//			{
//				memcpy((void*)(m_cPacket.GetBodyData() + m_iPacketSize), m_Stream + iReadLength ,tLen);
//			
//				m_iPacketSize += tLen;
//
//				if(m_iPacketSize ==  (m_cPacket.GetHead()->length - PACKET_HEADER_SIZE))
//				{
//					//PrintBuff(packet.GetPacketData(),packet.GetLength());
//					m_RecvQ->AddQ(&m_cPacket);
//					unsigned int iPacketID ;
//					memcpy(&iPacketID, m_cPacket.GetBodyData(), 4);
//					DebugPrint("%d Recv %d\n",m_Socket, iPacketID);
//					RecvInit();	
//				}
//			}
//			else
//				return false;
//
//			break;
//
//		default :
//				return false;
//
//		} // end switch
//
//		iReadLength = iReadLength + tLen;
//
//	}
//
//	return true;
//
//}
BOOL CSockWnd::RecvPacket()
{
	if(!m_bConnect)		return FALSE;

	unsigned long iSize; // ���� �ִ�ũ��.
	int iTotalLen ;
	int iOnceLen ; // �ѹ��� ������ �ִ� �ִ��Ѱ������
	int iError ;

	iSize = 0; 
	iError = ioctlsocket(m_Socket, FIONREAD, &iSize);
	if(iError == SOCKET_ERROR )
	{
		return FALSE;
	}
	if(iSize > 0)
	{		
		iOnceLen = iSize ;

		iTotalLen = 0; 

		while(iSize > iTotalLen)
		{


			iError = 0;

			if(iOnceLen > MAX_STREAM_SIZE)  iOnceLen = MAX_STREAM_SIZE;

			// iOnceLen��ŭ �о��

			if( RecvStream(iOnceLen) < 0)
			{
				DebugPrint("RecvStream::Socket Fail : %d\n ", GetLastError());
				return FALSE;
			}
			else
			{
				//�о�� ������ ��Ŷ�� ������.

				if(!MakePacket(iOnceLen))
				{
					DebugPrint("MakePacket::Socket Fail : %d\n ", GetLastError());
					return FALSE;
				}
			}

			iTotalLen += iOnceLen;

			iOnceLen = (iSize - iTotalLen);

		} // ������� ��� ��Ʈ���� ���ũ�⸦ �� �о���.
	}

	return TRUE;
}

//iMaxSize  :: �� ��Ʈ��.

int CSockWnd::RecvStream(const int iMaxSize)
{
	int t_len = 0;
	m_iReadStreamCount = 0;

	while(iMaxSize > m_iReadStreamCount )	 // iMaxSize�� �� ����������...
	{
		t_len = recv(m_Socket, (char *)m_Stream + m_iReadStreamCount, iMaxSize - m_iReadStreamCount,0 );

		// FIN�� �ϴ� ����.

		if ( t_len < 0 )
		{
			if ( WSAGetLastError() != WSAEWOULDBLOCK )
			{
				DebugPrint("RecvStream :: Socket Fail : %d\n ", GetLastError());
				return t_len;

			}
			DebugPrint("RecvStream :: Socket WSAEWOULDBLOCK\n");
			continue;
		}

		// PrintBuff((unsigned char *)msg,iMaxSize );
		m_iReadStreamCount = t_len + m_iReadStreamCount;

	}


	return t_len;
}
#if 1
bool CSockWnd::MakePacket(const int iMaxSize)
{

	// <PacketChunk> ::= <len:2><key:2><packetID:4><data:len-6>
	//
	//			<len:2> ::= sizeof(<PacketChunk>)


	//[xialin 2008/09/08]���Ĵ��ģʽ >>>
	//static const int  iTmpBufSize = 2048*2048;
	//static int  m_len = 0;
	//static char m_tmpBuf[iTmpBufSize];
	//if( iMaxSize < 0 || m_len + iMaxSize > iTmpBufSize )
	//{
	//	return false;
	//}
	//if(m_len < 0) m_len = 0;

	//memset(&m_tmpBuf[m_len] , 0 , iTmpBufSize - m_len);
	//memcpy(m_tmpBuf + m_len, m_Stream, iMaxSize);
 //	m_len += iMaxSize;

	//do
	//{
	//	int tmpLen = PACKET_HEADER_SIZE;
	//	if ( tmpLen > m_len ) return true;

	//	PACKET_HEADER Header;
	//	memset(&Header, 0x00, sizeof(PACKET_HEADER));
	//	memcpy(&Header, m_tmpBuf, tmpLen);

	//	tmpLen = Header.length;
	//	if ( tmpLen > m_len ) return true;

	//	RecvInit();
	//	memcpy(m_cPacket.GetPacketData(), m_tmpBuf, tmpLen);
	//	m_RecvQ->AddQ(&m_cPacket);

	//	if( (m_len - tmpLen > 0) && (m_len - tmpLen <= iTmpBufSize) )
	//		memcpy(&m_tmpBuf[0], &m_tmpBuf[tmpLen], m_len - tmpLen);

	//	m_len -= tmpLen;
	//}while(m_len > 0);
	//[xialin 2008/09/08]���Ĵ��ģʽ <<<



	int iRemainedBytes		= 0;	// �����ִ� ��
	int iStreamReadCount	= 0;
	int iStreamRemainedSize = iMaxSize; // ó���� �� ��Ʈ�� ������.

	//// �ѽ�Ʈ���� �� �Ҹ��Ҷ�����
	while(iStreamRemainedSize > 0)
	{
		// �ּ� ���̺δ� �޾����ִ��� üũ	
		if(m_iPacketSize >= PACKET_LENGTH_SIZE) 
		{
			// �޾ƾ� �� ũ�⸦ ����Ѵ�
			//	���� ����Ʈ �� = ��Ŷ��ũ�� - �޾Ƶ� ��Ŷ ũ�� ;
			if(m_cPacket.GetHead()->length > m_iPacketSize) 
				iRemainedBytes =  m_cPacket.GetHead()->length - m_iPacketSize;
			else 
				iRemainedBytes = 0;
		}
		else
		{
			// �ּ� ���̺ε� �޾��� ���� ���� �����̴�.
			iRemainedBytes = PACKET_LENGTH_SIZE - m_iPacketSize;
		}

		// ���� ���� ����.
		if( iStreamRemainedSize < iRemainedBytes) iRemainedBytes = iStreamRemainedSize;

		memcpy(m_cPacket.GetPacketData()+m_iPacketSize, m_Stream + iStreamReadCount, iRemainedBytes);

		m_iPacketSize += iRemainedBytes ;


		if(m_iPacketSize >=PACKET_LENGTH_SIZE && (m_cPacket.GetHead()->length == m_iPacketSize)) // �ϳ� �Ϸ�� ����
		{
			//unsigned int iPacketID ;
			//memcpy(&iPacketID, m_cPacket.GetBodyData(), 4);
			//DebugPrint("%d Recv %d, %d\n",m_Socket, iPacketID, m_cPacket.GetHead()->length);
			m_RecvQ->AddQ(&m_cPacket);
			RecvInit();	
		}

		iStreamRemainedSize -= iRemainedBytes;
		iStreamReadCount = iMaxSize - iStreamRemainedSize;
	}

	return true;
}

#else
//bool CSockWnd::MakePacket(const int iMaxSize)
//{
//
//	// <PacketChunk> ::= <len:2><key:2><packetID:4><data:len-6>
//	//
//	//			<len:2> ::= sizeof(<PacketChunk>)
//
//	int iRemainedBytes ;	// �����ִ� ��
//	int iStreamReadCount = 0;
//	int iStreamRemainedSize = iMaxSize; // ó���� �� ��Ʈ�� ������.
//	
//	// �ѽ�Ʈ���� �� �Ҹ��Ҷ�����
//	while(iStreamRemainedSize > 0)
//	{
//		// �ּ� ���̺δ� �޾����ִ��� üũ	
//		if(m_iPacketSize >=2) 
//		{
//			// �޾ƾ� �� ũ�⸦ ����Ѵ�
//			//	���� ����Ʈ �� = ��Ŷ��ũ�� - �޾Ƶ� ��Ŷ ũ�� ;
//			iRemainedBytes =  m_cPacket.GetHead()->length - m_iPacketSize;
//		}
//		else
//		{
//			// �ּ� ���̺ε� �޾��� ���� ���� �����̴�.
//			iRemainedBytes = 2;
//		}
//
//		// ���� ���� ����.
//		if( iStreamRemainedSize < iRemainedBytes) iRemainedBytes = iStreamRemainedSize;
//
//		memcpy(m_cPacket.GetPacketData()+m_iPacketSize, m_Stream + iStreamReadCount, iRemainedBytes);
//
//		m_iPacketSize += iRemainedBytes ;
//		
//
//		if(m_iPacketSize >=2 && (m_cPacket.GetHead()->length == m_iPacketSize)) // �ϳ� �Ϸ�� ����
//		{
//			//unsigned int iPacketID ;
//			//memcpy(&iPacketID, m_cPacket.GetBodyData(), 4);
//			//DebugPrint("%d Recv %d, %d\n",m_Socket, iPacketID, m_cPacket.GetHead()->length);
//			m_RecvQ->AddQ(&m_cPacket);
//			RecvInit();	
//		}
//
//		iStreamRemainedSize -= iRemainedBytes;
//		iStreamReadCount = iMaxSize - iStreamRemainedSize;
//
//	}
//
//	return true;
//
//}
//

#endif
//BOOL CSockWnd::RecvPacket()
//{
//	if(!m_bConnect)		return FALSE;
//
//	unsigned long iSize; // ���� �ִ�ũ��.
//	UINT16 iTotalLen ;
//	UINT16 iOnceLen ; // �ѹ��� ������ �ִ� �ִ��Ѱ������
//	int iError ;
//
//	iSize = 0; 
//	iError = ioctlsocket(m_Socket, FIONREAD, &iSize);
//	if(iError == SOCKET_ERROR )
//	{
//		return FALSE;
//	}
//	if(iSize > 0)
//	{		
//		DebugPrint("RecvPacket::ioctlsocket : %d\n ", iSize);
//		iOnceLen = (UINT16)iSize ;
//
//
//		if(!MakePacket(iOnceLen))
//		{
//			if(GetLastError() != WSAEWOULDBLOCK )
//			{
//				DebugPrint("MakePacket::Socket Fail : %d\n ", GetLastError());
//				return FALSE;
//			}
//		}
//	}
//
//	return TRUE;
//}
//

LRESULT CSockWnd::WndProcSock(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if(message == WM_SOCKET_MESSAGE)
	{
		if(WSAGETSELECTERROR(lParam) == 0)	// no error
		{
			switch (WSAGETSELECTEVENT(lParam))
			{
				case FD_WRITE : 
					DebugPrint("FD_WRITE:: %d,%d\n ", wParam,lParam);
					break;

				case FD_READ : 
                    {
						// test
						//time_t tTime = time(NULL);
						//if(tTime%2) break;
						// test

						if(!RecvPacket())
						{
							DebugPrint("FD_READ::Socket Fail : %d\n ", GetLastError());
						}
					}
					break;

				case FD_CLOSE :	
					// ���������� ������ ::shutdown �Ѱ��.
					DebugPrint("FD_CLOSE ::Socket Fail : %d\n ", GetLastError());
					PostMessage(m_hParentWnd, WM_SOCKET_DISCONNECT, 0, 0);

					closesocket(m_Socket);
					// ���� �õ� ���
					break;

				case FD_CONNECT :
					DebugPrint("FD_CONNECT ::%d\n");
					break;

				default :
					DebugPrint("default : Socket Fail : %d\n ", GetLastError());
					break;
			}
		}
		else
		{
			// ������ü�� ����Ȱ��. 
			// ������ ������������ ������ ����̹Ƿ� FD_CLOSE �� ���ƿ��� �ʴ´�.
			//m_bConnect = FALSE;
			m_RecvQ->reset();
			m_SendQ->reset();
			DebugPrint("Connect Abort %d\n", HIWORD(lParam));
			PostMessage(m_hParentWnd, WM_SOCKET_DISCONNECT, 0, 0);
		}
	}
	else
	{
		DebugPrint("DefWindowProc(%d, %d, %d, %d)\n",hWnd,message,wParam,lParam);
		return DefWindowProc(hWnd, message, wParam, lParam); 
	}

	return 0l;
}

void CSockWnd::PrintBuff(unsigned char* buf, int len )
{
	char    s2[3000]={'\0'};

	memset(s2,0,3000);

	get_dump_data(s2, buf, len,0);

	
	OutputDebugString(s2);
	OutputDebugString("\n");
	
	//printf("%s\n",s2);
//	g_packetDump.WriteLog(time(NULL), s2);

}

void CSockWnd::ForGracefulDisconnect()
{
	int ret = 0;

	char buf[100];

	while(1)
	{
		ret = recv(m_Socket, buf, 100,0 );
		if(ret <= 0)
		{
			break;
		}
	}

	::closesocket(m_Socket);
}

#if 0
	bool CSockWnd::SendPacketQ()
	{
		CPacket t_sendpacket;
		int t_len = 0, send_count = 0;

		if (m_Socket < 0) return FALSE;

		while(m_SendQ->PopQ(t_sendpacket))
		{
			t_len = 0;
			send_count = 0;

			//t_sendpacket.UpdateLength(); // ����� ���� ����

			//PrintBuff((unsigned char *)(t_sendpacket.GetPacketData()),t_sendpacket.GetHead()->length);
			while( send_count < t_sendpacket.GetHead()->length ) 
			{
				t_len = send(m_Socket,(char *)t_sendpacket.GetPacketData() + send_count, t_sendpacket.GetHead()->length - send_count,MSG_DONTROUTE);

				if ( t_len < 0 ) // error 
				{
					if( WSAGetLastError() != WSAEWOULDBLOCK)  
					{	
						DebugPrint("SendPacket :: Socket Fail : %d\n ", GetLastError());
	//					SendMessage(m_hParentWnd, WM_SOCKET_FAIL, WSAGetLastError(), 0);
						return false;
					}
					else
					{
						DebugPrint("Send::WSAEWOULDBLOCK");

						// Bug : comment by hoshim at 2007-8-29
						//			WSAEWOULDBLOCK ������ �߻��� ���, ���� �����Ϸ��� �� ��Ŷ(t_sendpacket)�� Queue���� pop �� ���¶�
						//			�� ��Ŷ�� �������� �ȴ�. ��, �������� ���� ���ϴ� ��Ŷ�� �߻��ϰ� �ȴ�.
						//		���� ���� : PopQ�� ����� PeekQ() �� ���� ����� �����ϴ���, t_sendpacket�� �ٽ� Queue�� PushHead()�ϵ��� ����.
					}
					break;
				}
				send_count += t_len;
			}	
		}
		return true;
	}
#else

	// WSAEWOULDBLOCK�� �߻����� ��, ó�� ���μ��� : 
	//		WSAEWOULDBLOCK --> Send �ߴ� --> Idle_Loop(Wait for FD_WRITE) --> FD_WRITE ���� --> Send ��õ�
	//
	bool CSockWnd::SendPacketQ()
	{
		if (m_Socket < 0) return FALSE;

		CPacket packet;
		int nSent = 0;					// send()�� ���� ���۵� ��
		int nTotalSent = 0;				// ���۵� �ѷ�
		int nDataLen = 0;				// ������ �����ͷ�
		TCHAR* pszData = NULL;			// ���� ���ۿ� ���� ������

		while(m_SendQ->PopQ(packet))
		{
			nSent = 0;
			nTotalSent = 0;
			pszData = (TCHAR*)packet.GetPacketData();
			nDataLen = packet.GetHead()->length;

			while(nTotalSent < nDataLen) 
			{
				nSent = send(m_Socket,pszData + nTotalSent, nDataLen - nTotalSent,MSG_DONTROUTE);
				if(nSent < 0) 
				{
					if(WSAGetLastError() != WSAEWOULDBLOCK)  
					{	
						DebugPrint("SendPacket :: Socket Fail : %d\n ", GetLastError());
						return false;
					}
					else
					{
						DebugPrint("Send::WSAEWOULDBLOCK");

						// �ӽ������� Sleep()�� �̿��Ͽ� ���ϴ� ����� ���� �� �־���.
						Sleep(100);
						// 2008.03.13 dhpark �ٽ� �۽��ؾ��ϹǷ� nTotalSent�� ������ ��ġ�� ���ϵ��� 0���� �����մϴ�. ���θ� -1 ��.
						nSent = 0;
					}
				}
				// 2008.03.13 dhpark WSAEWOULDBLOCK�� ������ ��۽��Ҷ� nSent�� -1�̾ nTotalSent�� 1����Ʈ ������ ���� ������ ������� �ִٰ� ������.
				// �հ���԰� ���� �ʿ�. �ϴ� nSent�� 0���� ������.
				nTotalSent += nSent;
			}
		}
		return true;
	}
#endif