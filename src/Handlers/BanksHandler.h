#include "BrasilAPIHandlerBase.h"
#include "Response/BankResponse.h"
#include "Response/ErrorResponse.h"
#include <functional>
#include <variant>

class BanksHandler : public BrasilAPIHandlerBase {
  public:
  void getAllBanks(std::function<void(std::variant<BankResponse, ErrorResponse>)> callback);
  void getBanksByCode(int code, std::function<void(std::variant<Bank, ErrorResponse>)> callback);
};
