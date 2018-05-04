#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Field.h"
#include "Store.h"
#include "Item.h"

CMainGame::CMainGame(void)
: m_pPlayer(NULL), m_pField(NULL), m_pStore(NULL)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}

bool CMainGame::Initialize(void)
{
	if(NULL == m_pPlayer)
	{
		CreatePlayer();

		if(NULL == m_pPlayer)
			return false;
	}

	if(NULL == m_pField)
	{
		m_pField = new CField;

		if(NULL == m_pField)
			return false;

		m_pField->SetPlayer(m_pPlayer);
	}

	if(NULL == m_pStore)
	{
		m_pStore = new CStore;

		if(NULL == m_pStore)
			return false;

		m_pStore->Initialize();
		m_pStore->SetPlayer(m_pPlayer);
	}

	return true;
}	

void CMainGame::CreatePlayer(void)
{
	int		 iInput = 0;

	while(true)
	{
		system("cls");

		cout << "#### ���� ���� ####" << endl;
		cout << "1.���� 2.������ 3.���� 4.�ҷ����� 5.���� ����" << endl;
		cin >> iInput;

		system("cls");

		switch(iInput)
		{
		case 1:
			m_pPlayer = new CPlayer("����", 10, 200);
			m_pPlayer->Initialize();
			cout << "���縦 �����Ͽ����ϴ�" << endl;
			system("pause");
			return;

		case 2:
			m_pPlayer = new CPlayer("������", 20, 100);
			m_pPlayer->Initialize();
			cout << "�����縦 �����Ͽ����ϴ�" << endl;
			system("pause");
			return;

		case 3:
			m_pPlayer = new CPlayer("����", 15, 150);
			m_pPlayer->Initialize();
			cout << "������ �����Ͽ����ϴ�" << endl;
			system("pause");
			return;

		case 4:
			if(LoadData())
				return;
			else
				break;

		case 5:
			cout << "������ �����մϴ�" << endl;
			return;

		default:
			cout << "�ٽ� �����ϼ���" << endl;
			break;
		}
		
	}
}

void CMainGame::GameProgress(void)
{
	int iInput = 0;

	while(true)
	{
		system("cls");
		m_pPlayer->Render_Info();

		cout << "1.���� 2.���� 3.��� 4.���� 5.����" << endl;
		cin >> iInput;

		switch(iInput)
		{
		case 1:
			m_pField->Progress();
			break;

		case 2:
			m_pStore->Progress();
			break;

		case 3:
			D_CAST(CPlayer, m_pPlayer)->Inventory();
			break;

		case 4:
			SaveData();
			break;

		case 5:
			cout << "������ �����մϴ�." << endl;
			return;

		default:
			cout << "�ٽ� �����ϼ���" << endl;
			break;
		}

		system("pause");
	}
} 

void CMainGame::SaveData(void)
{
	FILE* fp = NULL;
	errno_t err = 0;

	err = fopen_s(&fp, "data.txt", "wb");

	if(0 == err)
	{
		fwrite(&(m_pPlayer->GetInfo()), sizeof(INFO), 1, fp);

		vector<CObj*> vecTemp = D_CAST(CPlayer, m_pPlayer)->GetInven();

		ITEMTYPE eType = ITEMTYPE_END;
		ITEMSTATE eState = STATE_END;

		for(size_t i = 0; i < vecTemp.size(); ++i)
		{
			eType = D_CAST(CItem, vecTemp[i])->GetType();
			eState = D_CAST(CItem, vecTemp[i])->GetState();

			fwrite(&(vecTemp[i]->GetInfo()), sizeof(INFO), 1, fp);
			fwrite(&eType, sizeof(ITEMTYPE), 1, fp);
			fwrite(&eState, sizeof(ITEMSTATE), 1, fp);
		}

		cout << "���� ����!!" << endl;

		fclose(fp);
	}
	else
	{
		cout << "���� ����!!" << endl;
	}
}

bool CMainGame::LoadData(void)
{
	FILE* fp = NULL;
	errno_t err = 0;

	err = fopen_s(&fp, "data.txt", "rb");

	if(0 == err)
	{
		if(NULL == m_pPlayer)
		{
			m_pPlayer = new CPlayer;
			m_pPlayer->Initialize();
		}

		INFO tTemp;

		fread(&tTemp, sizeof(INFO), 1, fp);
		m_pPlayer->SetInfo(tTemp);

		ITEMTYPE eType = ITEMTYPE_END;
		ITEMSTATE eState = STATE_END;

		int iCount = 0;		
		CObj* pItem = NULL;

		while(true)
		{
			fread(&tTemp, sizeof(INFO), 1, fp);
			fread(&eType, sizeof(ITEMTYPE), 1, fp);
			iCount = fread(&eState, sizeof(ITEMSTATE), 1, fp);

			if(1 > iCount)
				break;

			pItem = new CItem;
			pItem->Initialize();

			pItem->SetInfo(tTemp);
			D_CAST(CItem, pItem)->SetType(eType);
			D_CAST(CItem, pItem)->SetState(eState);

			D_CAST(CPlayer, m_pPlayer)->Gain_Item(pItem);
		}

		cout << "�ҷ����� ����!!!" << endl;

		D_CAST(CPlayer, m_pPlayer)->SettingEquipment();

		fclose(fp);

		

		return true;
	}
	else
	{
		cout << "�ҷ����� ����!" << endl;
		cout << "ĳ���͸� ���� �����ϼ���!" << endl;
		system("pause");
		return false;
	}

	return false;
}

void CMainGame::Release(void)
{
	if(NULL != m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if(NULL != m_pField)
	{
		delete m_pField;
		m_pField = NULL;
	}

	if(NULL != m_pStore)
	{
		delete m_pStore;
		m_pStore = NULL;
	}
}
