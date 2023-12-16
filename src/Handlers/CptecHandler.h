#include "BrasilAPIHandlerBase.h"
#include "Response/CondicoesAeroporto.h"
#include "Response/CptecCapitaisResponse.h"
#include "Response/CptecCidadesResponse.h"

class CptecHandler : public BrasilAPIHandlerBase {
  public:
  void listAllCities(std::function<void(const CptecCidadesResponse &)> callback);
  void searchByTerms(std::string cityName, std::function<void(const CptecCidadesResponse &)> callback);
  void getCapitais(std::function<void(const CptecCapitaisResponse &)> callback);
  void getCondicoesAeroporto(std::string icao, std::function<void(const CptecAeroporto &)> callback);
};