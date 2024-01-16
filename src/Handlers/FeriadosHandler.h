#include "BrasilAPIHandlerBase.h"
#include "Response/ErrorResponse.h"
#include "Response/FeriadosResponse.h"
#include <variant>

class FeriadosHandler : public BrasilAPIHandlerBase {
  public:
  void listHolidaysAtYear(int ano, std::function<void(std::variant<FeriadosResponse, ErrorResponse>)> callback);
};
