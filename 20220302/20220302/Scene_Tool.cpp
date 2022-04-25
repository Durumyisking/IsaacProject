#include "pch.h"
#include "Scene_Tool.h"

#include "Tile.h"

#include "ResMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "UIMgr.h"
#include "PathMgr.h"

#include "UI.h"
#include "BtnUI.h"
#include "PanelUI.h"

#include "SelectGDI.h"

#include "resource.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	: m_pTileTex(nullptr)
	, m_pUI(nullptr)
{

}


CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	if (KEY_TAP(KEY::P))
		CUIMgr::GetInst()->SetFocusedUI(m_pUI);

	if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTile(L"tile\\Test.tile");
	}
	if (KEY_TAP(KEY::O))
	{
		LoadTile(L"tile\\Test.tile");
	}

}

void CScene_Tool::render(HDC _dc)
{
	CSelectGDI pen(_dc, PEN_TYPE::GREEN);
	CSelectGDI brush(_dc, BRUSH_TYPE::WHITE);

	Rectangle(_dc, 0, 0, static_cast<int>(m_vResolution.x), static_cast<int>(m_vResolution.y));

	CScene::render(_dc);
}



void CScene_Tool::Enter()
{
	// Ÿ�� ����
	CreateTile(4, 8);

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"PanelUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(m_vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"BtnUI");
	pBtnUI->SetScale(Vec2(100.f, 50.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	// pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);


	CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene,0,0);
	AddObject(pClonePanel, GROUP_TYPE::UI);

	m_pUI = pClonePanel;

	CCamera::GetInst()->SetLookAt(m_vResolution / 2.f);

}

void CScene_Tool::Exit()
{
	DeleteAll();
}

void CScene_Tool::SetTileIdx()
{
	Vec2 vMousePos = MOUSE_POS;

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		UINT iTileX = (int)GetTileX();
		UINT iTileY = (int)GetTileY();

		// ������ �����ϱ� UINT ���� int�� ����
		int iCol = (int)vMousePos.x / ROCK_SIZE;
		int iRow = (int)vMousePos.y / ROCK_SIZE;


		// bmp���� �Ѿ���� ���� �ȵǰ� ó��
		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector <CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();


	}
}

void CScene_Tool::SaveTile(const wstring & _strRelativePath)
{
	// ������ �Լ����� �ʿ�� �ϴ� ���� ��θ� ���� ����� ��
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;

	// �츰 2����Ʈ ���ڿ��� ���ϱ�  wopen ���
	// ������ "w"�� ������ ���� ������ �Ѵٴ� �ǹ̶� ������ ������ ���� �������
	// "b" �츮�� ����ϴ� ��Ʈ(binary) ������ ���·� �����ϰڴ�.
	// �Ⱥ����� �츮�� �����̳� �ҷ����� ��Ʈ �����͸� char ������ ������
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);


	// ������ ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile); 

	// ��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}



	fclose(pFile);
}


void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}







// �����Լ� �Դϴ�
// Tile Count Window Proc
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{

			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// tool scene������ �����ϴ� �Լ��ϱ� ó�� ������
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);



			// EndDialog�� �ι�° ���ڴ� dialogbox �Լ� ��������� �����
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}