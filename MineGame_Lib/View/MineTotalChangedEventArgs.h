#ifndef __MINETOTALCHANGEDEVENTARGS_H__
#define __MINETOTALCHANGEDEVENTARGS_H__

#include <mUI.h>
using mUI::System::EventArgs;

class MineTotalChangedEventArgs : public EventArgs
{
public:
	MineTotalChangedEventArgs(int mineTotal)
		: _mineTotal(mineTotal)
	{}

	int get_MineTotal() const { return _mineTotal; }

private:
	const int _mineTotal;
};

#endif // __MINETOTALCHANGEDEVENTARGS_H__
