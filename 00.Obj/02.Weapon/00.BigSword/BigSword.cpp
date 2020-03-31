#include "stdafx.h"
#include "BigSword.h"
#include "ObjMgr.h"
#include "BigBullet.h"
#include "AbstractFactory.h"
CBigSword::CBigSword()
{
}


CBigSword::~CBigSword()
{
}

void CBigSword::Initialize()
{
	m_tInfo.fCX = 384.f;
	m_tInfo.fCY = 384.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Weapon/W_BIG/W_BIG_STATE.bmp", L"W_BIG");
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	m_pFrameKey = L"W_BIG";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 39;
	m_tFrame.iFrameScene = m_eRotate;
	m_tFrame.dwFrameSpeed = 80;
	m_tFrame.dwFrameTime = GetTickCount();
	m_bIsBullet = false;
}

int CBigSword::Update()
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
	return OBJ_NOEVENT;
}

void CBigSword::LateUpdate()
{
	CObj::UpdateRect();
	
}

void CBigSword::Render(HDC hDC)
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

void CBigSword::Release()
{
}

void CBigSword::MotionChange()
{
	m_tFrame.iFrameStart = m_pTarget->Get_Frame().iFrameStart;
	m_tFrame.iFrameEnd = 39;
	m_tFrame.iFrameScene = m_eRotate;
	m_tFrame.dwFrameSpeed = 80;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CBigSword::CreateBullet()
{
	if (m_tFrame.iFrameStart == 6 || m_tFrame.iFrameStart == 17 || m_tFrame.iFrameStart == 28)
	{
		if (m_bIsBullet == false)
		{
			switch (m_eRotate)
			{
			case CObj::LEFT:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX - 50.f, m_tInfo.fY, 30.f, 100.f, L"fx_hit_bigsword"));
				break;
			case CObj::UP:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY - 50.f, 100.f, 30.f, L"fx_hit_bigsword"));
				break;
			case CObj::RIGHT:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX + 50.f, m_tInfo.fY, 30.f, 100.f, L"fx_hit_bigsword"));
				break;
			case CObj::DOWN:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY + 50.f, 100.f, 30.f, L"fx_hit_bigsword"));
				break;
			default:
				break;
			}
			m_bIsBullet = true;
		}
		if (m_tFrame.iFrameStart == 6)
			CSoundMgr::Get_Instance()->MyPlaySound(L"big_sword_main_attack_swing.wav", CSoundMgr::BIGSWORD);
		if (m_tFrame.iFrameStart == 16)
			CSoundMgr::Get_Instance()->MyPlaySound(L"big_sword_main_attack_swing2.wav", CSoundMgr::BIGSWORD);
		if (m_tFrame.iFrameStart == 28)
			CSoundMgr::Get_Instance()->MyPlaySound(L"big_sword_main_attack_swing3.wav", CSoundMgr::BIGSWORD);
	}
	else if (m_tFrame.iFrameStart >= 8 || m_tFrame.iFrameStart >= 19 || m_tFrame.iFrameStart >= 30)
	{
		if (!CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).empty())
			CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).back()->Set_Dead();
		m_bIsBullet = false;
	}
}
