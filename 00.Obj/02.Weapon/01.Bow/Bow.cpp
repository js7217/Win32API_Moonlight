#include "stdafx.h"
#include "Bow.h"
#include "ObjMgr.h"

CBow::CBow()
{
}


CBow::~CBow()
{
}

void CBow::Initialize()
{
	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 90.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Weapon/W_BOW/W_BOW.bmp", L"W_BOW");
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	m_pFrameKey = L"W_BOW";
}

int CBow::Update()
{
	CObj::UpdateRect();
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;
	m_eRotate = m_pTarget->Get_Rotate();
	m_eCurState = m_pTarget->Get_State();
	if (m_eRotate == CObj::DOWN)
		m_tInfo.fY += 20.f;
	if (m_eCurState == CObj::ATTACK)
		MotionChange();
	return 0;
}

void CBow::LateUpdate()
{
}

void CBow::Render(HDC hDC)
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

void CBow::Release()
{
}

void CBow::MotionChange()
{
	m_tFrame.iFrameStart = m_pTarget->Get_Frame().iFrameStart;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iFrameScene = m_eRotate;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}
