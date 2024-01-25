#include "BrasilAPIHandlerBase.h"
#include "Response/ISBNProviders.h"
#include "Response/ISBNResponse.h"
#include <string>

class ISBNHandler : public BrasilAPIHandlerBase {
  public:
  void getLivrosBrasil(const std::string &isbn, std::initializer_list<std::string> providers,
      std::function<void(std::variant<BookInfo, ErrorResponse>)> callback);
};
