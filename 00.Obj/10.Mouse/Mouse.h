#pragma once
#include "Obj.h"
class CMouse :
	public CObj
{
public:
	CMouse();
	virtual ~CMouse();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void ChangeObject(TCHAR* pFrameKey, int iDrawID, float fCX, float fCY, int iRed, int iGreen, int iBlue);

private:
	int m_iDrawID;
	int m_iRed;
	int m_iGreen;
	int m_iBlue;
};
