#include "pch.h"





/*

	r * 3.14 = �ѷ��� ����

	���� : �������� ȣ�� ���̿��� �������� ������

	�츮�� ���̸� ������ ������

	3.14 ���� = 180��

	������ 1�϶� ȣ�� ���� = ������



	cos = �غ� / ��������, ������ 1�϶� �غ��� ����������� ����
	�������� �״��

	cos0 = 1	cos90 = 0	cos180 = -1 
	sin0 = 0	sin90 = 1	sin180 = 0


	�츮�� �������� 100�� ������ 1�����Ӹ��� 100 * DT�� �̵��ؼ� 100�� ���� �̶� 1�� �ɸ�
	�츮�� 45�� �������� 100�� ����ʹ� ĥ�� 45�� �������� 100�� ���� �� �׶� ��ǥ�� x, y�� ���ؼ� ��Ÿ��� ������ ���ؾ鸶
	�׶��� x�� 100cos45		y�� 100sin45
	d

*/
	


/*
	project �帧

	***obj delete***
	1frame
	update		: 
	finalupdate	: 2. oncollision enter
	collision	: 1. �ݸ��� �߻�
	render		: 4. obj set dead, 5. deadvec.pushback(obj)
	event		: 3. Delete event

	2frame
	update		: 
	finalupdate	: 
	collision	: 
	render		: 6. dead������ obj scene������ erase
	event		: 7. ����س��� deadvec ����

*/


/*

	Scene �� �ٲ�
	A scene�� ��
	change scene �������� ���� scene�� �ѱ�ڴٰ� ��ŷ�صа͵鸸 ���� ��Ƽ� 
	���� scene�� enter�� �־��ָ� ������ü�� �Ѱ��� �� ����

*/

/*
	Unity Build
	��ҿ��� �츮�� Ŭ�������� ����� �ڵ��� ������
	�����Ҷ��� �ϳ��� Cpp�� ��Ƽ� �����Ѵ�

	��� Ŭ������ ���忡�� ���ܽ�Ű��
	�ӽ� cpp file�� ���� 
	�� cpp file��
	include cpp

	��� : ������Ʈ vcsproj ������ �޸������� �� ��
	  <PropertyGroup>
	<EnableUnitySupport>true</EnableUnitySupport>
  </PropertyGroup>
  �̰� �ְ� ���־� ���� Ų ����
  ������Ʈ �Ӽ� - c/cpp - unitybuild
  unity ���� ���͸� $(ProjectDir)\������\
  unity ������ �ּ� �ҽ� �� 8
  
  ���� ���μ��� ������ = yes
  �̸������ϵ� ��� -> ���
  
	
*/

/*
	������ �ٸ� â�� ������� ���Ѵ� (���α׷��� ����� ������)
	ex) ���� �޽����� �����غ��� �������߸� Ȯ�ζǴ� ��Ҹ� ����߸� �������� �����̰���
	�׵��� �ڿ��ִ� â�� ������ �Ұ�

*/