#include "pch.h"
#include "PathMgr.h"

#include "Core.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}


CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	// �츮�� ���־�Ʃ������� ����� ���� �����ϸ� 
	// ���־�Ʃ����� ���� ����ǰ�, ���־�Ʃ������� ����� ���� �ٽ� ������
	// ���� ���� ��θ� ������Ʈ ���� ��η� �����
	// �츮�� ������Ʈ �Ӽ����� �۾� ���丮�� solutiondir�� �ִ°����� �������ٰ�
	GetCurrentDirectory(255, m_szContentPath); // m_szContentPath�� ���� ��θ� ä���


	// ../ ../ �̵��� ���� �ȵǰ� ��� �޴� �Լ��� ������..
	// �츮�� ��θ� ���� ��
	// asdf\\wqeqe\\weqe\\qwe �� �޾�����
	// �� �������� qwe���� ������ �о ã�� ������ ������ qwe���� \\�� \0���� �ٲ㼭
	// ���ڿ��� ���� �����ؼ� ������ �ö󰥰���
	// �츮�� �� �ܰ踸 �ö󰡸� �Ǵϱ� ���� ù��° \\������ break �ɾ��

	int iLen = wcslen(m_szContentPath);

	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}


	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}








