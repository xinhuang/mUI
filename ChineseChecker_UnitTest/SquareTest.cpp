#include <gtest/gtest.h>

#include <Presenter/Square.h>

class SquareTest : public ::testing::Test
{
public:

};

TEST_F(SquareTest, Constructor_Typical)
{
	Square* square = new Square();
	delete square;
}
