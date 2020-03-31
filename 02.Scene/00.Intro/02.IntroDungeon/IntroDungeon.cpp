#include "stdafx.h"
#include "IntroDungeon.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "Player.h"
#include "Tutorial.h"
#include "Tutorial_Att_Roll.h"
#include "AbstractFactory.h"
CIntroDungeon::CIntroDungeon()
{
}


CIntroDungeon::~CIntroDungeon()
{
	Release();
}

void CIntroDungeon::Initialize()
{
	m_iMapCX = 1600;
	m_iMapCY = 600;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/Tutorial_background.bmp", L"Tutorial_background");
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CTutorial>::Create(400.f, 75.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CTutorial_Att_Roll>::Create(1200.f, 75.f));
	CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER, CAbstractFactory<CPlayer>::Create(250.f, 300.f));
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Intro();

	CObjMgr::Get_Instance()->Set_ObjKey(L"../Data/Tutorial_background_Obj.dat"); 
	CTileMgr::Get_Instance()->Set_SaveKey(L"../Data/Tutorial_background_Tile.dat");
	CObjMgr::Get_Instance()->LoadObj();
	CTileMgr::Get_Instance()->LoadTile();
	CSoundMgr::Get_Instance()->PlayBGM(L"golem_dungeon_floor.wav");
}

void CIntroDungeon::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	if (2 == m_iOption)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_HOME);
	if (CKeyMgr::Get_Instance()->KeyDown('M'))
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_HOME);
}

void CIntroDungeon::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CScrollMgr::ScrollLock(m_iMapCX, m_iMapCY);
}

void CIntroDungeon::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Tutorial_background");

	BitBlt(hDC, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // ¸Ê »çÀÌÁî¸¸Å­ ÇØÁà¾ßÇÔ.

	CObjMgr::Get_Instance()->Render(hDC);
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
		CTileMgr::Get_Instance()->Render(hDC);
}

void CIntroDungeon::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CTileMgr::Destory_Instance();
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
	CObjMgr::Get_Instance()->DeleteID(ObjID::DOOR);
	CObjMgr::Get_Instance()->DeleteID(ObjID::LOWERDETAIL);
	CObjMgr::Get_Instance()->DeleteID(ObjID::SHADOW);
	CObjMgr::Get_Instance()->DeleteID(ObjID::STONE);
	CObjMgr::Get_Instance()->DeleteID(ObjID::HOLE);
	CObjMgr::Get_Instance()->DeleteID(ObjID::PLAYER);
}
