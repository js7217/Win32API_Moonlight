#include "stdafx.h"
#include "Tutorial_Att_Roll.h"


CTutorial_Att_Roll::CTutorial_Att_Roll()
{
}


CTutorial_Att_Roll::~CTutorial_Att_Roll()
{
}

void CTutorial_Att_Roll::Initialize()
{
	m_tInfo.fCX = 675.f;
	m_tInfo.fCY = 75.f;
	m_tInfo.fCollisionCX = 675.f;
	m_tInfo.fCollisionCY = 75.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/Tutorial_Attack_Roll.bmp", L"Tutorial_Attack_Roll");
	m_pFrameKey = L"Tutorial_Attack_Roll";

	m_eGroupID = GroupID::GAMEOBJECT;
}

int CTutorial_Att_Roll::Update()
{
	return 0;
}

void CTutorial_Att_Roll::LateUpdate()
{
}

void CTutorial_Att_Roll::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 255, 255));
}

void CTutorial_Att_Roll::Release()
{
}
