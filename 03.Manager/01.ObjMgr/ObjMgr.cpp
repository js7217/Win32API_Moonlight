#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Slime.h"
#include "Stone.h"
#include "Tangle.h"
#include "GolemTurret.h"
#include "LowerDetail.h"
#include "StoneSoldier.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Set_StopList(ObjID::ID eID)
{
	OBJITER iter = m_ObjList[eID].begin();
	for (; iter != m_ObjList[eID].end(); ++iter)
	{
		(*iter)->Set_Speed(0.f);
	}
}

void CObjMgr::AddObject(ObjID::ID eID, CObj * pObj)
{
	m_ObjList[eID].emplace_back(pObj);
}

void CObjMgr::AddSaveObject(CObj * pObj)
{
	m_SaveObjList.emplace_back(pObj);
}

void CObjMgr::DeleteID(ObjID::ID eID)
{
	OBJITER iter = m_ObjList[eID].begin();
	for (; iter != m_ObjList[eID].end(); )
	{
		if (*iter)
		{
			delete *iter;
			iter = m_ObjList[eID].erase(iter);
		}
		else
			++iter;
	}
	m_ObjList[eID].clear();
}

int CObjMgr::Update()
{
	for (int i = 0; i < ObjID::END; ++i)
	{
		OBJITER iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return OBJ_NOEVENT;
}

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < ObjID::END; ++i)
	{
		OBJITER iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->LateUpdate();
			if (m_ObjList[i].empty())
			{
				break;
			}
			GroupID::ID eID = (*iter)->Get_GroupID();
			// ���⼭ �׷� ���̵�� ����Ʈ�� ���� ������Ʈ��. 
			m_RenderList[eID].emplace_back(*iter);
		}
	}
	// CollisionRect : �Ѿ� vs ���� or ����
	// CollisionRectExtra : ������ �ȹи��� ������
	// CollisionRectMonster : ����(����) vs �÷��̾� - hit�ɶ�.
	// CollisionRectHole : �÷��̾�, ���� vs ������
	// CollisionRectStone : �÷��̾�, ���� vs ����
	CCollisionMgr::CollisionRect(m_ObjList[ObjID::PLAYER_BULLET], m_ObjList[ObjID::MONSTER]);
	CCollisionMgr::CollisionRect(m_ObjList[ObjID::PLAYER_BULLET], m_ObjList[ObjID::BOSS_BULLET]);
	CCollisionMgr::CollisionRect(m_ObjList[ObjID::PLAYER_BULLET], m_ObjList[ObjID::BOSS]);
	CCollisionMgr::CollisionRect(m_ObjList[ObjID::MONSTER_BULLET], m_ObjList[ObjID::PLAYER]);

	CCollisionMgr::CollisionRectBoss(m_ObjList[ObjID::BOSS_ARM], m_ObjList[ObjID::PLAYER]);

	CCollisionMgr::CollisionRectExtra(m_ObjList[ObjID::PLAYER], m_ObjList[ObjID::BOSS_BULLET]);
	CCollisionMgr::CollisionRectExtra(m_ObjList[ObjID::PLAYER], m_ObjList[ObjID::BOSS]);
	CCollisionMgr::CollisionRectExtra(m_ObjList[ObjID::PLAYER], m_ObjList[ObjID::DOOR]);
	CCollisionMgr::CollisionRectExtra(m_ObjList[ObjID::PLAYER], m_ObjList[ObjID::STONE]);
	CCollisionMgr::CollisionRectExtra(m_ObjList[ObjID::MONSTER], m_ObjList[ObjID::STONE]);

	CCollisionMgr::CollisionRectMonster(m_ObjList[ObjID::MONSTER], m_ObjList[ObjID::PLAYER]);

	CCollisionMgr::CollisionRectStone(m_ObjList[ObjID::MONSTER_BULLET], m_ObjList[ObjID::STONE]);

	CCollisionMgr::CollisionRectHole(m_ObjList[ObjID::PLAYER], m_ObjList[ObjID::HOLE]);
	CCollisionMgr::CollisionRectHole(m_ObjList[ObjID::MONSTER], m_ObjList[ObjID::HOLE]);



}

