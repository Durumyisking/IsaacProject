#include "pch.h"
#include "Heart.h"

#include "ResMgr.h"
#include "Texture.h"

#include "Player.h"

CHeart::CHeart(int _iRenderGap)
	: CUI(false)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"texheart", L"texture\\UI\\ui_hearts.bmp");
	SetScale(Vec2(16.f, 16.f));
	SetPos(Vec2(100.f + (32.f*_iRenderGap), 50.f));
	
}

CHeart::~CHeart()
{
}

void CHeart::update()
{
	// 하트를 배열로 선언한다
// 크기는 player max hp/2

	

	



}

void CHeart::render(HDC _dc)
{
	CUI::render(_dc);




}
