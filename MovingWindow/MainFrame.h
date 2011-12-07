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

#include <vector>
using namespace std;

class MovingForm;
class InfoForm;

class MainFrame : public Frame
{
public:
	MainFrame();

	virtual int get_Fps() const;
	virtual bool Initialize();
	virtual bool LogicTick(float delta);

private:
	void MainFrame_OnKeyPress( void* sender, KeyPressEventArgs* e );

	void AddForm();
	void RemoveForm();

private:
	vector<MovingForm*> forms_;
	InfoForm* infoform_;
};
