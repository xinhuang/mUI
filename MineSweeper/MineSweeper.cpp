#include "MineSweeper.h"

#include "PHGE.h"

#include <algorithm>
using namespace std;

#include "DigitBox.h"

MineSweeper::MineSweeper() : elapsed_(0.f), started_(false), pressed_tile_(-1)
{
	level_ = Intermediate;
	set_Text(L"mUI Example - Mine Sweeper");
	set_Size(Size(get_Width() * Tile::Width + 2 * BORDER_SIZE, 
		get_Height() * Tile::Height + 2 * BORDER_SIZE + BORDER_SIZE + 23));
}

int MineSweeper::get_Fps() const
{
	return 50;
}

bool MineSweeper::Initialize()
{
	timer_ = new DigitBox();
	timer_->set_Location(
		Point(get_Size().Width - timer_->get_Size().Width - BORDER_SIZE, BORDER_SIZE));
	Controls.Add(*timer_);

	remains_ = new DigitBox();
	remains_->set_Location(Point(BORDER_SIZE, BORDER_SIZE));
	Controls.Add(*remains_);

	reset_.set_NormalImage(L"res/smile.png");
	reset_.set_PressedImage(L"res/smile_pressed.png");
	reset_.set_Size(Size(24, 24));
	reset_.set_Location(
		Point((get_Size().Width - reset_.get_Size().Width) / 2, BORDER_SIZE));
	reset_.Click += EventHandler<>(this, &MineSweeper::OnResetClick);
	Controls.Add(reset_);

	remains_->set_Value(get_MineNumber());
	timer_->set_Value(0);

	tile_images_[Tile::Safe]		= Image::FromFile(L"res/flat.png");
	tile_images_[Tile::Adjacent1]	= Image::FromFile(L"res/flag_1.png");
	tile_images_[Tile::Adjacent2]	= Image::FromFile(L"res/flag_2.png");
	tile_images_[Tile::Adjacent3]	= Image::FromFile(L"res/flag_3.png");
	tile_images_[Tile::Adjacent4]	= Image::FromFile(L"res/flag_4.png");
	tile_images_[Tile::Adjacent5]	= Image::FromFile(L"res/flag_5.png");
	tile_images_[Tile::Adjacent6]	= Image::FromFile(L"res/flag_6.png");
	tile_images_[Tile::Adjacent7]	= Image::FromFile(L"res/flag_7.png");
	tile_images_[Tile::Adjacent8]	= Image::FromFile(L"res/flag_8.png");
	tile_images_[Tile::Coverred]	= Image::FromFile(L"res/coverred.png");
	tile_images_[Tile::Flag]		= Image::FromFile(L"res/flag.png");
	tile_images_[Tile::Boom]		= Image::FromFile(L"res/boom.png");
	tile_images_[Tile::Mine]		= Image::FromFile(L"res/mine.png");
	tile_images_[Tile::Question]	= Image::FromFile(L"res/question.png");
	tile_images_[Tile::Wrong]		= Image::FromFile(L"res/wrong.png");

	tiles_ = new Tile[get_Width() * get_Height()];

	Paint += PaintEventHandler(this, &MineSweeper::MineBox_OnPaint);
	MouseDown += MouseEventHandler(this, &MineSweeper::Sweep_OnMouseDown);
	MouseUp += MouseEventHandler(this, &MineSweeper::Sweep_OnMouseUp);
	MouseMove += MouseEventHandler(this, &MineSweeper::OnSweepMove);

	Reset();

	return true;
}

MineSweeper::~MineSweeper()
{
	delete tiles_;
	tiles_ = NULL;
	for (size_t i = 0; i < Tile::StateMax; ++i)
	{
		delete tile_images_[i];
		tile_images_[i] = NULL;
	}
}

bool MineSweeper::LogicTick( float delta )
{
	if (started_ && !end_)
	{
		elapsed_ += delta;
		if (elapsed_ > 1)
		{
			elapsed_ -= 1;
			timer_->set_Value(timer_->get_Value() + 1);
		}
	}
	return false;
}

