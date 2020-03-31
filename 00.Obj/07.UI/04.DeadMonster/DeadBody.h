#pragma once
#include "Obj.h"
class CDeadBody :
	public CObj
{
public:
	CDeadBody();
	CDeadBody(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey);
	virtual ~CDeadBody();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	DWORD m_dwOldTime;
};

