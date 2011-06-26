#include "MovingForm.h"

MovingForm::MovingForm()
{
	set_BackgroundImage(Image::FromFile(L"res/anchor.png"));
	Random random;
	delta_.X = random.Next(-5, 5);
	delta_.Y = random.Next(-5, 5);

	set_Size(Size(100, 50));
}

MovingForm::~MovingForm()
{
}

void MovingForm::FlipHori()
{
	delta_.X = -delta_.X;
}

void MovingForm::FlipVert()
{
	delta_.Y = -delta_.Y;
}

void MovingForm::Move()
{
	Point loc = get_Location();
	loc.X += delta_.X;
	loc.Y += delta_.Y;
	set_Location(loc);
}
