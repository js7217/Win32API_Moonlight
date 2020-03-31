#include "stdafx.h"
#include "Village.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
CVillage::CVillage()
{
}


CVillage::~CVillage()
{
	Release();
}

void CVillage::Initialize()
{
	m_iMapCX = 2602;
	m_iMapCY = 2134;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/Village.bmp", L"Village");
	Set_Init(false);
	CTileMgr::Get_Instance()->Set_SaveKey(L"../Data/Village_Tile.dat");
	CTileMgr::Get_Instance()->LoadTile();
	//Å¸ÀÏÃß°¡ÇÏ¼À.
	CScrollMgr::Set_Scroll(-1200.f, -300.f);
}

void CVillage::LateInitialize()
{
	CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1670.f, 630.f);
}

void CVillage::Update()
{
	CScene::LateInitialize();
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	if (2 == m_iOption)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);
	if (7 == m_iOption)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_HOME);
	if (CKeyMgr::Get_Instance()->KeyDown('M'))
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);
	if (CKeyMgr::Get_Instance()->KeyDown('B'))
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE2);
}

void CVillage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CScrollMgr::ScrollLock(m_iMapCX, m_iMapCY);
}

void CVillage::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"Village");

	BitBlt(hDC, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // ¸Ê »çÀÌÁî¸¸Å­ ÇØÁà¾ßÇÔ.

	CObjMgr::Get_Instance()->Render(hDC);
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
		CTileMgr::Get_Instance()->Render(hDC);
}

void CVillage::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CTileMgr::Destory_Instance();
}
