#include "stdafx.h"
#include "Alert.h"


CAlert::CAlert()
{
}


CAlert::~CAlert()
{
}

void CAlert::Initialize()
{
	m_tInfo.fCX = 43.5f;
	m_tInfo.fCY = 43.5f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/visitor_talk_base.bmp", L"visitor_talk_base");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/PlayerUI/visitortalk_alert.bmp", L"visitortalk_alert");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 130;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwOldTime = GetTickCount();
	CSoundMgr::Get_Instance()->MyPlaySound(L"will_exclamation_tutorial.wav", CSoundMgr::EFFECT);
}

int CAlert::Update()
{
	CObj::UpdateRect();
	if (m_bIsDead)
	{
		if (m_dwOldTime + 1000 < GetTickCount())
			return OBJ_DEAD;
	}
	else
		m_dwOldTime = GetTickCount();
	return OBJ_NOEVENT;
}

void CAlert::LateUpdate()
{
	CObj::UpdateRect();
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		m_bIsDead = true;
	}
}

void CAlert::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"visitor_talk_base");
	HDC hAlertDC = CBitmapMgr::Get_Instance()->FindImage(L"visitortalk_alert");
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, (int)m_tRect.top,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		0, 0,
		(int)m_tInfo.fCX / 1.5f, (int)m_tInfo.fCY / 1.5f,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tRect.left - 1.5f, (int)m_tRect.top - 1.5f,
		(int)48, (int)48,
		hAlertDC,
		32 * m_tFrame.iFrameStart, 0,
		32, 32,
		RGB(255, 0, 255));
}

void CAlert::Release()
{
}
