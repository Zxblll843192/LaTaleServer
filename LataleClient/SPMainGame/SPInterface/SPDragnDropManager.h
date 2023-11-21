// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-7-1    10:22 
//***************************************************************************

#pragma once

class SPTexture;
class SPWindow;
class SPUIUnit;

class SPDragnDropManager
{
private:
	SPDragnDropManager			();

	static	SPDragnDropManager*	m_pDragnDropManagerInstance;

public:
	virtual ~SPDragnDropManager	();

	static	SPDragnDropManager*	GetInstance(void);
	static	void				DelInstance(void);

	enum DRAGNDROP_STATUS_TYPE
	{
		DRAGNDROP_STATUS_ENABLE		=	0	,
		DRAGNDROP_STATUS_DISABLE			,
		DRAGNDROP_STATUS_ISDRAGGING			,
		DRAGNDROP_STATUS_MAX				,
	};

	//	�ʱ�ȭ
	void						Init				();

	//	�巡�� ����
	void						End					();

	//	�Ŵ��� ���� �������̽�
	BOOL						IsDragging			();
	BOOL						IsEnable			();

	//	�巡�׾� ����� ����ϱ� ���� ���� �������̽�
	BOOL						Set					( SPWindow* pWindow , SPUIUnit* pUIUnit );
	BOOL						Get					( SPWindow** ppWindow , SPUIUnit** ppUIUnit );

protected:

	//	�巡�׾� ����� ����ϱ� ���� ���� �������̽�
	BOOL						SetSPWindow			( SPWindow*		pWindow			);
	BOOL						SetUIUnit			( SPUIUnit*		pUIUnit			);

	//	�巡�׾� ����� ����ϱ� ���� �������� �������̽�
	SPWindow*					GetSPWindow			();
	SPUIUnit*					GetUIUnit			();


	//////////////////////////////////////////////////////////////////////////
	//
	//	������
	//

	DRAGNDROP_STATUS_TYPE		m_eStatus;				//		�Ŵ����� ���� ����

	SPWindow*					m_pWindow;				//		�巡�� �� ����� ��� �ϴ� ������
	SPUIUnit*					m_pUIUnit;				//		�巡�� �� ����Ǵ� Unit

};
