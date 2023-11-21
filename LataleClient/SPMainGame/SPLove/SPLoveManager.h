// ***************************************************************
//  SPLoveManager		Version:  1.0		Date: 2008/09/25
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#ifndef SPLoveManager_h__
#define SPLoveManager_h__

#pragma once

enum LOVE_LDT_REQUIRE
{
	LOVE_LDT_REQUIRE_NULL		=	0				,
	LOVE_LDT_REQUIRE_FRIENDSHIP_CONSUME_ELY			,	//	133	[��ȥ]_(����)_Ely �Һ� �ݾ�
	LOVE_LDT_REQUIRE_FRIENDSHIP_CONSUME_ITEM		,	//	14	[��ȥ]_(����)_���� ������ ID
	LOVE_LDT_REQUIRE_PROPOSE_COMSUME_ELY			,	//	105	[��ȥ]_(��������)_ �������� �Һ� �ݾ�
	LOVE_LDT_REQUIRE_PROPOSE_COMSUME_ITEM			,	//	18	[��ȥ]_(��������)_ �������� ������
	LOVE_LDT_REQUIRE_PROPOSE_POSSIBLE_DISTANCE		,	//	19	[��ȥ]_(��������)_�������� ���� �ȼ� ���� �Ÿ�
	LOVE_LDT_REQUIRE_PROPOSE_POSSIBLE_LOVEPOINT		,	//	20	[��ȥ]_(��������)_�������� ���� ������
	LOVE_LDT_REQUIRE_PARTING_CONSUME_ELY			,	//	26	[��ȥ]_(�̺�)_�̺� �� �Һ�Ǵ� Ely
	LOVE_LDT_REQUIRE_PARTING_PENALTY_TIME			,	//	27	[��ȥ]_(�̺�)_�Ⱓ ���Ƽ �� ���� �ð�
	LOVE_LDT_REQUIRE_COMMON_MESSAGEBOX_REMAIN_TIME	,	//	28	[��ȥ]_(����)_�˾� �޽��� â ��� �� ���� �ð�
	LOVE_LDT_REQUIRE_WEDDING_POSSIBLE_DISTANCE		,	//	29	[��ȥ]_(��ȥ��)_��ȥ�� �Ÿ� üũ
	LOVE_LDT_REQUIRE_WEDDING_SHOUT_REMAIN_TIME		,	//	30	[��ȥ]_(��ȥ��)_��ġ�� �Է� �ʴ��� ��� �ð�
	LOVE_LDT_REQUIRE_WEDDING_EQUIP_SET_EFFECT		,	//	24	[��ȥ]_(��ȥ��)_���� ������ ���� üũ ��Ʈ ����Ʈ���̵�

	LOVE_LDT_REQUIRE_MAX							,
};


const int	RECALL_EFFECT_ID						= 100003;	/**< ���� ��ȯ Effect ID <br> */  


struct LOVE_LEVEL_DATA 
{
	int												m_iLevel;
	std::string										m_strTitle;
};

typedef std::map< int , LOVE_LEVEL_DATA >			STD_MAP_LOVE_LEVEL_DATA;

class SPPlayer;

class SPLoveManager
{
private:
	SPLoveManager									();

	static	SPLoveManager*							m_pLoveManagerInstance;

public:
	virtual ~SPLoveManager							();

	static	SPLoveManager*							GetInstance				(void);
	static	void									DelInstance				(void);

	//	�ʱ�ȭ
	void											Init					();
	void											ClearVariables			();

	int												GetRequire				( LOVE_LDT_REQUIRE eChatLDTRequire );

	LOVE_LEVEL_DATA*								GetLevelData			( int iLevel );

	void											SetLoveInfo				( WEDDING_INFO& stLoveInfo );
	WEDDING_INFO*									GetLoveInfo				();
	void											ClearLoveInfo			();
	int												GetCurPartingTime		();

	void											SetLifePartnerGUID		( GU_ID eLifePartner );
	GU_ID											GetLifePartnerGUID		();
	const char*										GetLifePartnerString	();

	SPPlayer*										GetLifePartner			();

	void											SetCutIn				( bool bCutIn );


	/**  
	 * NPC ���������� ��ȥ�� ��û <br>
	 @param  
	 @return 
	*/  
	bool											SetWeddingRequest		();
	
	/**  
	 * WEDDING_CS_REQUEST <br>
	 * ���� ���� ��û ��Ŷ�� ������ ������. <br>
	 @param  WEDDING_TYPE iType
	 @param  int iEly
	 @param  CONTAINER_SLOT SlotInfo
	 @param  std::string strName
	 @return bool
	*/  
	bool											SendWeddingRequest		(WEDDING_TYPE iType, int iEly, CONTAINER_SLOT SlotInfo, std::string strName);

	/**  
	 * WEDDING_SC_REQUEST <br>
	 * ���� ���� ��û�� ���� ����� ó���Ѵ�. <br>	 
	 * ���� ��û�� ���� ������ Response���� ó���Ѵ� <br>
	 @param  CPacket* pPacket
	 @return bool	 
	*/  
	bool											OnWeddingRequest		(CPacket* pPacket);

	/**  
	 * WEDDING_SC_REQUEST_RECV <br>
	 * ���� ���� ��û�� ���� <br>
	 @param  
	 @return 
	*/  
	// SPWIndowLove �������̽� ó���� [11/10/2008 AJJIYA]
//	bool											OnWeddingRequestRecv	(CPacket* pPacket);

