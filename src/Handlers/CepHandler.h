#include "BrasilAPIHandlerBase.h"
#include "Response/CepResponse.h"

class CepHandler: public BrasilAPIHandlerBase{
    public:
        void getCep(int cep, std::function<void(const CepResponse&)> callback);
        void getCepV2(int cep, std::function<void(const CepResponse&)> callback);
};