#pragma once
#include "Scene.h"
class CEditor :
	public CScene
{
public:
	CEditor();
	virtual ~CEditor();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void KeyCheck();
	void MapChange();
private:
	bool m_bIsLockX;
	bool m_bIsLockY;
	TCHAR* m_pFrameKey;
	TCHAR* m_pTileKey;
	TCHAR* m_pObjKey;
	int m_iPickTile;
	int m_iObj;
	int m_iLowerDrawID;
	int m_iStoneDrawID;
	float m_fLockX;
	float m_fLockY;
};

