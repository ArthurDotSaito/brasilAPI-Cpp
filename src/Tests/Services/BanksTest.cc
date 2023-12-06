#include <gtest/gtest.h>
#include "../../Client/BrasilAPIClient.h"

class BrasilAPIClientTests : public ::testing::Test {
protected:
    BrasilAPIClient brasilAPI;

    BrasilAPIClientTests() {
        brasilAPI.setUserAgent("MeuApp/1.0");
    }
};

TEST_F(BrasilAPIClientTests, TestGetAllBanks) {
    std::promise<BankResponse> promise;
    auto future = promise.get_future();    

    brasilAPI.getAllBanks([&promise](const BankResponse& response) {
        promise.set_value(response);
    });

    future.wait();
    auto response = future.get();

    EXPECT_FALSE(response.banks.empty());
}

TEST_F(BrasilAPIClientTests, TestGetBankByCode) {
    //Arrange
    std::promise<Bank> promise;
    auto future = promise.get_future();

    //Act
    brasilAPI.getBanksByCode(1, [&promise](const Bank& response) {
        promise.set_value(response);
    });

    future.wait();
    auto response = future.get();
    //Assert

    EXPECT_FALSE(response.name.empty());
    EXPECT_FALSE(response.fullName.empty());
    EXPECT_FALSE(response.ispb.empty());
    EXPECT_TRUE(response.code.has_value());
    EXPECT_EQ(response.code.value(), 1);
}