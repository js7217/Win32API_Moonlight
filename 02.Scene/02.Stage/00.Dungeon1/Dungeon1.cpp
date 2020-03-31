#include "stdafx.h"
#include "Dungeon1.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "Tutorial.h"
#include "GolemDoor.h"
#include "Slime.h"
#include "AbstractFactory.h"

#include "BossScroll.h"

CDungeon1::CDungeon1()
{
}


CDungeon1::~CDungeon1()
{
	Release();
}

void CDungeon1::Initialize()
{
	m_iMapCX = 2400;
	m_iMapCY = 1800;
	m_iOption = 0;
//	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(500.f, 300.f));
//	CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, CAbstractFactory<CSlime>::Create(500.f, 400.f));
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/Dungeon1_background.bmp", L"Dungeon1_background");
	CObjMgr::Get_Instance()->Set_ObjKey(L"../Data/Dungeon1_background_1_Obj.dat");
	CTileMgr::Get_Instance()->Set_SaveKey(L"../Data/Dungeon1_background_1_Tile.dat");
	CObjMgr::Get_Instance()->LoadObj();
	CTileMgr::Get_Instance()->LoadTile();
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(200.f, 300.f);
	CScrollMgr::Set_Scroll(0.f, 0.f);
	CSoundMgr::Get_Instance()->PlayBGM(L"golem_dungeon_floor.wav");
}

void CDungeon1::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_EDIT)
	{
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		{
			CScrollMgr::Set_ScrollX(10.f);
		}
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		{
			CScrollMgr::Set_ScrollX(-10.f);
		}
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		{
			CScrollMgr::Set_ScrollY(10.f);
		}
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		{
			CScrollMgr::Set_ScrollY(-10.f);
		}
	}
	if (2 == m_iOption)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE2);
}

void CDungeon1::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
//	CScrollMgr::ScrollLock(m_iMapCX, m_iMapCY);
}

void CDungeon1::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Dungeon1_background");

	BitBlt(hDC, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // ¸Ê »çÀÌÁî¸¸Å­ ÇØÁà¾ßÇÔ.

	CObjMgr::Get_Instance()->Render(hDC);
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
		CTileMgr::Get_Instance()->Render(hDC);
}

void CDungeon1::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->DeleteID(ObjID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(ObjID::DOOR);
	CObjMgr::Get_Instance()->DeleteID(ObjID::HOLE);
	CTileMgr::Destory_Instance();
}
