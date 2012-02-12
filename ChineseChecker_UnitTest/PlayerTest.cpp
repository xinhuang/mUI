#include <Presenter/Player.h>

#include <gtest/gtest.h>

class PlayerTest : public ::testing::Test
{
public:
    virtual void SetUp()
    {
        _sut = new Player(vector<int>());
    }
    virtual void TearDown()
    {
        delete _sut; _sut = nullptr;
    }

protected:
    Player* _sut;
};

TEST_F(PlayerTest, Owns_WhenColorListIsEmpty)
{
    ASSERT_FALSE(_sut->Owns(2));
}
