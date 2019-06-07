#include "stdafx.h"
#include "RoomBack.h"
#include "SingleActorRender.h"

RoomBack::RoomBack()
{
	//0, 0으로 포스를 정해주면 실제로 0, 0에서부터 그려지는 것이 아니라
	//내가 이미지가 가운데 나오게 하기 위해서 이미지사이즈 반만큼 빼줬으니까 반이 잘려서 나온다.
	//그러니까 이미지 사이즈 반만큼 다시 더해줘야 0, 0부터 나오게되는것.
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
