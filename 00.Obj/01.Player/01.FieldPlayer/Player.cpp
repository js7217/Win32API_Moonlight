#include "stdafx.h"
#include "Player.h"

#include "BigSword.h"
#include "Bow.h"
#include "Gloves.h"
#include "ShortSword.h"
#include "Spear.h"
#include "HpBar.h"
#include "HeartCircle.h"
#include "WeaponCircle.h"
#include "Alert.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
CPlayer::CPlayer()
	:m_bIsIntro(false)
	,m_bIsShake(false)
	,m_iShakeNum(2)
	,m_iIntro(0)
	,m_eCurAtt(ATT_STATE::END)
	,m_ePreAtt(ATT_STATE::END)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
	{
		m_pFrameKey = L"PLAYER_LEFT";
		m_eCurState = CObj::WALK;
		m_eRotate = LEFT;
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed;
			m_tInfo.fY -= m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed;
			m_tInfo.fY += m_fSpeed;
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
	{
		m_pFrameKey = L"PLAYER_RIGHT";
		m_eCurState = CObj::WALK;
		m_eRotate = RIGHT;
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		{
			m_tInfo.fX += m_fSpeed;
			m_tInfo.fY -= m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed;
			m_tInfo.fY += m_fSpeed;
		}
		else
			m_tInfo.fX += m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
	{
		m_pFrameKey = L"PLAYER_UP";
		m_eCurState = CObj::WALK;
		m_eRotate = UP;
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
	{
		m_pFrameKey = L"PLAYER_DOWN";
		m_eCurState = CObj::WALK;
		m_eRotate = DOWN;
		m_tInfo.fY += m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing('A'))					//공격
	{
		m_eCurState = CObj::ATTACK;

	}
	else
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		m_eCurState = CObj::IDLE;
		switch (m_eRotate)
		{
		case CPlayer::LEFT:
			m_pFrameKey = L"PLAYER_LEFT";
			break;
		case CPlayer::UP:
			m_pFrameKey = L"PLAYER_UP";
			break;
		case CPlayer::RIGHT:
			m_pFrameKey = L"PLAYER_RIGHT";
			break;
		case CPlayer::DOWN:
			m_pFrameKey = L"PLAYER_DOWN";
			break;
		default:
			break;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
	{
		m_bIsJump = true;
	}
}

void CPlayer::MotionChange()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CObj::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 1;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::ATTACK:
			AttMotionChange();
			break;
		case CObj::JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 64;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CObj::DEAD:
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPlayer::AttMotionChange()
{
	if (true)
	{
		switch (m_eCurAtt)
		{
		case CPlayer::BIGSWORD:
			m_pFrameKey = L"BIG_STATE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 39;
			m_tFrame.iFrameScene = m_eRotate;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::GLOVES:
			m_pFrameKey = L"GLOVES_STATE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 19;
			m_tFrame.iFrameScene = m_eRotate;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::SHOTSWORD:
			m_pFrameKey = L"SHORT_STATE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iFrameScene = m_eRotate;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::SPEAR:
			m_pFrameKey = L"SPEAR_STATE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 22;
			m_tFrame.iFrameScene = m_eRotate;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::END:
			break;
		default:
			break;
		}
	//	m_eCurAtt = m_ePreAtt;
	}
}

void CPlayer::IsJumping()
{
	if (m_bIsJump)
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_roll.wav", CSoundMgr::EFFECT);
		m_eCurState = CObj::JUMP;
		m_fSpeed = 4.f;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			m_fSpeed = 3.f;
			m_bIsJump = false;
		}
	}
}

void CPlayer::IsHit()
{
	if (m_bIsCollision)
	{
		if (!m_bIsHit)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
			CSoundMgr::Get_Instance()->MyPlaySound(L"will_damaged.wav", CSoundMgr::PLAYER);
			m_bIsHit = true;
		}
		if (m_dwHitTime + 2000 < GetTickCount())
		{
			m_bIsCollision = false;
			m_bIsHit = false;
			m_dwHitTime = GetTickCount();
		}
		/*m_eCurState = CObj::HIT;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
			switch (m_eRotate)
			{
			case CPlayer::LEFT:
				m_tInfo.fX += m_fSpeed;
				break;
			case CPlayer::UP:
				m_tInfo.fY += m_fSpeed;
				break;
			case CPlayer::RIGHT:
				m_tInfo.fX -= m_fSpeed;
				break;
			case CPlayer::DOWN:
				m_tInfo.fY -= m_fSpeed;
				break;
			default:
				break;
			}
		}
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
			m_bIsHit = false;*/
	}
	else
	{
		m_dwHitTime = GetTickCount();
		m_dwHitRenderTime = GetTickCount();
	}
}

