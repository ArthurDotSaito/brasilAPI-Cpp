#include "BrasilAPIHandlerBase.h"
#include "Response/DDD.h"

class DDDHandler : public BrasilAPIHandlerBase {
  public:
  void listStateAndCities(int ddd, std::function<void(const DDDResponse &)> callback);
};