#include "BrasilAPIHandlerBase.h"
#include "Response/CorretorasResponse.h"
#include "Response/ErrorResponse.h"
#include <variant>

class CorretorasHandler : public BrasilAPIHandlerBase {
  public:
  void getAllCorretoras(std::function<void(std::variant<CorretorasResponse, ErrorResponse>)> callback);
  void getCorretorasByCnpj(std::string cnpj, std::function<void(std::variant<Corretoras, ErrorResponse>)> callback);
};