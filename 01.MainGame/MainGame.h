#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
public:
	void PlayerBitMap();
private:
	HDC m_hDC;
};

