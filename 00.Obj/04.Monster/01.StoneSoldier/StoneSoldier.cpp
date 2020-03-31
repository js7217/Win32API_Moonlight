#include "stdafx.h"
#include "StoneSoldier.h"
#include "StoneSoldierBullet.h"
#include "ObjMgr.h"
#include "Player.h"
#include "DeadBody.h"
#include "AbstractFactory.h"
CStoneSoldier::CStoneSoldier()
{
}


CStoneSoldier::~CStoneSoldier()
{
}

void CStoneSoldier::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;
	m_tInfo.fCollisionCX = 40.f;
	m_tInfo.fCollisionCY = 50.f;
	m_eObjID = ObjID::MONSTER;
	m_iMaxHp = 100.f;
	m_iHp = m_iMaxHp;
	m_fSpeed = 0.8f;
	m_pFrameKey = L"StoneSoldier_DOWN";

	m_eCurState = CObj::WALK;
	m_eRotate = DOWN;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_bIsBullet = false;
	m_dwOldTime = GetTickCount();
	m_bIsHit = false;
}

void CStoneSoldier::LateInitialize()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

int CStoneSoldier::Update()
{
	CObj::LateInitialize();
	if (m_bIsDead)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
		CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_golem_crash.wav", CSoundMgr::MONSTER);
		CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CDeadBody>::Create(m_tInfo.fX, m_tInfo.fY, 28.f, 23.f, L"deadenemy_soldier"));
		return OBJ_DEAD;
	}
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return OBJ_NOEVENT;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();

	if (m_eCurState == CObj::WALK)
	{
		FollowPlayer();
	}
	if (m_eCurState == CObj::HIT)
	{
		if (!m_bIsHit)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
			CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_golem_hit.wav", CSoundMgr::MONSTER);
			m_bIsHit = true;
		}
		if (m_dwOldTime + 100 < GetTickCount())
		{
			m_bIsHit = false;
			m_eCurState = CObj::WALK;
		}
		m_tInfo.fX -= cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fY += sinf(m_fAngle) * m_fSpeed;
	}
	else
	{
		m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle) * m_fSpeed;
		m_dwOldTime = GetTickCount();
	}

	return OBJ_NOEVENT;
}

void CStoneSoldier::LateUpdate()
{
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	
	if (m_eCurState == CObj::ATTACK)
	{
		m_fSpeed = 0.f;
		CreateBullet();
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{

			m_eCurState = CObj::WALK;
			m_fSpeed = 1.f;
		}
	}
	else
		CObj::FrameMove(0);
	MotionChange();
}

void CStoneSoldier::Render(HDC hDC)
{
	if (m_pTarget != nullptr && m_pTarget->Get_Index() != m_iIndex)
		return;
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX / 1.5f , (int)m_tInfo.fCY / 1.5f , RGB(255, 0, 255));
}

void CStoneSoldier::Release()
{
}

void CStoneSoldier::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_bIsDead = true;
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CStoneSoldier::FollowPlayer()
{
	if (nullptr == m_pTarget)
		return;

	float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);
	m_fAngle = acosf(fWidth / fDist);
	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
	{
		m_fAngle *= -1.f;
		if (fWidth > 0) // 오른쪽에 있다.
		{
			if (fWidth > fHeight)
			{
				m_eRotate = RIGHT;
				m_pFrameKey = L"StoneSoldier_RIGHT";
			}
			else
			{
				m_eRotate = DOWN;
				m_pFrameKey = L"StoneSoldier_DOWN";
			}
		}
		else // 왼쪽에 있다.
		{
			if (fabsf(fWidth) > fabsf(fHeight))
			{
				m_eRotate = LEFT;
				m_pFrameKey = L"StoneSoldier_LEFT";
			}
			else
			{
				m_eRotate = DOWN;
				m_pFrameKey = L"StoneSoldier_DOWN";
			}
		}
	}
	else
	{
		if (fWidth > 0) // 오른쪽에 있다.
		{
			if (fWidth > fHeight)
			{
				m_eRotate = RIGHT;
				m_pFrameKey = L"StoneSoldier_RIGHT";
			}
			else
			{
				m_eRotate = UP;
				m_pFrameKey = L"StoneSoldier_UP";
			}
		}
		else // 왼쪽에 있다.
		{
			if (fabsf(fWidth) > fabsf(fHeight))
			{
				m_eRotate = LEFT;
				m_pFrameKey = L"StoneSoldier_LEFT";
			}
			else
			{
				m_eRotate = UP;
				m_pFrameKey = L"StoneSoldier_UP";
			}
		}
	}
	
}

void CStoneSoldier::CreateBullet()
{
	if (m_tFrame.iFrameStart == 7)
	{
		if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Shake() == false)
			dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Shake();
		if (m_bIsBullet == false)
		{
			switch (m_eRotate)
			{
			case CObj::LEFT:
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER_BULLET, CAbstractFactory<CStoneSoldierBullet>::Create(m_tInfo.fX - 50.f, m_tInfo.fY, 30.f, 30.f));
				break;
			case CObj::UP:
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER_BULLET, CAbstractFactory<CStoneSoldierBullet>::Create(m_tInfo.fX, m_tInfo.fY - 50.f, 30.f, 30.f));
				break;
			case CObj::RIGHT:
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER_BULLET, CAbstractFactory<CStoneSoldierBullet>::Create(m_tInfo.fX + 50.f, m_tInfo.fY, 30.f, 30.f));
				break;
			case CObj::DOWN:
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER_BULLET, CAbstractFactory<CStoneSoldierBullet>::Create(m_tInfo.fX, m_tInfo.fY + 50.f, 30.f, 30.f));
				break;
			default:
				break;
			}
			m_bIsBullet = true;
		}
	}
	else if (m_tFrame.iFrameStart == 10)
	{
		m_bIsBullet = false;
	}
}
