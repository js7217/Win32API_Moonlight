#pragma once
#include "Obj.h"
class CRightWall :
	public CObj
{
public:
	CRightWall();
	virtual ~CRightWall();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

