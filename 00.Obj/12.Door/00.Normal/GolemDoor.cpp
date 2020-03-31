#include "stdafx.h"
#include "GolemDoor.h"
#include "ObjMgr.h"

CGolemDoor::CGolemDoor()
{
}

CGolemDoor::CGolemDoor(CObj::ROTATE eRotate)
{
	switch (eRotate)
	{
	case CObj::LEFT:
		m_pFrameKey = L"golem_doors_left";
		break;
	case CObj::UP:
		m_pFrameKey = L"golem_doors_up";
		break;
	case CObj::RIGHT:
		m_pFrameKey = L"golem_doors_right";
		break;
	case CObj::DOWN:
		m_pFrameKey = L"golem_doors_down";
		break;
	default:
		break;
	}
}


CGolemDoor::~CGolemDoor()
{
}

void CGolemDoor::Initialize()
{
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 192.f;
	m_tInfo.fCollisionCX = 100.f;
	m_tInfo.fCollisionCY = 100.f;

	m_eCurState = CObj::DEAD; // ´ÝÈù »óÅÂ.
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eGroupID = GroupID::UI;
}

int CGolemDoor::Update()
{
	if (CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER).empty())
		return OBJ_NOEVENT;
	int iIndex = CObjMgr::Get_Instance()->Get_Player()->Get_Index();

	int Cnt = 0;

	for (auto& pMonster : CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER))
	{
		if (iIndex == pMonster->Get_Index())
			Cnt++;
	}

	if (0 == Cnt)
		m_eCurState = CObj::HIT; // ¿­¸°
	else
		m_eCurState = CObj::DEAD; // ´ÝÈû

	return 0;
}

void CGolemDoor::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_eCurState == CObj::HIT)
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_bIsCollisionExtra = false;
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		}
	}
	else if (m_eCurState == CObj::DEAD)
	{
		m_bIsCollisionExtra = true;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			m_eCurState = CObj::IDLE;
		}
	}
	else
	{
		m_bIsCollisionExtra = true;
		m_eCurState = CObj::IDLE;
	}

	MotionChange();
}

void CGolemDoor::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 255, 255));
}

void CGolemDoor::Release()
{
}

void CGolemDoor::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::IDLE: // ´ÝÈù Æò¼Ò »óÅÂ
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::HIT: // ¿­¸° »óÅÂ.
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD: // ´ÝÈù »óÅÂ
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}
