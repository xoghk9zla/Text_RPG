// 161221_TextRPG.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

