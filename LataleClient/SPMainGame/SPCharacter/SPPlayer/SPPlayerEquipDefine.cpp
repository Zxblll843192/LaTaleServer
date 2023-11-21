
#include <WTypes.h>	
#include "PacketID.h"

#ifdef _LATALE_CLIENT
	#include "SPGOBClusterDef.h"
#endif

#include "SPAvatarModelUnitDEF.h"
#include "SPPlayerEquipDefine.h"

//typedef struct _CHAR_EQUIPMENT
//{
//	INT16	iEquipID;			// enum EQUIP_ID		 0 = NULL, -1 = INVALID
//	INT16	iEquipClass;		// enum EQUIP_CLASS		 0 = NULL, -1 = INVALID
//	INT16	iiItemID;			// 0~999
//	INT8	iiItemColor;		// 0~99
//
//} CHAR_EQUIPMENT;

//�Ӹ�ī��		1302_001_01	1302_002_01	1302_003_01
//��ǥ��		1402_003_01	1402_001_01	1402_002_01
//�Ǻλ�		1501_001_01	1501_001_02	1501_001_03
//����			0514_002_01	0514_002_01	0514_002_01
//����			0302_101_01	0302_101_01	0302_101_01
/*
CHAR_EQUIPMENT	g_aaDefaultEquip[][MAX_DEFAULT_EQUIP] = {
	// ĳ���� A
	{
		{	EQ_HAIR,		EQCLASS_1302,	  1,	1	},
		{	EQ_EXPRESSION,	EQCLASS_1402,	  3,	1	},
		{	EQ_SKIN,		EQCLASS_1501,	  1,	1	},
		{	EQ_BLOUSE,		EQCLASS_0514,	  2,	1	},
		{	EQ_PANTS,		EQCLASS_0302,	101,	1	},
	},													 
	// ĳ���� B
	{													 
		{	EQ_HAIR,		EQCLASS_1302,	  2,	1	},
		{	EQ_EXPRESSION,	EQCLASS_1402,	  1,	1	},
		{	EQ_SKIN,		EQCLASS_1501,	  1,	2	},
		{	EQ_BLOUSE,		EQCLASS_0514,	  2,	1	},
		{	EQ_PANTS,		EQCLASS_0302,	101,	1	},
	},													 
	// ĳ���� C
	{													 
		{	EQ_HAIR,		EQCLASS_1302,	  3,	1	},
		{	EQ_EXPRESSION,	EQCLASS_1402,	  2,	1	},
		{	EQ_SKIN,		EQCLASS_1501,	  1,	3	},
		{	EQ_BLOUSE,		EQCLASS_0514,	  2,	1	},
		{	EQ_PANTS,		EQCLASS_0302,	101,	1	},
	},
};


//����(�ѹ���)	0210_010_01	0210_011_01	0513_011_01
//����			0304_010_01	0301_011_01	
//�尩			0103_010_01	0101_011_01	
//�Ź�			0702_010_01	0701_011_01	0701_002_01
//��Ÿŷ		0601_002_01						
//����						0401_002_01					
//����			0803_001_01	0803_002_01	0807_003_01				
//����			0904_002_01	0905_002_01	0905_003_01				
//�Ȱ�						1001_002_01					
//�����								1201_002_01				
//�Ͱ���		1101_002_01				1101_003_01	

CHAR_EQUIPMENT	g_aaInitEquip[][MAX_INIT_EQUIP] = {
	//ĳ���� A - 0
	{
		{	EQ_PANTS,		EQCLASS_0304,	10,	1		},
		{	EQ_BLOUSE,		EQCLASS_0210,	10,	1		},
		{	EQ_GLOVES,		EQCLASS_0103,	10,	1		},
		{	EQ_SHOES,		EQCLASS_0702,	10,	1		},
		{	EQ_STOCKINGS,	EQCLASS_0601,	2,	1		},
		{	EQ_CLOAK,		EQCLASS_NULL,   0,	0		},	 	
		{	EQ_WEAPON1,		EQCLASS_0803,	1,	1		},
		{	EQ_HAIR_DRESS,	EQCLASS_0904,	2,	1		},
		{	EQ_GOGGLE,		EQCLASS_NULL,	0,	0		},	 	
		{	EQ_MAKEUP,		EQCLASS_NULL,	0,	0		},	 	
		{	EQ_EARRING,		EQCLASS_1101,	2,	1		},
		//{	EQ_ONE_PIECE,	EQCLASS_NULL,	10,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
	},
	//ĳ���� B - 1
	{
		{	EQ_PANTS,		EQCLASS_0301,	11,	1		},	
		{	EQ_BLOUSE,		EQCLASS_0210,	11,	1		},
		{	EQ_GLOVES,		EQCLASS_0101,	11,	1		},	
		{	EQ_SHOES,		EQCLASS_0701,	11,	1		},	
		{	EQ_STOCKINGS,	EQCLASS_NULL,	0,	0		},	 	
		{	EQ_CLOAK,		EQCLASS_0401,	2,	1		},	
		{	EQ_WEAPON1,		EQCLASS_0803,	2,	1		},	
		{	EQ_HAIR_DRESS,	EQCLASS_0905,	2,	1		},	
		{	EQ_GOGGLE,		EQCLASS_1001,	2,	1		},	
		{	EQ_MAKEUP,		EQCLASS_NULL,	0,	0		},	 	
		{	EQ_EARRING,		EQCLASS_NULL,	0,	0		},
		//{	EQ_ONE_PIECE,	EQCLASS_NULL,	10,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
	},
	//ĳ���� C - 2
	{
		{	EQ_PANTS,		EQCLASS_NULL,	0,	0		},
		{	EQ_ONE_PIECE,	EQCLASS_0513,	11,	1		},
		{	EQ_GLOVES,		EQCLASS_NULL,	0,	0		},	 	
		{	EQ_SHOES,		EQCLASS_0701,	2,	1		},	
		{	EQ_STOCKINGS,	EQCLASS_NULL,	0,	0		},	 	
		{	EQ_CLOAK,		EQCLASS_NULL,	0,	0		},	 	
		{	EQ_WEAPON1,		EQCLASS_0807,	3,	1		},	
		{	EQ_HAIR_DRESS,	EQCLASS_0905,	3,	1		},	
		{	EQ_GOGGLE,		EQCLASS_NULL,	0,	0		},	 	
		{	EQ_MAKEUP,		EQCLASS_1201,	2,	1		},
		{	EQ_EARRING,		EQCLASS_1101,	3,	1		},
		//{	EQ_ONE_PIECE,	EQCLASS_0513,	11,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
		{	EQ_NULL,		EQCLASS_NULL,	2,	1		},
	},

};


//�ʰ���������							
//����(�ѹ���)	0514_002_01	0210_010_01	0210_011_01	0513_011_01	����		
//����			0302_101_01	0304_102_01	0304_010_01	0301_011_01	����		
//�尩			0103_010_01	0101_011_01	����				
//�Ź�			0702_010_01	0701_011_01	0701_002_01	����			
//��Ÿŷ		0601_002_01	����					
//����			0401_002_01	����					
//����			0901_002_01	0902_010_01	0906_002_01	0904_002_01	0905_002_01	0905_003_01	����
//�Ȱ�			1001_003_01	1001_002_01	����				
//�����		1201_002_01	����					
//�Ͱ���		1101_002_01	1101_003_01	����				
//

CHAR_EQUIPMENT	g_aEquipBlouse[] = {
	{	EQ_ONE_PIECE,	EQCLASS_0514,	2,	1	},	
	{	EQ_BLOUSE,		EQCLASS_0210,	10,	1	},		
	{	EQ_BLOUSE,		EQCLASS_0210,	11,	1	},	
	{	EQ_ONE_PIECE,	EQCLASS_0513,	11,	1	},	
	{	EQ_BLOUSE,		EQCLASS_NULL,	11,	1	},	
};

CHAR_EQUIPMENT	g_aEquipPants[] = {
	{	EQ_PANTS,		EQCLASS_0302,	101,	1	},	
	{	EQ_PANTS,		EQCLASS_0304,	102,	1	},	
	{	EQ_PANTS,		EQCLASS_0304,	10,		1	},	
	{	EQ_PANTS,		EQCLASS_0301,	11,		1	},	
	{	EQ_PANTS,		EQCLASS_NULL,	11,		1	},
};

CHAR_EQUIPMENT	g_aEquipGloves[] = {
	{	EQ_GLOVES,		EQCLASS_0103,	10,	1	},
	{	EQ_GLOVES,		EQCLASS_0101,	11,	1	},
	{	EQ_GLOVES,		EQCLASS_NULL,	11,	1	},
};

CHAR_EQUIPMENT	g_aEquipShoes[] = {
	{	EQ_SHOES,		EQCLASS_0702,	10,	1	},
	{	EQ_SHOES,		EQCLASS_0701,	11,	1	},
	{	EQ_SHOES,		EQCLASS_0701,	02,	1	},
	{	EQ_SHOES,		EQCLASS_NULL,	11,	1	},
};

CHAR_EQUIPMENT	g_aEquipStoking[] = {
	{	EQ_STOCKINGS,	EQCLASS_0601,	2,	1	},
	{	EQ_STOCKINGS,	EQCLASS_NULL,	2,	1	},
};

CHAR_EQUIPMENT	g_aEquipCloak[] = {
	{	EQ_CLOAK,		EQCLASS_0401,	2,	1	},
	{	EQ_CLOAK,		EQCLASS_NULL,	2,	1	},
};

CHAR_EQUIPMENT	g_aEquipHairDress[] = {
	{	EQ_HAIR_DRESS,	EQCLASS_0901,	2,	1	},		
	{	EQ_HAIR_DRESS,	EQCLASS_0902,	10,	1	},		
	{	EQ_HAIR_DRESS,	EQCLASS_0906,	2,	1	},		
	{	EQ_HAIR_DRESS,	EQCLASS_0904,	2,	1	},		
	{	EQ_HAIR_DRESS,	EQCLASS_0905,	2,	1	},		
	{	EQ_HAIR_DRESS,	EQCLASS_0905,	3,	1	},	
	{	EQ_HAIR_DRESS,	EQCLASS_NULL,	3,	1	},	
};
											 	
CHAR_EQUIPMENT	g_aEquipGoggle[] = {
	{	EQ_GOGGLE,		EQCLASS_1001,	3,	1	},	
	{	EQ_GOGGLE,		EQCLASS_1001,	2,	1	},	
	{	EQ_GOGGLE,		EQCLASS_NULL,	2,	1	},	
};											 	
											 	
CHAR_EQUIPMENT	g_aEquipMakeup[] = {
	{	EQ_MAKEUP,		EQCLASS_1201,	2,	1	},	
	{	EQ_MAKEUP,		EQCLASS_NULL,	2,	1	},	
};											 	
											 	
CHAR_EQUIPMENT	g_aEquipEarring[] = {		 	
	{	EQ_EARRING,		EQCLASS_1101,	2,	1	},	
	{	EQ_EARRING,		EQCLASS_1101,	3,	1	},	
	{	EQ_EARRING,		EQCLASS_NULL,	3,	1	},	
};											 



*/













