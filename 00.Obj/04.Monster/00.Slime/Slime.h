#pragma once
#include "Monster.h"
class CSlime :
	public CMonster
{
public:
	CSlime();
	virtual ~CSlime();

	// CMonster��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void MotionChange();
private:
	bool m_bIsHit;
};

