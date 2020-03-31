#include "stdafx.h"
#include "BossScroll.h"


CBossScroll::CBossScroll()
{
}


CBossScroll::~CBossScroll()
{
}

void CBossScroll::Initialize()
{
	m_tInfo.fX = 430.f;
	m_tInfo.fY = 850.f;
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 120.f;
	m_fSpeed = 5.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/Dungeon1_Scroll.bmp", L"Dungeon1_Scroll");
	m_pFrameKey = L"Dungeon1_Scroll";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 50.f;
	m_tFrame.dwFrameTime = GetTickCount();

	m_dwOldTime = GetTickCount();
	m_bIsJump = false;
	m_eGroupID = GroupID::UI;
}

int CBossScroll::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	m_tInfo.fY -= m_fSpeed;
	if (m_tInfo.fY < 430.f)
	{
		if (m_dwOldTime + 1000 < GetTickCount())
		{
			m_bIsJump = false;
			if (m_dwOldTime + 2000 < GetTickCount())
			{
				m_fSpeed = -5.f;
				m_dwOldTime = GetTickCount();
			}
		}
		else
		{
			m_bIsJump = true;
			m_fSpeed = 0.f;
		}
	}
	else
		m_dwOldTime = GetTickCount();
	return OBJ_NOEVENT;
}

void CBossScroll::LateUpdate()
{
	if (m_bIsJump)
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
	}
	else
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			--m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart < 0)
			m_tFrame.iFrameStart = 0;
	}
}

void CBossScroll::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, (int)m_tInfo.fCY * m_tFrame.iFrameStart,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CBossScroll::Release()
{
}
