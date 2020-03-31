#include "stdafx.h"
#include "BossHpBar.h"
#include "GolemBoss.h"
#include "ObjMgr.h"

CBossHpBar::CBossHpBar()
{
}


CBossHpBar::~CBossHpBar()
{
}

void CBossHpBar::Initialize()
{
	m_tInfo.fX = 400.5f;
	m_tInfo.fY = 530.5f;
	m_tInfo.fCX = 663.f;
	m_tInfo.fCY = 18.f;
	m_fHpBarCX = 648.f;
	m_fMaxfCX = m_fHpBarCX;
	m_fSlideCX = m_fHpBarCX;
	m_fHpBarCY = 9.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/HUD_Boss_HealthBar.bmp", L"HUD_Boss_HealthBar");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/HUD_Boss_HealthBar_Decoration.bmp", L"HUD_Boss_HealthBar_Decoration");
	CObj::UpdateRect();
	m_dwOldTime = GetTickCount();
	m_eGroupID = GroupID::UI;
}

int CBossHpBar::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	if (CObjMgr::Get_Instance()->Get_List(ObjID::BOSS).empty())
		return OBJ_NOEVENT;
	m_iMaxHp = CObjMgr::Get_Instance()->Get_Instance()->Get_List(ObjID::BOSS).front()->Get_MaxHp();
	m_iHp = CObjMgr::Get_Instance()->Get_Instance()->Get_List(ObjID::BOSS).front()->Get_Hp();
	m_fHpBarCX = (m_fMaxfCX * m_iHp) / m_iMaxHp;
	if (m_fHpBarCX < m_fSlideCX)			//È÷Æ® »óÅÂ ÀÏ¶§ ÀÌ Á¶°Ç¹® Åº´Ù.
	{
		if (m_dwOldTime + 50 < GetTickCount())
		{
			m_fSlideCX -= 5.f;
			m_dwOldTime = GetTickCount();
		}
	}
	return 0;
}

void CBossHpBar::LateUpdate()
{
}

void CBossHpBar::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"HUD_Boss_HealthBar_Decoration");
	HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(L"HUD_Boss_HealthBar");
	
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, m_tInfo.fX, m_tInfo.fY - 50, L"°ñ·½ ¿Õ", lstrlen(L"°ñ·½ ¿Õ"));
	SetTextColor(hDC, RGB(0, 0, 0));
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 255, 255));

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 7.5f, (int)m_tRect.top + 5.f,
		(int)m_fSlideCX, (int)m_fHpBarCY,
		hHpDC,
		0, 0,
		(int)m_fSlideCX, (int)m_fHpBarCY,
		RGB(255, 255, 255));
}

void CBossHpBar::Release()
{
}
