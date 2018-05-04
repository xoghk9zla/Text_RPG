#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer(void);
	CPlayer(char* str, int iAtt, int iMaxHp);
	virtual ~CPlayer(void);

public:
	int GetDamage(void) { return m_tInfo.iAtt + EquipATT(); }
	vector<CObj*> GetInven(void) { return m_vecInven; }

public:
	virtual void Initialize(void);
	virtual void Render_Info(void);
	virtual void Release(void);

public:
	void Init_Hp(void) { m_tInfo.iHp = m_tInfo.iMaxHp + EquipMaxHp(); }
	void Earn_Gold(int iGold) { m_tInfo.iGold += iGold; }
	void Spend_Gold(int iGold) { m_tInfo.iGold -= iGold; }
	void Gain_Exp(int iExp);
	bool Gain_Item(CObj* pItem);
	bool Drop_Item(size_t iIndex, int* pGold);
	void Render_Inven(void);
	void Inventory(void);
	void SettingEquipment(void);

private:
	void EquipItem(void);
	void UnEquipItem(void);
	int EquipATT(void);
	int EquipMaxHp(void);

private:
	vector<CObj*>	m_vecInven;
	size_t			m_iMaxInven;

	CObj*			m_pEquipment[ITEMTYPE_END];
	
};

#endif