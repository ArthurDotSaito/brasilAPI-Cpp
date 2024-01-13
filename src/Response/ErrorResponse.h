#ifndef ERROR_RESPONSE_H
#define ERROR_RESPONSE_H

#include <string>

struct ErrorResponse {
  int errorCode;
  std::string errorMessage;
};

#endif // ERROR_RESPONSE_H