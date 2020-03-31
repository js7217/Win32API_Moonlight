#pragma once
#include "Obj.h"
class CRockShadow :
	public CObj
{
public:
	CRockShadow();
	virtual ~CRockShadow();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	static int m_iCnt;
private:
	bool m_bIsRock;
	DWORD m_dwOldTime;
};

