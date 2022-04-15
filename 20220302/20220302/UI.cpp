#include "pch.h"
#include "UI.h"


// ��� UI�� �θ�ν� �߻� Ŭ������ ��ü ���� ���ϰ� �Ұ���
// UI���� �θ� �ڽİ��踦 ����
// Scene���� ���� �ֻ��� �θ� �� �ϳ��� �־��� ����



CUI::CUI()
{
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::update()
{
	update_child();
}

// ���� ��ġ�� ��������
void CUI::finalupdate()
{
	CObject::finalupdate();

	m_vFinalPos = GetPos();

	// UI�� ���� ��ǥ�� ���Ѵ�.
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	finalupdate_child();

}

void CUI::render(HDC _dc)
{
	// �׳� getpos��� �ϸ� vParnetpos�� �������� ���� �ʱ�ȭ ��ġ�� ������
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();


	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}

}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

