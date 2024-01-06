#include "BanksHandler.h"
#include <Utils/BrasilAPIException.h>

void BanksHandler::getAllBanks(std::function<void(const BankResponse &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/banks/v1");
  std::string fullUrl = baseUrl + req->getPath();
  std::cout << "Iniciando a solicitação para: " << fullUrl << std::endl;

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    ensureSuccess(response, "api/banks/v1");
    std::string responseBody = std::string(response->getBody());

    BankResponse bankResponse;
    bankResponse.calledURL = fullUrl;
    bankResponse.jsonResponse = responseBody;

    Json::Value jsonResponse;
    Json::Reader reader;
    if (reader.parse(responseBody, jsonResponse) && jsonResponse.isArray()) {
      for (const auto &jsonBank : jsonResponse) {
        Bank bank;
        bank.setIspb(jsonBank["ispb"].asString());
        bank.setName(jsonBank["name"].asString());
        if (!jsonBank["code"].isNull()) {
          bank.setCode(std::to_string(jsonBank["code"].asInt()));
        }
        bank.setFullName(jsonBank["fullName"].asString());
        bankResponse.banks.push_back(bank);
      }
    }

    callback(bankResponse);
  });
}

void BanksHandler::getBanksByCode(int code, std::function<void(const Bank &)> callback) {
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::HttpMethod::Get);
  req->setPath("/api/banks/v1/" + std::to_string(code));
  std::string fullUrl = baseUrl + req->getPath();

  httpClient->sendRequest(req, [this, callback, fullUrl](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {
    ensureSuccess(response, "api/banks/v1/{code}");
    std::string responseBody = std::string(response->getBody());

    Json::Value jsonResponse;
    Json::Reader reader;
    Bank bank;
    if (reader.parse(responseBody, jsonResponse)) {
      bank.setIspb(jsonResponse["ispb"].asString());
      bank.setName(jsonResponse["name"].asString());
      if (!jsonResponse["code"].isNull()) {
        bank.setCode(std::to_string(jsonResponse["code"].asInt()));
      }
      bank.setFullName(jsonResponse["fullName"].asString());
      bank.calledURL = fullUrl;
      bank.jsonResponse = responseBody;
    } else {
      std::cerr << "Error during JSON parsing: " << responseBody << std::endl;
      return;
    }

    callback(bank);
  });
}
