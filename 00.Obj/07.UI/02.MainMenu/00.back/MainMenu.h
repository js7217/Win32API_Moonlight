#pragma once
#include "Obj.h"
class CMainMenu :
	public CObj
{
public:
	CMainMenu();
	virtual ~CMainMenu();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

