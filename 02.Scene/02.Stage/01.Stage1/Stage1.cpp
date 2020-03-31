#include "stdafx.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Stage1.h"
#include "TileMgr.h"
#include "Slime.h"
#include "Tangle.h"
#include "StoneSoldier.h"
#include "GolemTurret.h"
#include "GolemBoss.h"
#include "SceneMgr.h"
// ÀÓ½Ã(»¬°Í)
#include "Tutorial.h"
#include "GolemBullet.h"
CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
//	CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER, CAbstractFactory<CPlayer>::Create());
	m_iMapCX = 1156;
	m_iMapCY = 783;
	//CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CStoneSoldier>::Create(300.f, 300.f));
	//CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(300.f, 400.f));
	//CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CTutorial>::Create(600.f, 100.f));
	//CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CTangle>::Create(500.f, 200.f));
	//CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CGolemTurret>::Create(400.f, 400.f));
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/background_boss room0.bmp", L"room0");
//	CObjMgr::Get_Instance()->Set_ObjKey(L"../Data/Stage1_Obj.dat");
	CTileMgr::Get_Instance()->Set_SaveKey(L"../Data/Stage1_Tile.dat");
//	CObjMgr::Get_Instance()->LoadObj();
	CTileMgr::Get_Instance()->LoadTile();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 600.f);
	CScrollMgr::Set_Scroll(0.f, 0.f);
	CSoundMgr::Get_Instance()->PlayBGM(L"golem_boss_track.wav");
}


void CStage1::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	Create_Boss(CAbstractFactory<CGolemBoss>::Create(600.f, 250.f));
}

void CStage1::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CScrollMgr::ScrollLock(m_iMapCX, m_iMapCY);
}

void CStage1::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"room0");

	BitBlt(hDC, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // ¸Ê »çÀÌÁî¸¸Å­ ÇØÁà¾ßÇÔ.

	CObjMgr::Get_Instance()->Render(hDC);
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
		CTileMgr::Get_Instance()->Render(hDC);
}

void CStage1::Release()
{
//	CObjMgr::Destory_Instance();
	CObjMgr::Get_Instance()->DeleteID(ObjID::MONSTER);
	CTileMgr::Destory_Instance();
}
