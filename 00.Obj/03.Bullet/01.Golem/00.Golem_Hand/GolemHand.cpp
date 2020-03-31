#include "stdafx.h"
#include "GolemHand.h"
#include "ObjMgr.h"

CGolemHand::CGolemHand()
{
}

CGolemHand::~CGolemHand()
{
	Release();
}

void CGolemHand::Initialize()
{
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 192.f;
	m_tInfo.fCollisionCX = 45.f;
	m_tInfo.fCollisionCY = 90.f;
	m_iAtt = 30.f;
	m_fSpeed = 30.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/BOSS_A_PUNCH.bmp", L"BOSS_A_PUNCH");
	m_pFrameKey = L"BOSS_A_PUNCH";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iFrameScene = 1;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_iCnt = 0;
	m_eCurState = CObj::ATTACK;
}

void CGolemHand::LateInitialize()
{
	m_fDistY = m_tInfo.fY;
}

int CGolemHand::Update()
{
	CObj::LateInitialize();
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_bIsDead)
		return OBJ_DEAD;
	m_iIndex = CObjMgr::Get_Instance()->Get_Player()->Get_Index();
	if (m_tFrame.iFrameScene == 0)			// 올라갈때
	{
		m_fSpeed = 30.f;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}
		if (m_tFrame.iFrameStart >= 5)
		{
			m_tInfo.fY -= m_fSpeed;
		}

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		}
	}
	else if (m_tFrame.iFrameScene == 1)			//내려올때
	{
		m_fSpeed = 30.f;
		if (m_fDistY + 300 <= m_tInfo.fY)
		{
			if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
			{
				++m_tFrame.iFrameStart;
				m_tFrame.dwFrameTime = GetTickCount();
			}

			if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameScene = 0;
				m_iCnt++;
			}
			m_fSpeed = 0.f;
		}
		m_tInfo.fY += m_fSpeed;
	}
	return 0;
}

void CGolemHand::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_fDistY - 1000 >= m_tInfo.fY)
	{
		m_bIsDead = true;
	}
}

void CGolemHand::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
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

void CGolemHand::Release()
{
}
