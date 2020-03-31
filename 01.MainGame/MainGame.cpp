#include "stdafx.h"
#include "MainGame.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGO);
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BackBuffer.bmp", L"BackBuffer");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Black.bmp", L"Black");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Tile (2).bmp", L"Tile");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/Dungeon1_LowerDetail.bmp", L"Dungeon1_LowerDetail");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/MONSTER_SLIME.bmp", L"MONSTER_SLIME");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/tangle_cycle.bmp", L"tangle_cycle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/GolemTurret_shotwalking.bmp", L"GolemTurret_shotwalking");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/StoneSoldier_LEFT.bmp", L"StoneSoldier_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/StoneSoldier_UP.bmp", L"StoneSoldier_UP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/StoneSoldier_RIGHT.bmp", L"StoneSoldier_RIGHT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/StoneSoldier_DOWN.bmp", L"StoneSoldier_DOWN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/golemturret_projectile.bmp", L"golemturret_projectile");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/golemturret_projectile_collision.bmp", L"golemturret_projectile_collision");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/BOSS_A.bmp", L"BOSS_A");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BOSS/BOSS_A/DEATH/BOSS_A_DEATH.bmp", L"BOSS_A_DEATH");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/deadenemy_soldier.bmp", L"deadenemy_soldier");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Monster/deadenemy_tangle.bmp", L"deadenemy_tangle");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/GAME_EFFECT/ATTACK/fx_hit_Gloves.bmp", L"fx_hit_Gloves");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/GAME_EFFECT/ATTACK/fx_hit_shortsword.bmp", L"fx_hit_shortsword");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/GAME_EFFECT/ATTACK/fx_hit_bigsword.bmp", L"fx_hit_bigsword");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/GAME_EFFECT/ATTACK/spearHitEffect.bmp", L"spearHitEffect");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/golem_doors_down.bmp", L"golem_doors_down");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/golem_doors_left.bmp", L"golem_doors_left");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/golem_doors_right.bmp", L"golem_doors_right");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/golem_doors_up.bmp", L"golem_doors_up");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/boss1_door.bmp", L"boss1_door"); //obstacles_stone
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/obstacles_stone.bmp", L"obstacles_stone");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Object/hole.bmp", L"hole");
	PlayerBitMap();

	CSoundMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->KeyUpdate();
}

void CMainGame::Render()
{
	if (CSceneMgr::SCENE_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Black");
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
	CSceneMgr::Get_Instance()->Render(hBackBuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CSceneMgr::Destory_Instance();
	CBitmapMgr::Destory_Instance();
	CTileMgr::Destory_Instance();
}

void CMainGame::PlayerBitMap()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/FLEID/PLAYER_DOWN.bmp", L"PLAYER_DOWN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/FLEID/PLAYER_LEFT.bmp", L"PLAYER_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/FLEID/PLAYER_RIGHT.bmp", L"PLAYER_RIGHT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/FLEID/PLAYER_UP.bmp", L"PLAYER_UP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/FLEID/Will_Scene2.bmp", L"Will_Scene2");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/ATTACK/BIGSWORD/BIG_STATE.bmp", L"BIG_STATE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/ATTACK/BOW/BOW_STATE.bmp", L"BOW_STATE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/ATTACK/GLOVES/GLOVES_STATE.bmp", L"GLOVES_STATE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/ATTACK/SHOTSWORD/SHORT_STATE.bmp", L"SHORT_STATE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/Player/ATTACK/SPEAR/SPEAR_STATE.bmp", L"SPEAR_STATE");


}
