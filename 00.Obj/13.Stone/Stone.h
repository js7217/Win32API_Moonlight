#pragma once
#include "Obj.h"
class CStone :
	public CObj
{
public:
	CStone();
	virtual ~CStone();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

