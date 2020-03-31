#include "stdafx.h"
#include "GolemTurret.h"
#include "DeadBody.h"
#include "GolemTurretBullet.h"
#include "ObjMgr.h"

#include "AbstractFactory.h"

CGolemTurret::CGolemTurret()
{
}


CGolemTurret::~CGolemTurret()
{
}

void CGolemTurret::Initialize()
{
	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 96.f;
	m_tInfo.fCollisionCX = 40.f;
	m_tInfo.fCollisionCY = 40.f;
	m_iMaxHp = 70.f;
	m_iHp = m_iMaxHp;
	m_fSpeed = 1.f;
	m_eObjID = ObjID::MONSTER;
	m_bIsBullet = false;
	m_pFrameKey = L"GolemTurret_shotwalking";

	m_eCurState = CObj::WALK;
	m_eRotate = DOWN;
	m_ePreRotate = DOWN;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.iFrameScene = m_eRotate;
	m_tFrame.dwFrameSpeed = 80.f;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwOldTime = GetTickCount();
	m_dwBulletTime = GetTickCount();
}

void CGolemTurret::LateInitialize()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CGolemTurret::Update()
{
	CObj::LateInitialize();
	if (m_bIsDead)
	{
		return OBJ_DEAD;
	}
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return OBJ_NOEVENT;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	CMonster::FollowTarget(m_tInfo.fX, m_tInfo.fY);
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_bIsBullet = false;
		CreateBullet();
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;
	}
	if (m_eCurState == CObj::HIT)
	{
		if (m_dwOldTime + 100 < GetTickCount())
		{
			m_eCurState = CObj::WALK;
		}
		m_tInfo.fX -= cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fY += sinf(m_fAngle) * m_fSpeed;
	}
	else
	{
		m_dwOldTime = GetTickCount();
	}
	return OBJ_NOEVENT;
}

void CGolemTurret::LateUpdate()
{
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_eCurState == CObj::DEAD)
		m_bIsDead = true;
}

void CGolemTurret::Render(HDC hDC)
{
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 0, 255));
}

void CGolemTurret::Release()
{
}

void CGolemTurret::MotionChange()
{
	if (nullptr == m_pTarget)
		return;

	float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
	{
		if (fWidth > 0) // 오른쪽에 있다.
		{
			if (fWidth > fHeight)
			{
				m_eRotate = RIGHT;
			}
			else
			{
				m_eRotate = DOWN;
			}
		}
		else // 왼쪽에 있다.
		{
			if (fabsf(fWidth) > fabsf(fHeight))
			{
				m_eRotate = LEFT;
			}
			else
			{
				m_eRotate = DOWN;
			}
		}
	}
	else
	{
		if (fWidth > 0) // 오른쪽에 있다.
		{
			if (fWidth > fHeight)
			{
				m_eRotate = RIGHT;
			}
			else
			{
				m_eRotate = UP;
			}
		}
		else // 왼쪽에 있다.
		{
			if (fabsf(fWidth) > fabsf(fHeight))
			{
				m_eRotate = LEFT;
			}
			else
			{
				m_eRotate = UP;
			}
		}
	}
	m_tFrame.iFrameScene = m_eRotate;
}

void CGolemTurret::CreateBullet()
{
	CObj* pBullet = nullptr;
	if (m_tFrame.iFrameStart >= 9)
	{
		if (m_bIsBullet == false)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::Get_Instance()->BULLET);
			CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_turret_shot.wav", CSoundMgr::BULLET);
			pBullet = CAbstractFactory<CGolemTurretBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_eRotate);
			CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER_BULLET, pBullet);
			m_dwBulletTime = GetTickCount();
			m_bIsBullet = true;
		}
	}
	else
		MotionChange();
}
