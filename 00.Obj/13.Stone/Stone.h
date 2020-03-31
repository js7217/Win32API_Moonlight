#pragma once
#include "Obj.h"
class CStone :
	public CObj
{
public:
	CStone();
	virtual ~CStone();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

