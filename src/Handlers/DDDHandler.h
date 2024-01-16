#include "BrasilAPIHandlerBase.h"
#include "Response/DDD.h"
#include "Response/ErrorResponse.h"
#include <variant>

class DDDHandler : public BrasilAPIHandlerBase {
  public:
  void listStateAndCities(int ddd, std::function<void(std::variant<DDDResponse, ErrorResponse>)> callback);
};