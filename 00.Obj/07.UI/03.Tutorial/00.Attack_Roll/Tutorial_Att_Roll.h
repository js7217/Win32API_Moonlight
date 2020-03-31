#pragma once
#include "Obj.h"
class CTutorial_Att_Roll :
	public CObj
{
public:
	CTutorial_Att_Roll();
	virtual ~CTutorial_Att_Roll();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

