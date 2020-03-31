#include "stdafx.h"
#include "Editor.h"
#include "Mouse.h"
#include "Slime.h"
#include "Tangle.h"
#include "GolemTurret.h"
#include "StoneSoldier.h"
#include "LowerDetail.h"
#include "Stone.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
CEditor::CEditor()
{
}


CEditor::~CEditor()
{
	Release();
}

void CEditor::Initialize()
{
	m_iPickTile = 0;
	m_iObj = 1;
	m_iLowerDrawID = 0;
	m_iStoneDrawID = 0;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/shop_background.bmp", L"shop_background");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/Village.bmp", L"Village");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/background_boss room0.bmp", L"room0");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/Dungeon1_background.bmp", L"Dungeon1_background");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Moonlight_Resource/BACKGROUND/Tutorial_background.bmp", L"Tutorial_background");
	CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	CTileMgr::Get_Instance()->Initialize();
	m_iMapCX = 1200;
	m_iMapCY = 900;
	m_pFrameKey = L"shop_background";
	m_pTileKey = L"../Data/Shop_Tile.dat";
	m_pObjKey = L"../Data/Shop_Obj.dat";
	CTileMgr::Get_Instance()->Set_SaveKey(m_pTileKey);
	CObjMgr::Get_Instance()->Set_ObjKey(m_pObjKey);
	m_bIsLockX = false;
	m_bIsLockY = false;
}

void CEditor::Update()
{
	if (CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).empty())
		CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	MapChange();
	KeyCheck();
	//if(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
}

void CEditor::LateUpdate()
{
	//if (CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())
	CObjMgr::Get_Instance()->LateUpdate();
	if (!CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).empty())
		CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front()->LateUpdate();
	CTileMgr::Get_Instance()->LateUpdate();
	CScrollMgr::ScrollLock(m_iMapCX, m_iMapCY);
}

void CEditor::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_ScrollY();
	HDC hBackBuffer = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	BitBlt(hBackBuffer, iScrollX, iScrollY, (int)m_iMapCX, (int)m_iMapCY,
		hBack, 0, 0, SRCCOPY); // ∏  ªÁ¿Ã¡Ó∏∏≈≠ «ÿ¡‡æﬂ«‘.

	CObjMgr::Get_Instance()->Render(hDC);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_TAB))
		CTileMgr::Get_Instance()->Render(hBackBuffer);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CEditor::Release()
{
	CTileMgr::Destory_Instance();
	CObjMgr::Get_Instance()->DeleteID(ObjID::MOUSE);
}

