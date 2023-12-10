#include "BrasilAPIHandlerBase.h"
#include "Response/CepResponse.h"

class CepHandler: public BrasilAPIHandlerBase{
    public:
        void getCep(const std::string& cep, std::function<void(const CepResponse&)> callback);
};