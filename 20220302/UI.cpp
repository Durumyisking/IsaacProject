#include "pch.h"
#include "UI.h"

#include "Core.h"

#include "Camera.h"
#include "KeyMgr.h"

#include "SelectGDI.h"

// ��� UI�� �θ�ν� �߻� Ŭ������ ��ü ���� ���ϰ� �Ұ���
// UI���� �θ� �ڽİ��踦 ����
// Scene���� ���� �ֻ��� �θ� �� �ϳ��� �־��� ����



CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCameAffected(_bCamAff)
	, m_bMouseOn(false)
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
	MouseOnCheck();

	//if (KEY_AWAY(KEY::LBTN))
	//	m_bMouseOn = false;

	finalupdate_child();

}

void CUI::render(HDC _dc)
{
	// �׳� getpos��� �ϸ� vParnetpos�� �������� ���� �ʱ�ȭ ��ġ�� ������
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();


	if (m_bCameAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	if (m_bLbtnDown)
	{
		CSelectGDI select(_dc, PEN_TYPE::RED);

		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

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

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnClicked()
{

}

void CUI::MouseOnCheck()
{

	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();



	if (m_bCameAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}
	
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"MXY : %f, %f		on : %d", vMousePos.x, vMousePos.y, m_bMouseOn);
	SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);


}

