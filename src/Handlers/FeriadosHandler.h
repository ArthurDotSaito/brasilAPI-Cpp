#include "BrasilAPIHandlerBase.h"
#include "Response/FeriadosResponse.h"

class FeriadosHandler : public BrasilAPIHandlerBase {
  public:
  void getFeriados(int ano, std::function<void(const FeriadosResponse &)> callback);
};
