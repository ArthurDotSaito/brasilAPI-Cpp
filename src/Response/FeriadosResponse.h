#ifndef FERIADOS_RESPONSE_H
#define FERIADOS_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>
#include <vector>

class Feriados : public BaseResponse, public JsonSerialize {
  private:
  std::string date;
  std::string name;
  std::string type;

  public:
  const std::string &getDate() const {
    return date;
  }

  const std::string &getName() const {
    return name;
  }

  const std::string &getType() const {
    return type;
  }

  void setDate(const std::string &d) {
    date = d;
  }

  void setName(const std::string &n) {
    name = n;
  }

  void setType(const std::string &t) {
    type = t;
  }

  Json::Value toJson() const override {
    Json::Value jsonFeriado;
    jsonFeriado["date"] = date;
    jsonFeriado["name"] = name;
    jsonFeriado["type"] = type;
    return jsonFeriado;
  }
};

class FeriadosResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<Feriados> feriados;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : feriados) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // FERIADOS_RESPONSE_H
