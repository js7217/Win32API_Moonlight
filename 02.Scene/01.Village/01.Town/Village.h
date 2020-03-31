#pragma once
#include "Scene.h"
class CVillage :
	public CScene
{
public:
	CVillage();
	virtual ~CVillage();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

