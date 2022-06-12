#include "gtest/gtest.h"
#include <canvas.h>

class CanvasBasics : public ::testing::Test
{
  protected:
    Canvas c = Canvas{ 10, 20 };
};

TEST_F(CanvasBasics, CreateCanvas)
{
    EXPECT_EQ(c.getWidth(), 10);
    EXPECT_EQ(c.getHeight(), 20);
}
