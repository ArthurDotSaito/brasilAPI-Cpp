#ifndef FERIADOS_RESPONSE_H
#define FERIADOS_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>
#include <vector>

class Feriados : public BaseResponse {
  public:
  std::string date;
  std::string name;
  std::string type;

  Json::Value toJson() const {
    Json::Value jsonFeriado;
    jsonFeriado["date"] = date;
    jsonFeriado["name"] = name;
    jsonFeriado["type"] = type;
    return jsonFeriado;
  }
};

class FeriadosResponse : public BaseResponse {
  public:
  std::vector<Feriados> feriados;

  std::string serialize() const {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &feriado : feriados) {
      jsonRoot.append(feriado.toJson());
    }

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonRoot);
  }
};

#endif // FERIADOS_RESPONSE_H
