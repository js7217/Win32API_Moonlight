#pragma once
#include "Obj.h"
class CMainMenu_front :
	public CObj
{
public:
	CMainMenu_front();
	virtual ~CMainMenu_front();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

