#include <drogon/HttpController.h>
#include "Services/BanksFacade.h"
#include "Response/BankResponse.h"

class BanksController: public drogon::HttpController<BanksController>{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(BanksController::getAllBanks, "/banks", drogon::Get);
        METHOD_ADD(BanksController::getBankByCode, "/banks/{code}", drogon::Get);
    METHOD_LIST_END

private:
    BanksFacade banksFacade;

    void getAllBanks(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)> callback);
    void getBankByCode(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)> callback, int code);
};