#ifndef CEP_RESPONSE_H
#define CEP_RESPONSE_H

#include<string>
#include<optional> 
#include<vector>
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

    Json::Value toJsonValue() const;
    static CepResponse fromJsonValue(const Json::Value& jsonValue);
};

#endif // CEP_RESPONSE_H