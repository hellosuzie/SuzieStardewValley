#pragma once
class MathMgr
{
public:
	static const float PI;
	static const float DTOR;
	static const float RTOD;

public:
	//� ��׸� �� �־��ָ� �װ� �������� �ٲ㼭 �� ���ȿ� �´� {�غ�(x), ����(y)}�����ϴ� �Լ�
	static FPOS DTODIR(float _D)
	{
		float R = _D * DTOR;
		return{ cosf(R), sinf(R) };
	}
	
	//����� �ٲٱ�
	static float PositiveNum(const float _Num);
	//���� ����� ���ϱ�
	static float PointToPointDis(const FPOS _Left, const FPOS _Right);

	static float PointToPointRad(const FPOS _Left, const FPOS _Right);
	static int PointToPointDig(const FPOS _Left, const FPOS _Right);
	//�÷��̾� �������� �Ѿ� ���
	static FPOS PointToPointDir(const FPOS _Left, const FPOS _Right);
	static bool RectToRect(const FRECT& _Left, const FRECT& _Right);

private:
	MathMgr();
	~MathMgr();
};

