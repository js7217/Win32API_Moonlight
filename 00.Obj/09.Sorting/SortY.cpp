#include "stdafx.h"
#include "SortY.h"


CSortY::CSortY()
{
}

CSortY::CSortY(float fX, float fY, float fCX, float fCY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = fCX;
	m_tInfo.fCY = fCY;
	m_tInfo.fCollisionCX = fCX;
	m_tInfo.fCollisionCY = fCY;
}


CSortY::~CSortY()
{
	Release();
}

void CSortY::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Sort.bmp", L"Sort");
	m_eGroupID = GroupID::UI;
}

int CSortY::Update()
{
	return 0;
}

void CSortY::LateUpdate()
{
}

void CSortY::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Sort");

//	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		0, 0,
		m_tInfo.fCX / 1.5f , m_tInfo.fCY / 1.5f, SRCCOPY);
}

void CSortY::Release()
{
}
