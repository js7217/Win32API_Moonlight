#pragma once
#include "Scene.h"
class CIntroDungeon :
	public CScene
{
public:
	CIntroDungeon();
	virtual ~CIntroDungeon();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

