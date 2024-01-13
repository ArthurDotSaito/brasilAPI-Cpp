#include "BrasilAPIHandlerBase.h"
#include "Response/CNPJResponse.h"
#include "Response/ErrorResponse.h"
#include <variant>

class CNPJHandler : public BrasilAPIHandlerBase {
  public:
  void getCNPJ(std::string cnpj, std::function<void(std::variant<CNPJResponse, ErrorResponse>)> callback);
};