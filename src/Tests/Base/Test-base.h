#ifndef TESTBASE_H
#define TESTBASE_H

#include "../../Client/BrasilAPIClient.h"
#include <chrono>
#include <future>
#include <gtest/gtest.h>

class TestBase : public ::testing::Test {
  protected:
  BrasilAPIClient brasilAPI;

  void SetUp() override {
    brasilAPI.setUserAgent("MeuApp/1.0");
  }

  void TearDown() override {
  }

  template <typename T>
  T waitForResult(std::future<T> &future) {
    std::future_status status = future.wait_for(std::chrono::seconds(10));
    EXPECT_EQ(status, std::future_status::ready);
    return future.get();
  }
};
#endif // TESTBASE_H
