#pragma once
class CObj;
class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)
private:
	CTileMgr();
	~CTileMgr();
public:
	void Set_SaveKey(TCHAR* TileKey){ m_pTileKey = TileKey; }
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	void CollisionTile(CObj*& rTile, OBJLIST& rList);
	void CollisionBullet(CObj*& rTile, OBJLIST& rList);
	void PickTile(const POINT& pt, int iDrawID, int iOption);
	void ChangeTile(int iDrawID, int iOptionID);
	void SaveTile();
	void LoadTile();
	bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
private:
	int m_iDrawID;
	int m_iOptionID;
	vector<CObj*> m_vecTile;
	TCHAR* m_pTileKey;
	OBJLIST PlayerList;
	OBJLIST MonsterList;
	OBJLIST MonsterBulletList;
};

