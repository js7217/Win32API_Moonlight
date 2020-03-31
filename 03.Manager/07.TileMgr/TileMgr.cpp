#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "Player.h"
#include "Scene.h"
#include "GolemDoor.h"
#include "BossDoor.h"
#include "Hole.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
IMPLEMENT_SINGLETON(CTileMgr)

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	m_iDrawID = 0;
	m_iOptionID = 0;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = (j * TILECX) + (TILECX * 0.5f);
			float fY = (i * TILECY) + (TILECY * 0.5f);
			CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.emplace_back(pTile);
		}
	}
}

void CTileMgr::Update()
{
	PlayerList = CObjMgr::Get_Instance()->Get_List(ObjID::PLAYER);
	MonsterList = CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER);
	MonsterBulletList = CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER_BULLET);
	if (PlayerList.empty())
		return;
	// 좌상단
	int iCullX = abs(CScrollMgr::Get_ScrollX() / TILECX);
	int iCullY = abs(CScrollMgr::Get_ScrollY() / TILECY);

	// 우하단 
	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;

	for (int i = iCullY; i < iCullEndY + 2; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (i * TILEX);
			if (0 > iIndex || m_vecTile.size() <= iIndex)
				continue;
			m_vecTile[iIndex]->Update();
			CollisionTile(m_vecTile[iIndex], PlayerList);
			CollisionTile(m_vecTile[iIndex], MonsterList);
			CollisionBullet(m_vecTile[iIndex], MonsterBulletList);
		}
	}
}

void CTileMgr::LateUpdate()
{
	int iCullX = abs(CScrollMgr::Get_ScrollX() / TILECX);
	int iCullY = abs(CScrollMgr::Get_ScrollY() / TILECY);

	// 우하단 
	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;

	for (int i = iCullY; i < iCullEndY + 2; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (i * TILEX);
			if (0 > iIndex || m_vecTile.size() <= iIndex)
				continue;
			m_vecTile[iIndex]->LateUpdate();
		}
	}
}

void CTileMgr::Render(HDC hDC)
{
	// 좌상단
	int iCullX = abs(CScrollMgr::Get_ScrollX() / TILECX);
	int iCullY = abs(CScrollMgr::Get_ScrollY() / TILECY);

	// 우하단 
	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;

	for (int i = iCullY; i < iCullEndY + 2; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (i * TILEX);
			if (0 > iIndex || m_vecTile.size() <= iIndex)
				continue;
			m_vecTile[iIndex]->Render(hDC);
		}
	}
}

void CTileMgr::Release()
{
	for (auto& pTile : m_vecTile)
	{
		Safe_Delete(pTile);
	}
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}


void CTileMgr::CollisionTile(CObj *& rTile,OBJLIST& rList)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	
	int iOption = dynamic_cast<CTile*>(rTile)->Get_Option();
	if (0 == iOption)
		return;
	for (auto& pObj : rList)
	{
		if (CheckRect(pObj, rTile, &fMoveX, &fMoveY))
		{
			float x = pObj->Get_Info().fX;
			float y = pObj->Get_Info().fY;
			switch (iOption)
			{
			case 1: // 벽
				if (fMoveX > fMoveY)
				{
					if (y < rTile->Get_Info().fY)
						fMoveY *= -1.f;
					pObj->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < rTile->Get_Info().fX)
						fMoveX *= -1.f;
					pObj->Set_Pos(x + fMoveX, y);
				}
				break;
			case 2: // 다음맵
				CSceneMgr::Get_Instance()->Get_Scene()->Set_Option(2);
				break;
			case 3: // 위
				if (pObj->Get_ObjID() == ObjID::PLAYER)
				{
					pObj->Set_Pos(pObj->Get_Info().fX, pObj->Get_Info().fY + 300.f);
					dynamic_cast<CPlayer*>(pObj)->Set_Scroll(CScrollMgr::Get_ScrollY(), -WINCY, 1);
				}
				break;
			case 4: // 아래
				if (pObj->Get_ObjID() == ObjID::PLAYER)
				{
					pObj->Set_Pos(pObj->Get_Info().fX, pObj->Get_Info().fY - 300.f);
					dynamic_cast<CPlayer*>(pObj)->Set_Scroll(CScrollMgr::Get_ScrollY(), WINCY, 1);
				}
				break;
			case 5: // 왼쪽
				if (pObj->Get_ObjID() == ObjID::PLAYER)
				{
					pObj->Set_Pos(pObj->Get_Info().fX + 300.f, pObj->Get_Info().fY);
					dynamic_cast<CPlayer*>(pObj)->Set_Scroll(CScrollMgr::Get_ScrollX(), -WINCX, -1);
				}
				break;
			case 6: // 오른쪽
				if (pObj->Get_ObjID() == ObjID::PLAYER)
				{
					pObj->Set_Pos(pObj->Get_Info().fX - 300.f, pObj->Get_Info().fY);
					dynamic_cast<CPlayer*>(pObj)->Set_Scroll(CScrollMgr::Get_ScrollX(), WINCX, -1);
				}
				break;
			case 7: // 이전맵
				CSceneMgr::Get_Instance()->Get_Scene()->Set_Option(7);
				break;
			case 8:
				if (pObj->Get_ObjID() == ObjID::PLAYER)
				{
					pObj->Set_Init();
				}
				break;
			default:
				break;
			}
		}
	}
}

