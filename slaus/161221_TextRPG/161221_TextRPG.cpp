// 161221_TextRPG.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Maingame.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CMainGame mainGame;

	if(false == mainGame.Initialize())
		return 0;

	mainGame.GameProgress();

	return 0;
}

