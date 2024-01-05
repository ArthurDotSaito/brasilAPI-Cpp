#include <json/json.h>
#include <string>
#include <vector>

class JsonSerialize {
  public:
  virtual ~JsonSerialize() = default;
  virtual Json::Value toJson() const = 0;

  std::string serialize() const {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "  ";
    return Json::writeString(builder, this->toJson());
  }
};
