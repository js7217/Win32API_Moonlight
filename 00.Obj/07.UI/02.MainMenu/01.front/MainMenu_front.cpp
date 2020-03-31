#include "stdafx.h"
#include "MainMenu_front.h"


CMainMenu_front::CMainMenu_front()
{
}


CMainMenu_front::~CMainMenu_front()
{
}

void CMainMenu_front::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 640.f;
	m_tInfo.fCY = 540.f;
	m_tInfo.fCollisionCX = 640.f;
	m_tInfo.fCollisionCY = 540.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/MAINMENU/MAIN_MENU_FRONT.bmp", L"MAIN_MENU_FRONT");
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eGroupID = GroupID::UI;
}

int CMainMenu_front::Update()
{
	return 0;
}

void CMainMenu_front::LateUpdate()
{
	CObj::UpdateRect();
	CObj::FrameMove(0);
}

void CMainMenu_front::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	HDC hFrontMemDC = CBitmapMgr::Get_Instance()->FindImage(L"MAIN_MENU_FRONT");
	
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hFrontMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY / 1.5f, RGB(255, 255, 255));
}

void CMainMenu_front::Release()
{
}
