#include "stdafx.h"
#include "Monster.h"

CMonster::CMonster(void)
{

}

CMonster::CMonster(char* str, int iAtt, int iMaxhp, int iExp, int iLevel, int iGold)
: CObj(str, iAtt, iMaxhp, iExp, iLevel, iGold)
{
	
}

CMonster::~CMonster(void)
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_tInfo.iMaxExp = m_tInfo.iExp;
}

void CMonster::Render_Info(void)
{
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "레벨: " << m_tInfo.iLevel << endl;
	cout << "경험: " << m_tInfo.iExp << endl;
	cout << "공격: " << m_tInfo.iAtt << endl;
	cout << "체력: " << m_tInfo.iHp << " / " << m_tInfo.iMaxHp << endl;
	cout << "==============================" << endl;
}

void CMonster::Release(void)
{
}
