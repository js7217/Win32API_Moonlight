#pragma once
class CObj;
template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fX, float fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		return pObj;
	}
	static CObj* Create(float fX, float fY, int iOption, int iDrawID)  // Lower
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		pObj->Set_Option(iOption);
		pObj->Set_DrawID(iDrawID);
		return pObj;
	}
	static CObj* Create(float fX, float fY, CObj::ROTATE iRotate) // 문
	{
		CObj* pObj = new T(iRotate);
		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		return pObj;
	}
	static CObj* Create(float fX, float fY, float fSpeed, int iOption)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		pObj->Set_Speed(fSpeed);
		pObj->Set_Option(iOption);
		return pObj;
	}
	static CObj* Create(float fX, float fY, float fCX, float fCY)
	{
		CObj* pObj = new T(fX, fY, fCX, fCY);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fX, float fY, float fCX, float fCY, float fSpeed)
	{
		CObj* pObj = new T(fX, fY, fCX, fCY);
		pObj->Initialize();
		pObj->Set_Speed(fSpeed);
		return pObj;
	}
	static CObj* Create(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey)
	{
		CObj* pObj = new T(fX, fY, fCX, fCY, pFrameKey);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float fX, float fY, float fCX, float fCY, TCHAR* pFrameKey, int iFrameend) // 이펙트 전용.
	{
		CObj* pObj = new T(fX, fY, fCX, fCY, pFrameKey, iFrameend);
		pObj->Initialize();
		return pObj;
	}
};