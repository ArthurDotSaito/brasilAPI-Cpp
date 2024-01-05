#include "BrasilAPIHandlerBase.h"
#include "Response/FipeResponse.h"

class FipeHandler : public BrasilAPIHandlerBase {
  public:
  void getFipe(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
      std::function<void(const FipeMarcas &)> callback);
};
