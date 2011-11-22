#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <SquareFactory.h>
#include <ISquare.h>

#include "mocks/MineFieldMock.h"

class SquareFactoryTest : public testing::Test
{
public:
};

TEST_F(SquareFactoryTest, Constructor_Typical)
{
	SquareFactory factory;
}
