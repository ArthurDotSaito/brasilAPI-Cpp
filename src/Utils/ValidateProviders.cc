#include "ValidateProviders.h"

#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

bool isValidProvider(const std::string &provider) {
  static const std::set<std::string> validProviders = {"dados-abertos-br", "gov", "wikipedia"};
  return validProviders.find(provider) != validProviders.end();
}

bool isValidISBNProvider(const std::string &provider) {
  static const std::set<std::string> validProviders = {"cbl", "mercado-editorial", "open-library", "google-books"};
  return validProviders.find(provider) != validProviders.end();
}

bool validateProviders(const std::optional<std::string> &providers) {
  if (!providers)
    return true;

  std::istringstream ss(*providers);
  std::string provider;
  while (std::getline(ss, provider, ',')) {
    if (!isValidProvider(provider)) {
      return false;
    }
  }
  return true;
}

bool validateISBNProviders(const std::optional<std::vector<std::string>> &providers) {
  if (providers) {
    for (const auto &provider : *providers) {
      if (!isValidISBNProvider(provider)) {
        return false;
      }
    }
  }
  return true;
}
