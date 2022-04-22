#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);

private:
	Vec2		m_vLookAt;		// ī�޶� ���� �ִ°� (ȭ���� �߽�)
	Vec2		m_vPrevLookAt;	// ī�޶� ���� ���������� ��ġ
	// �� �� ��ġ�� ���̰� �ް��ϰ� �������� �������ϰ� �̵��ϴ°� ���� ����!
	Vec2		m_vCurLookAt;	// ���� ��ġ�� ���� ��ġ ������ġ (�� Lookat)

	CObject*	m_pTargetObj;	// ī�޶� Ÿ�� ������Ʈ

	Vec2		m_vDiff;		// �ػ� �߽���ġ��, ī�޶� LookAt���� ���̰�

	float		m_fTime;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float		m_fSpeed;
	float		m_fAccTime;


public:
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	void SetLookAt(Vec2 _vLook)
	{
		// �Ÿ� = �ӷ� * �ð�
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	Vec2 GetRenderPos(Vec2 _vObjPos){ return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) {return  _vRenderPos + m_vDiff; }

public:
	void update();

private:
	// ������ ȭ�� �߾ӿ������� �󸶳� ������ �ִ���
	void CalDiff();
};
