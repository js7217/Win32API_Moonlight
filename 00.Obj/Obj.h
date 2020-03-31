#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	enum STATE { IDLE, WALK, ATTACK, JUMP, HIT, DEAD }; // 상태..
	enum ROTATE { LEFT, UP, RIGHT, DOWN };
public:
	void UpdateRect();
	void UpdateCollisionRect();
	void FrameMove(int iStart);
public:
	const INFO& Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }
	const bool& Get_Init() { return m_bInit; }
	const RECT& Get_CollisionRect() { return m_tCollisionRect; }
	const bool& Get_IsJump() { return m_bIsJump; }
	const STATE& Get_State() { return m_eCurState; }
	const ROTATE& Get_Rotate() { return m_eRotate; }
	const FRAME& Get_Frame() { return m_tFrame; }
	const bool& Get_IsCollision() { return m_bIsCollision; }
	const bool& Get_IsCollisionExtra() { return m_bIsCollisionExtra; }
	const GroupID::ID Get_GroupID() { return m_eGroupID; }
	const int& Get_MaxHp() { return m_iMaxHp; }
	const int& Get_Hp() { return m_iHp; }
	const int& Get_Att() { return m_iAtt; }
	const int& Get_Option() { return m_iOption; }
	const int& Get_DrawID() { return m_iDrawID; }
	const int& Get_Index() { return m_iIndex; }
	const ObjID::ID& Get_ObjID() { return m_eObjID; }
public:
	void Set_Pos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void Set_Init() { m_bInit = true; }
	void Set_Dead() { m_bIsDead = true; }
	void Set_State(STATE eState) { m_eCurState = eState; }
	void Set_IsCollision(bool bIsColl) { m_bIsCollision = bIsColl; }
	void Set_IsCollisionExtra(bool bIsColl) { m_bIsCollisionExtra = bIsColl; }
	void Set_Hp(int iDamage) { m_iHp -= iDamage; }
	void Set_Speed(float fSpeed) { m_fSpeed = fSpeed; }
	void Set_Option(int iOption) { m_iOption = iOption; }
	void Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void Set_Index(int iIndex) { m_iIndex = iIndex; }
public:
	virtual void Initialize() = 0;
	virtual void LateInitialize();
	virtual int  Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
public:
	int RandomNumber(int min, int max);
protected:
	bool m_bInit;
	bool m_bIsDead;
	bool m_bIsJump;
	bool m_bIsCollision;
	bool m_bIsCollisionExtra;
	int m_iHp;
	int m_iMaxHp;
	int m_iAtt;
	int m_iOption;
	int m_iDrawID;
	int m_iIndex; // 오브젝트가 위치한 맵 인덱스 값.
	float m_fSpeed;
	float m_fAngle;
	TCHAR* m_pFrameKey;
	CObj* m_pTarget;
	INFO m_tInfo;	//크기 및 좌표
	RECT m_tRect;	//해당 렉트
	RECT m_tCollisionRect;	// 충돌용 렉트
	FRAME m_tFrame;
	STATE m_eCurState;
	STATE m_ePreState;
	ROTATE m_eRotate;
	GroupID::ID m_eGroupID;
	ObjID::ID m_eObjID;
};

