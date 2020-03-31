#include "stdafx.h"
#include "StoneSoldierBullet.h"


CStoneSoldierBullet::CStoneSoldierBullet()
{
}

CStoneSoldierBullet::CStoneSoldierBullet(float fX, float fY, float fCX, float fCY)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = fCX;
	m_tInfo.fCY = fCY;
	m_tInfo.fCollisionCX = fCX;
	m_tInfo.fCollisionCY = fCY;
}


CStoneSoldierBullet::~CStoneSoldierBullet()
{
	Release();
}

void CStoneSoldierBullet::Initialize()
{
	m_iAtt = 10;
	m_dwOldTime = GetTickCount();
	m_eCurState = CObj::ATTACK;
}

int CStoneSoldierBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	return OBJ_NOEVENT;
}

void CStoneSoldierBullet::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_dwOldTime + 500 < GetTickCount())
		m_bIsDead = true;
}

void CStoneSoldierBullet::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();

//	Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
}

void CStoneSoldierBullet::Release()
{
}
