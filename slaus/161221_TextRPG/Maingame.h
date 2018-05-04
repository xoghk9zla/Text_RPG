#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CObj;
class CField;
class CStore;

class CMainGame
{
public:
	CMainGame(void);
	~CMainGame(void);

public:
	bool Initialize(void);
	void GameProgress(void);
	void Release(void);

private:	
	void CreatePlayer(void);
	void SaveData(void);
	bool LoadData(void);

private:
	CObj*		m_pPlayer;
	CField*		m_pField;
	CStore*		m_pStore;
};

#endif