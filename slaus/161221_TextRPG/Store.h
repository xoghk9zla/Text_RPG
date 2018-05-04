#pragma once

class CObj;

class CStore
{
public:
	CStore(void);
	~CStore(void);

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	void Initialize(void);
	void Progress(void);
	void Release(void);

private:
	void RenderItem(ITEMLEVEL eItemLevel);
	void PurchaseItem(CObj* pItem);
	void SellItem(void);

private:
	CObj*	m_pPlayer;
	CObj*	m_pItem2DArr[ITEMLEVEL_END][ITEMTYPE_END];
};
