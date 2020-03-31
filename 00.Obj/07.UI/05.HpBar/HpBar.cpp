#include "stdafx.h"
#include "HpBar.h"
#include "Player.h"
#include "Obj.h"
#include "HeartCircle.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CHpBar::CHpBar()
{
}


CHpBar::~CHpBar()
{
}

void CHpBar::Initialize()
{
	m_tInfo.fX = 150.f;
	m_tInfo.fY = 50.f;
	m_tInfo.fCX = 146.f;
	m_tInfo.fCY = 44.f;
	m_fHpBarCX = 128.f;
	m_fMaxfCX = m_fHpBarCX;
	m_fSlideCX = m_fHpBarCX;
	m_fHpBarCY = 24.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/HealthBar_Base.bmp", L"HealthBar_Base");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/HUD_HealthBar.bmp", L"HUD_HealthBar");
	m_pHeart = CAbstractFactory<CHeartCircle>::Create();
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, m_pHeart);
	CObj::UpdateRect();
	m_eGroupID = GroupID::UI;
	m_dwOldTime = GetTickCount();
}

int CHpBar::Update()
{
	m_iMaxHp = CObjMgr::Get_Instance()->Get_Player()->Get_MaxHp();
	m_iHp = CObjMgr::Get_Instance()->Get_Player()->Get_Hp();
	m_fHpBarCX = (m_fMaxfCX * m_iHp) / m_iMaxHp;
	if (m_fHpBarCX < m_fSlideCX)			//히트 상태 일때 이 조건문 탄다.
	{
		dynamic_cast<CHeartCircle*>(m_pHeart)->Set_IsCollision(true);
		if (m_dwOldTime + 50 < GetTickCount())
		{
			m_fSlideCX -= 1.f;
			m_dwOldTime = GetTickCount();
		}
	}
	else
		dynamic_cast<CHeartCircle*>(m_pHeart)->Set_IsCollision(false);
	return 0;
}

void CHpBar::LateUpdate()
{
}

void CHpBar::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"HealthBar_Base");
	HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(L"HUD_HealthBar");
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 0 , 255));

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 14, (int)m_tRect.top + 10,
		(int)m_fSlideCX, (int)m_fHpBarCY,
		hHpDC,
		0, 0,
		(int)m_fSlideCX, (int)m_fHpBarCY,
		RGB(255, 0, 255));
}

void CHpBar::Release()
{
}
