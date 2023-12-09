#ifndef CEP_RESPONSE_H
#define CEP_RESPONSE_H

#include<string>
#include <json/json.h>
#include "BaseResponse.h"

class CepResponse:public BaseResponse {
public:
    std::string cep;
    std::string state;
    std::string city;
    std::string neighborhood;
    std::string street;
    std::string service;

    std::string serialize() const {
        Json::Value jsonCep;
        jsonCep["cep"] = cep;
        jsonCep["state"] = state;
        jsonCep["city"] = city;
        jsonCep["neighborhood"] = neighborhood;
        jsonCep["street"] = street;
        jsonCep["service"] = service;

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";  
        return Json::writeString(builder, jsonCep);
    }
};

#endif // CEP_RESPONSE_H