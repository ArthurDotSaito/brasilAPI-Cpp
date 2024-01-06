#ifndef CEP_RESPONSE_H
#define CEP_RESPONSE_H

#include "BaseResponse.h"
#include "Utils/JsonSerialize.h"
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

class CepResponse : public BaseResponse, public JsonSerialize {
  private:
  std::string cep;
  std::string state;
  std::string city;
  std::string neighborhood;
  std::string street;
  std::string service;
  Location location;

  public:
  std::string getCep() const {
    return cep;
  }
  std::string getState() const {
    return state;
  }
  std::string getCity() const {
    return city;
  }
  std::string getNeighborhood() const {
    return neighborhood;
  }
  std::string getStreet() const {
    return street;
  }
  std::string getService() const {
    return service;
  }
  const Location &getLocation() const {
    return location;
  }

  void setCep(const std::string &value) {
    cep = value;
  }
  void setState(const std::string &value) {
    state = value;
  }
  void setCity(const std::string &value) {
    city = value;
  }
  void setNeighborhood(const std::string &value) {
    neighborhood = value;
  }
  void setStreet(const std::string &value) {
    street = value;
  }
  void setService(const std::string &value) {
    service = value;
  }
  void setLocation(const Location &value) {
    location = value;
  }

  Json::Value toJson() const {
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
    return jsonCep;
  }
};

#endif // CEP_RESPONSE_H