#include "stdafx.h"
#include "Slime.h"
#include "ObjMgr.h"

CSlime::CSlime()
{
}


CSlime::~CSlime()
{
}

void CSlime::Initialize()
{
	m_tInfo.fCX = 97.5f;
	m_tInfo.fCY = 75.f;
	m_tInfo.fCollisionCX = 35.f;
	m_tInfo.fCollisionCY = 35.f;
	m_iMaxHp = 30;
	m_iHp = m_iMaxHp;
	m_iAtt = 10;
	m_fSpeed = 1.3f;
	m_eObjID = ObjID::MONSTER;
	m_pFrameKey = L"MONSTER_SLIME";

	m_eCurState = CObj::WALK;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwOldTime = GetTickCount();
	m_bIsHit = false;
}

void CSlime::LateInitialize()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CSlime::Update()
{
	CObj::LateInitialize();
	if (m_bIsDead)
		return OBJ_DEAD;
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return OBJ_NOEVENT;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();

	CMonster::FollowTarget(m_tInfo.fX, m_tInfo.fY);
	if (m_eCurState == CObj::HIT)
	{
		if (!m_bIsHit)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_babyslime_hit.wav", CSoundMgr::MONSTER);
			m_bIsHit = true;
		}
		if (m_dwOldTime + 300 < GetTickCount())
		{
			m_bIsHit = false;
			m_eCurState = CObj::WALK;
			m_dwOldTime = GetTickCount();
		}
		m_tInfo.fX -= cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fY += sinf(m_fAngle) * m_fSpeed;
	}
	else
	{
		m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle) * m_fSpeed;
		m_dwOldTime = GetTickCount();
	}
	return OBJ_NOEVENT;
}

void CSlime::LateUpdate()
{
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	CMonster::FrameDead();
	MotionChange();

	if(m_eCurState != CObj::DEAD)
		CObj::FrameMove(0);
}

void CSlime::Render(HDC hDC)
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
		(int)m_tInfo.fCX / 1.5f , (int)m_tInfo.fCY / 1.5f , RGB(255, 0, 255));
}

void CSlime::Release()
{
}

void CSlime::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}
