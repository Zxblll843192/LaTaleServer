#pragma once 


enum CHECK_STATUS_RESULT {
	CHECK_STATUS_RESULT_FAIL = 0,
	CHECK_STATUS_RESULT_V1 = 1,
	CHECK_STATUS_RESULT_V2 = 2,
	CHECK_STATUS_RESULT_OK = 3,
	CHECK_STATUS_RESULT_MAX = 4,
};


enum REQUIRE_TYPE {
	REQUIRE_TYPE_NULL			= 0,	/**< ��Ÿ�� ���� <br> */
	REQUIRE_TYPE_STAT			= 1,	/**< ��Ÿ�� ���� <br> */
	REQUIRE_TYPE_ITEM			= 2,	/**< ��Ÿ�� ������ <br> */	
	REQUIRE_TYPE_SKILL			= 3,	/**< ��Ÿ�� ��ƿ <br> */
	REQUIRE_TYPE_QUEST			= 4,	/**< ��Ÿ�� ����Ʈ <br> */
	REQUIRE_TYPE_TITLE			= 5,	/**< ��Ÿ�� Ÿ��Ʋ <br> */
	REQUIRE_TYPE_MAP			= 6,	/**< ��Ÿ�� �� <br> */
	REQUIRE_TYPE_EFFECT			= 7,	/**< ��Ÿ�� ����Ʈ <br> */
	REQUIRE_TYPE_GUILD			= 8,	/**< ��Ÿ�� ��� <br> */
	REQUIRE_TYPE_COREEVENT		= 9,	/**< ��Ÿ�� ���� �̺�Ʈ<br> */
	REQUIRE_TYPE_EQUIP			= 10,	/**< ��Ÿ�� ��� ���� <br> */
	REQUIRE_TYPE_EQUIP_MOTION	= 11,	/**< ��Ÿ�� ��� MotionID Ÿ�� <br> */
	REQUIRE_TYPE_MAX,					/**< �ִ� <br> */
};


enum PLAYER_STATE {
	PLAYER_STATE_NOT			= -1,	/**< �÷��̾� ��ü ���� <br> */
	PLAYER_STATE_NULL			= 0,	/**< �����̵� �Ҽ� ���� <br> */
	PLAYER_STATE_DEAD			= 1,	/**< ��� <br> */
	PLAYER_STATE_TRADE			= 2,	/**< Ʈ���̵� �� <br> */
	PLAYER_STATE_SHOPOPEN		= 3,	/**< ���λ��� ������ <br> */
	PLAYER_STATE_SHOPIN			= 4,	/**< ���λ��� �� ��� <br> */
	PLAYER_STATE_CUTIN			= 5,	/**< ���� ��Ȳ�� ��� <br> */
	PLAYER_STATE_MAX			= 6,
};


enum NOTICE_USE;


/**
* @class SPCheckManager
* @brief PC�� �������ͽ�, ITEM, SKILL, QUEST���� üũ�ϱ� ���� �뵵�� �޴���
* @author Jinhee
* @version 00.00.01
* @date 2005.9.27
* @bug ����
* @warning 
*/
class SPCheckManager : public SPManager {
public:
	SPCheckManager();
	virtual ~SPCheckManager();

	virtual void Process	(float fTime);
	virtual	void Render		(float fTime);
	//virtual void RenderTextDebug();
	//virtual void RenderText();

	virtual bool Init();
	virtual void Clean();

	virtual int SPPerformMessage	(UINT msg, WPARAM wparam = 0, LPARAM lParam= 0);	


	/**
	* PC STATUS �� üũ�� �������� �Ұ��������� ��ȯ�Ѵ� <br> 
	@param CHECK_STATUS iStatus
	@param INT64 iValue1
	@param INT64 iValue2
	@return bool
	*/
	bool	CheckPCStatus(CHECK_STATUS iStatus, INT64 iValue1, INT64 iValue2);

	/**
	 * �ش� ID�� �������� ���ü��� üũ�Ѵ� <br>
	 @param int iItemID
	 @param INT64 iValue1
	 @param INT64 iValue2
	 @return bool
	*/
	bool	CheckPCItem(int iItemID, INT64 iValue1, INT64 iValue2);

	/**
	 * ���� �κ��丮�� �ش�������� �ѽ��ü��� �����´� <br>
	 @param int iItemID
	 @return int
	*/
	int		GetTotalPCItemCount(int iItemID);

