#pragma once

#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#if defined(_DUMMY_CLIENT)
	#include "stdafx.h"
#endif

#if defined(_LATALE_TOOL)
	#include "stdafx.h"
#endif

#include "SPCoreDef.h"			// SPCore�� ���� ��� ����.
#include "LaTaleCommonDef.h"	// Launcher , Error ��ſ� ��Ģ
#include "LataleClient.h"		// �������� ����
#include "SPMainGameDef.h"		// ���ΰ��� ����
#include "findClass.h"
#include "IGWInterface.h"
#include "IGWLoaderDx9.h"



#define    ARGB(a,r,g,b)       (a<<24 | r<<16 | g<<8 | b)    //[xialin 2008/07/24]add
