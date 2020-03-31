#pragma once
#include "Scene.h"
class CHome :
	public CScene
{
public:
	CHome();
	virtual ~CHome();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

