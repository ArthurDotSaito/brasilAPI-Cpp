#include "CepResponse.h"
#include <json/json.h>

Json::Value CepResponse::toJsonValue() const {
    Json::Value jsonValue;
    jsonValue["cep"] = cep;
    jsonValue["state"] = state;
    jsonValue["city"] = city;
    jsonValue["neighborhood"] = neighborhood;
    jsonValue["street"] = street;
    jsonValue["service"] = service;
    jsonValue["CalledURL"] = calledURL;
    jsonValue["JsonResponse"] = jsonResponse;

    return jsonValue;
}

CepResponse CepResponse::fromJsonValue(const Json::Value& jsonValue) {
    CepResponse response;

    response.cep = jsonValue["cep"].asString();
    response.state = jsonValue["state"].asString();
    response.city = jsonValue["city"].asString();
    response.neighborhood = jsonValue["neighborhood"].asString();
    response.street = jsonValue["street"].asString();
    response.service = jsonValue["service"].asString();

    response.calledURL = jsonValue["CalledURL"].asString();
    response.jsonResponse = jsonValue["JsonResponse"].asString();

    return response;
}