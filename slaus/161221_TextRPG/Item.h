#pragma once
#include "obj.h"

class CItem : public CObj
{
public:
	CItem(void);
	CItem(char* str, int iAtt, int iMaxhp, int iExp, int iLevel, int iGold);
	virtual ~CItem(void);

public:
	ITEMTYPE GetType(void) { return m_eType; }
	ITEMSTATE GetState(void) { return m_eState; }

public:
	void SetType(ITEMTYPE eType) { m_eType = eType; }
	void SetState(ITEMSTATE eState) { m_eState = eState; }

public:
	virtual void Initialize(void);
	virtual void Render_Info(void);
	virtual void Release(void);

private:
	ITEMTYPE	m_eType;
	ITEMSTATE	m_eState;

};
