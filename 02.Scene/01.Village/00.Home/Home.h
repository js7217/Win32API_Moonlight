#pragma once
#include "Scene.h"
class CHome :
	public CScene
{
public:
	CHome();
	virtual ~CHome();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