void CTileMgr::CollisionBullet(CObj *& rTile, OBJLIST & rList)
{
	RECT rc = {};
	if (MonsterBulletList.empty())
		return;

	int iOption = dynamic_cast<CTile*>(rTile)->Get_Option();
	if (0 == iOption)
		return;
	for (auto& pObj : rList)
	{
		if (IntersectRect(&rc, &rTile->Get_CollisionRect(), &pObj->Get_CollisionRect()))
		{
			if (1 == iOption)
			{
				pObj->Set_Dead();
			}
		}
	}
}

void CTileMgr::PickTile(const POINT & pt, int iDrawID, int iOption)
{
	int x = pt.x / TILECX;
	int y = pt.y / TILECY;

	int iIndex = x + (TILEX * y)/*j + (i * iSize)*/;

	if (0 > iIndex || m_vecTile.size() <= iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(m_iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(m_iOptionID);
}

void CTileMgr::ChangeTile(int iDrawID, int iOptionID)
{
	m_iDrawID = iDrawID;
	m_iOptionID = iOptionID;
}

void CTileMgr::SaveTile()
{
	HANDLE hFile = CreateFile(m_pTileKey, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	assert(!(INVALID_HANDLE_VALUE == hFile));

	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장성공!!", L"Save", MB_OK);
}

void CTileMgr::LoadTile()
{
	HANDLE hFile = CreateFile(m_pTileKey, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	assert(!(INVALID_HANDLE_VALUE == hFile));

	INFO tInfo = {};
	int iDrawID = 0;
	int iOption = 0;
	DWORD dwByte = 0;

	if (!m_vecTile.empty())
	{
		Release();
	}
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
		CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

		m_vecTile.emplace_back(pTile);

		switch (iDrawID)
		{
		case 3:				// 위
			CObjMgr::Get_Instance()->AddObject(ObjID::DOOR, CAbstractFactory<CGolemDoor>::Create(tInfo.fX, tInfo.fY, CObj::UP));
			break;
		case 4:				// 아래
			CObjMgr::Get_Instance()->AddObject(ObjID::DOOR, CAbstractFactory<CGolemDoor>::Create(tInfo.fX, tInfo.fY, CObj::DOWN));
			break;
		case 5:				// 왼쪽
			CObjMgr::Get_Instance()->AddObject(ObjID::DOOR, CAbstractFactory<CGolemDoor>::Create(tInfo.fX, tInfo.fY, CObj::LEFT));
			break;
		case 6:				//오른쪽
			CObjMgr::Get_Instance()->AddObject(ObjID::DOOR, CAbstractFactory<CGolemDoor>::Create(tInfo.fX, tInfo.fY, CObj::RIGHT));
			break;
		case 8:				// 보스 문
			CObjMgr::Get_Instance()->AddObject(ObjID::DOOR, CAbstractFactory<CBossDoor>::Create(tInfo.fX, tInfo.fY));
			break;
		case 9:				// 밑 구덩이
			CObjMgr::Get_Instance()->AddObject(ObjID::HOLE, CAbstractFactory<CHole>::Create(tInfo.fX, tInfo.fY, 9, 0));
			break;
		case 10:			// 그라데이션 구덩이.
			CObjMgr::Get_Instance()->AddObject(ObjID::HOLE, CAbstractFactory<CHole>::Create(tInfo.fX, tInfo.fY, 10, 1));
			break;
		default:
			break;
		}
	}
	CloseHandle(hFile);
}

bool CTileMgr::CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY)
{
	float fRadSumX = (pDst->Get_Info().fCollisionCX + pSrc->Get_Info().fCX) * 0.5f;
	float fRadSumY = (pDst->Get_Info().fCollisionCY + pSrc->Get_Info().fCY) * 0.5f;

	float fDistX = fabs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float fDistY = fabs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	if (fRadSumX >= fDistX && fRadSumY >= fDistY)
	{
		*pMoveX = fRadSumX - fDistX;
		*pMoveY = fRadSumY - fDistY;
		return true;
	}
	return false;
}
