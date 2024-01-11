#include "BrasilAPIHandlerBase.h"
#include "Response/IBGEResponse.h"

class IBGEHandler : public BrasilAPIHandlerBase {
  public:
  void listMunicipios(const std::string &siglaUf, const std::optional<std::string> &providers,
      std::function<void(const IBGEMunicipiosResponse &)> callback);

  void listRegioes(std::function<void(const IBGERegioesResponse &)> callback);
};
