#pragma once
#include "Obj.h"
class CSortY :
	public CObj
{
public:
	CSortY();
	CSortY(float fX, float fY, float fCX, float fCY);
	virtual ~CSortY();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

