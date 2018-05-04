#include "stdafx.h"
#include "Field.h"
#include "Player.h"
#include "Monster.h"

CField::CField(void)
{
	m_pPlayer = NULL;
	m_pMonster = NULL;
}

CField::~CField(void)
{
	Release();
}

void CField::Progress(void)
{
	int iInput = 0;
	m_pMonster = NULL;

	while(true)
	{
		system("cls");
		m_pPlayer->Render_Info();

		cout << "### 던전을 고르세요 ###" << endl;
		cout << "1.초급 2.중급 3.고급 4.나가기" << endl;
		cin >> iInput;

		

		switch(iInput)
		{
		case 1:
			m_pMonster = new CMonster("슬라임", 10, 30, 30, 1, 1000);
			m_pMonster->Initialize();
			break;

		case 2:
			m_pMonster = new CMonster("오우거", 30, 60, 60, 2, 2000);
			m_pMonster->Initialize();
			break;

		case 3:
			m_pMonster = new CMonster("골렘", 60, 90, 90, 3, 3000);
			m_pMonster->Initialize();
			break;

		case 4:			
			return;

		default:
			cout << "다시 선택하세요" << endl;
			system("pause");
			continue;
		}

		if(1 == Combat())
			dynamic_cast<CPlayer*>(m_pPlayer)->Init_Hp();

		Release();
	}
}

int CField::Combat(void)
{
	int iInput = 0;

	while(true)
	{
		system("cls");
		m_pPlayer->Render_Info();
		m_pMonster->Render_Info();

		INFO tMobInfo = m_pMonster->GetInfo();

		if(0 >= m_pPlayer->GetInfo().iHp)
		{
			cout << "플레이어 사망" << endl;
			system("pause");
			return 1;
		}
		else if(0 >= tMobInfo.iHp)
		{
			cout << "사냥 성공!!!" << endl;
			cout << "경험치 +" << tMobInfo.iExp << endl;
			cout << "소지금 +" << tMobInfo.iGold << endl;

			dynamic_cast<CPlayer*>(m_pPlayer)->Gain_Exp(tMobInfo.iExp);	
			dynamic_cast<CPlayer*>(m_pPlayer)->Earn_Gold(tMobInfo.iGold);	

			system("pause");
			return 0;
		}

		cout << "1.공격 2.도망" << endl;
		cin >> iInput;

		switch(iInput)
		{
		case 1:
			/**m_pMonster -= *m_pPlayer;
			*m_pPlayer -= *m_pMonster;*/
			m_pMonster->SetDamage(D_CAST(CPlayer, m_pPlayer)->GetDamage());
			m_pPlayer->SetDamage(tMobInfo.iAtt);			
			break;

		case 2:
			cout << "도망!!!" << endl;
			system("pause");
			return 0;

		default:
			cout << "다시 선택하세요" << endl;
			system("pause");
			break;
		}
	}

	return 0;
}

void CField::Release(void)
{
	if(NULL != m_pMonster)
	{
		delete m_pMonster;
		m_pMonster = NULL;
	}
}
