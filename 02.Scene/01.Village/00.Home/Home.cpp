#include "stdafx.h"
#include "Home.h"
#include "ShopPlayer.h"
#include "SortY.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
CHome::CHome()
{
}


CHome::~CHome()
{
	Release();
}

void CHome::Initialize()
{
	m_iMapCX = WINCX * 1.5f;
	m_iMapCY = WINCY * 1.5f;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/shop_background.bmp", L"shop_background");
	CObjMgr::Get_Instance()->AddObject(ObjID::UI, CAbstractFactory<CSortY>::Create(438.f, 255.f, 45.f, 66.f));
//	Set_Init(false);
//	CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER, CAbstractFactory<CShopPlayer>::Create());
	CTileMgr::Get_Instance()->Set_SaveKey(L"../Data/Shop_Tile.dat");
	CTileMgr::Get_Instance()->LoadTile();
	CScrollMgr::Set_Scroll(0.f, 0.f);
	CSoundMgr::Get_Instance()->PlayBGM(L"shop_day_open.wav");
}

void CHome::LateInitialize()
{
	CObjMgr::Get_Instance()->AddObject(ObjID::PLAYER, CAbstractFactory<CShopPlayer>::Create());
}

void CHome::Update()
{
	CScene::LateInitialize();
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	int iScrollY = CScrollMgr::Get_ScrollY();
	if(2 == m_iOption)
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_VILLAGE);
}

void CHome::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
//	CScrollMgr::ScrollLock(m_iMapCX, m_iMapCY);
}

void CHome::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"shop_background");
	BitBlt(hDC, iScrollX, iScrollY, m_iMapCX, m_iMapCY,
		hBack, 0, 0, SRCCOPY); // ¸Ê »çÀÌÁî¸¸Å­ ÇØÁà¾ßÇÔ.

	CObjMgr::Get_Instance()->Render(hDC);
	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
		CTileMgr::Get_Instance()->Render(hDC);
}

void CHome::Release()
{
	CObjMgr::Get_Instance()->DeleteID(ObjID::UI);
	CObjMgr::Get_Instance()->DeleteID(ObjID::PLAYER);
	CTileMgr::Destory_Instance();
}
