#include "stdafx.h"
#include "ScrollMgr.h"

float CScrollMgr::m_fScrollX = 0.f;
float CScrollMgr::m_fScrollY = 0.f;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::ScrollLock(int fCX, int fCY)
{
	// ����. 
	if (m_fScrollX > 0.f)
		m_fScrollX = 0.f;
	if (m_fScrollY > 0.f)
		m_fScrollY = 0.f;
	// ��������� ����Ʈ ž. 
	if (WINCX - fCX > m_fScrollX)
		m_fScrollX = WINCX - fCX;
	if (WINCY - fCY > m_fScrollY)
		m_fScrollY = WINCY - fCY;
	//LOCK �غ�����.
}
