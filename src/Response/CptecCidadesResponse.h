#ifndef CPTECCIDADES_RESPONSE_H
#define CPTECCIDADES_RESPONSE_H

#include<string>
#include <json/json.h>
#include "BaseResponse.h"

class CptecCidades:public BaseResponse {
public:
    std::string nome;
    std::string estado;
    int id;

    std::string serialize() const {
        Json::Value jsonCptecCidades;
        jsonCptecCidades["nome"] = nome;
        jsonCptecCidades["estado"] = estado;
        jsonCptecCidades["id"] = id;

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";  
        return Json::writeString(builder, jsonCptecCidades);
    }
};

class CptecCidadesResponse : public BaseResponse {
public:
    std::vector<CptecCidades> cptecCidades;

    std::string serialize() const {
        Json::Value jsonRoot;
        for (const auto& cptecCidade : cptecCidades) {
            Json::Value jsonCptecCidades;
            jsonCptecCidades["nome"] = cptecCidade.nome;
            jsonCptecCidades["estado"] = cptecCidade.estado;
            jsonCptecCidades["id"] = cptecCidade.id;

            jsonRoot.append(jsonCptecCidades);
        }

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = ""; 
        return Json::writeString(builder, jsonRoot);
    }
};


#endif // CPTECCIDADES_RESPONSE_H