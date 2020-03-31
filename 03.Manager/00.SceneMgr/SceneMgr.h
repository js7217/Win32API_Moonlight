#pragma once
class CScene;
class CSceneMgr
{
public:
	DECLARE_SINGLETON(CSceneMgr)
private:
	CSceneMgr();
	~CSceneMgr();
public:
	enum SCENEID { SCENE_LOGO, SCENE_MENU, SCENE_INTRO, SCENE_HOME, SCENE_VILLAGE, SCENE_STAGE1, SCENE_STAGE2, SCENE_STAGE3, SCENE_STAGE4, SCENE_EDIT, SCENE_END };
public:
	void SceneChange(SCENEID eSceneID);	// Scene�� ��ȯ��Ű�� ���� �Լ�.
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
public:
	SCENEID Get_SceneID() { return m_eCurScene; }
	CScene*& Get_Scene() { return m_pScene; }
private:
	bool m_bInit;
	CScene* m_pScene;
	SCENEID m_eCurScene;	//���� ��
	SCENEID m_eNextScene;	//�޾ƿ� ��
};

