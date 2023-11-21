// ***************************************************************
//  MiniDumper.h   version:  1.0   date:2006/01/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2006 AJJIYA - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#pragma once

//////////////////////////////////////////////////////////////////////////////
/// \class MiniDumper
/// \brief �̴� ������ �����ϱ� ���� Ŭ����. 
///
/// Ư���� �ϴ� ���� ����, ���� ������ �Լ��� ������ �ִ� ���� �����̽� ���� 
/// ���� �ۿ��� �ϴ� ���� ����. ������ �̴� ������ �̷������ ���� 
/// TopLevelFilter �Լ���.
//////////////////////////////////////////////////////////////////////////////

class MiniDumper
{
public:
	/// \brief ������ �������� ����
	enum DumpLevel
	{
		DUMP_LEVEL_0, ///< MiniDumpNormal�� ���
		DUMP_LEVEL_1, ///< MiniDumpWithDataSegs�� ���
		DUMP_LEVEL_2, ///< MiniDumpWithIndirectlyReferencedMemory�� ���
		DUMP_LEVEL_3, ///< MiniDumpWithFullMemory�� ���
	};


private:
	/// ���� ����.
	static DumpLevel s_DumpLevel;            

	/// ���� ���� �̸����ٰ� ���� ������ ������ ��¥�� ����ִ°��� ����.
	static bool s_bAddTimeStamp;

	/// ���� ���� �̸� ���ڿ�.
	static TCHAR s_szAppName[_MAX_PATH];

	/// ������ �߻��� ����
	static TCHAR s_szFaultReason[2048];


public:
	/// \brief ������
	MiniDumper(DumpLevel DL, bool bAddTimestamp=true);

	/// \brief �Ҹ���
	~MiniDumper();


private:
	/// \brief ���ܿ� ���� ������ �޾Ƽ�, �̴� ���� ������ �����Ѵ�. 
	static LONG WINAPI TopLevelFilter(struct _EXCEPTION_POINTERS* pExPtrs);

	/// \brief ������ ���ο� ���� ���ڿ��� ��ȯ�Ѵ�.
	static LPCTSTR GetFaultReason(struct _EXCEPTION_POINTERS* pExPtrs);
};
