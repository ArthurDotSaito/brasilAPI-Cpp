#ifndef PROVIDER_VALIDATION_H
#define PROVIDER_VALIDATION_H

#include <optional>
#include <set>
#include <sstream>
#include <string>

bool isValidProvider(const std::string &provider) {
  static const std::set<std::string> validProviders = {"dados-abertos-br", "gov", "wikipedia"};
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

#endif // PROVIDER_VALIDATION_H