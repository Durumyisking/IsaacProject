#pragma once

class CCollider;

union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	// �浹 �׷� üũ����Ʈ m_arrCheck[32]
	// �� ���� �浹�� �� ���� �� �浹�ڷ� ����
	// �� �浹�ڴ� 32���� ��Ʈ�� �̷���� �־�
	// �� �պ�Ʈ�� Group_type�� default�� ���� ������Ʈ ���� ���ʷ� grouptype�� ���� enum���� �����Ѵ�
	// �� ��Ʈ�� 1�̸� m_arrCheck[i]�� group i�� �ش� ��Ʈ�� �浹�Ѵٴ� ���̴�
	// �̷��� ������ ����� ���� üũ����Ʈ�� �����µ�
	// �밢�� ������ ��Ī�̹Ƿ� �ʿ䰡 ����

	// UINT�� 4����Ʈ�ϱ� 32*32�� �������
	UINT					m_arrCheck[(UINT)GROUP_TYPE::END];
	
	// key���� �� collider�θ� ���� �� �ִ� ���̵��̾�� �� (key �ϳ��� UINT�ϱ�)
	map	<ULONGLONG, bool>	m_mapColInfo;

	// �浹ü���� ���� ������ �浹 ����
	// �浹�߿� ���� �������� �浹 ������ ������ obj�� ���ļ� �������� ���� ��
	// �ٵ� ��� obj�� ���� Ȯ���ϸ� ���� ��ȿ����
	// �׷��� Ž���Ҷ� ���� map���� �ؾ���
	// �� Ű�� �� �浹ü�� ������ Ž���� �� �־����
	// �̶� Ű�� �� �浹ü ������ ���� �����ؼ� ���� ��ĥ �� ���� �����̿��� ��
	// �� �浹ü�� ��ĥ�� ���� �ٸ� id���� �ް� �� ��




public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); // ������ �ּҸ� ������ ������ŭ ������ ����Ʈ������ ����
																	 // 4byte * 32idx �� m_arrCheck�� ��� �ε����� ��Ʈ�� 0���� �����
	}

private:
	void CollisionGroupupdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* pLeftCol, CCollider* pRightCol);

};