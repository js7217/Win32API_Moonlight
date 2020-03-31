#pragma once
#include "Obj.h"
#include "Player.h"
class CWeaponCircle :
	public CObj
{
public:
	CWeaponCircle();
	virtual ~CWeaponCircle();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	CPlayer::ATT_STATE m_eCurAttState;
};

