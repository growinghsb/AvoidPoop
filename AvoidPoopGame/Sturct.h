#pragma once

// ���� ����� Ű ���
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

// Ű�� ���¸� ��Ÿ���� enum ��
enum class KEY_STATE
{
	TIC,
	PRESS,
	ANY,
	NONE,
	END
};

enum class ITEM_LIST 
{
	HP, 
	MP, 
	OFFENCE_POWER, 
	BULLET_UP,
	END
};

enum class OBJ_TYPE 
{
	PLAYER,
	ENEMY, 
	OBSTACLE,
	PBULLET, 
	PMISSILE, 
	ITEM, 
	END
};

// float Ÿ���� x, y ���� ��Ÿ���� ����ü
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

// Ű�� ���� ������ ������ ����ü
struct KEY_INFO
{
	KEY_STATE mKeyState;
	bool mPrevState;
};

struct COLOR
{
	int r, g, b;
};


