#include "stdafx.h"
#include "Boss.h"


CBoss::CBoss()
{
}


CBoss::~CBoss()
{
}

float CBoss::Target_Angle()
{
	float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDist = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float fAngle = acosf(fWidth / fDist);
	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
	{
		fAngle *= -1.f;
	}

	return fAngle;
}
