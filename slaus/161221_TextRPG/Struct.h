#pragma once

typedef struct tagInfo
{
	tagInfo(void) {}
	tagInfo(char* str, int _iAtt, int _iMaxHp, int _iExp = 0, int _iLevel = 1, int _iGold = 0)
		: iAtt(_iAtt), iMaxHp(_iMaxHp), iExp(_iExp), iLevel(_iLevel), iGold(_iGold)
	{
		strcpy_s(szName, sizeof(szName), str);
	}

	char	szName[16];
	int		iAtt;
	int		iHp;
	int		iMaxHp;
	int		iExp;
	int		iMaxExp;
	int		iLevel;
	int		iGold;
}INFO;