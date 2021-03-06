#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Head.h"
#include "Body.h"


#include "Core.h"

#include"TimeMgr.h"
#include"PathMgr.h"
#include"ResMgr.h"
#include"CollisionMgr.h"
#include"EventMgr.h"
#include"SceneMgr.h"
#include "KeyMgr.h"

#include "WallCollider.h"
#include "SceneMgr.h"

#include "UI.h"
#include "Heart.h"
#include"PanelUI.h"
#include"BtnUI.h"


CScene_Start::CScene_Start()
	: vecHeartUI{}

{
	m_pBgTex = CResMgr::GetInst()->LoadTexture(L"BgTex", L"texture\\BackGround\\BG_basement.bmp");
	m_eAdjacencyRoom[(UINT)DIR::N] = SCENE_TYPE::ITEM;
	m_eAdjacencyRoom[(UINT)DIR::S] = SCENE_TYPE::TOOL;
}


CScene_Start::~CScene_Start()
{
	DeleteAll();
}


void CScene_Start::Enter()
{
	// Object 추가
	CObject* pPlayer = new CPlayer;
	CPlayer* objPlayer = (CPlayer*)pPlayer;

	m_pPlayer = objPlayer;

	objPlayer->init();

	SetPlayerPos(objPlayer);
	pPlayer->SetName(L"Player");

	CreateObject(pPlayer, GROUP_TYPE::PLAYER);

	AddDoor(DIR::N);
	AddDoor(DIR::S);
	AddWall();


	round(213);

	int iHeartSize = objPlayer->GetStat().m_iMaxHP / 2;
	for (int i = 0; i < iHeartSize; ++i)
	{
		CUI* pHeartUI = new CHeart(i + 1);
		vecHeartUI.push_back(pHeartUI);
		AddObject(pHeartUI, GROUP_TYPE::UI);
	}

	// 타일 로딩
	// LoadTile(L"Tile\\start.tile");


	// 충돌 지정

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::DOOR);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::TEARWALL, GROUP_TYPE::PROJ_PLAYER);

	


	// 카메라 효과 지정
	CCamera::GetInst()->FadeIn(2.f);

}

void CScene_Start::Exit()
{
	DeleteAll();

	// 다른 씬에서는 다른 충돌 그룹을 쓸 수 있기 때문에 해제시켜주어야함
	CCollisionMgr::GetInst()->Reset();

}

void CScene_Start::update()
{
	CScene::update();


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}



	// 카메라 전환
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}

	int iIdx = m_pPlayer->GetStat().m_iHP / 2;
	if (1 == m_pPlayer->GetStat().m_iHP % 2)
	{
		vecHeartUI[iIdx]->SetSlice(Vec2(1, 0));
	}
}



void CScene_Start::render(HDC _dc)
{

	int iWidth = (int)m_pBgTex->GetWidth();
	int iHeight = (int)m_pBgTex->GetHeight();


	StretchBlt(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y), m_pBgTex->GetDC(), 0, 0, iWidth, iHeight, SRCCOPY);	

	CScene::render(_dc);

}