	/**  
	 * WEDDING_CS_RESPONSE <br>
	 * ���� ���� ��û�� ���� ������ �Ѵ� <br>
	 * ���� ���� ���� ��Ŷ�� ������ ������ <br>
	 @param  WEDDING_TYPE iType
	 @param  bool bAccept						0�� ��� ���� 1�ΰ�� ����
	 @param  std::string strName				��û�� �̸�
	 @return 
	*/ 
	// SPWIndowLove �������̽� ó���� [11/10/2008 AJJIYA]
//	bool											SendWeddingResponse		(WEDDING_TYPE iType, bool bAccept, std::string strName);

	/**  
	 *  WEDDING_SC_RESPONSE <br>
	 * ���� ���� ��û�� ���� ������ ó���Ѵ� <br>
	 @param  
	 @return 
	*/  
	// SPWIndowLove �������̽� ó���� [11/10/2008 AJJIYA]
//	bool											OnWeddingResponse		(CPacket* pPacket);
	

	/**  
	 * �̺� �� Notice�� �ʿ��� �޽����� ����� �̺��Ұ����� ����� <br>
	 @param  
	 @return 
	*/  
	bool											GetWeddingDivorceMsgIndex	();

	/**  
	 * �̺��� Notice���� Yes�� ������ ��� �̺� �۾��� �����Ѵ� <br>
	 @param  
	 @return 
	*/  
	bool											SetWeddingDivorce		();	

	/**  
	 * WEDDING_SC_PARTING <br>
	 * �̺� ��û�� ���� ������ �޴´� <br>
	 @param  
	 @return 
	*/  
	bool											OnWeddingDivorce		(CPacket* pPacket);

	/**  
	* WEDDING_SC_WEDDING_CANCEL <br>
	* ���� ���¶�� ��� �������¸� ��ҽ�Ų��. <br>
	@param  
	@return 
	*/  

	void											OnWeddingCancel			( CPacket* pPacket );

	/**  
	* WEDDING_SC_MOTION_STARTEND <br>
	* ���� ��� ���� ���۽� Ű���� �Է� ó���� �Ѵ�. <br>
	@param  
	@return 
	*/  

	void											OnMotionStartEnd		( CPacket* pPacket );

	/**  
	 * ���� �÷��̾�� �߰��Ǵ� ����Ʈ �߿� ����� ��ȯ �� ���Դ��� Ȯ�� <br>
	 * �ش� ��ȯ�� ���� ��� ��ȯ ������ �ִ��� Ȯ���Ͽ� ��ȯ ���θ� ���� notice�� �ٿ�� <br>
	 @param  
	 @return 
	*/  
	//bool											CheckRecallEffect		( int iEffectID );

	/**  
	 * ��ȯ ���� ��û <br>
	 * �˾� �޽����� ��ȯ�� ���Ұ����� Ȯ�� �Ҽ� �ֵ��� �Ѵ� <br>
	 @param  
	 @return 
	*/  
	bool											OnRequestRecall			( CPacket* pPacket );

	/**  
	* ��ȯ �����ڿ��� ��ȯ�� ���� �ߴ��� �˸� <br>
	@param  
	@return 
	*/  
	bool											OnRequestRecallErr		( CPacket* pPacket );

	/**  
	 * ��ȯ ���ο� ���� ������ �˸� <br>
	 @param  
	 @return 
	*/  
	bool											SendAcceptRecall		( bool bAccept );
	
	/**  
	 * ��ȯ ���� ���� �˸��� ��� <br> 
	 * ��ȯ ������� �ǻ� ���� <br>
	 @param  
	 @return 
	*/  
	bool											OnAcceptRecall			( CPacket* pPacket );

	/**  
	 * ��ȯ ���� ���� �˸��� ��� <br> 
	 * ��ȯ ��ų �����ڿ��� ��ȯ ������� �ǻ� ���� <br>
	 @param  
	 @return 
	*/  
	bool											OnResultRecall			( CPacket* pPacket );

	D3DXCOLOR										GetD3DColor				( int ColorIndex );
	D3DXCOLOR*										GetD3DColor2			( int ColorIndex );
	
	void											CleanColor2();

	void											LoadColorNameLDT		();
protected:

	void											LoadGlobalSysLDT		();
	void											LoadLDT					();

	void											AddLevelData			( LOVE_LEVEL_DATA& stLoveLevelData );

	/**  
	* WEDDING_CS_PARTING �� �ӽ� <br>  
	* ���� �Ǵ� ��ȥ ���¿��� ���󼭱� ��û�� �Ѵ� <br>
	@param  
	@return 
	*/  
	bool											SendWeddingDivorce		(int iEly);

	/**  
	 * ����� ��ȯ�� ���� ��ȯ ������ �ִ� ��Ȳ���� üũ �Ѵ� <br>
	 @param  
	 @return 
	*/  
	//bool											IsEnableRecall			();

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	int												m_iRequireLDT[ LOVE_LDT_REQUIRE_MAX ];

	STD_MAP_LOVE_LEVEL_DATA							m_mLoveLevelData;

	WEDDING_INFO									m_stLoveInfo;
	GU_ID											m_eLifePartner;

	double											m_iAbsoluteTime;
	enum { ColorNameNum = 11 };
	D3DXCOLOR										m_ColorName[ ColorNameNum ];

	D3DXCOLOR*										m_ColorNameTwo[ ColorNameNum ];

};

#endif // SPLoveManager_h__