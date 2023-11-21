
#pragma once

#include <windows.h>

#include <vector>

class CFixPool
{
private:
	typedef std::vector<BYTE *> VPoint;

	DWORD	m_dwEleSize;			// ÿ����Ԫ��С
	DWORD	m_dwBaseEles;			// ������Ԫ����
	BYTE*	m_pBaseAddr;			// �����ؿ�ʼλ��

	DWORD	m_dwCurEles;			// ��ǰ��Ԫ����
	DWORD	m_dwMaxEles;			// ���Ԫ����

	VPoint	m_vFreeBase;			// �������г�
	VPoint	m_vFreeExt;				// ��չ���г�

public:
	CFixPool(DWORD dwEleSize,DWORD dwBaseEles);
	~CFixPool(void);

	BYTE*	NewEle(void);
	void	DelEle(BYTE *pEle);
};