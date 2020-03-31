#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Moonlight_Resource/VIDEO/Digital-Sun-Layered_final.wmv");
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, false);

	MCIWndPlay(m_hVideo);

}

void CLogo::Update()
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) || CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
	}
}

void CLogo::LateUpdate()
{
}

void CLogo::Render(HDC hDC)
{
}

void CLogo::Release()
{
	MCIWndClose(m_hVideo);
}
