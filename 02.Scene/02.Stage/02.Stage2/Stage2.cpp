#include "stdafx.h"
#include "Stage2.h"

#include "TileMgr.h"
#include "ObjMgr.h"
CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Initialize()
{
	m_iMapCX = 1156.f;
	m_iMapCY = 724.f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/background_boss room1.bmp", L"room1");
	CTileMgr::Get_Instance()->Set_SaveKey(L"../Data/Stage2_Tile.dat");
	CTileMgr::Get_Instance()->LoadTile();
}

void CStage2::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CStage2::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CScrollMgr::ScrollLock(m_iMapCX, m_iMapCY);
}

void CStage2::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"room1");
	BitBlt(hDC, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // ¸Ê »çÀÌÁî¸¸Å­ ÇØÁà¾ßÇÔ.

	CObjMgr::Get_Instance()->Render(hDC);

	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
		CTileMgr::Get_Instance()->Render(hDC);
}

void CStage2::Release()
{
	CTileMgr::Destory_Instance();
}
