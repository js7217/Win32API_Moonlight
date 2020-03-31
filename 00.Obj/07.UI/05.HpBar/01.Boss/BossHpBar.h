#pragma once
#include "Obj.h"
class CBossHpBar :
	public CObj
{
public:
	CBossHpBar();
	virtual ~CBossHpBar();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	float m_iDamageUI;
	float m_fMaxfCX;
	float m_fHpBarCX;
	float m_fHpBarCY;
	float m_fSlideCX;
	DWORD m_dwOldTime;
};