void MineSweeper::MineBox_OnPaint( void* sender, PaintEventArgs* e )
{
	SolidBrush normal_brush(SystemColors::Control);
	SolidBrush highlight_brush(Color::Silver);
	SolidBrush dark_brush(Color::Grey);

	Drawing::Rectangle rect = get_ClientRectangle();
	e->Graphics.FillRectangle(dark_brush, rect);

	rect.Location.X += BORDER_SIZE / 2;
	rect.Location.Y += BORDER_SIZE / 2;
	rect.Size.Width -= BORDER_SIZE;
	rect.Size.Height -= BORDER_SIZE;
	e->Graphics.FillRectangle(normal_brush, rect);

	e->Graphics.FillRectangle(dark_brush, 0, 
		timer_->get_Location().Y + timer_->get_Size().Height + BORDER_SIZE / 4,
		get_Size().Width, BORDER_SIZE / 4);

	int tiles_x = BORDER_SIZE;
	int tiles_y = BORDER_SIZE + timer_->get_Location().Y + timer_->get_Size().Height;
	for (size_t i = 0; i < get_Width(); ++i)
	{
		for (size_t j = 0; j < get_Height(); ++j)
		{
			Image* image = NULL;
			Tile& t = tiles_[i * get_Width() + j];
			if (i * get_Width() + j == pressed_tile_ && t.State == Tile::Coverred)
			{
				image = tile_images_[Tile::Safe];
			}
			else
			{
				image = tile_images_[t.State];
			}
			int x, y;
			x = i * Tile::Width + tiles_x;
			y = j * Tile::Height + tiles_y;
			e->Graphics.DrawImage(*image, Point(x, y));
		}
	}
}

void MineSweeper::Reset()
{
	size_t nMine = get_MineNumber();
	started_ = false;
	end_ = false;
	opened_ = 0;
	timer_->set_Value(0);
	remains_->set_Value(nMine);

	for (size_t i = 0; i < nMine; ++i)
	{
		tiles_[i].HasMine = true;
	}
	for (size_t i = nMine; i < get_Width() * get_Height(); ++i)
	{
		tiles_[i].HasMine = false;
	}

	Random random;
	for (size_t i = 0; i < get_Width() * get_Height(); ++i)
	{
		int j = random.Next(get_Width() * get_Height());
		bool temp = tiles_[j].HasMine;
		tiles_[j].HasMine = tiles_[i].HasMine;
		tiles_[i].HasMine = temp;
		tiles_[i].State = Tile::Coverred;
		tiles_[i].AdjacentMine = 0;
	}
	for (size_t i = 0; i < get_Width(); ++i)
	{
		for (size_t j = 0; j < get_Height(); ++j)
		{
			if (tiles_[i * get_Width() + j].HasMine)
			{
				if (i-1 >= 0 && i-1 < get_Width() && j-1 >= 0 && j-1 < get_Height())
					++ tiles_[(i-1) * get_Width() + j-1].AdjacentMine;
				if (i >= 0 && i < get_Width() && j-1 >= 0 && j-1 < get_Height())
					++ tiles_[i * get_Width() + j-1].AdjacentMine;
				if (i+1 >= 0 && i+1 < get_Width() && j-1 >= 0 && j-1 < get_Height())
					++ tiles_[(i+1) * get_Width() + j-1].AdjacentMine;

				if (i-1 >= 0 && i-1 < get_Width() && j >= 0 && j < get_Height())
					++ tiles_[(i-1) * get_Width() + j].AdjacentMine;
				if (i+1 >= 0 && i+1 < get_Width() && j >= 0 && j < get_Height())
					++ tiles_[(i+1) * get_Width() + j].AdjacentMine;

				if ((i-1) >= 0 && (i-1) < get_Width() && j+1 >= 0 && j+1 < get_Height())
					++ tiles_[(i-1) * get_Width() + j+1].AdjacentMine;
				if (i >= 0 && i < get_Width() && j+1 >= 0 && j+1 < get_Height())
					++ tiles_[i * get_Width() + j+1].AdjacentMine;
				if ((i+1) >= 0 && (i+1) < get_Width() && j+1 >= 0 && j+1 < get_Height())
					++ tiles_[(i+1) * get_Width() + j+1].AdjacentMine;
			}
		}
	}
	reset_.set_NormalImage(L"res/smile.png");				// reset this.
}

bool MineSweeper::Open( size_t x, size_t y, bool allow_boom )
{
	if (x < 0 || x >= get_Width() || y < 0 || y >= get_Height())
		return false;
	Tile* tile = &tiles_[x * get_Width() + y];
	if (tile->State != Tile::Coverred && tile->State != Tile::Question)
		return false;

	if (!allow_boom)
	{
		if (tile->HasMine)
			tile->State = Tile::Mine;
		else
			tile->State = static_cast<Tile::Tag>(tile->AdjacentMine);
	}
	else if (tile->HasMine)
	{
		tile->State = Tile::Boom;
		return true;
	}
	else
	{
		if (tile->AdjacentMine > 0)
		{
			tile->State = static_cast<Tile::Tag>(tile->AdjacentMine);
			++opened_;
		}
		else
		{
			tile->State = Tile::Safe;
			++opened_;
			Open(x - 1, y - 1, allow_boom);
			Open(x    , y - 1, allow_boom);
			Open(x + 1, y - 1, allow_boom);
			Open(x - 1, y    , allow_boom);
			Open(x + 1, y    , allow_boom);
			Open(x - 1, y + 1, allow_boom);
			Open(x    , y + 1, allow_boom);
			Open(x + 1, y + 1, allow_boom);
		}
	}
	return false;
}

