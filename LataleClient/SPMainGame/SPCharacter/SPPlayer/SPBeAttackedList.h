#pragma once 

//#define _USE_OLD_HP_BAR				255;

struct SPGOBModel;
class SPGameObject;
class SPGOBModelUnit;


enum TARGET_OBJECT_TYPE {
	TARGET_OBJECT_TYPE_MONSTER			= 0,				/**< ���� <br> */
	TARGET_OBJECT_TYPE_PLAYER			= 1,				/**< �÷��̾� <br> */
	TARGET_OBJECT_TYPE_BOSS				= 2,
	TARGET_OBJECT_TYPE_MAX				= 3,				/**< ??? <br> */
};


enum TARGET_OBJECT_SHOW_TYPE {
	TARGET_OBJECT_SHOW_TYPE_NORMAL		= 0,				/**< �Ϲ� ���� <br> */
	TARGET_OBJECT_SHOW_TYPE_DEAD		= 1,				/**< ��� ���� <br> */
	TARGET_OBJECT_SHOW_TYPE_MAX			= 2,
};


enum TARGET_LIST {
	TARGET_LIST_5,											/**< 6�� ��� <br> */
	TARGET_LIST_4,											/**< 5�� ��� <br> */
	TARGET_LIST_3,											/**< 4�� ��� <br> */
	TARGET_LIST_2,											/**< 3�� ��� <br> */
	TARGET_LIST_1,											/**< 2�� ��� <br> */
	TARGET_LIST_0,											/**< 1�� ��� <br> */
	TARGET_LIST_MAX,
};


const int MAX_VIEW_LIST			= 6;						/**< ����Ʈ �ִ� ���� <br> */
const int MOB_ICON_WIDTH		= 32;
const int MOB_ICON_HEIGHT		= 32;


struct SPBeAttackedObject {
	TARGET_OBJECT_TYPE			m_iObjectType;				/**< ǰ�� �ִ� ��ü Ÿ�� <br> */
	SPGameObject*				m_pGameObject;				/**< ��ũ�� ��ü <br> ���� NULLüũ ���Ұ� <br> */
	TARGET_OBJECT_SHOW_TYPE		m_iShowType;				/**< �������� ��Ȳ <br> */
	float						m_fDeleyTime;				/**< ���� �ܰ�� �Ѿ�� ���� ���ð� <br> */
	float						m_fAccmulateTime;			/**< �ð� ��� �� <br> */
	SPTexture*					m_pIconTexture;				/**< ������ �̹��� <br> */
	RECT						m_rtIcon;					/**< ������ �̹��� �ҽ� ���� <br> */
	int							m_iMaxHp;					/**< �ִ� HP <br> */
	int							m_iCurHp;					/**< ���� HP <br> */
	float						m_fHpRatio;					/**< HP % <br> */	
	RECT						m_rtGageLeft;				/**< Hp Gage���� <br> */
	RECT						m_rtGageRight;				/**< Hp Gage���� <br> */
	std::string					m_strName;					/**< ���� �̸� <br> */

	SPBeAttackedObject() {
		Clear();
	}

	~SPBeAttackedObject() {
		if(m_pIconTexture) {
			SAFE_RELEASE(m_pIconTexture);
		}
		Clear();
	}
	
	void Clear();	

	/**
	 * ǰ�� ��ü�� ���� <br>
	*/
	void SetObject(SPGameObject* pObject, TARGET_OBJECT_TYPE iType);

	/**
	 * �������� ��Ȳ�� ���� <br> 
	*/
	void SetShowType(TARGET_OBJECT_SHOW_TYPE iShowType);
	
	/**
	 * Hp ������� �����Ͽ� Ÿ�Ժ��� ������ ����� ��ȯ�Ѵ� <br>
	 @param 
	 @return  
	*/
	int SetHpRatio(int iMaxHp, int iCurHp);
	
	/**
	 * ������ ������� ��� ������ �̿��Ͽ� �������� ��� ������ �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void SetGageRect(int iHpWidth, RECT* p_rtMobGage);	
};


class SPBeAttackedList {
public:
	SPBeAttackedList();
	~SPBeAttackedList();

	void ClearAllList();

	void Process(float fTime);
	
	/**
	 * ���� �ܰ�� �Ѿ�� ���� üũ ���μ��� <br>
	 @param 
	 @return  
	*/
	void CheckObjectProcess(float fTime);

	/**
	 * �������� ó���� ���� ���� ����� �Ѵ� <br> 
	 @param 
	 @return  
	*/
	void RenderProcess(float fTime);

