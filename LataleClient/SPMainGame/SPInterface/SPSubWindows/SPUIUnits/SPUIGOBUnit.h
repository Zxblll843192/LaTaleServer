// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-9-29    11:31 
//***************************************************************************

#pragma once

class SPUIUnit;

class SPUIGOBUnit : public SPUIUnit
{
public:
	SPUIGOBUnit									(void);
	virtual ~SPUIGOBUnit						(void);

	//	�⺻ �������̽�
	virtual	void			Init				();
	virtual	void			Clear				();
	virtual	void			Process				( float fTime );
	virtual	void			Render				();
	virtual	BOOL			Use					();

	//	Class ���̵� �������̽�
	void					SetClassID			( CLASS_ID eClassID );
	CLASS_ID				GetClassID			();

	//	�ڱ� �ڽ� ���� �������̽�
	virtual SPUIUnit*		ClonePtr			();
	virtual BOOL			Copy				( SPUIUnit** ppDestUIUnit );

	//	���̵�� ���ҽ� �� �ε�
	virtual	BOOL			ReResourceLoad		();

	//	GOB �̸� �������̽�
	void					SetName				( const char* pstrName );
	const char*				GetName				();

protected:

	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	CLASS_ID				m_eClassID;
	std::string				m_strName;

};
