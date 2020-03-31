#include "stdafx.h"
#include "DeadBody.h"


CDeadBody::CDeadBody()
{
}

CDeadBody::CDeadBody(float fX, float fY, float fCX, float fCY, TCHAR * pFrameKey)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = fCX * 1.5f;
	m_tInfo.fCY = fCY * 1.5f;
	m_pFrameKey = pFrameKey;
}


CDeadBody::~CDeadBody()
{
}

void CDeadBody::Initialize()
{
	m_tInfo.fCollisionCX = m_tInfo.fCX;
	m_tInfo.fCollisionCY = m_tInfo.fCY;
	m_dwOldTime = GetTickCount();
}

int CDeadBody::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	CObj::UpdateRect();

	return OBJ_NOEVENT;
}

void CDeadBody::LateUpdate()
{
	if (m_dwOldTime + 5000 < GetTickCount())
		m_bIsDead = true;
}

void CDeadBody::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 0, 255));
}

void CDeadBody::Release()
{
}
