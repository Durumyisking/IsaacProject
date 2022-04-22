#include "pch.h"
#include "Camera.h"

#include "Object.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"


CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
{
}


CCamera::~CCamera()
{
}



void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 300.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 300.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 300.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 300.f * fDT;

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ������ ����
	// �� ���̸�ŭ �ٸ� OBj���� �ݴ�� �̵������ٰ�
	CalDiff();

}

void CCamera::CalDiff()
{
	// prevlook �� ����look�� ���̰��� �����ؼ� ������ lookat�� ���Ѵ�.
	// m_vLookAt - m_vPrevLookAt = ����

	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		// ������ �ð��� ���� �ʾ��������� ����ص� �ӵ��� ���缭 �̵�
		// SetLookat�� ���� ������
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize()*m_fSpeed * fDT;
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;

}