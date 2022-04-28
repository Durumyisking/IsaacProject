#pragma once
#include "Object.h"
#include"Texture.h"

class CAnimation;
class CItem;

class CPlayer :
	public CObject
{
private:
	DIR m_ePrevDoorDir;


protected:

	Stat stat;


	double		m_dPrevTime; // ��Ÿ ��Ÿ��

	vector<CItem*>	m_vInventory;
	CItem*			m_GetItemCheck;

public:
	CPlayer();
	~CPlayer();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName,  Vec2 _vOffset);

	// ȹ�� ������ üũ -
	// �̹� �����ӿ� ȹ���� �������� ������ -
	// �ݸ��� �̺�Ʈ���� �κ��丮 �� ȹ�� �����ۿ� �߰�-
	// update�� ȹ�� ������ üũ�� -
	// ȹ�� ȿ�� ó��
	// ȹ�� ������ ����


	CLONE(CPlayer);

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual void CreateMissile(Vec2 _vDir);

public:
	// �̹������ӿ� ȹ�� �������� �־����� ������ ȿ���� �ο�
	void ItemCheck();
};

