#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Player.h"
#include "ObjMgr.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(OBJLIST & rDst, OBJLIST & rSrc) // 무기 , 맞는 상대
{
	RECT rc = {};
	for (auto& rDestObj : rDst)
	{
		if (rDestObj->Get_IsCollision() || rDestObj->Get_State() != CObj::ATTACK) // 무기가 한번 맞았으면 더이상 안맞게 해줘야한다.
			continue;
		for (auto& rSourceObj : rSrc)
		{
			if (rSourceObj->Get_State() == CObj::STATE::DEAD)
				return;
			if (rSourceObj->Get_ObjID() == ObjID::PLAYER) // 맞는 상대가 플레이어일 경우 조건.
			{
				if (rSourceObj->Get_IsCollision() || rSourceObj->Get_IsJump())
					return;
			}
			if (IntersectRect(&rc, &rDestObj->Get_CollisionRect(), &rSourceObj->Get_CollisionRect()))
			{
				int iDstAtt = rDestObj->Get_Att();
				rSourceObj->Set_Hp(iDstAtt);
				rSourceObj->Set_State(CObj::STATE::HIT);
				rSourceObj->Set_IsCollision(true);
				rDestObj->Set_IsCollision(true);
				rDestObj->Set_Dead();
				if(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Shake() == false)
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Shake();
				if (rSourceObj->Get_Hp() <= 0)
					rSourceObj->Set_State(CObj::STATE::DEAD);
			}
		}
	}
}

void CCollisionMgr::CollisionRectExtra(OBJLIST & rDst, OBJLIST & rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pSourceObj : rSrc)
	{
		if (!pSourceObj->Get_IsCollisionExtra())
			continue;
		for (auto& pDestObj : rDst)
		{
			if (CheckRect(pDestObj, pSourceObj, &fMoveX, &fMoveY))
			{
				float x = pDestObj->Get_Info().fX;
				float y = pDestObj->Get_Info().fY;
				if (fMoveX > fMoveY)
				{
					if (y < pSourceObj->Get_Info().fY)
						fMoveY *= -1.f;
					pDestObj->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < pSourceObj->Get_Info().fX)
						fMoveX *= -1.f;
					pDestObj->Set_Pos(x + fMoveX, y);
				}
			}
		}
	}
}

void CCollisionMgr::CollisionRectMonster(OBJLIST & rDst, OBJLIST & rSrc) // 몬스터와 플레이어의 충돌
{
	RECT rc = {};
	for (auto& rSourceObj : rSrc)
	{
		if (rSourceObj->Get_IsCollision() || rSourceObj->Get_IsJump())
			return;
		if (rSourceObj->Get_State() == CObj::STATE::DEAD)
			return;
		for (auto& rDestObj : rDst)
		{
			if (rDestObj->Get_State() == CObj::DEAD)
				continue;
			if (IntersectRect(&rc, &rDestObj->Get_CollisionRect(), &rSourceObj->Get_CollisionRect()))
			{
				rDestObj->Set_State(CObj::ATTACK);
				int iDstAtt = rDestObj->Get_Att();
				if (iDstAtt > 0)
				{
					rSourceObj->Set_Hp(iDstAtt);
					rSourceObj->Set_IsCollision(true);
					rSourceObj->Set_State(CObj::HIT);
				}
				if (rSourceObj->Get_Hp() <= 0)
					rSourceObj->Set_State(CObj::STATE::DEAD);
			}
		}
	}
}

void CCollisionMgr::CollisionRectBoss(OBJLIST & rDst, OBJLIST & rSrc)	// 보스 팔 vs 플레이어.
{
	RECT rc = {};
	for (auto& rDestObj : rDst)
	{
		if (rDestObj->Get_IsCollision() || rDestObj->Get_State() != CObj::ATTACK) // 무기가 한번 맞았으면 더이상 안맞게 해줘야한다.
			continue;
		for (auto& rSourceObj : rSrc)
		{
			if (rSourceObj->Get_State() == CObj::STATE::DEAD)
				return;
			if (rSourceObj->Get_ObjID() == ObjID::PLAYER) // 맞는 상대가 플레이어일 경우 조건.
			{
				if (rSourceObj->Get_IsCollision() || rSourceObj->Get_IsJump())
					return;
			}
			if (IntersectRect(&rc, &rDestObj->Get_CollisionRect(), &rSourceObj->Get_CollisionRect()))
			{
				int iDstAtt = rDestObj->Get_Att();
				rSourceObj->Set_Hp(iDstAtt);
				rSourceObj->Set_State(CObj::STATE::HIT);
				rSourceObj->Set_IsCollision(true);
				rDestObj->Set_IsCollision(true);

				if (rSourceObj->Get_Hp() <= 0)
					rSourceObj->Set_State(CObj::STATE::DEAD);
			}
		}
	}
}

void CCollisionMgr::CollisionRectStone(OBJLIST & rDst, OBJLIST & rSrc) // 몬스터 총알과 돌 사이의 충돌 검사
{
	RECT rc = {};
	for (auto& rSourceObj : rSrc)
	{
		for (auto& rDestObj : rDst)
		{
			if (IntersectRect(&rc, &rDestObj->Get_CollisionRect(), &rSourceObj->Get_CollisionRect()))
			{
				rDestObj->Set_IsCollision(true);
				rDestObj->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::CollisionRectHole(OBJLIST & rDst, OBJLIST & rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto& pDestObj : rDst)
	{
		if (pDestObj->Get_IsJump())
			continue;
		for (auto& pSourceObj : rSrc)
		{
			if (CheckRect(pDestObj, pSourceObj, &fMoveX, &fMoveY))
			{
				float x = pDestObj->Get_Info().fX;
				float y = pDestObj->Get_Info().fY;
				if (fMoveX > fMoveY)
				{
					if (y < pSourceObj->Get_Info().fY)
						fMoveY *= -1.f;
					pDestObj->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < pSourceObj->Get_Info().fX)
						fMoveX *= -1.f;
					pDestObj->Set_Pos(x + fMoveX, y);
				}
			}
		}
	}
}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float fRadSumX = (pDst->Get_Info().fCollisionCX + pSrc->Get_Info().fCollisionCX) * 0.5f;
	float fRadSumY = (pDst->Get_Info().fCollisionCY + pSrc->Get_Info().fCollisionCY) * 0.5f;

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
