#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::CItem(char* str, int iAtt, int iMaxhp, int iExp, int iLevel, int iGold)
: CObj(str, iAtt, iMaxhp, iExp, iLevel, iGold)
{

}

CItem::~CItem(void)
{
	Release();
}

void CItem::Initialize(void)
{
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_tInfo.iMaxExp = m_tInfo.iExp;

	m_eState = UNEQUIP;
}

void CItem::Render_Info(void)
{
	if(EQUIP == m_eState)
		cout << "장착중" << endl;

	cout << "이름: " << m_tInfo.szName << endl;
	cout << "공격: " << m_tInfo.iAtt << endl;
	cout << "체력: " << m_tInfo.iMaxHp << endl;
	cout << "가격: " << m_tInfo.iGold << endl;
	cout << "==============================" << endl;
}

void CItem::Release(void)
{
}