void CObjMgr::Render(HDC hDC)
{
	//for (int i = 0; i < ObjID::END; ++i)
	//{
	//	for (auto& pObj : m_ObjList[i])
	//		pObj->Render(hDC);
	//}
	for (int i = 0; i < GroupID::END; ++i)
	{
		m_RenderList[i].sort([](auto& rDst, auto& rSrc)
		{
			return rDst->Get_Info().fY < rSrc->Get_Info().fY;
		});

		for (auto& pObj : m_RenderList[i])
		{
			pObj->Render(hDC);
		}
		// ��������Ʈ�� ����µ� ���Ҵ� ����� �ȵȴ� ���� ! �� ? ��������Ʈ�� ���Ҹ� safe_delete�ϴ¼��� �ż��踦 ���� �Ҥ���� 
		// �̰� ���״�� �׷��ֱ� ���� �����ϴ� ����Ʈ�⶧���� �������� ������� �ȵ�. 
		m_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < ObjID::END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), [](CObj*& rObj)
		{
			if (nullptr != rObj)
			{
				delete rObj;
				rObj = nullptr;
			}
		});
		m_ObjList[i].clear();
	}
}

void CObjMgr::SaveObj()
{
	HANDLE hFile = CreateFile(m_pObjKey, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	assert(!(INVALID_HANDLE_VALUE == hFile));

	int iOption = 0;
	int iDrawID = 0;
	int iIndex = 0;
	DWORD dwByte = 0;

	for (auto& pObj : m_SaveObjList)
	{
		iOption = pObj->Get_Option();
		iDrawID = pObj->Get_DrawID();
		iIndex = pObj->Get_Index();
		WriteFile(hFile, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"���强��!!(Obj)", L"Save", MB_OK);
}

void CObjMgr::LoadObj()
{
	HANDLE hFile = CreateFile(m_pObjKey, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
//	assert(!(INVALID_HANDLE_VALUE == hFile));

	INFO tInfo = {};
	int iOption = 0;
	int iDrawID = 0;
	int iIndex = 0;
	DWORD dwByte = 0;
	CObj* pObj = nullptr;
	if (!m_ObjList->empty())
		Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		switch (iOption)
		{
		case 0:	// �ٴ� UI
			pObj = CAbstractFactory<CLowerDetail>::Create(tInfo.fX, tInfo.fY);
			pObj->Set_DrawID(iDrawID);
			pObj->Set_Option(iOption);
			pObj->Set_Index(iIndex);
			AddObject(ObjID::LOWERDETAIL, pObj);
			m_SaveObjList.emplace_back(pObj);
			break;
		case 1: // ������
			pObj = CAbstractFactory<CSlime>::Create(tInfo.fX, tInfo.fY);
			pObj->Set_Option(iOption);
			pObj->Set_Index(iIndex);
			AddObject(ObjID::MONSTER, pObj);
			m_SaveObjList.emplace_back(pObj); // ���� �ּҰ������� ���� ����Ʈ���� �־�־� �ҷ��°� �ٽ� �����Ҷ� ������ �Ȼ����.
			break;
		case 2: // ��
			pObj = CAbstractFactory<CStoneSoldier>::Create(tInfo.fX, tInfo.fY);
			pObj->Set_Option(iOption);
			pObj->Set_Index(iIndex);
			AddObject(ObjID::MONSTER, pObj);
			m_SaveObjList.emplace_back(pObj);
			break;
		case 3: // Tangle
			pObj = CAbstractFactory<CTangle>::Create(tInfo.fX, tInfo.fY);
			pObj->Set_Option(iOption);
			pObj->Set_Index(iIndex);
			AddObject(ObjID::MONSTER, pObj);
			m_SaveObjList.emplace_back(pObj);
			break;
		case 4: // ���ͷ�
			pObj = CAbstractFactory<CGolemTurret>::Create(tInfo.fX, tInfo.fY);
			pObj->Set_Option(iOption);
			pObj->Set_Index(iIndex);
			AddObject(ObjID::MONSTER, pObj);
			m_SaveObjList.emplace_back(pObj);
			break;
		case 9:	// �� ���� �ִ� �����
			pObj = CAbstractFactory<CStone>::Create(tInfo.fX, tInfo.fY);
			pObj->Set_DrawID(iDrawID);
			pObj->Set_Option(iOption);
			pObj->Set_Index(iIndex);
			AddObject(ObjID::STONE, pObj);
			m_SaveObjList.emplace_back(pObj);
			break;
		default:
			break;
		}
	}
	CloseHandle(hFile);
}
