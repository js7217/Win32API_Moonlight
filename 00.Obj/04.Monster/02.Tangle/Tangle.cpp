#include "stdafx.h"
#include "Tangle.h"
#include "DeadBody.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CTangle::CTangle()
{
}


CTangle::~CTangle()
{
}

void CTangle::Initialize()
{
	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 96.f;
	m_tInfo.fCollisionCX = 25.f;
	m_tInfo.fCollisionCY = 25.f;
	m_iMaxHp = 30.f;
	m_iHp = m_iMaxHp;
	m_iAtt = 3;
	m_fSpeed = 2.0f;
	m_eObjID = ObjID::MONSTER;
	m_pFrameKey = L"tangle_cycle";
	m_eCurState = CObj::WALK;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwOldTime = GetTickCount();
	m_bIsHit = false;
}

void CTangle::LateInitialize()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CTangle::Update()
{
	CObj::LateInitialize();
	if (m_bIsDead)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CDeadBody>::Create(m_tInfo.fX, m_tInfo.fY, 26.f, 20.f, L"deadenemy_tangle"));
		return OBJ_DEAD;
	}
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
			CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_tangle_hit.wav", CSoundMgr::MONSTER);
			m_bIsHit = true;
		}
		if (m_dwOldTime + 100 < GetTickCount())
		{
			m_bIsHit = false;
			m_eCurState = CObj::WALK;
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

void CTangle::LateUpdate()
{
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_eCurState == CObj::DEAD)
		m_bIsDead = true;
	CObj::FrameMove(0);
}

void CTangle::Render(HDC hDC)
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
		(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, 0,
		(int)m_tInfo.fCX / 1.5f , (int)m_tInfo.fCY / 1.5f , RGB(255, 0, 255));
}

void CTangle::Release()
{
}
