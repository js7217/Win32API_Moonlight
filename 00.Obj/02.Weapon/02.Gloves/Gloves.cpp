#include "stdafx.h"
#include "Gloves.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BigBullet.h"
CGloves::CGloves()
{
}


CGloves::~CGloves()
{
}

void CGloves::Initialize()
{
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 192.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Weapon/W_GLOVES/W_GLOVES.bmp", L"W_GLOVES");
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	m_pFrameKey = L"W_GLOVES";
}

int CGloves::Update()
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

void CGloves::LateUpdate()
{
}

void CGloves::Render(HDC hDC)
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
			(int)(m_tInfo.fCX /1.5f * m_tFrame.iFrameStart), (int)(m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene),
			(int)m_tInfo.fCX /1.5f , (int)m_tInfo.fCY / 1.5f ,
			RGB(255, 0, 255));
	}
}

void CGloves::Release()
{
}

void CGloves::MotionChange()
{
	m_tFrame.iFrameStart = m_pTarget->Get_Frame().iFrameStart;
	m_tFrame.iFrameEnd = 19;
	m_tFrame.iFrameScene = m_eRotate;
	m_tFrame.dwFrameSpeed = 80;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CGloves::CreateBullet()
{
	if (m_tFrame.iFrameStart == 2 || m_tFrame.iFrameStart == 6 || m_tFrame.iFrameStart == 11)
	{
		if (m_bIsBullet == false)
		{
			switch (m_eRotate)
			{
			case CObj::LEFT:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX - 50.f, m_tInfo.fY, 40.f, 30.f, L"fx_hit_Gloves"));
				break;
			case CObj::UP:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY - 50.f, 30.f, 40.f, L"fx_hit_Gloves"));
				break;
			case CObj::RIGHT:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX + 50.f, m_tInfo.fY, 40.f, 30.f, L"fx_hit_Gloves"));
				break;
			case CObj::DOWN:
				CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER_BULLET, CAbstractFactory<CBigBullet>::Create(m_tInfo.fX, m_tInfo.fY + 50.f, 30.f, 40.f, L"fx_hit_Gloves"));
				break;
			default:
				break;
			}
			m_bIsBullet = true;
		}
		if (m_tFrame.iFrameStart == 2)
			CSoundMgr::Get_Instance()->MyPlaySound(L"gloves_main_attack_swing.wav", CSoundMgr::GLOVES);
		if (m_tFrame.iFrameStart == 4)
			CSoundMgr::Get_Instance()->MyPlaySound(L"gloves_main_attack_swing_2.wav", CSoundMgr::GLOVES);
		if (m_tFrame.iFrameStart == 11)
			CSoundMgr::Get_Instance()->MyPlaySound(L"gloves_main_attack_swing_3.wav", CSoundMgr::GLOVES);
	}
	else if (m_tFrame.iFrameStart >= 4 || m_tFrame.iFrameStart >= 8 || m_tFrame.iFrameStart >= 13)
	{
		if (!CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).empty())
			CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER_BULLET).back()->Set_Dead();
		m_bIsBullet = false;
	}
}
