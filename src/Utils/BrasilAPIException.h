
#define BRASIL_API_EXCEPTION_H

#include <stdexcept>
#include <string>

class BrasilAPIException : public std::runtime_error {
  private:
  int statusCode;
  std::string url;

  public:
  BrasilAPIException(const std::string &message, int statusCode, const std::string &url)
      : std::runtime_error(message), statusCode(statusCode), url(url) {
  }

  int getStatusCode() const {
    return statusCode;
  }
  const std::string &getURL() const {
    return url;
  }
};
