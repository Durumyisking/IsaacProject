#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);



public:
	void update();

public:
	CUI* GetTargetedUI(CUI* _pParentUI); // �θ� UI ������ ������ Ÿ���� �� UI���� ã�Ƽ� ��ȯ
};

