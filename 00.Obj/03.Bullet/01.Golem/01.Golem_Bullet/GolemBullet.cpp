#include "stdafx.h"
#include "GolemBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CGolemBullet::CGolemBullet()
{
}


CGolemBullet::~CGolemBullet()
{
}

void CGolemBullet::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/ROCK/BOSS_A_ROCK.bmp", L"BOSS_A_ROCK");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/GAME_EFFECT/ROCK/ROCK_DEAD.bmp", L"ROCK_DEAD");
	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 96.f;
	m_tInfo.fCollisionCX = 50.f;
	m_tInfo.fCollisionCY = 50.f;
	m_fSpeed = 30.f;
	m_iMaxHp = 50;
	m_iHp = m_iMaxHp;
	m_pFrameKey = L"BOSS_A_ROCK";
	m_tFrame.iFrameStart = RandomNumber(0, 4);
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwOldTime = GetTickCount();
}

void CGolemBullet::LateInitialize()
{
	m_fDist = m_tInfo.fY;
}

int CGolemBullet::Update()
{
	CObj::LateInitialize();
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_bIsDead)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::
			Create(m_tInfo.fX, m_tInfo.fY, 96.f, 96.f, L"ROCK_DEAD", 9));
		return OBJ_DEAD;
	}
	if (m_bIsCollisionExtra == false)
	{
		if (m_fDist + 300 <= m_tInfo.fY)
		{
			m_fSpeed = 0.f;
			m_bIsCollisionExtra = true;
		}
	}
	m_tInfo.fY += m_fSpeed;
	return OBJ_NOEVENT;
}

void CGolemBullet::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_eCurState == DEAD)
		m_bIsDead = true;
	if (m_dwOldTime + 10000 < GetTickCount())
	{
		m_bIsDead = true;
	}
}

void CGolemBullet::Render(HDC hDC)
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

void CGolemBullet::Release()
{
}
