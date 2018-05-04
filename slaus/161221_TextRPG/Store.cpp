#include "StdAfx.h"
#include "Store.h"
#include "Player.h"
#include "Item.h"

CStore::CStore(void)
: m_pPlayer(NULL)
{
	memset(m_pItem2DArr, NULL, sizeof(m_pItem2DArr));
}

CStore::~CStore(void)
{
	Release();
}

void CStore::Initialize(void)
{
	CObj* pItem = new CItem("초급검", 10, 5, 0, 1, 1000);
	pItem->Initialize();
	D_CAST(CItem, pItem)->SetType(SWORD);
	m_pItem2DArr[BASIC][SWORD] = pItem;

	pItem = new CItem("중급검", 20, 15, 0, 2, 2000);
	pItem->Initialize();
	D_CAST(CItem, pItem)->SetType(SWORD);
	m_pItem2DArr[ADVANCED][SWORD] = pItem;

	pItem = new CItem("고급검", 30, 25, 0, 3, 3000);
	pItem->Initialize();
	D_CAST(CItem, pItem)->SetType(SWORD);
	m_pItem2DArr[EXPERT][SWORD] = pItem;

	pItem = new CItem("초급옷", 5, 10, 0, 1, 1000);
	pItem->Initialize();
	D_CAST(CItem, pItem)->SetType(ARMOR);
	m_pItem2DArr[BASIC][ARMOR] = pItem;

	pItem = new CItem("중급옷", 15, 20, 0, 2, 2000);
	pItem->Initialize();
	D_CAST(CItem, pItem)->SetType(ARMOR);
	m_pItem2DArr[ADVANCED][ARMOR] = pItem;

	pItem = new CItem("고급옷", 25, 30, 0, 3, 3000);
	pItem->Initialize();
	D_CAST(CItem, pItem)->SetType(ARMOR);
	m_pItem2DArr[EXPERT][ARMOR] = pItem;
	
}

void CStore::Progress(void)
{
	int iInput = 0;

	while(true)
	{
		system("cls");
		m_pPlayer->Render_Info();

		cout << "상점을 고르시오" << endl;
		cout << "1.초급 2.중급 3.고급 4.판매 5.나가기" << endl;
		cin >> iInput;

		switch(iInput)
		{
		case 1:
			RenderItem(BASIC);
			break;

		case 2:
			RenderItem(ADVANCED);
			break;

		case 3:
			RenderItem(EXPERT);
			break;

		case 4:
			SellItem();
			break;

		case 5:
			return;

		default:
			cout << "다시 선택하세요" << endl;
			system("pause");
			break;
		}
	}
}

void CStore::Release(void)
{
	for(int i = 0; i < ITEMLEVEL_END; ++i)
	{
		for(int j = 0; j < ITEMTYPE_END; ++j)
			delete m_pItem2DArr[i][j];
	}

	memset(m_pItem2DArr, NULL, sizeof(m_pItem2DArr));
}

void CStore::RenderItem(ITEMLEVEL eItemLevel)
{
	int iInput = 0;

	while(true)
	{
		system("cls");
		m_pPlayer->Render_Info();

		m_pItem2DArr[eItemLevel][SWORD]->Render_Info();
		m_pItem2DArr[eItemLevel][ARMOR]->Render_Info();		

		cout << "1.무기 구매 2.방어구 구매 3.나가기" << endl;
		cin >> iInput;

		switch(iInput)
		{
		case 1:
			PurchaseItem(m_pItem2DArr[eItemLevel][SWORD]);
			break;

		case 2:
			PurchaseItem(m_pItem2DArr[eItemLevel][ARMOR]);
			break;

		case 3:
			return;

		default:
			cout << "다시 선택하세요" << endl;
			break;
		}

		system("pause");
	}	
}

void CStore::PurchaseItem(CObj* pItem)
{
	if(m_pPlayer->GetInfo().iGold >= pItem->GetInfo().iGold
		&& D_CAST(CPlayer, m_pPlayer)->Gain_Item(pItem))
	{
		D_CAST(CPlayer, m_pPlayer)->Spend_Gold(pItem->GetInfo().iGold);
		
		cout << "아이템을 구매하였습니다" << endl;
	}
	else
		cout << "아이템 구매 실패!!!" << endl;
}

void CStore::SellItem(void)
{
	int iInput = 0;

	while(true)
	{
		system("cls");
		m_pPlayer->Render_Info();

		cout << "0) 나가기" << endl;
		D_CAST(CPlayer, m_pPlayer)->Render_Inven();
		cout << "선택: ";
		cin >> iInput;
		--iInput;

		if(0 > iInput)
			return;

		int iGold = 0;

		if(D_CAST(CPlayer, m_pPlayer)->Drop_Item((size_t)iInput, &iGold))
		{
			D_CAST(CPlayer, m_pPlayer)->Earn_Gold(iGold);
			cout << "아이템을 판매하였습니다" << endl;
			system("pause");
		}
	}
}
