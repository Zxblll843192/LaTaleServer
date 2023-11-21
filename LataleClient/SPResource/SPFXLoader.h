// Copyright (C) AJJIYA
//***************************************************************************
// System Name : 
// Comment     : 
// Creation    : AJJIYA 2005-4-20    15:37 
//***************************************************************************

#pragma once

#include <string>

class SPFXGroupLoader;
class SPFXModelLoader;
class SPFXModel;

struct SPFXGroup;

class SPFXLoader
{
private:
	SPFXGroupLoader		m_FXGroupLoader;
	SPFXModelLoader		m_FXModelLoader;

public:
	SPFXLoader(void);
	virtual ~SPFXLoader(void);

	//	FX���õ� ������ �ε��Ѵ�.
	//	���ο��� new�ؼ� �����ֱ� ������ ����ϴ°����� delete�� �ʼ����̴�!!!
	SPFXGroup*	LoadGroupFile( std::string strFileName = "" );	//	FXG ������ �ε��ؼ� �����͸� �����ش�.
	SPFXModel*	LoadModelFile( std::string strFileName = "" );	//	FXM ������ �ε��ؼ� �����͸� �����ش�.

	//	FXModelLoader���� ĳ�������� ����� �����н��� �����´�.
	const char* GetFXMImgPath()	{	return m_FXModelLoader.GetImgPath();	}
	const char* GetFXMImgName()	{	return m_FXModelLoader.GetImgName();	}
};
