#include "Services/BanksFacade.h"
#include "Response/BankResponse.h"

class BrasilAPIClient {
private:

    BanksFacade banksFacade;
    std::string userAgent;


public:
    BrasilAPIClient();

    void setUserAgent(const std::string& userAgent);

    void getAllBanks(std::function<void(const BankResponse&)> callback);
    std::string getAllBanks();
    void getBanksByCode(int code, std::function<void(const Bank&)> callback);
    std::string getBanksByCode(int code);
};