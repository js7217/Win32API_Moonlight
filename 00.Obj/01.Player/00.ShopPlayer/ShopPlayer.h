#pragma once
#include "Obj.h"
class CShopPlayer :
	public CObj
{
public:
	CShopPlayer();
	virtual ~CShopPlayer();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void KeyCheck();
	void MotionChange();
	void IsJumping();
	void IsOffSet();
public:
	void Set_IsOffset(bool bIsOffset) { m_bIsOffset = bIsOffset; }
private:
	bool m_bIsJump;
	bool m_bIsOffset;
};

