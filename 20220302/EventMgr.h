#pragma once

// �� ��Ȳ���� �Ͼ�� �̺�Ʈ���� �ѹ��� ��Ƽ� ó������ �Ŵ���
// ��� �߿� �̺�Ʈ���� ��Ƽ� ���� �����ӿ� �Ѳ����� ó���Ѵ�


struct tEvent
{
	EVENT_TYPE		eEvent;
	DWORD_PTR		lParam;	// (�̺�Ʈ Ÿ�Ը��� �ٸ� param ������)
							// DWORD�� �׳� ���� 32bit�� �����Ҷ�
							// lParam�� ������ ������ ���� ��� �� �ֱ� ������
							// �߰����ڰ� �ʿ� ���� �� ����
							// �׷��� �츮�� �������� ���ִ� ��ũ�� ����Ұ�
	DWORD_PTR		wParam;	
};


class CEventMgr
{
	SINGLE(CEventMgr);
private:
	vector<tEvent> m_vecEvent;

	vector<CObject*> m_vecDead;


public:
	void init();
	void update();
		
	void AddEvent(const tEvent& _event)
	{
		m_vecEvent.push_back(_event);
	}

private:
	void Execute(const tEvent& _eve);

};

