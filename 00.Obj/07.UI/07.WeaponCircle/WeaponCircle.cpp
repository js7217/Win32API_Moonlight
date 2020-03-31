#include "stdafx.h"
#include "WeaponCircle.h"
#include "ObjMgr.h"
#include "Player.h"
CWeaponCircle::CWeaponCircle()
{
}


CWeaponCircle::~CWeaponCircle()
{
}

void CWeaponCircle::Initialize()
{
	m_tInfo.fX = 700.f;
	m_tInfo.fY = 80.f;
	m_tInfo.fCX = 58.f;
	m_tInfo.fCY = 58.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/HUD_BaseCircle.bmp", L"HUD_BaseCircle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/Item_weapon.bmp", L"Item_weapon");
	
	m_eCurAttState = CPlayer::ATT_STATE::SPEAR;
}

int CWeaponCircle::Update()
{
	if (CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER).empty())
		return OBJ_NOEVENT;
	m_eCurAttState = 
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_AttState();

	return 0;
}

void CWeaponCircle::LateUpdate()
{
}

void CWeaponCircle::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"HUD_BaseCircle");
	HDC hWeaponDC = CBitmapMgr::Get_Instance()->FindImage(L"Item_weapon");
	GdiTransparentBlt(hDC,
		m_tRect.left, m_tRect.top,
		58, 58,
		hMemDC,
		0, 0,
		58, 58,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hWeaponDC,
		(int)m_tInfo.fCX * m_eCurAttState, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CWeaponCircle::Release()
{
}
