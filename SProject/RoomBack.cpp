#include "stdafx.h"
#include "RoomBack.h"
#include "SingleActorRender.h"

RoomBack::RoomBack()
{
	//0, 0���� ������ �����ָ� ������ 0, 0�������� �׷����� ���� �ƴ϶�
	//���� �̹����� ��� ������ �ϱ� ���ؼ� �̹��������� �ݸ�ŭ �������ϱ� ���� �߷��� ���´�.
	//�׷��ϱ� �̹��� ������ �ݸ�ŭ �ٽ� ������� 0, 0���� �����ԵǴ°�.
	Pos({ 1088 * 0.5f, 960 * 0.5f });
}


RoomBack::~RoomBack()
{
}

void RoomBack::Init()
{
	m_RoomBack = MakeRender<SingleActorRender>(0);
	m_RoomBack->SetSprite(L"RoomMap.bmp");
	m_RoomBack->Size({ 1088, 960 });
}

void RoomBack::PrevUpdate()
{
}

void RoomBack::Update()
{
}

void RoomBack::LaterUpdate()
{
}
