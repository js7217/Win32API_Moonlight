#pragma once
#include "Bullet.h"
class CGolemBullet :
	public CBullet
{
public:
	CGolemBullet();
	virtual ~CGolemBullet();

	// CBullet을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_fDist;
	DWORD m_dwOldTime;
};

