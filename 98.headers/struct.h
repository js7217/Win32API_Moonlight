#pragma once
typedef struct tagInfo
{
	float fCX;
	float fCY;
	float fCollisionCX;
	float fCollisionCY;
	float fX;
	float fY;
}INFO;

typedef struct tagFrame
{
	int iFrameStart; // x시작점
	int iFrameEnd;   // x끝지점
	int iFrameScene; // y좌표.
	DWORD dwFrameSpeed; // 반복 속도.
	DWORD dwFrameTime; // 얼마만큼 빠르게 움직일지.
}FRAME;
