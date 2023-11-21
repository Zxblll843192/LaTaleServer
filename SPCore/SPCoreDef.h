
#pragma once

#define WIN32_LEAN_AND_MEAN					// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEFINE_DEPRECATED_HASH_CLASSES
#undef _DEFINE_DEPRECATED_HASH_CLASSES
#define _DEFINE_DEPRECATED_HASH_CLASSES 0	// .NET2003 ���� �ؽø� ��붧����.. 
#endif

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif


#define INPUT_CLOCK_ID	10001


#include <windows.h>
#include <MMSystem.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <assert.h>

#include <D3D9.h>
#include <dinput.h>

#include "DXUtil.h"
#include "CD3DEnumeration.h"
#include "D3DSettings.h"

#include "SPResourceBaseDEF.h"
#include "SPResourceBase.h"

#include "SPVideoCommon.h"
#include "SPVideo.h"
#include "SPLine.h"
#include "SPFont.h"
#include "SPTexture.h"
#include "SPTextureMgr.h"

#include "SPInputDef.h"
#include "SPInput.h"
#include "SPSoundBase.h"

#include "SPVector.h"
#include "SPBezier.h"






