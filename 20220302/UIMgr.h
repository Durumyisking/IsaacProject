#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI);

public:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI); // �θ� UI ������ ������ Ÿ���� �� UI���� ã�Ƽ� ��ȯ
};

