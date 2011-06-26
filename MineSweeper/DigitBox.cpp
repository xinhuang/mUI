#include "DigitBox.h"

DigitBox::DigitBox(void)
{
	InitializeComponent();
}

DigitBox::~DigitBox(void)
{
}

void DigitBox::set_Value( int value )
{
	if (value < -99 || value > 1000)
		goto __overflow;

	value_ = value;
	value = value < 0 ? -value : value;

	int temp;
	char szbuf[32];
	for (int i = MAX_DIGITS - 1; i >= 0; --i)
	{
		if (value != 0)
		{
			temp = value % 10;
			value /= 10;
			_snprintf(szbuf, sizeof(szbuf)-1, "res/%d.png", temp);
			digits[i].Load(szbuf);
		}
		else
		{
			digits[i].Load(L"res/na.png");
		}
	}
	if (value_ == 0)
	{
		digits[MAX_DIGITS - 1].Load(L"res/0.png");
	}
	if (value_ < 0)
	{
		if (value_ < -99)
			goto __overflow;
		else
		{
			digits[0].Load(L"res/-.png");
		}
	}
	return;

__overflow:
	for (size_t i = 0; i < MAX_DIGITS; ++i)
		digits[i].Load(L"res/-.png");
}

void DigitBox::InitializeComponent()
{
	set_Size(Size(MAX_DIGITS * 13, 23));
	for (int i = 0; i < MAX_DIGITS; ++i)
	{
		digits[i].set_Size(Size(13, 23));
		digits[i].set_Location(Point(13 * i, 0));
		Controls.Add(digits[i]);
	}
}

int DigitBox::get_Value() const
{
	return value_;
}
