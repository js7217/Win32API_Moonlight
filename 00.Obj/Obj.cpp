#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_bInit(FALSE)
	, m_bIsDead(FALSE)
	, m_bIsJump(FALSE)
	, m_bIsCollision(FALSE)
	, m_bIsCollisionExtra(FALSE)
	, m_iAtt(0)
	, m_iHp(0)
	, m_iMaxHp(0)
	, m_fSpeed(0.f)
	, m_fAngle(0.f)
	, m_pTarget(nullptr)
	, m_eGroupID(GroupID::GAMEOBJECT)
	, m_iOption(0)
	, m_iDrawID(0)
	, m_iIndex(0)
	, m_eObjID(ObjID::END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tCollisionRect, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::UpdateCollisionRect()
{
	m_tCollisionRect.left = LONG(m_tInfo.fX - (m_tInfo.fCollisionCX * 0.5f));
	m_tCollisionRect.top = LONG(m_tInfo.fY - (m_tInfo.fCollisionCY * 0.5f));
	m_tCollisionRect.right = LONG(m_tInfo.fX + (m_tInfo.fCollisionCX * 0.5f));
	m_tCollisionRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCollisionCY * 0.5f));
}

void CObj::FrameMove(int iStart)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = iStart;
}

void CObj::LateInitialize()
{
	if (!m_bInit)
	{
		this->LateInitialize();
		m_bInit = true;
	}
}

int CObj::RandomNumber(int min, int max)
{
	random_device rn;
	mt19937_64 rnd(rn());
	uniform_int_distribution<int> range(min, max);
	return range(rnd);
}
