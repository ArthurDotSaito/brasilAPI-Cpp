#ifndef BASE_RESPONSE_H
#define BASE_RESPONSE_H
#include "Utils/JsonSerialize.h"
#include <string>

class BaseResponse {
  public:
  std::string calledURL;
  std::string jsonResponse;
};

#endif // BASE_RESPONSE_H