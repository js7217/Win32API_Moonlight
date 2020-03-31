#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	enum ATT_STATE { BIGSWORD, GLOVES, SHOTSWORD, SPEAR, END };
	void KeyCheck();
	void MotionChange();
	void AttMotionChange();
	void IsJumping();
	void IsHit();
	void IsOffSet();
	void IsShake();
	void IsOffSet_Dungeon();
	void WeaponChange();
	void IntroSceneSprite();
public:
	void Set_Scroll(float fPreScroll, float fAddScroll, int Rotate)
	{
		m_fPreScroll = fPreScroll;
		m_fAddScroll = fAddScroll;
		m_iLR = Rotate;
	}
	void Set_Shake() { m_bIsShake = true; }
	void Set_Intro() { m_bIsIntro = true; }
	const bool& Get_Intro() { return m_bIsIntro; }
	const bool& Get_Shake() { return m_bIsShake; }
	const ATT_STATE Get_AttState() { return m_eCurAtt; }
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	bool m_bIsIntro;
	bool m_bIsShake;
	bool m_bIsHit;
	int m_iLR;
	int m_iIntro;
	int m_iShakeNum;
	float m_fPreScroll;
	float m_fAddScroll;
	float m_fScrollX;
	float m_fScrollY;

	ATT_STATE m_eCurAtt;
	ATT_STATE m_ePreAtt;
	DWORD m_dwHitTime;
	DWORD m_dwHitRenderTime;
};

