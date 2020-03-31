#include "stdafx.h"
#include "BossDoor.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
CBossDoor::CBossDoor()
{
}


CBossDoor::~CBossDoor()
{
}

void CBossDoor::Initialize()
{
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 192.f;
	m_tInfo.fCollisionCX = 142.f;
	m_tInfo.fCollisionCY = 82.5f;

	m_pFrameKey = L"boss1_door";
	m_eCurState = CObj::IDLE;
	m_tFrame.iFrameStart = 18;
	m_tFrame.iFrameEnd = 18;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_eGroupID = GroupID::UI;
}

int CBossDoor::Update()
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
		m_eCurState = CObj::HIT;
	else
		m_eCurState = CObj::DEAD;

	return OBJ_NOEVENT;
}

void CBossDoor::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_eCurState == HIT) // ¿­¸° »óÅÂ
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Init())
		{
			if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
			{
				++m_tFrame.iFrameStart;
				m_tFrame.dwFrameTime = GetTickCount();
			}

			if (m_tFrame.iFrameStart >= 18)
			{
				CSceneMgr::Get_Instance()->Get_Scene()->Set_Option(2);
			}
		}
		else
		{
			if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
			{
				--m_tFrame.iFrameStart;
				m_tFrame.dwFrameTime = GetTickCount();
			}

			if (m_tFrame.iFrameStart <= m_tFrame.iFrameEnd)
			{
				m_bIsCollisionExtra = false;
				m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			}
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

void CBossDoor::Render(HDC hDC)
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

void CBossDoor::Release()
{
}

void CBossDoor::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::IDLE: // ´ÝÈù Æò¼Ò »óÅÂ
			m_tFrame.iFrameStart = 18;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::HIT: // ¿­¸° »óÅÂ.
			m_tFrame.iFrameStart = 18;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD: // ´ÝÈù »óÅÂ
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 18;
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
