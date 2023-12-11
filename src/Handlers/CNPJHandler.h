#include "BrasilAPIHandlerBase.h"
#include "Response/CNPJResponse.h"

class CNPJHandler: public BrasilAPIHandlerBase{
    public:
        void getCNPJ(std::string cnpj, std::function<void(const CNPJResponse&)> callback);
};