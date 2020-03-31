#include "stdafx.h"
#include "ShopPlayer.h"


CShopPlayer::CShopPlayer()
{
}


CShopPlayer::~CShopPlayer()
{
}

void CShopPlayer::Initialize()
{
	m_tInfo.fCX = 384.f;
	m_tInfo.fCY = 384.f;
	m_tInfo.fCollisionCX = 70.f;
	m_tInfo.fCollisionCY = 50.f;
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;
	m_fSpeed = 2.f;

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/SHOP/PLAYER_SHOP_DOWN.bmp", L"PLAYER_SHOP_DOWN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/SHOP/PLAYER_SHOP_LEFT.bmp", L"PLAYER_SHOP_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/SHOP/PLAYER_SHOP_RIGHT.bmp", L"PLAYER_SHOP_RIGHT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/SHOP/PLAYER_SHOP_UP.bmp", L"PLAYER_SHOP_UP");
	m_pFrameKey = L"PLAYER_SHOP_DOWN";
	m_eCurState = CObj::IDLE;
	m_eRotate = DOWN;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_bIsOffset = false;
}

int CShopPlayer::Update()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	KeyCheck();
	IsJumping();
	if(m_bIsOffset)
		IsOffSet();
	return OBJ_NOEVENT;
}

void CShopPlayer::LateUpdate()
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	MotionChange();
	if (m_eCurState != CObj::JUMP)
		CObj::FrameMove(0);
}

void CShopPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();
	CObj::UpdateCollisionRect();
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX / 1.5f * m_tFrame.iFrameStart, (int)m_tInfo.fCY / 1.5f * m_tFrame.iFrameScene,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f, RGB(255, 0, 255));
}

void CShopPlayer::Release()
{
}

void CShopPlayer::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav2", CSoundMgr::PLAYER);
		m_pFrameKey = L"PLAYER_SHOP_LEFT";
		m_eCurState = CObj::WALK;
		m_eRotate = LEFT;
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav", CSoundMgr::PLAYER);
			m_tInfo.fX -= m_fSpeed;
			m_tInfo.fY -= m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav", CSoundMgr::PLAYER);
			m_tInfo.fX -= m_fSpeed;
			m_tInfo.fY += m_fSpeed;
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav2", CSoundMgr::PLAYER);
		m_pFrameKey = L"PLAYER_SHOP_RIGHT";
		m_eCurState = CObj::WALK;
		m_eRotate = RIGHT;
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav", CSoundMgr::PLAYER);
			m_tInfo.fX += m_fSpeed;
			m_tInfo.fY -= m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		{
			CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav", CSoundMgr::PLAYER);
			m_tInfo.fX += m_fSpeed;
			m_tInfo.fY += m_fSpeed;
		}
		else
			m_tInfo.fX += m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav", CSoundMgr::PLAYER);
		m_pFrameKey = L"PLAYER_SHOP_UP";
		m_eCurState = CObj::WALK;
		m_eRotate = UP;
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_step_golem_dungeon.wav2", CSoundMgr::PLAYER);
		m_pFrameKey = L"PLAYER_SHOP_DOWN";
		m_eCurState = CObj::WALK;
		m_eRotate = DOWN;
		m_tInfo.fY += m_fSpeed;
	}
	else
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		m_eCurState = CObj::IDLE;
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
	{
		m_bIsJump = true;
	}
}

void CShopPlayer::MotionChange()
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
			break;
		case CObj::JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 2;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CShopPlayer::IsJumping()
{
	if (m_bIsJump)
	{
		CSoundMgr::Get_Instance()->MyPlaySound(L"will_roll.wav", CSoundMgr::PLAYER);
		m_eCurState = CObj::JUMP;
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			m_tFrame.dwFrameTime = GetTickCount();
		}
		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_bIsJump = false;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		}
	}
}

void CShopPlayer::IsOffSet()
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
}
