#include "BrasilAPIFacadeBase.h"
#include <json/json.h>
#include <functional>

class BanksFacade: public BrasilAPIFacadeBase{
    public:
        void getBanks(std::function<void(const Json::Value&)> callback);
        void getBanksByCode(int code, std::function<void(const Json::Value&)> callback);
};