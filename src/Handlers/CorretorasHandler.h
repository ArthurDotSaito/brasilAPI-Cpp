#include "BrasilAPIHandlerBase.h"
#include "Response/CorretorasResponse.h"

class CorretorasHandler: public BrasilAPIHandlerBase{
    public:
        void getAllCorretoras(std::function<void(const CorretorasResponse&)> callback);
        void getCorretorasByCnpj(int cnpj, std::function<void(const Corretoras&)> callback);
};