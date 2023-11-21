
#include "SPCommon.h"
//
#include "SPGameObjectDEF.h"
#include "SPManagerDef.h"
#include "SPManager.h"
#include "SPGOBManager.h"

//
#include "SPGameObject.h"
#include "SPGOBStatus.h"
#include "SPGOBClusterDef.h"
#include "SPGOBCluster.h"
#include "SPGobModelUnit.h"
#include "SPAvatarModelUnitDef.h"
#include "SPAvatarModelUnit.h"
#include "SPPlayer.h"

#include <WinSock2.h>
#include "Packet.h"
#include "PacketHandler.h"

#include "SPNetworkManager.h"

extern SPNetworkManager* g_pNetworkManager;


DEFINE_SC_PACKET_PROC(TRADE_SC_REQUEST)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	// GU_ID			SrcCharGUID;				// �ŷ���û��
	// char				szSrcCharName[LEN_NAME+1];	// �ŷ���û���̸�
	// GU_ID			DstCharGUID;				// �ŷ������
	// char				szDstCharName[LEN_NAME+1];	// �ŷ�������̸�
	// GOLBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&SrcCharGUID);
	//packet->ExtractData(szSrcCharName, LEN_NAME+1);
	//packet->ExtractUINT64(&DstCharGUID);
	//packet->ExtractData(szDstCharName, LEN_NAME+1);
	//packet->ExtractUINT32(&ErrorID);

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;

	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_REQUEST, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(TRADE_SC_RESPONSE)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	// GU_ID			SrcCharGUID;				// �ŷ���û��
	// char				szSrcCharName[LEN_NAME+1];	// �ŷ���û���̸�
	// GU_ID			DstCharGUID;				// �ŷ������
	// char				szDstCharName[LEN_NAME+1];	// �ŷ�������̸�
	// UINT8			byAccept;					// ����/����
	// GOLBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&SrcCharGUID);
	//packet->ExtractData(szSrcCharName, LEN_NAME+1);
	//packet->ExtractUINT64(&DstCharGUID);
	//packet->ExtractData(szDstCharName, LEN_NAME+1);
	//packet->ExtractUINT8(&byAccept);
	//packet->ExtractUINT32(&ErrorID);
	
	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;
	
	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_RESPONSE, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(TRADE_SC_PUSHMONEY)
{
	GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
	//GU_ID			ActCharGUID;	// ���� �ø� �ƹ�Ÿ�� Ű
	//UINT64		uiMoney;		// �ø� ��

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&ActCharGUID);
	//packet->ExtractUINT64(&uiMoney);

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;

	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_PUSHMONEY, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(TRADE_SC_PUSHITEM)
{
	GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
	//GU_ID			ActCharGUID;	// �������� �ø� �ƹ�ŸŰ
	//TRADE_ITEM	stTradeItem;	// �������� �ø� ������ �����̳�,����,Ʈ���̵彽�� ������ ����ִ� ����ü
	//ITEM			stItem;			// �����ۿ� ���� �������� �����༭ ���콺�� �����ۿ� ��ġ��Ű�� ������ �����ټ��ֵ�����

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&ActCharGUID);
	//packet->ExtractStruct(&stTradeItem, sizeof(TRADE_ITEM));
	//packet->ExtractStruct(&stItem, sizeof(ITEM));

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;

	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_PUSHITEM, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(TRADE_SC_POPITEM)
{
	GU_ID			ObjectGUID;		// ���ӿ�����Ʈ���̵�
	//GU_ID			ActCharGUID;	// �������� ���� �ƹ�ŸŰ
	//SLOT_INDEX	TradeSlotIndex;	// Ʈ���̵彽��

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&ActCharGUID);
	//packet->ExtractUINT8(&TradeSlotIndex);

	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;

	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_POPITEM, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(TRADE_SC_WAIT)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	// GU_ID			ActCharGUID;				// accept�� ���� �ƹ�ŸŰ
	// UINT8			byAllWait;					// �ŷ����ϷῩ��

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&ActCharGUID);
	//packet->ExtractUINT8(&byAllWait);
	
	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;

	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_WAIT, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(TRADE_SC_ACCEPT)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	// GU_ID			ActCharGUID;				// accept�� ���� �ƹ�ŸŰ
	// UINT8			byFinish;					// �ŷ��ϷῩ��
	// GOLBAL_STRING_ID	ErrorID;					// �������̵�(0�̸� ��������)
	// GU_ID			ErrCharGUID;				// ���������� �ƹ�ŸŰ

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&ActCharGUID);
	//packet->ExtractUINT8(&byFinish);
	//packet->ExtractUINT32(&ErrorID);
	//packet->ExtractUINT64(&ErrCharGUID);
	
	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;

	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_ACCEPT, wParam, lParam);
}

DEFINE_SC_PACKET_PROC(TRADE_SC_CANCEL)
{
	GU_ID				ObjectGUID;					// ���ӿ�����Ʈ���̵�
	// GU_ID			ActCharGUID;				// �ŷ��� ����� �ƹ�ŸŰ

	packet->ExtractUINT64(&ObjectGUID);
	//packet->ExtractUINT64(&ActCharGUID);
	
	WPARAM wParam = (WPARAM)(&ObjectGUID);
	LPARAM lParam = (LPARAM)packet;
	g_pGOBManager->SPPerformMessage(SPGM_TRADE_SC_CANCEL, wParam, lParam);
}
