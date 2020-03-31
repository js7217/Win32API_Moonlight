#include "stdafx.h"
#include "LeftWall.h"


CLeftWall::CLeftWall()
{
}


CLeftWall::~CLeftWall()
{
}

void CLeftWall::Initialize()
{
	m_tInfo.fX = -200.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 640.f;
	m_tInfo.fCY = 540.f;
	m_tInfo.fCollisionCX = 640.f;
	m_tInfo.fCollisionCY = 540.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/MAINMENU/GameLogo_1.bmp", L"GameLogo_1");
	m_pFrameKey = L"GameLogo_1";
	m_eGroupID = GroupID::UI;
}

int CLeftWall::Update()
{
	return 0;
}

void CLeftWall::LateUpdate()
{
}

void CLeftWall::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		320, 362, SRCCOPY);
}

void CLeftWall::Release()
{
}
