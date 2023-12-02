#include "Client/BrasilAPIClient.h"
#include <gtest/gtest.h>

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