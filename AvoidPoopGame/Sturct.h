#pragma once

// 내가 사용할 키 목록
enum class KEY_LIST
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	ESCAPE,
	SPACE,

	LEFT,
	TOP,
	RIGHT,
	BOTTOM,

	LSHIFT,
	LCTRL,
	LALT,

	LBUTTON,
	RBUTTON,

	END
};

// 키의 상태를 나타내는 enum 값
enum class KEY_STATE
{
	TIC,
	PRESS,
	ANY,
	NONE,
	END
};

// float 타입의 x, y 값을 나타내는 구조체
struct FPOINT
{
	float mX;
	float mY;

	FPOINT(float x, float y) 
		: mX(x)
		, mY(y)
	{
	}

	FPOINT(const FPOINT& fPoint)
		: mX(fPoint.mX)
		, mY(fPoint.mY)
	{
	}

	FPOINT(FPOINT&& fPoint) noexcept
		: mX(fPoint.mX)
		, mY(fPoint.mY)
	{
		fPoint.mX = 0.f;
		fPoint.mY = 0.f;
	}

	FPOINT(const POINT& point)
		: mX((float)point.x)
		, mY((float)point.y)
	{
	}

	FPOINT(POINT&& point) noexcept
		: mX((float)point.x)
		, mY((float)point.y)
	{
		point.x = 0;
		point.y = 0;
	}

	void operator=(const FPOINT& rhs) 
	{
		if (*this == rhs) 
		{
			return;
		}

		mX = rhs.mX;
		mY = rhs.mY;
	}

	void operator=(FPOINT&& rhs) noexcept
	{
		if (*this == rhs)
		{
			return;
		}

		mX = rhs.mX;
		mY = rhs.mY;

		rhs.mX = 0.f;
		rhs.mY = 0.f;
	}

	bool operator==(const FPOINT& rhs)
	{
		return mX == rhs.mX && mY == rhs.mY;
	}

	bool operator !=(const FPOINT& rhs) 
	{
		return !(*this == rhs);
	}
};

struct LENGTH
{
	int mWidth;
	int mVertical;
};

// 키의 상태 정보를 가지는 구조체
struct KEY_INFO
{
	KEY_STATE mKeyState;
	bool mPrevState;
};

struct COLOR
{
	int r, g, b;
};


