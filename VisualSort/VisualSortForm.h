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

#ifndef __QUICKSORTFORM_H__
#define __QUICKSORTFORM_H__

#include <mUI.h>

using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;
using namespace mUI::System::Threading;

class TitleBar;

class VisualSortForm : public Form
{
public:
	VisualSortForm();
	virtual ~VisualSortForm();
	virtual void Dispose();

	void BeginSort(vector<int>& array);
	void set_Fixed(size_t i);
	void Swap(size_t a, size_t b);

	virtual void Sort(vector<int> array) = 0;

protected:
	virtual void OnPaint(void* sender, PaintEventArgs* e);

private:
	TitleBar* titlebar_;
	Thread* worker_;
	vector<int> array_;
	vector<Color> color_;
};

#endif 
