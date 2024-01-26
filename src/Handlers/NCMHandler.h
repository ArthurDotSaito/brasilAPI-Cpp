#include "BrasilAPIHandlerBase.h"
#include "Response/NCMResponse.h"
#include <string>

class NCMHandler : public BrasilAPIHandlerBase {
  public:
  void listarTodosNCM(std::function<void(std::variant<NCMResponse, ErrorResponse>)> callback);
};
