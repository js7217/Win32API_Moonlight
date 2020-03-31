#include "stdafx.h"
#include "Spear.h"
#include "ObjMgr.h"
#include "BigBullet.h"
#include "AbstractFactory.h"
CSpear::CSpear()
{
}


CSpear::~CSpear()
{
}

void CSpear::Initialize()
{
	m_tInfo.fCX = 384.f;
	m_tInfo.fCY = 384.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Weapon/W_SPEAR/W_SPEAR.bmp", L"W_SPEAR");
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	m_pFrameKey = L"W_SPEAR";
	m_bIsBullet = false;
}

int CSpear::Update()
{
	CObj::UpdateRect();
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;
	m_eRotate = m_pTarget->Get_Rotate();
	m_eCurState = m_pTarget->Get_State();
	if (m_eCurState == CObj::ATTACK)
	{
		MotionChange();
		CreateBullet();
	}
	else
	{
		if (!CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).empty())
			CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).back()->Set_Dead();
	}
	return 0;
}

void CSpear::LateUpdate()
{
}

void CSpear::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (m_eCurState == CObj::ATTACK)
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left + iScrollX), int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX), int(m_tInfo.fCY),
			hMemDC,
			(int)(m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart), (int)(m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene),
			(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f,
			RGB(255, 0, 255));
	}
}

void CSpear::Release()
{
}

void CSpear::MotionChange()
{
	m_tFrame.iFrameStart = m_pTarget->Get_Frame().iFrameStart;
	m_tFrame.iFrameEnd = 22;
	m_tFrame.iFrameScene = m_eRotate;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CSpear::CreateBullet()
{
	if (m_tFrame.iFrameStart == 1 || m_tFrame.iFrameStart == 8 || m_tFrame.iFrameStart == 15)
	{
		if (m_bIsBullet == false)
		{
			switch (m_eRotate)
			{
			case CObj::LEFT:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX - 70.f, m_tInfo.fY + 5.f, 50.f, 10.f, L"spearHitEffect"));
				break;
			case CObj::UP:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY - 70.f, 10.f, 50.f, L"spearHitEffect"));
				break;
			case CObj::RIGHT:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX + 70.f, m_tInfo.fY + 5.f, 50.f, 10.f, L"spearHitEffect"));
				break;
			case CObj::DOWN:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY + 70.f, 10.f, 50.f, L"spearHitEffect"));
				break;
			default:
				break;
			}
			m_bIsBullet = true;
		}
		if (m_tFrame.iFrameStart == 1)
			CSoundMgr::Get_Instance()->MyPlaySound(L"spear_main_attack_swing.wav", CSoundMgr::SPEAR);
		if (m_tFrame.iFrameStart == 8)
			CSoundMgr::Get_Instance()->MyPlaySound(L"spear_main_attack_swing2.wav", CSoundMgr::SPEAR);
		if (m_tFrame.iFrameStart == 15)
			CSoundMgr::Get_Instance()->MyPlaySound(L"spear_main_attack_swing3.wav", CSoundMgr::SPEAR);
	}
	else if (m_tFrame.iFrameStart >= 3 || m_tFrame.iFrameStart >= 10 || m_tFrame.iFrameStart >= 17)
	{
		if (!CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).empty())
			CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).back()->Set_Dead();
		m_bIsBullet = false;
	}
}
