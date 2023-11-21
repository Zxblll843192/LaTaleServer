#define PACK_MAX 20480

#define RETSZ_NET_UNINIT			"����������δ��ʼ���������SetNetParam�������÷�����IP�Ͷ˿ڡ�"
#define RETSZ_NET_SENDFAIL			"������Ϣʧ�ܣ�������Ϊ��"
#define RETSZ_NET_RECVTIMEOUT		"���ճ�ʱ��"
#define RETSZ_NET_RECVERR			"�����������ڣ�����ʧ�ܡ�"
#define RETN_NET_UNINIT				0x0100		//Please call ��SetNetParam�� first
#define RETN_NET_SENDFAIL			0x0101		//Send failed
#define RETN_NET_RECVTIMEOUT		0x0102		//Receive message time out
#define RETN_NET_RECVERR			0x0103		//Server not exist

#define	RETSZ_PARAM_ERR				"�����������"
#define RETSZ_PARAM_COMBINEFAIL		"����������ʧ�ܡ�"
#define RETSZ_PARAM_ANALYZEFAIL		"���ܵ�content����ʧ�ܡ�"
#define RETSZ_PARAM_OVERFLOW		"�ֽ�������������õ�����ռ䣬�뿪�����Ľ��ܻ�������"
#define	RETN_PARAM_ERR				0x0200		//Parameters is empty or wrong value     
#define RETN_PARAM_COMBINEFAIL		0x0201		//Combine request packet failed
#define RETN_PARAM_ANALYZEFAIL		0x0202		//Analyze receive packet failed
#define RETN_PARAM_OVERFLOW			0x0203		//szRetContent is smaller than needed

#define	RETSZ_PARAM_NULL			"�����������"
#define	RETSZ_PARAM_EMPTY			"�������Ϊ�ա�"
#define	RETSZ_PARAM_2LONG			"�������������"
#define	RETSZ_PARAM_IDTYPE			"IDTYPE����"
#define	RETSZ_PARAM_POINT			"���۷�������"
#define	RETN_PARAM_NULL				0x0211		//point is NULL		
#define	RETN_PARAM_EMPTY			0x0212		//����
#define	RETN_PARAM_2LONG			0x0213		//too long
#define	RETN_PARAM_IDTYPE			0x0214		//idtype is not 0,1 or 2
#define	RETN_PARAM_POINT			0x0215		//point is not one of 1,2,3

#define RETSZ_RECV_PARAMERR			"���ز����Ƿ�"
#define RETN_RECV_PARAMERR			0x0300		//Return value wrong

#define	RETSZ_CATCH					"catch error"
#define RETSZ_NEVERREACH			"never run to here"
#define	RETN_CATCH					0x0900		//unknown error throw by catch(��)
#define RETN_NEVERREACH				0x0901		//logical impossibly

///////////////////////////////////////////////////����Ϊ����������////////////////////////////

//SERVER RETURN VALUE
#define SENDQ						0x1000
#define RETN_SENDQ_OK				0x1010		//�������ݣ����ش�										//Return right content
#define RETN_SENDQ_SYSERR			0x1011		//��ϵͳ����												//System Error
#define	RETN_SENDQ_SYSREFUSE		0x1012		//��ϵͳ�ܾ�												//System Refused request
#define	RETN_SENDQ_PARAMERR			0x1013		//����������												//Parameter error
#define	RETN_SENDQ_BUSY				0x1014		//��ϵͳæ�����ݣ����磺���ء�ϵͳæ����1���Ӻ����ԡ�.��	//System busy
#define	RETN_SENDQ_NOMATCH			0x1015		//����ƥ���												//no match answer or question check failed

#define RETSZ_SENDQ_OK				"�����ݣ����ش�"			
#define RETSZ_SENDQ_SYSERR			"ϵͳ����"					
#define	RETSZ_SENDQ_SYSREFUSE		"ϵͳ�ܾ�"					
#define	RETSZ_SENDQ_PARAMERR		"��������"					
#define	RETSZ_SENDQ_BUSY			"ϵͳæ����1���Ӻ����ԡ�"	
#define	RETSZ_SENDQ_NOMATCH			"��ƥ���"				

#define JUDGE_GOOD					"1"
#define JUDGE_JUSTSOSO				"2"
#define JUDGE_AWFUL					"3"

