#include "stdafx.h"
#include "GolemBoss.h"
#include "RockShadow.h"
#include "PunchShadow.h"
#include "BossHpBar.h"
#include "BossScroll.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CGolemBoss::CGolemBoss()
{
}


CGolemBoss::~CGolemBoss()
{
	Release();
}

void CGolemBoss::Initialize()
{
	m_iRockCnt = 0;
	m_tInfo.fCX = 768.f;
	m_tInfo.fCY = 768.f;
	m_tInfo.fCollisionCX = 140.f;
	m_tInfo.fCollisionCY = 100.f;
	m_fSpeed = 0.f;
	m_iRandom = 0;
	m_iMaxHp = 663;
	m_iHp = m_iMaxHp;
	m_bIsCollisionExtra = true;
	m_pFrameKey = L"BOSS_A";
	m_eCurBossState = WAKEUP;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 31;
	m_tFrame.iFrameScene = 5;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_dwOldTime = GetTickCount();
	m_dwTime = GetTickCount();
	m_dwRockCreateTime = GetTickCount();

	m_fRockX = 0.f;
	m_fRockY = 0.f;
	m_bIsPunch = false;
}

void CGolemBoss::LateInitialize()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CBossScroll>::Create());
	m_pHpBar = CAbstractFactory<CBossHpBar>::Create();
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, m_pHpBar);
}

int CGolemBoss::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	CObj::LateInitialize();
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_eCurState != CObj::DEAD)
	{
		AttackPattern();
		if (m_eCurBossState == LAUNCH)
			Golem_Punch();
		else if (m_eCurBossState == SPAWN)
			SPAWN_CASE();
	}
	if (m_eCurState == CObj::HIT)
		CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_king_golem_awake.wav", CSoundMgr::BOSS);
	MotionChange();
	return OBJ_NOEVENT;
}

void CGolemBoss::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (m_eCurState == CObj::DEAD)
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_king_golem_death.wav", CSoundMgr::BOSS);
		m_eCurBossState = DEAD;
		m_pFrameKey = L"BOSS_A_DEATH";
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			if (m_tFrame.iFrameScene == 1)
				m_bIsDead = true;
			if (m_tFrame.iFrameScene == 0)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameScene = 1;
			}
		}
	}
	else
	{
		FrameBack();
		CObj::FrameMove(0);
	}
}

void CGolemBoss::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
//	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
//	Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 0, 255));
}

void CGolemBoss::Release()
{
	m_pHpBar->Set_Dead();
}

void CGolemBoss::FrameBack()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		m_eCurBossState = IDLE;
}

void CGolemBoss::MotionChange()
{
	if (m_eCurBossState != m_ePreBossState)
	{
		switch (m_eCurBossState)
		{
		case CGolemBoss::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CGolemBoss::NOARM_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CGolemBoss::LAUNCH:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 38;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CGolemBoss::RECOVER:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 25;
			m_tFrame.iFrameScene = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CGolemBoss::SPAWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 42;
			m_tFrame.iFrameScene = 4;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CGolemBoss::WAKEUP:
			CSoundMgr::Get_Instance()->MyPlaySound(L"golem_dungeon_king_golem_awake.wav", CSoundMgr::BOSS);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 31;
			m_tFrame.iFrameScene = 5;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CGolemBoss::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 40;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
		default:
			break;
		}
		m_ePreBossState = m_eCurBossState;
	}
}

void CGolemBoss::AttackPattern()
{
	if (m_dwTime + 10000 < GetTickCount())
	{
		m_iRandom = RandomNumber(1, 2);
		switch (m_iRandom)
		{
		case 1:
			m_eCurBossState = LAUNCH;
			m_bIsPunch = false;
			break;
		case 2:
			m_eCurBossState = SPAWN;
			m_iRockCnt = 0;
			m_iRandom = RandomNumber(1, 3);
			break;
		default:
			break;
		}
		m_dwTime = GetTickCount();
		m_dwRockCreateTime = GetTickCount();
	}
}

