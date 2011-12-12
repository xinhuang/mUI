#include "MineFieldMock.h"

#include "SquareFactoryMock.h"

MineFieldMock::MineFieldMock()
	: base(NULL)
{
	SquareFactory* oldFactory = get_SquareFactory();
	delete oldFactory;
	set_SquareFactory(new SquareFactoryFake());
}