	/**
	 * ������
	 @param 
	 @return  
	*/
	void Render(float fTime);

	/**
	* ������ �������� ũ�⿡ ���� ��ġ �������� �Ѵ� <br> 
	@param 
	@return  
	*/
	void SetQuickSlotSize(int iSize);

	/**
	 * ��ü �߰� <br>
	 @param 
	 @return  
	*/
	bool AddObject(SPGameObject* pObject, TARGET_OBJECT_TYPE iType);	
	
	/**
	 * ������ �߰� <br>
	 @param 
	 @return  
	*/
	bool AddBossObject(SPGameObject* pObject, TARGET_OBJECT_TYPE iType = TARGET_OBJECT_TYPE_BOSS);
	
	
	/**
	 * ��ü ���� <br>
	 @param GU_ID iId
	 @return  
	*/
	bool DelObject(GU_ID iId);
	
	/**
	 * ��ü�� ���� ���� ���� <br> 
	 @param GU_ID iId
	 @return  
	*/
	bool SetDead(GU_ID iId);	

protected:			
	/**
	 * ��¿����� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void SetDestRect();
	
	/**
	 * ������ <br>
	 @param 
	 @return  
	*/
	void DebugListSize();	
	
	/**
	 * �־��� ���̵�� ��ü �˻� <br>
	 @param GU_ID iId
	 @return  
	*/
	SPBeAttackedObject* FindObject(GU_ID iId);	

private:
	SPBeAttackedObject*					m_pBossBeAttacked;						/**< ���� �ǰ� ���� <br> */
	std::vector<SPBeAttackedObject*>	m_vpBeAttackedList;						/**< ��, �÷��̾� �ǰ� ���� ����Ʈ <br> */

	int									m_iStartX;								/**< ������ ���� ���� X <br> */
	int									m_iStartY;								/**< ������ ���� ���� Y <br> */
	int									m_iQuickSlotSize;						/**< ���� �������� ũ�� <br> */

	RECT								m_rtBossIconDest;						/**< ���� ������ ��� ���� <br> */
	RECT								m_rtBossIconLineDest;					/**< ���� ������ �׵θ� ��� ���� <br> */
	RECT								m_rtBossNameDest;						/**< ���� �̸� ��� ���� <br> */
	RECT								m_rtBossGageDestLeft;					/**< ���� Hp Gage ���̽� ��� ���� <br> */
	RECT								m_rtBossGageDestCenter;					/**< ���� Hp Gage ���̽� ��� ���� <br> */
	RECT								m_rtBossGageDestRight;					/**< ���� Hp Gage ���̽� ��� ���� <br> */

	RECT								m_rtBossIconLineSrc;					/**< ���� �׵θ� �ҽ� ���� <br> */
	RECT								m_rtBossNameSrc;						/**< ���� �̸� �ҽ� ���� <br> */
	RECT								m_rtBossGageSrcLeft;					/**< ���� Hp ���̽� �ҽ� <br> */
	RECT								m_rtBossGageSrcCenter;					/**< ���� Hp ���̽� �ҽ� <br> */
	RECT								m_rtBossGageSrcRight;					/**< ���� Hp ���̽� �ҽ� <br> */
	RECT								m_rtBossHpSrcLeft;						/**< ���� Hp �ҽ� <br> */
	RECT								m_rtBossHpSrcRight;						/**< ���� Hp �ҽ� <br> */
	
	RECT								m_rtMobIconDest[TARGET_LIST_MAX];		/**< �Ϲ� �� Icon ��� <br> */
	RECT								m_rtMobGageDest[TARGET_LIST_MAX];		/**< �Ϲ� �� Gage ��� <br> */
	RECT								m_rtMobHpDest[TARGET_LIST_MAX];			/**< �Ϲ� �� HP ��� <br> */

	SPTexture*							m_pTexture;								/**< Hp�̹���, Gage�̹��� <br> */
	RECT								m_rtHpSrc;								/**< Hp�̹��� �ҽ� ���� <br> */
	RECT								m_rtGageBaseSrc;						/**< Hp������ ������ �ҽ� ���� <br> */
	RECT								m_rtGageSrc;							/**< �Ϲ� Hp������ �ҽ� ���� <br> */	

	RECT								m_rtDeadSrc;							/**< ����� �� Icon �ҽ� ���� <br> */
	RECT								m_rtMobSkinSrc;							/**< �Ϲݸ� Icon ���� <br> */
};
