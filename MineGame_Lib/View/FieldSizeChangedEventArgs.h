#ifndef __FIELDSIZECHANGEDEVENTARGS_H__
#define __FIELDSIZECHANGEDEVENTARGS_H__

#include <mUI.h>
using mUI::System::EventArgs;

class FieldSizeChangedEventArgs : public EventArgs
{
public:
	FieldSizeChangedEventArgs(const Size& size)
		: _size(size)
	{}

	const Size& get_Size() const { return _size; }

private:
	const Size _size;
};

#endif // __FIELDSIZECHANGEDEVENTARGS_H__
