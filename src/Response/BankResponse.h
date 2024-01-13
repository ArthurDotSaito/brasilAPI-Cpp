#ifndef BANK_RESPONSE_H
#define BANK_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>
#include <vector>

class Bank : public BaseResponse, public JsonSerialize {
  private:
  std::string ispb;
  std::string name;
  std::optional<int> code;
  std::string fullName;

  public:
  const std::string &getIspb() const {
    return ispb;
  }

  const std::string &getName() const {
    return name;
  }

  std::string getCode() const {
    return code.has_value() ? std::to_string(code.value()) : "";
  }

  const std::string &getFullName() const {
    return fullName;
  }

  void setIspb(const std::string &i) {
    ispb = i;
  }

  void setName(const std::string &n) {
    name = n;
  }

  void setCode(const std::string &c) {
    code = c.empty() ? std::nullopt : std::optional<int>(std::stoi(c));
  }

  void setFullName(const std::string &fn) {
    fullName = fn;
  }

  Json::Value toJson() const override {
    Json::Value jsonBank;
    jsonBank["ispb"] = ispb;
    jsonBank["name"] = name;
    jsonBank["code"] = code.has_value() ? code.value() : Json::Value(Json::nullValue);
    jsonBank["fullName"] = fullName;
    return jsonBank;
  }
};

class BankResponse : public BaseResponse, public JsonSerialize {
  public:
  std::vector<Bank> banks;

  Json::Value toJson() const override {
    Json::Value jsonRoot(Json::arrayValue);
    for (const auto &item : banks) {
      jsonRoot.append(item.toJson());
    }
    return jsonRoot;
  }
};

#endif // BANK_RESPONSE_H
