#pragma once
#include "Monster.h"
class CStoneSoldier :
	public CMonster
{
public:
	CStoneSoldier();
	virtual ~CStoneSoldier();

	// CMonster��(��) ���� ��ӵ�
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

