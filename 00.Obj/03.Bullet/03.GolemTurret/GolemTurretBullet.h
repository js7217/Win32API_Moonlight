#pragma once
#include "Bullet.h"
class CGolemTurretBullet :
	public CBullet
{
public:
	CGolemTurretBullet();
	CGolemTurretBullet(CObj::ROTATE eRotate);
	virtual ~CGolemTurretBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

