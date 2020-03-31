#pragma once
#include "Obj.h"
class CAlert :
	public CObj
{
public:
	CAlert();
	virtual ~CAlert();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD m_dwOldTime;
};

