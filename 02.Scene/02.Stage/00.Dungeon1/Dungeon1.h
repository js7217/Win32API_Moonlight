#pragma once
#include "Scene.h"
class CDungeon1 :
	public CScene
{
public:
	CDungeon1();
	virtual ~CDungeon1();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

