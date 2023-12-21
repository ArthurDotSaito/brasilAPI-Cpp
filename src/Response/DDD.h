#ifndef DDD_RESPONSE_H
#define DDD_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>

class DDDResponse : public BaseResponse {
  public:
  std::string state;
  std::vector<std::string> cities;

  Json::Value toJson() const {
    Json::Value jsonRoot;
    jsonRoot["state"] = state;
    Json::Value jsonCitiesArray(Json::arrayValue);
    for (const auto &city : cities) {
      jsonCitiesArray.append(city);
    }
    jsonRoot["cities"] = jsonCitiesArray;
    return jsonRoot;
  }

  std::string serialize() const {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, this->toJson());
  }
};

#endif // DDD_RESPONSE_H