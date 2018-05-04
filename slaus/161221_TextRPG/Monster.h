#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"

class CMonster : public CObj
{
public:
	CMonster(void);
	CMonster(char* str, int iAtt, int iMaxhp, int iExp, int iLevel, int iGold);
	virtual ~CMonster(void);

public:
	virtual void Initialize(void);
	virtual void Render_Info(void);
	virtual void Release(void);

};

#endif