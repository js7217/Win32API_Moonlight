#pragma once
#include "Obj.h"
class CLowerDetail :
	public CObj
{
public:
	CLowerDetail();
	virtual ~CLowerDetail();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

