#include "BrasilAPIHandlerBase.h"
#include "Response/IBGEResponse.h"

class IBGEHandler : public BrasilAPIHandlerBase {
  public:
  void listarMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
      std::function<void(std::variant<IBGEMunicipiosResponse, ErrorResponse>)> callback);

  void listRegioes(std::function<void(const IBGERegioesResponse &)> callback);
  void getEstado(const std::string &uf, std::function<void(const Estado &)> callback);
};
