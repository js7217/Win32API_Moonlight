#pragma once
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();
public:
	static void CollisionRect(OBJLIST& rDst, OBJLIST& rSrc);
	static void CollisionRectExtra(OBJLIST& rDst, OBJLIST& rSrc);
	static void CollisionRectMonster(OBJLIST& rDst, OBJLIST& rSrc);
	static void CollisionRectBoss(OBJLIST& rDst, OBJLIST& rSrc);
	static void CollisionRectStone(OBJLIST& rDst, OBJLIST& rSrc);
	static void CollisionRectHole(OBJLIST& rDst, OBJLIST& rSrc);
private:
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
};

