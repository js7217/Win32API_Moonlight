#include "stdafx.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Editor.h"
#include "Logo.h"
#include "MenuScene.h"
#include "IntroDungeon.h"
#include "Home.h"
#include "Village.h"
#include "Stage1.h"
#include "Dungeon1.h"
IMPLEMENT_SINGLETON(CSceneMgr)
CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	, m_bInit(FALSE)
	, m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENEID eSceneID)
{
	m_eNextScene = eSceneID;
	if (m_eNextScene != m_eCurScene)
	{
		m_bInit = false;
		CScene* pTemp = m_pScene;
		switch (m_eNextScene)
		{
		case CSceneMgr::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case CSceneMgr::SCENE_MENU:
			m_pScene = new CMenuScene;
			break;
		case CSceneMgr::SCENE_INTRO:
			m_pScene = new CIntroDungeon;
			break;
		case CSceneMgr::SCENE_HOME:
			m_pScene = new CHome;
			break;
		case CSceneMgr::SCENE_VILLAGE:
			m_pScene = new CVillage;
			break;
		case CSceneMgr::SCENE_STAGE1:
			m_pScene = new CDungeon1;
			break;
		case CSceneMgr::SCENE_STAGE2:
			m_pScene = new CStage1;
			break;
		case CSceneMgr::SCENE_EDIT:
			m_pScene = new CEditor;
			break;
		default:
			MessageBox(g_hWnd, L"����?�߸����µ�??", L"����â", MB_OK);
			break;
		}
		Safe_Delete(pTemp);
		m_eCurScene = m_eNextScene;
	}
}

void CSceneMgr::Update()
{
	if (!m_bInit)
	{
		m_pScene->Initialize();
		m_bInit = true;
	}
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
