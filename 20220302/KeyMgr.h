#pragma once


// keymgr ��� ����

// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ����

// 2. Ű �Է� �̺�Ʈ�� ��ü������ ó��
// tap, hold, away


enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN, RBTN,

	LAST
};

enum class KEY_STATE
{
	TAP,	// �� ���� ����
	HOLD,	// ������ �ִ�
	AWAY,	// �� �� ����
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ���
};


struct tKeyInfo
{
	KEY_STATE	eState;	// Ű�� ����
	bool		bPrev;	// ���� �����ӿ� Ű�� ���ȴ��� �ƴ���
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;	// ������ idx�� KEY ��
								// idx 0�� left

	// ���� ���콺 ��ġ
	Vec2			m_vCurMousePos;




public:
	void init();
	void update();


public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMousePos() { return m_vCurMousePos; }
	
};

