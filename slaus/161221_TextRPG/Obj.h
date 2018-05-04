#pragma once

class CObj
{
public:
	CObj(void);
	CObj(char* str, int iAtt, int iMaxhp, int iExp = 0, int iLevel = 1, int iGold = 0);
	virtual ~CObj(void);

public:
	INFO GetInfo(void) { return m_tInfo; }

public:
	void SetDamage(int iAtt) { m_tInfo.iHp -= iAtt; }
	void SetInfo(INFO& rTemp) { m_tInfo = rTemp; }

public:
	CObj& operator-=(CObj& _obj)
	{
		m_tInfo.iHp -= _obj.m_tInfo.iAtt;
		return *this;
	}

public:
	virtual void Initialize(void) = 0;
	virtual void Render_Info(void) = 0;
	virtual void Release(void) = 0;

protected:
	INFO	m_tInfo;
};
