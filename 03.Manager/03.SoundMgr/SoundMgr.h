#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

public:
	enum CHANNELID { BGM, PLAYER, MONSTER, BOSS, BULLET, EFFECT, BIGSWORD, GLOVES, SHORTSWORD, SPEAR, UI, MAXCHANNEL };
private:
	CSoundMgr();
	~CSoundMgr();
public:
	void Initialize();

	void Release();
public:
	void MyPlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void AllStop();
	void LoadSoundFile();
public:
	// FMOD_SOUND : ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// FMOD_SYSTEM : ���� ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;
};

