#pragma once
#include "Scene.h"
class CScene_Start :
	public CScene
{

private:
	int m_iWave;
	
	
public:
	CScene_Start();
	~CScene_Start();

public:
	virtual void Enter();	// virtual ����� �Ǵµ� �򰥸���� ������
	virtual void Exit();
	virtual void update();

public:
	virtual void render(HDC _dc);

};

	