void CPlayer::IsOffSet()
{
	float iOffSetX = WINCX * 0.5f;
	float iOffSetY = WINCY * 0.5f;
	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();

	if (iOffSetX < m_tInfo.fX + iScrollX + 50.f)
	{
		CScrollMgr::Set_ScrollX(-m_fSpeed);
	}
	if (iOffSetX > m_tInfo.fX + iScrollX - 50.f)
	{
		CScrollMgr::Set_ScrollX(m_fSpeed);
	}
	if (iOffSetY < m_tInfo.fY + iScrollY + 50.f)
	{
		CScrollMgr::Set_ScrollY(-m_fSpeed);
	}
	if (iOffSetY > m_tInfo.fY + iScrollY - 50.f)
	{
		CScrollMgr::Set_ScrollY(m_fSpeed);
	}
	//cout << m_tInfo.fX + iScrollX << ", " << m_tInfo.fY + iScrollY << endl;
}

void CPlayer::IsShake()
{
	if (m_bIsShake)
	{
		if (m_iShakeNum > 0 && m_iShakeNum % 2 == 0)
		{
			CScrollMgr::Set_Scroll(m_fScrollX, m_fScrollY - 10);
			--m_iShakeNum;
		}
		else if (m_iShakeNum > 0 && m_iShakeNum % 2 != 0)
		{
			CScrollMgr::Set_Scroll(m_fScrollX, m_fScrollY);
			m_bIsShake = false;
			--m_iShakeNum;
		}
	}
	else
	{
		m_iShakeNum = 2;
		m_fScrollX = CScrollMgr::Get_ScrollX();
		m_fScrollY = CScrollMgr::Get_ScrollY();
	}
	return;
}

void CPlayer::IsOffSet_Dungeon()
{
	if (m_iLR == -1) // x축
	{
		if (m_fAddScroll < 0)
		{
			if (m_fPreScroll + m_fAddScroll < CScrollMgr::Get_ScrollX()) // 
			{
				CScrollMgr::Set_ScrollX(m_fAddScroll * 0.05f);
			}
		}
		else
		{
			if (m_fPreScroll + m_fAddScroll > CScrollMgr::Get_ScrollX())
			{
				CScrollMgr::Set_ScrollX(m_fAddScroll * 0.05f);
			}
		}
	}
	else if (m_iLR == 1) //y축
	{
		if (m_fAddScroll < 0)
		{
			if (m_fPreScroll + m_fAddScroll < CScrollMgr::Get_ScrollY()) // 
			{
				CScrollMgr::Set_ScrollY(m_fAddScroll * 0.05f);
			}
		}
		else
		{
			if (m_fPreScroll + m_fAddScroll > CScrollMgr::Get_ScrollY())
			{
				CScrollMgr::Set_ScrollY(m_fAddScroll * 0.05f);
			}
		}
	}
	cout << CScrollMgr::Get_ScrollX() << ", " << CScrollMgr::Get_ScrollY() << endl;
}

void CPlayer::WeaponChange()
{
	if (CKeyMgr::Get_Instance()->KeyDown('1'))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_weapon_change.wav", CSoundMgr::PLAYER);
		m_tFrame.iFrameStart = 0;
		CObjMgr::Get_Instance()->DeleteID(ObjID::WEAPON);
		CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CBigSword>::Create(m_tInfo.fX, m_tInfo.fY));
		m_eCurAtt = ATT_STATE::BIGSWORD;
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('2'))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_weapon_change.wav", CSoundMgr::PLAYER);
		CObjMgr::Get_Instance()->DeleteID(ObjID::WEAPON);
		CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CGloves>::Create(m_tInfo.fX, m_tInfo.fY));
		m_eCurAtt = ATT_STATE::GLOVES;
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('3'))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_weapon_change.wav", CSoundMgr::PLAYER);
		CObjMgr::Get_Instance()->DeleteID(ObjID::WEAPON);
		CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CShortSword>::Create(m_tInfo.fX, m_tInfo.fY));
		m_eCurAtt = ATT_STATE::SHOTSWORD;
	}
	else if (CKeyMgr::Get_Instance()->KeyDown('4'))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_weapon_change.wav", CSoundMgr::PLAYER);
		CObjMgr::Get_Instance()->DeleteID(ObjID::WEAPON);
		CObjMgr::Get_Instance()->AddObject(ObjID::WEAPON, CAbstractFactory<CSpear>::Create(m_tInfo.fX, m_tInfo.fY));
		m_eCurAtt = ATT_STATE::SPEAR;
	}
}