void MineSweeper::OnResetClick( void * sender, EventArgs* e )
{
	Reset();
}

void MineSweeper::Sweep_OnMouseDown( void* sender, MouseEventArgs* e )
{
	if (end_)
		return;
	int tiles_x = BORDER_SIZE;
	int tiles_y = BORDER_SIZE + timer_->get_Location().Y + timer_->get_Size().Height;
	Drawing::Rectangle tile_rect(tiles_x, tiles_y, get_Width() * Tile::Width, get_Height() * Tile::Height);
	if (tile_rect.Contains(e->Location))
	{
		int i = (e->Location.X - tiles_x) / Tile::Width;
		int j = (e->Location.Y - tiles_y) / Tile::Height;

		if (e->Button == MouseButtons::Left)
		{
			pressed_tile_ = i * get_Height() + j;
			if (tiles_[pressed_tile_].State == Tile::Coverred
				|| tiles_[pressed_tile_].State == Tile::Question)
				reset_.set_NormalImage(L"res/oops.png");
		}
	}
}

void MineSweeper::Sweep_OnMouseUp( void* sender, MouseEventArgs* e )
{
	if (end_)
		return;
	pressed_tile_ = -1;
	int tiles_x = BORDER_SIZE;
	int tiles_y = BORDER_SIZE + timer_->get_Location().Y + timer_->get_Size().Height;
	Drawing::Rectangle tile_rect(tiles_x, tiles_y, get_Width() * Tile::Width, get_Height() * Tile::Height);
	if (tile_rect.Contains(e->Location))
	{
		int i = (e->Location.X - tiles_x) / Tile::Width;
		int j = (e->Location.Y - tiles_y) / Tile::Height;
		if (e->Button == MouseButtons::Left)
		{
			if (Open(i, j, true))
			{
				end_ = true;
				reset_.set_NormalImage(L"res/xxface.png");
			}
			else
			{
				reset_.set_NormalImage(L"res/smile.png");
			}
		}
		else
		{
			Flag(i, j);
		}

		if (!started_)
			started_ = true;

		if (get_Winned())
		{
			end_ = true;
			reset_.set_NormalImage(L"res/sunglass.png");
		}
	}
}

void MineSweeper::OnSweepMove( void* sender, MouseEventArgs* e )
{
	if (pressed_tile_ == -1)
		return;
	int tiles_x = BORDER_SIZE;
	int tiles_y = BORDER_SIZE + timer_->get_Location().Y + timer_->get_Size().Height;
	Drawing::Rectangle tile_rect(tiles_x, tiles_y, get_Width() * Tile::Width, get_Height() * Tile::Height);
	if (tile_rect.Contains(e->Location))
	{
		int i = (e->Location.X - tiles_x) / Tile::Width;
		int j = (e->Location.Y - tiles_y) / Tile::Height;
		pressed_tile_ = i * get_Height() + j;
	}
}

void MineSweeper::Flag( size_t x, size_t y )
{
	if (x < 0 || x >= get_Width() || y < 0 || y >= get_Height())
		return;
	Tile* tile = &tiles_[x * get_Width() + y];

	switch (tile->State)
	{
	case Tile::Coverred:
		tile->State = Tile::Flag;
		remains_->set_Value(remains_->get_Value() - 1);
		break;

	case Tile::Flag:
		tile->State = Tile::Question;
		remains_->set_Value(remains_->get_Value() + 1);
		break;

	case Tile::Question:
		tile->State = Tile::Coverred;
		break;
	}
}

size_t MineSweeper::get_MineNumber() const
{
	switch (level_)
	{
	case Easy:
		return 10;

	case Intermediate:
		return 40;

	default:
		return 10;
	}	
}

size_t MineSweeper::get_Width() const
{
	switch (level_)
	{
	case Easy:
		return 9;

	case Intermediate:
		return 16;

	default:
		return 32;
	}	
}

size_t MineSweeper::get_Height() const
{
	switch (level_)
	{
	case Easy:
		return 9;

	case Intermediate:
		return 16;

	default:
		return 32;
	}	
}

bool MineSweeper::get_Winned()
{
	return opened_ == get_Width() * get_Height() - get_MineNumber();
}
