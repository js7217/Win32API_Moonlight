#pragma once
#include "Bullet.h"
class CBigBullet :
	public CBullet
{
public:
	CBigBullet();
	CBigBullet(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey);
	virtual ~CBigBullet();

	// CBullet을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