#define	JUDGEANSWER					0x1100
#define RETN_JUDGEANSWER_OK			0x1110		//���ɹ�			//Send OK
#define RETN_JUDGEANSWER_SYSERR		0x1111		//��ϵͳ����		// System Error
#define RETN_JUDGEANSWER_SYSREFUSE	0x1112		//��ϵͳ�ܾ�		// System Refused request
#define RETN_JUDGEANSWER_PARAMERR	0x1113		//����������		// Parameter error
#define RETN_JUDGEANSWER_BUSY		0x1114		//��ϵͳæ			// System busy
#define RETN_JUDGEANSWER_NOMATCH	0x1115		//����ƥ������		// no match answer or question check failed

#define RETSZ_JUDGEANSWER_OK		"�ɹ�"
#define RETSZ_JUDGEANSWER_SYSERR	"ϵͳ����"
#define RETSZ_JUDGEANSWER_SYSREFUSE	"ϵͳ�ܾ�"
#define RETSZ_JUDGEANSWER_PARAMERR	"��������"
#define RETSZ_JUDGEANSWER_BUSY		"ϵͳæ����1���Ӻ����ԡ�"
#define RETSZ_JUDGEANSWER_NOMATCH	"��ƥ������"

#define SENDQEX						0x1300
#define RETN_SENDQEX_OK				0x1310		//�������ݣ����ش�									// Return right content
#define RETN_SENDQEX_SYSERR			0x1311		//��ϵͳ����											// System Error
#define	RETN_SENDQEX_SYSREFUSE		0x1312		//��ϵͳ�ܾ�											// System Refused request
#define	RETN_SENDQEX_PARAMERR		0x1313		//����������											// Parameter error
#define	RETN_SENDQEX_BUSY			0x1314		//��ϵͳæ�����ݣ����磺���ء�ϵͳæ����1���Ӻ����ԡ�.��// System busy
#define	RETN_SENDQEX_NOMATCH		0x1315		//����ƥ���											// no match answer or question check failed

#define RETSZ_SENDQEX_OK			"�����ݣ����ش�"
#define RETSZ_SENDQEX_SYSERR		"ϵͳ����"
#define	RETSZ_SENDQEX_SYSREFUSE		"ϵͳ�ܾ�"
#define	RETSZ_SENDQEX_PARAMERR		"��������"
#define	RETSZ_SENDQEX_BUSY			"ϵͳæ����1���Ӻ����ԡ�"
#define	RETSZ_SENDQEX_NOMATCH		"��ƥ���"

#define SENDQNEW					0x1400
#define RETN_SENDQNEW_OK			0x1410		//�������ݣ����ش�										// Return right content
#define RETN_SENDQNEW_SYSERR		0x1411		//��ϵͳ����												// System Error
#define RETN_SENDQNEW_SYSREFUSE		0x1412		//��ϵͳ�ܾ�												// System Refused request
#define RETN_SENDQNEW_PARAMERR		0x1413		//����������												// Parameter error
#define RETN_SENDQNEW_BUSY			0x1414		//��ϵͳæ�����ݣ����磺����"ϵͳæ����1���Ӻ����ԡ�."		// System busy
#define RETN_SENDQNEW_NOMATCH		0x1415		//�������ݣ���ƥ��𰸻�������Ⱦ�����						// no match answer or question check failed

#define RETSZ_SENDQNEW_OK			"�����ݣ����ش�"
#define RETSZ_SENDQNEW_SYSERR		"ϵͳ����"
#define	RETSZ_SENDQNEW_SYSREFUSE	"ϵͳ�ܾ�"
#define	RETSZ_SENDQNEW_PARAMERR		"��������"
#define	RETSZ_SENDQNEW_BUSY			"ϵͳæ����1���Ӻ����ԡ�"
#define	RETSZ_SENDQNEW_NOMATCH		"��ƥ��𰸻�������Ⱦ�����"


#define RECVANS						0x1500
#define RETN_RECVANS_OK				0x1510		//�������ݣ����ش�										// Return right content
#define RETN_RECVANS_SYSERR			0x1511		//��ϵͳ����												// System Error
#define RETN_RECVANS_SYSREFUSE		0x1512		//��ϵͳ�ܾ�												// System Refused request
#define RETN_RECVANS_PARAMERR		0x1513		//����������												// Parameter error
#define RETN_RECVANS_BUSY			0x1514		//��ϵͳæ�����ݣ����磺���ء�ϵͳæ����1���Ӻ����ԡ�.��	// System busy 

