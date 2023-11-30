#include "BrasilAPIFacadeBase.h"

void BrasilAPIFacadeBase::ensureSuccess(const drogon::HttpResponsePtr& response, const std::string& url) {
    if (response->getStatusCode() > 400) {
        std::string contentString = std::string(response->getBody());
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string message = "Error while trying to acess the BrasilAPI";

       if (reader.parse(contentString, jsonResponse)) {
            if (jsonResponse.isObject() && jsonResponse.isMember("message")) {
                message = jsonResponse["message"].asString();
            } else {
                message += " - Response: " + contentString;
            }
        }


    }
}