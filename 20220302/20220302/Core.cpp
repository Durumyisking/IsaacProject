#include "pch.h"
#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
#include "Camera.h"

#include "Object.h"


CCore::CCore()
	: m_hWnd(0)
	, m_vResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CCore::~CCore()
{	
	ReleaseDC(m_hWnd, m_hDC);
	
	// compatible�� ������ ģ������ delete�� �����ؾ���
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
		DeleteObject(m_arrPen[i]);
}

// CObject g_obj;

int CCore::init(HWND _hWnd, Vec2 _vResolution)
{
	m_hWnd = _hWnd;
	m_vResolution = _vResolution;


	
	RECT rt = { 0.f, 0.f, m_vResolution.x, m_vResolution.y };
	
	
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); 
	SetWindowPos(_hWnd, nullptr, 0, 0,
		rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd); 

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� ����
	m_hBit = CreateCompatibleBitmap(m_hDC, (int)m_vResolution.x, (int)m_vResolution.y);
	// �� ��¥ ��Ʈ�ʿ� ���� ������ �� �� �� ����� ��¥ ��Ʈ�ʿ� �ø�����
	// �׷��� ���� �ٸ� ������Ʈ���� ���� ���������� ����
	m_memDC = CreateCompatibleDC(m_hDC); // ȭ�鿡 ���� ��µ����ʴ� memory dc ����
	// DC�� ���۸� �뵵�� ��Ʈ���� ����ϰ���	
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);	// ������ ���� bitmap�� �ʿ���� ���ο� ��Ʈ������ ��ü�ع������
							// �������� �޸��� ���� ��Ʈ�� ����

	// �귯�ÿ� �� ����
	CreateBrushPen();

	// �Ŵ��� �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CCollisionMgr::GetInst()->init();
	CEventMgr::GetInst()->init();


	return S_OK;
}


void CCore::progress()
{
	// Mgr update (1 frame cycle)
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	// CCamera::GetInst()->update();

	// Scene update
	CSceneMgr::GetInst()->update();

	// check collision
	CCollisionMgr::GetInst()->update();
	
	// =========
	// Rendering
	// =========

	// ȭ�� Ŭ����
	Rectangle(m_memDC, -1, -1, (int)m_vResolution.x + 1, (int)m_vResolution.y + 1);


	CSceneMgr::GetInst()->render(m_memDC);

	// ��Ʈ���̶�� �ҷ���
	BitBlt(m_hDC, 0, 0, (int)m_vResolution.x, (int)m_vResolution.y,
		m_memDC, 0, 0, SRCCOPY); // hdc���� ������ ũ�⸸ŭ ������ dc(memdc)�� ������ ��ġ���� ���ȼ��� ����

	// �̺�Ʈ ���� ó��
	CEventMgr::GetInst()->update();

	
	
}

void CCore::CreateBrushPen()
{
	// GetStockObject���� ���־��°͵��� �޾ƿü� �ְ� ����
	// Window�Ҽ��̶� �츮�� delete �� �� �ʿ� ����
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// red green blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
