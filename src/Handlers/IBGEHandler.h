#include "BrasilAPIHandlerBase.h"
#include "Response/IBGEResponse.h"

class IBGEHandler : public BrasilAPIHandlerBase {
  public:
  void listarMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
      std::function<void(std::variant<IBGEMunicipiosResponse, ErrorResponse>)> callback);

  void listarRegioes(std::function<void(std::variant<IBGERegioesResponse, ErrorResponse>)> callback);
  void getEstado(const std::string &uf, std::function<void(const Estado &)> callback);
};
