#include "MineFieldMock.h"

#include "SquareFactoryFake.h"

MineFieldMock::MineFieldMock()
	: base(NULL)
{
	SquareFactory* oldFactory = get_SquareFactory();
	delete oldFactory;
	set_SquareFactory(new SquareFactoryFake());
}