void CEditor::KeyCheck()
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

	if (CKeyMgr::Get_Instance()->KeyPressing(VK_TAB)) // ≈∏¿œ
	{
		dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"Tile", m_iPickTile, TILECX, TILECY, 0.f, 255.f, 0.f);
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
		{
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			pt.x -= (LONG)CScrollMgr::Get_ScrollX();
			pt.y -= (LONG)CScrollMgr::Get_ScrollY();

			CTileMgr::Get_Instance()->PickTile(pt, m_iPickTile, m_iPickTile);
		}
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			if (m_iPickTile >= 10)
				m_iPickTile = -1;
			++m_iPickTile;
			CTileMgr::Get_Instance()->ChangeTile(m_iPickTile, m_iPickTile);
			dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"Tile", m_iPickTile, TILECX, TILECY, 0.f, 255.f, 0.f);
		}
	}
	else// ø¿∫Í¡ß∆Æ
	{
		if (CKeyMgr::Get_Instance()->KeyUp(VK_SHIFT))
			m_bIsLockY = false;
		if (CKeyMgr::Get_Instance()->KeyUp('A'))						// shift : y√‡ ∞Ì¡§, A : x√‡ ∞Ì¡§
			m_bIsLockX = false;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			CObj* pObj = nullptr;
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			pt.x -= (LONG)CScrollMgr::Get_ScrollX();
			pt.y -= (LONG)CScrollMgr::Get_ScrollY();
			int iIndex = (pt.y / WINCY * 3) + ((pt.x / WINCX)); // «ÿ¥Á ƒ≠.
			if (CKeyMgr::Get_Instance()->KeyPressing('A'))
			{
				if (!m_bIsLockX)
				{
					m_fLockX = pt.x;
					m_bIsLockX = true;
				}
				pt.x = m_fLockX;
			}

			if (CKeyMgr::Get_Instance()->KeyPressing(VK_SHIFT))
			{
				if (!m_bIsLockY)
				{
					m_fLockY = pt.y;
					m_bIsLockY = true;
				}
				pt.y = m_fLockY;
			}

			switch (m_iObj)
			{
			case 0:					//Lower
				pObj = CAbstractFactory<CLowerDetail>::Create(pt.x, pt.y, m_iObj, m_iLowerDrawID);
				pObj->Set_Index(iIndex);
				cout << iIndex << endl;
				CObjMgr::Get_Instance()->AddObject(ObjID::LOWERDETAIL, pObj);
				CObjMgr::Get_Instance()->AddSaveObject(pObj);
				break;
			case 1:					//ΩΩ∂Û¿”
				pObj = CAbstractFactory<CSlime>::Create(pt.x, pt.y, 0.f, m_iObj);
				pObj->Set_Index(iIndex);
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, pObj);
				CObjMgr::Get_Instance()->AddSaveObject(pObj);
				break;
			case 2:					//∞Ò∑Ω
				pObj = CAbstractFactory<CStoneSoldier>::Create(pt.x, pt.y, 0.f, m_iObj);
				pObj->Set_Index(iIndex);
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, pObj);
				CObjMgr::Get_Instance()->AddSaveObject(pObj);
				break;
			case 3:					// Tangle
				pObj = CAbstractFactory<CTangle>::Create(pt.x, pt.y, 0.f, m_iObj);
				pObj->Set_Index(iIndex);
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, pObj);
				CObjMgr::Get_Instance()->AddSaveObject(pObj);
				break;
			case 4:					// ≈Õ∑ø
				pObj = CAbstractFactory<CGolemTurret>::Create(pt.x, pt.y, 0.f, m_iObj);
				pObj->Set_Index(iIndex);
				CObjMgr::Get_Instance()->AddObject(ObjID::MONSTER, pObj);
				CObjMgr::Get_Instance()->AddSaveObject(pObj);
				break;
			case 9:					// µπ∏Õ¿Ã
				pObj = CAbstractFactory<CStone>::Create(pt.x, pt.y, m_iObj, m_iStoneDrawID);
				pObj->Set_Index(iIndex);
				cout << iIndex << endl;
				CObjMgr::Get_Instance()->AddObject(ObjID::STONE, pObj);
				CObjMgr::Get_Instance()->AddSaveObject(pObj);
				break;
			default:
				break;
			}
		//	cout << iIndex << endl;
		}
		if (CKeyMgr::Get_Instance()->KeyDown('0'))
		{
			m_iObj = 0;
			m_iLowerDrawID++;
			if (m_iLowerDrawID > 7)
				m_iLowerDrawID = 0;
			dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"Dungeon1_LowerDetail", m_iLowerDrawID, 130.f, 130.f, 45, 76, 78);
		}
		else if (CKeyMgr::Get_Instance()->KeyDown('1')) // ΩΩ∂Û¿”
		{
			m_iObj = 1;
			dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"MONSTER_SLIME", 0, 65.f, 50.f, 255, 0, 255);
		}
		else if (CKeyMgr::Get_Instance()->KeyDown('2')) // ∞Ò∑Ω
		{
			m_iObj = 2;
			dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"StoneSoldier_DOWN", 0, 100.f, 100.f, 255, 0, 255);
		}
		else if (CKeyMgr::Get_Instance()->KeyDown('3')) // Tangle
		{
			m_iObj = 3;
			dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"tangle_cycle", 0, 64.f, 64.f, 255, 0, 255);
		}
		else if (CKeyMgr::Get_Instance()->KeyDown('4')) // ∞Ò∑Ω≈Õ∑ø
		{
			m_iObj = 4;
			dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"GolemTurret_shotwalking", 0, 64.f, 64.f, 255, 0, 255);
		}
		else if (CKeyMgr::Get_Instance()->KeyDown('9')) // µπ∏Õ¿ÃµÈ
		{
			m_iObj = 9;
			m_iStoneDrawID++;
			if (m_iStoneDrawID > 10)
				m_iStoneDrawID = 0;
			dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_List(ObjID::MOUSE).front())->ChangeObject(L"obstacles_stone", m_iStoneDrawID, 50.f, 50.f, 255, 0, 255);
		}
	}

	if (CKeyMgr::Get_Instance()->KeyUp('S'))
	{
		CTileMgr::Get_Instance()->SaveTile();
		CObjMgr::Get_Instance()->SaveObj();
	}
	if (CKeyMgr::Get_Instance()->KeyUp('L'))
	{
		CTileMgr::Get_Instance()->LoadTile();
	}
	if (CKeyMgr::Get_Instance()->KeyUp('O'))
	{
		CObjMgr::Get_Instance()->LoadObj();
		CObjMgr::Get_Instance()->Set_StopList(ObjID::MONSTER);
	}
}

