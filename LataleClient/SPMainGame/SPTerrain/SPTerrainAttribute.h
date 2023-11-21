// Copyright (C) metalgeni
//***************************************************************************
// System Name : SPTerrainAttribute
// Comment     : Ŭ���̾�Ʈ, ����, �������� �������� ���.
//
// Creation    : metalgeni 2004-11-22 ���� 10:26:19
//***************************************************************************

#pragma once


extern BG_ID;

#define MAX_ATTR_LAYER 3

#define TILE_WIDTH	32
#define TILE_HEIGHT	16

#define ATTR_PIXEL_TO_OFFSET_X(fPixelX)		(fPixelX/TILE_WIDTH)
#define ATTR_PIXEL_TO_OFFSET_Y(fPixelY)		(fPixelY/TILE_HEIGHT)

#define ATTR_OFFSET_TO_PIXEL_X(iOffsetX)	(iOffsetX*TILE_WIDTH)
#define ATTR_OFFSET_TO_PIXEL_Y(iOffsetY)	(iOffsetY*TILE_HEIGHT)


/**
 * ��Ʈ����Ʈ üũ�� ����Ī ���� <br>
*/
enum POS_MOVE {
	POS_MOVE_NULL = 0,				/**< ����Ī ���� <br> */
	POS_MOVE_UP = 1,				/**< �Ѻ� ���� ����Ī <br> */
	POS_MOVE_DOWN = 10,				/**< �Ѻ� �Ʒ��� ����Ī <br> */
	POS_MOVE_LEFT = 20,				/**< �Ѻ� �������� ����Ī <br> */
	POS_MOVE_RIGHT = 30,			/**< �Ѻ� ���������� ����Ī <br> */
	POS_MOVE_CENTER = 40			/**< �� X�� �߾����� <br> */
};

////
//enum CLIMB {
//	CLIMB_NONE,
//	CLIMB_NONE_UP,
//	CLIMB_NONE_DOWN,
//	CLIMB_UP_DOWN
//};

class SPTerrainAttribute {

public:
	SPTerrainAttribute();
	virtual ~SPTerrainAttribute();

	bool Init();
	void Clean();		
	
	/**
	 * �־��� grid Size�� �ǰ� Attribute Layer���� �����Ѵ� <br>
	 @author Jinhee
	 @date 04.11.22 - jinhee
	 @param int Grid Width 
	 @param int Grid Height 
	 @return bool
	*/
	long Create(int iGridWidth, int iGridHeight);

	/**
	* Attribute �� Load�Ѵ� <br>
	* Maptool���� ��� <br>
	@author Jinhee
	@date 04.11.23 - jinhee
	@param string Path
	@param string File
	@param long GroupWidth		��ġ ����
	@param long GroupHeight		��ġ ����
	@return bool
	*/
	bool Load(std::string strPath = "", 
		std::string strFile = "",
		long lGroupWidth = 0, long lGroupHeight = 0);

	/**
	 * �ش� ��ǥ�� ��ġ�� Attribute Layer1���� Grid Attribute���� �����Ѵ� <br>
	 @author Jinhee
	 @date 04.11.22 - jinhee
	 @param BYTE Attribute ID
	 @param float X
	 @param float Y
	 @return 
	*/
	long SetAttr1(BYTE bAttr = 0, float fX = 0.0f, float fY = 0.0f);
	
	/**
	* �ش� ��ǥ�� ��ġ�� Attribute Layer2���� Grid Attribute���� �����Ѵ� <br>
	@author Jinhee
	@date 04.11.22 - jinhee
	@param BYTE Attribute ID
	@param float X
	@param float Y
	@return 
	*/
	long SetAttr2(BYTE bAttr = 0, float fX = 0.0f, float fY = 0.0f);

	/**
	* �ش� ��ǥ�� ��ġ�� Attribute Layer3���� Grid Attribute���� �����Ѵ� <br>
	@author Jinhee
	@date 04.11.22 - jinhee
	@param BYTE Attribute ID
	@param float X
	@param float Y
	@return 
	*/
	long SetAttr3(BYTE bAttr = 0, float fX = 0.0f, float fY = 0.0f);




	/**
	 * ���̾�1���� �ش� ��ǥ�� ��ġ�ϴ� ��Ʈ����Ʈ���� ���´� <br> 
	 @param int iLayer	�ش� ���� ���̾�(0Base)
	 @param float fX	�ش� �ʻ��� ���ϴ� X�� ��ǥ
	 @param float fY	�ش� �ʻ��� ���ϴ� Y�� ��ǥ
	 @return BYTE (0xFF�� ��� Fail)
	*/
	BYTE GetAttrLayer(int iLayer, float fX, float fY);

