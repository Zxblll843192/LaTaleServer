// ***************************************************************
//  SPTitleArchive   version:  1.0   ��  date: 03/30/2006
//  -------------------------------------------------------------
//  
//	AJJIYA
//
//  -------------------------------------------------------------
//  Copyright (C) 2006 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#pragma once

struct	SPTitleData
{
	UINT32		m_uiTitleID;
};

typedef	std::vector< SPTitleData >		STD_VECTOR_TITLE;

class SPTitleArchive
{
public:
	SPTitleArchive				(void);
	virtual ~SPTitleArchive		(void);

	void			Init				();
	void			Destroy				();

	void			AddTitleData		( SPTitleData&	stTitleData );
	SPTitleData*	GetTitleData		( int iNumber );

	void			DelAllTitleData		();

	int				GetCount			();
	
	/**
	 * �־��� ID�� Ÿ��Ʋ�� ������ ������ �ִ��� Ȯ���Ѵ� <br> 
	 @param int iTitleID
	 @return bool
	*/
	bool			FindTitle		(int iTitleID);

protected:

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	STD_VECTOR_TITLE			m_vTitleData;

};
