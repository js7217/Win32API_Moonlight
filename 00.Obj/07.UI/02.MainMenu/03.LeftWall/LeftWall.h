#pragma once
#include "Obj.h"
class CLeftWall :
	public CObj
{
public:
	CLeftWall();
	virtual ~CLeftWall();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

