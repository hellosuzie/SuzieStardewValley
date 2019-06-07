#pragma once

class VEC2F
{
public:
	float X;
	float Y;

public:
	static const VEC2F One;
	static const VEC2F Zero;

public:
	static const VEC2F LEFT;
	static const VEC2F RIGHT;
	static const VEC2F UP;
	static const VEC2F DOWN;

public:
	VEC2F() : X(0.0f), Y(0.0f) {	}
	VEC2F(float _X, float _Y) : X(_X), Y(_Y) {	}
	VEC2F(int _X, int _Y) : X((float)(_X)), Y((float)(_Y)) {	}
	VEC2F(float _X, int _Y) : X((_X)), Y((float)(_Y)) {	}
	VEC2F(int _X, float _Y) : X((float)(_X)), Y((_Y)) {	}

public:
	int IX()	const { return (int)X; };
	int IY()	const { return (int)Y; };
	int IXH()	const { return (int)(X * 0.5f); };
	int IYH()	const { return (int)(Y * 0.5f); };

	float XH() const { return (X * 0.5f); };
	float YH() const { return (Y * 0.5f); };

	VEC2F VEC2FH() { return{ IXH(), IYH() }; }

	VEC2F operator +(const VEC2F& _Other) const
	{
		return{ X + _Other.X, Y + _Other.Y };
	}
	VEC2F operator -(const VEC2F& _Other) const
	{
		return{ X - _Other.X, Y - _Other.Y };
	}
	VEC2F operator *(const VEC2F& _Other) const
	{
		return{ X * _Other.X, Y * _Other.Y };
	}
	VEC2F operator *(const float _Num) const
	{
		return{ X * _Num, Y * _Num };
	}

	VEC2F& operator +=(const VEC2F& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}
	VEC2F& operator -=(const VEC2F& _Other) 
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}
	VEC2F& operator +=(const float _Num)
	{
		X += _Num;
		Y += _Num;
		return *this;
	}
};

class VEC2I
{
//이름을 안붙인 Struct는 멤버변수처럼 사용할 수 있다.
//union도 이름 안붙이면 그 안의 내용은 멤버변수처럼 사용할수이따.
public:
	union 
	{
		__int64 Value;
		struct 
		{
			int X;
			int Y;
		};
	};

public:
	operator __int64()
	{
		return Value;
	}

public:
	static const VEC2I IZero;

public:
	VEC2I() : X(0), Y(0) {}
	VEC2I(__int64 _Value) : Value(_Value) {}
	VEC2I(int _X, int _Y) : X(_X), Y(_Y) {}

public:
	VEC2I& operator -=(const VEC2F& _Other)
	{
		X -= (int)_Other.X;
		Y -= (int)_Other.Y;
		return *this;
	}
};

typedef VEC2F FPOS;
typedef VEC2F FSIZE;
typedef VEC2I IPOS;
typedef VEC2I ISIZE;

class FRECT
{
public:
	FPOS Pos;
	FSIZE Size;

public:
	FRECT() : Pos(), Size() {	}
	FRECT(FPOS _Pos, FSIZE _Size) : Pos(_Pos), Size(_Size) {	}

public:
	float FLEFT()		const { return Pos.X - Size.XH(); }
	float FRIGHT()		const { return Pos.X + Size.XH(); }
	float FTOP()		const { return Pos.Y - Size.YH(); }
	float FBOT()		const { return Pos.Y + Size.YH(); }
					
	FPOS FLEFTEDGE()	const { return{ FLEFT(), Pos.Y };	 }
	FPOS FRIGHTEDGE()	const { return{ FRIGHT(), Pos.Y };	 }
	FPOS FTOPEDGE()		const { return{ Pos.X, FTOP() };	 }
	FPOS FBOTEDGE()		const { return{ Pos.X, FBOT() };	 }
					
	FPOS FLEFTTOP()		const { return{ FLEFT(), FTOP() };	}
	FPOS FRIGHTTOP()	const { return{ FRIGHT(), FTOP() };	}
	FPOS FLEFTBOT()		const { return{ FLEFT(), FBOT() };	}
	FPOS FRIGHTBOT()	const { return{ FRIGHT(), FBOT() };	}

	int ILEFT()			{ return (int)FLEFT();	}
	int IRIGHT()		{ return (int)FRIGHT(); }
	int ITOP()			{ return (int)FTOP();	}
	int IBOT()			{ return (int)FBOT();	}

	IPOS ILEFTEDGE()	{ return{ ILEFT(), Pos.IY() };	}
	IPOS IRIGHTEDGE()	{ return{ IRIGHT(), Pos.IY() };	}
	IPOS ITOPEDGE()		{ return{ Pos.IX(), ITOP() };	}
	IPOS IBOTEDGE()		{ return{ Pos.IX(), IBOT() };	}
		 
	IPOS ILEFTTOP()		{ return{ ILEFT(), ITOP() };	}
	IPOS IRIGHTTOP()	{ return{ IRIGHT(), ITOP() };	}
	IPOS ILEFTBOT()		{ return{ ILEFT(), IBOT() };	}
	IPOS IRIGHTBOT()	{ return{ IRIGHT(), IBOT() };	}

};


