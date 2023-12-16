#ifndef CIDADE_CLIMA_RESPONSE_H
#define CIDADE_CLIMA_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>

class ClimaDiario {
  public:
  std::string data;
  std::string condicao;
  int min;
  int max;
  int indice_uv;
  std::string condicao_desc;

  Json::Value toJson() const {
    Json::Value jsonClima;
    jsonClima["data"] = data;
    jsonClima["condicao"] = condicao;
    jsonClima["min"] = min;
    jsonClima["max"] = max;
    jsonClima["indice_uv"] = indice_uv;
    jsonClima["condicao_desc"] = condicao_desc;
    return jsonClima;
  }
};

class CidadeClimaResponse : public BaseResponse {
  public:
  std::string cidade;
  std::string estado;
  std::string atualizado_em;
  std::vector<ClimaDiario> clima;

  std::string serialize() const {
    Json::Value jsonRoot;
    jsonRoot["cidade"] = cidade;
    jsonRoot["estado"] = estado;
    jsonRoot["atualizado_em"] = atualizado_em;
    Json::Value jsonClimaArray(Json::arrayValue);
    for (const auto &climaDiario : clima) {
      jsonClimaArray.append(climaDiario.toJson());
    }
    jsonRoot["clima"] = jsonClimaArray;

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonRoot);
  }
};

#endif // CIDADE_CLIMA_RESPONSE_H
