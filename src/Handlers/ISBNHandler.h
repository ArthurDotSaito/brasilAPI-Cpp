#include "BrasilAPIHandlerBase.h"
#include "Response/ISBNProviders.h"
#include "Response/ISBNResponse.h"

class ISBNHandler : public BrasilAPIHandlerBase {
  public:
  void getLivrosBrasil(const std::string &isbn, const std::optional<std::vector<Provider>> &providers,
      std::function<void(std::variant<BookInfo, ErrorResponse>)> callback);
};
