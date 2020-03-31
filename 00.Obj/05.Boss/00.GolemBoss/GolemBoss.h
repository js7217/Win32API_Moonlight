#pragma once
#include "Boss.h"
class CGolemBoss :
	public CBoss
{
public:
	enum GOLEMSTATE { IDLE, NOARM_IDLE, LAUNCH, RECOVER, SPAWN, WAKEUP, DEAD };
public:
	CGolemBoss();
	virtual ~CGolemBoss();
public:
	// CBoss을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void LateInitialize();
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void FrameBack();
	void MotionChange();
	void AttackPattern();
	void Straight_Rock();
	void Half_Circle_Rock();
	void Sector_Form_Rock();
	void Get_Angle();
	void Golem_Punch();
	void SPAWN_CASE();
private:
	bool m_bIsPunch;
	int m_iRockCnt;
	int m_iRandom;
	float m_fRockX;
	float m_fRockY;
	GOLEMSTATE m_eCurBossState;
	GOLEMSTATE m_ePreBossState;
	DWORD m_dwRockCreateTime;
	CObj* m_pHpBar;
};

