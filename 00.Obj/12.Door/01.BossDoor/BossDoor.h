#pragma once
#include "Obj.h"
class CBossDoor :
	public CObj
{
public:
	CBossDoor();
	virtual ~CBossDoor();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MotionChange();
};

