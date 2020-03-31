#include "stdafx.h"
#include "MenuScene.h"
#include "MainMenu.h"
#include "MainMenu_front.h"
#include "MainMenu_Logo.h"
#include "LeftWall.h"
#include "RightWall.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
CMenuScene::CMenuScene()
{
}


CMenuScene::~CMenuScene()
{
	Release();
}

void CMenuScene::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"main_menu_screen.wav");
//	CSoundMgr::Get_Instance()->PlayBGM(L"main_menu_door_opened_loop.wav");
	m_iNextScene = 0;
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CMainMenu>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CMainMenu_Logo>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CMainMenu_front>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CLeftWall>::Create());
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CRightWall>::Create());
}

void CMenuScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		switch (m_iNextScene)
		{
		case 0:
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_INTRO);
			break;
		case 1:
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_EDIT);
			break;
		case 2:
			DestroyWindow(g_hWnd);
			break;
		default:
			break;
		}
	}
}

void CMenuScene::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMenuScene::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CMenuScene::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
//	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
}
