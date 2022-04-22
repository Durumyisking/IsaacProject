#include "pch.h"
#include "UIMgr.h"

#include "UI.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Camera.h"
#include "KeyMgr.h"

#include "Object.h"



CUIMgr::CUIMgr()
{


	
}

CUIMgr::~CUIMgr()
{



}

void CUIMgr::update()
{
	CScene* pcurScene = CSceneMgr::GetInst()->GetCurScene();

	Vec2 vMousePos = MOUSE_POS;
	const vector<CObject*>& vecUI = pcurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{		
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			// Ÿ�� UI�� üũ
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI * CUIMgr::GetTargetedUI(CUI * _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. �θ� ���� ��� �ڽ� UI�� �˻�
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*>  vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ���� UI�� TargetUI���� Ȯ��

		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ�

		if (pUI->IsMouseOn())
		{
			// ���ο� UI�� Ÿ������ �����Ǳ� ����
			// ���� Ÿ�� UI�� nonetarget
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		// �� UI�� �ڽĵ��� ������
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			// �޾ƿ� �ڽĵ��� inqueue
			queue.push_back(vecChild[i]);
		}

		// ��Ÿ�� ���͵鸸 ���콺 ��ư �����ִ°� Ȯ��
		if (bLbtnAway)
		{
			for (size_t i = 0; i < vecNoneTarget.size(); ++i)
			{
				vecNoneTarget[i]->m_bLbtnDown = false;
			}
		}
	}

	return pTargetUI;;
}
