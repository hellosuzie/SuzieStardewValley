#include "stdafx.h"
#include "StoreDask.h"
#include "SingleActorRender.h"

StoreDask::StoreDask()
{
	Pos({ 384, 266 });
}


StoreDask::~StoreDask()
{
}

void StoreDask::Init()
{
	m_Dask = MakeRender<SingleActorRender>(3);
	m_Dask->Size({ 384, 256 });
	m_Dask->SetSprite(L"StoreDask.bmp");
}

void StoreDask::PrevUpdate()
{
}

void StoreDask::Update()
{
}

void StoreDask::LaterUpdate()
{
}
