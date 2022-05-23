#include "failures.h"

#include <iostream>
#include <memory>

#include "gtest/gtest.h"

namespace jbox {
namespace failures {
namespace tests {

class FailuresEncodingTest : public ::testing::Test {
 protected:
  // clang-format off
  const Failure failure =
    Failure('a', OTHER, "NAME", {
      FailureParam(INT, "int"), 
      FailureParam(FLOAT, "float")
    });
  // clang-format on
};

TEST_F(FailuresEncodingTest, StartMessage) {
  Failure f = failure.create_instance({ParamData(5), ParamData(5.5f)});
  ASSERT_EQ(f.toStartMessage(), "!a/B/5/5.5%");
}

TEST_F(FailuresEncodingTest, StopMessage) {
  Failure f = failure.create_instance({ParamData(5), ParamData(5.5f)});
  ASSERT_EQ(f.toStopMessage(), "!a/S%");
}

TEST_F(FailuresEncodingTest, TypeRuntimeError) {
  int didCatch = 0;
  try {
    Failure f = failure.create_instance({ParamData(5), ParamData(5)});
  } catch (const std::runtime_error& e) {
    didCatch = 1;
  }
  ASSERT_EQ(didCatch, 1);
}

TEST_F(FailuresEncodingTest, SizeRuntimeError) {
  int didCatch = 0;
  try {
    Failure f = failure.create_instance({ParamData(5)});
  } catch (const std::runtime_error& e) {
    didCatch = 1;
  }
  ASSERT_EQ(didCatch, 1);
}

}  // namespace tests
}  // namespace failures
}  // namespace jbox
