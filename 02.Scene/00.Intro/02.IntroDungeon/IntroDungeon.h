#pragma once
#include "Scene.h"
class CIntroDungeon :
	public CScene
{
public:
	CIntroDungeon();
	virtual ~CIntroDungeon();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