	/**
	 * �ش� ID�� �������� ���� �ִ� ���� ������ �ִ��� Ȯ���Ѵ� <br>
	 @param int iItemID
	 @param int iStack = 1			�������� Ȯ���� ���ü�
	 @param int iCheckCount = 1		�������� Ȯ���� ���Լ�
	 @return bool
	*/
	bool	CheckEnableSlot(int iItemID, int iStack = 1, int iCheckCount = 1);

	/**
	 * 
	 @param 
	 @return
	*/
	bool	CheckRequireSlot(int iContainerType, int iRequireCount);
	
	/**
	 * �ش� ID�� ��ų�� üũ�Ѵ� <br>  
	 @param int iSkillID
	 @param INT64 iValue1
	 @param INT64 iValue2
	 @return bool
	*/
	bool	CheckPCSkill(int iSkillID, INT64 iValue1, INT64 iValue2);
	
	/**
	 * �ش� ID�� ����Ʈ�� üũ�Ѵ� <br>  
	 * ����Ʈ�� �ݺ� ������ üũ�Ѵ� <br>
	 @param int iQuestID
	 @param INT64 iValue1
	 @param INT64 iValue2
	 @return bool
	*/
	bool	CheckPCQuest(int iQuestID, INT64 iValue1, INT64 iValue2);

	/**
	 * �־��� ID�� ����Ʈ�� ���� ������ üũ�Ѵ� <br>
	 * Type�� 3�ΰ�� �������� ����Ʈ�� �����ϴ����� ��ȯ <br>
	 * Type�� 4�ΰ�� 3�ΰ���� �ݴ밪���� ��ȯ <br> �������̿��� ���� �ʴ°�� �ľ� <br>
	 @param int iType
	 @param int iQuestID
	 @return bool  
	*/
	bool	CheckDoingQuest(int iType, int iQuestID);

	/**
	 * �ش� ID�� Title�� üũ�Ѵ� <br> 
	 @param int iTitleID
	 @param INT64 iValue1	������
	 @param INT64 iValue2   ������
	 @return bool (�ִ°��  true)
	*/
	bool	CheckPCTitle(int iTitleID, INT64 iValue1, INT64 iValue2);

	/**
	* �ش� ID�� Effect�� üũ�Ѵ� <br> 
	@param int iTitleID
	@param INT64 iValue1	������
	@param INT64 iValue2   ������
	@return bool (�ִ°��  true)
	*/
	bool	CheckPCEffect(int iEffectID, INT64 iValue1, INT64 iValue2);

	/**
	* ��尡 �ش� Level���� üũ�Ѵ�. <br> 
	@param int iGuildLevel
	@param INT64 iValue1	������
	@param INT64 iValue2   ������
	@return bool (�ִ°��  true)
	*/
	bool CheckPCGuildLevel(int iGuildLevel, INT64 iValue1, INT64 iValue2) ;
	bool CheckPCGuildType(int iGuildType, INT64 iValue1, INT64 iValue2) ;

	/**
	 * �־��� �ε����� ���� �̺�Ʈ�� ����� CheckValue�� ���Ͽ� <br> 
	 * ����� �����ϸ� true �׷��� ������ false�� �����Ѵ� <br>
	 @param int iIndex			Ȯ���� ���� �̺�Ʈ �ε���
	 @param bool bCheckValue	���� ���� �̺�Ʈ ���� ���� 
	 @return  bool �������� (CheckValue�� ������ ��� true)
	*/
	//bool CheckPCCoreEvent(int iIndex, bool bCheckValue);
	
	/**
	* �־��� �ε����� ���� �̺�Ʈ�� ����� CheckValue�� ���Ͽ� <br> 
	* ����� �����ϸ� true �׷��� ������ false�� �����Ѵ� <br>
	@param int iID			üũ�� ���� �̺�Ʈ Ÿ�� 1�ΰ�� ����Ȱ� 2�ΰ�� ������� ����
	@param int iIndex		Ȯ���� ���� �̺�Ʈ �ε���
	@return  bool			
	*/
	bool CheckPCCoreEvent(int iID, int iIndex);

	/**
	* �ش� ����� �´� �����÷��� ���´� <br> 
	@param int iRareLevel
	@return D3DXCOLOR
	*/
	D3DXCOLOR GetItemColor(int iRareLevel);
	
