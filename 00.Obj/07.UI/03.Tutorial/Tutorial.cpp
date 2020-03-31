#include "stdafx.h"
#include "Tutorial.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"

CTutorial::CTutorial()
{
}


CTutorial::~CTutorial()
{
}

void CTutorial::Initialize()
{
	m_tInfo.fCX = 384.f;
	m_tInfo.fCY = 384.f;
	m_tInfo.fCollisionCX = 376.5f;
	m_tInfo.fCollisionCY = 75.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/Tutorial_Scroll_Move_WASD.bmp", L"Tutorial_Scroll_Move_WASD");
	m_pFrameKey = L"Tutorial_Scroll_Move_WASD";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 130;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eGroupID = GroupID::GAMEOBJECT;
	m_dwOldTime = GetTickCount();
}

int CTutorial::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	if (CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER).empty())
		return OBJ_NOEVENT;
	if (m_bInit)
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
	}
	return OBJ_NOEVENT;
}

void CTutorial::LateUpdate()
{
	UpdateRect();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_INTRO && !dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Intro())
		m_bInit = true;
}

void CTutorial::Render(HDC hDC)
{
	if (CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER).empty())
		return;
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 0, 255));
}

void CTutorial::Release()
{
}
