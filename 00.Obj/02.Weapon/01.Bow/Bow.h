#pragma once
#include "Obj.h"
class CBow :
	public CObj
{
public:
	CBow();
	virtual ~CBow();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MotionChange();
};

