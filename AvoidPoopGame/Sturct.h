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

enum class ITEM_TYPE 
{
	BULLTE_SIZE_UP, 
	OFFENCE_POWER_UP,
	END
};

// float Ÿ���� x, y ���� ��Ÿ���� ����ü
struct FPOINT 
{
	float mX;
	float mY;
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


