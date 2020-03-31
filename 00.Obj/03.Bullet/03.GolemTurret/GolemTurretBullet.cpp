#include "stdafx.h"
#include "GolemTurretBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CGolemTurretBullet::CGolemTurretBullet()
{
}

CGolemTurretBullet::CGolemTurretBullet(CObj::ROTATE eRotate)
{
	m_eRotate = eRotate;
}


CGolemTurretBullet::~CGolemTurretBullet()
{
}

void CGolemTurretBullet::Initialize()
{
	m_tInfo.fCX = 37.5f;
	m_tInfo.fCY = 37.5f;

	m_tInfo.fCollisionCX = 20.f;
	m_tInfo.fCollisionCY = 20.f;
	m_fSpeed = 5.f;
	m_iAtt = 5.f;
	m_pFrameKey = L"golemturret_projectile";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameScene = m_eRotate;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eCurState = CObj::ATTACK;
}

int CGolemTurretBullet::Update()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_bIsDead)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::Create(m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY, L"golemturret_projectile_collision", 4));
		return OBJ_DEAD;
	}
	switch (m_eRotate)
	{
	case CObj::LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case CObj::UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case CObj::RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	case CObj::DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	default:
		break;
	}
	return OBJ_NOEVENT;
}

void CGolemTurretBullet::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	if (iScrollX > m_tRect.left ||
		iScrollY > m_tRect.top ||
		WINCX - iScrollX < m_tRect.right ||
		WINCY - iScrollY < m_tRect.bottom)
	{
		m_bIsDead = true;
	}

	CObj::FrameMove(0);
}

void CGolemTurretBullet::Render(HDC hDC)
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

void CGolemTurretBullet::Release()
{
}
