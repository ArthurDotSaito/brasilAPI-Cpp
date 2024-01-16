#include "BrasilAPIHandlerBase.h"
#include "Response/ErrorResponse.h"
#include "Response/FipeResponse.h"
#include <variant>

class FipeHandler : public BrasilAPIHandlerBase {
  public:
  void listarFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
      std::function<void(std::variant<FipeMarcas, ErrorResponse>)> callback);

  void listFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
      std::function<void(const FipePrecos &)> callback);

  void listFipeTabelas(std::function<void(const FipeTabelasReferencia &)> callback);
};
