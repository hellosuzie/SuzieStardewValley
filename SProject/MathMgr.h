#pragma once
class MathMgr
{
public:
	static const float PI;
	static const float DTOR;
	static const float RTOD;

public:
	//어떤 디그리 값 넣어주면 그걸 라디안으로 바꿔서 그 라디안에 맞는 {밑변(x), 높이(y)}리턴하는 함수
	static FPOS DTODIR(float _D)
	{
		float R = _D * DTOR;
		return{ cosf(R), sinf(R) };
	}
	
	//양수로 바꾸기
	static float PositiveNum(const float _Num);
	//빗변 양수로 구하기
	static float PointToPointDis(const FPOS _Left, const FPOS _Right);

	static float PointToPointRad(const FPOS _Left, const FPOS _Right);
	static int PointToPointDig(const FPOS _Left, const FPOS _Right);
	//플레이어 방향으로 총알 쏘기
	static FPOS PointToPointDir(const FPOS _Left, const FPOS _Right);
	static bool RectToRect(const FRECT& _Left, const FRECT& _Right);

private:
	MathMgr();
	~MathMgr();
};

