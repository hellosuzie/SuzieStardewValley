#include "stdafx.h"
#include "MathMgr.h"
#include <math.h>

const float MathMgr::PI = 3.14159265359f;
const float MathMgr::DTOR = PI / 180;
const float MathMgr::RTOD = 180 / PI;

float MathMgr::PositiveNum(const float _Num)
{
	return _Num > 0.0f ? _Num : _Num * -1.0f;
}

float MathMgr::PointToPointDis(const FPOS _Left, const FPOS _Right)
{
	//���̿� �غ� ����� ���ϱ�
	float LeftRightX = PositiveNum(_Left.X - _Right.X);
	float LeftRightY = PositiveNum(_Left.Y - _Right.Y);

	return sqrtf(pow(LeftRightX, 2) + pow(LeftRightY, 2));
}

float MathMgr::PointToPointRad(const FPOS _Left, const FPOS _Right)
{
	//���� ó���� ���ؾ� �� ��
	//�������� ���ϱ�
	float Widthline = _Right.X - _Left.X;
	float Heightline = _Right.Y - _Left.Y;

	float HLine = PointToPointDis(_Left, _Right);

	//�������� �غ��� �ڻ��ΰ�
	float CosS = Widthline / HLine;

	//�ڻ��ΰ��� ��ũ�ڻ��� �׷����� ������ ���Ȱ��� ���ϵȴ�.
	float Radian = acosf(CosS);

	if (0 <= HLine && 0 <= Heightline)
	{
		Radian = (PI * 2) - Radian;
	}

	return Radian;
}

int MathMgr::PointToPointDig(const FPOS _Left, const FPOS _Right)
{
	float Rad = PointToPointRad(_Left, _Right);
	return (int)(Rad * RTOD);
}

FPOS MathMgr::PointToPointDir(const FPOS _Left, const FPOS _Right)
{
	float Rad = PointToPointRad(_Left, _Right);
	//�غ�, ���� �� �����ϴ� �Լ�. = �� ����
	return{ cos(Rad), -sin(Rad) };
}

bool MathMgr::RectToRect(const FRECT & _Left, const FRECT & _Right)
{
	if (_Left.FLEFT() > _Right.FRIGHT())
	{
		return false;
	}
	if (_Left.FRIGHT() < _Right.FLEFT())
	{
		return false;
	}
	if (_Left.FTOP() > _Right.FBOT())
	{
		return false;
	}
	if (_Left.FBOT() < _Right.FTOP())
	{
		return false;
	}
	return true;
}

MathMgr::MathMgr()
{
}


MathMgr::~MathMgr()
{
}
