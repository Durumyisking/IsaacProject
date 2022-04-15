#pragma once
#include "Camera.h"

class CCollider;
class CAnimator;

class CObject
{

private:
	wstring		m_strName;

	Vec2		m_vPos;		// ������ ���� ��ġ
	Vec2		m_vScale;

	CCollider*	m_pCollider; // �浹ü �ʿ��ϸ� �� ������ ������ �Ȱ����� �Ǵ� ��
	CAnimator*	m_pAnimator;

	bool		m_bAlive;	// ��Ҵ� �׾���

protected:
	Vec2		m_vResolution;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	bool IsDead() { return !m_bAlive; }



public:
	virtual void update() = 0;

	virtual void finalupdate();

	virtual void render(HDC _dc);

	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

	void component_render(HDC _dc);

	// �ڱ� �ڽ��� ��ü�� �������Ѽ� �ǵ�����
	virtual CObject* Clone() = 0;


private:
	// �ڽ� obj ������ �� �Լ��� ��� �Ұ����ϴ�
	// ������ eventmgr������ ����ϰ� �� ��
	friend class CEventMgr;
	void SetDead() { m_bAlive = false; }

};
