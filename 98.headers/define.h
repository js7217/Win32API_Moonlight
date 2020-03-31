#pragma once

#define WINCX 800
#define WINCY 600

#define TILECX 40
#define TILECY 40

#define TILEX 100
#define TILEY 100

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define PI	3.141592f
#define DEGREE_TO_RADIAN(fAngle)		fAngle * PI / 180.f
#define RADIAN_TO_DEGREE(fAngle)		fAngle * 180.f / PI

#define DECLARE_SINGLETON(ClassName)			\
public:											\
	static ClassName* Get_Instance()			\
	{											\
		if (nullptr == m_pInstance)				\
			m_pInstance = new ClassName;		\
		return m_pInstance;						\
	}											\
	static void Destory_Instance()				\
	{											\
		if(m_pInstance != nullptr)				\
		{										\
			delete m_pInstance;					\
			m_pInstance = nullptr;				\
		}										\
	}											\
private:										\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;