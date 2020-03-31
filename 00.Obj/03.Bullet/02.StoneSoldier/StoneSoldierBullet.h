#pragma once
#include "Bullet.h"
class CStoneSoldierBullet :
	public CBullet
{
public:
	CStoneSoldierBullet();
	CStoneSoldierBullet(float fX, float fY, float fCX, float fCY);
	virtual ~CStoneSoldierBullet();

	// CBullet��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	DWORD m_dwOldTime;
};

