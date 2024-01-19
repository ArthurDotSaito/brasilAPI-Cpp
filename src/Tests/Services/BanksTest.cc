#include "../Base/Test-base.h"
#include <nlohmann/json.hpp>

class BanksTest : public TestBase {};

TEST_F(BanksTest, GetAllBanks) {
  auto futureBank = brasilAPI.getAllBanksAsync();
  auto bankDataString = waitForResult(futureBank);

  EXPECT_FALSE(bankDataString.empty());
  auto bankData = nlohmann::json::parse(bankDataString);

  EXPECT_TRUE(bankData.is_array());
  EXPECT_FALSE(bankData.empty());

  auto firstBank = bankData.at(0);
  EXPECT_FALSE(firstBank["name"].empty());
  EXPECT_FALSE(firstBank["ispb"].empty());
  EXPECT_TRUE(firstBank["code"].is_number());
  EXPECT_FALSE(firstBank["fullName"].empty());
}

TEST_F(BanksTest, GetBankByCode) {
  auto future = brasilAPI.getBanksByCodeAsync(1);
  auto responseString = waitForResult(future);
  EXPECT_FALSE(responseString.empty());
}