#pragma once
#include "Obj.h"
class CMainMenu_front :
	public CObj
{
public:
	CMainMenu_front();
	virtual ~CMainMenu_front();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

