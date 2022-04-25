#include "pch.h"
#include "UIMgr.h"

#include "UI.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Camera.h"
#include "KeyMgr.h"

#include "Object.h"



CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{}

CUIMgr::~CUIMgr()
{}

void CUIMgr::update()
{

	// FocusedUI Ȯ�� (�θ� UI�� ��)
	m_pFocusedUI = GetFocusedUI();
	if (!m_pFocusedUI)
		return;


	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// FocusedUI ���� �θ� �ڽ� UI���� ���� Ÿ���� �� UI �޾ƿ�
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		// Ÿ�� UI�� üũ
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
		
	}
}

void CUIMgr::SetFocusedUI(CUI * _pUI)
{
	if (m_pFocusedUI == _pUI || nullptr == m_pFocusedUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;


	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
			break;				
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}


CUI * CUIMgr::GetFocusedUI()
{
	// �θ� UI���� ���� ��Ŀ�̵� UI, ������ ������ UI ������

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ��Ŀ�� �� ������ ��Ŀ�� �Ǵ� UI�� ������ �� �ڷ� �����ٰ���
	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ��
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		// ���� Ŭ���� ������ ������ focusedui ��ȯ
		return pFocusedUI;
	}
	
	// ����Ŭ���� �߻�
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// focus �� ui�� ����
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// ���� ������ �� �ڷ� ���� ��ü

	// ���� �ڸ� �����
	vecUI.erase(targetiter);

	// �����صξ��� focusedui pushback
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
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
