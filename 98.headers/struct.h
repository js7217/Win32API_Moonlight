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
	int iFrameStart; // x������
	int iFrameEnd;   // x������
	int iFrameScene; // y��ǥ.
	DWORD dwFrameSpeed; // �ݺ� �ӵ�.
	DWORD dwFrameTime; // �󸶸�ŭ ������ ��������.
}FRAME;
