#include "BrasilAPIHandlerBase.h"
#include "Response/BankResponse.h"
#include <json/json.h>
#include <functional>

class BanksHandler: public BrasilAPIHandlerBase{
    public:
        void getAllBanks(std::function<void(const BankResponse&)> callback);
        void getBanksByCode(int code, std::function<void(const Bank&)> callback);
};