void CGolemBoss::Straight_Rock()
{
	if (m_tFrame.iFrameStart == 10)
	{
		Get_Angle();
	}
	if (m_tFrame.iFrameStart >= 16)
	{
		if (m_dwRockCreateTime + 50 < GetTickCount() && m_iRockCnt < 40)
		{
			m_fRockX = m_tInfo.fX + cosf((m_fAngle * 3.141592f / 180.f)) * m_iRockCnt * 10;
			m_fRockY = m_tInfo.fY - sinf((m_fAngle * 3.141592f / 180.f)) * m_iRockCnt * 10 + m_tInfo.fCollisionCY;

			for (int i = 0; i < 5; ++i)
			{
				CObjMgr::Get_Instance()->AddObject(ObjID::SHADOW, CAbstractFactory<CRockShadow>::
					Create(m_fRockX - 50.f + i * 30, m_fRockY));
				m_iRockCnt++;
			}
			m_dwRockCreateTime = GetTickCount();
		}
	}
}

void CGolemBoss::Half_Circle_Rock()
{
	if (m_tFrame.iFrameStart >= 16)
	{
		if (m_dwRockCreateTime + 300 < GetTickCount())
		{
			for (int angle = 180; angle <= 360; angle += 10)
			{
				if (m_iRockCnt <= 60)
				{
					m_fRockX = m_tInfo.fX + cosf((angle * 3.141592f / 180.f)) * m_iRockCnt * 10;
					m_fRockY = m_tInfo.fY - sinf((angle * 3.141592f / 180.f)) * m_iRockCnt * 10;
					CObjMgr::Get_Instance()->AddObject(ObjID::SHADOW, CAbstractFactory<CRockShadow>::
						Create(m_fRockX - 80.f, m_fRockY));
					cout << CRockShadow::m_iCnt << endl;
					m_iRockCnt++;
				}
			}
			m_dwRockCreateTime = GetTickCount();
		}
	}
}

void CGolemBoss::Sector_Form_Rock()
{
	if (m_tFrame.iFrameStart == 10)
	{
		Get_Angle();
	}
	if (m_tFrame.iFrameStart >= 16)
	{
		if (m_dwRockCreateTime + 100 < GetTickCount() && m_iRockCnt < 10)
		{
			for (float i = 0; i < 5; ++i)
			{
				m_fRockX = m_tInfo.fX + cosf((m_fAngle * 3.141592f / 180.f) + (i * 0.5f)) * m_iRockCnt * 40;
				m_fRockY = m_tInfo.fY - sinf((m_fAngle * 3.141592f / 180.f)) * m_iRockCnt * 40 + m_tInfo.fCollisionCY;
				CObjMgr::Get_Instance()->AddObject(ObjID::SHADOW, CAbstractFactory<CRockShadow>::
					Create(m_fRockX - i * 80, m_fRockY));
				m_iRockCnt++;
			}
			m_dwRockCreateTime = GetTickCount();
		}
	}
}

void CGolemBoss::Get_Angle()
{
	float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);
	m_fAngle = acosf(fWidth / fDist);
	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
	{
		m_fAngle *= -1.f;
	}
	m_fAngle = m_fAngle * 180.f / 3.14f;
}

void CGolemBoss::Golem_Punch()
{
	if (m_tFrame.iFrameStart >= 22)
	{
		if (m_bIsPunch == false)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::SHADOW, CAbstractFactory<CPunchShadow>::Create(m_pTarget->Get_Info().fX, m_pTarget->Get_Info().fY));
			m_bIsPunch = true;
		}
	}
}

void CGolemBoss::SPAWN_CASE()
{
	switch (m_iRandom)
	{
	case 1:
		Half_Circle_Rock();
		break;
	case 2:
		Straight_Rock();
		break;
	case 3:
		Sector_Form_Rock();
	default:
		break;
	}
}
