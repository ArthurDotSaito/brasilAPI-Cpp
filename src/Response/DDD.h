#ifndef DDD_RESPONSE_H
#define DDD_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
#include <json/json.h>
#include <string>

class DDDResponse : public BaseResponse, JsonSerialize {
  private:
  std::string state;
  std::vector<std::string> cities;

  public:
  const std::string &getState() const {
    return state;
  }

  const std::vector<std::string> &getCities() const {
    return cities;
  }

  void setState(const std::string &s) {
    state = s;
  }
  void addCities(const std::string &c) {
    cities.push_back(c);
  }

  Json::Value toJson() const override {
    Json::Value jsonRoot;
    Json::Value jsonCities(Json::arrayValue);

    jsonRoot["state"] = state;

    for (const auto &city : cities) {
      jsonCities.append(city);
    }

    jsonRoot["cities"] = jsonCities;
    return jsonRoot;
  }

  std::string serialize() const override {
    return JsonSerialize::serialize();
  }
};

#endif // DDD_RESPONSE_H