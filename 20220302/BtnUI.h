#pragma once
#include "UI.h"
#include "Scene.h"
#include "Object.h"

class CObject;
class CScene;


// ��ȯŸ���� void��		�� �� ���� ���ڰ� ���� �Լ��� BTN_FUNC���� ������
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// �Լ������ͷ� ����Լ� ȣ���Ҷ� ������ ����
// ����Լ� �����ʹ� ������Ͱ� �����Լ� �����Ϳʹ� �ٸ�
// void(classname)
// �̷��� �ϸ� toolscene�� �ִ� ����Լ��� ��� �Լ� �����͸� �����

// �̷��� �ص� ������ typedef void(CScene_Tool::*TOOL_SCENE_MEMFUNC)(void);
typedef void(CScene::*SCENE_MEMFUNC)(void);
// �̷��� �θ�Ÿ������ ����� �ڽĵ� ����� �Լ����� �޾ƾ�������
// ��� Ŭ������ �Լ��� �� �ް� ������ �츮 ������Ʈ������ ��θ� �ƿ츣�� �ֻ��� �θ� ������
// �����Ƽ� ���Ұ�
typedef void(CObject::*OBJECT_MEMFUNC)(void);


class CBtnUI :
	public CUI
{
private:
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;

	SCENE_MEMFUNC	m_pSceneFunc;

	// �Լ��� ������ �ν��Ͻ�
	CScene*			m_pSceneInst;



public:
	CBtnUI();
	~CBtnUI();

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();


	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}

	void SetClickedCallBack(SCENE_MEMFUNC _pSceneFunc, CScene* _pScene)
	{
		m_pSceneFunc = _pSceneFunc;
		m_pSceneInst = _pScene;
	}

	CLONE(CBtnUI);
};

