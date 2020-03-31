#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	CEffect();
	CEffect(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey, int iFrameend);
	virtual ~CEffect();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

