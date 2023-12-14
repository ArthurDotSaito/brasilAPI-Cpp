#include "BrasilAPIHandlerBase.h"
#include "Response/CptecCidadesResponse.h"

class CorretorasHandler: public BrasilAPIHandlerBase{
    public:
        void listAllCities(std::function<void(const CptecCidadesResponse&)> callback);
        void searchByTerms(std::string cityName , std::function<void(const CptecCidades&)> callback);
};