#include "BrasilAPIHandlerBase.h"
#include "Response/ISBNResponse.h"

class ISBNHandler : public BrasilAPIHandlerBase {
  public:
  void getLivrosBrasil(const std::string &isbn, const std::vector<Provider> &providers = {},
      std::function<void(std::variant<BookInfo, ErrorResponse>)> callback);
};
