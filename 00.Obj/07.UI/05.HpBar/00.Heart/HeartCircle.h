#pragma once
#include "Obj.h"
class CHeartCircle :
	public CObj
{
public:
	CHeartCircle();
	virtual ~CHeartCircle();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD m_dwOldTime;
};

