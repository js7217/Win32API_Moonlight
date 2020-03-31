#include "stdafx.h"
#include "MainMenu_Logo.h"


CMainMenu_Logo::CMainMenu_Logo()
{
}


CMainMenu_Logo::~CMainMenu_Logo()
{
}

void CMainMenu_Logo::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 258.f;
	m_tInfo.fCY = 210.f;
	m_tInfo.fCollisionCX = 258.f;
	m_tInfo.fCollisionCY = 210.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/MAINMENU/GameLogo_0.bmp", L"GameLogo_0");
	m_pFrameKey = L"GameLogo_0";
	m_eGroupID = GroupID::UI;
}

int CMainMenu_Logo::Update()
{
	return 0;
}

void CMainMenu_Logo::LateUpdate()
{
}

void CMainMenu_Logo::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(0, 0, 0));
}

void CMainMenu_Logo::Release()
{
}
