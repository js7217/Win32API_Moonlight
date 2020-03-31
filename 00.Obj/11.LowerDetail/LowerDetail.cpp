#include "stdafx.h"
#include "LowerDetail.h"

#include "ObjMgr.h"
CLowerDetail::CLowerDetail()
{
}

CLowerDetail::~CLowerDetail()
{
	Release();
}

void CLowerDetail::Initialize()
{
	m_tInfo.fCX = 195.f;
	m_tInfo.fCY = 195.f;
	m_tInfo.fCollisionCX = m_tInfo.fCX;
	m_tInfo.fCollisionCY = m_tInfo.fCY;
	m_pFrameKey = L"Dungeon1_LowerDetail";
	m_eGroupID = GroupID::SHADOW;
}

int CLowerDetail::Update()
{
	return 0;
}

void CLowerDetail::LateUpdate()
{
}

void CLowerDetail::Render(HDC hDC)
{
	if (CObjMgr::Get_Instance()->Get_Player() != nullptr && CObjMgr::Get_Instance()->Get_Player()->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, int(m_tRect.left + iScrollX), int(m_tRect.top + iScrollY),
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		int(m_iDrawID * m_tInfo.fCX / 1.5f) , 0,
		int(m_tInfo.fCX / 1.5f), int(m_tInfo.fCY / 1.5f) , RGB(45, 76, 78));
}

void CLowerDetail::Release()
{
}
