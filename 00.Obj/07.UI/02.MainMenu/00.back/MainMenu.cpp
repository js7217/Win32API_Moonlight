#include "stdafx.h"
#include "MainMenu.h"

#include "MenuScene.h"
#include "SceneMgr.h"
CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
}

void CMainMenu::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 640.f;
	m_tInfo.fCY = 540.f;
	m_tInfo.fCollisionCX = 640.f;
	m_tInfo.fCollisionCY = 540.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/MAINMENU/MAIN_MENU_BACK.bmp", L"MAIN_MENU_BACK");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/MAINMENU/Menu_Select.bmp", L"Menu_Select");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/MAINMENU/Menu_connect.bmp", L"Menu_connect");
//	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/MAINMENU/GameLogo_0.bmp", L"GameLogo_0");Menu_Select
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CMainMenu::Update()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
		++m_iDrawID;
	if (CKeyMgr::Get_Instance()->KeyDown(VK_UP))
		--m_iDrawID;
	if (m_iDrawID < 0)
		m_iDrawID = 2;
	if (m_iDrawID > 2)
		m_iDrawID = 0;
	dynamic_cast<CMenuScene*>(CSceneMgr::Get_Instance()->Get_Scene())->Set_NextScene(m_iDrawID);
	return 0;
}

void CMainMenu::LateUpdate()
{
	CObj::UpdateRect();
	CObj::FrameMove(0);
}

void CMainMenu::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
//	HDC hLogoMemDC = CBitmapMgr::Get_Instance()->FindImage(L"GameLogo_0");
	HDC hBackMemDC = CBitmapMgr::Get_Instance()->FindImage(L"MAIN_MENU_BACK");
	HDC hBackDC = CBitmapMgr::Get_Instance()->FindImage(L"Menu_Select");
	HDC hSelectDC = CBitmapMgr::Get_Instance()->FindImage(L"Menu_connect");
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hBackMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY / 1.5f, SRCCOPY);

	GdiTransparentBlt(hDC,
		325, 350,
		160, 141,
		hBackDC,
		0, 0,
		160, 141, RGB(255, 255, 255));

	GdiTransparentBlt(hDC,
		315, 365 + m_iDrawID * 43,
		180, 18,
		hSelectDC,
		0, 0,
		135, 18, RGB(255, 0, 255));
}

void CMainMenu::Release()
{
}
