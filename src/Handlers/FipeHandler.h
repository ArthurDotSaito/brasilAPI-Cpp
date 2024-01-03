#include "BrasilAPIHandlerBase.h"
#include "Response/FipeResponse.h"

class FipeHandler : public BrasilAPIHandlerBase {
  public:
  void getFipe(const std::string &tipoVeiculo, int tabela_referencia, std::function<void(const FipeResponse &)> callback);
};
