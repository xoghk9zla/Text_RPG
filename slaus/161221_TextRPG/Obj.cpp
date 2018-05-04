#include "StdAfx.h"
#include "Obj.h"

CObj::CObj(void)
{
}

CObj::CObj(char* str, int iAtt, int iMaxhp, int iExp, int iLevel, int iGold)
: m_tInfo(str, iAtt, iMaxhp, iExp, iLevel, iGold)
{

}

CObj::~CObj(void)
{
}
