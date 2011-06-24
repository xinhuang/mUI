#include "QuickSortForm.h"

#include <mUI.h>
using namespace mUI::System;

#include <algorithm>
using namespace std;

QuickSortForm::QuickSortForm(void)
{
}

QuickSortForm::~QuickSortForm(void)
{
    Dispose();
}

void QuickSortForm::Swap(vector<int>& array, size_t a, size_t b )
{
	if (a == b)
		return;

	swap(array[a], array[b]);

	Invoke(Delegate<void>(*this, &VisualSortForm::Swap, a, b));
	Thread::Sleep(300);
}

void QuickSortForm::Sort( vector<int> array )
{
	Sort(array, 0, array.size());
}

void QuickSortForm::Sort( vector<int>& array, size_t a, size_t b )
{
	if (a + 1 < b)
	{
		size_t p = Partition(array, a, b);
		Sort(array, a, p);
		Sort(array, p + 1, b);
	}
}

size_t QuickSortForm::Partition( vector<int>& array, size_t a, size_t b )
{
	if (a + 1 < b)
	{
		size_t p = random_.Next(a, b);
		swap(array[p], array[b - 1]);
		VisualSortForm::Swap(p, b - 1);

		size_t i = a;
		for (size_t j = a; j < b - 1; ++j)
		{
			if (array[j] < array[b - 1])
			{
				Swap(array, j, i);
				++i;
			}
		}
		Swap(array, i, b - 1);

		if (get_InvokeRequired())
			Invoke(Delegate<void>(this, &QuickSortForm::set_Fixed, i));

		return i;
	}
	else
	{
		assert(false);
		return -1;
	}
}
