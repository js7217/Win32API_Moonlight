#pragma once
#include "Obj.h"
class CTutorial :
	public CObj
{
public:
	CTutorial();
	virtual ~CTutorial();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD m_dwOldTime;
};

