#include "stdafx.h"
#include "Stone.h"

#include "ObjMgr.h"
CStone::CStone()
{
}


CStone::~CStone()
{
	Release();
}

void CStone::Initialize()
{
	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 75.f;
	m_tInfo.fCollisionCX = 20.f;
	m_tInfo.fCollisionCY = 20.f;
	m_pFrameKey = L"obstacles_stone";
	m_eGroupID = GroupID::GAMEOBJECT;
	m_bIsCollision = true;
}

int CStone::Update()
{
	if (CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER).empty())
		return OBJ_NOEVENT;

	CObj::UpdateCollisionRect();
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Index() == m_iIndex)
	{
		m_bIsCollision = false;
		m_bIsCollisionExtra = true;
	}
	else
	{
		m_bIsCollision = true;
		m_bIsCollisionExtra = false;
	}

	return OBJ_NOEVENT;
}

void CStone::LateUpdate()
{
	CObj::UpdateCollisionRect();
}

void CStone::Render(HDC hDC)
{
	if (CObjMgr::Get_Instance()->Get_Player() != nullptr && CObjMgr::Get_Instance()->Get_Player()->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, int(m_tRect.left + iScrollX), int(m_tRect.top + iScrollY),
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		int(m_iDrawID * m_tInfo.fCX / 1.5f), 0,
		int(m_tInfo.fCX / 1.5f), int(m_tInfo.fCY / 1.5f), RGB(255, 0, 255));
}

void CStone::Release()
{
}
