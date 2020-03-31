#pragma once
#include "Monster.h"
class CStoneSoldier :
	public CMonster
{
public:
	CStoneSoldier();
	virtual ~CStoneSoldier();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MotionChange();
	void FollowPlayer();
	void CreateBullet();
private:
	bool m_bIsBullet;
	bool m_bIsHit;
};

