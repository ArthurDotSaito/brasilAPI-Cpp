#include "BrasilAPIHandlerBase.h"
#include "Response/NCMResponse.h"
#include <string>

class ISBNHandler : public BrasilAPIHandlerBase {
  public:
  void listAllNCM(std::function<void(std::variant<NCMResponse, ErrorResponse>)> callback);
};