	/**
	 * �־��� �������� ���� �÷��̾ ����Ҽ� �ִ����� Ȯ���Ѵ� <br> 
	 @param  int iItemID		üũ�� �������� ID
	 @param bool bPvp = false	PVP ��Ȳ�� üũ���� (true�ΰ�� Pvp ���� üũ)
	 @return bool				��� false�� ��� ����Ҽ� ���� 
	*/
	bool CheckItemStatus(int iItemID, bool bPvp = false);

	/**
	 * �־��� �������� �κ��丮�� �ѽ��Կ��� ������ �����ϴ��� Ȯ���Ѵ� <br>
	 @param int iItemID
	 @param int iCheckStack
	 @return bool ���� ������ true
	*/
	bool	CheckBiggerSlot(int iItemID, int iCheckStack);

	/**
	* �־��� �������� �κ��丮�� ������� 5���� ���Կ��� ������ �����ϴ��� Ȯ���Ѵ� <br>
	@param int iItemID
	@param int iCheckStack
	@return bool ���� ������ true
	*/
	bool	CheckBiggerSlot5(int iItemID, int iCheckStack);

	/**
	 * �־��� Ÿ�Կ� �ǰ� ���(����,�м�)�� ���� ��Ȳ�� Ȯ���Ѵ� <br>	
	 * SPPlayerInvenArchive::CheckEquipInven ���� <br> 
	 @param  int iCheckType			1, 3�� ��� ���� 2,4�ΰ�� �м�
	 @param  int iCheckSlotIndex = 0  ���԰��� ���ο��� 0���̽��� �����Ѵ� 17�� ��� ��� üũ
	 @return bool ���� ������ true  
	*/
	bool	CheckEquip(int iCheckType, int iCheckSlotIndex = 0);
	
	/**
	 * �־��� Ÿ�Կ� �ǰ� ����� ���� ��� ID���� Ȯ���Ѵ� <br>
	 @param  int iCheckType				1, 3�� ��� ���� 2,4�ΰ�� �м�
	 @param  int iCheckSlotIndex = 0	���԰��� ���ο��� 0���̽��� �����Ѵ� 
	 @param	 int iCheckMotionID = 0		Ȯ���� ��� ��
	 @return bool ���� ������ true   
	*/
	bool	CheckEquipMotion(int iCheckType, int iCheckSlotIndex = 0, int iCheckMotionID = 0);

	/**
	 * Notice Box�� ��� �뵵�� Ȯ�� <br>
	 @param  NONE
	 @return NOTICE_USE
	*/
	NOTICE_USE GetNoticeUse();

	/**
	* Notice Box�� ��� �뵵�� ���� <br>
	* ���� üũ�ϴ� �ɹ� ������ �κ��丮�� �ɹ��̴� <br>
	@param  NOTICE_USE iUse
	@return NOTICE_USE
	*/
	NOTICE_USE SetNoticeUse(NOTICE_USE iUse = (NOTICE_USE)0);

	/**
	 * ���� �÷��̾�� ����Ʈ�� �����ϴ� ��� ��� <br> 
	 @param int iEffectID
	 @return bool	 
	*/
	bool SetLocalEffect(int iEffectID);

	/**
	 * DB�� �����¸� �����Ѵ� <br> 
	 @param bool bBlock
	 @return NONE
	*/
	void SetDBBlock(bool bBlock);
	
	/**
	 * DB�� �� ���¸� Ȯ���Ѵ� <br>
	 @param NONE
	 @return bool	true�� ��� ������
	*/
	bool IsDBBlock();

	/**
	* ���� eEquipID�� �������� ���� ���θ� Ȯ���Ѵ� <br>
	@param EQUIP_ID eEquipID
	@param INT64 iValue
	@return bool	true�� ��� �ش� eEquipID�� �����ϰ� �ִ�.
	*/
	bool	CheckEquipItem( int eEquipID , INT64 iValue );

	/**
	* iSkillID�� ��ų�� ������ üũ�Ѵ� <br>  
	@param int iSkillID
	@return bool	true�� ��� ��ų�� ����
	*/
	bool	CheckSkillUpRequire( int iSkillID );

	/**
	* iSkillID�� ��ų �ߵ� ������ üũ�Ѵ� <br>  
	@param int iSkillID
	@param bool bDisplayCheck ( ȭ�� ǥ�ÿ����� ���� ��� �ǳʶڴ� )
	@return bool	true�� ��� ��ų �ߵ� ����
	*/
	bool	CheckSkillUseRequire( int iSkillID , bool bDisplayCheck = false );

