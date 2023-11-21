#pragma once


/**
 * PvpLevel�� �⺻ ������ ���Ѵ� <br>
*/
struct SPPvpGloryLevelAttr {
	int					m_iID;						/**< ItemID <br> LevelIndex <br> */
	UINT64				m_iMinPoint;				/**< �������� ���� ����Ʈ <br> */
	UINT64				m_iMaxPoint;				/**< �������� �ְ� ����Ʈ <br> */
	std::string			m_strLevel;					/**< ����ǥ�� ���� <br> */
	int					m_iIconIndex;				/**< ����ǥ�� ������ �ε��� <br> */

	SPPvpGloryLevelAttr(){
		Clear();
	}

	~SPPvpGloryLevelAttr(){
		Clear();
	}

	void Clear() {
		m_iID					= 0;
		m_iMinPoint				= 0;
		m_iMaxPoint				= 0;
		m_strLevel.clear();
		m_iIconIndex			= 0;		
	}
};



/**
* @class SPPvpGloryLevelArchive
* @brief Pvp�� ���������� ����
* @author Jinhee
* @version 00.00.01
* @date 2007.11.27
* @bug ����
* @warning 
*/
class SPPvpGloryLevelArchive {
public:
	SPPvpGloryLevelArchive();
	~SPPvpGloryLevelArchive();

	/**
	* �־��� PvpPoint �� �ش��ϴ� ������ SPPvpGloryLevelAttr �� Ȯ���Ѵ� <br>
	@param 
	@return  
	*/
	SPPvpGloryLevelAttr* GetPvpGloryLevel(UINT64 iPvpPoint);

	/**
	* �־��� ������ SPPvpGloryLevelAttr�� Ȯ���Ѵ� <br>
	* ���� �ε����� 0���̽��̹Ƿ� 1�� ���� �����´� <br>
	@param 
	@return  
	*/
	SPPvpGloryLevelAttr* GetPvpGloryLevel(int iPvpLevel);

	/**
	 *
	 @param 
	 @return  
	*/
	std::string GetPvpGloryLevelString(int iPvpLevel);

private:
	/**
	 *
	 @param 
	 @return  
	*/
	bool LoadPvpGloryLevelAttr();
	
	/**
	 *
	 @param 
	 @return  
	*/
	void DeleteAllLevelInfo();	


private:
	std::vector<SPPvpGloryLevelAttr*>		m_vpPvpGloryLevelInfo;
};



