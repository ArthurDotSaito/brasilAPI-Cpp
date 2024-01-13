#include "BrasilAPIHandlerBase.h"
#include "Response/CepResponse.h"
#include "Response/ErrorResponse.h"
#include <variant>

class CepHandler : public BrasilAPIHandlerBase {
  public:
  void getCep(int cep, std::function<void(std::variant<CepResponse, ErrorResponse>)> callback);
  void getCepV2(int cep, std::function<void(std::variant<CepResponse, ErrorResponse>)> callback);
};