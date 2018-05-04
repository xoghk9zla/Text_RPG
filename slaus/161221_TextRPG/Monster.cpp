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
	cout << "�̸�: " << m_tInfo.szName << endl;
	cout << "����: " << m_tInfo.iLevel << endl;
	cout << "����: " << m_tInfo.iExp << endl;
	cout << "����: " << m_tInfo.iAtt << endl;
	cout << "ü��: " << m_tInfo.iHp << " / " << m_tInfo.iMaxHp << endl;
	cout << "==============================" << endl;
}

void CMonster::Release(void)
{
}
