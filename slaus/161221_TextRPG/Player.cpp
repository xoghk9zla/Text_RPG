#include "stdafx.h"
#include "Player.h"
#include "Item.h"

CPlayer::CPlayer(void)
{

}

CPlayer::CPlayer(char* str, int iAtt, int iMaxHp)
: CObj(str, iAtt, iMaxHp)
{
	
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.iHp = m_tInfo.iMaxHp;	
	m_tInfo.iMaxExp = 100;

	m_iMaxInven = 5;
	m_vecInven.reserve(m_iMaxInven);

	m_tInfo.iGold = 99999999;

	memset(m_pEquipment, NULL, sizeof(m_pEquipment));
}

void CPlayer::Render_Info(void)
{
	cout << "직업: " << m_tInfo.szName << endl;
	cout << "레벨: " << m_tInfo.iLevel << endl;
	cout << "경험: " << m_tInfo.iExp << " / " << m_tInfo.iMaxExp << endl;
	cout << "공격: " << m_tInfo.iAtt + EquipATT() << endl;
	cout << "체력: " << m_tInfo.iHp << " / " << m_tInfo.iMaxHp + EquipMaxHp() << endl;
	cout << "골드: " << m_tInfo.iGold << endl;
	cout << "==============================" << endl;
}

void CPlayer::Release(void)
{
	for_each(m_vecInven.begin(), m_vecInven.end(), Safe_Delete<CObj*>);
}

void CPlayer::Gain_Exp(int iExp)
{
	m_tInfo.iExp += iExp;

	if(m_tInfo.iExp >= m_tInfo.iMaxExp)
	{
		cout << "레벨업!!" << endl;
		m_tInfo.iLevel++;
		m_tInfo.iAtt += 2;
		m_tInfo.iMaxHp += 20;
		Init_Hp();

		int iTemp = m_tInfo.iExp - m_tInfo.iMaxExp;

		if(0 < iTemp)
			m_tInfo.iExp = iTemp;
		else
			m_tInfo.iExp = 0;

		m_tInfo.iMaxExp *= m_tInfo.iLevel;
	}
}

bool CPlayer::Gain_Item(CObj* pItem)
{
	if(m_vecInven.size() < m_iMaxInven)
	{
		CItem* pMyItem = new CItem(*D_CAST(CItem, pItem));
		m_vecInven.push_back(pMyItem);
		return true;
	}
	else
	{
		cout << "인벤토리가 가득찼습니다" << endl;
		system("pause");
		return false;
	}

	return false;
}

void CPlayer::Render_Inven(void)
{
	if(m_vecInven.empty())
		cout << "인벤토리가 비어있습니다" << endl;

	for(size_t i = 0; i < m_vecInven.size(); ++i)
	{
		cout << i + 1 << ')' << endl;
		m_vecInven[i]->Render_Info();
	}
}

void CPlayer::EquipItem(void)
{
	if(m_vecInven.empty())
	{
		cout << "인벤토리는 비어있습니다" << endl;
		system("pause");
		return;
	}
	
	int iInput = 0;

	while(true)
	{
		system("cls");
		Render_Info();

		cout << "0) 나가기" << endl;
		Render_Inven();
		cout << "선택: ";
		cin >> iInput;
		--iInput;

		if(0 > iInput)
			return;
		else if((size_t)iInput >= m_vecInven.size())
		{
			cout << "해당 아이템은 존재하지 않습니다" << endl;
			system("pause");
		}
		else
		{
			ITEMTYPE eType = D_CAST(CItem, m_vecInven[iInput])->GetType();

			if(NULL != m_pEquipment[eType])
				D_CAST(CItem, m_pEquipment[eType])->SetState(UNEQUIP);

			m_pEquipment[eType] = m_vecInven[iInput];
			D_CAST(CItem, m_pEquipment[eType])->SetState(EQUIP);
		}

	}
}

void CPlayer::Inventory(void)
{
	int iInput = 0;

	while(true)
	{
		system("cls");
		Render_Info();
		Render_Inven();

		cout << "1.장착 2.장착해제 3.나가기" << endl;
		cin >> iInput;

		switch(iInput)
		{
		case 1:
			EquipItem();
			break;

		case 2:
			UnEquipItem();
			break;

		case 3:
			return;

		default:
			cout << "다시 선택하세여" << endl;
			system("pause");
			break;
		}
	}
}

int CPlayer::EquipATT(void)
{
	int iITempAtt = 0;

	for(int i = 0; i < ITEMTYPE_END; ++i)
	{
		if(NULL != m_pEquipment[i])
			iITempAtt += m_pEquipment[i]->GetInfo().iAtt;
	}

	return iITempAtt;
}

int CPlayer::EquipMaxHp(void)
{
	int iITempMaxHp = 0;

	for(int i = 0; i < ITEMTYPE_END; ++i)
	{
		if(NULL != m_pEquipment[i])
			iITempMaxHp += m_pEquipment[i]->GetInfo().iMaxHp;
	}

	return iITempMaxHp;
}

void CPlayer::UnEquipItem(void)
{
	int iInput = 0;
	bool bExist = false;
	ITEMTYPE eType = ITEMTYPE_END;

	while(true)
	{
		system("cls");
		Render_Info();

		for(int i = 0; i < ITEMTYPE_END; ++i)
		{
			cout << i + 1 << ')' << endl;

			if(NULL != m_pEquipment[i])
			{
				bExist = true;
				m_pEquipment[i]->Render_Info();
			}
			else
			{
				cout << "Empty!!!!!!" << endl;
				cout << "==============================" << endl;
			}
		}

		if(false == bExist)
		{
			cout << "장착한 아이템이 없습니다" << endl;
			system("pause");
			return;
		}

		cout << "3. 나가기" << endl;
		cin >> iInput;

		switch(iInput)
		{
		case 1:
			eType = SWORD;
			break;

		case 2:
			eType = ARMOR;
			break;

		case 3:
			return;

		default:
			cout << "다시 선택해주세요" << endl;
			system("pause");
			continue;
		}

		if(NULL != m_pEquipment[eType])
		{
			D_CAST(CItem, m_pEquipment[eType])->SetState(UNEQUIP);
			m_pEquipment[eType] = NULL;
		}
		else
			cout << "해당 칸은 비어있습니다" << endl;

		system("pause");
	}
}

bool CPlayer::Drop_Item(size_t iIndex, int* pGold)
{
	if(m_vecInven.empty())
	{
		cout << "인벤토리는 비어있습니다" << endl;
		return false;
	}
	else if(iIndex >= m_vecInven.size())
	{
		cout << "해당 아이템이 없습니다" << endl;
		return false;
	}
	else
	{
		vector<CObj*>::iterator iter = m_vecInven.begin();

		iter += iIndex;

		if(EQUIP == D_CAST(CItem, *iter)->GetState())
		{
			cout << "장착 중인 아이템입니다" << endl;
			return false;
		}

		if(NULL != pGold)
			*pGold = (*iter)->GetInfo().iGold;

		Safe_Delete<CObj*>(*iter);
		m_vecInven.erase(iter);
		return true;
	}
}

void CPlayer::SettingEquipment(void)
{
	ITEMSTATE eState = STATE_END;
	ITEMTYPE eType = ITEMTYPE_END;

	for(size_t i = 0; i < m_vecInven.size(); ++i)
	{
		eState = D_CAST(CItem, m_vecInven[i])->GetState();

		if(EQUIP == eState)
		{
			eType = D_CAST(CItem, m_vecInven[i])->GetType();
			m_pEquipment[eType] = m_vecInven[i];
		}

	}
}






