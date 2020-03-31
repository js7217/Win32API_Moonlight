#include "stdafx.h"
#include "Hole.h"
#include "ObjMgr.h"

CHole::CHole()
{
}


CHole::~CHole()
{
}

void CHole::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_tInfo.fCollisionCX = 40.f;
	m_tInfo.fCollisionCY = 40.f;
	m_pFrameKey = L"hole";
	m_eGroupID = GroupID::BACKGROUND;
}

int CHole::Update()
{
	CObj::UpdateCollisionRect();

	return OBJ_NOEVENT;
}

void CHole::LateUpdate()
{
}

void CHole::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_iDrawID, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, SRCCOPY);
}

void CHole::Release()
{
}
