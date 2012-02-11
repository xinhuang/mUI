#include <Presenter/PieceGroup.h>

#include <gtest/gtest.h>

class PieceGroupTest : public ::testing::Test
{
public:
};

TEST_F(PieceGroupTest, Constructor_Typical)
{
	int groupId = 4;

	auto sut = new PieceGroup(groupId);

	ASSERT_NE(nullptr, sut);
	ASSERT_EQ(groupId, sut->get_Id());
	auto pieces = sut->get_Pieces();
	ASSERT_EQ(PieceGroup::PieceMax, pieces.size());
	for (auto iter = pieces.begin(); iter != pieces.end(); ++iter)
	{
		ASSERT_NE(nullptr, *iter);
	}

	delete sut;
}