	/**
	 * OffSet�� �̿��Ͽ� �ش� ��ġ�� ��Ʈ����Ʈ���� ���´� <br>
	 @param int iLayer		�ش� ���� ���̾�(0Base)
	 @param int iOffSetX	�ش� �ʻ��� X�� OffSet
	 @param int iOffSetY	�ش� �ʻ��� Y�� OffSet
	 @return BYTE (0xFF�� ��� Fail)
	*/
	BYTE GetOffSetAttrLayer(int iLayer, int iOffSetX, int iOffSetY);
	
	
	/**
	 * map �� Widht�� �����´� <br>
	 @author Jinhee
	 @date 04.11.25 - jinhee
	 @param NONE
	 @return float
	*/
	int GetWidth() { return m_iLenX; }

	/**
	 * map�� Height�� �����´� <br>
	 @author Jinhee
	 @date 04.11.25 - jinhee
	 @param NONE
	 @return float
	*/
	int GetHeight() { return m_iLenY; }
	
	// Inspect attribute size mismatch.
	//bool InspectTerrain();


	// ��Ʈ����
	bool MoveDrop(float fX, float fY, BG_ID eLayer);
	char InspectStandLayer(int iX, int iY, BG_ID& eLayer, int& iRevision);

	void SetLength(float fLenX, float fLenY) 
	{
		m_iLenX = (int)fLenX;
		m_iLenY = (int)fLenY;
	}


	// �����´���

	// ������ ��ǥ�� �̿��Ͽ� ��Ʈ����Ʈ������ �˻��Ͽ� �����Ѵ�.
	// ���̾ 0���ϰ�� ��緹�̾� �˻��� �ϰ� �˻��� ���̾ �����Ѵ�
	// ���̾� �켱������ 1�� (��緹�̾ �� �����Ұ�� 1���� �����Ѵ�)
	bool GetAttrType(int iOffsetX, int iOffsetY, BYTE& cAttr, int& iLayer);	
	
	int GetPosCorrect(BYTE cAttr, int iX, int iY, bool& bReCalculate);

	bool EnableLadderUp(float fX, float fY);
	bool EnableLadderDown(float fX, float fY);
	bool EnableVerRopeUp(float fX, float fY);
	bool EnableVerRopeDown(float fX, float fY);
	bool EnableHozRopeUp(float fX, float fY);

	bool IsBlock(BYTE cAttr);
	bool IsVerRope(BYTE cAttr);
	bool IsLadder(BYTE cAttr);
	bool IsHozRope(BYTE cAttr);
	bool IsUpBlock(BYTE cAttr);
	bool IsGround(BYTE CAttr, int iX, int iY);

private:
	// "distance" is over through value. 
	//// return attrubute unit.
	//BYTE GetAttr1(float fx, float fy, float& fDistanceX, float& fDistanceY);
	//BYTE GetAttr2(float fx, float fy, float& fDistanceX, float& fDistanceY);
	//BYTE GetAttr3(float fx, float fy, float& fDistanceX, float& fDistanceY);	
	/**
	 * �ش� ��ǥ�� �´� Attribute���� ���´� <br> 
	 * ��ǥ ������ ���� �������� ���� Attribute���� ���������� �ִ� <br>
	 * �׷� ��� GetAttrLayer1 ~ GetAttrLayer3 �� �Լ��� �̿��Ͽ� �о�� �ִ� <br>
	 @param int iLayer				�ش� ���� ���̾�(0Base)
	 @param float& fx				�ش� �ʿ����� x�� Offset
	 @param float& fy				�ش� �ʿ����� y�� Offset
	 @return BYTE					���� ��ǥ���� Attribute��
	*/
	BYTE GetAttr(int iLayer, int iX, int iY);

	char CheckStandLayer(int iLayer, int iX, int iY,
		int& iRevision, bool& bReCalculate);
	
	/**
	 * �ش� ��Ʈ����Ʈ���� X�� ��ǥ�� �������� ���� ��ġ�ؾ� �� Y�� ��ǥ�� ����س���. <br>
	 * jinhee - [2005/1/27] 
	 @param BYTE bAttr				�˻��� Attribute��
	 @float fx						�ش� ��Ʈ����Ʈ ���� �������� ������ X�� OffSet
	 @float fy						�ش� ��Ʈ����Ʈ ���� �������� ������ Y�� OffSet
	 @param float fVelocityX		���� X�������� ���⼺
	 @param	float fVelocityY		���� Y�������� ���⼺
	 @return float					�����Ǿ����� �� Y���� �� (�� ���� ���ϸ� �ڵ������� ���ϴ� ���� �ȴ�)
	*/	

private:

	//float	m_fLenX;
	//float	m_fLenY;
	int m_iLenX;
	int m_iLenY;


	int m_iHalfTileX;
	int m_iHalfTileY;
	int m_iQuadTileX;
	int m_iQuadTileY;
	
	BYTE* m_pkAttribute[MAX_ATTR_LAYER];
};

//extern SPTerrainAttribute* g_pTerrainAttribute;


