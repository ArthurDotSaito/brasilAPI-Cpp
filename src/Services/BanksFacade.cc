#include "BanksFacade.h"
#include "BankResponse.h"

void BanksFacade::getAllBanks(std::function<void(const BankResponse&)> callback) {
   auto req = drogon::HttpRequest::newHttpRequest();
   req->setMethod(drogon::HttpMethod::Get);
   req->setPath("/banks/v1");

   httpClient->sendRequest(req, [this, callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response) {
        if (result == drogon::ReqResult::Ok && response->getStatusCode() == drogon::HttpStatusCode::k200OK) {
            Json::Reader reader;
            Json::Value jsonResponse;
            std::string responseBody = std::string(response->getBody());
            reader.parse(responseBody, jsonResponse);

            BankResponse bankResponse;
            for (const auto& jsonBank : jsonResponse) {
                Bank bank;
                bank.ispb = jsonBank["ispb"].asString();
                bank.name = jsonBank["name"].asString();
                if (!jsonBank["code"].isNull()) {
                    bank.code = jsonBank["code"].asInt();
                }
                bank.fullname = jsonBank["fullName"].asString();
                bankResponse.banks.push_back(bank);
            }

            callback(bankResponse);
        } 
    });

};

void BanksFacade::getBanksByCode(int code, std::function<void(const Json::Value&)> callback) {
    // TODO
};