	/**
	* iSkillID�� ��ų �ߵ� ������ üũ�Ѵ� <br>  
	@param int iSkillID
	@param CONTAINER_TYPE eContainerType
	@param int iSlotIndex
	@param bool bDisplayCheck ( ȭ�� ǥ�ÿ����� ���� ��� �ǳʶڴ� )
	@return bool	true�� ��� ��ų �ߵ� ����
	*/
	bool	CheckItemSkillUseRequire( int iSkillID , int iItemID , CONTAINER_TYPE eContainerType , int iSlotIndex , bool bDisplayCheck = false );
	
	bool	CheckPetSkillUseRequire( int iSkillID, int iItemID, CONTAINER_TYPE eContainerType, int iSlotIndex, bool bDisplayCheck = false );

	/**
	* iSkillID�� �׼� ��ų �ߵ� ������ üũ�Ѵ� <br>  
	@param int iSkillID
	@return bool	true�� ��� ��ų �ߵ� ����
	*/
	bool	CheckActionSkillUseRequire( int iSkillID );

	/**
	* iType�� iID�� ������ üũ�Ѵ�. <br>
	@param int iType ( 1 ���� , 2 ������ , 3 ��ų , 4 ����Ʈ ,8 ���)
	@param int iID ( Ÿ���� 1�ϰ�� ���� ���� , Ÿ�� 2�ϰ�� 1�̸� ���� üũ Ÿ�� 3�ϰ�� 1�̸� ��ų ���� üũ , 2�̸� ��ų ���� üũ , Ÿ�� 4�� ��� 1�̸� �ݺ�Ƚ�� ���� üũ 2�̸� �ݺ�Ƚ�� �ʰ� üũ, Ÿ�� 8 ��� ������üũ )
	@return bool	true�� ��� ������ �����Ѵ�.
	*/
	bool	CheckCondition( int iType , int iID , int iValue1 , int iValue2 );

	bool	CheckApplyEffectRequire(int iEffectID, SPGameObject* pkGameObject);

	void	SetPetShopOpen(bool bOpen);
	bool	IsPetShopOpen();

	/**
	 * ���� �÷��̾��� �÷����� ���� �ϰ� �ִ� �Ͽ� ���� �߿��� üũ ������ Ȯ���Ѵ� <br>
	 @param
	 @return
	*/
	PLAYER_STATE	CheckPlayerState();
	
	/**
	 * ����г�Ƽ ���� ������ ���̵� Ȯ�� <br>
	 @param
	 @return
	*/
	int		GetDeathItemID();
	
	/**
	 * ����г�Ƽ ���� �������� �����ϴ��� Ȯ�� <br>
	 @param
	 @return
	*/
	bool	CheckDeathItem();

	/**
	 * ���� ��ġ�� ������ ID <br>
	 @param
	 @return
	*/
	int		GetMicServerItemID();
	
	/**
	 * ä�� ��ġ�� ������ ID <br>
	 @param
	 @return
	*/
	int		GetMicChannelItemID();

	int		GetMailFee();
	int		GetMailStampItemID();


	/**
		��ǰ������ ��� ���� ���� üũ
	 */
	bool	CheckBidEnable(USERID iBidUser) ;				// �������� üũ
	bool	CheckBidEnable(const char* pSellerName);		// ���ι�ǰ üũ

	/**
		���ڿ� ���� �ڸ��� üũ
	 */
	int		CheckDigitSize(INT64 iNumber) ;

	/**
		ĳ���� �̸� ��
	*/
	bool	IsCharNameCompare( const char* pSrcCharName , const char* pDestCharName , bool bLocalName , bool bNoCase );

protected:
	//SPIMESSAGE_MAP_DECLARE()

	/**
	 * ������ �������� 16���������� ��ȯ�� ���� <br> 
	 @param int iStatValue
	 @return int
	*/
	int		GetClass(INT64 iStatValue);

protected:
	bool	m_bDBBlock;				/**< DB Working ���� ���� �� �÷��� <br> true �ΰ�� ���Ǿ� ���� <br> */
	bool	m_bPetShopOpen;			/**< Pet Shop �� ���� �ִ��� <br> */
};

extern SPCheckManager*	g_pCheckManager;