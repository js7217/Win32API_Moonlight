#pragma once
#include "Obj.h"
class CGolemDoor :
	public CObj
{
public:
	CGolemDoor();
	CGolemDoor(CObj::ROTATE eRotate);
	virtual ~CGolemDoor();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MotionChange();
};

