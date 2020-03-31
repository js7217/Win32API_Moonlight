#include "stdafx.h"
#include "BigBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CBigBullet::CBigBullet()
{
}

CBigBullet::CBigBullet(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = fCX;
	m_tInfo.fCY = fCY;
	m_tInfo.fCollisionCX = fCX;
	m_tInfo.fCollisionCY = fCY;
	m_pFrameKey = pFrameKey;
}


CBigBullet::~CBigBullet()
{
	Release();
}

void CBigBullet::Initialize()
{
	m_iAtt = 25;
	m_eCurState = CObj::ATTACK;
}

int CBigBullet::Update()
{
	if (m_bIsDead)
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::EFFECT, CAbstractFactory<CEffect>::
			Create(m_tInfo.fX, m_tInfo.fY, 192.f, 192.f, m_pFrameKey, 2));
		return OBJ_DEAD;
	}
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	return OBJ_NOEVENT;
}

void CBigBullet::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
}

void CBigBullet::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();

//	Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
}

void CBigBullet::Release()
{
}
