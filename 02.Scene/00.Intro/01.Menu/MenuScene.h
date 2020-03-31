#pragma once
#include "Scene.h"
class CMenuScene :
	public CScene
{
public:
	CMenuScene();
	virtual ~CMenuScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void Set_NextScene(int iNext) { m_iNextScene = iNext; }
private:
	int m_iNextScene;
};

