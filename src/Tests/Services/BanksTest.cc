#include "../../Client/BrasilAPIClient.h"
#include <chrono>
#include <drogon/drogon.h>
#include <gtest/gtest.h>

void runTestGetAllBanks() {
  std::cout << "Starting runTestGetAllBanks" << std::endl;
  BrasilAPIClient brasilAPI;
  brasilAPI.setUserAgent("MeuApp/1.0");

  // Start Drogon event loop
  drogon::app().run();

  BankResponse response;
  std::promise<void> promise;

  brasilAPI.getAllBanks([&response, &promise](const BankResponse &bankResponse) {
    response = bankResponse;
    promise.set_value();
  });

  std::future<void> future = promise.get_future();
  std::future_status status = future.wait_for(std::chrono::seconds(10));

  // Stop Drogon event loop
  drogon::app().quit();

  EXPECT_EQ(status, std::future_status::ready);
  EXPECT_FALSE(response.banks.empty());
  std::cout << "Finishing runTestGetAllBanks" << std::endl;
}

void runTestGetBankByCode() {
  std::cout << "Starting runTestGetBankByCode" << std::endl;
  BrasilAPIClient brasilAPI;
  brasilAPI.setUserAgent("MeuApp/1.0");

  // Start Drogon event loop
  drogon::app().run();

  Bank response;
  std::promise<void> promise;

  brasilAPI.getBanksByCode(1, [&response, &promise](const Bank &bank) {
    response = bank;
    promise.set_value();
  });

  std::future<void> future = promise.get_future();
  std::future_status status = future.wait_for(std::chrono::seconds(10));

  // Stop Drogon event loop
  drogon::app().quit();

  EXPECT_EQ(status, std::future_status::ready);
  EXPECT_FALSE(response.getName().empty());
  EXPECT_FALSE(response.getFullName().empty());
  EXPECT_FALSE(response.getIspb().empty());
  EXPECT_FALSE(response.getCode().empty());
  std::cout << "Finishing runTestGetBankByCode" << std::endl;
}

TEST(RunTestGetAllBanks, BrasilAPIClientTests) {
  runTestGetAllBanks();
}

TEST(RunTestGetBankByCode, BrasilAPIClientTests) {
  runTestGetBankByCode();
}