#define RETSZ_RECVANS_OK			"�����ݣ����ش�"
#define RETSZ_RECVANS_SYSERR		"ϵͳ����"
#define	RETSZ_RECVANS_SYSREFUSE		"ϵͳ�ܾ�"
#define	RETSZ_RECVANS_PARAMERR		"��������"
#define	RETSZ_RECVANS_BUSY			"ϵͳæ����1���Ӻ����ԡ�"

#define HotQTopN					0x1600
#define RETN_HotQTopN_OK			0x1610		//�������ݣ�����HotQuestionTopN����							// Return right content
#define RETN_HotQTopN_SYSERR		0x1611		//��ϵͳ����												// System Error
#define RETN_HotQTopN_SYSREFUSE		0x1612		//��ϵͳ�ܾ�												// System Refused request
#define RETN_HotQTopN_PARAMERR		0x1613		//����������												// Parameter error
#define RETN_HotQTopN_BUSY			0x1614		//��ϵͳæ�����ݣ����磺���ء�ϵͳæ����1���Ӻ����ԡ�.��	// System busy

#define RETSZ_HotQTopN_OK			"�����ݣ�����HotQuestionTopN����"
#define RETSZ_HotQTopN_SYSERR		"ϵͳ����"
#define	RETSZ_HotQTopN_SYSREFUSE	"ϵͳ�ܾ�"
#define	RETSZ_HotQTopN_PARAMERR		"��������"
#define	RETSZ_HotQTopN_BUSY			"ϵͳæ����1���Ӻ����ԡ�"

#define REASONSTAISFIED  0x1A00
#define REASONSTAISFIED_OK 0x1A10
#define REASONSTAISFIED_SYSERR 0x1A11
#define REASONSTAISFIED_SYSREFUSE 0x1A12
#define REASONSTAISFIED_PARAMERR 0x1A13
#define REASONSTAISFIED_BUSY 0x1A14

#define DESC_REASONSTAISFIED_OK "�����ݣ����ز���������"
#define DESC_REASONSTAISFIED_SYSERR "ϵͳ����"
#define DESC_REASONSTAISFIED_SYSREFUSE "ϵͳ�ܾ�"
#define DESC_REASONSTAISFIED_PARAMERR "��������"
#define DESC_REASONSTAISFIED_BUSY "ϵͳæ����1���Ӻ����ԡ�"

// DDSS�����ʴ�(0x1700) 
/*
0x1710�������ݣ����ش�
0x1711��ϵͳ����
0x1712��ϵͳ�ܾ�
0x1713����������
0x1714��ϵͳæ�����ݣ����磺����"ϵͳæ����1���Ӻ����ԡ�."
0x1715�������ݣ���ƥ��𰸻�������Ⱦ�����

CommandΪ0x1715ʱ: ����Ϊ "0" \0�޴���ʾ��������Ⱦ����� \0 "0"
CommandΪ0x1710ʱ:
��Xml��ʽ����ƥ���(MasterAns<��Ϸ���͡���Id�������ݡ��û���־���>)
���������(OtherAns<��Ϸ���͡���Id������Id����������>)
*/
#define SENDQV2						0x1700
#define RETN_SENDQV2_OK				0x1710		//�������ݣ����ش�
#define RETN_SENDQV2_SYSERR			0x1711		//��ϵͳ����
#define RETN_SENDQV2_SYSREFUSE		0x1712		//��ϵͳ�ܾ�
#define RETN_SENDQV2_PARAMERR		0x1713		//����������
#define RETN_SENDQV2_BUSY			0x1714		//��ϵͳæ�����ݣ����磺����"ϵͳæ����1���Ӻ����ԡ�."
#define RETN_SENDQV2_NOMATCH		0x1715		//�������ݣ���ƥ��𰸻�������Ⱦ�����

#define RETSZ_SENDQV2_OK			"�����ݣ����ش�"
#define RETSZ_SENDQV2_SYSERR		"ϵͳ����"
#define	RETSZ_SENDQV2_SYSREFUSE		"ϵͳ�ܾ�"
#define	RETSZ_SENDQV2_PARAMERR		"��������"
#define	RETSZ_SENDQV2_BUSY			"ϵͳæ����1���Ӻ����ԡ�"
#define	RETSZ_SENDQV2_NOMATCH		"��ƥ��𰸻�������Ⱦ�����"