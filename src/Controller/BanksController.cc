#include "BanksController.h"
#include <drogon/HttpResponse.h>
#include <json/json.h>

void BanksController::getAllBanks(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)> callback){
    try{
        banksFacade.getAllBanks([callback](const BankResponse& bankResponse) {
        Json::Value jsonResponse;

        for(const auto& bank : bankResponse.banks){
            Json::Value jsonBank;
            jsonBank["ispb"] = bank.ispb;
            jsonBank["name"] = bank.name;
            jsonBank["code"] = bank.code.value_or(Json::Value());
            jsonBank["fullName"] = bank.fullname;
             jsonResponse.append(jsonBank);
        }
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k200OK);
        response->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        response->setBody(jsonResponse.toStyledString());
        callback(response);
    });
    }catch(const std::exception& e){
        auto errorResponse = drogon::HttpResponse::newHttpResponse();
        errorResponse->setStatusCode(drogon::HttpStatusCode::k500InternalServerError);
        errorResponse->setContentTypeCode(drogon::CT_APPLICATION_JSON);
        errorResponse->setBody("{\"error\":\"" + std::string(e.what()) + "\"}");
        callback(errorResponse);

    }
};