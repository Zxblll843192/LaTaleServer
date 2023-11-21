#pragma once


/**
 * Ŭ���� ü���� �� �߰��� Ŭ���̾�Ʈ���� üũ���־�� �� ������ ��� <br> 
*/
struct SPClassChangeReqAttr {
	int				m_iID;						/**< Item Index <br> */
	int				m_iItemID;					/**< �ʿ� ������ ID <br> */
	UINT64			m_iEly;						/**< �ʿ� Ely <br> */

	SPClassChangeReqAttr() {
		Clear();
	}

	~SPClassChangeReqAttr() {
		Clear();
	}

	void Clear() {
		m_iID				= 0;
		m_iItemID			= 0;
		m_iEly				= 0;
	}
};


/**
 * Ŭ���� ������ �߰� ǥ���� ȿ���� ���� ������ ��� <br>
*/
struct SPClassChangeEffectAttr {
	int				m_iID;
	int				m_iFx1;
	int				m_iFx2;
	int				m_iSoundEffect;
	std::string		m_strMsg;
	UINT8			m_iRed;
	UINT8			m_iGreen;
	UINT8			m_iBlue;
	//std::string		m_strMotion;

	SPClassChangeEffectAttr() {
		Clear();
	}

	~SPClassChangeEffectAttr() {
		Clear();
	}

	void Clear(){
		m_iID					= 0;
		m_iFx1					= 0;
		m_iFx2					= 0;
		m_iSoundEffect			= 0;
		m_strMsg.clear();
		m_iRed					= 0;
		m_iGreen				= 0;
		m_iBlue					= 0;
		//m_strMotion.clear();
	}
};


/**
 * Level up �� ȿ�� Effect ������ ���� <br>
*/
struct SPLevelUpEffectAttr {
	int 			m_iID;	
	int 			m_iLevel;
	int 			m_iClass;
	int 			m_iFx;
	int				m_iSoundEffect;
	std::string		m_strMsg;
	UINT8			m_iRed;
	UINT8			m_iGreen;
	UINT8			m_iBlue;
	int				m_iGuideBook;

	SPLevelUpEffectAttr() {
		void Clear();
	}

	~SPLevelUpEffectAttr() {
		void Clear();
	}

	void Clear() {
		m_iID				= 0;		
		m_iLevel			= 0;
		m_iClass			= CLASS_NULL;
		m_iFx				= 0;
		m_iSoundEffect		= 0;
		m_strMsg.clear();
		m_iRed				= 0;
		m_iGreen			= 0;
		m_iBlue				= 0;
		m_iGuideBook		= 0;
	}

	int SetID(int iLevel, int iClass) {
		m_iClass = iClass;
		m_iLevel = iLevel;
		m_iID = iClass * 1000 + iLevel;
		
		return m_iID;
	}	
};


/**
* @class SPClassChangeManager
* @brief Ŭ���� ����, �������� ȿ���� ���� ������ �����Ѵ� 
* @author Jinhee
* @version 00.00.01
* @date 2007.11.12
* @bug ����
* @warning 
*/
class SPClassChangeManager {
public:
	SPClassChangeManager();
	~SPClassChangeManager();	

	/**
	 * Ŭ���� ������ ��û�ϴ� ��Ŷ�� ���� <br> 
	 @param int iClassChangeID �����Ϸ��� Ŭ������ ID 
	 @return  bool
	*/
	bool SendClassChangeInfo(int iClassChangeID);

	/**
	 *
	 @param 
	 @return  
	*/
	bool OnClassChangeEffect(int iNewClassChangeType);
	
	/**
	 * �־��� �������� �߰��� üũ�� ������ �����´� <br>
	 @param int iItemID
	 @return  SPClassChangeReqAttr*
	*/
	SPClassChangeReqAttr*		GetClassChangeReqAttr(int iItemID);
	
	/**
	 * �־��� �������� Ŭ���� ���� ȿ�� ������ �����´� <br>
	 @param 
	 @return  
	*/
	SPClassChangeEffectAttr*	GetClassChangeEffectAttr(int iItemID);

	SPLevelUpEffectAttr*		GetLevelUpEffectAttr(int iItemID);
	SPLevelUpEffectAttr*		GetLevelUpEffectAttr(int iLevel, int iClass);

private:
	/**
	 * ��� ���� ���⸦ �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void DeleteAllClassChangeAttr();
	
	/**
	 * ���� ���⸦ �ε��Ѵ� <br>
	 @param 
	 @return  
	*/
	bool LoadClassChangeAttr();
	
	/**
	 * ���� ���⸦ ������Ǯ�� �ִ´� <br>
	 @param 
	 @return  
	*/
	bool InsertClassChangeAttr(SPClassChangeReqAttr* pClassChangeReqAttr);
	
	/**
	 * ��� Ŭ���� ���� ȿ���� �����Ѵ� <br>
	 @param 
	 @return  
	*/
	void DeleteAllClassChangeEffectAttr();
	
	/**
	 * Ŭ���� ���� ȿ���� �ε��Ѵ� <br>
	 @param 
	 @return  
	*/
	bool LoadClassChangeEffectAttr();
	
	/**
	 * Ŭ���� ���� ȿ���� ������Ǯ�� �ִ´� <br>
	 @param 
	 @return  
	*/
	bool InsertClassChangeEffectAttr(SPClassChangeEffectAttr* pClassChangeEffectAttr);

	/**
	 *
	 @param 
	 @return  
	*/
	int GetLevelUpEffectID(int iLevel, int iClass);
	
	/**
	 *
	 @param 
	 @return  
	*/
	void DeleteAllLevelUpEffectAttr();
	
	/**
	 *
	 @param 
	 @return  
	*/
	bool LoadLevelUpEffectAttr();
	
	/**
	 *
	 @param 
	 @return  
	*/
	bool InsertLevelUpEffectAttr(SPLevelUpEffectAttr* pLevelUpEffectAttr);

private:
	std::map<unsigned int, SPClassChangeReqAttr*>		m_mClassChangeReqInfo;		/**< Ŭ��������� �߰� �ʿ� ���� ����Ʈ <br> */
	std::map<unsigned int, SPClassChangeEffectAttr*>	m_mClassChangeEffectInfo;	/**< Ŭ���� ����� Ŭ���̾�Ʈ���� ������ ȿ�� <br> */
	std::map<unsigned int, SPLevelUpEffectAttr*>		m_mLevelUpEffectInfo;		/**< <br> */
};






