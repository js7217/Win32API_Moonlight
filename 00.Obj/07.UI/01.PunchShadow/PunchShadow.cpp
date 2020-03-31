#include "stdafx.h"
#include "PunchShadow.h"
#include "GolemHand.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CPunchShadow::CPunchShadow()
{
}


CPunchShadow::~CPunchShadow()
{
}

void CPunchShadow::Initialize()
{
	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;
	m_tInfo.fCollisionCX = 64.f;
	m_tInfo.fCollisionCY = 64.f;
	m_fSpeed = 0.3f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/PUNCH_SHADOW/BOSS_A_PUNCH_SHADOW.bmp", L"BOSS_A_PUNCH_SHADOW");
	m_pFrameKey = L"BOSS_A_PUNCH_SHADOW";
	m_dwOldTime = GetTickCount();
	m_bIsPunch = false;
	m_bIsStop = false;
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	m_eGroupID = GroupID::SHADOW;
}

int CPunchShadow::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	if (m_bIsStop == false)
	{
		m_tInfo.fX = m_pTarget->Get_Info().fX;
		m_tInfo.fY = m_pTarget->Get_Info().fY;
	}
	if (m_tInfo.fCX <= 64.f || m_tInfo.fCY <= 64.f)
	{
		m_tInfo.fCX += m_fSpeed;
		m_tInfo.fCY += m_fSpeed;
	}
	return OBJ_NOEVENT;
}

void CPunchShadow::LateUpdate()
{
	if (m_dwOldTime + 3500 < GetTickCount()) // 플레이어 추적
	{
		m_bIsStop = true;
	}
	if (m_dwOldTime + 4000 < GetTickCount())
	{
		if (m_bIsPunch == false)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::BOSS_ARM, CAbstractFactory<CGolemHand>::
				Create(m_tInfo.fX, m_tInfo.fY - 300.f));
			m_bIsPunch = true;
			m_bIsDead = true;
		}
	}  
}

void CPunchShadow::Render(HDC hDC)
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
		(int)m_tInfo.fCollisionCX * m_tFrame.iFrameStart, (int)m_tInfo.fCollisionCY * m_tFrame.iFrameScene,
		(int)m_tInfo.fCollisionCX, (int)m_tInfo.fCollisionCY, RGB(255, 0, 255));
}

void CPunchShadow::Release()
{
}
