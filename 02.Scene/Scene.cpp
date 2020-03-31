#include "stdafx.h"
#include "Scene.h"
#include "ObjMgr.h"
bool CScene::m_bInit = false;
CScene::CScene()
	:m_iOption(0)
	,m_iMapCX(0)
	,m_iMapCY(0)
	,m_bIsBoss(FALSE)
{
}


CScene::~CScene()
{
}

void CScene::Create_Boss(CObj * pBoss)
{
	if (m_bIsBoss == false && CObjMgr::Get_Instance()->Get_List(ObjID::MONSTER).empty())
	{
		CObjMgr::Get_Instance()->AddObject(ObjID::BOSS, pBoss);
		m_bIsBoss = true;
	}
}

void CScene::LateInitialize()
{
	if (!m_bInit)
	{
		this->LateInitialize();
		m_bInit = true;
	}
}
