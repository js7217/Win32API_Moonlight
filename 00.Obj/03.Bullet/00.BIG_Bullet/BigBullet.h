#pragma once
#include "Bullet.h"
class CBigBullet :
	public CBullet
{
public:
	CBigBullet();
	CBigBullet(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey);
	virtual ~CBigBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

