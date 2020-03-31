#pragma once
#include "Obj.h"
class CGloves :
	public CObj
{
public:
	CGloves();
	virtual ~CGloves();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	bool m_bIsBullet;
	void MotionChange();
	void CreateBullet();
};

