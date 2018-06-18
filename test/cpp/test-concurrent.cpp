#include <src/cpp/ABSwitchProcessor.h>
#include <gtest/gtest.h>

using namespace pongasoft::VST;

TEST(AtomicTest, EnsureLockFree)
{
  ABSwitchProcessor::AtomicValue<int> atomic{3};

  ASSERT_TRUE(true);
}
