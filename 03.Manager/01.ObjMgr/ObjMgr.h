#pragma once
class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)
private:
	CObjMgr();
	~CObjMgr();
public:
	void Set_ObjKey(TCHAR* ObjKey) { m_pObjKey = ObjKey; }
	void Set_StopList(ObjID::ID eID);
public:
	CObj* Get_Player() 
	{ 
		if (m_ObjList[ObjID::PLAYER].empty())
			return nullptr;
		return m_ObjList[ObjID::PLAYER].front(); 
	}
	OBJLIST Get_List(ObjID::ID eID) { return m_ObjList[eID]; }
	OBJLIST Get_SaveList() { return m_SaveObjList; }
public:
	void AddObject(ObjID::ID eID, CObj* pObj);
	void AddSaveObject(CObj* pObj);
	void DeleteID(ObjID::ID eID);
	int Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
public:
	void SaveObj();
	void LoadObj();
private:
	OBJLIST m_ObjList[ObjID::END];
	OBJLIST m_SaveObjList;
	OBJLIST m_RenderList[GroupID::END];
	TCHAR* m_pObjKey;
};

