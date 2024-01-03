#ifndef FIPE_RESPONSE_H
#define FIPE_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>

class Fipe : public BaseResponse {
  public:
  std::string nome;
  std::string valor;

  Json::Value toJson() const {
    Json::Value jsonValue;
    jsonValue["nome"] = nome;
    jsonValue["valor"] = valor;
    return jsonValue;
  }
};

class FipeResponse : public BaseResponse {
  public:
  std::vector<Fipe> fipe;

  Json::Value toJson() const {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : fipe) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }

  std::string serialize() const {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, this->toJson());
  }
};

#endif // FIPE_RESPONSE_H