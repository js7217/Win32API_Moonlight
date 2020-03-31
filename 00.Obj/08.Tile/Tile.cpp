#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
	: m_iDrawID(0)
	, m_iOption(0)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = float(TILECX);
	m_tInfo.fCY = float(TILECY);
	m_tInfo.fCollisionCX = float(TILECX);
	m_tInfo.fCollisionCY = float(TILECY);
}

int CTile::Update()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();

	return 0;
}

void CTile::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
}

void CTile::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Tile");

//	BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, TILECX, TILECY, hMemDC, m_iDrawID * TILECX, 0, SRCCOPY);

	GdiTransparentBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		m_iDrawID * TILECX, 0,
		m_tInfo.fCX, m_tInfo.fCY, RGB(48, 255, 0));
}

void CTile::Release()
{
}
