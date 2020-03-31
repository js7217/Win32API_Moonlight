#include "stdafx.h"
#include "HeartCircle.h"

CHeartCircle::CHeartCircle()
{
}


CHeartCircle::~CHeartCircle()
{
}

void CHeartCircle::Initialize()
{
	m_tInfo.fX = 60.f;
	m_tInfo.fY = 50.f;
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;
	m_fSpeed = 4.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/HealthBar_Circle.bmp", L"HealthBar_Circle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/HealthBar_Heart.bmp", L"HealthBar_Heart");

	m_dwOldTime = GetTickCount();
}

int CHeartCircle::Update()
{
	if (m_bIsCollision)
	{
		if (m_dwOldTime + 25 < GetTickCount())
		{
			if (m_tInfo.fX < 53.f || m_tInfo.fX > 67.f)
				m_fSpeed *= -1.f;
			m_tInfo.fX += m_fSpeed;
			m_dwOldTime = GetTickCount();
		}
	}
	return 0;
}

void CHeartCircle::LateUpdate()
{
}

void CHeartCircle::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"HealthBar_Circle");
	HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(L"HealthBar_Heart");
	GdiTransparentBlt(hDC,
		m_tRect.left - 8, m_tRect.top - 8,
		48, 48,
		hMemDC,
		0, 0,
		48, 48,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hHpDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CHeartCircle::Release()
{
}
