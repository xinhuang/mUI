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

#include "VisualSortForm.h"

class QuickSortForm :
	public VisualSortForm
{
public:
	QuickSortForm(void);
	virtual ~QuickSortForm(void);

	virtual void Sort(vector<int> array);

protected:
	void Swap(vector<int>& array, size_t a, size_t b);
	size_t Partition(vector<int>& array, size_t a, size_t b);
	void Sort(vector<int>& array, size_t a, size_t b);

private:
	Random random_;
};
