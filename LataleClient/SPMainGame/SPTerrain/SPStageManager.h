
// Copyright (C) jinhee
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : jinhee 2005-1-13 ���� 2:56:36
//***************************************************************************


#pragma once


struct SPMapInfo;
class SPMapGroup;
class SPStage;

/**
* @class SPStageManager
* @brief �������� ����
* @author Jinhee
* @version 00.00.01
* @date 2005.1.13
* @bug ����
* @warning ���ҽ� ������ LocalPlayer�� Stage, MapGroup Index�� �����Ѵ�.
*/
class SPStageManager {
public:
	SPStageManager();
	~SPStageManager();

	/**
	* �������� ����Ʈ�� �ʱ�ȭ �Ѵ� <br> 
	@param NONE
	@return NONE
	*/
	void DeleteAllStage();

	/**
	 * ���� ���������� ������ ���´� <br>  
	 @param NONE
	 @return int �������� ����
	*/
	int	GetStageCount();

	/**
	 * ���� �������� �ε����� ���� <br>
	 @param int iStage = -1
	 @return int
	*/
	int SetCurStageIndex(int iStage = -1);
	
	/**
	 * ���� �׷� �ε����� ���� <br>
	 @param int iGroup = -1
	 @return int
	*/
	int SetCurGroupIndex(int iGroup = -1);
	
	/**
	 * ���� �� �ε����� ���� <br>
	 @param int iMap = 0
	 @param int iGroup = -1
	 @param int iStage = -1
	 @return int
	*/
	int SetCurMapIndex(int iMap = 0, int iGroup = -1, int iStage = -1);

	/**
	 * ���� ���������� �ε����� �����´� <br>
	 @param NONE
	 @return int
	*/
	int GetCurStageIndex();
	
	/**
	 * ���� ���������� �׷� �ε����� �����´� <br>
	 @param NONE
	 @return int
	*/
	int GetCurGroupIndex();
	
	/**
	 * ���� �������� �׷� �� �� �ε����� �����´� <br>
	 @param NONE
	 @return int
	*/
	int GetCurMapIndex();	

	/**
	 * ���� ���������� �����´� <br>
	 @param int iStage = -1		�ε����� ���������� �����ö�
	 @return SPStage*	���°�� NULL
	*/
	SPStage* GetCurStage(int iStage = -1);
	
	/**
	 * ���� ���������� �׷��� �����´� <br>
	 @param int iGroup = -1	�ε���
	 @param int iStage = -1 �ε���
	 @return SPMapGroup*	���°�� NULL
	*/
	SPMapGroup* GetMapGroup(int iGroup = -1, int iStage = -1);	

	/**
	 * ���� ������ �������� ������ �̸� ������ ����ϰ� �ִ´� <br>
	 @param int iStage
	 @param int iMapGroup
	 @return NULL
	*/
	void SetNextStage(int iStage, int iMapGroup) {
		m_iNextStage = iStage;
		m_iNextMapGroup = iMapGroup;
	}

	/**
	 * ���� ������ �������� ������ Ȯ���Ѵ�  <br>
	 @param NONE
	 @return int
	*/
	int GetNextStage() { return m_iNextStage; }
	
	/**
	 * ���� ������ �� �׷� ������ Ȯ���Ѵ� <br>
	 @param NONE
	 @return int
	*/
	int GetNextMapGroup() { return m_iNextMapGroup; }


protected:
	/**
	 * �������� ����Ʈ �� �޴����� �ɹ��� �ʱ�ȭ �Ѵ� <br> 
	 @param NONE
	 @return NONE
	*/
	void SetNull();
	
	

public:
	//int m_iStageCount;
	std::vector<SPStage*>	m_vpStageList;	

protected:	
	int m_iCurStage;				/**< ���� ������ ���������� �ε��� <br> */
	int m_iCurMap;					/**< �� ID�� ���������� ���������� �����Ƿ�... <br> */

	int m_iNextStage;				/**< ���� ������ �������� <br> */
	int m_iNextMapGroup;			/**< ���� ������ �ʱ׷� <br> */
};

extern SPStageManager g_StageManager;