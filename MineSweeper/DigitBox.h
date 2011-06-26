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

class DigitBox :
	public Control
{
public:
	DigitBox(void);
	virtual ~DigitBox(void);

	void set_Value(int value);
	int get_Value() const;

private:
	void InitializeComponent();

private:
	static const int MAX_DIGITS = 3;
	int value_;
	PictureBox digits[MAX_DIGITS];
};
