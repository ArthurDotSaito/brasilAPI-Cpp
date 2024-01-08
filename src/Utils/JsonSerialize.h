#ifndef JSON_SERIALIZE_H
#define JSON_SERIALIZE_H

#include <json/json.h>
#include <string>
#include <vector>

class JsonSerialize {
  public:
  virtual ~JsonSerialize() = default;
  virtual Json::Value toJson() const = 0;

  virtual std::string serialize() const {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, this->toJson());
  }
};

#endif // JSON_SERIALIZE_H