void CPlayer::IntroSceneSprite()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		++m_iIntro;
		m_tFrame.dwFrameTime = GetTickCount();
	}
	if (m_iIntro <= 36)
		m_tInfo.fX += 0.3f;
	else if (m_iIntro >= 61 && m_iIntro <= 94)
		m_tInfo.fX += 0.3f;
	else
		m_tInfo.fX += 0.f;
	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		if (m_tFrame.iFrameScene == 0)
		{
			m_tFrame.iFrameScene = 1;
			m_tFrame.iFrameStart = 0;
		}
		else if (m_tFrame.iFrameScene == 1)
		{
			CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CAlert>::Create(m_tCollisionRect.right + 30.f, m_tCollisionRect.top));
			m_bIsIntro = false;
			m_pFrameKey = L"PLAYER_UP";
			m_eCurState = CObj::IDLE;
			m_eRotate = UP;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
		}
	}
}

void CPlayer::Initialize()
{
	m_tInfo.fCX = 384.f;
	m_tInfo.fCY = 384.f;
	m_tInfo.fCollisionCX = 30.f;
	m_tInfo.fCollisionCY = 60.f;
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;
	m_bIsHit = false;
	m_fSpeed = 3.f;
	m_iMaxHp = 128;
	m_iHp = m_iMaxHp;
	m_eObjID = ObjID::PLAYER;
	m_fScrollX = 0.f;
	m_fScrollY = 0.f;

	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CHpBar>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CWeaponCircle>::Create());

	m_eCurAtt = ATT_STATE::SPEAR;

	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_INTRO)
	{
		m_pFrameKey = L"Will_Scene2";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 64;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
	}
	else
	{
		m_pFrameKey = L"PLAYER_DOWN";
		m_eCurState = CObj::IDLE;
		m_eRotate = DOWN;
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 9;
		m_tFrame.iFrameScene = 0;
		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
	}
}

int CPlayer::Update()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	IsShake();

	if (!m_bIsIntro)
	{
		KeyCheck();
		IsJumping();
		IsHit();

		if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_VILLAGE ||
			CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_STAGE2)
		{
			IsOffSet();
		}
		else if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_STAGE1 ||
			CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_INTRO)
		{
			int iScrollX = (int)CScrollMgr::Get_ScrollX();
			int iScrollY = (int)CScrollMgr::Get_ScrollY();
			m_iIndex = (abs(iScrollY / WINCY) * 3) + abs(iScrollX / WINCX);
			cout << m_iIndex << endl;
			IsOffSet_Dungeon();
		}
		// cout << m_iHp << " /" << m_iMaxHp << endl;
	}
	else
		IntroSceneSprite();

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	if (!m_bIsIntro)
	{
		MotionChange();
		if(m_eCurState != CObj::JUMP)
			CObj::FrameMove(0);
		WeaponChange();				//무기 교체
	}
}

void CPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (m_bIsCollision)
	{
		if (m_dwHitRenderTime + 80 < GetTickCount())
		{
			GdiTransparentBlt(hDC,
				(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
				(int)m_tInfo.fCX, (int)m_tInfo.fCY,
				hMemDC,
				(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
				(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 0, 255));
			m_dwHitRenderTime = GetTickCount();
		}
	}
	else
	{
		GdiTransparentBlt(hDC,
			(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
			(int)m_tInfo.fCX / 1.5f , (int)m_tInfo.fCY / 1.5f, RGB(255, 0, 255));
	}
}

void CPlayer::Release()
{
}
