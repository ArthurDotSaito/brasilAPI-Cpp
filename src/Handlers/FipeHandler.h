#include "BrasilAPIHandlerBase.h"
#include "Response/ErrorResponse.h"
#include "Response/FipeResponse.h"
#include <variant>

class FipeHandler : public BrasilAPIHandlerBase {
  public:
  void listarFipeMarcas(const std::optional<std::string> &tipoVeiculo, const std::optional<int> &tabela_referencia,
      std::function<void(std::variant<FipeMarcas, ErrorResponse>)> callback);

  void listarFipePreco(const std::string &codigoFipe, const std::optional<int> &tabela_referencia,
      std::function<void(std::variant<FipePrecos, ErrorResponse>)> callback);

  void listarFipeTabelas(std::function<void(std::variant<FipeTabelasReferencia, ErrorResponse>)> callback);
};
