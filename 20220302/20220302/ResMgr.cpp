#include "pch.h"
#include "ResMgr.h"
#include "Res.h"

#include"PathMgr.h"
#include"Texture.h"

CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

// _strkey : �ؽ�ó�� ResMgr���� ã�ƿ��� ���� key��, _strRelativePath : ����� ��� (���� ��θ� pathmgr���� �ذ�)
CTexture * CResMgr::LoadTexture(const wstring & _strKey, const wstring & _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)	// _strKey�� ���� �ؽ�ó�� �����ϸ�
		return pTex;		// ���� �ؽ�ó ��ȯ


	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture; // �ؽ�ó�� ������ ��ü �����Ҵ�
	pTex->Load(strFilePath); // �ؽ�ó ��ü�� Bitmap�� ���� ��� �޾Ƽ� ����
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture * CResMgr::FindTexture(const wstring & _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	// �����ʹ� res���� �츰 �ؽ��� �ٲ��� ������ �ٿ�ĳ����
	return (CTexture*)iter->second;
}
