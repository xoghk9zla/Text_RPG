#ifndef __FIELD_H__
#define __FIELD_H__

class CObj;

class CField
{
public:
	CField(void);
	~CField(void);

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	void Progress(void);
	int Combat(void);
	void Release(void);

private:
	CObj*	m_pPlayer;
	CObj*	m_pMonster;
};

#endif