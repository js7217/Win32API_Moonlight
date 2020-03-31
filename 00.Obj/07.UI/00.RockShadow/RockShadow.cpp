#include "stdafx.h"
#include "RockShadow.h"
#include "GolemBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
int CRockShadow::m_iCnt = 0;
CRockShadow::CRockShadow()
{
}


CRockShadow::~CRockShadow()
{
	Release();
}

void CRockShadow::Initialize()
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	m_tInfo.fCollisionCX = 64.f;
	m_tInfo.fCollisionCY = 64.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/ROCK_SHADOW/BOSS_A_ROCK_SHADOW.bmp", L"BOSS_A_ROCK_SHADOW");
	m_pFrameKey = L"BOSS_A_ROCK_SHADOW";
	m_dwOldTime = GetTickCount();
	m_bIsRock = false;
	m_iCnt++;
	m_eGroupID = GroupID::SHADOW;
}

int CRockShadow::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CRockShadow::LateUpdate()
{
	if (m_dwOldTime + 1000 < GetTickCount())
	{
		if (m_bIsRock == false)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::BOSS_BULLET, CAbstractFactory<CGolemBullet>::Create(m_tInfo.fX, m_tInfo.fY - 300.f));
			m_bIsRock = true;
		}
	}
	if (m_dwOldTime + 2000 < GetTickCount())
		m_bIsDead = true;
}

void CRockShadow::Render(HDC hDC)
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
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, (int)m_tInfo.fCY * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 255, 255));
}

void CRockShadow::Release()
{
	m_iCnt--;
}
