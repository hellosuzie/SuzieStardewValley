#include "stdafx.h"
#include "NumberActor.h"

NumberActor::NumberActor() : m_Value(1), m_NumberCount(0)
{
}


NumberActor::~NumberActor()
{
}

void NumberActor::NumberInit(size_t _NumberCount, const WCHAR * _Name, FSIZE _Numbersize)
{
	m_NumberCount = _NumberCount;
	m_NumRenderVec.reserve(m_NumberCount);
	m_CutNumberVec.reserve(m_NumberCount);
	m_NumSpriteName = _Name;

	for (int i = 0; i < m_NumberCount; i++)
	{
		SingleActorRender* Render = MakeRender<SingleActorRender>(18);
		Render->SetSprite(L"Number.bmp", 0);
		Render->Size(_Numbersize);
		Render->Pivot({ _Numbersize.X * i , 0.0f });
		Render->CameraMode(false);

		m_CutNumberVec.push_back(0);
		m_NumRenderVec.push_back(Render);
	}
}

void NumberActor::Init()
{

}

void NumberActor::PrevUpdate()
{

}

void NumberActor::Update()
{
	int Count = 0;
	int TempValue = m_Value;

	while (TempValue != 0)
	{
		TempValue = TempValue / 10;
		++Count;
	}
	if (m_NumberCount < Count)
	{
		for (int i = 0; i < m_NumberCount; i++)
		{
			m_CutNumberVec[i] = 9;
		}
	}
	else if (0 >= m_Value)
	{
		for (int i = 0; i < m_NumberCount; i++)
		{
			m_CutNumberVec[i] = 0;
		}
	}
	else
	{
		int DivNumber = 1;

		for (int i = 0; i < Count - 1; i++)
		{
			DivNumber *= 10;
		}
		for (int i = 0; i < m_NumberCount - Count; i++)
		{
			m_CutNumberVec[i] = 0;
		}

		int NCount = m_NumberCount - Count;
		TempValue = m_Value;

		while (NCount < m_NumberCount)
		{
			m_CutNumberVec[NCount] = TempValue / DivNumber;
			TempValue -= m_CutNumberVec[NCount] * DivNumber;
			DivNumber /= 10;
			++NCount;
		}
		int a = 0;
	}

	for (size_t i = 0; i < m_CutNumberVec.size(); i++)
	{
		m_NumRenderVec[i]->SetSprite(m_NumSpriteName.c_str(), m_CutNumberVec[i]);
	}
}

void NumberActor::LaterUpdate()
{

}