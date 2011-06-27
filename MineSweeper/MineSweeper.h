/*
	Copyright 2011 hello.patz@gmail.com

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#pragma once

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

class DigitBox;

class MineSweeper : public Frame
{
public:
	MineSweeper();
	virtual ~MineSweeper();

	virtual int get_Fps() const;
	virtual bool Initialize();
	virtual bool LogicTick(float delta);

private:
	void MineBox_OnPaint( void* sender, PaintEventArgs* e);
	void OnResetClick(void * sender, EventArgs* e);
	void Sweep_OnMouseDown(void* sender, MouseEventArgs* e);
	void Sweep_OnMouseUp(void* sender, MouseEventArgs* e);
	void OnSweepMove(void* sender, MouseEventArgs* e);

	struct Tile
	{
		Tile() : State(Coverred), HasMine(false) {}
		enum Tag
		{
			Safe,
			Adjacent1,
			Adjacent2,
			Adjacent3,
			Adjacent4,
			Adjacent5,
			Adjacent6,
			Adjacent7,
			Adjacent8,
			Coverred,
			Flag,
			Boom,
			Mine,
			Question,
			Wrong,
			StateMax
		};
		Tag		State;
		bool	HasMine;
		int		AdjacentMine;

		static const int Width = 16;
		static const int Height = 16;
	};
	void Reset();		

	size_t get_MineNumber() const;
	size_t get_Width() const;
	size_t get_Height() const;
	bool Open(size_t x, size_t y, bool allow_boom);		// return true of BOOM!

	bool get_Winned();
	void Flag(size_t x, size_t y);

private:
	DigitBox*	timer_;
	DigitBox*	remains_;
	Button		reset_;

	Tile* tiles_;
	size_t pressed_tile_;
	Image* tile_images_[Tile::StateMax];

	enum Level
	{
		Easy, Intermediate, Hard, UserConf
	};
	Level	level_;
	bool	started_;
	bool	end_;
	float	elapsed_;
	size_t	opened_;

	static const int BORDER_SIZE = 16;
};
