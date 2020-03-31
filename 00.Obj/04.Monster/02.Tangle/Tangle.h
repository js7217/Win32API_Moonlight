#pragma once
#include "Monster.h"
class CTangle :
	public CMonster
{
public:
	CTangle();
	virtual ~CTangle();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	bool m_bIsHit;
};

