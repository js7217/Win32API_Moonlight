#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 0.f;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_pFrameKey = L"Tile";
	m_iDrawID = 0;
	m_iRed = 0;
	m_iGreen = 0;
	m_iBlue = 0;
}

int CMouse::Update()
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.fX = float(pt.x) - iScrollX;
	m_tInfo.fY = float(pt.y) - iScrollY;
	return 0;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	//	BitBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, TILECX, TILECY, hMemDC, m_iDrawID * TILECX, 0, SRCCOPY);

	GdiTransparentBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		m_tInfo.fCX * m_iDrawID, 0,
		m_tInfo.fCX, m_tInfo.fCY, RGB(m_iRed, m_iGreen, m_iBlue));
}

void CMouse::Release()
{
}

void CMouse::ChangeObject(TCHAR * pFrameKey, int iDrawID, float fCX, float fCY, int iRed, int iGreen, int iBlue)
{
	m_pFrameKey = pFrameKey;
	m_iDrawID = iDrawID;
	m_tInfo.fCX = fCX;
	m_tInfo.fCY = fCY;
	m_iRed = iRed;
	m_iGreen = iGreen;
	m_iBlue = iBlue;
}
