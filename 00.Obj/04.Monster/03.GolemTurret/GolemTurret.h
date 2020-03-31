#pragma once
#include "Monster.h"
class CGolemTurret :
	public CMonster
{
public:
	CGolemTurret();
	virtual ~CGolemTurret();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MotionChange();
	void CreateBullet();
private:
	bool m_bIsBullet;
	CObj::ROTATE m_ePreRotate;
	DWORD m_dwBulletTime;
};

