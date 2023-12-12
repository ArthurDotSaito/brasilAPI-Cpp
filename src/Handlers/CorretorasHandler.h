#include "BrasilAPIHandlerBase.h"
#include "Response/CorretorasResponse.h"

class CorretorasHandler: public BrasilAPIHandlerBase{
    public:
        void getAllCorretoras(std::function<void(const CorretorasResponse&)> callback);
        void getCorretorasByCnpj(std::string , std::function<void(const Corretoras&)> callback);
};