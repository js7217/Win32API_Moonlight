#pragma once
#include "Obj.h"
class CBigSword :
	public CObj
{
public:
	CBigSword();
	virtual ~CBigSword();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	bool m_bIsBullet;
	void MotionChange();
	void CreateBullet();
};

