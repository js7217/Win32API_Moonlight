#pragma once
#include "Obj.h"
class CAlert :
	public CObj
{
public:
	CAlert();
	virtual ~CAlert();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD m_dwOldTime;
};

