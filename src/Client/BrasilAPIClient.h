#include "Services/BanksFacade.h"
#include "Response/BankResponse.h"

class BrasilAPIClient {
public:
    BrasilAPIClient();

    void setUserAgent(const std::string& userAgent);

    void getAllBanks(std::function<void(const BankResponse&)> callback);
    void getBanksByCode(int code, std::function<void(const Json::Value&)> callback);

private:
    BanksFacade banksFacade;
    std::string userAgent;
};
