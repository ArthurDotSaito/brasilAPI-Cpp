#ifndef BRASIL_API_EXCEPTION_H
#define BRASIL_API_EXCEPTION_H

#include "BrasilAPIHandlerBase.h"
#include "Utils/BrasilAPIException.h"

void BrasilAPIHandlerBase::ensureSuccess(const drogon::HttpResponsePtr& response, const std::string& path) {
    if (response->getStatusCode() >= 400) {
        std::string url = baseUrl + path;
        std::string contentString = std::string(response->getBody());
        Json::Reader reader;
        Json::Value jsonResponse;
        std::string message = "Error while trying to acess the BrasilAPI";

       if (reader.parse(contentString, jsonResponse)) {
            if (jsonResponse.isObject() && jsonResponse.isMember("message")) {
                message = jsonResponse["message"].asString();
            } 
            else {
                message += " - Response: " + contentString;
            }
        }

        throw BrasilAPIException(message, response->getStatusCode(), path);

    }
}

#endif // BRASIL_API_EXCEPTION_H
