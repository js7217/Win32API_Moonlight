#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
};

