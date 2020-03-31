#pragma once
#include "Obj.h"
class CBoss :
	public CObj
{
public:
	CBoss();
	virtual ~CBoss();

public:
	virtual void Initialize() = 0;
	virtual int  Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
public:
	float Target_Angle();
protected:
	DWORD m_dwOldTime;
	DWORD m_dwTime;
};

