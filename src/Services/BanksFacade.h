#include "BrasilAPIFacadeBase.h"
#include "Response/BankResponse.h"
#include <json/json.h>
#include <functional>

class BanksFacade: public BrasilAPIFacadeBase{
    public:
        void getAllBanks(std::function<void(const BankResponse&)> callback);
        void getBanksByCode(int code, std::function<void(const Json::Value&)> callback);
};

