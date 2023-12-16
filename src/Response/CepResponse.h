#ifndef CEP_RESPONSE_H
#define CEP_RESPONSE_H

#include "BaseResponse.h"
#include <json/json.h>
#include <string>

struct Coordinates {
  std::string longitude;
  std::string latitude;
};

struct Location {
  std::string type;
  Coordinates coordinates;
};

class CepResponse : public BaseResponse {
  public:
  std::string cep;
  std::string state;
  std::string city;
  std::string neighborhood;
  std::string street;
  std::string service;
  Location location;

  std::string serialize() const {
    Json::Value jsonCep;
    jsonCep["cep"] = cep;
    jsonCep["state"] = state;
    jsonCep["city"] = city;
    jsonCep["neighborhood"] = neighborhood;
    jsonCep["street"] = street;
    jsonCep["service"] = service;

    if (!location.coordinates.longitude.empty() && !location.coordinates.latitude.empty()) {
      Json::Value jsonLocation;
      jsonLocation["type"] = location.type;
      jsonLocation["coordinates"]["longitude"] = location.coordinates.longitude;
      jsonLocation["coordinates"]["latitude"] = location.coordinates.latitude;
      jsonCep["location"] = jsonLocation;
    }

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, jsonCep);
  }
};

#endif // CEP_RESPONSE_H