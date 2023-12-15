#include "BrasilAPIHandlerBase.h"
#include "Response/CptecCidadesResponse.h"
#include "Response/CptecCapitaisResponse.h"

class CptecHandler: public BrasilAPIHandlerBase{
    public:
        void listAllCities(std::function<void(const CptecCidadesResponse&)> callback);
        void searchByTerms(std::string cityName , std::function<void(const CptecCidadesResponse&)> callback);
        void getCapitais(std::function<void(const CptecCapitaisResponse&)> callback);
};