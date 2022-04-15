#include "pch.h"
#include "KeyMgr.h"

#include "Core.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','Z','X','C','V','B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	VK_LBUTTON, VK_RBUTTON,
};


CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}


}

// �츮�� ������ �Լ��� ���� ���� �ʴ´�
// keymgr ���� ��� ������ΰ� Ȯ��
void CKeyMgr::update()
{
	// ������ â�� ��Ŀ���� ��� ��(��Ȱ��ȭ) ���� �۾��� �� ��ġ�� �������
	// ������� w�� �������� ĳ���Ͱ� 5�ʵ��� �ɾ�� ������ ������
	// �����츦 ����� 5�ʵ��� �ɾ�� �ൿ�� �����ؾ���

	// ������ ��Ŀ�� �˾Ƴ���
	// HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus(); // ���� ��Ŀ�� �Ǿ��ִ� �������� �ڵ鰪 �˷���
							// ��Ŀ�� �Ǿ��ִ¾ְ� ������ id 0(nullptr)�� ��ȯ 
	
	// ���� �����쿡���� Ű �Է��� �����ϰ� ������
	// ���� ������ �޾Ƴ��� GetFocus�� ���ؼ� üũ

	// �ƹ� �����쿡���� �۵��ϰ� ������
	// if���� true�̸� ��
	if (nullptr != hWnd)
	{

		for (int i = 0; i < (int)KEY::LAST; ++i)
		{

			// Ű�� ����������
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrev) // ���� �����ӿ� ���� �־�����
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrev = true;

			}
			else // Ű�� �ȴ���������
			{
				if (true == m_vecKey[i].bPrev)
				{
					// ������ �����־��ٸ�
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// �������� �ȴ����־��ٸ�
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrev = false;
			}
		}

		POINT ptPos = {};

		// getcursor�� window ��ü ��ǥ�� �������°��̱⶧���� ����������
		GetCursorPos(&ptPos);
		// ��ũ����ǥ���� Ŭ���̾�Ʈ ��ǥ�� �ٲ��ִ°�
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);
		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrev = false;
			
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::NONE;
			



		}
	}
}