void CEditor::MapChange()
{
	if (CKeyMgr::Get_Instance()->KeyDown('Q'))
	{
		CTileMgr::Get_Instance()->Release();
		CObjMgr::Get_Instance()->Release();
		m_pFrameKey = L"shop_background";
		m_pTileKey = L"../Data/Shop_Tile.dat";
		m_pObjKey = L"../Data/Shop_Obj.dat";
		m_iMapCX = 1200;
		m_iMapCY = 900;
		CTileMgr::Get_Instance()->Initialize();
		CTileMgr::Get_Instance()->Set_SaveKey(m_pTileKey);
		CObjMgr::Get_Instance()->Set_ObjKey(m_pObjKey);
		CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	}
	if (CKeyMgr::Get_Instance()->KeyDown('W'))
	{
		CTileMgr::Get_Instance()->Release();
		CObjMgr::Get_Instance()->Release();
		m_pFrameKey = L"Village";
		m_pTileKey = L"../Data/Village_Tile.dat";
		m_pObjKey = L"../Data/Village_Obj.dat";
		m_iMapCX = 2602;
		m_iMapCY = 2134;
		CTileMgr::Get_Instance()->Initialize();
		CTileMgr::Get_Instance()->Set_SaveKey(m_pTileKey);
		CObjMgr::Get_Instance()->Set_ObjKey(m_pObjKey);
		CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	}
	if (CKeyMgr::Get_Instance()->KeyDown('E'))
	{
		CTileMgr::Get_Instance()->Release();
		CObjMgr::Get_Instance()->Release();
		m_pFrameKey = L"room0";
		m_pTileKey = L"../Data/Stage1_Tile.dat";
		m_pObjKey = L"../Data/Stage1_Obj.dat";
		m_iMapCX = 1156;
		m_iMapCY = 783;
		CTileMgr::Get_Instance()->Initialize();
		CTileMgr::Get_Instance()->Set_SaveKey(m_pTileKey);
		CObjMgr::Get_Instance()->Set_ObjKey(m_pObjKey);
		CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	}
	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		CTileMgr::Get_Instance()->Release();
		CObjMgr::Get_Instance()->Release();
		m_pFrameKey = L"Dungeon1_background";
		m_pTileKey = L"../Data/Dungeon1_background_1_Tile.dat";
		m_pObjKey = L"../Data/Dungeon1_background_1_Obj.dat";
		m_iMapCX = 2400;
		m_iMapCY = 1800;
		CTileMgr::Get_Instance()->Initialize();
		CTileMgr::Get_Instance()->Set_SaveKey(m_pTileKey);
		CObjMgr::Get_Instance()->Set_ObjKey(m_pObjKey);
		CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	}
	if (CKeyMgr::Get_Instance()->KeyDown('T'))
	{
		CTileMgr::Get_Instance()->Release();
		CObjMgr::Get_Instance()->Release();
		m_pFrameKey = L"Tutorial_background";
		m_pTileKey = L"../Data/Tutorial_background_Tile.dat";
		m_pObjKey = L"../Data/Tutorial_background_Obj.dat";
		m_iMapCX = 1600;
		m_iMapCY = 600;
		CTileMgr::Get_Instance()->Initialize();
		CTileMgr::Get_Instance()->Set_SaveKey(m_pTileKey);
		CObjMgr::Get_Instance()->Set_ObjKey(m_pObjKey);
		CObjMgr::Get_Instance()->AddObject(ObjID::MOUSE, CAbstractFactory<CMouse>::Create());
	}
}
