#pragma once
#include "Obj.h"
class CPunchShadow :
	public CObj
{
public:
	CPunchShadow();
	virtual ~CPunchShadow();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool m_bIsStop;
	bool m_bIsPunch;
	DWORD m_dwOldTime;
};

