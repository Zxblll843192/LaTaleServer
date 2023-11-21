/*!
!module �������
!moduletype �������
�������

!inc SDRSClient.h
*/ 

// SDRSClient.h  �����ͷ�ļ� 
#pragma once
#include "SDBase.h"


namespace SGDP {

// �������
const char SDRSCLIENT_MODULENAME[] = "SDRSClient";

// ����汾��
const SSGDPVersion	SDRSCLIENT_VERSION = {0,5,0,1};

/*!
!macro SDRSCLIENT_
���鴰������
!inc SDRSClient.h
*/
#define SDRSCLIENT_INGAME		1		// ģ�����Ϸ�ڲ�����
#define SDRSCLIENT_POPUP		2		// ����ΪƯ������Ϸ�ⲿ�Ĵ���

/*!
!marco SDRSCLIENT_ERROR_
SDRSClient����������
!inc SDRSClient.h
*/

#define SDRSCLIENT_ERROR_OK						0				//>=0��ʾִ�гɹ�
#define SDRSCLIENT_ERROR_LOADCONFIG				-1				// -1 ��ʾ���������ļ���Դʧ��	��������ļ��Ƿ���ڡ���ʽ�Ƿ���ȷ
#define SDRSCLIENT_ERROR_NET					-2				// -2 ��ʼ������������ʱʧ�ܡ����DLL�Ƿ���� ��������ַ�����Ƿ���ȷ
#define SDRSCLIENT_ERROR_WIN32					-3				// -3 ����Win32����ʱʧ���ˡ����ͼƬ��Դ�Ƿ����

/*!
!marco SDRSCLIENT_ACTION_
SDRSClient�¼�����
!inc SDRSClient.h
*/

#define SDRSCLIENT_ACTION_SENDBTN				1				//�����������ⰴť�¼�
#define SDRSCLIENT_ACTION_EXITBTN				2				//�����뿪��ť�¼�
#define SDRSCLIENT_ACTION_HIGHBTN				3				//�������ⰴť�¼�
#define SDRSCLIENT_ACTION_LOWBTN				4				//���������ⰴť�¼�
#define SDRSCLIENT_ACTION_SLIDER_UP				5				//��������
#define SDRSCLIENT_ACTION_SLIDER_DOWN			6				//��������

//===========================================================================================================
/*!cls
�ʺ羫��ͳһ�ͻ��������
!inc SDRSClient.h
*/
class ISDRSClient : public ISDBase
{
public:
	/**************************************************************************************************/
	//!group ��ʼ������
	/*!func
	�˺������������ʺ羫�鴰��
	!param [in] ��Ϸ��Ⱦ���ھ��
	!param [in] ���ڲ��������ļ�
	!return ������롡�μ�SDRSCLIENT_ERROR_
	*/
	// �����ʺ羫�鴰��
	virtual int SDAPI CreateRSWindow(HWND hMainWnd = NULL, const char * strConfigFile = NULL) = 0;
	
	/*!func
	������Ϸ�����Ϣ(���������ļ��ж�ȡ,��������Ϸ�ṩ,�����ڴ������ڳɹ������)
	!param [in] ��Ϸ����(�μ���Ϸ�����ֱ���:���紫�� 1 �λ� 2)
	!param [in] ������������ֱ���
	!param [in] �ʺ����� "0" �����ʺ� "1"��ʢ��ͨ��֤
	!param [in] �ʺ�
	!return Ŀǰ����ʧ��
	*/
	virtual bool SDAPI SetGameInfo( int nGameType, int nAreaCode, char* szIDType, char* szUserID) = 0;
	

	/*!func
	// ���ô��ڵ�ģʽ �����ڴ���������֮����á�������Ч
	!param [in] �������ࡡ�μ�SDRSCLIENT_
	!return �ɹ�Ϊtue ʧ�� false
	*/
	virtual bool SDAPI SetMode(int iMode) = 0;


	/****************************************************************************************************/
	//!group ���ڿ��ƺ���
	/*!func
	// ����ʺ羫�鴰��״̬���ָ������ڴ���ʱ��״̬
	!return Ŀǰ����ʧ��
	*/
	virtual bool SDAPI Reset() = 0;
	/*!func 
	// ��ʾ�����زʺ羫�鴰��
	!param [in] ��ʾ���
	!return Ŀǰ����ʧ��
	*/
	virtual bool SDAPI Show(bool bShow = true) = 0;

	/*!func
	// ���ô��ڵ�����(ע����POPUPģʽ����Ϊ�������������)
	!param [in]��x
	!param [in] y
	!return Ŀǰ����ʧ��
	*/
	virtual bool SDAPI SetPos(int iX, int iY) = 0;

	/*!func
	// ���ô��ڵĳߴ�
	//�����ܳ����иı䴰�ڵĴ�С,���ڵĴ�С��Ҫ�������,��ͼƬ��Դ�ж�ȡ�������ýӿ�
	!param [in] ���ڿ�
	!param [in] ���ڸ�
	!return Ŀǰ��ʧ��
	*/
	virtual bool SDAPI SetSize(int iWidth, int iHeight) = 0;

	/*!func
	// ��ô��ڵ�λ��
	!param [in] x
	!param [in] y
	*/
	virtual bool SDAPI GetPos(int & iX, int & iY) = 0;

	/*!func
	// ��ô��ڵĳߴ�
	!param [in] ���ڿ�
	!param [in] ���ڸ�
	!return Ŀǰ����ʧ��
	*/
	virtual bool SDAPI GetSize(int & iWidth, int & iHeight) = 0;

	/*!func
	// ��ô��ڵ�ģʽ
	!return �μ�SDRSClIENT_
	*/

	virtual int  SDAPI GetMode() = 0;
	/*!func
	// �жϴ����Ƿ�����ʾ״̬
	!return ��ʾ��true ����false
	*/
	virtual bool SDAPI IsShow() = 0;
	
	/*!func
	//�����Ƿ��������ƶ�
	!param [in] �����������ƶ�
	!return Ŀǰ����ʧ��
	*/
	virtual bool SDAPI SetMoveable( bool bCanMove = true) = 0;

	/*!func
	//�жϴ����Ƿ���ƶ�
	!return ���ƶ� true ���ɡ�false
	*/
	virtual bool SDAPI GetMoveable( ) = 0;

	/*!func
	//�����ṩ���ֱ��ü�ģ�ⴰ���з�����һЩ�¼�
	!param [in] �¼����μ���SDRSCLINET_ACTION
	!return �ɹ���true ʧ�ܡ�false
	*/
	virtual bool SDAPI ExecuteAction( int iAction) = 0;
};


/*!func
�˺�������SDRSClient�����ʵ����
!param [in] �û�Ҫ��������Ͱ汾�ţ���SSGDPVersion��
!return ����ɹ������ش������ʾ�������ʶ�𷵻ؿ�ָ�롣
!inc SDRSClient.h
*/
ISDRSClient * SDAPI SDRSClientGetModule(const SSGDPVersion *pstVersion);

/*!typedef
SDRSClientGetModule ���������Ͷ��塣
!inc SDRSClient.h
*/
typedef ISDRSClient * (SDAPI *PFN_SDRSClientGetModule)(const SSGDPVersion *pstVersion);

}
