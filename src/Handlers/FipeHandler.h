#include "BrasilAPIHandlerBase.h"
#include "Response/FipeResponse.h"

class FipeHandler : public BrasilAPIHandlerBase {
  public:
  void listFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
      std::function<void(const FipeMarcas &)> callback);
  void listFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
      std::function<void(const FipePrecos &)> callback);
  void listFipeTabelas(std::function<void(const FipeTabelasReferencia &)> callback);
};
